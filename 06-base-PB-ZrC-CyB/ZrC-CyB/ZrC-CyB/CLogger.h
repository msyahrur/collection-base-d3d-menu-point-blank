/*CLogger.h PBHacks Last Edit By ZrC-CyB Hacks*/

#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <winbase.h>
#include <fstream>
#include <winbase.h>
#include <winternl.h>
#include <time.h>
#include "CByte.h"
#pragma warning(disable: 4996)

using namespace std;
ofstream infile;
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
char *GetDirectoryFile(char *filename);
void __cdecl Writelog(const char *fmt, ...);
DWORD FindPattern( DWORD dwStart, DWORD dwLen, BYTE* pszPatt, char pszMask[] );
DWORD GetSizeofCode( const char* szModuleName );

/*------------------------------------------- Declaration Function ------------------------------------------------------*/
char *GetDirectoryFile(char *filename)
{
	static char path[320];
	strcpy(path, dlldir);
	strcat(path, filename);
	return path;
}

void __cdecl Writelog(const char *fmt, ...)
{
	if(infile != NULL)
	{
		if(!fmt) { return; }

		va_list va_alist;
		char logbuf[256] = {0};

		va_start (va_alist, fmt);
		_vsnprintf (logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), fmt, va_alist);
		va_end (va_alist);

		infile << logbuf << endl;
	}
}

DWORD GetSizeofCode( const char* szModuleName ) 
{ 
	HMODULE hModule = GetModuleHandleA( szModuleName ); 
	if ( !hModule ) return NULL; 
	PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER( hModule ); 
	if( !pDosHeader ) return NULL; 
	PIMAGE_NT_HEADERS pNTHeader = PIMAGE_NT_HEADERS( (LONG)hModule + pDosHeader->e_lfanew ); 
	if( !pNTHeader ) return NULL; 
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pNTHeader->OptionalHeader; 
	if( !pOptionalHeader ) return NULL; 
	return pOptionalHeader->SizeOfCode; 
}

DWORD FindPattern( DWORD dwStart, DWORD dwLen, BYTE* pszPatt, char pszMask[] ) 
{ 
	unsigned int i = NULL; 
	int iLen = strlen( pszMask ) - 1; 
	for( DWORD dwRet = dwStart; dwRet < dwStart + dwLen; dwRet++ ) 
	{ 
		if( *(BYTE*)dwRet == pszPatt[i] || pszMask[i] == '?' ) 
		{ 
			if( pszMask[i+1] == '\0' ) return( dwRet - iLen ); i++; 
		} 
		else i = NULL; 
	} return NULL; 
}
/*------------------------------------------- Declaration hModule ------------------------------------------------------*/
LPTSTR PBSTR			= "PointBlank.exe";
LPTSTR PBi3Gfxx			= "i3GfxDx.dll";
LPTSTR PBi3Iptx			= "i3InputDx.dll";
LPTSTR PBi3Fmxx			= "i3FrameworkDx.dll";
LPTSTR PBNxChax			= "NxCharacter.2.8.1.dll";
LPTSTR g_EndRender		= "?EndRender@i3RenderContext@@QAEXXZ";
LPTSTR g_pRender		= "?g_pRenderContext@@3PAVi3RenderContext@@A";
LPTSTR g_ViewMatrix		= "?GetViewMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ";
LPTSTR g_ProjMatrix		= "?GetProjectMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ";
LPTSTR g_WorldMatrix	= "?GetWorldMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ";
LPTSTR g_DeltaX			= "?GetDeltaX@i3InputMouse@@QAEMXZ";
LPTSTR g_DeltaY			= "?GetDeltaY@i3InputMouse@@QAEMXZ";
LPTSTR g_BState			= "?GetButtonState@i3InputMouse@@QAEIXZ";

/*------------------------------------------- Declaration DWORD ------------------------------------------------------*/
DWORD DwStartAddress, DwStartGfx, DwStartScn, DwStartFmx, DwStartNxCha, DwSize, DwSizei3Fmx, DwSizeNxCha;
DWORD g_pRenderContext, Resultg_pRenderContext, EndRender, ResultEndRender, GetViewMatrix, ResultGetViewMatrix, GetProjMatrix, ResultGetProjMatrix, GetWorldMatrix, ResultGetWorldMatrix;
DWORD DwBaseWeapon, DwBaseCaclAmmo, ResultBaseWeapon, ResultBaseWeapon2, ResultBasePlayer, ResultBasePlayer2, ResultBaseHealth, ResultBaseHealth2, ResultBaseAmmo, ResultBaseAmmo2, ResultBaseCaclAmmo, ResultBaseMove, ResultBaseMove2, ResultBaseIdle, ResultBaseIdle2, ResultBaseWinMode, ResultBaseWinMode2;
DWORD DwPTRRecoil, DwPTRpTarget2, DwPTRCaclAmmo, DwPTRIdle, ResultPTRRecoil, DwmBone, DwStageInfo, DwBombArea, ResultmBone, ResultStageInfo, ResultBombArea, ResultPTRQC, ResultPTRWeapon, ResultPTRpTarget, ResultPTRpTarget2, ResultPTRJump, ResultPTRCamPos, ResultPTRFShot, ResultPTRRapid, ResultPTRFall, ResultPTRRepeat, ResultPTRCaclAmmo, ResultPTRCaclKnife, ResultPTRIdle, ResultPTRIdle2;
DWORD DwAsmDeltaX, DwAsmDeltaY, DwAsmBState, ResultAsmDeltaX, ResultAsmDeltaY, ResultAsmBState;
DWORD DwPLAYER, DwTEAM, DwNAMES, DwSKILL, DwHEALTH, DwNetChara, DwSkillGM, DwTSCORE, DwPING, ResultPLAYER, ResultTEAM, ResultNAMES, ResultSKILL, ResultSKILL2, ResultRESPAWN, ResultHEALTH, ResultNetChara, ResultPRIMARY, ResultSECONDARY, ResultMALE, ResultBOMB, ResultSMOKE, ResultSkillGM, ResultTSCORE, ResultINDISCORE, ResultPING;
DWORD DwVote, DwSuicide, DwBugUnyu, DwInvi, DwWallshoot, DwRange, Ret_Santet, DwMagnet, DwHover, ResultVote, ResultSuicide, ResultBugUnyu, ResultInvi, ResultWallshoot, ResultRange, ResultMagnet, ResultHover, ResultDatar;
DWORD DwSetNetChara, DwDoLine, DwCamPos, DwEventFire, ResultSetNetChara, ResultDoLine, ResultCamPos, ResultEventFire;
DWORD DwBullet, ResultBullet, DwDeltaX, DwDeltaY, DwGetButton, ResultDeltaX, ResultDeltaY, ResultGetButton;
DWORD DwPLAYERSIZE, DwWEAPONSIZE, DwHEALTHSIZE, DwRANKSIZE, DwNAMESIZE, ResultPLAYERSIZE, ResultWEAPONSIZE, ResultHEALTHSIZE, ResultRANKSIZE, ResultNAMESIZE;
DWORD ResultPRIMARYSIZE, ResultSECONDARYSIZE, ResultMALESIZE, ResultBOMBSIZE, ResultSMOKESIZE;
DWORD dwSetStart, dwSetEnd, dwInitialize, dwRaycastClosest, dwViewer;

/*------------------------------------------- Declaration AutoLogger ------------------------------------------------------*/
void SearchPatterns(void)
{
DwStartAddress = 0x400000;
do {
DwStartAddress = (DWORD)GetModuleHandle(PBSTR);
	}while(!DwStartAddress);
DwSize = 0xA00000;
DwSizei3Fmx = GetSizeofCode(PBi3Fmxx);
DwSizeNxCha = GetSizeofCode(PBNxChax);


dwSetStart = (DWORD)GetProcAddress(GetModuleHandleA("i3SceneDx.dll"), "?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z");
dwSetEnd = (DWORD)GetProcAddress(GetModuleHandleA("i3SceneDx.dll"), "?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z");
dwInitialize = (DWORD)GetProcAddress(GetModuleHandleA("i3SceneDx.dll"), "??0i3CollideeLine@@QAE@XZ");
dwRaycastClosest = (DWORD)GetProcAddress(GetModuleHandleA("i3SceneDx.dll"), "?RaycastClosest@i3PhysixContext@@QAEPAU_tagi3PhysixHitResult@@PAVi3CollideeLine@@HI@Z");
dwViewer = (DWORD)GetProcAddress(GetModuleHandleA("i3FrameworkDx.dll"), "?g_pMainViewer@@3PAVi3Viewer@@A");
		 
         DwStartGfx       = (DWORD)GetModuleHandle(PBi3Gfxx);
         DwStartFmx       = (DWORD)GetModuleHandle(PBi3Fmxx);
         DwStartNxCha     = (DWORD)GetModuleHandle(PBNxChax);
         EndRender		  = (DWORD)GetProcAddress(GetModuleHandleA(PBi3Gfxx), g_EndRender);
		 g_pRenderContext = (DWORD)GetProcAddress(GetModuleHandleA(PBi3Gfxx), g_pRender);
//		 GetViewMatrix    = (DWORD)GetProcAddress(GetModuleHandleA(PBi3Gfx), g_ViewMatrix);
//		 GetProjMatrix    = (DWORD)GetProcAddress(GetModuleHandleA(PBi3Gfx), g_ProjMatrix);
		 GetWorldMatrix   = (DWORD)GetProcAddress(GetModuleHandleA(PBi3Gfxx), g_WorldMatrix);
//		 DwAsmDeltaX      = (DWORD)GetProcAddress(GetModuleHandleA(PBi3Ipt), g_DeltaX);
//		 DwAsmDeltaY      = (DWORD)GetProcAddress(GetModuleHandleA(PBi3Ipt), g_DeltaY);
//		 DwAsmBState      = (DWORD)GetProcAddress(GetModuleHandleA(PBi3Ipt), g_BState);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (EndRender+0x2), &ResultEndRender, sizeof(ResultEndRender), NULL);
//		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (GetViewMatrix+0x2), &ResultGetViewMatrix, sizeof(ResultGetViewMatrix), NULL);
//		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (GetProjMatrix+0x2), &ResultGetProjMatrix, sizeof(ResultGetProjMatrix), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (GetWorldMatrix+0x2), &ResultGetWorldMatrix, sizeof(ResultGetWorldMatrix), NULL);
//		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwAsmDeltaX+0x2), &ResultAsmDeltaX, sizeof(ResultAsmDeltaX), NULL);
//		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwAsmDeltaY+0x2), &ResultAsmDeltaY, sizeof(ResultAsmDeltaY), NULL);
//		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwAsmBState+0x2), &ResultAsmBState, sizeof(ResultAsmBState), NULL);

		 DwBaseWeapon	  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_BaseWeapon,Mask_BaseWeapon);
		 DwPTRRecoil	  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_PTRRecoil,Mask_PTRRecoil);
		 DwmBone	      = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_mBone,Mask_mBone);
		 DwStageInfo	  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_STAGEINFO,Mask_STAGEINFO);
		 DwBombArea       = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_BombArea,Mask_BombArea);
		 DwBaseCaclAmmo	  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_BaseCaclAmmo,Mask_BaseCaclAmmo);
		 DwPTRpTarget2	  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_pTarget2,Mask_pTarget2);
		 DwPTRCaclAmmo    = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_CaclAmmo,Mask_CaclAmmo);
		 DwPTRIdle		  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_PTRIdle,Mask_PTRIdle);
//		 DwPLAYER		  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_PLAYER,Mask_PLAYER);
		 DwTEAM		      = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_TEAM,Mask_TEAM);
		 DwNAMES		  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_NAMES,Mask_NAMES);
		 DwSKILL		  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_SKILL,Mask_SKILL);
//		 DwHEALTH		  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_HEALTH,Mask_HEALTH);
		 DwNetChara		  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_NetChara,Mask_NetChara);
//		 DwSkillGM		  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_SkillGM,Mask_SkillGM);
		 DwTSCORE		  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_TSCORE,Mask_TSCORE);
		 DwPING		      = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_PING,Mask_PING);
//		 DwVote		      = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_Vote,Mask_Vote);
		 DwSuicide        = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_Suicide,Mask_Suicide);
		 DwBugUnyu        = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_BugUnyu,Mask_BugUnyu);
//		 DwInvi			  = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_Invi,Mask_Invi);
//		 DwWallshoot      = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_Wallshoot,Mask_Wallshoot);
//		 DwRange          = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_Range,Mask_Range);
		 DwSetNetChara    = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_SetNetChara,Mask_SetNetChara);
//		 DwDoLine         = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_DoLine,Mask_DoLine);
//		 DwCamPos         = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_CamPos,Mask_CamPos);
//		 DwEventFire      = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_EventFire,Mask_EventFire);
		 DwBullet         = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_Bullet,Mask_Bullet);
		 DwDeltaX         = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_DeltaX,Mask_DeltaX);
		 DwDeltaY         = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_DeltaX,Mask_DeltaX);
		 DwGetButton      = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_GetButton,Mask_GetButton);
		 DwPLAYERSIZE     = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_PLAYERSIZE,Mask_PLAYERSIZE);
		 DwWEAPONSIZE     = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_WEAPONSIZE,Mask_WEAPONSIZE);
//		 DwHEALTHSIZE     = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_HEALTHSIZE,Mask_HEALTHSIZE);
//		 DwRANKSIZE       = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_RANKSIZE,Mask_RANKSIZE);
//		 DwNAMESIZE       = FindPattern(DwStartAddress,DwSize,(PBYTE)Pattern_NAMESIZE,Mask_NAMESIZE);
		 DwMagnet         = FindPattern(DwStartFmx,DwSizei3Fmx,(PBYTE)Pattern_Magnet,Mask_Magnet);
		 DwHover          = FindPattern(DwStartNxCha,DwSizeNxCha,(PBYTE)Pattern_Hover,Mask_Hover);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwBaseWeapon+0x2), &ResultBaseWeapon2, sizeof(ResultBaseWeapon2), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwPTRRecoil+0x2), &ResultPTRRecoil, sizeof(ResultPTRRecoil), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwmBone+0x2), &ResultmBone, sizeof(ResultmBone), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwStageInfo+0x6), &ResultStageInfo, sizeof(ResultStageInfo), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwBombArea+0xF), &ResultBombArea, sizeof(ResultBombArea), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwBaseCaclAmmo+0xC), &ResultBaseCaclAmmo, sizeof(ResultBaseCaclAmmo), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwPTRpTarget2+0xE), &ResultPTRpTarget2, sizeof(ResultPTRpTarget2), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwPTRCaclAmmo+0xF), &ResultPTRCaclAmmo, sizeof(ResultPTRCaclAmmo), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwPTRIdle+0x18), &ResultPTRIdle, sizeof(ResultPTRIdle), NULL);
//		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwPLAYER+0x3), &ResultPLAYER, sizeof(ResultPLAYER), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwTEAM+0x2), &ResultTEAM, sizeof(ResultTEAM), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwNAMES+0x3), &ResultNAMES, sizeof(ResultNAMES), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwSKILL+0x3), &ResultSKILL, sizeof(ResultSKILL), NULL);
//		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwHEALTH+0x13), &ResultHEALTH, sizeof(ResultHEALTH), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwNetChara+0xC), &ResultNetChara, sizeof(ResultNetChara), NULL);
//		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwSkillGM+0x22), &ResultSkillGM, sizeof(ResultSkillGM), NULL);
//		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwTSCORE+0xC), &ResultTSCORE, sizeof(ResultTSCORE), NULL);
//		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwPING+0xB), &ResultPING, sizeof(ResultPING), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwBullet+0x9), &ResultBullet, sizeof(ResultBullet), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwDeltaX+0x1A), &ResultDeltaX, sizeof(ResultDeltaX), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwDeltaY+0x3F), &ResultDeltaY, sizeof(ResultDeltaY), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwGetButton+0x12), &ResultGetButton, sizeof(ResultGetButton), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwPLAYERSIZE+0x5), &ResultPLAYERSIZE, sizeof(ResultPLAYERSIZE), NULL);
		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwWEAPONSIZE+0x5), &ResultWEAPONSIZE, sizeof(ResultWEAPONSIZE), NULL);
//		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwHEALTHSIZE+0xA), &ResultHEALTHSIZE, sizeof(ResultHEALTHSIZE), NULL);
//		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwRANKSIZE+0x7), &ResultRANKSIZE, sizeof(ResultRANKSIZE), NULL);
//		 ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (DwNAMESIZE+0x7), &ResultNAMESIZE, sizeof(ResultNAMESIZE), NULL);

/*------------------------------------------- Declaration Result ------------------------------------------------------*/
		 Resultg_pRenderContext = g_pRenderContext - DwStartGfx;
         ResultGetViewMatrix    = 0x20;
		 ResultGetProjMatrix    = 0x60;
		 ResultAsmDeltaX        = 0x14;
		 ResultAsmDeltaY        = 0x18;
		 ResultAsmBState        = 0x20;
		 ResultBaseWeapon       = ResultBaseWeapon2 - DwStartAddress;
		 ResultBasePlayer		= ResultBaseWeapon + 0x1C;
		 ResultBasePlayer2		= ResultBaseWeapon2 + 0x1C;
		 ResultBaseHealth		= ResultBasePlayer - 0x34;
		 ResultBaseHealth2		= ResultBasePlayer2 - 0x34;
		 ResultBaseAmmo			= ResultBasePlayer - 0x38;
		 ResultBaseAmmo2		= ResultBasePlayer2 - 0x38;
		 ResultBaseMove			= ResultBasePlayer - 0x28;
		 ResultBaseMove2		= ResultBasePlayer2 - 0x28;
		 ResultBaseIdle			= ResultBasePlayer - 0x8;
		 ResultBaseIdle2		= ResultBasePlayer2 - 0x8;
		 ResultBaseWinMode		= ResultBasePlayer - 0x794;
		 ResultBaseWinMode2		= ResultBasePlayer2 - 0x794;
		 ResultPTRWeapon		= ResultPTRRecoil - 0x14;
		 ResultPTRCamPos		= ResultPTRRecoil - 0x4;
		 ResultPTRJump          = ResultPTRRecoil - 0x10;
		 ResultPTRQC		    = ResultPTRRecoil - 0x18;
		 ResultPTRpTarget		= ResultPTRRecoil + 0x8;
		 ResultPTRFShot		    = ResultPTRRecoil - 0x54;
		 ResultPTRRapid		    = ResultPTRCaclAmmo - 0x6B4;
		 ResultPTRFall		    = ResultPTRRecoil - 0x48;
		 ResultPTRRepeat		= ResultPTRFall + 0x3;
		 ResultPTRCaclKnife	    = ResultPTRCaclAmmo - 0xC;
		 ResultPTRIdle			= ResultPTRIdle - 0x1;
		 ResultPTRIdle2			= ResultPTRIdle + 0x4;
		 ResultPLAYER           = ResultSKILL - 0x26C;
		 ResultSKILL2           = ResultSKILL + 0x1;
		 ResultRESPAWN          = ResultSKILL + 0x2;
		 ResultHEALTH			= 0x264;
		 ResultPRIMARY          = ResultNetChara + 0x134;
		 ResultSECONDARY        = ResultPRIMARY + 0x4;
		 ResultMALE             = ResultPRIMARY + 0x8;
		 ResultBOMB             = ResultPRIMARY + 0xC;
		 ResultSMOKE            = ResultPRIMARY + 0x10;
		 ResultINDISCORE        = ResultTSCORE + 0x8;
		 ResultSkillGM          = ResultPLAYER + 0xAC;
		 ResultVote             = DwVote;
		 ResultSuicide          = DwSuicide;
		 ResultBugUnyu			= DwBugUnyu;
		 ResultInvi             = DwInvi;
		 ResultWallshoot        = DwWallshoot;
		 ResultRange            = DwRange;
		 Ret_Santet				= DwRange+0x5;
		 ResultMagnet           = DwMagnet + 0x6 - DwStartFmx;
		 ResultHover            = DwHover - DwStartNxCha;
		 ResultDatar            = ResultHover + 0xD3;
		 ResultSetNetChara      = DwSetNetChara + 0xD;
		 ResultDoLine           = DwDoLine;
		 ResultCamPos           = DwCamPos;
		 ResultEventFire        = DwEventFire;
		 ResultHEALTHSIZE       = 0x24;
		 ResultRANKSIZE         = 0x2B;
		 ResultNAMESIZE         = 0x21;
		 ResultPRIMARYSIZE      = 0x1C;
		 ResultSECONDARYSIZE    = 0x20;
		 ResultMALESIZE			= 0x24;
		 ResultBOMBSIZE			= 0x28;
		 ResultSMOKESIZE		= 0x2C;
}