// FORC
#pragma once
#include "../../chunk.h"

struct ForceData
{
  BYTE bPlayerTeam[8];
  WORD wForceString[4];
  BYTE bForceFlags[4];
};

extern ForceData gForceData;

bool __stdcall GetForces(chunk *pChunk);
