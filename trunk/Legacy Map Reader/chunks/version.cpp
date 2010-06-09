#include "version.h"

WORD gwVersion;

bool __stdcall GetVersion(chunk *pChunk)
{
  // verify the chunk size
  if ( pChunk->dwSize != sizeof(WORD) )
    return false;

  // get the version
  gwVersion = *(WORD*)&pChunk->data[0];
  return true;
}
