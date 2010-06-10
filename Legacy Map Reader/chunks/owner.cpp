#include "owner.h"

BYTE gbPlayerType[16];

bool __stdcall GetOwner(chunk *pChunk)
{
  // Verify the chunk size
  if ( pChunk->dwSize != gpChunk->dwPlayerCount )
    return false;

  // Copy the chunk data
  SMemCopy(gbPlayerType, pChunk->data, pChunk->dwSize);
  return true;
}
