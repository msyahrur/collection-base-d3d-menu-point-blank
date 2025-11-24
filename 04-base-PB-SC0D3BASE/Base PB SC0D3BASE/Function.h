//CREATED BY SC0D3 Solusi Game No Di Indoneisa
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
			}else{
			Ptr = *(DWORD*)(Ptr+Offsets[i]);
			if(Ptr == 0) return NULL;
		}
	}
	return Ptr;
}

//bool IsAliveDeath(int Index)
//{
//	if (!pGameContext->getUserDeath(Index) && pGameContext->setMySlotIdx() != Index){
//		if (pGameContext->setMySlotIdx() %2 != Index % 2){
//			return true; 
//		}
//	}
//	return false;
//}
//bool IsAliveDeath(int Index)
//{
//	if (!pGameContext->getUserDeath(Index) && pGameContext->setMySlotIdx() != Index){
//		if (pGameContext->setMySlotIdx() %2 != Index % 2){
//			return true; 
//		}
//	}
//	return false;
//}

void PacthHook(void *adr, void *ptr, int size)
{
	DWORD CheckProtection = 0;
	VirtualProtect(adr,size,PAGE_EXECUTE_READWRITE, &CheckProtection);
	RtlMoveMemory(adr,ptr,size);
	VirtualProtect(adr,size,CheckProtection, &CheckProtection);
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
float LongJumperDist;
bool JumperDist = false;
bool JumperDist2 = false;
DWORD pUpdateJumpJMP;
_declspec (naked) void JumperThread()
{
	if (JumperDist == true)
	{
		__asm
		{
			fld dword ptr[LongJumperDist]
				mov esp, ebp
				jmp dword ptr[pUpdateJumpJMP]
		}
	}
	__asm
	{
		fld dword ptr[ebp - 04]
			mov esp, ebp
			jmp dword ptr[pUpdateJumpJMP]
	}
}

DWORD GetSizeofCode( const char* szModuleName ) 
{ 
	HMODULE hModule = GetModuleHandleA( szModuleName ); 
	if ( !hModule ) return 0; 
	PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER( hModule ); 
	if( !pDosHeader ) return 0; 
	PIMAGE_NT_HEADERS pNTHeader = PIMAGE_NT_HEADERS( (LONG)hModule + pDosHeader->e_lfanew ); 
	if( !pNTHeader ) return 0; 
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pNTHeader->OptionalHeader; 
	if( !pOptionalHeader ) return 0; 
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

DWORD FindPattern(DWORD dwdwAdd,DWORD dwLen,DWORD Address)
{
    for(DWORD i=0; i<dwLen; i++)
        if (*(PDWORD)(dwdwAdd+i)==Address)
			return (DWORD)(dwdwAdd+i);
    return 0;
}

BOOL  bCompare ( const BYTE* pData, const BYTE* bMask, const char* szMask )
{
    for ( ;*szMask; ++szMask, ++pData, ++bMask )
    {
        if ( *szMask == 'x' && *pData != *bMask )
             return 0;
    }
    return (*szMask) == NULL;
}

DWORD FindPattern ( DWORD dwStartAddress,DWORD dwSize, BYTE *bMask, char * szMask, int codeOffset, BOOL extract )
{ 
    for ( DWORD i = 0; i < dwSize; i++ )
    {
        if (bCompare((BYTE*)(dwStartAddress + i),bMask,szMask) )
        {
            if ( extract )  
            {
                return *(DWORD*)(dwStartAddress+i+codeOffset);
 
            } else {
 
                return  (DWORD)(dwStartAddress+i+codeOffset);
            }
        }
    }
    return NULL;
}

MODULEINFO GetModuleInfo( char *szModule )
{
    MODULEINFO modinfo = {0};
    HMODULE hModule = GetModuleHandleA(szModule);
    if(hModule == 0) 
        return modinfo;
    GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
    return modinfo;
}

DWORD FindAddres(char *module,DWORD Address)
{    

    MODULEINFO mInfo = GetModuleInfo(module);


    DWORD base = (DWORD)mInfo.lpBaseOfDll;
    DWORD size =  (DWORD)mInfo.SizeOfImage;

	for(DWORD i=0; i<size; i++)
        if (*(PDWORD)(base+i)==Address)
			return (DWORD)(base+i);
    return 0;
}

DWORD FindAddresModule(char *module, char *pattern, char *mask)
{

    MODULEINFO mInfo = GetModuleInfo(module);

    DWORD base = (DWORD)mInfo.lpBaseOfDll;
    DWORD size =  (DWORD)mInfo.SizeOfImage;

    DWORD patternLength = (DWORD)strlen(mask);

    for(DWORD i = 0; i < size - patternLength; i++)
    {
        bool found = true;
        for(DWORD j = 0; j < patternLength; j++)
        {
            found &= mask[j] == '?' || pattern[j] == *(char*)(base + i + j);
        }
        if(found) 
        {
            return base + i;
        }
    }

    return NULL;
}

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

DWORD PUSH_STR_PB(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask,char * szMask)
{
	DWORD STR = FindPattern((DWORD)dwdwAdd						,(DWORD)dwLen		,(PBYTE)bMask,szMask); 
	if(STR!=NULL)
	{
		DWORD PUSH = FindPattern((DWORD)dwStartAddress,(DWORD)dwSize		,STR)-1;
		if(PUSH!=NULL)
		{
			return PUSH;
		}
	}
return 0;
}

class sAddy
{
public:
	char Key[100];
	DWORD Value;
	sAddy(char* Key, DWORD Value)
	{
		strcpy(this->Key, Key);
		this->Value = Value;
	}
};

enum AddyType
{
	ADDY_NORMAL = 0,
	ADDY_STRING = 1,
	ADDY_FUNCTION_GETCALL = 2,
	ADDY_FUNCTION_GETJMP = 3,
	ADDY_FUNCTION_FINDSTART = 4,
	ADDY_FUNCTION_FINDEND = 5,
	ADDY_FUNCTION_FINDNEXT = 6,
	ADDY_FUNCTION_FINDPREV = 7,
	ADDY_GET_VALUE = 8

};

class cAddyEngine
{
private:
	vector<sAddy> AddyList;
	MODULEINFO GetModuleInfo ( LPCTSTR lpModuleName );
	DWORD FindPattern( DWORD rangeStart, DWORD rangeEnd, const char* pattern );
public:
	virtual sAddy* FindAddyByPattern(char* Key, char* ModuleName, char* Pattern);
	virtual sAddy* ParseAddyByOption(sAddy* Addy, enum AddyType, DWORD Align, DWORD AlignSize);
	virtual void AddAddyByValue(char* Key, DWORD Value);
	virtual void AddAddyByValue(char* Key, enum AddyType, DWORD Align, DWORD AlignSize, DWORD Value);
	virtual void AddAddyByPattern(char* Key, enum AddyType, DWORD Align, DWORD AlignSize, char* ModuleName, char* Pattern);

	virtual int GetAddySize();
	virtual sAddy* GetAddyByIndex(int Index);
	virtual sAddy* GetAddyByKey(char* Key);
	virtual DWORD GetAddyValueByKey(char* Key);
};

MODULEINFO cAddyEngine::GetModuleInfo ( LPCTSTR lpModuleName )
{
	MODULEINFO miInfos = { NULL };
    HMODULE hPSAPI_module;

    if(!GetModuleHandleA(/*psapi.dll*/XorStr<0x7F,10,0x2D6771B8>("\x0F\xF3\xE0\xF2\xEA\xAA\xE1\xEA\xEB"+0x2D6771B8).s))
    {
        
        char szSystemPath[MAX_PATH];
        GetWindowsDirectory(szSystemPath, MAX_PATH);
        char szPSAPIDLLPath[MAX_PATH];
        sprintf(szPSAPIDLLPath, /*%s\\system32\\psapi.dll*/XorStr<0xD3,22,0x817F5100>("\xF6\xA7\x89\xA5\xAE\xAB\xAD\xBF\xB6\xEF\xEF\x82\xAF\x93\x80\x92\x8A\xCA\x81\x8A\x8B"+0x817F5100).s, szSystemPath);
		hPSAPI_module =  LoadLibrary(szPSAPIDLLPath);
        
    }
    else
        hPSAPI_module = GetModuleHandleA(/*psapi.dll*/XorStr<0x7F,10,0x2D6771B8>("\x0F\xF3\xE0\xF2\xEA\xAA\xE1\xEA\xEB"+0x2D6771B8).s);

    if (!hPSAPI_module)
        return miInfos;

	HMODULE hmModule = GetModuleHandle(lpModuleName); 
 
    typedef DWORD ( __stdcall *tGetModuleInformation)( HANDLE, HMODULE, LPMODULEINFO, DWORD );
    tGetModuleInformation oGetModuleInformation = (tGetModuleInformation) (GetProcAddress(hPSAPI_module, /*GetModuleInformation*/XorStr<0x35,21,0x3BDB8E31>("\x72\x53\x43\x75\x56\x5E\x4E\x50\x58\x77\x51\x26\x2E\x30\x2E\x25\x31\x2F\x28\x26"+0x3BDB8E31).s));
    oGetModuleInformation(GetCurrentProcess(), hmModule, &miInfos, sizeof ( MODULEINFO ));

    return miInfos;
}

#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
DWORD cAddyEngine::FindPattern( DWORD rangeStart, DWORD rangeEnd, const char* pattern )
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

sAddy* cAddyEngine::FindAddyByPattern(char* Key, char* ModuleName, char* Pattern)
{
	sAddy* NewAddy = new sAddy(Key, NULL);
	MODULEINFO mTarget = this->GetModuleInfo(ModuleName);
	if(mTarget.SizeOfImage == NULL){
		sprintf(NewAddy->Key, /*%s (ERR : EXECUTEABLE_NOT_FOUND)*/XorStr<0x29,33,0xe184be23>("\x0c\x59\x0b\x04\x68\x7c\x7d\x10\x0b\x12\x76\x6c\x70\x75\x62\x6c\x7c\x7b\x79\x70\x78\x61\x71\x0f\x15\x1d\x05\x0b\x10\x08\x03\x61"+0xe184be23).s, Key);
		return NewAddy;
	}

	DWORD Search = this->FindPattern((DWORD)mTarget.lpBaseOfDll, (DWORD)mTarget.lpBaseOfDll + (DWORD)mTarget.SizeOfImage, Pattern);
	if(Search == NULL){
		sprintf(NewAddy->Key, /*%s (ERR : ADDY_NOT_FOUND)*/XorStr<0x6c,26,0x9052aed6>("\x49\x1e\x4e\x47\x35\x23\x20\x53\x4e\x55\x37\x33\x3c\x20\x25\x35\x33\x29\x21\x39\xcf\xd4\xcc\xc7\xad"+0x9052aed6).s, Key);
		return NewAddy;
	}
	NewAddy->Value = Search;
	return NewAddy;
}

sAddy* cAddyEngine::ParseAddyByOption(sAddy* Addy,AddyType eAddyType, DWORD Align, DWORD AlignSize)
{

	DWORD Search = Addy->Value;
	DWORD CallPosition, CallDifference, JumpPosition, JumpDifference = NULL;
	if(Search == NULL){
		sprintf(Addy->Key, /*%s (ERR : ADDY_NOT_FOUND)*/XorStr<0x49,26,0xe9bbf1f1>("\x6c\x39\x6b\x64\x08\x1c\x1d\x70\x6b\x72\x12\x10\x11\x0f\x08\x16\x16\x0e\x04\x1a\x12\x0b\x11\x24\x48"+0xe9bbf1f1).s, Addy->Key);
		return Addy;
	}
	switch(eAddyType)
	{
	case ADDY_NORMAL:
		Addy->Value = Search + Align;
		break;
	case ADDY_FUNCTION_GETCALL:
		CallPosition = Search + Align;
		CallDifference = *(DWORD*)(CallPosition + 1);
		if(*(BYTE*)(CallPosition) != 0xE8){
			sprintf(Addy->Key, /*%s (ERR : INVALID_ALIGN_TO_CALL)*/XorStr<0xeb,33,0x3cdba6b3>("\xce\x9f\xcd\xc6\xaa\xa2\xa3\xd2\xc9\xd4\xbc\xb8\xa1\xb9\xb5\xb3\xbf\xa3\xbc\xb2\xb6\x47\x4f\x5d\x57\x4b\x5a\x45\x46\x44\x45\x23"+0x3cdba6b3).s, Addy->Key);
			break;
		}
		Addy->Value = CallPosition + CallDifference + 5;
		break;
	case ADDY_FUNCTION_GETJMP:
		JumpPosition = Search + Align;
		JumpDifference = *(DWORD*)(JumpPosition + 1);
		if(*(BYTE*)(JumpPosition) != 0xE9){
			sprintf(Addy->Key, /*%s (ERR : INVALID_ALIGN_TO_JMP)*/XorStr<0x87,32,0x24993e0c>("\xa2\xfb\xa9\xa2\xce\xde\xdf\xae\xb5\xb0\xd8\xdc\xc5\xd5\xd9\xdf\xd3\xc7\xd8\xd6\xd2\xdb\xd3\xc1\xcb\xef\xfe\xe8\xee\xf4\x8c"+0x24993e0c).s, Addy->Key);
			break;
		}
		Addy->Value = JumpPosition + JumpDifference + 5;
		break;
	case ADDY_FUNCTION_FINDSTART:
		while(true)
		{
			if(*(BYTE*)(Search + 0) == 0x55 &&
			   *(BYTE*)(Search + 1) == 0x8B &&
			   *(BYTE*)(Search + 2) == 0xEC)break;
			Search--;
		}
		if(Align > NULL && AlignSize > NULL && AlignSize <= 4){
			switch(AlignSize)
			{
			case 1:
				Addy->Value = *(BYTE*)(Search + Align);
				break;
			case 2:
				Addy->Value = *(WORD*)(Search + Align);
				break;
			case 4:
				Addy->Value = *(DWORD*)(Search + Align);
				break;
			}
		}
		else Addy->Value = Search;
		break;
	case ADDY_FUNCTION_FINDEND:
		while(true)
		{
			if(*(BYTE*)(Search + 0) == 0x55 &&
			   *(BYTE*)(Search + 1) == 0x8B &&
			   *(BYTE*)(Search + 2) == 0xEC)break;
			Search++;
		}
		if(Align > NULL && AlignSize > NULL && AlignSize <= 4){
			switch(AlignSize)
			{
			case 1:
				Addy->Value = *(BYTE*)(Search + Align);
				break;
			case 2:
				Addy->Value = *(WORD*)(Search + Align);
				break;
			case 4:
				Addy->Value = *(DWORD*)(Search + Align);
				break;
			}
		}
		else Addy->Value = Search;
		break;
	case ADDY_FUNCTION_FINDNEXT:
		Search += 1;
		while(true)
		{
			if(*(BYTE*)(Search + 0) == 0x55 &&
			   *(BYTE*)(Search + 1) == 0x8B &&
			   *(BYTE*)(Search + 2) == 0xEC)break;
			Search++;
		}
		if(Align > NULL && AlignSize > NULL && AlignSize <= 4){
			switch(AlignSize)
			{
			case 1:
				Addy->Value = *(BYTE*)(Search + Align);
				break;
			case 2:
				Addy->Value = *(WORD*)(Search + Align);
				break;
			case 4:
				Addy->Value = *(DWORD*)(Search + Align);
				break;
			}
		}
		else Addy->Value = Search;
		break;
	case ADDY_FUNCTION_FINDPREV:
		Search -= 1;
		while(true)
		{
			if(*(BYTE*)(Search + 0) == 0x55 &&
			   *(BYTE*)(Search + 1) == 0x8B &&
			   *(BYTE*)(Search + 2) == 0xEC)break;
			Search--;
		}
		if(Align > NULL && AlignSize > NULL && AlignSize <= 4){
			switch(AlignSize)
			{
			case 1:
				Addy->Value = *(BYTE*)(Search + Align);
				break;
			case 2:
				Addy->Value = *(WORD*)(Search + Align);
				break;
			case 4:
				Addy->Value = *(DWORD*)(Search + Align);
				break;
			}
		}
		else Addy->Value = Search;
		break;
	case ADDY_GET_VALUE:
		if(Align > NULL && AlignSize > NULL && AlignSize <= 4){
			switch(AlignSize)
			{
			case 1:
				Addy->Value = *(BYTE*)(Search + Align);
				break;
			case 2:
				Addy->Value = *(WORD*)(Search + Align);
				break;
			case 4:
				Addy->Value = *(DWORD*)(Search + Align);
				break;
			}
		}
	}
	return Addy;
}

void cAddyEngine::AddAddyByValue(char* Key, DWORD Value)
{
	sAddy NewAddy(Key, Value);
	AddyList.push_back(NewAddy);
}

void cAddyEngine::AddAddyByValue(char* Key, AddyType eAddyType, DWORD Align, DWORD AlignSize, DWORD Value)
{
	sAddy NewAddy (Key, Value);
	this->ParseAddyByOption(&NewAddy, eAddyType, Align, AlignSize);
	AddyList.push_back(NewAddy);
}

void cAddyEngine::AddAddyByPattern(char* Key, AddyType eAddyType, DWORD Align, DWORD AlignSize, char* ModuleName, char* Pattern)
{
	sAddy* NewAddy = this->FindAddyByPattern(Key, ModuleName, Pattern);
	if(NewAddy->Value > NULL)
		this->ParseAddyByOption(NewAddy, eAddyType, Align, AlignSize);
	sAddy InsertAddy(NewAddy->Key, NewAddy->Value);
	AddyList.push_back(InsertAddy);
}

int cAddyEngine::GetAddySize()
{
	return this->AddyList.size();
}

sAddy* cAddyEngine::GetAddyByIndex(int Index)
{
	return &this->AddyList[Index];
}

sAddy* cAddyEngine::GetAddyByKey(char* Key)
{
	for(unsigned int i = 0; i < AddyList.size(); i++)
	{
		sAddy* CurrentAddy = &AddyList[i];
		if(strcmp(CurrentAddy->Key, Key) == 0){
			return CurrentAddy;
		}
	}
	return NULL;
}

DWORD cAddyEngine::GetAddyValueByKey(char* Key)
{
	DWORD RetVal = NULL;
	sAddy* Search = GetAddyByKey(Key);
	if(Search > NULL)RetVal = Search->Value;
	if(RetVal == NULL){
		char T[260] = {0};
		sprintf(T, /*DWORD cAddyEngine::GetAddyValueByKey(char* Key) : %s = 0x%p;*/XorStr<0x29,61,0xe184be23>("\x6d\x7d\x64\x7e\x69\x0e\x4c\x71\x55\x56\x4a\x71\x5b\x51\x5e\x56\x5c\x00\x01\x7b\x58\x4a\x7e\x24\x25\x3b\x15\x25\x29\x33\x22\x0a\x30\x01\x2e\x35\x65\x2d\x27\x31\x23\x78\x73\x1f\x30\x2f\x7e\x78\x63\x7a\x7e\x2f\x7d\x63\x7f\x50\x19\x47\x13\x5f"+0xe184be23).s, Key, RetVal);
		MessageBoxA(0, T, "Error", MB_OK | MB_ICONERROR | MB_TOPMOST); 
	}
	return RetVal;
}
cAddyEngine* AddyEngine = NULL;