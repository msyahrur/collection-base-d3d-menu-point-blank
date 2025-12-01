#include <TlHelp32.h>
LPTSTR PointBlankNtDll = "ntdll.dll";
bool	Bulletf = false;
float	hoverv;
/*-------------------------------------------------------------------------------------------------------------------*/
typedef enum __THREAD_INFORMATION_CLASS { 
    ThreadBasicInformation, 
    ThreadTimes, 
    ThreadPriority, 
    ThreadBasePriority, 
    ThreadAffinityMask, 
    ThreadImpersonationToken, 
    ThreadDescriptorTableEntry, 
    ThreadEnableAlignmentFaultFixup, 
    ThreadEventPair, 
    ThreadQuerySetWin32StartAddress, 
    ThreadZeroTlsCell, 
    ThreadPerformanceCount, 
    ThreadAmILastThread, 
    ThreadIdealProcessor, 
    ThreadPriorityBoost, 
    ThreadSetTlsArrayAddress, 
//    ThreadIsIoPending, 
    ThreadHideFromDebugger 
} __THREAD_INFORMATION_CLASS, *PTHREAD_INFORMATION_CLASS;

/*-------------------------------------------------------------------------------------------------------------------*/
typedef DWORD(NTAPI *_ZwQueryInformationThread)(HANDLE ThreadHandle, __THREAD_INFORMATION_CLASS ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength, PULONG ReturnLength);  

/*-------------------------------------------------------------------------------------------------------------------*/
DWORD GetEntryPoint(DWORD TID)
{
	_ZwQueryInformationThread ZwQueryInformationThread = (_ZwQueryInformationThread)GetProcAddress(GetModuleHandleA(PointBlankNtDll), "ZwQueryInformationThread"); 
	HANDLE hThread = OpenThread(THREAD_QUERY_INFORMATION, false, TID);
	DWORD Start;
	ZwQueryInformationThread(hThread, ThreadQuerySetWin32StartAddress, &Start, sizeof(Start), NULL); 
	CloseHandle(hThread);
	return Start;
}

/*-------------------------------------------------------------------------------------------------------------------*/
HANDLE THandleFromEP()
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, GetCurrentThreadId());
	if (hSnap == INVALID_HANDLE_VALUE)
		return INVALID_HANDLE_VALUE;
	THREADENTRY32 TE = {0};
	TE.dwSize = sizeof(TE);
	Thread32First(hSnap, &TE);
	while (Thread32Next(hSnap, &TE))
	{
	//	if (GetEntryPoint(TE.th32ThreadID) == THandle1)
			return OpenThread(THREAD_SET_CONTEXT, false, TE.th32ThreadID);
	}
	return INVALID_HANDLE_VALUE;
}

/*-------------------------------------------------------------------------------------------------------------------*/
#define  Addres_BgHover	(DWORD)(GetModuleHandleA("NxCharacter.2.8.1.dll"))//+ ResultHover
DWORD RETURN_HOVERV = Addres_BgHover + 0x6;


__declspec( naked ) void Hover_On()
{
_asm
{
cmp [Bulletf],0
je Normall
mov [ebx+0000011Ch],eax
mov [hoverv],eax
jmp [RETURN_HOVERV]
Normall:
mov eax,[hoverv]
mov [ebx+0000011Ch],eax
jmp [RETURN_HOVERV]
}
}

//unsigned long PNT = THandle2;
LONG CALLBACK VectoredHandler(PEXCEPTION_POINTERS ExceptionInfo)
{
		if (ExceptionInfo->ExceptionRecord->ExceptionAddress == (void*)(Addres_BgHover))
	{
//     		ExceptionInfo->ContextRecord->Eip =PNT= (DWORD)Hover_On;

return EXCEPTION_CONTINUE_EXECUTION;
		}
return EXCEPTION_CONTINUE_SEARCH;
}
//==========================================================================================================================================//
#define PRCHOVER	(unsigned long)(GetModuleHandleA("NxCharacter.2.8.1.dll"))//+ ResultHover

void CallHover()
{
	AddVectoredExceptionHandler(1,VectoredHandler); 
	HANDLE hThread = THandleFromEP();
	CONTEXT Context = {CONTEXT_DEBUG_REGISTERS};
	Context.Dr0 = ((unsigned long)(PRCHOVER));
	Context.Dr6 = 0xFFFF0FF0;
	Context.Dr7 = 0x15;
	SetThreadContext(hThread,&Context);
}