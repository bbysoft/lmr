#include "bwunits.h"

struct BWUnit
{
  DWORD   dwIndex;
  WPOINT  position;
  WORD    wType;
  WORD    wRelation;
  WORD    wValidFlags;
  WORD    wValidProperties;
  BYTE    bOwner;
  BYTE    bHitPoints;
  BYTE    bShields;
  BYTE    bEnergy;
  WORD    wResources;
  WORD    wUnused1;
  WORD    wHanger;
  WORD    wFlags;
  DWORD   dwUnused2;
  DWORD   dwRelatedTo;
};

std::vector<BWUnit> bwUnits;

bool __stdcall GetBroodwarUnits(chunk *pChunk)
{
  // Retrieve unit count
  DWORD dwUnitCount = pChunk->dwSize / sizeof(BWUnit);

  // Verify section size
  if ( pChunk->dwSize % sizeof(BWUnit) )
    return false;

  // Localize a pointer to the data
  BWUnit *units = (BWUnit*)pChunk->data;

  // Iterate through each unit
  for ( unsigned int i = 0; i < dwUnitCount; i++ )
  {
    // Get the player owner
    BYTE bPl = units[i].bOwner;

    // Retrieve and ignore Start Locations
    if ( units[i].wType == 214 )
    {
      // Verify the player is valid
      if ( bPl < 8 )
      {
        // Save the start location position
        gStartLocations[bPl].x = units[i].position.x;
        gStartLocations[bPl].y = units[i].position.y;
      }
      continue;
    }

    // Assign the unit to the vector
    bwUnits.push_back(units[i]);
  }
  return true;
}
