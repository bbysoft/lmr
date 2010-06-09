#pragma once
#include <windows.h>
#include <windef.h>
#include "storm.h"
#include "main.h"
#include "chunkstructure.h"

/* Common Chunks */
#include "chunks/version.h"
#include "chunks/dimensions.h"
#include "chunks/side.h"
#include "chunks/owner.h"
#include "chunks/tileset.h"

/* Starcraft Chunks */
#include "chunks/Starcraft/strings.h"

/* Warcraft II Chunks */

extern chunklist *gpChunk;

void ReadScenarioFile();
