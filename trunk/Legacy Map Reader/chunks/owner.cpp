#include "owner.h"

BYTE gbPlayerType[16];

bool __stdcall GetOwner(chunk *pChunk)
{
  if ( pChunk->dwSize != gpChunk->dwPlayerCount )
    return false;

  SMemCopy(gbPlayerType, pChunk->data, pChunk->dwSize);
  return true;
}
