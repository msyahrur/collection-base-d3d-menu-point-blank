//CREATED BY SC0D3 Solusi Game No Di IndoneisaL
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
					if(pLine){
						pLine->OnLostDevice();
						pLine->OnResetDevice();
					}
				}
				if(stateReset[1] == true)
				{
					if(TexRed)	{
						TexRed->Release();
						TexRed = NULL;
					}
					if(TexBlue) {
						TexBlue->Release();
						TexBlue = NULL;
					}
				}				
			}
		}
		Sleep(0);
	}
}

HRESULT WINAPI hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if(stateReset[0] == true)
		goto skipES;
	while(!npDevice)
	{
		CreateThread(0,0,(LPTHREAD_START_ROUTINE)ThreadReset,0,0,0);
		npDevice = pDevice;
	}
	static bool bInitEs = false;
	while(!bInitEs)
	{
		Hook_SetEvent();
		bInitEs = true;
	}
	DirectInputLoop();
	DrawRainBow();
	DrawMenuD3D(pDevice);

	UpdateGameClass();
	UpdateLocalClass();

	CallAutoOff();
	CallDoESP(pDevice);
	CallDoAssist(pDevice);
	CallFuncOutGame();
	BulletTele();
	CallDoHack();
	DoSpamChat();
	CallGBMode();
	CallBypassAbuse();
	CallSetBrust();
	CallDoReplace();

	DrawString(20, 7, RainbowTextTest/*RainbowTextTest*/, "Cheat Point Blank Garena ID  | SC0D3");

	if(IsInBattle()){
		DWORD CrosshairColor = Green;
		if(pGameCharaManager->getLocalChara()->getGameCharaCollisionContext()->GetCrosshairTarget() > NULL )CrosshairColor = Red;
		if(Visual.Direct3D.CrossHair)Crosshair(pDevice, g_ViewPort, CrosshairColor);
	}
	if(Visual.Direct3D.FastExit)
	{
		ExitProcess(0);
	}
	
	if(IsKeyPressed(VK_F1, 0)&1){Visual.ESP.Bone=!Visual.ESP.Bone;}
	if(IsKeyPressed(VK_F2, 0)&1){Visual.ESP.Name=!Visual.ESP.Name;}
	if(IsKeyPressed(VK_F3, 0)&1){GameHack.Weapon.NoRecoil=!GameHack.Weapon.NoRecoil;}
	if(IsKeyPressed(VK_F4, 0)&1){GameHack.Weapon.QuickChange=!GameHack.Weapon.QuickChange;}
	if(IsKeyPressed(VK_F5, 0)&1){GameHack.Brutal.AutoKiller=!GameHack.Brutal.AutoKiller;}
	if(IsKeyPressed(VK_HOME, 0)&1){GameHack.Assist.Mode=!GameHack.Assist.Mode;}
	//if(IsKeyPressed(VK_TAB, 0)&1){GameHack.Assist.Target=!GameHack.Assist.Target;}
	//if(IsKeyPressed(VK_CAPITAL, 0)&1){GameHack.Assist.AimReal=!GameHack.Assist.AimReal;}
	if(IsKeyPressed(VK_END, 0)&1){GameHack.Player.Suicide=!GameHack.Player.Suicide;}
	if(IsKeyPressed(VK_RCONTROL, 0)&1){GameHack.Player.Reborn=!GameHack.Player.Reborn;}
	if(IsKeyPressed(VK_F12, 0)&1){ExitProcess(0);}

	skipES:
	oEndScene = (tEndScene)GetOriginalEndScene();
	return oEndScene(pDevice);
}

HRESULT WINAPI hkDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{
	if(!Generate)
	{
		Generate = true;
	}
	if(!TexRed)D3DXCreateTextureFromFileInMemory(pDevice, &_texRed, sizeof(_texRed), &TexRed);
	if(!TexBlue)D3DXCreateTextureFromFileInMemory(pDevice, &_texBlue, sizeof(_texBlue), &TexBlue);
	if(Visual.Direct3D.WallHack){
		if(allp){
			pDevice->SetRenderState(D3DRS_ZENABLE, false);
			pDevice->DrawIndexedPrimitive(PrimType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount);
			pDevice->SetRenderState(D3DRS_ZENABLE, true);
		}
	}
	if(Visual.Direct3D.Charms){
		if(allp){
			if(Visual.Direct3D.Charms == 1){
				pDevice->SetRenderState(D3DRS_ZENABLE,false);
				if(PlayerTR||TRHead||Weapons||K400||C5)pDevice->SetTexture(0, TexRed);
				if(PlayerCT||CTHead||Weapons||K400||C5)pDevice->SetTexture(0, TexBlue);
				pDevice->DrawIndexedPrimitive(PrimType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount);
				pDevice->SetRenderState(D3DRS_ZENABLE,true);
			}
			if(Visual.Direct3D.Charms == 2){
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
			if(Visual.Direct3D.Charms == 3){
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
	}
	if(Visual.Direct3D.NoSmoke){
		if((Stride==24 && (NumVertices==256||NumVertices==192)))return D3D_OK;
	}
	if(Visual.Direct3D.NoFog){
		pDevice->SetRenderState(D3DRS_FOGENABLE, false);
	}
	return pDevice->DrawIndexedPrimitive(PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}