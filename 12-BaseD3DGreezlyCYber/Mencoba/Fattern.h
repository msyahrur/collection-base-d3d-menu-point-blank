/*++

Copyright (c) Main Cit 96 Corporation.  All rights reserved.

Module Name:

 cFindFattern.h

Abstract:

    Type definitions for the basic sized types.

Author:

Revision History:

--*/

void hkEndRender();
//-------------------------------------------------------------------------------------------------//
DWORD	Resultg_pFramework,
		Resultg_pPlayer,
		Resultg_pCharaManager,
		Resultg_pCameraManager,
		Resultg_pBaseManager,
		Resultg_pWeaponEdit,
		Resultg_pGameContext,
		Resultg_pGameStatus,
		Resultg_pGameChatBox,
		ResultCGameUDPHandler,
		ResultCGetChatBox;

DWORD	ResultCallg_pFramework,
		ResultCallg_pGameContext,
		ResultCallg_pCharaManager,
		//ResultCallg_pCameraManager,
		ResultCallg_pPlayer;

DWORD	ResultFramework,
		ResultGameContext,
		ResultpPlayer,
		ResultpCharaManager,
		ResultpCameraManager;

DWORD	ResultPTRTeam,
		ResultPTRm_idxBone,
		ResultPTRm_Bone,
		ResultPTRm_pWeaponContext,
		ResultPTRm_pBoneContext,
		ResultPTRm_pCollisionContext,
		ResultPTRNickOnTarget,
		ResultPTRVectorBone,
		ResultPTRDefaultVariable,
		ResultPTRgetSlotWeapon;

DWORD	ResultCallm_idxBone,
		ResultCallm_Bone,
		ResultAbuse1,
		ResultAbuse2,
		ResultAbuse3,
		ResultCallm_pBoneContext,
		ResultCallNickOnTarget,
		ResultCallm_pCollisionContext,
		ResultCallm_pCameraContext,
		ResultCallm_pWeaponContext,
		ResultCallm_pAnimContext,
		ResultGetCharaByNetIdx,
		ResultgetCharaNetIndex,
		ResultGetCurrent,
		ResultGetMaxBulletWithCashItem,
		ResultCallgetSlotWeapon;

DWORD	PTRFastShot;
DWORD	ResultPTRAbuse1,
		ResultPTRAbuse2,
		ResultPTRAbuse3;


DWORD	ResultWriteGameEvent_Fire,Result__CreateRoomMasterKick,ResultgetVirtualCamPosition,ResultDoLineCollision,ResultSetCharaWeaponSet,ResultSetCharaWeapon,ResultSetKiller,ResultRespawnChara;
DWORD	ResultpEnd,ResultRETpEnd,ResultBullet,ResultDeltaX,ResultDeltaY,ResultDeltaZ,ResultGetButton,ResultSuicide,ResultSetEvent,ResultSetEventOnce;

DWORD	ResultBugWeapon,ResultWallShot,ResultWallShot2,ResultInvicible,ResultNoRecoil,ResultNoRecoil2,ResultQuickChange,ResultRETQuickChange,ResultAimDatar,ResultNoReload,ResultRETNoReload,ResultCharaManager,ResultCMD_Instal,ResultCall_Uninstal,ResultBaseStage,
		ResultUpdateNickOnTarget,ResultRETUpdateNickOnTarget,
		WTF,WTW,LX,LX2,ResultEndRenderPTR,ResultAccuracy,ResultDamage,ResultRETDamage,ResultFireSpeed,ResultRETFireSpeed,ResultRETFastPlant,ResultLongWeapon,ResultRETLongWeapon;
DWORD	ResultMsgBox,ResultSetAnnounceMessage,Result_PutStringBackUpBuffer,ResultCallRaycastClosest,ResultSetNightVisionEnable;
DWORD	BypassI3Error,GetPos,BypassSniper1,BypassSniper2,BypassShotgun1,BypassShotgun2,BypassBarefist1,BypassBarefist2,BypassDuplicate,BypassWord1,BypassWord2,BypassNickName1,BypassNickName2,BypassNickName3,BypassNickName4,BypassNickName5,BypassNickName6,BypassNickName7;
DWORD	ResultPTRGetWorldMatrix,ResultPTRGetViewMatrix,ResultPTRGetProjectMatrix,ResultD3D9Hook;
DWORD	ResultEndRender,ResultViewer;
DWORD	Result_OnHitCharaByExplosion,Result_OnCheckCollisionByExplosion,ResultNET_Fire,ResultReset,ResultGetOneVert,ResultGetOneHorz,ResultGetRecoilHorz,ResultGetRecoilVert;
DWORD	ResultImport_i3RenderContext_EndRender,ResultImport_i3AiContext_getLocalTime;
//----------------------------------------------------------------------------------

DWORD dwStartAddress;
DWORD dwi3GfxD;
DWORD dwNxChara;

DWORD dwBaseDx_Cli;
DWORD dwSize;
DWORD i3GfxD;
DWORD NxChara;
DWORD BaseDx_CliSize;
DWORD dwi3FrameworkDx;
DWORD i3FrameworkDxSize;
DWORD ResultTeam,ResultName,ResultDeath,ResultInfoChara,ResultNetChara,ResultGetUserInfoInvite,ResultgetCurHP,ResultgetCurHP_Real,ResultgetUdpHoleState,ResultGetChannelUserCount,ResultGetEnteredServerX,ResultGetEnteredServerJMP,ResultgetIndividualScore,ResultGetPing;
DWORD ResultPTRFireEndAnim,ResultPTRFastShot,ResultPTRFastShot1,ResultPTRAutoLauncher,ResultPTRAmmoA,ResultPTRAmmoB,ResultPTRAmmoC,ResultPTRProtectA,ResultPTRProtectB,ResultPTRProtectC,ResultPTRProtectD,ResultPTRProtectNew1,ResultPTRProtectNew2;
		
		DWORD ResultTime3M,ResultTime3Min,ResultReplaceAllMode;
DWORD ModuleD3D9,ModuleD3D9Size;
HMODULE ModuleNX;
HMODULE ModuleFW;
HMODULE ModuleGF;
HMODULE ModuleIP;
HMODULE ModuleSC;
HMODULE ModuleBC;

DWORD LogShowNickPlayers,LogGaugeMultiplier,LogAntiKickOut;
bool Exit;
//void ShowLogger(char* Name)
//{
//	if(Exit==false){
//		LPCSTR lpOperation	= "open";
//		LPCSTR lpFile		= "Notepad.exe";
//		LPCSTR lpDirectory	= GetDirectoryFile(Name);
//		INT nShowCmd		= SW_SHOWNORMAL;
//		ShellExecuteA(NULL,lpOperation,lpFile,lpDirectory,NULL,nShowCmd);
//		ExitProcess(NULL);
//	}
//	else if(Exit==true);
//}

DWORD PUSH_STR_PB(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask,char * szMask,int Offsete)
{	
	if(FindPattern(dwdwAdd,dwLen,bMask,szMask) != NULL)
	{
		DWORD ADR = FindPattern(dwdwAdd,dwLen,bMask,szMask);
		if(FindPattern((DWORD)dwdwAdd						,(DWORD)dwLen		,ADR))
		{
			DWORD PUSH = FindPattern((DWORD)dwdwAdd						,(DWORD)dwLen		,ADR)-1;
			if(PUSH!=NULL)
			{
				if((DWORD)(PUSH + Offsete))
				{
					return (DWORD)(PUSH + Offsete);
				}else return 0;
			}else return 0;
		}else return 0;
	}else return 0;
return 0;
}

DWORD FindString(char *module, char *pattern, char *mask,int Offsete)
{	
	if(FindAddresModule(module,pattern,mask) != NULL)
	{
		DWORD ADR = FindAddresModule(module,pattern,mask);
		if(FindAddres(module,ADR))
		{
			DWORD PUSH = FindAddres(module,ADR)-1;
			if(PUSH!=NULL)
			{	
				if((DWORD)(PUSH + Offsete))
				{
					return (DWORD)(PUSH + Offsete);
				}else return 0;
			}else return 0;
		}else return 0;
	}else return 0;
return 0;
}

DWORD WritePointerOffset(DWORD dwPtr)
{
	__try{
		DWORD C; 
		if(IsBadReadPtr((PDWORD)(dwPtr),4)==0){
			C=((DWORD)dwPtr); 
			if(IsBadReadPtr((PDWORD)(C),4)==0){
				return C; }
			else 
				return 0;}
		else 
			return 0;
	}__except ( EXCEPTION_EXECUTE_HANDLER ) {
		return 0;
	}
}

void MC96Updater()
{
Sleep(500);
do{
/*------------------------------------------- Declaration hModule ------------------------------------------------------*/
dwStartAddress	= (DWORD)GetModuleHandleA("PointBlank.exe");
dwSize			= GetSizeofCode("PointBlank.exe");

dwi3GfxD			= (DWORD)GetModuleHandleA("i3GfxDx.dll");
i3GfxD			= GetSizeofCode("i3GfxDx.dll");

dwNxChara			= (DWORD)GetModuleHandleA("NxCharacter.2.8.1.dll");
NxChara			= GetSizeofCode("NxCharacter.2.8.1.dll");

dwBaseDx_Cli		= (DWORD)GetModuleHandle("i3BaseDx_Cli.dll");
BaseDx_CliSize		= GetSizeofCode("i3BaseDx_Cli.dll");

dwi3FrameworkDx = (DWORD)GetModuleHandle("i3FrameworkDx.dll");
i3FrameworkDxSize		= GetSizeofCode("i3FrameworkDx.dll");

ModuleNX		= (HMODULE)LoadLibrary	 ("NxCharacter.2.8.1.dll");
ModuleFW		= (HMODULE)LoadLibrary	 ("i3FrameworkDx.dll");
ModuleGF		= (HMODULE)LoadLibrary	 ("i3GfxDx.dll");
ModuleIP		= (HMODULE)LoadLibrary	 ("i3inputdx.dll");
ModuleSC		= (HMODULE)LoadLibrary	 ("i3SceneDx.dll");
ModuleBC		= (HMODULE)LoadLibrary	 ("i3BaseDx_Cli.dll");
Sleep(500);
}while
(!dwStartAddress);
(!dwSize);

(!dwi3GfxD);
(!i3GfxD);

(!dwNxChara);
(!NxChara);

(!dwBaseDx_Cli);
(!BaseDx_CliSize);

(!dwi3FrameworkDx);
(!i3FrameworkDxSize);

(!ModuleNX);
(!ModuleFW);
(!ModuleGF);
(!ModuleIP);
(!ModuleSC);
(!ModuleBC);

DWORD GetButtonState	= (DWORD)GetProcAddress(ModuleIP, "?GetButtonState@i3InputMouse@@QAEIXZ");
DWORD SetEnd			= (DWORD)GetProcAddress(ModuleSC, "?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z");
DWORD GetDeltaX			= (DWORD)GetProcAddress(ModuleIP, "?GetDeltaX@i3InputMouse@@QAEMXZ");
DWORD GetDeltaY			= (DWORD)GetProcAddress(ModuleIP, "?GetDeltaY@i3InputMouse@@QAEMXZ");

DWORD EndRender				= (DWORD)GetProcAddress(ModuleGF, "?EndRender@i3RenderContext@@QAEXXZ");
DWORD i3GetViewMatrix		= (DWORD)GetProcAddress(ModuleGF, "?GetViewMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ");
DWORD i3GetProjectMatrix	= (DWORD)GetProcAddress(ModuleGF, "?GetProjectMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ");
DWORD i3GetWorldMatrix		= (DWORD)GetProcAddress(ModuleGF, "?GetWorldMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ");
//DWORD i3GetPos				= (DWORD)GetProcAddress(ModuleFW, "?GetPos@i3GameObj@@QAEPATVEC3D@@XZ");

DWORD dwSetStart			= (DWORD)GetProcAddress(ModuleSC, "?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z");
DWORD dwSetEnd				= (DWORD)GetProcAddress(ModuleSC, "?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z");
DWORD dwpEnd				= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"pEnd != NULL","xxxxxxxxxxxx",0x25); //

DWORD dwInitialize			= (DWORD)GetProcAddress(ModuleSC, "??0i3CollideeLine@@QAE@XZ");
DWORD dwRaycastClosest		= (DWORD)GetProcAddress(ModuleSC, "?RaycastClosest@i3PhysixContext@@QAEPAU_tagi3PhysixHitResult@@PAVi3CollideeLine@@HI@Z");
DWORD dwViewer				= (DWORD)GetProcAddress(ModuleFW, "?g_pMainViewer@@3PAVi3Viewer@@A");
DWORD dwi3Error				= (DWORD)GetProcAddress(ModuleBC, "?Log@i3Error@@YAXABV?$literal_base_range@PBD@i3@@@Z");
DWORD JumpBypassAllMode			= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall CGameCharaManager::SetCharaWeaponSet(class CGameCharaBase *,struct _NetCharaInfo *)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0x200-0xF);
DWORD JumpBypassDuplicatedChat	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"STR_TBL_CHAT_INGAME_NOTICE_WARNING_DUPLICATED_WORD","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",-0x9);
DWORD JumpBypassNickName		= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"NickName Contained Blank","xxxxxxxxxxxxxxxxxxxxxxxx",-0x2);

DWORD dwCallFramework		= FindPattern(dwStartAddress, dwSize, (PBYTE)"\x51\x6A\x00\x6A\x04\x8D\x44\x24\x08\x50\xE8\x00\x00\x00\x00\x8B\x04\x24\x59\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x51\x6A\x00\x6A\x04\x8D\x44\x24\x08\x50\xE8\x00\x00\x00\x00\x8B\x04\x24\x59\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x51\x6A\x00\x6A\x04\x8D\x44\x24\x08\x50\xE8\x00\x00\x00\x00\x8B\x04\x24\x59\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x51\x6A\x00\x6A\x04\x8D\x44\x24\x08\x50\xE8\x00\x00\x00\x00\x8B\x04\x24\x59\xC3","xxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxx");
DWORD dwFramework			= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"g_pFramework != NULL","xxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwGameContext			= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"g_pGameContext != NULL","xxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwpPlayer			= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"g_pPlayer != NULL","xxxxxxxxxxxxxxxxx",NULL);
//DWORD dwpCharaManager			= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"g_pCharaManager != NULL","xxxxxxxxxxxxxxxxxxxxxxx",0x2877A7);
DWORD dwpCharaManager		= FindPattern(dwStartAddress, dwSize, (PBYTE)"\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x08\x6A\x00\xB9\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8B\xC8\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x50","x????x????x????xxxxxx????x????xxx????x????x");
DWORD dwpCameraManager			= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"g_pCameraManager != NULL","xxxxxxxxxxxxxxxxxxxxxxxx",NULL);

DWORD dwCGameUDPHandler     = PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall GAMEINFO_SUICIDEDAMAGE::CopyTo(struct GAMEINFO_SUICIDEDAMAGE *)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwCGetChatBox     = PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"class CGameCharaBase *__thiscall CGameCharaManager::getCharaByNetIdx(int)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);

DWORD setMySlotIdx			= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"void __thiscall CGameContext::setMySlotIdx(int)", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD setMySlotIdxPointer	= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"void __thiscall CGameContext::setMySlotIdx(int)", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD getGameInfo_Chara		= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"struct GAMEINFO_CHARACTER *__thiscall CGameContext::getGameInfo_Chara(int)", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD getNetCharaInfo		= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"struct _NetCharaInfo *__thiscall CGameContext::getNetCharaInfo(int)", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0xACB2E);
DWORD GetUserInfoInvite		= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"const struct _UserInfoInvite *__thiscall CGameContext::GetUserInfoInvite(unsigned int) const", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);

DWORD getUserDeath			= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"bool __thiscall CGameContext::getUserDeath(int)", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD getNickForSlot		= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"const char *__thiscall CGameContext::getNickForSlot(int)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);

DWORD getCurHP				= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"int __thiscall CGameCharaBase::getCurHP(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD getCurHP_Real			= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"float __thiscall CGameCharaBase::getCurHP_Real(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD getUdpHoleState		= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"const enum UDP_STATE __thiscall CGameContext::getUdpHoleState(int) const","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD GetChannelUserCount	= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"int __thiscall CGameContext::GetChannelUserCount(int)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD GetEnteredServer		= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"int __thiscall CGameContext::GetEnteredServer(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD getIndividualScore	= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"struct __ScoreInfo *__thiscall CGameContext::getIndividualScore","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD GetPing				= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"unsigned char __thiscall CGameContext::GetPing(int)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);

DWORD dw_OnHitCharaByExplosion	= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"void __thiscall WeaponBase::_OnHitCharaByExplosion(class CGameCharaBase *,enum CHARA_HIT_PART,union VEC3D *,union VEC3D *)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwReset		= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall WeaponBase::Reset(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);

DWORD GetMaxBulletWithCashItem	= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"int __thiscall WeaponBase::GetMaxBulletWithCashItem(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD GetOneVert		= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"int __thiscall WeaponBase::GetOneVertEnable(class CWeaponInfo *,bool)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0x60);
DWORD GetOneHorz		= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"int __thiscall WeaponBase::GetOneHorzEnable(class CWeaponInfo *,bool)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0x60);
DWORD GetRecoilHorz	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"int __thiscall WeaponBase::GetRecoilHorzCount(class CWeaponInfo *,bool)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0x7B);
DWORD GetRecoilVert	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"int __thiscall WeaponBase::GetRecoilVertCount(class CWeaponInfo *,bool)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0x60);

DWORD dwCMD_Instal			= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"bool __thiscall CGameCharaBase::Cmd_Install(bool)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwgetCharaByNetIdx	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"class CGameCharaBase *__thiscall CGameCharaManager::getCharaByNetIdx(int)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL); 
DWORD dwgetCharaNetIndex	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"int __thiscall CGameCharaBase::getCharaNetIndex(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL); 
DWORD dwgetCurrent			= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"class WeaponBase *__thiscall CGameCharaWeaponContext::getCurrent(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
//----------------------------------------------------------------------------------------------------------------------------------//
DWORD dwSetEvent		= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"int __thiscall CGameContext::SetEvent(int,const void *,const void *,const void *,const char *,int)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwSetEventOnce		= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"int __thiscall CGameContext::SetEventOnce(int,const void *,const void *,const void *)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);

DWORD dwWriteGameEvent_Fire     = PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall CGameUDPHandler::WriteGameEvent_Fire(class CGameCharaBase *,union VEC3D *,class WeaponBase *)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dw__CreateRoomMasterKick     = PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall UIPhaseReadyRoom::__CreateRoomMasterKick(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwDoLineCollision	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall WeaponBase::DoLineCollision(union VEC3D *,union VEC3D *,int)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);

DWORD dw_OnCheckCollisionByExplosion	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall WeaponBase::_OnCheckCollisionByExplosion(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwNET_Fire	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall WeaponBase::NET_Fire(union VEC3D *,union VEC3D *,enum WEAPON_FIRE_ORDER)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);

DWORD dwSetCharaWeaponSet	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall CGameCharaManager::SetCharaWeaponSet(class CGameCharaBase *,struct _NetCharaInfo *)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwSetCharaWeapon	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"bool __thiscall CGameCharaBase::Cmd_Attack(enum WEAPON_FIRE_ORDER,union VEC3D *,union VEC3D *,bool,int)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);

DWORD dwSetCharaWeaponNEW	= FindString("PointBlank.exe",(PCHAR)"bool __thiscall CGameCharaBase::Cmd_Attack(enum WEAPON_FIRE_ORDER,union VEC3D *,union VEC3D *,bool,int)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);


DWORD dwgetVirtualCamPosition	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall CGameCharaCameraContext::getVirtualCamPosition(union VEC3D *,union _tagi3Matrix *,int)", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwRespawnChara	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall CGameCharaManager::RespawnChara(int,bool)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
//----------------------------------------------------------------------------------------------------------------------------------//
DWORD dwMsgBox			= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"[LEAVE] GotoNextStage( %s )","xxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwSetAnnounceMessage	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall CGameFramework::SetAnnounceMessage(const char *)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwCallRaycastClosest	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall CGameFramework::SetAnnounceMessage(const char *)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dw_PutStringBackUpBuffer	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall CGameChatBox::_PutStringBackUpBuffer(const char *)", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwSetNightVisionEnable	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall CGameFramework::SetNightVisionEnable(int)", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
//----------------------------------------------------------------------------------------------------------------------------------//
DWORD dwPTRgetSlotWeapon	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"class WeaponBase *__thiscall CGameCharaWeaponContext::getCurrent(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",-0x12);
DWORD dwgetSlotWeapon	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"STR_HACKER_MSG","xxxxxxxxxxxxxx",NULL); 

DWORD dwPTRm_pWeaponContext		= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"m_pWeaponContext != NULL","xxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwCallm_pWeaponContext	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"class CGameCharaBase *__thiscall CGameCharaManager::getCharaByNetIdx(int)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwCallm_pAnimContext	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"struct __SlotInfo *__thiscall CGameContext::getSlotInfo(int)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);

DWORD dwPTRVectorBone			= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"SpecialWarHeadHunterEmpty","xxxxxxxxxxxxxxxxxxxxxxxxx",-0x6); 
//DWORD dwPTRDefaultVariable		= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"lbSpecialWarButtonChallengeDescription","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0x11); 
DWORD dwPTRDefaultVariable = FindPattern(dwStartAddress, dwSize,(PBYTE)"\x68\x00\x00\x00\x00\x8B\x4D\x08\x51\xE8\x00\x00\x00\x00\x83\xC4\x10\x68\x00\x00\x00\x00\x8B\x95\x00\x00\x00\x00\x81\xC2\x00\x00\x00\x00\x52\x68\x00\x00\x00\x00\x8B\x45\x08\x50","x????xxxxx????xxxx????xx????xx????xx????xxxx");

DWORD dwPTRm_Bone				= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"m_Bone == NULL","xxxxxxxxxxxxxx",NULL); 
DWORD dwCallm_Bone				= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"int __thiscall CGameCharaBase::getCurHPAppliedCashItem(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL); 
DWORD dwPTRm_pBoneContext		= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"m_pBoneContext != NULL","xxxxxxxxxxxxxxxxxxxxxx",NULL); 
DWORD dwCallm_pBoneContext		= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall CGameContext::setMySlotIdx(int)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);

DWORD dwCallm_pCameraContext	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"bool __thiscall CGameCharaBase::isNetwork(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwPTRUpdateNickOnTarget	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"int __thiscall CGameCharaCollisionContext::UpdateNickOnTarget(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0x45);
DWORD dwCallUpdateNickOnTarget	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"int __thiscall CGameCharaCollisionContext::UpdateNickOnTarget(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0x30A);
DWORD dwPTRm_pCollisionContext	= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"m_pCollisionContext != NULL","xxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL); 
DWORD dwCallm_pCollisionContext	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"int __thiscall CGameContext::IsUseFuncItemSlot(int,unsigned int)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
	
DWORD TimeHack3O2 = FindPattern(dwStartAddress, dwSize,(PBYTE)"\x05\x00\x00\x00\x00\x8B\xE5\x5D\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x83\xEC\x14","x????xxxxxxxxxxxxxxxxxxxxxxx");
DWORD dwPTRFastShot	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"m_pWeaponInfo °","xxxxxxxxxxxxxxx",0x9);
DWORD dwPTRAutoLauncher	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall WeaponBase::setAIIndex(enum WEAPON_AI_INDEX,signed char)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0x69);
//----------------------------------------------------------------------------------------------------------------------------------//
DWORD BaseSuicide		= FindPattern(dwStartAddress,dwSize,(PBYTE)"\x55\x8B\xEC\x83\xEC\x74\x89\x4D\xAC","xxxxxxxxx");
DWORD SetKiller			= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall WeaponShotGun3::PlayAnim_UI_IdleB(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwBaseStage		= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"int __thiscall CGameCharaBase::getCharaNetIndex(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwCall_Uninstal	= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall CGameMissionManager::Uninstall(int,int)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
//----------------------------------------------------------------------------------------------------------------------------------//
DWORD dwLongWeapon		= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"float __thiscall WeaponBase::GetDamage(bool)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwQuickChange		= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall WeaponShotGun3::OnLoadMag_Ready(class i3AIContext *,float)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwNoReload		= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall WeaponBase::NET_Fire(union VEC3D *,union VEC3D *,enum WEAPON_FIRE_ORDER)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwWallShot		= PUSH_STR_PB(dwStartAddress,dwSize,(PBYTE)"void __thiscall WeaponBase::ReturnToReady(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
DWORD dwDamage			= FindPattern(dwStartAddress,dwSize,(PBYTE)"\xD9\x45\xF0\x5E\x8B\xE5\x5D\xC2\x04","xxxxxxxxx");
DWORD gi3AmmoStatus		= FindPattern(dwStartAddress,dwSize	,(PBYTE)"\x52\xE8\x00\x00\x00\x00\x83\xC4\x08\x8B\x45\xFC\x8B\x4D\x08\x89\x88\x00\x00\x00\x00\x8B\xE5\x5D\xC2\x04\x00\x55\x8B\xEC\x51\x89\x4D","xx????xxxxxxxxxxx??xxxxxxxxxxxxxx");
DWORD i3AmmoStatus1		= FindPattern(gi3AmmoStatus+1,dwSize,(PBYTE)"\x52\xE8\x00\x00\x00\x00\x83\xC4\x08\x8B\x45\xFC\x8B\x4D\x08\x89\x88\x00\x00\x00\x00\x8B\xE5\x5D\xC2\x04\x00\x55\x8B\xEC\x51\x89\x4D","xx????xxxxxxxxxxx??xxxxxxxxxxxxxx");
DWORD i3AmmoStatus2		= FindPattern(i3AmmoStatus1+1,dwSize,(PBYTE)"\x52\xE8\x00\x00\x00\x00\x83\xC4\x08\x8B\x45\xFC\x8B\x4D\x08\x89\x88\x00\x00\x00\x00\x8B\xE5\x5D\xC2\x04\x00\x55\x8B\xEC\x51\x89\x4D","xx????xxxxxxxxxxx??xxxxxxxxxxxxxx");

DWORD dwUnyuk			= FindPattern(dwStartAddress,dwSize*2,(PBYTE)"¾CGameCharaCollisionContext","xxxxxxxxxxxxxxxxxxxxxxxxxxx");
DWORD dwInvicible		= FindPattern(dwStartAddress,dwSize*2,(PBYTE)"((m_currentPhase) >= 0) && ((m_currentPhase) < (UIPHASE_MAX))","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
DWORD dwWTF				= FindPattern(dwNxChara,NxChara,(PBYTE)"\x5E\x00\xD9\x46\x00\xD9\x44\x24\x00\xD9\xC0\xDE\xC2\xD9\xC9\xD9\x5E\x00\xD9\x46\x00\xD8\xC3\xD9\x5E\x00\xD9\x46\x00\xD8\xC2\xD9\x5E\x00\xD9\x46\x00","x?xx?xxx?xxxxxxxx?xx?xxxx?xx?xxxx?xx?");

DWORD Import_i3RenderContext_EndRender	= FindPattern(dwi3FrameworkDx,i3FrameworkDxSize,(PBYTE)"\x8B\x4E\x24\xFF\x15\x00\x00\x00\x00\x8B\x4E\x18\xFF\x15\x00\x00\x00\x00\x85\xC0","xxxxx????xxxxx????xx");
DWORD Import_i3AiContext_getLocalTime	= FindPattern(dwStartAddress,dwSize	,(PBYTE)"\x8B\x4D\x08\xFF\x15\x00\x00\x00\x00\x8B\x45\xFC\x50\x8B\x4D\xF0","xxxxx????xxxxxxx");

		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwFramework+0x13), &ResultFramework     , sizeof(ResultFramework)     , NULL);
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwGameContext+0x13), &ResultGameContext     , sizeof(ResultGameContext)     , NULL);
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwpPlayer+0x19), &ResultpPlayer     , sizeof(ResultpPlayer)     , NULL);
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwpCharaManager+0x15), &ResultpCharaManager     , sizeof(ResultpCharaManager)     , NULL);
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwpCameraManager-0x24), &ResultpCameraManager     , sizeof(ResultpCameraManager)     , NULL);
	
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (setMySlotIdxPointer+0x2F)  , &ResultPTRTeam	 , sizeof(ResultPTRTeam)     , NULL);		
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPTRm_pWeaponContext-0x24), &ResultPTRm_pWeaponContext     , sizeof(ResultPTRm_pWeaponContext)     , NULL);
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPTRm_pBoneContext-0x24), &ResultPTRm_pBoneContext     , sizeof(ResultPTRm_pBoneContext)     , NULL);	
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPTRm_pCollisionContext-0x24), &ResultPTRm_pCollisionContext     , sizeof(ResultPTRm_pCollisionContext)     , NULL);
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPTRm_Bone-0x21), &ResultPTRm_Bone     , sizeof(ResultPTRm_Bone)     , NULL);	
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPTRUpdateNickOnTarget+0x2), &ResultPTRNickOnTarget     , sizeof(ResultPTRNickOnTarget)     , NULL);	
		
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPTRVectorBone+0x1), &ResultPTRVectorBone     , sizeof(ResultPTRVectorBone)     , NULL);
		//ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPTRDefaultVariable+0x1), &ResultPTRDefaultVariable     , sizeof(ResultPTRDefaultVariable)     , NULL);	
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPTRgetSlotWeapon+0x2), &ResultPTRgetSlotWeapon    , sizeof(ResultPTRgetSlotWeapon)     , NULL);	
				
		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (TimeHack3O2+0x1), &ResultTime3M, sizeof(ResultTime3M), NULL) ;
		ReadProcessMemory(GetCurrentProcess(),(LPCVOID)(dwPTRFastShot+0xC)		,&PTRFastShot			,sizeof(PTRFastShot)					,NULL);
		ReadProcessMemory(GetCurrentProcess(),(LPCVOID)(dwPTRAutoLauncher+0x2)		,&ResultPTRAutoLauncher			,sizeof(ResultPTRAutoLauncher)					,NULL);

		ReadProcessMemory(GetCurrentProcess(),(LPCVOID)(i3AmmoStatus1+0x11)		,&ResultPTRAmmoA			,sizeof(ResultPTRAmmoA)					,NULL);
		ReadProcessMemory(GetCurrentProcess(),(LPCVOID)(i3AmmoStatus2		+0x11)		,&ResultPTRAmmoB			,sizeof(ResultPTRAmmoB)					,NULL);	

		ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwpEnd+0x2), &ResultpEnd     , sizeof(ResultpEnd)     , NULL);		
		ReadProcessMemory(GetCurrentProcess(),(LPCVOID) (EndRender+0x2), &ResultEndRender, sizeof(ResultEndRender), NULL);

		ReadProcessMemory(GetCurrentProcess(),(LPCVOID) (Import_i3RenderContext_EndRender+0x5), &ResultImport_i3RenderContext_EndRender, sizeof(ResultImport_i3RenderContext_EndRender), NULL);
		ReadProcessMemory(GetCurrentProcess(),(LPCVOID) (Import_i3AiContext_getLocalTime+0x5), &ResultImport_i3AiContext_getLocalTime, sizeof(ResultImport_i3AiContext_getLocalTime), NULL);

		Resultg_pFramework 			= ResultFramework;
		Resultg_pGameContext 			= ResultGameContext;
		Resultg_pCharaManager 		= ResultpCharaManager;
		Resultg_pPlayer				= ResultpPlayer;
			
		ResultCallg_pFramework 		= dwCallFramework;
		ResultCallg_pGameContext 	= dwCallFramework+0x20;
		ResultCallg_pCharaManager 	= dwCallFramework+0x20+0x20;
		ResultCallg_pPlayer			= dwCallFramework+0x20+0x20+0x20;

		Resultg_pCameraManager 		= ResultpCameraManager;	
		//Resultg_pBaseManager 		= ResultFramework + 0x14;
		Resultg_pGameStatus 		= ResultFramework + 0x3B0+0x100;
		Resultg_pGameChatBox 		= ResultFramework + 0x1C8;
		ResultCGameUDPHandler 		= dwCGameUDPHandler + 0x35C;	
		ResultCGetChatBox 			= dwCGetChatBox - 0x75;
		////===============================================================================//
		ResultWriteGameEvent_Fire		= dwWriteGameEvent_Fire - 0x12;
		Result__CreateRoomMasterKick = dw__CreateRoomMasterKick - 0x23E;
		ResultgetVirtualCamPosition		= dwgetVirtualCamPosition - 0x2A;
		ResultDoLineCollision	= dwDoLineCollision - 0x15;
		ResultSetCharaWeaponSet	= dwSetCharaWeaponSet - 0x17;
		ResultSetCharaWeapon	= dwSetCharaWeaponNEW + 0x421;
		ResultRespawnChara		= dwRespawnChara-0x26;
		ResultSetEvent			= dwSetEvent - 0x1D0;
		ResultSetEventOnce		= dwSetEventOnce - 0xE4;

		ResultSuicide			= BaseSuicide;
		ResultSetKiller			= SetKiller+0xA6;/*Kaybo 0x8B*/ /*Indo 0x98*/
		ResultBullet			= SetEnd;
		ResultDeltaX			= GetDeltaX;
		ResultDeltaY			= GetDeltaY;
		ResultpEnd				= dwpEnd;
		ResultRETpEnd			= dwpEnd+0x7;

		ResultTeam = setMySlotIdx+0x6B;
		ResultName = getNickForSlot-0x15;
		ResultDeath = getUserDeath-0x15;
		ResultInfoChara = getGameInfo_Chara-0x15;
		ResultNetChara = getNetCharaInfo-0x15;
		ResultGetUserInfoInvite = GetUserInfoInvite-0x15;
		//
		ResultgetCurHP		= getCurHP-0x1B;
		ResultgetCurHP_Real	= getCurHP_Real-0x1B;	
		ResultgetUdpHoleState	= getUdpHoleState-0x15;	
		ResultGetChannelUserCount	= GetChannelUserCount-0x15;	
		ResultGetEnteredServerX	= GetEnteredServer-0x42;	
		ResultGetEnteredServerJMP	= GetEnteredServer-0x3C;	
		ResultgetIndividualScore	= getIndividualScore-0x15;	
		ResultGetPing	= GetPing-0x15;	
		//
		ResultCallm_pAnimContext = dwCallm_pAnimContext-0xF5;
		ResultCallm_pWeaponContext		= dwCallm_pWeaponContext-0x35;
		ResultCallm_Bone		= dwCallm_Bone+0x423;
		ResultCallm_pBoneContext= dwCallm_pBoneContext-0x1D5;
		ResultCallNickOnTarget		= dwCallUpdateNickOnTarget+0x6A4; //0x684
		ResultCallm_pCollisionContext = dwCallm_pCollisionContext-0x220;
		ResultCallm_pCameraContext		= dwCallm_pCameraContext+0x55;
		ResultGetCharaByNetIdx	= dwgetCharaByNetIdx-0x15;	
		ResultgetCharaNetIndex = dwgetCharaNetIndex-0x1B;
		ResultGetCurrent	= dwgetCurrent-0x2E;	
		ResultCallgetSlotWeapon = dwgetSlotWeapon+0x85;	
		
		ResultGetMaxBulletWithCashItem	= GetMaxBulletWithCashItem-0x1D;	
		Result_OnHitCharaByExplosion	= dw_OnHitCharaByExplosion-0x5C;	

		ResultNET_Fire	= dwNET_Fire-0xA2;	
		ResultReset 	= dwReset-0x228;	

		ResultGetOneVert	= GetOneVert;	
		ResultGetOneHorz 	= GetOneHorz;	
		ResultGetRecoilHorz	= GetRecoilHorz;	
		ResultGetRecoilVert	= GetRecoilVert;	

		ResultBugWeapon			= dwUnyuk;
		ResultWallShot			= dwWallShot+0xA81;
		ResultInvicible		= dwInvicible-0xC; // 

		ResultCMD_Instal		= dwCMD_Instal-0x3B;
		ResultBaseStage			= dwBaseStage+0x1D5;
		ResultCall_Uninstal		= dwCall_Uninstal+0x1021;

		ResultPTRAbuse1							=ResultAbuse1;
		ResultPTRAbuse2							=ResultAbuse1+0x4;
		ResultPTRAbuse3							=ResultAbuse1+0x8;		
		
		ResultMsgBox		= dwMsgBox+0x1F;
		ResultSetAnnounceMessage	= dwSetAnnounceMessage - 0x11;
		ResultCallRaycastClosest	= dwCallRaycastClosest + 0x140;	
		Result_PutStringBackUpBuffer	= dw_PutStringBackUpBuffer - 0x18;
		ResultSetNightVisionEnable = dwSetNightVisionEnable - 0x15;

		ResultLongWeapon		= dwLongWeapon-0x7F;
		ResultRETLongWeapon		= ResultLongWeapon+0x5;

		ResultQuickChange		= dwQuickChange-0x6A;
		ResultRETQuickChange	= ResultQuickChange+0x5;

		ResultNoReload			= dwNoReload-0x1362;
		ResultRETNoReload		= ResultNoReload+0x6;

		ResultPTRFastShot							=PTRFastShot+0x4;
		ResultPTRFastShot1						    =ResultPTRFastShot+0x140;
		ResultPTRFireEndAnim						=ResultPTRFastShot+0xF4;

		ResultPTRAmmoC								=ResultPTRAmmoB-0x4;
		ResultPTRProtectA							=ResultPTRAmmoC+0x8;
		ResultPTRProtectNew1						=ResultPTRProtectA-0x10;
		ResultPTRProtectB							=ResultPTRAmmoC+0x10;
		ResultPTRProtectNew2						=ResultPTRProtectB+0x4;
		ResultPTRProtectC							=ResultPTRAmmoC+0x24;
		ResultPTRProtectD							=ResultPTRAmmoC+0x68;

		BypassI3Error			= dwi3Error+0xC7-0x31;
		ResultTime3Min = ResultTime3M - 0x11;
		ResultReplaceAllMode = ResultTime3Min - 0x24;		
 
MakePTR((PBYTE)(DWORD)GetModuleHandleA("i3FrameWorkDx.dll")+ResultImport_i3RenderContext_EndRender-dwi3FrameworkDx,(DWORD)hkEndRender);// ini mungkin gabunganya yapi dia di pisah.. aslinya sih dari sini
}

#define OFS_Primary			(ResultPTRTeam - 0x187C)
#define OFS_Secondary 		(OFS_Primary + 0x4)
#define OFS_Melle			(OFS_Primary + 0x8)
#define OFS_Explosive  		(OFS_Primary + 0xC)
#define OFS_Smoke 			(OFS_Primary + 0x10)
#define WEAPSIZE			0x158

static struct key_s
{
	bool bPressed;
	DWORD dwStartTime;
}

kPressingKey[256];
BOOL IsKeyPressed(int Key,DWORD dwTimeOut)
{
	if( HIWORD( GetKeyState( Key ) ) )
	{
		if( !kPressingKey[Key].bPressed || ( kPressingKey[Key].dwStartTime && ( kPressingKey[Key].dwStartTime + dwTimeOut ) <= GetTickCount( ) ) )
		{
			kPressingKey[Key].bPressed = TRUE;
			if( dwTimeOut > NULL )
				kPressingKey[Key].dwStartTime = GetTickCount( );
			return TRUE;
		}
	}else
		kPressingKey[Key].bPressed = FALSE;
	return FALSE;
}


/*cOptions D3D9 PBHacks Last Edit By ZrC-CyB Hacks*/

	int	Direct_D3D=0;
	int Direct_ESP=0;
	int Direct_HOT=0;
	int Direct_PLAYER=0;
	int Direct_WEAPON=0;
	int Direct_HEDGER=0;
	int Direct_REPLACE=0;
	int Direct_AMMO=0;
	int Direct_MISI=0;
	int Direct_TUTOR=0;
	int Direct_MENU=0;
	int Direct_BUTTON=0;
	int Direct_WINDOW=0;

	int WallHack=0;
	int Charms=0;
	int NoSmoke=0;
	int Cross=0;
	int ESPKD=0;
	int ESPBone=0;
	int ESPHealth=0;
	int ESPName=0;
	int ESPLine=0;
	int ESPBox=0;
	
	int AimBullet=0;
	int AutoBone=0;
	int ShowNickPlayers=0;
	int KickAllPlayers=0;
	int ShieldBM=0;

	int wutmo=0;
	int QuickChange=0;
	int NoReload=0;

	int FallDamage=0;
	int CallFastKnife=0;
	int FastKnife=0;
	int JumpHeight=0;

	int Accuracy=0;
	int NoRecoil=0;
	int Invicible=0;
	int WallShot=0;
	int FsSht=0;
	int BugUnyu=0;
	int FastShot=0;

	int CTPlant=0;
	int FastKiller=0;
	int FastBomberMan=0;
	int AutoKill=0;
	int BulletTele=0;
	int Zombie=0;
	int Suicide=0;
	int FakeBomberman=0;
	int BrutalReplace=0;
	
	int FreezeRespawn=0;
	int SetBurst=0;
	int NightVision=0;
	int FastExit=0;
void _fastcall RebuildMenuOff(){
	if(!IsInBattle())
	{
	WallHack=0;
	Charms=0;
	NoSmoke=0;
	Cross=0;
	ESPKD=0;
	ESPBone=0;
	ESPHealth=0;
	ESPName=0;
	ESPLine=0;
	ESPBox=0;
	
	AimBullet=0;
	AutoBone=0;
	ShowNickPlayers=0;
	KickAllPlayers=0;
	ShieldBM=0;

	wutmo=0;
	QuickChange=0;
	NoReload=0;
	BugUnyu=0;

	FallDamage=0;
	CallFastKnife=0;
	FastKnife=0;
	JumpHeight=0;

	Accuracy=0;
	NoRecoil=0;
	Invicible=0;
	WallShot=0;
	FsSht=0;

	CTPlant=0;
	FastKiller=0;
	FastBomberMan=0;
	AutoKill=0;
	FastKiller=0;
	BulletTele=0;
	Zombie=0;
	Suicide=0;
	BrutalReplace=0;
	
	FreezeRespawn=0;
	SetBurst=0;
	NightVision=0;
	}
}


/*-------------------------------------------------------------------------------------------------------------------*/