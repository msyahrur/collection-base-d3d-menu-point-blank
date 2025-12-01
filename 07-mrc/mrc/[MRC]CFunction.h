//----------------------------------------------------------------------------------------
//---------------------------------------------------------// [MRC]
//----------------------------------------------------------------------------------------
#include <windows.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include <tchar.h>
#include <iostream>
#include <d3dx9math.h>
#include <fstream>
#include <time.h>
#include <vector>
#include <math.h>
#include <cmath>
#include <iostream>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include <Io.h>
#include <stdlib.h>
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__82B107C2_CA0A_11D3_AAA4_00A0CC601A2E__INCLUDED_)
#define AFX_STDAFX_H__82B107C2_CA0A_11D3_AAA4_00A0CC601A2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__82B107C2_CA0A_11D3_AAA4_00A0CC601A2E__INCLUDED_)

//----------------------------------------------------------------------------------------
#pragma warning(disable:4244)
#pragma warning(disable:4700)
#pragma warning(disable:4996 4715)
#pragma warning(disable:4305)
using namespace std;
ofstream infile;
bool ChekLogPortal = false;
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
//----------------------------------------------------------------------------------------
#define Result_Address			1
#define Result_PTRByte			2
#define Result_PTR4Byte			3
#define Result_AddressString	4
#define Result_PTRStringByte	5
#define Result_PTRString4Byte	6
//----------------------------------------------------------------------------------------
char *GetDirectoryFile(char *filename);
void __cdecl add_log (const char * fmt, ...);
void thethread();
char dlldir[320];
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
DWORD ModulePB			= (DWORD)GetModuleHandleA("PointBlank.exe");;
DWORD ModuleSizePB      = GetSizeofCode("PointBlank.exe");
DWORD ModuleGF			= (DWORD)GetModuleHandleA("ModuleSizeGF.dll");
DWORD ModuleSizeGF		= GetSizeofCode("ModuleSizeGF.dll");
DWORD ModuleIP			= (DWORD)GetModuleHandleA("i3InputDx.dll");
DWORD ModuleSizeIP		= GetSizeofCode("i3InputDx.dll");
DWORD ModuleSC			= (DWORD)GetModuleHandleA("i3SceneDx.dll");
DWORD ModuleSizeSC		= GetSizeofCode("i3SceneDx.dll");
DWORD ModuleFW			= (DWORD)GetModuleHandle("i3FrameworkDx.dll");
DWORD ModuleSizeFW		= GetSizeofCode("i3FrameworkDx.dll");
DWORD ModuleNX			= (DWORD)GetModuleHandleA("NxCharacter.2.8.1.dll");
DWORD ModuleSizeNX		= GetSizeofCode("NxCharacter.2.8.1.dll");
DWORD ModuleD3D9		= (DWORD)GetModuleHandleA("d3d9.dll");
DWORD ModuleSizeD3D9	= GetSizeofCode("d3d9.dll");
//----------------------------------------------------------------------------------------
char *GetDirectoryFile(char *filename)
{
static char path[320];
strcpy(path, dlldir);
strcat(path, filename);
return path;
}
//----------------------------------------------------------------------------------------
void __cdecl BaseLog (const char *fmt, ...){
	if(infile != NULL){
		if(!fmt) { return; }
		va_list va_alist;
		char logbuf[256] = {0};
		va_start (va_alist, fmt);
		_vsnprintf (logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), fmt, va_alist);
		va_end (va_alist);
		infile << logbuf << endl;
	}
}
//----------------------------------------------------------------------------------------
DWORD FindPattern(DWORD dwdwAdd,DWORD dwLen,DWORD Address)
{
    for(DWORD i=0; i<dwLen; i++)
        if (*(PDWORD)(dwdwAdd+i)==Address)
			return (DWORD)(dwdwAdd+i);
    return 0;
}
//----------------------------------------------------------------------------------------
DWORD PUSH_STR_PB(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask,char * szMask)
{
DWORD STR = FindPattern((DWORD)dwdwAdd, (DWORD)dwLen, (PBYTE)bMask,szMask); 
if(STR!=NULL)
	{
	DWORD PUSH = FindPattern((DWORD)ModulePB, (DWORD)ModuleSizePB, STR)-1;
	if(PUSH!=NULL)
		{
		return PUSH;
		}
	}
	return 0;
}
//----------------------------------------------------------------------------------------
DWORD Func_SmartModuleStart(DWORD A)
{
	DWORD ModuleStart;
	if(A==1)
		ModuleStart=(DWORD)ModuleNX;
	else if(A==2)
		ModuleStart=(DWORD)ModuleFW;
	else if(A==3)
		ModuleStart=(DWORD)ModuleGF;
	else if(A==4)
		ModuleStart=(DWORD)ModuleIP;
	else if(A==5)
		ModuleStart=(DWORD)ModuleSC;
	else if(A==6)
		ModuleStart=(DWORD)ModuleD3D9;
	else
		ModuleStart=ModulePB;
	return ModuleStart;
}
//----------------------------------------------------------------------------------------
DWORD Func_SmartModuleEnd(DWORD A)
{
	DWORD ModuleEnd;
	if(A==1)
		ModuleEnd=(DWORD)ModuleSizeNX;
	else if(A==2)
		ModuleEnd=(DWORD)ModuleSizeFW;
	else if(A==3)
		ModuleEnd=(DWORD)ModuleSizeGF;
	else if(A==4)
		ModuleEnd=(DWORD)ModuleSizeIP;
	else if(A==5)
		ModuleEnd=(DWORD)ModuleSizeSC;
	else if(A==6)
		ModuleEnd=(DWORD)ModuleSizeD3D9;
	else
		ModuleEnd=(DWORD)ModuleSizePB;
	return ModuleEnd;
}
//----------------------------------------------------------------------------------------
DWORD Func_CrazyFindSystem(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask,char * szMask,int Offsete,int Result)
{
	if(FindPattern(dwdwAdd,dwLen,bMask,szMask) != NULL)
	{
		DWORD ADR = FindPattern(dwdwAdd,dwLen,bMask,szMask);
		if(ADR != NULL)
		{
			if(Result==Result_Address)
			{
				if((DWORD)(ADR + Offsete) != NULL)
					return (DWORD)(ADR + Offsete);
				else return 0;
			}
			else
			if(Result==Result_PTRByte)
			{
				if(*(BYTE*)(ADR + Offsete))
					return *(BYTE*)(ADR + Offsete);
				else return 0;
			}
			else
			if(Result==Result_PTR4Byte)
			{
				if(*(DWORD*)(ADR + Offsete))
					return *(DWORD*)(ADR + Offsete);
				else return 0;
			}
			else
			if(Result==Result_AddressString)
			{
				if(FindPattern((DWORD)dwdwAdd						,(DWORD)dwLen		,ADR))
				{
					DWORD PUSH = FindPattern((DWORD)dwdwAdd						,(DWORD)dwLen		,ADR)-1;
					if(PUSH!=NULL)
						if((DWORD)(PUSH + Offsete))
							return (DWORD)(PUSH + Offsete);
						else return 0;
					else return 0;
				}
				else return 0;
			}
			else
			if(Result==Result_PTRStringByte)
			{
				if(FindPattern((DWORD)dwdwAdd						,(DWORD)dwLen		,ADR))
				{
					DWORD PUSH = FindPattern((DWORD)dwdwAdd						,(DWORD)dwLen		,ADR)-1;
					if(PUSH!=NULL)
						if(*(BYTE*)(PUSH + Offsete))
							return *(BYTE*)(PUSH + Offsete);
						else return 0;
					else return 0;
				}
				else return 0;
			}
			else
			if(Result==Result_PTRString4Byte)
			{
				if(FindPattern((DWORD)ModulePB						,(DWORD)ModuleSizePB		,ADR))
				{
					DWORD PUSH = FindPattern((DWORD)ModulePB		,(DWORD)ModuleSizePB		,ADR)-1;
					if(PUSH!=NULL)
						if(*(DWORD*)(PUSH + Offsete))
							return *(DWORD*)(PUSH + Offsete);
						else return 0;
					else return 0;
				}
				else return 0;
			}
			else return 0;
		}
		else return 0;
	}
	else return 0;
}
//----------------------------------------------------------------------------------------
DWORD Func_SmartPattern(DWORD A,DWORD B,DWORD C,BYTE *D,char *E)
{
	DWORD Smart=0;
	DWORD ModuleStart	=Func_SmartModuleStart(A);
	DWORD ModuleEnd		=Func_SmartModuleEnd(A);
	if(B == Result_Address)
		Smart = Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
	else 
		if(C == Result_PTRByte)
			Smart = Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
		else 
			if(C == Result_PTR4Byte)
				Smart = Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
			else 
				if(C == Result_AddressString)
					Smart = Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
				else 
					if(C == Result_PTRStringByte)
						Smart = Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
					else 
						if(C == Result_PTRString4Byte)
							Smart = Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
	if(Smart!=NULL)
		return Smart;
}