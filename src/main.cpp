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

vMode currentMode = vMode::MainMenu;
MainMenu* mainmenu;
Gameplay* gameplay;
hama::LevelEditor* leveleditor;

std::string userInput;
float clearChat = 10.0f;

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
static const int screenWidth = 1600;
static const int screenHeight = 900;

// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static vMode transToScreen = vMode::Unkown;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void ChangeToScreen(int screen);     // Change to screen, no transition effect
static void ChangeToFullScreen(void);          // Change window into fullscreen mode

static void TransitionToScreen(int screen); // Request transition to next screen
static void UpdateTransition(void);         // Update transition effect
static void DrawTransition(void);           // Draw transition effect (full-screen rectangle)

static void UpdateDrawFrame(void);          // Update and draw one frame

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(){
	// Initialization

	Json::Reader jsonreader;

	std::ifstream file("config.json");
	jsonreader.parse(file, config);

	//---------------------------------------------------------

	if(!config["showDebugLog"].asBool()) SetTraceLogLevel(LOG_NONE);
	InitWindow(screenWidth, screenHeight, "Kookies");

	InitAudioDevice();      // Initialize audio device
	//
	// Load the icon image
	Image icon = LoadImage("res/icon.png");

	// Set the window icon
	SetWindowIcon(icon);

	// Load global data (assets that must be available in all screens, i.e. font)
	isDebugging = false;
	isTyping = false;

	// Setup and init first screen
	currentMode = vMode::MainMenu;
	mainmenu = new MainMenu();

	SetExitKey(KEY_NULL);
	SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	if(config["fullscreen"].asBool())
		ToggleFullscreen();

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
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

		UpdateDrawFrame();
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	// Unload current screen data before closing
	switch (currentMode)
	{
		case vMode::MainMenu: mainmenu = new MainMenu(); break;
		case vMode::Gameplay: gameplay = new Gameplay(); break;
		case vMode::LevelEditor: leveleditor = new hama::LevelEditor(); break;
		default: break;
	}

	CloseAudioDevice();     // Close audio context

	CloseWindow();          // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}

//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------
// Change to next screen, no transition
static void ChangeToScreen(vMode screen)
{
	// Unload current screen
	switch (currentMode)
	{
		case vMode::MainMenu: mainmenu->Unload(); break;
		case vMode::Gameplay: gameplay->Unload(); break;
		case vMode::LevelEditor: leveleditor->Unload(); break;
		default: break;
	}
	switch (screen)
	{
		case vMode::MainMenu: mainmenu = new MainMenu(); break;
		case vMode::Gameplay: gameplay = new Gameplay(); break;
		case vMode::LevelEditor: leveleditor = new hama::LevelEditor(); break;
		default: break;
	}

	currentMode = screen;
}

static void ChangeToFullScreen(void){
	ToggleFullscreen();
}

// Request transition to next screen
static void TransitionToScreen(vMode screen)
{
	onTransition = true;
	transFadeOut = false;
	transFromScreen = (int)currentMode;
	transToScreen = screen;
	transAlpha = 0.0f;
}

// Update transition effect (fade-in, fade-out)
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
			switch(transFromScreen)
			{
				default: break;
			}

			// Load next screen
			switch(transToScreen)
			{
				case vMode::MainMenu: mainmenu = new MainMenu(); break;
				case vMode::Gameplay: gameplay = new Gameplay(); break;
				case vMode::LevelEditor: leveleditor = new hama::LevelEditor(); break;
				default: break;
			}

			currentMode = transToScreen;

			// Activate fade out effect to next loaded screen
			transFadeOut = true;
		}
	}
	else  // Transition fade out logic
{
		transAlpha -= 0.02f;

		if (transAlpha < -0.01f)
		{
			transAlpha = 0.0f;
			transFadeOut = false;
			onTransition = false;
			transFromScreen = -1;
			transToScreen = vMode::Unkown;
		}
	}
}

// Draw transition effect (full-screen rectangle)
static void DrawTransition(void)
{
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
	// Update
	//----------------------------------------------------------------------------------

	if (!onTransition){
		switch(currentMode){
			case vMode::MainMenu:
				{
					mainmenu->Update(GetFrameTime());

					if(mainmenu->getReturnCode() == 1) {mainmenu->resetReturnCode(); TransitionToScreen(vMode::LevelEditor);}
					else if(mainmenu->getReturnCode() == 2) {mainmenu->resetReturnCode(); TransitionToScreen(vMode::Gameplay);}
					else if(mainmenu->getReturnCode() == 3) {mainmenu->resetReturnCode(); TransitionToScreen(vMode::MainMenu);}

			}break;
			case vMode::Gameplay:
				{
					gameplay->Update(GetFrameTime());

					if(gameplay->getReturnCode() == 1) {gameplay->resetReturnCode(); TransitionToScreen(vMode::MainMenu);}

			} break;
			case vMode::LevelEditor:
				{
					leveleditor->Update(GetFrameTime());

					if(leveleditor->getReturnCode() == 1) {leveleditor->resetReturnCode(); TransitionToScreen(vMode::MainMenu);}
			}
			default: break;
		}
	}
	else UpdateTransition();    // Update transition (fade-in, fade-out)
	//----------------------------------------------------------------------------------

	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();

	ClearBackground(DARKGRAY);

	switch(currentMode)
	{
		case vMode::MainMenu: mainmenu->Draw(); break;
		case vMode::Gameplay: gameplay->Draw(); break;
		case vMode::LevelEditor: leveleditor->Draw(); break;
		default: break;
	}

	// Draw full screen rectangle in front of everything
	if(onTransition) DrawTransition();

	DrawFPS(GetScreenWidth()-50, GetScreenHeight()-30);

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
	//----------------------------------------------------------------------------------
}
