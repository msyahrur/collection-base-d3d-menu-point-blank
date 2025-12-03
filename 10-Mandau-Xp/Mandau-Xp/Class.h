//Bagus Tuyul
class CRenderContext
{
public:
	D3DXMATRIX* GetProjectMatrix(void)
	{
		typedef D3DXMATRIX* (__thiscall * tGetProjectMatrix)(CRenderContext* Base);
		tGetProjectMatrix GetProjectMatrix = (tGetProjectMatrix)(AddyEngine->GetAddyValueByKey(/*RenderContext.Function.GetProjectMatrix*/XorStr<0x8C,40,0xF89504AB>("\xDE\xE8\xE0\xEB\xF5\xE3\xD1\xFC\xFA\xE1\xF3\xEF\xEC\xB7\xDC\xEE\xF2\xFE\xEA\xF6\xCF\xCF\x8C\xE4\xC1\xD1\xF6\xD5\xC7\xC3\xCF\xC8\xD8\xE0\xCF\xDB\xC2\xD8\xCA"+0xF89504AB).s));
		return GetProjectMatrix(this);
	}
	D3DXMATRIX* GetViewMatrix(void)
	{
		typedef D3DXMATRIX* (__thiscall * tGetViewMatrix)(CRenderContext* Base);
		tGetViewMatrix GetViewMatrix = (tGetViewMatrix)(AddyEngine->GetAddyValueByKey(/*RenderContext.Function.GetViewMatrix*/XorStr<0x41,37,0x055D15D7>("\x13\x27\x2D\x20\x20\x34\x04\x27\x27\x3E\x2E\x34\x39\x60\x09\x25\x3F\x31\x27\x3D\x3A\x38\x79\x1F\x3C\x2E\x0D\x35\x38\x29\x12\x01\x15\x10\x0A\x1C"+0x055D15D7).s));
		return GetViewMatrix(this);
	}
	D3DXMATRIX* GetWorldMatrix(void)
	{
		typedef D3DXMATRIX* (__thiscall * tGetWorldMatrix)(CRenderContext* Base);
		tGetWorldMatrix GetWorldMatrix = (tGetWorldMatrix)(AddyEngine->GetAddyValueByKey(/*RenderContext.Function.GetWorldMatrix*/XorStr<0x4D,38,0xFD814B12>("\x1F\x2B\x21\x34\x34\x20\x10\x3B\x3B\x22\x32\x20\x2D\x74\x1D\x29\x33\x3D\x2B\x09\x0E\x0C\x4D\x23\x00\x12\x30\x07\x1B\x06\x0F\x21\x0C\x1A\x1D\x19\x09"+0xFD814B12).s));
		return GetWorldMatrix(this);
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
};
CRenderContext* pRenderContext = NULL;

class i3PhysixResult
{
public:
	char _unk001[0xA8];
	float GetDistanceResult()
	{
		typedef float (__thiscall * tReadData)(DWORD BaseData);
		tReadData ReadData = (tReadData)(AddyEngine->GetAddyValueByKey("PhysixResult.Function.ReadData"));
		return ReadData((DWORD)this + AddyEngine->GetAddyValueByKey("PhysixResult.Pointer.Distance"));
	}
};

class i3InputMouse
{
public:
	DWORD GetButtonState()
	{
		typedef DWORD (__thiscall * tGetButtonState)(i3InputMouse* Base);
		tGetButtonState GetButtonState = (tGetButtonState)( GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?GetButtonState@i3InputMouse@@QAEIXZ") );
		return GetButtonState(this);
	}
};

class CGameFramework
{
public:
	i3PhysixResult* RaycastClosest(i3CollideeLine* pLine, DWORD dwOption){
		typedef i3PhysixResult* (__thiscall * tRaycastClosest)(CGameFramework* Base, i3CollideeLine* pLine, DWORD dwOption);
		tRaycastClosest RaycastClosest = (tRaycastClosest)(AddyEngine->GetAddyValueByKey(/*GameFramework.Function.RaycastClosest*/XorStr<0xEF,38,0xAED11EFE>("\xA8\x91\x9C\x97\xB5\x86\x94\x9B\x92\x8F\x96\x88\x90\xD2\xBB\x8B\x91\x63\x75\x6B\x6C\x6A\x2B\x54\x66\x71\x6A\x6B\x78\x78\x4E\x62\x60\x63\x74\x61\x67"+0xAED11EFE).s));
		return RaycastClosest(this, pLine, dwOption);
	}
	i3InputMouse* geti3InputMouse(void)
	{
		return (i3InputMouse*)*(DWORD*)(this + AddyEngine->GetAddyValueByKey(/*GameFramework.Pointer.I3InputMouse*/XorStr<0x56,35,0xFC579D4C>("\x11\x36\x35\x3C\x1C\x29\x3D\x30\x3B\x28\x0F\x13\x09\x4D\x34\x0A\x0F\x09\x1C\x0C\x18\x45\x25\x5E\x27\x01\x00\x04\x06\x3E\x1B\x00\x05\x12"+0xFC579D4C).s));
	}
}; CGameFramework* pGameFramework = NULL;

class CGameContext 
{
public:
	DWORD setMySlotIdx(void)
	{
		return *(DWORD*)(this + AddyEngine->GetAddyValueByKey(/*GameContext.Pointer.MySlotIdx*/XorStr<0xC6,30,0xCA4F451A>("\x81\xA6\xA5\xAC\x89\xA4\xA2\xB9\xAB\xB7\xA4\xFF\x82\xBC\xBD\xBB\xA2\xB2\xAA\xF7\x97\xA2\x8F\xB1\xB1\xAB\xA9\x85\x9A"+0xCA4F451A).s));
	}
	bool isRedTeam(int CharaIndex)
	{
		if(CharaIndex % 2 == 0)return true;
		else return false;
	}
	bool getUserDeath(int iSlot) {
		auto Func = (bool(__thiscall*)(CGameContext*, int))ResultDeath;
		return Func(this, iSlot);
	}
	const char* getNickForSlot(int CharaIndex)
	{
		typedef const char* (__thiscall * tgetNickForSlot)(CGameContext* Base, int Index);
		tgetNickForSlot getNickForSlot = (tgetNickForSlot)(AddyEngine->GetAddyValueByKey(/*GameContext.Function.getNickForSlot*/XorStr<0xC5,36,0x9B884E46>("\x82\xA7\xAA\xAD\x8A\xA5\xA5\xB8\xA8\xB6\xBB\xFE\x97\xA7\xBD\xB7\xA1\xBF\xB8\xB6\xF7\xBD\xBE\xA8\x93\xB7\xBC\x8B\xA7\x8D\x91\xB7\x89\x89\x93"+0x9B884E46).s));
		return getNickForSlot(this,CharaIndex);
	}
	unsigned char GetPing(int iSlot) 
	{ 
		return ((unsigned char(__thiscall*)(CGameContext*, int))ResultPing)(this, iSlot);
	}
	__ScoreInfo* getIndividualScore(int iSlot) 
	{
		return ((__ScoreInfo*(__thiscall*)(CGameContext*, int))ResultgetIndividualScore)(this, iSlot);
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

class CGameCharaBase;
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
		tgetBones getBones = (tgetBones)(AddyEngine->GetAddyValueByKey(/*GameCharaBoneContext.Function.getBones*/XorStr<0x28,39,0x76950118>("\x6F\x48\x47\x4E\x6F\x45\x4F\x5D\x51\x73\x5D\x5D\x51\x76\x59\x59\x4C\x5C\x42\x4F\x12\x7B\x4B\x51\x23\x35\x2B\x2C\x2A\x6B\x21\x22\x3C\x0B\x25\x25\x29\x3E"+0x76950118).s));
		return (getBones(this) - AddyEngine->GetAddyValueByKey(/*GameCharaBoneContext.Size.BonesAlign*/XorStr<0x60,37,0x3F35F952>("\x27\x00\x0F\x06\x27\x0D\x07\x15\x09\x2B\x05\x05\x09\x2E\x01\x01\x04\x14\x0A\x07\x5A\x26\x1F\x0D\x1D\x57\x38\x14\x12\x18\x0D\x3E\xEC\xE8\xE5\xED"+0x3F35F952).s));
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
		return (i3AIContext*)*(DWORD*)(this + AddyEngine->GetAddyValueByKey(/*XFHPB.Pointer.QuickChange*/XorStr<0xAE,26,0xECC02C32>("\xF6\xE9\xF8\xE1\xF0\x9D\xE4\xDA\xDF\xD9\xCC\xDC\xC8\x95\xED\xC8\xD7\xDC\xAB\x82\xAA\xA2\xAA\xA2\xA3"+0xECC02C32).s));
	}
};

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
	void doFire()
	{
		typedef void (__thiscall * tdoFire)(CWeaponBase* Base, int a1, int a2);
		tdoFire doFire = (tdoFire)(AddyEngine->GetAddyValueByKey(/*WeaponBase.Function.DoFire*/XorStr<0xC3,27,0x82137AEF>("\x94\xA1\xA4\xB6\xA8\xA6\x8B\xAB\xB8\xA9\xE3\x88\xBA\xBE\xB2\xA6\xBA\xBB\xBB\xF8\x93\xB7\x9F\xB3\xA9\xB9"+0x82137AEF).s));
		return doFire(this,false,false);
	}
	void Reset()
	{
		typedef void (__thiscall * tReset)(CWeaponBase* Base);
		tReset Reset = (tReset)(AddyEngine->GetAddyValueByKey(/*WeaponBase.Function.Reset*/XorStr<0x7E,26,0xC0214BC8>("\x29\x1A\xE1\xF1\xED\xED\xC6\xE4\xF5\xE2\xA6\xCF\xFF\xE5\xEF\xF9\xE7\xE0\xFE\xBF\xC0\xF6\xE7\xF0\xE2"+0xC0214BC8).s));
		return Reset(this);
	}
	DWORD getSubAmmoCount(void)
	{
		typedef DWORD (__thiscall * tgetSubAmmoCount)(CWeaponBase* Base);
		tgetSubAmmoCount getSubAmmoCount = (tgetSubAmmoCount)(AddyEngine->GetAddyValueByKey(/*WeaponBase.Function.GetSubAmmoCount*/XorStr<0xD0,36,0x1B841E0D>("\x87\xB4\xB3\xA3\xBB\xBB\x94\xB6\xAB\xBC\xF4\x9D\xA9\xB3\xBD\xAB\x89\x8E\x8C\xCD\xA3\x80\x92\xB4\x9D\x8B\xAB\x86\x81\x82\xAD\x80\x85\x9F\x86"+0x1B841E0D).s));
		return getSubAmmoCount(this);
	}
	void NET_Fire(D3DXVECTOR3* a1, D3DXVECTOR3* a2)
	{
		typedef void (__thiscall * tNET_Fire)(CWeaponBase* Base, D3DXVECTOR3* a1, D3DXVECTOR3* a2, int a3);
		tNET_Fire NET_Fire = (tNET_Fire)(ResultNET_Fire);
		return NET_Fire(this, a1, a2, 1);
	}
};
CWeaponBase* LocalCharaWeapon = NULL;

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

class CGameCharaBase
{
public:
	CGameCharaBoneContext* getGameCharaBoneContext(void)
	{
		typedef CGameCharaBoneContext* (__thiscall * tgetGameCharaBoneContext)(CGameCharaBase* Base);
		tgetGameCharaBoneContext getGameCharaBoneContext = (tgetGameCharaBoneContext)AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.getGameCharaBoneContext*/XorStr<0x27,47,0x6D2526B4>("\x60\x49\x44\x4F\x68\x44\x4C\x5C\x4E\x72\x50\x41\x56\x1A\x73\x43\x59\x5B\x4D\x53\x54\x52\x13\x59\x5A\x34\x06\x23\x2E\x21\x06\x2E\x26\x3A\x28\x08\x24\x22\x28\x0D\x20\x3E\x25\x37\x2B\x20"+0x6D2526B4).s);
		return getGameCharaBoneContext(this);
	}
	CGameCharaWeaponContext* getGameCharaWeaponContext(void)
	{
		typedef CGameCharaWeaponContext* (__thiscall * tgetGameCharaWeaponContext)(CGameCharaBase* Base);
		tgetGameCharaWeaponContext getGameCharaWeaponContext = (tgetGameCharaWeaponContext)AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.getGameCharaWeaponContext*/XorStr<0xBC,49,0xB8504D0E>("\xFB\xDC\xD3\xDA\x83\xA9\xA3\xB1\xA5\x87\xA7\xB4\xAD\xE7\x8C\xBE\xA2\xAE\xBA\xA6\xBF\xBF\xFC\xB4\xB1\xA1\x91\xB6\xB5\xBC\x99\xB3\xBD\xAF\xBF\x88\x85\x80\x92\x8C\x8A\xA6\x89\x89\x9C\x8C\x92\x9F"+0xB8504D0E).s);
		return getGameCharaWeaponContext(this);
	}
	CGameCharaCollisionContext* getGameCharaCollisionContext(void)
	{
		typedef CGameCharaCollisionContext* (__thiscall * tgetGameCharaCollisionContext)(CGameCharaBase* Base);
		tgetGameCharaCollisionContext getGameCharaCollisionContext = (tgetGameCharaCollisionContext)(AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.getGameCharaCollisionContext*/XorStr<0x22,52,0x024DF36A>("\x65\x42\x49\x40\x65\x4F\x49\x5B\x4B\x69\x4D\x5E\x4B\x01\x76\x44\x5C\x50\x40\x5C\x59\x59\x16\x5E\x5F\x4F\x7B\x5C\x53\x5A\x03\x29\x23\x31\x25\x06\x29\x2B\x24\x20\x39\x22\x23\x23\x0D\x20\x3E\x25\x37\x2B\x20"+0x024DF36A).s));
		return getGameCharaCollisionContext(this);
	}
	CGameCharaAnimContext* getGameCharaAnimContext(void)
	{
		typedef CGameCharaAnimContext* (__thiscall * tgetGameCharaAnimContext)(CGameCharaBase* Base);
		tgetGameCharaAnimContext getGameCharaAnimContext = (tgetGameCharaAnimContext)(AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.getGameCharaAnimContext*/XorStr<0x9C,47,0x8D6AE408>("\xDB\xFC\xF3\xFA\xE3\xC9\xC3\xD1\xC5\xE7\xC7\xD4\xCD\x87\xEC\xDE\xC2\xCE\xDA\xC6\xDF\xDF\x9C\xD4\xD1\xC1\xF1\xD6\xD5\xDC\xF9\xD3\xDD\xCF\xDF\xFE\xAE\xA8\xAF\x80\xAB\xAB\xB2\xA2\xB0\xBD"+0x8D6AE408).s));
		return getGameCharaAnimContext(this);
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
	void eventFall(int numDmg)
	{
		typedef void (__thiscall * teventFall)(CGameCharaBase* Base, int a1, int a2, bool a3);
		teventFall eventFall = (teventFall)(AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.eventFall*/XorStr<0x5F,33,0x9857962C>("\x18\x01\x0C\x07\x20\x0C\x04\x14\x06\x2A\x08\x19\x0E\x42\x2B\x1B\x01\x13\x05\x1B\x1C\x1A\x5B\x13\x01\x1D\x17\x0E\x3D\x1D\x11\x12"+0x9857962C).s));
		return eventFall(this, numDmg, numDmg, false);
	}
	void Cmd_Respawn(D3DXVECTOR3* RespawnPos)
    {
		typedef void (__thiscall * tCmd_Respawn)(CGameCharaBase* Base, D3DXVECTOR3* RespawnPos);
		tCmd_Respawn Cmd_Respawn = (tCmd_Respawn)(AddyEngine->GetAddyValueByKey("GameCharaBase.Function.Cmd_Respawn"));
		return Cmd_Respawn(this, RespawnPos);
    }
	void setInvicibleTime(float invicibleTime)
	{
		typedef void (__thiscall * tWriteData)(DWORD BaseData, float InputValue);
		tWriteData WriteData = (tWriteData)(AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.writeData*/XorStr<0x1c,33,0x2032aedb>("\x5b\x7c\x73\x7a\x63\x49\x43\x51\x45\x67\x47\x54\x4d\x07\x6c\x5e\x42\x4e\x5a\x46\x5f\x5f\x1c\x44\x46\x5c\x42\x52\x7c\x58\x4e\x5a"+0x2032aedb).s));
		WriteData((DWORD)this + AddyEngine->GetAddyValueByKey(/*GameCharaBase.Pointer.invicibleTime*/XorStr<0x22,36,0x1AFE3E88>("\x65\x42\x49\x40\x65\x4F\x49\x5B\x4B\x69\x4D\x5E\x4B\x01\x60\x5E\x5B\x5D\x40\x50\x44\x19\x51\x57\x4C\x52\x5F\x54\x5C\x53\x25\x15\x2B\x2E\x21"+0x1AFE3E88).s), invicibleTime);
	}
	TSlotWeapon GetSlotWeapon()
	{
		int Slot = this->getGameCharaWeaponContext()->getCurrentWeaponIndex();
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
	bool isAlive(void)
	{
		return( this->getCurHP() > 0 );
	}
	bool isLocal(void)
	{
		return ( this->getCharaNetIndex() == pGameContext->setMySlotIdx());
	}
	bool isEnemy(void)
	{
		return (pGameContext->isRedTeam(this->getCharaNetIndex()) != pGameContext->isRedTeam(pGameContext->setMySlotIdx()));
	}
	bool isVisible(int BoneTargetIndex)
	{
		return GetPlayerVisibleStatus(pGameContext->setMySlotIdx(),this->getCharaNetIndex(),BoneTargetIndex);
	}
}; CGameCharaBase* pGameCharaBase;

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

class CGameCharaManager
{
public:
	CGameCharaBase* getLocalChara(void)
	{
		typedef CGameCharaBase* (__thiscall * tgetCharaByNetIdx)(CGameCharaManager* Base, int Index);
		tgetCharaByNetIdx getCharaByNetIdx = (tgetCharaByNetIdx)(AddyEngine->GetAddyValueByKey(/*GameCharaManager.Function.getCharaByNetIdx*/XorStr<0x10,43,0x56369F3A>("\x57\x70\x7F\x76\x57\x7D\x77\x65\x79\x54\x7B\x75\x7D\x7A\x7B\x6D\x0E\x67\x57\x4D\x47\x51\x4F\x48\x46\x07\x4D\x4E\x58\x6E\x46\x4E\x42\x50\x70\x4A\x7A\x50\x42\x7E\x5C\x41"+0x56369F3A).s));
		return getCharaByNetIdx(this, pGameContext->setMySlotIdx());
	}
	CGameCharaBase* getCharaByNetIdx(int CharaIndex)
	{
		typedef CGameCharaBase* (__thiscall * tgetCharaByNetIdx)(CGameCharaManager* Base, int Index);
		tgetCharaByNetIdx getCharaByNetIdx = (tgetCharaByNetIdx)(AddyEngine->GetAddyValueByKey(/*GameCharaManager.Function.getCharaByNetIdx*/XorStr<0x6E,43,0xC9BCD00A>("\x29\x0E\x1D\x14\x31\x1B\x15\x07\x17\x3A\x19\x17\x1B\x1C\x19\x0F\x50\x39\xF5\xEF\xE1\xF7\xED\xEA\xE8\xA9\xEF\xEC\xFE\xC8\xE4\xEC\xFC\xEE\xD2\xE8\xDC\xF6\xE0\xDC\xF2\xEF"+0xC9BCD00A).s));
		return getCharaByNetIdx(this, CharaIndex);
	}
	void RespawnChara(int iSlot)
	{	
		return ((void(__thiscall*)(CGameCharaManager*, int,bool))AddyEngine->GetAddyValueByKey(/*GameCharaManager.Function.RespawnChara*/XorStr<0x7F,39,0xD8D33CF0>("\x38\xE1\xEC\xE7\xC0\xEC\xE4\xF4\xE6\xC5\xE8\xE4\xEA\xEB\xE8\xFC\xA1\xD6\xE4\xFC\xF0\xE0\xFC\xF9\xF9\xB6\xCB\xFF\xE8\xEC\xFC\xE9\xF1\xE3\xC9\xC3\xD1\xC5"+0xD8D33CF0).s))(this, iSlot,1);	
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
}; CGameCharaManager* pGameCharaManager = NULL;

bool IsInBattle()
{
	if(pGameCharaManager->getLocalChara() > NULL)return true;
	return false; 
}

class CGameUDPHandler
{
public:
	void WriteGameEvent_Fire (CGameCharaBase* Chara, D3DXVECTOR3* vTarget, CWeaponBase* WeaponBase)
	{
		typedef void (__thiscall* tWriteGameEvent_Fire) (CGameUDPHandler* Base, CGameCharaBase* Chara, D3DXVECTOR3* vTarget, CWeaponBase* WeaponBase);
		tWriteGameEvent_Fire WriteGameEvent_Fire = (tWriteGameEvent_Fire)(AddyEngine->GetAddyValueByKey(/*GameUDPHandler.Function.WriteGameEvent_Fire*/XorStr<0xD2,44,0xC1F89C20>("\x95\xB2\xB9\xB0\x83\x93\x88\x91\xBB\xB5\xB8\xB1\xBB\xAD\xCE\xA7\x97\x8D\x87\x91\x8F\x88\x86\xC7\xBD\x99\x85\x99\x8B\xA8\x91\x9C\x97\xB6\x82\x90\x98\x83\xA7\xBF\x93\x89\x99"+0xC1F89C20).s));
		return WriteGameEvent_Fire(this, Chara, vTarget, WeaponBase);
	}
};
CGameUDPHandler* pGameUDPHandler = NULL;

void UpdateGameClass()
{
	pRenderContext = (CRenderContext*)( *(DWORD*)(AddyEngine->GetAddyValueByKey("RenderContext.Base")));
	pGameContext = (CGameContext*)(oReadBaseValue(AddyEngine->GetAddyValueByKey("GameContext.Base")));
	pGameCharaManager = (CGameCharaManager*)( oReadBaseValue(AddyEngine->GetAddyValueByKey("GameCharaManager.Base")));
	pGameFramework = (CGameFramework*)( oReadBaseValue(AddyEngine->GetAddyValueByKey("GameFramework.Base")));
}


void UpdateLocalClass()
{
	if(pGameCharaManager->getLocalChara()){
		pGameCharaBase = pGameCharaManager->getLocalChara();
		LocalCharaWeapon = pGameCharaManager->getLocalChara()->getGameCharaWeaponContext()->getCurrentWeapon();
	}
}