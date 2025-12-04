/*++

Copyright (c) Main Cit 96 Corporation.  All rights reserved.

Module Name:

  CGameCharaManager.h

Abstract:

    Type definitions for the basic sized types.

Author:

Revision History:

--*/

float CalcDistance( D3DXVECTOR3 VecA, D3DXVECTOR3 VecB )
{
        return sqrt( ( ( VecA.x - VecB.x ) * ( VecA.x - VecB.x ) ) +
                 ( ( VecA.y - VecB.y ) * ( VecA.y - VecB.y ) ) +
                 ( ( VecA.z - VecB.z ) * ( VecA.z - VecB.z ) ) );
}

class CGameCharaManager;

class CGameCharaManager
{
public:
	char unk_0x0[0x14];
	CGameCharaBase* GameCharaBase[16];

	CGameCharaBase* GetCharaByNetIdx(int IdxSlot)
	{
		return ((CGameCharaBase* (__thiscall*)(CGameCharaManager*, int))ResultGetCharaByNetIdx)(this, IdxSlot);
	}

	CGameCharaBase* getLocalChara(void)
	{
		return ((CGameCharaBase* (__thiscall*)(CGameCharaManager*, int))ResultGetCharaByNetIdx)(this, CGameContext::g_pGameContext()->setMySlotIdx());
	}

	CGameCharaBase* getAllChara(void)
	{		
		for(int iSlot = 0; iSlot <= 16; iSlot++){
		return ((CGameCharaBase* (__thiscall*)(CGameCharaManager*, int))ResultGetCharaByNetIdx)(this,iSlot);
		}
	}

	bool isValidChara(int CharaIndex)
	{
		return( this->GetCharaByNetIdx(CharaIndex) > NULL );
	}

	bool AllPlayerAlive(void){
		for(int i = 0; i<=15; i++)
		{
			if(this->isValidChara(i) && !this->GetCharaByNetIdx(i)->isAlive())
			{
				return false;
			}
		}
		return true;
	}

	bool AllEnemyAlive(void)
	{
		for(int i = 0; i<=15; i++)
		{
			if(this->isValidChara(i) && !this->GetCharaByNetIdx(i)->isAlive() && this->GetCharaByNetIdx(i)->isEnemy())
			{
				return false;
			}
		}
		return true;
	}

	bool AllPlayerDead(void){
		for(int i = 0; i<=15; i++)
		{
			if(this->isValidChara(i) && this->GetCharaByNetIdx(i)->isAlive())
			{
				return false;
			}
		}
		return true;
	}

	bool AllEnemyDead(void) 
	{
		for(int i = 0; i<=15; i++)
		{
			if(this->isValidChara(i) && this->GetCharaByNetIdx(i)->isAlive() && this->GetCharaByNetIdx(i)->isEnemy())
			{
				return false;
			}
		}
		return true;
	}
	
	bool AllEnemyHIT(void) 
	{
		for(int i = 0; i<=15; i++)
		{
			if(this->isValidChara(i) && this->GetCharaByNetIdx(i)->isCritalHIT() && this->GetCharaByNetIdx(i)->isEnemy())
			{
				return false;
			}
		}
		return true;
	}


	void SetCharaWeaponSet(CGameCharaBase* Base,_NetCharaInfo*CharaInfo)
	{
		return ((void(__thiscall*)(CGameCharaManager*,CGameCharaBase* CharaInfo,_NetCharaInfo*Indo))ResultSetCharaWeaponSet)(this,Base,CharaInfo);	
	}

	void RespawnChara(int iSlot)
	{	
		return ((void(__thiscall*)(CGameCharaManager*, int,bool))ResultRespawnChara)(this, iSlot,1);	
	}

	D3DXVECTOR3 _GetRespawnPosition(float Teleport,int A,int B)
	{	
		return ((D3DXVECTOR3(__thiscall*)(CGameCharaManager*, float,int,int))0x57F5A0)(this, Teleport,A,B);	
	}
	//005943AC - 68 1419B900           - push 00B91914 { ["EnableImmediateRespawn"] }

	static CGameCharaManager* g_pCharaManager()
	{
		DWORD Callerg_pCharaManager;
		__asm
		{
			mov ecx,Resultg_pCharaManager
				call ResultCallg_pCharaManager
				mov Callerg_pCharaManager,ecx;
		}
		return (CGameCharaManager*)((DWORD)Callerg_pCharaManager);
	}

};
