#include <Windows.h>
#include "CHover.h"

void PacthHook(void *adr, void *ptr, int size)
{
DWORD CheckProtection = 0;
VirtualProtect(adr,size,PAGE_EXECUTE_READWRITE, &CheckProtection);
RtlMoveMemory(adr,ptr,size);
VirtualProtect(adr,size,CheckProtection, &CheckProtection);
}

void LongPtr ( DWORD adress, DWORD offset, DWORD offset2, int Value )
{
	__try
	{
		DWORD OldPtr;
		OldPtr = *(PDWORD)((DWORD)adress) + offset;
		OldPtr = *(PDWORD)((DWORD)OldPtr) + offset2;
		*(int*)(OldPtr) = Value;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
	}

}

int WritePtr (unsigned long ads, unsigned long ptr, int value)
{
	__try
	{
		unsigned long WrtPointer = false;
		WrtPointer = *(unsigned long*)((ads))+ptr;
		*(int*)(WrtPointer) = value;
		return true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return false;
	}
}

void _patchPTRZ(unsigned long adr, unsigned long Ofset1, DWORD dwValue)
{ 
	DWORD A=0;
	if(IsBadReadPtr((PDWORD)adr,4))return;
	A=*(PDWORD)((DWORD)(adr))+Ofset1;
	if(IsBadReadPtr((PDWORD)A,4))return;
	if(*(PDWORD)A!=dwValue)*(PDWORD)A=dwValue;
}

void _patchPTR(unsigned long adr, unsigned long Ofset1, unsigned long Ofset2, unsigned long Ofset3, unsigned long Ofset4, DWORD dwValue)
{ 
	DWORD A=0;
	if(IsBadReadPtr((PDWORD)adr,4))return;
	A=*(PDWORD)((DWORD)(adr))+Ofset1;
	if(IsBadReadPtr((PDWORD)A,4))return;
	A=*(PDWORD)((DWORD)(A))+Ofset2;
	if(IsBadReadPtr((PDWORD)A,4))return;
	A=*(PDWORD)((DWORD)(A))+Ofset3;
	if(IsBadReadPtr((PDWORD)A,4))return;
	A=*(PDWORD)((DWORD)(A))+Ofset4;
	if(IsBadReadPtr((PDWORD)A,4))return;
	if(*(PDWORD)A!=dwValue)*(PDWORD)A=dwValue;
}

DWORD Read(DWORD dwPtr, DWORD dwOfs){ 
DWORD C; 
if(IsBadReadPtr((PDWORD)(dwPtr),4)==0){ 
C=*(PDWORD)((DWORD)(dwPtr))+dwOfs; 
if(IsBadReadPtr((PDWORD)(C),4)==0){ 
return *(PDWORD)C; 
} } 
return C;
}

bool MakePoint(unsigned long ADRexec, int OFSexec, int PTRexec)
{
if (!IsBadReadPtr((void*)ADRexec, sizeof(unsigned long)))
{
if (!IsBadReadPtr((void*)(*(unsigned long*)ADRexec + OFSexec), sizeof(unsigned long)))
{
*(int*)(*(unsigned long*)ADRexec + OFSexec) = PTRexec;
}
}
return 0;
}

DWORD _ReadMEM(DWORD dwPtr,DWORD A1,DWORD B1,DWORD C1)
{
	DWORD C=0;
	if (IsBadReadPtr((PDWORD)dwPtr,4)==0)
	{
		C=*(PDWORD)((DWORD)(dwPtr))+A1;
		if (IsBadReadPtr((PDWORD )C,4)==0)
		{
			C=*(PDWORD)((DWORD)(C ))+ B1;
			if (IsBadReadPtr((PDWORD)C,4)==0)
			{
				C=*(PDWORD)((DWORD)(C ))+ C1;
				if (IsBadReadPtr((PDWORD)C,4)==0)
				{
					return *(PDWORD)C; 
				}
			}
		}
	}
	return C;
}


void _WriteMEM(DWORD Adr, DWORD Ptr1, DWORD Ptr2, DWORD Ptr3, DWORD WriteValue)
{
	DWORD Temp=0;
	if (IsBadReadPtr((PDWORD)Adr, 4) == 0)
	{ 
		Temp = *(PDWORD)((DWORD)(Adr)) + Ptr1;
		if (IsBadReadPtr((PDWORD)Temp,4) == 0)
		{ 
			Temp = *(PDWORD)((DWORD)(Temp)) + Ptr2;
			if (IsBadReadPtr((PDWORD)Temp,4) == 0)
			{ 
				Temp = *(PDWORD)((DWORD)(Temp)) + Ptr3;
				if (IsBadReadPtr((PDWORD)Temp,4) == 0)
				{
					*(PDWORD)Temp = WriteValue;
				}
			}
		}
	}
}


BYTE Weapon,Pistol,Knife,Bomb,Smoke,Dual;
void __ReadMem(DWORD Base,DWORD Ofs1,DWORD Ofs2, DWORD Ofs3, int opt)
{
DWORD Temp =0;
if (IsBadReadPtr((PDWORD)Base,4)==0){
Temp=*(PDWORD)((DWORD)(Base))+Ofs1;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
Temp=*(PDWORD)((DWORD)(Temp))+Ofs2;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
Temp=*(PDWORD)((DWORD)(Temp))+Ofs3;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
switch (opt){
	                    case 1:
							Weapon = *(PBYTE)Temp;
						case 2:
							Pistol = *(PBYTE)Temp;
						case 3:
							Knife = *(PBYTE)Temp;
						case 4:
							Bomb = *(PBYTE)Temp;
						case 5:
							Smoke = *(PBYTE)Temp;
						case 6:
							Dual = *(PBYTE)Temp;
}}}}}}


void __WriteMem(DWORD Base,DWORD Ofs1,DWORD Ofs2, DWORD Ofs3, BYTE Value)
{ 
DWORD Temp=0;
if (IsBadReadPtr((PDWORD)Base,4)==0){
Temp=*(PDWORD)((DWORD)(Base))+Ofs1;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
Temp=*(PDWORD)((DWORD)(Temp))+Ofs2;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
Temp=*(PDWORD)((DWORD)(Temp))+Ofs3;
if (IsBadReadPtr((PDWORD)Temp,4)==0){
*(PBYTE)Temp=Value;
}}}}}

void  MakeJMP( BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen )
{
__try {
    DWORD dwOldProtect, dwBkup, dwRelAddr;
    VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    dwRelAddr = (DWORD) (dwJumpTo - (DWORD) pAddress) - 5;
    *pAddress = 0xE9;
    *((DWORD *)(pAddress + 0x1)) = dwRelAddr;
    for(DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
    VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
    return;
}__except ( EXCEPTION_EXECUTE_HANDLER ) {
	return ;
	}
}

void HideModule(HINSTANCE hModule)
{
        DWORD dwPEB_LDR_DATA = 0;
        _asm
        {
                pushad;
                pushfd;
                mov eax, fs:[30h]             
                mov eax, [eax+0Ch]               
                mov dwPEB_LDR_DATA, eax 

                InLoadOrderModuleList:
                        mov esi, [eax+0Ch]           
                        mov edx, [eax+10h]           

                LoopInLoadOrderModuleList: 
                    lodsd                        
                        mov esi, eax    
                        mov ecx, [eax+18h]  
                        cmp ecx, hModule        
                        jne SkipA                
                    mov ebx, [eax]        
                    mov ecx, [eax+4]  
                    mov [ecx], ebx    
                    mov [ebx+4], ecx      
                        jmp InMemoryOrderModuleList 

                SkipA:
                        cmp edx, esi     
                        jne LoopInLoadOrderModuleList

                InMemoryOrderModuleList:
                        mov eax, dwPEB_LDR_DATA
                        mov esi, [eax+14h]
                        mov edx, [eax+18h]

                LoopInMemoryOrderModuleList: 
                        lodsd
                        mov esi, eax
                        mov ecx, [eax+10h]
                        cmp ecx, hModule
                        jne SkipB
                        mov ebx, [eax] 
                        mov ecx, [eax+4]
                        mov [ecx], ebx
                        mov [ebx+4], ecx
                        jmp InInitializationOrderModuleList

                SkipB:
                        cmp edx, esi
                        jne LoopInMemoryOrderModuleList

                InInitializationOrderModuleList:
                        mov eax, dwPEB_LDR_DATA
                        mov esi, [eax+1Ch]        
                        mov edx, [eax+20h]        

                LoopInInitializationOrderModuleList: 
                        lodsd
                        mov esi, eax            
                        mov ecx, [eax+08h]
                        cmp ecx, hModule                
                        jne SkipC
                        mov ebx, [eax] 
                        mov ecx, [eax+4]
                        mov [ecx], ebx
                        mov [ebx+4], ecx
                        jmp Finished

                SkipC:
                        cmp edx, esi
                        jne LoopInInitializationOrderModuleList

                Finished:
                        popfd;
                        popad;
        }
}

#include <winternl.h>
typedef struct _PEB_LDR_DATA2  
	{ 
	  ULONG                   Length; 
	  BOOLEAN                 Initialized; 
	  PVOID                   SsHandle; 
	  LIST_ENTRY              InLoadOrderModuleList; 
	  LIST_ENTRY              InMemoryOrderModuleList; 
	  LIST_ENTRY              InInitializationOrderModuleList; 
	}PEB_LDR_DATA2, *PPEB_LDR_DATA2; 

	typedef struct _LDR_MODULE
	{
	  LIST_ENTRY              InLoadOrderModuleList; 
	  LIST_ENTRY              InMemoryOrderModuleList; 
	  LIST_ENTRY              InInitializationOrderModuleList; 
	  PVOID                   BaseAddress; 
	  PVOID                   EntryPoint; 
	  ULONG                   SizeOfImage; 
	  UNICODE_STRING          FullDllName; 
	  UNICODE_STRING          BaseDllName; 
	  ULONG                   Flags; 
	  SHORT                   LoadCount; 
	  SHORT                   TlsIndex; 
	  LIST_ENTRY              HashTableEntry; 
	  ULONG                   TimeDateStamp; 
	}LDR_MODULE, *PLDR_MODULE;

void UnlinkModule(char *szModule)
	{
		DWORD dwPEB = 0, dwOffset = 0;
		PLIST_ENTRY pUserModuleHead, pUserModule;
		PPEB_LDR_DATA2 pLdrData;
		PUNICODE_STRING lpModule;
		char szModuleName[512];
		int i = 0, n = 0;

		_asm
		{
			pushad
				mov eax, fs: [48]
				mov dwPEB, eax
			popad
		}

		pLdrData= ( PPEB_LDR_DATA2 )(PDWORD)(*(PDWORD)(dwPEB + 12)); 

		for (; i < 3; i++)
		{
			switch (i)
			{
				case 0:
					pUserModuleHead = pUserModule = ( PLIST_ENTRY ) ( &( pLdrData->InLoadOrderModuleList ) ); 
					dwOffset = 0;
					break;
				
				case 1:
					pUserModuleHead = pUserModule = ( PLIST_ENTRY ) ( &( pLdrData->InMemoryOrderModuleList ) );
					dwOffset = 8;
					break;
				case 2:
					pUserModuleHead = pUserModule = (PLIST_ENTRY) (&(pLdrData->InInitializationOrderModuleList));
					dwOffset = 16;
					break;
			}

			while (pUserModule->Flink != pUserModuleHead)
			{
				pUserModule = pUserModule->Flink;
				lpModule = (PUNICODE_STRING)(((DWORD)(pUserModule)) + (36-dwOffset));
				
				for (n = 0; n < (lpModule->Length)/2 && n < 512; n++)  
					szModuleName[n] = (CHAR)(* ((lpModule->Buffer)+(n))); 
				
				szModuleName[n] = '\0';
				//DbgPrint ("Found Module: %s\n", szModuleName);
				if (strstr (szModuleName, szModule))
				{
					pUserModule->Blink->Flink = pUserModule->Flink;
					pUserModule->Flink->Blink = pUserModule->Blink;
				}
			}
		}
	}
/*------------------------------------------- Declaration Eraser Module ------------------------------------------------------*/
void EraseHeaders(HINSTANCE hModule)
{
	PIMAGE_DOS_HEADER pDoH; 
	PIMAGE_NT_HEADERS pNtH;
	DWORD i, ersize, protect;
	if (!hModule) return;
	pDoH = (PIMAGE_DOS_HEADER)(hModule);
	pNtH = (PIMAGE_NT_HEADERS)((LONG)pDoH + pDoH->e_lfanew);
	ersize = sizeof(IMAGE_DOS_HEADER);
	
	if(VirtualProtect(pDoH, ersize, PAGE_READWRITE, &protect) != 0)
	{
		for(i = 0; i < ersize + 150; i++)
			*(PBYTE)((PBYTE)pDoH + i) = 0;
	}
	ersize = sizeof(IMAGE_NT_HEADERS);
	
	if(pNtH && VirtualProtect(pNtH, ersize, PAGE_READWRITE, &protect) != 0)
	{
		for(i = 0; i < ersize; i++)
			*(PBYTE)((PBYTE)pNtH + i) = 0;
	}
	return;
}