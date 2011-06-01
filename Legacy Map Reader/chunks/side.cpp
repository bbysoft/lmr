#include "side.h"

BYTE gbPlayerRace[16];

bool __stdcall GetSide(chunk *pChunk)
{
  // Verify the chunk size
  if ( pChunk->dwSize != gpChunk->dwPlayerCount )
    return false;

  // Copy the chunk data
  memcpy(gbPlayerRace, pChunk->data, pChunk->dwSize);
  return true;
}
