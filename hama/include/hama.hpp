#pragma once

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

	void writeTileJson(hcm::Level &level, Vector2 pos, std::string filename);
	void InteractWithTile();

	void TypingCode();
public:
	hcm::Level *level;

	void Update(float dt) override;
	void Draw() override;

	void Unload() override;

	LevelEditor();
};

std::vector<std::string> tilesToStrings(std::vector<std::unique_ptr<hcm::Tile>>& tiles, Vector2 canvas_size, int total_layers);
void fill(LevelEditor &hostScene, std::vector<std::unique_ptr<hcm::Tile>>& canvas, int x, int y, int z, int targetID, int fillID, std::unordered_set<int>& visited);

};
