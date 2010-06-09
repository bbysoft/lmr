// ERA
#pragma once
#include "../chunk.h"
#include "version.h"

extern WORD gwTileset;

static char *StarcraftTileset[] = {
  "Badlands",
  "Space Platform",
  "Installation",
  "Ashworld",
  "Jungle",
  "Desert",
  "Arctic",
  "Twilight"
};

static char *WarcraftTileset[] = {
  "Forest",
  "Snow",
  "Wasteland",
  "Orc Swamp"
};

bool __stdcall GetTileset(chunk *pChunk);
