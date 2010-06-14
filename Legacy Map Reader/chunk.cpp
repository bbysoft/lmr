#include "chunk.h"

chunklist *gpChunk;

chunkdef Primary[] = {
  { REVERSE('VER '), &GetVersion, CHUNK_REQUIRED | CHUNK_ONCE }
};

chunkdef AllRequired[] = {
  { REVERSE('DIM '), &GetDimensions, CHUNK_REQUIRED },
  { REVERSE('ERA '), &GetTileset, CHUNK_REQUIRED },
  { REVERSE('OWNR'), &GetOwner, CHUNK_REQUIRED },
  { REVERSE('SIDE'), &GetSide, CHUNK_REQUIRED },
  { REVERSE('MTXM'), &GetMatrixMap, CHUNK_REQUIRED }
};

chunkdef StarcraftRequired[] = {
  { REVERSE('STR '), &GetStrings, CHUNK_REQUIRED },
  { REVERSE('SPRP'), NULL, CHUNK_REQUIRED },
  { REVERSE('FORC'), &GetForces, CHUNK_REQUIRED },
  { REVERSE('VCOD'), &CheckVCode, CHUNK_REQUIRED }
};

chunkdef StarcraftAdditionalReq[] = {
  { REVERSE('THG2'), NULL, CHUNK_REQUIRED },
  { REVERSE('UNIT'), &GetBroodwarUnits, CHUNK_REQUIRED }
};

chunkdef BroodwarAdditionalReq[] = {
  { REVERSE('COLR'), NULL, CHUNK_REQUIRED }
};

chunkdef WarcraftReq[] = {
  { REVERSE('TYPE'), NULL, CHUNK_REQUIRED },
  { REVERSE('DESC'), NULL, CHUNK_REQUIRED },
  { REVERSE('SGLD'), NULL, CHUNK_REQUIRED },
  { REVERSE('SLBR'), NULL, CHUNK_REQUIRED },
  { REVERSE('SOIL'), NULL, CHUNK_REQUIRED },
  { REVERSE('SQM '), NULL, CHUNK_REQUIRED },
  { REVERSE('OILM'), NULL, CHUNK_REQUIRED },
  { REVERSE('REGM'), NULL, CHUNK_REQUIRED },
  { REVERSE('UNIT'), &GetWar2Units, CHUNK_REQUIRED | CHUNK_ONCE }
};

chunkdef WarcraftOptional[] = {
  { REVERSE('SIGN'), NULL, 0 },
  { REVERSE('UDTA'), NULL, 0 },
  { REVERSE('UGRD'), NULL, 0 },
  { REVERSE('ALOW'), NULL, 0 },
  { REVERSE('AIPL'), NULL, 0 }
};

chunklist chunks[] = {
  { WARCRAFT2, "Warcraft II Retail", 16,
    {
      MAKECHUNKHEADER(AllRequired),
      MAKECHUNKHEADER(WarcraftReq),
      MAKECHUNKHEADER(WarcraftOptional),
      { NULL, 0 },
      { NULL, 0 },
      { NULL, 0 }
    }
  },
  { WARCRAFT2_EXP, "Warcraft II Battle.net Edition Retail", 16,
    {
      MAKECHUNKHEADER(AllRequired),
      MAKECHUNKHEADER(WarcraftReq),
      MAKECHUNKHEADER(WarcraftOptional),
      { NULL, 0 },
      { NULL, 0 },
      { NULL, 0 }
    }
  },
  { STARCRAFT_BETA_EARLY, "Unknown Starcraft Beta (Early Beta?)", 12,
    {
      MAKECHUNKHEADER(AllRequired),
      MAKECHUNKHEADER(StarcraftRequired),
      { NULL, 0 },
      { NULL, 0 },
      { NULL, 0 },
      { NULL, 0 }
    }
  },
  { STARCRAFT_BETA, "Starcraft Battle.net Beta", 12,
    {
      MAKECHUNKHEADER(AllRequired),
      MAKECHUNKHEADER(StarcraftRequired),
      { NULL, 0 },
      { NULL, 0 },
      { NULL, 0 },
      { NULL, 0 }
    }
  },
  { STARCRAFT, "Starcraft Retail", 12,
    {
      MAKECHUNKHEADER(AllRequired),
      MAKECHUNKHEADER(StarcraftRequired),
      MAKECHUNKHEADER(StarcraftAdditionalReq),
      { NULL, 0 },
      { NULL, 0 },
      { NULL, 0 }
    }
  },
  { STARCRAFT_STAREDIT, "Starcraft Unknown (Staredit only)", 12,
    {
      MAKECHUNKHEADER(AllRequired),
      MAKECHUNKHEADER(StarcraftRequired),
      MAKECHUNKHEADER(StarcraftAdditionalReq),
      { NULL, 0 },
      { NULL, 0 },
      { NULL, 0 }
    }
  },
  { STARCRAFT_ENHANCED, "Starcraft Enhanced (1.04)", 12,
    {
      MAKECHUNKHEADER(AllRequired),
      MAKECHUNKHEADER(StarcraftRequired),
      MAKECHUNKHEADER(StarcraftAdditionalReq),
      { NULL, 0 },
      { NULL, 0 },
      { NULL, 0 }
    }
  },
  { BROODWAR_BETA, "Broodwar Battle.net Beta", 12,
    {
      MAKECHUNKHEADER(AllRequired),
      MAKECHUNKHEADER(StarcraftRequired),
      MAKECHUNKHEADER(StarcraftAdditionalReq),
      MAKECHUNKHEADER(BroodwarAdditionalReq),
      { NULL, 0 },
      { NULL, 0 }
    }
  },
  { BROODWAR_STAREDIT, "Broodwar Unknown (Staredit only)", 12,
    {
      MAKECHUNKHEADER(AllRequired),
      MAKECHUNKHEADER(StarcraftRequired),
      MAKECHUNKHEADER(StarcraftAdditionalReq),
      MAKECHUNKHEADER(BroodwarAdditionalReq),
      { NULL, 0 },
      { NULL, 0 }
    }
  },
  { BROODWAR, "Broodwar Retail", 12,
    {
      MAKECHUNKHEADER(AllRequired),
      MAKECHUNKHEADER(StarcraftRequired),
      MAKECHUNKHEADER(StarcraftAdditionalReq),
      MAKECHUNKHEADER(BroodwarAdditionalReq),
      { NULL, 0 },
      { NULL, 0 }
    }
  }
};

void ReadChunkData(chunkdef *chunks, DWORD dwCount)
{
  for (DWORD i = 0; i < dwCount; i++)
  {
    // Start the search
    chunk *data = (chunk*)gpbChkBuffer;
    bool found = false;
    while(1)
    {
      if ( chunks[i].dwId == data->dwId )
      {
        // Callback for the chunk
        if ( !chunks[i].pfCallback )
          Debug("It appears the section '%c%c%c%c' is missing a callback function. Ignore the next warning.", CHARLIST(chunks[i].dwId));
        if ( chunks[i].pfCallback && chunks[i].pfCallback(data) )
          found = true;

        // Return if we only want to find the first chunk
        if ( chunks[i].dwFlags & CHUNK_ONCE )
          return;
      }

      // Go to next chunk
      if ( ((DWORD)data + data->dwSize + 16) > ((DWORD)gpbChkBuffer + gdwChunkSize) )
        break;
      data = (chunk*)((DWORD)data + data->dwSize + 8);
    }
    // If chunk was not found
    if ( !found && chunks[i].dwFlags & CHUNK_REQUIRED )
      Fatal(true, "The section '%c%c%c%c' was either not found or invalid. This would otherwise not work in Starcraft or Warcraft II. Do you wish to continue?", CHARLIST(chunks[i].dwId));
    else if ( found )
      Debug("Found the section '%c%c%c%c'.", CHARLIST(chunks[i].dwId));
  }
}

void ReadScenarioFile()
{
  ReadChunkData(Primary, countof(Primary));

  // Get version
  int i = 0;
  while(1)
  {
    // verify if the version is valid
    if ( chunks[i].dwVersion == gwVersion )
    {
      gpChunk = &chunks[i];
      Debug("Map identified as: %s", gpChunk->pszDebug);
      for (int j = 0; j < countof(gpChunk->chunkHeader) && gpChunk->chunkHeader[j].pChunks != NULL; j++)
        ReadChunkData(gpChunk->chunkHeader[j].pChunks, gpChunk->chunkHeader[j].dwCount);
      break;
    }

    i++;
    // Can't continue if version is unsupported
    if ( i > countof(chunks) )
      Fatal(false, "Unable to identify map version.");
  }

  MessageBox(NULL, "Finished reading the map.", "Debug", MB_OK);
}
