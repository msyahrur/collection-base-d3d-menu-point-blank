//CREATED BY SC0D3 Solusi Game No Di Indoneisa
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxguid.lib")
LPDIRECTINPUT8 Input;
void InitializeDirectInput();
void UpdateDirectInput();
void DirectInputLoop();

LPDIRECTINPUTDEVICE8 Keyboard;
void InitializeKeyboard();
void UpdateKeyboard();
char* getKeyboardState();   

bool IsKeyboardKeyDownOnce(int Index);

char KeyboardState[256];
bool KeyPressed[256] = {0};

LPDIRECTINPUTDEVICE8 Mouse; 
void InitializeMouse();
void UpdateMouse();

typedef struct {
	int x;        
	int y;        
	bool button[2]; 
} MOUSE;
MOUSE mouse;
bool MousePressed[2] = {0};
HANDLE MouseEvent;
#define DIM_LBUTTON 0
#define DIM_RBUTTON 1
#define DIM_MBUTTON 2
void InitializeDirectInput()
{
	 DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&Input, NULL);
}
void UpdateDirectInput()
{
	if(Keyboard == NULL)InitializeKeyboard();
	else UpdateKeyboard();
}
void DirectInputLoop()
{
	if(Input == NULL)InitializeDirectInput();
	else UpdateDirectInput();
}
void InitializeKeyboard()
{  
    Input->CreateDevice(GUID_SysKeyboard, &Keyboard, NULL);
    Keyboard->SetDataFormat(&c_dfDIKeyboard);
    Keyboard->SetCooperativeLevel(GetForegroundWindow(), DISCL_FOREGROUND|DISCL_NONEXCLUSIVE);
    Keyboard->Acquire();
}
void UpdateKeyboard()
{
	HRESULT res = Keyboard->GetDeviceState(sizeof(KeyboardState),(LPVOID)&KeyboardState); 
	if FAILED(res)
	{ 
		Keyboard->Release();
		Keyboard = NULL;
		return;
	}
}
bool GetKeyboardPressState(int nIndex)
{
    return (KeyboardState[nIndex] && 0x80);
}
bool IsKeyboardKeyDownOnce(int Index){
	if(GetKeyboardPressState(Index)){
		if(KeyPressed[Index] == false){
			KeyPressed[Index] = true;
			return true;
		} else return false;
	} else KeyPressed[Index] = false;
	return false;
}

static struct key_s
{
	bool bPressed;
	DWORD dwStartTime;
}
kPressingKey[256];

BOOL IsKeyPressed(int Key,DWORD dwTimeOut)
{
	if( HIWORD( GetKeyState( Key ) ) )
	{
		if( !kPressingKey[Key].bPressed || ( kPressingKey[Key].dwStartTime && ( kPressingKey[Key].dwStartTime + dwTimeOut ) <= GetTickCount( ) ) )
		{
			kPressingKey[Key].bPressed = TRUE;
			if( dwTimeOut > NULL )
				kPressingKey[Key].dwStartTime = GetTickCount( );
			return TRUE;
		}
	}else
		kPressingKey[Key].bPressed = FALSE;
	return FALSE;
}

#define VK_A           0x41
#define VK_B           0x42
#define VK_A           0x41
#define VK_B           0x42
#define VK_C           0x43
#define VK_D           0x44
#define VK_E           0x45
#define VK_F           0x46
#define VK_G           0x47
#define VK_H           0x48
#define VK_I           0x49
#define VK_J           0x4A
#define VK_K           0x4B
#define VK_L           0x4C
#define VK_M           0x4D
#define VK_N           0x4E
#define VK_O           0x4F
#define VK_P           0x50
#define VK_Q           0x51
#define VK_R           0x52
#define VK_S           0x53
#define VK_T           0x54
#define VK_U           0x55
#define VK_V           0x56
#define VK_W           0x57
#define VK_X           0x58
#define VK_Y           0x59
#define VK_Z           0x5A
#define VK_0           0x30
#define VK_1           0x31
#define VK_2           0x32
#define VK_3           0x33
#define VK_4           0x34
#define VK_5           0x35
#define VK_6           0x36
#define VK_7           0x37
#define VK_8           0x38
#define VK_9           0x39