class CGameContext;

struct _NetCharaInfo
{
DWORD ReplaceWeapon;
};

struct GAMEINFO_CHARACTER
{
	D3DXVECTOR3 &m_pPosContext;
};

struct __ScoreInfo
{
public:
BYTE Kill;
char _0001[1];
BYTE Dead;
char _0003[1];
};
//------------------------------------------------------------------------------------------------------//
//--------------------------------------------CGameContext---------------------------------------------
//------------------------------------------------------------------------------------------------------//
class CSlot
{
public:
BYTE iSlot;
};

class CGameContext {
public:

	int getUdpHoleState(int iSlot) 
	{	
		return ((int(__thiscall*)(CGameContext*, int))ResultgetUdpHoleState)(this, iSlot);
	}

	int setMySlotIdx() 
	{	
		return ((int(__thiscall*)(CGameContext*))ResultTeam)(this);
	}

	int GetMySlotIdx(unsigned int Index)
	{
		BYTE MyTeam = *(BYTE*)((DWORD)this + ResultPTRTeam);
		Index=MyTeam;
		return Index;
	}

	bool isRedTeam(int CharaIndex)
	{
		if(CharaIndex % 2 == 0)return true;
		else return false;
	}

	bool getUserDeath(int iSlot) 
	{ 		
		return ((bool(__thiscall*)(CGameContext*, int))ResultDeath)(this, iSlot);	
	}
	
	bool MyCharaDeath() 
	{ 		
		return ((bool(__thiscall*)(CGameContext*, int))ResultDeath)(this, setMySlotIdx());	
	}

	_NetCharaInfo* getNetCharaInfo(int iSlot) 
	{ 
		return ((_NetCharaInfo*(__thiscall*)(CGameContext*, int))ResultNetChara)(this, iSlot);
	}
	
	GAMEINFO_CHARACTER* getGameInfo_Chara(int iSlot)
	{
		return ((GAMEINFO_CHARACTER*(__thiscall*)(CGameContext*, int))ResultInfoChara)(this, iSlot);
	}

	__ScoreInfo* getIndividualScore(int iSlot) 
	{
		return ((__ScoreInfo*(__thiscall*)(CGameContext*, int))ResultgetIndividualScore)(this, iSlot);
	}

	unsigned char GetPing(int iSlot) 
	{ 
		return ((unsigned char(__thiscall*)(CGameContext*, int))ResultGetPing)(this, iSlot);
	}

	//unsigned char SetPing(float Ping) 
	//{ 
	//	for (int index = 0; index <= (Ping-1); index++)
	//	{
	//	return ((void(__thiscall*)(CGameContext*,float))0x9DC3B0)(this,Ping);
	//	}
	//}

	const char* getNickForSlot(int iSlot) 
	{
		return ((const char*(__thiscall*)(CGameContext*, int))ResultName)(this, iSlot);
	}

	void SetChannelUserCount(int idxChannel, DWORD Count)
	{		
		*(DWORD*)((DWORD)this + 0x486FC + (idxChannel * 4) ) = Count;
	}

	const char* getMyNickName() 
	{
		return ((const char*(__thiscall*)(CGameContext*,int))ResultName)(this,setMySlotIdx());
	}

	int SetEvent(int Size,int Idx,int Idx2) 
	{ 
		__try
		{
		return ((int(__thiscall*)(CGameContext*, int, int,int, int,int, int))ResultSetEvent)(this, Size, Idx, Idx2, NULL, NULL, NULL);
		}__except (EXCEPTION_EXECUTE_HANDLER){}
	}

	int SetEventOnce(int Size) 
	{ 
		return ((int(__thiscall*)(CGameContext*, int, const void*,const void*, const void*))0x5946C0)(this,Size,0,0,0);
	}
	
	void GetUserInfoInvite(int iSlot)
	{
		return ((void(__thiscall*)(CGameContext*, int))ResultGetUserInfoInvite)(this, iSlot);
	}

	bool InBatlle() 
	{
		return (getUdpHoleState(setMySlotIdx()) == 6);
	}
	
	static CGameContext* ReplaceWeapon(int PointerWeapon,int ByteWeapon)
	{	
		__try
		{
		return (CGameContext*)(*(DWORD*)((DWORD)(CGameContext::g_pGameContext()) + PointerWeapon  + ((int)CGameContext::g_pGameContext()->setMySlotIdx()*0x158))=ByteWeapon); 
		}__except (EXCEPTION_EXECUTE_HANDLER){}
	}

	static CGameContext* Singleton()
	{
		DWORD A=Resultg_pGameContext;
		DWORD B=ResultCallg_pGameContext;
		DWORD Callerg_pGameContext;
		__asm
		{
			mov ecx,A
				call B
				mov Callerg_pGameContext,ecx;
		}
		return (CGameContext*)((DWORD)Callerg_pGameContext);
	}
	static CGameContext* g_pGameContext()
	{
		DWORD Callerg_pGameContext;
		__asm
		{
			mov ecx,Resultg_pGameContext
				call ResultCallg_pGameContext
				mov Callerg_pGameContext,ecx;
		}
		return (CGameContext*)((DWORD)Callerg_pGameContext);
	}
};