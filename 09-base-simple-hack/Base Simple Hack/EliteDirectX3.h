//----------------------------------------------------------------------------------------------//
#include <windows.h>
#include < stdio.h>
#include <fstream>
#include <d3dx9.h>
#include <Psapi.h>
#include <ctime>
#include <vector>
//----------------------------------------------------------------------------------------------
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
//----------------------------------------------------------------------------------------------
#pragma warning (disable : 4996 4244)
//----------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------
#define CDllExport extern "C" __declspec( dllexport )
#define DllExport __declspec( dllexport )
//----------------------------------------------------------------------------------------------
int Create;
DWORD dwDIP, dwES;
LPDIRECT3DVERTEXBUFFER9 Stream_Data;
LPDIRECT3DDEVICE9 npDevice;
D3DVIEWPORT9 g_ViewPort;
LPDIRECT3DTEXTURE9 Red;
LPDIRECT3DTEXTURE9 Blue;
LPD3DXLINE g_pLine  = NULL; //D3D Line
LPD3DXFONT g_pFont = NULL; //D3D Font
UINT Offset, Stride = 0;
//----------------------------------------------------------------------------------------------
float ScreenCenterX, ScreenCenterY = 0;
bool Generate = false;
bool hooked = false;
//----------------------------------------------------------------------------------------------