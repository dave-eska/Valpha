#pragma once

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>
#include <map>

#include <raylib.h>

#include "scene.hpp"
#include "world.hpp"

namespace hama{

enum LevelEditorMode{
    Mode_One_Select,
    Mode_Pencil,
    Mode_Fill,
    Mode_Eraser,
    Mode_ColorPicker,
    Mode_SelectionTools,

    Mode_Max,
};

inline std::map<LevelEditorMode, std::string> LevelEditorToStringMap = {
    { Mode_One_Select, "One Select" },
    { Mode_Pencil, "Pencil" },
    { Mode_Fill, "Fill" },
    { Mode_Eraser, "Eraser" },
    { Mode_ColorPicker, "Color Picker" },
    { Mode_SelectionTools, "Selection Tools" }
};

inline std::string LevelEditorModeToString(LevelEditorMode mode){
    return LevelEditorToStringMap[mode];
}


class LevelEditor : public hcm::Scene{
private:
	int finish_screen = 0;

	int cam_speed;

	std::string canvas_sizeStr;

	Texture2D BlockOutlineTexture;

	hcm::Tile selectedTile;
	bool has_selected_tile;
	int selectedTileZ;

	int current_mode;

	std::vector<std::string> commands;

	bool isDebugging;

	Camera2D camera;

	std::string user_input;
	std::string last_input;
	std::string prev_user_input;

	int currentTileID;
	Texture2D currentTileTexture;

	int font_size;

	char tr_dest[128];
	bool isEditingTD;
	void TypingCode();
public:
	hcm::Level *level;

	void Update(float dt) override;
	void Draw() override;

	void Unload() override;

	LevelEditor();
};

static void fill(LevelEditor &hostScene, std::vector<std::unique_ptr<hcm::Tile>>& canvas, int x, int y, int z, int targetID, int fillID, std::unordered_set<int>& visited) {
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

};
