//CREATED BY SC0D3 Solusi Game No Di Indoneisa
void CallDoESP(IDirect3DDevice9 *pDevice)
{ 
	if(IsInBattle()){
		for (int iSlot = 0; iSlot < 16; iSlot++){
			CGameCharaBase* Chara = pGameCharaManager->getCharaByNetIdx(iSlot);
			if(Chara){
				if(Chara->isEnemy() == false)continue;
				if(Chara->isAlive() == false)continue;
				pDevice->GetViewport(&g_ViewPort);
				ScreenCenterX = g_ViewPort.Width/2;
				ScreenCenterY = g_ViewPort.Height/2;
				ScreenButtomY = g_ViewPort.Height;
				float ScreenCenterX = (g_ViewPort.Width /2.0f);
				float ScreenButtomY = (g_ViewPort.Height);
				D3DXVECTOR3 Head = Chara->getGameCharaBoneContext()->getBonePosition(7);
				D3DXVECTOR3 Body = Chara->getGameCharaBoneContext()->getBonePosition(5);
				D3DXVECTOR3 Foot = Chara->getGameCharaBoneContext()->getBonePosition(1);
				D3DXVECTOR3 ScreenHead;
				D3DXVECTOR3 ScreenBody;
				D3DXVECTOR3 ScreenFoot;
				D3DXVECTOR3 ScreenHeadNames;
				D3DXVECTOR3 ScreenHeadHealth;
				if( pRenderContext->WorldToScreen(D3DXVECTOR3(Head.x, Head.y + 0.1f, Head.z),ScreenHead,pDevice) &&
					pRenderContext->WorldToScreen(D3DXVECTOR3(Body.x, Body.y + 0.1f, Body.z),ScreenBody,pDevice) &&
					pRenderContext->WorldToScreen(D3DXVECTOR3(Foot.x, Foot.y + 0.1f, Foot.z),ScreenFoot,pDevice) &&
					pRenderContext->WorldToScreen(D3DXVECTOR3(Head.x, Head.y + 0.5f, Head.z),ScreenHeadNames,pDevice) &&
					pRenderContext->WorldToScreen(D3DXVECTOR3(Foot.x, Foot.y - 0.8f, Foot.z),ScreenHeadHealth,pDevice))
				{
					if(Visual.ESP.Bone)CallEspBone(iSlot,White);
					if(Visual.ESP.Head)FillRGB((float)ScreenHead.x, (float)ScreenHead.y, 2, 2, Red, pDevice);
					if(Visual.ESP.Line==1)DrawESPLine((float)ScreenCenterX, (float)ScreenButtomY, (float)ScreenHead.x, (float)ScreenFoot.y, 1, Chara->getCurHP(), pDevice);
					if(Visual.ESP.Line==2)DrawESPLine((float)ScreenCenterX, (float)ScreenCenterY, (float)ScreenHead.x, (float)ScreenBody.y, 1, Chara->getCurHP(), pDevice);
					if(Visual.ESP.Line==3)DrawESPLine((float)ScreenCenterX, (float)0, (float)ScreenHead.x, (float)ScreenHead.y, 1, Chara->getCurHP(), pDevice);
					if(Visual.ESP.Name)DrawStringC(g_pFont, ScreenHeadNames.x, ScreenHeadNames.y-15, Chara->getCurHP(), "%s - %dHP", Chara->getNickname(), Chara->getCurHP(), pDevice);
					if(Visual.ESP.Health==1)HealthBarnew((int)ScreenHeadHealth.x-25, (int)ScreenHeadHealth.y+5, Chara->getCurHP(), pDevice);
					if(Visual.ESP.Health==2)HealthEqui((int)ScreenHeadHealth.x-25, (int)ScreenHeadHealth.y+10, Chara->getCurHP(), pDevice);
					if(Visual.ESP.Health==3)HealthEqui2((int)ScreenHeadHealth.x-25, (int)ScreenHeadHealth.y+10, Chara->getCurHP(), pDevice);
					if(Visual.ESP.KillDeath)DrawKD((int)ScreenHeadNames.x-50.0, (int)ScreenHeadNames.y - 30, Red, "Kill : %d - Death : %d", pGameContext->getIndividualScore(iSlot)->Kill, pGameContext->getIndividualScore(iSlot)->Dead);
					if(Visual.ESP.Ping)PingServer((int)ScreenHeadHealth.x - 55, (int)ScreenHeadHealth.y+10, pGameContext->GetPing(iSlot), pDevice);
				}			
			}
		}
	}
}

bool GetAimAssistState()
{
	if(GameHack.Assist.Hotkey == 0)return true;
	if(GameHack.Assist.HotkeyMode == 0){
		switch(GameHack.Assist.Hotkey)
		{
		case 1:
			bAimState = GetKeyboardPressState(DIK_LCONTROL);
			break;
		case 2:
			bAimState = GetKeyboardPressState(DIK_LALT);
			break;
		case 3:
			bAimState = GetKeyboardPressState(DIK_LSHIFT);
			break;
		case 4:
			bAimState = GetKeyboardPressState(DIK_CAPSLOCK);
			break;
		case 5:
			bAimState = GetKeyboardPressState(DIK_TAB);
			break;
		}
	}
	else if (GameHack.Assist.Hotkey == 1){
		switch(GameHack.Assist.Hotkey)
		{
		case 1:
			if(IsKeyboardKeyDownOnce(DIK_LCONTROL))bAimState = !bAimState;
			break;
		case 2:
			if(IsKeyboardKeyDownOnce(DIK_LALT))bAimState = !bAimState;
			break;
		case 3:
			if(IsKeyboardKeyDownOnce(DIK_LSHIFT))bAimState = !bAimState;
			break;
		case 4:
			if(IsKeyboardKeyDownOnce(DIK_CAPSLOCK))bAimState = !bAimState;
			break;
		case 5:
			if(IsKeyboardKeyDownOnce(DIK_TAB))bAimState = !bAimState;
			break;
		}
	}
	return bAimState;
}

DWORD GetPlayerTarget(int Index)
{
	CGameCharaBase* pTarget = pGameCharaManager->getCharaByNetIdx(Index);
	if (pTarget->getGameCharaCollisionContext() && pTarget->getGameCharaCollisionContext()->getCrossHairTarget())
	{
		return pTarget->getGameCharaCollisionContext()->getCrossHairTarget();
	}
	return NULL;
}

bool bIsAimTargetValid = false;
void DisableAimAssist()
{
	if(bIsAimTargetValid == true){
		SetEndVector->Disable();
		bIsAimTargetValid = false;
	}
}

void CallDoAssist(LPDIRECT3DDEVICE9 pDevice)
{
	if(IsInBattle()){
		switch(GameHack.Assist.Target)
		{
		case 0:
			BoneIndexSelector = 7;
			break;
		case 1:
			BoneIndexSelector = 5;
			break;
		}
		CGameCharaBase* LocalChara = pGameCharaManager->getLocalChara();
		if(LocalChara && LocalChara->isAlive()){
			if(GameHack.Assist.Mode){
				if(GetAimAssistState()){
					CGameCharaBase* Target = pGameCharaManager->getCharaToAim();
					if(Target){
						bIsAimTargetValid = true;
							D3DXVECTOR3 AimTarget = Target->getGameCharaBoneContext()->getBonePosition(BoneIndexSelector);
							AimTarget.y += 0.1f;
						SetEndVector->SetTargetVector(AimTarget);
					} else DisableAimAssist();
				} else DisableAimAssist();
			} else DisableAimAssist();
		} else DisableAimAssist();
	} else DisableAimAssist();
}