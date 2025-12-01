#include <Windows.h>

DWORD *NewFuctX;
DWORD OldProtect;
DWORD KillEhSvc;
LPDIRECT3DDEVICE9 NewDevice;

BOOL NewMemoryX( DWORD dwAddress, const void* cpvPatch, DWORD dwSize )
{
DWORD dwProtect;
if( VirtualProtect( (void*)dwAddress, dwSize, PAGE_READWRITE, &dwProtect ) ) //Unprotect the memory
memcpy( (void*)dwAddress, cpvPatch, dwSize ); 
else
return false; //Failed to unprotect, so return false..
return VirtualProtect( (void*)dwAddress, dwSize, dwProtect, new DWORD ); //Reprotect the memory
}
int WriteHook(LPVOID Device , LPCVOID Addres , int Size)
{
			DWORD OldProtect;
			VirtualProtect((void*)(Addres), Size, PAGE_EXECUTE_READWRITE, &OldProtect);
			memcpy(Device, (void *)Addres, Size);
			VirtualProtect((void*)(Addres), Size, OldProtect, NULL);
			return true;
}
BOOL NewFuntionE9( DWORD From, DWORD To )
{
BYTE bpJump2[2] = { 0xEB, (BYTE)(0xFF - ((From - To) + 1)) }; 
BYTE bpJump[2] = { 0xEB, (BYTE)((To - From) - 2)};
BYTE bpJump1[5] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };


if( To < From + 128 && To > From - 128 ) 
if(To > From)
return NewMemoryX( From, bpJump, 2 );
else  
return NewMemoryX( From, bpJump2, 2 );
else 
if(To > From)  
*(DWORD*)&bpJump1[1] = To - (From + 5); 
 else 
*(DWORD*)&bpJump1[1] = (0xFFFFFFFF - (From + 4)) + To; 
return NewMemoryX( From, bpJump1, 5 );
return false; 
}

DWORD ProtecGfx=0;
DWORD ReadDevc (DWORD ALAY1,DWORD ALAY2)
{

if(IsBadReadPtr((PDWORD)(ALAY1),4)==0) 
ProtecGfx=*(PDWORD)((DWORD)(ALAY1))+ALAY2; 
if(IsBadReadPtr((PDWORD)ProtecGfx,4)==0) 
return *(PDWORD)ProtecGfx;

return ProtecGfx;
}

void *DetourCreate(BYTE *src, const BYTE *dst, const int len)
{
	BYTE *jmp = (BYTE*)malloc(len+5);
	DWORD dwBack;

	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwBack);
	memcpy(jmp, src, len);	
	jmp += len;
	jmp[0] = 0xE9;
	*(DWORD*)(jmp+1) = (DWORD)(src+len - jmp) - 5;
	src[0] = 0xE9;
	*(DWORD*)(src+1) = (DWORD)(dst - src) - 5;
	for (int i=5; i<len; i++)  src[i]=0x90;
	VirtualProtect(src, len, dwBack, &dwBack);
	return (jmp-len);
}