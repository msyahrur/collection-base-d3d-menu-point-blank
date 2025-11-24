//--------------------------------------------------------------------------//
#include "Xstr.h"
#include "GameHack.h"
#include "xKeyboard.h"
#include "MenuMouse.h"
#include "Aim+Esp.h"
#include "Texture.h"
//--------------------------------------------------------------------------//
typedef HRESULT (WINAPI* tEndScene)(LPDIRECT3DDEVICE9 );
tEndScene oEndScene = 0;
typedef HRESULT (WINAPI* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 , D3DPRIMITIVETYPE ,INT ,UINT ,UINT ,UINT ,UINT );
tDrawIndexedPrimitive oDrawIndexedPrimitive = 0;
#define XMenuMouse(Function) CreateThread(0,0,(LPTHREAD_START_ROUTINE)Function,0,0,0);
//--------------------------------------------------------------------------//
void InstallPresent(LPDIRECT3DDEVICE9 pDevice){
if(IsKeyPressed(VK_INSERT,0)) ShowX = !ShowX;
if (ShowX == true){
if (FontCreate == true){
D3DXCreateFontA(pDevice, 15, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &NHT3XT);
D3DXCreateLine(pDevice, &NHLine);
FontCreate = false;
}
if (MenuX_Minisize == 1){
pMenu.BoardersMinimize(pDevice);
pMenu.SelectionButtonMinimize(MenuX_MouseShow,457,19,pDevice);
MenuX_MouseShow	= (int)pMenu.SelectionMinimizeReturn(457,19,MenuX_MouseShow);
}
if (MenuX_MouseShow == 1){
if(Menu && NHT3XT){
MenuX_Minisize	= 1;
MenuX_sShow		= 0;
pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
RenderMenu_M(pDevice);
}}
if(MenuX_sShow == 1){
if(Menu && NHT3XT){
MenuX_Minisize	= 0;
MenuX_MouseShow = 0;
pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
RenderMenu_S(pDevice);
}}}
return;
}
//--------------------------------------------------------------------------//
HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32){
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
//--------------------------------------------------------------------------//
HRESULT WINAPI pGEndScene(LPDIRECT3DDEVICE9 pDevice){
InstallPresent(pDevice);
if(*(PBYTE)ResultBaseAmmo2 > NULL){
}
//--------------------------------------------------------------------------//
if(Nh_Teknology34){
D3DVIEWPORT9 viewP;
pDevice->GetViewport( &viewP );
DWORD ScreenCenterX = viewP.Width / 2; 
DWORD ScreenCenterY = viewP.Height / 2; 
D3DRECT rec1 = {ScreenCenterX-35, ScreenCenterY, ScreenCenterX+ 35, ScreenCenterY+1};
D3DRECT rec2 =	{ScreenCenterX, ScreenCenterY-35, ScreenCenterX+ 1,ScreenCenterY+35};  
if(Nh_Teknology34==1){	
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
if(Nh_Teknology34==2){	
D3DRECT rec16 = {ScreenCenterX-2, ScreenCenterY-2, ScreenCenterX+ 2, ScreenCenterY+2};
D3DRECT rec17 = {ScreenCenterX-2, ScreenCenterY-2, ScreenCenterX+ 2,ScreenCenterY+2};  
pDevice->Clear( 1, &rec16, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), 0,  0 );//red
pDevice->Clear( 1, &rec17, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), 0,  0 );
}}
//--------------------------------------------------------------------------//
if(GetAsyncKeyState(VK_F12)){GameFastExit = !GameFastExit;Beep(2000,200);}
if (GameFastExit) { ExitProcess(0);}
return oEndScene(pDevice);
}
//--------------------------------------------------------------------------//
HRESULT WINAPI pGDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount){
if(pDevice->GetStreamSource(0, &iStreamData, &iOffset, &iStride) == D3D_OK)
iStreamData->Release();
if(Color){
GenerateTexture(pDevice, &WhiteX,  White);
GenerateTexture(pDevice, &RedX,    Red);
GenerateTexture(pDevice, &GreenX,  Green);
GenerateTexture(pDevice, &BlueX,   Blue);
GenerateTexture(pDevice, &BlackX,  Black);
GenerateTexture(pDevice, &PurpleX, Purple);
GenerateTexture(pDevice, &GreyX,   Grey);
GenerateTexture(pDevice, &YellowX, Yellow);
GenerateTexture(pDevice, &OrangeX, Orange);
Color = false;
}
//--------------------------------------------------------------------------//
if(Nh_Teknology30){	
if(playersterror){
pDevice->SetRenderState(D3DRS_ZENABLE, 0);
oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE, 1);
if(Nh_Teknology30==1) pDevice->SetTexture(0, WhiteX);
if(Nh_Teknology30==2) pDevice->SetTexture(0, RedX);
if(Nh_Teknology30==3) pDevice->SetTexture(0, GreenX);
if(Nh_Teknology30==4) pDevice->SetTexture(0, BlueX);
if(Nh_Teknology30==5) pDevice->SetTexture(0, BlackX);
if(Nh_Teknology30==6) pDevice->SetTexture(0, PurpleX);
if(Nh_Teknology30==7) pDevice->SetTexture(0, GreyX);
if(Nh_Teknology30==8) pDevice->SetTexture(0, YellowX);		
if(Nh_Teknology30==9) pDevice->SetTexture(0, OrangeX);
}
if (allp){	
CallpDevice = 0;
pDevice->SetRenderState(D3DRS_ZENABLE,CallpDevice);
}}
//--------------------------------------------------------------------------//
if(Nh_Teknology31){
if(playersswat){
pDevice->SetRenderState(D3DRS_ZENABLE, 0);
oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE, 1);
if(Nh_Teknology31==1) pDevice->SetTexture(0, WhiteX);
if(Nh_Teknology31==2) pDevice->SetTexture(0, RedX);
if(Nh_Teknology31==3) pDevice->SetTexture(0, GreenX);
if(Nh_Teknology31==4) pDevice->SetTexture(0, BlueX);
if(Nh_Teknology31==5) pDevice->SetTexture(0, BlackX);
if(Nh_Teknology31==6) pDevice->SetTexture(0, PurpleX);
if(Nh_Teknology31==7) pDevice->SetTexture(0, GreyX);
if(Nh_Teknology31==8) pDevice->SetTexture(0, YellowX);		
if(Nh_Teknology31==9) pDevice->SetTexture(0, OrangeX);
}
if (allp){	
CallpDevice = 0;
pDevice->SetRenderState(D3DRS_ZENABLE,CallpDevice);
}}
//--------------------------------------------------------------------------//
if(Nh_Teknology32){
if(playersterror){
pDevice->SetRenderState(D3DRS_ZENABLE, 0);
oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE, 1);
}
if(playersswat){
pDevice->SetRenderState(D3DRS_ZENABLE, 0);
oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE, 1);
}
if (allp){	
pDevice->SetRenderState(D3DRS_ZENABLE, 0);
oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
pDevice->SetRenderState(D3DRS_ZENABLE, 1);
}}
//--------------------------------------------------------------------------//
if(Nh_Teknology33){
if ((NumVertices == 192) || (NumVertices == 256)){
return D3D_OK;
return 0;
}}
return oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}
//-----------------------------------------------------------------------------//
DWORD WINAPI HookEngine(LPVOID Param){
if (hGfxDx > 0){ 
DWORD tmp1 = (DWORD)GetModuleHandle("i3GfxDx.dll") + HookBaseRender; 
DWORD tmp2 = 0; 
Sleep(1); 
while(!pGDevice){ 
if(IsBadReadPtr((PDWORD)tmp1,4)==NULL)tmp2 = *(PDWORD)((DWORD)(tmp1))+ HookEndRender; 
Sleep(1); 
if(IsBadReadPtr((PDWORD)tmp2,4)==NULL){ Sleep(1); 
DWORD OldProtect; 
VirtualProtect((void*)(tmp2), 4, PAGE_EXECUTE_READWRITE, &OldProtect); 
memcpy(&pGDevice, (void *)tmp2, 4); 
VirtualProtect((void*)(tmp2), 4, OldProtect, NULL); 
}}Sleep(1); 
DWORD *g_pDevice = (DWORD*)pGDevice; 
g_pDevice = (DWORD*)g_pDevice[0]; 
while(!pDevice)pDevice = (LPDIRECT3DDEVICE9)(DWORD*)g_pDevice; 
*(PDWORD)&oEndScene = g_pDevice[42]; 
*(PDWORD)&oDrawIndexedPrimitive = g_pDevice[82]; 
Sleep(1); UknownScript((PDWORD)(g_pDevice[1] - 5), (PDWORD)(g_pDevice[4] - 5)); 
Sleep(1); UknownScript((PDWORD)(g_pDevice[2] - 5), (PDWORD)(g_pDevice[5] - 5)); 
Sleep(1); UknownScript((PDWORD)(g_pDevice[3] - 5), (PDWORD)(g_pDevice[6] - 5)); 
Sleep(1); UknownScript((PDWORD)(g_pDevice[4] - 5), (PDWORD)pGEndScene); 
Sleep(1); UknownScript((PDWORD)(g_pDevice[5] - 5), (PDWORD)pGDrawIndexedPrimitive); 
Sleep(1); 
while(1){ 
g_pDevice[42] = (DWORD)g_pDevice[1] - 5; 
g_pDevice[82] = (DWORD)g_pDevice[2] - 5; 
Sleep(1000); 
} 
} return 0; 
}
//-----------------------------------------------------------------------------//
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpvReserved){
DisableThreadLibraryCalls(hModule);
if(dwReason == DLL_PROCESS_ATTACH){
XMenuMouse(HookEngine);
}
return TRUE;
}
//-----------------------------------------------------------------------------//

 