/*------------------------------------------------ Source Code [MRC]--------------------------------------------------------------*/
/*--------------------------------------------------- [MRC] ---------------------------------------------------------------*/
/*-----------------------------------------  Thanks For Allah & My Computer -------------------------------------------------*/
#include <windows.h>
#include <wininet.h>
#include <time.h>
#include "[MRC]CStdAfx.h"
#include "[MRC]CMenu.h"
#include "[MRC]CAimESP.h"
//----------------------------------------------------------------------------------------
typedef HRESULT (WINAPI* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene = NULL;
//----------------------------------------------------------------------------------------
typedef HRESULT (WINAPI* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
tDrawIndexedPrimitive oDrawIndexedPrimitive = NULL;
//----------------------------------------------------------------------------------------
typedef HRESULT(WINAPI* tReset)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
tReset oReset = NULL;
//----------------------------------------------------------------------------------------
void DrawMenuD3D(LPDIRECT3DDEVICE9 pDevice)
{
	if (DrawFont == 1) 
	{
		D3DXCreateFontA(pDevice, 12, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &pFont);
		DrawFont = 0;
	}

	if (Drawing == 0)
	{
		if(Mmax==0) 
		RebuildMenu(pDevice);
		MenuShow(mx,my,pDevice);
		MenuNav();
	}

	if(!g_pFont)	D3DXCreateFontA(pDevice, 10, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Hud_Small_Font", &g_pFont);//15
	if(!pLine)		D3DXCreateLine( pDevice, &pLine );
}
//----------------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 RainbowTextTestX;
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
//----------------------------------------------------------------------------------------
HRESULT WINAPI hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	while(!npDevice) {
		npDevice = pDevice;                      
	}
//----------------------------------------------------------------------------------------
	float ScreenCenterX = (Viewport.Width /2.0f);
	float ScreenCenterY = (Viewport.Height /2.0f);
	float ScreenBottomY = (Viewport.Height);
//----------------------------------------------------------------------------------------
	pDevice->GetViewport(&g_ViewPort);
	DrawMenuD3D(pDevice);
//----------------------------------------------------------------------------------------
	if(RainbowTexts!=100)
	{RainbowR-=2,RainbowG-=3,RainbowB-=3;}
	if(RainbowTexts!=255)
	{RainbowR+=2,RainbowG+=3,RainbowB+=4;}
	GenerateTexture(pDevice, &RainbowTextTestX,  RainbowTextTest);
//----------------------------------------------------------------------------------------
	if(*(PBYTE)ResultBaseAmmo2 > NULL){
		Accuracy_Hack(pDevice);
		NormalHacks();
	}
//----------------------------------------------------------------------------------------
	if(!GetBattleState()){
	Accuracy=0;
	}
//----------------------------------------------------------------------------------------
if(IsKeyPressed(VK_END, 0)&1){ExitProcess(0);}
if(GetBattleState()){if(IsKeyPressed(VK_NUMPAD1, 0)&1){Planted=!Planted;Cmd_Planted_On();}}
if(GetBattleState()){if(IsKeyPressed(VK_NUMPAD2, 0)&1){DefuseX=!DefuseX;Cmd_Defiuse_On();}}
//-------------------------------------------------------------------------------
if(Cross)
{
	D3DVIEWPORT9 viewP;
	pDevice->GetViewport( &viewP );
	DWORD ScreenCenterX = viewP.Width / 2; 
	DWORD ScreenCenterY = viewP.Height / 2; 

	D3DRECT rec1 = {ScreenCenterX-35, ScreenCenterY, ScreenCenterX+ 35, ScreenCenterY+1};
	D3DRECT rec2 =	{ScreenCenterX, ScreenCenterY-35, ScreenCenterX+ 1,ScreenCenterY+35};  
	if(Cross==1)
	{	
		D3DRECT rec16 = {ScreenCenterX-2, ScreenCenterY-2, ScreenCenterX+ 2, ScreenCenterY+2};
		D3DRECT rec17 = {ScreenCenterX-2, ScreenCenterY-2, ScreenCenterX+ 2,ScreenCenterY+2};  
		pDevice->Clear( 1, &rec16, D3DCLEAR_TARGET, RainbowTextTest, 0,  0 );
		pDevice->Clear( 1, &rec17, D3DCLEAR_TARGET, RainbowTextTest, 0,  0 );
	}
}
//----------------------------------------------------------------------------------------
return oEndScene(pDevice);
}
//----------------------------------------------------------------------------------------
HRESULT WINAPI hkDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{
if(pDevice->GetStreamSource(0, &Stream_Data, &Offset, &Stride) == D3D_OK){
Stream_Data->Release();
}
//----------------------------------------------------------------------------------------
if(GetBattleState()){
if(WHClean==1)
{   
	if(allp)   
	{            
		pDevice->SetRenderState(D3DRS_ZENABLE, false);
		pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		pDevice->SetRenderState(D3DRS_LIGHTING, D3DLIGHT_DIRECTIONAL);
		oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
		pDevice->SetRenderState(D3DRS_ZENABLE, true);
		pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		pDevice->SetRenderState(D3DRS_LIGHTING, D3DLIGHT_DIRECTIONAL);
	}
}}
//----------------------------------------------------------------------------------------
if(GetBattleState()){
if(WHGlass==1)
{   
	if(allp)   
	{            
		pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
	}
}}
//----------------------------------------------------------------------------------------
if(GetBattleState()){
if(DontFog==1)
{
	if ((NumVertices == 192) || (NumVertices == 256))	  
	{
		return D3D_OK;
		return 0;
	}
}}
//----------------------------------------------------------------------------------------
if(Planted==1){Cmd_Planted_On();}//CT Middle C4
if(DefuseX==1){Cmd_Defiuse_On();}
//----------------------------------------------------------------------------------------
if(GetBattleState()){
if(DontSmoke==1)                                                   
{
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);
}}

	return oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}
//----------------------------------------------------------------------------------------
HRESULT WINAPI hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
 if( g_pFont )
        g_pFont->OnLostDevice();

	if( pFont )
		pFont->OnLostDevice();

    if( pLine )
        pLine->OnLostDevice();

    if(oReset == D3D_OK) 
	{
		if( g_pFont )
            g_pFont->OnResetDevice();
		
		if( pFont )
			pFont->OnResetDevice();

        if( pLine )
            pLine->OnResetDevice();
	}

    return oReset(pDevice, pPresentationParameters);
}
//----------------------------------------------------------------------------------------
DWORD EndRenderBCKx;
__declspec (naked) void HooKMeUp(void)
{
	__asm 
	{ 
		mov eax,[ecx+0x04]
		cmp eax,[ecx+0x08]
		je Exit
		mov [ecx+0x08],eax
			jmp EndRenderBCKx
Exit:
		mov [oEndScene],eax
		mov eax,[hkEndScene]
		ret
			jmp EndRenderBCKx

	} 
}
//----------------------------------------------------------------------------------------
__declspec(naked)void HookES()
{
	_asm
	{
		push eax
			pop eax
			jmp hkEndScene
	}
}
//----------------------------------------------------------------------------------------
__declspec(naked)void HookDIP()
{
	_asm
	{
		push eax
			pop eax
			jmp hkDrawIndexedPrimitive
	}
}
//----------------------------------------------------------------------------------------
__declspec(naked)void HookRES()
{
	_asm
	{
		push eax
			pop eax
			jmp hkReset
	}
}
//----------------------------------------------------------------------------------------
DWORD WINAPI HookEngine()
{
	if (ModuleGFX > 0)
	{
		DWORD tmp1 = (DWORD)GetModuleHandle("i3GfxDx.dll") + ADR_g_pRenderContext;
		DWORD tmp2 = 0;
		Sleep(1);
		while(!pGDevice){
			if(IsBadReadPtr((PDWORD)tmp1,4)==NULL)
			tmp2 = *(PDWORD)((DWORD)(tmp1))+PTR_EndRender;
			if(IsBadReadPtr((PDWORD)tmp2,4)==NULL){
				DWORD OldProtect;
				VirtualAlloc((void*)tmp2, 4, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
				VirtualProtectEx(GetCurrentProcess(),(void*)tmp2, 4, PAGE_READWRITE, &OldProtect);
				memcpy(&pGDevice, (void *)tmp2, 4);
				VirtualProtectEx(GetCurrentProcess(),(void*)tmp2, 4, OldProtect, &OldProtect );
			}
		}
		DWORD *g_pDevice = (DWORD*)pGDevice;
		g_pDevice = (DWORD*)g_pDevice[0];
		while(!npDevice)npDevice = (LPDIRECT3DDEVICE9)(DWORD*)g_pDevice;
		*(PDWORD)&oEndScene	= g_pDevice[42];
		*(PDWORD)&oDrawIndexedPrimitive	= g_pDevice[82];
		*(PDWORD)&oReset	= g_pDevice[16];
		Hooked((PDWORD)(g_pDevice[1] - 5), (PDWORD)(g_pDevice[4] - 5));
		Hooked((PDWORD)(g_pDevice[2] - 5), (PDWORD)(g_pDevice[5] - 5));
		Hooked((PDWORD)(g_pDevice[3] - 5), (PDWORD)(g_pDevice[6] - 5));
		Hooked((PDWORD)(g_pDevice[4] - 5), (PDWORD)HookES);
		Hooked((PDWORD)(g_pDevice[5] - 5), (PDWORD)HookDIP);
		Hooked((PDWORD)(g_pDevice[6] - 5), (PDWORD)HookRES);
		while(1){
			g_pDevice[42] = (DWORD)g_pDevice[1] - 5;
			g_pDevice[82] = (DWORD)g_pDevice[2] - 5;
			g_pDevice[16] = (DWORD)g_pDevice[3] - 5;
			Sleep(100); 
		} 
	}
	return 0; 
}
//----------------------------------------------------------------------------------------
void SystemPortal()
{
	HookAim();
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HookEngine,NULL,NULL,NULL);
}
 
//----------------------------------------------------------------------------------------
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
	if(dwReason == DLL_PROCESS_ATTACH){
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SystemPortal,NULL,NULL,NULL);
		//Beep(1000, 100);
}
return TRUE;
}
//----------------------------------------------------------------------------------------
//---------------------------------------------------------// [MRC]
//----------------------------------------------------------------------------------------