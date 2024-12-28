#pragma once

#include <string>

#include "world.hpp"
#include "scene.hpp"
#include "player.hpp"
#include "ability.hpp"

class Gameplay : public hcm::Scene{
private:
	hcm::Level* level;

	hcm::Player* player;
	hcm::AbilityManager* am;

	std::string userInput;

	float camMax;
	float camMin;

	float clearChat;

	void TypingCode();
public:
	void Update(float dt) override;
	void Draw() override;

	void Unload() override;

	Gameplay();
};
