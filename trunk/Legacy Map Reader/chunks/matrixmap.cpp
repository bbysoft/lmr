#include "matrixmap.h"

WORD *pwMatrixMap;

void FreeMatrix()
{
  // Free allocated memory
  STORMFREE(pwMatrixMap);
}

bool __stdcall GetMatrixMap(chunk *pChunk)
{
  // Verify the chunk size
  if ( gwVersion == WARCRAFT2 || gwVersion == WARCRAFT2_EXP )
  {
    // Limit Warcraft II map size
    if ( pChunk->dwSize > (128 * 128 * sizeof(WORD)) )
        return false;
  }
  else
  {
    // Limit Starcraft map size
    if ( pChunk->dwSize > (256 * 256 * sizeof(WORD)) )
      return false;
  }

  // Allocate memory for tiles
  if ( !pwMatrixMap )
  {
    pwMatrixMap = (WORD*)SMAlloc(256 * 256 * sizeof(WORD));
    atexit(&FreeMatrix);
  }

  // Copy the data
  memcpy(pwMatrixMap, pChunk->data, pChunk->dwSize);
  return true;
}
