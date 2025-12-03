class CWeaponInfo
{
public:	
};

class WeaponInfoDataBase
{
public:	

	const char* GetWeaponClass(CWeaponInfo*CWI) 
	{
		return ((const char*(__thiscall*)(WeaponInfoDataBase*, CWeaponInfo*))0x60B300)(this, CWI);
	}

	static WeaponInfoDataBase* g_pWeaponInfoDataBase()
	{
		DWORD Callerg_pWeaponInfoDataBase;
		DWORD Resultg_pWeaponInfoDataBaser = 0xDCAD4C;
		DWORD ResultCallg_pWeaponInfoDataBase = 0x4AF4F0;
		__asm
		{
			mov ecx,Resultg_pWeaponInfoDataBaser
				call ResultCallg_pWeaponInfoDataBase
				mov Callerg_pWeaponInfoDataBase,ecx;
		}
		return (WeaponInfoDataBase*)((DWORD)Callerg_pWeaponInfoDataBase);
	}

};                                         
