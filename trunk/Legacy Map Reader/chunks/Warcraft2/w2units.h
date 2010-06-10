// UNIT 
#pragma once
#include "../../chunk.h"
#include <vector>

struct WAR2Unit;

extern std::vector<WAR2Unit> war2Units;

bool __stdcall GetWar2Units(chunk *pChunk);
