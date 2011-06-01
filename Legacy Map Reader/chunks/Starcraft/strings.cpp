#include "strings.h"

WORD *gpMapStrings;

void CleanupStrings()
{
  // Free allocated memory for strings
  if ( gpMapStrings )
    SMFree(gpMapStrings);
  gpMapStrings = NULL;
}

bool __stdcall GetStrings(chunk *pChunk)
{
  // Free previous memory if necessary
  STORMFREE(gpMapStrings);
  
  // Allocate memory for strings
  gpMapStrings = (WORD*)SMAlloc(pChunk->dwSize);
  if ( gpMapStrings )
  {
    atexit(&CleanupStrings);
    // Copy the string data
    memcpy(gpMapStrings, pChunk->data, pChunk->dwSize);
    return true;
  }
  return false;
}

char *GetString(WORD wIndex)
{
  // Return blank if not allocated
  if ( !gpMapStrings )
    return "";

  // Retrieve the string at the index
  return (char*)((DWORD)gpMapStrings + gpMapStrings[wIndex + 1]);
}
