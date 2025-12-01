int MouseDeltaX = 0;
int MouseDeltaY = 0;
bool AimEnable = false;
bool bExecuted = false;
int BoneIndexSelector = 0;
int ScreenCenterX,ScreenCenterY = 0;
#define GPT_FAIL -1
int AimLock,AimTarget,AimHotkey,MouseClick;
#define TEAM_T  0x4FFAF
#define TEAM_CT 0x4CCAF

int GetMyTeam(int MyT)
{

	for(int i = 0; i<=15; i+=2)if(i == MyT)return TEAM_T;
	for(int i = 1; i<=15; i+=2)if(i == MyT)return TEAM_CT;
	return -1;
}


class cCharaMainInfo;
class cCharaTargetBase;
class cCharaTargetBase
{
public:
	char _pad1 [0x160];
	cCharaMainInfo *pInfo;
};
class cCharaMainInfo
{
public:
	char _pad1 [0x94E8];
	DWORD PlayerTarget;
};
DWORD GetPlayerTarget(int Index)
{
//=== Show HUD Nick, deket is type of ================//
DWORD ModuleHandle = (DWORD)GetModuleHandleA("pointblank.exe");
DWORD BasePlayer_B = *(DWORD*)(ModuleHandle + 0x6FEE8C);
if( BasePlayer_B ){
cCharaTargetBase *pTarget = (cCharaTargetBase*)(*(DWORD*)(BasePlayer_B + 0x14 + (Index*4)));
if(pTarget->pInfo && pTarget->pInfo->PlayerTarget)
{
return pTarget->pInfo->PlayerTarget;
}
}
return NULL;
}
int GetTargetIndex(DWORD PlayerTarget)
{
	//=== Show HUD Nick, deket is type of ================//
DWORD ModuleHandle = (DWORD)GetModuleHandleA("Pointblank.exe");
DWORD BasePlayer_B = *(DWORD*)(ModuleHandle + 0x6FEE8C);
if(PlayerTarget && BasePlayer_B){
for(int i = 0; i<=15; i++){
DWORD PlayerIndexA = *(DWORD*)(BasePlayer_B + 0x14 + (i * 4));
if(PlayerIndexA == PlayerTarget)return i;
}
}
return -1;
}
