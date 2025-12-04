/*Fucntion.h D3D9 PBHacks Last Edit By Muhammad Zaki Mubarak*/

#define ZonaXCyber(Function) CreateThread(0,0,(LPTHREAD_START_ROUTINE)Function,0,0,0);
#include <windows.h>

/*-------------------------------------------------------------------------------------------------------------------*/

static struct key_s
{
	bool bPressed;
	DWORD dwStartTime;
}
kPressingKey[256];
BOOL IsKeyPressed2(int Key,DWORD dwTimeOut)
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


/*-------------------------------------------------------------------------------------------------------------------*/
VOID JMPE92(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen)
{
    DWORD dwOldProtect, dwBkup, dwRelAddr;
    VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    dwRelAddr = (DWORD) (dwJumpTo - (DWORD) pAddress) - 5;
    *pAddress = 0xE9;
    *((DWORD *)(pAddress + 0x1)) = dwRelAddr;
    for(DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
    VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
    return;
}

/*-------------------------------------------------------------------------------------------------------------------*/
void *DetourFunction2 (BYTE *src, const BYTE *dst, const int len)
{
    BYTE *jmp;
    DWORD dwback;
    DWORD jumpto, newjump;

    VirtualProtect(src,len,PAGE_READWRITE,&dwback);
    
    if(src[0] == 0xE9)
    {
        jmp = (BYTE*)malloc(10);
        jumpto = (*(DWORD*)(src+1))+((DWORD)src)+5;
        newjump = (jumpto-(DWORD)(jmp+5));
        jmp[0] = 0xE9;
       *(DWORD*)(jmp+1) = newjump;
        jmp += 5;
        jmp[0] = 0xE9;
       *(DWORD*)(jmp+1) = (DWORD)(src-jmp);
    }
    else
    {
        jmp = (BYTE*)malloc(5+len);
        memcpy(jmp,src,len);
        jmp += len;
        jmp[0] = 0xE9;
       *(DWORD*)(jmp+1) = (DWORD)(src+len-jmp)-5;
    }
    src[0] = 0xE9;
   *(DWORD*)(src+1) = (DWORD)(dst - src) - 5;

    for(int i = 5; i < len; i++)
        src[i] = 0x90;
    VirtualProtect(src,len,dwback,&dwback);
    return (jmp-len);
} 


