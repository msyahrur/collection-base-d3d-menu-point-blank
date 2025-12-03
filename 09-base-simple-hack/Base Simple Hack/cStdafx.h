//------------------------------------------------------------------------------//
//							Coded By Zaki Mubarak									//
//							Date Create : 11 April 2016							//
//------------------------------------------------------------------------------//
#include <windows.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <direct.h>
#include <fcntl.h>
#include <io.h>
#include <vector>
#include <rpc.h>
#include <rpcdce.h>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include <tlhelp32.h>
#include <process.h>
#include <shellapi.h>
#include "winsock.h"
#include <fstream>
#include <string>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <sapi.h>
#include <wininet.h>
#include <conio.h>
#include <tchar.h>
#include <Iphlpapi.h>
#include <Assert.h>
#define PSAPI_VERSION 1
#include <Mmsystem.h>
#include "X0r.h"


//EnumProcess
#include <Psapi.h>
#pragma comment(lib, "Psapi.lib")

//CreateToolHelp32Snapshot
#include <TlHelp32.h>
#pragma warning(disable:4996 4244 4551 4715 4700 4129 4552 4806)
#pragma warning (disable:4309 4244 4996 4102 4305 4566 4307)
//----------------------------------------------//
#pragma comment(lib, "iphlpapi.lib")
#pragma comment( lib, "winmm.lib" )
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment (lib, "wininet.lib")
#pragma comment(lib,"psapi.lib")
//#pragma comment(lib,"zdll.lib")
#pragma comment(lib, "WinMM.Lib")

#pragma message("Harry Petter!")
#pragma message("@2017")
#pragma message("All Source...")
#pragma message("XMakerHack")
#include <Windows.h>

//enum Hotkey : int
//{
//KEY_A = 0x41,
//KEY_B = 0x42,
//KEY_C = 0x43,
//KEY_D = 0x44,
//KEY_E = 0x45,
//KEY_F = 0x46,
//KEY_G = 0x47,
//KEY_H = 0x48,
//KEY_I = 0x49,
//KEY_J = 0x4A,
//KEY_K = 0x4B,
//KEY_L = 0x4C,
//KEY_M = 0x4D,
//KEY_N = 0x4E,
//KEY_O = 0x4F,
//KEY_P = 0x50,
//KEY_Q = 0x51,
//KEY_R = 0x52,
//KEY_S = 0x53,
//KEY_T = 0x54,
//KEY_U = 0x55,
//KEY_V = 0x56,
//KEY_W = 0x57,
//KEY_X = 0x58,
//KEY_Y = 0x59,
//KEY_Z = 0x5A,
//};

#define VK_A           0x41
#define VK_B           0x42
#define VK_C           0x43
#define VK_D           0x44
#define VK_E           0x45
#define VK_F           0x46
#define VK_G           0x47
#define VK_H           0x48
#define VK_I           0x49
#define VK_J           0x4A
#define VK_K           0x4B
#define VK_L           0x4C
#define VK_M           0x4D
#define VK_N           0x4E
#define VK_O           0x4F
#define VK_P           0x50
#define VK_Q           0x51
#define VK_R           0x52
#define VK_S           0x53
#define VK_T           0x54
#define VK_U           0x55
#define VK_V           0x56
#define VK_W           0x57
#define VK_X           0x58
#define VK_Y           0x59
#define VK_Z           0x5A
#define VK_0           0x30
#define VK_1           0x31
#define VK_2           0x32
#define VK_3           0x33
#define VK_4           0x34
#define VK_5           0x35
#define VK_6           0x36
#define VK_7           0x37
#define VK_8           0x38
#define VK_9           0x39