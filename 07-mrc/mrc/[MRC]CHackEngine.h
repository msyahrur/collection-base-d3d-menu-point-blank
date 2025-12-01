//----------------------------------------------------------------------------------------
//---------------------------------------------------------// [MRC]
//----------------------------------------------------------------------------------------
#include <windows.h>
#include "[MRC]CClass.h"
#include "[MRC]CColor.h"
LPTSTR PointBlankSTR8 = "PointBlank.exe";
//----------------------------------------------------------------------------------------
float xFastReload1=1000;
float xFastReload2;
DWORD g_Reload = RETNeoNoReload;
//----------------------------------------------------------------------------------------
int WHClean,WHGlass,DontFog,DontSmoke,Cross; 
int Accuracy,AimBody;
int AntiRecoil,Quick,FReload;
int Planted,DefuseX;
//----------------------------------------------------------------------------------------
bool GetBattleState() { 
	unsigned long xBase = *(DWORD*)(ResultBaseAmmo2); 
	if(xBase > NULL){ 
		return true; 
	} return false; 
}
//----------------------------------------------------------------------------------------
int GetTeam(char MyTeam)
{
for(int i = 0; i < 16; i+=2)
if(i == MyTeam)return 2;
for(int i = 1; i < 16; i+=2)
if(i == MyTeam)return 1;
return -1;
}
//----------------------------------------------------------------------------------------
int Index;
int GetMyCharaIndex(unsigned int Index) 
{ 
	DWORD dwI3EXEC = (DWORD)GetModuleHandleA(PointBlankSTR8); 
	unsigned long dwBase = *(DWORD*)(dwI3EXEC + ResultBasePlayer); 
	CTeam *MyTeam = (CTeam*) ((dwBase + OFS_Team)); 
	Index=MyTeam->iTeam; 
	return Index; 
}
//----------------------------------------------------------------------------------------
int GetMyCharaIndex2() 
{ 
unsigned long dwBase = *(DWORD*)(dwPBExe + ResultBasePlayer); 
CTeam *MyTeam = (CTeam*) ((dwBase + OFS_Team)); 
return MyTeam->iTeam; 
} 
//----------------------------------------------------------------------------------------
__declspec( naked ) void speedreload_on(){
_asm{
fstp dword ptr [ebp-0x0C]
movss [xFastReload2],xmm0
movss xmm0,[xFastReload1]
movss [ebp-0x0C],xmm0
movss xmm0,[xFastReload2]
mov ecx,[ebp-0x14]
jmp [g_Reload]
}}
//-----------------------------------------------------------------------------------------
DWORD WINAPI NormalHacks()
{
	if(GetBattleState()){
	if(AntiRecoil==1){
		MemWrite((void*)NeoNoRecoil1,(void*)(PBYTE)"\xD9\x45\xFF",3);
		MemWrite((void*)NeoNoRecoil2,(void*)(PBYTE)"\xD9\x45\xFF",3);}
	if(AntiRecoil==0){
		MemWrite((void*)NeoNoRecoil1,(void*)(PBYTE)"\xD9\x45\xF8",3);
		MemWrite((void*)NeoNoRecoil2,(void*)(PBYTE)"\xD9\x45\xF8",3);
	}}
//------------------------------------------------------------------------------//
	if(GetBattleState()){
	if(Quick==1){
	MemWrite((void*)NeoQuickChange,(void*)(PBYTE)"\xD9\x45\xFF", 3);
	}
	if(Quick==0){
	MemWrite((void*)NeoQuickChange,(void*)(PBYTE)"\xD9\x45\xF8", 3);
	}}
	if(GetBattleState()){
	if(FReload==1){
	MakeJMP((PBYTE)ResultNoReload,(DWORD)speedreload_on,6);
	}
	if(FReload==0){
	MemWrite((void*)ResultNoReload,(PBYTE)"\xD9\x5D\xF4\x8B\x4D\xEC",6);
	}}
return 0;
}
//----------------------------------------------------------------------------------------
void Cmd_Planted_On(){ 	
DWORD Cmd_Planted_On = ResultPlant;
DWORD g_pGameContext_On	= *(DWORD*)(ResultBaseAmmo2);
__asm { 
push 0x1 
mov ecx, [g_pGameContext_On] 
call [Cmd_Planted_On]
}}
void Cmd_Defiuse_On(){ 	
DWORD Cmd_Defiuse_One = ResultDefus1;
DWORD Cmd_Defiuse_Two = ResultDefus2;
DWORD g_pBasePlayer_On = *(DWORD*)(ResultBasePlayer2);
__asm { 
push 0x1
mov ecx, [g_pBasePlayer_On]
call [Cmd_Defiuse_One]
mov ecx, eax
call [Cmd_Defiuse_Two] 
}}
//----------------------------------------------------------------------------------------
//---------------------------------------------------------// [MRC]
//----------------------------------------------------------------------------------------