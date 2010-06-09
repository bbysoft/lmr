#include "tileset.h"

WORD gwTileset;

bool __stdcall GetTileset(chunk *pChunk)
{
  if ( pChunk->dwSize != 2 )
    return false;

  if ( gwVersion == WARCRAFT2 || gwVersion == WARCRAFT2_EXP )
  {
    gwTileset = *(WORD*)&pChunk->data[0];
    if ( gwTileset > 3 )
      gwTileset = 0;
  }
  else
    gwTileset = *(WORD*)&pChunk->data[0] & 7;
  return true;
}
