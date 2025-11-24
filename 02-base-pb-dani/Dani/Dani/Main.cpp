//Created by DANI XCT / WA DANI IDI/MENU XXN PART 2
#include "StdAfx.h"
#include "Main.h"
#include "Hdsn.h"
#include "InputHdsn.h"
#include "DirectInputKey.h"
#include "D3DColor.h"
#include "AddyFunction.h"
#include "AddyLogger.h"
#include "CRenderContext.h"
#include "CGameFramework.h"
#include "CGameContext.h"
#include "CGameCharaBase.h"
#include "CGameCharaManager.h"
#include "GameClasses.h"
#include "FeatureStruct.h"
#include "DrawingTools.h"
#include "ESPFunctions.h"
#include "ESPLoop.h"
#include "HackFunctions.h"
#include "HackHook.h"
#include "HackLoop.h"
#include "MenuSound.h"
#include "MenuClass.h"
#include "MENUXNN.h"
#include "D3DHack.h"
#include "D3DHook.h"

cFeature Feature;

void MainThread()
{
	LogAddyValues();
	HookSetEnd();
	HookLocalTime();
	InitializeVisibleCheck();
	StartRoutine(HookJumpHight);
	StartRoutine(HookAutoMacro);
	StartRoutine(HookSetEvent);
	StartRoutine(ThreadHook);
}

//BOOL WINAPI DllMain (HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
//{
//	if(dwReason == DLL_PROCESS_ATTACH)
//	{	
//		//StartRoutine(Read_HDSN8);
//		StartRoutine(MainThread);
//		Beep(1000, 100);
//		//MessageBox(0, "Created by Dani Xct\nCEO. VIP-Xlonz", "Info", MB_OK | MB_ICONINFORMATION );
//	}
//return TRUE;
//}



void *DetourCreate(BYTE *src, const BYTE *dst, const int len)
{
BYTE *jmp;
 DWORD dwback;
 DWORD jumpto, newjump;

 VirtualProtect(src,len,PAGE_READWRITE,&dwback);

 if(src[0] == 0xE9)
 {
  jmp = (BYTE*)malloc(10);
  jumpto = (*(DWORD*)(src+1))+((DWORD)src)+5;
  newjump = (jumpto-(DWORD)(jmp+5));
  jmp[0] = 0xE9;
  *(DWORD*)(jmp+1) = newjump;
  jmp += 5;
  jmp[0] = 0xE9;
  *(DWORD*)(jmp+1) = (DWORD)(src-jmp);
 }
 else
 {
  jmp = (BYTE*)malloc(5+len);
  memcpy(jmp,src,len);
  jmp += len;
  jmp[0] = 0xE9;
  *(DWORD*)(jmp+1) = (DWORD)(src+len-jmp)-5;
 }
 src[0] = 0xE9;
 *(DWORD*)(src+1) = (DWORD)(dst - src) - 5;

 for(int i = 5; i < len; i++)
  src[i] = 0x90;
 VirtualProtect(src,len,dwback,&dwback);
 return (jmp-len);
}
//=============================================//
typedef HRESULT(APIENTRY* oPresent) (IDirect3DDevice9*, const RECT *, const RECT *, HWND, const RGNDATA *);
HRESULT APIENTRY Present_hook(IDirect3DDevice9*, const RECT *, const RECT *, HWND, const RGNDATA *);
oPresent pPresent = 0;
//=============================================//
HRESULT APIENTRY Present_hook(IDirect3DDevice9* pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
 //menu...
	
	RainBow();
	DrawD3DFont(pDevice);
	DrawD3DMenu(pDevice);
  return pPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}
//=============================================//
DWORD*vtbl=0;
DWORD end,pre;
int HookpDevice(void)
{
DWORD hD3D9=(DWORD)LoadLibraryA("d3d9.dll");
DWORD table=FindPattern(hD3D9,0x128000,(PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86","xx????xx????xx");
 
memcpy(&vtbl,(void*)(table+2),4); 
pre = vtbl[17];  
pPresent=(oPresent)DetourCreate((PBYTE)pre,(PBYTE)Present_hook,5); 
return 0;
}
//=============================================//
bool ck =true;
BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
DisableThreadLibraryCalls(hDll);
if (dwReason==DLL_PROCESS_ATTACH)
{
CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)HookpDevice,NULL,NULL,NULL); 
}
return TRUE;
}