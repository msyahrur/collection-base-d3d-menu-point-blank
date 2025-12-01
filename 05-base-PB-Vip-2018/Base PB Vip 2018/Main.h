//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//--        // Created By : MhmmdYogiSaputra                                                               --  
//--        // Facebook   : https://www.facebook.com/gigntng                                               --
//--        // Youtube    : https://www.youtube.com/channel/UCoCztOogokhBSJoAFWiW1yA                       --
//--       // Website    : http://www.pintercit.me/                                                        --
//--                                                                                                       --
//--        // CopyRight 2018  ( Woy Ngentod Jangan Di Ganti CopyRight Dan Created Hargain Anjing Kontol ) --
//--                                                                                                       -- 
//------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <wininet.h>
#include <time.h>
#include <cstdint>
#include <string>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
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
#include <wininet.h>
#include <conio.h>
#include <tchar.h>
#include <Iphlpapi.h>
#include <Assert.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment (lib, "wininet.lib")
#include <iostream>
#include <string>
using namespace std;

#include <psapi.h>
#pragma comment(lib,"psapi.lib")

#pragma message("SourceCode Database By : MhmmdYogiSaputra")
#pragma message("Created By             : MhmmdYogiSaputra")

#pragma warning (disable : 4996)
using namespace std;
#define CDllExport extern "C" __declspec( dllexport )
#define DllExport __declspec( dllexport )

//==============================================================================================================================================
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

float ScreenCenterX, ScreenCenterY = 0;
bool Generate = false;
bool hooked = false;
typedef HRESULT (WINAPI* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene = NULL;
typedef HRESULT (WINAPI* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
tDrawIndexedPrimitive oDrawIndexedPrimitive = NULL;
typedef HRESULT (WINAPI* tReset)(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
tReset oReset = NULL;

string LocalDllName;

void HookResetDevice();

int VoteMenuIdx = 0;
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//--        // Created By : MhmmdYogiSaputra                                                               --  
//--        // Facebook   : https://www.facebook.com/gigntng                                               --
//--        // Youtube    : https://www.youtube.com/channel/UCoCztOogokhBSJoAFWiW1yA                       --
//--       // Website    : http://www.pintercit.me/                                                        --
//--                                                                                                       --
//--        // CopyRight 2018  ( Woy Ngentod Jangan Di Ganti CopyRight Dan Created Hargain Anjing Kontol ) --
//--                                                                                                       -- 
//------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------