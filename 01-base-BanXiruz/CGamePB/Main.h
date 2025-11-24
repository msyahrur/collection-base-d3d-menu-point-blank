//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
typedef HRESULT (WINAPI* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene = NULL;
typedef int (__thiscall * tReadBaseValue)(DWORD BaseValue);
tReadBaseValue oReadBaseValue;
typedef void (__thiscall* tSetEvent)(void *p, int, const void*, const void*,const void*, const char*, int);
tSetEvent oSetEvent;

bool GetPlayerVisibleStatus(int ActorIndex, int TargetIndex, int BoneTargetIndex);
float DistanceBetweenVector(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB);
enum TStageGame{SERVER, CHANNEL, LOBBY, AWAITING, PLAYING};
enum TSlotWeapon {Primary, Secondary, Melle, Explosive, Special, ExplosiveC4, Teuapal};

#define Xx 880
#define Yy 680
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

INPUT buffer[1];
DWORD Ticks,TimeReady;
DWORD Tick = NULL;

ID3DXFont*  mFont;
ID3DXSprite* textSprite;
LPD3DXFONT g_pFont = NULL;
LPD3DXLINE g_pLine = NULL;
LPD3DXFONT pFont = NULL;
LPDIRECT3DDEVICE9 npDevice;
D3DVIEWPORT9 g_ViewPort;
LPDIRECT3DVERTEXBUFFER9 Stream_Data;
UINT Offset = 0;
UINT Stride = 0;
RECT rect,rect2,rect3, rect4;

bool IsInBattle();
bool stateReset[2] = {0};
bool DebugMode = true;
bool CallerNoRecoil;
bool bEnableVisibleCheck = true;
bool bIsAimTargetValid = false;
char LastEvent[1000];
int MyCurrentWeaponIndex;
ofstream myFunctionLog;
DWORD BoneIndexSelector;
DWORD GetOriginalEndScene();

class CRenderContext;
class CGameFramework;
class CGameContext;
class CGameCharaBase;
class CGameCharaManager;