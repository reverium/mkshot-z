#pragma once


#include <iostream>
#include <windows.h>
#include <fcntl.h>
#include <io.h>

bool setupWindowsConsole();

void reopenWindowsStreams();

int getStdFD(const DWORD &nStdHandle);

#endif
