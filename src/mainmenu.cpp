#include "mainmenu.hpp"
#include "raylib.h"
#include "scene.hpp"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

void MainMenu::Update(float dt){
}

void MainMenu::Draw(){
	DrawText("Valpha", 200, 50, 200, WHITE);
	if(GuiButton((Rectangle){100, 320, 150*2, 30*2}, "Gameplay")){
		returnCode = 2;
	}

	if(GuiButton((Rectangle){100, 420, 150*2, 30*2}, "LevelEditor")){
		returnCode = 1;
	}
}

void MainMenu::Unload(){
}

MainMenu::MainMenu() : hcm::Scene("Valpha v0.1", 1.0f){
	GuiSetStyle(DEFAULT, TEXT_SIZE, 24);  // Default text size is 10
}
