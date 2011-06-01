#include "sproperties.h"

Properties gSProperties;

bool __stdcall GetScenarioProperties(chunk *pChunk)
{
  // Verify the chunk size
  if ( pChunk->dwSize != sizeof(Properties) )
    return false;

  // Copy the chunk data
  memset(&gSProperties, 0, sizeof(gSProperties));
  memcpy(&gSProperties, pChunk->data, pChunk->dwSize);
  return true;
}
