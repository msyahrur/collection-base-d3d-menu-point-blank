//Created by DANI XCT / WA DANI IDI/MENU XXN PART 2
class CGameCharaCollisionContext
{
public:
	int getCrossHairTarget(void)
	{
		auto Func = (int (__thiscall*)(DWORD))AddyEngine->GetAddyValueByKey("GameCharaCollisionContext.Function.ReadData");
		return Func((DWORD)this + AddyEngine->GetAddyValueByKey("GameCharaCollisionContext.Pointer.CrosshairTarget"));
	}
	CGameCharaBase* GetCrosshairTarget()
	{
		typedef DWORD (__thiscall * tReadData)(DWORD BaseData);
		tReadData ReadData = (tReadData)(AddyEngine->GetAddyValueByKey("GameCharaCollisionContext.Function.ReadData"));

		return (CGameCharaBase*)ReadData((DWORD)this + AddyEngine->GetAddyValueByKey("GameCharaCollisionContext.Pointer.CrosshairTarget"));
	}
};

class CWeaponProperty
{
public:
	DWORD RecoilV1;
	DWORD RecoilV2;
	DWORD RecoilH1;
	DWORD RecoilH2;
	DWORD RecoilH3;
	char pad2[0x20];
	DWORD Deviation1;
	DWORD Deviation2;
	DWORD Deviation3;
};

class CGameCharaBoneContext
{
public:
	CWeaponProperty* getWeaponProperty()
	{
		return (CWeaponProperty*)(this + 0x74);
	}

	DWORD getBones()
	{
		typedef DWORD (__thiscall * tgetBones)(CGameCharaBoneContext* Base);
		tgetBones getBones = (tgetBones)(AddyEngine->GetAddyValueByKey("GameCharaBoneContext.Function.getBones"));
		return (getBones(this) - AddyEngine->GetAddyValueByKey("GameCharaBoneContext.Size.BonesAlign"));
	}
	D3DXVECTOR3 getBonePosition(int BoneIndex)
	{
		D3DXMATRIX *pBone = (D3DXMATRIX*)(this->getBones());
		return D3DXVECTOR3(pBone[ BoneIndex ]._41, pBone[ BoneIndex ]._42, pBone[ BoneIndex ]._43);
	}

};

class i3AIContext
{
public:

};

class CGameCharaAnimContext
{
public:
	i3AIContext* geti3AIContext(void)
	{
		return (i3AIContext*)*(DWORD*)(this + AddyEngine->GetAddyValueByKey("XFHPB.Pointer.QuickChange"));
	}
};

class CWeaponBase
{
public:
	void Reset()
	{
		typedef void (__thiscall * tReset)(CWeaponBase* Base);
		tReset Reset = (tReset)(AddyEngine->GetAddyValueByKey("WeaponBase.Function.Reset"));
		return Reset(this);
	}
	void doFire()
	{
		typedef void (__thiscall * tdoFire)(CWeaponBase* Base, int a1, int a2);
		tdoFire doFire = (tdoFire)(AddyEngine->GetAddyValueByKey("WeaponBase.Function.DoFire"));
		return doFire(this,false,false);
	}
	void doLineCollision(D3DXVECTOR3* Start, D3DXVECTOR3* End, DWORD a1)
	{
		typedef void (__thiscall * tdoLineCollision)(CWeaponBase* Base, D3DXVECTOR3* Start, D3DXVECTOR3* End, DWORD a1);
		tdoLineCollision doLineCollision = (tdoLineCollision)(AddyEngine->GetAddyValueByKey("WeaponBase.Function.DoLineCollision"));
		return doLineCollision(this,Start,End,a1);
	}
	void NET_Fire(D3DXVECTOR3* a1, D3DXVECTOR3* a2)
	{
		typedef void (__thiscall * tNET_Fire)(CWeaponBase* Base, D3DXVECTOR3* a1, D3DXVECTOR3* a2, int a3);
		tNET_Fire NET_Fire = (tNET_Fire)(ResultNET_Fire);
		return NET_Fire(this, a1, a2, 1);
	}
}; CWeaponBase* pGameLocalWeapon = NULL;

class CGameCharaWeaponContext
{
public:
	CWeaponBase* getCurrentWeapon(void)
	{
		typedef CWeaponBase* (__thiscall * tgetCurrentWeapon)(CGameCharaWeaponContext* Base);
		tgetCurrentWeapon getCurrentWeapon = (tgetCurrentWeapon)(ResultGetCurrent);
		return getCurrentWeapon(this);
	}
	DWORD getCurrentWeaponIndex(void)
	{
		if(ResultCallgetSlotWeapon > NULL){
			typedef DWORD (__thiscall * tDecryptWeaponIndex)(CGameCharaWeaponContext* Base);
			tDecryptWeaponIndex DecryptWeaponIndex = (tDecryptWeaponIndex)ResultCallgetSlotWeapon;
			return DecryptWeaponIndex(this + ResultPTRgetSlotWeapon);
		}
		else return *(DWORD*)(this + ResultPTRgetSlotWeapon);
	}
};

class CWeaponGrenade : public CWeaponBase
{
public:
	DWORD GetVirtualFunction(DWORD dwVFIndex)
	{
		return *(DWORD*)(*(DWORD*)(this) + dwVFIndex*4);
	}
	void onHitCharaByExplosion(CGameCharaBase* pHitUser, int CHARA_HIT_PART, D3DXVECTOR3* DirPos, D3DXVECTOR3* SrcPos)
	{
		typedef void (__thiscall * tonHitCharaByExplosion)(CWeaponBase* Base, CGameCharaBase* pHitUser, int CHARA_HIT_PART, D3DXVECTOR3* DirPos, D3DXVECTOR3* DstPos);
		tonHitCharaByExplosion onHitCharaByExplosion = (tonHitCharaByExplosion)(GetVirtualFunction(67));
		return onHitCharaByExplosion(this, pHitUser, CHARA_HIT_PART, DirPos, SrcPos);
	}
};

class CGameCharaBase
{
public:
	int getCharaNetIndex(void)
	{
		typedef int (__thiscall * tgetCharaNetIndex)(CGameCharaBase* Base);
		tgetCharaNetIndex getCharaNetIndex = (tgetCharaNetIndex)(AddyEngine->GetAddyValueByKey("GameCharaBase.Function.getCharaNetIdx"));
		if(this == NULL)return -1;
		return getCharaNetIndex(this);
	}
	const char* getNickname(void)
	{
		return pGameContext->getNickForSlot(this->getCharaNetIndex());	
	}
	int getCurHP(void)
	{
		typedef int (__thiscall * tgetCurHP)(CGameCharaBase* Base);
		tgetCurHP getCurHP = (tgetCurHP)(AddyEngine->GetAddyValueByKey("GameCharaBase.Function.getCurHP"));
		return getCurHP(this);
	}
	void eventFall(int numDmg)
	{
		typedef void (__thiscall * teventFall)(CGameCharaBase* Base, int a1, int a2, bool a3);
		teventFall eventFall = (teventFall)(AddyEngine->GetAddyValueByKey("GameCharaBase.Function.eventFall"));
		return eventFall(this, numDmg, numDmg, false);
	}
	void setInvicibleTime(float invicibleTime)
	{
		typedef void (__thiscall * tWriteData)(DWORD BaseData, float InputValue);
		tWriteData WriteData = (tWriteData)(AddyEngine->GetAddyValueByKey("GameCharaBase.Function.writeData"));
		WriteData((DWORD)this + AddyEngine->GetAddyValueByKey("GameCharaBase.Pointer.invicibleTime"), invicibleTime);
	}
	bool isAlive(void)
	{
		return( this->getCurHP() > 0 );
	}
	bool isLocal(void)
	{
		return ( this->getCharaNetIndex() == pGameContext->getMySlotIdx() );
	}
	bool isEnemy(void)
	{
		return (pGameContext->isRedTeam(this->getCharaNetIndex()) != pGameContext->isRedTeam(pGameContext->getMySlotIdx()));
	}
	bool isVisible(int BoneTargetIndex)
	{
		return GetPlayerVisibleStatus(pGameContext->getMySlotIdx(),this->getCharaNetIndex(),BoneTargetIndex);
	}
	void Cmd_Respawn(D3DXVECTOR3* RespawnPos)
    {
		typedef void (__thiscall * tCmd_Respawn)(CGameCharaBase* Base, D3DXVECTOR3* RespawnPos);
		tCmd_Respawn Cmd_Respawn = (tCmd_Respawn)(AddyEngine->GetAddyValueByKey("GameCharaBase.Function.Cmd_Respawn"));
		return Cmd_Respawn(this, RespawnPos);
    }
	void setCharaWeapon(unsigned int WeaponSlot, unsigned int WeaponType, unsigned int WeaponIndex)
	{
		typedef void (__thiscall * tsetCharaWeapon)(CGameCharaBase* Base, unsigned int WeaponSlot, unsigned int WeaponType, unsigned int WeaponIndex);
		tsetCharaWeapon setCharaWeapon = (tsetCharaWeapon)(AddyEngine->GetAddyValueByKey("GameCharaBase.Function.setCharaWeapon"));
		return setCharaWeapon(this, WeaponSlot, WeaponType, WeaponIndex);
	}
	CGameCharaCollisionContext* getGameCharaCollisionContext(void)
	{
		typedef CGameCharaCollisionContext* (__thiscall * tgetGameCharaCollisionContext)(CGameCharaBase* Base);
		tgetGameCharaCollisionContext getGameCharaCollisionContext = (tgetGameCharaCollisionContext)(AddyEngine->GetAddyValueByKey("GameCharaBase.Function.getGameCharaCollisionContext"));
		return getGameCharaCollisionContext(this);
	}
	CGameCharaBoneContext* getGameCharaBoneContext(void)
	{
		typedef CGameCharaBoneContext* (__thiscall * tgetGameCharaBoneContext)(CGameCharaBase* Base);
		tgetGameCharaBoneContext getGameCharaBoneContext = (tgetGameCharaBoneContext)(AddyEngine->GetAddyValueByKey("GameCharaBase.Function.getGameCharaBoneContext"));
		return getGameCharaBoneContext(this);
	}
	CGameCharaWeaponContext* getGameCharaWeaponContext(void)
	{
		typedef CGameCharaWeaponContext* (__thiscall * tgetGameCharaWeaponContext)(CGameCharaBase* Base);
		tgetGameCharaWeaponContext getGameCharaWeaponContext = (tgetGameCharaWeaponContext)(AddyEngine->GetAddyValueByKey("GameCharaBase.Function.getGameCharaWeaponContext"));
		return getGameCharaWeaponContext(this);
	}
	CGameCharaAnimContext* getGameCharaAnimContext(void)
	{
		typedef CGameCharaAnimContext* (__thiscall * tgetGameCharaAnimContext)(CGameCharaBase* Base);
		tgetGameCharaAnimContext getGameCharaAnimContext = (tgetGameCharaAnimContext)(AddyEngine->GetAddyValueByKey("GameCharaBase.Function.getGameCharaAnimContext"));
		return getGameCharaAnimContext(this);
	}
}; CGameCharaBase* pGameCharaBase;