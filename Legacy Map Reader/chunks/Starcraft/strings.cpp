#include "strings.h"

WORD *gpMapStrings;

void CleanupStrings()
{
  if ( gpMapStrings )
    SMemFree(gpMapStrings, __FILE__, __LINE__, 0);
  gpMapStrings = NULL;
}

bool __stdcall GetStrings(chunk *pChunk)
{
  if ( pChunk->dwSize < 1 )
    return false;

  if ( gpMapStrings )
    SMemFree(gpMapStrings, __FILE__, __LINE__, 0);
  
  gpMapStrings = (WORD*)SMemAlloc(pChunk->dwSize, __FILE__, __LINE__, 0);
  if ( gpMapStrings )
  {
    atexit(&CleanupStrings);
    SMemCopy(gpMapStrings, pChunk->data, pChunk->dwSize);
    return true;
  }
  return false;
}

char *GetString(WORD wIndex)
{
  if ( !gpMapStrings )
    return "";

  return (char*)((DWORD)gpMapStrings + gpMapStrings[wIndex + 1]);
}
