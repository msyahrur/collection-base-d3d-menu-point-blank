#include <windows.h>
#include "File.h"
#include "XStr.h"
bool BulletEnable = false;
int Norespawn,xxAccuracy,FileLine,CallAImFunc,Tsung,Tsung2,TsungHS,Tsung5 = NULL;
int xAccuracy;
int CallAmmo = NULL;
int HollowSetan = NULL;
int FastChange = NULL;
int RapidAdvancFire,FlyCacadMode,CallFlyHack,RapidQQ,RelCacadMode = NULL;
int BombEnywhere = NULL;
int BAKSOKA = NULL;
int HeadLock = NULL;
int AimCrotMode,AimCrotModeFake ,ammoroll,DepositAmmo = NULL;
int CallAimCrotMode = NULL;
int WallCrot = NULL;
int PlayerNameV2 = NULL;
int ChamsTR = NULL;
int ChamsTR2 = NULL;
int ChamsCT = NULL;
int ChamsCT2 = NULL;
int Weapon = NULL;
int chamsWeapon = NULL;
int DateTimes = NULL;
int ShowTime ,Suicide,DUp= NULL;
int biar = 1;
int NoFog = NULL;
int Damage1 = NULL;
int UnSmoke = NULL;
int AntiAFK = NULL;
int Gila = NULL;
int Folder1,Folder2,Folder3,Folder4,Folder5,Folder6,Folder7=NULL;
int NoRecoil = NULL;
int AimPelor,AimPelorBadan,AimLockHotkey ,AutoHeS= NULL;
int ReloadMayor = NULL;
int ReplaceCCD = NULL;
int BugtrapEnemy = NULL;
int ReplaceAcc = NULL;
int ReplaceAWP = NULL;
int ReplaceSG = NULL;
int ReplaceSMG = NULL;
int FastKnife = NULL;
int GhostExit,FallDmg = NULL;
int AutoRedyGB = NULL;
int BrustSniperSg = NULL;
int AutoOutGB = NULL;
int ShowName = NULL;
int AutoShoot = NULL;
int Knife = NULL;
int RepeatCall = NULL;
int AutoHS = NULL;
int FlyHack = NULL;
int GhostBuster = NULL;
int UltimateAmmo = NULL;
int ModeFloodVoteKick = NULL;
int FiturRusuh = NULL;
int CrossEnds = NULL;
int Reload;
int DinoSpam = NULL;
int SuicideTruz = NULL;
int StringHacker = 1;
int RenderText = 1;
int HideMenu = 1;
int TargetPelor = NULL;
int PelorSetan = NULL;
int ESPBone = NULL;
int ESPHealth = NULL;
int AutoHeadshot = NULL;
int Accuracy,CallAccuracy,AimBody,callAimHead = NULL;
int AutoCrotCacad = NULL;
DWORD BackupEDXTele,BackupEDXTeleTod,ReadHSC,ReadHSD,ReadHSF,ReadHSE,ReadHSG,ReadHSH,
ReadDMGA,ReadDMGB,ReadDMGC,ReadDMGD,ReadDMGE,ReadDMGF,ReadDMGG,ReadDMGH,ReadBYPASSKACA,ReadBYPASSD,
ReadBYPASSKELA,ReadBYPASSKELB,ReadBYPASSKELC,ReadBYPASSKELD,ReadBYPASSKELE,ReadBYPASSKELF,ReadBYPASSKELG,ReadBYPASSKELH;
bool bBetrayer = false;
bool bGExit = false;
bool Bbetrayer = true;
bool BGExit = true;
bool Shot = false;
bool HookedShot = false;
int CallReplace = NULL;
bool Keprok,Keprox = false;
bool bPiso = false;
#define ResultBasePlayer            0x9802F4
#define ResultBasePlayer2            0xD802F4
#define ResultBaseHealth      0x97D2C0
#define ResultBaseHealth2      0xD802C0
#define ResultBaseAmmo        0x9802BC
#define ResultBaseAmmo2        0xD802BC
#define ResultTeam             0x2A254
#define ResultCallm_Bone      0x529D50
#define ResultgetCurHP      0x54DBC0
#define ResultCallm_pBoneContext      0x50BE20
#define ResultGetCharaByNetIdx      0x4C8550
#define ResultPTRm_Bone      0x150
#define SizeOffset_BoneCurrent                          (ResultCallm_Bone)//0x529C80
#define SizeOffset_HPCurrent                            (ResultgetCurHP)
#define SizeOffset_CharaCurrent                         (ResultCallm_pBoneContext)
#define SizeOffset_CharaBase                            (ResultGetCharaByNetIdx) 
#define SizeOffset_PTRBoneContext                       (ResultPTRm_Bone)
bool ADDXW2S(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player,D3DVECTOR &PlayerScaled){
D3DXVECTOR3 PlayerPos(Player.x,Player.y,Player.z);
D3DXMATRIX identity;
D3DXVECTOR3 vScreen;
pDevice->GetViewport(&Viewport);
Viewport.X = Viewport.Y = 0;
Viewport.MinZ     = 0;
Viewport.MaxZ     = 1;
D3DXVec3Project(&vScreen, &PlayerPos, &Viewport, &pRC->pRenderData->ProjMatrix, &pRC->pRenderData->ViewMatrix, &pRC->pRenderData->World);
if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height){
PlayerScaled.x = vScreen.x;
PlayerScaled.y = vScreen.y ;
PlayerScaled.z = vScreen.z;
return true; 
}
return false;
}
//----------------------------------------------------------------------------------------
void FillRGB( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice )
{
    if( w < 0 )w = 1;
    if( h < 0 )h = 1;
    if( x < 0 )x = 1;
    if( y < 0 )y = 1;

    D3DRECT rec = { x, y, x + w, y + h };
    pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}
//---------------------------------------------------------------------------//
BYTE GetUserLife(int iSlot){
DWORD g_pGameContext   = *(DWORD*)ResultBasePlayer2;
CDeathPlayer *Life = (CDeathPlayer *) (g_pGameContext + 0x2CDAC);
return Life->Death[iSlot];
}
//---------------------------------------------------------------------------//
int GetCharaIndex(){
DWORD g_pGameContext   = *(DWORD*)ResultBasePlayer2;
CLocalPlayerID *LocID = (CLocalPlayerID *) (g_pGameContext + ResultTeam);
return LocID->ID;
}

class CGameCharaBoneContextz
{
public:
	D3DMATRIX* getArrayBones()
	{
		auto Func = (D3DMATRIX* (__thiscall*)(DWORD))SizeOffset_BoneCurrent;
		return Func((DWORD)this + SizeOffset_PTRBoneContext);
	}
};
class CGameCharaBoneContext1
{
public:
	

	D3DMATRIX* m_Bone1()
	{
		auto Func = (D3DMATRIX* (__thiscall*)(DWORD))ResultCallm_Bone;
		return Func((DWORD)this + ResultPTRm_Bone);
	}
	};
//===================================================================//
class CGameCharaBasez
{
public:
	int getCurHP()
	{
		auto Func = (int(__thiscall*)(CGameCharaBasez*))SizeOffset_HPCurrent;
		return Func(this); 
	}
	CGameCharaBoneContextz* getBoneContext()
	{
		auto Func = (CGameCharaBoneContextz* (__thiscall*)(CGameCharaBasez*))SizeOffset_CharaCurrent;
		return Func(this);
	}
};
//=====================================================================//
class CGameCharaManagerz
{
public:
	CGameCharaBasez* GetCharaByNetId(int IdxSlot)
	{
		auto Func = (CGameCharaBasez* (__thiscall*)(CGameCharaManagerz*, int))SizeOffset_CharaBase;
		return Func(this, IdxSlot);
	}
	static CGameCharaManagerz* Singleton()
	{
		return (CGameCharaManagerz*)(*(PDWORD)ResultBaseHealth2);
	}
};
bool GetUserBone( D3DXVECTOR3 &Out,  int BoneIdx ,int Idx)
{
CGameCharaBasez* GameBase = CGameCharaManagerz::Singleton()->GetCharaByNetId(Idx);
	if (GameBase && GameBase->getBoneContext())
	{
		Out.x = GameBase->getBoneContext()->getArrayBones()[BoneIdx]._41;
		Out.y = GameBase->getBoneContext()->getArrayBones()[BoneIdx]._42;
		Out.z = GameBase->getBoneContext()->getArrayBones()[BoneIdx]._43;
		return true;
	}
	return false;
}
float fX,fY,fZ = 0;
//----------------------------------------------------------------------------------------
_declspec(naked)void i3CollideeLine_SetEnd()
{
_asm
{
	cmp [BulletEnable],0
		je Skip
		mov eax,dword ptr ss:[esp+0x4]
	mov [BackupEDXTele],edx
		mov edx,[fX]
	mov [eax+0x0],edx
		mov edx,[fY]
	mov [eax+0x4],edx
		mov edx,[fZ]
	mov [eax+0x8],edx
		mov edx,[BackupEDXTele]
Skip:
	MOV EAX,DWORD PTR SS:[ESP+0x4]
FLD DWORD PTR DS:[EAX]
FSTP DWORD PTR DS:[ECX+0x7C]
FLD DWORD PTR DS:[EAX+0x4]
FSTP DWORD PTR DS:[ECX+0x80]
FLD DWORD PTR DS:[EAX+0x8]
FSTP DWORD PTR DS:[ECX+0x84]
FLD DWORD PTR DS:[ECX+0x7C]
FSUB DWORD PTR DS:[ECX+0x70]
FSTP DWORD PTR DS:[ECX+0x88]//
FLD DWORD PTR DS:[ECX+0x80]
FSUB DWORD PTR DS:[ECX+0x74]
FSTP DWORD PTR DS:[ECX+0x8C] //S Explosive
FLD DWORD PTR DS:[ECX+0x84]
FSUB DWORD PTR DS:[ECX+0x78]
FSTP DWORD PTR DS:[ECX+0x90] // Spesial
RETN 0x4

}}
//----------------------------------------------------------------------------------------
DWORD HookAIM(BYTE *MemoryTarget, DWORD FunctionTarget){
Sleep(5);
*((DWORD *)(MemoryTarget)) = FunctionTarget;
Sleep(5);
return 0;
}
//----------------------------------------------------------------------------------------
float CalcDistance( D3DXVECTOR3 VecA, D3DXVECTOR3 VecB ){
return sqrt( ( ( VecA.x - VecB.x ) * ( VecA.x - VecB.x ) ) +
( ( VecA.y - VecB.y ) * ( VecA.y - VecB.y ) ) +
( ( VecA.z - VecB.z ) * ( VecA.z - VecB.z ) ) );
}
//----------------------------------------------------------------------------------------
int GetPriorityTarget()
{
int Result = -1;
float fMaxDistance = 180.0f;
D3DXVECTOR3 PlayerEnd, LocPlayer;
for (int index = 0; index < 16; index++)
{
if (!GetUserLife(index) && GetCharaIndex() != index)
{
if (GetCharaIndex() %2 != index % 2)
{
GetUserBone(LocPlayer, 7,GetCharaIndex());
GetUserBone(PlayerEnd, 7,index );
if (CalcDistance(LocPlayer, PlayerEnd) < fMaxDistance)
{
fMaxDistance = CalcDistance(PlayerEnd, LocPlayer);
Result = index;
}
}
}
}
return Result;
}

//----------------------------------------------------------------------------------------
DWORD OldProtect;
bool BHookedTele,cHookedShot = false;
//----------------------------------------------------------------------------------------
void HookAim()
{
	if(BHookedTele)return;
	MakePTR((PBYTE)0xDAFC70,(DWORD)i3CollideeLine_SetEnd);
	BHookedTele = true;
}
#define PINK			D3DCOLOR_ARGB(255, 255, 240,   0)
//----------------------------------------------------------------------------------------
void Accuracy_Hack(LPDIRECT3DDEVICE9 pDevice)
{
HookAim();
	 if(Accuracy)
    {

       if(*(PBYTE)ResultBaseAmmo2 > NULL){
       int AimSlot = GetPriorityTarget();
       if(AimSlot != -1){
       D3DXVECTOR3 OnWorld,OnScreen;
       int BoneIndexSelector = 0;
       switch(AimBody)
       {
          case 0: BoneIndexSelector = 7; break;
          case 1: BoneIndexSelector = 5; break;
       }
           float ScreenCenterX = (Viewport.Width /2.0f);
           float ScreenCenterY = (Viewport.Height /2.0f);
           float ScreenBottomY = (Viewport.Height);
           GetUserBone(OnWorld,BoneIndexSelector,AimSlot);
           BulletEnable = true;
           fX = OnWorld.x; 
           fY = OnWorld.y + 0.1f; 
           fZ = OnWorld.z;
          if(ADDXW2S(pDevice,OnWorld,OnScreen))
 		  {
             int x = ( GetSystemMetrics( 0 ) / 2);
             int y = ( GetSystemMetrics( 1 ) / 2);
//                Circle (OnScreen.x, OnScreen.y,4,true,PINK,pDevice);
               // DrawPoint(OnScreen.x, OnScreen.y, 2, 2, YELLOW, pDevice);//Point
				FillRGB(OnScreen.x-10, OnScreen.y, 7, 1,PINK,pDevice);
				FillRGB(OnScreen.x+4, OnScreen.y, 7, 1,PINK,pDevice);
				FillRGB(OnScreen.x, OnScreen.y-10, 1, 7,PINK,pDevice);
				FillRGB(OnScreen.x, OnScreen.y+4, 1, 7,PINK,pDevice);
                    }
                 }
               else
             {
           BulletEnable = false;
          }
       }
      else
    {
   BulletEnable = false;
  }
}
if(Accuracy == 0 && !Accuracy)
{
BulletEnable = false;
}
}

