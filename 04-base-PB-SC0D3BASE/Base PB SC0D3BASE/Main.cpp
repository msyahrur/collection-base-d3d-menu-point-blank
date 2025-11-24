//CREATED BY SC0D3 Solusi Game No Di Indoneisa
#include "StdAfx.h"
#include "XorStr.h"
#include "InputKey.h"
#include "Color.h"
#include "Sound.h"
#include "Texture.h"
#include "Defines.h"
#include "Struct.h"
#include "Function.h"
#include "Logger.h"
#include "Class.h"
#include "Draw.h"
#include "Esp.h"
#include "GameHack.h"
#include "GBMode.h"
#include "OutGame.h"
#include "Menu.h"
#include "Main.h"
#include "XN2HDSN.h"
#include "XN2INPUT.h"
#include "XN2XORSTR.h"

float __fastcall hkGetLocalTime(DWORD Base){

	float retVal = pGetLocalTime(Base);
	for(int i = 0; i < 100; i++)
	{
		if(ModifyTargetBase[i] > NULL && ModifyTargetBase[i] == Base){
			if(i == 0)retVal = 2.519999862f;
			if(i == 1 || i == 2){
				if(GetAsyncKeyState(VK_R)){
					__asm {
						lea edx,retVal
						mov [edx + 3],0x41
					}
				}
			}
			break;
		}
	}
	return retVal;
}

void HookLocalTime()
{
if(bHookedLT)return;
	pGetLocalTime = (tGetLocalTime)MakePTR((PBYTE)AddyEngine->GetAddyValueByKey("XFHPB.Import.i3AiContext::getLocalTime"),(DWORD)hkGetLocalTime);
	bHookedLT = true;
}

DWORD pSetEnd;
_declspec(naked) void hkSetEnd(){
	__asm 
	{
		sub esp, 0x8
		push esi
	}
	DWORD dwOrigLine;
	__asm
	{
		mov eax,[esp + 0x10];
		mov [dwOrigLine],eax
	}
	dwOrigLine = SetEndVector->GetSetEndVector(dwOrigLine);
	__asm
	{
		mov eax,[dwOrigLine];
		mov [esp + 0x10],eax
	}
	__asm 
	{
		pop esi
		add esp, 0x8
	}
	__asm jmp pSetEnd;
}

void HookSetEnd()
{
	SetEndVector = new pSetEndVector();
	if(bHookedTele)return;
	pSetEnd = MakePTR((PBYTE)AddyEngine->GetAddyValueByKey("XFHPB.Import.i3CollideeLine::SetEnd"),(DWORD)hkSetEnd);
	bHookedTele = true;
}

HRESULT WINAPI hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	if(pFont){
        pFont->OnLostDevice();
	}
	if(mFont){
        mFont->OnLostDevice();
	}
    if(g_pFont){
        g_pFont->OnLostDevice();
	}
    if(g_pLine){
        g_pLine->OnLostDevice();
	}
    if(oReset == D3D_OK) 
	{
		if(pFont){
            pFont->OnResetDevice();
		}
		if(mFont){
            mFont->OnResetDevice();
		}
		if(g_pFont){
            g_pFont->OnResetDevice();
		}
        if(g_pLine){
            g_pLine->OnResetDevice();
		}
		if(textSprite){
			textSprite->OnResetDevice();
		}
	}
    return oReset(pDevice, pPresentationParameters);
}

DWORD pEndScene;
int cInit = 0;
_declspec(naked)void hkEndRender()
{
	__asm {
		mov eax,[ecx+0x53A8]
		mov ecx,[eax]
		mov edx,[ecx+0xA8]
		mov [pEndScene],edx
		cmp [cInit],0
		je InitES
		cmp [cInit],1
		je Normal
		cmp [cInit],2
		je ReInitES
InitES:
        push eax
		call hkEndScene
		mov [cInit],1
		retn
Normal:
        push eax
        call edx
		mov [cInit],2
		retn
ReInitES:
		push eax
		call hkEndScene
        retn           
	}
}
DWORD pDrawIndexedPrimitive;
DWORD m_pCaps, SelectShader = 0;
_declspec(naked)void hkDrawIndexedPrim()
{
	_asm
	{
		push ebx
        push esi
        push edi
        mov edi,dword ptr ss:[esp+0x1c]
        mov esi,ecx
        add dword ptr ds:[esi+0xF8],edi
        mov ebx,0x1
        add dword ptr ds:[esi+0x14],ebx
        mov eax,dword ptr ds:[m_pCaps]
		mov eax,[eax];
        cmp dword ptr ds:[eax+0x150],0x0
        je i3GfxDx_100CBFC3 
        mov ecx,dword ptr ss:[esp+0x10]
        push 0x0
        push ecx
        mov ecx,esi
        call [SelectShader] ;<= Jump/Call Address Not Resolved

i3GfxDx_100CBFC3: 

        cmp byte ptr ds:[esi+0x160],0x0
        je i3GfxDx_100CC112
        cmp dword ptr ds:[esi+0x5468],ebx
        jnz i3GfxDx_100CC112 

        mov eax,dword ptr ds:[esi+0x5458]
        mov ebx,dword ptr ds:[esi+0x5464]
        mov edx,dword ptr ds:[eax+0x1e0]
        push ebp
        mov ebp,dword ptr ds:[eax+0x188]
        xor edi,edi
        imul ebx,ebp
        cmp dword ptr ds:[esi+0x5450],edi
        mov dword ptr ss:[esp+0x14],edx
        jle i3GfxDx_100CC085 

i3GfxDx_100CC0B0: 

        mov edx,dword ptr ss:[esp+0x14]
        mov eax,dword ptr ds:[esi+0x53A8]
        mov ecx,dword ptr ds:[eax]
        push 0x0
        push ebx
        push edx
        push 0x1
        push eax
        mov eax,dword ptr ds:[ecx+0x190]
        call eax
        mov edx,dword ptr ss:[esp+0x20]
        mov eax,dword ptr ds:[esi+0x53A8]
        mov ecx,dword ptr ds:[eax]
        push edx
        mov edx,dword ptr ss:[esp+0x20]
        push edx
        mov edx,dword ptr ds:[esi+0x924]
        mov edx,dword ptr ds:[edx+0x170]
        push edx
        mov edx,dword ptr ss:[esp+0x24]
        push 0x0
        push 0x0
        push edx
        push eax
        mov eax,dword ptr ds:[ecx+0x148]
		mov [pDrawIndexedPrimitive],eax
        call hkDrawIndexedPrimitive
        inc edi
        add ebx,ebp
        cmp edi,dword ptr ds:[esi+0x5450]
        jl i3GfxDx_100CC0B0 

i3GfxDx_100CC085: 

        mov eax,dword ptr ds:[esi+0xAE8]
        pop ebp
        pop edi
        pop esi
        pop ebx
        retn 0x10

i3GfxDx_100CC112: 

        mov edx,dword ptr ss:[esp+0x18]
        mov eax,dword ptr ds:[esi+0x53A8]
        mov ecx,dword ptr ds:[eax]
        push edi
        push edx
        mov edx,dword ptr ds:[esi+0x924]
        mov edx,dword ptr ds:[edx+0x170]
        push edx
        mov edx,dword ptr ss:[esp+0x20]
        push 0x0
        push 0x0
        push edx
        push eax
        mov eax,dword ptr ds:[ecx+0x148]
		mov [pDrawIndexedPrimitive],eax
        call hkDrawIndexedPrimitive
        mov eax,dword ptr ds:[esi+0xAE8]
        pop edi
        pop esi
        pop ebx
        retn 0x10
	}
}
IDirect3D9 * HookDirect3DCreate9(VOID)
{
    DWORD Base = (DWORD)LoadLibraryW(L"d3d9.dll");
 
    for(DWORD i = 0; i < 0x128000; i++ )
    {
      if ( (*(BYTE *)(Base+i+0x00))==0xC7
        && (*(BYTE *)(Base+i+0x01))==0x06
        && (*(BYTE *)(Base+i+0x06))==0x89
        && (*(BYTE *)(Base+i+0x07))==0x86
        && (*(BYTE *)(Base+i+0x0C))==0x89
        && (*(BYTE *)(Base+i+0x0D))==0x86 )
        return (IDirect3D9*)(Base + i + 2);
    }
    return NULL;
}
IDirect3D9 *pD3D;
void __fastcall HookD3D9()
{
	while(!pD3D){
		pD3D=HookDirect3DCreate9();
	}
	DWORD *VD3D	= (DWORD*)pD3D;
	VD3D = (DWORD*)VD3D[0];
	oReset = (tReset) DetourFunction((PBYTE)VD3D[16], (PBYTE)hkReset, 5);
	//oEndScene = (tEndScene) DetourFunction((PBYTE)VD3D[42], (PBYTE)hkEndScene, 5);
	//oDrawIndexedPrimitive = (tDrawIndexedPrimitive)	DetourFunction((PBYTE)VD3D[82], (PBYTE)hkDrawIndexedPrimitive, 5);
	Sleep(10);
}
DWORD GetOriginalEndScene()
{
	return pEndScene;
}

DWORD GetOriginalDIP()
{
	return pDrawIndexedPrimitive;
}

void ThreadHook()
{
	MakePTR((PBYTE)AddyEngine->GetAddyValueByKey("XFHPB.Import.i3RenderContext::EndRender"),(DWORD)hkEndRender);
}
	void HookJumpHight()
{
	pUpdateJumpJMP = AddyEngine->GetAddyValueByKey("XFHPB.Function.UpdateJumpJMP");
	MakeJMP((PBYTE)AddyEngine->GetAddyValueByKey("XFHPB.Function.UpdateJumpX"), (DWORD)JumperThread, 5);
}

void CallerThread()
{
	LogAddyValues();
	ScannerLogger();
	HookLocalTime();
	HookSetEnd();
	InitializeVisibleCheck();
	StartRoutine(Hook_Brust);
	StartRoutine(Hook_MouseMacro);
    StartRoutine(HookJumpHight);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HookD3D9,NULL,NULL,NULL);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ThreadHook,NULL,NULL,NULL);
}
//
//DWORD ModuleP			= (DWORD)GetModuleHandleA("PointBlank.exe");
//bool WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
//{
//	if(dwReason == DLL_PROCESS_ATTACH && ModuleP){
//		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CallerThread,NULL,NULL,NULL);
//	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Read_HDSN8,NULL,NULL,NULL);
//		MessageBox (0,"Cheat Aktif !!.","Information", MB_OK | NULL);
//		GetModuleFileName(hModule, dlldir, 512);
//		for(int i = strlen(dlldir); i > 0; i--) { if(dlldir[i] == '\\') { dlldir[i+1] = 0; break;}}
//		infile.open(GetDirectoryFile("SearchLogger.txt"), ios::out);
//		Beep(1000, 100);
//	}
//	return TRUE;
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
		DirectInputLoop();
	DrawRainBow();
	DrawMenuD3D(pDevice);
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