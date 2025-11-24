//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
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

DWORD PUSH_STR_PB(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask,char * szMask,int Offsete)
{	
	if(FindPattern(dwdwAdd,dwLen,bMask,szMask) != NULL)
	{
		DWORD ADR = FindPattern(dwdwAdd,dwLen,bMask,szMask);
		if(FindPattern((DWORD)dwdwAdd, (DWORD)dwLen, ADR))
		{
			DWORD PUSH = FindPattern((DWORD)dwdwAdd, (DWORD)dwLen, ADR)-1;
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

    if(!GetModuleHandleA("psapi.dll"))
    {
        
        char szSystemPath[MAX_PATH];
        GetWindowsDirectory(szSystemPath, MAX_PATH);
        char szPSAPIDLLPath[MAX_PATH];
        sprintf(szPSAPIDLLPath, "%s\\system32\\psapi.dll", szSystemPath);
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
		sprintf(NewAddy->Key, "%s (ERR : EXECUTEABLE_NOT_FOUND)", Key);
		return NewAddy;
	}

	DWORD Search = this->FindPattern((DWORD)mTarget.lpBaseOfDll, (DWORD)mTarget.lpBaseOfDll + (DWORD)mTarget.SizeOfImage, Pattern);
	if(Search == NULL){
		sprintf(NewAddy->Key, "%s (ERR : ADDY_NOT_FOUND)", Key);
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
		sprintf(Addy->Key, "%s (ERR : ADDY_NOT_FOUND)", Addy->Key);
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
			sprintf(Addy->Key, "%s (ERR : INVALID_ALIGN_TO_CALL)", Addy->Key);
			break;
		}
		Addy->Value = CallPosition + CallDifference + 5;
		break;
	case ADDY_FUNCTION_GETJMP:
		JumpPosition = Search + Align;
		JumpDifference = *(DWORD*)(JumpPosition + 1);
		if(*(BYTE*)(JumpPosition) != 0xE9){
			sprintf(Addy->Key, "%s (ERR : INVALID_ALIGN_TO_JMP)", Addy->Key);
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
		sprintf(T, "DWORD cAddyEngine::GetAddyValueByKey(char* Key) : %s = 0x%p;", Key, RetVal);
		MessageBoxA(0, T, "Error", MB_OK | MB_ICONERROR | MB_TOPMOST); 
	}
	return RetVal;
}
cAddyEngine* AddyEngine = NULL;