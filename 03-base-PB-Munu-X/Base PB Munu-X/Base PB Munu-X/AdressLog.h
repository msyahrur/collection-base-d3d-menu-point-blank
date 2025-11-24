//--------------------------------------------------------------------------//
HMODULE hGfxDx	= LoadLibrary("i3GfxDx.dll");
DWORD dwPBExe   = (DWORD)GetModuleHandleA("PointBlank.exe");
DWORD dwNxChara = (DWORD)GetModuleHandleA("NxCharacter.2.8.1.dll");
//--------------------------------------------------------------------------//
#define ResultBasePlayer	 0x98B0D4
#define ResultBasePlayer2	 0xD8B0D4
#define ResultBaseHealth	(ResultBasePlayer-0x34)
#define ResultBaseHealth2	(ResultBasePlayer2-0x34)
#define ResultBaseAmmo		(ResultBasePlayer-0x38)
#define ResultBaseAmmo2		(ResultBasePlayer2-0x38)
#define HookEndRender        0x53A8
#define HookBaseRender       0x1E7790
//--------------------------------------------------------------------------//