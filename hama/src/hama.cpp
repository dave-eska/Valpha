#include "hama.hpp"

#include "json/reader.h"
#include "json/value.h"
#include "json/writer.h"
#include <algorithm>

#include <fstream>
#include <iostream>
#include <memory>
#include <raymath.h>
#include <string>

#include "global_functions.hpp"
#include "global_variable.hpp"
#include "raylib.h"
#include "scene.hpp"
#include "tile.hpp"
#include "world.hpp"

#define MaxTileID 3.5

namespace hama{

std::vector<std::string> tilesToStrings(std::vector<std::unique_ptr<hcm::Tile>>& tiles, Vector2 canvas_size, int total_layers){
	std::vector<std::string> result;

	std::string layer;

	for(int j=0;j<total_layers;j++){
		for(int i=0;i<tiles.size();++i){
			if(tiles[i]->getZ() == j){
				std::string tileID = std::to_string(tiles[i]->getID());
				for(const char& c:tileID)
				layer.push_back(c);
				layer.push_back(' ');
				if((i+1) % (int)canvas_size.x == 0 && i != 0){
					layer.push_back('\n');
				}
			}
		}

		// Remove the spaces behind newlines
		for(int i=0;i<layer.size();i++){
			if(layer[i] == ' ' && layer[i+1] == '\n'){
				layer.erase(layer.begin() + i);
			}
		}

		result.push_back(layer);
		layer.clear();
	}

	return result;
}

void LevelEditor::fill(std::vector<std::unique_ptr<hcm::Tile>>& canvas, int x, int y, int z, int targetID, int fillID, std::unordered_set<int>& visited) {
	// Check if current position is within canvas bounds
	if(x < 0 || y < 0 || x >= (this->level->getSize().x*TILE_SIZE) || y >= (this->level->getSize().y*TILE_SIZE)) return;

	// Calculate index of the tile in the vector
	auto it = std::find_if(canvas.begin(), canvas.end(), [x, y, z](const auto& tile){
		return tile->getBody().x == x && tile->getBody().y == y && tile->getZ() == z;
	});


	if(it == canvas.end()) return;
	int index = (*it)->getSlot();

	// Check if current position has already been visited or has different ID or z value
	if(visited.find(index) != visited.end() || canvas[index]->getID() != targetID || canvas[index]->getZ() != z)
		return;

	// Fill current tile with fill ID
	int prevSlot = canvas[index]->getSlot();
	canvas[index] = std::make_unique<hcm::Tile>(hcm::Tile(fillID, canvas[index]->getPos(), canvas[index]->getZ()));
	canvas[index]->setSlot(prevSlot);

	// Add current index to visited set
	visited.insert(index);

	// Perform fill operation recursively in all four directions
	fill(canvas, x + TILE_SIZE, y, z, targetID, fillID, visited); // Right
	fill(canvas, x - TILE_SIZE, y, z, targetID, fillID, visited); // Left
	fill(canvas, x, y + TILE_SIZE, z, targetID, fillID, visited); // Down
	fill(canvas, x, y - TILE_SIZE, z, targetID, fillID, visited); // Up
}

void LevelEditor::Update(float dt){
	// Camera Movement
	if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) or IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)){
		Vector2 delta = GetMouseDelta();
		delta = Vector2Scale(delta, -1.0f/camera.zoom);

		camera.target = Vector2Add(camera.target, delta);
	}

	if(IsKeyDown(KEY_LEFT_CONTROL)){
		if(IsKeyPressed(KEY_S)){
			writeTileJson(*level, {0,0}, "save.json");
		}
	}

	// Zoom with mouse wheel
	float wheel = GetMouseWheelMove();
	Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
	if(!IsKeyDown(KEY_LEFT_CONTROL)){
		if(wheel != 0){
			camera.offset = GetMousePosition();
			camera.target = mouseWorldPos;
			const float zoomIncrement = 0.125f;
			camera.zoom += (wheel*zoomIncrement);

			if (camera.zoom < zoomIncrement) camera.zoom = zoomIncrement;
		}
	}else{
		if(wheel != 0){
			if(wheel > 0) {
				currentTile.tileID++;
				if (currentTile.tileID > maxTile) {
					currentTile.tileID = 0; // Wrap around to the minimum tileID
				}
			}else if(wheel< 0) {
				currentTile.tileID--;
				if (currentTile.tileID < 0) {
					currentTile.tileID = maxTile; // Wrap around to the maximum tileID
				}
			}
			currentTile = hcm::newItem<hcm::Tile>(currentTile.tileID);
		}
	}

	hcm::changeIntWithKey(currentMode, KEY_D, KEY_A, (int)Modes::EOE-1, 0);
	hcm::changeIntWithKey(currentZLayer, KEY_W, KEY_S, 2, 0);

	if(IsKeyPressed(KEY_B)) currentMode = (int)Modes::Pencil;
	if(IsKeyPressed(KEY_E)) currentMode = (int)Modes::Eraser;
	if(IsKeyPressed(KEY_I)) currentMode = (int)Modes::Eyedrop;

	for(auto& tile : level->tiles){
		tile->setIsTouchingMouse(false);

		if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), tile->getBody())){
			tile->setIsTouchingMouse(true);
		}

		switch((Modes)currentMode){
			case hama::Modes::Pencil:
				{
					if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && tile->getIsTouchingMouse() && currentZLayer == tile->getZ()){
						int slot = tile->getSlot();
						tile = std::make_unique<hcm::Tile>(hcm::Tile(currentTile.tileID, tile->getPos(), tile->getZ()));
						tile->setSlot(slot);
					}
				}
			break;
			case hama::Modes::Eraser:
				{
					if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && tile->getIsTouchingMouse() && currentZLayer == tile->getZ()){
						int slot = tile->getSlot();
						tile = std::make_unique<hcm::Tile>(hcm::Tile(0, tile->getPos(), tile->getZ()));
						tile->setSlot(slot);
					}else if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
						auto it = std::find_if(level->tiles.begin(), level->tiles.end(), [this](const auto& tile){
							return  this->selectedTile.idx == tile->getSlot();
						});
						if(it != level->tiles.end()){
						}

						tile = std::make_unique<hcm::Tile>(hcm::Tile(0, tile->getPos(), tile->getZ()));
						tile->setSlot(selectedTile.idx);
					}
				}
			break;
			case hama::Modes::Eyedrop:
				{
					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && tile->getIsTouchingMouse() && currentZLayer == tile->getZ()){
						currentTile = hcm::newItem<hcm::Tile>(tile->getID());
					}
				}
			break;
			case hama::Modes::SingleSelect:
				{
					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && tile->getIsTouchingMouse() && currentZLayer == tile->getZ()){
						selectedTile = {
							.idx = tile->getSlot(),
							.id = 1,
							.texture = hcm::newItem<hcm::Tile>(tile->getID()).iconTexture
						};
					}
				}
			break;
			default:
			break;
		}
	}

	level->Update(GetFrameTime());
}

void LevelEditor::Draw(){
	BeginMode2D(camera);

	level->Draw();

	EndMode2D();

	DrawText("Current Tile", 32-12, 20, 15, BLACK);
	DrawText("Selected Tile", 32*4-12, 20, 15, BLACK);

	DrawTexturePro(currentTile.iconTexture, {0,0,32,32}, {32, 32, 32*2, 32*2}, {0, 0}, 0, WHITE);
	DrawTexturePro(selectedTile.texture, {0,0,32,32}, {32*4, 32, 32*2, 32*2}, {0, 0}, 0, WHITE);

	std::string tmpStr = "< " + modeToString[(Modes)currentMode] + " >";
	DrawText(tmpStr.c_str(), 32, 32*4, 32, BLACK);

	tmpStr = "Current Z Layer: " + std::to_string(currentZLayer);
	DrawText(tmpStr.c_str(), 32, 32*6, 32, BLACK);
}

void LevelEditor::Unload(){
	delete(&currentTile);
	delete(&selectedTile);
	delete(&maxTile);

	delete(&currentZLayer);

	delete(&currentMode);

	delete(&cammax);
	delete(&cammin);
}

LevelEditor::LevelEditor() : hcm::Scene("Hama", 0.5){
	level = new hcm::Level(config["hama"]["defaultLevelPath"].asString().c_str());

	currentTile = hcm::newItem<hcm::Tile>(1);
	currentMode = (int)Modes::Pencil;

	selectedTile = {
		.idx = -1,
		.id = 1,
		.texture = hcm::newItem<hcm::Tile>(1).iconTexture
	};

	currentZLayer = 0;

	Json::Reader jsonreader;
	Json::Value itemsJson;

	std::ifstream file("res/items.json");
	jsonreader.parse(file, itemsJson);

	maxTile = itemsJson.size() - 1;

	cammax = config["hama"]["cammax"].asFloat();
	cammin = config["hama"]["cammin"].asFloat();
}

void writeTileJson(hcm::Level &level, Vector2 pos, std::string filename){
	Json::Value root;

	root["x"] = (int)pos.x;
	root["y"] = (int)pos.y;

	std::vector<std::string> strTiles = tilesToStrings(level.tiles, level.getSize(), level.getTotal_layers());
	for(int i=0;i<strTiles.size();i++)
		root["layers"][i] = strTiles[i];

	Json::StreamWriterBuilder builder;
	std::string jsonString = Json::writeString(builder, root);

	std::ofstream outFile(filename);
	if (outFile.is_open()) {
		outFile << jsonString;
		outFile.close();
		std::cout << "JSON file written successfully." << std::endl;
	}else {
		std::cerr << "Error opening file for writing." << std::endl;
	}
}

};
