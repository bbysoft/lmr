#include "thingy2.h"

struct Thingy2
{
  DWORD oshit;
};

std::vector<Thingy2> Sprites;

bool __stdcall GetBroodwarSprites2(chunk *pChunk)
{
  // Retrieve unit count
  DWORD dwSpriteCount = pChunk->dwSize / sizeof(Thingy2);

  // Verify section size
  if ( pChunk->dwSize % sizeof(Thingy2) )
    return false;

  // Localize a pointer to the data
  Thingy2 *sprites = (Thingy2*)pChunk->data;

  // Iterate through each unit
  for ( unsigned int i = 0; i < dwSpriteCount; i++ )
  {
    // Assign the sprite to the vector
    Sprites.push_back(sprites[i]);
  }
  return true;
}
