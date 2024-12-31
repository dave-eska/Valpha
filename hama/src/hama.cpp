#include "hama.hpp"

#include <algorithm>

#include <raymath.h>

#include "raylib.h"
#include "scene.hpp"

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

void fill(LevelEditor &hostScene, std::vector<std::unique_ptr<hcm::Tile>>& canvas, int x, int y, int z, int targetID, int fillID, std::unordered_set<int>& visited) {
	// Check if current position is within canvas bounds
	if(x < 0 || y < 0 || x >= (hostScene.level->getSize().x*TILE_SIZE) || y >= (hostScene.level->getSize().y*TILE_SIZE)) return;

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
	fill(hostScene, canvas, x + TILE_SIZE, y, z, targetID, fillID, visited); // Right
	fill(hostScene, canvas, x - TILE_SIZE, y, z, targetID, fillID, visited); // Left
	fill(hostScene, canvas, x, y + TILE_SIZE, z, targetID, fillID, visited); // Down
	fill(hostScene, canvas, x, y - TILE_SIZE, z, targetID, fillID, visited); // Up
}

void LevelEditor::Update(float dt){
	float wheelMove = GetMouseWheelMove();
	if(wheelMove != 0.0f) {
		camera.zoom += wheelMove * 0.1f; // Adjust zoom sensitivity if needed
		if(camera.zoom > cammax) camera.zoom = cammax;
		if(camera.zoom < cammin) camera.zoom = cammin;
	}
}

void LevelEditor::Draw(){
	BeginMode2D(camera);
	//!stuff in camera here

	EndMode2D();

}

void LevelEditor::Unload(){
}

LevelEditor::LevelEditor() : hcm::Scene("hamma homtana", 0.5){
}

};
