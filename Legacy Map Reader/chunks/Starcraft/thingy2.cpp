#include "thingy2.h"

struct Thingy2Entry
{
  WORD    wType;
  WPOINT  position;
  BYTE    wOwner;
  BYTE    bUnused;
  WORD    wFlags;
};

std::vector<Thingy2Entry> Sprites;

bool __stdcall GetBroodwarSprites2(chunk *pChunk)
{
  // Retrieve sprite count
  DWORD dwSpriteCount = pChunk->dwSize / sizeof(Thingy2Entry);

  // Verify section size
  if ( pChunk->dwSize % sizeof(Thingy2Entry) )
    return false;

  // Localize a pointer to the data
  Thingy2Entry *sprites = (Thingy2Entry*)pChunk->data;

  // Iterate through each sprite and assign it to the vector
  for ( unsigned int i = 0; i < dwSpriteCount; ++i )
    Sprites.push_back(sprites[i]);

  return true;
}
