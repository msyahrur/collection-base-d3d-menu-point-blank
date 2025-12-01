
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//--        // Created By : MhmmdYogiSaputra                                                               --  
//--        // Facebook   : https://www.facebook.com/gigntng                                               --
//--        // Youtube    : https://www.youtube.com/channel/UCoCztOogokhBSJoAFWiW1yA                       --
//--       // Website    : http://www.pintercit.me/                                                        --
//--                                                                                                       --
//--        // CopyRight 2018  ( Woy Ngentod Jangan Di Ganti CopyRight Dan Created Hargain Anjing Kontol ) --
//--                                                                                                       -- 
//------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//--------------------------------- Get Battle State -----------------------
/*
Fungsi : Mendapatkan informasi apakah user sedang bertanding di dalam pertandingan atau tidak
Dengan memanfaatkan Base CGameCharaBase, apabila Base Pointer valid, maka Pemain sedang di dalam pertandingan
Class yang digunakan : CGameCharaBase
*/
bool IsInBattle()
{
	if(pGameCharaManager->getLocalChara() > NULL)return true;
	return false;
}

void _patchPTR(unsigned long adr, unsigned long Ofset1, DWORD dwValue)
{ 
	DWORD A=0;
	if(IsBadReadPtr((PDWORD)adr,4))return;
	A=*(PDWORD)((DWORD)(adr))+Ofset1;
	if(IsBadReadPtr((PDWORD)A,4))return;
	if(*(PDWORD)A!=dwValue)*(PDWORD)A=dwValue;
}

inline void MakeJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen)
{
    DWORD dwOldProtect, dwBkup, dwRelAddr;
	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	dwRelAddr = (DWORD)(dwJumpTo - (DWORD)pAddress) - 5;
	*pAddress = 0xE9;
	*((DWORD *)(pAddress + 0x1)) = dwRelAddr;
	for (DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
	return;
}

void _patchPTR(unsigned long adr, unsigned long Ofset1, unsigned long Ofset2, DWORD dwValue)
{ 
	DWORD A=0;
	if(IsBadReadPtr((PDWORD)adr,4))return;
	A=*(PDWORD)((DWORD)(adr))+Ofset1;
	if(IsBadReadPtr((PDWORD)A,4))return;
	A=*(PDWORD)((DWORD)(A))+Ofset2;
	if(IsBadReadPtr((PDWORD)A,4))return;
	if(*(PDWORD)A!=dwValue)*(PDWORD)A=dwValue;
}

VOID JMPE9(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen)
{
    DWORD dwOldProtect, dwBkup, dwRelAddr;
    VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    dwRelAddr = (DWORD) (dwJumpTo - (DWORD) pAddress) - 5;
    *pAddress = 0xE9;
    *((DWORD *)(pAddress + 0x1)) = dwRelAddr;
    for(DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
    VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
    return;
}

int WriteHook(LPVOID Device , LPCVOID Addres , int Size)
{
	__try
	{
		DWORD OldProtect;
		VirtualAlloc	((void*)Addres, Size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		VirtualProtect	((void*)(Addres), Size, PAGE_EXECUTE_READWRITE, &OldProtect);
		VirtualProtectEx(GetCurrentProcess(),(void*)Addres, Size, PAGE_EXECUTE_READWRITE, &OldProtect);		
		memcpy(Device,	(void *)Addres, Size);
		VirtualProtect	((void*)(Addres), Size, OldProtect,&OldProtect); 
		VirtualProtectEx(GetCurrentProcess(),(void*)Addres, Size, OldProtect, &OldProtect );
		return true;
		}
	__except (EXCEPTION_EXECUTE_HANDLER){
		return false;
	}
}

DWORD WritePTR(DWORD Base,DWORD PTR1,DWORD Byte){ 
if (!IsBadReadPtr((PDWORD)Base,4)){DWORD RPTR1=*(PDWORD)((DWORD)(Base))+PTR1;
if (!IsBadReadPtr((PDWORD)RPTR1,4)){*(PDWORD)RPTR1=Byte;}}
return 0;
}

void MemWrite(void *adr, void *byte, int size)
{
	DWORD X;
    VirtualProtect(adr, size, PAGE_EXECUTE_READWRITE, &X);
	memcpy(adr, byte, size);   
    VirtualProtect(adr,size,X,&X);
}

bool IsAliveDeath(int Index)
{
	if (!pGameContext->getUserDeath(Index) && pGameContext->getMySlotIdx() != Index){
		if (pGameContext->getMySlotIdx() %2 != Index % 2){
			return true; 
		}
	}
	return false;
}

int GetTeamX(char MyTeam)
{
	for(int i = 0; i < 16; i+=2)
		if(i == MyTeam)return 2;
	for(int i = 1; i < 16; i+=2)
		if(i == MyTeam)return 1;
	return -1;
}

int cTeamFind(int iSlot) 
{ 
	__try
	{
		if (iSlot%2 == 0) 
			return 1; 
		else 
			return 2; 
	}__except ( EXCEPTION_EXECUTE_HANDLER ) {return 0;}
}

DWORD FindDmaAddy(int PointerLevel, DWORD Offsets[], DWORD BaseAddress)
{
	DWORD Ptr = (DWORD)(BaseAddress);
	if(Ptr == 0) return NULL;
	for(int i = 0; i < PointerLevel; i ++)
	{
		if(i == PointerLevel-1)
		{
			Ptr = (DWORD)(Ptr+Offsets[i]);
			if(Ptr == 0) return NULL;
			return Ptr;
		}
		else
		{
			Ptr = *(DWORD*)(Ptr+Offsets[i]);
			if(Ptr == 0) return NULL;
		}
	}
	return Ptr;
}

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

void _patchPTR(unsigned long adr, unsigned long Ofset1, unsigned long Ofset2, unsigned long Ofset3, DWORD dwValue)
{ 
	DWORD A=0;
	if(IsBadReadPtr((PDWORD)adr,4))return;
	A=*(PDWORD)((DWORD)(adr))+Ofset1;
	if(IsBadReadPtr((PDWORD)A,4))return;
	A=*(PDWORD)((DWORD)(A))+Ofset2;
	if(IsBadReadPtr((PDWORD)A,4))return;
	A=*(PDWORD)((DWORD)(A))+Ofset3;
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

DWORD _readPTR(unsigned long adr, unsigned long Ofset1, unsigned int dwSize)
{ 
	DWORD A=0;
	if(IsBadReadPtr((PDWORD)adr,4))return NULL;
	A=*(PDWORD)((DWORD)(adr))+Ofset1;
	if(IsBadReadPtr((PDWORD)A,4))return NULL;
	switch(dwSize)
	{
	case 1:
		return *(BYTE*)(A);
		break;
	case 2:
		return *(WORD*)(A);
		break;
	case 4:
		return *(DWORD*)(A);
		break;
	}
	return NULL;
}

DWORD _readPTR(unsigned long adr, unsigned long Ofset1, unsigned long Ofset2, unsigned int dwSize)
{ 
	DWORD A=0;
	if(IsBadReadPtr((PDWORD)adr,4))return NULL;
	A=*(PDWORD)((DWORD)(adr))+Ofset1;
	if(IsBadReadPtr((PDWORD)A,4))return NULL;
	A=*(PDWORD)((DWORD)(A))+Ofset2;
	if(IsBadReadPtr((PDWORD)A,4))return NULL;
	switch(dwSize)
	{
	case 1:
		return *(BYTE*)(A);
		break;
	case 2:
		return *(WORD*)(A);
		break;
	case 4:
		return *(DWORD*)(A);
		break;
	}
	return NULL;
}

DWORD _readPTR(unsigned long adr, unsigned long Ofset1, unsigned long Ofset2, unsigned long Ofset3, unsigned int dwSize)
{ 
	DWORD A=0;
	if(IsBadReadPtr((PDWORD)adr,4))return NULL;
	A=*(PDWORD)((DWORD)(adr))+Ofset1;
	if(IsBadReadPtr((PDWORD)A,4))return NULL;
	A=*(PDWORD)((DWORD)(A))+Ofset2;
	if(IsBadReadPtr((PDWORD)A,4))return NULL;
	A=*(PDWORD)((DWORD)(A))+Ofset3;
	if(IsBadReadPtr((PDWORD)A,4))return NULL;
	switch(dwSize)
	{
	case 1:
		return *(BYTE*)(A);
		break;
	case 2:
		return *(WORD*)(A);
		break;
	case 4:
		return *(DWORD*)(A);
		break;
	}
	return NULL;
}

DWORD _readPTR(unsigned long adr, unsigned long Ofset1, unsigned long Ofset2, unsigned long Ofset3, unsigned long Ofset4, unsigned int dwSize)
{ 
	DWORD A=0;
	if(IsBadReadPtr((PDWORD)adr,4))return NULL;
	A=*(PDWORD)((DWORD)(adr))+Ofset1;
	if(IsBadReadPtr((PDWORD)A,4))return NULL;
	A=*(PDWORD)((DWORD)(A))+Ofset2;
	if(IsBadReadPtr((PDWORD)A,4))return NULL;
	A=*(PDWORD)((DWORD)(A))+Ofset3;
	if(IsBadReadPtr((PDWORD)A,4))return NULL;
	A=*(PDWORD)((DWORD)(A))+Ofset4;
	if(IsBadReadPtr((PDWORD)A,4))return NULL;
	switch(dwSize)
	{
	case 1:
		return *(BYTE*)(A);
		break;
	case 2:
		return *(WORD*)(A);
		break;
	case 4:
		return *(DWORD*)(A);
		break;
	}
	return NULL;
}

void _patchMEM(void* MemoryTarget, char* Value,int len)
{
	DWORD dwOldProtect, dwBkup;
    VirtualProtect(MemoryTarget, len, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	memcpy((void*)MemoryTarget,(void*)Value,len);
    VirtualProtect(MemoryTarget, len, dwOldProtect, &dwBkup);
}

void _patchMEM(void *Addres, int Byte)
{
	__try {
		DWORD OldProtect;
		VirtualProtect(Addres, Byte, PAGE_EXECUTE_READWRITE, &OldProtect);
		*(BYTE*)Addres=Byte;
		VirtualProtect(Addres, Byte, PAGE_EXECUTE_READWRITE,&OldProtect);
	}__except (EXCEPTION_EXECUTE_HANDLER){} 
}

void *DetourFunction (BYTE *src, const BYTE *dst, const int len)
{
    BYTE *jmp;
    DWORD dwback;
    DWORD jumpto, newjump;

    VirtualProtect(src,len,PAGE_READWRITE,&dwback);
    
    if(src[0] == 0xE9)
    {
        jmp = (BYTE*)malloc(10);
        jumpto = (*(DWORD*)(src+1))+((DWORD)src)+5;
        newjump = (jumpto-(DWORD)(jmp+5));
        jmp[0] = 0xE9;
       *(DWORD*)(jmp+1) = newjump;
        jmp += 5;
        jmp[0] = 0xE9;
       *(DWORD*)(jmp+1) = (DWORD)(src-jmp);
    }
    else
    {
        jmp = (BYTE*)malloc(5+len);
        memcpy(jmp,src,len);
        jmp += len;
        jmp[0] = 0xE9;
       *(DWORD*)(jmp+1) = (DWORD)(src+len-jmp)-5;
    }
    src[0] = 0xE9;
   *(DWORD*)(src+1) = (DWORD)(dst - src) - 5;

    for(int i = 5; i < len; i++)
        src[i] = 0x90;
    VirtualProtect(src,len,dwback,&dwback);
    return (jmp-len);
}

DWORD MakePTR(BYTE *MemoryTarget, DWORD FunctionTarget)
{
	//XFiles make PTR
	//2014 FahmyXFiles
	DWORD dwOldProtect,dwBkup;
	DWORD dwRetn = *(DWORD*)(MemoryTarget);

	VirtualProtect(MemoryTarget, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*((DWORD *)(MemoryTarget)) = FunctionTarget;
	VirtualProtect(MemoryTarget, 4, dwOldProtect, &dwBkup);
	return dwRetn;
}

DWORD hook(PDWORD target, PDWORD myFunction)
{
	DWORD Jmpto=((DWORD)(myFunction)-(DWORD)target)-5;
	DWORD a;
	VirtualProtect(target, 5, PAGE_EXECUTE_READWRITE, &a);
	*(PBYTE)((DWORD)(target))=0xE9;
	*(PDWORD)((DWORD)(target)+1)=Jmpto;
	VirtualProtect(target, 5, a, &a);
	return false;
}

DWORD DetourB8( DWORD SrcVA, DWORD DstVA, DWORD Size )
{
	DWORD DetourVA, dwProtect, i;
	#define SIZEOF_MOVEAX_JMPEAX 7
	if ( SrcVA && DstVA && Size >= SIZEOF_MOVEAX_JMPEAX )
	{
		DetourVA = (DWORD) VirtualAlloc( 
		NULL, Size + SIZEOF_MOVEAX_JMPEAX, 
		MEM_COMMIT, PAGE_EXECUTE_READWRITE );
		if ( DetourVA && VirtualProtect( (VOID*)SrcVA, Size, PAGE_EXECUTE_READWRITE, &dwProtect ) )
		{
			for ( i=0; i < Size; i++ ) {
			*(BYTE*)( DetourVA + i ) = *(BYTE*)( SrcVA + i );
			}
			*(BYTE*)( DetourVA + Size + 0 ) = 0xB8;
			*(DWORD*)( DetourVA + Size + 1 ) = ( SrcVA + Size );
			*(WORD*)( DetourVA + Size + 5 ) = 0xE0FF;
			*(BYTE*)( SrcVA + 0 ) = 0xB8;
			*(DWORD*)( SrcVA + 1 ) = ( DstVA );
			*(WORD*)( SrcVA + 5 ) = 0xE0FF;
			VirtualProtect( (VOID*)SrcVA, Size, dwProtect, &dwProtect );
			VirtualProtect( (VOID*)DetourVA, Size + 
			SIZEOF_MOVEAX_JMPEAX, PAGE_EXECUTE_READ, &dwProtect );
			return DetourVA;
		}
	}
return (0);
}

void hexDump (char *desc, void *addr, int len, FILE* pFile) {
    int i;
    unsigned char buff[17];       // stores the ASCII data
    unsigned char *pc = (unsigned char*)addr;     // cast to make the code cleaner.

    // Output description if given.

    if (desc != NULL)
        fprintf (pFile, "%s:\n", desc);

    // Process every byte in the data.

    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.

            if (i != 0)
                fprintf (pFile, "  %s\n", buff);

            // Output the offset.

            fprintf (pFile, "  %04x ", i);
        }

        // Now the hex code for the specific character.

        fprintf (pFile, " %02x", pc[i]);

        // And store a printable ASCII character for later.

        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.

    while ((i % 16) != 0) {
        fprintf (pFile, "   ");
        i++;
    }

    // And print the final ASCII bit.

    fprintf (pFile, "  %s\n", buff);
}

string hexDump (char *desc, void *addr, int len) {
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;
	char szPrntBuffer[100];
	string output;

	if(IsBadReadPtr((void*)addr,4))
	{
		sprintf (szPrntBuffer,"%s: 0x0", desc);
		output += szPrntBuffer;
		return output;
	}
    // Output description if given.
    if (desc != NULL){
        sprintf (szPrntBuffer,"%s:\n", desc);
		output += szPrntBuffer;
	}

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0){
                sprintf (szPrntBuffer,"  %s\n", buff);
				output += szPrntBuffer;
			}

            // Output the offset.
            sprintf (szPrntBuffer,"  %08X ", (int)addr + i);
			output += szPrntBuffer;
        }

        // Now the hex code for the specific character.
        sprintf (szPrntBuffer," %02x", pc[i]);
		output += szPrntBuffer;

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        sprintf (szPrntBuffer,"   ");
		output += szPrntBuffer;
        i++;
    }

    // And print the final ASCII bit.
    sprintf (szPrntBuffer,"  %s", buff);
	output += szPrntBuffer;
	return output;
}

DWORD GenerateRandomNumber_(int min, int max)
{
	
	SYSTEMTIME pTime = {0};
	GetSystemTime(&pTime);
	
	int randNum = pTime.wMilliseconds * rand()%(max-min + 1) + min;
	return randNum;
}

char* GenerateRandomString_(const int len) {
	char* s = new char[len];
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[GenerateRandomNumber_(20,50) % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
	return s;
}

//bool bPatchWallShot = false;
//void EnableWallShot()
//{
//	if(!bPatchWallShot){
//		DWORD Function = AddyEngine->GetAddyValueByKey(/*XFHPB.Function.SetHitCollision*/XorStr<0x29,31,0xe184be23>("\x71\x6c\x63\x7c\x6f\x00\x69\x45\x5f\x51\x47\x5d\x5a\x58\x19\x6b\x5c\x4e\x73\x55\x49\x7d\x50\x2c\x2d\x2b\x30\x2d\x2a\x28"+0xe184be23).s);
//		_patchMEM((void*)(Function + 10),(char*)"\xEB",1);
//		_patchMEM((void*)(Function + 28),(char*)"\xEB",1);
//		_patchMEM((void*)(Function + 54),(char*)"\xEB",1);
//		bPatchWallShot = true;
//	}
//	
//}
//void DisableWallShot()
//{
//	if(bPatchWallShot){
//		DWORD Function = AddyEngine->GetAddyValueByKey(/*XFHPB.Function.SetHitCollision*/XorStr<0x6c,31,0x9052aed6>("\x34\x2b\x26\x3f\x32\x5f\x34\x06\x1a\x16\x02\x1e\x17\x17\x54\x28\x19\x09\x36\x16\xf4\xc2\xed\xef\xe8\xec\xf5\xee\xe7\xe7"+0x9052aed6).s);
//		_patchMEM((void*)(Function + 10),(char*)"\x74",1);
//		_patchMEM((void*)(Function + 28),(char*)"\x74",1);
//		_patchMEM((void*)(Function + 54),(char*)"\x74",1);
//		bPatchWallShot = false;
//	}
//}

//void FireBulletOnTarget(CGameCharaBase* Target)
//{	
//	CGameCharaBase* LocalChara = pGameCharaManager->getLocalChara();
//
//	DWORD CurrentWeaponIdx = LocalChara->getGameCharaWeaponContext()->getCurrentWeaponIndex();
//	//if(CurrentWeaponIdx == 2)return;
//
//	CWeaponBase* CurrentWeapon = LocalChara->getGameCharaWeaponContext()->getCurrentWeapon();
//
//	D3DXVECTOR3 SourcePos = LocalChara->getGameCharaBoneContext()->getBonePosition(5);
//	D3DXVECTOR3 TargetPos = Target->getGameCharaBoneContext()->getBonePosition(BoneIndexSelector);
//	TargetPos.y += 0.1f;
//	
//	DWORD OptTeam = 2;
//	if(pGameContext->isRedTeam(Target->getCharaNetIndex()))OptTeam = 1;
//	
//	
//	SetEndVector->SetTargetVector(TargetPos);
//	CurrentWeapon->doFire();
//	SetEndVector->Disable();
//	//pGameUDPHandler->WriteGameEvent_Fire(LocalChara, &TargetPos, CurrentWeapon);
//	//CurrentWeapon->doLineCollision(&SourcePos, &TargetPos, OptTeam);
//
//}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//--        // Created By : MhmmdYogiSaputra                                                               --  
//--        // Facebook   : https://www.facebook.com/gigntng                                               --
//--        // Youtube    : https://www.youtube.com/channel/UCoCztOogokhBSJoAFWiW1yA                       --
//--       // Website    : http://www.pintercit.me/                                                        --
//--                                                                                                       --
//--        // CopyRight 2018  ( Woy Ngentod Jangan Di Ganti CopyRight Dan Created Hargain Anjing Kontol ) --
//--                                                                                                       -- 
//------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
