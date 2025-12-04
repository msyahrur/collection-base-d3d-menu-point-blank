/*++

Copyright (c) Main Cit 96 Corporation.  All rights reserved.

Module Name:

 Modul.cpp

Abstract:

    Type definitions for the basic sized types.

Author:

Revision History:

--*/
#include "cStdafx.h"
#include "cMenu.h"
#include "cStride.h"

bool  ChekAimHook=false;
DWORD GetOriginalEndScene();
bool GuProSettimer1 = true;
BYTE RET[] = {0xC3}; 
BYTE PUSH_EBP[]= {0x55}; 
BYTE JUMP[] = {0xEB}; 
BYTE RETURN[] = {0xC3}; 
void InstallMyMenu( LPDIRECT3DDEVICE9 pDevice )
{
	if( !BFont )
	{
		D3DXCreateLine(pDevice, &pLine );
		BFont = TRUE;
	}
	
	if(!pFont)D3DXCreateFontA(pDevice, 14, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
	if(!pFont2)D3DXCreateFontA(pDevice, 13, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont2 );
	if(!fName)D3DXCreateFontA(pDevice, 13, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &fName);
	//-------------------------------------------------------------------------------------------------------//
if (Drawing == 0)
	{
		if(Mmax==0) 
		if(Menu && pFont)
		{
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
			RebuildMenu(pDevice);
		}
//-------------------------------------------------------------------------------------------------------//		
		
		MenuShow(mx,my,pDevice);
		MenuNav();
		ColorRainBow();
	}	
}

bool stateReset[2] = {0};
typedef HRESULT ( WINAPI* tEndScene ) ( LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene;
//-----------------------------------------------------------------------------------------------------------------------------------
HRESULT _stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{	
	if(stateReset[0] == true)
		goto skipES;
	InstallMyMenu(pDevice);
	if (!pFont || !pFont2 ||!fName ||pLine)
	{
		pFont->OnLostDevice();
		pFont2->OnLostDevice();
		fName->OnLostDevice();
		pLine->OnLostDevice();
	}
	else
	{
		pFont->OnLostDevice();
		pFont->OnResetDevice();
		pFont2->OnLostDevice();
		pFont2->OnResetDevice();
		fName->OnLostDevice();
		fName->OnResetDevice();
		pLine->OnLostDevice();
		pLine->OnResetDevice();
	}

//---------------------------------------------------------------------------------
skipES:
	oEndScene = (tEndScene)GetOriginalEndScene();
return oEndScene(pDevice);
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


DWORD GetOriginalEndScene(){return pEndScene;}

void CallProcessThread ()
{
	Beep(1000,200);	
	MC96(MC96Updater);	
	MessageBox(0, "Enable","Info", MB_OK + MB_ICONINFORMATION );	
}

BOOL APIENTRY DllMain(HINSTANCE zlib1, DWORD reason, LPVOID lpvReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		MC96(CallProcessThread);	
	}
	return TRUE;
}