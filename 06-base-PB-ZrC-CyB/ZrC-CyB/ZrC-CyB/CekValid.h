#include <WinInet.h>
#include <stdlib.h>
#include <mmsystem.h>
#include <ShellAPI.h>
#define INFO_BUFFER_SIZE 32767
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "winmm.lib")

bool activer=false;
bool exiter=false;

int CEK(char *url1,char *url2,char *url3)
{
char output[15000];
HINTERNET hInternet;
HINTERNET hFile;
DWORD ReadSize;
BOOL bResult;

hInternet = InternetOpenA(url2, INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL, NULL);
hFile = InternetOpenUrlA(hInternet, 
						 url1,
						 NULL,NULL, INTERNET_FLAG_RELOAD,NULL);

ReadSize = 15;
bResult = InternetReadFile( hFile, output, 15, &ReadSize);

output[ReadSize] = '\0';
if(strcmp(url3,output)== 0)
{
activer=true;
}
else
{
MessageBoxA(0,"Cant Connect To Server Or Cheat / Hacks Expired\nPlease Re-Download New Version In Website","",MB_OK | MB_ICONINFORMATION);
ShellExecute(NULL, "Open", "http://www.zero-cyberz-server.com/category/point-blank/", NULL, NULL, SW_SHOWNORMAL);
ExitProcess(0);
InternetCloseHandle(hFile);
InternetCloseHandle(hInternet);
}
return 0;
}