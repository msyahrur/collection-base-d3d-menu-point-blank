#include <windows.h>

static struct key_sf
{
	bool bPressedf;
	DWORD dwStartTimef;
}
kPressingKey[256];
BOOL IsKeyPressedF(int Keyf,DWORD dwTimeOutf)
{
	if( HIWORD( GetKeyState( Keyf ) ) )
	{
		if( !kPressingKey[Keyf].bPressedf || ( kPressingKey[Keyf].dwStartTimef && ( kPressingKey[Keyf].dwStartTimef + dwTimeOutf ) <= GetTickCount( ) ) )
		{
			kPressingKey[Keyf].bPressedf = TRUE;
			if( dwTimeOutf > NULL )
				kPressingKey[Keyf].dwStartTimef = GetTickCount( );
			return TRUE;
		}
	}else
		kPressingKey[Keyf].bPressedf = FALSE;
	return FALSE;
}