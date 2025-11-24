//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
class CGameCharaManager 
{
public:
	CGameCharaBase* getCharaByNetIdx(int CharaIndex)
	{
		typedef CGameCharaBase* (__thiscall * tgetCharaByNetIdx)(CGameCharaManager* Base, int Index);
		tgetCharaByNetIdx getCharaByNetIdx = (tgetCharaByNetIdx)(AddyEngine->GetAddyValueByKey("GameCharaManager.Function.getCharaByNetIdx"));
		return getCharaByNetIdx(this, CharaIndex);
	}
	CGameCharaBase* getLocalChara(void)
	{
		typedef CGameCharaBase* (__thiscall * tgetCharaByNetIdx)(CGameCharaManager* Base, int Index);
		tgetCharaByNetIdx getCharaByNetIdx = (tgetCharaByNetIdx)(AddyEngine->GetAddyValueByKey("GameCharaManager.Function.getCharaByNetIdx"));
		return getCharaByNetIdx(this,pGameContext->getMySlotIdx());
	}
	CGameCharaBase* getCharaToAim(void)
	{
		CGameCharaBase* Result = NULL;
		float Farthest = 1000.0f;
		for(int i = 0; i <= 15; i++)
		{
			CGameCharaBase* Chara = this->getCharaByNetIdx(i);
			if(Chara)
			{
				if(Chara->isEnemy() == false)continue;
				if(Chara->isAlive() == false)continue;
				if(Chara->isVisible(BoneIndexSelector) == false)continue;
				float PawnDistanceFromLocalPawn = DistanceBetweenVector(Chara->getGameCharaBoneContext()->getBonePosition(0), this->getLocalChara()->getGameCharaBoneContext()->getBonePosition(0));
				if(PawnDistanceFromLocalPawn < Farthest)
				{
					Farthest = PawnDistanceFromLocalPawn;
					Result = Chara;
				}
			}
		}
		return Result;
	}
	void RespawnChara(int iSlot)
	{	
		return ((void(__thiscall*)(CGameCharaManager*, int,bool))AddyEngine->GetAddyValueByKey("GameCharaManager.Function.RespawnChara"))(this, iSlot,1);	
	}
}; CGameCharaManager* pGameCharaManager = NULL;