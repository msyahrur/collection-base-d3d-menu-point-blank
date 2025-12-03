#include <sstream>
#include <stdexcept>
#include <string>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <wininet.h>
#pragma comment(lib,"wininet.lib")
using namespace std;
#pragma warning(disable:4018)
//=================================================Cek Serial HRD=====================================================================
inline std::string trim_right(const std::string &source, const std::string& t = " ")
{
	std::string str = source;
	return str.erase(str.find_last_not_of(t) + 1);
}

inline std::string trim_left(const std::string& source, const std::string& t = " ")
{
	std::string str = source;
	return str.erase(0, source.find_first_not_of(t));
}

inline std::string trim(const std::string& source, const std::string& t = " ")
{
	std::string str = source;
	return trim_left(trim_right(str, t), t);
}

std::string IntToStr(int n)
{
	std::ostringstream result;
	result << n;
	return result.str();
}
string MyRandomString(void)
{
	string Agent;
	SYSTEMTIME st;
	GetLocalTime(&st);
	if (st.wHour<10)Agent = "0" + IntToStr(st.wHour);
	else Agent = IntToStr(st.wHour);

	if (st.wMinute<10)Agent = Agent + "0" + IntToStr(st.wMinute);
	else Agent = Agent + IntToStr(st.wMinute);

	if (st.wSecond<10) Agent = Agent + "0" + IntToStr(st.wSecond);
	else Agent = Agent + IntToStr(st.wSecond);

	if (st.wDayOfWeek<10)Agent = Agent + "0" + IntToStr(st.wDayOfWeek);
	else Agent = Agent + IntToStr(st.wDayOfWeek);
	return Agent;
}
HINTERNET hInternet, hFile1, hFile2, hFile3 , hFile4;
DWORD ReadSize;
//HDSN
char output[16];
char output2[1226];
char output3[1111];
string strSerial1;
string strSerial2;
string HostServer;
string HostServer2, HostServer3;
int OpenServer()
{
	struct tm * current_tm;
	time_t current_time;
	time(&current_time);
	current_tm = localtime(&current_time);
	DiskInfo *di;
	di = new DiskInfo(0);
	di->LoadDiskInfo();
	strSerial1 = di->SerialNumber();
	strSerial2 = trim(strSerial1);
	HostServer  = "http://kolor-ijo.ga/dee1ebcd105d3d47adf43aba6fd674e80d1dc35f/data-expired.php?e=" + strSerial2; //View=1 = Game 1 | View=2 = Game 2 dan seterunya
	HostServer2 = "http://kolor-ijo.ga/dee1ebcd105d3d47adf43aba6fd674e80d1dc35f/data-exp.php?e=" + strSerial2;
	HostServer3 = "http://kolor-ijo.ga/dee1ebcd105d3d47adf43aba6fd674e80d1dc35f/data-nama.php?e=" + strSerial2;

	hInternet = InternetOpenA("Some USER-AGENT", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	hFile1 = InternetOpenUrlA(hInternet, HostServer.c_str(), NULL, NULL, INTERNET_FLAG_RELOAD, NULL);
	hFile2 = InternetOpenUrlA(hInternet, HostServer2.c_str(), NULL, NULL, INTERNET_FLAG_RELOAD, NULL);
	hFile3 = InternetOpenUrlA(hInternet, HostServer3.c_str(), NULL, NULL, INTERNET_FLAG_RELOAD, NULL);
	return 0;
}
char Sempakx[1233];
char Sempak2[1233];


void CheckALL()
{
	sprintf(Sempakx, "%s", strSerial2.c_str());
	//sprintf(Sempak2, "%s", dwSerial);
	
}

void Read_HDSN8()
{
	while (1)
	{
		bool IsVerify = false;
		OpenServer();
		DWORD ReadSize; DWORD ReadSize2; DWORD ReadSize3; DWORD ReadSize4; BOOL bResult; BOOL bResult2; BOOL bResult3; 
		ReadSize = 15;
		ReadSize2 = 15;
		ReadSize3 = 15;
		ReadSize4 = 15;
		Sleep(10);
		bResult = InternetReadFile(hFile1, output, 15, &ReadSize);
		bResult2 = InternetReadFile(hFile2, output2, 15, &ReadSize2);
		bResult3 = InternetReadFile(hFile3, output3, 15, &ReadSize3);
		output[ReadSize] = '\0';
		if (strcmp("aktif", output) == 0)
		{

			IsVerify = true;
		}
		if (IsVerify)
		{
		
//		EliteWorldVIP(HookD3D9);
//		EliteWorldVIP(XMCR_Updater);
		Beep(1000,100);
		}
		else
		{
		  int iStaticModule = MessageBoxA(0, "Anda Tidak Terdaftar Member KoLor Ijo Cyber™", ":::PointBlank Garena Indonesia:::", MB_OK|MB_ICONERROR|MB_TOPMOST);
			ExitProcess(0);
		}
		goto end;
	}
	InternetCloseHandle(hFile1);
	InternetCloseHandle(hFile2);
	InternetCloseHandle(hFile3);
  end: return;
}