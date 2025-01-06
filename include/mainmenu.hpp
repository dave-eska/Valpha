#pragma once

#include "scene.hpp"

class MainMenu : public hcm::Scene{
private:
public:
	void Update(float dt) override;
	void Draw() override;

	void Unload() override;

	MainMenu();
};
