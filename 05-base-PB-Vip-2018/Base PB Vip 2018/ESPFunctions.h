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
float DistanceBetweenVector( D3DXVECTOR3 VecA, D3DXVECTOR3 VecB )
{
        return sqrt( ( ( VecA.x - VecB.x ) * ( VecA.x - VecB.x ) ) +
                 ( ( VecA.y - VecB.y ) * ( VecA.y - VecB.y ) ) +
                 ( ( VecA.z - VecB.z ) * ( VecA.z - VecB.z ) ) );
}

int GetTeam(int MyT)
{

	if(MyT % 2 == 0)return 0;
	else return 1;
	return -1;
}

bool GetUserBone(D3DXVECTOR3 &Out,int BoneIndex, int CharaIndex)
{

	if( pGameCharaManager->getCharaByNetIdx(CharaIndex) && 
		pGameCharaManager->getCharaByNetIdx(CharaIndex)->getGameCharaBoneContext() )
	{
		Out = pGameCharaManager->getCharaByNetIdx(CharaIndex)->getGameCharaBoneContext()->getBonePosition(BoneIndex);
		return true;
	}
	return false;
}

typedef void (__thiscall * ti3CollideeLine_Initialize)(i3CollideeLine* pLine);
ti3CollideeLine_Initialize i3CollideeLine_Initialize;

typedef void (__thiscall * ti3CollideeLine_SetStart)(i3CollideeLine* pLine, D3DXVECTOR3 *Value);
ti3CollideeLine_SetStart i3CollideeLine_SetStart;

typedef void (__thiscall * ti3CollideeLine_SetEnd)(i3CollideeLine* pLine, D3DXVECTOR3 *Value);
ti3CollideeLine_SetEnd i3CollideeLine_SetEnd;

void InitializeVisibleCheck()
{
	static bool bInitViscek = false;
	if(bInitViscek) return;
	HMODULE hScene = GetModuleHandle("i3SceneDx.dll");
	while(!hScene)Sleep(50);
	i3CollideeLine_Initialize = (ti3CollideeLine_Initialize)(DWORD)GetProcAddress(hScene,"??0i3CollideeLine@@QAE@XZ"); 
	i3CollideeLine_SetStart = (ti3CollideeLine_SetStart)(DWORD)GetProcAddress(hScene,"?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z");
	i3CollideeLine_SetEnd = (ti3CollideeLine_SetEnd)(DWORD)GetProcAddress(hScene,"?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z");
	bInitViscek = true;
}

bool GetPlayerVisibleStatus(int ActorIndex, int TargetIndex, int BoneTargetIndex)
{
	if(bEnableVisibleCheck == false) return true;
	i3CollideeLine Line;
	D3DXVECTOR3 vTarget, vLocal;

	GetUserBone(vLocal,5,ActorIndex);
	GetUserBone(vTarget,BoneTargetIndex,TargetIndex);

	vLocal.y += 0.1f;

	i3CollideeLine_Initialize(&Line);
	i3CollideeLine_SetStart(&Line,&vLocal);
	i3CollideeLine_SetEnd(&Line,&vTarget);

	i3PhysixResult* pResult = pGameFramework->RaycastClosest(&Line,NULL);
	if(!pResult)return false;

	return(pResult->GetDistanceResult() >= DistanceBetweenVector(vTarget,vLocal));
}

void DrawBone(int CharaIndex, int BoneIndexStart, int BoneIndexEnd, DWORD Color)
{
	D3DXVECTOR3 OnWorldA,OnScreenA;
	D3DXVECTOR3 OnWorldB,OnScreenB;
	if(GetUserBone(OnWorldA,BoneIndexStart,CharaIndex) && pRenderContext->WorldToScreen(OnWorldA,OnScreenA,npDevice) && GetUserBone(OnWorldB,BoneIndexEnd,CharaIndex) && pRenderContext->WorldToScreen(OnWorldB,OnScreenB,npDevice))
	{
		DrawLineColor(OnScreenA.x,OnScreenA.y,OnScreenB.x,OnScreenB.y,1,Color);
	}
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

bool bAimState = false;
bool GetAimAssistState()
{
	if(FeatureEngine->_get("GameHack.Assist.Hotkey")->_val() == 0)return true;
	if(FeatureEngine->_get("GameHack.Assist.HotkeyMode")->_val() == 0){
		switch(FeatureEngine->_get("GameHack.Assist.Hotkey")->_val())
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
	else if (FeatureEngine->_get("GameHack.Assist.Hotkey")->_val() == 1){
		switch(FeatureEngine->_get("GameHack.Assist.Hotkey")->_val())
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