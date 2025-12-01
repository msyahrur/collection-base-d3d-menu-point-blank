//===============================================================//
// Source PointBlank Hacks By ZeRo-CyBeRz Hacks [www.zero-cyberz-server.com]
// D3D Menu By UC Forum [www.unknowncheats.me] || Last Edit By Y.L.A.S
//===============================================================//
#pragma warning (disable:4099)

#include "CMenu.h"
#include "CSound.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <windows.h>
#include <sddl.h>
#include <accctrl.h>
#include <stdio.h>
#include <conio.h>
#include <aclapi.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include "CGameOFS.h"
#include "CBulletKill.h"
#include "CHook.h"
#include "CStride.h"

cMenu Menu;
copt opt;
cSound Sound;
LPDIRECT3DVERTEXBUFFER9 Stream_Data;
UINT Offset = 0;
UINT Stride = 0;

void PreReset( LPDIRECT3DDEVICE9 pDevice )
{ 
	Menu.PreReset();
	return;
}

void PostReset( LPDIRECT3DDEVICE9 pDevice )
{ 
	Menu.PostReset(pDevice);
	return;
}

typedef HRESULT ( WINAPI* oReset )( LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters );
oReset pReset;
typedef HRESULT	( WINAPI* oEndScene )( LPDIRECT3DDEVICE9 pDevice );
oEndScene pEndScene;
typedef HRESULT (WINAPI* oDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
oDrawIndexedPrimitive pDrawIndexedPrimitive;


HRESULT APIENTRY HkReset( LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters )
{
	_asm pushad;
	Menu.PreReset();
    Tools.pLine->OnLostDevice();
	pFont2->OnLostDevice();
	textSprite->OnLostDevice();
	Tools.g_pLine->OnLostDevice();
	
	Tools.pLine->OnResetDevice();
	pFont2->OnResetDevice();
	textSprite->OnResetDevice();
	Tools.g_pLine->OnResetDevice();
	
	_asm popad;

	return pReset( pDevice, pPresentationParameters );
}

void DrawCross( LPDIRECT3DDEVICE9 pDevice )
{
	if (opt.d3d.CrosCol ==0)CrossCol=WHITE;
	if (opt.d3d.CrosCol ==1)CrossCol=RED;
	if (opt.d3d.CrosCol ==2)CrossCol=GREEN;
	if (opt.d3d.CrosCol ==3)CrossCol=BLUE;
	if (opt.d3d.CrosCol ==4)CrossCol=GREY;
	if (opt.d3d.CrosCol ==5)CrossCol=YELLOW;
	if (opt.d3d.CrosCol ==6)CrossCol=ORANGE;
	if(opt.d3d.Cross)
	{
		int x = ( GetSystemMetrics( 0 ) / 2);
		int y = ( GetSystemMetrics( 1 ) / 2);
		D3DRECT RectA, RectB;
		RectA.x1 = (x)-10;
		RectA.x2 = (x)+ 10;
		RectA.y1 = (y);
		RectA.y2 = (y)+1;
		RectB.x1 = (x);
		RectB.x2 = (x)+ 1;
		RectB.y1 = (y)-10;
		RectB.y2 = (y)+10;
		pDevice->Clear(1, &RectA, D3DCLEAR_TARGET, CrossCol, 0,  0);
		pDevice->Clear(1, &RectB, D3DCLEAR_TARGET, CrossCol, 0,  0);
	}
}

void DrawMenu( LPDIRECT3DDEVICE9 pDevice )
{

	if(!Tools.Init)
	{
		D3DXCreateLine(pDevice,&Tools.g_pLine);
		D3DXCreateLine(pDevice,&Tools.pLine);
		D3DXCreateFontA(pDevice, 15, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Hud_Small_Font", &pFont2 );
		D3DXCreateSprite(pDevice, &textSprite);
		Tools.Init = TRUE;
	}
	PostReset(pDevice);
	Menu.ShowMenu(pDevice);
	DrawTextColor(pDevice);
}

HRESULT WINAPI HkEndScene ( LPDIRECT3DDEVICE9 pDevice )
{
	DrawMenu(pDevice);
	pDevice->GetViewport(&Tools.g_ViewPort);
	ScreenCenterX = (float)Tools.g_ViewPort.Width / 2;
	ScreenCenterY = (float)Tools.g_ViewPort.Height / 2;
	if ( *(PDWORD)((DWORD)BASE_AMMO2) )
	{
		DrawCross(pDevice);
		ADDXESP(pDevice);
		DoAimbot(pDevice);
		DoAimBullet(pDevice);
/*		if(opt.d3d.HeadShot){
		DoAutoHSNoSyarat(pDevice);}
		if(opt.d3d.AutoBody){
		DoAutoBody(pDevice);}
		DoAutoShot(pDevice);
/*		if(opt.d3d.KillerKey==1){
		CallLineHit(); }
		if(opt.d3d.ScdKillerKey==1){
		RangeWeapon();
		CallLineHit_Scd();}
		GhostHide();*/
//		DrawStringInBox();
		All_ThreadHax();
		if(opt.d3d.PlantCT==1){
		Cmd_Install_On(); }
		if(opt.d3d.DefuseCT==1){
		Cmd_Uninstall_On(); }
	}
	/*--------------------------------*/
	if(IsKeyPressedF(VK_F12, 0)&1){
		ExitProcess(0); }
	/*--------------------------------*/
	return pEndScene(pDevice);
}

HRESULT WINAPI HkDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{

if(pDevice->GetStreamSource(0, &Stream_Data, &Offset, &Stride) == D3D_OK){
Stream_Data->Release();
}

/*------------------------------------------- Declaration Wallhack ------------------------------------------------------*/
if(GetBattleState()){
if( opt.d3d.Wall )
{   
	if(All_Stride)   
	{            
		pDevice->SetRenderState(D3DRS_ZENABLE, false);
		pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		pDevice->SetRenderState(D3DRS_LIGHTING, D3DLIGHT_DIRECTIONAL);
		pDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
		pDevice->SetRenderState(D3DRS_ZENABLE, true);
		pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		pDevice->SetRenderState(D3DRS_LIGHTING, D3DLIGHT_DIRECTIONAL);
	}
}}

if(GetBattleState()){
if( opt.d3d.WallRbt )
{   
	if(All_Stride)   
	{            
		pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		pDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
	}
}}

/*------------------------------------------- Declaration Champs ------------------------------------------------------*/
if(GetBattleState()){
if( opt.d3d.Champ==1 )
{
	if(cTeroH)
	{
		pDevice->SetRenderState(D3DRS_ZENABLE, false);
		pDevice->SetRenderState(D3DRS_LIGHTING, D3DLIGHT_DIRECTIONAL);
		pDevice->SetTexture(0, texRed);
		pDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount); 
		pDevice->SetRenderState(D3DRS_ZENABLE, true);
		pDevice->SetRenderState(D3DRS_LIGHTING, D3DLIGHT_DIRECTIONAL);
		pDevice->SetTexture(0, texRed);
	}
	if(cPoliceH){
		pDevice->SetRenderState(D3DRS_ZENABLE, false);
		pDevice->SetRenderState(D3DRS_LIGHTING, D3DLIGHT_DIRECTIONAL);
		pDevice->SetTexture(0, texBlue);
		pDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount); 
		pDevice->SetRenderState(D3DRS_ZENABLE, true);
		pDevice->SetRenderState(D3DRS_LIGHTING, D3DLIGHT_DIRECTIONAL);
		pDevice->SetTexture(0, texBlue); 
	}
}}

/*------------------------------------------- Declaration No Smoke ------------------------------------------------------*/
if(GetBattleState()){
if( opt.d3d.Wall )
{
	if ((NumVertices == 192) || (NumVertices == 256))	  
	{
		return D3D_OK;
		return 0;
	}
}}

if(GetBattleState()){
if( opt.d3d.WallRbt )
{
	if ((NumVertices == 192) || (NumVertices == 256))	  
	{
		return D3D_OK;
		return 0;
	}
}}

/*------------------------------------------- Declaration No Fog Map ------------------------------------------------------*/
if(GetBattleState()){
if( opt.d3d.Wall )                                                   
{
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);
}}

if(GetBattleState()){
if( opt.d3d.WallRbt )                                                   
{
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);
}}
	return pDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

/*------------------------------------------- Declaration Hooked ------------------------------------------------------*/
bool LoopEngine = false;
DWORD WINAPI WriteHooking(){
HWND PointBlankWindow;
do {
	PointBlankWindow = FindWindowA(PBViewer,PBWindow);
}while (!PointBlankWindow);
Sleep(3500);
while(!NewDevice){
	ReadDevc(g_pRenderContext,END_RENDER);
	WriteHook((LPVOID)&NewDevice,(LPCVOID)ProtecGfx,4);
}
NewFuctX = (DWORD*)NewDevice;
NewFuctX = (DWORD*)NewDevice;
NewFuctX = (DWORD*)NewFuctX[0];
while(!pDevice) {
	pDevice = (LPDIRECT3DDEVICE9)(DWORD*)NewFuctX;
}
*(PDWORD)&pDrawIndexedPrimitive = NewFuctX[82];
*(PDWORD)&pEndScene = NewFuctX[42];
*(PDWORD)&pReset = NewFuctX[16];
DWORD *NewFuntion_1 = ( PDWORD )( NewFuctX[1] - 5 );
DWORD *NewFuntion_2 = ( PDWORD )( NewFuctX[2] - 5 );
DWORD *NewFuntion_3 = ( PDWORD )( NewFuctX[3] - 5 );
DWORD *NewFuntion_4 = ( PDWORD )( NewFuctX[4] - 5 );
DWORD *NewFuntion_5 = ( PDWORD )( NewFuctX[5] - 5 );
DWORD *NewFuntion_6 = ( PDWORD )( NewFuctX[6] - 5 );

NewFuntionE9((DWORD)( NewFuntion_1 ), (DWORD)( NewFuntion_4 ));
NewFuntionE9((DWORD)( NewFuntion_2 ), (DWORD)( NewFuntion_5  ));
NewFuntionE9((DWORD)( NewFuntion_3 ), (DWORD)( NewFuntion_6  ));
NewFuntionE9((DWORD)( NewFuntion_4 ), (DWORD)HkEndScene);
NewFuntionE9((DWORD)( NewFuntion_5 ), (DWORD)HkDrawIndexedPrimitive);
NewFuntionE9((DWORD)( NewFuntion_6 ), (DWORD)HkReset);
for(;;)
{
	NewFuctX[42] = (DWORD)NewFuntion_1;
	NewFuctX[82] = (DWORD)NewFuntion_2;
	NewFuctX[16] = (DWORD)NewFuntion_3;
	Sleep(100);
}
return(0);
}

/*------------------------------------------- Declaration Hacks ------------------------------------------------------*/
DWORD WINAPI ReloadGM()
{
	for(;;)
	{
		if( opt.d3d.RldM==1 )
		{
			LongPtr( (DWORD)BASE_PLAYER2, OFS_RELOAD, 0x8, 0x41AF3B3F);
			LongPtr( (DWORD)BASE_PLAYER2, OFS_RELOAD, 0xC, 0x41BE7D7E);
		}
		
/*		if(GetBattleState()){
		if( opt.d3d.NoSpread )
		{
			for( int iR = 32; iR <= 108; iR += 4 )
				LongPtr( (DWORD)BASE_AMMO2, PTR_RECOIL, iR, 0);
		}}
		
		if(GetBattleState()){
		if( opt.d3d.InfAmmo )
		{
			if(bAmmo == false)
			{
				__ReadMem( (DWORD)BASE_AMMO2, PTR_WEAPON, 0x1C, CALCWPN2, 1);
				__ReadMem( (DWORD)BASE_AMMO2, PTR_WEAPON, 0x20, CALCWPN2, 2);
				bAmmo = true;
			}
			if(bAmmo == true)
			{
				_WriteMEM( (DWORD)BASE_AMMO2, PTR_WEAPON, 0x1C, CALCWPN2, Weapon);
				_WriteMEM( (DWORD)BASE_AMMO2, PTR_WEAPON, 0x20, CALCWPN2, Pistol);
			}
		}}

/*------------------------------------------- Declaration Replace ------------------------------------------------------*/
/*		if(GetBattleState()){
		if ( opt.d3d.Bomb == 1 )
		{ 
			opt.d3d.Wst = 1;
			opt.d3d.Invi = 1;
			unsigned long PtrAdrkla = *(LPBOOL)(ResultBasePlayer2); 
			CTeam* GetSlot = (CTeam*)(PtrAdrkla + ResultTEAM);{
				MakePoint(ResultBasePlayer2, ResultSMOKE + (GetSlot->iTeam * ResultWEAPONSIZE), 0x35E20D72); // Decory
			}
		}}*/

/*		if(GetBattleState()){
		if ( opt.d3d.Bomb == 1 )
		{ 
			opt.d3d.Wst = 1;
			opt.d3d.Invi = 1;
			unsigned long PtrAdrkla = *(LPBOOL)(ResultBasePlayer2); 
			CTeam* GetSlot = (CTeam*)(PtrAdrkla + ResultTEAM);{
				MakePoint(ResultBasePlayer2, ResultSMOKE + (GetSlot->iTeam * ResultWEAPONSIZE), 0x35E20D6C); // Lolipop
			}
		}}

		if(GetBattleState()){
		if ( opt.d3d.Rpg == 1 )
		{ 
			opt.d3d.Invi = 1;
			opt.d3d.AimBullet = 1;
			unsigned long PtrAdrkla = *(LPBOOL)(ResultBasePlayer2); 
			CTeam* GetSlot = (CTeam*)(PtrAdrkla + ResultTEAM);{
				MakePoint(ResultBasePlayer2, ResultPRIMARY + (GetSlot->iTeam * ResultWEAPONSIZE), 0x5F5E8EA); // HK69
				MakePoint(ResultBasePlayer2, ResultSECONDARY + (GetSlot->iTeam * ResultWEAPONSIZE), 0x23D2902A);
				MakePoint(ResultBasePlayer2, ResultMALE + (GetSlot->iTeam * ResultWEAPONSIZE), 0x29D7B36A);
			}
		}}

		if(GetBattleState()){
		if ( opt.d3d.Rpg == 2 )
		{ 
			opt.d3d.Invi = 1;
			opt.d3d.Quick = 1;
			opt.d3d.NoReload = 1;
			opt.d3d.AimBullet = 1;
			unsigned long PtrAdrkla = *(LPBOOL)(ResultBasePlayer2); 
			CTeam* GetSlot = (CTeam*)(PtrAdrkla + ResultTEAM);{
				MakePoint(ResultBasePlayer2, ResultPRIMARY + (GetSlot->iTeam * ResultWEAPONSIZE), 0x5F61F81); // RPG7
				MakePoint(ResultBasePlayer2, ResultSECONDARY + (GetSlot->iTeam * ResultWEAPONSIZE), 0x23D2C6C1);
				MakePoint(ResultBasePlayer2, ResultMALE + (GetSlot->iTeam * ResultWEAPONSIZE), 0x29D7EA01);
			}
		}}*/

		Sleep(10);
	}
	return (0);
}

#include "CekValid.h"
/*------------------------------------------- Declaration Call All Thread ------------------------------------------------------*/
void BlogCheatGames_08062015()
{
/*	DWORD i3GfxDx,I3InputDx,i3SceneDx,i3BaseDx;
	DWORD dwStartAddress = 0x400000;
	do {
	dwStartAddress = (DWORD)GetModuleHandleA(PointBlankSTR);
	i3GfxDx = (DWORD)GetModuleHandleA(PointBlanki3Gfx);
	I3InputDx = (DWORD)GetModuleHandleA(PointBlanki3Ipt);
	i3SceneDx = (DWORD)GetModuleHandleA(PointBlanki3Scn);
	i3BaseDx = (DWORD)GetModuleHandleA(PointBlanki3Bsd);
	}while(!dwStartAddress);
	DWORD dwSize = dwStartAddress + 0x6FFFFF;
	DWORD dwSizei3GfxDx = i3GfxDx + 0x1FFFFF;
	DWORD dwSizeI3InputDx_Hook = I3InputDx + 0x1FFFFF;
	DWORD dwSizei3SceneDx = i3SceneDx + 0x1FFFFF;*/
//	SearchPatterns();
	Thread_Aimbot();
	HookTelekill();

/*-------------------------------------------------------------------------------------------------------------------*/
	//ShellExecuteA(NULL, "Open", "http://www.zero-cyberz-server.com/category/point-blank/", NULL, NULL, SW_SHOWNORMAL);
	//CEK("http://zero-cyberz-server.com/Redirect/Protection/Trial.txt","ZRC","13042016");
//	CEK("http://zero-cyberz-vip.net/8495112d96cbcbcd72a42f5003642bc7/75c5ffc6a24877985c5ba2e1c2e0b577/Diskless/ayanda_251015.txt","ZRC","checkedclear");
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)WriteHooking, NULL, NULL, NULL );
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ReloadGM, NULL, NULL, NULL );
}

#include "Hwid.h"
#include "sha1.h"
#include "CekHwid.h"
 
/*------------------------------------------- Declaration Dll Attach ------------------------------------------------------*/
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
	if(dwReason == DLL_PROCESS_ATTACH){
		DisableThreadLibraryCalls(hModule);
//		HideModule(hModule);
//		EraseHeaders(hModule);
//		UnlinkModule("PB.dll");
//		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CheckLicense, NULL, NULL, NULL);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)BlogCheatGames_08062015, NULL, NULL, NULL);
		Beep(1000,100);
}
return TRUE;
}