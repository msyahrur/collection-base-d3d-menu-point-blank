//Bagus Tuyul
typedef HRESULT (WINAPI* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene = NULL;
typedef HRESULT (WINAPI* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
tDrawIndexedPrimitive oDrawIndexedPrimitive = NULL;
typedef HRESULT (WINAPI* tReset)(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
tReset oReset = NULL;
#define StartRoutine(Function) CreateThread(0,0,(LPTHREAD_START_ROUTINE)Function,0,0,0);

LPD3DXFONT g_pFont = NULL;
ID3DXSprite* textSprite;
ID3DXFont*  mFont;
LPD3DXLINE g_pLine = NULL;
LPD3DXFONT pFont = NULL;
LPD3DXLINE pLine = NULL;
LPDIRECT3DDEVICE9 npDevice;
D3DVIEWPORT9 g_ViewPort;
LPDIRECT3DTEXTURE9 TexRed;
LPDIRECT3DTEXTURE9 TexBlue;
LPDIRECT3DVERTEXBUFFER9 Stream_Data;
UINT Offset = 0;
UINT Stride = 0;
RECT rect,rect2,rect3,rect4;
DWORD GetOriginalEndScene();
DWORD GetOriginalDIP();
float ScreenCenterX, ScreenCenterY = 0, ScreenButtomY;

int MenuFolder[10];
int Drawing		= 0;
int Mpos		= 0;	
int Mmax		= 0;
int DrawFont	= 1;
int Mvisible	= 1;
int Mysize		= 25;
int Mxofs		= 25.0f;
int my			= 20; // Up Down
int	mx			= 270; // Right Left

#define 		MENUMAXINDEX	100
#define 		MENUFOLDER		1
#define 		MENUTEXT		2
#define 		MENUITEM		3
#define			MENUCAT			4
#define			MCOLOR_HEADER	RainbowTextTest
#define			MCOLOR_FOOTER	RainbowTextTest
#define			MCOLOR_CURRENT	Red
#define			MCOLOR_FOLDER	SkyBlue
#define			MCOLOR_TEXT		Orange
#define			MCOLOR_INACTIVE	White
#define			MCOLOR_ACTIVE	Green
#define			MCOLOR_BORDER	Yellow
#define			MCOLOR_BOX		Transparant

struct{
	int  *var;
	int  maxvalue;
	int  typ;
	char *txt;
	char **opt;
}
D3MENU[MENUMAXINDEX];

DWORD ModifyTargetBase[100] = {0};
DWORD MyCurrentWeaponIndex = 0;

int BoneIndexSelector;
char LastEvent[1000];
bool IsInBattle();
bool stateReset[2] = {0};
bool CallerNoRecoil;
bool DebugMode = true;
bool Generate = false;
bool bAimState = false;
bool bHookedLT = false;
bool bHookedTele = false;
bool bEnableVisibleCheck = true;

struct __ScoreInfo
{
public:
	BYTE Kill;
	char _0001[1];
	BYTE Dead;
	char _0003[1];
};

class i3CollideeLine
{
public:
	char _pad1[0x7C];
	D3DXVECTOR3 vStart; 
	D3DXVECTOR3 vEnd;
	D3DXVECTOR3 vDir;
};

float DistanceBetweenVector( D3DXVECTOR3 VecA, D3DXVECTOR3 VecB )
{
        return sqrt( ( ( VecA.x - VecB.x ) * ( VecA.x - VecB.x ) ) +
                 ( ( VecA.y - VecB.y ) * ( VecA.y - VecB.y ) ) +
                 ( ( VecA.z - VecB.z ) * ( VecA.z - VecB.z ) ) );
}

typedef float (__thiscall * tGetLocalTime)(DWORD Base);
tGetLocalTime pGetLocalTime;
typedef int (__thiscall * tReadBaseValue)(DWORD BaseValue);
tReadBaseValue oReadBaseValue;
typedef void (__thiscall* tSetEvent)(void *p, int, const void*, const void*,const void*, const char*, int);
tSetEvent oSetEvent;
enum TSlotWeapon {Primary, Secondary, Melle, Explosive, Special, ExplosiveC4,Teuapal};
bool GetPlayerVisibleStatus(int ActorIndex, int TargetIndex, int BoneTargetIndex);
float DistanceBetweenVector( D3DXVECTOR3 VecA, D3DXVECTOR3 VecB );

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
}; pSetEndVector *SetEndVector = NULL;

DWORD dwStartAddress, dwi3GfxD, dwNxChara, dwBaseDx_Cli, dwSize, i3GfxD, NxChara, BaseDx_CliSize, dwi3FrameworkDx, i3FrameworkDxSize, ModuleD3D9,ModuleD3D9Size;
HMODULE ModuleNX, ModuleFW, ModuleGF, ModuleIP, ModuleSC, ModuleBC;

ofstream infile;
ofstream myFunctionLog;
char dlldir[320];
char *GetDirectoryFile(char *filename)
{
static char path[320];
strcpy(path, dlldir);
strcat(path, filename);
return path;
}

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
}; sEventCode EventCode;

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

struct CNames
{
    char szNames[33];
};

struct CTeam
{
	BYTE iTeam;
};

int GetTeam(char MyTeam)
{
	for(int i = 0; i < 16; i+=2)
		if(i == MyTeam)return 2;
	for(int i = 1; i < 16; i+=2)
		if(i == MyTeam)return 1;
	return -1;
}