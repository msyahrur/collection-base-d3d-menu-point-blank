//------------------------------------------------------------------------------//
//							Coded By Zaki Mubarak									//
//							Date Create : 11 April 2016							//
//------------------------------------------------------------------------------//
bool IsInBattle();
#include "cLoggerIndo.h"
//#include "cLoggerKaybo.h"
LPDIRECT3DTEXTURE9 Red;
LPDIRECT3DTEXTURE9 Blue;
#pragma once using namespace std;
//static D3DVIEWPORT9 pViewPort;
bool GetUserBone( D3DXVECTOR3 &Out,int getBoneIndex ,int Index);
D3DXVECTOR3 getBonePosition(int getBoneIndex ,int Index);
DWORD ModifyTargetBase[100] = {0};

enum TStageGame {SERVER, CHANNEL, LOBBY, AWAITING, PLAYING };
enum TSlotWeapon {Primary, Secondary, Melle, Explosive, Special,ExplosiveC4,Teuapal};

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

#include "i3RenderContext.h"
//#include "i3CollideeLine.h"
#include "CGameFramework.h"
#include "CGameContext.h"
#include "CGameCharaBase.h"
#include "CGameCharaManager.h"
#include "CGameUDPHandler.h"

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
//---------------------------------------------------------------------------
pSetEndVector *SetEndVector = NULL;
typedef float (__thiscall * tGetLocalTime)(DWORD Base);
tGetLocalTime pGetLocalTime;
float __fastcall hkGetLocalTime(DWORD Base)
{
		float retVal = pGetLocalTime(Base);
		for(int i = 0; i < 100; i++)
		{
			if(ModifyTargetBase[i] > NULL && ModifyTargetBase[i] == Base){
				if(i == 0)retVal = 2.519999862f;
				if(i == 1 || i == 2){
					if(GetKeyboardPressState(DIK_R)){
						__asm
						{
							lea edx,retVal
								mov [edx + 3],0x41
						}
					}
				}
				break;
			}
		}
		return retVal;

}

bool bHookedLT = false;
void HookLocalTime()
{
if(bHookedLT)return;
	pGetLocalTime = (tGetLocalTime)MakePTR((PBYTE)ResultImport_i3AiContext_getLocalTime,(DWORD)hkGetLocalTime);
	bHookedLT = true;
}
//---------------------------------------------------------------------------
DWORD pSetEnd;
_declspec(naked) void hkSetEnd(){
	__asm 
	{
		sub esp, 0x8
		push esi
	}
	DWORD dwOrigLine;
	__asm
	{
		mov eax,[esp+0x10+0x4];
		mov [dwOrigLine],eax
	}
	dwOrigLine = SetEndVector->GetSetEndVector(dwOrigLine);
	__asm
	{
		mov eax,[dwOrigLine];
		mov [esp+0x10+0x4],eax
	}
	__asm 
	{
		pop esi
		add esp, 0x8
	}
	__asm jmp pSetEnd;
}

bool bHookedTele = false;
void HookSetEnd()
{
	SetEndVector = new pSetEndVector();
	if(bHookedTele)return;
	pSetEnd = MakePTR((PBYTE)0xDFCE04,(DWORD)hkSetEnd);
	bHookedTele = true;
}
//---------------------------------------------------------------------------
WeaponBase* LocalCharaWeapon = NULL;
DWORD dwBurst, dwRet_Burst, dwMyWeapon = NULL;
DWORD dwSetBurst = 1;
__declspec(naked) void hkBurst()
{
	__asm {
		call eax
		mov ecx, [ebp-0x4]
		cmp [LocalCharaWeapon], ecx
		jne SkipPatch
	}
		if(SetBurst){
			__asm {
			mov eax,[dwSetBurst]
			}
		}
__asm {
SkipPatch:
		mov dword ptr[ebp-0x58],eax
		jmp [dwRet_Burst]
	}
}

void HookBurst()
{
	dwBurst = 0x616D99;
	dwRet_Burst = dwBurst + 5;
	LocalCharaWeapon = CGameCharaManager::g_pCharaManager()->getLocalChara()->m_pWeaponContext()->getCurrent();
	hook((PDWORD)dwBurst, (PDWORD)hkBurst);

	Write_((void*)(dwBurst + 39), (char*)"\xEB", 1);	
}
//---------------------------------------------------------------------------
bool GetUserBone( D3DXVECTOR3 &Out,int getBoneIndex ,int Index)
{__try
{
CGameCharaBase* GameBase = CGameCharaManager::g_pCharaManager()->GetCharaByNetIdx(Index);
	if (GameBase && GameBase->m_pBoneContext())
	{
		Out.x = GameBase->m_pBoneContext()->m_Bone()[getBoneIndex]._41;
		Out.y = GameBase->m_pBoneContext()->m_Bone()[getBoneIndex]._42;
		Out.z = GameBase->m_pBoneContext()->m_Bone()[getBoneIndex]._43;
		return true;
	}
	return false;
}__except (EXCEPTION_EXECUTE_HANDLER){return false;}
}

D3DXVECTOR3 getBonePosition(int getBoneIndex ,int Index)
{
D3DXVECTOR3 Out;
CGameCharaBase* GameBase = CGameCharaManager::g_pCharaManager()->GetCharaByNetIdx(Index);
if (GameBase && GameBase->m_pBoneContext())
{
		Out.x = GameBase->m_pBoneContext()->m_Bone()[getBoneIndex]._41;
		Out.y = GameBase->m_pBoneContext()->m_Bone()[getBoneIndex]._42;
		Out.z = GameBase->m_pBoneContext()->m_Bone()[getBoneIndex]._43;
}
return Out;
}

int GetMySlotAUTOHS()
{
	BYTE MyTeam = *(BYTE*) ((DWORD)CGameContext::g_pGameContext() + ResultPTRTeam);
	return MyTeam;
}

int GetMyCharaIndex()
{
	BYTE MyTeam = *(BYTE*) ((DWORD)CGameContext::g_pGameContext() + ResultPTRTeam);
	return MyTeam;
}

int GetMyCharaIndex(unsigned int Index)
{
	BYTE MyTeam = *(BYTE*) ((DWORD)CGameContext::g_pGameContext() + ResultPTRTeam);
	Index=MyTeam;
	return Index;
}

typedef DWORD (__thiscall * tgetCharaByNetIdxAll)(DWORD CGameCharaManager,int Index);
tgetCharaByNetIdxAll getCharaByNetIdxAll;

DWORD GetGameAllCharaBase()
{
for(int Index = 0; Index <= 16; Index++){
getCharaByNetIdxAll = (tgetCharaByNetIdxAll)((DWORD)ResultGetCharaByNetIdx); 
return getCharaByNetIdxAll((DWORD)CGameCharaManager::g_pCharaManager(),Index);
}
}

typedef DWORD (__thiscall * tgetCharaByNetIdx)(DWORD CGameCharaManager, int Index);
tgetCharaByNetIdx getCharaByNetIdx;

DWORD GetGameCharaBase(int Index)
{
getCharaByNetIdx = (tgetCharaByNetIdx)((DWORD)ResultGetCharaByNetIdx); 
return getCharaByNetIdx((DWORD)CGameCharaManager::g_pCharaManager(),Index);
}

typedef int (__thiscall * tgetCurHP)(DWORD CGameCharaBase);
tgetCurHP getCurHP;
float GetPlayerHP (int Index)
{
	DWORD CGameCharaBase = GetGameCharaBase(Index);
	if(CGameCharaBase)
	{
		getCurHP = (tgetCurHP)((DWORD)ResultgetCurHP_Real); 
		return (float)getCurHP(CGameCharaBase);
	}
return NULL;
}

bool GetUserLifeX(int iSlot)
{
	if(CGameContext::g_pGameContext()->getUserDeath(iSlot) == 0)
	{
		return (GetPlayerHP(iSlot) > 0.1f);
	}
	return false;
}

 typedef DWORD (__thiscall * tgetCurrentWeapon)(DWORD CGameCharaWeaponContext);
tgetCurrentWeapon getCurrentWeapon;
DWORD GetCurrentWeapon(DWORD CGameCharaWeaponContext)
{
	getCurrentWeapon = (tgetCurrentWeapon)(ResultGetCurrent);
	return getCurrentWeapon(CGameCharaWeaponContext);
}

typedef DWORD (__thiscall * tgetGameCharaWeaponContext)(DWORD CGameCharaBase);
tgetGameCharaWeaponContext getGameCharaWeaponContext;
DWORD GetGameCharaWeaponContext(DWORD CGameCharaBase)
{
	getGameCharaWeaponContext = (tgetGameCharaWeaponContext)(ResultCallm_pWeaponContext);
	return getGameCharaWeaponContext(CGameCharaBase);

}

//============================DoLineColl=========================//

int cTeamFind(int iSlot) 
{ 
	__try
	{
		if (iSlot%2 == 0) 
			return 1; 
		else 
			return 2; 
	}__except ( EXCEPTION_EXECUTE_HANDLER ) {return 0;}
}
//============================DoLineColl=========================//
typedef void(__thiscall * tSet_OnHitCharaByExplosion)(DWORD,int, D3DXVECTOR3*, D3DXVECTOR3*);
tSet_OnHitCharaByExplosion oSet_OnHitCharaByExplosion;
void Set_OnHitCharaByExplosion(DWORD AllChara,D3DXVECTOR3 A, D3DXVECTOR3 B)
{
	if(AllChara)
	{
		oSet_OnHitCharaByExplosion = (tSet_OnHitCharaByExplosion)Result_OnCheckCollisionByExplosion;
		return oSet_OnHitCharaByExplosion(AllChara,0x22,&A,&B);
	}
}
//============================SetNET_Fire=========================//
typedef void(__thiscall * tSetNET_Fire)(DWORD,D3DXVECTOR3*,D3DXVECTOR3*,int);
tSetNET_Fire oSetNET_Fire;
void SetNET_Fire(DWORD WeaponBase,D3DXVECTOR3 A, D3DXVECTOR3 B)
{
	if(WeaponBase)
	{
		oSetNET_Fire = (tSetNET_Fire)ResultNET_Fire;
		return oSetNET_Fire(WeaponBase,&A,&B,1);
	}
}
//============================SetKiller=========================//
typedef void(__thiscall * tSetKiller)(DWORD, int, int);
tSetKiller oSetKiller;
void SetKiller(DWORD WeaponBase,int A, int B)
{
	if(WeaponBase)
	{
		oSetKiller 	   = (tSetKiller)ResultSetKiller;
		return oSetKiller(WeaponBase, 0,0);
	}
}

//============================DoLineColl=========================//
typedef void(__thiscall * tDoLineColl)(DWORD, D3DXVECTOR3 *, D3DXVECTOR3 *, int);
tDoLineColl oDoLineColl;
void SetDoLineColl(DWORD WeaponBase, D3DXVECTOR3 Loc, D3DXVECTOR3 Target, int Idx)
{
	if(WeaponBase)
	{
		oDoLineColl 	   = (tDoLineColl)ResultDoLineCollision;
		return oDoLineColl(WeaponBase, &Loc, &Target, cTeamFind(Idx));
	}
}

//============================WriteGameEvent=========================//
typedef void(__thiscall * tWriteGameEvent)(DWORD GameUDP, DWORD CGameCharaBase, D3DXVECTOR3*, DWORD WeaponBase);
tWriteGameEvent WriteGameEvent;
void SetWriteGameEvent(DWORD WeaponBase, D3DXVECTOR3 Loc)
{
	if(WeaponBase)
	{
		DWORD CGameCharaBase = GetGameCharaBase(GetMyCharaIndex());
		WriteGameEvent = (tWriteGameEvent)ResultWriteGameEvent_Fire;	
		return WriteGameEvent(WeaponBase, CGameCharaBase, &Loc, WeaponBase);
	}
}
//=========================================GetVectorBone=============================================//	
bool GetVectorBone( D3DXVECTOR3 &Out ,int BoneIdx,int Index)
{
	DWORD CGameCharaFlag =  *((DWORD*)(DWORD)CGameCharaManager::g_pCharaManager() + Index + 5);
	if(CGameCharaFlag && BoneIdx < 34)
	{
		DWORD Root = *(DWORD*)(CGameCharaFlag + (ResultPTRVectorBone + (BoneIdx*0x10)));
		D3DXMATRIX &DefaultVariable = *(D3DXMATRIX*)(Root + 0xB0);//ResultPTRDefaultVariable
		Out.x = DefaultVariable._41; 
		Out.y = DefaultVariable._42; 
		Out.z = DefaultVariable._43; 
		return true;
	}
	return false; 
}

D3DXVECTOR3 GetVectorBonePos(int Index ,int BoneIdx)
{
	D3DXVECTOR3 Out;
	DWORD CGameCharaFlag =  *((DWORD*)(DWORD)CGameCharaManager::g_pCharaManager() + Index + 5);
	if(CGameCharaFlag && BoneIdx < 34)
	{
		DWORD Root = *(DWORD*)(CGameCharaFlag + (ResultPTRVectorBone + (BoneIdx*0x10)));
		D3DXMATRIX &DefaultVariable = *(D3DXMATRIX*)(Root + 0xB0);//ResultPTRDefaultVariable
		Out.x = DefaultVariable._41; 
		Out.y = DefaultVariable._42; 
		Out.z = DefaultVariable._43; 
	}
	return Out;
}

LPD3DXLINE pLine;
LPD3DXFONT pFont;
LPD3DXFONT pFont2;
LPD3DXFONT fName;
D3DXVECTOR3 vStart,vEnd,OnXScreen,OnYScreen,OnScreen;
bool Menu = true;
#define WHITE			D3DCOLOR_ARGB(255, 255, 255, 255)
#define RED				D3DCOLOR_ARGB(255, 245, 000, 000)
#define GREEN			D3DCOLOR_ARGB(255, 000, 255, 000)
#define BLUE			D3DCOLOR_ARGB(255, 000, 000, 255) 
#define BLACK			D3DCOLOR_ARGB(150, 000, 000, 000)
#define SKYBLUE			D3DCOLOR_ARGB(255, 0, 180, 255)

//COLOR PALETTES
struct COLORS
{

	D3DCOLOR Black, White, LightGray, DarkGray, Pink, Red,
		Maroon, Magenta, Brown, Yellow, LightGreen, 
                      Green, DarkGreen, LightBlue, Blue, DarkBlue, Purple;
	COLORS()
		:Black			(D3DCOLOR_ARGB(0,0,0,255)),
		 White			(D3DCOLOR_ARGB(255,255,255,255)),
		 LightGray	        (D3DCOLOR_ARGB(195,195,195,255)),
		 DarkGray		(D3DCOLOR_ARGB(127,127,127,255)),
		 Pink		        (D3DCOLOR_ARGB(255,174,201,255)),
		 Red			(D3DCOLOR_ARGB(255,0,0,255)),
		 Maroon		        (D3DCOLOR_ARGB(136,0,21,255)),
		 Magenta		(D3DCOLOR_ARGB(255,0,255,255)),
		 Brown			(D3DCOLOR_ARGB(185,122,87,255)),
		 Yellow			(D3DCOLOR_ARGB(255,255,0,255)),
		 LightGreen	        (D3DCOLOR_ARGB(128,255,128,255)),
		 Green			(D3DCOLOR_ARGB(0,255,0,255)),
		 DarkGreen	        (D3DCOLOR_ARGB(0,128,0,255)),
		 LightBlue    	        (D3DCOLOR_ARGB(128,128,255,255)),
		 Blue			(D3DCOLOR_ARGB(0,0,255,255)),
		 DarkBlue		(D3DCOLOR_ARGB(0,0,128,255)),
		 Purple			(D3DCOLOR_ARGB(163,73,164,255)) 
		 {}
}Colors;

int				RainbowR		= 100;
int				RainbowG		= 100;
int				RainbowB		= 100;
float			RainbowTexts	= 100;

void ColorRainBow()
{
	if(RainbowTexts!=100)
	{
				RainbowR-=2,RainbowG-=3,RainbowB-=3;
	}
	if(RainbowTexts!=255)
	{
		RainbowR+=2,RainbowG+=3,RainbowB+=4;
	}
}
#define	RainbowTextTest D3DCOLOR_ARGB(255, RainbowR, RainbowG, RainbowB)

//----------------------------------------------------------------------------------------//
                        // GET TEAM and GET CHARA JONES //
//----------------------------------------------------------------------------------------//
int GetTeamALL(int MyT)
{
	__try 
	{
		if(MyT == 0 || MyT == 2 || MyT == 4 || MyT == 6 || MyT == 8 || MyT == 10|| MyT == 12|| MyT == 14)
			return 1;
	}__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return 0;
	}
	__try
	{
		if(MyT == 1 || MyT == 3 || MyT == 5 || MyT == 7 || MyT == 9 || MyT == 11|| MyT == 13|| MyT == 15)
			return 2;
		return 0;
	}__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return 0;
	}
}

int GetTeam(int iSlot) 
{ __try{
    if (iSlot%2 == 0) 
        return 1; 
    else 
        return 2; 
}__except ( EXCEPTION_EXECUTE_HANDLER ) {return 0;}
}

bool GetUserPlayer(D3DXVECTOR3 &Player,int Index)
{
 GAMEINFO_CHARACTER *pPlayer = (GAMEINFO_CHARACTER*)(CGameContext::g_pGameContext()->getGameInfo_Chara(Index)); 
 if (pPlayer->m_pPosContext.x && pPlayer->m_pPosContext.y && pPlayer->m_pPosContext.z)
 {
	Player.x = pPlayer->m_pPosContext.x;
	Player.y = pPlayer->m_pPosContext.y;
	Player.z = pPlayer->m_pPosContext.z;
  return true; 
 }
 return false;
}

D3DXVECTOR3 GetUserVector( int Index )
{
	GAMEINFO_CHARACTER *pPlayer = (GAMEINFO_CHARACTER*)(CGameContext::g_pGameContext()->getGameInfo_Chara(Index)); 
	return pPlayer->m_pPosContext;
} 

int GetPlayerTarget(int Index)
{
	CGameCharaBase* pTarget = CGameCharaManager::g_pCharaManager()->GetCharaByNetIdx(Index);
		if(pTarget->m_pCollisionContext() && pTarget->m_pCollisionContext()->UpdateNickOnTarget())
		{
			return pTarget->m_pCollisionContext()->UpdateNickOnTarget();
		}
	return NULL;
}

int GetTargetIndex(DWORD PlayerTarget)
{
	if(PlayerTarget)
	{
		for(int i = 0; i<=16; i++)
		{
			DWORD PlayerIndexA = ((DWORD)CGameCharaManager::g_pCharaManager()->GetCharaByNetIdx(i));
			if(PlayerIndexA == PlayerTarget)return i;
		}
	}
	return -1;
}


bool IsAlive(int Index)
{
	__try{
	CGameCharaBase* pCharaBase = CGameCharaManager::g_pCharaManager()->GetCharaByNetIdx(Index);
	if(pCharaBase->getCurHP_Real() > 0.1f)
		return true;
	return false;
	}__except (EXCEPTION_EXECUTE_HANDLER){}
}

bool IsAliveDeath(int Index)
{
	if (!CGameContext::g_pGameContext()->getUserDeath(Index) && CGameContext::g_pGameContext()->setMySlotIdx() != Index)
	{
		if (CGameContext::g_pGameContext()->setMySlotIdx() %2 != Index % 2)
		{
				return true; 
		}
	}
 return false;
}
//-----------------------------------------------------------------------------------------//
int Get_OSSystem()
{
	OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);
	if(osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)		return 1;//WindowsXP
	else if(osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)   return 2;//windowsVista
	else if(osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1)	return 3;//windows7
	else if(osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 2)	return 4;//windows8
	return 0;
}
//-----------------------------------------------------------------------------------------//
enum TOSSystem {NO, WIN_XP, WIN_Vista, WIN_7, WIN_8 };
TOSSystem GetOSSystem() {
	int CurrentOS = Get_OSSystem(); 
	switch (CurrentOS)//  
	{
	case 1: return WIN_XP; break;
	case 2: return WIN_Vista; break;
	case 3: return WIN_7; break;
	case 4: return WIN_8; break;
	}
}
//-----------------------------------------------------------------------------------------//
CHAR OS_Version[12322] = "";
char  ComputerName [MAX_COMPUTERNAME_LENGTH + 1];
DWORD cbComputerName = sizeof ( ComputerName );
//-----------------------------------------------------------------------------------------//
TStageGame GetStageGame() {
	DWORD Stage = *(DWORD*)Resultg_pGameStatus; //GameStatus String - > CStageReady::OnCreate() Leave
	switch (Stage)//  
	{
	case 0: return SERVER; break;
	case 1: return CHANNEL; break;
	case 2: return LOBBY; break;
	case 3:
		if (CGameContext::g_pGameContext()->InBatlle())  
			return PLAYING;
		else
			return AWAITING;
		break;
	}
}

TSlotWeapon GetSlotWeapon()
{
	int Slot = (int)CGameCharaBase::g_pPlayer()->m_pWeaponContext()->getCurrentWeaponSlot(); //
	switch (Slot)//  
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

bool IsInBattle()
{
	//if(CGameCharaManager::g_pCharaManager()->getLocalChara() > NULL)return true;
	//return false;
	if(CGameCharaBase::g_pPlayer() > 0)return true;
	return false; 
}

struct D3DTLVERTEX
{
	float fX;
	float fY;
	float fZ;
	float fRHW;
	D3DCOLOR Color;
	float fU;
	float fV;
};

/*-------------------------------------------------------------------------------------------------------------------*/
