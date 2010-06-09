#include "dimensions.h"

WSIZE gDimensions;

bool __stdcall GetDimensions(chunk *pChunk)
{
  // verify the chunk size
  if ( pChunk->dwSize != sizeof(WSIZE) )
    return false;

  // get the dimensions
  gDimensions.cx = *(WORD*)&pChunk->data[0];
  gDimensions.cy = *(WORD*)&pChunk->data[2];
  return true;
}
