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
class CRenderContext;
class CGameContext;
class i3AIContext;
class CWeaponBase;
class CGameCharaWeaponContext;
class CGameCharaBoneContext;
class CWeaponProperty;
class CGameCharaBase;
class CGameCharaManager;
class i3InputMouse;
class i3InputKeyboard;
class i3PhysixResult;
class CGameFramework;
class GM;
enum TSlotWeapon {Primary, Secondary, Melle, Explosive, Special,ExplosiveC4,Teuapal};

struct sEventCode{
	enum Values
	{
		Respawn = 0x97,
		GetLobbyUserList = 0x86,
		SendInviteUser = 0x87,
		JoinRoom = 0x73,
		Whisper = 0x66,
		GlobalChat = 0x1FD,
	};
};
sEventCode EventCode;

struct _WeaponValue
{
	DWORD Value;
	_WeaponValue(DWORD dwValue)
	{
		this->Value = dwValue;
	}
	signed int WeaponSlot()
	{
		return (this->Value % 100000000 / 1000000);
	}
	signed int WeaponType()
	{
		return (this->Value % 1000000 / 1000);
	}
	signed int WeaponIndex()
	{
		return (this->Value % 1000);
	}
};

struct CRank
{
	BYTE iRank;
};

struct CNames
{
    char szNames[33];
};

class GM
{
public:
	BYTE iRank;
	char _0x0001[15];
	WORD iHack;
};

struct CTeam
{
	BYTE iTeam;
};

//==================================================================================================================================
struct _NetCharaInfo
{
	_WeaponValue getWeaponValue(int EquipIndex)
	{

		//typedef _WeaponValue (__thiscall * tgetWeaponValue)(_NetCharaInfo* Base, int EquipIndex);
		//tgetWeaponValue getWeaponValue = (tgetWeaponValue)(AddyEngine->GetAddyValueByKey(/*_NetCharaInfo.Function.getWeaponValue*/XorStr<0x0A,38,0xA2C21B10>("\x55\x45\x69\x79\x4D\x67\x71\x63\x73\x5A\x7A\x73\x79\x39\x5E\x6C\x74\x78\x68\x74\x71\x71\x0E\x46\x47\x57\x73\x40\x47\x57\x47\x47\x7C\x4A\x40\x58\x4B"+0xA2C21B10).s));
		//return getWeaponValue(this, EquipIndex);
		DWORD FinalValue = *(DWORD*)(this + AddyEngine->GetAddyValueByKey(/*_NetCharaInfo.Pointer.Weapon*/XorStr<0xeb,29,0x3cdba6b3>("\xb4\xa2\x88\x9a\xac\x98\x90\x80\x92\xbd\x9b\x90\x98\xd6\xa9\x95\x92\x92\x89\x9b\x8d\x2e\x56\x67\x62\x74\x6a\x68"+0x3cdba6b3).s) + (EquipIndex*4));
		return _WeaponValue( FinalValue );
	}
	void setWeaponValue(int EquipIndex, DWORD* Value)
	{
		typedef void (__thiscall * tsetWeaponValue)(_NetCharaInfo* Base, int EquipIndex, DWORD* Value);
		tsetWeaponValue setWeaponValue = (tsetWeaponValue)(AddyEngine->GetAddyValueByKey(/*_NetCharaInfo.Function.setWeaponValue*/XorStr<0x69,38,0x3450DD69>("\x36\x24\x0E\x18\x2E\x06\x0E\x02\x10\x3B\x1D\x12\x1A\x58\x31\x0D\x17\x19\x0F\x15\x12\x10\x51\xF3\xE4\xF6\xD4\xE1\xE4\xF6\xE8\xE6\xDF\xEB\xE7\xF9\xE8"+0x3450DD69).s));
		return setWeaponValue(this, EquipIndex, Value);
	}
};

class CRenderContext
{
public:
	const D3DXMATRIX* GetProjectMatrix(void )
	{
		return ((const D3DXMATRIX*(__thiscall*)(CRenderContext*))((DWORD)GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetProjectMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ")))(this);
	}	
	
	const D3DXMATRIX* GetViewMatrix(void)
	{
		return ((const D3DXMATRIX*(__thiscall*)(CRenderContext*))((DWORD)GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetViewMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ")))(this);
	}

	const D3DXMATRIX* GetWorldMatrix(void)
	{
		return ((const D3DXMATRIX*(__thiscall*)(CRenderContext*))((DWORD)GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetWorldMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ")))(this);
	}

	static CRenderContext* g_pRenderContext()
	{ 
		return (CRenderContext*)(*(DWORD*)GetProcAddress(LoadLibrary("i3GfxDx.dll"),"?g_pRenderContext@@3PAVi3RenderContext@@A")); 
	}

	bool WorldToScreen(D3DXVECTOR3 PlayerPos,D3DXVECTOR3 &Output,LPDIRECT3DDEVICE9 pDevice)
	{
		D3DXVECTOR3 vScreen;
		pDevice->GetViewport(&g_ViewPort);
		g_ViewPort.X = g_ViewPort.Y = 0;
		g_ViewPort.MinZ = 0;
		g_ViewPort.MaxZ = 1;
		D3DXVec3Project(&vScreen, &PlayerPos, &g_ViewPort, this->GetProjectMatrix(), this->GetViewMatrix(), this->GetWorldMatrix());

		if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < g_ViewPort.Width && vScreen.y < g_ViewPort.Height)
		{
			Output.x = vScreen.x;
			Output.y = vScreen.y;
			Output.z = vScreen.z;
			return true; 
		}
		return false;
	}
}; CRenderContext* pRenderContext = NULL;

//==================================================================================================================================
class CGameCharaMissionManager
{
public:
	void InstallBomb(bool State)
	{
		typedef void (__thiscall* tInstallBomb)(CGameCharaMissionManager* Base, bool State);
		tInstallBomb InstallBomb = (tInstallBomb)(AddyEngine->GetAddyValueByKey(/*GameCharaMissionManager.Function.InstallBomb*/XorStr<0x5F,45,0x4B561883>("\x18\x01\x0C\x07\x20\x0C\x04\x14\x06\x25\x00\x19\x18\x05\x02\x00\x22\x11\x1F\x13\x14\x11\x07\x58\x31\x0D\x17\x19\x0F\x15\x12\x10\x51\xC9\xEF\xF1\xF7\xE5\xE9\xEA\xC5\xE7\xE4\xE8"+0x4B561883).s));
		return InstallBomb(this, State);
	}
	void UnInstallBomb(bool State)
	{
		typedef void (__thiscall* tUnInstallBomb)(CGameCharaMissionManager* Base, bool State);
		tUnInstallBomb UnInstallBomb = (tUnInstallBomb)(AddyEngine->GetAddyValueByKey(/*GameCharaMissionManager.Function.UnInstallBomb*/XorStr<0x56,47,0x890BB5FE>("\x11\x36\x35\x3C\x19\x33\x3D\x2F\x3F\x12\x09\x12\x11\x0A\x0B\x0B\x2B\x06\x06\x08\x0D\x0E\x1E\x43\x28\x1A\x1E\x12\x06\x1A\x1B\x1B\x58\x22\x16\x30\x14\x08\x08\x1C\x12\x13\xC2\xEE\xEF\xE1"+0x890BB5FE).s));
		return UnInstallBomb(this, State);
	}
};

//==================================================================================================================================
class CGameContext
{
public:
	CGameCharaMissionManager* getGameCharaMissionManager(void)
	{
		typedef CGameCharaMissionManager* (__thiscall* tgetGameCharaMissionManager)(CGameContext* Base);
		tgetGameCharaMissionManager getGameCharaMissionManager = (tgetGameCharaMissionManager)(AddyEngine->GetAddyValueByKey(/*GameContext.Function.getGameCharaMissionManager*/XorStr<0xFE,48,0x87191867>("\xB9\x9E\x6D\x64\x41\x6C\x6A\x71\x63\x7F\x7C\x27\x4C\x7E\x62\x6E\x7A\x66\x7F\x7F\x3C\x74\x71\x61\x51\x76\x75\x7C\x59\x73\x7D\x6F\x7F\x52\x49\x52\x51\x4A\x4B\x4B\x6B\x46\x46\x48\x4D\x4E\x5E"+0x87191867).s));
		return getGameCharaMissionManager(this);
	}
	DWORD getMySlotIdx(void)
	{
		return *(DWORD*)(this + AddyEngine->GetAddyValueByKey(/*GameContext.Pointer.MySlotIdx*/XorStr<0xC6,30,0xCA4F451A>("\x81\xA6\xA5\xAC\x89\xA4\xA2\xB9\xAB\xB7\xA4\xFF\x82\xBC\xBD\xBB\xA2\xB2\xAA\xF7\x97\xA2\x8F\xB1\xB1\xAB\xA9\x85\x9A"+0xCA4F451A).s));
	}
	_NetCharaInfo* getNetCharaInfo(int CharaIndex)
	{
		typedef _NetCharaInfo* (__thiscall * tgetNetCharaInfo)(CGameContext* Base, int Index);
		tgetNetCharaInfo getNetCharaInfo = (tgetNetCharaInfo)(AddyEngine->GetAddyValueByKey(/*GameContext.Function.getNetCharaInfo*/XorStr<0xB3,37,0x9714FEB8>("\xF4\xD5\xD8\xD3\xF4\xD7\xD7\xCE\xDE\xC4\xC9\x90\xF9\xB5\xAF\xA1\xB7\xAD\xAA\xA8\xE9\xAF\xAC\xBE\x85\xA9\xB9\x8D\xA7\xB1\xA3\xB3\x9A\xBA\xB3\xB9"+0x9714FEB8).s));
		return getNetCharaInfo(this,CharaIndex);
	}
	const char* getNickForSlot(int CharaIndex)
	{
		typedef const char* (__thiscall * tgetNickForSlot)(CGameContext* Base, int Index);
		tgetNickForSlot getNickForSlot = (tgetNickForSlot)(AddyEngine->GetAddyValueByKey(/*GameContext.Function.getNickForSlot*/XorStr<0xC5,36,0x9B884E46>("\x82\xA7\xAA\xAD\x8A\xA5\xA5\xB8\xA8\xB6\xBB\xFE\x97\xA7\xBD\xB7\xA1\xBF\xB8\xB6\xF7\xBD\xBE\xA8\x93\xB7\xBC\x8B\xA7\x8D\x91\xB7\x89\x89\x93"+0x9B884E46).s));
		return getNickForSlot(this,CharaIndex);
	}
	bool getUserDeath(int iSlot) {
		auto Func = (bool(__thiscall*)(CGameContext*, int))GameContext.Function.getUserDeath;
		return Func(this, iSlot);
	}
	int SetEvent(int protocol, int parm2, int parm3) 
	{ 
		auto Func = (int (__thiscall*)(CGameContext*, int, int, int, int, int, int))AddyEngine->GetAddyValueByKey(/*GameContext.Function.setEvent*/XorStr<0xE2,30,0x5AF4E64A>("\xA5\x82\x89\x80\xA5\x88\x86\x9D\x8F\x93\x98\xC3\xA8\x9A\x9E\x92\x86\x9A\x9B\x9B\xD8\x84\x9D\x8D\xBF\x8D\x99\x93\x8A"+0x5AF4E64A).s);
		return Func(this, protocol, parm2, parm3, NULL, NULL, NULL);
	}
	bool isRedTeam(int CharaIndex)
	{
		if(CharaIndex % 2 == 0)return true;
		else return false;
	}
	void setRankValue(int Index, BYTE RankValue)
	{
		*(BYTE*)(this + AddyEngine->GetAddyValueByKey(/*GameContext.Pointer.Rank*/XorStr<0xCA,25,0x6C879A10>("\x8D\xAA\xA1\xA8\x8D\xA0\xBE\xA5\xB7\xAB\xA0\xFB\x86\xB8\xB1\xB7\xAE\xBE\xAE\xF3\x8C\xBE\x8E\x8A"+0x6C879A10).s) + (Index * AddyEngine->GetAddyValueByKey(/*GameContext.Size.Rank*/XorStr<0x0A,22,0x95C3799A>("\x4D\x6A\x61\x68\x4D\x60\x7E\x65\x77\x6B\x60\x3B\x45\x7E\x62\x7C\x34\x49\x7D\x73\x75"+0x95C3799A).s))) = RankValue;
	}
	void setEvent (int EventIndex, const void* pArg, const void* a3,const void* a4, const char* a5, int a6)
	{
		typedef void (__thiscall* tsetEvent)(CGameContext* Base, int EventIndex, const void* pArg, const void* a3,const void* a4, const char* a5, int a6);
		tsetEvent setEvent = (tsetEvent)(AddyEngine->GetAddyValueByKey(/*GameContext.Function.setEvent*/XorStr<0xE2,30,0x5AF4E64A>("\xA5\x82\x89\x80\xA5\x88\x86\x9D\x8F\x93\x98\xC3\xA8\x9A\x9E\x92\x86\x9A\x9B\x9B\xD8\x84\x9D\x8D\xBF\x8D\x99\x93\x8A"+0x5AF4E64A).s));
		return setEvent(this, EventIndex, pArg, a3, a4, a5, a6);
	}
	void SetInviteUser(int Index)
	{
		typedef void (__thiscall * tSetInviteUser)(CGameContext* Base, int Index);
		tSetInviteUser SetInviteUser = (tSetInviteUser)( AddyEngine->GetAddyValueByKey(/*GameContext.Function.SetInviteUser*/XorStr<0x47,35,0x4d12b3de>("\x00\x29\x24\x2f\x08\x23\x23\x3a\x2a\x28\x25\x7c\x15\x21\x3b\x35\x23\x31\x36\x34\x75\x0f\x38\x2a\x16\x0e\x17\x0b\x17\x01\x30\x15\x02\x1a"+0x4d12b3de).s) );
		return SetInviteUser(this, Index);
	}
	void SetMaxChannelUserCount(DWORD Count)
	{
		*(DWORD*)( this + AddyEngine->GetAddyValueByKey(/*GameContext.Pointer.MaxChannelUserCount*/XorStr<0x1f,40,0x097d5a03>("\x58\x41\x4c\x47\x60\x4b\x4b\x52\x42\x50\x5d\x04\x7b\x43\x44\x40\x5b\x55\x43\x1c\x7e\x55\x4d\x75\x5f\x59\x57\x54\x5e\x50\x68\x4d\x5a\x32\x02\x2d\x36\x2a\x31"+0x097d5a03).s) ) = Count;
	}
	void SetChannelUserCount(int idxChannel, DWORD Count)
	{
		*(DWORD*)( this + AddyEngine->GetAddyValueByKey(/*GameContext.Pointer.ChannelUserCount*/XorStr<0x47,37,0x4d12b3de>("\x00\x29\x24\x2f\x08\x23\x23\x3a\x2a\x28\x25\x7c\x03\x3b\x3c\x38\x23\x3d\x2b\x74\x18\x34\x3c\x30\x31\x05\x0d\x37\x10\x01\x17\x25\x08\x1d\x07\x1e"+0x4d12b3de).s) + (idxChannel * 4) ) = Count;
	}
}; CGameContext* pGameContext = NULL;

//==================================================================================================================================
class i3AIContext
{
public:
};

class CGameCharaAnimContext
{
public:
	i3AIContext* geti3AIContext(void)
	{
		return (i3AIContext*)*(DWORD*)(this + AddyEngine->GetAddyValueByKey(/*XFHPB.Pointer.QuickChange*/XorStr<0xAE,26,0xECC02C32>("\xF6\xE9\xF8\xE1\xF0\x9D\xE4\xDA\xDF\xD9\xCC\xDC\xC8\x95\xED\xC8\xD7\xDC\xAB\x82\xAA\xA2\xAA\xA2\xA3"+0xECC02C32).s));
	}
};

//==================================================================================================================================
class CGameUDPHandler
{
public:
	void WriteGameEvent_Fire (CGameCharaBase* Chara, D3DXVECTOR3* vTarget, CWeaponBase* WeaponBase)
	{
		typedef void (__thiscall* tWriteGameEvent_Fire) (CGameUDPHandler* Base, CGameCharaBase* Chara, D3DXVECTOR3* vTarget, CWeaponBase* WeaponBase);
		tWriteGameEvent_Fire WriteGameEvent_Fire = (tWriteGameEvent_Fire)(AddyEngine->GetAddyValueByKey(/*GameUDPHandler.Function.WriteGameEvent_Fire*/XorStr<0xA5,44,0x372A9B8B>("\xE2\xC7\xCA\xCD\xFC\xEE\xFB\xE4\xCC\xC0\xCB\xDC\xD4\xC0\x9D\xF2\xC0\xD8\xD4\xCC\xD0\xD5\xD5\x92\xEA\xCC\xD6\xB4\xA4\x85\xA2\xA9\xA0\x83\xB1\xAD\xA7\xBE\x94\x8A\xA4\xBC\xAA"+0x372A9B8B).s));
		return WriteGameEvent_Fire(this, Chara, vTarget, WeaponBase);
	}
}; CGameUDPHandler* pGameUDPHandler = NULL;

//==================================================================================================================================
class CWeaponBase
{
public:
	i3AIContext* geti3AIContext(void)
	{
		return (i3AIContext*)*(DWORD*)(this + AddyEngine->GetAddyValueByKey(/*XFHPB.Pointer.NoReload*/XorStr<0x4A,23,0xBDBFAD19>("\x12\x0D\x04\x1D\x0C\x61\x00\x3E\x3B\x3D\x20\x30\x24\x79\x16\x36\x08\x3E\x30\x32\x3F\x3B"+0xBDBFAD19).s));
	}
	void doLineCollision(D3DXVECTOR3* Start, D3DXVECTOR3* End, DWORD a1)
	{
		typedef void (__thiscall * tdoLineCollision)(CWeaponBase* Base, D3DXVECTOR3* Start, D3DXVECTOR3* End, DWORD a1);
		tdoLineCollision doLineCollision = (tdoLineCollision)(AddyEngine->GetAddyValueByKey(/*WeaponBase.Function.DoLineCollision*/XorStr<0x78,36,0x94273C30>("\x2F\x1C\x1B\x0B\x13\x13\x3C\x1E\xF3\xE4\xAC\xC5\xF1\xEB\xE5\xF3\xE1\xE6\xE4\xA5\xC8\xE2\xC2\xE6\xFE\xF4\xD1\xFC\xF8\xF9\xFF\xE4\xF1\xF6\xF4"+0x94273C30).s));
		return doLineCollision(this,Start,End,a1);
	}
	DWORD getSubAmmoCount(void)
	{
		typedef DWORD (__thiscall * tgetSubAmmoCount)(CWeaponBase* Base);
		tgetSubAmmoCount getSubAmmoCount = (tgetSubAmmoCount)(AddyEngine->GetAddyValueByKey(/*WeaponBase.Function.GetSubAmmoCount*/XorStr<0xD0,36,0x1B841E0D>("\x87\xB4\xB3\xA3\xBB\xBB\x94\xB6\xAB\xBC\xF4\x9D\xA9\xB3\xBD\xAB\x89\x8E\x8C\xCD\xA3\x80\x92\xB4\x9D\x8B\xAB\x86\x81\x82\xAD\x80\x85\x9F\x86"+0x1B841E0D).s));
		return getSubAmmoCount(this);
	}
	void Reset()
	{
		typedef void (__thiscall * tReset)(CWeaponBase* Base);
		tReset Reset = (tReset)(AddyEngine->GetAddyValueByKey(/*WeaponBase.Function.Reset*/XorStr<0x7E,26,0xC0214BC8>("\x29\x1A\xE1\xF1\xED\xED\xC6\xE4\xF5\xE2\xA6\xCF\xFF\xE5\xEF\xF9\xE7\xE0\xFE\xBF\xC0\xF6\xE7\xF0\xE2"+0xC0214BC8).s));
		return Reset(this);
	}
	void doFire()
	{
		typedef void (__thiscall * tdoFire)(CWeaponBase* Base, int a1, int a2);
		tdoFire doFire = (tdoFire)(AddyEngine->GetAddyValueByKey(/*WeaponBase.Function.DoFire*/XorStr<0xC3,27,0x82137AEF>("\x94\xA1\xA4\xB6\xA8\xA6\x8B\xAB\xB8\xA9\xE3\x88\xBA\xBE\xB2\xA6\xBA\xBB\xBB\xF8\x93\xB7\x9F\xB3\xA9\xB9"+0x82137AEF).s));
		return doFire(this,false,false);
	}
	void NET_Fire(D3DXVECTOR3* a1, D3DXVECTOR3* a2)
	{
		typedef void (__thiscall * tNET_Fire)(CWeaponBase* Base, D3DXVECTOR3* a1, D3DXVECTOR3* a2, int a3);
		tNET_Fire NET_Fire = (tNET_Fire)(WeaponBase.Function.NET_Fire);
		return NET_Fire(this, a1, a2, 1);
	}
};

//==================================================================================================================================
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

//==================================================================================================================================
class CGameCharaWeaponContext
{
public:
	CWeaponBase* getWeapon(int WeaponIndex)
	{
		typedef CWeaponBase* (__thiscall * tSafeGetWeapon)(CGameCharaWeaponContext* Base, int WeaponIndex);
		tSafeGetWeapon SafeGetWeapon = (tSafeGetWeapon)(AddyEngine->GetAddyValueByKey(/*GameCharaWeaponContext.Function.SafeGetWeapon*/XorStr<0x1F,46,0x0B5F2327>("\x58\x41\x4C\x47\x60\x4C\x44\x54\x46\x7F\x4C\x4B\x5B\x43\x43\x6D\x40\x5E\x45\x57\x4B\x40\x1B\x70\x42\x56\x5A\x4E\x52\x53\x53\x10\x6C\x21\x27\x27\x04\x21\x31\x11\x22\x29\x39\x25\x25"+0x0B5F2327).s));
		return SafeGetWeapon(this,WeaponIndex);
	}
	CWeaponBase* getCurrentWeapon(void)
	{
		typedef CWeaponBase* (__thiscall * tgetCurrentWeapon)(CGameCharaWeaponContext* Base);
		tgetCurrentWeapon getCurrentWeapon = (tgetCurrentWeapon)(GameCharaWeaponContext.Function.getCurrent);
		return getCurrentWeapon(this);
	}
	DWORD getCurrentWeaponIndex(void)
	{
		if(GameCharaWeaponContext.Function.DecryptWeaponIndex > NULL){
			typedef DWORD (__thiscall * tDecryptWeaponIndex)(CGameCharaWeaponContext* Base);
			tDecryptWeaponIndex DecryptWeaponIndex = (tDecryptWeaponIndex)GameCharaWeaponContext.Function.DecryptWeaponIndex;
			return DecryptWeaponIndex(this + GameCharaWeaponContext.Pointer.CurrentWeaponIndex);
		}
		else return *(DWORD*)(this + GameCharaWeaponContext.Pointer.CurrentWeaponIndex);
	}
};

//==================================================================================================================================
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
		tgetBones getBones = (tgetBones)(AddyEngine->GetAddyValueByKey(/*GameCharaBoneContext.Function.getBones*/XorStr<0x28,39,0x76950118>("\x6F\x48\x47\x4E\x6F\x45\x4F\x5D\x51\x73\x5D\x5D\x51\x76\x59\x59\x4C\x5C\x42\x4F\x12\x7B\x4B\x51\x23\x35\x2B\x2C\x2A\x6B\x21\x22\x3C\x0B\x25\x25\x29\x3E"+0x76950118).s));
		return (getBones(this) - AddyEngine->GetAddyValueByKey(/*GameCharaBoneContext.Size.BonesAlign*/XorStr<0x60,37,0x3F35F952>("\x27\x00\x0F\x06\x27\x0D\x07\x15\x09\x2B\x05\x05\x09\x2E\x01\x01\x04\x14\x0A\x07\x5A\x26\x1F\x0D\x1D\x57\x38\x14\x12\x18\x0D\x3E\xEC\xE8\xE5\xED"+0x3F35F952).s));
	}
	D3DXVECTOR3 getBonePosition(int BoneIndex)
	{
		D3DXMATRIX *pBone = (D3DXMATRIX*)(this->getBones());
		return D3DXVECTOR3(pBone[ BoneIndex ]._41, pBone[ BoneIndex ]._42, pBone[ BoneIndex ]._43);
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


//==================================================================================================================================
class CGameCharaCollisionContext
{
public:
	int getCrossHairTarget(void)
	{
		auto Func = (int (__thiscall*)(DWORD))AddyEngine->GetAddyValueByKey(/*GameCharaCollisionContext.Function.ReadData*/XorStr<0x58,44,0xB21E4442>("\x1F\x38\x37\x3E\x1F\x35\x3F\x2D\x01\x22\x0D\x0F\x08\x0C\x15\x0E\x07\x07\x29\x04\x02\x19\x0B\x17\x04\x5F\x34\x06\x1A\x16\x02\x1E\x17\x17\x54\x29\x19\x1C\x1A\x3B\xE1\xF5\xE3"+0xB21E4442).s);
		return Func((DWORD)this + AddyEngine->GetAddyValueByKey(/*GameCharaCollisionContext.Pointer.CrosshairTarget*/XorStr<0x28,50,0xED32A4CC>("\x6F\x48\x47\x4E\x6F\x45\x4F\x5D\x51\x72\x5D\x5F\x58\x5C\x45\x5E\x57\x57\x79\x54\x52\x49\x5B\x47\x34\x6F\x12\x2C\x2D\x2B\x32\x22\x3A\x67\x09\x39\x23\x3E\x3D\x27\x31\x38\x20\x07\x35\x27\x31\x32\x2C"+0xED32A4CC).s));
	}
	CGameCharaBase* GetCrosshairTarget()
	{
		typedef DWORD (__thiscall * tReadData)(DWORD BaseData);
		tReadData ReadData = (tReadData)(AddyEngine->GetAddyValueByKey(/*GameCharaCollisionContext.Function.ReadData*/XorStr<0x58,44,0xB21E4442>("\x1F\x38\x37\x3E\x1F\x35\x3F\x2D\x01\x22\x0D\x0F\x08\x0C\x15\x0E\x07\x07\x29\x04\x02\x19\x0B\x17\x04\x5F\x34\x06\x1A\x16\x02\x1E\x17\x17\x54\x29\x19\x1C\x1A\x3B\xE1\xF5\xE3"+0xB21E4442).s));

		return (CGameCharaBase*)ReadData((DWORD)this + AddyEngine->GetAddyValueByKey(/*GameCharaCollisionContext.Pointer.CrosshairTarget*/XorStr<0x28,50,0xED32A4CC>("\x6F\x48\x47\x4E\x6F\x45\x4F\x5D\x51\x72\x5D\x5F\x58\x5C\x45\x5E\x57\x57\x79\x54\x52\x49\x5B\x47\x34\x6F\x12\x2C\x2D\x2B\x32\x22\x3A\x67\x09\x39\x23\x3E\x3D\x27\x31\x38\x20\x07\x35\x27\x31\x32\x2C"+0xED32A4CC).s));
	}
};

//==================================================================================================================================
class CGameCharaBase
{
public:
	CGameCharaCollisionContext* getGameCharaCollisionContext(void)
	{
		typedef CGameCharaCollisionContext* (__thiscall * tgetGameCharaCollisionContext)(CGameCharaBase* Base);
		tgetGameCharaCollisionContext getGameCharaCollisionContext = (tgetGameCharaCollisionContext)(AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.getGameCharaCollisionContext*/XorStr<0x22,52,0x024DF36A>("\x65\x42\x49\x40\x65\x4F\x49\x5B\x4B\x69\x4D\x5E\x4B\x01\x76\x44\x5C\x50\x40\x5C\x59\x59\x16\x5E\x5F\x4F\x7B\x5C\x53\x5A\x03\x29\x23\x31\x25\x06\x29\x2B\x24\x20\x39\x22\x23\x23\x0D\x20\x3E\x25\x37\x2B\x20"+0x024DF36A).s));
		return getGameCharaCollisionContext(this);
	}
	CGameCharaBoneContext* getGameCharaBoneContext(void)
	{
		typedef CGameCharaBoneContext* (__thiscall * tgetGameCharaBoneContext)(CGameCharaBase* Base);
		tgetGameCharaBoneContext getGameCharaBoneContext = (tgetGameCharaBoneContext)(AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.getGameCharaBoneContext*/XorStr<0x27,47,0x6D2526B4>("\x60\x49\x44\x4F\x68\x44\x4C\x5C\x4E\x72\x50\x41\x56\x1A\x73\x43\x59\x5B\x4D\x53\x54\x52\x13\x59\x5A\x34\x06\x23\x2E\x21\x06\x2E\x26\x3A\x28\x08\x24\x22\x28\x0D\x20\x3E\x25\x37\x2B\x20"+0x6D2526B4).s));
		return getGameCharaBoneContext(this);
	}
	CGameCharaWeaponContext* getGameCharaWeaponContext(void)
	{
		typedef CGameCharaWeaponContext* (__thiscall * tgetGameCharaWeaponContext)(CGameCharaBase* Base);
		tgetGameCharaWeaponContext getGameCharaWeaponContext = (tgetGameCharaWeaponContext)(AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.getGameCharaWeaponContext*/XorStr<0xBC,49,0xB8504D0E>("\xFB\xDC\xD3\xDA\x83\xA9\xA3\xB1\xA5\x87\xA7\xB4\xAD\xE7\x8C\xBE\xA2\xAE\xBA\xA6\xBF\xBF\xFC\xB4\xB1\xA1\x91\xB6\xB5\xBC\x99\xB3\xBD\xAF\xBF\x88\x85\x80\x92\x8C\x8A\xA6\x89\x89\x9C\x8C\x92\x9F"+0xB8504D0E).s));
		return getGameCharaWeaponContext(this);
	}
	CGameCharaAnimContext* getGameCharaAnimContext(void)
	{
		typedef CGameCharaAnimContext* (__thiscall * tgetGameCharaAnimContext)(CGameCharaBase* Base);
		tgetGameCharaAnimContext getGameCharaAnimContext = (tgetGameCharaAnimContext)(AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.getGameCharaAnimContext*/XorStr<0x9C,47,0x8D6AE408>("\xDB\xFC\xF3\xFA\xE3\xC9\xC3\xD1\xC5\xE7\xC7\xD4\xCD\x87\xEC\xDE\xC2\xCE\xDA\xC6\xDF\xDF\x9C\xD4\xD1\xC1\xF1\xD6\xD5\xDC\xF9\xD3\xDD\xCF\xDF\xFE\xAE\xA8\xAF\x80\xAB\xAB\xB2\xA2\xB0\xBD"+0x8D6AE408).s));
		return getGameCharaAnimContext(this);
	}
	TSlotWeapon GetSlotWeapon()
	{
		int Slot = this->getGameCharaWeaponContext()->getCurrentWeaponIndex(); //
		switch (Slot)
		{
			case 0: return Primary; break;
			case 1: return Secondary; break;
			case 2: return Melle; break;
			case 3: return Explosive; break;
			case 4: return Special; break;
			case 5: return ExplosiveC4; break;
			case 6: return Teuapal; break;
		}
	}
	void setCharaWeapon(unsigned int WeaponSlot, unsigned int WeaponType, unsigned int WeaponIndex)
	{
		typedef void (__thiscall * tsetCharaWeapon)(CGameCharaBase* Base, unsigned int WeaponSlot, unsigned int WeaponType, unsigned int WeaponIndex);
		tsetCharaWeapon setCharaWeapon = (tsetCharaWeapon)(AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.setCharaWeapon*/XorStr<0xFC,38,0x2CE8BD3B>("\xBB\x9C\x93\x9A\x43\x69\x63\x71\x65\x47\x67\x74\x6D\x27\x4C\x7E\x62\x6E\x7A\x66\x7F\x7F\x3C\x60\x71\x61\x55\x7F\x79\x6B\x7B\x4C\x79\x7C\x6E\x70\x4E"+0x2CE8BD3B).s));
		return setCharaWeapon(this, WeaponSlot, WeaponType, WeaponIndex);
	}
	void SetCharaWeapon(unsigned int WeaponSlot,DWORD ValueByte)
	{
		return ((void(__thiscall*)(CGameCharaBase*,signed int, signed int,signed int))AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.setCharaWeapon*/XorStr<0xEA,38,0xED7261BD>("\xAD\x8A\x81\x88\xAD\x87\x91\x83\x93\xB1\x95\x86\x93\xD9\xBE\x8C\x94\x98\x88\x94\x91\x91\x2E\x72\x67\x77\x47\x6D\x67\x75\x69\x5E\x6F\x6A\x7C\x62\x60"+0xED7261BD).s))(this,WeaponSlot,_WeaponValue(ValueByte).WeaponType(),_WeaponValue(ValueByte).WeaponIndex());	
	}
	void eventFall(int numDmg)
	{
		typedef void (__thiscall * teventFall)(CGameCharaBase* Base, int a1, int a2, bool a3);
		teventFall eventFall = (teventFall)(AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.eventFall*/XorStr<0x5F,33,0x9857962C>("\x18\x01\x0C\x07\x20\x0C\x04\x14\x06\x2A\x08\x19\x0E\x42\x2B\x1B\x01\x13\x05\x1B\x1C\x1A\x5B\x13\x01\x1D\x17\x0E\x3D\x1D\x11\x12"+0x9857962C).s));
		return eventFall(this, numDmg, numDmg, false);
	}
	int getCharaNetIndex(void)
	{
		typedef int (__thiscall * tgetCharaNetIndex)(CGameCharaBase* Base);
		tgetCharaNetIndex getCharaNetIndex = (tgetCharaNetIndex)(AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.getCharaNetIdx*/XorStr<0x75,38,0x5CFC09E2>("\x32\x17\x1A\x1D\x3A\x12\x1A\x0E\x1C\x3C\x1E\xF3\xE4\xAC\xC5\xF1\xEB\xE5\xF3\xE1\xE6\xE4\xA5\xEB\xE8\xFA\xCC\xF8\xF0\xE0\xF2\xDA\xF0\xE2\xDE\xFC\xE1"+0x5CFC09E2).s));
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
		tgetCurHP getCurHP = (tgetCurHP)(AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.getCurHP*/XorStr<0x92,32,0x6B032C2F>("\xD5\xF2\xF9\xF0\xD5\xFF\xF9\xEB\xFB\xD9\xFD\xEE\xFB\xB1\xE6\xD4\xCC\xC0\xD0\xCC\xC9\xC9\x86\xCE\xCF\xDF\xEF\xD8\xDC\xE7\xE0"+0x6B032C2F).s));
		return getCurHP(this);
	}
	float getCurHP_Real()
	{
		__try{
			auto Func = (float(__thiscall*)(CGameCharaBase*))GameCharaBase.Function.getCurHP_Real;
			return Func(this);
		}__except (EXCEPTION_EXECUTE_HANDLER){}
	}
	void setInvicibleTime(float invicibleTime)
	{
		typedef void (__thiscall * tWriteData)(DWORD BaseData, float InputValue);
		tWriteData WriteData = (tWriteData)(AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.writeData*/XorStr<0x1c,33,0x2032aedb>("\x5b\x7c\x73\x7a\x63\x49\x43\x51\x45\x67\x47\x54\x4d\x07\x6c\x5e\x42\x4e\x5a\x46\x5f\x5f\x1c\x44\x46\x5c\x42\x52\x7c\x58\x4e\x5a"+0x2032aedb).s));
		WriteData((DWORD)this + AddyEngine->GetAddyValueByKey(/*GameCharaBase.Pointer.invicibleTime*/XorStr<0x22,36,0x1AFE3E88>("\x65\x42\x49\x40\x65\x4F\x49\x5B\x4B\x69\x4D\x5E\x4B\x01\x60\x5E\x5B\x5D\x40\x50\x44\x19\x51\x57\x4C\x52\x5F\x54\x5C\x53\x25\x15\x2B\x2E\x21"+0x1AFE3E88).s), invicibleTime);
	}
	void Cmd_Respawn(D3DXVECTOR3* RespawnPos)
    {
		typedef void (__thiscall * tCmd_Respawn)(CGameCharaBase* Base, D3DXVECTOR3* RespawnPos);
		tCmd_Respawn Cmd_Respawn = (tCmd_Respawn)(AddyEngine->GetAddyValueByKey("GameCharaBase.Function.Cmd_Respawn"));
		return Cmd_Respawn(this, RespawnPos);
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
	DWORD GetTeamColor()
	{
		if(this->isEnemy())return RED;
		return SKYBLUE;
	}
	DWORD GetPlayerColor()
	{
		if(this->isEnemy())return GREEN;
		return WHITE;
	}
};

//==================================================================================================================================
class CGameCharaManager 
{
public:
	CGameCharaBase* getCharaByNetIdx(int CharaIndex)
	{
		typedef CGameCharaBase* (__thiscall * tgetCharaByNetIdx)(CGameCharaManager* Base, int Index);
		tgetCharaByNetIdx getCharaByNetIdx = (tgetCharaByNetIdx)(AddyEngine->GetAddyValueByKey(/*GameCharaManager.Function.getCharaByNetIdx*/XorStr<0x6E,43,0xC9BCD00A>("\x29\x0E\x1D\x14\x31\x1B\x15\x07\x17\x3A\x19\x17\x1B\x1C\x19\x0F\x50\x39\xF5\xEF\xE1\xF7\xED\xEA\xE8\xA9\xEF\xEC\xFE\xC8\xE4\xEC\xFC\xEE\xD2\xE8\xDC\xF6\xE0\xDC\xF2\xEF"+0xC9BCD00A).s));
		return getCharaByNetIdx(this, CharaIndex);
	}
	CGameCharaBase* getCharaByNickname(char* szNickname)
	{
		for(int i = 0; i <= 15; i++)
		{
			CGameCharaBase* Chara = getCharaByNetIdx(i);
			if(!strcmp(Chara->getNickname(), szNickname))
			{
				return Chara;
			}
		}
		return NULL;
	}
	void SetCharaWeaponSetWithoutLock(CGameCharaBase* Chara, _NetCharaInfo* CharaInfo)
	{
		for(int i = 0; i < 5; i++)
			Chara->setCharaWeapon(i, CharaInfo->getWeaponValue(i).WeaponType(), CharaInfo->getWeaponValue(i).WeaponIndex());
	}
	void SetCharaWeaponSet(CGameCharaBase* Chara, _NetCharaInfo* CharaInfo)
	{
		typedef void (__thiscall * tSetCharaWeaponSet)(CGameCharaManager* Base, CGameCharaBase* Chara, _NetCharaInfo* CharaInfo);
		tSetCharaWeaponSet SetCharaWeaponSet = (tSetCharaWeaponSet)(GameCharaManager.Function.SetCharaWeaponSet);
		return SetCharaWeaponSet(this, Chara, CharaInfo);
	}
	CGameCharaBase* getLocalChara(void)
	{
		typedef CGameCharaBase* (__thiscall * tgetCharaByNetIdx)(CGameCharaManager* Base, int Index);
		tgetCharaByNetIdx getCharaByNetIdx = (tgetCharaByNetIdx)(AddyEngine->GetAddyValueByKey(/*GameCharaManager.Function.getCharaByNetIdx*/XorStr<0x10,43,0x56369F3A>("\x57\x70\x7F\x76\x57\x7D\x77\x65\x79\x54\x7B\x75\x7D\x7A\x7B\x6D\x0E\x67\x57\x4D\x47\x51\x4F\x48\x46\x07\x4D\x4E\x58\x6E\x46\x4E\x42\x50\x70\x4A\x7A\x50\x42\x7E\x5C\x41"+0x56369F3A).s));
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
				float PawnDistanceFromLocalPawn = DistanceBetweenVector( Chara->getGameCharaBoneContext()->getBonePosition(0), this->getLocalChara()->getGameCharaBoneContext()->getBonePosition(0) );
				if(PawnDistanceFromLocalPawn < Farthest)
				{
					Farthest = PawnDistanceFromLocalPawn;
					Result = Chara;
				}
			}
		}
		return Result;
	}
	bool isValidChara(int CharaIndex)
	{
		return( this->getCharaByNetIdx(CharaIndex) > NULL );
	}
	bool allPlayerAlive(void){
		for(int i = 0; i<=15; i++)
		{
			if(this->isValidChara(i) && !this->getCharaByNetIdx(i)->isAlive())
			{
				return false;
			}
		}
		return true;
	}
	bool allEnemyAlive(void)
	{
		for(int i = 0; i<=15; i++)
		{
			if(this->isValidChara(i) && !this->getCharaByNetIdx(i)->isAlive() && this->getCharaByNetIdx(i)->isEnemy())
			{
				return false;
			}
		}
		return true;
	}
	bool allPlayerDead(void){
		for(int i = 0; i<=15; i++)
		{
			if(this->isValidChara(i) && this->getCharaByNetIdx(i)->isAlive())
			{
				return false;
			}
		}
		return true;
	}
	bool allEnemyDead(void)
	{
		for(int i = 0; i<=15; i++)
		{
			if(this->isValidChara(i) && this->getCharaByNetIdx(i)->isAlive() && this->getCharaByNetIdx(i)->isEnemy())
			{
				return false;
			}
		}
		return true;
	}
	void RespawnChara(int Index, bool State)
	{
		typedef void (__thiscall * tRespawnChara)(CGameCharaManager* Base, int Index, bool State);
		tRespawnChara RespawnChara = (tRespawnChara)(AddyEngine->GetAddyValueByKey(/*GameCharaManager.Function.RespawnChara*/XorStr<0x7F,39,0xD8D33CF0>("\x38\xE1\xEC\xE7\xC0\xEC\xE4\xF4\xE6\xC5\xE8\xE4\xEA\xEB\xE8\xFC\xA1\xD6\xE4\xFC\xF0\xE0\xFC\xF9\xF9\xB6\xCB\xFF\xE8\xEC\xFC\xE9\xF1\xE3\xC9\xC3\xD1\xC5"+0xD8D33CF0).s));
		return RespawnChara(this, Index, State);
	}
	void RespawnChara(int iSlot)
	{	
		return ((void(__thiscall*)(CGameCharaManager*, int,bool))AddyEngine->GetAddyValueByKey(/*GameCharaManager.Function.RespawnChara*/XorStr<0x7F,39,0xD8D33CF0>("\x38\xE1\xEC\xE7\xC0\xEC\xE4\xF4\xE6\xC5\xE8\xE4\xEA\xEB\xE8\xFC\xA1\xD6\xE4\xFC\xF0\xE0\xFC\xF9\xF9\xB6\xCB\xFF\xE8\xEC\xFC\xE9\xF1\xE3\xC9\xC3\xD1\xC5"+0xD8D33CF0).s))(this, iSlot,1);	
	}
}; CGameCharaManager* pGameCharaManager = NULL;

//==================================================================================================================================
class i3InputMouse
{
public:
	float GetDeltaX()
	{
		typedef float (__thiscall * tGetDeltaX)(i3InputMouse* Base);
		tGetDeltaX GetDeltaX = (tGetDeltaX)( GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?GetDeltaX@i3InputMouse@@QAEMXZ") );
		return GetDeltaX(this);
	}
	float GetDeltaY()
	{
		typedef float (__thiscall * tGetDeltaY)(i3InputMouse* Base);
		tGetDeltaY GetDeltaY = (tGetDeltaY)( GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?GetDeltaY@i3InputMouse@@QAEMXZ") );
		return GetDeltaY(this);
	}
	float GetDeltaZ()
	{
		typedef float (__thiscall * tGetDeltaZ)(i3InputMouse* Base);
		tGetDeltaZ GetDeltaZ = (tGetDeltaZ)( GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?GetDeltaZ@i3InputMouse@@QAEMXZ") );
		return GetDeltaZ(this);
	}
	DWORD GetButtonState()
	{
		typedef DWORD (__thiscall * tGetButtonState)(i3InputMouse* Base);
		tGetButtonState GetButtonState = (tGetButtonState)( GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?GetButtonState@i3InputMouse@@QAEIXZ") );
		return GetButtonState(this);
	}
	DWORD GetStrokeButtonState()
	{
		typedef DWORD (__thiscall * tGetStrokeButtonState)(i3InputMouse* Base);
		tGetStrokeButtonState GetStrokeButtonState = (tGetStrokeButtonState)( GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?GetStrokeButtonState@i3InputMouse@@QAEIXZ") );
		return GetStrokeButtonState(this);
	}
	float GetX()
	{
		typedef float (__thiscall * tGetX)(i3InputMouse* Base);
		tGetX GetX = (tGetX)( GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?GetX@i3InputMouse@@QAEMXZ") );
		return GetX(this);
	}
	float GetY()
	{
		typedef float (__thiscall * tGetY)(i3InputMouse* Base);
		tGetY GetY = (tGetY)( GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?GetY@i3InputMouse@@QAEMXZ") );
		return GetY(this);
	}
	float GetZ()
	{
		typedef float (__thiscall * tGetZ)(i3InputMouse* Base);
		tGetZ GetZ = (tGetZ)( GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?GetZ@i3InputMouse@@QAEMXZ") );
		return GetZ(this);
	}
};

//==================================================================================================================================
class i3InputKeyboard
{
public:
	DWORD GetPressState(int I3I_KEY)
	{
		typedef DWORD (__thiscall * tGetPressState)(i3InputKeyboard* Base, int I3I_KEY);
		tGetPressState GetPressState = (tGetPressState)( GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?GetPressState@i3InputKeyboard@@QAEHW4I3I_KEY@@@Z") );
		return GetPressState(this, I3I_KEY);
	}
	DWORD GetRepeatState(int I3I_KEY)
	{
		typedef DWORD (__thiscall * tGetRepeatState)(i3InputKeyboard* Base, int I3I_KEY);
		tGetRepeatState GetRepeatState = (tGetRepeatState)( GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?GetRepeatState@i3InputKeyboard@@QAEHW4I3I_KEY@@@Z") );
		return GetRepeatState(this, I3I_KEY);
	}
	DWORD GetStrokeState(int I3I_KEY)
	{
		typedef DWORD (__thiscall * tGetStrokeState)(i3InputKeyboard* Base, int I3I_KEY);
		tGetStrokeState GetStrokeState = (tGetStrokeState)( GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?GetStrokeState@i3InputKeyboard@@QAEHW4I3I_KEY@@@Z") );
		return GetStrokeState(this, I3I_KEY);
	}
	DWORD SetPressState(int I3I_KEY, int Value)
	{
		typedef DWORD (__thiscall * tSetPressState)(i3InputKeyboard* Base, int I3I_KEY, int Value);
		tSetPressState SetPressState = (tSetPressState)( GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?SetPressState@i3InputKeyboard@@QAEHW4I3I_KEY@@@Z") );
		return SetPressState(this, I3I_KEY, Value);
	}
	DWORD SetStrokeState(int I3I_KEY, int Value)
	{
		typedef DWORD (__thiscall * tSetStrokeState)(i3InputKeyboard* Base, int I3I_KEY, int Value);
		tSetStrokeState SetStrokeState = (tSetStrokeState)( GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?SetStrokeState@i3InputKeyboard@@QAEHW4I3I_KEY@@@Z") );
		return SetStrokeState(this, I3I_KEY, Value);
	}
};

//==================================================================================================================================
class i3PhysixResult
{
public:
	float GetDistanceResult()
	{
		typedef float (__thiscall * tReadData)(DWORD BaseData);
		tReadData ReadData = (tReadData)(AddyEngine->GetAddyValueByKey(/*PhysixResult.Function.ReadData*/XorStr<0x35,31,0x359A3465>("\x65\x5E\x4E\x4B\x50\x42\x69\x59\x4E\x4B\x53\x34\x6F\x04\x36\x2A\x26\x32\x2E\x27\x27\x64\x19\x29\x2C\x2A\x0B\x31\x25\x33"+0x359A3465).s));
		return ReadData((DWORD)this + AddyEngine->GetAddyValueByKey(/*PhysixResult.Pointer.Distance*/XorStr<0x0F,30,0xB629A5A3>("\x5F\x78\x68\x61\x7A\x6C\x47\x73\x64\x6D\x75\x6E\x35\x4C\x72\x77\x71\x54\x44\x50\x0D\x60\x4C\x55\x53\x49\x47\x49\x4E"+0xB629A5A3).s));
	}
};

//==================================================================================================================================
class CGameFramework
{
public:
	i3InputKeyboard* geti3InputKeyboard(void)
	{
		return (i3InputKeyboard*)*(DWORD*)(this + AddyEngine->GetAddyValueByKey(/*GameFramework.Pointer.I3InputKeyboard*/XorStr<0x8F,38,0x7493CAC9>("\xC8\xF1\xFC\xF7\xD5\xE6\xF4\xFB\xF2\xEF\xF6\xE8\xF0\xB2\xCD\xF1\xF6\xCE\xD5\xC7\xD1\x8A\xEC\x95\xEE\xC6\xD9\xDF\xDF\xE7\xC8\xD7\xCD\xDF\xD0\xC0\xD7"+0x7493CAC9).s));
	}
	i3InputMouse* geti3InputMouse(void)
	{
		return (i3InputMouse*)*(DWORD*)(this + AddyEngine->GetAddyValueByKey(/*GameFramework.Pointer.I3InputMouse*/XorStr<0x56,35,0xFC579D4C>("\x11\x36\x35\x3C\x1C\x29\x3D\x30\x3B\x28\x0F\x13\x09\x4D\x34\x0A\x0F\x09\x1C\x0C\x18\x45\x25\x5E\x27\x01\x00\x04\x06\x3E\x1B\x00\x05\x12"+0xFC579D4C).s));
	}
	i3PhysixResult* RaycastClosest(i3CollideeLine* pLine, DWORD dwOption){
		typedef i3PhysixResult* (__thiscall * tRaycastClosest)(CGameFramework* Base, i3CollideeLine* pLine, DWORD dwOption);
		tRaycastClosest RaycastClosest = (tRaycastClosest)(AddyEngine->GetAddyValueByKey(/*GameFramework.Function.RaycastClosest*/XorStr<0x9E,38,0x6E0A0DA9>("\xD9\xFE\xCD\xC4\xE4\xD1\xC5\xC8\xC3\xD0\xC7\xDB\xC1\x85\xEA\xD8\xC0\xCC\xC4\xD8\xDD\xDD\x9A\xE7\xD7\xCE\xDB\xD8\xC9\xCF\xFF\xD1\xD1\xCC\xA5\xB2\xB6"+0x6E0A0DA9).s));
		return RaycastClosest(this, pLine, dwOption);
	}
}; CGameFramework* pGameFramework = NULL;

//==================================================================================================================================
void UpdateGameClass()
{
	// Init Render Context
	pRenderContext = (CRenderContext*)( *(DWORD*)(AddyEngine->GetAddyValueByKey(/*RenderContext.Base*/XorStr<0xED,19,0xF9C24CA7>("\xBF\x8B\x81\x94\x94\x80\xB0\x9B\x9B\x82\x92\x80\x8D\xD4\xB9\x9D\x8E\x9B"+0xF9C24CA7).s)) );
	// Init CGameContext
	pGameContext = (CGameContext*)( oReadBaseValue(AddyEngine->GetAddyValueByKey(/*GameContext.Base*/XorStr<0x11,17,0x2EE27975>("\x56\x73\x7E\x71\x56\x79\x79\x6C\x7C\x62\x6F\x32\x5F\x7F\x6C\x45"+0x2EE27975).s)) );
	// Init CGameCharaManager
	pGameCharaManager = (CGameCharaManager*)( oReadBaseValue(AddyEngine->GetAddyValueByKey(/*GameCharaManager.Base*/XorStr<0x4F,22,0x1D671608>("\x08\x31\x3C\x37\x10\x3C\x34\x24\x36\x15\x38\x34\x3A\x3B\x38\x2C\x71\x22\x00\x11\x06"+0x1D671608).s)) );
	// Init CGameFramework
	pGameFramework = (CGameFramework*)( oReadBaseValue(AddyEngine->GetAddyValueByKey(/*GameFramework.Base*/XorStr<0xF1,19,0x8EDBBDAD>("\xB6\x93\x9E\x91\xB3\x84\x96\x95\x9C\x8D\x94\x8E\x96\xD0\xBD\x61\x72\x67"+0x8EDBBDAD).s)) );
	// Init CGameUDPHandler
	typedef CGameUDPHandler* (__stdcall * tgetGameUDPHandler)();
	tgetGameUDPHandler getGameUDPHandler = (tgetGameUDPHandler)(AddyEngine->GetAddyValueByKey(/*GameUDPHandler.Function.GetBase*/XorStr<0x12,32,0x3D1F158B>("\x55\x72\x79\x70\x43\x53\x48\x51\x7B\x75\x78\x71\x7B\x6D\x0E\x67\x57\x4D\x47\x51\x4F\x48\x46\x07\x6D\x4E\x58\x6F\x4F\x5C\x55"+0x3D1F158B).s));
	pGameUDPHandler = (CGameUDPHandler*)(getGameUDPHandler());
}

CWeaponBase* LocalCharaWeapon = NULL;
CGameCharaBase* LocalChara = NULL;
int MouseClick = 0;
void UpdateLocalClass()
{
	if(pGameCharaManager->getLocalChara()){
		LocalChara = pGameCharaManager->getLocalChara();
		LocalCharaWeapon = pGameCharaManager->getLocalChara()->getGameCharaWeaponContext()->getCurrentWeapon();
	}
	if(pGameFramework->geti3InputMouse())
	{
		MouseClick = pGameFramework->geti3InputMouse()->GetButtonState();
	}
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