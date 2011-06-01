#include "force.h"

ForceData gForceData;

bool __stdcall GetForces(chunk *pChunk)
{
  // Verify the chunk size
  if ( pChunk->dwSize > sizeof(ForceData) )
    return false;

  // Copy the chunk data
  memset(&gForceData, 0, sizeof(gForceData));
  memcpy(&gForceData, pChunk->data, pChunk->dwSize);
  return true;
}
