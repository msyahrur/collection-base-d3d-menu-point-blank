#include <sstream>
#include <stdexcept>
#include <string>
#include <time.h>
#include "XN2XORSTR.h"
#include "XN2HDSN.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <wininet.h>
#pragma comment(lib,"wininet.lib")
using namespace std;
#pragma warning(disable:4018)
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

std::string IntToStr( int n )
{
	std::ostringstream result;
	result << n;
	return result.str();
} 
string MyRandomString (void)
{
	string Agent;
	SYSTEMTIME st;
	GetLocalTime(&st);	
	if (st.wHour<10)Agent="0"+IntToStr(st.wHour);
	else Agent=IntToStr(st.wHour);

	if (st.wMinute<10)Agent=Agent+"0"+IntToStr(st.wMinute);
	else Agent=Agent+IntToStr(st.wMinute);

	if (st.wSecond<10) Agent=Agent+"0"+IntToStr(st.wSecond);
	else Agent=Agent+IntToStr(st.wSecond);

	if (st.wDayOfWeek<10)Agent=Agent+"0"+IntToStr(st.wDayOfWeek);
	else Agent=Agent+IntToStr(st.wDayOfWeek);
	return Agent;
}
HINTERNET hInternet, hFile1;
DWORD ReadSize;
char output[16];
string strSerial1;
string strSerial2;
string HostServer;

int OpenServer()
{	
	struct tm * current_tm;
	time_t current_time;
	time (&current_time);
	current_tm = localtime (&current_time);
	DiskInfo *di;
	di = new DiskInfo(0);
	di->LoadDiskInfo();
	strSerial1 = di->SerialNumber();
	strSerial2 = trim(strSerial1);
	HostServer = "http://eh404-project.ga/PointBlank/data-expired.php?e="+strSerial2;
	hInternet = InternetOpenA("Some USER-AGENT", INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL, NULL);
	hFile1 = InternetOpenUrlA(hInternet, HostServer.c_str(), NULL,NULL, INTERNET_FLAG_RELOAD,NULL);
	return 0;
}

int Read_HDSN8()
{ 
	while(1)
	{	
		bool IsVerify = false;
		OpenServer();
		DWORD ReadSize; BOOL bResult;
		ReadSize = 15;
		Sleep (10);
		bResult = InternetReadFile( hFile1, output, 15, &ReadSize); 
		output[ReadSize] = '\0';
		if(strcmp(/*aktif*/XorStr<0xEC,6,0xE712EC1B>("\x8D\x86\x9A\x86\x96"+0xE712EC1B).s,output)==0)
   		{
			IsVerify=true;
			Beep(889, 780);
			return 0;
		}
		if(strcmp(/*Expired*/XorStr<0x6C,8,0xFA8C1A90>("\x29\x15\x1E\x06\x02\x14\x16"+0xFA8C1A90).s,output)==0)
		{
			MessageBox(0, "HDSN PC Anda telah expired!", "[E]-[H] 404", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
		if(IsVerify)
		{
		}else
		{
			MessageBox(0, "HDSN Anda belum terdaftar!", "[E]-[H] 404", MB_OK | MB_ICONERROR);
			ExitProcess(0);
		}
	}
}
