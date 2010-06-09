// SIDE
#pragma once
#include "../chunk.h"

extern BYTE gbPlayerRace[16];

static char *StarcraftRace[] = {
  "Zerg",
  "Terran",
  "Protoss",
  "Independant",
  "Neutral",
  "User Select",
  "Random",
  "Inactive"
};

static char *WarcraftRace[] = {
  "Human",
  "Orc",
  "Neutral",
  "Random"
};

bool __stdcall GetSide(chunk *pChunk);
