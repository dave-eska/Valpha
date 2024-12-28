#pragma once

#include <string>

#include <raylib.h>

#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_world.h>

#include "animation.h"
#include "box2d/b2_fixture.h"

#define TILE_SIZE (96)

namespace hcm{
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

	static constexpr float PIXELS_PER_METER = 50.0f;

public:
	bool hasAnimation();
	int getSlot(){ return slot; };

	Rectangle getBody(){ return body; }
	Vector2 getPos(){ return {body.x, body.y}; }
	std::string getType(){ return type; };

	int getZ(){ return z_level; }
	int getID(){ return id; }

	b2Body* getB2Body(){ return b2body; }

	void setSlot(int val){ slot = val; }

	void Update();
	void Draw();

	void initCollision(b2World*& world);

	Tile();
	Tile(int id, Vector2 pos, int z_level);
};
};
