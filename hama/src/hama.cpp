#include "hama.hpp"

#include "json/value.h"
#include "json/writer.h"
#include <algorithm>

#include <fstream>
#include <iostream>
#include <raymath.h>

#include "raygui.h"
#include "raylib.h"

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

void LevelEditor::InteractWithTile(){
    if(IsKeyPressed(KEY_DELETE)){
        level->tiles[selectedTile.getSlot()] = std::make_unique<hcm::Tile>(hcm::Tile(0, {selectedTile.getX(), selectedTile.getY()}, selectedTile.getZ()));
        has_selected_tile = false;
    }
    if(IsKeyPressed(KEY_C)){
        level->tiles[selectedTile.getSlot()] = std::make_unique<hcm::Tile>(hcm::Tile(currentTileID, {selectedTile.getX(), selectedTile.getY()}, selectedTile.getZ()));
    }
}

void LevelEditor::writeTileJson(hcm::Level &level, Vector2 pos, std::string filename){
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
        std::cout<< "JSON file written successfully." << std::endl;
    }else {
        std::cerr<< "Error opening file for writing." << std::endl;
    }
}

void LevelEditor::Update(float dt){
	if(IsKeyPressed(KEY_ESCAPE))
		finish_screen = 1;

	// Camera Movement
	if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) or IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)){
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/camera.zoom);

        camera.target = Vector2Add(camera.target, delta);
    }

    // Zoom with mouse wheel
    if(!IsKeyDown(KEY_LEFT_CONTROL)){
        float wheel = GetMouseWheelMove();
        if(wheel != 0){
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            camera.offset = GetMousePosition();
            camera.target = mouseWorldPos;
            const float zoomIncrement = 0.125f;
            camera.zoom += (wheel*zoomIncrement);

            if (camera.zoom < zoomIncrement) camera.zoom = zoomIncrement;
        }
    }

    // Selecting Z
    if(IsKeyPressed(KEY_UP) or IsKeyPressed(KEY_DOWN)){
        if(IsKeyPressed(KEY_UP)) selectedTileZ++;
        if(IsKeyPressed(KEY_DOWN)) selectedTileZ--;

        auto it = std::find_if(level->tiles.begin(), level->tiles.end(), [this](const auto& tile){
                return (tile->getX() == selectedTile.getX() && tile->getY() == selectedTile.getY()) && tile->getZ() == selectedTileZ;
                });
        if(it != level->tiles.end()){
            selectedTile = hcm::Tile((*it)->getID(), {(*it)->getX(), (*it)->getY()}, selectedTileZ);
            selectedTile.setSlot((*it)->getSlot());
            selectedTile.setTexture((*it)->getTexture());
        }
    }

	float inputX = IsKeyDown(KEY_D)-IsKeyDown(KEY_A);
	float inputY = IsKeyDown(KEY_S)-IsKeyDown(KEY_W);

	camera.target.x += (inputX * cam_speed) * GetFrameTime();
	camera.target.y += (inputY * cam_speed) * GetFrameTime();

	if(IsKeyDown(KEY_LEFT_CONTROL)){
		currentTileID += (GetMouseWheelMove() * 1);
		Clamp(currentTileID, 0, MaxTileID-1);
		if(GetMouseWheelMove() != 0) currentTileTexture = hcm::newItem(currentTileID).iconTexture;

		if(IsKeyPressed(KEY_S)){
			writeTileJson(*level, {0,0}, "save.json");
		}
	}

	// Make new layer
	if(IsKeyPressed(KEY_N)){
		for(int i=0;i<level->getSize().x*level->getSize().x;i++){
			auto& tile = level->tiles[i];
			level->tiles.push_back(std::make_unique<hcm::Tile>(hcm::Tile(0, {tile->getX(), tile->getY()}, level->getTotal_layers())));
		}
		level->setTotalLayers(level->getTotal_layers()+1);
	}

	if(IsKeyPressed(KEY_I)) current_mode = Mode_ColorPicker;
	if(IsKeyPressed(KEY_B)) current_mode = Mode_Pencil;
	if(IsKeyPressed(KEY_G)) current_mode = Mode_Fill;
	if(IsKeyPressed(KEY_E)) current_mode = Mode_Eraser;

	// Switch Betweeen Modes
	if(IsKeyPressed(KEY_LEFT)) current_mode--;
	if(IsKeyPressed(KEY_RIGHT)) current_mode++;

	if(IsKeyPressed(KEY_SLASH)){
		//isTyping = true;
	}

	if(has_selected_tile && current_mode == Mode_One_Select) InteractWithTile();


	for(auto& tile : level->tiles){
		tile->setIsTouchingMouse(false);

		if(CheckCollisionPointRec(GetScreenToWorld2D(GetMousePosition(), camera), tile->getBody())){
			tile->setIsTouchingMouse(true);
		}

		switch(current_mode){
			case Mode_One_Select:
				{
					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) or IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
						if(tile->getIsTouchingMouse()){
							selectedTile = hcm::Tile(tile->getID(), {tile->getX(), tile->getY()}, tile->getZ());
							selectedTile.setSlot(tile->getSlot());
							selectedTile.setTexture(tile->getTexture());

                            selectedTileZ = selectedTile.getZ();

                            if(!has_selected_tile)
                                has_selected_tile = true;
                        }
                    }
                }
                break;
            case Mode_Pencil:
                {
                    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && tile->getIsTouchingMouse() && tile->getZ() == selectedTileZ){
                        int prev_slot = tile->getSlot();
                        tile = std::make_unique<hcm::Tile>(hcm::Tile(currentTileID, {tile->getX(), tile->getY()}, tile->getZ()));
                        tile->setSlot(prev_slot);
                    }
                }
                break;
            case Mode_Eraser:
                {
                    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && tile->getIsTouchingMouse() && tile->getZ() == selectedTileZ){
                        int prev_slot = tile->getSlot();
                        tile = std::make_unique<hcm::Tile>(hcm::Tile(0, {tile->getX(), tile->getY()}, tile->getZ()));
                        tile->setSlot(prev_slot);
                    }
                }
                break;
            case Mode_ColorPicker:
                {
                    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && tile->getIsTouchingMouse() && tile->getZ() == selectedTileZ){
                        currentTileID = tile->getID();
                        currentTileTexture = tile->getTexture();
                    }
                }
                break;
            case Mode_Fill:
                {
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && tile->getIsTouchingMouse() && tile->getZ() == selectedTileZ){
                        std::unordered_set<int> visited;
                        fill(*this, level->tiles, tile->getX(), tile->getY(), tile->getZ(), tile->getID(), currentTileID, visited);
                    }
                }
                break;
            default:
                break;
        }
    }

    // Clamps
    Clamp(selectedTileZ, 0, level->getTotal_layers()-1);
    Clamp(currentTileID, 0, MaxTileID-1);
    Clamp(current_mode, 0, Mode_Max-1);
}

LevelEditor::LevelEditor(){
    isDebugging = true;

    currentTileID = 1;
    currentTileTexture = hcm::Tile(currentTileID, {0,0}, 0).getTexture();

    level = new hcm::Level("res/levels/test.json");
    canvas_sizeStr = std::to_string((int)level->getSize().x) + ", " + std::to_string((int)level->getSize().y);
    current_mode = Mode_One_Select;

    font_size = 20;
    BlockOutlineTexture = LoadTexture("res/img/inventory_outline.png");

    camera = { 0 };
    camera.target = { 1000, 500 };
    camera.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 0.45;

    cam_speed = 500;

    selectedTile = hcm::Tile(0, {}, 0);
    has_selected_tile = false;
    selectedTileZ = 0;

    commands = {
        "/tell",
        "/reset",
        "/clear",
        "/debug",
        "/change",
        "/save",
        "/load",
        "/del",
        "/set"
    };

}

void LevelEditor::Draw(){
	BeginMode2D(camera);

	level->Draw();

	if(has_selected_tile && current_mode == Mode_One_Select)
		DrawRectangleRec(selectedTile.getBody(), {200, 200, 200, 255/2});

	EndMode2D();

	// Drawing UI
	DrawTextEx(GetFontDefault(), "Current Tile", {10, 40}, font_size, 0, WHITE);
	DrawTextureEx(BlockOutlineTexture, {20, 70}, 0, 2.2, WHITE);
	DrawTexturePro(currentTileTexture, {0,0,32,32}, {32, 83, 32*2, 32*2}, {0, 0}, 0, WHITE);
	DrawTextEx(GetFontDefault(), std::to_string(currentTileID).c_str(), {57.5, 103}, font_size+3.5, 0, WHITE);

	DrawTextEx(GetFontDefault(), "Selected Tile", {160, 40}, font_size, 0, WHITE);
	DrawTextureEx(BlockOutlineTexture, {170, 70}, 0, 2.2, WHITE);
	DrawTexturePro(selectedTile.getTexture(), {0,0,32,32}, {182, 83, 32*2, 32*2}, {0, 0}, 0, WHITE);
	DrawTextEx(GetFontDefault(), std::to_string(selectedTile.getID()).c_str(), {57.5+150, 103}, font_size+5, 3.5, WHITE);

	// Modes
	DrawTextEx(GetFontDefault(), "     Modes   ", {(float)GetScreenWidth()-200, 40}, font_size+5, 3.5, WHITE);
	DrawTextEx(GetFontDefault(), "<=                =>", {(float)GetScreenWidth()-230, 70}, font_size+5, 3.5, WHITE);
	DrawTextEx(GetFontDefault(), LevelEditorModeToString((LevelEditorMode)current_mode).c_str(), {(float)GetScreenWidth()-(float)193, 70}, font_size+1, 3.5, WHITE);

	// Texts
	std::string canvsaSizeStr = "Canvas Size: " + canvas_sizeStr;
	DrawTextEx(GetFontDefault(), canvsaSizeStr.c_str(), {20, 190}, font_size, 3.5, WHITE);

	std::string layerStr = "Layers: " + std::to_string(level->getTotal_layers());
	DrawTextEx(GetFontDefault(), layerStr.c_str(), {20, 215}, font_size, 3.5, WHITE);

	std::string zStr = "Current Layer: " + std::to_string(selectedTileZ+1);
	DrawTextEx(GetFontDefault(), zStr.c_str(), {20, 240}, font_size, 3.5, WHITE);

	Rectangle box = { 100, 85, 285, 30 };
	/*
	if(level->tiles.size() >= selectedTile.getSlot()){
		if(level->tiles[selectedTile.getSlot()]->getID() == Transition_Tile){
			if(GuiTextBox({ box.x + 170, box.y, 200, 30 }, tr_dest, 128, isEditingTD)){
				if(isEditingTD){
					auto transitionTile = dynamic_cast<TransitionTile*>(level->tiles[selectedTile.getSlot()].get());
					transitionTile->attachLevel(tr_dest);
				}
				isEditingTD = !isEditingTD;
			}
		}
	}
	*/

	/*
	// Draw Save button
	if(GuiButton((Rectangle){ (float)GetScreenWidth() - 100, (float)GetScreenHeight() - 50, 80, 30 }, "Save"))
		writeTileJson(*level, {0,0}, "save.json");

	if(GuiButton((Rectangle){ (float)GetScreenWidth() - 230, (float)GetScreenHeight() - 50, 110, 30 }, "Re-Load"))
		level->changeLevel("save.json");

	if(isTyping){
		DrawRectangleRec({30,(float)GetScreenHeight()-50,500,35}, {20,20,20,130});
		DrawText(user_input.c_str(), 30, (float)GetScreenHeight()-50, 35, WHITE);
	}
	*/
}

void LevelEditor::Unload(){
}

};
