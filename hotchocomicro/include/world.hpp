#pragma once

#include <string>
#include <vector>
#include <memory>

#include <raylib.h>

#include <box2d/b2_world.h>

#include "tile.hpp"

namespace hcm{
class Level{
private:
	Vector2 starting_pos;
	Vector2 size;
	int total_layers;

	std::string name;

	std::vector<std::unique_ptr<Tile>> loadLevelFromFile(std::string file_path);
public:
	std::vector<std::unique_ptr<Tile>> tiles;
	b2World* b2world;

	Vector2 getStarting_pos(){ return starting_pos; }
	Vector2 getSize(){ return size; }
	int getTotal_layers(){ return total_layers; }

	void loadPath(std::string path);

	void Update(float dt);
	void Draw();

	Level();
	Level(std::string path);

};
};
