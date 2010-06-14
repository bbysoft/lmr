#include "force.h"

ForceData gForceData;

bool __stdcall GetForces(chunk *pChunk)
{
  // Verify the chunk size
  if ( pChunk->dwSize > sizeof(ForceData) )
    return false;

  // Copy the chunk data
  SMemZero(&gForceData, sizeof(gForceData));
  SMemCopy(&gForceData, pChunk->data, pChunk->dwSize);
  return true;
}
