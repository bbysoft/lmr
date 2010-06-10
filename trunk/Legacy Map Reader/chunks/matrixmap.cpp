#include "matrixmap.h"

WORD *pwMatrixMap;

void FreeMatrix()
{
  if ( pwMatrixMap )
    SMemFree(pwMatrixMap, __FILE__, __LINE__, 0);
  pwMatrixMap = NULL;
}

bool __stdcall GetMatrixMap(chunk *pChunk)
{
  if ( gwVersion == WARCRAFT2 || gwVersion == WARCRAFT2_EXP )
  {
    if ( pChunk->dwSize > (128 * 128 * sizeof(WORD)) )
        return false;
  }
  else
  {
    if ( pChunk->dwSize > (256 * 256 * sizeof(WORD)) )
      return false;
  }

  if ( !pwMatrixMap )
  {
    pwMatrixMap = (WORD*)SMemAlloc(256 * 256 * sizeof(WORD), __FILE__, __LINE__, 0);
    atexit(&FreeMatrix);
  }

  SMemCopy(pwMatrixMap, pChunk->data, pChunk->dwSize);
  return true;
}
