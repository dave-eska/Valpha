#pragma once

#include <raylib.h>

namespace hcm{
Color GetRainbowColor();
void changeIntWithKey(int& val, int incrKey, int decrKey, int maxVal, int minVal);
}
