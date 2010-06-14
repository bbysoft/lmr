#include "w2units.h"

struct WAR2Unit
{
  WPOINT  position;
  BYTE    bType;
  BYTE    bOwner;
  WORD    wProperties;
};

std::vector<WAR2Unit> war2Units;

bool __stdcall GetWar2Units(chunk *pChunk)
{
  // Retrieve unit count
  DWORD dwUnitCount = pChunk->dwSize / sizeof(WAR2Unit);

  // Verify section size
  if ( pChunk->dwSize % sizeof(WAR2Unit) )
    return false;

  // Localize a pointer to the data
  WAR2Unit *units = (WAR2Unit*)pChunk->data;

  // player-specific variables
  bool  bHasStart[16];
  BYTE  bCounts[16];

  // Iterate through each unit
  for ( unsigned int i = 0; i < dwUnitCount; i++ )
  {
    // Get the player owner
    BYTE bPl = units[i].bOwner;

    // Retrieve and ignore Start Locations
    if ( units[i].bType == 94 || units[i].bType == 95 )
    {
      // Verify that the player is valid
      if ( bPl < 16 )
      {
        // Save the Start Location X/Y
        gStartLocations[bPl].x = units[i].position.x;
        gStartLocations[bPl].y = units[i].position.y;
        bHasStart[bPl] = true;
      }
      continue;
    }

    // Make the first unit the start location if there isn't any
    if ( bPl < 16 && !bHasStart[bPl] )
    {
      // Save the Start Location X/Y
      gStartLocations[bPl].x = units[i].position.x;
      gStartLocations[bPl].y = units[i].position.y;
      bHasStart[bPl] = true;
    }
    
    // Don't go over the player unit limit
    if ( bPl < 16 && bCounts[bPl] < 200 )
      bCounts[bPl]++;
    else
      continue;

    // Assign the unit to the vector
    war2Units.push_back(units[i]);
  }

  return true;
}
