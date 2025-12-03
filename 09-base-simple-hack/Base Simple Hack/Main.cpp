//------------------------------------------------------------------------------//
//							Coded By Zaki Mubarak									//
//							Date Create : 11 April 2016							//
//------------------------------------------------------------------------------//
#include "cStdafx.h"
#include "cMenu.h"
#include "cStride.h"
#include "cAim.h"
#include "cString.h"
#include "cInGame.h"
#include "cOutGame.h"
bool  ChekAimHook=false;
DWORD GetOriginalEndScene();
bool GuProSettimer1 = true;
BYTE RET[] = {0xC3}; //deklarasi byte untuk RET
BYTE PUSH_EBP[]= {0x55}; //deklarasi byte untuk PUSH_EBP
BYTE JUMP[] = {0xEB}; //deklarasi byte untuk RET
BYTE RETURN[] = {0xC3}; //deklarasi byte untuk RET
void InstallMyMenu( LPDIRECT3DDEVICE9 pDevice )
{
	if (GuProSettimer1 == true)
	{
		GuProSettimer1 = false;
	}
//-----------------------------MenuD3D-----------------------------//
	if( !BFont )
	{
		D3DXCreateLine(pDevice, &pLine );	
		//MEMpatch((BYTE*)BypassI3Error, JUMP, sizeof(JUMP));
		//MEMpatch((BYTE*)Result__CreateRoomMasterKick, RET, sizeof(RET));  // AntiRoomMasterKick
//------------------------------------------------------------------
		//if(!IsInBattle()) // ON
		//{		
		////	HookSetEvent();
		////	HookChatEvent();
		//	//HookSetEnd();
		//	HookLocalTime();
		//	MEMpatch((BYTE*)LogAntiKickOut, RET, sizeof(RET));
		//}

		//if(IsInBattle()) // OFF
		//{	
		//	MEMpatch((BYTE*)LogAntiKickOut, PUSH_EBP, sizeof(PUSH_EBP));
		//}

		BFont = TRUE;
	}
	
	if(!pFont)D3DXCreateFontA(pDevice, 14, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Consolas", &pFont);
	if(!pFont2)D3DXCreateFontA(pDevice, 13, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Time New Roman", &pFont2 );
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
		DirectInputLoop();
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
CallPlayerESP(pDevice);
Crosshair(pDevice, RainbowTextTest);
CallBypassAbuse();
CallPlantC4();
CallZombie();
CallHack();
CallBrustWeapon();
CallNightVision();

CallFuncInGame();
CallFuncOutGame();
if(IsInBattle())
{
	//HookBurst();
	if(GetAsyncKeyState(VK_RCONTROL)&1){Zombie=!Zombie;}
	if(GetAsyncKeyState(VK_F3)&1){NoRecoil=!NoRecoil;}
	if(GetAsyncKeyState(VK_F4)&1){wutmo=!wutmo;}
	if(GetAsyncKeyState(VK_F5)&1){Zombie=!Zombie;}
	if(GetAsyncKeyState(VK_F7)&1){FastKiller=!FastKiller;}
	if(GetAsyncKeyState(VK_F9)&1){BugUnyu=!BugUnyu;}
	if(GetAsyncKeyState(VK_F12)&1){Beep(2500,500);ExitProcess(0);}
	if(GetAsyncKeyState(VK_HOME)&1){AimBullet=!AimBullet;}
	if(GetAsyncKeyState(VK_END)&1){CGameCharaBase::g_pPlayer()->Cmd_Damage(0x64);}
	if(Suicide){CGameCharaBase::g_pPlayer()->Cmd_Damage(0x64);;}
	if(FastExit){Beep(2500,500);ExitProcess(0);}
}else{}
CheckMyProfile();
RebuildMenuOff();
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

typedef HRESULT (WINAPI* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
tDrawIndexedPrimitive oDrawIndexedPrimitive = NULL;
HRESULT WINAPI hkDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{
	if(stateReset[1] == true)
	if(IsInBattle())
	{
		if(NoSmoke==1){
			pDevice->SetRenderState(D3DRS_FOGENABLE, false);
			if((NumVertices == 192) || (NumVertices == 256))return D3D_OK;}

	}
	return oDrawIndexedPrimitive(pDevice,PrimType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount);
}

DWORD GetOriginalEndScene(){return pEndScene;}

void CallProcessThread ()
{
	Beep(1000,200);
	EliteWorldCyber(XMCR_Updater);	
	Exit=true;
	EliteWorldCyber(UpdateHack);	
}

 
BOOL APIENTRY DllMain(HINSTANCE zlib1, DWORD reason, LPVOID lpvReserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		EliteWorldCyber(CallProcessThread);			
	}
	return TRUE;
}