#pragma once


#define REVERSE(x) ( ((x & 0xFF000000) >> 24) | ((x & 0xFF0000) >> 8) | ((x & 0xFF00) << 8) | ((x & 0xFF) << 24))
#define CHARLIST(x) (x & 0xFF), ((x & 0xFF00) >> 8), ((x & 0xFF0000) >> 16), ((x & 0xFF000000) >> 24)

struct chunk
{
  DWORD dwId;
  DWORD dwSize;
  BYTE  data[1];
};

struct chunkdef
{
  DWORD dwId;
  bool (__stdcall *pfCallback)(chunk *pChunk);
  DWORD dwFlags;
};

#define CHUNK_REQUIRED  1
#define CHUNK_ONCE      2
#define CHUNK_UMS       4

#define MAKECHUNKHEADER(x) { x, countof(x)}
struct chunklist
{
  DWORD   dwVersion;
  char    *pszDebug;
  DWORD   dwPlayerCount;
  struct  _chunkHead
  {
    chunkdef  *pChunks;
    DWORD     dwCount;
  } chunkHeader[6];
};
