//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
DWORD ResultPTRName;
DWORD ResultUserDeath;
DWORD ResultPTRgetSlotWeapon;
DWORD ResultGetCurrent;
DWORD ResultCallgetSlotWeapon;
DWORD ResultGetOneVert;
DWORD ResultGetOneHorz;
DWORD ResultGetRecoilHorz;
DWORD ResultGetRecoilVert;
DWORD ResultGetEnteredServerX;
DWORD ResultGetEnteredServerJMP;
DWORD ResultSetNightVisionEnable;
DWORD ResultNET_Fire;

DWORD dwStartAddress;
DWORD dwSize;

DWORD GetSizeofCode( const char* szModuleName ) 
{ 
	HMODULE hModule = GetModuleHandleA( szModuleName ); 
	if ( !hModule ) return 0; 
	PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER( hModule ); 
	if( !pDosHeader ) return 0; 
	PIMAGE_NT_HEADERS pNTHeader = PIMAGE_NT_HEADERS( (LONG)hModule + pDosHeader->e_lfanew ); 
	if( !pNTHeader ) return 0; 
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pNTHeader->OptionalHeader; 
	if( !pOptionalHeader ) return 0; 
	return pOptionalHeader->SizeOfCode;
}

void LogScanner()
{
	dwStartAddress					= (DWORD)GetModuleHandleA("PointBlank.exe");(!dwStartAddress);
	dwSize							= GetSizeofCode("PointBlank.exe");(!dwSize);

	DWORD getNickFotSlot			= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"const char *__thiscall CGameContext::getNickForSlot(int)", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
	DWORD getUserDeath				= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"bool __thiscall CGameContext::getUserDeath(int)", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
	DWORD dwgetCurrent				= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"class WeaponBase *__thiscall CGameCharaWeaponContext::getCurrent(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
	DWORD dwgetSlotWeapon			= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"STR_HACKER_MSG","xxxxxxxxxxxxxx",NULL);
	DWORD dwPTRgetSlotWeapon		= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"class WeaponBase *__thiscall CGameCharaWeaponContext::getCurrent(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",-0x12);
	DWORD GetOneVert				= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"int __thiscall WeaponBase::GetOneVertEnable(class CWeaponInfo *,bool)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0x60);
	DWORD GetOneHorz				= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"int __thiscall WeaponBase::GetOneHorzEnable(class CWeaponInfo *,bool)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0x60);
	DWORD GetRecoilHorz				= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"int __thiscall WeaponBase::GetRecoilHorzCount(class CWeaponInfo *,bool)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0x7B);
	DWORD GetRecoilVert				= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"int __thiscall WeaponBase::GetRecoilVertCount(class CWeaponInfo *,bool)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",0x60);
	DWORD GetEnteredServer			= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"int __thiscall CGameContext::GetEnteredServer(void)","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
	DWORD dwSetNightVisionEnable	= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"void __thiscall CGameFramework::SetNightVisionEnable(int)", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);
	DWORD dwNET_Fire				= PUSH_STR_PB(dwStartAddress, dwSize, (PBYTE)"void __thiscall WeaponBase::NET_Fire(union VEC3D *,union VEC3D *,enum WEAPON_FIRE_ORDER)", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",NULL);

	ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (dwPTRgetSlotWeapon+0x2), &ResultPTRgetSlotWeapon, sizeof(ResultPTRgetSlotWeapon), NULL);
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID) (getNickFotSlot+0xC0), &ResultPTRName, sizeof(ResultPTRName), NULL);

	ResultGetCurrent				= dwgetCurrent-0x2E;	
	ResultCallgetSlotWeapon			= dwgetSlotWeapon+0x85;
	ResultUserDeath					= getUserDeath-0x15;
	ResultGetOneVert				= GetOneVert;
	ResultGetOneHorz 				= GetOneHorz;
	ResultGetRecoilHorz				= GetRecoilHorz;
	ResultGetRecoilVert				= GetRecoilVert;
	ResultGetEnteredServerX			= GetEnteredServer-0x42;
	ResultGetEnteredServerJMP		= GetEnteredServer-0x3C;
	ResultSetNightVisionEnable		= dwSetNightVisionEnable - 0x15;
	ResultNET_Fire					= dwNET_Fire-0xD7;
}

void LogAddyValues()
{
	LogScanner();
	AddyEngine = new cAddyEngine;
	AddyEngine->AddAddyByPattern("XFHPB.Function.ReadBaseValue", ADDY_FUNCTION_GETCALL, 14, 4, "PointBlank.exe", "8B 4D 0C E8 ?? ?? ?? ?? 50 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ??");
	oReadBaseValue = (tReadBaseValue)(AddyEngine->GetAddyValueByKey("XFHPB.Function.ReadBaseValue"));
	AddyEngine->AddAddyByPattern("XFHPB.Import.i3CollideeLine::SetEnd", ADDY_GET_VALUE, 15, 4, "PointBlank.exe", "8B 4D 0C 51 8B 4D F4 81 C1 ?? ?? ?? ?? FF 15 ?? ?? ?? ??");
	AddyEngine->AddAddyByPattern("XFHPB.Import.i3AiContext::getLocalTime", ADDY_GET_VALUE, 5, 4, "PointBlank.exe", "8B 4D 08 FF 15 ?? ?? ?? ?? 8B 45 FC 50 8B 4D F0");
	AddyEngine->AddAddyByPattern("XFHPB.Import.i3RenderContext::EndRender", ADDY_GET_VALUE, 2, 4, "i3FrameWorkDx.dll", "FF 15 ?? ?? ?? ?? 8B 4E 18 FF 15 ?? ?? ?? ?? 85 C0");
	AddyEngine->AddAddyByPattern("XFHPB.Function.UpdateJumpX", ADDY_NORMAL, 0x8, NULL, "PointBlank.exe", "F3 0F 11 82 98 01 ?? ?? D9 45 FC");
	AddyEngine->AddAddyByValue("XFHPB.Function.UpdateJumpJMP", AddyEngine->GetAddyValueByKey("XFHPB.Function.UpdateJumpX")+0x5);
	AddyEngine->AddAddyByPattern("XFHPB.Pointer.QuickChange", ADDY_GET_VALUE, 10, 2, "PointBlank.exe", "89 4D FC 8B 45 FC 33 C9 83 78 ?? ?? 0F 95 C1 8A C1 8B E5 5D C3 CC");
	AddyEngine->AddAddyByPattern("XFHPB.Values.GaugeMultiplier", ADDY_GET_VALUE, 15, 4, "PointBlank.exe", "C7 45 ?? 01 00 00 00 DB 45 ?? DA 75 ?? DC 0D ?? ?? ?? ??");

	AddyEngine->AddAddyByValue("RenderContext.Base", (DWORD)GetProcAddress(GetModuleHandle("i3GfxDx.dll"), "?g_pRenderContext@@3PAVi3RenderContext@@A"));
	AddyEngine->AddAddyByValue("RenderContext.Function.GetProjectMatrix", (DWORD)GetProcAddress(GetModuleHandle("i3GfxDx.dll"), "?GetProjectMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ"));
	AddyEngine->AddAddyByValue("RenderContext.Function.GetViewMatrix", (DWORD)GetProcAddress(GetModuleHandle("i3GfxDx.dll"), "?GetViewMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ"));
	AddyEngine->AddAddyByValue("RenderContext.Function.GetWorldMatrix", (DWORD)GetProcAddress(GetModuleHandle("i3GfxDx.dll"), "?GetWorldMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ"));

	AddyEngine->AddAddyByValue("i3InputMouse.Function.GetButtonState", (DWORD)GetProcAddress(GetModuleHandle("i3InputDx.dll"), "?GetButtonState@i3InputMouse@@QAEIXZ"));

	AddyEngine->AddAddyByPattern("GameFramework.Base", ADDY_GET_VALUE, 8, 4, "PointBlank.exe", "8D 95 C0 FE FF FF 52 B9 ?? ?? ?? ? E8 ?? ?? ?? ?? 8B C8");
	AddyEngine->AddAddyByPattern("GameFramework.Function.RaycastClosest", ADDY_FUNCTION_GETCALL, 25, NULL, "PointBlank.exe", "C7 45 F0 ?? ?? ?? ?? 6A 00 8B 45 ?? 50 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ??");
	AddyEngine->AddAddyByPattern("GameFramework.Pointer.I3InputMouse", ADDY_GET_VALUE, 11, 4, "PointBlank.exe", "51 D9 EE D9 1C 24 8B 45 F8 8B 88 ?? ?? ?? ?? FF 15 ?? ?? ?? ?? 51");

	AddyEngine->AddAddyByValue("GameStatus.Base", AddyEngine->GetAddyValueByKey("GameFramework.Base") + 0x3B0+0x100);

	AddyEngine->AddAddyByPattern("PhysixResult.Pointer.Distance", ADDY_GET_VALUE, 13, 4, "PointBlank.exe", "E9 ?? ?? ?? ?? 8B 8D 48 FF FF FF 81 C1 ?? ?? ?? ?? E8 ?? ?? ?? ??");
	AddyEngine->AddAddyByPattern("PhysixResult.Function.ReadData", ADDY_FUNCTION_GETCALL, 17, 4, "PointBlank.exe", "E9 ?? ?? ?? ?? 8B 8D 48 FF FF FF 81 C1 ?? ?? ?? ?? E8 ?? ?? ?? ??");

	AddyEngine->AddAddyByPattern("PhaseReadyRoom.Function.SelfRemoveFromRoom", ADDY_FUNCTION_FINDSTART, 13, NULL, "PointBlank.exe", "6A 00 6A 00 6A 00 6A 01 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 8B 4D FC C7 81 ?? ?? ?? ??");

	AddyEngine->AddAddyByPattern("GameContext.Base", ADDY_GET_VALUE, 10, 4, "PointBlank.exe", "8B 4D 0C E8 ?? ?? ?? ?? 50 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ??");
	AddyEngine->AddAddyByPattern("GameContext.Pointer.MySlotIdx", ADDY_GET_VALUE, 16, 4, "PointBlank.exe", "E8 ?? ?? ?? ?? 83 C4 08 8B 45 FC 8B 4D 08 89 88 ?? ?? ?? ?? 8B E5 5D C2 04 00 CC");
	if(AddyEngine->GetAddyValueByKey("GameContext.Pointer.MySlotIdx") == NULL){
	AddyEngine->AddAddyByPattern("GameContext.Pointer.MySlotIdx", ADDY_GET_VALUE, 17, 4, "PointBlank.exe", "FF 15 ?? ?? ?? ?? 83 C4 08 8B 45 FC 8B 4D 08 89 88 ?? ?? ?? ?? 8B E5 5D C2 04 00 CC");}
	AddyEngine->AddAddyByPattern("GameContext.Function.getNickForSlot", ADDY_GET_VALUE, 8, 8, "PointBlank.exe", "55 8B EC 51 89 4D FC 83 7D 08 ?? 7C 06 83 7D 08 10 7C 29 6A ?? 68 34 ?? BD ?? 68 2A 04 ?? ?? 6A");
	AddyEngine->AddAddyByPattern("GameContext.Function.setEvent", ADDY_FUNCTION_GETCALL, 12, 4, "PointBlank.exe", "B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 8B 45 F8 8A 88 ?? ?? ?? ??");
	AddyEngine->AddAddyByPattern("GameContext.Function.SetInviteUser", ADDY_FUNCTION_GETCALL, 16, 4, "PointBlank.exe", "8B 4D F8 51 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 8B 55 FC");
	AddyEngine->AddAddyByPattern("GameContext.Function.GetChannelUserCount", ADDY_FUNCTION_GETCALL, 12, 4, "PointBlank.exe", "B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 89 45 F8 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 3B 45 F8 7F 41");
	AddyEngine->AddAddyByValue("GameContext.Pointer.ChannelUserCount", ADDY_GET_VALUE, 0x45, 4, AddyEngine->GetAddyValueByKey("GameContext.Function.GetChannelUserCount"));
	AddyEngine->AddAddyByPattern("GameContext.Function.GetMaxChannelUserCount", ADDY_FUNCTION_GETCALL, 17, 4, "PointBlank.exe", "A1 ?? ?? ?? ?? 33 C5 89 45 F0 56 89 4D A4 8B 4D A4 E8 ?? ?? ?? ??");
	AddyEngine->AddAddyByValue("GameContext.Pointer.MaxChannelUserCount", ADDY_GET_VALUE, 12, 4, AddyEngine->GetAddyValueByKey("GameContext.Function.GetMaxChannelUserCount"));

	AddyEngine->AddAddyByPattern("GameCharaCollisionContext.Pointer.CrosshairTarget", ADDY_GET_VALUE, 12, 4, "PointBlank.exe", "C7 45 EC 01 00 00 00 8B 4D ?? 81 C1 ?? ?? ?? ?? E8 ?? ?? ?? ?? 85 C0");	
	AddyEngine->AddAddyByPattern("GameCharaCollisionContext.Function.ReadData", ADDY_FUNCTION_GETCALL, 16, NULL, "PointBlank.exe", "C7 45 EC 01 00 00 00 8B 4D ?? 81 C1 ?? ?? ?? ?? E8 ?? ?? ?? ?? 85 C0");	
	
	AddyEngine->AddAddyByPattern("GameCharaBoneContext.Function.getBones", ADDY_FUNCTION_GETCALL, 19, NULL, "PointBlank.exe", "D9 1C 24 8B 4D FC 8B 89 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ??");	
	AddyEngine->AddAddyByValue("GameCharaBoneContext.Size.BonesAlign", AddyEngine->ParseAddyByOption(&sAddy("Temp",AddyEngine->GetAddyValueByKey("GameCharaBoneContext.Function.getBones")), ADDY_GET_VALUE, 22, 4)->Value);

	AddyEngine->AddAddyByPattern("WeaponBase.Function.Reset", ADDY_FUNCTION_GETCALL, 7, NULL, "PointBlank.exe", "51 89 4D FC 8B 4D FC E8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 25 FF FF 00 00");
	AddyEngine->AddAddyByPattern("WeaponBase.Function.DoFire", ADDY_FUNCTION_GETCALL, 7, NULL, "PointBlank.exe", "6A 00 6A 00 8B 4D F4 E8 ?? ?? ?? ?? 8B 45");
	AddyEngine->AddAddyByPattern("WeaponBase.Function.DoLineCollision", ADDY_FUNCTION_GETCALL, 8, NULL, "PointBlank.exe", "52 8D 45 E8 50 8B 4D D8 E8 ?? ?? ?? ?? EB");

	AddyEngine->AddAddyByValue("GameCharaBase.Base", AddyEngine->GetAddyValueByKey("GameContext.Base") - 0x38);
	AddyEngine->AddAddyByPattern("GameCharaBase.Function.getGameCharaBoneContext", ADDY_FUNCTION_GETCALL, 12, NULL, "PointBlank.exe", "D9 1C 24 8B 4D FC 8B 89 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ??");	
	AddyEngine->AddAddyByPattern("GameCharaBase.Function.getGameCharaCollisionContext", ADDY_FUNCTION_GETCALL, 10, NULL, "PointBlank.exe", "E8 ?? ?? ?? ?? EB ?? 8B 4D ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? E9");
	AddyEngine->AddAddyByPattern("GameCharaBase.Function.getGameCharaWeaponContext", ADDY_FUNCTION_GETCALL, 10, NULL, "PointBlank.exe", "0F B6 D0 85 D2 75 ?? 8B 4D F8 E8 ?? ?? ?? ??");
	AddyEngine->AddAddyByValue("GameCharaBase.Function.getGameCharaAnimContext", ADDY_FUNCTION_GETCALL, 20, NULL, AddyEngine->ParseAddyByOption(AddyEngine->FindAddyByPattern("Temp", "PointBlank.exe", "88 45 C7 8B 8D ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8"), ADDY_FUNCTION_GETCALL, 9, NULL)->Value);
	AddyEngine->AddAddyByPattern("GameCharaBase.Function.getCharaNetIdx", ADDY_FUNCTION_GETCALL, 14, NULL, "PointBlank.exe", "D8 4D ?? D9 5D ?? E9 ?? ?? ?? ?? 8B 4D ?? E8 ?? ?? ?? ??");
	AddyEngine->AddAddyByPattern("GameCharaBase.Function.getCurHP", ADDY_FUNCTION_FINDSTART, NULL, NULL, "PointBlank.exe", "8B 4D FC 81 C1 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? E8 ?? ?? ?? ??");
	AddyEngine->AddAddyByPattern("GameCharaBase.Function.eventFall", ADDY_FUNCTION_GETCALL, 25, NULL, "PointBlank.exe", "6A 00 68 FF FF 00 00 68 FF 00 00 00 8B 4D ?? 83 C1 ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ??");
	AddyEngine->AddAddyByPattern("GameCharaBase.Function.setCharaWeapon", ADDY_FUNCTION_GETCALL, 21, NULL, "PointBlank.exe", "B9 E8 03 00 00 F7 F1 50 8B 55 ?? 52 8B 45 ?? 8B 88 ?? ?? ?? ?? E8 ?? ?? ?? ??");
	AddyEngine->AddAddyByPattern("GameCharaBase.Function.Cmd_Respawn", ADDY_NORMAL, 6, 0, "PointBlank.exe", "E8 ?? ?? ?? ?? C3 53 8B DC 83 EC 08 83 E4 F0 83 C4 04 55 8B 6B 04");
	AddyEngine->AddAddyByPattern("GameCharaBase.Function.writeData", ADDY_FUNCTION_GETCALL, 16, NULL, "PointBlank.exe", "D9 45 E4 51 D9 1C 24 8B 4D ?? 81 C1 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 4D");
	AddyEngine->AddAddyByPattern("GameCharaBase.Pointer.invicibleTime", ADDY_GET_VALUE, 12, 4, "PointBlank.exe", "D9 45 E4 51 D9 1C 24 8B 4D ?? 81 C1 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B 4D");

	AddyEngine->AddAddyByPattern("GameCharaManager.Base", ADDY_GET_VALUE, 5, 4, "PointBlank.exe", "8B 4D 08 51 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? 89 45 F8");
	AddyEngine->AddAddyByPattern("GameCharaManager.Function.getCharaByNetIdx", ADDY_FUNCTION_FINDSTART, NULL, NULL, "PointBlank.exe", "EB ?? 8B 45 08 8B 4D FC 8B 44 81 ?? 8B E5");
	AddyEngine->AddAddyByPattern("GameCharaManager.Function.RespawnChara", ADDY_FUNCTION_GETCALL, 20, NULL, "PointBlank.exe", "8B C8 E8 ?? ?? ?? ?? 50 B9 ?? ?? ?? ?? E8 ?? ?? ?? ?? 8B C8 E8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 25 01 00 00 80");
	Beep(1300, 500);
}