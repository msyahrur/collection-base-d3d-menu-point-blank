//Bagus Tuyul
#pragma once

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define CDllExport extern "C" __declspec( dllexport )
#define DllExport __declspec( dllexport )

#include <windows.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <stdlib.h>
#include <direct.h>
#include <fcntl.h>
#include <io.h>
#include <vector>
#include <rpc.h>
#include <rpcdce.h>
#include <iomanip>
#include <cstdlib>
#include <tlhelp32.h>
#include <process.h>
#include <shellapi.h>
#include "winsock.h"
#include <fstream>
#include <string>
#include <string.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <wininet.h>
#include <Iphlpapi.h>
#include <Assert.h>
#include <winbase.h>
#include <winternl.h>
#include <psapi.h>
#include <mmsystem.h>
#pragma comment(lib,"iphlpapi.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"wininet.lib")
#pragma comment(lib,"WinMM.Lib")
#pragma comment(lib,"psapi.lib")
#pragma warning(disable:4996 4244 4715 4551)
using namespace std;