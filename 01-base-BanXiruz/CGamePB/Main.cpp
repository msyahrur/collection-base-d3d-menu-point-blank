//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
#include "StdAfx.h"
#include "Main.h"
#include "Hdsn.h"
#include "InputHdsn.h"
#include "DirectInputKey.h"
#include "D3DColor.h"
#include "AddyFunction.h"
#include "AddyLogger.h"
#include "CRenderContext.h"
#include "CGameFramework.h"
#include "CGameContext.h"
#include "CGameCharaBase.h"
#include "CGameCharaManager.h"
#include "GameClasses.h"
#include "FeatureStruct.h"
#include "DrawingTools.h"
#include "ESPFunctions.h"
#include "ESPLoop.h"
#include "HackFunctions.h"
#include "HackHook.h"
#include "HackLoop.h"
#include "MenuSound.h"
#include "MenuClass.h"
#include "FrameworkMenu.h"
#include "D3DHack.h"
#include "D3DHook.h"

cFeature Feature;

void MainThread()
{
	LogAddyValues();
	HookSetEnd();
	HookLocalTime();
	InitializeVisibleCheck();
	StartRoutine(HookJumpHight);
	StartRoutine(HookAutoMacro);
	StartRoutine(HookSetEvent);
	StartRoutine(ThreadHook);
} 
BOOL WINAPI DllMain (HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
	if(dwReason == DLL_PROCESS_ATTACH)
	{	
		//StartRoutine(Read_HDSN8);
		StartRoutine(MainThread);
		Beep(1000, 100);
	MessageBox(0, "Created by Wawa Andra", "Info", MB_OK | MB_ICONINFORMATION );
	}
return TRUE;
}

//NOTE :
//Saya share Base Cheat PointBlank secara gratis dan tanpa dipungut biaya apaun! Gratiss!!
//Jika ada yang memperjualbelikan Base ini, segera laporkan kepada saya! supaya tidak ada orang yang kena tipu
//Status Base, Full Fiture dengan Updatean fiture terbaru sesuai perkembangan Game PointBlank
//Sudah support ALT-TAB dan All OS Windows karena menggunakan Hook Engine i3Framework
//Auto Logger, jadi resiko geser saat Maintance PointBlank sedikit! Dijamin Base tahan lama
//Gunakan Base ini dengan bijak! Kami tidak bertanggungjawab apabila ada masalah dengan Base ini!
//Jika ada problem saat menggunakan Base ini, bisa Lapor/Konsultasi di groups Facebook kami
//Website Resmi : www.citpurworejo.com
//Groups Facebook : www.facebook.com/groups/purworejocheater
//Copyright (c) 2018 Cheat Purworejo
//Salam #Admin Refaldy Muhammad