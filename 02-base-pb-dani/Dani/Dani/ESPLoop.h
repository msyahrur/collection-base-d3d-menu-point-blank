//Created by DANI XCT / WA DANI IDI/MENU XXN PART 2
void DoESP(LPDIRECT3DDEVICE9 pDevice)
{
	if(IsInBattle()){
		for(int iSlot = 0; iSlot <= 16; iSlot++){
			CNames *pNames = (CNames*)((pGameContext + ResultPTRName) + iSlot * 0x21);
			CGameCharaBase* Chara = pGameCharaManager->getCharaByNetIdx(iSlot);
			if(Chara){
				if(Chara->isEnemy() == false)continue;
				if(Chara->isAlive() == false)continue;
				pDevice->GetViewport(&g_ViewPort);
				DWORD ScreenButtomY = g_ViewPort.Height;
				DWORD ScreenCenterX = g_ViewPort.Width/2;
				DWORD ScreenCenterY = g_ViewPort.Height/2;
				D3DXVECTOR3 Head = Chara->getGameCharaBoneContext()->getBonePosition(7);
				D3DXVECTOR3 Body = Chara->getGameCharaBoneContext()->getBonePosition(1);
				D3DXVECTOR3 ScreenHead;
				D3DXVECTOR3 ScreenHeadNames;
				D3DXVECTOR3 ScreenBodyHealth;
				if(pRenderContext->WorldToScreen(D3DXVECTOR3(Head.x, Head.y + 0.1f, Head.z),ScreenHead,pDevice) &&
					pRenderContext->WorldToScreen(D3DXVECTOR3(Head.x, Head.y + 0.5f, Head.z),ScreenHeadNames,pDevice) &&
					pRenderContext->WorldToScreen(D3DXVECTOR3(Body.x, Body.y - 0.8f, Body.z), ScreenBodyHealth, pDevice))
				{
					if(Feature.ESP.Bone)DrawPlayerBone(iSlot, Chara->getCurHP(), pDevice);
					if(Feature.ESP.Line)DrawESPLine(ScreenCenterX, ScreenButtomY, ScreenHead.x, ScreenBodyHealth.y-2, 1, Chara->getCurHP(), pDevice);
					if(Feature.ESP.NameTag)DrawStringC(g_pFont, ScreenHeadNames.x, ScreenHeadNames.y-15, Chara->getCurHP(), "%s (%d)", Chara->getNickname(), Chara->getCurHP(), pDevice);
					if(Feature.ESP.Health){HealthBar(ScreenBodyHealth.x-25, ScreenBodyHealth.y+5,Chara->getCurHP(),pDevice);}
					if(Feature.ESP.TagGM)
					{
						Feature.ESP.NameTag=0;
						char pName[33];
						sprintf_s(pName, "%s", pNames->szNames);
						DrawOutlineString(ScreenHeadNames.x,ScreenHeadNames.y-25, RED, DT_NOCLIP, g_pFont, pName, iSlot);
					}
				}
			}
		}
	}
}

void DisableAimAssist()
{
	if(bIsAimTargetValid == true)
	{
		SetEndVector->Disable();
		bIsAimTargetValid = false;
	}
}

void DoAimBullet(LPDIRECT3DDEVICE9 pDevice)
{
	if(IsInBattle())
	{
		D3DXVECTOR3 SelectionHead;
		D3DXVECTOR3 SelectionBody;
		pDevice->GetViewport(&g_ViewPort);
		CGameCharaBase* LocalChara = pGameCharaManager->getLocalChara();
		if(LocalChara && LocalChara->isAlive())
		{
			CGameCharaBase* TargetAim = pGameCharaManager->getCharaToAim();
			if(Feature.AIM.Bullet)
			{
				if(TargetAim){
					bIsAimTargetValid = true;
					D3DXVECTOR3 AimTargetHead = TargetAim->getGameCharaBoneContext()->getBonePosition(7);
					D3DXVECTOR3 AimTargetBody = TargetAim->getGameCharaBoneContext()->getBonePosition(5);
					AimTargetHead.y += 0.1f;
					AimTargetBody.y += 0.1f;
					switch(Feature.AIM.Bullet)
					{
					case 1: SetEndVector->SetTargetVector(AimTargetHead);
						break;
					case 2: SetEndVector->SetTargetVector(AimTargetBody);
						break;
					}
				} else DisableAimAssist();
			} else DisableAimAssist();
		} else DisableAimAssist();
	}
}

void DoAimReal(){
	if(IsInBattle()){
		if(Feature.AIM.Real)
		{
		Feature.AIM.Bullet=0;
		CGameCharaBase* MyTarget = pGameCharaBase->getGameCharaCollisionContext()->GetCrosshairTarget();
			switch(Feature.AIM.Real)
			{
				case 1: if(MyTarget > NULL)SetEndVector->SetTargetVector(MyTarget->getGameCharaBoneContext()->getBonePosition(7));
						else
					SetEndVector->Disable();
				break;
				case 2: if(MyTarget > NULL)SetEndVector->SetTargetVector(MyTarget->getGameCharaBoneContext()->getBonePosition(5));
						else
					SetEndVector->Disable();
				break;
			}
		}
	}
}