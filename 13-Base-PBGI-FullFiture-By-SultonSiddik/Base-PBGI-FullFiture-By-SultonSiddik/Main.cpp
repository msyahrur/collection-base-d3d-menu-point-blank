/*Main.cpp D3D9 PBHacks Last Edit By Muhammad Zaki Mubarak*/
/*------------------------------------------- PB Hacks By Muhammad Zaki Mubarak ----------------------------------------------------*/
/*------------------------------------------ Created Muhammad Zaki Mubarak ©Copyright 2016 -------------------------------------------------*/
/*----------------------------------------- Thanks For Google -------------------------------------------------*/

#pragma comment (lib, "Iqhwan")

#include <windows.h>
#include <wininet.h>
#include <time.h>
#include "XStr.h"
#include "Stdafx.h"
#include "directInput.h"
#include "cMenu.h"
#include "Texture.h"
//#include "Internal.h"

#pragma warning(disable:4805)
#pragma warning(disable:4806)
/*-------------------------------------------------------------------------------------------------------------------*/
typedef HRESULT (WINAPI* tEndScene2)(LPDIRECT3DDEVICE9 pDevice);
tEndScene2 oEndScene2 = NULL;

typedef HRESULT (WINAPI* tDrawIndexedPrimitivee)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
tDrawIndexedPrimitivee oDrawIndexedPrimitivee = NULL;

typedef HRESULT (WINAPI* tReset2)(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
tReset2 oReset2 = NULL;

#define CallInFiture(Function) CreateThread(0,0,(LPTHREAD_START_ROUTINE)&Function,0,0,0);

/*------------------------------------------- Declaration DrawMenuD3D ------------------------------------------------------*/
bool ShowX2		= true;
void MenuHandler( LPDIRECT3DDEVICE9 pDevice )
{
	return;
}
void DrawTextR(int x,int y,DWORD color,char *text)
{
    RECT rect, rect1, rect2, rect3, rect4, rect5;
    SetRect( &rect, x, y, x, y );
	SetRect( &rect1, x-1, y, x-1, y );
    SetRect( &rect2, x, y, x, y );
	SetRect( &rect3, x, y+1, x, y+1 );
    SetRect( &rect4, x, y, x, y );
	SetRect( &rect5, x - 0.1, y + 0.2, x - 0.1, y + 0. );
	pFont2->DrawTextA(NULL,text,-1,&rect5, DT_LEFT|DT_NOCLIP, color );
    pFont2->DrawTextA(NULL,text,-1,&rect,  DT_LEFT|DT_WORDBREAK, BLACK );
	pFont2->DrawTextA(NULL,text,-1,&rect1, DT_LEFT|DT_WORDBREAK, BLACK );
	pFont2->DrawTextA(NULL,text,-1,&rect2, DT_LEFT|DT_WORDBREAK, BLACK );
	pFont2->DrawTextA(NULL,text,-1,&rect3, DT_LEFT|DT_WORDBREAK, BLACK );
	pFont2->DrawTextA(NULL,text,-1,&rect4, DT_LEFT|DT_WORDBREAK, BLACK );
}

void DrawTextL(int x,int y,DWORD color,char *text)
{
	RECT rect, rect1, rect2, rect3, rect4, rect5;
    SetRect( &rect, x, y, x, y );
	SetRect( &rect1, x-1, y, x-1, y );
    SetRect( &rect2, x, y, x, y );
	SetRect( &rect3, x, y+1, x, y+1 );
    SetRect( &rect4, x, y, x, y );
	SetRect( &rect5, x - 0.1, y + 0.2, x - 0.1, y + 0. );
	pFont2->DrawTextA(NULL,text,-1,&rect5, DT_RIGHT|DT_NOCLIP, color );
    pFont2->DrawTextA(NULL,text,-1,&rect,  DT_RIGHT|DT_WORDBREAK, BLACK );
	pFont2->DrawTextA(NULL,text,-1,&rect1, DT_RIGHT|DT_WORDBREAK, BLACK );
	pFont2->DrawTextA(NULL,text,-1,&rect2, DT_RIGHT|DT_WORDBREAK, BLACK );
	pFont2->DrawTextA(NULL,text,-1,&rect3, DT_RIGHT|DT_WORDBREAK, BLACK );
	pFont2->DrawTextA(NULL,text,-1,&rect4, DT_RIGHT|DT_WORDBREAK, BLACK );
}


LPD3DXFONT g_pFont2 = NULL; //D3D Font
void MenuNav(void)
{
	if (IsKeyPressed2(VK_INSERT, 0)&1)
	{
		Mvisible=(!Mvisible);
	}
	if (!Mvisible) return;
	if (IsKeyPressed2(VK_UP, 0)&1) {
		do {
			Mpos--;
			if (Mpos<0)  Mpos=Mmax-1;
		} 
		while (D3MENU[Mpos].typ==MENUTEXT);	
	}else if (IsKeyPressed2(VK_DOWN, 0)&1) {
		do {
			Mpos++;
			if (Mpos==Mmax) Mpos=0;
		} while (D3MENU[Mpos].typ==MENUTEXT);		
	} else if (D3MENU[Mpos].var) {
		int dir=0;
		if ( ( IsKeyPressed2(VK_LEFT, 0)&1) && *D3MENU[Mpos].var > 0 ) dir=-1;
		if ( ( IsKeyPressed2(VK_RIGHT, 0)&1) && *D3MENU[Mpos].var < (D3MENU[Mpos].maxvalue-1)) dir=1;
		if (dir) {
			*D3MENU[Mpos].var += dir;
			if (D3MENU[Mpos].typ==MENUFOLDER) Mmax=0;
			if (D3MENU[Mpos].typ==MENUCAT) Mmax=0;  
		}
	}
}

void MenuShow(float x, float y, LPDIRECT3DDEVICE9 pDevice)
{
	int i, val;
	DWORD color;
	DWORD texty;
	char text[100];
	if (!Mvisible) return;
	//DrawMenu12(x-5, y-5, 200/*<wigth*/, 23/*<heigt*/, 3,Hijau, Hijau, pDevice);
if (Mtitle2[0]) 
	{
		//DrawMenu12(x-5, y-5, 200/*<wigth*/, 23/*<heigt*/, 3,Hijau, Hijau, pDevice);// Warna dan lebar tinggi line
		pFont2->DrawText(NULL,Mtitle2,-1,&rect22,DT_NOCLIP | DT_CENTER, GREEN);
		y+=Mysize;
	}
	for (i=0; i<Mmax; i++) 
	{
		//DrawMenu12(x-5, y-5, 200/*<wigth*/, 25/*<heigt*/, 3,ABUABU /*Warna BG*/, Hijau, pDevice);
		val=(D3MENU[i].var)?(*D3MENU[i].var):0;
		sprintf(text, "%s", D3MENU[i].txt);
		if (i==Mpos){
			color=RED;
			texty=RED;

			sprintf(text, "~> %s", D3MENU[i].txt);
		}
		else if (D3MENU[i].typ==MENUFOLDER){
			color=YELLOW;
			texty=YELLOW;
		}
		else if (D3MENU[i].typ==MENUTEXT){
			color=GREEN;
			texty=GREEN;
		}
		else{
			color=(val)?GREEN:WHITE;
			texty=(val)?COLORCURENT:COLORCURENT;
		}
		if (D3MENU[i].opt)
		{
			if (D3MENU[i].typ==MENUITEM){
				DrawTextL(x+3, y, texty,text);
				y = y + 2;
			}else{
				DrawTextL(x+3, y, texty,text);
			}
		}
		if (D3MENU[i].opt) {
			if (D3MENU[i].typ==MENUTEXT)
				DrawTextR((x+Mxofs), y, color,(char *)D3MENU[i].opt);
			else
				DrawTextR((x+Mxofs), y, color,(char *)D3MENU[i].opt[val]);
		}
		y+=Mysize;
	}
}
void DrawMenuD3D(LPDIRECT3DDEVICE9 pDevice)
{
	static bool DrawDXFont = false;
	if(!DrawDXFont)
	{
		D3DXCreateFontA(pDevice, 14, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Consolas", &pFont2);
		DrawDXFont = true;
	}

	if (Drawing == 0)
	{
		if(Mmax==0) 
			RebuildMenu(pDevice);
			MenuShow(mx,my,pDevice);
//			MenuHandler(pDevice);
			MenuNav();
	}

	if(Font())FontCreate(pDevice);

	if(!g_pFont2)	D3DXCreateFontA(pDevice, 15, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &g_pFont2);
}


LPDIRECT3DTEXTURE9 Redd;
LPDIRECT3DTEXTURE9 Bluee;
bool stateReset2[2] = {0};
/*------------------------------------------- Declaration GenerateTexture ------------------------------------------------------*/
LPDIRECT3DTEXTURE9 RainbowTextTestX;
LPDIRECT3DTEXTURE9 WhiteX,RedX,GreenX;
HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
    if(FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
        return E_FAIL;
    
    WORD colour16 = ((WORD)((colour32>>28)&0xF)<<12)
	            	|(WORD)(((colour32>>20)&0xF)<<8)
	             	|(WORD)(((colour32>>12)&0xF)<<4)
                 	|(WORD)(((colour32>>4)&0xF)<<0);

    D3DLOCKED_RECT d3dlr;    
    (*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
    WORD *pDst16 = (WORD*)d3dlr.pBits;

    for(int xy=0; xy < 8*8; xy++)
        *pDst16++ = colour16;

    (*ppD3Dtex)->UnlockRect(0);

    return S_OK;
}
LPD3DXFONT g_pFont23 = NULL;
/*------------------------------------------- Declaration DrawReset ------------------------------------------------------*/
void ThreadReset()
{
	static DWORD TickReset = 0;
	while(true)
	{
		if(npDevice2){

			if(npDevice2->TestCooperativeLevel() == D3DERR_DEVICELOST){
				stateReset2[0] = true;
				stateReset2[1] = true;
				TickReset = GetTickCount() + 4000;
			}
			else {
				stateReset2[0] = false;
				stateReset2[1] = false;
			}
			while(TickReset >= GetTickCount()){
				if(stateReset2[0] == true)
				{
					
					if(g_pFont23){
						g_pFont23->OnLostDevice();
						g_pFont23->OnResetDevice();
					}
					if(g_pLine2)
					{
						g_pLine2->OnLostDevice();
						g_pLine2->OnResetDevice();
					}
					if(pLine){
						pLine->OnLostDevice();
						pLine->OnResetDevice();
					}
					if(pFont2){
						pFont2->OnLostDevice();
						pFont2->OnResetDevice();
					}
				}
				if(stateReset2[1] == true)
				{
					if(Redd)	{
						Redd->Release();
						Redd = NULL;
					}
					if(Bluee) {
						Bluee->Release();
						Bluee = NULL;
					}
				}
				
			}
		}
		Sleep(0);
	}
}




LPDIRECT3DTEXTURE9 Rede;
DWORD WINAPI DoESP(LPDIRECT3DDEVICE9 pDevice);
DWORD WINAPI DoAimAssist(LPDIRECT3DDEVICE9 pDevice);
DWORD WINAPI DoHack();
DWORD WINAPI DoRoomHack();
DWORD WINAPI Replace_Real();
DWORD WINAPI BypassAbuse();
DWORD WINAPI HookBurst();
DWORD WINAPI SetEventHack();
DWORD WINAPI ChatEventHack();
DWORD WINAPI UpdateGameClass();
DWORD WINAPI UpdateLocalClass();
DWORD WINAPI DirectInputLoop();
HRESULT WINAPI hkEndScene(LPDIRECT3DDEVICE9 pDevice){

	while(!npDevice2)
	{
		npDevice2 = pDevice;	
		CreateThread(0,0,(LPTHREAD_START_ROUTINE)ThreadReset,0,0,0);
	}

	static bool bInitEs = false;
	while(!bInitEs)
	{
		SetEventHack();
		ChatEventHack();
		//HookResetDevice();
		bInitEs = true;
	}

	UpdateGameClass();
	UpdateLocalClass();

	pDevice->GetViewport(&g_ViewPort2);

	if(!g_pLine2)D3DXCreateLine(pDevice,&g_pLine2);

	if(Rede == NULL)D3DXCreateTextureFromFileInMemory(pDevice, &_texRed2, sizeof(_texRed2), &Rede);
	if(Bluee == NULL)D3DXCreateTextureFromFileInMemory(pDevice, &_texBlue2, sizeof(_texBlue2), &Bluee);

	ScreenCenterX2 = g_ViewPort2.Width / 2;
	ScreenCenterY2 = g_ViewPort2.Height / 2;

	DirectInputLoop();
	float ScreenCenterX = (g_ViewPort2.Width /2.0f);
	float ScreenButtomY = (g_ViewPort2.Height);
	DrawMenuD3D(pDevice);

	DoESP(pDevice);
	DoAimAssist(pDevice);
	DoHack();
	DoRoomHack();
	Replace_Real();
	BypassAbuse();
	HookBurst();

	if(IsKeyPressed2(VK_F12, 0)&1)
	{
		ExitProcess(0);
	}



	
		/*if( (CrossHair) )Crosshair(pDevice, g_ViewPort, RED);*/
		if((CrossHair))
		{
			D3DVIEWPORT9 viewP;
			pDevice->GetViewport( &viewP );
			DWORD ScreenCenterX = viewP.Width / 2; 
			DWORD ScreenCenterY = viewP.Height / 2; 

			D3DRECT rec1 = {ScreenCenterX-35, ScreenCenterY, ScreenCenterX+ 35, ScreenCenterY+1};
			D3DRECT rec2 =	{ScreenCenterX, ScreenCenterY-35, ScreenCenterX+ 1,ScreenCenterY+35};  

			if((CrossHair) == 1)
			{	
				D3DRECT rec10 = {ScreenCenterX-6, ScreenCenterY, ScreenCenterX+ 6, ScreenCenterY+1};
				D3DRECT rec11 = {ScreenCenterX, ScreenCenterY-6, ScreenCenterX+ 1,ScreenCenterY+6};  
				pDevice->Clear( 1, &rec10, D3DCLEAR_TARGET, D3DXCOLOR(0.0, 1.0, 0.0, 1.0), 0,  0 );// green
				pDevice->Clear( 1, &rec11, D3DCLEAR_TARGET, D3DXCOLOR(0.0, 1.0, 0.0, 1.0), 0,  0 );

				D3DRECT rec12 = {ScreenCenterX-4, ScreenCenterY, ScreenCenterX+ 4, ScreenCenterY+1};
				D3DRECT rec13 = {ScreenCenterX, ScreenCenterY-4, ScreenCenterX+ 1,ScreenCenterY+4};  
				pDevice->Clear( 1, &rec12, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 1.0, 0.0, 1.0), 0,  0 );// yellow
				pDevice->Clear( 1, &rec13, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 1.0, 0.0, 1.0), 0,  0 );

				D3DRECT rec16 = {ScreenCenterX-1, ScreenCenterY, ScreenCenterX+ 1, ScreenCenterY+1};
				D3DRECT rec17 = {ScreenCenterX, ScreenCenterY-1, ScreenCenterX+ 1,ScreenCenterY+1};  
				pDevice->Clear( 1, &rec16, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), 0,  0 );//red
				pDevice->Clear( 1, &rec17, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), 0,  0 );
			}
			if((CrossHair) == 2)
			{	
				D3DRECT rec16 = {ScreenCenterX-2, ScreenCenterY-2, ScreenCenterX+ 2, ScreenCenterY+2};
				D3DRECT rec17 = {ScreenCenterX-2, ScreenCenterY-2, ScreenCenterX+ 2,ScreenCenterY+2};  
				pDevice->Clear( 1, &rec16, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), 0,  0 );//red
				pDevice->Clear( 1, &rec17, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), 0,  0 );
			}
		
	}
	/*return pDevice->EndScene();*/
	return oEndScene2(pDevice);
}
/*------------------------------------------- Declaration DrawEndScene ------------------------------------------------------*/

/*------------------------------------------- Declaration DrawIndexPrim ------------------------------------------------------*/
//HRESULT WINAPI hkDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
//{
//	if(stateReset2[1] == true)
//		goto skipDIP;
//
//		if(WHClean || Chams){
//			if(allp2){  
//				//pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
//				if(Chams){
//					if(Chams == 1){ //Light Chams
//						pDevice->SetRenderState(D3DRS_ZENABLE,false);
//						if(PlayerTerorist||TeroHead||C5||K400)pDevice->SetTexture(0,Redd);
//						if(PlayerCT||CTHead)pDevice->SetTexture(0,Bluee);
//						oDrawIndexedPrimitivee(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
//						pDevice->SetRenderState(D3DRS_ZENABLE,true);
//
//					}
//					if(Chams == 2){ //Ghost Chams
//						pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
//						pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVDESTCOLOR);
//						pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_INVSRCCOLOR);
//						pDevice->SetRenderState(D3DRS_ZENABLE,false);	
//						oDrawIndexedPrimitivee(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
//						pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
//						pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVDESTCOLOR);
//						pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_INVSRCCOLOR);
//						pDevice->SetRenderState(D3DRS_ZENABLE,true);
//					}
//					if(Chams == 3){ //Phantom Chams
//						pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
//						pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVDESTCOLOR);
//						pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_INVSRCALPHA);
//						pDevice->SetRenderState(D3DRS_ZENABLE,false);
//						oDrawIndexedPrimitivee(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
//						pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
//						pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVDESTCOLOR);
//						pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_INVSRCALPHA);
//						pDevice->SetRenderState(D3DRS_ZENABLE,false);
//					}
//				}
//				else
//				{
//					pDevice->SetRenderState(D3DRS_ZENABLE, false);
//					oDrawIndexedPrimitivee(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
//					pDevice->SetRenderState(D3DRS_ZENABLE, true);
//				
//			}
//		}
//
//		if(DontSmoke)
//			if((NumVertices == 192) || (NumVertices == 256))return D3D_OK;
//
//		if(DontSmoke)pDevice->SetRenderState(D3DRS_FOGENABLE, false);
//
//	}
//skipDIP:
//	oDrawIndexedPrimitivee = (tDrawIndexedPrimitivee)GetOriginalDIP();
//	return oDrawIndexedPrimitivee(pDevice,PrimType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount);
//}

/*------------------------------------------- Declaration AsmHookEngine ------------------------------------------------------*/


DWORD m_pCaps2, SelectShader2 = 0;
//_declspec(naked)void hkDrawIndexedPrim()
//{
//	_asm
//	{
//		push ebx
//        push esi
//        push edi
//        mov edi,dword ptr ss:[esp+0x1c]
//        mov esi,ecx
//        add dword ptr ds:[esi+0xF8],edi
//        mov ebx,0x1
//        add dword ptr ds:[esi+0x14],ebx
//        mov eax,dword ptr ds:[m_pCaps2]
//		mov eax,[eax];
//        cmp dword ptr ds:[eax+0x150],0x0
//        je i3GfxDx_100CC413 //Pertama
//        mov ecx,dword ptr ss:[esp+0x10]
//        push 0x0
//        push ecx
//        mov ecx,esi
//        call [SelectShader2] ;<= Jump/Call Address Not Resolved
//
//i3GfxDx_100CC413: //Pertama
//
//        cmp byte ptr ds:[esi+0x160],0x0
//        je i3GfxDx_100CC562 //Kedua
//        cmp dword ptr ds:[esi+0x5468],ebx
//        jnz i3GfxDx_100CC562 //Kedua
//
//        mov eax,dword ptr ds:[esi+0x5458]
//        mov ebx,dword ptr ds:[esi+0x5464]
//        mov edx,dword ptr ds:[eax+0x1e0]
//        push ebp
//        mov ebp,dword ptr ds:[eax+0x188]
//        xor edi,edi
//        imul ebx,ebp
//        cmp dword ptr ds:[esi+0x5450],edi
//        mov dword ptr ss:[esp+0x14],edx
//        jle i3GfxDx_100CC4D5 //Ketiga
//
//i3GfxDx_100CC500: //Keempat
//
//        mov edx,dword ptr ss:[esp+0x14]
//        mov eax,dword ptr ds:[esi+0x53A8]
//        mov ecx,dword ptr ds:[eax]
//        push 0x0
//        push ebx
//        push edx
//        push 0x1
//        push eax
//        mov eax,dword ptr ds:[ecx+0x190]
//        call eax
//        mov edx,dword ptr ss:[esp+0x20]
//        mov eax,dword ptr ds:[esi+0x53A8]
//        mov ecx,dword ptr ds:[eax]
//        push edx
//        mov edx,dword ptr ss:[esp+0x20]
//        push edx
//        mov edx,dword ptr ds:[esi+0x924]
//        mov edx,dword ptr ds:[edx+0x170]
//        push edx
//        mov edx,dword ptr ss:[esp+0x24]
//        push 0x0
//        push 0x0
//        push edx
//        push eax
//        mov eax,dword ptr ds:[ecx+0x148]
//		//===============================================
//		mov [pDrawIndexedPrimitive],eax
//		//===============================================
//        call hkDrawIndexedPrimitive
//        inc edi
//        add ebx,ebp
//        cmp edi,dword ptr ds:[esi+0x5450]
//        jl i3GfxDx_100CC500 //Keempat
//
//i3GfxDx_100CC4D5: //Ketiga
//
//        mov eax,dword ptr ds:[esi+0xAE4]
//        pop ebp
//        pop edi
//        pop esi
//        pop ebx
//        retn 0x10
//
//i3GfxDx_100CC562: //Kedua
//
//        mov edx,dword ptr ss:[esp+0x18]
//        mov eax,dword ptr ds:[esi+0x53A8]
//        mov ecx,dword ptr ds:[eax]
//        push edi
//        push edx
//        mov edx,dword ptr ds:[esi+0x924]
//        mov edx,dword ptr ds:[edx+0x170]
//        push edx
//        mov edx,dword ptr ss:[esp+0x20]
//        push 0x0
//        push 0x0
//        push edx
//        push eax
//        mov eax,dword ptr ds:[ecx+0x148]
//		//===============================================
//		mov [pDrawIndexedPrimitive],eax
//		//===============================================
//        call hkDrawIndexedPrimitive
//        mov eax,dword ptr ds:[esi+0xAE4]
//        pop edi
//        pop esi
//        pop ebx
//        retn 0x10
//	}
//}




/*------------------------------------------- Declaration HookEngine ------------------------------------------------------*/


/*--------------------------------------- Declaration Caller AllThread --------------------------------------------------*/
bool Exit;



IDirect3D9 * HookDirect3DCreate92(VOID)
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

IDirect3D9 *pD3D2;
void __fastcall ThreadHookX()
{
	while(!pD3D2){
		pD3D2 = HookDirect3DCreate92();
	}
	DWORD *VD3D				= (DWORD*)pD3D2;
	VD3D					= (DWORD*)VD3D[0];
	oEndScene2				= (tEndScene2)				DetourFunction2((PBYTE)VD3D[42], (PBYTE)hkEndScene				,5);
//	oReset2					= (tReset2)					DetourFunction((PBYTE)VD3D[16], (PBYTE)hkReset					,5);
	Sleep(10);
}
DWORD WINAPI HackCyberMaker();


 


/*------------------------------------------- Declaration Attach Dll ------------------------------------------------------*/
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
	char strDLLName [_MAX_PATH];
	GetModuleFileName(hModule, strDLLName , _MAX_PATH);
	if(dwReason == DLL_PROCESS_ATTACH){
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)HackCyberMaker,NULL,NULL,NULL);  //HkEndSceneFiture
		//MessageBoxA(0," New Sytem " , " Notice " , MB_ICONWARNING | MB_YESNO);
		CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ThreadHookX,NULL,NULL,NULL);
		//ZonaXCyber(HaIhaaa);	
		//ZonaXCyber(TrialStarter);
		//ZonaXCyber(CallerThread);
		Beep(1000, 100);
		 /*------------------------------- Declaration SEARCH OFFSET -------------------------------*/
//		GetModuleFileName(hModule, dlldir, 512);
//		for(int i = strlen(dlldir); i > 0; i--) { if(dlldir[i] == '\\') { dlldir[i+1] = 0; break;}}
		//infile.open(GetDirectoryFile("SearchOFS.txt"), ios::out);
		//Beep(1000, 100);
	}
	return TRUE;
}

/*---------------------------------------------------------------- Declaration Attach Dll ----------------------------------------------------------------*/
//BOOL WINAPI DllMain ( HMODULE hAdd, DWORD dwReason, LPVOID lpReserved )
//{
//	//DisableThreadLibraryCalls(hAdd);
//	if (dwReason==DLL_PROCESS_ATTACH)
//	{
//		//dltProtectTrial();
//		Beep(1000,100);
//		MessageBox (0,"Logger Not For Share & Sale","Created By Muhammad Zaki Mubarak", MB_OK | MB_ICONINFORMATION);
//		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SearchPatterns, NULL, NULL, NULL);
//
//        /*------------------------------- Declaration SEARCH OFFSET -------------------------------*/
//		GetModuleFileName(hAdd, dlldir, 512);
//		for(int i = strlen(dlldir); i > 0; i--) { if(dlldir[i] == '\\') { dlldir[i+1] = 0; break;}}
//		infile.open(GetDirectoryFile("SearchOFS.txt"), ios::out);
//	}
//	return TRUE;
//}

/*-------------------------------------------------------------------------------------------------------------------*/
//CAllNotice//

