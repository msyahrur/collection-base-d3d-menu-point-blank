


class tools
{
public:
	void Message(char * text, char * title);
	void OpenURL(char * url);
	void WriteAsm(void * adress, BYTE * bytes, int size);
};

void tools::Message(char * text, char * title)
{
	MessageBoxA(NULL,        //HWND
		text,                //lpText
		title,               //lpCaption
		MB_ICONINFORMATION); //uType
}

void tools::OpenURL(char * url)
{
	ShellExecuteA(NULL,      //HWND
		"Open",              //lpOperation
		url,                 //lpFile
		NULL,                //lpParameter
		NULL,                //lpDirectory
		SW_SHOWNORMAL);      //nShowCmd
}

void tools::WriteAsm(void * adress, BYTE * bytes, int size)
{
	DWORD dwProtect = NULL;

	VirtualProtect(adress, size, PAGE_READWRITE, &dwProtect);
	memcpy(adress, (PBYTE)bytes, size);
	VirtualProtect(adress, size, dwProtect, &dwProtect);
}