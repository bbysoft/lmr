// SPRP (Scenario Properties)
#pragma once
#include "../../chunk.h"

struct Properties
{
  WORD  wTitleIndex;
  WORD  wDescriptionIndex;
};

extern Properties gSProperties;

bool __stdcall GetScenarioProperties(chunk *pChunk);
