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
#include "HackFunctions.h"
#include "HackDefines.h"

#pragma warning(disable:4309)
/*---------------------------------------- Declaration MoveSpeed --------------------------------------------------*/
__declspec (naked) void GetMoveSpeed()
{
	static float V_Move1 = 100;
	static float V_Move2 = 108;
	static float V_Move3 = 112;
	static float V_Move4 = 116;
	static float V_Move5 = 118;
	static float V_Move6 = 120;

	if (GameHack.Player.MoveSpeed == 1)__asm fld dword ptr[V_Move1]
	if (GameHack.Player.MoveSpeed == 2)__asm fld dword ptr[V_Move2]
	if (GameHack.Player.MoveSpeed == 3)__asm fld dword ptr[V_Move3]
	if (GameHack.Player.MoveSpeed == 4)__asm fld dword ptr[V_Move4]
	if (GameHack.Player.MoveSpeed == 5)__asm fld dword ptr[V_Move5]
	if (GameHack.Player.MoveSpeed == 6)__asm fld dword ptr[V_Move6]

	if (GameHack.Player.MoveSpeed == 0)__asm fld dword ptr[ebp - 8]

	__asm mov esp, ebp
	__asm jmp[WeaponBase.Function.RETGetMoveSpeed]
}

/*---------------------------------------- Declaration Brust Weapon ----------------------------------------------------*/
DWORD dwBurst, dwRet_Burst, dwMyWeapon = NULL;
DWORD dwSetBurst = 1; // Kalau di set 1, peluru yang keluar 1 tiap nembak, kalau di set 30, peluru yang keluar sekali nembak 30
__declspec(naked) void hkBurst()
{
	__asm 
	{
		call eax
			mov ecx, [ebp-0x4]
	}
	if(GameHack.Weapon.SetBrust){ // ini int di menu kamu
		__asm
		{
			mov eax,[dwSetBurst]
		}
	}
	__asm 
	{
		mov dword ptr[ebp-0x58],eax
			jmp [dwRet_Burst]
	}
}

void HookBurst()
{
	dwBurst = Address.Function.Brust;
	dwRet_Burst = Address.Function.RETBrust;
	hook((PDWORD)dwBurst, (PDWORD)hkBurst);
	_patchMEM((void*)(Address.Function.BypassBrust), (char*)"\xE9\x83\x00\x00\x00\x90", 6); //Bypass koneksi bermasalah burst
}

/*---------------------------------------- Declaration ForceAcess ----------------------------------------------------*/
static BYTE Room, IsGM = 0;
__declspec (naked) void ForceAcess() {
	{	
		__asm {
			push 0
				push 0
				lea ecx, IsGM
				push ecx
				jmp Address.Function.RETgetEnteredServerX
		}
	}
}

char PlayerSelectNickname[33] = {0};
bool CallerNoRecoil;
void DoHack()
{	
	//==============================================================================================================================================
	/*if(FeatureEngine->_get("GameHack.Player.WallShot")->_val())EnableWallShot();
	else DisableWallShot();*/

	//==============================================================================================================================================
	if(IsInBattle()){
		if(FeatureEngine->_get("GameHack.Weapon.NET_FIRE")->_val() && !pGameContext->getUserDeath(pGameContext->getMySlotIdx())){
			if(LocalChara->GetSlotWeapon() == Primary || LocalChara->GetSlotWeapon() == Secondary){
				D3DXVECTOR3 vMe, vEnemy;
				CWeaponGrenade* pGrenade = (CWeaponGrenade*)(LocalChara->getGameCharaWeaponContext()->getCurrentWeapon());
				for(int iSlot = 0; iSlot <= 16; iSlot++){
					if(IsAliveDeath(iSlot)){
						if(GetUserBone(vMe, 7, pGameContext->getMySlotIdx())){
							if(GetUserBone(vEnemy, 7, iSlot)){
								pGrenade->NET_Fire(&vMe, &vEnemy);
								pGrenade->doFire();
								pGrenade->doLineCollision(&vMe, &vEnemy, cTeamFind(iSlot));
		}}}}}}
	}

	//==============================================================================================================================================
	if(IsInBattle())
	{
		CGameCharaBase* LocalChara = pGameCharaManager->getLocalChara();
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Player.Reborn")->_val() && !LocalChara->isAlive() && IsKeyboardKeyDownOnce(DIK_C))pGameContext->setEvent(EventCode.Respawn, NULL, NULL, NULL, NULL, NULL);
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Player.FreeMove")->_val()){
			_patchPTR((AddyEngine->GetAddyValueByKey("GameContext.Base") - 0x28), 0x44, 0x18, 0xDC, 0x04); 
		}
		//==============================================================================================================================================
		if(IsKeyPressed(VK_END, 0)&1)
		{
			LocalChara->eventFall(200);
		}
		//==============================================================================================================================================
		if(GameHack.Player.HookMoveSpeed)
		{
			MakeJMP((PBYTE)WeaponBase.Function.GetMoveSpeed, (DWORD)GetMoveSpeed, 5);
		}
		//==============================================================================================================================================
		int count = 0;
		for(int i = 0; i <= 15; i+=2)
		{
			if(pGameContext->getMySlotIdx() == i)continue;
			if(pGameCharaManager->isValidChara(i)){
				MoptVote[count] = (char*)pGameContext->getNickForSlot(i);
				count++;
			}
		}
		for(int i = 1; i <= 15; i+=2)
		{
			if(pGameContext->getMySlotIdx() == i)continue;
			if(pGameCharaManager->isValidChara(i)){
				(char*)pGameContext->getNickForSlot(i);
				count++;
			}
		}
		VoteMenuIdx = count;

		if(IsKeyboardKeyDownOnce(DIK_DELETE)){
			FeatureEngine->_get("GameHack.Misc.KickPlayer")->_toggle();
			strcpy(PlayerSelectNickname, MoptVote[FeatureEngine->_get("GameHack.Misc.KickPlayerSelector")->_val()]);
		}
		if(FeatureEngine->_get("GameHack.Misc.KickPlayer")->_val())
		{
			DWORD dwIndexToKick = pGameCharaManager->getCharaByNickname(PlayerSelectNickname)->getCharaNetIndex();
			if(dwIndexToKick != -1){
				static DWORD dwTick = NULL;
				if(dwTick <= GetTickCount()){
					pGameContext->setEvent(EventCode.Whisper, PlayerSelectNickname, "V.I.P XenonProject | CyberCrimeHack™ Cheater", NULL, NULL, NULL);
					dwTick = GetTickCount() + 2000;
				}
			}
			else FeatureEngine->_get("GameHack.Misc.KickPlayer")->_disable();
		}
		//==============================================================================================================================================
		static bool bSavePosFastKiller = false;
			if(FeatureEngine->_get("GameHack.Brutal.FastKiller")->_val()){
				*(DWORD*)(LocalChara->getGameCharaWeaponContext()->getCurrentWeapon() + 0x648) = 100;

				if(LocalChara->isAlive() ){
					LocalChara->eventFall(200);
					bSavePosFastKiller = false;
				}
				else {

					static D3DXVECTOR3 pMySavePos;
					if(bSavePosFastKiller == false){
						LocalChara->setCharaWeapon(0, _WeaponValue(803007026).WeaponType(), _WeaponValue(803007026).WeaponIndex());
						pMySavePos = LocalChara->getGameCharaBoneContext()->getBonePosition(5);
						bSavePosFastKiller = true;
					}
					CWeaponGrenade* pGrenade = (CWeaponGrenade*)(LocalChara->getGameCharaWeaponContext()->getCurrentWeapon());
					for(int i = 0; i <= 15; i++){
						CGameCharaBase* Target = pGameCharaManager->getCharaByNetIdx(i);
						if(Target == NULL || Target->isAlive() == false || Target->isEnemy() == false || Target->isLocal() == true)continue;
						Target->setInvicibleTime(0.0f);
						DWORD OptTeam = 2;
						D3DXVECTOR3 AimTarget = Target->getGameCharaBoneContext()->getBonePosition(5);
						if(pGameContext->isRedTeam(Target->getCharaNetIndex()))OptTeam = 1;
						for(int i = 0; i <= 12; i++){
							i3CollideeLine GrenadeLine;
							i3CollideeLine_Initialize(&GrenadeLine);
							i3CollideeLine_SetStart(&GrenadeLine,&LocalChara->getGameCharaBoneContext()->getBonePosition(5));
							i3CollideeLine_SetEnd(&GrenadeLine,&Target->getGameCharaBoneContext()->getBonePosition(5));
							LocalChara->getGameCharaWeaponContext()->getCurrentWeapon()->doFire();
							pGrenade->doLineCollision(&AimTarget, &pMySavePos, OptTeam);
							pGrenade->doLineCollision(&AimTarget, &pMySavePos, OptTeam);
							pGrenade->doLineCollision(&AimTarget, &pMySavePos, OptTeam);
						
							pGrenade->onHitCharaByExplosion(Target, 0x22, &GrenadeLine.vDir, &GrenadeLine.vStart);
							pGrenade->onHitCharaByExplosion(Target, 0x22, &GrenadeLine.vDir, &GrenadeLine.vStart);
							pGrenade->onHitCharaByExplosion(Target, 0x22, &GrenadeLine.vDir, &GrenadeLine.vStart);
							pGrenade->onHitCharaByExplosion(Target, 0x22, &GrenadeLine.vDir, &GrenadeLine.vStart);
							pGrenade->onHitCharaByExplosion(Target, 0x22, &GrenadeLine.vDir, &GrenadeLine.vStart);
							pGrenade->onHitCharaByExplosion(Target, 0x22, &GrenadeLine.vDir, &GrenadeLine.vStart);
					
						}
					}
				}
			} else bSavePosFastKiller = false;
	
	//==============================================================================================================================================
	static bool bSavePosHealthSupport = false;
		if(FeatureEngine->_get("GameHack.Special.HealthSupport")->_val())
		{
			*(DWORD*)(LocalChara->getGameCharaWeaponContext()->getCurrentWeapon() + 0x648) = 10;

			if(LocalChara->isAlive()){
				LocalChara->eventFall(200);
				bSavePosHealthSupport = false;
			}
			else {

				static D3DXVECTOR3 pMySavePos;
				if(bSavePosHealthSupport == false){
					LocalChara->setCharaWeapon(0, _WeaponValue(904007014).WeaponType(), _WeaponValue(904007014).WeaponIndex());
					pMySavePos = LocalChara->getGameCharaBoneContext()->getBonePosition(5);
					bSavePosHealthSupport = true;
				}
				CWeaponGrenade* pGrenade = (CWeaponGrenade*)(LocalChara->getGameCharaWeaponContext()->getCurrentWeapon());
				static DWORD dwTick = NULL;
				if(dwTick <= GetTickCount()){
					for(int i = 0; i <= 15; i++){
						CGameCharaBase* Target = pGameCharaManager->getCharaByNetIdx(i);
						if(Target == NULL)continue; if(Target->isEnemy() == true)continue; if(Target->isAlive() == false)continue; if(Target->isLocal() == true)continue;
						if(Target->getCurHP() < 10)continue;
						Target->setInvicibleTime(0.0f);
						DWORD OptTeam = 2;
						D3DXVECTOR3 AimTarget = Target->getGameCharaBoneContext()->getBonePosition(5);
						if(pGameContext->isRedTeam(Target->getCharaNetIndex()))OptTeam = 1;
						i3CollideeLine GrenadeLine;
						i3CollideeLine_Initialize(&GrenadeLine);
						i3CollideeLine_SetStart(&GrenadeLine,&LocalChara->getGameCharaBoneContext()->getBonePosition(5));
						i3CollideeLine_SetEnd(&GrenadeLine,&Target->getGameCharaBoneContext()->getBonePosition(5));
						pGrenade->onHitCharaByExplosion(Target, 0x22, &GrenadeLine.vDir, &GrenadeLine.vStart);
						pGrenade->doLineCollision(&AimTarget, &pMySavePos, OptTeam);
						pGameUDPHandler->WriteGameEvent_Fire(LocalChara, &AimTarget, pGrenade);

					}
					dwTick = GetTickCount() + 75;
				}
			}
		} else bSavePosHealthSupport = false;
		
		//==============================================================================================================================================
		}
		else {
			FeatureEngine->_get("GameHack.Player.FreeMove")->_disable();
			FeatureEngine->_get("GameHack.Misc.KickPlayer")->_disable();
			FeatureEngine->_get("GameHack.Misc.KickPlayerSelector")->_disable();
			MoptVote[0] = "Off";
		}
		//==============================================================================================================================================
	if(IsInBattle()){
		CGameCharaBase* LocalChara = pGameCharaManager->getLocalChara();
	}
	//==============================================================================================================================================
	if(IsInBattle()){
		static bool bSavePosHealth = false;
		if(FeatureEngine->_get("GameHack.Special.HealthAbsorber")->_val())
		{
			*(DWORD*)(LocalChara->getGameCharaWeaponContext()->getCurrentWeapon() + 0x648) = 100;
			if(LocalChara->isAlive())
			{
				LocalChara->eventFall(200);
				bSavePosHealth = false;
			}else{
				static D3DXVECTOR3 pMySavePos;
				if(!LocalChara->isAlive())
				{
					if(bSavePosHealth == false)
					{
						LocalChara->setCharaWeapon(0, _WeaponValue(803007026).WeaponType(), _WeaponValue(803007026).WeaponIndex());
						pMySavePos = LocalChara->getGameCharaBoneContext()->getBonePosition(5);
						bSavePosHealth = true;
					}
				}
				CWeaponGrenade* pGrenade = (CWeaponGrenade*)(LocalChara->getGameCharaWeaponContext()->getCurrentWeapon());
				if(!LocalChara->isAlive())
				{
					for(int i = 0; i <= 16; i++)
					{
						CGameCharaBase* Chara = pGameCharaManager->getCharaByNetIdx(i);
						if(Chara)
						{
							if(Chara->isEnemy() == false)continue;
							if(Chara->getCurHP_Real() > 90.0f)
							{
								if(Chara->getCurHP() > 90.0f)
								{
									if(Chara->getCurHP_Real() > 90.0f)
									{
										static DWORD dwSedot = NULL;
										if(dwSedot <= GetTickCount())
										{
											CGameCharaBase* Target = pGameCharaManager->getCharaByNetIdx(i);
											if(Target == NULL || Target->isAlive() == false || Target->isEnemy() == false || Target->isLocal() == true)continue;
											Target->setInvicibleTime(0.0f);
											DWORD OptTeam = 2;
											D3DXVECTOR3 AimTarget = Target->getGameCharaBoneContext()->getBonePosition(5);
											if(pGameContext->isRedTeam(Target->getCharaNetIndex()))OptTeam = 1;
											i3CollideeLine GrenadeLine;
											i3CollideeLine_Initialize(&GrenadeLine);
											i3CollideeLine_SetStart(&GrenadeLine,&LocalChara->getGameCharaBoneContext()->getBonePosition(5));
											i3CollideeLine_SetEnd(&GrenadeLine,&Target->getGameCharaBoneContext()->getBonePosition(5));
											if(Chara->getCurHP_Real() > 25)
											{
												if(Chara->getCurHP() > 25)
												{
													if(Chara->getCurHP_Real() > 25)
													{
														pGrenade->doLineCollision(&AimTarget, &pMySavePos, OptTeam);
														pGrenade->onHitCharaByExplosion(Target, 0x22, &GrenadeLine.vDir, &GrenadeLine.vStart);
													}
												}
											}
											dwSedot = GetTickCount() + 0x001;
										}
									}
								}
							}else{}
						}
					}
				}
			}
		}else bSavePosHealth = false;
	}
	//==============================================================================================================================================
	if(IsInBattle() && pGameCharaManager->getLocalChara() && pGameCharaManager->getLocalChara()->isAlive()){
		//==============================================================================================================================================
		CGameCharaBase* LocalChara = pGameCharaManager->getLocalChara();
		MyCurrentWeaponIndex = LocalChara->getGameCharaWeaponContext()->getCurrentWeaponIndex();
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Weapon.QuickChange")->_val()){
			CGameCharaAnimContext* pMyCharaAnimContext = LocalChara->getGameCharaAnimContext();
			if(pMyCharaAnimContext > NULL){
				i3AIContext* pMyCharai3AIContext = pMyCharaAnimContext->geti3AIContext();
				if(pMyCharai3AIContext > NULL){
					ModifyTargetBase[0] = (DWORD)pMyCharai3AIContext;
				} else ModifyTargetBase[0] = NULL;
			}else ModifyTargetBase[0] = NULL;
		}else ModifyTargetBase[0] = NULL;
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Weapon.NoRecoil")->_val() == 1){
			if(CallerNoRecoil == false)
				_patchMEM((void*)WeaponBase.Function.GetOneVertEnable,0xFF);		_patchMEM((void*)WeaponBase.Function.GetOneHorzEnable,0xFF);
				_patchMEM((void*)WeaponBase.Function.GetRecoilHorzCount,0xFF);		_patchMEM((void*)WeaponBase.Function.GetRecoilVertCount,0xFF);
				//WriteHook((void*)WeaponBase.Function.ReadWeaponInfo,(void*)(PBYTE)"\xD9\x45\xFF",3);
				CallerNoRecoil = true;
		}
		if (FeatureEngine->_get("GameHack.Weapon.NoRecoil")->_val() == 0){
			if(CallerNoRecoil == true) 
				_patchMEM((void*)WeaponBase.Function.GetOneVertEnable,0xFC);		_patchMEM((void*)WeaponBase.Function.GetOneHorzEnable,0xFC);
				_patchMEM((void*)WeaponBase.Function.GetRecoilHorzCount,0xFC);		_patchMEM((void*)WeaponBase.Function.GetRecoilVertCount,0xFC);
				//WriteHook((void*)WeaponBase.Function.ReadWeaponInfo,(void*)(PBYTE)"\xD9\x45\xF4",3);
				CallerNoRecoil = false;
		}
		if(FeatureEngine->_get("GameHack.Weapon.Accuracy")->_val())
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
		if(FeatureEngine->_get("GameHack.Player.PlantDefuse")->_val() && pGameContext->isRedTeam(pGameContext->getMySlotIdx()) == false){
			if(GetKeyboardPressState(DIK_E))
				pGameContext->getGameCharaMissionManager()->InstallBomb(true);
			else
				pGameContext->getGameCharaMissionManager()->UnInstallBomb(true);
		}
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Player.AutoHeadshot")->_val()){
			FeatureEngine->_get("GameHack.Assist.Mode")->_disable();
			CGameCharaBase* MyTarget = LocalChara->getGameCharaCollisionContext()->GetCrosshairTarget();
			if(MyTarget > NULL)
				SetEndVector->SetTargetVector(MyTarget->getGameCharaBoneContext()->getBonePosition(BoneIndexSelector));
			else 
				SetEndVector->Disable();
		}
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Weapon.AutoFillSubAmmo")->_val()){
			CGameCharaWeaponContext* pMyCharaWeaponContext = LocalChara->getGameCharaWeaponContext();
			if(pMyCharaWeaponContext){
				CWeaponBase* pMyWeaponBase = pMyCharaWeaponContext->getCurrentWeapon();
				if(pMyWeaponBase && pMyCharaWeaponContext->getCurrentWeaponIndex() >= 0 && pMyCharaWeaponContext->getCurrentWeaponIndex() <= 1){
					if(pMyWeaponBase->getSubAmmoCount() < 1)
					{
						pMyWeaponBase->Reset();
					}
				}
			}
		}
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Weapon.AutoFire")->_val())
		{
			CGameCharaBase* MyTarget = LocalChara->getGameCharaCollisionContext()->GetCrosshairTarget();
			if(MyTarget > NULL)
				LocalChara->getGameCharaWeaponContext()->getCurrentWeapon()->doFire();
		}
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Weapon.AutoShot")->_val())
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
		if (FeatureEngine->_get("GameHack.Player.BugUp")->_val()){
			MemWrite((void *)(ModuleNX+Address.Function.BugDatar+0x2),(void*)(PBYTE)"\x33",1);
		} else if(!FeatureEngine->_get("GameHack.Player.BugUp")->_val()) {
			MemWrite((void *)(ModuleNX+Address.Function.BugDatar+0x2),(void*)(PBYTE)"\x34",1);
		}
		//==============================================================================================================================================
		/*if(FeatureEngine->_get("GameHack.Player.BugDatar")->_val()){
			MemWrite((void *)(ModuleNX+Address.Function.BugDatar),(int*)(PBYTE)"\xFF",1);
		} else if(!FeatureEngine->_get("GameHack.Player.BugDatar")->_val()){
			MemWrite((void *)(ModuleNX+Address.Function.BugDatar),(int*)(PBYTE)"\x89",1);
		}*/
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Player.BugUnyu")->_val() == 1){
			MemWrite((void *)(Address.Pointer.BugWeapon),(int*)(PBYTE)"\xC0",1);}
		else if(FeatureEngine->_get("GameHack.Player.BugUnyu")->_val() == 0){
			MemWrite((void *)(Address.Pointer.BugWeapon),(int*)(PBYTE)"\xBE",1);}
		if(FeatureEngine->_get("GameHack.Player.BugUnyu")->_val() == 2){
			MemWrite((void *)(Address.Pointer.BugWeapon),(int*)(PBYTE)"\xC1",1);}
		else if(FeatureEngine->_get("GameHack.Player.BugUnyu")->_val() == 0){
			MemWrite((void *)(Address.Pointer.BugWeapon),(int*)(PBYTE)"\xBE",1);}
		if(FeatureEngine->_get("GameHack.Player.BugUnyu")->_val() == 3){
			MemWrite((void *)(Address.Pointer.BugWeapon),(int*)(PBYTE)"\xC2",1);}
		else if(FeatureEngine->_get("GameHack.Player.BugUnyu")->_val() == 0){
			MemWrite((void *)(Address.Pointer.BugWeapon),(int*)(PBYTE)"\xBE",1);}
		if(FeatureEngine->_get("GameHack.Player.BugUnyu")->_val() == 4){
			MemWrite((void *)(Address.Pointer.BugWeapon),(int*)(PBYTE)"\xC3",1);}
		else if(FeatureEngine->_get("GameHack.Player.BugUnyu")->_val() == 0){
			MemWrite((void *)(Address.Pointer.BugWeapon),(int*)(PBYTE)"\xBE",1);}
		if(FeatureEngine->_get("GameHack.Player.BugUnyu")->_val() == 5){
			MemWrite((void *)(Address.Pointer.BugWeapon),(int*)(PBYTE)"\xC4",1);}
		else if(FeatureEngine->_get("GameHack.Player.BugUnyu")->_val() == 0){
			MemWrite((void *)(Address.Pointer.BugWeapon),(int*)(PBYTE)"\xBE",1);}
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Brutal.AutoKiller")->_val()){
			FeatureEngine->_get("GameHack.Assist.Mode")->_disable();
			for(int i = 0; i <= 15; i++){
				CGameCharaBase* Target = pGameCharaManager->getCharaByNetIdx(i);
				if(Target == NULL || Target->isAlive() == false || Target->isEnemy() == false || Target->isLocal() == true || Target->isVisible(BoneIndexSelector) == false)continue;
				DWORD OptTeam = 2;
				D3DXVECTOR3 AimTarget = Target->getGameCharaBoneContext()->getBonePosition(BoneIndexSelector);
				AimTarget.y += 0.1f;
				if(pGameContext->isRedTeam(Target->getCharaNetIndex()))OptTeam = 1;
				if(LocalChara->getGameCharaWeaponContext()->getCurrentWeaponIndex() == 2){
					SetEndVector->SetTargetVector(AimTarget);
					LocalChara->getGameCharaWeaponContext()->getCurrentWeapon()->doFire();
					SetEndVector->Disable();
				}
				else {
					LocalChara->getGameCharaWeaponContext()->getCurrentWeapon()->doLineCollision(&LocalChara->getGameCharaBoneContext()->getBonePosition(5), &AimTarget, OptTeam);
					LocalChara->getGameCharaWeaponContext()->getCurrentWeapon()->doFire();
				}
			}
		}
		//==============================================================================================================================================
		/*if(FeatureEngine->_get("GameHack.Brutal.ExplosiveKiller")->_val())
		{
			*(DWORD*)(LocalChara->getGameCharaWeaponContext()->getCurrentWeapon() + 0x648) = 10;

				if(LocalChara->getGameCharaWeaponContext()->getCurrentWeaponIndex() == 3){
					CWeaponGrenade* pGrenade = (CWeaponGrenade*)(LocalChara->getGameCharaWeaponContext()->getCurrentWeapon());
					for(int i = 0; i <= 15; i++){
						CGameCharaBase* Target = pGameCharaManager->getCharaByNetIdx(i);
						if(Target == NULL || Target->isAlive() == false || Target->isEnemy() == false || Target->isLocal() == true)continue;
						if(Target->getCurHP() < 10)continue;
						Target->setInvicibleTime(0.0f);
						for(int x = 0; x < 8; x++){
							i3CollideeLine GrenadeLine;
							i3CollideeLine_Initialize(&GrenadeLine);
							i3CollideeLine_SetStart(&GrenadeLine,&LocalChara->getGameCharaBoneContext()->getBonePosition(5));
							i3CollideeLine_SetEnd(&GrenadeLine,&Target->getGameCharaBoneContext()->getBonePosition(5));
							pGrenade->onHitCharaByExplosion(Target, 0x22, &GrenadeLine.vDir, &GrenadeLine.vStart);
						}
					}

					if(pGameFramework->geti3InputMouse()->GetButtonState() == 2){
						if(pGrenadeKeyer == false){
							LocalChara->getGameCharaWeaponContext()->getCurrentWeapon()->Reset();
							pGrenadeKeyer = true;
						}
					}
					else {
						if(pGrenadeKeyer == true){
							pGrenadeKeyer = false;
						}
					}
				}
			}*/
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Player.Teleport")->_val()){
			if(IsKeyboardKeyDownOnce(DIK_F3)){
				for(int i = 0; i <= 15; i++){
					CGameCharaBase* Target = pGameCharaManager->getCharaByNetIdx(i);
					if(Target == NULL || Target->isAlive() == false || Target->isEnemy() == false || Target->isLocal() == true)continue;
					LocalChara->Cmd_Respawn(&Target->getGameCharaBoneContext()->getBonePosition(0));
				}
				for(int i = 0; i <= 15; i++){
					CGameCharaBase* Target = pGameCharaManager->getCharaByNetIdx(i);
					if(Target == NULL || Target->isAlive() == false || Target->isEnemy() == false || Target->isLocal() == true || Target->isVisible(0) == false)continue;
					DWORD OptTeam = 2;
					D3DXVECTOR3 AimTarget = Target->getGameCharaBoneContext()->getBonePosition(7);
					AimTarget.y += 0.1f;
					if(pGameContext->isRedTeam(Target->getCharaNetIndex()))OptTeam = 1;
					if(LocalChara->getGameCharaWeaponContext()->getCurrentWeaponIndex() == 2){
						/*SetEndVector->SetTargetVector(AimTarget);
						LocalChara->getGameCharaWeaponContext()->getCurrentWeapon()->doFire();
						SetEndVector->Disable();*/
					}
				}
			}
		}
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Weapon.SkipReload")->_val()){
			CGameCharaWeaponContext* pMyCharaWeaponContext = LocalChara->getGameCharaWeaponContext();
			if(pMyCharaWeaponContext > NULL){
				CWeaponBase* CurrentWeapon = pMyCharaWeaponContext->getCurrentWeapon(); 
				if(CurrentWeapon){
					i3AIContext* pMyCharai3AIContext = CurrentWeapon->geti3AIContext();
					if(pMyCharai3AIContext > NULL){
						ModifyTargetBase[1] = (DWORD)pMyCharai3AIContext;
					} else ModifyTargetBase[1] = NULL;
				} else ModifyTargetBase[1] = NULL;
			}else ModifyTargetBase[1] = NULL;
		}else ModifyTargetBase[1] = NULL;
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Weapon.FireSpeed")->_val())
			_patchPTR((unsigned long)LocalChara, (unsigned long)AddyEngine->GetAddyValueByKey(/*XFHPB.Pointer.FireSpeed*/XorStr<0xB1,24,0xFCC5E154>("\xE9\xF4\xFB\xE4\xF7\x98\xE7\xD7\xD0\xD4\xCF\xD9\xCF\x90\xF9\xA9\xB3\xA7\x90\xB4\xA0\xA3\xA3"+0xFCC5E154).s), 0x00);
		
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Player.AlwaysInvicible")->_val()){
			static DWORD dwTick = NULL;
			if(dwTick <= GetTickCount()){
				LocalChara->setInvicibleTime(4.0f);
				dwTick = GetTickCount() + 2000;
			}
		}
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Player.ResetWeapon")->_val())
		{
			if(IsKeyboardKeyDownOnce(DIK_V)){
				if(FeatureEngine->_get("GameHack.Player.ResetWeapon")->_val() == 1){
					pGameCharaManager->SetCharaWeaponSet(LocalChara, pGameContext->getNetCharaInfo(LocalChara->getCharaNetIndex()));
				}
				if(FeatureEngine->_get("GameHack.Player.ResetWeapon")->_val() == 2){
					LocalChara->getGameCharaWeaponContext()->getCurrentWeapon()->Reset();
				}
				/*if(FeatureEngine->_get("GameHack.Player.ResetWeapon")->_val() == 3){
					pGameCharaManager->SetCharaWeaponSetWithoutLock(LocalChara, pGameContext->getNetCharaInfo(LocalChara->getCharaNetIndex()));
				}*/
			}
		}
		//==============================================================================================================================================
		if(GameHack.Weapon.SetBrust)
		{
			switch(GameHack.Weapon.SetBrust)
			{
			case 1:
				dwSetBurst = 5;
				break;
			case 2:
				dwSetBurst = 10;
				break;
			case 3:
				dwSetBurst = 25;
				break;
			case 4:
				dwSetBurst = 50;
				break;
			case 5:
				dwSetBurst = 100;
				break;
			}
		}
		else dwSetBurst = 1;
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Weapon.RapidFire")->_val())
		{
			if(pGameFramework->geti3InputMouse()->GetButtonState() == 1){
				DWORD dwDelay = 0;
				switch(FeatureEngine->_get("GameHack.Weapon.RapidFire")->_val())
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
					LocalChara->getGameCharaWeaponContext()->getCurrentWeapon()->Reset();
					LocalChara->getGameCharaWeaponContext()->getCurrentWeapon()->doFire();
					dwTick = GetTickCount() + dwDelay;
				}
			}
		}
		//==============================================================================================================================================
		if(FeatureEngine->_get("GameHack.Brutal.ShieldBM")->_val())
		{
			if (IsKeyPressed(VK_HOME,1))
			{
				pGameCharaManager->RespawnChara(LocalChara->getCharaNetIndex());
			}
		}
		//==============================================================================================================================================
		/*if(FeatureEngine->_get("GameHack.Misc.KickAllPlayer")->_val())
		{
			static DWORD dwTick = NULL;
			if(dwTick <= GetTickCount()){
				pGameContext->setEvent(EventCode.GlobalChat, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@BY UNKNOWN@@@@@@@@@@@@@@", NULL, NULL, NULL, NULL);
				dwTick = GetTickCount() + 2000;
			}
		}*/
	}
}

void DoRoomHack()
{
	//==============================================================================================================================================
	if(FeatureEngine->_get("GameHack.Player.autoGM")->_val() == 1)
	{
		CTeam *pTeam		= (CTeam*)(pGameContext + GameContext.Pointer.MySlotIdx); 
		int MyTeam = GetTeamX(pTeam->iTeam);
			GM			*DualDinamic = (GM*)((pGameContext + GameContext.Pointer.getRankInfo)+ pTeam->iTeam * 0x2B);
			CNames		*pFake	     = (CNames*)((pGameContext + GameContext.Pointer.getNickForSlot) + pTeam->iTeam  * GameContext.Size.getNickForSlotSize);
			if(FeatureEngine->_get("GameHack.Player.autoGM")->_val() == 1)
			{
				DualDinamic->iRank = 0x36;
				DualDinamic->iHack = 0xFFFFFF;
				strcpy(pFake->szNames,"{/COL}"); // max 16 angka/huruf
			}
	}
	if(FeatureEngine->_get("GameHack.Player.autoGM")->_val() == 2)
	{
		CTeam *pTeam		= (CTeam*)(pGameContext + GameContext.Pointer.MySlotIdx); 
		int MyTeam = GetTeamX(pTeam->iTeam);
			GM			*DualDinamic = (GM*)((pGameContext + GameContext.Pointer.getRankInfo)+ pTeam->iTeam * 0x2B);
			CNames		*pFake		 = (CNames*)((pGameContext + GameContext.Pointer.getNickForSlot) + pTeam->iTeam  * GameContext.Size.getNickForSlotSize);
			if(FeatureEngine->_get("GameHack.Player.autoGM")->_val() == 2)
			{
				DualDinamic->iRank = 0x35;
				DualDinamic->iHack = 0xFFFFFF;
				strcpy(pFake->szNames,"Xenon Project"); // max 16 angka/huruf
			}
	}
	//==============================================================================================================================================
	if(FeatureEngine->_get("GameHack.Misc.AntiKick")->_val())
	{
		_patchMEM((void*)(AddyEngine->GetAddyValueByKey(/*PhaseReadyRoom.Function.SelfRemoveFromRoom*/XorStr<0x65,43,0x36BAA349>("\x35\x0E\x06\x1B\x0C\x38\x0E\x0D\x09\x17\x3D\x1F\x1E\x1F\x5D\x32\x00\x18\x14\x0C\x10\x15\x15\x52\x2E\x1B\x13\xE6\xD3\xE7\xEE\xEB\xF3\xE3\xC1\xFA\xE6\xE7\xD9\xE3\xE2\xE3"+0x36BAA349).s)), (char*)"\xC3", 1);
	}else{
		_patchMEM((void*)(AddyEngine->GetAddyValueByKey(/*PhaseReadyRoom.Function.SelfRemoveFromRoom*/XorStr<0x65,43,0x36BAA349>("\x35\x0E\x06\x1B\x0C\x38\x0E\x0D\x09\x17\x3D\x1F\x1E\x1F\x5D\x32\x00\x18\x14\x0C\x10\x15\x15\x52\x2E\x1B\x13\xE6\xD3\xE7\xEE\xEB\xF3\xE3\xC1\xFA\xE6\xE7\xD9\xE3\xE2\xE3"+0x36BAA349).s)), (char*)"\x55", 1);
	}
	//==============================================================================================================================================
	if(FeatureEngine->_get("GameHack.Player.SkillUp")->_val())
	{
		pGameContext->setRankValue(pGameContext->getMySlotIdx(), 0x35);
	}
	//==============================================================================================================================================
	if(FeatureEngine->_get("GameHack.Misc.AutoInviteRoom")->_val() && !IsInBattle())
	{
		static DWORD dwTick = NULL;
		if(dwTick <= GetTickCount()){

			pGameContext->setEvent(EventCode.GetLobbyUserList, NULL, NULL, NULL, NULL, NULL);
			for(int i = 0; i < 8; i++){
				pGameContext->SetInviteUser(i);
			}
			pGameContext->setEvent(EventCode.SendInviteUser, NULL, NULL, NULL, NULL, NULL);//0x85

			dwTick = GetTickCount() + 500;
		}
	}
	//==============================================================================================================================================
	if(FeatureEngine->_get("GameHack.Misc.BypassRoomPassword")->_val())
	{
		IsGM = 1; 
	    MakeJMP((PBYTE)Address.Function.getEnteredServerX, (DWORD)ForceAcess, 0x4); 
	}
	//==============================================================================================================================================
	if(FeatureEngine->_get("GameHack.Misc.BypassServerFull")->_val() && !IsInBattle())
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
}

typedef void (__thiscall* tSetEvent)(void *p, int, const void*, const void*,const void*, const char*, int);
tSetEvent oSetEvent;
void __fastcall hkSetEvent(void *p, void *Unknown, int a1, const void* a2, const void* a3,const void* a4, const char* a5, int a6)
{
	if(DebugMode == true)
	{
		sprintf(LastEvent, "void __thiscall CGameContext::SetEvent(int, const void*, const void*,const void*, const char*, int)\na1: 0x%X\n%s\n%s\n%s\n%s\na6: 0x%X", a1, hexDump("a2", (void*)a2, 0x20).c_str(), hexDump("a3", (void*)a3, 0x20).c_str(), hexDump("a4", (void*)a4, 0x20).c_str(), hexDump("a5", (void*)a5, 0x20).c_str(), a6);
		myFunctionLog << LastEvent << endl;
	}

	if(FeatureEngine->_get("GameHack.Brutal.ShieldBM")->_val())
	{
		if(a1 == EventCode.Respawn)
		{
			return;
		}
	}

	/*if(FeatureEngine->_get("GameHack.Misc.BypassRoomPassword")->_val())
	{
		if(a1 == EventCode.JoinRoom && a2 == NULL){
			BYTE UnRoom = 1;
			a2 = &UnRoom;
		}
	}*/
	return oSetEvent(p, a1, a2, a3, a4, a5, a6); 
}

void __fastcall SetEventHack()
{
	__try{
		oSetEvent = (tSetEvent)DetourFunction((PBYTE)(AddyEngine->GetAddyValueByKey("GameContext.Function.setEvent")),(PBYTE)hkSetEvent,10);
	}__except (EXCEPTION_EXECUTE_HANDLER){}
}

/*---------------------------------------- Declaration Anti DC Enemy ----------------------------------------------------*/
typedef void (__thiscall* tPutStringBuffer)(void *p, const char*, unsigned short);
tPutStringBuffer oPutStringBuffer;

typedef void (__thiscall* tPutStringBackupBuffer)(void *p, const char*);
tPutStringBackupBuffer oPutStringBackupBuffer;

typedef void (__thiscall* tPutHistory)(void *p, char*, int);
tPutHistory oPutHistory;

void __fastcall hkPutHistory(void *p, void *Unknown, char* Text, int a2)
{
	if(strlen(Text) >= 120) // Stop jika teks lebih dari 120 karakter
	{
		return;
	}

	return oPutHistory(p, Text, a2);
}

void __fastcall hkPutStringBuffer(void *p, void *Unknown, const char* Text, unsigned short a2)//ASCII "void __thiscall CGameChatBox::_PutStringBuffer(const char *,unsigned short)"
{
	if(strlen(Text) >= 120) // Stop jika teks lebih dari 120 karakter
	{
		return;
	}
	return oPutStringBuffer(p, Text, a2);
}

void __fastcall hkPutStringBackupBuffer(void *p, void *Unknown, const char* Text)
{
	if(strlen(Text) >= 120) // Stop jika teks lebih dari 120 karakter
	{
		return;
	}
	return oPutStringBackupBuffer(p, Text);
}

void ChatEventHack()
{
	oPutStringBuffer		= (tPutStringBuffer)		DetourB8((DWORD)(Address.Function.getPutString)			,(DWORD)hkPutStringBuffer		, 9);
	oPutHistory				= (tPutHistory)				DetourB8((DWORD)(Address.Function.getPutHistory)		,(DWORD)hkPutHistory			, 9);
	oPutStringBackupBuffer	= (tPutStringBackupBuffer)	DetourB8((DWORD)(Address.Function.getPutStringBackUp)	,(DWORD)hkPutStringBackupBuffer	, 9);
}

/*---------------------------------------- Declaration Replace Real ----------------------------------------------------*/
void Replace_Real()
{
	__try{
		if(IsInBattle() && pGameCharaManager->getLocalChara() && pGameCharaManager->getLocalChara()->isAlive()){
			//==============================================================================================================================================
			CGameCharaBase* LocalChara = pGameCharaManager->getLocalChara();
			MyCurrentWeaponIndex = LocalChara->getGameCharaWeaponContext()->getCurrentWeaponIndex();
			//==============================================================================================================================================
			if(FeatureEngine->_get("GameHack.Selector.Damage")->_val()){
				if(IsKeyPressed(VK_LBUTTON,100)){
					CGameCharaBase* MyTarget = LocalChara->getGameCharaCollisionContext()->GetCrosshairTarget();
					if(MyTarget > NULL)
						LocalChara->getGameCharaWeaponContext()->getCurrentWeapon()->doFire();
				}
			}
			//==============================================================================================================================================
			if(FeatureEngine->_get("GameHack.Selector.Assault")->_val()){
				FeatureEngine->_get("GameHack.Selector.Damage")->_enable();
				for (int i = 0; i <=16;i++)
					if(IsKeyboardKeyDownOnce(DIK_F2))
						switch(FeatureEngine->_get("GameHack.Selector.Assault")->_val())
					{
						case 1: LocalChara->SetCharaWeapon(Primary,100003062); break; /*FAMAS G2 Comman do E-Sport*/	case 2: LocalChara->SetCharaWeapon(Primary,100003068); break; /*AK-47 F.C Red*/
						case 3: LocalChara->SetCharaWeapon(Primary,100003039); break; /*AK SOPMOD D*/					case 4: LocalChara->SetCharaWeapon(Primary,100003028); break; /*AUG A3 EV*/
						case 5: LocalChara->SetCharaWeapon(Primary,100003042); break; /*M4 SR-16 Lv1*/					case 6: LocalChara->SetCharaWeapon(Primary,100003043); break; /*M4 SR-16 Lv2*/
						case 7: LocalChara->SetCharaWeapon(Primary,100003044); break; /*M4 SR-16 Lv3*/					case 8: LocalChara->SetCharaWeapon(Primary,100003045); break; /*M4 SR-16 F.C*/
						case 9: LocalChara->SetCharaWeapon(Primary,100003063); break; /*AUG A3 E-Sport*/				case 10: LocalChara->SetCharaWeapon(Primary,0x5F5ED99); break; /*AUG A3 Love*/
						case 11: LocalChara->SetCharaWeapon(Primary,0x5F5EDB4); break; /*AK SOPMOD Sakura*/				case 12: LocalChara->SetCharaWeapon(Primary,0x5F5ED6A); break; /*AK Sopmod Medical*/
						case 13: LocalChara->SetCharaWeapon(Primary,100003257); break; /*AUG A3 PBGI 2015*/				case 14: LocalChara->SetCharaWeapon(Primary,0x5F5EDB9); break; /*AUG A3 Best*/
						case 15: LocalChara->SetCharaWeapon(Primary,0x5F5EDB6); break; /*Watergun 2015*/				case 16: LocalChara->SetCharaWeapon(Primary,0x5F5EDB8); break; /*AUG A3 Sky*/
						case 17: LocalChara->SetCharaWeapon(Primary,0x5F5EDB0); break; /*AUG A3 Serpent*/				case 18: LocalChara->SetCharaWeapon(Primary,0x5F5EDB1); break; /*AUG A3 Silencer*/
						case 19: LocalChara->SetCharaWeapon(Primary,0x5F5EDB3); break; /*AUG A3 Sakura*/				case 20: LocalChara->SetCharaWeapon(Primary,0x5F5EDB5); break; /*AUG A3 Lebaran*/
						case 21: LocalChara->SetCharaWeapon(Primary,0x5F5EDB7); break; /*AUG A3 GRS*/					case 22: LocalChara->SetCharaWeapon(Primary,0x5F5EDAA); break; /*SC 2010 X-FAMAS*/
						case 23: LocalChara->SetCharaWeapon(Primary,0x5F5ED87); break; /*AUG A3 Green*/					case 24: LocalChara->SetCharaWeapon(Primary,0x5F5EDC7); break; /*AUG A3 Aruna*/
						case 25: LocalChara->SetCharaWeapon(Primary,100003072); break; /*AK-47 OLD SPEC*/				case 26: LocalChara->SetCharaWeapon(Primary,100003049); break; /*FAMAS G2*/
						case 27: LocalChara->SetCharaWeapon(Primary,100003050); break; /*FAMAS G2 Commando*/			case 28: LocalChara->SetCharaWeapon(Primary,100003051); break; /*FAMAS G2 Siniper*/
						case 29: LocalChara->SetCharaWeapon(Primary,100003052); break; /*FAMAS G2 M203*/				case 30: LocalChara->SetCharaWeapon(Primary,100003064); break; /*FAMAS G2 Comman do G*/
					}
			}
			//==============================================================================================================================================
			if(FeatureEngine->_get("GameHack.Selector.SMG")->_val()){
				FeatureEngine->_get("GameHack.Selector.Damage")->_enable();
				for (int i = 0; i <=16;i++)
					if(IsKeyboardKeyDownOnce(DIK_F2))
						switch(FeatureEngine->_get("GameHack.Selector.SMG")->_val())
					{
						case 1: LocalChara->SetCharaWeapon(Primary,200004050); break; /*Kriss S.V E-Sport*/				case 2: LocalChara->SetCharaWeapon(Primary,200004029); break; /*P90 ext D*/
						case 3: LocalChara->SetCharaWeapon(Primary,200018005); break; /*Dual Mini-Uzi*/					case 4: LocalChara->SetCharaWeapon(Primary,200004032); break; /*P90 M.C. D*/
						case 5: LocalChara->SetCharaWeapon(Primary,200018009); break; /*Dual Micro Mini Uzi Silencer*/	case 6: LocalChara->SetCharaWeapon(Primary,200004034); break; /*M4 CQB-R Lv1*/
						case 7: LocalChara->SetCharaWeapon(Primary,200004035); break; /*M4 CQB-R Lv2*/					case 8: LocalChara->SetCharaWeapon(Primary,200004036); break; /*M4 CQB-R Lv3*/
						case 9: LocalChara->SetCharaWeapon(Primary,200004013); break; /*Kriss S.V.*/					case 10: LocalChara->SetCharaWeapon(Primary,0xBEBD272); break; /*P90 Ext Mech*/
						case 11: LocalChara->SetCharaWeapon(Primary,0xBEBD29B); break; /*OA-93*/						case 12: LocalChara->SetCharaWeapon(Primary,0xBEBD24A); break; /*Kriss Love*/
					}
			}
			//==============================================================================================================================================
			if(FeatureEngine->_get("GameHack.Selector.Sniper")->_val()){
				FeatureEngine->_get("GameHack.Selector.Damage")->_enable();
				for (int i = 0; i <=16;i++)
					if(IsKeyboardKeyDownOnce(DIK_F2))
						switch(FeatureEngine->_get("GameHack.Selector.Sniper")->_val())
					{
						case 1: LocalChara->SetCharaWeapon(Primary,300005032); break; /*Barrett M82A1*/					case 2: LocalChara->SetCharaWeapon(Primary,300005030); break; /*CheyTac M200 Rusia*/
						case 3: LocalChara->SetCharaWeapon(Primary,300005023); break; /*Rangemaster 7,62 STBY*/			case 4: LocalChara->SetCharaWeapon(Primary,300005033); break; /*L115A1 E-Sport*/
						case 5: LocalChara->SetCharaWeapon(Primary,300005020); break; /*M4 SRP Lv3*/					case 6: LocalChara->SetCharaWeapon(Primary,300005031); break; /*Winchester M70*/
						case 7: LocalChara->SetCharaWeapon(Primary,300005021); break; /*Rangemaster .338*/				case 8: LocalChara->SetCharaWeapon(Primary,300005022); break; /*Rangemaster 7,62*/
						case 9: LocalChara->SetCharaWeapon(Primary,300005036); break; /*L115A1 SE*/						case 10: LocalChara->SetCharaWeapon(Primary,0x11E1B703); break; /*Tacktitle*/
					}
			}
			//==============================================================================================================================================
			if(FeatureEngine->_get("GameHack.Selector.Shotgun")->_val()){
				FeatureEngine->_get("GameHack.Selector.Damage")->_enable();
				for (int i = 0; i <=16;i++)
					if(IsKeyboardKeyDownOnce(DIK_F2))
						switch(FeatureEngine->_get("GameHack.Selector.Shotgun")->_val())
					{
						case 1: LocalChara->SetCharaWeapon(Primary,400006021); break; /*M1887 SL*/						case 2: LocalChara->SetCharaWeapon(Primary,400006016); break; /*SPAS-15 SI. D*/
						case 3: LocalChara->SetCharaWeapon(Primary,400006019); break; /*Jackhammer*/					case 4: LocalChara->SetCharaWeapon(Primary,400006020); break; /*Kel-Tec KSG-15*/
						case 5: LocalChara->SetCharaWeapon(Primary,400006018); break; /*SPAS-15 MSC*/					case 6: LocalChara->SetCharaWeapon(Primary,400006042); break; /*Zombie Slayer*/
					}
			}
			//==============================================================================================================================================
			if(FeatureEngine->_get("GameHack.Selector.Secondary")->_val()){
				FeatureEngine->_get("GameHack.Selector.Damage")->_enable();
				for (int i = 0; i <=16;i++)
					if(IsKeyboardKeyDownOnce(DIK_F2))
						switch(FeatureEngine->_get("GameHack.Selector.Secondary")->_val())
					{
						case 1: LocalChara->SetCharaWeapon(Secondary,601002012); break; /*Colt Python D*/					case 2: LocalChara->SetCharaWeapon(Secondary,601002016); break; /*R.B SS8M + S 454*/
						case 3: LocalChara->SetCharaWeapon(Secondary,601002023); break; /*IMI Uzi 9 mm*/					case 4: LocalChara->SetCharaWeapon(Secondary,601002007); break; /*C. Python*/
						case 5: LocalChara->SetCharaWeapon(Secondary,601002013); break; /*R.B SS2M 454*/					case 6: LocalChara->SetCharaWeapon(Secondary,601002014); break; /*R.B SS5M 454*/
						case 7: LocalChara->SetCharaWeapon(Secondary,601002015); break; /*R.B SS8M 454*/
					}
			}
			//==============================================================================================================================================
			if(FeatureEngine->_get("GameHack.Selector.MachineGun")->_val()){
				FeatureEngine->_get("GameHack.Selector.Damage")->_enable();
				for (int i = 0; i <=16;i++)
					if(IsKeyboardKeyDownOnce(DIK_F2))
						switch(FeatureEngine->_get("GameHack.Selector.MachineGun")->_val())
					{
						case 1: LocalChara->SetCharaWeapon(Primary,500010001); break; /*MK.46 Ext*/						case 2: LocalChara->SetCharaWeapon(Primary,500010002); break; /*MK.46 S1.*/
						case 3: LocalChara->SetCharaWeapon(Primary,500010003); break; /*RPD*/							case 4: LocalChara->SetCharaWeapon(Primary,500010004); break; /*L86 LSW*/
					}
			}
		}
	}__except( EXCEPTION_EXECUTE_HANDLER ){}
}

/*---------------------------------------- Declaration Reset Abuse ----------------------------------------------------*/
bool FuncAbuse1=true;
void BypassAbuse()
{
	if(FuncAbuse1==true)
	{
		if(!IsInBattle())
		{
			static bool setAbuse = false;
			if(*(PDWORD)((DWORD)pGameContext+ GameContext.Function.ResetAbuseCounter3) != NULL) 
				setAbuse = true;
			else
				setAbuse = false;

			static DWORD dwTick = NULL;
			if(setAbuse == true)
			{
				if(dwTick == NULL)
				{
					*(PDWORD)((DWORD)pGameContext+ GameContext.Function.ResetAbuseCounter3)	= 1;
					dwTick =  GetTickCount() + 2000;
				}
				if(dwTick <= GetTickCount())
				{
					*(PDWORD)((DWORD)pGameContext+ GameContext.Function.ResetAbuseCounter3)	= 0;
					setAbuse = false;
					dwTick = NULL;
				}
			}
		}
	}
}

DWORD Hook_MouseMacro(void)
{
	while(true)
	{
		if(FeatureEngine->_get("GameHack.Weapon.MacroAllWeapon")->_val())
		{
			if(pGameFramework->geti3InputMouse()->GetButtonState() == 1)
			{
				keybd_event(0x33, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
				{
					Sleep(50);
				}
					keybd_event(0x33, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
					keybd_event(0x31, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
				{
					Sleep(50);
				}
				keybd_event(0x31, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
			}
		}
		Sleep(50);
	}
	return false;
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