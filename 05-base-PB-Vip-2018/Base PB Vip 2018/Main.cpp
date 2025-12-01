//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//--        // Created By : MhmmdYogiSaputra                                                               --  
//--        // Facebook   : https://www.facebook.com/gigntng                                               --
//--        // Youtube    : https://www.youtube.com/channel/UCoCztOogokhBSJoAFWiW1yA                       --
//--       // Website    : http://www.pintercit.me/                                                        --
//--                                                                                                       --
//--        // CopyRight 2018  ( Woy Ngentod Jangan Di Ganti CopyRight Dan Created Hargain Anjing Kontol ) --
//--                                                                                                       -- 
//------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
#include "Main.h"
#include "XorStr.h"

#include "GlobalDefines.h"
#include "MenuColor.h"
#include "directInput.h"
#include "LoadDll.h"
#include "LoadDllTools.h"

#include "FeatureEngine.h"

#include "AddyLogger.h"
#include "GameClasses.h"

#include "D3DMenu.h"

#include "DrawingTools.h"

#include "ESPLoop.h"
#include "HackLoop.h"

#include "D3DHack.h" 
#include "D3DHook.h"

#pragma warning(disable:4007 4129 4715)

 

#pragma comment(lib, "XenonProject")
HMODULE hMyDll;
DWORD __declspec(dllexport)DllMain (HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
	hMyDll = hModule;
	LPSTR lpModulePath = (LPSTR)GlobalAlloc(GPTR,1000);
    GetModuleFileNameA(NULL,lpModulePath,1000);
	LocalDllName = string(lpModulePath);

	if(dwReason == DLL_PROCESS_ATTACH){
		InitLog();
		//CreateThread(0,0,(LPTHREAD_START_ROUTINE)ThreadHook,0,0,0);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CallerThread, NULL, NULL, NULL);
		MessageBox(NULL, "Ganti Terserah Dah", "PointBlank.exe", MB_OK);
		//CreateThread(0,0,(LPTHREAD_START_ROUTINE)HDSN_HACKS,0,0,0);
		/*GetModuleFileName(hModule, dlldir, 512);
		for(int i = strlen(dlldir); i > 0; i--) { if(dlldir[i] == '\\') { dlldir[i+1] = 0; break;}}
		infile.open(GetDirectoryFile("SearchLog.txt"), ios::out);*/
		Beep(2000,100);
	}
	return true;
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//--        // Created By : MhmmdYogiSaputra                                                               --  
//--        // Facebook   : https://www.facebook.com/gigntng                                               --
//--        // Youtube    : https://www.youtube.com/channel/UCoCztOogokhBSJoAFWiW1yA                       --
//--       // Website    : http://www.pintercit.me/                                                        --
//--                                                                                                       --
//--        // CopyRight 2018  ( Woy Ngentod Jangan Di Ganti CopyRight Dan Created Hargain Anjing Kontol ) --
//--                                                                                                       -- 
//------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------