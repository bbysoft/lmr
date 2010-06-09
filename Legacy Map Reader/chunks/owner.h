// OWNR
#pragma once
#include "../chunk.h"

extern BYTE gbPlayerType[16];

static char *StarcraftOwner[] = {
  "None",
  "Computer",
  "Player",
  "Rescue Passive",
  "Rescue Active",
  "Prefer Computer",
  "Prefer Human",
  "Neutral",
  "Closed",
  "Observer",
  "Player Left",
  "Computer Left"
};

static char *WarcraftOwner[] = {
  "Player",
  "Computer",
  "Neutral",
  "None",
  "Prefer Computer",
  "Prefer Human",
  "Rescue Passive",
  "Rescue Active",
  "Closed"
};

bool __stdcall GetOwner(chunk *pChunk);
