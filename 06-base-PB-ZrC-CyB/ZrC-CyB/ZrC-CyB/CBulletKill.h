#include <windows.h>
#include <fstream>
#include "CGameSDK.h"

DWORD Base_DoLine,Base_CamPos,Base_HitEvent,Base_HitEventt,CallHitEvent,CallDoLineColl,CallGetCamVPoss;
/*-------------------------------------------------------------------------------------------------------------------*/
DWORD Define_1(DWORD dwPtr, DWORD dwOfs, DWORD dwOfs2){ 
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

/*-------------------------------------------------------------------------------------------------------------------*/
DWORD Define_2(DWORD dwPtr, DWORD dwOfs){ 
	DWORD C; 
	if(IsBadReadPtr((PDWORD)(dwPtr),4)==0){ 
		C=*(PDWORD)((DWORD)(dwPtr))+dwOfs; 
		if(IsBadReadPtr((PDWORD)(C),4)==0){ 
			return *(PDWORD)C; 
		} 
	} 
	return C;
}

/*-------------------------------------------------------------------------------------------------------------------*/
DWORD Define_3(DWORD dwPtr){ 
	DWORD C; 
	if(IsBadReadPtr((PDWORD)(dwPtr),4)==0){ 
		C=(*(DWORD*)(dwPtr)); 
		if(IsBadReadPtr((PDWORD)(C),4)==0){ 
			return C; 
		} 
	} 
	return C;
}

/*-------------------------------------------------------------------------------------------------------------------*/
DWORD Define_4(DWORD dwPtr){ 
	DWORD C; 
	if(IsBadReadPtr((PDWORD)(dwPtr),4)==0){ 
		C=((DWORD)dwPtr); 
		if(IsBadReadPtr((PDWORD)(C),4)==0){ 
			return C; 
		} 
	} 
	return C;
}

/*-------------------------------------------------------------------------------------------------------------------*/
#define GetCamVPoss CALL_CAMPOS

DWORD GetCamVCPoss(D3DXVECTOR3* Vect, D3DXMATRIX* Mat, int iUnk)
{
	Base_CamPos = Define_2(BASE_AMMO2, PTR_CAMPOS);
	CallGetCamVPoss = Define_4(GetCamVPoss);
	if (!Base_CamPos)return 0;
	DWORD RunVCPoss;
	if(Base_CamPos)
	{
		RunVCPoss = ((DWORD (__thiscall *)(DWORD, D3DXVECTOR3*, D3DXMATRIX*, int))CallGetCamVPoss)(Base_CamPos, Vect, Mat, iUnk);
	}
return RunVCPoss;
}

/*-------------------------------------------------------------------------------------------------------------------*/
#define DoLineColl CALL_DOLINE 

DWORD DoLineCollis(UINT i)
{
	D3DXVECTOR3	vBone, vLocal;
	DWORD RunDoLine;
	int BoneIndexSelector;
	switch(opt.d3d.BoneTarget)
	{
	case 0:
		BoneIndexSelector = 7.0; // Head
		break;
	case 1:
		BoneIndexSelector = 5; // Body
		break;
	}
	DWORD Change;
	if ( opt.d3d.Switch == 0 ) {Change=0x1C;} // Primary
	if ( opt.d3d.Switch == 1 ) {Change=0x20;} // Pistol
	Base_DoLine   = Define_1(BASE_AMMO2, PTR_WEAPON , Change);
	CallDoLineColl = Define_4(DoLineColl);
	GetCamVCPoss(&vLocal,0,0);
	vBone = GetUserBonePos_Scd(i, BoneIndexSelector);
	if(Base_DoLine)
	{
		RunDoLine = ((DWORD (__thiscall *)(DWORD, D3DXVECTOR3*, D3DXVECTOR3*, int))CallDoLineColl)(Base_DoLine, &vLocal, &vBone, GetIdxTeam(i));
	}
	return RunDoLine;
}

DWORD DoLineCollis_Scd(UINT i)
{
	D3DXVECTOR3	vBone, vLocal;
	DWORD RunDoLine;
	int BoneIndexSelector;
	switch(opt.d3d.BoneTarget)
	{
	case 0:
		BoneIndexSelector = 7.7; // Head
		break;
	case 1:
		BoneIndexSelector = 5; // Body
		break;
	}
	Base_DoLine   = Define_1(BASE_AMMO2, PTR_WEAPON , 0x2C);
	CallDoLineColl = Define_4(DoLineColl);
	GetCamVCPoss(&vLocal,0,0);
	vBone = GetUserBonePos_Scd(i, BoneIndexSelector);
	if(Base_DoLine)
	{
		RunDoLine = ((DWORD (__thiscall *)(DWORD, D3DXVECTOR3*, D3DXVECTOR3*, int))CallDoLineColl)(Base_DoLine, &vLocal, &vBone, GetIdxTeam(i));
	}
	return RunDoLine;
}

/*-------------------------------------------------------------------------------------------------------------------*/
#define GameEventHit CALL_HITEVENT

DWORD WriteGameEvent(UINT i)
{
	D3DXVECTOR3	vEnemy;
	DWORD RunHitEvent;
	DWORD Change;
	if ( opt.d3d.Switch == 0 ) {Change=0x1C;} // Primary
	if ( opt.d3d.Switch == 1 ) {Change=0x20;} // Pistol
	Base_HitEvent   = Define_1(BASE_AMMO2, PTR_WEAPON, Change);
	Base_HitEventt   = Define_3(BASE_AMMO2);
	CallHitEvent = Define_4(GameEventHit);
    GetCamVCPoss(&vEnemy,0,0);
    if(Base_HitEvent)
	{
		RunHitEvent = ((DWORD (__thiscall *)(DWORD, DWORD, D3DXVECTOR3*, DWORD))CallHitEvent)(Base_HitEvent, Base_HitEventt, &vEnemy, Base_HitEvent);// ikine bedo, podo ae
	}
	return RunHitEvent;
}

DWORD WriteGameEvent_Scd(UINT i)
{
	D3DXVECTOR3	vEnemy;
	DWORD RunHitEvent;
	Base_HitEvent   = Define_1(BASE_AMMO2, PTR_WEAPON, 0x2C);
	Base_HitEventt   = Define_3(BASE_AMMO2);
	CallHitEvent = Define_4(GameEventHit);
    GetCamVCPoss(&vEnemy,0,0);
    if(Base_HitEvent)
	{
		RunHitEvent = ((DWORD (__thiscall *)(DWORD, DWORD, D3DXVECTOR3*, DWORD))CallHitEvent)(Base_HitEvent, Base_HitEventt, &vEnemy, Base_HitEvent);// ikine bedo, podo ae
	}
	return RunHitEvent;
}

/*-------------------------------------------------------------------------------------------------------------------*/

bool AutoOn=false;
void CallLineHit() {
if(opt.d3d.KillerKey==1){
if(opt.d3d.Killer==1){
	for(int i=0; i<=16; i++)
	{
			int MySlot = GetIdxTeam(GetMyCharaIndexed(i)); 
				if(GetIdxTeam(i) == MySlot) continue;
				if(IsAlive(i)){
				//	if ( VisibleTarget(i) ) {
					DoLineCollis(i);
					DoLineCollis(i);
					DoLineCollis(i);
					DoLineCollis(i);
					DoLineCollis(i);
					AutoOn=true;
					if(AutoOn==true){
						WriteGameEvent(i);
					}
				}
			}
	}
}

	if(opt.d3d.KillerKey==1){
		if(IsKeyPressedF(VK_RBUTTON,0))
		{
	opt.d3d.Killer=1;}
		else{
			opt.d3d.Killer=0;
			AutoOn=false;}
	}
}

void CallLineHit_Scd() {
if(opt.d3d.ScdKillerKey==1){
if(opt.d3d.ScdKiller==1){
	for(int i=0; i<=16; i++)
	{
			int MySlot = GetIdxTeam(GetMyCharaIndexed(i)); 
				if(GetIdxTeam(i) == MySlot) continue;
				if(IsAlive(i)){
				//	if ( VisibleTarget(i) ) {
					DoLineCollis_Scd(i);
					DoLineCollis_Scd(i);
					DoLineCollis_Scd(i);
					DoLineCollis_Scd(i);
					AutoOn=true;
					if(AutoOn==true){
						WriteGameEvent_Scd(i);
					}
				}
			}
	}
}

	if(opt.d3d.ScdKillerKey==1){
		if(GetBattleState())
		{
	opt.d3d.ScdKiller=1;}
		else{
			opt.d3d.ScdKiller=0;
			AutoOn=false;}
	}
}
/*-------------------------------------------------------------------------------------------------------------------*/