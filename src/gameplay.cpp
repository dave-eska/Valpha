#include "gameplay.hpp"

#include <string>
#include <cstring>

#include "global_variable.hpp"

#include <raylib.h>

#include "scene.hpp"
#include "ability.hpp"

void Gameplay::Update(float dt){

	float wheelMove = GetMouseWheelMove();

	if(wheelMove != 0.0f) {
		camera.zoom += wheelMove * 0.1f; // Adjust zoom sensitivity if needed
		if (camera.zoom > camMax) camera.zoom = camMax;
		if (camera.zoom < camMin) camera.zoom = camMin;
	}

	if(!isTyping){
        camera.target = {player->getBody().x + (player->getBody().width/2), player->getBody().y + (player->getBody().height/2)};
        player->Move(GetFrameTime());

		if(IsKeyPressed(KEY_ESCAPE)) returnCode = 1;
    }

	level->Update(GetFrameTime());
	am->Update();
}

void Gameplay::Draw(){
	BeginMode2D(camera);

	level->Draw();
	player->Animate();

	EndMode2D();

	am->Draw();
	am->DrawUI();

	for(int i=0;i<chatlog.size();i++){
		auto& chat = chatlog[i];
		DrawText(chat.c_str(), 0, GetScreenHeight()/2 + i*20, 20, WHITE);
	}

	if(isDebugging){
		DrawText(std::to_string(player->getSpeed()).c_str(), 0, 0, 35, BLACK);
		DrawText(isTyping ? "IsTyping" : "NotTyping", 0, 35, 35, BLACK);
		DrawText(std::to_string(GetFPS()).c_str(), 0, GetScreenHeight() - 50, 35, GREEN);
	}
}

void Gameplay::Unload(){
	delete(level);

	delete(player);
	delete(am);

	delete(&camMax);
	delete(&camMin);
}

Gameplay::Gameplay() : Scene("Gameplay Test", 0.5){
	level = new hcm::Level("res/levels/test.json");

	camera.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };

	player = new hcm::Player("res/img/player_atlas.png", {TILE_SIZE*2,TILE_SIZE*3}, 500, *level->b2world);
	am = new hcm::AbilityManager(*player);

	camMax = 3.0f;
	camMin = 0.1f;

	returnCode = 1;
}
