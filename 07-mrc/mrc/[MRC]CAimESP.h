//----------------------------------------------------------------------------------------
//---------------------------------------------------------// [MRC]
//----------------------------------------------------------------------------------------
#include <windows.h>
#pragma warning ( disable : 4244 4305 )
//----------------------------------------------------------------------------------------
#define PISSS 3.14159265
bool BulletEnable = false;
bool AimOff,AimOff2 = false;
bool Shot = false;
bool HookedShot = false;
float fX,fY,fZ = 0;
DWORD BackupEDXTele = 0;
//----------------------------------------------------------------------------------------
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
//----------------------------------------------------------------------------------------
D3DTLVERTEX CreateD3DTLVERTEX (float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V)
{
	D3DTLVERTEX v;
	v.fX = X;
	v.fY = Y;
	v.fZ = Z;
	v.fRHW = RHW;
	v.Color = color;
	v.fU = U;
	v.fV = V;
	return v;
}
//----------------------------------------------------------------------------------------
void Circle( float x, float y, float rad, bool center, DWORD color ,LPDIRECT3DDEVICE9 pDevice)
{
	const int NUMPOINTS = 34;

	if(!center)
	{
		x -= rad;
		y -= rad;
	}

	D3DTLVERTEX Circle[NUMPOINTS + 1];
	int i;
	float X;
	float Y;
	float Theta;
	float WedgeAngle;
	WedgeAngle = (float)( (2*PISSS) / NUMPOINTS );
	for( i=0; i<=NUMPOINTS; i++ )
	{
		Theta = i * WedgeAngle;
		X = (float)( x + rad * cos(Theta) );
		Y = (float)( y - rad * sin(Theta) );
		Circle[i] = CreateD3DTLVERTEX( X, Y, 0.0f, 1.0f, color, 0.0f, 0.0f );
	}
	pDevice->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
	pDevice->SetTexture( 0, NULL );
	pDevice->DrawPrimitiveUP( D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]) );
}
//----------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
bool GetUserBone(  int Idx, D3DXVECTOR3 &Out, int BoneIdx )
{
	unsigned long dwGameBase = *(DWORD*)(ResultBaseHealth2);
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
//----------------------------------------------------------------------------------------
void DrawLineBone(float StartX, float StartY, float EndX, float EndY, int Width, D3DCOLOR dColor)
{
	pLine[0].SetWidth(Width);
	pLine[0].SetGLLines(0);
	pLine[0].SetAntialias(1);
	D3DXVECTOR2 v2Line[2];
	v2Line[0].x = StartX;
	v2Line[0].y = StartY;
	v2Line[1].x = EndX;
	v2Line[1].y = EndY;
	pLine[0].Begin();
	pLine[0].Draw(v2Line, 2, dColor);
	pLine[0].End();
}

//------------------------------------------------------------------------------
void DesenharBoneco(int iSlot, int Start, int End, DWORD Cor,LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 vStart, vEnd;
	D3DXVECTOR3 vvStart, vvEnd;
	GetUserBone(iSlot, vStart, Start);
	GetUserBone(iSlot, vEnd, End);
	if (ADDXW2S(pDevice,vStart, vvStart))
	{
		if (ADDXW2S(pDevice,vEnd, vvEnd))
		{
			DrawLineBone(vvStart.x, vvStart.y, vvEnd.x, vvEnd.y, 1, Cor);
		}
	}
}
//------------------------------------------------------------------------------
void DrawSkeleton(int iSlot, DWORD Cor, LPDIRECT3DDEVICE9 pDevice)
{
	DesenharBoneco(iSlot, 0, 6, Cor,pDevice);
	DesenharBoneco(iSlot, 6, 10, Cor,pDevice);
	DesenharBoneco(iSlot, 6, 11, Cor,pDevice);
	DesenharBoneco(iSlot, 0, 12, Cor,pDevice);
	DesenharBoneco(iSlot, 0, 13, Cor,pDevice);
	DesenharBoneco(iSlot, 12, 14, Cor,pDevice);
	DesenharBoneco(iSlot, 13, 15, Cor,pDevice);
	DesenharBoneco(iSlot, 14, 8, Cor,pDevice);
	DesenharBoneco(iSlot, 15, 9, Cor,pDevice);
}
//----------------------------------------------------------------------------------------
void FillRGBBOX( float x, float y, float w, float h, D3DCOLOR color){
if( w < 0 )w = 1;
if( h < 0 )h = 1;
if( x < 0 )x = 1;
if( y < 0 )y = 1;
D3DRECT rec = { x, y, x + w, y + h };
npDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}
//----------------------------------------------------------------------------------------
void DrawBorder( float x, float y, float w, float h, int px, float Health){
FillRGBBOX( x, (y + h - px), w, px, TeamColor);
FillRGBBOX( x, y, px, h, TeamColor);
FillRGBBOX( x, y, w, px, TeamColor);
FillRGBBOX( (x + w - px), y, px, h, TeamColor); 
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
//----------------------------------------------------------------------------------------
void DrawBorder( int x, int y, int w, int h, int px, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice )
{
    FillRGB( x, (y + h - px), w, px,    BorderColor, pDevice );
    FillRGB( x, y, px, h,                BorderColor, pDevice );
    FillRGB( x, y, w, px,                BorderColor, pDevice );
    FillRGB( (x + w - px), y, px, h,    BorderColor, pDevice );
}
//----------------------------------------------------------------------------------------
int GetMyCharaIndex()
{
unsigned long dwBase	= *(DWORD*)ResultBasePlayer2;
CTeam *MyTeam = (CTeam*) ((dwBase + OFS_Team));
return MyTeam->iTeam;
}
//---------------------------------------------------------------------------//
BYTE GetUserLife(int iSlot){
DWORD g_pGameContext   = *(DWORD*)ResultBasePlayer2;
CDeathPlayer *Life = (CDeathPlayer *) (g_pGameContext + OFS_Bone);
return Life->Death[iSlot];
}
//---------------------------------------------------------------------------//
int GetCharaIndex(){
DWORD g_pGameContext   = *(DWORD*)ResultBasePlayer2;
CLocalPlayerID *LocID = (CLocalPlayerID *) (g_pGameContext + OFS_Team);
return LocID->ID;
}
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
	float fMaxDistance = 1000.0f;
	D3DXVECTOR3 PlayerEnd, LocPlayer;
	int MyTeam = GetTeam(GetMyCharaIndex());
	unsigned long BASESlot = *(DWORD*) ResultBasePlayer2;
	D3DXVECTOR3 HeadMe,Player,HeadPos ;
	
	for (int i = 0; i <=15; i++)
	{
		CTeam		*pTeam		= ((CTeam*)(BASESlot + OFS_Team));
		DWORD OldProtect;
		DWORD pCalculate		= *(DWORD*)(BASESlot + 0x4 * i + OFS_Player );
		DWORD pCalculate2		= *(DWORD*)(BASESlot + 0x4 * pTeam->iTeam + OFS_Player );
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
//----------------------------------------------------------------------------------------
DWORD OldProtect;
bool BHookedTele,cHookedShot = false;
//----------------------------------------------------------------------------------------
void HookAim()
{
	if(BHookedTele)return;
	MakePTR((PBYTE)ResultBullet,(DWORD)i3CollideeLine_SetEnd);
	BHookedTele = true;
}
//----------------------------------------------------------------------------------------
void Accuracy_Hack(LPDIRECT3DDEVICE9 pDevice)
{
if(Accuracy==1)
{
	BulletEnable = true;
	int AimSlot = GetPriorityTarget();
	if(AimSlot != -1)
	{
		D3DXVECTOR3 OnWorld,OnScreen;
		D3DXVECTOR3 NeckPos,BodyPos;
		DWORD ADR_PLAYER		= *(DWORD*)(ResultBasePlayer2);
		CTeam		*pTeam		= ((CTeam*)(ADR_PLAYER + OFS_Team));
		DWORD OldProtect;
		DWORD pCalculate		= *(DWORD*)(ADR_PLAYER + 0x4 * AimSlot + OFS_Player );
		DWORD pCalculate2		= *(DWORD*)(ADR_PLAYER + 0x4 * pTeam->iTeam + OFS_Player );
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

			int BoneIndexSelector = 0;
			switch(AimBody){
			case 0:
			if( ADDXW2S(pDevice,HeadPos,OnScreen))
			{
					int x = ( GetSystemMetrics( 0 ) / 2);
					int y = ( GetSystemMetrics( 1 ) / 2);
					Circle (OnScreen.x, OnScreen.y,6,true,PINK,pDevice);
					FillRGB(OnScreen.x-10, OnScreen.y, 7, 1,SKYBLUE,pDevice);
					FillRGB(OnScreen.x+4, OnScreen.y, 7, 1,SKYBLUE,pDevice);
					FillRGB(OnScreen.x, OnScreen.y-10, 1, 7,SKYBLUE,pDevice);
					FillRGB(OnScreen.x, OnScreen.y+4, 1, 7,SKYBLUE,pDevice);
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
				Circle (OnScreen.x, OnScreen.y,6,true,PINK,pDevice);
					FillRGB(OnScreen.x-10, OnScreen.y, 7, 1,SKYBLUE,pDevice);
					FillRGB(OnScreen.x+4, OnScreen.y, 7, 1,SKYBLUE,pDevice);
					FillRGB(OnScreen.x, OnScreen.y-10, 1, 7,SKYBLUE,pDevice);
					FillRGB(OnScreen.x, OnScreen.y+4, 1, 7,SKYBLUE,pDevice);
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
if(Accuracy == 0 && !Accuracy)
{
	BulletEnable = false;
}
}
}
//----------------------------------------------------------------------------------------
//---------------------------------------------------------// [MRC]
//----------------------------------------------------------------------------------------