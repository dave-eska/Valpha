#include "mainmenu.hpp"
#include "scene.hpp"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

void MainMenu::Update(float dt){
}

void MainMenu::Draw(){
	if(GuiButton((Rectangle){ (float)GetScreenWidth() - 100, (float)GetScreenHeight() - 50, 80, 30 }, "Gameplay")){
		returnCode = 1;
	}

	if(GuiButton((Rectangle){ (float)GetScreenWidth() - 230, (float)GetScreenHeight() - 50, 110, 30 }, "LevelEditor")){
		returnCode = 2;
	}

}

void MainMenu::Unload(){
}

MainMenu::MainMenu() : hcm::Scene("Valpha v0.1", 1.0f){
}
