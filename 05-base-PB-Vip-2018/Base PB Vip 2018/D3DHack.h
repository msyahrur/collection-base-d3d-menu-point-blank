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
#include "Textures.h"

HWND myWindow = NULL;
bool stateReset[2] = {0};
void ResetDevice()
{
	if(!Font())FontReset();
	if(g_pFont){
		g_pFont->OnLostDevice();
		g_pFont->OnResetDevice();
		g_pFont->Release();
		g_pFont = NULL;
	}
	if(g_pLine){
		g_pLine->OnLostDevice();
		g_pLine->OnResetDevice();
		g_pLine->Release();
		g_pLine = NULL;
	}
	if(pFont){
		pFont->OnLostDevice();
		pFont->OnResetDevice();
		pFont->Release();
		pFont = NULL;
	}
	if(Red)	{
		Red->Release();
		Red = NULL;
	}
	if(Blue) {
		Blue->Release();
		Blue = NULL;
	}
	if(npDevice)
		npDevice = NULL;
}

//==============================================================================================================================================
HRESULT WINAPI hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    if( g_pFont )
        g_pFont->OnLostDevice();
   
	if( g_pLine )
		g_pLine->OnLostDevice();

	if( pFont )
		pFont->OnLostDevice();

    if(oReset == D3D_OK) 
	{
		if( g_pFont )
            g_pFont->OnResetDevice();

		if(g_pLine)
			g_pLine->OnResetDevice();

		if( pFont )
			pFont->OnResetDevice();

		if(Red)	{
			Red->Release();
			Red = NULL;
		}

		if(Blue) {
			Blue->Release();
			Blue = NULL;
		}

	}

    return oReset(pDevice, pPresentationParameters);
}

//==============================================================================================================================================
void ThreadReset()
{
	static DWORD TickReset = 0;
	while(true)
	{
		if(npDevice){

			if(npDevice->TestCooperativeLevel() == D3DERR_DEVICELOST){
				stateReset[0] = true;
				stateReset[1] = true;
				TickReset = GetTickCount() + 4000;
			}
			else {
				stateReset[0] = false;
				stateReset[1] = false;
			}
			while(TickReset >= GetTickCount()){
				if(stateReset[0] == true)
				{
					
					if(g_pFont){
						g_pFont->OnLostDevice();
						g_pFont->OnResetDevice();
					}
					if(g_pLine)
					{
						g_pLine->OnLostDevice();
						g_pLine->OnResetDevice();
					}
					if(pFont){
						pFont->OnLostDevice();
						pFont->OnResetDevice();
					}
				}
				if(stateReset[1] == true)
				{
					if(Red)	{
						Red->Release();
						Red = NULL;
					}
					if(Blue) {
						Blue->Release();
						Blue = NULL;
					}
				}
				
			}
		}
		Sleep(0);
	}
}

void Crosshair(LPDIRECT3DDEVICE9 pDevice, D3DVIEWPORT9 pViewPort, D3DCOLOR Color)
{

	pDevice->GetViewport(&pViewPort);
	D3DRECT RectA, RectB;
	RectA.x1 = (pViewPort.Width/2)-10;
	RectA.x2 = (pViewPort.Width/2)+ 10;
	RectA.y1 = (pViewPort.Height/2);
	RectA.y2 = (pViewPort.Height/2)+1;
	RectB.x1 = (pViewPort.Width/2);
	RectB.x2 = (pViewPort.Width/2)+ 1;
	RectB.y1 = (pViewPort.Height/2)-10;
	RectB.y2 = (pViewPort.Height/2)+10;
	pDevice->Clear(1, &RectA, D3DCLEAR_TARGET, Color, 0,  0);
	pDevice->Clear(1, &RectB, D3DCLEAR_TARGET, Color, 0,  0);
}

#define SAFE_RELEASE(p){ if (p) { (p)->Release(); (p)=NULL; } }

bool bScreenshotTaken = false;

void UnProtectAndModify(DWORD Offset, DWORD Pointer, DWORD Length)
{
	DWORD OldProtection;
	VirtualProtect((void *)Offset, Length, PAGE_EXECUTE_READWRITE, &OldProtection);
	RtlCopyMemory((void *)Offset, (const void*)Pointer, Length);
	VirtualProtect((void *)Offset, Length, OldProtection, &OldProtection);
}

void MEMPatch( BYTE *Offset, BYTE *ByteArray, DWORD Length)
{
	__try 
	{
		UnProtectAndModify((DWORD)Offset , (DWORD)ByteArray , Length);
	}__except ( EXCEPTION_EXECUTE_HANDLER ) {}
}

//==============================================================================================================================================
bool ShowX		= true;
void DrawMenuD3D(LPDIRECT3DDEVICE9 pDevice)
{
	static bool DrawDXFont = false;
	if(!DrawDXFont)
	{
		D3DXCreateFontA(pDevice, 15, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, /*"Courier"*/"Arial"/*"Franklin Gothic"*/, &pFont);
		DrawDXFont = true;
	}

	if (Drawing == 0)
	{
		if(Mmax==0) 
			RebuildMenu(pDevice);
			MenuShow(mx,my,pDevice);
			MenuHandler(pDevice);
			MenuNav();
	}

	if(Font())FontCreate(pDevice);

	if(!g_pFont)D3DXCreateFontA(pDevice, 15, 0, FW_EXTRALIGHT, 2, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCSTR)"Arial", &g_pFont);
}

//==============================================================================================================================================
HRESULT WINAPI hkEndScene(LPDIRECT3DDEVICE9 pDevice){

	while(!npDevice)
	{
		npDevice = pDevice;	
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

	pDevice->GetViewport(&g_ViewPort);

	if(!g_pLine)D3DXCreateLine(pDevice,&g_pLine);

	if(Red == NULL)D3DXCreateTextureFromFileInMemory(pDevice, &_texRed, sizeof(_texRed), &Red);
	if(Blue == NULL)D3DXCreateTextureFromFileInMemory(pDevice, &_texBlue, sizeof(_texBlue), &Blue);

	ScreenCenterX = g_ViewPort.Width / 2;
	ScreenCenterY = g_ViewPort.Height / 2;

	DirectInputLoop();
	float ScreenCenterX = (g_ViewPort.Width /2.0f);
	float ScreenButtomY = (g_ViewPort.Height);
	DrawMenuD3D(pDevice);

	DoESP(pDevice);
	DoAimAssist(pDevice);
	DoHack();
	DoRoomHack();
	Replace_Real();
	BypassAbuse();
	HookBurst();

	if(IsKeyPressed(VK_F12, 0)&1)
	{
		ExitProcess(0);
	}

	if(!IsInBattle()){
		FeatureEngine->_get("GameHack.Selector.Damage")->_disable();
		FeatureEngine->_get("GameHack.Selector.Assault")->_disable();
		FeatureEngine->_get("GameHack.Selector.SMG")->_disable();
		FeatureEngine->_get("GameHack.Selector.Sniper")->_disable();
		FeatureEngine->_get("GameHack.Selector.Shotgun")->_disable();
		FeatureEngine->_get("GameHack.Selector.Secondary")->_disable();
		FeatureEngine->_get("GameHack.Selector.Machingun")->_disable();
	}

	if( IsInBattle() ){
		/*if( FeatureEngine->_get("Visual.Direct3D.CrossHair")->_val() )Crosshair(pDevice, g_ViewPort, RED);*/
		if(FeatureEngine->_get("Visual.Direct3D.CrossHair")->_val())
		{
			D3DVIEWPORT9 viewP;
			pDevice->GetViewport( &viewP );
			DWORD ScreenCenterX = viewP.Width / 2; 
			DWORD ScreenCenterY = viewP.Height / 2; 

			D3DRECT rec1 = {ScreenCenterX-35, ScreenCenterY, ScreenCenterX+ 35, ScreenCenterY+1};
			D3DRECT rec2 =	{ScreenCenterX, ScreenCenterY-35, ScreenCenterX+ 1,ScreenCenterY+35};  

			if(FeatureEngine->_get("Visual.Direct3D.CrossHair")->_val() == 1)
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
			if(FeatureEngine->_get("Visual.Direct3D.CrossHair")->_val() == 2)
			{	
				D3DRECT rec16 = {ScreenCenterX-2, ScreenCenterY-2, ScreenCenterX+ 2, ScreenCenterY+2};
				D3DRECT rec17 = {ScreenCenterX-2, ScreenCenterY-2, ScreenCenterX+ 2,ScreenCenterY+2};  
				pDevice->Clear( 1, &rec16, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), 0,  0 );//red
				pDevice->Clear( 1, &rec17, D3DCLEAR_TARGET, D3DXCOLOR(1.0, 0.0, 0.0, 1.0), 0,  0 );
			}
		}
	}
	/*return pDevice->EndScene();*/
	return oEndScene(pDevice);
}

//==============================================================================================================================================
HRESULT WINAPI hkDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{
	if(!Generate)
	{
		Generate = true;
	}
	if(!Red)D3DXCreateTextureFromFileInMemory(pDevice, &_texRed, sizeof(_texRed), &Red);
	if(!Blue)D3DXCreateTextureFromFileInMemory(pDevice, &_texBlue, sizeof(_texBlue), &Blue);
	if(IsInBattle()){	
		if(FeatureEngine->_get("Visual.Direct3D.WallHack")->_val() || FeatureEngine->_get("Visual.Direct3D.Charms")->_val()){
			if(allp2){  
				//pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
				if(FeatureEngine->_get("Visual.Direct3D.Charms")->_val()){
					if(FeatureEngine->_get("Visual.Direct3D.Charms")->_val() == 1){ //Light Charms
						pDevice->SetRenderState(D3DRS_ZENABLE,false);
						if(PlayerTerorist||TeroHead||C5||K400)pDevice->SetTexture(0,Red);
						if(PlayerCT||CTHead)pDevice->SetTexture(0,Blue);
						pDevice->DrawIndexedPrimitive(PrimType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount);
						pDevice->SetRenderState(D3DRS_ZENABLE,true);

					}
					if(FeatureEngine->_get("Visual.Direct3D.Charms")->_val() == 2){ //Ghost Charms
						pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
						pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVDESTCOLOR);
						pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_INVSRCCOLOR);
						pDevice->SetRenderState(D3DRS_ZENABLE,false);	
						pDevice->DrawIndexedPrimitive(PrimType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount);
						pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
						pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVDESTCOLOR);
						pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_INVSRCCOLOR);
						pDevice->SetRenderState(D3DRS_ZENABLE,true);
					}
					if(FeatureEngine->_get("Visual.Direct3D.Charms")->_val() == 3){ //Phantom Charms
						pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
						pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVDESTCOLOR);
						pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_INVSRCALPHA);
						pDevice->SetRenderState(D3DRS_ZENABLE,false);
						pDevice->DrawIndexedPrimitive(PrimType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount);
						pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
						pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVDESTCOLOR);
						pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_INVSRCALPHA);
						pDevice->SetRenderState(D3DRS_ZENABLE,false);
					}
				}
				else
				{
					pDevice->SetRenderState(D3DRS_ZENABLE, false);
					pDevice->DrawIndexedPrimitive(PrimType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount);
					pDevice->SetRenderState(D3DRS_ZENABLE, true);
				}
			}
		}


		if(FeatureEngine->_get("Visual.Direct3D.NoSmoke")->_val())
			if((NumVertices == 192) || (NumVertices == 256))return D3D_OK;

		if(FeatureEngine->_get("Visual.Direct3D.NoSmoke")->_val())pDevice->SetRenderState(D3DRS_FOGENABLE, false);

	}
	return pDevice->DrawIndexedPrimitive(PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}
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