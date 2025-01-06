#include <string>
#include <fstream>
#include <cstring>

#include <json/reader.h>

#include <raylib.h>

#include "hama.hpp"
#include "mainmenu.hpp"
#include "utils/fileUtil.hpp"

#include "global_variable.hpp"
#include "gameplay.hpp"

enum class vMode{
	Gameplay,
	LevelEditor,
	MainMenu,
	Unkown
};

void TypingCode(std::string& userInput){
	char c = GetCharPressed();
	if (c){
		userInput.push_back(c);
	}

	if(IsKeyPressed(KEY_BACKSPACE) && !userInput.empty())
		userInput.pop_back();
	if(IsKeyPressed(KEY_ENTER)){
		if(!userInput.empty()){
			chatlog.push_back(userInput);
			userInput.clear();
		}
		isTyping=false;
	}
}

static void changeVMode(vMode newMode);

static void fancyStuff();
static void ChangeToScreen(vMode mode);
static void TransitionToScreen(vMode mode);
static void UpdateTransition();

static Gameplay* gameplay;
static MainMenu* mainmenu;
static hama::LevelEditor* levelEditor;

static int currentMode;

static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static vMode transToMode = vMode::Unkown;

int main(){
	Json::Reader jsonreader;

	std::ifstream file("res/config.json");
	jsonreader.parse(file, config);

	if(!config["showDebugLog"].asBool()) SetTraceLogLevel(LOG_NONE);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(1920, 1080, "valpha v0.1");

	isDebugging = false;
	isTyping = false;

	std::string userInput;
	float clearChat = 10.0f;

	ChangeToScreen(vMode::MainMenu);

	SetTargetFPS(60);
	while(!WindowShouldClose()){
		if(IsKeyPressed(KEY_X)) isDebugging = !isDebugging;
		if(IsKeyPressed(KEY_PAGE_UP)) isTyping = true;

		if(clearChat > 0 && !chatlog.empty()) clearChat -= GetFrameTime();
		if(clearChat <= 0){
			std::string strText = readFile("chatLogs.txt");
			for(auto& e : chatlog){
				strText.append("\n");
				strText.append(e);
			}

			char* text = new char[strText.length() + 1];
			std::strcpy(text, strText.c_str());

			SaveFileText("chatLogs.txt", text);

			delete[] text;
			chatlog.clear();
		}

		if(clearChat <= 0) clearChat = 10.0f;

		fancyStuff();

		BeginDrawing();

		ClearBackground(GRAY);

		switch(currentMode)
		{
			case (int)vMode::MainMenu: mainmenu->Draw(); break;
			case (int)vMode::Gameplay: gameplay->Draw(); break;
			case (int)vMode::LevelEditor: levelEditor->Draw(); break;
			default: break;
		}

		// Draw full screen rectangle in front of everything
		if(onTransition) DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));


		for(int i=0;i<chatlog.size();i++){
			auto& chat = chatlog[i];
			DrawText(chat.c_str(), 0, GetScreenHeight()/2 + i*20, 20, WHITE);
		}

		if(isTyping){
			TypingCode(userInput);
			DrawRectangleRec({(float)GetScreenWidth()-520, 10, 500, 35}, {20,20,20,130});
			DrawText(userInput.c_str(), (float)GetScreenWidth()-500, 10, 35, BLACK);
		}


		EndDrawing();
	}

	CloseWindow();

	return 0;
}

static void changeVMode(vMode newMode){
	currentMode = (int)newMode;
}

static void fancyStuff(){
	if (!onTransition)
	{
		switch(currentMode)
		{
		case (int)vMode::MainMenu:
				{
					mainmenu->Update(GetFrameTime());
					if(mainmenu->getReturnCode() == 1) {mainmenu->resetReturnCode(); TransitionToScreen(vMode::Gameplay);}
					else if(mainmenu->getReturnCode() == 2) {mainmenu->resetReturnCode(); TransitionToScreen(vMode::LevelEditor);}
			}break;
		case (int)vMode::Gameplay:
				{
					gameplay->Update(GetFrameTime());
					if(gameplay->getReturnCode() == 1) {gameplay->resetReturnCode(); TransitionToScreen(vMode::MainMenu);}

			}break;
		case (int)vMode::LevelEditor:
				{
					levelEditor->Update(GetFrameTime());
					if(levelEditor->getReturnCode() == 1) {levelEditor->resetReturnCode(); TransitionToScreen(vMode::MainMenu);}
			}break;
			default: break;
		}
	}
	else UpdateTransition();    // Update transition (fade-in, fade-out)

}

// Request transition to next screen
static void TransitionToScreen(vMode mode)
{
	onTransition = true;
	transFadeOut = false;
	transFromScreen = currentMode;
	transToMode = mode;
	transAlpha = 0.0f;
}

static void ChangeToScreen(vMode mode)
{
	// Unload current screen
	switch (currentMode)
	{
		case (int)vMode::MainMenu: mainmenu->Unload(); break;
		case (int)vMode::Gameplay: gameplay->Unload(); break;
		case (int)vMode::LevelEditor: levelEditor->Unload(); break;
		default: break;
	}

	// Init next screen
	switch (mode)
	{
		case vMode::MainMenu: mainmenu = new MainMenu(); break;
		case vMode::Gameplay: gameplay = new Gameplay(); break;
		case vMode::LevelEditor: levelEditor = new hama::LevelEditor(); break;
		default: break;
	}

	currentMode = (int)mode;
}

static void UpdateTransition(void)
{
	if (!transFadeOut)
	{
		transAlpha += 0.05f;

		// NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
		// For that reason we compare against 1.01f, to avoid last frame loading stop
		if (transAlpha > 1.01f)
		{
			transAlpha = 1.0f;

			// Unload current screen
			switch (currentMode)
			{
				case (int)vMode::MainMenu: mainmenu->Unload(); break;
				case (int)vMode::Gameplay: gameplay->Unload(); break;
				case (int)vMode::LevelEditor: levelEditor->Unload(); break;
				default: break;
			}

			// Init next screen
			switch (transToMode)
			{
				case vMode::MainMenu: mainmenu = new MainMenu(); break;
				case vMode::Gameplay: gameplay = new Gameplay(); break;
				case vMode::LevelEditor: levelEditor = new hama::LevelEditor(); break;
				default: break;
			}

			currentMode = (int)transToMode;

			// Activate fade out effect to next loaded screen
			transFadeOut = true;
		}
	}
	else{
		transAlpha -= 0.02f;

		if (transAlpha < -0.01f)
		{
			transAlpha = 0.0f;
			transFadeOut = false;
			onTransition = false;
			transFromScreen = -1;
			transToMode = vMode::Unkown;
		}
	}
}
