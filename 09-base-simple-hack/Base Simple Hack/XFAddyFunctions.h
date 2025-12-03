
class sElite
{
public:
	char Key[100];
	DWORD Value;
	sElite(char* Key, DWORD Value)
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

class xEliteWorldCyber
{
private:
	vector<sElite> AddyList;
	MODULEINFO GetModuleInfo ( LPCTSTR lpModuleName );
	DWORD FindPattern( DWORD rangeStart, DWORD rangeEnd, const char* pattern );
public:
	virtual sElite* FindAddyByPattern(char* Key, char* ModuleName, char* Pattern);
	virtual sElite* ParseAddyByOption(sElite* Addy, enum AddyType, DWORD Align, DWORD AlignSize);
	virtual void AddAddyByValue(char* Key, DWORD Value);
	virtual void AddAddyByValue(char* Key, enum AddyType, DWORD Align, DWORD AlignSize, DWORD Value);
	virtual void AddAddyByPattern(char* Key, enum AddyType, DWORD Align, DWORD AlignSize, char* ModuleName, char* Pattern);

	virtual int GetAddySize();
	virtual sElite* GetAddyByIndex(int Index);
	virtual sElite* GetAddyByKey(char* Key);
	virtual DWORD GetAddyValueByKey(char* Key);
	
};
MODULEINFO xEliteWorldCyber::GetModuleInfo ( LPCTSTR lpModuleName )
{
	MODULEINFO miInfos = { NULL };
    HMODULE hPSAPI_module;

    if(!GetModuleHandleA("psapi.dll"))
    {
        
        char szSystemPath[MAX_PATH];
        GetWindowsDirectory(szSystemPath, MAX_PATH);
        char szPSAPIDLLPath[MAX_PATH];
        sprintf(szPSAPIDLLPath,"%s\\system32\\psapi.dll", szSystemPath);
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
DWORD xEliteWorldCyber::FindPattern( DWORD rangeStart, DWORD rangeEnd, const char* pattern )
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
sElite* xEliteWorldCyber::FindAddyByPattern(char* Key, char* ModuleName, char* Pattern)
{
	sElite* NewElite = new sElite(Key, NULL);
	MODULEINFO mTarget = this->GetModuleInfo(ModuleName);
	if(mTarget.SizeOfImage == NULL){
		sprintf(NewElite->Key, "%s (ERR : EXECUTEABLE_NOT_FOUND)", Key);
		return NewElite;
	}

	DWORD Search = this->FindPattern((DWORD)mTarget.lpBaseOfDll, (DWORD)mTarget.lpBaseOfDll + (DWORD)mTarget.SizeOfImage, Pattern);
	if(Search == NULL){
		sprintf(NewElite->Key, "%s (ERR : ADDY_NOT_FOUND)", Key);
		return NewElite;
	}
	NewElite->Value = Search;
	return NewElite;
}
sElite* xEliteWorldCyber::ParseAddyByOption(sElite* Addy,AddyType eAddyType, DWORD Align, DWORD AlignSize)
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
void xEliteWorldCyber::AddAddyByValue(char* Key, DWORD Value)
{
	sElite NewElite(Key, Value);
	AddyList.push_back(NewElite);
}
void xEliteWorldCyber::AddAddyByValue(char* Key, AddyType eAddyType, DWORD Align, DWORD AlignSize, DWORD Value)
{
	sElite NewElite (Key, Value);
	this->ParseAddyByOption(&NewElite, eAddyType, Align, AlignSize);
	AddyList.push_back(NewElite);
}
void xEliteWorldCyber::AddAddyByPattern(char* Key, AddyType eAddyType, DWORD Align, DWORD AlignSize, char* ModuleName, char* Pattern)
{
	sElite* NewElite = this->FindAddyByPattern(Key, ModuleName, Pattern);
	if(NewElite->Value > NULL)
		this->ParseAddyByOption(NewElite, eAddyType, Align, AlignSize);
	sElite InsertAddy(NewElite->Key, NewElite->Value);
	AddyList.push_back(InsertAddy);
}
int xEliteWorldCyber::GetAddySize()
{
	return this->AddyList.size();
}
sElite* xEliteWorldCyber::GetAddyByIndex(int Index)
{
	return &this->AddyList[Index];
}
sElite* xEliteWorldCyber::GetAddyByKey(char* Key)
{
	for(unsigned int i = 0; i < AddyList.size(); i++)
	{
		sElite* CurrentAddy = &AddyList[i];
		if(strcmp(CurrentAddy->Key, Key) == 0){
			return CurrentAddy;
		}
	}
	return NULL;
}

DWORD xEliteWorldCyber::GetAddyValueByKey(char* Key)
{
	DWORD RetVal = NULL;
	sElite* Search = GetAddyByKey(Key);
	if(Search > NULL)RetVal = Search->Value;
	if(RetVal == NULL){
		char T[260] = {0};
		sprintf(T, "DWORD xEliteWorldCyber::GetAddyValueByKey(char* Key) : %s = 0x%p;", Key, RetVal);
		MessageBoxA(0, T, "Error", MB_OK | MB_ICONERROR | MB_TOPMOST); 
	}
	return RetVal;
}

xEliteWorldCyber* EliteWorldCyber = NULL;