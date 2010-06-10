#include "tileset.h"

WORD gwTileset;

bool __stdcall GetTileset(chunk *pChunk)
{
  // Verify the chunk size
  if ( pChunk->dwSize != sizeof(WORD) )
    return false;

  // Retrieve the tileset
  if ( gwVersion == WARCRAFT2 || gwVersion == WARCRAFT2_EXP )
  {
    // Perform Warcraft II filtering
    gwTileset = *(WORD*)&pChunk->data[0];
    if ( gwTileset > 3 )
      gwTileset = 0;
  }
  else
  {
    // Perform Starcraft filtering
    gwTileset = *(WORD*)&pChunk->data[0] & 7;
  }
  return true;
}
