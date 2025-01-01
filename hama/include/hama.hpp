#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include <raylib.h>

#include "scene.hpp"
#include "tile.hpp"
#include "world.hpp"

namespace hama{

enum class Modes{
	Pencil,
	Eraser,
	Eyedrop
};

class LevelEditor : public hcm::Scene{
private:
	hcm::Level *level;

	hcm::InventoryItem currentTile;
	int maxTile;

	Modes currentMode;

	float cammax, cammin;

	void fill(std::vector<std::unique_ptr<hcm::Tile>>& canvas, int x, int y, int z, int targetID, int fillID, std::unordered_set<int>& visited);
public:

	void Update(float dt) override;
	void Draw() override;

	void Unload() override;

	LevelEditor();
};

std::vector<std::string> tilesToStrings(std::vector<std::unique_ptr<hcm::Tile>>& tiles, Vector2 canvas_size, int total_layers);

};
