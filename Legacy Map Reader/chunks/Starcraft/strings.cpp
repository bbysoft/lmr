#include "strings.h"

WORD *gpMapStrings;

void CleanupStrings()
{
  // Free allocated memory for strings
  if ( gpMapStrings )
    SMemFree(gpMapStrings, __FILE__, __LINE__, 0);
  gpMapStrings = NULL;
}

bool __stdcall GetStrings(chunk *pChunk)
{
  // Free previous memory if necessary
  if ( gpMapStrings )
    SMemFree(gpMapStrings, __FILE__, __LINE__, 0);
  
  // Allocate memory for strings
  gpMapStrings = (WORD*)SMemAlloc(pChunk->dwSize, __FILE__, __LINE__, 0);
  if ( gpMapStrings )
  {
    atexit(&CleanupStrings);
    // Copy the string data
    SMemCopy(gpMapStrings, pChunk->data, pChunk->dwSize);
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
