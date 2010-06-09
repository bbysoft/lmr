#include "main.h"

HANDLE  ghMpq = NULL;
HANDLE  ghFile = NULL;

char illegal[] = "*?\"<>|";

void *gpChkBuffer = NULL;
DWORD gdwChunkSize;

void Debug(const char *format, ...)
{
  char buffer[MAX_PATH];
  va_list ap;
  va_start(ap, format);
  vsnprintf(buffer, MAX_PATH, format, ap);
  va_end(ap);
  MessageBox(NULL, buffer, "Debug", MB_OK | MB_ICONASTERISK);
}

void Fatal(bool choice, const char *format, ...)
{
  char buffer[MAX_PATH];

  va_list ap;
  va_start(ap, format);
  vsnprintf(buffer, MAX_PATH, format, ap);
  va_end(ap);

  if ( choice )
  {
    switch( MessageBox(NULL, buffer, "Warning", MB_YESNO | MB_ICONWARNING) )
    {
    case IDYES:
      return;
    case IDNO:
    default:
      break;
    }
  }
  else
    MessageBox(NULL, buffer, "Error", MB_OK | MB_ICONHAND);

  if ( ghFile )
  {
    SFileCloseFile(ghFile);
    ghFile = NULL;
  }

  if ( ghMpq )
  {
    SFileCloseArchive(ghMpq);
    ghMpq = NULL;
  }

  if ( gpChkBuffer )
  {
    SMemFree(gpChkBuffer, __FILE__, __LINE__, 0);
    gpChkBuffer = NULL;
  }
  exit(1);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
// Function variables
  char szFileName[MAX_PATH];
  DWORD dwExtension;
  DWORD dwBytesRead = 0;

// Low level command line parse
  if ( strlen(lpCmdLine) == 0)
    Fatal(false, "Must pass a file name to the command line.");
  int k = 0;
  for (int i = 0; lpCmdLine[i] != 0 && i < MAX_PATH; i++)
  {
    if ( lpCmdLine[i] < ' ' )
      continue;

    int j = 0;
    for (; illegal[j] != 0 && lpCmdLine[i] != illegal[j]; j++) {}

    if ( lpCmdLine[i] == illegal[j] )
      continue;

    szFileName[k] = lpCmdLine[i];
    k++;
  }
  szFileName[k] = 0;

  // Get extension as a value
  dwExtension = REVERSE(*(DWORD*)strlwr(strrchr(szFileName, '.')));
  switch( dwExtension )
  {
  case '.rep':
    Debug("Starcraft Replay File");
    Fatal(false, "Starcraft replays are currently unsupported.");
    break;
  case '.snx':
  case '.mlx':
    Debug("Starcraft Save File");
    Fatal(false, "Starcraft save files are currently unsupported.");
    break;
  case '.sav':
  case '.mlt':
    Debug("Warcraft II Save File");
    Fatal(false, "Warcraft II save files are currently unsupported.");
    break;
  default:
    if ( SFileOpenArchive(szFileName, 0, 0, &ghMpq) && ghMpq )
    {
      if ( !SFileOpenFileEx(ghMpq, "staredit\\scenario.chk", SFILE_FROM_MPQ, &ghFile) || !ghFile)
        Fatal(false, "Unable to open '%s'.", "staredit\\scenario.chk");
      Debug("MPQ File");
    }
    else
    {
      if ( !SFileOpenFileEx(NULL, szFileName, SFILE_FROM_ABSOLUTE, &ghFile) || !ghFile)
        Fatal(false, "Unable to open '%s'.", szFileName);
      Debug("Chunk File (pud, chk)");
    }
    // Get file size
    gdwChunkSize = SFileGetFileSize(ghFile, 0);

    // Verify valid file size
    if ( gdwChunkSize < 8)
      Fatal(false, "Bad file size.");

    // Create file buffer
    gpChkBuffer = SMemAlloc(gdwChunkSize, __FILE__, __LINE__, 0);
    if ( !gpChkBuffer )
      Fatal(false, "Unable to allocate %d bytes of memory.", gdwChunkSize);

    // Read file to buffer
    SFileReadFile(ghFile, gpChkBuffer, gdwChunkSize, &dwBytesRead, 0);
    if ( dwBytesRead != gdwChunkSize )
      Fatal(false, "Unable to read chunk data.");

    // Close handles
    SFileCloseFile(ghFile);
    ghFile = NULL;
    if ( ghMpq )
    {
      SFileCloseArchive(ghMpq);
      ghMpq = NULL;
    }
    break;
  }

// /-\|/-\| DO STUFF /-\|/-\|

  ReadScenarioFile();



// Free memory
  SMemFree(gpChkBuffer, __FILE__, __LINE__, 0);
  gpChkBuffer = NULL;
  return 0;
}

