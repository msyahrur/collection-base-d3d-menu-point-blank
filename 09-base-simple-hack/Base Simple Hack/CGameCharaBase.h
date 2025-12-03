class CGameCharaBase;
//------------------------------------------------------------------------------------------------------//
//--------------------------------------------CGameCharaBase---------------------------------------------
//------------------------------------------------------------------------------------------------------//
class i3AIContext{public:};

class WeaponBase
{
public:
	
	i3AIContext* geti3AIContext(void)
	{
		return (i3AIContext*)*(DWORD*)(this+0x30);
	}

	void DoLineCollision(D3DXVECTOR3* SetStar,D3DXVECTOR3* SetEnd,int Slot)
	{		
		return ((void(__thiscall*)(WeaponBase*,D3DXVECTOR3*,D3DXVECTOR3*,int))ResultDoLineCollision)(this,SetStar,SetEnd,Slot);
	}

	void _OnHitCharaByExplosion(CGameCharaBase* AllChara,int CHARA_HIT_PART, D3DXVECTOR3* DirPos, D3DXVECTOR3* SrcPos)
	{	
		return ((void(__thiscall*)(WeaponBase*,CGameCharaBase* AllChara,int,D3DXVECTOR3*,D3DXVECTOR3*))Result_OnHitCharaByExplosion)(this,AllChara,CHARA_HIT_PART,DirPos,SrcPos);
	}

	void NET_Fire(D3DXVECTOR3* A,D3DXVECTOR3* B)
	{
		return ((void(__thiscall*)(WeaponBase*,D3DXVECTOR3*,D3DXVECTOR3*,int))ResultNET_Fire)(this,A,B,1);
	}

	void Reset(void)
	{
		return ((void(__thiscall*)(WeaponBase*))ResultReset)(this);
	}		

	void SetKiller()
	{
		return ((void(__thiscall*)(WeaponBase*,int,int))ResultSetKiller)(this,0,0);
	}	

	static WeaponBase* setGrenadeDamage(WeaponBase* pWeaponBase)
	{
		return (WeaponBase*)(*(DWORD*)(*(DWORD*)/*Batas*/((DWORD)(pWeaponBase))+0x660)=200);
	}
	
	static WeaponBase* setFloatExplosion(DWORD pWeaponBase)
	{
		return (WeaponBase*)(*(DWORD*)(*(DWORD*)/*Batas*/((DWORD)(pWeaponBase))+0x660)=200);
	}

	static CGameCharaBase* Fire_EndAnim(WeaponBase* pWeaponBase)
	{
		__try
		{
			return (CGameCharaBase*)(*(DWORD*)(*(DWORD*)((DWORD)(pWeaponBase))+ResultPTRFireEndAnim)=0);
		}__except (EXCEPTION_EXECUTE_HANDLER){}
	}

	static WeaponBase* JumpByte(unsigned long Addres,BYTE Size)
	{
		return (WeaponBase*)(*(BYTE*)Addres = Size);
	}
};

class CGameCharaWeaponContext 
{
public:

	WeaponBase* getCurrent()
	{
		auto Func = (WeaponBase* (__thiscall*)(CGameCharaWeaponContext*))ResultGetCurrent;
		return Func(this);
	}
	
	int getCurrentWeaponSlot(void)
	{
		auto Func = (int (__thiscall*)(DWORD))ResultCallgetSlotWeapon;
		return Func((DWORD)this+ResultPTRgetSlotWeapon);
	}

};

class CWeaponProperty
{
public:
	DWORD RecoilV1; // 0x74
	DWORD RecoilV2; // 0x78
	DWORD RecoilH1; // 0x7C
	DWORD RecoilH2; // 0x80 << freeze
	DWORD RecoilH3; // 0x84 << freeze
	char pad2[0x20]; // 0x88
	DWORD Deviation1; // 0xA8
	DWORD Deviation2; // 0xAC
	DWORD Deviation3; // 0xB0
};

class CGameCharaBoneContext
{
public:
	CWeaponProperty* getWeaponProperty()
	{
		return (CWeaponProperty*)(this + 0x74);
	}

	D3DMATRIX* m_Bone()
	{
		auto Func = (D3DMATRIX* (__thiscall*)(DWORD))ResultCallm_Bone;
		return Func((DWORD)this + ResultPTRm_Bone);
	}
};

class CGameCharaCollisionContext
{
public:

	int UpdateNickOnTarget(void)
	{
		auto Func = (int (__thiscall*)(DWORD))ResultCallNickOnTarget;
		return Func((DWORD)this + ResultPTRNickOnTarget);
	}

	CGameCharaBase* GetCrosshairTarget()
	{
		typedef DWORD (__thiscall * tReadData)(DWORD BaseData);
		tReadData ReadData = (tReadData)((DWORD)ResultCallNickOnTarget);

		return (CGameCharaBase*)ReadData((DWORD)this + ResultPTRNickOnTarget);
	}
};

class CGameCharaMoveContext
{
public:

	D3DXVECTOR3 *m_Controller()
	{
		auto Func = (D3DXVECTOR3*(__thiscall*)(DWORD))0x816B50;
		return Func((DWORD)this +0x110);
	}
};

class CGameCharaCameraContext
{
public:

	void getVirtualCamPosition(D3DXVECTOR3* vCam)
	{
		auto Func = (void(__thiscall*)(CGameCharaCameraContext*,D3DXVECTOR3*,D3DXMATRIX*,int))ResultgetVirtualCamPosition;
		return Func(this,vCam,NULL,NULL);
	}

	static CGameCharaCameraContext* NoRespawn()
	{
		__try
		{
			return (CGameCharaCameraContext*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((DWORD)(Resultg_pCameraManager)+0x44)+0x44)+0x9C)=1084227584);
		}__except (EXCEPTION_EXECUTE_HANDLER){}
	}

	static CGameCharaCameraContext* g_pCameraManager()
	{
		DWORD ResultCallg_pCameraManager=0x64CFE0;
		DWORD Callerg_pCameraManager;	
		__asm
		{
			mov ecx,ResultpCameraManager
				call ResultCallg_pCameraManager
				mov Callerg_pCameraManager,ecx;
		}
		return (CGameCharaCameraContext*)((DWORD)Callerg_pCameraManager);
	}
	
};

class CGameCharaAnimContext
{
public:
	i3AIContext* geti3AIContext(void)
	{
		return (i3AIContext*)*(DWORD*)(this+0x5C);
	}
};


class CGameCharaBase
{
public:	

	int getCurHP()
	{__try{
	auto Func = (int(__thiscall*)(CGameCharaBase*))ResultgetCurHP;
	return Func(this);}__except (EXCEPTION_EXECUTE_HANDLER){}	
	}
	
	float getCurHP_Real()
	{__try{
	auto Func = (float(__thiscall*)(CGameCharaBase*))ResultgetCurHP_Real;
	return Func(this);
	}__except (EXCEPTION_EXECUTE_HANDLER){}
	}

	CGameCharaWeaponContext* m_pWeaponContext()
	{
		auto Func = (CGameCharaWeaponContext* (__thiscall*)(CGameCharaBase*))ResultCallm_pWeaponContext; 
		return Func(this);
	}

	CGameCharaBoneContext* m_pBoneContext()
	{
		auto Func = (CGameCharaBoneContext* (__thiscall*)(CGameCharaBase*))ResultCallm_pBoneContext;
		return Func(this);
	}	

	CGameCharaCollisionContext* m_pCollisionContext()
	{
		auto Func = (CGameCharaCollisionContext* (__thiscall*)(CGameCharaBase*))ResultCallm_pCollisionContext; 
		return Func(this);
	}

	CGameCharaMoveContext* m_pMoveContext()
	{
		auto Func = (CGameCharaMoveContext* (__thiscall*)(CGameCharaBase*))0x4E4570; 
		return Func(this);
	}

	CGameCharaCameraContext* m_pCameraContext()
	{
		auto Func = (CGameCharaCameraContext* (__thiscall*)(CGameCharaBase*))ResultCallm_pCameraContext; 
		return Func(this);
	}
	
	CGameCharaAnimContext* m_pAnimContext(void)
	{
		auto Func = (CGameCharaAnimContext* (__thiscall*)(CGameCharaBase*))ResultCallm_pAnimContext; 
		return Func(this);
	}

	int WriteDamage(int parm1, __int16 parm2, char parm3) 
	{ 		
		__try
		{
		auto Func = (int (__thiscall*)(CGameCharaBase*, int, __int16, char))ResultSuicide;
		return Func(this, parm1, parm2, parm3);
		}__except (EXCEPTION_EXECUTE_HANDLER){}
	}
	
	void Cmd_Damage(int numDmg)
	{		
		__try
		{
		typedef void (__thiscall * teventFall)(CGameCharaBase* Base, int, int, bool);
		teventFall eventFall = (teventFall)(ResultSuicide);
		return eventFall(this, numDmg, numDmg, false);}__except (EXCEPTION_EXECUTE_HANDLER){}
		
	}

	bool Cmd_Install()
	{		
		auto Func = (bool(__thiscall*)(CGameCharaBase*, bool))ResultCMD_Instal;
		return Func(this,true);
	}

	void Cmd_PickupWeapon(WeaponBase*WB)
	{		
		auto Func = (void(__thiscall*)(CGameCharaBase*, WeaponBase*))0x7AA330;
		return Func(this,WB);
	}

	void Cmd_ToogleZoom()
	{		
		auto Func = (void(__thiscall*)(CGameCharaBase*))0x9AAD00;
		return Func(this);
	}

	char Cmd_FallDamage(char FallDamage) 
	{
		return ((char(__thiscall*)(CGameCharaBase*, char))0x7A9F90)(this, FallDamage);
	}

	static CGameCharaBase* Fast_Shot()
	{
		__try
		{
			return (CGameCharaBase*)(*(DWORD*)((DWORD)(g_pPlayer())+ ResultPTRFastShot)=0);
		}__except (EXCEPTION_EXECUTE_HANDLER){}
	}
	
	int getCharaNetIndex(void)
	{
		typedef int (__thiscall * tgetCharaNetIndex)(CGameCharaBase* Base);
		tgetCharaNetIndex getCharaNetIndex = (tgetCharaNetIndex)(ResultgetCharaNetIndex);
		if(this == NULL)return -1;
		return getCharaNetIndex(this);
	}

	const char* getNickname(void)
	{
		return CGameContext::g_pGameContext()->getNickForSlot(this->getCharaNetIndex());	
	}

	bool isAlive(void)
	{
		return( this->getCurHP() > 0 );
	}

	bool isCritalHIT(void)
	{
		return( this->getCurHP() > 20 );
	}

	//begin
	bool isAlive_1(void)//RespawnChara_
	{
		return( this->getCurHP() > 1 );
	}
	bool isAlive_2(void)//RespawnChara_
	{
		return( this->getCurHP() < 1 );
	}
	//end
	bool isLocal(void)
	{
		return ( this->getCharaNetIndex() == CGameContext::g_pGameContext()->setMySlotIdx() );
	}

	bool isEnemy(void)
	{
		return (CGameContext::g_pGameContext()->isRedTeam(this->getCharaNetIndex()) != CGameContext::g_pGameContext()->isRedTeam(CGameContext::g_pGameContext()->setMySlotIdx()));
	}

	bool isVisible(int BoneTargetIndex)
	{
		return GetPlayerVisibleStatus(CGameContext::g_pGameContext()->setMySlotIdx(),this->getCharaNetIndex(),BoneTargetIndex);
	}

	DWORD GetTeamColor()
	{
		if(this->isEnemy())return D3DCOLOR_ARGB(255, 0, 180, 255);
		return D3DCOLOR_ARGB(255, 245, 000, 000);
	}

	void SetCharaWeapon(unsigned int WeaponSlot,DWORD ValueByte)
	{
		return ((void(__thiscall*)(CGameCharaBase*,signed int, signed int,signed int))ResultSetCharaWeapon)(this,WeaponSlot,_WeaponValue(ValueByte).WeaponType(),_WeaponValue(ValueByte).WeaponIndex());	
	}
	
	static CGameCharaBase* g_pPlayer()
	{
		DWORD Callerg_pPlayer;
		__asm
		{
			mov ecx,Resultg_pPlayer
				call ResultCallg_pPlayer
				mov Callerg_pPlayer,ecx;
		}
		return (CGameCharaBase*)((DWORD)Callerg_pPlayer);
	}

};                                         
