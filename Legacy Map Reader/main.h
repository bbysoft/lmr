#pragma once
#include <windows.h>
#include <stdio.h>
#include "storm.h"
#include "chunk.h"

extern void   *gpChkBuffer;
extern DWORD  gdwChunkSize;

void Debug(const char *format, ...);
void Fatal(bool choice, const char *format, ...);

