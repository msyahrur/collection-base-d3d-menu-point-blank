

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

#define XOR_KEY		0xA8
#define RANDOM_LEN	8		// length harus sama dengan SERVER_KEY
#define SERVER_KEY	(BYTE *)"\x5a\x52\x43\x43\x59\x42\x32\x32"

__forceinline void random_byte(unsigned char *buf, size_t len)
{
	unsigned char *pbuf = new unsigned char[len];
	memset(pbuf, 0, len);

	srand((UINT)time(NULL));

	for(int i=0; i < (int)len; i++) {
		pbuf[i] = static_cast<unsigned char>(rand() % 0xFE + 1);
		pbuf[i] ^= XOR_KEY;
	}

	memcpy_s(buf, len, pbuf, len);

	delete pbuf;
}

bool response_valid(unsigned char *prnd, size_t len, char *resp_rnd)
{
	bool bRet = false;

	unsigned char *buf = new unsigned char[len+8];
	memset(buf, 0, len+8);

	for(int i=0; i < (int)len; i++)
	{
		buf[i] = prnd[i] ^ XOR_KEY; //de-xor
	}

	memcpy(&buf[len], SERVER_KEY, 8); // ini kunci penentu

	unsigned char *hashbuf = new unsigned char[20];
	sha1::calc(buf, len+8, hashbuf);

	char *shahex = new char[40+1]; // hexhash + null terminator
	sha1::toHexString(hashbuf, shahex);

	shahex[strlen(shahex)-8] = '\0';

	if(strcmp(resp_rnd, shahex) == 0)
		bRet = true;

	delete buf;
	delete hashbuf;
	delete shahex;

	return bRet;
}

void CheckLicense()
{
//CODEREPLACE_START;

	//DWORD InetOpenA = (DWORD)GetProcAddress(GetModuleHandleW(Utils::SXorW((PBYTE)"\x28\x36\x31\x36\x31\x3A\x2B\x71\x3B\x33\x33\x5F" /*wininet.dll*/, 12).str()), Utils::SXor((PBYTE)"\x16\x31\x2B\x3A\x2D\x31\x3A\x2B\x10\x2F\x3A\x31\x1E\x5F" /*InternetOpenA*/, 14).c_str());
	//DWORD InetOpenUrlA = (DWORD)GetProcAddress(GetModuleHandleW(Utils::SXorW((PBYTE)"\x28\x36\x31\x36\x31\x3A\x2B\x71\x3B\x33\x33\x5F" /*wininet.dll*/, 12).str()), Utils::SXor((PBYTE)"\x16\x31\x2B\x3A\x2D\x31\x3A\x2B\x10\x2F\x3A\x31\x0A\x2D\x33\x1E\x5F" /*InternetOpenUrlA*/, 17).c_str());
	//DWORD InetReadFile = (DWORD)GetProcAddress(GetModuleHandleW(Utils::SXorW((PBYTE)"\x28\x36\x31\x36\x31\x3A\x2B\x71\x3B\x33\x33\x5F" /*wininet.dll*/, 12).str()), Utils::SXor((PBYTE)"\x16\x31\x2B\x3A\x2D\x31\x3A\x2B\x0D\x3A\x3E\x3B\x19\x36\x33\x3A\x5F" /*InternetReadFile*/, 17).c_str());

	//if((*(PBYTE)InetOpenA == 0xFF) || (*(PBYTE)InetOpenA == 0x68) || (*(PBYTE)InetOpenA == 0xE9) || (*(PBYTE)InetOpenA == 0xB8))
	//	*(PBYTE)0 = 0;

	//if((*(PBYTE)InetOpenUrlA == 0xFF) || (*(PBYTE)InetOpenUrlA == 0x68) || (*(PBYTE)InetOpenUrlA == 0xE9) || (*(PBYTE)InetOpenUrlA == 0xB8))
	//	*(PBYTE)0 = 0;

	//if((*(PBYTE)InetReadFile == 0xFF) || (*(PBYTE)InetReadFile == 0x68) || (*(PBYTE)InetReadFile == 0xE9) || (*(PBYTE)InetReadFile == 0xB8))
	//	*(PBYTE)0 = 0;

	unsigned char *pRandomKey = new unsigned char[RANDOM_LEN];
	random_byte(pRandomKey, RANDOM_LEN);

	char *pszRandomString = new char[RANDOM_LEN*2+1];
	memset(pszRandomString, 0, RANDOM_LEN*2+1);

	for(int i=0; i < RANDOM_LEN; i++)
	{
		char szHex[3] = {0};
		sprintf_s(szHex, 3, "%02x", pRandomKey[i] ^ XOR_KEY);
		strcat(pszRandomString, szHex);
	}

	DiskInfo *di;
	di = new DiskInfo(0);
	di->LoadDiskInfo();
	std::string snhdd1x = di->SerialNumber();
	std::string snhddx = trim(snhdd1x);

	char link[150], output[32];
	DWORD ReadSize = 32;
	HINTERNET hInternet = InternetOpenA(pszRandomString, INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0);
	sprintf(link, "http://zero-cyberz-vip.net/8495112d96cbcbcd72a42f5003642bc7/75c5ffc6a24877985c5ba2e1c2e0b577/hwid.php?id=%s&rnd=%s", snhddx.c_str(), pszRandomString);
	HINTERNET hFile = InternetOpenUrlA(hInternet, link, NULL, NULL, INTERNET_FLAG_RELOAD, NULL);
	InternetReadFile(hFile, output, 32, &ReadSize);
	output[ReadSize] = '\0';

	if(response_valid(pRandomKey, RANDOM_LEN, output))
	{
		//m_bIsValidUser = TRUE;
		//CT(MainThread, 0);
	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Thread_ZrCCyB,NULL,NULL,NULL);
	Beep(1000, 100);
	}else 
	ExitProcess (0);
	//*(PBYTE)0 = 0;

	delete pRandomKey;
	InternetCloseHandle(hInternet);
	InternetCloseHandle(hFile);
	//CODEREPLACE_END;
}

//harus di tambah ?id=%s&rnd=%s pada link hwid
//http://www.zero-cyberz-vip.net/hwid.php  + ?id=%s&rnd=%s === http://www.zero-cyberz-vip.net/hwid.php?id=%s&rnd=%s