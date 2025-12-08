//
//#include <windows.h>
//
//#include "Microsoft.h"
//
//#include "StandardIncludes.h"
//
//#include "cInclude.h"
//#include <windows.h>
//#include "wininet.h"
//#pragma comment(lib, "wininet.lib")
//#pragma message("Files-Destroyer™")
//#include "wininet.h"
//#pragma comment(lib, "wininet.lib")
void EliteWorldLog(HMODULE DLL,LPSTR NamaLogger){
GetModuleFileName(DLL, dlldir, 512);
for(int i = strlen(dlldir); i > 0; i--) { if(dlldir[i] == '\\') { dlldir[i+1] = 0; break;}}
infile.open(GetDirectoryFile(NamaLogger), ios::out);
}




/******************* HWID ********************/


int ThreadTrial(char *url){
char output[16];
HINTERNET hInternet;HINTERNET hFile;DWORD ReadSize; BOOL bResult;
hInternet = InternetOpen("Some USER-AGENT",INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,NULL);
hFile = InternetOpenUrl(hInternet,url,NULL,NULL,INTERNET_FLAG_RELOAD,NULL);
ReadSize = 15;Sleep(500);bResult = InternetReadFile(hFile,output,15,&ReadSize);output[ReadSize]='\0';
if(strcmp(/*familiarpcon*/XorStr<0x81,13,0x48C286D4>("\xE7\xE3\xEE\xED\xE9\xEF\xE6\xFA\xF9\xE9\xE4\xE2"+0x48C286D4).s,output)==0){ /// silakan diganti 
GetCurrentProcess();
}else{
ShellExecute(NULL, "Open", "https://www.facebook.com/LosNachosMotors", NULL, NULL, SW_SHOWNORMAL);
//ShellExecute(NULL, "Open", "http://astronxx.wixsite.com/gamesharp", NULL, NULL, SW_SHOWNORMAL);
//MessageBox(0,"Su Licencia Expiro Vuelva a Descargar el Hack",XorStr<0x5E,17,0xCFD57692>("\x19\x3E\x4D\x2D\x03\x17\x0D\x0B\x09\x47\x2D\x11\x1A\x02\x1E\x02"+0xCFD57692).s,MB_OK | MB_ICONINFORMATION);
ExitProcess(0);
}
return 0;
}
void __stdcall TrialStarter(){

ThreadTrial(XorStr<0xB6,33,0xDDADA201>("\xDE\xC3\xCC\xC9\x80\x94\x93\xCD\xDF\xCC\xB4\xA4\xA0\xAA\xAA\xEB\xA5\xA8\xA5\xE6\xB8\xAA\xBB\xE2\x9E\xF7\xA3\x82\xE4\xB5\xB9\x94"+0xDDADA201).s);
}

//=================================================Cek Serial HRD=====================================================================

//=================================================Cek Serial HRD=====================================================================
//=================================================Cek Serial HRD=====================================================================
inline std::string trim_right(const std::string &source , const std::string& t = " ")
{
	std::string str = source;
	return str.erase( str.find_last_not_of(t) + 1);
}

inline std::string trim_left( const std::string& source, const std::string& t = " ")
{
	std::string str = source;
	return str.erase(0 , source.find_first_not_of(t) );
}

inline std::string trim(const std::string& source, const std::string& t = " ")
{
	std::string str = source;
	return trim_left( trim_right( str , t) , t );
} 

void trim2(string& str)
{
string::size_type pos = str.find_last_not_of(' ');
if(pos != string::npos) {
str.erase(pos + 1);
pos = str.find_first_not_of(' ');
if(pos != string::npos) str.erase(0, pos);
}
else str.erase(str.begin(), str.end());
}

void CekHWID(void) 
{
	struct tm * current_tm;
	time_t current_time;
	time (&current_time);
	current_tm = localtime (&current_time);
	DiskInfo *di;
	di = new DiskInfo(0);
	di->LoadDiskInfo();
	string strSerial1 = di->SerialNumber();
	string strSerial2 = trim(strSerial1);

	 if (strcmp(strSerial2.c_str(), "8494S0PGS")==0) { //tu  Serial
	}else{
		MessageBeep(MB_ICONERROR);
		system("start https://www.facebook.com/LosNachosMotors");
		ExitProcess(1);
	}
}
void CekMODEL(void) //MODELNAME
{
	struct tm * current_tm;
	time_t current_time;
	time (&current_time);
	current_tm = localtime (&current_time);
	DiskInfo *di;
	di = new DiskInfo(0);
	di->LoadDiskInfo();
	string modell = di->ModelNumber();
	string modell2 = trim(modell);

	if (strcmp(modell2.c_str(), "TOSHIBA DT01ACA200")==0) { // tu Modelo Hardisk
		MessageBeep(MB_ICONWARNING );

	}else{
		MessageBeep(MB_ICONERROR);
		system("start https://www.facebook.com/LosNachosMotors");
		ExitProcess(1);
	}
} 
 void HideModule( HINSTANCE hModule )
{
    DWORD dwPEB_LDR_DATA = 0;

    _asm
    {
        pushad;
        pushfd;
        mov eax, fs:[30h]                    // PEB
        mov eax, [eax+0Ch]                    // PEB-&gt;ProcessModuleInfo
        mov dwPEB_LDR_DATA, eax                // Save ProcessModuleInfo

InLoadOrderModuleList:
        mov esi, [eax+0Ch]                    // ProcessModuleInfo-&gt;InLoadOrderModuleList[FORWARD]
        mov edx, [eax+10h]                    //  ProcessModuleInfo-&gt;InLoadOrderModuleList[BACKWARD]

LoopInLoadOrderModuleList:
        lodsd                                //  Load First Module
            mov esi, eax                      //  ESI points to Next Module
            mov ecx, [eax+18h]                  //  LDR_MODULE-&gt;BaseAddress
        cmp ecx, hModule                  //  Is it Our Module ?
            jne SkipA                        //  If Not, Next Please (@f jumps to nearest Unamed Lable @@:)
            mov ebx, [eax]                        //  [FORWARD] Module
        mov ecx, [eax+4]                 //  [BACKWARD] Module
        mov [ecx], ebx                        //  Previous Module's [FORWARD] Notation, Points to us, Replace it with, Module++
            mov [ebx+4], ecx                    //  Next Modules, [BACKWARD] Notation, Points to us, Replace it with, Module--
            jmp InMemoryOrderModuleList            //  Hidden, so Move onto Next Set
SkipA:
        cmp edx, esi                        //  Reached End of Modules ?
            jne LoopInLoadOrderModuleList        //  If Not, Re Loop

InMemoryOrderModuleList:
        mov eax, dwPEB_LDR_DATA                //  PEB-&gt;ProcessModuleInfo
            mov esi, [eax+14h]                    //  ProcessModuleInfo-&gt;InMemoryOrderModuleList[START]
        mov edx, [eax+18h]                    //  ProcessModuleInfo-&gt;InMemoryOrderModuleList[FINISH]

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
        mov eax, dwPEB_LDR_DATA                    //  PEB-&gt;ProcessModuleInfo
            mov esi, [eax+1Ch]                        //  ProcessModuleInfo-&gt;InInitializationOrderModuleList[START]
        mov edx, [eax+20h]                        //  ProcessModuleInfo-&gt;InInitializationOrderModuleList[FINISH]

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

