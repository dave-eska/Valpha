#pragma once

#include <string>

#include <raylib.h>

#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>
#include <vector>

#include "animation.h"
#include "box2d/b2_fixture.h"

#define TILE_SIZE (96)

namespace hcm{
struct RecipeItem{
	int id;
	int count;
};

struct InventoryItem{
	int tileID{};
	std::string item_type{};
	std::string item_name{};

	std::string filename{};

	int item_invslot{};
	int item_count{};

	int damage;
	int durability;

	std::vector<RecipeItem> recipe;

	std::string drawItem;
	void UpdateDrawItem();


	Texture2D iconTexture{};
};

class Tile{
private:
	std::string name;
	std::string type;
	int id;

	Rectangle body;
	int z_level;

	int slot;

	b2Body* b2body;
	b2PolygonShape boxShape;
	b2FixtureDef fixtureDef;

	Texture2D texture;
	SpriteAnimation animation;
	bool animationOnDefault;
	bool isRunningAnimation;

	bool isTouchingMouse{false};

	static constexpr float PIXELS_PER_METER = 50.0f;

public:
	bool hasAnimation();
	int getSlot(){ return slot; };
	void setSlot(int val){ slot = val; }

	Rectangle getBody(){ return body; }
	Vector2 getPos(){ return {body.x, body.y}; }
	std::string getType(){ return type; };

	int getZ(){ return z_level; }
	int getID(){ return id; }

	b2Body* getB2Body(){ return b2body; }

	bool getIsTouchingMouse(){ return isTouchingMouse; }
	void setIsTouchingMouse(bool val){ isTouchingMouse = val; }

	void Update();
	void Draw();

	void initCollision(b2World*& world);

	InventoryItem asItem(int total_count);

	Tile();
	Tile(int id, Vector2 pos, int z_level);
};

template<typename T>
InventoryItem newItem(int tileID){
	return T(tileID, {}, 0).asItem(1);
}

template<typename T>
InventoryItem newItem(int tileID, int count){
	return T(tileID, {}, 0).asItem(count);
}

void assignInvSlot(InventoryItem& item, int slot);

};
