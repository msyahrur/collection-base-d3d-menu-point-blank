/*CGameSDK PBHacks Last Edit By ZrC-CyB Hacks*/

#include "CColor.h"
//#include "CGameOFS.h"
#include "CGameClasses.h"
#include "CHacks.h"
#include "StandardIncludes.h"
#include "KeyFPresent.h"
#pragma warning (disable:4305)
LPD3DXLINE	pLine    = NULL;
LPD3DXFONT	fName	= NULL;
LPD3DXFONT	fSmall	= NULL;
LPD3DXFONT	Title    = NULL;
LPD3DXFONT	g_pFont = NULL; //D3D Font
LPD3DXFONT	g_pFont2 = NULL; //D3D Font
LPD3DXLINE	g_Line = NULL; //D3D Line
D3DVIEWPORT9	g_ViewPort; //ViewPort
LPDIRECT3DDEVICE9	pDevice;
D3DVIEWPORT9	Viewport;
float ScreenCenterX = (Viewport.Width /2.0f);
float ScreenCenterY = (Viewport.Height /2.0f);
float ScreenBottomY = (Viewport.Height);
bool bGhost		  = false;
bool bPiso		  = false;
bool bAmmo		  = false;
bool Shot		  = false;
bool HookedShot	  = false;
bool bHookedTele  = false;
bool AimEnable    = false;
bool BulletEnable = false;
bool bReadJump	  = true;
bool StrBox		  = true;
bool StrNotice	  = true;
bool StrMessage	  = true;
float DeltaX   = 0;    
float DeltaY   = 0;     
float fX,fY,fZ = 0;     
int AimSlot = 0;
DWORD d;
DWORD BackupEDXTele = 0;
DWORD DwBypass;
DWORD Ghoster;
DWORD DwJump;
DWORD BurstPiso;
DWORD CrossCol;
DWORD TeamColor;
DWORD NameCol;
DWORD HeadCol;
DWORD BoneCol;
DWORD LineCol;
DWORD BoxCol;
DWORD DisCol;
D3DVECTOR Player;
D3DVECTOR HeadPos;
D3DVECTOR PlayerScaled;
D3DVECTOR HeadScaled;
D3DVECTOR BonePos;
D3DVECTOR ScreenPos;
D3DXVECTOR3 vStart,vEnd;
D3DXVECTOR3 vvStart,vvEnd;
D3DXVECTOR3 vStart2,vEnd2;
D3DXVECTOR3 vvStart2,vvEnd2;
D3DXVECTOR3 vStart3,vEnd3;
D3DXVECTOR3 vvStart3,vvEnd3;
D3DXVECTOR3 vStart4,vEnd4;
D3DXVECTOR3 vvStart4,vvEnd4;
D3DXVECTOR3 vStart5,vEnd5;
D3DXVECTOR3 vvStart5,vvEnd5;
D3DXVECTOR3 vStart6,vEnd6;
D3DXVECTOR3 vvStart6,vvEnd6;
D3DXVECTOR3 vStart7,vEnd7;
D3DXVECTOR3 vvStart7,vvEnd7;
D3DXVECTOR3 vStart8,vEnd8;
D3DXVECTOR3 vvStart8,vvEnd8;
D3DXVECTOR3 vStart9,vEnd9;
D3DXVECTOR3 vvStart9,vvEnd9;
D3DXVECTOR3 vStart10,vEnd10;
D3DXVECTOR3 vvStart10,vvEnd10;

/*-------------------------------------------------------------------------------------------------------------------*/
int GetTeam(char MyTeam)
{
	for(int i = 0; i < 16; i+=2)
		if(i == MyTeam)return 2;
	for(int i = 1; i< 16; i+=2)
		if(i == MyTeam)return 1;
	return -1;
}

int GetIdxTeam(int Team)
{
for(int i = 0; i<=15; i+=2)
if( i == Team ) return 1;
for(int i = 1; i<=15; i+=2)
if( i == Team ) return 2;
return 0;
}

/*-------------------------------------------------------------------------------------------------------------------*/
bool GetBattleState() 
{
	unsigned long xBase = *(DWORD*)(BASE_AMMO2); 
	if(xBase > NULL)
	{ 
		return true; 
	} 
	return false; 
}

/*-------------------------------------------------------------------------------------------------------------------*/
int GetMyCharaIndex()
{
	unsigned long dwBase	= *(DWORD*)(BASE_PLAYER2);
	CTeam *MyTeam = (CTeam*) ((dwBase + OFS_TEAM));
	return MyTeam->iTeam;
}

int GetMyCharaIndexed(unsigned int Index)
{
	unsigned long dwBase	= *(DWORD*)(BASE_PLAYER2);
	CTeam *MyTeam = (CTeam*) ((dwBase + OFS_TEAM));
	Index=MyTeam->iTeam;
	return Index;
}

/*-------------------------------------------------------------------------------------------------------------------*/
DWORD MakePTR(BYTE *MemoryTarget, DWORD FunctionTarget)
{
	DWORD dwOldProtect,dwBkup;
	DWORD dwRetn = *(DWORD*)(MemoryTarget);
	VirtualProtect(MemoryTarget, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*((DWORD *)(MemoryTarget)) = FunctionTarget;
	VirtualProtect(MemoryTarget, 4, dwOldProtect, &dwBkup);
	return dwRetn;
}

/*-------------------------------------------------------------------------------------------------------------------*/
void FillRGB( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice )
{
	if( w < 0 )w = 1;
	if( h < 0 )h = 1;
	if( x < 0 )x = 1;
	if( y < 0 )y = 1;
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}

/*-------------------------------------------------------------------------------------------------------------------*/
ID3DXFont*  pFont2;
ID3DXSprite* textSprite;
void iDrawString(int x, int y, D3DCOLOR dwColour, DWORD Flag, LPD3DXFONT Font, const char* text, ...)
{
	D3DCOLOR colour = dwColour;

	RECT rct;
	rct.left     = x - 1;   
	rct.right    = x + 1;   
	rct.top      = y - 1 ;   
	rct.bottom   = y + 1;

	va_list va_alist;
	char logbuf[256] = {0};
	va_start(va_alist, text);
	_vsnprintf(logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), text, va_alist);
	va_end(va_alist);

	textSprite->Begin(D3DXSPRITE_ALPHABLEND);
	Font->DrawText(textSprite, logbuf, -1, &rct, Flag|DT_NOCLIP, colour);
	textSprite->End();	
}

void DrawOutlineString(int x, int y, D3DCOLOR dwColour, DWORD Flag, LPD3DXFONT Font, const char* text, ...)
{
	iDrawString(x, y, dwColour, DT_NOCLIP | DT_CENTER, pFont2, text);
	iDrawString(x-1, y, 0xFF000000, DT_NOCLIP | DT_CENTER, pFont2, text);
	iDrawString(x+1, y, 0xFF000000, DT_NOCLIP | DT_CENTER, pFont2, text);
	iDrawString(x, y-1, 0xFF000000, DT_NOCLIP | DT_CENTER, pFont2, text);
	iDrawString(x, y+1, 0xFF000000, DT_NOCLIP | DT_CENTER, pFont2, text);
	iDrawString(x, y, dwColour, DT_NOCLIP | DT_CENTER, pFont2, text);
}

/*-------------------------------------------------------------------------------------------------------------------*/
void iDFillRGB( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice )
{
	if( w < 0 )w = 1;
	if( h < 0 )h = 1;
	if( x < 0 )x = 1;
	if( y < 0 )y = 1;
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}
 
void iDrawBorder( int x, int y, int w, int h, int px, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice )
{
	iDFillRGB( x, (y + h - px), w, px, BorderColor, pDevice );
	iDFillRGB( x, y, px, h, BorderColor, pDevice );
	iDFillRGB( x, y, w, px, BorderColor, pDevice );
	iDFillRGB( (x + w - px), y, px, h, BorderColor, pDevice );
}

void iDHealth(LPDIRECT3DDEVICE9 pDevice,float x, float y, float Health)
{
	DWORD HPcol = GREEN;
	if (Health < 90)HPcol = YELLOW;
	if (Health < 80) HPcol = ORANGE;
	if (Health < 40) HPcol = RED;
	if (Health < 10) HPcol = BLACK;
	iDFillRGB(x-1,y-1,52,5,GREY,pDevice );
	iDrawBorder(x-1,y-1,52,5,1,BLACK,pDevice );
	iDFillRGB(x,y,Health/2,3,HPcol,pDevice );

}

void DrawBoxESP( int x, int y, int w, int h, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice )
{
iDrawBorder( x, y, w, h, 1, BorderColor, pDevice );
} 

/*-------------------------------------------------------------------------------------------------------------------*/
bool GetBonePos(CGameCharaBase*m_CharaBase,D3DXVECTOR3 &outpos,int BoneIndex)
{
outpos.x = m_CharaBase->m_BoneContext->m_Bone[BoneIndex].m_Bone._41;
outpos.y = m_CharaBase->m_BoneContext->m_Bone[BoneIndex].m_Bone._42;
outpos.z = m_CharaBase->m_BoneContext->m_Bone[BoneIndex].m_Bone._43;
return true;
}

/*-------------------------------------------------------------------------------------------------------------------*/
bool WorldToScreenA(D3DXVECTOR3 inpos, D3DXVECTOR3 &outpos, LPDIRECT3DDEVICE9 pDevice)
{
//	DWORD dwRenderData = (DWORD)GetModuleHandleA(PointBlanki3Gfx) + G_RENDER;
	RenderContext* GfxDx = (RenderContext*)(g_pRenderContext);
	D3DXMATRIX identity;
	D3DXVECTOR3 vScreen;
	D3DVIEWPORT9 g_ViewPort;
	pDevice->GetViewport(&Tools.g_ViewPort);
	Tools.g_ViewPort.X = Tools.g_ViewPort.Y = 0;
	Tools.g_ViewPort.MinZ = 0;
	Tools.g_ViewPort.MaxZ = 1;
	D3DXVec3Project(&vScreen, &inpos, &Tools.g_ViewPort,
		&GfxDx->pRenderData->ProjMatrix,
		&GfxDx->pRenderData->ViewMatrix,
		&GfxDx->pRenderData->World);
	if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Tools.g_ViewPort.Width && vScreen.y < Tools.g_ViewPort.Height)
	{
		outpos.x = vScreen.x;
		outpos.y = vScreen.y;
		outpos.z = vScreen.z;
		AimEnable=false;
		return true;
	}
	AimEnable=true;
	return false;
}

bool ADDXW2S(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player,D3DVECTOR &PlayerScaled)
{
   D3DXVECTOR3 PlayerPos(Player.x,Player.y,Player.z);
	D3DXMATRIX identity;
    D3DXVECTOR3 vScreen;
	Tools.g_ViewPort.X = Tools.g_ViewPort.Y = 0;
    Tools.g_ViewPort.MinZ     = 0;
    Tools.g_ViewPort.MaxZ     = 1;
	D3DXVec3Project(&vScreen, &PlayerPos, &Tools.g_ViewPort, &pRC->pRenderData->ProjMatrix, &pRC->pRenderData->ViewMatrix, &pRC->pRenderData->World);
  
 if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Tools.g_ViewPort.Width && vScreen.y < Tools.g_ViewPort.Height)
 {
     PlayerScaled.x = vScreen.x;
     PlayerScaled.y = vScreen.y ;
     PlayerScaled.z = vScreen.z;

  return true; 
 }
 return false;
}

/*-------------------------------------------------------------------------------------------------------------------*/
void DrawLineBone ( long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, D3DCOLOR Color )
{
	D3DXVECTOR2 vLine[ 2 ];
	Tools.pLine->SetAntialias( 0 );
	Tools.pLine->SetWidth( (float)dwWidth );
	Tools.pLine->Begin();
	vLine[ 0 ][ 0 ] = (float)Xa;
	vLine[ 0 ][ 1 ] = (float)Ya;
	vLine[ 1 ][ 0 ] = (float)Xb;
	vLine[ 1 ][ 1 ] = (float)Yb;
	Tools.pLine->Draw( vLine, 2, Color );
	Tools.pLine->End();
}

/*-------------------------------------------------------------------------------------------------------------------*/
void DrawBone(CGameCharaBase* m_CharaBase,int Start,int End,DWORD Color,LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 vStart,vEnd;
	D3DXVECTOR3 vvStart,vvEnd;
	if(GetBonePos(m_CharaBase,vStart,Start))
	{
		if(GetBonePos(m_CharaBase,vEnd,End))
		{
			if(ADDXW2S(pDevice,vStart,vvStart))
			{
				if(ADDXW2S(pDevice,vEnd,vvEnd))
				{
					DrawLineBone(vvStart.x,vvStart.y,vvEnd.x,vvEnd.y,1,Color);
				}
			}
		}
	}
}

/*-------------------------------------------------------------------------------------------------------------------*/
void DrawSkeleton(CGameCharaBase* m_CharaBase,DWORD Color,LPDIRECT3DDEVICE9 pDevice)
{
float wraw = 2;
DrawBone(m_CharaBase,0,6,Color,pDevice);
DrawBone(m_CharaBase,6,10,Color,pDevice);
DrawBone(m_CharaBase,6,11,Color,pDevice);
DrawBone(m_CharaBase,0,12,Color,pDevice);
DrawBone(m_CharaBase,0,13,Color,pDevice);
DrawBone(m_CharaBase,12,14,Color,pDevice);
DrawBone(m_CharaBase,13,15,Color,pDevice);
DrawBone(m_CharaBase,14,8,Color,pDevice);
DrawBone(m_CharaBase,15,9,Color,pDevice);
}

/*-------------------------------------------------------------------------------------------------------------------*/
bool GetUserBone( D3DXVECTOR3 &Out, int Idx, int BoneIdx )
{
	unsigned long dwGameBase = *(DWORD*)(BASE_HEALTH2);
	if ( dwGameBase )
	{
		CGameCharaBase* GameBase = (CGameCharaBase*)( *(DWORD*)(dwGameBase + 0x14 + ( 0x4 * Idx ) ) );
		if ( GameBase && GameBase->m_BoneContext )
		{
			Out.x = GameBase->m_BoneContext->m_Bone[ BoneIdx ].m_Bone._41;
			Out.y = GameBase->m_BoneContext->m_Bone[ BoneIdx ].m_Bone._42;
			Out.z = GameBase->m_BoneContext->m_Bone[ BoneIdx ].m_Bone._43;
			return true;
		}
	}
	return false;
}

D3DXVECTOR3 GetUserBonePos_Scd(int Idx ,int BoneIdx)
{
	D3DXVECTOR3 Out;
	unsigned long dwGameBase = *(DWORD*)(BASE_HEALTH2);
	if ( dwGameBase )
	{
		CGameCharaBase* GameBase = (CGameCharaBase*)( *(DWORD*)(dwGameBase + 0x14 + ( 0x4 * Idx ) ) );
		if ( GameBase && GameBase->m_BoneContext )
		{
			Out.x = GameBase->m_BoneContext->m_Bone[ BoneIdx ].m_Bone._41;
			Out.y = GameBase->m_BoneContext->m_Bone[ BoneIdx ].m_Bone._42;
			Out.z = GameBase->m_BoneContext->m_Bone[ BoneIdx ].m_Bone._43;
		}
	}
	return Out;
}

/*-------------------------------------------------------------------------------------------------------------------*/
float CalcDistance( D3DXVECTOR3 VecA, D3DXVECTOR3 VecB )
{
	return sqrt( ( ( VecA.x - VecB.x ) * ( VecA.x - VecB.x ) ) +
		( ( VecA.y - VecB.y ) * ( VecA.y - VecB.y ) ) +
		( ( VecA.z - VecB.z ) * ( VecA.z - VecB.z ) ) );
}

/*-------------------------------------------------------------------------------------------------------------------*/
float FindDistance(D3DXVECTOR3 my,D3DXVECTOR3 other,CPlayers* pPlayer,CPlayers* pLocal)
{
	return sqrt((pLocal->pos.x-pPlayer->pos.x)*(pLocal->pos.x-pPlayer->pos.x) + (pLocal->pos.y-pPlayer->pos.y)*(pLocal->pos.y-pPlayer->pos.y) + (pLocal->pos.z-pPlayer->pos.z)*(pLocal->pos.z-pPlayer->pos.z));
}

/*-------------------------------------------------------------------------------------------------------------------*/
bool IsAlive(int Index)
{
	unsigned long dwBase2	= *(DWORD*)(BASE_HEALTH2);
	CHealth		*Health		= (CHealth*) ((dwBase2 + OFS_HEALTH) + Index * HPSIZE);
	if(Health->CurHP > 0.1f)
		return true;
	return false;
}

/*-------------------------------------------------------------------------------------------------------------------*/
D3DXVECTOR3 GetUserVector( int Index )
{
	DWORD ADR_PLAYER = *(DWORD*)(BASE_PLAYER2);
	DWORD OldProtect;
	DWORD pCalculate = *(DWORD*)(ADR_PLAYER + 4 * Index + OFS_PLAYER );
	VirtualProtect ( (LPVOID)(pCalculate), sizeof (pCalculate), PAGE_EXECUTE_READWRITE, &OldProtect );
	CPlayers	*Players	= (CPlayers*)(pCalculate + 0x64 );
	VirtualProtect ( (LPVOID)(pCalculate), sizeof (pCalculate), OldProtect, &OldProtect );
	return Players->pos;
}

BYTE GetUserLife(int iSlot)
{
    DWORD g_pGameContext   = *(DWORD*)BASE_PLAYER2;
    CDeathPlayer *Life = (CDeathPlayer *) (g_pGameContext + OFS_DEATH);
    return Life->Death[iSlot];
    VirtualProtect((PVOID*)(g_pGameContext + OFS_DEATH), 10, PAGE_EXECUTE_READWRITE, &d);
}

int GetCharaIndex()
{
    DWORD g_pGameContext   = *(DWORD*)BASE_PLAYER2; 
    CLocalPlayerID *LocID = (CLocalPlayerID *) (g_pGameContext + OFS_TEAM);
    return LocID->ID;
    VirtualProtect((PVOID*)(g_pGameContext + OFS_TEAM), 10, PAGE_EXECUTE_READWRITE, &d);
}

/*-------------------------------------------------------------------------------------------------------------------*/
int AutomaticTarget_World()
{
	int Result = -1;
	float NearDistance = 1000.0f;
	int MyTeam = GetTeam(GetMyCharaIndex());
	if(!IsAlive(GetMyCharaIndex()))return Result;
	for(int i = 0; i<=16; i++)
	{
		int TargetTeam = GetTeam(i);
		if(TargetTeam == MyTeam)continue;
		if(TargetTeam == 0)continue;
		if ( IsAlive(i) )
		{
			D3DXVECTOR3 Head;
			if ( GetMyCharaIndex( ) %2 != i % 2 && GetUserBone( Head, i, 7.7 ) )
			{
				if(CalcDistance(GetUserVector(GetMyCharaIndex()),GetUserVector(i)) < NearDistance)
				{
					NearDistance = CalcDistance(GetUserVector(GetMyCharaIndex()),GetUserVector(i));
					Result = i;
				}
			}
		}
		
	}
	return Result;
}

int GetPriorityTarget()
{
	int Result = -1;
	float fMaxDistance = 1000.0f;
	D3DXVECTOR3 PlayerEnd, LocPlayer;
	int MyTeam = GetTeam(GetMyCharaIndex());
	unsigned long BASESlot = *(DWORD*) BASE_PLAYER2;
	unsigned long dwBase2	= *(DWORD*)BASE_HEALTH2;
	D3DXVECTOR3 HeadMe,Player,HeadPos ;
	
	for (int i = 0; i <=15; i++)
	{
		CTeam		*pTeam		= ((CTeam*)(BASESlot + OFS_TEAM));
		DWORD OldProtect;
		DWORD pCalculate		= *(DWORD*)(BASESlot + 0x4 * i + OFS_PLAYER );
		DWORD pCalculate2		= *(DWORD*)(BASESlot + 0x4 * pTeam->iTeam + OFS_PLAYER );
		VirtualProtect ( (LPVOID)(pCalculate), sizeof (pCalculate), PAGE_EXECUTE_READWRITE, &OldProtect );
		VirtualProtect ( (LPVOID)(pCalculate2), sizeof (pCalculate2), PAGE_EXECUTE_READWRITE, &OldProtect );
		CPlayers	*pPlayer	= (CPlayers*)(pCalculate /*+ 0x64*/ );
		CPlayers	*pLocal		= (CPlayers*)(pCalculate2 /*+ 0x64*/ );
		VirtualProtect ( (LPVOID)(pCalculate), sizeof (pCalculate), OldProtect, &OldProtect );
		VirtualProtect ( (LPVOID)(pCalculate2), sizeof (pCalculate2), OldProtect, &OldProtect );
		
		HeadPos.x = pPlayer->pos.x;
		HeadPos.y = 1.6f + pPlayer->pos.y;
		HeadPos.z = pPlayer->pos.z;
		HeadMe.x = pLocal->pos.x;
		HeadMe.y = 1.6f + pLocal->pos.y;
		HeadMe.z = pLocal->pos.z;
		
		int TargetTeam = GetTeam(i);
		if(TargetTeam == MyTeam)continue;
		if(TargetTeam == 0)continue;
		
		if (!GetUserLife(i) && GetCharaIndex() != i){
			if (GetCharaIndex() %2 != i % 2){
				if (CalcDistance(HeadMe, HeadPos) < fMaxDistance)
				{
					fMaxDistance = CalcDistance( HeadPos,HeadMe);
					Result = i;
				}
			}
		}
}
return Result;
}

/*------------------------------------------- Declaration Aimbot ------------------------------------------------------*/
float MouseDeltaX, MouseDeltaY, MouseDeltaZ = 0;
bool AimStart = false;
__declspec(naked)void Aim_DeltaX()
{
_asm
{
	cmp opt.d3d.AimBot,1
		je StartAim
NORMAL:
	fld dword ptr [ecx+0x14]
	ret
StartAim:
	cmp AimEnable,0
		je NORMAL
		fld dword ptr[MouseDeltaX]
	ret
}
}

__declspec(naked)void Aim_DeltaY()
{
_asm
{
	cmp opt.d3d.AimBot,1
		je StartAim
NORMAL:
	fld dword ptr [ecx+0x18]
	ret
StartAim:
	cmp AimEnable,0
		je NORMAL
	fld dword ptr[MouseDeltaY]
	ret 
}
}

/*-------------------------------------------------------------------------------------------------------------------*/
void Thread_Aimbot()
{
	MakePTR((PBYTE)BASE_AIMBOTX,(DWORD)Aim_DeltaX);
	MakePTR((PBYTE)BASE_AIMBOTY,(DWORD)Aim_DeltaY);
}

void DoAimbot(LPDIRECT3DDEVICE9 pDevice)
{
	unsigned long dwBase	= *(DWORD*)(BASE_PLAYER2);
	int ScreenCenterX = (Tools.g_ViewPort.Width /2.0f);
	int ScreenCenterY = (Tools.g_ViewPort.Height /2.0f);
	CPlayers *pNearEnt = NULL;
	float NearTargetX = 0.0f;
	float NearTargetY = 0.0f;
	float DisX = 0.0f;
	float DisY = 0.0f;
	CNames *pTarget = NULL;
	CHealth *iTarget = NULL;
	float Nearest = (float) INT_MAX;
	float PosX = 0.0f;
	float PosY = 0.0f;
	if(opt.d3d.AimBot)
	{
		int AimSlot = GetPriorityTarget(); //get priority target, player that alive, nearest, and visible
		if(AimSlot != -1)
		{
			D3DXVECTOR3 OnWorld,OnScreen;
			D3DXVECTOR3 NeckPos,BodyPos;
			DWORD ADR_PLAYER		= *(DWORD*)(BASE_PLAYER2);
			CTeam		*pTeam		= ((CTeam*)(ADR_PLAYER + OFS_TEAM));
			DWORD OldProtect;
			DWORD pCalculate		= *(DWORD*)(ADR_PLAYER + 0x4 * AimSlot + OFS_PLAYER );
			DWORD pCalculate2		= *(DWORD*)(ADR_PLAYER + 0x4 * pTeam->iTeam + OFS_PLAYER );
			VirtualProtect ( (LPVOID)(pCalculate), sizeof (pCalculate), PAGE_EXECUTE_READWRITE, &OldProtect );
			VirtualProtect ( (LPVOID)(pCalculate2), sizeof (pCalculate2), PAGE_EXECUTE_READWRITE, &OldProtect );
			CPlayers	*pPlayer	= (CPlayers*)(pCalculate /*+ 0x64*/ );
			CPlayers	*pLocal		= (CPlayers*)(pCalculate2 /*+ 0x64*/ );
			VirtualProtect ( (LPVOID)(pCalculate), sizeof (pCalculate), OldProtect, &OldProtect );
			VirtualProtect ( (LPVOID)(pCalculate2), sizeof (pCalculate2), OldProtect, &OldProtect );

			HeadPos.x = pPlayer->pos.x;
			HeadPos.y = 1.5f + pPlayer->pos.y;
			HeadPos.z = pPlayer->pos.z;

			NeckPos.x = pPlayer->pos.x;
			NeckPos.y = 1.3f + pPlayer->pos.y;
			NeckPos.z = pPlayer->pos.z;

			BodyPos.x = pPlayer->pos.x;
			BodyPos.y = 1.0f + pPlayer->pos.y;
			BodyPos.z = pPlayer->pos.z;

			int MyTeam = GetTeam(pTeam->iTeam);
			for (int i = 0; i<=0x16;i++){
			int iTeam				= GetTeam(i);
			if (iTeam == MyTeam)continue;
			switch(opt.d3d.BoneTarget){
			case 0:
			if( ADDXW2S(pDevice,HeadPos,OnScreen))
			{
				if (!GetUserLife(i) && GetCharaIndex() != i)
								{
									if (GetCharaIndex() %2 != i % 2)
									{
										PosX = ScreenCenterX - HeadPos.x;
										PosY = ScreenCenterY - HeadPos.y;

										DisX = (pLocal->pos.x - pPlayer->pos.x) * (pLocal->pos.x - pPlayer->pos.x) ;
										DisY = (pLocal->pos.y - pPlayer->pos.y) * (pLocal->pos.y - pPlayer->pos.y) ;

										float Temp = sqrt(PosX) + sqrt(PosY);
										float Temp2 = sqrt(DisX) + sqrt(DisY);
										if (Temp > Nearest && Temp2 > Nearest) continue;
										if (Nearest < 0.0f || Temp < Nearest)
										{
										if (Temp2 < Nearest)
										{
										pNearEnt = pPlayer;
										//pTarget = pNames;
										//iTarget = pHealth;
										Nearest = Temp;
										NearTargetX = HeadScaled.x;
										NearTargetY = HeadScaled.y;
										}
										int x = ( GetSystemMetrics( 0 ) / 2);
					int y = ( GetSystemMetrics( 1 ) / 2);
					Tools.FillRGB(OnScreen.x-10, OnScreen.y, 7, 1,SKYBLUE,pDevice);//Left line
					Tools.FillRGB(OnScreen.x+4, OnScreen.y, 7, 1,SKYBLUE,pDevice);//Right line
					Tools.FillRGB(OnScreen.x, OnScreen.y-10, 1, 7,SKYBLUE,pDevice);//Top line
					Tools.FillRGB(OnScreen.x, OnScreen.y+4, 1, 7,SKYBLUE,pDevice);//Bottom line
					Tools.DrawPoint(OnScreen.x,OnScreen.y,2,2,RED2,pDevice);//Point
					fX = HeadPos.x;
					fY = HeadPos.y;// + 0.1f;
					fZ = HeadPos.z;
			}
			break;
			}
					AimEnable = true; // Enable the aimlock
					int LocalX = OnScreen.x; //Define that player on screen
					int LocalY = OnScreen.y;
					if(LocalX == ScreenCenterX && LocalY == ScreenCenterY) // if the screen center is player target
					{ 
						MouseDeltaX = 0; // make mouse delta is NULL
						MouseDeltaY = 0;
					}
					else
					{   // if not then
						MouseDeltaX = LocalX - ScreenCenterX; // Mouse delta X is LocalX - ScreenCenterX
						MouseDeltaY = LocalY - ScreenCenterY;
					}
				}
					else
					{
						AimEnable = false;//Disable the aimlock
					}
				}
			else
			{
				AimEnable = false;//Disable the aimlock
			}
	}
		}
		}
		}
		}
/*------------------------------------------- Declaration Bullet ------------------------------------------------------*/
_declspec(naked)void i3CollideeLine_SetEnd()
{
_asm
{
	cmp [BulletEnable],0
		je Skip
		mov eax,dword ptr ss:[esp+0x4]
	mov [BackupEDXTele],edx
		mov edx,[fX]
	mov [eax+0],edx
		mov edx,[fY]
	mov [eax+4],edx
		mov edx,[fZ]
	mov [eax+8],edx
		mov edx,[BackupEDXTele]
Skip:
	mov eax,dword ptr ss:[esp+0x4]
	fld dword ptr ds:[eax]
	fstp dword ptr ds:[ecx+0x18]
	fld dword ptr ds:[eax+0x4]
	fstp dword ptr ds:[ecx+0x1C]
	fld dword ptr ds:[eax+0x8]
	fstp dword ptr ds:[ecx+0x20]
	fld dword ptr ds:[ecx+0x18]
	fsub dword ptr ds:[ecx+0x0C]
	fstp dword ptr ds:[ecx+0x24]
	fld dword ptr ds:[ecx+0x1C]
	fsub dword ptr ds:[ecx+0x10]
	fstp dword ptr ds:[ecx+0x28]
	fld dword ptr ds:[ecx+0x20]
	fsub dword ptr ds:[ecx+0x14]
	fstp dword ptr ds:[ecx+0x2C]
	retn 0x4                             
}
}

/*-------------------------------------------------------------------------------------------------------------------*/
void HookTelekill()
{
	if(bHookedTele)return;
	MakePTR((PBYTE)BASE_BULLET,(DWORD)i3CollideeLine_SetEnd);
	bHookedTele = true;
}

void DoAimBullet(LPDIRECT3DDEVICE9 pDevice)
{
if(opt.d3d.AimBullet==1)
{
	BulletEnable = true;
	int AimSlot = GetPriorityTarget();
	if(AimSlot != -1)
	{
		D3DXVECTOR3 OnWorld,OnScreen;
		D3DXVECTOR3 NeckPos,BodyPos;
		DWORD ADR_PLAYER		= *(DWORD*)(BASE_PLAYER2);
		CTeam		*pTeam		= ((CTeam*)(ADR_PLAYER + OFS_TEAM));
		DWORD OldProtect;
		DWORD pCalculate		= *(DWORD*)(ADR_PLAYER + 0x4 * AimSlot + OFS_PLAYER );
		DWORD pCalculate2		= *(DWORD*)(ADR_PLAYER + 0x4 * pTeam->iTeam + OFS_PLAYER );
		VirtualProtect ( (LPVOID)(pCalculate), sizeof (pCalculate), PAGE_EXECUTE_READWRITE, &OldProtect );
		VirtualProtect ( (LPVOID)(pCalculate2), sizeof (pCalculate2), PAGE_EXECUTE_READWRITE, &OldProtect );
		CPlayers	*pPlayer	= (CPlayers*)(pCalculate /*+ 0x64*/ );
		CPlayers	*pLocal		= (CPlayers*)(pCalculate2 /*+ 0x64*/ );
		VirtualProtect ( (LPVOID)(pCalculate), sizeof (pCalculate), OldProtect, &OldProtect );
		VirtualProtect ( (LPVOID)(pCalculate2), sizeof (pCalculate2), OldProtect, &OldProtect );

//			D3DXVECTOR3 OnWorld,OnScreen;
			HeadPos.x = pPlayer->pos.x;
			HeadPos.y = 1.5f + pPlayer->pos.y;
			HeadPos.z = pPlayer->pos.z;

			NeckPos.x = pPlayer->pos.x;
			NeckPos.y = 1.3f + pPlayer->pos.y;
			NeckPos.z = pPlayer->pos.z;

			BodyPos.x = pPlayer->pos.x;
			BodyPos.y = 1.0f + pPlayer->pos.y;
			BodyPos.z = pPlayer->pos.z;

			int BoneIndexSelector = 0;
			switch(opt.d3d.BoneTarget){
			case 0:
			if( ADDXW2S(pDevice,HeadPos,OnScreen))
			{
					int x = ( GetSystemMetrics( 0 ) / 2);
					int y = ( GetSystemMetrics( 1 ) / 2);
					Tools.FillRGB(OnScreen.x-10, OnScreen.y, 7, 1,SKYBLUE,pDevice);//Left line
					Tools.FillRGB(OnScreen.x+4, OnScreen.y, 7, 1,SKYBLUE,pDevice);//Right line
					Tools.FillRGB(OnScreen.x, OnScreen.y-10, 1, 7,SKYBLUE,pDevice);//Top line
					Tools.FillRGB(OnScreen.x, OnScreen.y+4, 1, 7,SKYBLUE,pDevice);//Bottom line
					Tools.DrawPoint(OnScreen.x,OnScreen.y,2,2,RED2,pDevice);//Point
					fX = HeadPos.x;
					fY = HeadPos.y;// + 0.1f;
					fZ = HeadPos.z;
			}
			break;
			case 1:
			if( ADDXW2S(pDevice,BodyPos,OnScreen))	
			{
				int x = ( GetSystemMetrics( 0 ) / 2);
				int y = ( GetSystemMetrics( 1 ) / 2);
				Tools.FillRGB(OnScreen.x-10, OnScreen.y, 7, 1,SKYBLUE,pDevice);//Left line
				Tools.FillRGB(OnScreen.x+4, OnScreen.y, 7, 1,SKYBLUE,pDevice);//Right line
				Tools.FillRGB(OnScreen.x, OnScreen.y-10, 1, 7,SKYBLUE,pDevice);//Top line
				Tools.FillRGB(OnScreen.x, OnScreen.y+4, 1, 7,SKYBLUE,pDevice);//Bottom line
				Tools.DrawPoint(OnScreen.x,OnScreen.y,2,2,RED2,pDevice);//Point
				fX = BodyPos.x;
				fY = BodyPos.y;// + 0.1f;
				fZ = BodyPos.z;
			}
			break;
			}
	}
	else
	{
		BulletEnable = false;
	}
}
else
{
if(opt.d3d.AimBullet == 0 && !opt.d3d.AimBullet)
{
	BulletEnable = false;
}
}
}

/*------------------------------------------- Declaration ESP ------------------------------------------------------*/
///*void ADDXESP(LPDIRECT3DDEVICE9 pDevice)
//{
//	unsigned long dwBase	= *(DWORD*)(BASE_PLAYER2);
//	//unsigned long dwBase2	= *(DWORD*)(BASE_HEALTH2);	
//	CTeam		*pTeam		= ((CTeam*)(dwBase + OFS_TEAM));
//
//	CGameCharaBase* m_CharaBase = NULL;
//	D3DXVECTOR3 HeadScaled,Screen,Kepala,Leher,Badan,LTangan,RTangan,LPanggul,RPanggul,LPaha,RPaha,LKaki,RKaki;
//	CPlayers *pNearEnt = NULL;
//	float NearTargetX = 0.0f;
//	float NearTargetY = 0.0f;
//	float DisX = 0.0f;
//	float DisY = 0.0f;
//	CNames *pTarget = NULL;
//	CHealth *iTarget = NULL;
//	float Nearest = (float) INT_MAX;
//	float PosX = 0.0f;
//	float PosY = 0.0f;
//
//	float ScreenCenterX = (Tools.g_ViewPort.Width /2.0f);
//	float ScreenCenterY = (Tools.g_ViewPort.Height /2.0f);
//	float ScreenBottomY = (Tools.g_ViewPort.Height);
//
//	int MyTeam = GetTeam(pTeam->iTeam);
//	if(*(PBYTE)BASE_AMMO2 > NULL){
//		for (int i = 0; i<=0x16;i++)
//		{
//				CNames		*pNames		= (CNames*)((dwBase + OFS_NAMES) + i * NAMESIZE);
//		//		CHealth		*pHealth	= (CHealth*)((dwBase2 + OFS_HEALTH) + i * HPSIZE);
//		//		CHealth		*mHealth	= (CHealth*)((dwBase2 + OFS_HEALTH) + pTeam->iTeam * HPSIZE);
//				DWORD ADR_PLAYER		= *(DWORD*)(BASE_PLAYER2);
//				DWORD OldProtect;
//				DWORD pCalculate		= *(DWORD*)(ADR_PLAYER + 0x4 * i + OFS_PLAYER );
//				DWORD pCalculate2		= *(DWORD*)(ADR_PLAYER + 0x4 * pTeam->iTeam + OFS_PLAYER );
//				VirtualProtect ( (LPVOID)(pCalculate), sizeof (pCalculate), PAGE_EXECUTE_READWRITE, &OldProtect );
//				VirtualProtect ( (LPVOID)(pCalculate2), sizeof (pCalculate2), PAGE_EXECUTE_READWRITE, &OldProtect );
//				CPlayers	*pPlayer	= (CPlayers*)(pCalculate /*+ 0x64*/ );
//				CPlayers	*pLocal		= (CPlayers*)(pCalculate2 /*+ 0x64*/ );
//				VirtualProtect ( (LPVOID)(pCalculate), sizeof (pCalculate), OldProtect, &OldProtect );
//				VirtualProtect ( (LPVOID)(pCalculate2), sizeof (pCalculate2), OldProtect, &OldProtect );
//				Player.x				=  pPlayer->pos.x;
//				Player.y				=  pPlayer->pos.y;
//				Player.z				=  pPlayer->pos.z;
//				HeadPos.x				=	pPlayer->pos.x;
//				HeadPos.y				=	1.6f + pPlayer->pos.y;
//				HeadPos.z				=	pPlayer->pos.z;
//				HeadPos.x				= pPlayer->pos.x;
//				/*Kepala.x				= pPlayer->pos.x;
//				Kepala.y				= 1.5f + pPlayer->pos.y;
//				Kepala.z				= pPlayer->pos.z;
//				Leher.x					= pPlayer->pos.x;
//				Leher.y					= 1.4f + pPlayer->pos.y;
//				Leher.z					= pPlayer->pos.z;
//				Badan.x					= pPlayer->pos.x;
//				Badan.y					= 1.0f + pPlayer->pos.y;
//				Badan.z					= pPlayer->pos.z;
//				LTangan.x				= pPlayer->pos.x - 0.7f;
//				LTangan.y				= 1.4f + pPlayer->pos.y;
//				LTangan.z				= pPlayer->pos.z;
//				RTangan.x				= pPlayer->pos.x + 0.7f;
//				RTangan.y				= 1.4f + pPlayer->pos.y;
//				RTangan.z				= pPlayer->pos.z;
//				LPanggul.x				= pPlayer->pos.x - 0.4f;
//				LPanggul.y				= 1.0f + pPlayer->pos.y;
//				LPanggul.z				= pPlayer->pos.z;
//				RPanggul.x				= pPlayer->pos.x + 0.4f;
//				RPanggul.y				= 1.0f + pPlayer->pos.y;
//				RPanggul.z				= pPlayer->pos.z;
//				LPaha.x					= pPlayer->pos.x - 0.5f;
//				LPaha.y					= 0.7f + pPlayer->pos.y;
//				LPaha.z					= pPlayer->pos.z;
//				RPaha.x					= pPlayer->pos.x + 0.5f;
//				RPaha.y					= 0.7f + pPlayer->pos.y;
//				RPaha.z					= pPlayer->pos.z;
//				LKaki.x					= pPlayer->pos.x - 0.4f;
//				LKaki.y					= pPlayer->pos.y;
//				LKaki.z					= pPlayer->pos.z;
//				RKaki.x					= pPlayer->pos.x + 0.4f;
//				RKaki.y					= pPlayer->pos.y;
//				RKaki.z					= pPlayer->pos.z;*/
//
//				//D3DXVECTOR3 MyDistance	=	pLocal->pos - pPlayer->pos;
//				//float MyaDistance = D3DXVec3Length(&MyDistance );
//
//				int iTeam				= GetTeam(i);
//				if (iTeam == MyTeam)continue;
///*-------------------------------------------------------------------------------------------------------------------*/
///*				if (ADDXW2S(pDevice,Player,PlayerScaled))
//				{
//				//	if (pHealth->CurHP > 1)
//				//	{
//					if (!GetUserLife(i) && GetCharaIndex() != i)
//					{
//						if (GetCharaIndex() %2 != i % 2)
//						{
//						if (opt.d3d.EspHealth)
//						{
//							iDHealth(pDevice,(float)PlayerScaled.x-25,(float)PlayerScaled.y+5,pHealth->CurHP);
//						}
//				//	}
//						}
//					}
//				}*/
//						
///*-------------------------------------------------------------------------------------------------------------------*/
//						D3DXVECTOR3 OnWorld,OnScreen;
//						//if(GetUserBone(OnWorld,i,7)){
//							if (ADDXW2S(pDevice,HeadPos,HeadScaled))
//							{
//							//	if (pHealth->CurHP > 1) 
//							//	{
//								
//				if (!GetUserLife(i) && GetCharaIndex() != i)
//								{
//									if (GetCharaIndex() %2 != i % 2)
//									{
//										PosX = ScreenCenterX - HeadPos.x;
//										PosY = ScreenCenterY - HeadPos.y;
//
//										DisX = (pLocal->pos.x - pPlayer->pos.x) * (pLocal->pos.x - pPlayer->pos.x) ;
//										DisY = (pLocal->pos.y - pPlayer->pos.y) * (pLocal->pos.y - pPlayer->pos.y) ;
//
//										float Temp = sqrt(PosX) + sqrt(PosY);
//										float Temp2 = sqrt(DisX) + sqrt(DisY);
//										if (Temp > Nearest && Temp2 > Nearest) continue;
//										if (Nearest < 0.0f || Temp < Nearest)
//										{
//										if (Temp2 < Nearest)
//										{
//										pNearEnt = pPlayer;
//										//pTarget = pNames;
//										//iTarget = pHealth;
//										Nearest = Temp;
//										NearTargetX = HeadScaled.x;
//										NearTargetY = HeadScaled.y;
//										}
//									}
//									if (opt.d3d.cEspNameCol ==0)NameCol=WHITE;
//									if (opt.d3d.cEspNameCol ==1)NameCol=RED;
//									if (opt.d3d.cEspNameCol ==2)NameCol=GREEN;
//									if (opt.d3d.cEspNameCol ==3)NameCol=BLUE;
//									if (opt.d3d.cEspNameCol ==4)NameCol=GREY;
//									if (opt.d3d.cEspNameCol ==5)NameCol=YELLOW;
//									if (opt.d3d.cEspNameCol ==6)NameCol=ORANGE;
//
//										if(opt.d3d.EspName)
//										{
//											char pName[33];
//											sprintf_s (pName, "%s", pNames->szNames );
//											DrawOutlineString((float)HeadScaled.x-9,HeadScaled.y-35, NameCol, DT_NOCLIP, pFont2, pName );
//										}
//
///*-------------------------------------------------------------------------------------------------------------------*/
//												if (opt.d3d.cEspHeadCol ==0)HeadCol=WHITE;
//												if (opt.d3d.cEspHeadCol ==1)HeadCol=RED;
//												if (opt.d3d.cEspHeadCol ==2)HeadCol=GREEN;
//												if (opt.d3d.cEspHeadCol ==3)HeadCol=BLUE;
//												if (opt.d3d.cEspHeadCol ==4)HeadCol=GREY;
//												if (opt.d3d.cEspHeadCol ==5)HeadCol=YELLOW;
//												if (opt.d3d.cEspHeadCol ==6)HeadCol=ORANGE;
//
//													if (opt.d3d.EspHead)
//													{
//														Tools.FillRGB((float)HeadScaled.x, (float)HeadScaled.y, 2, 2,HeadCol, pDevice );
//													}
///*-------------------------------------------------------------------------------------------------------------------*/													
//													if (opt.d3d.cEspBoneCol ==0)BoneCol=WHITE;
//													if (opt.d3d.cEspBoneCol ==1)BoneCol=RED;
//													if (opt.d3d.cEspBoneCol ==2)BoneCol=GREEN;
//													if (opt.d3d.cEspBoneCol ==3)BoneCol=BLUE;
//													if (opt.d3d.cEspBoneCol ==4)BoneCol=GREY;
//													if (opt.d3d.cEspBoneCol ==5)BoneCol=YELLOW;
//													if (opt.d3d.cEspBoneCol ==6)BoneCol=ORANGE;
//
//													/*if(opt.d3d.EspBone){
//														if (!GetUserLife(i) && GetCharaIndex() != i){
//														if (GetCharaIndex() %2 != i % 2){
//															if(vStart = Leher){//leher
//															if(vEnd = Kepala){//head
//															if( ADDXW2S(pDevice,vStart,vvStart)){
//															if( ADDXW2S(pDevice,vEnd,vvEnd)){
//																if(vStart2 = Leher ){
//																if(vEnd2 = Badan)	{
//																if( ADDXW2S(pDevice,vStart2,vvStart2))	{
//																if( ADDXW2S(pDevice,vEnd2,vvEnd2))	{
//																	if(vStart3 = Leher  ){
//																	if(vEnd3 = LTangan){
//																	if( ADDXW2S(pDevice,vStart3,vvStart3))	{
//																	if( ADDXW2S(pDevice,vEnd3,vvEnd3))	{
//																		if(vStart4 = Leher){
//																		if(vEnd4 = RTangan){
//																		if( ADDXW2S(pDevice,vStart4,vvStart4))	{
//																		if( ADDXW2S(pDevice,vEnd4,vvEnd4))	{
//																			if(vStart5 = Badan){
//																			if(vEnd5 = LPanggul){
//																			if( ADDXW2S(pDevice,vStart5,vvStart5))	{
//																			if( ADDXW2S(pDevice,vEnd5,vvEnd5))	{
//																				if(vStart6 = Badan){
//																				if(vEnd6 = RPanggul){
//																				if( ADDXW2S(pDevice,vStart6,vvStart6))	{
//																				if( ADDXW2S(pDevice,vEnd6,vvEnd6))	{
//																					if(vStart7 = LPanggul){
//																					if(vEnd7 = LPaha){
//																					if( ADDXW2S(pDevice,vStart7,vvStart7))	{
//																					if( ADDXW2S(pDevice,vEnd7,vvEnd7))	{
//																						if(vStart8 = RPanggul){
//																						if(vEnd8 = RPaha){
//																						if( ADDXW2S(pDevice,vStart8,vvStart8))	{
//																						if( ADDXW2S(pDevice,vEnd8,vvEnd8))	{
//																							if(vStart9 = LPaha){
//																							if(vEnd9 = LKaki)	{
//																							if( ADDXW2S(pDevice,vStart9,vvStart9))	{
//																							if( ADDXW2S(pDevice,vEnd9,vvEnd9))	{
//																								if(vStart10 = RPaha)	{
//																								if(vEnd10 = RKaki){
//																								if( ADDXW2S(pDevice,vStart10,vvStart10)){
//																								if( ADDXW2S(pDevice,vEnd10,vvEnd10)){
//															
//														
//															DrawLineBone(vvStart.x,vvStart.y,vvEnd.x,vvEnd.y,1,BoneCol);//leher-kepala
//																DrawLineBone(vvStart2.x,vvStart2.y,vvEnd2.x,vvEnd2.y,1,BoneCol);//badan ampe kontol
//																	DrawLineBone(vvStart3.x,vvStart3.y,vvEnd3.x,vvEnd3.y,1,BoneCol);//tangan kiri
//																		DrawLineBone(vvStart4.x,vvStart4.y,vvEnd4.x,vvEnd4.y,1,BoneCol);//tangan kanan
//																			DrawLineBone(vvStart5.x,vvStart5.y,vvEnd5.x,vvEnd5.y,1,BoneCol);//pinggul kiri
//																				DrawLineBone(vvStart6.x,vvStart6.y,vvEnd6.x,vvEnd6.y,1,BoneCol);//pinggul kanan
//																					DrawLineBone(vvStart7.x,vvStart7.y,vvEnd7.x,vvEnd7.y,1,BoneCol);//paha kiri
//																						DrawLineBone(vvStart8.x,vvStart8.y,vvEnd8.x,vvEnd8.y,1,BoneCol);//paha kanan
//																							DrawLineBone(vvStart9.x,vvStart9.y,vvEnd9.x,vvEnd9.y,1,BoneCol);//kaki kiri
//																								DrawLineBone(vvStart10.x,vvStart10.y,vvEnd10.x,vvEnd10.y,1,BoneCol);//kaki kanan
//														}}
//																								}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}*/
//												}
//											}
//										}
//									}
//								}
//								}
							//}
//	}

void ADDXESP(LPDIRECT3DDEVICE9 pDevice) 
{
	DWORD dwBasePlayer = *(PDWORD)(BASE_PLAYER2);
	DWORD dwBaseHealth = *(PDWORD)(BASE_HEALTH2);
	DWORD TeamColor;

	CTeam *pTeam = (CTeam*)(dwBasePlayer + OFS_TEAM);
	//CTeamScore *pTeamScore = (CTeamScore*)(dwBasePlayer + 0x3B7A4);
	
	int MyTeam = GetTeam(pTeam->iTeam);

	float ScreenCenterX = (Tools.g_ViewPort.Width /2.0f);
	float ScreenCenterY = (Tools.g_ViewPort.Height /2.0f);
	float ScreenBottomY = (Tools.g_ViewPort.Height);

	CPlayersX *pNearEnt = NULL;
	float NearTargetX = 0.0f;
	float NearTargetY = 0.0f;
	float DisX = 0.0f;
	float DisY = 0.0f;
	CNames *pTarget = NULL;
	CHealth *iTarget = NULL;
	float Nearest = (float) INT_MAX;
	float PosX = 0.0f;
	float PosY = 0.0f;

	//int ServerX1 = 100;
	//int ServerY1 = 480;
	//int ServerX2 = 750;
	//int ServerY2 = 480;

	if(IsBadReadPtr((PDWORD)*(PDWORD)BASE_AMMO2, 4) == 0)
	{
		for(DWORD i = 0; i <= 15; i++)
		{
			CNames *pNames = (CNames*)((dwBasePlayer + OFS_NAMES) + i * 0x21);
			CHealth *pHealth = (CHealth*)((dwBaseHealth + 0x262) + i * 0x104);
			CPlayersX *pPlayer = (CPlayersX*)((*(PDWORD)(dwBasePlayer + 0x4 * i + OFS_PLAYER)) + 0x64);
			CPlayersX *pLocal = (CPlayersX*)((*(PDWORD)(dwBasePlayer + 0x4 * pTeam->iTeam + OFS_PLAYER)) + 0x64);

			int iTeam = GetTeam(i);
			Player.x = pPlayer->pos.x;
			Player.y = pPlayer->pos.y;
			Player.z = pPlayer->pos.z;

			HeadPos.x = pPlayer->pos.x;
			HeadPos.y = 1.5f + pPlayer->pos.y;
			HeadPos.z = pPlayer->pos.z;

			float Nearest = (float)INT_MAX;
			float PosX = 0.0f;
			float PosY = 0.0f;

			D3DXVECTOR3 MyDistance	=	pLocal->pos - pPlayer->pos;
			float MyaDistance = D3DXVec3Length(&MyDistance );

			if (iTeam == MyTeam)continue;

			///*if(opt.esp.ESPSelectTeam == 0)*/if(iTeam == MyTeam)continue;
			///*if(opt.esp.ESPSelectTeam == 1)*/if(iTeam != MyTeam)continue;
			
			//if(iTeam == 1)TeamColor = D3DCOLOR_ARGB(255, 255, 0, 0);
			//else if(iTeam == 2)TeamColor = D3DCOLOR_ARGB(255, 19, 84, 199);
			//else continue;

			if(ADDXW2S(pDevice, HeadPos, HeadScaled) == TRUE)
			{
				if (!GetUserLife(i) && GetCharaIndex() != i)
								{
									if (GetCharaIndex() %2 != i % 2)
									{
										PosX = ScreenCenterX - HeadPos.x;
										PosY = ScreenCenterY - HeadPos.y;

										DisX = (pLocal->pos.x - pPlayer->pos.x) * (pLocal->pos.x - pPlayer->pos.x) ;
										DisY = (pLocal->pos.y - pPlayer->pos.y) * (pLocal->pos.y - pPlayer->pos.y) ;

										float Temp = sqrt(PosX) + sqrt(PosY);
										float Temp2 = sqrt(DisX) + sqrt(DisY);
										if (Temp > Nearest && Temp2 > Nearest) continue;
										if (Nearest < 0.0f || Temp < Nearest)
										{
										if (Temp2 < Nearest)
										{
										pNearEnt = pPlayer;
										//pTarget = pNames;
										//iTarget = pHealth;
										Nearest = Temp;
										NearTargetX = HeadScaled.x;
										NearTargetY = HeadScaled.y;
										}
										}
									}
				
				if(opt.d3d.EspName)
				{
					/*DrawString(HeadScaled.x-40, HeadScaled.y-10, TeamColor, "%s", pNames->szNames);*/
				char pName[33];
				sprintf_s (pName, "%s", pNames->szNames );
				DrawOutlineString((float)HeadScaled.x-9,HeadScaled.y-35, RED, DT_NOCLIP, pFont2, pName );
				}

					if (opt.d3d.EspHead)
					{
						Tools.FillRGB((float)HeadScaled.x, (float)HeadScaled.y, 2, 2,YELLOW, pDevice );
					}
			}
			}

			if(ADDXW2S(pDevice, Player, PlayerScaled) == TRUE)
			{ 
				/*if(opt.d3d.EspHealth)
					iDHealth(pDevice, (int)PlayerScaled.x-25,(int)PlayerScaled.y, pHealth->CurHP);

				/*if(opt.d3d.EspDistance)
					DrawString(PlayerScaled.x-40, PlayerScaled.y-12, D3DCOLOR_ARGB(255, 255, 0, 0), "%0.1f M", (FindDistance(pLocal->pos, pPlayer->pos, pPlayer,pLocal))/4);*/

				//if (pHealth->CurHP > 1) 
				//{
				if (!GetUserLife(i) && GetCharaIndex() != i)
								{
									if (GetCharaIndex() %2 != i % 2)
									{
										PosX = ScreenCenterX - HeadPos.x;
										PosY = ScreenCenterY - HeadPos.y;

										DisX = (pLocal->pos.x - pPlayer->pos.x) * (pLocal->pos.x - pPlayer->pos.x) ;
										DisY = (pLocal->pos.y - pPlayer->pos.y) * (pLocal->pos.y - pPlayer->pos.y) ;

										float Temp = sqrt(PosX) + sqrt(PosY);
										float Temp2 = sqrt(DisX) + sqrt(DisY);
										if (Temp > Nearest && Temp2 > Nearest) continue;
										if (Nearest < 0.0f || Temp < Nearest)
										{
										if (Temp2 < Nearest)
										{
										pNearEnt = pPlayer;
										//pTarget = pNames;
										//iTarget = pHealth;
										Nearest = Temp;
										NearTargetX = HeadScaled.x;
										NearTargetY = HeadScaled.y;
										}
										}
									}
					if(opt.d3d.EspBox)
					{
						DrawBoxESP((float)PlayerScaled.x-(5000/MyaDistance)/30,(float)PlayerScaled.y-(35000/MyaDistance)/45, 50000/MyaDistance/6*2/40,50000/MyaDistance/3*2/40, BLUE, pDevice);
					}
					if(opt.d3d.EspLine)
					{
						DrawLineBone((float)ScreenCenterX, (float)ScreenBottomY, (float)PlayerScaled.x, (float)PlayerScaled.y, 1, D3DCOLOR_ARGB(255, 0, 255, 0));
					}
				}
				//}
			}
		}

	}
}

/*-------------------------------------------------------------------------------------------------------------------*/
DWORD GetPlayerTarget(int MyIdx)
{
	DWORD BasePlayer_B = *(DWORD*)(BASE_HEALTH2);
	if(IsBadReadPtr((void*)BasePlayer_B,4))return 0;
	DWORD PlayerIndexA = *(DWORD*)(BasePlayer_B + 0x14 + (MyIdx * 4));
	if(IsBadReadPtr((void*)PlayerIndexA,4))return 0;
	DWORD PlayerIndexB = *(DWORD*)(PlayerIndexA + PTR_BUTTON1);
	if(IsBadReadPtr((void*)PlayerIndexB,4))return 0;
	DWORD IsTargetingEnemy = *(DWORD*)(PlayerIndexB + PTR_BUTTON2);
	if(IsBadReadPtr((void*)IsTargetingEnemy,4))return 0;
	return IsTargetingEnemy;
}

int GetTargetIndex(DWORD PlayerTarget)
{
	DWORD BasePlayer_B = *(DWORD*)(BASE_HEALTH2);
	if(PlayerTarget && BasePlayer_B){
		for(int i = 0; i<=15; i++){
			DWORD PlayerIndexA = *(DWORD*)(BasePlayer_B + 0x14 + (i * 4));
			if(PlayerIndexA == PlayerTarget)return i;
		}
	}
	return -1;
}

/*------------------------------------------- Declaration AutoShoot ------------------------------------------------------*/
_declspec(naked)void MouseHook()
{
	_asm {
		cmp [Shot],0
			je Normal
			mov eax, 1;
		ret
Normal:
		mov eax, [ecx+0x20]
		ret
	}
}

void DoAutoShot(LPDIRECT3DDEVICE9 pDevice)
{
	if(HookedShot == false){
		MakePTR((PBYTE)BASE_GETBUTTON,(DWORD)MouseHook);
		HookedShot = true;
	}
	if(opt.d3d.AutoShot){
		if(GetPlayerTarget(GetMyCharaIndex()) > NULL)Shot = true;
		else Shot = false;
	}
}

/*------------------------------------------- Declaration AutoHeadshoot ------------------------------------------------------*/
void DoAutoHSNoSyarat(LPDIRECT3DDEVICE9 pDevice)
{
if(opt.d3d.HeadShot)
{
	DWORD pMyTarget = GetPlayerTarget(GetMyCharaIndex());
	if(pMyTarget > NULL)
	{
		DWORD TargetIndex = GetTargetIndex(pMyTarget);
		D3DXVECTOR3 OnWorld,OnScreen;
		D3DXVECTOR3 NeckPos,BodyPos ;
		DWORD ADR_PLAYER		= *(DWORD*)(BASE_PLAYER2);
		CTeam		*pTeam		= ((CTeam*)(ADR_PLAYER + OFS_TEAM));
		DWORD OldProtect;
		DWORD pCalculate		= *(DWORD*)(ADR_PLAYER + 0x4 * TargetIndex + OFS_PLAYER );
		DWORD pCalculate2		= *(DWORD*)(ADR_PLAYER + 0x4 * pTeam->iTeam + OFS_PLAYER );
		VirtualProtect ( (LPVOID)(pCalculate), sizeof (pCalculate), PAGE_EXECUTE_READWRITE, &OldProtect );
		VirtualProtect ( (LPVOID)(pCalculate2), sizeof (pCalculate2), PAGE_EXECUTE_READWRITE, &OldProtect );
		CPlayers	*pPlayer	= (CPlayers*)(pCalculate + 0x64 );
		CPlayers	*pLocal		= (CPlayers*)(pCalculate2 + 0x64 );
		VirtualProtect ( (LPVOID)(pCalculate), sizeof (pCalculate), OldProtect, &OldProtect );
		VirtualProtect ( (LPVOID)(pCalculate2), sizeof (pCalculate2), OldProtect, &OldProtect );
		HeadPos.x = pPlayer->pos.x;
		HeadPos.y = 1.4f + pPlayer->pos.y;
		HeadPos.z = pPlayer->pos.z;
		//GetUserBone(OnWorld,TargetIndex,7.0);
		BulletEnable = true;
		fX = HeadPos.x;
		fY = HeadPos.y;// + 0.1f;
		fZ = HeadPos.z;
	}
	else BulletEnable = false;
}
if(opt.d3d.HeadShot == 0 && !opt.d3d.HeadShot)
{
	BulletEnable = false;
}
}

/*------------------------------------------- Declaration AutoBody ------------------------------------------------------*/
void DoAutoBody(LPDIRECT3DDEVICE9 pDevice)
{
if(opt.d3d.AutoBody)
{	
	DWORD pMyTarget = GetPlayerTarget(GetMyCharaIndex());
	if(pMyTarget > NULL)
	{
		DWORD TargetIndex = GetTargetIndex(pMyTarget);
		D3DXVECTOR3 OnWorld,OnScreen;
		D3DXVECTOR3 NeckPos,BodyPos ;
		DWORD ADR_PLAYER		= *(DWORD*)(BASE_PLAYER2);
		CTeam		*pTeam		= ((CTeam*)(ADR_PLAYER + OFS_TEAM));
		DWORD OldProtect;
		DWORD pCalculate		= *(DWORD*)(ADR_PLAYER + 0x4 * TargetIndex + OFS_PLAYER );
		DWORD pCalculate2		= *(DWORD*)(ADR_PLAYER + 0x4 * pTeam->iTeam + OFS_PLAYER );
		VirtualProtect ( (LPVOID)(pCalculate), sizeof (pCalculate), PAGE_EXECUTE_READWRITE, &OldProtect );
		VirtualProtect ( (LPVOID)(pCalculate2), sizeof (pCalculate2), PAGE_EXECUTE_READWRITE, &OldProtect );
		CPlayers	*pPlayer	= (CPlayers*)(pCalculate + 0x64 );
		CPlayers	*pLocal		= (CPlayers*)(pCalculate2 + 0x64 );
		VirtualProtect ( (LPVOID)(pCalculate), sizeof (pCalculate), OldProtect, &OldProtect );
		VirtualProtect ( (LPVOID)(pCalculate2), sizeof (pCalculate2), OldProtect, &OldProtect );
		BodyPos.x = pPlayer->pos.x;
		BodyPos.y = 1.4f + pPlayer->pos.y;
		BodyPos.z = pPlayer->pos.z;
		//GetUserBone(OnWorld,TargetIndex,5);
		BulletEnable = true;
		fX = BodyPos.x;
		fY = BodyPos.y;// + 0.1f;
		fZ = BodyPos.z;
	}
	else BulletEnable = false;
}
if(opt.d3d.AutoBody == 0 && !opt.d3d.AutoBody)
{
	BulletEnable = false;
}
}

/*-------------------------------------------------------------------------------------------------------------------*/
void KickPlayer (int Idx,int Reason)
{
		DWORD KickUser		= 0x552C00/*ResultVote*/;
		DWORD BaseECX		= *(DWORD*)(BASE_PLAYER2);
		PlayerKickData KickData;
		PlayerKickData* pKickData;
		KickData.Index = Idx;
		KickData.Reason = Reason;
		pKickData = &KickData;
		__asm{
			push 0
			mov eax,[pKickData]
			add eax,4
			push eax
			mov edx,[pKickData]
			push edx
			//push 0xA0
			push 0xA1
			mov ecx,[BaseECX]
			call [KickUser]
		}
}

/*------------------------------------------- Declaration Auto Vote ------------------------------------------------------*/
DWORD WINAPI DoFloodVK()
{
	for(;;)
	{
		if(GetBattleState()){
			if(opt.d3d.AutoVote)
		{
			for(int i = 0; i <= 16; i++)
			{
				int iSlot = GetMyCharaIndex();
				if(iSlot == i)continue;
				if(!IsAlive(i))continue;
				KickPlayer(i,2);
				Sleep(2500);
			}
		}
		}
		Sleep(2500);
	}
	return 0;
}

/*------------------------------------------- Declaration Ghost Hide ------------------------------------------------------*/
void GhostHide(void)
{
	DWORD PactPBexe = *(DWORD *)BASE_PLAYER2;
	CTeam* GetCSlot	= (CTeam*)(PactPBexe + OFS_TEAM);
	if(bGhost == false){
		Ghoster = Read( (DWORD)BASE_HEALTH2, OFS_HEALTH-0x4 + GetCSlot->iTeam * HPSIZE);
	}
	if(opt.d3d.Zombie == 0){
		bGhost = false;
		WritePtr( (DWORD)BASE_HEALTH2, OFS_HEALTH-0x4 + GetCSlot->iTeam * HPSIZE, Ghoster);
	}
	if(opt.d3d.Zombie == 1){
		bGhost = true;
		WritePtr( (DWORD)BASE_HEALTH2, OFS_HEALTH-0x4 + GetCSlot->iTeam * HPSIZE, Ghoster-1);
	}
}

/*------------------------------------------- Declaration Range Weapon ------------------------------------------------------*/
float acr = 2000;
DWORD Retn_Range = BASE_RANGE + 0x5;
__declspec(naked) void Range_On()
{
	_asm
	{
		fld dword ptr [acr]
		mov esp,ebp
			jmp [Retn_Range]
	}
}

__declspec(naked) void Range_Off()
{
	_asm
	{
		fld dword ptr[ebp-04]
		mov esp,ebp
			jmp [Retn_Range]
	}
}

void RangeWeapon()
{
	if(opt.d3d.ScdKillerKey == 1){
		MakeJMP((PBYTE)BASE_RANGE, (DWORD)Range_On, 5);
	}else{
		MakeJMP((PBYTE)BASE_RANGE, (DWORD)Range_Off, 5);
	}
}

/*------------------------------------------- Declaration Suicide ------------------------------------------------------*/
typedef void (__thiscall * tCmd_Damage)(DWORD CGameCharaLocalBase, int HPDrain, int a2, int a3);
tCmd_Damage Cmd_Damage;

void KillMySelf()
{
	Cmd_Damage = (tCmd_Damage)(SUICIDE);
	DWORD CGameCharaLocalBase = *(DWORD*)(BASE_AMMO2);
	Cmd_Damage(CGameCharaLocalBase,0xFF,0xFFFF,false);
	
}

DWORD Define_X(DWORD dwPtr, DWORD dwOfs, DWORD dwOfs2){ 
	DWORD C; 
	if(IsBadReadPtr((PDWORD)(dwPtr),4)==0){ 
		C=*(PDWORD)((DWORD)(dwPtr))+dwOfs; 
		if(IsBadReadPtr((PDWORD)(C),4)==0){ 
		C=*(PDWORD)((DWORD)(C))+dwOfs2;
		if(IsBadReadPtr((PDWORD)(C),4)==0){ 
			return *(PDWORD)C; 
		} }
	} 
	return C;
}

/*------------------------------------------- Declaration Auto Suicide ------------------------------------------------------*/
void Auto_KillMySelf()
{
	if(opt.d3d.Suicide == 2){
	Cmd_Damage = (tCmd_Damage)(SUICIDE);
	DWORD CGameCharaLocalBase = *(DWORD*)(BASE_AMMO2);
	Cmd_Damage(CGameCharaLocalBase,0xFF,0xFFFF,false);
	}
}

/*------------------------------------------- Declaration Fake ------------------------------------------------------*/
DWORD CGameCharaBaseShoot(void) 
{ 
	unsigned long dwBase = *(DWORD*)BASE_HEALTH2; 
	return dwBase; 
}

typedef void (__thiscall * tSetCharaWeaponSet)(DWORD CGameCharaManager,DWORD CGameCharaBase, DWORD pNetCharaInfo); 
tSetCharaWeaponSet SetCharaWeaponSet;

void FakeReplace() 
{
			DWORD BasePlayer_A = *(DWORD*)(BASE_PLAYER2); 
			DWORD BasePlayer_B = *(DWORD*)(BASE_HEALTH2); 
			int MyIndex = GetMyCharaIndex(); 
			DWORD CGameCharaManager = CGameCharaBaseShoot(); 
			DWORD CGameCharaBase = *(DWORD*)(BasePlayer_B + 0x14 + (MyIndex*4)); 
			DWORD pNetCharaInfo = BasePlayer_A + ((OFS_WEAPON-0x134) + (MyIndex*WEAPSIZE)); 
			SetCharaWeaponSet = (tSetCharaWeaponSet)CALL_SETWEAPON; 
			SetCharaWeaponSet(CGameCharaManager, CGameCharaBase, pNetCharaInfo);
}

void Cmd_Install_On() 
{ 	
	DWORD Cmd_Install_On		= 0x6FFD00;
	DWORD g_pGameContext_On		= *(DWORD*)(BASE_AMMO2);
    __asm { 
        push 0x1 
        mov ecx, [g_pGameContext_On] 
        call [Cmd_Install_On]
    } 
}

void Cmd_Uninstall_On() 
{ 	
	DWORD Cmd_UnBaseStage_On    = 0x4D3460;
	DWORD Cmd_Uninstall_On		= 0x556870;
	DWORD g_pBasePlayer_On		= *(DWORD*)(BASE_PLAYER2);
    __asm { 
        push 0x1
		mov ecx, [g_pBasePlayer_On]
		call [Cmd_UnBaseStage_On]
        mov ecx, eax
        call [Cmd_Uninstall_On] 
    } 
}

/*------------------------------------------- Declaration All Hacks ------------------------------------------------------*/
DWORD WINAPI All_ThreadHax()
{
/*	if( opt.d3d.Repeat )
	{
		WritePtr( (DWORD)BASE_AMMO2, PTR_REPEAT, 0x40);
	}

	if( opt.d3d.Fall )
	{
		WritePtr( (DWORD)BASE_AMMO2, PTR_FALL, 0x64047214);
	}*/

	if( opt.d3d.Afk )
	{
		LongPtr( (DWORD)BASE_IDLE2, 0x18, PTR_IDLE1, 0x41);
		LongPtr( (DWORD)BASE_IDLE2, 0x18, PTR_IDLE2, 0x42);
	}

	if( opt.d3d.Move )
	{
		_WriteMEM( (DWORD)BASE_MOVE2, 0x44, 0x18, 0xDC, 0x4);
	}

	if( opt.d3d.AccGM==1 )
	{
		unsigned long dwBase	= *(DWORD*)(BASE_PLAYER2);
		CTeam *pTeam		= ((CTeam*)(dwBase + OFS_TEAM)); 
		int MyTeam = GetTeam(pTeam->iTeam);
			GM	  *DualDinamic = (GM*)((dwBase + OFS_RANK2)+ pTeam->iTeam * RANKSIZE);
			CNames		*pFake	= (CNames*)((dwBase + OFS_NAMES) + pTeam->iTeam  * NAMESIZE);
			if(opt.d3d.AccGM==1)
			{
				DualDinamic->iRank = 0x36;
				DualDinamic->iHack = 0xFFFFFF;
				strcpy(pFake->szNames,"{/COL}");
			}
	}
	
	if( opt.d3d.AccGM==2 )
	{
		unsigned long dwBase	= *(DWORD*)(BASE_PLAYER2);
		CTeam *pTeam		= ((CTeam*)(dwBase + OFS_TEAM)); 
		int MyTeam = GetTeam(pTeam->iTeam);
			GM	  *DualDinamic = (GM*)((dwBase + OFS_RANK2)+ pTeam->iTeam * RANKSIZE);
			CNames		*pFake	= (CNames*)((dwBase + OFS_NAMES) + pTeam->iTeam  * NAMESIZE);
			if(opt.d3d.AccGM==2)
			{
				DualDinamic->iRank = 0x35;
				DualDinamic->iHack = 0xFFFFFF;
				strcpy(pFake->szNames,"\GM-FUCK/");
			}
	}

	if( opt.d3d.Plant==1 )
	{
		cGameBases *GameBase = (cGameBases*) *(DWORD*)(BASE_PLAYER2);
		DWORD dwBase = *(DWORD*)(BASE_PLAYER2);
		CTeam *pTeam				= ((CTeam*)(dwBase + OFS_TEAM)); 
		DWORD OldProtect;
		DWORD pCalculate2 = *(DWORD*)(dwBase + 0x4 * pTeam->iTeam + OFS_PLAYER);
		CPlayers	*Me	= (CPlayers*)(pCalculate2 /*+ 0x64*/ );
		if( opt.d3d.Plant==1 )
		{
			GameBase->StageInfo->BombPositionA.x = Me->pos.x;
			GameBase->StageInfo->BombPositionA.y = Me->pos.y;
			GameBase->StageInfo->BombPositionA.z = Me->pos.z;
		}
	}

	if( opt.d3d.Plant==2 )
	{
		cGameBases *GameBase = (cGameBases*) *(DWORD*)(BASE_PLAYER2);
		DWORD dwBase = *(DWORD*)(BASE_PLAYER2);
		CTeam *pTeam				= ((CTeam*)(dwBase + OFS_TEAM)); 
		DWORD OldProtect;
		DWORD pCalculate2 = *(DWORD*)(dwBase + 0x4 * pTeam->iTeam + OFS_PLAYER);
		CPlayers	*Me	= (CPlayers*)(pCalculate2 /*+ 0x64*/ );
		if( opt.d3d.Plant==2 )
		{
			GameBase->StageInfo->BombPositionB.x = Me->pos.x;
			GameBase->StageInfo->BombPositionB.y = Me->pos.y;
			GameBase->StageInfo->BombPositionB.z = Me->pos.z;
		}
	}

	if ( opt.d3d.BugWs == 0 )
	{
		PacthHook((void *)(BASE_UNYU),(int*)(PBYTE)"\xBE",1);
	}
	if ( opt.d3d.BugWs == 1 )
	{
		PacthHook((void *)(BASE_UNYU),(int*)(PBYTE)"\xC0",1);
	}

/*	if ( opt.d3d.BugDt == 0 )
	{
		PacthHook((void *)(NxCha+ResultDatar/*+0x2),(int*)(PBYTE)"\x89",1);
	}
	if ( opt.d3d.BugDt == 1 )
	{
		PacthHook((void *)(NxCha+ResultDatar/*+0x2),(int*)(PBYTE)"\xFF",1);
	}

	if ( opt.d3d.Invi == 0 )
	{
		PacthHook((void *)(ResultInvi+0x3),(int*)(PBYTE)"\x3C",1);
	}
	if ( opt.d3d.Invi == 1 )
	{
		PacthHook((void *)(ResultInvi+0x3),(int*)(PBYTE)"\x42",1);
	}

	if ( opt.d3d.Wst == 0 )
	{
		PacthHook((void *)(ResultWallshoot),(int*)(PBYTE)"\x75\x1F",2);
	}
	if ( opt.d3d.Wst == 1 )
	{
		PacthHook((void *)(ResultWallshoot),(int*)(PBYTE)"\x90\x90",2);
	}*/

/*-------------------------------------------------------------------------------------------------------------------*/

/*	if( bPiso == false )
	{
		BurstPiso	= _ReadMEM( (DWORD)BASE_AMMO2, PTR_WEAPON, 0x24, CALCWPN1);
	}
	if( opt.d3d.BstPs == 0 )
	{
		bPiso = false;
		_WriteMEM( (DWORD)BASE_AMMO2, PTR_WEAPON, 0x24, CALCWPN1, BurstPiso);
	}
	if( opt.d3d.BstPs == 1 )
	{
		bPiso = true;
		_WriteMEM( (DWORD)BASE_AMMO2, PTR_WEAPON, 0x24, CALCWPN1, BurstPiso);
	}
	
	if( opt.d3d.Quick )
	{
		_WriteMEM( (DWORD)BASE_AMMO2, PTR_QC, 0x3C, 0x64, 1069715291);
	}

	if( opt.d3d.FsSht )
	{
		WritePtr( (DWORD)BASE_AMMO2, PTR_RAPID1, 0);
	}

	if( opt.d3d.FrSpd )
	{
		LongPtr( (DWORD)BASE_AMMO2, PTR_WEAPON, 0x38, 1);
		LongPtr( (DWORD)BASE_AMMO2, PTR_WEAPON, 0x38, 0);
		LongPtr( (DWORD)BASE_AMMO2, 0x30, PTR_RAPID2, 0);
		WritePtr( (DWORD)BASE_AMMO2, PTR_RAPID1, 0);
	}

	if( opt.d3d.NoReload )
	{
		_patchPTR( (DWORD)BASE_AMMO2, PTR_WEAPON, 0x1C, 0x30, 0x67, 65);
		_patchPTR( (DWORD)BASE_AMMO2, PTR_WEAPON, 0x20, 0x30, 0x67, 65);
	}*/

	/*--------------------------------*/
	Auto_KillMySelf();

/*	if(opt.d3d.Zombie00 == 1)
	{
		if(IsKeyPressedF(VK_HOME, 0)&1){
		opt.d3d.Repeat = 1;
		opt.d3d.Zombie=!opt.d3d.Zombie;
		KillMySelf();
		Beep(1000, 100);}
	}

	if(opt.d3d.OnBomb == 1)
	{
		if(IsKeyPressedF(VK_F2, 0)&1){
		FakeReplace();}
	}

	if(opt.d3d.OnRpg == 1)
	{
		if(IsKeyPressedF(VK_LBUTTON, 100)&1){
		FakeReplace();}
	}*/

	if(opt.d3d.Suicide == 1){
	if(IsKeyPressedF(VK_END, 0)&1){
		KillMySelf();
		Beep(1000, 100);
	}}
	
	if(IsKeyPressedF(VK_RMENU, 0)&1){
		opt.d3d.AimBot=!opt.d3d.AimBot;
		Beep(1000, 100);
	}

	if(IsKeyPressedF(VK_LSHIFT, 0)&1){
		opt.d3d.AimBullet=!opt.d3d.AimBullet;
		Beep(1000, 100);
	}

/*	if(IsKeyPressedF(VK_CAPITAL, 0)&1){
		opt.d3d.HeadShot=!opt.d3d.HeadShot;
		Beep(1000, 100);
	}
	
	if(IsKeyPressedF(VK_RSHIFT, 0)&1){
		opt.d3d.AutoBody=!opt.d3d.AutoBody;
		Beep(1000, 100);
	}*/
	
	if(IsKeyPressedF(VK_F6, 0)&1){
		opt.d3d.BugWs=!opt.d3d.BugWs;
		Beep(1000, 100);
	}
	
/*	if(IsKeyPressedF(VK_F7, 0)&1){
		opt.d3d.BugDt=!opt.d3d.BugDt;
		Beep(1000, 100);
	}

	if(IsKeyPressedF(VK_LMENU, 0)&1){
		opt.d3d.Zombie=!opt.d3d.Zombie;
		Beep(1000, 100);
	}
	
	if(IsKeyPressedF(VK_DELETE, 0)&1){
		opt.d3d.ScdKillerKey=!opt.d3d.ScdKillerKey;
		Beep(1000, 100);
	}*/

return (0);
}