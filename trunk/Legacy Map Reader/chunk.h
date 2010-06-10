#pragma once
#include <windows.h>
//#include <windef.h>

#include "storm.h"
#include "main.h"
#include "chunkstructure.h"

#include "map.h"

/* Common Chunks */
#include "chunks/version.h"
#include "chunks/dimensions.h"
#include "chunks/side.h"
#include "chunks/owner.h"
#include "chunks/tileset.h"
#include "chunks/matrixmap.h"

/* Starcraft Chunks */
#include "chunks/Starcraft/strings.h"
#include "chunks/Starcraft/bwunits.h"

/* Warcraft II Chunks */
#include "chunks/Warcraft2/w2units.h"

extern chunklist *gpChunk;

void ReadScenarioFile();

