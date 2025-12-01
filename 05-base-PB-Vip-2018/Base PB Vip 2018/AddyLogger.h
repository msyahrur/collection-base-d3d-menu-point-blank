
#pragma comment( lib, "psapi.lib" )
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
		AddLog(/*DWORD cAddyEngine::GetAddyValueByKey(char* Key) : %s = 0x%p;*/XorStr<0x29,61,0xe184be23>("\x6d\x7d\x64\x7e\x69\x0e\x4c\x71\x55\x56\x4a\x71\x5b\x51\x5e\x56\x5c\x00\x01\x7b\x58\x4a\x7e\x24\x25\x3b\x15\x25\x29\x33\x22\x0a\x30\x01\x2e\x35\x65\x2d\x27\x31\x23\x78\x73\x1f\x30\x2f\x7e\x78\x63\x7a\x7e\x2f\x7d\x63\x7f\x50\x19\x47\x13\x5f"+0xe184be23).s, Key, RetVal);
	}
	return RetVal;
}

ofstream infile;
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

char dlldir[320];
char *GetDirectoryFile(char *filename)
{
	static char path[320];
	strcpy(path, dlldir);
	strcat(path, filename);
	return path;
}

cAddyEngine* AddyEngine = NULL;

#pragma warning(disable:4244)
#pragma warning(disable:4700)
#pragma warning(disable:4996)
#pragma warning(disable:4305)
#pragma warning(disable:4715)
using namespace std;
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

/*------------------------------------------- Declaration String ------------------------------------------------------*/
#define Result_Address			1
#define Result_PTRByte			2
#define Result_PTR4Byte			3
#define Result_AddressString	4
#define Result_PTRStringByte	5
#define Result_PTRString4Byte	6

/*------------------------------------------- Declaration Function ------------------------------------------------------*/
void __cdecl add_log (const char * fmt, ...);
void thethread();

DWORD Temp = NULL;
typedef int (__thiscall * tReadBaseValue)(DWORD BaseValue);
tReadBaseValue oReadBaseValue;
void LogAddyValues()
{
	

	AddyEngine = new cAddyEngine;
	//14 = 5
	AddyEngine->AddAddyByPattern(/*XFHPB.Function.ReadBaseValue*/XorStr<0x29,29,0xe184be23>("\x71\x6c\x63\x7c\x6f\x00\x69\x45\x5f\x51\x47\x5d\x5a\x58\x19\x6a\x5c\x5b\x5f\x7e\x5c\x4d\x5a\x16\x20\x2e\x36\x21"+0xe184be23).s, ADDY_FUNCTION_GETCALL, 14, 4, /*PointBlank.exe*/XorStr<0x6c,15,0x9052aed6>("\x3c\x02\x07\x01\x04\x33\x1e\x12\x1a\x1e\x58\x12\x00\x1c"+0x9052aed6).s, /*8B 4D 0C E8 ?? ?? ?? ?? 50 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ??*/XorStr<0x49,78,0xe9bbf1f1>("\x71\x08\x6b\x78\x09\x6e\x7f\x13\x71\x17\x6b\x74\x6a\x69\x77\x67\x66\x7a\x64\x63\x7d\x61\x60\x40\x54\x52\x43\x26\x5c\x46\x58\x57\x49\x55\x54\x4c\x52\x51\x4f\x4f\x4e\x52\x36\x4c\x55\x49\x48\x58\x46\x45\x5b\x43\x42\x5e\x40\xbf\xa1\xba\xc1\xa4\xc6\xbe\xa7\xcd\xb1\xaa\xb4\xb3\xad\xb1\xb0\xb0\xae\xad\xb3\xab\xaa"+0xe9bbf1f1).s);
	oReadBaseValue = (tReadBaseValue)(AddyEngine->GetAddyValueByKey(/*XFHPB.Function.ReadBaseValue*/XorStr<0xeb,29,0x3cdba6b3>("\xb3\xaa\xa5\xbe\xad\xde\xb7\x87\x9d\x97\x81\x9f\x98\x96\xd7\xa8\x9e\x9d\x99\xbc\x9e\x73\x64\x54\x62\x68\x70\x63"+0x3cdba6b3).s));
	
	AddyEngine->AddAddyByPattern(/*XFHPB.Import.i3CollideeLine::SetEnd*/XorStr<0x29,36,0xe184be23>("\x71\x6c\x63\x7c\x6f\x00\x66\x5d\x41\x5d\x41\x40\x1b\x5f\x04\x7b\x56\x56\x57\x55\x59\x5b\x5a\x0c\x28\x2c\x26\x7e\x7f\x15\x22\x3c\x0c\x24\x2f"+0xe184be23).s, ADDY_GET_VALUE, 15, 4, /*PointBlank.exe*/XorStr<0x6c,15,0x9052aed6>("\x3c\x02\x07\x01\x04\x33\x1e\x12\x1a\x1e\x58\x12\x00\x1c"+0x9052aed6).s, /*8B 4D 0C 51 8B 4D F4 81 C1 ?? ?? ?? ?? FF 15 ?? ?? ?? ??*/XorStr<0x20,57,0x0F92F191>("\x18\x63\x02\x17\x60\x05\x16\x64\x08\x1C\x1B\x0B\x14\x6F\x0E\x1B\x74\x11\x74\x07\x14\x0D\x07\x17\x7B\x08\x1A\x04\x03\x1D\x01\x00\x60\x7E\x7D\x63\x7B\x7A\x66\x01\x0E\x69\x7B\x7E\x6C\x72\x71\x6F\x6F\x6E\x72\x6C\x6B\x75\x69\x68"+0x0F92F191).s);
	AddyEngine->AddAddyByPattern(/*XFHPB.Import.i3AiContext::getLocalTime*/XorStr<0x49,39,0xe9bbf1f1>("\x11\x0c\x03\x1c\x0f\x60\x06\x3d\x21\x3d\x21\x20\x7b\x3f\x64\x19\x30\x19\x34\x32\x29\x3b\x27\x14\x5b\x58\x04\x01\x11\x2a\x08\x0b\x08\x06\x3f\x05\x00\x0b"+0xe9bbf1f1).s, ADDY_GET_VALUE, 5, 4, /*PointBlank.exe*/XorStr<0xeb,15,0x3cdba6b3>("\xbb\x83\x84\x80\x9b\xb2\x9d\x93\x9d\x9f\xdb\x93\x8f\x9d"+0x3cdba6b3).s, /*8B 4D 08 FF 15 ?? ?? ?? ?? 8B 45 FC 50 8B 4D F0*/XorStr<0xF5,48,0xD12D028D>("\xCD\xB4\xD7\xCC\xBD\xDA\xCB\xC4\xDD\xB8\xB9\x20\x30\x37\x23\x3B\x3A\x26\x38\x37\x29\x35\x34\x2C\x32\x31\x2F\x28\x53\x32\x27\x21\x35\x50\x54\x38\x2C\x2A\x3B\x24\x5F\x3E\x2B\x64\x01\x64\x13"+0xD12D028D).s);
	//AddyEngine->AddAddyByPattern(/*XFHPB.Import.i3RenderContext::EndRender*/XorStr<0x87,40,0x24993e0c>("\xdf\xce\xc1\xda\xc9\xa2\xc4\xe3\xff\xff\xe3\xe6\xbd\xfd\xa6\xc4\xf2\xf6\xfd\xff\xe9\xdf\xf2\xf0\xeb\xc5\xd9\xd6\x99\x9e\xe0\xc8\xc3\xfa\xcc\xc4\xcf\xc9\xdf"+0x24993e0c).s, ADDY_GET_VALUE, 2, 4, /*i3FrameWorkDx.dll*/XorStr<0x5e,18,0xb7061c0d>("\x37\x6c\x26\x13\x03\x0e\x01\x32\x09\x15\x03\x2d\x12\x45\x08\x01\x02"+0xb7061c0d).s, /*FF 15 ?? ?? ?? ?? 8B 4E 18 FF 15 ?? ?? ?? ?? 85 C0*/XorStr<0x33,51,0x914ED228>("\x75\x72\x15\x07\x02\x18\x06\x05\x1B\x03\x02\x1E\x00\x7F\x61\x7D\x7C\x64\x7D\x04\x67\x7C\x0C\x6A\x7A\x74\x6D\x08\x09\x70\x60\x67\x73\x6B\x6A\x76\x68\x67\x79\x65\x64\x7C\x62\x61\x7F\x58\x54\x42\x20\x54"+0x914ED228).s);	
	AddyEngine->AddAddyByPattern(/*XFHPB.Import.i3RenderContext::DrawIndexedPrim*/XorStr<0x47,46,0x4d12b3de>("\x1f\x0e\x01\x1a\x09\x62\x04\x23\x3f\x3f\x23\x26\x7d\x3d\x66\x04\x32\x36\x3d\x3f\x29\x1f\x32\x30\x2b\x05\x19\x16\x59\x5e\x21\x14\x06\x1f\x20\x04\x0f\x09\x15\x0b\x0b\x20\x03\x1b\x1e"+0x4d12b3de).s, ADDY_GET_VALUE, 7, 4, /*i3SceneDx.dll*/XorStr<0xc8,14,0xa68bbb43>("\xa1\xfa\x99\xa8\xa9\xa3\xab\x8b\xa8\xff\xb6\xbf\xb8"+0xa68bbb43).s, /*50 51 52 8B CF FF 15 ?? ?? ?? ?? 8B 4C 24*/XorStr<0x21,42,0xF61786D3>("\x14\x12\x03\x11\x14\x06\x12\x1A\x09\x12\x69\x0C\x6E\x68\x0F\x76\x77\x12\x02\x01\x15\x09\x08\x18\x06\x05\x1B\x03\x02\x1E\x00\x7F\x61\x7A\x01\x64\x71\x05\x67\x7A\x7D"+0xF61786D3).s);	
	AddyEngine->AddAddyByPattern(/*XFHPB.Values.GaugeMultiplier*/XorStr<0x29,29,0xe184be23>("\x71\x6c\x63\x7c\x6f\x00\x79\x51\x5d\x47\x56\x47\x1b\x71\x56\x4d\x5e\x5f\x76\x49\x51\x4a\x56\x30\x2d\x2b\x26\x36"+0xe184be23).s, ADDY_GET_VALUE, 15, 4, /*PointBlank.exe*/XorStr<0x6c,15,0x9052aed6>("\x3c\x02\x07\x01\x04\x33\x1e\x12\x1a\x1e\x58\x12\x00\x1c"+0x9052aed6).s, /*C7 45 ?? 01 00 00 00 DB 45 ?? DA 75 ?? DC 0D ?? ?? ?? ??*/XorStr<0x49,57,0xe9bbf1f1>("\x0a\x7d\x6b\x78\x78\x6e\x70\x6f\x71\x62\x62\x74\x65\x66\x77\x68\x69\x7a\x6b\x6c\x7d\x1a\x1d\x40\x55\x57\x43\x5b\x5a\x46\x23\x29\x49\x5d\x5e\x4c\x52\x51\x4f\x34\x32\x52\x43\x30\x55\x49\x48\x58\x46\x45\x5b\x43\x42\x5e\x40\xbf"+0xe9bbf1f1).s);
	AddyEngine->AddAddyByPattern(/*XFHPB.Pointer.QuickChange*/XorStr<0x1f,26,0x097d5a03>("\x47\x66\x69\x72\x61\x0a\x75\x49\x4e\x46\x5d\x4f\x59\x02\x7c\x5b\x46\x53\x5a\x71\x5b\x55\x5b\x51\x52"+0x097d5a03).s, ADDY_GET_VALUE, 10, 2, /*PointBlank.exe*/XorStr<0x38,15,0xd45d1f25>("\x68\x56\x53\x55\x48\x7f\x52\x5e\x2e\x2a\x6c\x26\x3c\x20"+0xd45d1f25).s, /*89 4D FC 8B 45 FC 33 C9 83 78 ?? ?? 0F 95 C1 8A C1 8B E5 5D C3 CC*/XorStr<0x29,66,0xe184be23>("\x11\x13\x0b\x18\x69\x0e\x69\x73\x11\x0a\x71\x14\x01\x03\x17\x7e\x7a\x1a\x08\x0f\x1d\x7d\x06\x60\x79\x71\x63\x73\x7d\x66\x78\x77\x69\x75\x74\x6c\x7d\x08\x6f\x69\x64\x72\x10\x65\x75\x6e\x16\x78\x1a\x6b\x7b\x64\x1f\x7e\x1a\x55\x41\x57\x27\x44\x26\x55\x47\x2b\x2a"+0xe184be23).s );	
	AddyEngine->AddAddyByPattern(/*XFHPB.Pointer.NoReload*/XorStr<0xcb,23,0x45f596fc>("\x93\x8a\x85\x9e\x8d\xfe\x81\xbd\xba\xba\xa1\xb3\xa5\xf6\x97\xb5\x89\xb9\xb1\xb1\xbe\x84"+0x45f596fc).s, ADDY_GET_VALUE, 4, 1, /*i3FrameWorkDx.dll*/XorStr<0x3b,18,0x0a890d13>("\x52\x0f\x7b\x4c\x5e\x2d\x24\x15\x2c\x36\x2e\x02\x3f\x66\x2d\x26\x27"+0x0a890d13).s, /*DD D8 8B 76 ?? 85 F6*/XorStr<0x18,21,0x711BE83B>("\x5C\x5D\x3A\x5F\x24\x3D\x26\x5D\x00\x16\x14\x03\x1B\x1A\x06\x1F\x1D\x09\x6C\x1D"+0x711BE83B).s );	
	AddyEngine->AddAddyByPattern(/*XFHPB.Pointer.FireSpeed*/XorStr<0x1c,24,0x2032aedb>("\x44\x5b\x56\x4f\x62\x0f\x72\x4c\x4d\x4b\x52\x42\x5a\x07\x6c\x42\x5e\x48\x7d\x5f\x55\x54\x56"+0x2032aedb).s, ADDY_GET_VALUE, 10, 4, /*PointBlank.exe*/XorStr<0x9a,15,0x7840ee50>("\xca\xf4\xf5\xf3\xea\xdd\xcc\xc0\xcc\xc8\x8a\xc0\xde\xc2"+0x7840ee50).s, /*8B 45 ?? F7 D0 8B 4D ?? 23 81 ?? ?? ?? ?? 8B 55 ??*/XorStr<0xFF,51,0x5539E028>("\xC7\x42\x21\x36\x36\x24\x3A\x39\x27\x4E\x3E\x2A\x4F\x3C\x2D\x36\x4D\x30\x25\x56\x33\x2B\x2A\x36\x25\x2B\x39\x22\x2A\x3C\x22\x21\x3F\x1F\x1E\x02\x1C\x1B\x05\x19\x18\x08\x11\x68\x0B\x19\x18\x0E\x10\x0F"+0x5539E028).s);	
	AddyEngine->AddAddyByPattern(/*XFHPB.Function.SetHitCollision*/XorStr<0x36,31,0x324912fd>("\x6e\x71\x70\x69\x78\x15\x7a\x48\x50\x5c\x34\x28\x2d\x2d\x6a\x16\x23\x33\x00\x20\x3e\x08\x23\x21\x22\x26\x23\x38\x3d\x3d"+0x324912fd).s, ADDY_FUNCTION_GETCALL, 9, NULL, /*i3FrameWorkDx.dll*/XorStr<0xf6,18,0xdc497d9e>("\x9f\xc4\xbe\x8b\x9b\x96\x99\xaa\x91\x8d\x6b\x45\x7a\x2d\x60\x69\x6a"+0xdc497d9e).s, /*8B 87 ?? ?? ?? ?? 50 8B CE E8 ?? ?? ?? ?? 8B 9F*/XorStr<0x1D,48,0x87C5AFC9>("\x25\x5C\x3F\x18\x16\x02\x1C\x1B\x05\x19\x18\x08\x16\x15\x0B\x13\x12\x0E\x1A\x00\x11\x0A\x71\x14\x76\x73\x17\x7D\x01\x1A\x04\x03\x1D\x01\x00\x60\x7E\x7D\x63\x7B\x7A\x66\x7F\x0A\x69\x73\x0D"+0x87C5AFC9).s);	
	
	Temp = AddyEngine->ParseAddyByOption(AddyEngine->FindAddyByPattern(/*Temp*/XorStr<0xad,5,0x44f2144f>("\xf9\xcb\xc2\xc0"+0x44f2144f).s, /*PointBlank.exe*/XorStr<0x40,15,0xc46bd066>("\x10\x2e\x2b\x2d\x30\x07\x2a\x26\x26\x22\x64\x2e\x34\x28"+0xc46bd066).s, /*8B 4D 10 DD 5D D8 E8 ?? ?? ?? ??*/XorStr<0x51,33,0xA0A26C7D>("\x69\x10\x73\x60\x11\x76\x66\x68\x79\x1E\x1F\x7C\x68\x1A\x7F\x24\x59\x42\x26\x5C\x45\x59\x58\x48\x56\x55\x4B\x53\x52\x4E\x50\x4F"+0xA0A26C7D).s), ADDY_FUNCTION_GETCALL, 6, NULL)->Value;
	while(true)
	{
		if(*(BYTE*)(Temp + 0) == 0xD9 &&
		   *(BYTE*)(Temp + 1) == 0x45 &&
		   *(BYTE*)(Temp + 2) == 0xF8 &&
		   *(BYTE*)(Temp + 3) == 0x8B &&
		   *(BYTE*)(Temp + 4) == 0xE5)break;
		Temp++;
	}
	AddyEngine->AddAddyByValue(/*XFHPB.Address.Hook.RecoilV*/XorStr<0x30,27,0xa13b32b7>("\x68\x77\x7a\x63\x76\x1b\x77\x53\x5c\x4b\x5f\x48\x4f\x13\x76\x50\x2f\x2a\x6c\x11\x21\x26\x29\x2e\x24\x1f"+0xa13b32b7).s, Temp);
	
	Temp = AddyEngine->ParseAddyByOption(AddyEngine->FindAddyByPattern(/*Temp*/XorStr<0x22,5,0x9d9122f6>("\x76\x46\x49\x55"+0x9d9122f6).s, /*PointBlank.exe*/XorStr<0xe1,15,0xb0da1f8b>("\xb1\x8d\x8a\x8a\x91\xa4\x8b\x89\x87\x81\xc5\x89\x95\x8b"+0xb0da1f8b).s, /*8B 4D 10 DD 5D DC E8 ?? ?? ?? ??*/XorStr<0x1A,33,0xFF26DC2D>("\x22\x59\x3C\x29\x5A\x3F\x11\x11\x02\x67\x60\x05\x13\x63\x08\x6D\x69\x0B\x69\x15\x0E\x10\x0F\x11\x0D\x0C\x14\x0A\x09\x17\x07\x06"+0xFF26DC2D).s), ADDY_FUNCTION_GETCALL, 6, NULL)->Value;
	while(true)
	{
		if(*(BYTE*)(Temp + 0) == 0xD9 &&
		   *(BYTE*)(Temp + 1) == 0x45 &&
		   *(BYTE*)(Temp + 2) == 0xF8 &&
		   *(BYTE*)(Temp + 3) == 0x8B &&
		   *(BYTE*)(Temp + 4) == 0xE5)break;

		Temp++;
	}
	AddyEngine->AddAddyByValue(/*XFHPB.Address.Hook.RecoilH*/XorStr<0xca,27,0x72b90299>("\x92\x8d\x84\x9d\x8c\xe1\x91\xb5\xb6\xa1\xb1\xa6\xa5\xf9\x90\xb6\xb5\xb0\xf2\x8f\xbb\xbc\x8f\x88\x8e\xab"+0x72b90299).s, Temp);

	Temp = AddyEngine->FindAddyByPattern(/*Temp*/XorStr<0x9d,5,0x7e802c49>("\xc9\xfb\xf2\xd0"+0x7e802c49).s, /*PointBlank.exe*/XorStr<0xc5,15,0x80e9d599>("\x95\xa9\xae\xa6\xbd\x88\xa7\xad\xa3\xa5\xe1\xb5\xa9\xb7"+0x80e9d599).s, /*74 ?? 8B 45 F4 8B 88 ?? ?? ?? ?? E8 ?? ?? ?? ??*/XorStr<0x05,48,0x429AF083>("\x32\x32\x27\x37\x36\x2A\x33\x4E\x2D\x3A\x3A\x30\x57\x26\x33\x2C\x57\x36\x2F\x20\x39\x25\x24\x3C\x22\x21\x3F\x1F\x1E\x02\x1C\x1B\x05\x63\x1F\x08\x16\x15\x0B\x13\x12\x0E\x10\x0F\x11\x0D\x0C"+0x429AF083).s)->Value;
	while(true)
	{
		if(*(BYTE*)(Temp + 0) == 0xD9 &&
		   *(BYTE*)(Temp + 1) == 0x45 &&
		   *(BYTE*)(Temp + 2) == 0xFC &&
		   *(BYTE*)(Temp + 3) == 0x8B &&
		   *(BYTE*)(Temp + 4) == 0xE5)break;
		Temp++;
	}
	AddyEngine->AddAddyByValue(/*XFHPB.Address.Hook.Range*/XorStr<0xb2,25,0x53ccc9ea>("\xea\xf5\xfc\xe5\xf4\x99\xf9\xdd\xde\xc9\xd9\xce\xcd\x91\x88\xae\xad\xa8\xea\x97\xa7\xa9\xaf\xac"+0x53ccc9ea).s, Temp);

	Temp = AddyEngine->FindAddyByPattern(/*Temp*/XorStr<0xbf,5,0x14bfd667>("\xeb\xa5\xac\xb2"+0x14bfd667).s, /*PointBlank.exe*/XorStr<0xd6,15,0x8edc2d7e>("\x86\xb8\xb1\xb7\xae\x99\xb0\xbc\xb0\xb4\xce\x84\x9a\x86"+0x8edc2d7e).s, /*85 C0 74 ?? 8B 55 ?? 8B 8A ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? D8 4D*/XorStr<0xBF,81,0x161209C2>("\x87\xF5\xE1\x81\xF3\xE4\xF2\xF2\xE7\xF7\xF6\xEA\xF3\x8E\xED\xFB\xFA\xF0\xEE\xED\xF3\xEC\x97\xF6\xEF\x99\xF9\xE5\xE4\xFC\xE2\xE1\xFF\xDF\xDE\xC2\xDC\xDB\xC5\xA3\xDF\xC8\xD6\xD5\xCB\xD3\xD2\xCE\xD0\xCF\xD1\xCD\xCC\xD4\xCD\xB4\xD7\xBB\xC1\xDA\xBE\xC4\xDD\xC1\xC0\x20\x3E\x3D\x23\x3B\x3A\x26\x38\x37\x29\x4E\x33\x2C\x39\x4A"+0x161209C2).s)->Value;
	while(true)
	{
		if(*(BYTE*)(Temp + 0) == 0xD9 &&
		   *(BYTE*)(Temp + 1) == 0x45 &&
		   *(BYTE*)(Temp + 2) == 0xF0 &&
		   *(BYTE*)(Temp + 3) == 0x5E &&
		   *(BYTE*)(Temp + 4) == 0x8B &&
		   *(BYTE*)(Temp + 5) == 0xE5)break;
		Temp++;
	}
	AddyEngine->AddAddyByValue(/*XFHPB.Address.Hook.Damage*/XorStr<0x66,26,0x4957ef83>("\x3e\x21\x20\x39\x28\x45\x2d\x09\x0a\x1d\x15\x02\x01\x5d\x3c\x1a\x19\x1c\x56\x3d\x1b\x16\x1d\x1a\x1b"+0x4957ef83).s, Temp);
	AddyEngine->AddAddyByPattern(/*XFHPB.Address.Hook.Burst*/XorStr<0x61,25,0x618f69ff>("\x39\x24\x2b\x34\x27\x48\x26\x0c\x0d\x18\x0e\x1f\x1e\x40\x27\x1f\x1e\x19\x5d\x36\x00\x04\x04\x0c"+0x618f69ff).s, ADDY_NORMAL, 20, NULL, /*PointBlank.exe*/XorStr<0xcd,15,0x9c9d1ed1>("\x9d\xa1\xa6\xbe\xa5\x90\xbf\xb5\xbb\xbd\xf9\xbd\xa1\xbf"+0x9c9d1ed1).s, /*8B 82 ?? ?? ?? ?? 8B 4D ?? 8B 89 ?? ?? ?? ?? 8B 10 8B 42 ?? FF D0 89 45 ?? C7 45 ?? 00 00 00 00*/XorStr<0x2D,96,0x256C4D8B>("\x15\x6C\x0F\x08\x03\x12\x0C\x0B\x15\x09\x08\x18\x06\x05\x1B\x03\x02\x1E\x07\x02\x61\x76\x07\x64\x7A\x79\x67\x70\x0B\x6A\x73\x75\x6D\x71\x70\x70\x6E\x6D\x73\x6B\x6A\x76\x68\x67\x79\x62\x19\x7C\x6C\x6E\x7F\x58\x23\x42\x57\x56\x45\x59\x58\x48\x2F\x2C\x4B\x28\x5D\x4E\x57\x49\x51\x46\x46\x54\x4A\x49\x57\x3B\x4E\x5A\x4F\x49\x5D\x41\x40\xA0\xB1\xB2\xA3\xB4\xB5\xA6\xB7\xB8\xA9\xBA\xBB"+0x256C4D8B).s );
	AddyEngine->AddAddyByPattern(/*XFHPB.Address.Hook.SearchFile*/XorStr<0x29,30,0xe184be23>("\x71\x6c\x63\x7c\x6f\x00\x6e\x54\x55\x40\x56\x47\x46\x18\x7f\x57\x56\x51\x15\x6f\x58\x5f\x4d\x23\x29\x04\x2a\x28\x20"+0xe184be23).s, ADDY_FUNCTION_GETCALL, 15, NULL, /*PointBlank.exe*/XorStr<0x6c,15,0x9052aed6>("\x3c\x02\x07\x01\x04\x33\x1e\x12\x1a\x1e\x58\x12\x00\x1c"+0x9052aed6).s, /*83 C4 0C 68 ?? ?? ?? ?? 8D 95 FC ED FF FF 52 E8 ?? ?? ?? ??*/XorStr<0x49,60,0xe9bbf1f1>("\x71\x79\x6b\x0f\x79\x6e\x7f\x13\x71\x64\x6b\x74\x6a\x69\x77\x67\x66\x7a\x64\x63\x7d\x61\x60\x40\x59\x26\x43\x5d\x50\x46\x21\x2b\x49\x2f\x2f\x4c\x2b\x28\x4f\x36\x37\x52\x46\x46\x55\x33\x4f\x58\x46\x45\x5b\x43\x42\x5e\x40\xbf\xa1\xbd\xbc"+0xe9bbf1f1).s);	
	AddyEngine->AddAddyByValue(/*XFHPB.Address.Function.SearchFile*/XorStr<0xeb,34,0x3cdba6b3>("\xb3\xaa\xa5\xbe\xad\xde\xb0\x96\x97\x86\x90\x85\x84\xd6\xbf\x8f\x95\x9f\x89\x97\x90\x6e\x2f\x51\x66\x65\x77\x65\x6f\x4e\x60\x66\x6e"+0x3cdba6b3).s,
								ADDY_FUNCTION_GETCALL, 
								11, 
								NULL, 
								AddyEngine->GetAddyValueByKey(/*XFHPB.Address.Hook.SearchFile*/XorStr<0x87,30,0x24993e0c>("\xdf\xce\xc1\xda\xc9\xa2\xcc\xea\xeb\xe2\xf4\xe1\xe0\xba\xdd\xf9\xf8\xf3\xb7\xc9\xfe\xfd\xef\xfd\xf7\xe6\xc8\xce\xc6"+0x24993e0c).s)
							  );

	AddyEngine->AddAddyByPattern(/*XFHPB.Address.Modify.MovingSpeed*/XorStr<0x16,33,0x1de67272>("\x4e\x51\x50\x49\x58\x35\x5d\x79\x7a\x6d\x45\x52\x51\x0d\x69\x4a\x42\x4e\x4e\x50\x04\x66\x43\x5b\x47\x41\x57\x62\x42\x56\x51\x51"+0x1de67272).s, ADDY_GET_VALUE, 17, 4, /*PointBlank.exe*/XorStr<0xf0,15,0x774a4f84>("\xa0\x9e\x9b\x9d\x80\xb7\x9a\x96\x96\x92\xd4\x9e\x84\x98"+0x774a4f84).s, /*0F AF F0 89 B5 ?? ?? ?? ?? DB 85 ?? ?? ?? ?? DC 0D ?? ?? ?? ??*/XorStr<0x4C,63,0xF1C2E5CF>("\x7C\x0B\x6E\x0E\x16\x71\x14\x63\x74\x6D\x6F\x77\x1A\x6C\x7A\x64\x63\x7D\x61\x60\x40\x5E\x5D\x43\x5B\x5A\x46\x23\x2A\x49\x52\x5E\x4C\x52\x51\x4F\x4F\x4E\x52\x4C\x4B\x55\x49\x48\x58\x3D\x39\x5B\x4C\x39\x5E\x40\xBF\xA1\xBD\xBC\xA4\xBA\xB9\xA7\xB7\xB6"+0xF1C2E5CF).s );
	AddyEngine->AddAddyByPattern(/*XFHPB.Address.Modify.BugView*/XorStr<0x02,29,0x2c39e8d7>("\x5a\x45\x4c\x55\x44\x29\x49\x6d\x6e\x79\x69\x7e\x7d\x21\x5d\x7e\x76\x7a\x72\x6c\x38\x55\x6d\x7e\x4c\x72\x79\x6a"+0x2c39e8d7).s, ADDY_NORMAL, NULL, NULL, /*PointBlank.exe*/XorStr<0x53,15,0x1e12c9cb>("\x03\x3b\x3c\x38\x23\x1a\x35\x3b\x35\x37\x73\x3b\x27\x05"+0x1e12c9cb).s, /*9A 99 19 BE*/XorStr<0xC1,12,0x38D14799>("\xF8\x83\xE3\xFD\xFC\xE6\xF6\xF1\xE9\x88\x8E"+0x38D14799).s );
	AddyEngine->AddAddyByPattern(/*XFHPB.Address.Modify.Burst*/XorStr<0x33,27,0xf40c9e74>("\x6b\x72\x7d\x66\x75\x16\x78\x5e\x5f\x4e\x58\x4d\x4c\x6e\x0c\x2d\x27\x2d\x23\x3f\x69\x0a\x3c\x38\x38\x38"+0xf40c9e74).s, ADDY_NORMAL, 0x3B, NULL, /*PointBlank.exe*/XorStr<0xd5,15,0xa4d49fd4>("\x85\xb9\xbe\xb6\xad\x98\xb7\xbd\xb3\xb5\xf1\x85\x99\x87"+0xa4d49fd4).s, /*8B 82 ?? ?? ?? ?? 8B 4D ?? 8B 89 ?? ?? ?? ?? 8B 10 8B 42 ?? FF D0 89 45 ?? C7 45 ?? 00 00 00 00*/XorStr<0x2D,96,0x256C4D8B>("\x15\x6C\x0F\x08\x03\x12\x0C\x0B\x15\x09\x08\x18\x06\x05\x1B\x03\x02\x1E\x07\x02\x61\x76\x07\x64\x7A\x79\x67\x70\x0B\x6A\x73\x75\x6D\x71\x70\x70\x6E\x6D\x73\x6B\x6A\x76\x68\x67\x79\x62\x19\x7C\x6C\x6E\x7F\x58\x23\x42\x57\x56\x45\x59\x58\x48\x2F\x2C\x4B\x28\x5D\x4E\x57\x49\x51\x46\x46\x54\x4A\x49\x57\x3B\x4E\x5A\x4F\x49\x5D\x41\x40\xA0\xB1\xB2\xA3\xB4\xB5\xA6\xB7\xB8\xA9\xBA\xBB"+0x256C4D8B).s );

	AddyEngine->AddAddyByValue(/*RenderContext.Base*/XorStr<0x59,19,0x32cf357e>("\x0b\x3f\x35\x38\x38\x2c\x1c\x0f\x0f\x16\x06\x1c\x11\x48\x25\x09\x1a\x0f"+0x32cf357e).s, (DWORD)GetProcAddress(GetModuleHandle(/*i3GfxDx.dll*/XorStr<0x22,12,0xd3cfccf4>("\x4b\x10\x63\x43\x5e\x63\x50\x07\x4e\x47\x40"+0xd3cfccf4).s),/*?g_pRenderContext@@3PAVi3RenderContext@@A*/XorStr<0x54,42,0x25F16688>("\x6B\x32\x09\x27\x0A\x3C\x34\x3F\x39\x2F\x1D\x30\x0E\x15\x07\x1B\x10\x25\x26\x54\x38\x28\x3C\x02\x5F\x3F\x0B\x01\x14\x14\x00\x30\x1B\x1B\x02\x12\x00\x0D\x3A\x3B\x3D"+0x25F16688).s));
	AddyEngine->AddAddyByValue(/*RenderContext.Function.GetProjectMatrix*/XorStr<0x90,40,0x8fd3482d>("\xc2\xf4\xfc\xf7\xf1\xe7\xd5\xf8\xf6\xed\xff\xe3\xe8\xb3\xd8\xea\xce\xc2\xd6\xca\xcb\xcb\x88\xe0\xcd\xdd\xfa\xd9\xc3\xc7\xcb\xcc\xc4\xfc\xd3\xc7\xc6\xdc\xce"+0x8fd3482d).s, (DWORD)GetProcAddress(GetModuleHandle(/*i3GfxDx.dll*/XorStr<0x75,12,0x2a1dd9e6>("\x1c\x45\x30\x1e\x01\x3e\x03\x52\x19\x12\x13"+0x2a1dd9e6).s),/*?GetProjectMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ*/XorStr<0xDB,58,0x29861AEB>("\xE4\x9B\xB8\xAA\x8F\x92\x8E\x88\x86\x87\x91\xAB\x86\x9C\x9B\x83\x93\xAC\x84\xDD\xBD\x95\x9F\x96\x96\x86\xB6\x99\x99\x8C\x9C\x82\x8F\xBC\xBD\xAF\xBE\x45\x51\x43\x57\x5B\x71\x67\x60\x61\x3A\x47\x6A\x78\x7F\x67\x77\x50\x51\x4A\x49"+0x29861AEB).s));
	AddyEngine->AddAddyByValue(/*RenderContext.Function.GetViewMatrix*/XorStr<0xe5,37,0x782bf7c0>("\xb7\x83\x89\x8c\x8c\x98\xa8\x83\x83\x9a\x8a\x88\x85\xdc\xb5\x81\x9b\x95\x83\x91\x96\x94\xd5\xbb\x98\x8a\xa9\x69\x64\x75\x4e\x65\x71\x74\x6e\x70"+0x782bf7c0).s, (DWORD)GetProcAddress(GetModuleHandle(/*i3GfxDx.dll*/XorStr<0x81,12,0x5f0e4487>("\xe8\xb1\xc4\xe2\xfd\xc2\xff\xa6\xed\xe6\xe7"+0x5f0e4487).s),/*?GetViewMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ*/XorStr<0xC0,55,0x3E789821>("\xFF\x86\xA7\xB7\x92\xAC\xA3\xB0\x85\xA8\xBE\xB9\xA5\xB5\x8E\xA6\xE3\x83\xB7\xBD\xB0\xB0\xA4\x94\xB7\xB7\xAE\xBE\xA4\xA9\x9E\x9F\xB1\xA0\xA7\xB3\xA5\xB1\xB9\x93\x89\x8E\x83\xD8\xA1\x8C\x9A\x9D\x99\x89\xB2\xB3\xAC\xAF"+0x3E789821).s));
	AddyEngine->AddAddyByValue(/*RenderContext.Function.GetWorldMatrix*/XorStr<0x50,38,0x8d61d400>("\x02\x34\x3c\x37\x31\x27\x15\x38\x36\x2d\x3f\x23\x28\x73\x18\x2a\x0e\x02\x16\x0a\x0b\x0b\x48\x20\x0d\x1d\x3d\x04\x1e\x01\x0a\x22\x11\x05\x00\x1a\x0c"+0x8d61d400).s, (DWORD)GetProcAddress(GetModuleHandle(/*i3GfxDx.dll*/XorStr<0xbe,12,0x0715057b>("\xd7\x8c\x87\xa7\xba\x87\xbc\xeb\xa2\xab\xa4"+0x0715057b).s),/*?GetWorldMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ*/XorStr<0x22,56,0x0BF4AF1D>("\x1D\x64\x41\x51\x71\x48\x5A\x45\x4E\x66\x4D\x59\x5C\x46\x48\x71\x5B\x00\x66\x50\x58\x53\x5D\x4B\x79\x54\x52\x49\x5B\x47\x34\x01\x02\x12\x05\x00\x16\x06\x1C\x16\x3E\x2A\x2B\x24\x7D\x02\x31\x25\x20\x3A\x2C\x15\x16\x0F\x02"+0x0BF4AF1D).s));

	AddyEngine->AddAddyByPattern(/*GameContext.Base*/XorStr<0x3b,17,0x181f8233>("\x7c\x5d\x50\x5b\x7c\x2f\x2f\x36\x26\x3c\x31\x68\x05\x29\x3a\x2f"+0x181f8233).s, ADDY_GET_VALUE, 10, 4, /*PointBlank.exe*/XorStr<0x70,15,0x5464da92>("\x20\x1e\x1b\x1d\x00\x37\x1a\x16\x16\x12\x54\x1e\x04\x18"+0x5464da92).s, /*8B 4D 0C E8 ?? ?? ?? ?? 50 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ??*/XorStr<0x29,78,0xe184be23>("\x11\x68\x0b\x18\x69\x0e\x1f\x73\x11\x77\x0b\x14\x0a\x09\x17\x07\x06\x1a\x04\x03\x1d\x01\x00\x60\x74\x72\x63\x06\x7c\x66\x78\x77\x69\x75\x74\x6c\x72\x71\x6f\x6f\x6e\x72\x16\x6c\x75\x69\x68\x78\x66\x65\x7b\x63\x62\x7e\x60\x5f\x41\x5a\x21\x44\x26\x5e\x47\x2d\x51\x4a\x54\x53\x4d\x51\x50\x50\x4e\x4d\x53\x4b\x4a"+0xe184be23).s);
	AddyEngine->AddAddyByPattern(/*GameContext.Function.getNickForSlot*/XorStr<0xce,36,0x693e85b1>("\x89\xae\xbd\xb4\x91\xbc\xba\xa1\xb3\xaf\xac\xf7\x9c\xae\xb2\xbe\xaa\xb6\x8f\x8f\xcc\x84\x81\x91\xa8\x8e\x8b\x82\xac\x84\x9e\xbe\x82\x80\x84"+0x693e85b1).s, ADDY_FUNCTION_FINDSTART, NULL, NULL, /*PointBlank.exe*/XorStr<0x15,15,0x046a46f8>("\x45\x79\x7e\x76\x6d\x58\x77\x7d\x73\x75\x31\x45\x59\x47"+0x046a46f8).s, /*8B 55 08 6B D2 ?? 8B 45 FC 8D 84  10 ?? ?? ?? ??*/XorStr<0xF5,48,0x93CD4814>("\xCD\xB4\xD7\xCD\xCC\xDA\xCB\xC4\xDD\xC8\xBD\x20\x45\x30\x23\x3B\x3A\x26\x3F\x4A\x29\x3E\x3E\x2C\x4B\x4D\x2F\x28\x55\x32\x2B\x20\x35\x27\x27\x38\x26\x25\x3B\x23\x22\x3E\x20\x1F\x01\x1D\x1C"+0x93CD4814).s);
	AddyEngine->AddAddyByPattern(/*GameContext.Function.getNetCharaInfo*/XorStr<0x87,37,0x24993e0c>("\xc0\xe9\xe4\xef\xc8\xe3\xe3\xfa\xea\xe8\xe5\xbc\xd5\xe1\xfb\xf5\xe3\xf1\xf6\xf4\xb5\xfb\xf8\xea\xd1\xc5\xd5\xe1\xcb\xc5\xd7\xc7\xee\xc6\xcf\xc5"+0x24993e0c).s, ADDY_FUNCTION_GETCALL, 24, 0, /*PointBlank.exe*/XorStr<0x5e,15,0xb7061c0d>("\x0e\x30\x09\x0f\x16\x21\x08\x04\x08\x0c\x46\x0c\x12\x0e"+0xb7061c0d).s, /*8B 88 ?? ?? ?? ?? E8 ?? ?? ?? ?? 50 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 89 45 F4*/XorStr<0x47,96,0x4d12b3de>("\x7f\x0a\x69\x72\x73\x6c\x72\x71\x6f\x6f\x6e\x72\x6c\x6b\x75\x69\x68\x78\x1c\x62\x7b\x63\x62\x7e\x60\x5f\x41\x5d\x5c\x44\x5a\x59\x47\x5d\x59\x4a\x29\x55\x4d\x51\x50\x50\x4e\x4d\x53\x4b\x4a\x56\x48\x47\x59\x3f\x43\x5c\x42\x41\x5f\xbf\xbe\xa2\xbc\xbb\xa5\xb9\xb8\xa8\xb1\xc8\xab\xcf\xb5\xae\xca\xa8\xb1\xad\xac\xb4\xaa\xa9\xb7\xa7\xa6\xba\xa4\xa3\xbd\xa6\xa6\x80\x95\x97\x83\xe2\x91"+0x4d12b3de).s);
	AddyEngine->AddAddyByPattern(/*GameContext.Function.setEvent*/XorStr<0xc8,30,0xa68bbb43>("\x8f\xa8\xa7\xae\x8f\xa2\xa0\xbb\xb5\xa9\xa6\xfd\x92\xa0\xb8\xb4\xac\xb0\xb5\xb5\xf2\xae\xbb\xab\xa5\x97\x87\x8d\x90"+0xa68bbb43).s, ADDY_FUNCTION_GETCALL, 12, 4, /*PointBlank.exe*/XorStr<0x1f,15,0x097d5a03>("\x4f\x4f\x48\x4c\x57\x66\x49\x47\x49\x43\x07\x4f\x53\x49"+0x097d5a03).s, /*B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 8B 45 F8 8A 88 ?? ?? ?? ??*/XorStr<0x38,78,0xd45d1f25>("\x7a\x00\x1a\x04\x03\x1d\x01\x00\x60\x7e\x7d\x63\x7b\x7a\x66\x02\x70\x69\x75\x74\x6c\x72\x71\x6f\x6f\x6e\x72\x6c\x6b\x75\x6e\x15\x78\x1a\x62\x7b\x19\x65\x7e\x60\x5f\x41\x5d\x5c\x44\x5a\x59\x47\x57\x56\x4a\x53\x2e\x4d\x5a\x5a\x50\x37\x4a\x53\x4c\x34\x56\x4f\x40\x59\x45\x44\x5c\x42\x41\x5f\xbf\xbe\xa2\xbc\xbb"+0xd45d1f25).s);
	AddyEngine->AddAddyByPattern(/*GameContext.Function.getGameCharaMissionManager*/XorStr<0xcb,48,0x45f596fc>("\x8c\xad\xa0\xab\x8c\xbf\xbf\xa6\xb6\xac\xa1\xf8\x91\xad\xb7\xb9\xaf\xb5\xb2\xb0\xf1\x87\x84\x96\xa4\x85\x88\x83\xa4\x80\x88\x98\x8a\xa1\x84\x9d\x9c\x99\x9e\x9c\xbe\x95\x9b\x97\x90\x9d\x8b"+0x45f596fc).s, ADDY_FUNCTION_GETCALL, 19, 4, /*PointBlank.exe*/XorStr<0x3b,15,0x0a890d13>("\x6b\x53\x54\x50\x4b\x02\x2d\x23\x2d\x2f\x6b\x23\x3f\x2d"+0x0a890d13).s, /*32 C0 E9 ?? ?? ?? ?? B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 89 45 FC 83 7D FC 00 75 29*/XorStr<0x1c,99,0x2032aedb>("\x2f\x2f\x3e\x5c\x10\x01\x67\x1a\x04\x1a\x19\x07\x17\x16\x0a\x14\x13\x0d\x11\x10\x10\x73\x0b\x13\x0b\x0a\x16\x08\x07\x19\x05\x04\x1c\x02\x01\x1f\x05\x79\x62\x7c\x7b\x65\x79\x78\x68\x76\x75\x6b\x73\x72\x6e\x77\x12\x71\x11\x6b\x74\x10\x6e\x77\x67\x66\x7a\x64\x63\x7d\x61\x60\x40\x5e\x5d\x43\x5c\x5c\x46\x53\x5d\x49\x2c\x28\x4c\x55\x5d\x4f\x47\x35\x52\x35\x37\x55\x46\x47\x58\x4e\x4f\x5b\x4e\x44"+0x2032aedb).s);
	AddyEngine->AddAddyByPattern(/*GameContext.Function.ResetAbuseCounter*/XorStr<0x9a,39,0x7840ee50>("\xdd\xfa\xf1\xf8\xdd\xf0\xce\xd5\xc7\xdb\xd0\x8b\xe0\xd2\xc6\xca\xde\xc2\xc3\xc3\x80\xfd\xd5\xc2\xd7\xc7\xf5\xd7\xc3\xc4\xdd\xfa\xd5\xce\xd2\xc9\xdb\xcd"+0x7840ee50).s, ADDY_FUNCTION_GETCALL, 15, 4, /*PointBlank.exe*/XorStr<0x36,15,0x324912fd>("\x66\x58\x51\x57\x4e\x79\x50\x5c\x50\x54\x6e\x24\x3a\x26"+0x324912fd).s, /*89 4D FC B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 6A 00*/XorStr<0xf6,66,0xdc497d9e>("\xce\xce\xd8\xcd\xbe\xdb\xba\xbe\xde\xbd\x39\x21\x3d\x3c\x24\x3a\x39\x27\x37\x36\x2a\x34\x33\x2d\x4b\x37\x30\x2e\x2d\x33\x2b\x2a\x36\x28\x27\x39\x25\x24\x3c\x25\x5c\x3f\x63\x19\x02\x66\x1c\x05\x19\x18\x08\x16\x15\x0b\x13\x12\x0e\x10\x0f\x11\x04\x72\x14\x05\x06"+0xdc497d9e).s);
	AddyEngine->AddAddyByValue(/*GameContext.Function.SetAbuseCounter*/XorStr<0x29,37,0xe184be23>("\x6e\x4b\x46\x49\x6e\x41\x41\x44\x54\x4a\x47\x1a\x73\x43\x59\x5b\x4d\x53\x54\x52\x13\x6d\x5a\x34\x00\x20\x36\x37\x20\x05\x28\x3d\x27\x3e\x2e\x3e"+0xe184be23).s, ADDY_FUNCTION_FINDPREV, NULL, NULL, AddyEngine->GetAddyValueByKey(/*GameContext.Function.ResetAbuseCounter*/XorStr<0x6c,39,0x9052aed6>("\x2b\x0c\x03\x0a\x33\x1e\x1c\x07\x11\x0d\x02\x59\x3e\x0c\x14\x18\x08\x14\x11\x11\xae\xd3\xe7\xf0\xe1\xf1\xc7\xe5\xfd\xfa\xef\xc8\xe3\xf8\xe0\xfb\xf5\xe3"+0x9052aed6).s));
	AddyEngine->AddAddyByPattern(/*GameContext.Function.SetInviteUser*/XorStr<0xad,35,0x44f2144f>("\xea\xcf\xc2\xd5\xf2\xdd\xdd\xc0\xd0\xce\xc3\x96\xff\xcf\xd5\xdf\xc9\xd7\xd0\xae\xef\x91\xa6\xb0\x8c\xa8\xb1\xa1\xbd\xaf\x9e\xbf\xa8\xbc"+0x44f2144f).s, ADDY_FUNCTION_GETCALL, 16, 4, /*PointBlank.exe*/XorStr<0x40,15,0xc46bd066>("\x10\x2e\x2b\x2d\x30\x07\x2a\x26\x26\x22\x64\x2e\x34\x28"+0xc46bd066).s, /*8B 4D F8 51 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 8B 55 FC*/XorStr<0x30,72,0xa13b32b7>("\x08\x73\x12\x07\x70\x15\x70\x0f\x18\x0c\x0b\x1b\x7e\x04\x1e\x00\x7f\x61\x7d\x7c\x64\x7a\x79\x67\x77\x76\x6a\x0e\x74\x6d\x71\x70\x70\x6e\x6d\x73\x6b\x6a\x76\x68\x67\x79\x62\x19\x7c\x1e\x66\x7f\x25\x59\x42\x5c\x5b\x45\x59\x58\x48\x56\x55\x4b\x53\x52\x4e\x57\x32\x51\x47\x46\x54\x33\x35"+0xa13b32b7).s);
	AddyEngine->AddAddyByPattern(/*GameContext.Pointer.MySlotIdx*/XorStr<0xe5,30,0xd345f43c>("\xa2\x87\x8a\x8d\xaa\x85\x85\x98\x88\x96\x9b\xde\xa1\x9d\x9a\x9a\x81\x93\x85\xd6\xb4\x83\xa8\x90\x92\x8a\xb6\x64\x79"+0xd345f43c).s, ADDY_GET_VALUE, 16, 4, /*PointBlank.exe*/XorStr<0xd8,15,0xf50bce28>("\x88\xb6\xb3\xb5\xa8\x9f\xb2\xbe\x8e\x8a\xcc\x86\x9c\x80"+0xf50bce28).s, /*E8 ?? ?? ?? ?? 83 C4 08 8B 45 FC 8B 4D 08 89 88 ?? ?? ?? ?? 8B E5 5D C2 04 00 CC*/XorStr<0x29,81,0xe184be23>("\x6c\x12\x0b\x13\x12\x0e\x10\x0f\x11\x0d\x0c\x14\x0a\x09\x17\x00\x0a\x1a\x78\x08\x1d\x0e\x07\x60\x79\x00\x63\x70\x70\x66\x01\x0b\x69\x72\x09\x6c\x79\x0a\x6f\x60\x69\x72\x6b\x6d\x75\x6e\x6f\x78\x66\x65\x7b\x63\x62\x7e\x60\x5f\x41\x5d\x5c\x44\x5d\x24\x47\x2d\x5c\x4a\x5e\x28\x4d\x2d\x5d\x50\x41\x46\x53\x44\x45\x56\x34\x3b"+0xe184be23).s);
	if(AddyEngine->GetAddyValueByKey(/*GameContext.Pointer.MySlotIdx*/XorStr<0x29,30,0xe184be23>("\x6e\x4b\x46\x49\x6e\x41\x41\x44\x54\x4a\x47\x1a\x65\x59\x5e\x56\x4d\x5f\x49\x12\x70\x47\x6c\x2c\x2e\x36\x0a\x20\x3d"+0xe184be23).s) == NULL){
		// Failsafe kaybo
		AddyEngine->AddAddyByPattern(/*GameContext.Pointer.MySlotIdx*/XorStr<0xe5,30,0xd345f43c>("\xa2\x87\x8a\x8d\xaa\x85\x85\x98\x88\x96\x9b\xde\xa1\x9d\x9a\x9a\x81\x93\x85\xd6\xb4\x83\xa8\x90\x92\x8a\xb6\x64\x79"+0xd345f43c).s, ADDY_GET_VALUE, 17, 4, /*PointBlank.exe*/XorStr<0xd8,15,0xf50bce28>("\x88\xb6\xb3\xb5\xa8\x9f\xb2\xbe\x8e\x8a\xcc\x86\x9c\x80"+0xf50bce28).s, /*FF 15 ?? ?? ?? ?? 83 C4 08 8B 45 FC 8B 4D 08 89 88 ?? ?? ?? ?? 8B E5 5D C2 04 00 CC*/XorStr<0x6c,84,0x9052aed6>("\x2a\x2b\x4e\x5e\x45\x51\x4d\x4c\x54\x4a\x49\x57\x47\x46\x5a\x44\x43\x5d\x46\x4c\xa0\xc2\xb6\xa3\xb4\xbd\xa6\xbf\xca\xa9\xbe\xbe\xac\xcb\xcd\xaf\xa8\xd3\xb2\xa7\xd0\xb5\xa6\xaf\xb8\xa1\xa3\xbb\xa4\xa5\xbe\xa0\x9f\x81\x9d\x9c\x84\x9a\x99\x87\x97\x96\x8a\x93\xee\x8d\xeb\x9a\x90\x84\xf6\x93\xf7\x87\x96\x87\x8c\x99\x8a\x8b\x9c\xfe\xfd"+0x9052aed6).s);
	}
	AddyEngine->AddAddyByPattern(/*GameContext.Pointer.Rank*/XorStr<0xc5,25,0x973d5960>("\x82\xa7\xaa\xad\x8a\xa5\xa5\xb8\xa8\xb6\xbb\xfe\x81\xbd\xba\xba\xa1\xb3\xa5\xf6\x8b\xbb\xb5\xb7"+0x973d5960).s, ADDY_GET_VALUE, 17, 4, /*PointBlank.exe*/XorStr<0x27,15,0x2d76598a>("\x77\x47\x40\x44\x5f\x6e\x41\x4f\x41\x5b\x1f\x57\x4b\x51"+0x2d76598a).s, /*51 89 4D FC 8B 45 08 6B C0 ?? 8B 4D FC 0F B6 94 01 ?? ?? ?? ??*/XorStr<0x64,63,0xDC379274>("\x51\x54\x46\x5F\x51\x49\x5E\x2F\x4C\x2B\x2D\x4F\x48\x33\x52\x47\x41\x55\x46\x4F\x58\x4F\x38\x5B\x3F\x4D\x5E\x40\xBF\xA1\xBA\xC1\xA4\xB1\xC2\xA7\xCE\xCA\xAA\xBB\xCA\xAD\xCC\xB9\xB0\xA8\xA6\xB3\xA4\xA4\xB6\xA8\xA7\xB9\xA5\xA4\xBC\xA2\xA1\xBF\x9F\x9E"+0xDC379274).s);
	AddyEngine->AddAddyByPattern(/*GameContext.Size.Rank*/XorStr<0xd0,22,0x68cdc9c2>("\x97\xb0\xbf\xb6\x97\xba\xb8\xa3\xbd\xa1\xae\xf5\x8f\xb4\xa4\xba\xce\xb3\x83\x8d\x8f"+0x68cdc9c2).s, ADDY_GET_VALUE, 9, 1, /*PointBlank.exe*/XorStr<0xd4,15,0x25796a49>("\x84\xba\xbf\xb9\xac\x9b\xb6\xba\xb2\xb6\xf0\xba\x98\x84"+0x25796a49).s, /*51 89 4D FC 8B 45 08 6B C0 ?? 8B 4D FC 0F B6 94 01 ?? ?? ?? ??*/XorStr<0x64,63,0xDC379274>("\x51\x54\x46\x5F\x51\x49\x5E\x2F\x4C\x2B\x2D\x4F\x48\x33\x52\x47\x41\x55\x46\x4F\x58\x4F\x38\x5B\x3F\x4D\x5E\x40\xBF\xA1\xBA\xC1\xA4\xB1\xC2\xA7\xCE\xCA\xAA\xBB\xCA\xAD\xCC\xB9\xB0\xA8\xA6\xB3\xA4\xA4\xB6\xA8\xA7\xB9\xA5\xA4\xBC\xA2\xA1\xBF\x9F\x9E"+0xDC379274).s);

	AddyEngine->AddAddyByPattern(/*GameContext.Function.GetChannelUserCount*/XorStr<0x22,41,0x9d9122f6>("\x65\x42\x49\x40\x65\x48\x46\x5d\x4f\x53\x58\x03\x68\x5a\x5e\x52\x46\x5a\x5b\x5b\x18\x70\x5d\x4d\x79\x53\x5d\x53\x50\x5a\x2c\x14\x31\x26\x36\x06\x29\x32\x26\x3d"+0x9d9122f6).s, ADDY_FUNCTION_GETCALL, 12, 4, /*PointBlank.exe*/XorStr<0xe1,15,0xb0da1f8b>("\xb1\x8d\x8a\x8a\x91\xa4\x8b\x89\x87\x81\xc5\x89\x95\x8b"+0xb0da1f8b).s, /*B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 89 45 F8 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 3B 45 F8 7F 41*/XorStr<0xca,126,0x72b90299>("\x88\xf2\xec\xf2\xf1\xef\xef\xee\xf2\xec\xeb\xf5\xe9\xe8\xf8\x9c\xe2\xfb\xe3\xe2\xfe\xe0\xdf\xc1\xdd\xdc\xc4\xda\xd9\xc7\xd0\xab\xca\xa8\xd4\xcd\xab\xd7\xd0\xce\xcd\xd3\xcb\xca\xd6\xc8\xc7\xd9\xc5\xc4\xdc\xc5\xc7\xdf\x34\x34\x22\x45\x3c\x25\x44\x3e\x28\x36\x35\x2b\x33\x32\x2e\x30\x2f\x31\x2d\x2c\x34\x50\x2e\x37\x27\x26\x3a\x24\x23\x3d\x21\x20\x00\x1e\x1d\x03\x1c\x67\x06\x64\x10\x09\x6f\x13\x0c\x12\x11\x0f\x0f\x0e\x12\x0c\x0b\x15\x09\x08\x18\x0a\x78\x1b\x08\x08\x1e\x79\x78\x61\x75\x05\x64\x71\x77"+0x72b90299).s);
	AddyEngine->AddAddyByValue( /*GameContext.Pointer.ChannelUserCount*/XorStr<0x47,37,0x4d12b3de>("\x00\x29\x24\x2f\x08\x23\x23\x3a\x2a\x28\x25\x7c\x03\x3b\x3c\x38\x23\x3d\x2b\x74\x18\x34\x3c\x30\x31\x05\x0d\x37\x10\x01\x17\x25\x08\x1d\x07\x1e"+0x4d12b3de).s , ADDY_GET_VALUE, 0x45, 4, AddyEngine->GetAddyValueByKey( /*GameContext.Function.GetChannelUserCount*/XorStr<0xc8,41,0xa68bbb43>("\x8f\xa8\xa7\xae\x8f\xa2\xa0\xbb\xb5\xa9\xa6\xfd\x92\xa0\xb8\xb4\xac\xb0\xb5\xb5\xf2\x9a\xbb\xab\xa3\x89\x83\x8d\x8a\x80\x8a\xb2\x9b\x8c\x98\xa8\x83\x98\x80\x9b"+0xa68bbb43).s ) );

	AddyEngine->AddAddyByPattern(/*GameContext.Function.GetMaxChannelUserCount*/XorStr<0x9d,44,0x7e802c49>("\xda\xff\xf2\xc5\xe2\xcd\xcd\xd0\xc0\xde\xd3\x86\xef\xdf\xc5\xcf\xd9\xc7\xc0\xde\x9f\xf5\xd6\xc0\xf8\xd7\xcf\xfb\xd1\xdb\xd5\xd2\xd8\xd2\xea\xb3\xa4\xb0\x80\xab\xb0\xa8\xb3"+0x7e802c49).s, ADDY_FUNCTION_GETCALL, 17, 4, /*PointBlank.exe*/XorStr<0xc5,15,0x80e9d599>("\x95\xa9\xae\xa6\xbd\x88\xa7\xad\xa3\xa5\xe1\xb5\xa9\xb7"+0x80e9d599).s, /*A1 ?? ?? ?? ?? 33 C5 89 45 F0 56 89 4D A4 8B 4D A4 E8 ?? ?? ?? ??*/XorStr<0xb2,66,0x53ccc9ea>("\xf3\x82\x94\x8a\x89\x97\x87\x86\x9a\x84\x83\x9d\x81\x80\xe0\xf2\xf1\xe3\x87\xf0\xe6\xff\xf1\xe9\xfe\xfe\xec\x8b\xfe\xef\xe5\xe7\xf2\xeb\xed\xf5\xe2\x93\xf8\x98\xee\xfb\xe4\x9f\xfe\xeb\xa4\xc1\xa3\xd7\xc4\xa0\xde\xc7\xd7\xd6\xca\xd4\xd3\xcd\xd1\xd0\xd0\xce\xcd"+0x53ccc9ea).s);
	AddyEngine->AddAddyByValue( /*GameContext.Pointer.MaxChannelUserCount*/XorStr<0x3b,40,0x0a890d13>("\x7c\x5d\x50\x5b\x7c\x2f\x2f\x36\x26\x3c\x31\x68\x17\x27\x20\x24\x3f\x29\x3f\x60\x02\x31\x29\x11\x3b\x35\x3b\x38\x32\x34\x0c\x29\x3e\x2e\x1e\x31\x2a\x0e\x15"+0x0a890d13).s , ADDY_GET_VALUE, 12, 4, AddyEngine->GetAddyValueByKey( /*GameContext.Function.GetMaxChannelUserCount*/XorStr<0x1c,44,0x2032aedb>("\x5b\x7c\x73\x7a\x63\x4e\x4c\x57\x41\x5d\x52\x09\x6e\x5c\x44\x48\x58\x44\x41\x41\x1e\x76\x57\x47\x79\x54\x4e\x74\x50\x58\x54\x55\x59\x51\x6b\x4c\x25\x33\x01\x2c\x31\x2b\x32"+0x2032aedb).s ) );

	AddyEngine->AddAddyByPattern(/*PhaseReadyRoom.Function.SelfRemoveFromRoom*/XorStr<0x9a,43,0x7840ee50>("\xca\xf3\xfd\xee\xfb\xcd\xc5\xc0\xc6\xda\xf6\xca\xc9\xca\x86\xef\xdf\xc5\xcf\xd9\xc7\xc0\xde\x9f\xe1\xd6\xd8\xd3\xe4\xd2\xd5\xd6\xcc\xde\xfa\xcf\xd1\xd2\x92\xae\xad\xae"+0x7840ee50).s, ADDY_FUNCTION_FINDSTART, 13, NULL, /*PointBlank.exe*/XorStr<0x36,15,0x324912fd>("\x66\x58\x51\x57\x4e\x79\x50\x5c\x50\x54\x6e\x24\x3a\x26"+0x324912fd).s, "6A 00 6A 00 6A 00 6A 01 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 8B 4D FC C7 81 ?? ?? ?? ??");

	AddyEngine->AddAddyByPattern(/*GameCharaMissionManager.Function.InstallBomb*/XorStr<0x08,45,0xb1144061>("\x4f\x68\x67\x6e\x4f\x65\x6f\x7d\x71\x5c\x7b\x60\x67\x7c\x79\x79\x55\x78\x74\x7a\x7b\x78\x6c\x31\x66\x54\x4c\x40\x50\x4c\x49\x49\x06\x60\x44\x58\x58\x4c\x42\x43\x72\x5e\x5f\x51"+0xb1144061).s, ADDY_FUNCTION_GETCALL, 5, NULL, /*PointBlank.exe*/XorStr<0x3b,15,0x2811a56a>("\x6b\x53\x54\x50\x4b\x02\x2d\x23\x2d\x2f\x6b\x23\x3f\x2d"+0x2811a56a).s, /*6A 01 8B 4D ?? E8 ?? ?? ?? ?? B0 01 E9*/XorStr<0xAC,39,0xB8AAA28D>("\x9A\xEC\x8E\x9F\x81\x91\x8A\xF1\x94\x81\xF2\x97\x87\x86\x9A\xFE\x84\x9D\x81\x80\xE0\xFE\xFD\xE3\xFB\xFA\xE6\xF8\xF7\xE9\x88\xFB\xEC\xFD\xFF\xEF\x95\xE8"+0xB8AAA28D).s);
	AddyEngine->AddAddyByPattern(/*GameCharaMissionManager.Function.UnInstallBomb*/XorStr<0xc1,47,0x0ba9d68c>("\x86\xa3\xae\xa1\x86\xae\xa6\xba\xa8\x87\xa2\xbf\xbe\xa7\xa0\xbe\x9c\xb3\xbd\xb5\xb2\xb3\xa5\xf6\x9f\xaf\xb5\xbf\xa9\xb7\xb0\x8e\xcf\xb7\x8d\xad\x8b\x95\x93\x89\x85\x86\xa9\x83\x80\x8c"+0x0ba9d68c).s, ADDY_FUNCTION_GETCALL, 21, NULL, /*PointBlank.exe*/XorStr<0x87,15,0xf12f8c97>("\xd7\xe7\xe0\xe4\xff\xce\xe1\xef\xe1\xfb\xbf\xf7\xeb\xf1"+0xf12f8c97).s, "6A 00 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 32 C0");
	
	//AddyEngine->AddAddyByPattern(/*_NetCharaInfo.Function.getWeaponValue*/XorStr<0x15,38,0xc1959a1d>("\x4a\x58\x72\x6c\x5a\x72\x7a\x6e\x7c\x57\x71\x46\x4e\x0c\x65\x51\x4b\x45\x53\x41\x46\x44\x05\x4b\x48\x5a\x78\x55\x50\x42\x5c\x5a\x63\x57\x5b\x4d\x5c"+0xc1959a1d).s, ADDY_FUNCTION_GETCALL, 13, NULL, /*PointBlank.exe*/XorStr<0x9b,15,0xe97ec0e1>("\xcb\xf3\xf4\xf0\xeb\xe2\xcd\xc3\xcd\xcf\x8b\xc3\xdf\xcd"+0xe97ec0e1).s, /*83 7D DC 06 7D ?? 8B 4D ?? 51 8B 4D ?? E8 ?? ?? ?? ??*/XorStr<0x2E,54,0xBEE904B7>("\x16\x1C\x10\x06\x76\x13\x70\x76\x16\x07\x0E\x19\x0D\x7F\x1C\x02\x01\x1F\x78\x03\x62\x77\x00\x65\x79\x78\x68\x7C\x7B\x6B\x74\x0F\x6E\x7B\x14\x71\x6D\x6C\x74\x10\x6E\x77\x67\x66\x7A\x64\x63\x7D\x61\x60\x40\x5E\x5D"+0xBEE904B7).s);
	//AddyEngine->AddAddyByValue(/*_NetCharaInfo.Pointer.Weapon*/XorStr<0x29,29,0xe184be23>("\x76\x64\x4e\x58\x6e\x46\x4e\x42\x50\x7b\x5d\x52\x5a\x18\x67\x57\x50\x54\x4f\x59\x4f\x10\x68\x25\x20\x32\x2c\x2a"+0xe184be23).s, ADDY_GET_VALUE, 20, 4, AddyEngine->GetAddyValueByKey(/*_NetCharaInfo.Function.getWeaponValue*/XorStr<0x6c,38,0x9052aed6>("\x33\x23\x0b\x1b\x33\x19\x13\x01\x15\x3c\x18\x11\x17\x57\x3c\x0e\x12\x1e\x0a\x16\xef\xef\xac\xe4\xe1\xf1\xd1\xe2\xe9\xf9\xe5\xe5\xda\xec\xe2\xfa\xf5"+0x9052aed6).s));
	//AddyEngine->AddAddyByValue(/*_NetCharaInfo.Function.setWeaponValue*/XorStr<0xa8,38,0xc286a79a>("\xf7\xe7\xcf\xdf\xef\xc5\xcf\xdd\xd1\xf8\xdc\xd5\xdb\x9b\xf0\xc2\xd6\xda\xce\xd2\xd3\xd3\x90\xcc\xa5\xb5\x95\xa6\xa5\xb5\xa9\xa9\x9e\xa8\xa6\xbe\xa9"+0xc286a79a).s, AddyEngine->ParseAddyByOption(&sAddy(/*Temp*/XorStr<0xb5,5,0xe79abf54>("\xe1\xd3\xda\xc8"+0xe79abf54).s,AddyEngine->GetAddyValueByKey(/*_NetCharaInfo.Function.getWeaponValue*/XorStr<0xd9,38,0x9055d123>("\x86\x94\xbe\xa8\x9e\xb6\xbe\x92\x80\xab\x8d\x82\x8a\xc8\xa1\x9d\x87\x89\x9f\x85\x82\x80\xc1\x97\x94\x86\xa4\x91\x94\x86\x98\x96\xaf\x9b\x97\x89\x98"+0x9055d123).s)), ADDY_FUNCTION_FINDNEXT, NULL, NULL)->Value);

	AddyEngine->AddAddyByPattern(/*GameUDPHandler.Function.GetBase*/XorStr<0x38,32,0x6cd9d128>("\x7f\x58\x57\x5e\x69\x79\x6e\x77\x21\x2f\x26\x2f\x21\x37\x68\x01\x3d\x27\x29\x3f\x25\x22\x20\x61\x17\x34\x26\x11\x35\x26\x33"+0x6cd9d128).s, ADDY_FUNCTION_GETCALL, 4, NULL, /*PointBlank.exe*/XorStr<0xa1,15,0xe14e5e66>("\xf1\xcd\xca\xca\xd1\xe4\xcb\xc9\xc7\xc1\x85\xc9\xd5\xcb"+0xe14e5e66).s, /*8B 55 08 52 E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 5D*/XorStr<0x6c,51,0x9052aed6>("\x54\x2f\x4e\x5a\x45\x51\x42\x4b\x54\x40\x44\x57\x3d\x41\x5a\x44\x43\x5d\x41\x40\xa0\xbe\xbd\xa3\xbb\xba\xa6\xbf\xca\xa9\xc9\xb3\xac\xc8\xb6\xaf\xaf\xae\xb2\xac\xab\xb5\xa9\xa8\xb8\xa6\xa5\xbb\xa9\xd9"+0x9052aed6).s);	
	AddyEngine->AddAddyByPattern(/*GameUDPHandler.Function.WriteGameEvent_Fire*/XorStr<0x30,44,0x71d9fe9c>("\x77\x50\x5f\x56\x61\x71\x66\x7f\x59\x57\x5e\x57\x59\x4f\x10\x79\x35\x2f\x21\x37\x2d\x2a\x28\x69\x1f\x3b\x23\x3f\x29\x0a\x2f\x22\x35\x14\x24\x36\x3a\x21\x09\x11\x31\x2b\x3f"+0x71d9fe9c).s, ADDY_FUNCTION_GETCALL, 11, NULL, /*PointBlank.exe*/XorStr<0x9f,15,0x0ce2a5e2>("\xcf\xcf\xc8\xcc\xd7\xe6\xc9\xc7\xc9\xc3\x87\xcf\xd3\xc9"+0x0ce2a5e2).s, /*8B 55 08 52 E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 5D*/XorStr<0x49,51,0xe9bbf1f1>("\x71\x08\x6b\x79\x78\x6e\x7f\x68\x71\x67\x61\x74\x10\x6e\x77\x67\x66\x7a\x64\x63\x7d\x61\x60\x40\x5e\x5d\x43\x5c\x27\x46\x24\x50\x49\x2f\x53\x4c\x52\x51\x4f\x4f\x4e\x52\x4c\x4b\x55\x49\x48\x58\x4c\x3e"+0xe9bbf1f1).s);	
	
	AddyEngine->AddAddyByPattern(/*GameCharaManager.Base*/XorStr<0xbf,22,0x14bfd667>("\xf8\xa1\xac\xa7\x80\xac\xa4\xb4\xa6\x85\xa8\xa4\xaa\xab\xa8\xbc\xe1\x92\xb0\xa1\xb6"+0x14bfd667).s, ADDY_GET_VALUE, 5, 4, /*PointBlank.exe*/XorStr<0xd6,15,0x8edc2d7e>("\x86\xb8\xb1\xb7\xae\x99\xb0\xbc\xb0\xb4\xce\x84\x9a\x86"+0x8edc2d7e).s, /*8B 4D 08 51 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 89 45 F8*/XorStr<0x66,72,0x4957ef83>("\x5e\x25\x48\x5d\x2e\x4b\x5c\x55\x4e\x5a\x41\x51\x30\x4a\x54\x4a\x49\x57\x47\x46\x5a\x44\x43\x5d\x41\x40\xa0\xc4\xba\xa3\xbb\xba\xa6\xb8\xb7\xa9\xb5\xb4\xac\xb2\xb1\xaf\xa8\xd3\xb2\xd0\xac\xb5\xd3\xaf\xb8\xa6\xa5\xbb\xa3\xa2\xbe\xa0\x9f\x81\x9d\x9c\x84\x9d\x9f\x87\x9c\x9c\x8a\xed\x94"+0x4957ef83).s);
	AddyEngine->AddAddyByPattern(/*GameCharaManager.Function.getCharaByNetIdx*/XorStr<0x29,43,0xe0623e6d>("\x6e\x4b\x46\x49\x6e\x46\x4e\x42\x50\x7f\x52\x5a\x54\x51\x52\x4a\x17\x7c\x4e\x52\x5e\x4a\x56\x2f\x2f\x6c\x24\x21\x31\x05\x2f\x29\x3b\x2b\x09\x35\x03\x2b\x3b\x19\x35\x2a"+0xe0623e6d).s, ADDY_FUNCTION_FINDSTART, NULL, NULL, /*PointBlank.exe*/XorStr<0x96,15,0x39bf3412>("\xc6\xf8\xf1\xf7\xee\xd9\xf0\xfc\xf0\xf4\x8e\xc4\xda\xc6"+0x39bf3412).s, /*EB ?? 8B 45 08 8B 4D FC 8B 44 81 ?? 8B E5*/XorStr<0xAC,42,0xA61894D2>("\xE9\xEF\x8E\x90\x8F\x91\x8A\xF1\x94\x81\x83\x97\x88\x81\x9A\x83\xFE\x9D\x8A\xFB\xE0\x87\x81\xE3\xFC\x87\xE6\xF3\xFC\xE9\xF2\xFA\xEC\xF2\xF1\xEF\xE8\x93\xF2\x96\xE1"+0xA61894D2).s);
	//AddyEngine->AddAddyByPattern(/*GameCharaManager.Function.SetCharaWeaponSet*/XorStr<0xa6,44,0xf15e893f>("\xe1\xc6\xc5\xcc\xe9\xc3\xcd\xdf\xcf\xe2\xd1\xdf\xd3\xd4\xd1\xc7\x98\xf1\xcd\xd7\xd9\xcf\xd5\xd2\xd0\x91\x93\xa4\xb6\x80\xac\xa4\xb4\xa6\x9f\xac\xab\xbb\xa3\xa3\x9d\xaa\xa4"+0xf15e893f).s, ADDY_FUNCTION_GETCALL, 28, NULL, /*PointBlank.exe*/XorStr<0x6d,15,0x286ce30e>("\x3d\x01\x06\x1e\x05\x30\x1f\x15\x1b\x1d\x59\x1d\x01\x1f"+0x286ce30e).s, "74 ?? 8B 4D ?? 51 8B 55 ?? 8B 82 ?? ?? ?? ?? 50 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ??");
	AddyEngine->AddAddyByPattern(/*GameCharaManager.Function.RespawnChara*/XorStr<0x29,39,0xe184be23>("\x6e\x4b\x46\x49\x6e\x46\x4e\x42\x50\x7f\x52\x5a\x54\x51\x52\x4a\x17\x7c\x4e\x52\x5e\x4a\x56\x2f\x2f\x6c\x11\x21\x36\x36\x26\x3f\x27\x09\x23\x2d\x3f\x2f"+0xe184be23).s, ADDY_FUNCTION_GETCALL, 20, NULL, /*PointBlank.exe*/XorStr<0x6c,15,0x9052aed6>("\x3c\x02\x07\x01\x04\x33\x1e\x12\x1a\x1e\x58\x12\x00\x1c"+0x9052aed6).s, "8B C8 E8 ?? ?? ?? ?? 50 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 25 01 00 00 80");

	AddyEngine->AddAddyByPattern(/*GameFramework.Base*/XorStr<0x61,19,0x618f69ff>("\x26\x03\x0e\x01\x23\x14\x06\x05\x0c\x1d\x04\x1e\x06\x40\x2d\x11\x02\x17"+0x618f69ff).s, ADDY_GET_VALUE, 8, 4, /*PointBlank.exe*/XorStr<0xcd,15,0x9c9d1ed1>("\x9d\xa1\xa6\xbe\xa5\x90\xbf\xb5\xbb\xbd\xf9\xbd\xa1\xbf"+0x9c9d1ed1).s, /*8D 95 C0 FE FF FF 52 B9 ?? ?? ?? ? E8 ?? ?? ?? ?? 8B C8*/XorStr<0x16,56,0x1de67272>("\x2e\x53\x38\x20\x2f\x3b\x5f\x2d\x3e\x59\x65\x01\x64\x65\x04\x63\x60\x07\x1d\x1b\x0a\x69\x15\x0d\x11\x10\x10\x0e\x0d\x13\x0b\x0a\x16\x08\x18\x7c\x02\x1b\x03\x02\x1e\x00\x7f\x61\x7d\x7c\x64\x7a\x79\x67\x70\x0b\x6a\x08\x74"+0x1de67272).s);
	AddyEngine->AddAddyByPattern(/*GameFramework.Pointer.I3InputMouse*/XorStr<0x29,35,0xe184be23>("\x6e\x4b\x46\x49\x6b\x5c\x4e\x5d\x54\x45\x5c\x46\x5e\x18\x67\x57\x50\x54\x4f\x59\x4f\x10\x76\x73\x08\x2c\x33\x31\x31\x0b\x28\x3d\x3a\x2f"+0xe184be23).s, ADDY_GET_VALUE, 11, 4, /*PointBlank.exe*/XorStr<0x6c,15,0x9052aed6>("\x3c\x02\x07\x01\x04\x33\x1e\x12\x1a\x1e\x58\x12\x00\x1c"+0x9052aed6).s, /*51 D9 EE D9 1C 24 8B 45 F8 8B 88 ?? ?? ?? ?? FF 15 ?? ?? ?? ?? 51*/XorStr<0x29,66,0xe184be23>("\x1c\x1b\x0b\x68\x14\x0e\x6a\x75\x11\x76\x0a\x14\x04\x75\x17\x0a\x0d\x1a\x03\x7e\x1d\x0a\x0a\x60\x07\x7a\x63\x7c\x07\x66\x7f\x70\x69\x75\x74\x6c\x72\x71\x6f\x6f\x6e\x72\x6c\x6b\x75\x10\x11\x78\x68\x6f\x7b\x63\x62\x7e\x60\x5f\x41\x5d\x5c\x44\x5a\x59\x47\x5d\x58"+0xe184be23).s);
	AddyEngine->AddAddyByPattern(/*GameFramework.Pointer.I3InputKeyboard*/XorStr<0xeb,38,0x3cdba6b3>("\xac\x8d\x80\x8b\xa9\x82\x90\x9f\x96\x83\x9a\x84\x9c\xd6\xa9\x95\x92\x92\x89\x9b\x8d\x2e\x48\x31\x4a\x6a\x75\x73\x73\x43\x6c\x73\x69\x63\x6c\x7c\x6b"+0x3cdba6b3).s, ADDY_GET_VALUE, 9, 4, /*PointBlank.exe*/XorStr<0x87,15,0x24993e0c>("\xd7\xe7\xe0\xe4\xff\xce\xe1\xef\xe1\xfb\xbf\xf7\xeb\xf1"+0x24993e0c).s, /*8B 45 FC 50 8B 4D F8 8B 89 ?? ?? ?? ??*/XorStr<0x5e,39,0xb7061c0d>("\x66\x1d\x40\x55\x57\x43\x22\x26\x46\x52\x58\x49\x52\x29\x4c\x59\x2a\x4f\x36\x49\x52\x4b\x36\x55\x4e\x4e\x58\x46\x45\x5b\x43\x42\x5e\x40\xbf\xa1\xbd\xbc"+0xb7061c0d).s);
	AddyEngine->AddAddyByPattern(/*GameFramework.Function.RaycastClosest*/XorStr<0x84,38,0x6505140f>("\xc3\xe4\xeb\xe2\xce\xfb\xeb\xe6\xe9\xfa\xe1\xfd\xfb\xbf\xd4\xe6\xfa\xf6\xe2\xfe\xf7\xf7\xb4\xc9\xfd\xe4\xfd\xfe\xd3\xd5\xe1\xcf\xcb\xd6\xc3\xd4\xdc"+0x6505140f).s, ADDY_FUNCTION_GETCALL, 25, NULL, /*PointBlank.exe*/XorStr<0x1b,15,0xc5c96128>("\x4b\x73\x74\x70\x6b\x62\x4d\x43\x4d\x4f\x0b\x43\x5f\x4d"+0xc5c96128).s, "C7 45 F0 ?? ?? ?? ?? 6A 00 8B 45 ?? 50 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ??");	

	AddyEngine->AddAddyByPattern(/*PhysixResult.Pointer.Distance*/XorStr<0xf0,30,0x774a4f84>("\xa0\x99\x8b\x80\x9d\x8d\xa4\x92\x8b\x8c\x96\x8f\xd2\xad\x91\x96\x6e\x75\x67\x71\x2a\x41\x6f\x74\x7c\x68\x64\x68\x69"+0x774a4f84).s, ADDY_GET_VALUE, 13, 4, /*PointBlank.exe*/XorStr<0x02,15,0x2c39e8d7>("\x52\x6c\x6d\x6b\x72\x45\x64\x68\x64\x60\x22\x68\x76\x6a"+0x2c39e8d7).s, /*E9 ?? ?? ?? ?? 8B 8D 48 FF FF FF 81 C1 ?? ?? ?? ?? E8 ?? ?? ?? ??*/XorStr<0x53,66,0x1e12c9cb>("\x16\x6d\x75\x69\x68\x78\x66\x65\x7b\x63\x62\x7e\x60\x5f\x41\x5a\x21\x44\x5d\x22\x47\x5c\x51\x4a\x2d\x2a\x4d\x28\x29\x50\x37\x34\x53\x4c\x44\x56\x34\x49\x59\x45\x44\x5c\x42\x41\x5f\xbf\xbe\xa2\xbc\xbb\xa5\xc3\xbf\xa8\xb6\xb5\xab\xb3\xb2\xae\xb0\xaf\xb1\xad\xac"+0x1e12c9cb).s);
	AddyEngine->AddAddyByPattern(/*PhysixResult.Function.ReadData*/XorStr<0x33,31,0xf40c9e74>("\x63\x5c\x4c\x45\x5e\x40\x6b\x5f\x48\x49\x51\x4a\x11\x06\x34\x2c\x20\x30\x2c\x29\x29\x66\x1b\x2f\x2a\x28\x09\x2f\x3b\x31"+0xf40c9e74).s, ADDY_FUNCTION_GETCALL, 17, 4, /*PointBlank.exe*/XorStr<0xd5,15,0xa4d49fd4>("\x85\xb9\xbe\xb6\xad\x98\xb7\xbd\xb3\xb5\xf1\x85\x99\x87"+0xa4d49fd4).s, /*E9 ?? ?? ?? ?? 8B 8D 48 FF FF FF 81 C1 ?? ?? ?? ?? E8 ?? ?? ?? ??*/XorStr<0x59,66,0x32cf357e>("\x1c\x63\x7b\x63\x62\x7e\x60\x5f\x41\x5d\x5c\x44\x5a\x59\x47\x50\x2b\x4a\x53\x28\x4d\x5a\x57\x50\x37\x34\x53\x32\x33\x56\x31\x3e\x59\x42\x4a\x5c\x3e\x4f\x5f\xbf\xbe\xa2\xbc\xbb\xa5\xb9\xb8\xa8\xb6\xb5\xab\xc9\xb5\xae\xb0\xaf\xb1\xad\xac\xb4\xaa\xa9\xb7\xa7\xa6"+0x32cf357e).s);

	AddyEngine->AddAddyByValue(/*GameCharaBase.Base*/XorStr<0xe7,19,0x36468e2c>("\xa0\x89\x84\x8f\xa8\x84\x8c\x9c\x8e\xb2\x90\x81\x96\xda\xb7\x97\x84\x9d"+0x36468e2c).s, AddyEngine->GetAddyValueByKey(/*GameContext.Base*/XorStr<0x08,17,0x8da8f3dc>("\x4f\x68\x67\x6e\x4f\x62\x60\x7b\x75\x69\x66\x3d\x56\x74\x65\x72"+0x8da8f3dc).s) - 0x38);
	AddyEngine->AddAddyByPattern(/*GameCharaBase.Function.getGameCharaBoneContext*/XorStr<0xfe,47,0x71ebf2be>("\xb9\x9e\x6d\x64\x41\x6b\x65\x77\x67\x45\x69\x7a\x6f\x25\x4a\x78\x60\x6c\x64\x78\x7d\x7d\x3a\x72\x73\x63\x5f\x78\x77\x7e\x5f\x75\x7f\x6d\x41\x63\x4d\x4d\x41\x66\x49\x49\x5c\x4c\x52\x5f"+0x71ebf2be).s, ADDY_FUNCTION_GETCALL, 12, NULL, /*PointBlank.exe*/XorStr<0xff,15,0x753bd0a0>("\xaf\x6f\x68\x6c\x77\x46\x69\x67\x69\x63\x27\x6f\x73\x69"+0x753bd0a0).s, "D9 1C 24 8B 4D FC 8B 89 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ??");	
	AddyEngine->AddAddyByPattern(/*GameCharaBase.Function.getGameCharaWeaponContext*/XorStr<0x06,49,0x78877e8c>("\x41\x66\x65\x6c\x49\x63\x6d\x7f\x6f\x4d\x71\x62\x77\x3d\x52\x60\x78\x74\x6c\x70\x75\x75\x32\x7a\x7b\x6b\x67\x40\x4f\x46\x67\x4d\x47\x55\x49\x7e\x4f\x4a\x5c\x42\x40\x6c\x5f\x5f\x46\x56\x4c\x41"+0x78877e8c).s, ADDY_FUNCTION_GETCALL, 10, NULL, /*PointBlank.exe*/XorStr<0x73,15,0x82bed04d>("\x23\x1b\x1c\x18\x03\x3a\x15\x1b\x15\x17\x53\x1b\x07\xe5"+0x82bed04d).s, /*0F B6 D0 85 D2 75 ?? 8B 4D F8 E8 ?? ?? ?? ??*/XorStr<0x4E,45,0x40144352>("\x7E\x09\x70\x13\x64\x73\x10\x65\x76\x6F\x6D\x79\x1E\x69\x7C\x6A\x6B\x7F\x5F\x5E\x42\x5B\x26\x45\x52\x23\x48\x2F\x52\x4B\x29\x55\x4E\x50\x4F\x51\x4D\x4C\x54\x4A\x49\x57\x47\x46"+0x40144352).s);	
	AddyEngine->AddAddyByPattern(/*GameCharaBase.Function.getGameCharaCollisionContext*/XorStr<0xbe,52,0x4146c2db>("\xf9\xde\xad\xa4\x81\xab\xa5\xb7\xa7\x85\xa9\xba\xaf\xe5\x8a\xb8\xa0\xac\xa4\xb8\xbd\xbd\xfa\xb2\xb3\xa3\x9f\xb8\xb7\xbe\x9f\xb5\xbf\xad\x81\xa2\x8d\x8f\x88\x8c\x95\x8e\x87\x87\xa9\x84\x82\x99\x8b\x97\x84"+0x4146c2db).s, ADDY_FUNCTION_GETCALL, 10, NULL, /*PointBlank.exe*/XorStr<0x2b,15,0x7f30fa8c>("\x7b\x43\x44\x40\x5b\x72\x5d\x53\x5d\x5f\x1b\x53\x4f\x5d"+0x7f30fa8c).s, /*E8 ?? ?? ?? ?? EB ?? 8B 4D ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? E9*/XorStr<0xD6,69,0xC1F4CE82>("\x93\xEF\xF8\xE6\xE5\xFB\xE3\xE2\xFE\xE0\xDF\xC1\xDD\xDC\xC4\xA0\xA4\xC7\xD7\xD6\xCA\xD3\xAE\xCD\xDA\xAB\xD0\xCE\xCD\xD3\xB1\xCD\xD6\xC8\xC7\xD9\xC5\xC4\xDC\xC2\xC1\xDF\x3F\x3E\x22\x3B\x46\x25\x45\x3F\x28\x4C\x32\x2B\x33\x32\x2E\x30\x2F\x31\x2D\x2C\x34\x2A\x29\x37\x5D\x20"+0xC1F4CE82).s);	
	AddyEngine->AddAddyByPattern(/*GameCharaBase.Function.setCharaWeapon*/XorStr<0x70,38,0x8654a7f0>("\x37\x10\x1f\x16\x37\x1d\x17\x05\x19\x3b\x1b\x08\x19\x53\x38\x0a\xee\xe2\xf6\xea\xeb\xeb\xa8\xf4\xed\xfd\xc9\xe3\xed\xff\xef\xd8\xf5\xf0\xe2\xfc\xfa"+0x8654a7f0).s, ADDY_FUNCTION_GETCALL, 21, NULL, /*PointBlank.exe*/XorStr<0x32,15,0x685baa95>("\x62\x5c\x5d\x5b\x42\x75\x54\x58\x54\x50\x12\x58\x46\x5a"+0x685baa95).s, /*B9 E8 03 00 00 F7 F1 50 8B 55 ?? 52 8B 45 ?? 8B 88 ?? ?? ?? ?? E8 ?? ?? ?? ??*/XorStr<0x56,78,0xFA80A00A>("\x14\x6E\x78\x1C\x62\x7B\x6C\x6E\x7E\x6F\x50\x41\x52\x53\x44\x23\x51\x47\x2E\x58\x4A\x5E\x5C\x4D\x56\x2D\x50\x44\x47\x53\x4B\x4A\x56\x42\x4A\x59\x42\x39\x5C\x49\x4B\x5F\xBF\xBE\xA2\xBB\xC6\xA5\xBE\xBF\xA8\xB6\xB5\xAB\xB3\xB2\xAE\xB0\xAF\xB1\xAD\xAC\xB4\xD0\xAE\xB7\xA7\xA6\xBA\xA4\xA3\xBD\xA1\xA0\x80\x9E\x9D"+0xFA80A00A).s);	
	AddyEngine->AddAddyByPattern(/*GameCharaBase.Function.Cmd_Respawn*/XorStr<0x29,35,0xe184be23>("\x6e\x4b\x46\x49\x6e\x46\x4e\x42\x50\x70\x52\x47\x50\x18\x71\x4d\x57\x59\x4f\x55\x52\x50\x11\x03\x2c\x26\x1c\x16\x20\x35\x37\x29\x3e\x24"+0xe184be23).s, ADDY_NORMAL, 6, 0, /*PointBlank.exe*/XorStr<0x6c,15,0x9052aed6>("\x3c\x02\x07\x01\x04\x33\x1e\x12\x1a\x1e\x58\x12\x00\x1c"+0x9052aed6).s, /*E8 ?? ?? ?? ?? C3 53 8B DC 83 EC 08 83 E4 F0 83 C4 04 55 8B 6B 04*/XorStr<0x49,66,0xe9bbf1f1>("\x0c\x72\x6b\x73\x72\x6e\x70\x6f\x71\x6d\x6c\x74\x6a\x69\x77\x1b\x6a\x7a\x6e\x6f\x7d\x66\x1d\x40\x25\x21\x43\x5c\x56\x46\x22\x2b\x49\x5a\x53\x4c\x55\x5d\x4f\x35\x45\x52\x35\x44\x55\x4e\x44\x58\x3a\x4e\x5b\x4c\x49\x5e\x4a\xb5\xa1\xba\xc1\xa4\xb3\xc4\xa7\xb8\xbd"+0xe9bbf1f1).s);
	AddyEngine->AddAddyByValue(/*GameCharaBase.Function.getGameCharaAnimContext*/XorStr<0x13,47,0xf5fce60b>("\x54\x75\x78\x73\x54\x70\x78\x68\x7a\x5e\x7c\x6d\x7a\x0e\x67\x57\x4d\x47\x51\x4f\x48\x46\x07\x4d\x4e\x58\x6a\x4f\x42\x55\x72\x5a\x52\x46\x54\x77\x59\x51\x54\x79\x54\x52\x49\x5b\x47\x34"+0xf5fce60b).s,
								ADDY_FUNCTION_GETCALL, 
								20, 
								NULL, 
								AddyEngine->ParseAddyByOption(AddyEngine->FindAddyByPattern(/*Temp*/XorStr<0xca,5,0x899f7dbe>("\x9e\xae\xa1\xbd"+0x899f7dbe).s, /*PointBlank.exe*/XorStr<0x8a,15,0xb8fd1b41>("\xda\xe4\xe5\xe3\xfa\xcd\xfc\xf0\xfc\xf8\xba\xf0\xee\xf2"+0xb8fd1b41).s, /*88 45 C7 8B 8D ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8*/XorStr<0xEE,48,0xA6AC9396>("\xD6\xD7\xD0\xC5\xC7\xD3\xB7\xC2\xD6\xCF\xBA\xD9\xC2\xBF\xDC\xC2\xC1\xDF\x3F\x3E\x22\x3C\x3B\x25\x39\x38\x28\x4C\x32\x2B\x33\x32\x2E\x30\x2F\x31\x2D\x2C\x34\x2A\x29\x37\x20\x5B\x3A\x58\x24"+0xA6AC9396).s), ADDY_FUNCTION_GETCALL, 9, NULL)->Value
							  );

	AddyEngine->AddAddyByPattern(/*GameCharaBase.Function.getCharaNetIdx*/XorStr<0x4f,38,0x7b72f668>("\x08\x31\x3c\x37\x10\x3c\x34\x24\x36\x1a\x38\x29\x3e\x72\x1b\x2b\x31\x03\x15\x0b\x0c\x0a\x4b\x01\x02\x1c\x2a\x02\x0a\x1e\x0c\x20\x0a\x04\x38\x16\x0b"+0x7b72f668).s, ADDY_FUNCTION_GETCALL, 14, NULL, /*PointBlank.exe*/XorStr<0x14,15,0x0dd3cd99>("\x44\x7a\x7f\x79\x6c\x5b\x76\x7a\x72\x76\x30\x7a\x58\x44"+0x0dd3cd99).s, /*D8 4D ?? D9 5D ?? E9 ?? ?? ?? ?? 8B 4D ?? E8 ?? ?? ?? ??*/XorStr<0x42,57,0x77474DF1>("\x06\x7B\x64\x71\x02\x67\x77\x76\x6A\x0F\x75\x6D\x7B\x0B\x70\x6E\x6D\x73\x11\x6C\x76\x68\x67\x79\x65\x64\x7C\x62\x61\x7F\x5F\x5E\x42\x5B\x26\x45\x52\x23\x48\x56\x55\x4B\x29\x55\x4E\x50\x4F\x51\x4D\x4C\x54\x4A\x49\x57\x47\x46"+0x77474DF1).s);	
	AddyEngine->AddAddyByPattern(/*GameCharaBase.Function.eventFall*/XorStr<0xf0,33,0xa6b43a44>("\xb7\x90\x9f\x96\xb7\x9d\x97\x85\x99\xbb\x9b\x88\x99\xd3\xb8\x8a\x6e\x62\x76\x6a\x6b\x6b\x28\x62\x7e\x6c\x64\x7f\x4a\x6c\x62\x63"+0xa6b43a44).s, ADDY_FUNCTION_GETCALL, 25, NULL, /*PointBlank.exe*/XorStr<0x66,15,0xcb0b3353>("\x36\x08\x01\x07\x1e\x29\x00\x0c\x00\x04\x5e\x14\x0a\x16"+0xcb0b3353).s, /*6A 00 68 FF FF 00 00 68 FF 00 00 00 8B 4D ?? 83 C1 ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ??*/XorStr<0x44,90,0x1D90568E>("\x72\x04\x66\x77\x78\x69\x7C\x73\x6C\x0B\x08\x6F\x16\x17\x72\x63\x64\x75\x66\x67\x78\x6F\x62\x7B\x1A\x1B\x7E\x6F\x50\x41\x52\x53\x44\x55\x56\x47\x50\x2B\x4A\x5F\x28\x4D\x51\x50\x50\x49\x41\x53\x37\x44\x56\x48\x47\x59\x3F\x43\x5C\x42\x41\x5F\xBF\xBE\xA2\xBC\xBB\xA5\xB9\xB8\xA8\xB1\xC8\xAB\xCF\xB5\xAE\xCA\xA8\xB1\xAD\xAC\xB4\xAA\xA9\xB7\xA7\xA6\xBA\xA4\xA3"+0x1D90568E).s);	
	AddyEngine->AddAddyByPattern(/*GameCharaBase.Function.getCurHP*/XorStr<0xa1,32,0xec4c5e10>("\xe6\xc3\xce\xc1\xe6\xce\xc6\xda\xc8\xe8\xca\xdf\xc8\x80\xe9\xc5\xdf\xd1\xc7\xdd\xda\xd8\x99\xdf\xdc\xce\xf8\xc9\xcf\xf6\xef"+0xec4c5e10).s, ADDY_FUNCTION_FINDSTART, NULL, NULL, /*PointBlank.exe*/XorStr<0x03,15,0x05e6734c>("\x53\x6b\x6c\x68\x73\x4a\x65\x6b\x65\x67\x23\x6b\x77\x75"+0x05e6734c).s, /*8B 4D FC 81 C1 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? E8 ?? ?? ?? ??*/XorStr<0x76,78,0x0BDB9F11>("\x4E\x35\x58\x4D\x3E\x5B\x3A\x3E\x5E\x47\xB1\xA1\xC1\xB2\xA4\xBA\xB9\xA7\xB7\xB6\xAA\xB4\xB3\xAD\xB1\xB0\xB0\xD4\xAA\xB3\xAB\xAA\xB6\xA8\xA7\xB9\xA5\xA4\xBC\xA2\xA1\xBF\x98\xE3\x82\xE0\x9C\x85\xE3\x9F\x88\x96\x95\x8B\x93\x92\x8E\x90\x8F\x91\x8D\x8C\x94\xF0\x8E\x97\x87\x86\x9A\x84\x83\x9D\x81\x80\xE0\xFE\xFD"+0x0BDB9F11).s);
	AddyEngine->AddAddyByPattern(/*GameCharaBase.Function.writeData*/XorStr<0x29,33,0xe184be23>("\x6e\x4b\x46\x49\x6e\x46\x4e\x42\x50\x70\x52\x47\x50\x18\x71\x4d\x57\x59\x4f\x55\x52\x50\x11\x37\x33\x2b\x37\x21\x01\x27\x33\x29"+0xe184be23).s, ADDY_FUNCTION_GETCALL, 16, NULL, /*PointBlank.exe*/XorStr<0x6c,15,0x9052aed6>("\x3c\x02\x07\x01\x04\x33\x1e\x12\x1a\x1e\x58\x12\x00\x1c"+0x9052aed6).s, /*D9 45 E4 51 D9 1C 24 8B 4D ?? 81 C1 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 4D*/XorStr<0x49,69,0xe9bbf1f1>("\x0d\x73\x6b\x78\x78\x6e\x0a\x64\x71\x67\x62\x74\x11\x6f\x77\x69\x1a\x7a\x69\x68\x7d\x66\x1d\x40\x55\x26\x43\x5b\x5a\x46\x5f\x59\x49\x29\x5a\x4c\x52\x51\x4f\x4f\x4e\x52\x4c\x4b\x55\x49\x48\x58\x3c\x42\x5b\x43\x42\x5e\x40\xbf\xa1\xbd\xbc\xa4\xba\xb9\xa7\xb0\xcb\xaa\xbf\xc8"+0xe9bbf1f1).s);
	AddyEngine->AddAddyByValue(/*GameCharaBase.Function.readData*/XorStr<0x29,32,0xe184be23>("\x6e\x4b\x46\x49\x6e\x46\x4e\x42\x50\x70\x52\x47\x50\x18\x71\x4d\x57\x59\x4f\x55\x52\x50\x11\x32\x24\x23\x27\x00\x24\x32\x26"+0xe184be23).s, ADDY_FUNCTION_FINDNEXT, NULL, NULL, AddyEngine->GetAddyValueByKey(/*GameCharaBase.Function.writeData*/XorStr<0x6c,33,0x9052aed6>("\x2b\x0c\x03\x0a\x33\x19\x13\x01\x15\x37\x17\x04\x1d\x57\x3c\x0e\x12\x1e\x0a\x16\xef\xef\xac\xf4\xf6\xec\xf2\xe2\xcc\xe8\xfe\xea"+0x9052aed6).s));
	AddyEngine->AddAddyByPattern(/*GameCharaBase.Pointer.invicibleTime*/XorStr<0xeb,36,0x3cdba6b3>("\xac\x8d\x80\x8b\xac\x98\x90\x80\x92\xb6\x94\x85\x92\xd6\xa9\x95\x92\x92\x89\x9b\x8d\x2e\x68\x6c\x75\x6d\x66\x6f\x65\x64\x6c\x5e\x62\x61\x68"+0x3cdba6b3).s, ADDY_GET_VALUE, 12, 4, /*PointBlank.exe*/XorStr<0x87,15,0x24993e0c>("\xd7\xe7\xe0\xe4\xff\xce\xe1\xef\xe1\xfb\xbf\xf7\xeb\xf1"+0x24993e0c).s, /*D9 45 E4 51 D9 1C 24 8B 4D ?? 81 C1 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 4D*/XorStr<0x5e,69,0xb7061c0d>("\x1a\x66\x40\x55\x57\x43\x21\x51\x46\x52\x59\x49\x2e\x52\x4c\x5c\x2d\x4f\x42\x45\x52\x4b\x36\x55\x42\x33\x58\x46\x45\x5b\x44\x4c\x5e\x3c\xb1\xa1\xbd\xbc\xa4\xba\xb9\xa7\xb7\xb6\xaa\xb4\xb3\xad\xcb\xb7\xb0\xae\xad\xb3\xab\xaa\xb6\xa8\xa7\xb9\xa5\xa4\xbc\xa5\xdc\xbf\x94\xe5"+0xb7061c0d).s);

	AddyEngine->AddAddyByPattern(/*GameCharaCollisionContext.Pointer.CrosshairTarget*/XorStr<0xb4,50,0xadaa0e31>("\xf3\xd4\xdb\xd2\xfb\xd1\xdb\xc9\xdd\xfe\xd1\xd3\xac\xa8\xb1\xaa\xab\xab\x85\xa8\xa6\xbd\xaf\xb3\xb8\xe3\x9e\xa0\xb9\xbf\xa6\xb6\xa6\xfb\x95\xa5\xb7\xaa\xa9\xb3\xbd\xb4\xac\x8b\x81\x93\x85\x86\x90"+0xadaa0e31).s, ADDY_GET_VALUE, 12, 4, /*PointBlank.exe*/XorStr<0xcf,15,0x27cab0d5>("\x9f\xbf\xb8\xbc\xa7\x96\xb9\xb7\xb9\xb3\xf7\xbf\xa3\xb9"+0x27cab0d5).s, /*C7 45 EC 01 00 00 00 8B 4D ?? 81 C1 ?? ?? ?? ?? E8 ?? ?? ?? ?? 85 C0*/XorStr<0x29,69,0xe184be23>("\x6a\x1d\x0b\x18\x18\x0e\x6a\x73\x11\x02\x02\x14\x05\x06\x17\x08\x09\x1a\x0b\x0c\x1d\x06\x7d\x60\x75\x06\x63\x7b\x7a\x66\x7f\x79\x69\x09\x7a\x6c\x72\x71\x6f\x6f\x6e\x72\x6c\x6b\x75\x69\x68\x78\x1c\x62\x7b\x63\x62\x7e\x60\x5f\x41\x5d\x5c\x44\x5a\x59\x47\x50\x5c\x4a\x28\x5c"+0xe184be23).s);	
	AddyEngine->AddAddyByPattern(/*GameCharaCollisionContext.Function.ReadData*/XorStr<0xff,44,0x4d149dd8>("\xb8\x61\x6c\x67\x40\x6c\x64\x74\x66\x4b\x66\x66\x67\x65\x7e\x67\x60\x7e\x52\x7d\x7d\x60\x70\x6e\x63\x36\x5f\x6f\x75\x7f\x69\x77\x70\x4e\x0f\x70\x46\x45\x41\x62\x46\x5c\x48"+0x4d149dd8).s, ADDY_FUNCTION_GETCALL, 16, NULL, /*PointBlank.exe*/XorStr<0xf4,15,0x42592779>("\xa4\x9a\x9f\x99\x8c\xbb\x96\x9a\x92\x96\xd0\x9a\x78\x64"+0x42592779).s, /*C7 45 EC 01 00 00 00 8B 4D ?? 81 C1 ?? ?? ?? ?? E8 ?? ?? ?? ?? 85 C0*/XorStr<0x6c,69,0x9052aed6>("\x2f\x5a\x4e\x5b\x45\x51\x37\x30\x54\x45\x47\x57\x48\x49\x5a\x4b\x4c\x5d\x4e\x4f\xa0\xb9\xc0\xa3\xb0\xc1\xa6\xb8\xb7\xa9\xb2\xba\xac\xce\xbf\xaf\xaf\xae\xb2\xac\xab\xb5\xa9\xa8\xb8\xa6\xa5\xbb\xd9\xa5\xbe\xa0\x9f\x81\x9d\x9c\x84\x9a\x99\x87\x97\x96\x8a\x93\x99\x8d\xed\x9f"+0x9052aed6).s);	
	
	AddyEngine->AddAddyByPattern(/*GameCharaBoneContext.Function.writeYaw*/XorStr<0x7c,39,0xcdf8c19c>("\x3b\x1c\x13\x1a\xc3\xe9\xe3\xf1\xe5\xc7\xe9\xe9\xed\xca\xe5\xe5\xf8\xe8\xf6\xfb\xbe\xd7\xe7\xfd\xf7\xe1\xff\xf8\xf6\xb7\xed\xe9\xf5\xe9\xfb\xc6\xc1\xd6"+0xcdf8c19c).s, ADDY_FUNCTION_GETCALL, 6, NULL, /*PointBlank.exe*/XorStr<0x8c,15,0x64232087>("\xdc\xe2\xe7\xe1\xe4\xd3\xfe\xf2\xfa\xfe\xb8\xf2\xe0\xfc"+0x64232087).s, /*D9 1C 24 8B 4D E0 E8 ?? ?? ?? ?? 8B 4D E0 83 C1 ??*/XorStr<0x3E,51,0xF92EF395>("\x7A\x06\x60\x70\x01\x63\x76\x71\x66\x7F\x0A\x69\x7E\x0F\x6C\x08\x7E\x6F\x15\x69\x72\x6C\x6B\x75\x69\x68\x78\x66\x65\x7B\x63\x62\x7E\x67\x22\x41\x56\x27\x44\x20\x56\x47\x50\x5A\x4A\x28\x5D\x4D\x51\x50"+0xF92EF395).s);	
	AddyEngine->AddAddyByPattern(/*GameCharaBoneContext.Function.writePitch*/XorStr<0xb8,41,0x4c9587a6>("\xff\xd8\xd7\xde\xff\xd5\xdf\xcd\xa1\x83\xad\xad\xa1\x86\xa9\xa9\xbc\xac\xb2\xbf\xe2\x8b\xbb\xa1\xb3\xa5\xbb\xbc\xba\xfb\xa1\xa5\xb1\xad\xbf\x8b\xb5\xa9\xbd\xb7"+0x4c9587a6).s, ADDY_FUNCTION_GETCALL, 10, NULL, /*PointBlank.exe*/XorStr<0xb0,15,0x2d4e8d5a>("\xe0\xde\xdb\xdd\xc0\xf7\xda\xd6\xd6\xd2\x94\xde\xc4\xd8"+0x2d4e8d5a).s, /*8B 4D D4 E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? EB ?? C7 45*/XorStr<0x72,57,0x5C5ABF63>("\x4A\x31\x54\x41\x32\x57\x3C\x4D\x5A\x3E\x44\x5D\x41\x40\xA0\xBE\xBD\xA3\xBB\xBA\xA6\xB8\xB7\xA9\xB2\xC9\xAC\xCE\xB6\xAF\xD5\xA9\xB2\xAC\xAB\xB5\xA9\xA8\xB8\xA6\xA5\xBB\xA3\xA2\xBE\xDA\xE2\x81\x9D\x9C\x84\xE6\x91\x87\x9C\x9C"+0x5C5ABF63).s);	
	AddyEngine->AddAddyByPattern(/*GameCharaBoneContext.Function.getBones*/XorStr<0x99,39,0x60b13de7>("\xde\xfb\xf6\xf9\xde\xf6\xfe\xd2\xc0\xe0\xcc\xca\xc0\xe5\xc8\xc6\xdd\xcf\xd3\xd8\x83\xe8\xda\xde\xd2\xc6\xda\xdb\xdb\x98\xd0\xdd\xcd\xf8\xd4\xd2\xd8\xcd"+0x60b13de7).s, ADDY_FUNCTION_GETCALL, 19, NULL, /*PointBlank.exe*/XorStr<0xde,15,0x08ad80b1>("\x8e\xb0\x89\x8f\x96\xa1\x88\x84\x88\x8c\xc6\x8c\x92\x8e"+0x08ad80b1).s, "D9 1C 24 8B 4D FC 8B 89 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ??");	
	AddyEngine->AddAddyByValue(/*GameCharaBoneContext.Size.BonesAlign*/XorStr<0x41,37,0xa54167e9>("\x06\x23\x2e\x21\x06\x2e\x26\x3a\x28\x08\x24\x22\x28\x0d\x20\x3e\x25\x37\x2b\x20\x7b\x05\x3e\x22\x3c\x74\x19\x33\x33\x3b\x2c\x21\x0d\x0b\x04\x0a"+0xa54167e9).s, AddyEngine->ParseAddyByOption(&sAddy(/*Temp*/XorStr<0xd5,5,0x9f18e49f>("\x81\xb3\xba\xa8"+0x9f18e49f).s,AddyEngine->GetAddyValueByKey(/*GameCharaBoneContext.Function.getBones*/XorStr<0x15,39,0xfe260042>("\x52\x77\x7a\x7d\x5a\x72\x7a\x6e\x7c\x5c\x70\x4e\x44\x61\x4c\x4a\x51\x43\x5f\x5c\x07\x6c\x5e\x42\x4e\x5a\x46\x5f\x5f\x1c\x54\x51\x41\x74\x58\x56\x5c\x49"+0xfe260042).s)), ADDY_GET_VALUE, 22, 4)->Value);

	//AddyEngine->AddAddyByPattern(/*GameCharaWeaponContext.Function.getCurrent*/XorStr<0x4c,43,0x930421d1>("\x0b\x2c\x23\x2a\x13\x39\x33\x21\x35\x02\x33\x36\x28\x36\x34\x18\x33\x33\x2a\x3a\x18\x15\x4c\x25\x11\x0b\x05\x13\x01\x06\x04\x45\x0b\x08\x1a\x2c\x05\x03\x00\x16\x1a\x01"+0x930421d1).s, ADDY_FUNCTION_GETCALL, 7, NULL, /*PointBlank.exe*/XorStr<0x2f,15,0x53738fb3>("\x7f\x5f\x58\x5c\x47\x76\x59\x57\x59\x53\x17\x5f\x43\x59"+0x53738fb3).s, /*E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 89 45 F4 C7 45 EC 00 00 00 00*/XorStr<0x51,66,0xBF902D3B>("\x14\x6A\x73\x6B\x6A\x76\x68\x67\x79\x65\x64\x7C\x62\x61\x7F\x58\x23\x42\x20\x5C\x45\x23\x5F\x48\x56\x55\x4B\x53\x52\x4E\x50\x4F\x51\x4D\x4C\x54\x4D\x4F\x57\x4C\x4C\x5A\x3D\x48\x5D\x3D\x48\xA0\xB5\xB7\xA3\xC1\xC6\xA6\xB7\xB8\xA9\xBA\xBB\xAC\xBD\xBE\xAF\xA0\xA1"+0xBF902D3B).s);	
	//AddyEngine->AddAddyByValue(/*GameCharaWeaponContext.Pointer.CurrentWeaponIndex*/XorStr<0x40,50,0x7eaf8a43>("\x07\x20\x2f\x26\x07\x2d\x27\x35\x29\x1e\x2f\x2a\x3c\x22\x20\x0c\x3f\x3f\x26\x36\x2c\x21\x78\x07\x37\x30\x34\x2f\x39\x2f\x70\x1c\x15\x13\x10\x06\x0a\x11\x31\x02\x09\x19\x05\x05\x25\x03\x0a\x0a\x08"+0x7eaf8a43).s, AddyEngine->ParseAddyByOption(&sAddy(/*Temp*/XorStr<0xca,5,0xd3cfd56f>("\x9e\xae\xa1\xbd"+0xd3cfd56f).s,AddyEngine->GetAddyValueByKey(/*GameCharaWeaponContext.Function.getCurrent*/XorStr<0xa1,43,0xbe5ace95>("\xe6\xc3\xce\xc1\xe6\xce\xc6\xda\xc8\xfd\xce\xcd\xdd\xc1\xc1\xf3\xde\xdc\xc7\xd1\xcd\xc2\x99\xfe\xcc\xd4\xd8\xc8\xd4\xd1\xd1\xee\xa6\xa7\xb7\x87\xb0\xb4\xb5\xad\xa7\xbe"+0xbe5ace95).s)), ADDY_GET_VALUE, 12, 2)->Value);
	//if(*(BYTE*)(AddyEngine->GetAddyValueByKey(/*GameCharaWeaponContext.Function.getCurrent*/XorStr<0x65,43,0x07f62a27>("\x22\x07\x0a\x0d\x2a\x02\x0a\x1e\x0c\x39\x0a\x11\x01\x1d\x1d\x37\x1a\x18\x03\x1d\x01\x0e\x55\x3a\x08\x10\x1c\xf4\xe8\xed\xed\xaa\xe2\xe3\xf3\xcb\xfc\xf8\xf9\xe9\xe3\xfa"+0x07f62a27).s) + 16) == 0xE8){
	//	AddyEngine->AddAddyByValue(/*GameCharaWeaponContext.Function.DecryptWeaponIndex*/XorStr<0xad,51,0xa665bea1>("\xea\xcf\xc2\xd5\xf2\xda\xd2\xc6\xd4\xe1\xd2\xd9\xc9\xd5\xd5\xff\xd2\xd0\xcb\xa5\xb9\xb6\xed\x82\xb0\xa8\xa4\xbc\xa0\xa5\xa5\xe2\x89\xab\xac\xa2\xa8\xa2\xa7\x83\xb0\xb7\xa7\xb7\xb7\x93\xb5\xb8\xb8\xa6"+0xa665bea1).s, AddyEngine->ParseAddyByOption(&sAddy(/*Temp*/XorStr<0xb4,5,0x3269c0c9>("\xe0\xd0\xdb\xc7"+0x3269c0c9).s,AddyEngine->GetAddyValueByKey(/*GameCharaWeaponContext.Function.getCurrent*/XorStr<0x34,43,0x014d2c09>("\x73\x54\x5b\x52\x7b\x51\x5b\x49\x5d\x6a\x5b\x5e\x30\x2e\x2c\x00\x2b\x2b\x32\x22\x30\x3d\x64\x0d\x39\x23\x2d\x3b\x39\x3e\x3c\x7d\x33\x30\x22\x14\x2d\x2b\x28\x3e\x32\x29"+0x014d2c09).s)), ADDY_FUNCTION_GETCALL, 16, 2)->Value);
	//}
	AddyEngine->AddAddyByPattern(/*GameCharaWeaponContext.Function.SafeGetWeapon*/XorStr<0x8f,46,0xdbc65617>("\xc8\xf1\xfc\xf7\xd0\xfc\xf4\xe4\xf6\xcf\xfc\xfb\xeb\xf3\xf3\xdd\xf0\xce\xd5\xc7\xdb\xd0\x8b\xe0\xd2\xc6\xca\xde\xc2\xc3\xc3\x80\xfc\xd1\xd7\xd7\xf4\xd1\xc1\xe1\xd2\xd9\xc9\xd5\xd5"+0xdbc65617).s, ADDY_FUNCTION_GETCALL, 10, NULL, /*PointBlank.exe*/XorStr<0x9d,15,0x0bd8a6c8>("\xcd\xf1\xf6\xce\xd5\xe0\xcf\xc5\xcb\xcd\x89\xcd\xd1\xcf"+0x0bd8a6c8).s, /*8B 55 FC 8B 42 ?? 50 8B 4D FC E8 ?? ?? ?? ??*/XorStr<0xEE,45,0x67EB84C4>("\xD6\xAD\xD0\xC4\xC7\xD3\xB2\xB6\xD6\xCF\xBA\xD9\xCE\xC9\xDC\xC2\xC1\xDF\x35\x31\x22\x3B\x46\x25\x32\x43\x28\x4F\x49\x2B\x49\x35\x2E\x30\x2F\x31\x2D\x2C\x34\x2A\x29\x37\x27\x26"+0x67EB84C4).s);	

	AddyEngine->AddAddyByPattern(/*WeaponBase.Function.Reset*/XorStr<0x88,26,0x6b613881>("\xdf\xec\xeb\xfb\xe3\xe3\xcc\xee\xe3\xf4\xbc\xd5\xe1\xfb\xf5\xe3\xf1\xf6\xf4\xb5\xce\xf8\xed\xfa\xd4"+0x6b613881).s, ADDY_FUNCTION_GETCALL, 7, NULL, /*PointBlank.exe*/XorStr<0x68,15,0x54f96212>("\x38\x06\x03\x05\x18\x2f\x02\x0e\x1e\x1a\x5c\x16\x0c\x10"+0x54f96212).s, /*51 89 4D FC 8B 4D FC E8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 25 FF FF 00 00*/XorStr<0xFD,66,0x7D0F6CCA>("\xC8\xCF\xDF\x38\x38\x22\x37\x40\x25\x40\x44\x28\x31\x48\x2B\x38\x49\x2E\x49\x53\x31\x57\x2B\x34\x2A\x29\x37\x27\x26\x3A\x24\x23\x3D\x21\x20\x00\x64\x1A\x03\x1B\x1A\x06\x18\x17\x09\x15\x14\x0C\x12\x11\x0F\x02\x04\x12\x75\x72\x15\x70\x71\x18\x09\x0A\x1B\x0C\x0D"+0x7D0F6CCA).s);	
	AddyEngine->AddAddyByPattern(/*WeaponBase.Function.GetSubAmmoCount*/XorStr<0xb8,36,0x5795b0b5>("\xef\xdc\xdb\xcb\xd3\xd3\xfc\xde\xb3\xa4\xec\x85\xb1\xab\xa5\xb3\xa1\xa6\xa4\xe5\x8b\xa8\xba\x9c\xa5\xb3\x93\xbe\xb9\xba\x95\xb8\xad\xb7\xae"+0x5795b0b5).s, ADDY_FUNCTION_GETCALL, 8, NULL, /*PointBlank.exe*/XorStr<0xf5,15,0x6d6c80df>("\xa5\x99\x9e\x96\x8d\xb8\x97\x9d\x93\x95\xd1\x65\x79\x67"+0x6d6c80df).s, /*F3 0F 11 40 ?? 8B 4D F4 E8 ?? ?? ?? ??*/XorStr<0x59,39,0x4477412C>("\x1F\x69\x7B\x6C\x1B\x7E\x6E\x51\x41\x56\x53\x44\x5A\x59\x47\x50\x2B\x4A\x5F\x28\x4D\x28\x5B\x50\x34\x4A\x53\x4B\x4A\x56\x48\x47\x59\x45\x44\x5C\x42\x41"+0x4477412C).s);	
	AddyEngine->AddAddyByPattern(/*WeaponBase.Function.SetSubAmmoCount*/XorStr<0x8d,36,0x438bd974>("\xda\xeb\xee\xe0\xfe\xfc\xd1\xf5\xe6\xf3\xb9\xde\xec\xf4\xf8\xe8\xf4\xf1\xf1\x8e\xf2\xc7\xd7\xf7\xd0\xc4\xe6\xc5\xc4\xc5\xe8\xc3\xd8\xc0\xdb"+0x438bd974).s, ADDY_FUNCTION_GETCALL, 10, NULL, /*PointBlank.exe*/XorStr<0x65,15,0xf6a50811>("\x35\x09\x0e\x06\x1d\x28\x07\x0d\x03\x05\x41\x15\x09\x17"+0xf6a50811).s, /*8B 8D 08 FF FF FF 51 8B 4D EC E8 ?? ?? ?? ??*/XorStr<0x25,45,0x83BA14EE>("\x1D\x64\x07\x10\x6D\x0A\x1B\x14\x0D\x68\x69\x10\x77\x74\x13\x72\x73\x16\x02\x09\x19\x02\x79\x1C\x09\x7A\x1F\x05\x02\x62\x06\x7C\x65\x79\x78\x68\x76\x75\x6B\x73\x72\x6E\x70\x6F"+0x83BA14EE).s);	
	AddyEngine->AddAddyByPattern(/*WeaponBase.Function.DoFire*/XorStr<0x79,27,0x15ebf7bd>("\x2e\x1f\x1a\x0c\x12\x10\x3d\xe1\xf2\xe7\xad\xc2\xf0\xe8\xe4\xfc\xe0\xe5\xe5\xa2\xc9\xe1\xc9\xf9\xe3\xf7"+0x15ebf7bd).s, ADDY_FUNCTION_GETCALL, 7, NULL, /*PointBlank.exe*/XorStr<0xb8,15,0x8f60e1e0>("\xe8\xd6\xd3\xd5\xc8\xff\xd2\xde\xae\xaa\xec\xa6\xbc\xa0"+0x8f60e1e0).s, /*6A 00 6A 00 8B 4D F4 E8 ?? ?? ?? ?? 8B 45*/XorStr<0x0E,42,0xC6EF3C8F>("\x38\x4E\x30\x21\x22\x33\x22\x54\x36\x27\x28\x39\x22\x59\x3C\x29\x5A\x3F\x66\x15\x02\x66\x1C\x05\x19\x18\x08\x16\x15\x0B\x13\x12\x0E\x10\x0F\x11\x0A\x71\x14\x01\x03"+0xC6EF3C8F).s);	
	AddyEngine->AddAddyByPattern(/*WeaponBase.Function.DoLineCollision*/XorStr<0x6e,36,0x5bf47b3c>("\x39\x0a\x11\x01\x1d\x1d\x36\x14\x05\x12\x56\x3f\x0f\x15\x1f\x09\x17\x10\xee\xaf\xc6\xec\xc8\xec\xe8\xe2\xcb\xe6\xe6\xe7\xe5\xfe\xe7\xe0\xfe"+0x5bf47b3c).s, ADDY_FUNCTION_GETCALL, 8, NULL, /*PointBlank.exe*/XorStr<0x62,15,0x278f8a8a>("\x32\x0c\x0d\x0b\x12\x25\x04\x08\x04\x00\x42\x08\x16\x0a"+0x278f8a8a).s, /*52 8D 45 E8 50 8B 4D D8 E8 ?? ?? ?? ?? EB*/XorStr<0x29,42,0xe184be23>("\x1c\x18\x0b\x14\x69\x0e\x1b\x05\x11\x77\x0b\x14\x00\x06\x17\x00\x7b\x1a\x0f\x78\x1d\x7a\x07\x60\x04\x7a\x63\x7b\x7a\x66\x78\x77\x69\x75\x74\x6c\x72\x71\x6f\x15\x13"+0xe184be23).s);	
	AddLog(/*Init Logger >>*/XorStr<0x5c,15,0x4a87e5f7>("\x15\x33\x37\x2b\x40\x2d\x0d\x04\x03\x00\x14\x47\x56\x57"+0x4a87e5f7).s);
	for(int i = 0; i < AddyEngine->GetAddySize(); i++)
	{
		sAddy* Addy = AddyEngine->GetAddyByIndex(i);
		AddLog(/*%s = 0x%p;*/XorStr<0x3b,11,0x40619b32>("\x1e\x4f\x1d\x03\x1f\x70\x39\x67\x33\x7f"+0x40619b32).s, Addy->Key, Addy->Value);
	}
	AddLog(/*Init Logger <<*/XorStr<0x84,15,0xa7b1c3c6>("\xcd\xeb\xef\xf3\xa8\xc5\xe5\xec\xeb\xe8\xfc\xaf\xac\xad"+0xa7b1c3c6).s);
	

	BaseLog("#define XFHPB.Function.ReadBaseValue                        0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Function.ReadBaseValue"));
	BaseLog("#define XFHPB.Import.i3CollideeLine::SetEnd                 0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Import.i3CollideeLine::SetEnd"));
	BaseLog("#define XFHPB.Import.i3AiContext::getLocalTime              0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Import.i3AiContext::getLocalTime"));
	//BaseLog("#define XFHPB.Import.i3RenderContext::EndRender             0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Import.i3RenderContext::EndRender"));
	BaseLog("#define XFHPB.Import.i3RenderContext::DrawIndexedPrim       0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Import.i3RenderContext::DrawIndexedPrim"));
	BaseLog("#define XFHPB.Values.GaugeMultiplier                        0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Values.GaugeMultiplier"));
	BaseLog("#define XFHPB.Pointer.QuickChange                           0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Pointer.QuickChange"));
	BaseLog("#define XFHPB.Pointer.NoReload                              0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Pointer.NoReload"));
	BaseLog("#define XFHPB.Pointer.FireSpeed                             0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Pointer.FireSpeed"));
	BaseLog("#define XFHPB.Function.SetHitCollision                      0x%X\n", AddyEngine->GetAddyValueByKey("XFHPB.Function.SetHitCollision"));

	BaseLog("#define Temp                                                0x%X", AddyEngine->GetAddyValueByKey("Temp"));
	BaseLog("#define XFHPB.Address.Hook.RecoilV                          0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Address.Hook.RecoilV"));
	BaseLog("#define XFHPB.Address.Hook.RecoilH                          0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Address.Hook.RecoilH"));
	BaseLog("#define XFHPB.Address.Hook.Range                            0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Address.Hook.Range"));
	BaseLog("#define XFHPB.Address.Hook.Damage                           0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Address.Hook.Damage"));
	BaseLog("#define XFHPB.Address.Hook.Burst                            0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Address.Hook.Burst"));
	BaseLog("#define XFHPB.Address.Hook.SearchFile                       0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Address.Hook.SearchFile"));
	BaseLog("#define XFHPB.Address.Function.SearchFile                   0x%X\n", AddyEngine->GetAddyValueByKey("XFHPB.Address.Function.SearchFile"));

	BaseLog("#define XFHPB.Address.Modify.MovingSpeed                    0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Address.Modify.MovingSpeed"));
	BaseLog("#define XFHPB.Address.Modify.BugView                        0x%X", AddyEngine->GetAddyValueByKey("XFHPB.Address.Modify.BugView"));
	BaseLog("#define XFHPB.Address.Modify.Burst                          0x%X\n", AddyEngine->GetAddyValueByKey("XFHPB.Address.Modify.Burst"));

	BaseLog("#define RenderContext.Base                                  0x%X", AddyEngine->GetAddyValueByKey("RenderContext.Base"));
	BaseLog("#define RenderContext.Function.GetProjectMatrix             0x%X", AddyEngine->GetAddyValueByKey("RenderContext.Function.GetProjectMatrix"));
	BaseLog("#define RenderContext.Function.GetViewMatrix                0x%X", AddyEngine->GetAddyValueByKey("RenderContext.Function.GetViewMatrix"));
	BaseLog("#define RenderContext.Function.GetWorldMatrix               0x%X\n", AddyEngine->GetAddyValueByKey("RenderContext.Function.GetWorldMatrix"));

	BaseLog("#define GameContext.Base                                    0x%X", AddyEngine->GetAddyValueByKey("GameContext.Base"));
	BaseLog("#define GameContext.Function.getNickForSlot                 0x%X", AddyEngine->GetAddyValueByKey("GameContext.Function.getNickForSlot"));
	BaseLog("#define GameContext.Function.getNetCharaInfo                0x%X", AddyEngine->GetAddyValueByKey("GameContext.Function.getNetCharaInfo"));
	BaseLog("#define GameContext.Function.setEvent                       0x%X", AddyEngine->GetAddyValueByKey("GameContext.Function.setEvent"));
	BaseLog("#define GameContext.Function.getGameCharaMissionManager     0x%X", AddyEngine->GetAddyValueByKey("GameContext.Function.getGameCharaMissionManager"));
	BaseLog("#define GameContext.Function.ResetAbuseCounter              0x%X", AddyEngine->GetAddyValueByKey("GameContext.Function.ResetAbuseCounter"));
	BaseLog("#define GameContext.Function.SetAbuseCounter                0x%X", AddyEngine->GetAddyValueByKey("GameContext.Function.SetAbuseCounter"));
	BaseLog("#define GameContext.Function.SetInviteUser                  0x%X", AddyEngine->GetAddyValueByKey("GameContext.Function.SetInviteUser"));
	BaseLog("#define GameContext.Pointer.MySlotIdx                       0x%X\n", AddyEngine->GetAddyValueByKey("GameContext.Pointer.MySlotIdx"));

	BaseLog("#define GameContext.Pointer.Rank                            0x%X", AddyEngine->GetAddyValueByKey("GameContext.Pointer.Rank"));
	BaseLog("#define GameContext.Size.Rank                               0x%X\n", AddyEngine->GetAddyValueByKey("GameContext.Size.Rank"));
	
	BaseLog("#define GameContext.Function.GetChannelUserCount            0x%X", AddyEngine->GetAddyValueByKey("GameContext.Function.GetChannelUserCount"));
	BaseLog("#define GameContext.Pointer.ChannelUserCount                0x%X\n", AddyEngine->GetAddyValueByKey("GameContext.Pointer.ChannelUserCount"));
	
	BaseLog("#define GameContext.Function.GetMaxChannelUserCount         0x%X", AddyEngine->GetAddyValueByKey("GameContext.Function.GetMaxChannelUserCount"));
    BaseLog("#define GameContext.Pointer.MaxChannelUserCount             0x%X\n", AddyEngine->GetAddyValueByKey("GameContext.Pointer.MaxChannelUserCount"));
	
	BaseLog("#define PhaseReadyRoom.Function.SelfRemoveFromRoom          0x%X\n", AddyEngine->GetAddyValueByKey("PhaseReadyRoom.Function.SelfRemoveFromRoom"));

	BaseLog("#define GameCharaMissionManager.Function.InstallBomb        0x%X", AddyEngine->GetAddyValueByKey("GameCharaMissionManager.Function.InstallBomb"));
	BaseLog("#define GameCharaMissionManager.Function.UnInstallBomb      0x%X\n", AddyEngine->GetAddyValueByKey("GameCharaMissionManager.Function.UnInstallBomb"));
	
	//BaseLog("#define _NetCharaInfo.Function.getWeaponValue               0x%X", AddyEngine->GetAddyValueByKey("_NetCharaInfo.Function.getWeaponValue"));
	//BaseLog("#define _NetCharaInfo.Pointer.Weapon                        0x%X", AddyEngine->GetAddyValueByKey("_NetCharaInfo.Pointer.Weapon"));
	//BaseLog("#define _NetCharaInfo.Function.setWeaponValue               0x%X\n", AddyEngine->GetAddyValueByKey("_NetCharaInfo.Function.setWeaponValue"));

	BaseLog("#define GameUDPHandler.Function.GetBase                     0x%X", AddyEngine->GetAddyValueByKey("GameUDPHandler.Function.GetBase"));
	BaseLog("#define GameUDPHandler.Function.WriteGameEvent_Fire         0x%X\n", AddyEngine->GetAddyValueByKey("GameUDPHandler.Function.WriteGameEvent_Fire"));

	BaseLog("#define GameCharaManager.Base                               0x%X", AddyEngine->GetAddyValueByKey("GameCharaManager.Base"));
	BaseLog("#define GameCharaManager.Function.getCharaByNetIdx          0x%X", AddyEngine->GetAddyValueByKey("GameCharaManager.Function.getCharaByNetIdx"));
	//BaseLog("#define GameCharaManager.Function.SetCharaWeaponSet         0x%X", AddyEngine->GetAddyValueByKey("GameCharaManager.Function.SetCharaWeaponSet"));
	BaseLog("#define GameCharaManager.Function.RespawnChara              0x%X\n", AddyEngine->GetAddyValueByKey("GameCharaManager.Function.RespawnChara"));

	BaseLog("#define GameFramework.Base                                  0x%X", AddyEngine->GetAddyValueByKey("GameFramework.Base"));
	BaseLog("#define GameFramework.Pointer.I3InputMouse                  0x%X", AddyEngine->GetAddyValueByKey("GameFramework.Pointer.I3InputMouse"));
	BaseLog("#define GameFramework.Pointer.I3InputKeyboard               0x%X", AddyEngine->GetAddyValueByKey("GameFramework.Pointer.I3InputKeyboard"));
	BaseLog("#define GameFramework.Function.RaycastClosest               0x%X\n", AddyEngine->GetAddyValueByKey("GameFramework.Function.RaycastClosest"));

	BaseLog("#define PhysixResult.Pointer.Distance                       0x%X", AddyEngine->GetAddyValueByKey("PhysixResult.Pointer.Distance"));
	BaseLog("#define PhysixResult.Function.ReadData                      0x%X\n", AddyEngine->GetAddyValueByKey("PhysixResult.Function.ReadData"));

	BaseLog("#define GameCharaBase.Base                                  0x%X", AddyEngine->GetAddyValueByKey("GameCharaBase.Base"));
	BaseLog("#define GameCharaBase.Function.getGameCharaBoneContext      0x%X", AddyEngine->GetAddyValueByKey("GameCharaBase.Function.getGameCharaBoneContext"));
	BaseLog("#define GameCharaBase.Function.getGameCharaWeaponContext    0x%X", AddyEngine->GetAddyValueByKey("GameCharaBase.Function.getGameCharaWeaponContext"));
	BaseLog("#define GameCharaBase.Function.getGameCharaCollisionContext 0x%X", AddyEngine->GetAddyValueByKey("GameCharaBase.Function.getGameCharaCollisionContext"));
	BaseLog("#define GameCharaBase.Function.setCharaWeapon               0x%X", AddyEngine->GetAddyValueByKey("GameCharaBase.Function.setCharaWeapon"));
	BaseLog("#define GameCharaBase.Function.Cmd_Respawn                  0x%X", AddyEngine->GetAddyValueByKey("GameCharaBase.Function.Cmd_Respawn"));
	BaseLog("#define GameCharaBase.Function.getGameCharaAnimContext      0x%X\n", AddyEngine->GetAddyValueByKey("GameCharaBase.Function.getGameCharaAnimContext"));

	BaseLog("#define GameCharaBase.Function.getCharaNetIdx               0x%X", AddyEngine->GetAddyValueByKey("GameCharaBase.Function.getCharaNetIdx"));
	BaseLog("#define GameCharaBase.Function.eventFall                    0x%X", AddyEngine->GetAddyValueByKey("GameCharaBase.Function.eventFall"));
	BaseLog("#define GameCharaBase.Function.getCurHP                     0x%X", AddyEngine->GetAddyValueByKey("GameCharaBase.Function.getCurHP"));
	BaseLog("#define GameCharaBase.Function.writeData                    0x%X", AddyEngine->GetAddyValueByKey("GameCharaBase.Function.writeData"));
	BaseLog("#define GameCharaBase.Function.readData                     0x%X", AddyEngine->GetAddyValueByKey("GameCharaBase.Function.readData"));
	BaseLog("#define GameCharaBase.Pointer.invicibleTime                 0x%X\n", AddyEngine->GetAddyValueByKey("GameCharaBase.Pointer.invicibleTime"));

	BaseLog("#define GameCharaCollisionContext.Pointer.CrosshairTarget   0x%X", AddyEngine->GetAddyValueByKey("GameCharaCollisionContext.Pointer.CrosshairTarget"));
	BaseLog("#define GameCharaCollisionContext.Function.ReadData         0x%X\n", AddyEngine->GetAddyValueByKey("GameCharaCollisionContext.Function.ReadData"));

	BaseLog("#define GameCharaBoneContext.Function.writeYaw              0x%X", AddyEngine->GetAddyValueByKey("GameCharaBoneContext.Function.writeYaw"));
	BaseLog("#define GameCharaBoneContext.Function.writePitch            0x%X", AddyEngine->GetAddyValueByKey("GameCharaBoneContext.Function.writePitch"));
	BaseLog("#define GameCharaBoneContext.Function.getBones              0x%X", AddyEngine->GetAddyValueByKey("GameCharaBoneContext.Function.getBones"));
	BaseLog("#define GameCharaBoneContext.Size.BonesAlign                0x%X\n", AddyEngine->GetAddyValueByKey("GameCharaBoneContext.Size.BonesAlign"));

	//BaseLog("#define GameCharaWeaponContext.Function.getCurrent          0x%X", AddyEngine->GetAddyValueByKey("GameCharaWeaponContext.Function.getCurrent"));
	//BaseLog("#define GameCharaWeaponContext.Pointer.CurrentWeaponIndex   0x%X", AddyEngine->GetAddyValueByKey("GameCharaWeaponContext.Pointer.CurrentWeaponIndex"));
	//BaseLog("#define GameCharaWeaponContext.Function.getCurrent          0x%X", AddyEngine->GetAddyValueByKey("GameCharaWeaponContext.Function.getCurrent"));
	//BaseLog("#define GameCharaWeaponContext.Function.DecryptWeaponIndex  0x%X", AddyEngine->GetAddyValueByKey("GameCharaWeaponContext.Function.DecryptWeaponIndex"));
	BaseLog("#define GameCharaWeaponContext.Function.SafeGetWeapon       0x%X\n", AddyEngine->GetAddyValueByKey("GameCharaWeaponContext.Function.SafeGetWeapon"));

	BaseLog("#define WeaponBase.Function.Reset                           0x%X", AddyEngine->GetAddyValueByKey("WeaponBase.Function.Reset"));
	BaseLog("#define WeaponBase.Function.GetSubAmmoCount                 0x%X", AddyEngine->GetAddyValueByKey("WeaponBase.Function.GetSubAmmoCount"));
	BaseLog("#define WeaponBase.Function.SetSubAmmoCount                 0x%X", AddyEngine->GetAddyValueByKey("WeaponBase.Function.SetSubAmmoCount"));
	BaseLog("#define WeaponBase.Function.DoFire                          0x%X", AddyEngine->GetAddyValueByKey("WeaponBase.Function.DoFire"));
	BaseLog("#define WeaponBase.Function.DoLineCollision                 0x%X", AddyEngine->GetAddyValueByKey("WeaponBase.Function.DoLineCollision"));

	/*ShellExecute(NULL, "open", "Notepad.exe", GetDirectoryFile("SearchLog.txt"), NULL, SW_SHOWNORMAL);
	ExitProcess(0);*/
}

/*-------------------------------------------------------------------------------------------------------------------*/
class Framework
{
public:
	DWORD FindPattern( DWORD dwStart, DWORD dwLen, BYTE* pszPatt, char pszMask[]);
	DWORD FindPattern(DWORD dwdwAdd,DWORD dwLen,DWORD Address);
	DWORD PUSH_STR_PB(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask,char * szMask);
	DWORD Func_CrazyFindSystem(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask,char * szMask,int Adr,int Result);
	DWORD FindPatternText(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask);
	DWORD PUSH_STR_PB(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask,char * szMask,int Offsete);
	bool CheckWindowsVersion(DWORD dwMajorVersion,DWORD dwMinorVersion,DWORD dwProductType);
	void __cdecl BaseLog (const char *fmt, ...);
}; Framework*_DDFramework;

class cFunction
{
public:
	/*GameContext*/
	DWORD getUserDeath;
	DWORD ResetAbuseCounter;
	DWORD ResetAbuseCounter2;
	DWORD ResetAbuseCounter3;
	/*GameCharaManager*/
	DWORD SetCharaWeaponSet;
	/*GameCharaWeaponContext*/
	DWORD getCurrent;
	DWORD DecryptWeaponIndex;
	/*GameCharaBase*/
	DWORD getCurHP_Real;
	/*WeaponBase*/
	DWORD GetMoveSpeed;
	DWORD RETGetMoveSpeed;
	DWORD GetOneVertEnable;	
	DWORD GetOneHorzEnable;	
	DWORD GetRecoilHorzCount;	
	DWORD GetRecoilVertCount;
	DWORD ReadWeaponInfo;
	DWORD NET_Fire;
	/*Address*/
	DWORD Brust;
	DWORD RETBrust;
	DWORD BypassBrust;
	DWORD getPutString;
	DWORD getPutHistory;
	DWORD getPutStringBackUp;
	DWORD getEnteredServerX;
	DWORD RETgetEnteredServerX;
	DWORD BugDatar;
}; 

class cPointer
{
public:
	/*GameContext*/
	DWORD getNickForSlot;
	DWORD getSlotInfo;
	DWORD getRankInfo;
	DWORD MySlotIdx;
	/*GameCharaWeaponContext*/
	DWORD CurrentWeaponIndex;
	/*Address*/
	DWORD BugWeapon;
};

class cSize
{
public:
	/*GameContext*/
	DWORD getNickForSlotSize;
	DWORD getNickForSlotMaxSize;
	DWORD getCharaInfoSize;
};

class cGameContext
{
public:
	cFunction Function;
	cPointer Pointer;
	cSize Size;
}; cGameContext GameContext;
DWORD ResultResetAbuseCounter;

class cGameCharaManager
{
public:
	cFunction Function;
}; cGameCharaManager GameCharaManager;

class cGameCharaWeaponContext
{
public:
	cFunction Function;
	cPointer Pointer;
}; cGameCharaWeaponContext GameCharaWeaponContext;
DWORD ResultCurrentWeaponIndex;

class cGameCharaBase
{
public:
	cFunction Function;
}; cGameCharaBase GameCharaBase;

class cWeaponBase
{
public:
	cFunction Function;
}; cWeaponBase WeaponBase;

class cAddress
{
public:
	cFunction Function;
	cPointer Pointer;
}; cAddress Address;

DWORD ModulePointBlank;
DWORD Modulei3GfxDx;
DWORD ModuleNxCharacter;
DWORD Modulei3FrameworkDx;
DWORD Modulei3BaseDx_Cli;
DWORD Modulei3InputDx;
DWORD Modulei3SceneDx;
DWORD Module_D3D9;

DWORD SizePointBlank;
DWORD Sizei3GfxDx;
DWORD SizeNxCharacter;
DWORD Sizei3FrameworkDx;
DWORD Sizei3BaseDx_Cli;
DWORD Sizei3InputDx;
DWORD Sizei3SceneDx;
DWORD SizeD3D9;

HMODULE ModuleNC;
HMODULE ModuleFD;
HMODULE ModuleGD;
HMODULE ModuleID;
HMODULE ModuleSD;
HMODULE ModuleBC;

/*-------------------------------------------------------------------------------------------------------------------*/
#pragma warning(disable:4244)
#pragma warning(disable:4700)
#pragma warning(disable:4996)
#pragma warning(disable:4305)
#pragma warning(disable:4715)
using namespace std;
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
bool ChekLogPortal = false;
bool CHekHook=false;

/*------------------------------------------- Declaration String ------------------------------------------------------*/
#define Result_Address			1
#define Result_PTRByte			2
#define Result_PTR4Byte			3
#define Result_AddressString	4
#define Result_PTRStringByte	5
#define Result_PTRString4Byte	6

/*------------------------------------------- Declaration Function ------------------------------------------------------*/
char *GetDirectoryFile(char *filename);
void __cdecl add_log (const char * fmt, ...);
void thethread();

DWORD Framework::FindPattern( DWORD dwStart, DWORD dwLen, BYTE* pszPatt, char pszMask[])
{ 
	unsigned int i = NULL; 
	int iLen = strlen( pszMask ) - 1; 
	for( DWORD dwRet = dwStart; dwRet < dwStart + dwLen; dwRet++ ){ 
		if( *(BYTE*)dwRet == pszPatt[i] || pszMask[i] == '?' ){ 
			if( pszMask[i+1] == '\0' ) return( dwRet - iLen ); i++; 
		} 
		else i = NULL; 
	}
	return NULL; 
}

DWORD GetSizeofCode( const char* szModuleName ) 
{ 
	HMODULE hModule = GetModuleHandleA( szModuleName ); 
	if ( !hModule ) return NULL; 
	PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER( hModule ); 
	if( !pDosHeader ) return NULL; 
	PIMAGE_NT_HEADERS pNTHeader = PIMAGE_NT_HEADERS( (LONG)hModule + pDosHeader->e_lfanew ); 
	if( !pNTHeader ) return NULL; 
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pNTHeader->OptionalHeader; 
	if( !pOptionalHeader ) return NULL; 
	return pOptionalHeader->SizeOfCode; 
}

/*--------------------------------------------------------------*/
DWORD ModuleP			= (DWORD)GetModuleHandleA("PointBlank.exe");;
DWORD ModulePBB			= (DWORD)GetModuleHandleA("PointBlank.exe");
DWORD ModulePB			= (DWORD)GetModuleHandleA("PointBlank.exe");
DWORD ModuleSizePB      = GetSizeofCode("PointBlank.exe");
DWORD ModuleGF			= (DWORD)GetModuleHandleA("i3GfxDx.dll");
DWORD ModuleSizeGF		= GetSizeofCode("i3GfxDx.dll");
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
DWORD ModuleDX			= (DWORD)GetModuleHandle("i3BaseDx_Cli.dll");
DWORD ModuleSizeDX		= GetSizeofCode("i3BaseDx_Cli.dll");
/*--------------------------------------------------------------*/

bool Framework::CheckWindowsVersion(DWORD dwMajorVersion,DWORD dwMinorVersion,DWORD dwProductType)
{
    OSVERSIONINFOEX VersionInfo;
    ZeroMemory(&VersionInfo,sizeof(OSVERSIONINFOEX));
    VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
    GetVersionEx((OSVERSIONINFO*)&VersionInfo);
        if ( VersionInfo.dwMajorVersion == dwMajorVersion )
        {
                if ( VersionInfo.dwMinorVersion == dwMinorVersion )
                {
                        if ( VersionInfo.wProductType == dwProductType )
                        {
                                return ( TRUE );
                        }
                }
        }
        return ( FALSE );
}

void __cdecl Framework::BaseLog (const char *fmt, ...){
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

DWORD Framework::FindPattern(DWORD dwdwAdd,DWORD dwLen,DWORD Address)
{
    for(DWORD i=0; i<dwLen; i++)
        if (*(PDWORD)(dwdwAdd+i)==Address)
			return (DWORD)(dwdwAdd+i);
    return 0;
}

DWORD Framework::PUSH_STR_PB(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask,char * szMask)
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
		ModuleStart=ModulePBB;
	return ModuleStart;
}

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

DWORD Framework::Func_CrazyFindSystem(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask,char * szMask,int Offsete,int Result)
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

DWORD Func_SmartPattern(DWORD A,DWORD B,DWORD C,BYTE *D,char *E)
{
	DWORD Smart=0;
	DWORD ModuleStart	=Func_SmartModuleStart(A);
	DWORD ModuleEnd		=Func_SmartModuleEnd(A);
	if(B == Result_Address)
		Smart = _DDFramework->Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
	else 
		if(C == Result_PTRByte)
			Smart = _DDFramework->Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
		else 
			if(C == Result_PTR4Byte)
				Smart = _DDFramework->Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
			else 
				if(C == Result_AddressString)
					Smart = _DDFramework->Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
				else 
					if(C == Result_PTRStringByte)
						Smart = _DDFramework->Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
					else 
						if(C == Result_PTRString4Byte)
							Smart = _DDFramework->Func_CrazyFindSystem(ModuleStart,ModuleEnd,(PBYTE)D,E,B,C); 
	if(Smart!=NULL)
		return Smart;
}

DWORD Framework::FindPatternText(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask)
{
    for(DWORD i=0; i<dwLen; i++)
		if(memcpy((void*)(dwdwAdd+i), (void*)&bMask , sizeof(bMask)) == 0 ) 
			return (DWORD)(dwdwAdd+i);
    return 0;
}

DWORD Framework::PUSH_STR_PB(DWORD dwdwAdd,DWORD dwLen,BYTE *bMask,char * szMask,int Offsete)
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

//GameContext//
	#define String_STR_ResetAbuseCounter		"void __thiscall CGameContext::setCurrentDifficultyLevel(int)"
	#define Mask_STR_ResetAbuseCounter			"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
	#define String_STR_getUserDeath				"bool __thiscall CGameContext::getUserDeath(int)"
	#define Mask_STR_getUserDeath				"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
	#define String_STR_getNickForSlot			"const char *__thiscall CGameContext::getNickForSlot(int)"
	#define Mask_STR_getNickForSlot				"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
	#define String_STR_getSlotInfo				"struct __SlotInfo *__thiscall CGameContext::getSlotInfo(int)"
	#define Mask_STR_getSlotInfo				"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
	#define String_STR_setMySlotIdx				"void __thiscall CGameContext::setMySlotIdx(int)"
	#define Mask_STR_setMySlotIdx				"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

//GameCharaManager//
	#define String_STR_SetCharaWeaponSet		"void __thiscall CGameCharaManager::SetCharaWeaponSet(class CGameCharaBase *,struct _NetCharaInfo *)"
	#define Mask_STR_SetCharaWeaponSet			"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

//GameCharaWeaponContext//
	#define String_STR_getCurrent				"class WeaponBase *__thiscall CGameCharaWeaponContext::getCurrent(void)"
	#define Mask_STR_getCurrent					"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

//GameCharaBase//
	#define String_STR_getCurHP_Real			"float __thiscall CGameCharaBase::getCurHP_Real(void)"
	#define Mask_STR_getCurHP_Real				"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

//WeaponBase//
	#define Pattern_GetMoveSpeed				"\xD9\x45\xF8\x8B\xE5\x5D\xC2\x04\x00\x90\x2B\x7D"// float __thiscall WeaponBase::GetMoveSpeed(enum WEAPON_MOVE_SPEED_TYPE)
	#define Mask_GetMoveSpeed					"xxxxxxxxxxxx"
	#define String_STR_GetOneVertEnable			"int __thiscall WeaponBase::GetOneVertEnable(class CWeaponInfo *,bool)"
	#define Mask_STR_GetOneVertEnable			"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
	#define String_STR_GetOneHorzEnable			"int __thiscall WeaponBase::GetOneHorzEnable(class CWeaponInfo *,bool)"
	#define Mask_STR_GetOneHorzEnable			"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
	#define String_STR_GetRecoilHorzCount		"int __thiscall WeaponBase::GetRecoilHorzCount(class CWeaponInfo *,bool)"
	#define Mask_STR_GetRecoilHorzCount			"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
	#define String_STR_GetRecoilVertCount		"int __thiscall WeaponBase::GetRecoilVertCount(class CWeaponInfo *,bool)"
	#define Mask_STR_GetRecoilVertCount			"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
	#define String_STR_ReadWeaponInfo			"void __thiscall CGunInfo::ReadWeaponInfo(class i3RegKey *)"
	#define Mask_STR_ReadWeaponInfo				"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
	#define String_STR_NET_Fire					"void __thiscall WeaponBase::NET_Fire(union VEC3D *,union VEC3D *,enum WEAPON_FIRE_ORDER)"
	#define Mask_STR_NET_Fire					"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

//Address//
	#define Pattern_Brust						"\xFF\xD0\x89\x45\xA8"
	#define Mask_Brust							"xxxxx"
	#define Pattern_BypassBrust					"\x0F\x8E\x00\x00\x00\x00\x8B\x45\xFC\x8B\x88\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xF8\x23"
	#define Mask_BypassBrust					"xx????xxxxx????x????xxx"
	#define String_STR_getPutString				"void __thiscall CGameChatBox::_PutStringBuffer(const char *,unsigned short)"
	#define Mask_STR_getPutString				"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
	#define String_STR_getPutHistory			"void __thiscall CGameChatBox::PutHistory(const char *,int)"
	#define Mask_STR_getPutHistory				"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
	#define String_STR_getPutStringBackUpBuffer "void __thiscall CGameChatBox::_PutStringBackUpBuffer(const char *)"
	#define Mask_STR_getPutStringBackUpBuffer	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
	#define String_STR_GetEnteredServer			"int __thiscall CGameContext::GetEnteredServer(void)"
	#define Mask_STR_GetEnteredServer			"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
	#define Pattern_BugWTF						"\x5E\x00\xD9\x46\x00\xD9\x44\x24\x00\xD9\xC0\xDE\xC2\xD9\xC9\xD9\x5E\x00\xD9\x46\x00\xD8\xC3\xD9\x5E\x00\xD9\x46\x00\xD8\xC2\xD9\x5E\x00\xD9\x46\x00"
	#define Mask_BugWTF							"x?xx?xxx?xxxxxxxx?xx?xxxx?xx?xxxx?xx?"

/*------------------------------------------- Declaration Auto Logger ------------------------------------------------------*/
void SearchPatterns()
{
	Sleep(0);
	do{
		ModulePointBlank	= (DWORD)GetModuleHandle("PointBlank.exe");
		Modulei3GfxDx		= (DWORD)GetModuleHandle("i3GfxDx.dll");
		ModuleNxCharacter	= (DWORD)GetModuleHandle("NxCharacter.2.8.1.dll");
		Modulei3FrameworkDx	= (DWORD)GetModuleHandle("i3FrameworkDx.dll");
		Modulei3BaseDx_Cli	= (DWORD)GetModuleHandle("i3BaseDx_Cli.dll");
		Modulei3InputDx		= (DWORD)GetModuleHandle("i3InputDx.dll");
		Modulei3SceneDx		= (DWORD)GetModuleHandle("i3SceneDx.dll");
		Module_D3D9			= (DWORD)GetModuleHandle("d3d9.dll");

		SizePointBlank		= GetSizeofCode("PointBlank.exe");
		Sizei3GfxDx			= GetSizeofCode("i3GfxDx.dll");
		SizeNxCharacter		= GetSizeofCode("NxCharacter.2.8.1.dll");
		Sizei3FrameworkDx	= GetSizeofCode("i3FrameworkDx.dll");
		Sizei3BaseDx_Cli	= GetSizeofCode("i3BaseDx_Cli.dll");
		Sizei3InputDx		= GetSizeofCode("i3InputDx.dll");
		Sizei3SceneDx		= GetSizeofCode("i3SceneDx.dll");
		SizeD3D9			= GetSizeofCode("d3d9.dll");

		ModuleNC			= (HMODULE)LoadLibrary("NxCharacter.2.8.1.dll");
		ModuleFD			= (HMODULE)LoadLibrary("i3FrameworkDx.dll");
		ModuleGD			= (HMODULE)LoadLibrary("i3GfxDx.dll");
		ModuleID			= (HMODULE)LoadLibrary("i3InputDx.dll");
		ModuleSD			= (HMODULE)LoadLibrary("i3SceneDx.dll");
		ModuleBC			= (HMODULE)LoadLibrary("i3BaseDx_Cli.dll");
	Sleep(0);
	}while
	
	(!ModulePointBlank);
	(!Modulei3GfxDx);
	(!ModuleNxCharacter);
	(!Modulei3FrameworkDx);
	(!Modulei3BaseDx_Cli);
	(!Module_D3D9);

	(!SizePointBlank);
	(!Sizei3GfxDx);
	(!SizeNxCharacter);
	(!Sizei3FrameworkDx);
	(!Sizei3BaseDx_Cli);
	(!SizeD3D9);

	(!ModuleNC);
	(!ModuleFD);
	(!ModuleGD);
	(!ModuleID);
	(!ModuleSD);
	(!ModuleBC);

	//GameContext//
		DWORD getUserDeath					= Func_SmartPattern(0, -0x15,Result_AddressString		,(PBYTE)String_STR_getUserDeath				,Mask_STR_getUserDeath);
		DWORD ResetAbuseCounter				= Func_SmartPattern(0,  0xB5,Result_AddressString		,(PBYTE)String_STR_ResetAbuseCounter		,Mask_STR_ResetAbuseCounter);
		ReadProcessMemory(GetCurrentProcess(),(LPCVOID)(ResetAbuseCounter+0x2)		,&ResultResetAbuseCounter	,sizeof(ResultResetAbuseCounter)			,NULL);
		DWORD getNickForSlot				= Func_SmartPattern(0,  0xC0,Result_PTRString4Byte		,(PBYTE)String_STR_getNickForSlot			,Mask_STR_getNickForSlot);
		DWORD getNickForSlotSize			= Func_SmartPattern(0,  0xB9,Result_PTRStringByte		,(PBYTE)String_STR_getNickForSlot			,Mask_STR_getNickForSlot);
		DWORD getNickForSlotMaxSize			= Func_SmartPattern(0,  0xAC,Result_PTRString4Byte		,(PBYTE)String_STR_getNickForSlot			,Mask_STR_getNickForSlot);
		DWORD getSlotInfo					= Func_SmartPattern(0,  0xD3,Result_PTRString4Byte		,(PBYTE)String_STR_getSlotInfo				,Mask_STR_getSlotInfo);
		DWORD getSlotInfoSize				= Func_SmartPattern(0,  0xCC,Result_PTRStringByte		,(PBYTE)String_STR_getSlotInfo				,Mask_STR_getSlotInfo);
		DWORD MySlotIdx						= Func_SmartPattern(0,  0x2F,Result_PTRString4Byte		,(PBYTE)String_STR_setMySlotIdx				,Mask_STR_setMySlotIdx);

	//GameCharaManager//
		DWORD SetCharaWeaponSet				= Func_SmartPattern(0, -0x17,Result_AddressString		,(PBYTE)String_STR_SetCharaWeaponSet		,Mask_STR_SetCharaWeaponSet);

	//GameCharaWeaponContext//
		DWORD getCurrent					= _DDFramework->PUSH_STR_PB(ModulePointBlank			,SizePointBlank		,(PBYTE)String_STR_getCurrent			,Mask_STR_getCurrent			,NULL); 
		DWORD getDecryptWeapon				= _DDFramework->PUSH_STR_PB(ModulePointBlank			,SizePointBlank		,(PBYTE)"STR_HACKER_MSG"				,"xxxxxxxxxxxxxx"				,NULL); 
		DWORD getCurrentSlot				= _DDFramework->PUSH_STR_PB(ModulePointBlank			,SizePointBlank		,(PBYTE)String_STR_getCurrent			,Mask_STR_getCurrent			,-0x12);
		ReadProcessMemory(GetCurrentProcess(),(LPCVOID)(getCurrentSlot	+0x2)		,&ResultCurrentWeaponIndex	,sizeof(ResultCurrentWeaponIndex)			,NULL);

	//GameCharaBase//
		DWORD getCurHP_Real					= Func_SmartPattern(0, -0x1B,Result_AddressString		,(PBYTE)String_STR_getCurHP_Real			,Mask_STR_getCurHP_Real);
	
	//WeaponBase//
		DWORD GetMoveSpeed					= _DDFramework->FindPattern(ModulePointBlank			,SizePointBlank		,(PBYTE)Pattern_GetMoveSpeed			,Mask_GetMoveSpeed);
		DWORD GetOneVertEnable				= _DDFramework->PUSH_STR_PB(ModulePointBlank			,SizePointBlank		,(PBYTE)String_STR_GetOneVertEnable		,Mask_STR_GetOneVertEnable		,0x60);
		DWORD GetOneHorzEnable				= _DDFramework->PUSH_STR_PB(ModulePointBlank			,SizePointBlank		,(PBYTE)String_STR_GetOneHorzEnable		,Mask_STR_GetOneHorzEnable		,0x60);
		DWORD GetRecoilHorzCount			= _DDFramework->PUSH_STR_PB(ModulePointBlank			,SizePointBlank		,(PBYTE)String_STR_GetRecoilHorzCount	,Mask_STR_GetRecoilHorzCount	,0x7B);
		DWORD GetRecoilVertCount			= _DDFramework->PUSH_STR_PB(ModulePointBlank			,SizePointBlank		,(PBYTE)String_STR_GetRecoilVertCount	,Mask_STR_GetRecoilVertCount	,0x60);
		DWORD ReadWeaponInfo				= Func_SmartPattern(0, 0x4C1,Result_AddressString		,(PBYTE)String_STR_ReadWeaponInfo			,Mask_STR_ReadWeaponInfo);
		DWORD NET_Fire						= _DDFramework->PUSH_STR_PB(ModulePointBlank			,SizePointBlank		,(PBYTE)String_STR_NET_Fire				,Mask_STR_NET_Fire				,NULL);

	//Address//
		DWORD Brust							= _DDFramework->FindPattern(ModulePointBlank			,SizePointBlank		,(PBYTE)Pattern_Brust					,Mask_Brust);
		DWORD BypassBrust					= _DDFramework->FindPattern(ModulePointBlank			,SizePointBlank		,(PBYTE)Pattern_BypassBrust				,Mask_BypassBrust);
		DWORD getPutString					= _DDFramework->PUSH_STR_PB(ModulePointBlank			,SizePointBlank		,(PBYTE)String_STR_getPutString			,Mask_STR_getPutString)-0x18;
		DWORD getPutHistory					= _DDFramework->PUSH_STR_PB(ModulePointBlank			,SizePointBlank		,(PBYTE)String_STR_getPutHistory		,Mask_STR_getPutHistory)-0x18;
		DWORD getPutStringBackUp			= _DDFramework->PUSH_STR_PB(ModulePointBlank			,SizePointBlank		,(PBYTE)String_STR_getPutStringBackUpBuffer,Mask_STR_getPutStringBackUpBuffer)-0x18;
		DWORD getEnteredServerX				= Func_SmartPattern(0, -0x42,Result_AddressString		,(PBYTE)String_STR_GetEnteredServer			,Mask_STR_GetEnteredServer);
		DWORD adrBugDatar					= _DDFramework->FindPattern(ModuleNxCharacter			,SizeNxCharacter	,(PBYTE)Pattern_BugWTF					,Mask_BugWTF);
		DWORD adrBugWeapon					= _DDFramework->FindPattern(ModulePointBlank			,SizePointBlank*2	,(PBYTE)"¾CGameCharaCollisionContext"	,"xxxxxxxxxxxxxxxxxxxxxxxxxxx");

	/*---------------------------------- GameContext ----------------------------------*/
	GameContext.Function.getUserDeath						=getUserDeath;
	GameContext.Function.ResetAbuseCounter					=ResultResetAbuseCounter;
	GameContext.Function.ResetAbuseCounter2					=ResultResetAbuseCounter+0x4;
	GameContext.Function.ResetAbuseCounter3					=ResultResetAbuseCounter+0x8;
	GameContext.Pointer.getNickForSlot						=getNickForSlot;
	GameContext.Size.getNickForSlotSize						=getNickForSlotSize;
	GameContext.Size.getNickForSlotMaxSize					=(getNickForSlotMaxSize-getNickForSlot)/getNickForSlotSize;
	GameContext.Pointer.getSlotInfo							=getSlotInfo;
	GameContext.Pointer.getRankInfo							=getSlotInfo+0x1;
	GameContext.Size.getCharaInfoSize						=getSlotInfoSize;
	GameContext.Pointer.MySlotIdx							=MySlotIdx;

	/*---------------------------------- GameCharaManager ----------------------------------*/
	GameCharaManager.Function.SetCharaWeaponSet				=SetCharaWeaponSet;

	/*---------------------------------- GameCharaWeaponContext ----------------------------------*/
	GameCharaWeaponContext.Function.getCurrent				=getCurrent-0x2E;
	GameCharaWeaponContext.Function.DecryptWeaponIndex		=getDecryptWeapon+0x85;	
	GameCharaWeaponContext.Pointer.CurrentWeaponIndex		=ResultCurrentWeaponIndex;

	/*---------------------------------- GameCharaBase ----------------------------------*/
	GameCharaBase.Function.getCurHP_Real					=getCurHP_Real;

	/*---------------------------------- WeaponBase ----------------------------------*/
	WeaponBase.Function.GetMoveSpeed						=GetMoveSpeed;
	WeaponBase.Function.RETGetMoveSpeed						=WeaponBase.Function.GetMoveSpeed+0x5;
	WeaponBase.Function.GetOneVertEnable					=GetOneVertEnable;	
	WeaponBase.Function.GetOneHorzEnable 					=GetOneHorzEnable;	
	WeaponBase.Function.GetRecoilHorzCount					=GetRecoilHorzCount;	
	WeaponBase.Function.GetRecoilVertCount					=GetRecoilVertCount;
	WeaponBase.Function.ReadWeaponInfo						=ReadWeaponInfo+0xC;
	WeaponBase.Function.NET_Fire							=NET_Fire-0xA2;

	/*---------------------------------- Address ----------------------------------*/
	Address.Function.Brust									=Brust;
	Address.Function.RETBrust								=Brust+0x5;
	Address.Function.BypassBrust							=BypassBrust;
	Address.Function.getPutString							=getPutString;
	Address.Function.getPutHistory							=getPutHistory;
	Address.Function.getPutStringBackUp						=getPutStringBackUp;
	Address.Function.getEnteredServerX						=getEnteredServerX;
	Address.Function.RETgetEnteredServerX					=getEnteredServerX+0x06;
	Address.Function.BugDatar								=adrBugDatar-ModuleNxCharacter-0x1000;
	Address.Pointer.BugWeapon								=adrBugWeapon;

	/*---------------------------------- BaseLog ----------------------------------*/
	_DDFramework->BaseLog("//GameContext//");
	_DDFramework->BaseLog("    GameContext.Function.getUserDeath                   =0x%X;", GameContext.Function.getUserDeath);
	_DDFramework->BaseLog("    GameContext.Function.ResetAbuseCounter              =0x%X;", GameContext.Function.ResetAbuseCounter3);
	_DDFramework->BaseLog("    GameContext.Pointer.getNickForSlot                  =0x%X;", GameContext.Pointer.getNickForSlot);
	_DDFramework->BaseLog("    GameContext.Size.getNickForSlotSize                 =0x%X;", GameContext.Size.getNickForSlotSize);
	_DDFramework->BaseLog("    GameContext.Size.getNickForSlotMaxSize              =0x%X;", GameContext.Size.getNickForSlotMaxSize);
	_DDFramework->BaseLog("    GameContext.Pointer.getSlotInfo                     =0x%X;", GameContext.Pointer.getSlotInfo);
	_DDFramework->BaseLog("    GameContext.Pointer.getRankInfo                     =0x%X;", GameContext.Pointer.getRankInfo);
	_DDFramework->BaseLog("    GameContext.Size.getCharaInfoSize                   =0x%X;", GameContext.Size.getCharaInfoSize);
	_DDFramework->BaseLog("    GameContext.Pointer.MySlotIdx                       =0x%X;\n", GameContext.Pointer.MySlotIdx);
	_DDFramework->BaseLog("//GameCharaManager//");
	_DDFramework->BaseLog("    GameCharaManager.Function.SetCharaWeaponSet         =0x%X;\n", GameCharaManager.Function.SetCharaWeaponSet);
	_DDFramework->BaseLog("//GameCharaWeaponContext//");
	_DDFramework->BaseLog("    GameCharaWeaponContext.Function.getCurrent          =0x%X;", GameCharaWeaponContext.Function.getCurrent);
	_DDFramework->BaseLog("    GameCharaWeaponContext.Pointer.CurrentWeaponIndex   =0x%X;", GameCharaWeaponContext.Pointer.CurrentWeaponIndex);
	_DDFramework->BaseLog("    GameCharaWeaponContext.Function.DecryptWeaponIndex  =0x%X;\n", GameCharaWeaponContext.Function.DecryptWeaponIndex);
	_DDFramework->BaseLog("//GameCharaBase//");
	_DDFramework->BaseLog("    GameCharaBase.Function.getCurHP_Real                =0x%X;\n", GameCharaBase.Function.getCurHP_Real);
	_DDFramework->BaseLog("//WeaponBase//");
	_DDFramework->BaseLog("    WeaponBase.Function.GetMoveSpeed                    =0x%X;", WeaponBase.Function.GetMoveSpeed);
	_DDFramework->BaseLog("    WeaponBase.Function.RETGetMoveSpeed                 =0x%X;", WeaponBase.Function.RETGetMoveSpeed);
	_DDFramework->BaseLog("    WeaponBase.Function.GetOneVertEnable                =0x%X;", WeaponBase.Function.GetOneVertEnable);
	_DDFramework->BaseLog("    WeaponBase.Function.GetOneHorzEnable                =0x%X;", WeaponBase.Function.GetOneHorzEnable);
	_DDFramework->BaseLog("    WeaponBase.Function.GetRecoilHorzCount              =0x%X;", WeaponBase.Function.GetRecoilHorzCount);
	_DDFramework->BaseLog("    WeaponBase.Function.GetRecoilVertCount              =0x%X;", WeaponBase.Function.GetRecoilVertCount);
	_DDFramework->BaseLog("    WeaponBase.Function.ReadWeaponInfo                  =0x%X;", WeaponBase.Function.ReadWeaponInfo);
	_DDFramework->BaseLog("    WeaponBase.Function.NET_Fire                        =0x%X;\n", WeaponBase.Function.NET_Fire);
	_DDFramework->BaseLog("//Address//");
	_DDFramework->BaseLog("    Address.Function.Brust                              =0x%X;", Address.Function.Brust);
	_DDFramework->BaseLog("    Address.Function.RETBrust                           =0x%X;", Address.Function.RETBrust);
	_DDFramework->BaseLog("    Address.Function.BypassBrust                        =0x%X;", Address.Function.BypassBrust);
	_DDFramework->BaseLog("    Address.Function.getPutString                       =0x%X;", Address.Function.getPutString);
	_DDFramework->BaseLog("    Address.Function.getPutHistory                      =0x%X;", Address.Function.getPutHistory);
	_DDFramework->BaseLog("    Address.Function.getPutStringBackUp                 =0x%X;", Address.Function.getPutStringBackUp);
	_DDFramework->BaseLog("    Address.Function.getEnteredServerX                  =0x%X;", Address.Function.getEnteredServerX);
	_DDFramework->BaseLog("    Address.Function.RETgetEnteredServerX               =0x%X;", Address.Function.RETgetEnteredServerX);
	_DDFramework->BaseLog("    Address.Function.BugDatar                           =0x%X;", Address.Function.BugDatar);
	_DDFramework->BaseLog("    Address.Pointer.BugWeapon                           =0x%X;", Address.Pointer.BugWeapon);

	/*ShellExecute(NULL, "open", "Notepad.exe", GetDirectoryFile("SearchLog.txt"), NULL, SW_SHOWNORMAL);
	ExitProcess(0);*/
}
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