#pragma once

#include "converUI.hpp"
#include "world.hpp"
#include "scene.hpp"
#include "player.hpp"
#include "ability.hpp"

class Gameplay : public hcm::Scene{
private:
	hcm::Level* level;

	hcm::Player* player;
	hcm::AbilityManager* am;

	float camMax;
	float camMin;

	hcm::MessageUI msg;
public:
	void Update(float dt) override;
	void Draw() override;

	void Unload() override;

	Gameplay();
};
