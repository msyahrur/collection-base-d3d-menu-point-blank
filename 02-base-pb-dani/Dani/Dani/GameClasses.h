//Created by DANI XCT / WA DANI IDI/MENU XXN PART 2
struct CTeam
{
	BYTE iTeam;
};

struct CNames
{
	char szNames[33];
};

int GetTeam(char MyTeam)
{
	for(int i = 0; i < 16; i+=2)
		if(i == MyTeam)return 2;
	for(int i = 1; i< 16; i+=2)
		if(i == MyTeam)return 1;
	return -1;
}

float DistanceBetweenVector( D3DXVECTOR3 VecA, D3DXVECTOR3 VecB )
{
        return sqrt( ( ( VecA.x - VecB.x ) * ( VecA.x - VecB.x ) ) +
                 ( ( VecA.y - VecB.y ) * ( VecA.y - VecB.y ) ) +
                 ( ( VecA.z - VecB.z ) * ( VecA.z - VecB.z ) ) );
}

class pSetEndVector
{
public:
	D3DXVECTOR3 TargetVector;
	bool State;

	void SetTargetVector(D3DXVECTOR3 VecIn)
	{
		TargetVector = VecIn;
		State = true;
	}

	void Disable()
	{
		State = false;
	}

	DWORD GetSetEndVector(DWORD OrigSetLine)
	{
		if(State == true){
			return (DWORD)&TargetVector;
		}
		else return OrigSetLine;
	}
	pSetEndVector()
	{
		State = false;
		TargetVector.x = 0;
		TargetVector.y = 0;
		TargetVector.z = 0;
	}
};
pSetEndVector *SetEndVector = NULL;

void UpdateGameClass()
{
	pRenderContext = (CRenderContext*)( *(DWORD*)(AddyEngine->GetAddyValueByKey("RenderContext.Base")));
	pGameContext = (CGameContext*)(oReadBaseValue(AddyEngine->GetAddyValueByKey("GameContext.Base")));
	pGameCharaManager = (CGameCharaManager*)( oReadBaseValue(AddyEngine->GetAddyValueByKey("GameCharaManager.Base")));
	pGameFramework = (CGameFramework*)( oReadBaseValue(AddyEngine->GetAddyValueByKey("GameFramework.Base")));
}

void UpdateLocalClass()
{
	if(pGameCharaManager->getLocalChara())
	{
		pGameCharaBase = pGameCharaManager->getLocalChara();
	}
}