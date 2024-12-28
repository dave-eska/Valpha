#pragma once

#include <string>
#include <vector>

#include <raylib.h>

#include "scene.hpp"
#include "world.hpp"

class LevelEditor : public hcm::Scene{
private:
	int finish_screen = 0;

	int cam_speed;

	hcm::Level *level;
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
	void Update(float dt) override;
	void Draw() override;

	void Unload() override;

	LevelEditor();
};
