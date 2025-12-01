//----------------------------------------------------------------------------------------
DWORD FindPattern( DWORD dwStart, DWORD dwLen, BYTE* pszPatt, char pszMask[]){ 
unsigned int i = NULL; 
int iLen = strlen( pszMask ) - 1; 
for( DWORD dwRet = dwStart; dwRet < dwStart + dwLen; dwRet++ ){ 
if( *(BYTE*)dwRet == pszPatt[i] || pszMask[i] == '?' ){ 
if( pszMask[i+1] == '\0' ) return( dwRet - iLen ); i++; 
} 
else i = NULL; 
}
return NULL; 
}
//----------------------------------------------------------------------------------------
DWORD GetSizeofCode( const char* szModuleName ) { 
HMODULE hModule = GetModuleHandleA( szModuleName ); 
if ( !hModule ) return NULL; 
PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER( hModule ); 
if( !pDosHeader ) return NULL; 
PIMAGE_NT_HEADERS pNTHeader = PIMAGE_NT_HEADERS( (LONG)hModule + pDosHeader->e_lfanew ); 
if( !pNTHeader ) return NULL; 
PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pNTHeader->OptionalHeader; 
if( !pOptionalHeader ) return NULL; 
return pOptionalHeader->SizeOfCode; 
}
//----------------------------------------------------------------------------------------
HMODULE hGfxDx		= LoadLibrary("i3GfxDx.dll");
DWORD dwi3GfxDx     = (DWORD)GetModuleHandleA("i3GfxDx.dll");
DWORD i3GfxDx       = GetSizeofCode("i3GfxDx.dll");
DWORD dwPBExe		= (DWORD)GetModuleHandleA("PointBlank.exe");
DWORD i3PBExe		= GetSizeofCode("PointBlank.exe");
DWORD NxCharakter2	= (DWORD)LoadLibraryA("NxCharacter.2.8.1.dll");
HMODULE ModuleGFX	= LoadLibrary("i3GfxDx.dll");
DWORD NxCha			= (DWORD)GetModuleHandleA("NxCharacter.2.8.1.dll");
DWORD ModuleDX		= (DWORD)GetModuleHandle("i3BaseDx_Cli.dll");
DWORD ModuleSizeDX	= GetSizeofCode("i3BaseDx_Cli.dll");
//----------------------------------------------------------------------------------------