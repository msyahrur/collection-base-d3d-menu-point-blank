/*++

Copyright (c) Main Cit 96 Corporation.  All rights reserved.

Module Name:

 CGameFramework.h

Abstract:

    Type definitions for the basic sized types.

Author:

Revision History:

--*/

class i3PhysixResult
{
public:
	char _unk001[0x28];
	float Distance;
};

class i3CollideeLine
{
public:
	char _pad1[0x70];
	D3DXVECTOR3 vStart;  //0x70, 0x74, 0x78
	D3DXVECTOR3 vEnd;  //0x7C, 0x80, 0x84
	D3DXVECTOR3 vDir;  //0x88, 0x8C, 0x90
};

class i3InputMouse
{
public:

	DWORD GetButtonState()
	{
		typedef DWORD (__thiscall * tGetButtonState)(i3InputMouse* Base);
		tGetButtonState GetButtonState = (tGetButtonState)(GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?GetButtonState@i3InputMouse@@QAEIXZ") );
		return GetButtonState(this);
	}

};

class CGameChatBox 
{
public:

	void _PutStringBackUpBuffer(const char* str) 
	{ 	
		return ((void(__thiscall*)(CGameChatBox*, const char *))Result_PutStringBackUpBuffer)(this, str);
	}
};

class CGameFramework 
{
public:

	void SetAnnounceMessage(const char* str) 
	{ 
		__try
		{
			return ((void(__thiscall*)(CGameFramework*, const char *))ResultSetAnnounceMessage)(this, str);
		}__except (EXCEPTION_EXECUTE_HANDLER){}
	}
	
	void SetNightVisionEnable(int N) 
	{ 
		__try
		{
			return ((void(__thiscall*)(CGameFramework*, int))ResultSetNightVisionEnable)(this, N);
		}__except (EXCEPTION_EXECUTE_HANDLER){}
	}

	void MsgBox(LPCSTR lpText, LPCSTR lpCaption) 
	{ 
		__try
		{
		DWORD CMsgBoxCallBack=00; 
#define MB_OKONLY           0x20001
#define MB_OKEXITCANCEL     0x20002
#define MB_NOBUTTON         0x20004
		return ((void(__thiscall*)(CGameFramework*, const char *, const char *, int, void*, void*, int,int,int))ResultMsgBox)(this, lpText, lpCaption, MB_OKONLY,&CMsgBoxCallBack, 00, 0x0A,0x01,0x1);
		}__except (EXCEPTION_EXECUTE_HANDLER){}
	}

	CGameChatBox* GetChatBox() 
	{
		return ((CGameChatBox* (__thiscall*)(CGameFramework*))ResultCGetChatBox)(this);
	}
	
	i3InputMouse* geti3InputMouse(void)
	{
		return (i3InputMouse*)*(DWORD*)(this+0x1D4);
	}

	i3PhysixResult* RaycastClosest(i3CollideeLine* pLine, DWORD dwOption){
		typedef i3PhysixResult* (__thiscall * tRaycastClosest)(CGameFramework* Base, i3CollideeLine* pLine, DWORD dwOption);
		tRaycastClosest RaycastClosest = (tRaycastClosest)(ResultCallRaycastClosest);
		return RaycastClosest(this, pLine, dwOption);
	}

	static CGameFramework* g_pFramework()
	{
		DWORD Callerg_pFramework;
		__asm
		{
			mov ecx,Resultg_pFramework
				call ResultCallg_pFramework
				mov Callerg_pFramework,ecx;
		}
		return (CGameFramework*)((DWORD)Callerg_pFramework);
	}
};

void PrintChatBox(const char* fmt, ...)
{
	va_list va_alist;
	char logbuf[256] = { 0 };
	va_start(va_alist, fmt);
	vsnprintf_s(logbuf + strlen(logbuf), sizeof(logbuf) - strlen(logbuf), _TRUNCATE, fmt, va_alist);
	va_end(va_alist);
	CGameFramework::g_pFramework()->GetChatBox()->_PutStringBackUpBuffer(logbuf);
}

float DistanceBetweenVector( D3DXVECTOR3 VecA, D3DXVECTOR3 VecB )
{
        return sqrt( ( ( VecA.x - VecB.x ) * ( VecA.x - VecB.x ) ) +
                 ( ( VecA.y - VecB.y ) * ( VecA.y - VecB.y ) ) +
                 ( ( VecA.z - VecB.z ) * ( VecA.z - VecB.z ) ) );
}

//----------------------------------------------------------------------------------------//
typedef void (__thiscall * ti3CollideeLine_Initialize)(i3CollideeLine* pLine);
ti3CollideeLine_Initialize i3CollideeLine_Initialize;
//----------------------------------------------------------------------------------------//
typedef void (__thiscall * ti3CollideeLine_SetStart)(i3CollideeLine* pLine, D3DXVECTOR3 *Value);
ti3CollideeLine_SetStart i3CollideeLine_SetStart;
//----------------------------------------------------------------------------------------//
typedef void (__thiscall * ti3CollideeLine_SetEnd)(i3CollideeLine* pLine, D3DXVECTOR3 *Value);
ti3CollideeLine_SetEnd i3CollideeLine_SetEnd;
//----------------------------------------------------------------------------------------//
void InitializeVisibleCheck()
{
	static bool bInitViscek = false;
	if(bInitViscek) return;
	HMODULE hScene = GetModuleHandle("i3SceneDx.dll");
	while(!hScene)Sleep(50);
	i3CollideeLine_Initialize = (ti3CollideeLine_Initialize)(DWORD)GetProcAddress(hScene,"??0i3CollideeLine@@QAE@XZ"); 
	i3CollideeLine_SetStart = (ti3CollideeLine_SetStart)(DWORD)GetProcAddress(hScene,"?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z");
	i3CollideeLine_SetEnd = (ti3CollideeLine_SetEnd)(DWORD)GetProcAddress(hScene,"?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z");
	bInitViscek = true;
}

bool GetPlayerVisibleStatus(int ActorIndex, int TargetIndex, int BoneTargetIndex)
{
	InitializeVisibleCheck();
	i3CollideeLine Line;
	D3DXVECTOR3 vTarget, vLocal;

	GetUserBone(vLocal,5,ActorIndex);
	GetUserBone(vTarget,BoneTargetIndex,TargetIndex);

	vLocal.y += 0.1f;

	i3CollideeLine_Initialize(&Line);
	i3CollideeLine_SetStart(&Line,&vLocal);
	i3CollideeLine_SetEnd(&Line,&vTarget);

	i3PhysixResult* pResult = CGameFramework::g_pFramework()->RaycastClosest(&Line,NULL);
	if(!pResult)return false;

	return(pResult->Distance >= DistanceBetweenVector(vTarget,vLocal));
}