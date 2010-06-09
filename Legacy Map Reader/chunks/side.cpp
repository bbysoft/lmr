#include "side.h"

BYTE gbPlayerRace[16];

bool __stdcall GetSide(chunk *pChunk)
{
  if ( pChunk->dwSize != gpChunk->dwPlayerCount )
    return false;

  SMemCopy(gbPlayerRace, pChunk->data, pChunk->dwSize);
  return true;
}
