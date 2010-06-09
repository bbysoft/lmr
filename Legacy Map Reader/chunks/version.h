#pragma once
#include "../chunk.h"

#define WARCRAFT2             17
#define WARCRAFT2_EXP         19
#define STARCRAFT_BETA_EARLY  47
#define STARCRAFT_BETA        57
#define STARCRAFT             59
#define STARCRAFT_STAREDIT    61
#define STARCRAFT_ENHANCED    63
#define BROODWAR_BETA         75
#define ENHANCED_STAREDIT     201
#define BROODWAR_STAREDIT     203
#define BROODWAR              205

extern WORD gwVersion;

bool __stdcall GetVersion(chunk *pChunk);
