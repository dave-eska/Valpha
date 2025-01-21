#pragma once

#include <string>

#include <raylib.h>
#include <vector>

namespace hcm{

class MessageUI{
private:
	std::string msg;
	std::vector<std::string> responds;

	Vector2 basePos;

	Rectangle baseBody;
	Rectangle respBody;
	Texture2D base, respButtonSmall, respButtonBig, name, npcPrev;
public:

	void Draw();

	MessageUI(const char* jsonFilePath);
	MessageUI();
};

class ConverUI{
private:
public:
	ConverUI(const char* folderPath);
};
};
