//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
void DoSpamChat(){
	static DWORD dwTick = NULL;
	if(dwTick <= GetTickCount())
	{
		pGameContext->setEvent(0x1FD, "LAVERZOKA ID", NULL, NULL, NULL, NULL);
		pGameContext->setEvent(0x1FD, "Wawa Andra", NULL, NULL, NULL, NULL);
		dwTick = GetTickCount() + 25000;
	}
}

void DoHack()
{
	//==============================================================================================================================================
	if(IsInBattle() && pGameCharaManager->getLocalChara() && pGameCharaManager->getLocalChara()->isAlive()){
		//==============================================================================================================================================
		CGameCharaBase* LocalChara = pGameCharaManager->getLocalChara();
		MyCurrentWeaponIndex = LocalChara->getGameCharaWeaponContext()->getCurrentWeaponIndex();
		//==============================================================================================================================================
		if(Feature.AIM.AutoKiller)
		{
			DoSpamChat();
			Feature.AIM.Bullet=0;
			for(int i = 0; i <= 16; i++)
			{
				if(GetSlotWeapon() == Primary || GetSlotWeapon() == Secondary)
				{
					CGameCharaBase* Target = pGameCharaManager->getCharaByNetIdx(i);
					if(Target == NULL || Target->isAlive() == false || Target->isEnemy() == false || Target->isLocal() == true)continue;
					DWORD OptTeam = 2;
					D3DXVECTOR3 AimTargetHead = Target->getGameCharaBoneContext()->getBonePosition(7);
					D3DXVECTOR3 AimTargetBody = Target->getGameCharaBoneContext()->getBonePosition(5);
					AimTargetHead.y += 0.1f;
					AimTargetBody.y += 0.1f;
					if(Feature.AIM.AutoKiller == 1)
					{
						if(pGameContext->isRedTeam(Target->getCharaNetIndex()))OptTeam = 1;
						if(pGameCharaBase->getGameCharaWeaponContext()->getCurrentWeaponIndex() == 2)
						{
							SetEndVector->SetTargetVector(AimTargetHead);
							pGameCharaBase->getGameCharaWeaponContext()->getCurrentWeapon()->doFire();
							SetEndVector->Disable();
						}
						else
						{
							pGameCharaBase->getGameCharaWeaponContext()->getCurrentWeapon()->doLineCollision(&pGameCharaBase->getGameCharaBoneContext()->getBonePosition(7), &AimTargetHead, OptTeam);
							pGameCharaBase->getGameCharaWeaponContext()->getCurrentWeapon()->doFire();
						}
					}
					if(Feature.AIM.AutoKiller == 2){
						if(pGameContext->isRedTeam(Target->getCharaNetIndex()))OptTeam = 1;
						if(pGameCharaBase->getGameCharaWeaponContext()->getCurrentWeaponIndex() == 2)
						{
							SetEndVector->SetTargetVector(AimTargetBody);
							pGameCharaBase->getGameCharaWeaponContext()->getCurrentWeapon()->doFire();
							SetEndVector->Disable();
						}
						else
						{
							pGameCharaBase->getGameCharaWeaponContext()->getCurrentWeapon()->doLineCollision(&pGameCharaBase->getGameCharaBoneContext()->getBonePosition(5), &AimTargetBody, OptTeam);
							pGameCharaBase->getGameCharaWeaponContext()->getCurrentWeapon()->doFire();
						}
					}
				}
			}
		}
		//==============================================================================================================================================
		if(Feature.AIM.NetFire && !pGameContext->getUserDeath(pGameContext->getMySlotIdx()))
		{
			DoSpamChat();
			if(GetSlotWeapon() == Primary || GetSlotWeapon() == Secondary)
			{
				D3DXVECTOR3 vMe, vEnemy;
				CWeaponGrenade* pGrenade = (CWeaponGrenade*)(LocalChara->getGameCharaWeaponContext()->getCurrentWeapon());
				for(int iSlot = 0; iSlot <= 16; iSlot++)
				{
					if(IsAliveDeath(iSlot))
					{
						if(GetUserBone(vMe, 7, pGameContext->getMySlotIdx()))
						{
							if(GetUserBone(vEnemy, 7, iSlot))
							{
								pGrenade->NET_Fire(&vMe, &vEnemy);
								pGrenade->doFire();
								pGrenade->doLineCollision(&vMe, &vEnemy, GetTeam(iSlot));
							}
						}
					}
				}
			}
		}
		//==============================================================================================================================================
		if(Feature.AIM.AutoFire)
		{
			CGameCharaBase* MyTarget = LocalChara->getGameCharaCollisionContext()->GetCrosshairTarget();
			if(MyTarget > NULL)
				LocalChara->getGameCharaWeaponContext()->getCurrentWeapon()->doFire();
		}
		//==============================================================================================================================================
		if(Feature.Player.Teleport)
		{
			if(GetAsyncKeyState(VK_H))
			{
				for(int i = 0; i <= 16; i++)
				{
					CGameCharaBase* Target = pGameCharaManager->getCharaByNetIdx(i);
					if(Target == NULL || Target->isAlive() == false || Target->isEnemy() == false || Target->isLocal() == true)continue;
					pGameCharaBase->Cmd_Respawn(&Target->getGameCharaBoneContext()->getBonePosition(0));
				}
			}
		}
		//==============================================================================================================================================
		if(Feature.Weapon.QuickChange){
			CGameCharaAnimContext* pMyCharaAnimContext = LocalChara->getGameCharaAnimContext();
			if(pMyCharaAnimContext > NULL){
				i3AIContext* pMyCharai3AIContext = pMyCharaAnimContext->geti3AIContext();
				if(pMyCharai3AIContext > NULL){
					ModifyTargetBase[0] = (DWORD)pMyCharai3AIContext;
				} else ModifyTargetBase[0] = NULL;
			}else ModifyTargetBase[0] = NULL;
		}else ModifyTargetBase[0] = NULL;
		//==============================================================================================================================================
		if(Feature.Weapon.NoRecoil == 1){
		if(CallerNoRecoil == false)
				_patchMEM((void*)ResultGetOneVert,0xFF);		_patchMEM((void*)ResultGetRecoilHorz,0xFF);
				_patchMEM((void*)ResultGetOneHorz,0xFF);		_patchMEM((void*)ResultGetRecoilVert,0xFF);
				//WriteHook((void*)WeaponBase.Function.ReadWeaponInfo,(void*)(PBYTE)"\xD9\x45\xFF",3);
				CallerNoRecoil = true;
		}
		if (Feature.Weapon.NoRecoil == 0){
			if(CallerNoRecoil == true) 
				_patchMEM((void*)ResultGetOneVert,0xFC);		_patchMEM((void*)ResultGetRecoilHorz,0xFC);
				_patchMEM((void*)ResultGetOneHorz,0xFC);		_patchMEM((void*)ResultGetRecoilVert,0xFC);
				//WriteHook((void*)WeaponBase.Function.ReadWeaponInfo,(void*)(PBYTE)"\xD9\x45\xF4",3);
				CallerNoRecoil = false;
		}
		//==============================================================================================================================================
		if(Feature.Weapon.Accuracy)
		{
			CGameCharaBoneContext* pMyCharaBoneContext = LocalChara->getGameCharaBoneContext();
			if(pMyCharaBoneContext > NULL){
				CWeaponProperty* pMyWeaponProperty = pMyCharaBoneContext->getWeaponProperty();
				if(pMyWeaponProperty > NULL){

					static DWORD dwFreezeH1, dwFreezeH2, dwFreezeH3 = NULL;
					if(!dwFreezeH1)dwFreezeH1 = pMyWeaponProperty->RecoilH1;
					if(!dwFreezeH2)dwFreezeH2 = pMyWeaponProperty->RecoilH2;
					if(!dwFreezeH3)dwFreezeH3 = pMyWeaponProperty->RecoilH3;

					pMyWeaponProperty->RecoilV1 = 0;
					pMyWeaponProperty->RecoilV2 = 0;
					pMyWeaponProperty->RecoilH1 = dwFreezeH1;
					pMyWeaponProperty->RecoilH2 = dwFreezeH2;
					pMyWeaponProperty->RecoilH3 = dwFreezeH3;
					pMyWeaponProperty->Deviation1 = 0;
					pMyWeaponProperty->Deviation2 = 0;
					pMyWeaponProperty->Deviation3 = 0;
				}
			}
		}
		//==============================================================================================================================================
		if(Feature.Weapon.AutoShot)
		{
			if (!pGameContext->getUserDeath(pGameContext->getMySlotIdx()))
			{
				if(GetPlayerTarget(pGameContext->getMySlotIdx()))
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				}else{
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				}
			}
		}
		//==============================================================================================================================================
		if(Feature.Weapon.RapidFire)
		{
			if(pGameFramework->geti3InputMouse()->GetButtonState() == 1){
				DWORD dwDelay = 0;
				switch(Feature.Weapon.RapidFire)
				{
				case 1:
					dwDelay = 500;
					break;
				case 2:
					dwDelay = 300;
					break;
				case 3:
					dwDelay = 100;
					break;
				case 4:
					dwDelay = 10;
					break;
				}
				static DWORD dwTick = 0;
				if(dwTick <= GetTickCount())
				{
					pGameCharaBase->getGameCharaWeaponContext()->getCurrentWeapon()->Reset();
					pGameCharaBase->getGameCharaWeaponContext()->getCurrentWeapon()->doFire();
					dwTick = GetTickCount() + dwDelay;
				}
			}
		}
		//==============================================================================================================================================
		if(Feature.Player.Reborn)
		{
			pGameCharaManager->RespawnChara(pGameContext->getMySlotIdx());
		}
		Feature.Player.Reborn=0;
		//==============================================================================================================================================
		if(Feature.Player.NoFallDamage)
		{
			static DWORD dwTick = NULL;
			if(dwTick <= GetTickCount()){
				LocalChara->setInvicibleTime(4.0f);
				dwTick = GetTickCount() + 2000;
			}
		}
		//==============================================================================================================================================
		if(Feature.Player.JumpHight)
		{
			if(JumperDist == false){JumperDist2 = true;}
			if(JumperDist2 == true){JumperDist = true;JumperDist2 = false;}
			if(Feature.Player.JumpHight == 1)
			{
				LongJumperDist = 0.1f;
				if(GetAsyncKeyState(VK_SPACE)){
					JumperDist = true;
				}
				else{
					JumperDist = false;
				}
			}
		}
		//==============================================================================================================================================
		if(Feature.Player.HideNick)
		{
			CTeam *pTeam		= (CTeam*)(pGameContext + AddyEngine->GetAddyValueByKey("GameContext.Pointer.MySlotIdx"));
			int MyTeam = GetTeam(pTeam->iTeam);
			CNames		*pFake	     = (CNames*)((pGameContext + ResultPTRName) + pTeam->iTeam * 0x21);
			if(Feature.Player.HideNick == 1)
			{
				strcpy(pFake->szNames," ");
			}
		}
		//==============================================================================================================================================
		if(Feature.Player.NightVision){		
			pGameFramework->SetNightVisionEnable(true);
		}
		else if(!Feature.Player.NightVision){
			pGameFramework->SetNightVisionEnable(false);
		}
	}
	//==============================================================================================================================================
	if(Feature.Misc.AutoInvite && !IsInBattle() && GetStageGame() == AWAITING)
	{
		static DWORD dwTick = NULL;
		if(dwTick <= GetTickCount()){
			pGameContext->setEvent(0x86, NULL, NULL, NULL, NULL, NULL);
			for(int i = 0; i < 8; i++){
				pGameContext->SetInviteUser(i);
			}
			pGameContext->setEvent(0x87, NULL, NULL, NULL, NULL, NULL);
				dwTick = GetTickCount() + 500;
		}
	}
	//==============================================================================================================================================
	if(Feature.Misc.OpenSFull && !IsInBattle() && GetStageGame() == CHANNEL || GetStageGame() == SERVER)
	{
		pGameContext->SetMaxChannelUserCount(1000);
		for(int i = 0; i < 10; i++)
		{
			pGameContext->SetChannelUserCount(i, 0);
		}
		_patchMEM((void*)(AddyEngine->GetAddyValueByKey("XFHPB.Values.GaugeMultiplier")), (char*)"\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	}
	else
	{
		_patchMEM((void*)(AddyEngine->GetAddyValueByKey("XFHPB.Values.GaugeMultiplier")), (char*)"\x00\x00\x00\x00\x00\x00\x59\x40", 8);
	}
	//==============================================================================================================================================
	if(Feature.Misc.UnlockPW && !IsInBattle() && GetStageGame() == LOBBY)
	{
		IsGM = 1; 
	    MakeJMP((PBYTE)ResultGetEnteredServerX, (DWORD)ForceAcess, 0x4); 
	}
	//==============================================================================================================================================
	if(Feature.Misc.AntiKick && !IsInBattle() && GetStageGame() == AWAITING)
	{
		_patchMEM((void*)(AddyEngine->GetAddyValueByKey("PhaseReadyRoom.Function.SelfRemoveFromRoom")), (char*)"\xC3", 1);
	}
	else 
	{
		_patchMEM((void*)(AddyEngine->GetAddyValueByKey("PhaseReadyRoom.Function.SelfRemoveFromRoom")), (char*)"\x55", 1);
	}
	//==============================================================================================================================================
	if(Feature.Misc.AutoReady)
	{
		if(GetStageGame() == AWAITING)
		{
			TimeReady=250;
			MouseMoveAbsolute(TimeReady,buffer, Xx, Yy);
		}
	}
	//==============================================================================================================================================
	if(Feature.Misc.AutoBundir)
	{
		if(IsInBattle)
		{
			if (Tick <= GetTickCount())
			{
				keybd_event(VK_4, 0x85, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 1024, 1024, 0, 0);
				keybd_event(VK_RETURN, 0x9C, 0, 0);
				Tick = GetTickCount() + 1350 ;
			}
			else
			{
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				keybd_event(VK_4, 0x85, KEYEVENTF_KEYUP, 0);
				keybd_event(VK_RETURN, 0x9C, KEYEVENTF_KEYUP, 0);
			}
		}
	}
	//==============================================================================================================================================
	if(IsInBattle() && pGameCharaManager->getLocalChara() && pGameCharaManager->getLocalChara()->isAlive()){
		CGameCharaBase* LocalChara = pGameCharaManager->getLocalChara();
		MyCurrentWeaponIndex = LocalChara->getGameCharaWeaponContext()->getCurrentWeaponIndex();
		//==============================================================================================================================================
		if(Feature.Replace.Damage){
			if(IsKeyPressed(VK_LBUTTON,100))
				LocalChara->getGameCharaWeaponContext()->getCurrentWeapon()->doFire();
		}
		//==============================================================================================================================================
		if(Feature.Replace.Assault){
			Feature.Replace.Damage = 1;
			for (int i = 0; i <=16;i++)
				if(GetAsyncKeyState(VK_V))
					switch(Feature.Replace.Assault)
				{
				case 1: LocalChara->setCharaWeapon(0, _WeaponValue(100003039).WeaponType(), _WeaponValue(100003039).WeaponIndex()); break;//AK Sopmod D
				case 2: LocalChara->setCharaWeapon(0, _WeaponValue(100003068).WeaponType(), _WeaponValue(100003068).WeaponIndex()); break;//AK 47 FC Red
				case 3: LocalChara->setCharaWeapon(0, _WeaponValue(100003062).WeaponType(), _WeaponValue(100003062).WeaponIndex()); break;//AK Sopmod Medical
				case 4: LocalChara->setCharaWeapon(0, _WeaponValue(0x5F5EDB4).WeaponType(), _WeaponValue(0x5F5EDB4).WeaponIndex()); break;//AK Sopmod Sakura
				case 5: LocalChara->setCharaWeapon(0, _WeaponValue(0x5F5ECDC).WeaponType(), _WeaponValue(0x5F5ECDC).WeaponIndex()); break;//AUG A3 D
				case 6: LocalChara->setCharaWeapon(0, _WeaponValue(100003028).WeaponType(), _WeaponValue(100003028).WeaponIndex()); break;//AUG A3 EV
				case 7: LocalChara->setCharaWeapon(0, _WeaponValue(0x5F5ECDD).WeaponType(), _WeaponValue(0x5F5ECDD).WeaponIndex()); break;//AUG A3 Gold
				case 8: LocalChara->setCharaWeapon(0, _WeaponValue(100003341).WeaponType(), _WeaponValue(100003341).WeaponIndex()); break;//AUG A3 Chicano
				case 9: LocalChara->setCharaWeapon(0, _WeaponValue(100003343).WeaponType(), _WeaponValue(100003343).WeaponIndex()); break;//AUG A3 Beach
				case 10: LocalChara->setCharaWeapon(0, _WeaponValue(100003344).WeaponType(), _WeaponValue(100003344).WeaponIndex()); break;//AUG A3 Naga
				case 11: LocalChara->setCharaWeapon(0, _WeaponValue(100003345).WeaponType(), _WeaponValue(100003345).WeaponIndex()); break;//AUG A3 Comic
				case 12: LocalChara->setCharaWeapon(0, _WeaponValue(100003349).WeaponType(), _WeaponValue(100003349).WeaponIndex()); break;//AUG A3 Midnight3
				case 13: LocalChara->setCharaWeapon(0, _WeaponValue(100003350).WeaponType(), _WeaponValue(100003350).WeaponIndex()); break;//AUG A3 PBWC 2017
				case 14: LocalChara->setCharaWeapon(0, _WeaponValue(100003352).WeaponType(), _WeaponValue(100003352).WeaponIndex()); break;//AUG A3 CNPB T5
				case 15: LocalChara->setCharaWeapon(0, _WeaponValue(100003354).WeaponType(), _WeaponValue(100003354).WeaponIndex()); break;//AUG A3 Mech
				case 16: LocalChara->setCharaWeapon(0, _WeaponValue(100003355).WeaponType(), _WeaponValue(100003355).WeaponIndex()); break;//AUG A3 Lebaran 2017
				case 17: LocalChara->setCharaWeapon(0, _WeaponValue(100003359).WeaponType(), _WeaponValue(100003359).WeaponIndex()); break;//AUG A3 Infinitum
				case 18: LocalChara->setCharaWeapon(0, _WeaponValue(100003361).WeaponType(), _WeaponValue(100003361).WeaponIndex()); break;//AUG A3 Graffity
				case 19: LocalChara->setCharaWeapon(0, _WeaponValue(100003367).WeaponType(), _WeaponValue(100003367).WeaponIndex()); break;//AUG A3 Tropical
				case 20: LocalChara->setCharaWeapon(0, _WeaponValue(100003360).WeaponType(), _WeaponValue(100003360).WeaponIndex()); break;//Pindad SS2 V5 Infinitum
				case 21: LocalChara->setCharaWeapon(0, _WeaponValue(100003356).WeaponType(), _WeaponValue(100003356).WeaponIndex()); break;//SC 2010 Lebaran 2017
				case 22: LocalChara->setCharaWeapon(0, _WeaponValue(100003353).WeaponType(), _WeaponValue(100003353).WeaponIndex()); break;//SC 2010 CNPB T5
				case 23: LocalChara->setCharaWeapon(0, _WeaponValue(100003348).WeaponType(), _WeaponValue(100003348).WeaponIndex()); break;//SC 2010 Green
				case 24: LocalChara->setCharaWeapon(0, _WeaponValue(0x5F5EDAA).WeaponType(), _WeaponValue(0x5F5EDAA).WeaponIndex()); break;//SC 2010 X-MAS
				case 25: LocalChara->setCharaWeapon(0, _WeaponValue(0x5F5EDB6).WeaponType(), _WeaponValue(0x5F5EDB6).WeaponIndex()); break;//Water Gun
				case 26: LocalChara->setCharaWeapon(0, _WeaponValue(100003338).WeaponType(), _WeaponValue(100003338).WeaponIndex()); break;//MSBS
				case 27: LocalChara->setCharaWeapon(0, _WeaponValue(100003339).WeaponType(), _WeaponValue(100003339).WeaponIndex()); break;//MSBS Silver
				case 28: LocalChara->setCharaWeapon(0, _WeaponValue(100003340).WeaponType(), _WeaponValue(100003340).WeaponIndex()); break;//MSBS Gold
				case 29: LocalChara->setCharaWeapon(0, _WeaponValue(100003042).WeaponType(), _WeaponValue(100003042).WeaponIndex()); break;//M4 SR-16 Lv1
				case 30: LocalChara->setCharaWeapon(0, _WeaponValue(100003043).WeaponType(), _WeaponValue(100003043).WeaponIndex()); break;//M4 SR-16 Lv2
				case 31: LocalChara->setCharaWeapon(0, _WeaponValue(100003044).WeaponType(), _WeaponValue(100003044).WeaponIndex()); break;//M4 SR-16 Lv3
				case 32: LocalChara->setCharaWeapon(0, _WeaponValue(100003045).WeaponType(), _WeaponValue(100003045).WeaponIndex()); break;//M4 SR-16 FC
				case 33: LocalChara->setCharaWeapon(0, _WeaponValue(100003049).WeaponType(), _WeaponValue(100003049).WeaponIndex());break;//FAMAS G2
				case 34: LocalChara->setCharaWeapon(0, _WeaponValue(100003050).WeaponType(), _WeaponValue(100003050).WeaponIndex()); break;//FAMAS G2 Commando		
				case 35: LocalChara->setCharaWeapon(0, _WeaponValue(100003051).WeaponType(), _WeaponValue(100003051).WeaponIndex()); break;//FAMAS G2 Siniper
				case 36: LocalChara->setCharaWeapon(0, _WeaponValue(100003022).WeaponType(), _WeaponValue(100003022).WeaponIndex()); break;//FAMAS G2 M203			
				case 37: LocalChara->setCharaWeapon(0, _WeaponValue(100003064).WeaponType(), _WeaponValue(100003064).WeaponIndex()); break;//FAMAS G2 Commando G
				case 38: LocalChara->setCharaWeapon(0, _WeaponValue(100003062).WeaponType(), _WeaponValue(100003062).WeaponIndex()); break;//FAMAS G2 E-Sport
				case 39: LocalChara->setCharaWeapon(0, _WeaponValue(100003351).WeaponType(), _WeaponValue(100003351).WeaponIndex()); break;//FAMAS G2 Commando PBWC 2017
			}
		}
		//==============================================================================================================================================
		if(Feature.Replace.Smg){
			Feature.Replace.Damage = 1;
			for (int i = 0; i <=16;i++)
				if(GetAsyncKeyState(VK_V))
					switch(Feature.Replace.Smg)
				{		
				case 1: LocalChara->setCharaWeapon(0, _WeaponValue(200004029).WeaponType(), _WeaponValue(200004029).WeaponIndex()); break;//P90 Ext D
				case 2: LocalChara->setCharaWeapon(0, _WeaponValue(200004415).WeaponType(), _WeaponValue(200004415).WeaponIndex()); break;//P90 Ext Mech
				case 3: LocalChara->setCharaWeapon(0, _WeaponValue(200004425).WeaponType(), _WeaponValue(200004425).WeaponIndex()); break;//P90 Ext Infinitum
				case 4: LocalChara->setCharaWeapon(0, _WeaponValue(200004418).WeaponType(), _WeaponValue(200004418).WeaponIndex()); break;//P90 Ext Lebaran 2017
				case 5: LocalChara->setCharaWeapon(0, _WeaponValue(200004412).WeaponType(), _WeaponValue(200004412).WeaponIndex()); break;//P90 Ext CNPB T5
				case 6: LocalChara->setCharaWeapon(0, _WeaponValue(200004407).WeaponType(), _WeaponValue(200004407).WeaponIndex()); break;//P90 Ext Midnight3
				case 7: LocalChara->setCharaWeapon(0, _WeaponValue(200004402).WeaponType(), _WeaponValue(200004402).WeaponIndex()); break;//P90 Ext Green
				case 8: LocalChara->setCharaWeapon(0, _WeaponValue(200004395).WeaponType(), _WeaponValue(200004395).WeaponIndex()); break;//P90 Ext Naga
				case 9: LocalChara->setCharaWeapon(0, _WeaponValue(200004428).WeaponType(), _WeaponValue(200004428).WeaponIndex()); break;//OA 93 Grafitty
				case 10: LocalChara->setCharaWeapon(0, _WeaponValue(200004421).WeaponType(), _WeaponValue(200004421).WeaponIndex()); break;//OA 93 Infinitum
				case 11: LocalChara->setCharaWeapon(0, _WeaponValue(200004413).WeaponType(), _WeaponValue(200004413).WeaponIndex()); break;//OA 93 Mech
				case 12: LocalChara->setCharaWeapon(0, _WeaponValue(200004410).WeaponType(), _WeaponValue(200004410).WeaponIndex()); break;//OA 93 PBWC 2017
				case 13: LocalChara->setCharaWeapon(0, _WeaponValue(200004405).WeaponType(), _WeaponValue(200004405).WeaponIndex()); break;//OA 93 Midnught3
				case 14: LocalChara->setCharaWeapon(0, _WeaponValue(200004443).WeaponType(), _WeaponValue(200004443).WeaponIndex()); break;//OA 93 Tropical
				case 15: LocalChara->setCharaWeapon(0, _WeaponValue(200004441).WeaponType(), _WeaponValue(200004441).WeaponIndex()); break;//Kriss SV Tropical
				case 16: LocalChara->setCharaWeapon(0, _WeaponValue(200004426).WeaponType(), _WeaponValue(200004426).WeaponIndex()); break;//Kriss SV Grafitty
				case 17: LocalChara->setCharaWeapon(0, _WeaponValue(200004423).WeaponType(), _WeaponValue(200004423).WeaponIndex()); break;//Kriss SV Infinitum
				case 18: LocalChara->setCharaWeapon(0, _WeaponValue(200004416).WeaponType(), _WeaponValue(200004416).WeaponIndex()); break;//Kriss SV Lebaran 2017
				case 19: LocalChara->setCharaWeapon(0, _WeaponValue(200004408).WeaponType(), _WeaponValue(200004408).WeaponIndex()); break;//Kriss SV PBWC 2017
				case 20: LocalChara->setCharaWeapon(0, _WeaponValue(200004403).WeaponType(), _WeaponValue(200004403).WeaponIndex()); break;//Kriss SV Midnight3
				case 21: LocalChara->setCharaWeapon(0, _WeaponValue(200004400).WeaponType(), _WeaponValue(200004400).WeaponIndex()); break;//Kriss SV Green
				case 22: LocalChara->setCharaWeapon(0, _WeaponValue(200004396).WeaponType(), _WeaponValue(200004396).WeaponIndex()); break;//Kriss SV Comic
				case 23: LocalChara->setCharaWeapon(0, _WeaponValue(200004393).WeaponType(), _WeaponValue(200004393).WeaponIndex()); break;//Kriss SV Naga
				case 24: LocalChara->setCharaWeapon(0, _WeaponValue(200004391).WeaponType(), _WeaponValue(200004391).WeaponIndex()); break;//Kriss SV Beach
				case 25: LocalChara->setCharaWeapon(0, _WeaponValue(200004389).WeaponType(), _WeaponValue(200004389).WeaponIndex()); break;//Kriss SV Chicano
				case 26: LocalChara->setCharaWeapon(0, _WeaponValue(200004050).WeaponType(), _WeaponValue(200004050).WeaponIndex()); break;//Kriss SV E-Sport
				case 27: LocalChara->setCharaWeapon(0, _WeaponValue(0xBEBD24A).WeaponType(), _WeaponValue(0xBEBD24A).WeaponIndex()); break;//Kriss SV Love
			}
		}
		//==============================================================================================================================================
		if(Feature.Replace.Sniper){
			Feature.Replace.Damage = 1;
			for (int i = 0; i <=16;i++)
				if(GetAsyncKeyState(VK_V))
					switch(Feature.Replace.Sniper)
				{
				case 1: LocalChara->setCharaWeapon(0, _WeaponValue(300005021).WeaponType(), _WeaponValue(300005021).WeaponIndex()); break;//Rangemaster .338
				case 2: LocalChara->setCharaWeapon(0, _WeaponValue(300005022).WeaponType(), _WeaponValue(300005022).WeaponIndex()); break;//Rangemaster 7,62
				case 3: LocalChara->setCharaWeapon(0, _WeaponValue(300005023).WeaponType(), _WeaponValue(300005023).WeaponIndex()); break;//Rangemaster 7,62 STBY
				case 4: LocalChara->setCharaWeapon(0, _WeaponValue(300005032).WeaponType(), _WeaponValue(300005032).WeaponIndex()); break;//Barrett M82A1
				case 5: LocalChara->setCharaWeapon(0, _WeaponValue(300005232).WeaponType(), _WeaponValue(300005232).WeaponIndex()); break;//Barrett M82A1 Premium
				case 6: LocalChara->setCharaWeapon(0, _WeaponValue(300005225).WeaponType(), _WeaponValue(300005225).WeaponIndex()); break;//AS 50 Infinitum
				case 7: LocalChara->setCharaWeapon(0, _WeaponValue(300005217).WeaponType(), _WeaponValue(300005217).WeaponIndex()); break;//AS 50 Midnight3
				case 8: LocalChara->setCharaWeapon(0, _WeaponValue(0x11E1B699).WeaponType(), _WeaponValue(0x11E1B699).WeaponIndex()); break;//L115A1
				case 9: LocalChara->setCharaWeapon(0, _WeaponValue(300005036).WeaponType(), _WeaponValue(300005036).WeaponIndex()); break;//L115A1 SE
				case 10: LocalChara->setCharaWeapon(0, _WeaponValue(300005033).WeaponType(), _WeaponValue(300005033).WeaponIndex()); break;//L115A1 E-Sport
				case 11: LocalChara->setCharaWeapon(0, _WeaponValue(300005030).WeaponType(), _WeaponValue(300005030).WeaponIndex()); break;//Cheytac M200
				case 12: LocalChara->setCharaWeapon(0, _WeaponValue(300005233).WeaponType(), _WeaponValue(300005233).WeaponIndex()); break;//Cheytac M200 Tropical
				case 13: LocalChara->setCharaWeapon(0, _WeaponValue(300005220).WeaponType(), _WeaponValue(300005220).WeaponIndex()); break;//Cheytac M200 CNPB T5
				case 14: LocalChara->setCharaWeapon(0, _WeaponValue(300005218).WeaponType(), _WeaponValue(300005218).WeaponIndex()); break;//Cheytac M200 PBWC 2017
				case 15: LocalChara->setCharaWeapon(0, _WeaponValue(300005215).WeaponType(), _WeaponValue(300005215).WeaponIndex()); break;//Cheytac M200 Comic
				case 16: LocalChara->setCharaWeapon(0, _WeaponValue(300005214).WeaponType(), _WeaponValue(300005214).WeaponIndex()); break;//Cheytac M200 Naga
				case 17: LocalChara->setCharaWeapon(0, _WeaponValue(300005212).WeaponType(), _WeaponValue(300005212).WeaponIndex()); break;//Cheytac M200 Chicano
				case 18: LocalChara->setCharaWeapon(0, _WeaponValue(300005213).WeaponType(), _WeaponValue(300005213).WeaponIndex()); break;//PGM Hecate2 Beach
				case 19: LocalChara->setCharaWeapon(0, _WeaponValue(0x11E1B703).WeaponType(), _WeaponValue(0x11E1B703).WeaponIndex()); break;//Tactilite T2
				case 20: LocalChara->setCharaWeapon(0, _WeaponValue(300005227).WeaponType(), _WeaponValue(300005227).WeaponIndex()); break;//Tactilite T2 Grafitty
				case 21: LocalChara->setCharaWeapon(0, _WeaponValue(300005226).WeaponType(), _WeaponValue(300005226).WeaponIndex()); break;//Tactilite T2 Infinitum
				case 22: LocalChara->setCharaWeapon(0, _WeaponValue(300005222).WeaponType(), _WeaponValue(300005222).WeaponIndex()); break;//Tactilite T2 Lebaran 2017
				case 23: LocalChara->setCharaWeapon(0, _WeaponValue(300005221).WeaponType(), _WeaponValue(300005221).WeaponIndex()); break;//Tactilite T2 Mech
				case 24: LocalChara->setCharaWeapon(0, _WeaponValue(300005219).WeaponType(), _WeaponValue(300005219).WeaponIndex()); break;//Tactilite T2 PBWC 2017
				case 25: LocalChara->setCharaWeapon(0, _WeaponValue(300005216).WeaponType(), _WeaponValue(300005216).WeaponIndex()); break;//Tactilite T2 Green
			}
		}
		//==============================================================================================================================================
		if(Feature.Replace.Shotgun){
			Feature.Replace.Damage = 1;
			for (int i = 0; i <=16;i++)
				if(GetAsyncKeyState(VK_V))
					switch(Feature.Replace.Shotgun)
				{
				case 1: LocalChara->setCharaWeapon(0, _WeaponValue(400006020).WeaponType(), _WeaponValue(400006020).WeaponIndex()); break;//Kel-Tec KSG-15
				case 2: LocalChara->setCharaWeapon(0, _WeaponValue(400006019).WeaponType(), _WeaponValue(400006019).WeaponIndex()); break;//Jackhammer
				case 3: LocalChara->setCharaWeapon(0, _WeaponValue(0x17D79B7C).WeaponType(), _WeaponValue(0x17D79B7C).WeaponIndex()); break;//SPASS 15 D
				case 4: LocalChara->setCharaWeapon(0, _WeaponValue(0x17D79B79).WeaponType(), _WeaponValue(0x17D79B79).WeaponIndex()); break;//SPASS 15 SI
				case 5: LocalChara->setCharaWeapon(0, _WeaponValue(0x17D79B82).WeaponType(), _WeaponValue(0x17D79B82).WeaponIndex()); break;//SPASS 15 MSC
				case 6: LocalChara->setCharaWeapon(0, _WeaponValue(0x17D79B75).WeaponType(), _WeaponValue(0x17D79B75).WeaponIndex()); break;//M1187 D
				case 7: LocalChara->setCharaWeapon(0, _WeaponValue(400006021).WeaponType(), _WeaponValue(400006021).WeaponIndex()); break;//M1187 SL
				case 8: LocalChara->setCharaWeapon(0, _WeaponValue(400006111).WeaponType(), _WeaponValue(400006111).WeaponIndex()); break;//M1187 Tropical
				case 9: LocalChara->setCharaWeapon(0, _WeaponValue(400006109).WeaponType(), _WeaponValue(400006109).WeaponIndex()); break;//M1187 Infintum
				case 10: LocalChara->setCharaWeapon(0, _WeaponValue(400006105).WeaponType(), _WeaponValue(400006105).WeaponIndex()); break;//M1187 Lebaran 2017
				case 11: LocalChara->setCharaWeapon(0, _WeaponValue(400006104).WeaponType(), _WeaponValue(400006104).WeaponIndex()); break;//M1187 Mech
				case 12: LocalChara->setCharaWeapon(0, _WeaponValue(400006103).WeaponType(), _WeaponValue(400006103).WeaponIndex()); break;//M1187 PBWC 2017
				case 13: LocalChara->setCharaWeapon(0, _WeaponValue(400006102).WeaponType(), _WeaponValue(400006102).WeaponIndex()); break;//M1187 Green
				case 14: LocalChara->setCharaWeapon(0, _WeaponValue(400006101).WeaponType(), _WeaponValue(400006101).WeaponIndex()); break;//M1187 Comic
				case 15: LocalChara->setCharaWeapon(0, _WeaponValue(400006100).WeaponType(), _WeaponValue(400006100).WeaponIndex()); break;//M1187 Naga
				case 16: LocalChara->setCharaWeapon(0, _WeaponValue(400006099).WeaponType(), _WeaponValue(400006099).WeaponIndex()); break;//M1187 Beach
				case 17: LocalChara->setCharaWeapon(0, _WeaponValue(400006098).WeaponType(), _WeaponValue(400006098).WeaponIndex()); break;//M1187 Chicano
				case 18: LocalChara->setCharaWeapon(0, _WeaponValue(400006108).WeaponType(), _WeaponValue(400006108).WeaponIndex()); break;//Zombie Slayer Infinitum
			}
		}
		if(Feature.Replace.Launcher){
			for (int i = 0; i <=16;i++)
				if(GetAsyncKeyState(VK_V))
					Feature.Replace.Damage = 1;
					Feature.AIM.Bullet = 2;
					Feature.AIM.NetFire = 1;
					Feature.Weapon.QuickChange = 1;
					Feature.Player.NoFallDamage = 1;
					switch(Feature.Replace.Launcher)
				{
				case 1: LocalChara->setCharaWeapon(0, _WeaponValue(100016002).WeaponType(), _WeaponValue(100016002).WeaponIndex()); break;//RPG-7
				case 2: LocalChara->setCharaWeapon(0, _WeaponValue(0x23D2902C).WeaponType(), _WeaponValue(0x23D2902C).WeaponIndex()); break;//M-79
				case 3: LocalChara->setCharaWeapon(0, _WeaponValue(0x23D2902A).WeaponType(), _WeaponValue(0x23D2902A).WeaponIndex()); break;//HK-69
			}
		}
	}
}
//==============================================================================================================================================