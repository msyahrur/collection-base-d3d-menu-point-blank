//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
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
					if(mFont){
						mFont->OnLostDevice();
						mFont->OnResetDevice();
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

	RainBow();
	DrawD3DFont(pDevice);
	DrawD3DMenu(pDevice);

	UpdateGameClass();
	UpdateLocalClass();

	DoESP(pDevice);
	DoAimBullet(pDevice);
	DoAimReal();
	DoHack();

	if(!IsInBattle()){
		Feature.AIM.Bullet=0;
		Feature.AIM.AutoFire=0;
		Feature.AIM.AutoKiller=0;
		Feature.AIM.NetFire=0;
		Feature.Player.HideNick=0;
		Feature.Player.JumpHight=0;
		Feature.Player.Reborn=0;
		Feature.Player.NoFallDamage=0;
		Feature.Player.Teleport=0;
		Feature.Weapon.AutoMacro=0;
		Feature.Weapon.AutoShot=0;
		Feature.Weapon.RapidFire=0;
		Feature.Weapon.Accuracy=0;
		Feature.Replace.Damage=0;
		Feature.Replace.Assault=0;
		Feature.Replace.Smg=0;
		Feature.Replace.Sniper=0;
		Feature.Replace.Shotgun=0;
		Feature.Replace.Launcher=0;
	}

	if(IsInBattle()){
		if(Feature.Direct3D.CrossHair){DrawCrossHair(pDevice);}
		if(Feature.Player.AutoSuicide){pGameCharaBase->eventFall(200);}
	}
	
	if(IsKeyPressed(VK_F1, 0)&1){Feature.ESP.Bone=!Feature.ESP.Bone;}
	if(IsKeyPressed(VK_F2, 0)&1){Feature.ESP.NameTag=!Feature.ESP.NameTag;}
	if(IsKeyPressed(VK_F3, 0)&1){Feature.Weapon.NoRecoil=!Feature.Weapon.NoRecoil;}
	if(IsKeyPressed(VK_F4, 0)&1){Feature.Weapon.QuickChange=!Feature.Weapon.QuickChange;}
	if(IsKeyPressed(VK_F5, 0)&1){Feature.Weapon.AutoMacro=!Feature.Weapon.AutoMacro;}
	if(IsKeyPressed(VK_F6, 0)&1){Feature.Weapon.RapidFire=!Feature.Weapon.RapidFire;}
	if(IsKeyPressed(VK_F7, 0)&1){Feature.AIM.AutoKiller=!Feature.AIM.AutoKiller;}
	if(IsKeyPressed(VK_F12, 0)&1){ExitProcess(0);}
	if(IsKeyPressed(VK_HOME, 0)&1){Feature.AIM.Bullet=!Feature.AIM.Bullet;}
	if(IsKeyPressed(VK_CAPITAL, 0)&1){Feature.AIM.Real=!Feature.AIM.Real;}
	if(IsKeyPressed(VK_RCONTROL, 0)&1){Feature.Player.Reborn=!Feature.Player.Reborn;}
	if(IsKeyPressed(VK_END, 0)&1){Feature.Player.AutoSuicide=!Feature.Player.AutoSuicide;}

	skipES:
	oEndScene = (tEndScene)GetOriginalEndScene();
	return oEndScene(pDevice);
}