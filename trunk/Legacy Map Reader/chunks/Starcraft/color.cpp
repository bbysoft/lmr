#include "color.h"

BYTE gbPlayerColor[8];

bool __stdcall GetColor(chunk *pChunk)
{
  // Verify the chunk size
  if ( pChunk->dwSize != 8 )
    return false;

  // Copy the chunk data
  memcpy(gbPlayerColor, pChunk->data, pChunk->dwSize);
  return true;
}
