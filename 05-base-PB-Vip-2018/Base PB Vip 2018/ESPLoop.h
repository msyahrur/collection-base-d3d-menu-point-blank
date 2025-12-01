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
#include "ESPFunctions.h"
#include "ESPTools.h"

void DoESP(LPDIRECT3DDEVICE9 pDevice)
{
	if(IsInBattle()){
		for(int i = 0; i <= 15; i++){
			CGameCharaBase* Chara = pGameCharaManager->getCharaByNetIdx(i);
			if(Chara){
				if(Chara->isEnemy() == false && FeatureEngine->_get("Visual.ESP.Team")->_val() == 0)continue;
				if(Chara->isAlive() == false)continue;

				D3DXVECTOR3 Head = Chara->getGameCharaBoneContext()->getBonePosition(7);
				D3DXVECTOR3 ScreenHead;
				D3DXVECTOR3 ScreenHeadNames;
				D3DXVECTOR3 ScreenHeadHealth;
				if( pRenderContext->WorldToScreen(D3DXVECTOR3(Head.x, Head.y + 0.1f, Head.z),ScreenHead,pDevice) &&
					pRenderContext->WorldToScreen(D3DXVECTOR3(Head.x, Head.y + 0.5f, Head.z),ScreenHeadNames,pDevice) &&
					pRenderContext->WorldToScreen(D3DXVECTOR3(Head.x, Head.y + 0.3f, Head.z),ScreenHeadHealth,pDevice))
				{
					if(FeatureEngine->_get("Visual.ESP.Name")->_val())DrawStringC(g_pFont,ScreenHeadNames.x,ScreenHeadNames.y-15,Chara->GetTeamColor(),/*%s - %dHP*/XorStr<0xCD,10,0xF438969D>("\xE8\xBD\xEF\xFD\xF1\xF7\xB7\x9C\x85"+0xF438969D).s, Chara->getNickname(), Chara->getCurHP());	
					if(FeatureEngine->_get("Visual.ESP.Head")->_val())FillRGB((float)ScreenHead.x, (float)ScreenHead.y, 4, 4,Chara->GetTeamColor(), pDevice);
					if(FeatureEngine->_get("Visual.ESP.Healthbar")->_val())HealthBar((int)ScreenHeadHealth.x - 25,(int)ScreenHeadHealth.y,Chara->getCurHP(),pDevice);
					
					if(FeatureEngine->_get("Visual.ESP.Line")->_val())DrawESPLine((float)ScreenCenterX,(float)ScreenCenterY,(float)ScreenHead.x,(float)ScreenHead.y,1,Chara->GetPlayerColor());
					
					if(FeatureEngine->_get("Visual.ESP.Bone")->_val())DrawPlayerBone(i,Chara->GetPlayerColor());
				}
			}
		}
	}
}

bool bIsAimTargetValid = false;
void DisableAimAssist()
{
	if(bIsAimTargetValid == true){
		SetEndVector->Disable();
		bIsAimTargetValid = false;
	}
}

void DoAimAssist(LPDIRECT3DDEVICE9 pDevice)
{
	if(IsInBattle()){
		
		switch(FeatureEngine->_get("GameHack.Assist.Target")->_val())
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
			if(FeatureEngine->_get("GameHack.Assist.Mode")->_val()){
				if(GetAimAssistState()){
					CGameCharaBase* Target = pGameCharaManager->getCharaToAim();
					if(Target){
						bIsAimTargetValid = true;
						D3DXVECTOR3 AimTarget = Target->getGameCharaBoneContext()->getBonePosition(BoneIndexSelector);
						AimTarget.y += 0.1f;
						if(FeatureEngine->_get("GameHack.Assist.Mode")->_val() == 1)SetEndVector->SetTargetVector(AimTarget);
					} else DisableAimAssist();
				} else DisableAimAssist();
			} else DisableAimAssist();
		} else DisableAimAssist();
	} else DisableAimAssist();
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