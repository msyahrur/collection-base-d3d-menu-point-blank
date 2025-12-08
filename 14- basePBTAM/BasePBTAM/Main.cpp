#include "Main.h"
#include "Class.h"
// 
//#include "cLogger.h"
//#include <math.h>
//
//#include "StandardIncludes.h"
//#include "Tools.h"
D3DVIEWPORT9    g_ViewPort;
LPD3DXFONT      g_pFont = NULL;
 

int Drawing		= 0;	
int DrawFont	= 1;
//int uyeh = 0;

int wew = 1;
int whack = 0;
int d3d = 1;
int uyeh = 0;
int wexley=false;
int Smoke       = 0;
int Exit       = 0;
int bone = 0;
int Text        = false;
int CrossHire = 0;
int BrutalSmoke=0;
#define MAROON			D3DCOLOR_ARGB(255, 142, 30, 0)
#define LGRAY		    D3DCOLOR_ARGB(255, 174, 174, 174)  
bool Auth;
int Wallhack = 0;
int Wallhack2 = 0;
int FullCharm;
int group = 0;
int Player2 = 0;
int Player3 = 0;
int Player1 = 0;
char *KeyAim[] = { "LClick","SHIFT","ALT"};
char *VelocSpeed[] = { "Off","50%"};

char *MultiMode[] = { "Off","50%","100%"};
int ESBONE,ESPBox,ESPHP,ESPNAME;
char *cacad1[]	= {""};
int ESPBone;
void RebuildMenu(void)
{	
        
	//todossss("Licence:","Trial 2 Days... FUll Verison Buy Via Paypal  o Interbank");
	todossss("Copyrigth By:","Neil");
	todossss("DATE",__DATE__ );  
	todossss("TIME",__TIME__);
	todossss("PBTURKEY","NOT FOR PUBLIC");

MenuAddItem("Hack Work"     , Moptfolder  ,&Player1   ,2, MENUFOLDER);
if (Player1)
	{
//	
        MenuAddItem("NoRecoil",             Moptonoff  , &NoRecoil		, 2 , MENUITEM);
		MenuAddItem("Esqueleto",            Moptonoff  , &ESPBone		, 2 , MENUITEM);
		/*MenuAddItem("ESP Nombre",               Moptonoff  , &ESPName		, 2 , MENUITEM);
		MenuAddItem("ESP Cuadro",            Moptonoff  , &CH_ESPB3D		, 2 , MENUITEM);
		MenuAddItem("ESP Linia",               Moptonoff  , &ESPLine		, 2 , MENUITEM);
		MenuAddItem("ESP Vida",               Moptonoff  , &ESPHealth		, 2 , MENUITEM);
		MenuAddItem("Sin Rebote 1",            Moptonoff  , &NoRecoil		, 2 , MENUITEM);
	    MenuAddItem("Sin Rebote 2",            Moptonoff  , &NoRecoilHROZ		, 2 , MENUITEM);
	    MenuAddItem("Cambio Arma",            Moptonoff  , &TrocaRapida1		, 2 , MENUITEM);
		MenuAddItem("Sin Daño al Caer",            Moptonoff  , &NoFallDamage		, 2 , MENUITEM);
		MenuAddItem("Recarga Rapida",            Moptonoff  , &NoRecargar		, 2 , MENUITEM);
		MenuAddItem("Respanw",            Moptonoff  , &Respanw		, 2 , MENUITEM);
		MenuAddItem("Pasword-Sala",            Moptonoff  , &BruteForce		, 2 , MENUITEM);
		MenuAddItem("Moverse Rapido",            VelocSpeed  , &HackSpeed		, 2 , MENUITEM);
		MenuAddItem("MultiBalas",            MultiMode  , &MultiBalas		, 3, MENUITEM);
		MenuAddItem("Hack Topo",            Moptonoff  , &toup		, 2, MENUITEM);
		MenuAddItem("Fly -Space",            Moptonoff  , &FLYHACK100		, 2, MENUITEM);*/
		//MenuAddItem("Autogo",            Moptonoff  , &Autogo ,2, MENUITEM);
		

}
//		
//		
//	//  //MenuAddItem("•Cross",             MoptonoffAIM  , &Aimbottt		, 2 , MENUITEM);
//	  //MenuAddItem("•Aim Key",             KeyAim  , &AimKey2		, 4 , MENUITEM);
//	  //MenuAddItem("•AimLock",             MoptonoffAIM2  , &AimLock		, 2 , MENUITEM);
//	
//	  	//	DrawD3DItem("Cross Aim ", Moptonoff, &Aimbottt, 2, D3DDevice);
//		//DrawD3DItem("Aim Key", KeyAim, &AimKey2, 4, D3DDevice);
//		//DrawD3DItem("Aim Local", MoptTarget, &AimLock, 2, MENUCAT);
//}
//
//MenuAddItem("Hack Work"     , Moptfolder  ,&Player2   ,2, MENUFOLDER);
//if (Player2)
//	{
//
//
//		MenuAddItem("Aimbot",             MoptonoffAIM  , &Accuracy		, 2 , MENUITEM);
//	// MenuAddItem("•Cross",             MoptonoffAIM  , &Aimboot		, 2 , MENUITEM);
//	//  MenuAddItem("•Aim Key",             KeyAim  , &AimKey		, 4 , MENUITEM);
//	   MenuAddItem("Set Aimbot",             MoptonoffAIM2  , &AimLocal		, 2 , MENUITEM);
//	//  MenuAddItem("•AimLock",             MoptonoffAIM2  , &AimLock		, 2 , MENUITEM);
//
//}
//MenuAddItem("HACK VIP"     , Moptfolder  ,&Player2  , 2 , MENUFOLDER);
//if (Player2)
//	{
//	
////       MenuAddItem("PlantBomb",            Moptonoff  , &PlantBomb		, 2 , MENUITEM);
//	    MenuAddItem("Move Player",            Moptonoff  , &HackSpeed		, 2 , MENUITEM);
//////       MenuAddItem("RPG7",            Moptonoff  , &RPG7		, 2 , MENUITEM);
////       MenuAddItem("ForceRoom",            Moptonoff  , &BruteForce		, 2 , MENUITEM);
//
//}
//
//
//
//MenuAddItem("AUTO UP [VIP]"     , Moptfolder  ,&Player3   , 2, MENUFOLDER);
//if (Player3)
//	{
//	MenuAddItem("AntiAfk",            Moptonoff  , &HackAntiafk		, 2 , MENUITEM);
//	MenuAddItem("AutoGO",            Moptonoff  , &AutoGOx		, 2 , MENUITEM);
//	
//	
//}
}
void DrawMenuD3D(LPDIRECT3DDEVICE9 pDevice)
{
	if (DrawFont == 1)
	{
		D3DXCreateFontA(pDevice, 18, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
		DrawFont = 0;
	}

	if(uyeh == 0)
			{
				if (Mmax==0) 
					RebuildMenu();
				DrawMenuShow(200,70,g_pFont); // geser tex
				MenuNav();
			}	

	if (!g_pFont)	D3DXCreateFontA(pDevice, 18, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &g_pFont);//15
	if (!pLine)		D3DXCreateLine(pDevice, &pLine);
	//SetTimer(NULL, 0, 7000, (TIMERPROC)AutoGO);
}

bool bRenderText = true;
LPD3DXFONT fSmall	= NULL;
LPD3DXFONT Title    = NULL;
HRESULT WINAPI hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	//UpdateGameClass();
	pDevice->GetViewport(&g_ViewPort);
	
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->GetViewport(&Viewport);
	if(!pLine)D3DXCreateLine( pDevice, &pLine );
	if(!pFont)D3DXCreateFont( pDevice, 15, 0, FW_HEAVY, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont );
	if(!fName)  D3DXCreateFont(pDevice, 14, 0, FW_BOLD, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &fName);//15
	if(g_pFont == NULL) D3DXCreateFont(pDevice, 14, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &g_pFont); //Create fonts
	//RebuildMenuOff();
	//RebuildMenuOff2();
	//RebuildMenuOff3();
	DrawMenuD3D(pDevice);
	//CallHack();
	//CallHack();
//	AcurryHack(pDevice);
//	BrutalForcer();
//	toupeira();
//	SUUPÉRFLY();
//	afk();
//	SetTimer(NULL, 0, 7000, (TIMERPROC)AutoGO);
//	AutoGO();
//	ChamaSala3();
//	CrossAimbot(pDevice);
//	if(getStageGame() == JOGANDO)
//{
//	
//	
//		CallHack();
//	//AimBot();
//multialasfunc();
//	CallHack2();
//
//	//SuperAimbot();
//	
//
//BoneESP(pDevice);
//
//GameHackCreate22();
//
//dameueon();
//TrocaRapida();
//
//NoReloadNeil();
//EXITGAME();
//
//autoshoss();
//NoRecoilFunc();
//NoRecoilFunc2();
//
//	}
//
	return oEndScene(pDevice);
	} 
HRESULT WINAPI hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	if(g_pFont)g_pFont->OnLostDevice();

	if(textSprite)textSprite->OnLostDevice();
	if(pFont) pFont->OnLostDevice();
	if(pLine) pLine->OnLostDevice();
	if( fName )fName->OnLostDevice();
		if( fSmall )
		fSmall->OnLostDevice();
		if( Title )
		Title->OnLostDevice();
	if(oReset == D3D_OK)			
	{
	if(pFont) pFont->OnResetDevice();
	if( fName )fName->OnResetDevice();
	if(pLine) pLine->OnResetDevice();
	if(textSprite)textSprite->OnResetDevice();
	if(g_pFont)g_pFont->OnResetDevice();
		if( fSmall )
			fSmall->OnLostDevice();
		if( Title )
			Title->OnLostDevice();
	}
    return oReset(pDevice, pPresentationParameters);
} 



//---------------------------------------------------------------------------------------------





void *DetourCreateFAKE(BYTE *src, const BYTE *dst, const int len)
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
BOOL bCompareFAKE(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
for(;*szMask;++szMask,++pData,++bMask)
if(*szMask=='x' && *pData!=*bMask) 
return false;
return (*szMask) == NULL;
}
DWORD FindPatternFAKE(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask)
{
	for(DWORD i=0; i < dwLen; i++)
		if( bCompareFAKE((BYTE*)(dwAddress+i),bMask,szMask))
			return (DWORD)(dwAddress+i);

	return 0;
}
//=============================================//
typedef HRESULT(APIENTRY* oPresent) (IDirect3DDevice9*, const RECT *, const RECT *, HWND, const RGNDATA *);
HRESULT APIENTRY Present_hook(IDirect3DDevice9*, const RECT *, const RECT *, HWND, const RGNDATA *);
oPresent pPresent = 0;
//=============================================//
HRESULT APIENTRY Present_hook(IDirect3DDevice9* pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
 //menu...
		DrawMenuD3D(pDevice);
  return pPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}
//=============================================//
DWORD*vtbl=0;
DWORD end,pre;
int HookpDevice(void)
{
DWORD hD3D9=(DWORD)LoadLibraryA("d3d9.dll");
DWORD table=FindPatternFAKE(hD3D9,0x128000,(PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86","xx????xx????xx");
 
memcpy(&vtbl,(void*)(table+2),4); 
pre = vtbl[17];  
pPresent=(oPresent)DetourCreateFAKE((PBYTE)pre,(PBYTE)Present_hook,5); 
return 0;
}
//=============================================//
bool ck =true;
//BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
//{
//DisableThreadLibraryCalls(hDll);
//if (dwReason==DLL_PROCESS_ATTACH)
//{
//	MessageBox(0,"","",MB_OK);
//CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)HookpDevice,NULL,NULL,NULL); 
//}
//return TRUE;
//}





//
////CreateThread (0,0, (LPTHREAD_START_ROUTINE)&Start,0,0,0);
//BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpvReserved)
//{
//	DisableThreadLibraryCalls(hModule);
//	if (fdwReason == DLL_PROCESS_ATTACH)
//	{		
////
//		MessageBox(0,"","",MB_OK);
//	/*	CekMODEL();
//CekHWID();*/
//	//RegardoCall(TrialStarter);
//	//	CreateThread (0,0, (LPTHREAD_START_ROUTINE)&SystemStart,0,0,0);
//	EliteWorldLog(hModule,"LoggerPBTurkey.txt");
//	//system("start https://www.facebook.com/LosNachosMotors");
//	CreateThread (0,0, (LPTHREAD_START_ROUTINE)&Bagus_Updater,0,0,0);
//	CreateThread (0,0, (LPTHREAD_START_ROUTINE)&Start,0,0,0);
//	//HideModule(hModule);
//	//Initialize_HookedMyHotkey();
//	//_beginthread((void(*)(void*))ThreadHookX,0,0);
//	}
//	return TRUE;
//}