#include "global_variable.hpp"

#include "json/reader.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include <raylib.h>

#include "utils/fileUtil.hpp"

#include "gameplay.hpp"

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

int main(){

	std::cout<<"hello world!"<<std::endl;
	std::cout<<"typing on warnet"<<std::endl;
	
	// Initialization

    Json::Reader jsonreader;

    std::ifstream file("res/config.json");
    jsonreader.parse(file, config);

	if(!config["showDebugLog"].asBool()) SetTraceLogLevel(LOG_NONE);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	InitWindow(1920, 1080, "Melieska");

	Gameplay* gameplay = new Gameplay();

	isDebugging = false;
	isTyping = false;

	std::string userInput;
	float clearChat = 10.0f;

	SetTargetFPS(60);
	while(!WindowShouldClose()){
		if(IsKeyPressed(KEY_X)) isDebugging = !isDebugging;
		if(IsKeyPressed(KEY_PAGE_UP)) isTyping = true;

		gameplay->Update(GetFrameTime());

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


		BeginDrawing();

		ClearBackground(GRAY);

		gameplay->Draw();

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
