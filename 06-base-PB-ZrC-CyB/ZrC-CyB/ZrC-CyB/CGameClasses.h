/*Classes PBHacks Last Edit By ZrC-CyB Hacks*/

#include "StandardIncludes.h"
//#include "CLogger.h"
#include "CGameOFS.h"

LPTSTR PBViewer = "I3Viewer";
LPTSTR PBWindow = "Point Blank";
LPTSTR PointBlankSTR = "PointBlank.exe";
LPTSTR PointBlanki3Gfx = "i3GfxDx.dll";
HMODULE hGfxDx = LoadLibrary("i3GfxDx.dll");
LPTSTR PointBlanki3Scn = "i3SceneDx.dll";
HMODULE hSceneDx = LoadLibrary("i3SceneDx.dll");
LPTSTR PointBlanki3Bsd = "i3BaseDx_Cli.dll";
LPTSTR PointBlanki3Ntw = "i3NetworkDx_Cli.dll";
LPTSTR PointBlanki3Ipt = "i3InputDx.dll";
LPTSTR PointBlanki3Fm = "i3FrameworkDx.dll";
HMODULE hFrameworkDx = LoadLibrary("i3FrameworkDx.dll");
DWORD NxCha = (DWORD)GetModuleHandleA("NxCharacter.2.8.1.dll");
/*-------------------------------------------------------------------------------------------------------------------*/
class PlayerInfo;
class PlayerKickData;
class RenderContext;
class RenderData;
class i3CollideeLine;
class i3Viewer;
class i3PhysixHitResult;
class CGameBase;
class CBonesContext;
class CBone;
class cGameStageInfo;
class GM;
class CHANGENICK1;
class CHANGENICK2;
class CHANGENICK3;
class CHANGENICK4;

DWORD g_pRenderContext = (DWORD)GetModuleHandleA(PointBlanki3Gfx) + G_PRENDER;
RenderContext *pRC	   = (RenderContext*)(g_pRenderContext);
/*-------------------------------------------------------------------------------------------------------------------*/
struct CPlayers
{
	bool Layer;
    float yaw;
    float pitch;
	char unkn[0x60];
    D3DXVECTOR3 pos;
	D3DXVECTOR3 Targetpos;
};

struct CPlayersX
{
    float yaw;
    float pitch;
    D3DXVECTOR3 pos;
    char unkno8[0x60];
};

struct CTeam
{
	BYTE iTeam;
};
struct CHealth
{
	float CurHP;
};

struct CRank
{
	BYTE iRank;
};

struct CNames
{
	char szNames[33];
};

class CDeathPlayer
{
public:
    BYTE Death[16];
};
 
class CLocalPlayerID
{
public:
    BYTE ID;
};

/*-------------------------------------------------------------------------------------------------------------------*/
class cGameStageInfo
{
public:
	char _pad1[0x230];
	D3DXVECTOR3 BombPositionA; 
	D3DXVECTOR3 BombPositionB;
};

class cGameBases
{
public:
	char _pad1[0x46D28];
//	char _pad1[0x3B850];
	cGameStageInfo* StageInfo;
};

class PlayerInfo
{
public:
	D3DXVECTOR3 origin;
};

class PlayerKickData
{
public:
	int Index;
	int Reason;
};

class RenderContext
{
public:
	RenderData* pRenderData; 
//	char unknown4[930];
//	D3DXVECTOR3 bone;
//	D3DXVECTOR3 bone1;
//	D3DXVECTOR3 bone2;
};

class RenderData
{
public:
	char _0x0000[32];
	D3DXMATRIX ViewMatrix;
	D3DXMATRIX ProjMatrix;
	char _0xA0[4800];
	D3DXMATRIX World;
//	D3DXMATRIX WorldView[80];
};

class Bone
{
public:
	D3DXMATRIX m_Bone;
};

class CGameCharaBoneContext
{
public:
	char nop[0xF4];
	Bone* m_Bone;
};

class CGameCharaBase
{
public:
	char nop[0x68C];
	CGameCharaBoneContext* m_BoneContext;
};

extern RenderContext *pRC;

class GM
{
public:
	BYTE iRank;
	char _0x0001[15];
	WORD iHack;
};

class CHANGENICK1
{
public:
	DWORD iName1;
};

class CHANGENICK2
{
public:
	DWORD iName2;
};

class CHANGENICK3
{
public:
	DWORD iName3;
};

class CHANGENICK4
{
public:
	DWORD iName4;
};
/*-------------------------------------------------------------------------------------------------------------------*/