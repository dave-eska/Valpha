#include "hama.hpp"

#include "json/reader.h"
#include "json/value.h"
#include <algorithm>

#include <fstream>
#include <raymath.h>
#include <string>

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

	level->Update(GetFrameTime());
}

void LevelEditor::Draw(){
	BeginMode2D(camera);

	level->Draw();

	EndMode2D();

	DrawTexturePro(currentTile.iconTexture, {0,0,32,32}, {32, 83, 32*2, 32*2}, {0, 0}, 0, WHITE);
}

void LevelEditor::Unload(){
}

LevelEditor::LevelEditor() : hcm::Scene("hamma homtana", 0.5){
	level = new hcm::Level(config["hama"]["defaultLevelPath"].asString().c_str());

	currentTile = hcm::newItem<hcm::Tile>(1);
	currentMode = Modes::Pencil;

	Json::Reader jsonreader;
	Json::Value itemsJson;

	std::ifstream file("res/items.json");
	jsonreader.parse(file, itemsJson);

	maxTile = itemsJson.size() - 1;

	cammax = config["hama"]["cammax"].asFloat();
	cammin = config["hama"]["cammin"].asFloat();
}

};
