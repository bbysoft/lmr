// STR 
#pragma once
#include "../../chunk.h"

extern WORD *gpMapStrings;

bool __stdcall GetStrings(chunk *pChunk);
char *GetString(WORD wIndex);