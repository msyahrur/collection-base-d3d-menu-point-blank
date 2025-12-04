#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxguid.lib")

/////////////////////////////////////////////////////////////////////////////////
LPDIRECTINPUT8 Input2;
void InitializeDirectInput2();
void UpdateDirectInput2();
void DirectInputLoop2();
/////////////////////////////////////////////////////////////////////////////////
LPDIRECTINPUTDEVICE8 Keyboard2;
void InitializeKeyboard2();
void UpdateKeyboard2();
char* getKeyboard2State2();   
bool IsKeyboard2KeyDownOnce(int Index);

char Keyboard2State2[256];
bool KeyPressed2[256] = {0};


/////////////////////////////////////////////////////////////////////////////////
void InitializeDirectInput2()
{
	 DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&Input2, NULL);
}
void UpdateDirectInput2()
{
	if(Keyboard2 == NULL)InitializeKeyboard2();
	else UpdateKeyboard2();
}
void DirectInputLoop2()
{
	if(Input2 == NULL)InitializeDirectInput2();
	else UpdateDirectInput2();
}
/////////////////////////////////////////////////////////////////////////////////
void InitializeKeyboard2()
{  
    Input2->CreateDevice(GUID_SysKeyboard, &Keyboard2, NULL);
    Keyboard2->SetDataFormat(&c_dfDIKeyboard);
    Keyboard2->SetCooperativeLevel(GetForegroundWindow(), DISCL_FOREGROUND|DISCL_NONEXCLUSIVE);
    Keyboard2->Acquire();
}
void UpdateKeyboard2()
{
	HRESULT res = Keyboard2->GetDeviceState(sizeof(Keyboard2State2),(LPVOID)&Keyboard2State2); 
	if FAILED(res)
	{ 
		Keyboard2->Release();
		Keyboard2 = NULL;
		return;
	}
}
bool GetKeyboard2PressState2(int nIndex)
{
    return (Keyboard2State2[nIndex] && 0x80);
}
bool IsKeyboard2KeyDownOnce2(int Index){
	if(GetKeyboard2PressState2(Index)){
		if(KeyPressed2[Index] == false){
			KeyPressed2[Index] = true;
			return true;
		} else return false;
	} else KeyPressed2[Index] = false;
	return false;
}