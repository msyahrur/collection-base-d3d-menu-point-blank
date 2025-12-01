void MemWrite(LPVOID pxAddress,PBYTE code,int size)
{
    unsigned long Protection;
    VirtualProtect((LPVOID)pxAddress,size,PAGE_READWRITE,&Protection);
    memcpy((LPVOID)pxAddress,(const LPVOID )code,size);
    VirtualProtect((LPVOID)pxAddress,size,Protection,0);
}

void Bypass(void)
{
DWORD hEhSvc = 0;
do {
hEhSvc =(DWORD)GetModuleHandleA("EhSvc.dll");
Sleep(100);
} while(!hEhSvc);
if(hEhSvc > 0)
{
MemWrite((LPVOID)(hEhSvc+0x0B0F0),(PBYTE)"\xC2\x04\x00",3);//83ec0853555657
MemWrite((LPVOID)(hEhSvc+0x0B188),(PBYTE)"\x74",1);//751555e8????????83c4
MemWrite((LPVOID)(hEhSvc+0x3C9ED),(PBYTE)"\x90\x90",2);//0c5383f8017567
MemWrite((LPVOID)(hEhSvc+0x4B1d4),(PBYTE)"\x31",1);//8b85????????408985????????ff87????????85c074
MemWrite((LPVOID)(hEhSvc+0x4E2CE),(PBYTE)"\x31",1);//c70000000000e8
MemWrite((LPVOID)(hEhSvc+0x4e344),(PBYTE)"\x90\x90",2);//56c702????????e8 edit
MemWrite((LPVOID)(hEhSvc+0x9ff02),(PBYTE)"\xC3",1);//574c2089d289??89??89??89??89??908b55b8
MemWrite((LPVOID)(hEhSvc+0xc2cf8),(PBYTE)"\x90\x90\x90\x90\x90\x90",6);//8b55??8b45??0342??8945??
MemWrite((LPVOID)(hEhSvc+0xc8920),(PBYTE)"\x03\xD2",2);
}
}

void RegardsHackShield(void)
{
DWORD dwEhSvc;
do
{
dwEhSvc = (DWORD)GetModuleHandleA("Ehsvc.dll");
Sleep(30);
}
while (!dwEhSvc);//a011d,a0060
_My->PrivateOnly((void *)(dwEhSvc + 0xa011d), (void *)"\xC3",1);//55 8B EC 83 EC ?? 53 56 57 89 4D ??
_My->PrivateOnly((void *)(dwEhSvc + 0x0B0F0), (void *)"\xC2\x04\x00",3);//Detection//83 EC 08 53 55 56 57 89 4C 24 10 8B 41 0C 83 F8 
_My->PrivateOnly((void *)(dwEhSvc + 0x4B2DF), (void *)"\x90\x90",2);//HS_ASM//85 F6 0F 84 9C 01 00 00 8A 46 14 84 C0 0F 84 91 
_My->PrivateOnly((void *)(dwEhSvc + 0x4E3CE), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 

/*
_My->PrivateOnly((void *)(dwEhSvc + 0xa054F), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0xB58D), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0xB610), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0xF778), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0x100af), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0x10b9c), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0x11AEC), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0x181f2), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0x1dcfe), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0x3d53e), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0x3d9dc), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0x4f515), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0x563c7), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0x579e8), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0x6752f), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0x93799), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0x94166), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0x94179), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0xa10fe), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0xa17a2), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0xb1a70), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0xb1a86), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0xb1d81), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
_My->PrivateOnly((void *)(dwEhSvc + 0xbe17a), (void *)"\x90\x90",2);//HSAntiCrash//85 C0 0F 84 60 01 00 00 C7 45 E0 00 00 00 00 8B 
//*/
}//*/

#ifndef _ANTIHACKSHIELD_H
#define _ANTIHACKSHIELD_H

#include "Psapi.h"

typedef LONG (WINAPI* tZwSetEvent)(HANDLE EventHandle, PLONG PreviousState);
tZwSetEvent oZwSetEvent;

bool bThreadTerminate = false;

DWORD dwMAIN_THREAD;
DWORD dwLMP_HACKSHIELD_THREAD;
DWORD dwDETECT_GAME_HACK_HACKSHIELD_THREAD_1;
DWORD dwDETECT_GAME_HACK_HACKSHIELD_THREAD_2;
DWORD dwCHECK_INTEGRITY_HACKSHIELD_THREAD;
DWORD dwKDTRACE_HACKSHIELD_THREAD;

DWORD dwLMP_HACKSHIELD_THREAD_EVENT;
//DWORD dwDETECT_GAME_HACK_HACKSHIELD_THREAD_1_EVENT;
DWORD dwDETECT_GAME_HACK_HACKSHIELD_THREAD_2_EVENT;
DWORD dwCHECK_INTEGRITY_HACKSHIELD_THREAD_EVENT;

DWORD dwPFN_SECURE_HACKSHIELD_FUNCTION_CALL;
DWORD dwHACKSHIELD_CALL_TO_CREATE_THREAD;

MODULEINFO mEngine, mEhSvc;

#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
DWORD FindPattern( DWORD rangeStart, DWORD rangeEnd, const char* pattern )
{
    const char* pat = pattern;
    DWORD firstMatch = 0;
    for( DWORD pCur = rangeStart; pCur < rangeEnd; pCur++ )
    {
        if( !*pat ) return firstMatch;
        if( *(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte( pat ) ) {
            if( !firstMatch ) firstMatch = pCur;
            if( !pat[2] ) return firstMatch;
            if( *(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?' ) pat += 3;
            else pat += 2;  

        } else {
            pat = pattern;
            firstMatch = 0;
        }
    }
    return NULL;
}

struct sHackShieldThreadParams
{
    char _pad1[0x48];
    DWORD param1;
    DWORD param2;
};


#pragma optimize("", off)
void FakeASMCheck()
{
    
    oZwSetEvent((HANDLE) *(DWORD *)dwLMP_HACKSHIELD_THREAD_EVENT, 0);
    

    while(bThreadTerminate == false)
        Sleep(1000);
}

/*void FakeHeuristicScanThread()
{
    
    dwDETECT_GAME_HACK_HACKSHIELD_THREAD_1_EVENT = *(DWORD *)(dwDETECT_GAME_HACK_HACKSHIELD_THREAD_1_EVENT + 1 );
    dwDETECT_GAME_HACK_HACKSHIELD_THREAD_1_EVENT = *(DWORD *)(dwDETECT_GAME_HACK_HACKSHIELD_THREAD_1_EVENT + 0xBCC);

    oZwSetEvent((HANDLE)dwDETECT_GAME_HACK_HACKSHIELD_THREAD_1_EVENT, 0);
    
    while(bThreadTerminate == false)
        Sleep(1000);
}//*/

void FakeHeuristicModulesScanThread()
{
    
    dwDETECT_GAME_HACK_HACKSHIELD_THREAD_2_EVENT = *(DWORD *)(dwDETECT_GAME_HACK_HACKSHIELD_THREAD_2_EVENT + 1);
    dwDETECT_GAME_HACK_HACKSHIELD_THREAD_2_EVENT = *(DWORD *)(dwDETECT_GAME_HACK_HACKSHIELD_THREAD_2_EVENT);
    dwDETECT_GAME_HACK_HACKSHIELD_THREAD_2_EVENT = *(DWORD *)(dwDETECT_GAME_HACK_HACKSHIELD_THREAD_2_EVENT + 0xB98);

    oZwSetEvent((HANDLE)dwDETECT_GAME_HACK_HACKSHIELD_THREAD_2_EVENT, 0);
    
    while(bThreadTerminate == false)
        Sleep(1000);
}


void FakeHackShieldIntegrityChecks()
{
    
    dwCHECK_INTEGRITY_HACKSHIELD_THREAD_EVENT = **(DWORD **)(dwCHECK_INTEGRITY_HACKSHIELD_THREAD_EVENT + 2);
    oZwSetEvent((HANDLE) dwCHECK_INTEGRITY_HACKSHIELD_THREAD_EVENT, 0);
    
    while(bThreadTerminate == false)
        Sleep(1000);
}

void FakeKernelTraceThread()
{
    while(bThreadTerminate == false)
        Sleep(1000);
}


typedef HANDLE(WINAPI* tCreateThread)(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
tCreateThread oCreateThread;
HANDLE WINAPI hkCreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId)
{
    
    __asm pushad;

    if(lpStartAddress == (LPTHREAD_START_ROUTINE)dwMAIN_THREAD )
    {
        sHackShieldThreadParams * pHackShieldThreadParams = (sHackShieldThreadParams *)lpParameter;

        if(pHackShieldThreadParams->param1 == dwLMP_HACKSHIELD_THREAD )
            pHackShieldThreadParams->param1 = (DWORD)FakeASMCheck;
        
        if(pHackShieldThreadParams->param1 == dwCHECK_INTEGRITY_HACKSHIELD_THREAD ) 
            pHackShieldThreadParams->param1 = (DWORD)FakeHackShieldIntegrityChecks;

      //  if(pHackShieldThreadParams->param1 == dwDETECT_GAME_HACK_HACKSHIELD_THREAD_1 ) 
       //     pHackShieldThreadParams->param1 = (DWORD)FakeHeuristicScanThread;
            
        if(pHackShieldThreadParams->param1 == dwDETECT_GAME_HACK_HACKSHIELD_THREAD_2 )
            pHackShieldThreadParams->param1 = (DWORD)FakeHeuristicModulesScanThread;

        if(pHackShieldThreadParams->param1 == dwKDTRACE_HACKSHIELD_THREAD ) 
            pHackShieldThreadParams->param1 = (DWORD)FakeKernelTraceThread;

        lpParameter = (LPVOID)pHackShieldThreadParams;
    }

    __asm popad;

    return oCreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
    
}


MODULEINFO GetModuleInfo ( LPCTSTR lpModuleName )
{
    
    MODULEINFO miInfos = { NULL };

    HMODULE hPSAPI_module;

    if(!GetModuleHandleA("psapi.dll"))
    {
        
        char szSystemPath[MAX_PATH];
        GetWindowsDirectory(szSystemPath, MAX_PATH);
        char szPSAPIDLLPath[MAX_PATH];
        sprintf(szPSAPIDLLPath, "%s\\system32\\psapi.dll", szSystemPath);
        //char *szSystemPath = new char[MAX_PATH] = getenv("SystemRoot");
        //sprintf(szSystemPath, "%s\\system32\\psapi.dll", szSystemPath);
        hPSAPI_module =  LoadLibrary(szPSAPIDLLPath);
        
    }
    else
        hPSAPI_module = GetModuleHandleA("psapi.dll");

    if (!hPSAPI_module)
        return miInfos;

    HMODULE hmModule = GetModuleHandle(lpModuleName); 

    typedef DWORD ( __stdcall *tGetModuleInformation)( HANDLE, HMODULE, LPMODULEINFO, DWORD );
    tGetModuleInformation oGetModuleInformation = (tGetModuleInformation) (GetProcAddress(hPSAPI_module, "GetModuleInformation"));
    oGetModuleInformation(GetCurrentProcess(), hmModule, &miInfos, sizeof ( MODULEINFO ));

    return miInfos;

    
}

#pragma optimize("", on)
typedef int(__cdecl* tSecureFunctionCall)(int a1, int a2, int a3);
tSecureFunctionCall oSecureFunctionCall;
int hk_secureFunctionCall(int a1, int a2, int a3)
{
    __asm pushad;
    
    if(a1 == 6) 
        bThreadTerminate = true;
    
    __asm popad;
    return oSecureFunctionCall(a1,a2,a3);
}

#pragma optimize("", off)
void InitializeHSBypass(void)
{
     while(!GetModuleHandleA("EhSvc.dll") )
    Sleep(100);
    mEngine = GetModuleInfo(0);
    mEhSvc = GetModuleInfo("EhSvc.dll");
    dwMAIN_THREAD = (DWORD) FindPattern( (DWORD)mEhSvc.lpBaseOfDll, (DWORD)( (DWORD) mEhSvc.lpBaseOfDll + (DWORD)mEhSvc.SizeOfImage), "55 8B EC 6A FF 68 ?? ?? ?? ?? 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 83 EC ?? 53 56 57 89 65 ?? FF 35");
   
	dwLMP_HACKSHIELD_THREAD = (DWORD) FindPattern( (DWORD)mEhSvc.lpBaseOfDll, (DWORD)( (DWORD) mEhSvc.lpBaseOfDll + (DWORD)mEhSvc.SizeOfImage), "55 8B EC 53 56 57 E9");
    dwLMP_HACKSHIELD_THREAD = dwLMP_HACKSHIELD_THREAD + 0x1;
	dwLMP_HACKSHIELD_THREAD_EVENT = ( (DWORD) mEhSvc.lpBaseOfDll + 0x151510);

    dwLMP_HACKSHIELD_THREAD = (DWORD) FindPattern( (DWORD)dwLMP_HACKSHIELD_THREAD, (DWORD)dwLMP_HACKSHIELD_THREAD + (DWORD)mEhSvc.SizeOfImage, "55 8B EC 53 56 57 E9");
	dwDETECT_GAME_HACK_HACKSHIELD_THREAD_1 = (DWORD)FindPattern( (DWORD)mEhSvc.lpBaseOfDll, (DWORD)( (DWORD) mEhSvc.lpBaseOfDll + (DWORD)mEhSvc.SizeOfImage), "8B 4C 24 04 E8");
    //dwDETECT_GAME_HACK_HACKSHIELD_THREAD_1_EVENT = (DWORD)FindPattern( (DWORD)mEhSvc.lpBaseOfDll, (DWORD)( (DWORD) mEhSvc.lpBaseOfDll + (DWORD)mEhSvc.SizeOfImage), "B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 5D C3");
    
	dwDETECT_GAME_HACK_HACKSHIELD_THREAD_2 = (DWORD)FindPattern( (DWORD)mEhSvc.lpBaseOfDll, (DWORD)( (DWORD) mEhSvc.lpBaseOfDll + (DWORD)mEhSvc.SizeOfImage), "55 8B EC 6A FF 68 ?? ?? ?? ?? 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 81 EC ?? ?? ?? ?? 53 56 57 89 65 ?? C6 45 ?? ?? C6");
    dwDETECT_GAME_HACK_HACKSHIELD_THREAD_2_EVENT = (DWORD)FindPattern( (DWORD)mEhSvc.lpBaseOfDll, (DWORD)( (DWORD) mEhSvc.lpBaseOfDll + (DWORD)mEhSvc.SizeOfImage), "A1 ?? ?? ?? ?? 53 56 33 F6 57 3B C6 89 65 ?? 75");    
    
	dwCHECK_INTEGRITY_HACKSHIELD_THREAD = (DWORD)FindPattern( (DWORD)mEhSvc.lpBaseOfDll, ( (DWORD) mEhSvc.lpBaseOfDll + (DWORD)mEhSvc.SizeOfImage), "55 8B EC B8" );
    dwCHECK_INTEGRITY_HACKSHIELD_THREAD_EVENT = (DWORD)FindPattern( (DWORD)mEhSvc.lpBaseOfDll, (DWORD)( (DWORD) mEhSvc.lpBaseOfDll + (DWORD)mEhSvc.SizeOfImage), "8B 0D ?? ?? ?? ?? 51 FF 15 ?? ?? ?? ?? 8B 55");
    
	dwKDTRACE_HACKSHIELD_THREAD = (DWORD)FindPattern( (DWORD)mEhSvc.lpBaseOfDll, (DWORD)( (DWORD) mEhSvc.lpBaseOfDll + (DWORD)mEhSvc.SizeOfImage), "55 8B EC 6A FF 68 ?? ?? ?? ?? 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 81 C4 ?? ?? ?? ?? 53 56 57 89 65 ?? C7 45 ?? ?? ?? ?? ?? C7 45 ?? ?? ?? ?? ?? C7 45 ?? ?? ?? ?? ?? FF"); 
        
	dwHACKSHIELD_CALL_TO_CREATE_THREAD = (DWORD)FindPattern( (DWORD)mEhSvc.lpBaseOfDll, (DWORD) ( (DWORD)mEhSvc.lpBaseOfDll + (DWORD)mEhSvc.SizeOfImage), "FF 15 ?? ?? ?? ?? 85 C0 75 ?? FF 15 ?? ?? ?? ?? 8B F8 56");
    dwHACKSHIELD_CALL_TO_CREATE_THREAD = *(DWORD *)(dwHACKSHIELD_CALL_TO_CREATE_THREAD + 2);
    
	dwPFN_SECURE_HACKSHIELD_FUNCTION_CALL = (DWORD)FindPattern( (DWORD)mEngine.lpBaseOfDll, (DWORD) ( (DWORD)mEngine.lpBaseOfDll + (DWORD)mEngine.SizeOfImage), "89 0D ?? ?? ?? ?? 8B 55 E8");
    dwPFN_SECURE_HACKSHIELD_FUNCTION_CALL = *(DWORD *)(dwPFN_SECURE_HACKSHIELD_FUNCTION_CALL + 2);
    //*/

    oZwSetEvent = (tZwSetEvent)GetProcAddress( GetModuleHandle("ntdll.dll"), "ZwSetEvent");
	
	DWORD oldProtect;
    VirtualProtect((void *)mEhSvc.lpBaseOfDll, mEhSvc.SizeOfImage, PAGE_EXECUTE_READWRITE, &oldProtect);
    oCreateThread = (tCreateThread) *(DWORD *)((DWORD)dwHACKSHIELD_CALL_TO_CREATE_THREAD);
    *(DWORD *)(dwHACKSHIELD_CALL_TO_CREATE_THREAD) = (DWORD)hkCreateThread;
    VirtualProtect((void *)mEhSvc.lpBaseOfDll, mEhSvc.SizeOfImage, oldProtect, &oldProtect);
   
	VirtualProtect((void *)mEngine.lpBaseOfDll, mEngine.SizeOfImage, PAGE_EXECUTE_READWRITE, &oldProtect);
    oSecureFunctionCall = (tSecureFunctionCall)*(DWORD*)dwPFN_SECURE_HACKSHIELD_FUNCTION_CALL;
    *(DWORD *)(dwPFN_SECURE_HACKSHIELD_FUNCTION_CALL) = (DWORD)hk_secureFunctionCall;
	
    VirtualProtect((void *)mEngine.lpBaseOfDll, mEngine.SizeOfImage, oldProtect, &oldProtect);
	bThreadTerminate = false;
    //*/
}
#pragma optimize("", on)
#endif//*/


#include <WinBase.h>
#include <iostream>

using namespace std;

DWORD JumpDetour(PBYTE Target,DWORD DetourDest,int OpsLeft)
{
DWORD Old;
VirtualProtect(Target,9+OpsLeft,PAGE_READWRITE,&Old);
Sleep(1);
*Target = 0x33;
Sleep(1);
*(BYTE*)(Target+1) = 0xC0;
Sleep(1);
*(BYTE*)(Target+2) = 0x05;
Sleep(1);
*(DWORD*)(Target+3) = DetourDest;
Sleep(1);
*(BYTE*)(Target+7) = 0xFF;
Sleep(1);
*(BYTE*)(Target+8) = 0xE0;
Sleep(1);
for(int lftover = 9; lftover < 9+OpsLeft; lftover++)
{
*(BYTE*)(Target+lftover)=0x90;
Sleep(1);
}
VirtualProtect(Target,9+OpsLeft,Old,0);
Sleep(1);
return (DWORD)(Target+9+OpsLeft);
}

#define HOOK(func,addy)  JumpDetour((PBYTE)func,(DWORD)addy, 5)

static int c, d = 0;
static DWORD Original, dwAddr;

DWORD _cdecl TheThread(LPVOID lpParameters)
{
	DWORD Old;
	VirtualProtect((void*)dwAddr, 5, PAGE_EXECUTE_READWRITE, &Old);
	memcpy((void*)dwAddr, (void*)Original, 5);
	VirtualProtect((void*)dwAddr, 5, Old, &Old);
	FlushInstructionCache((HANDLE)-1, (void*)dwAddr, 5);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)dwAddr, lpParameters, NULL, NULL);
	cout << "HEHEHEHEHEHEHEHEHEHE" << endl;
	DWORD OFS_Telekill 	= (DWORD)GetProcAddress(LoadLibrary("i3SceneDx.dll"),"?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z");
	JumpDetour((PBYTE)OFS_Telekill,(DWORD)i3CollideeLine_SetEnd,5);
	/*while (true)
	{
		cout << "Tick tock" << endl;
		Sleep(2500);
	}//*/
	return 0;
}

HANDLE WINAPI hkCreateThreadFake(LPSECURITY_ATTRIBUTES lpThreadAttributes,SIZE_T dwStackSize,LPTHREAD_START_ROUTINE lpStartAddress,LPVOID lpParameter,DWORD dwCreationFlags,LPDWORD lpThreadId)
{
	if ((DWORD)lpStartAddress > 0x4000000 && (DWORD)lpStartAddress < 0x5000000 && !d)
	{
		dwAddr = (DWORD)lpStartAddress; 
		Original = HOOK(TheThread, lpStartAddress);
		//cout << "CRIADO" << endl;
		d = 1;
	}
	return CreateRemoteThread((HANDLE)-1, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

LONG WINAPI VectoredHandler(PEXCEPTION_POINTERS p)
{
	if (!c && GetModuleHandle("d3d9.dll") != INVALID_HANDLE_VALUE)
	{
		Original = HOOK(&hkCreateThread, (DWORD)GetProcAddress(LoadLibrary("kernel32.dll"), "CreateThread"));
		c++;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}
