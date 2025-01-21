#include "converUI.hpp"
#include "raylib.h"

#include <fstream>

#include "json/reader.h"
#include "json/value.h"

namespace hcm{
void MessageUI::Draw(){
	DrawTextureEx(base, basePos, 0, 7, WHITE);
	DrawTextureEx(npcPrev, {basePos.x+(7*7), basePos.y-(15*7)}, 0, 7, WHITE);
}

MessageUI::MessageUI(const char* jsonFilePath){
	base = LoadTexture("res/img/converbase.png");
	respButtonSmall = LoadTexture("res/img/converButtonSmall.png");
	respButtonBig = LoadTexture("res/img/converButtonBig.png");
	name = LoadTexture("res/img/converName.png");
	npcPrev = LoadTexture("res/img/converNPCPreview.png");

	basePos = {((float)GetScreenWidth()/2) - ((float)(base.width*7)/2), 760};

	Json::Reader jsonreader;
	Json::Value root;

	std::ifstream file(jsonFilePath);
	jsonreader.parse(file, root);
}

MessageUI::MessageUI(){
}

};
