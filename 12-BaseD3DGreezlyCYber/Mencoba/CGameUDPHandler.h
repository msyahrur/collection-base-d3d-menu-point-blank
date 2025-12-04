/*++

Copyright (c) Main Cit 96 Corporation.  All rights reserved.

Module Name:

 CGameUDPHandler.h

Abstract:

    Type definitions for the basic sized types.

Author:

Revision History:

--*/
class CGameUDPHandler
{
public:

	void WriteGameEvent_Fire(CGameCharaBase* Chara, D3DXVECTOR3* vTarget, WeaponBase* CWeaponBase)
	{		
		__try
		{
			return ((void(__thiscall*)(CGameUDPHandler* Base, CGameCharaBase* Chara, D3DXVECTOR3* vTarget, WeaponBase* CWeaponBase))ResultDoLineCollision)(this, Chara, vTarget, CWeaponBase);
		}__except (EXCEPTION_EXECUTE_HANDLER){}
		
	}

	static CGameUDPHandler* Singleton()
	{
		return ((CGameUDPHandler*(__stdcall*)(CGameUDPHandler*))ResultCGameUDPHandler)(&CGameUDPHandler());
	}
			
};
