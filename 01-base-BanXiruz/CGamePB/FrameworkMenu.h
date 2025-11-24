//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
char *Moptfolder	[]	= {" [0/1]", " [1/1]"};
char *Moptonoff		[]	= {": OFF", ": ON"};
char *Moptmd3d9		[]	= {": OFF", ": Press L-CTRL"};
char *Moptreborn	[]	= {": OFF", ": Press R-CTRL"};
char *Mopttelept	[]	= {": OFF", ": Press H"};
char *Moptbullet	[]	= {": OFF", ": Head", ": Body"};
char *Moptrapid		[]	= {": OFF", ": Lv. 1", ": Lv. 3", ": Lv. 5", ": Lv. 10"};
char *Moptasslt		[]  = {": OFF", ": AK Sopmod D", "AK 47 FC Red", "AK Sopmod Medical", "AK Sopmod Sakura", "AUG A3", "AUG A3 EV", "AUG A3 Gold", "AUG A3 Chicano", "AUG A3 Beach", "AUG A3 Naga", "AUG A3 Comic", "AUG A3 Midnight3", "AUG A3 PBWC 2017", "AUG A3 CNPB T5", "AUG A3 Mech", "AUG A3 Lebaran 2017", "AUG A3 Infinitum", "AUG A3 Grafitty", "AUG A3 Tropical", "Pindad SS2 V5 Infinitum", "SC 2010 Lebaran 2017", "SC 2010 Infinitum", "SC 2010 Green", "SC 2010 X-Mas", "Water Gun", "MSBS", "MSBS Silver", "MSBS Gold", "M4 SR-16 Lv1", "M4 SR-16 Lv2", "M4 SR-16 Lv3", "M4 SR-16 FC", "Famas G2", "Famas G2 Comando", "Famas G2 Sniper", "Famas G2 M203", "Famas G2 Comando Gold", "Famas G2 Comando E-Sport", "Famas G2 Comando PBWC 2017"};
char *Moptsubma		[]  = {": OFF", ": P90 Ext D", "P90 Ext Mech", "P90 Ext Infinitum", "P90 Ext Lebaran 2017", "P90 Ext CNPB T5", "P90 Ext Midnight3", "P90 Ext Green", "P90 Ext Naga", "OA 93 Grafitty", "OA 93 Infinitum", "OA 93 Mech", "OA 93 PBWC 2017", "OA 93 Midnight3", "OA 93 Tropical", "Kriss SV Tropical", "Kriss SV Grafitty", "Kriss SV Infinitum", "Kriss SV Lebaran 2017", "Kriss SV PBWC 2017", "Kriss SV Midnight3", "Kriss SV Green", "Kriss SV Comic", "Kriss SV Naga", "Kriss SV Beach", "Kriss SV Chicano", "Kriss SV E-Sport", "Kriss SV Love"};
char *Moptsnipe		[]  = {": OFF", ": Rangemaster .338", "Rangemaster 7,62", "Rangemaster 7,62 STBY", "Barrett M82A1", "Barrett M82A1 Premium", "AS 50 Infinitum", "AS 50 Midnight3", "L115A1", "L115A1 SE", "L115A1 E-Sport", "Cheytac M200", "Cheytac M200 Tropical", "Cheytac M200 CNPB T5", "Cheytac M200 PBWC 2017", "Cheytac M200 Comic", "Cheytac M200 Naga", "Cheytac M200 Chicano", "PGM Hecate2 Beach", "Tactilite T2", "Tactilite T2 Grafitty", "Tactilite T2 Infinitum", "Tactilite T2 Lebaran 2017", "Tactilite T2 Mech", "Tactilite T2 PBWC 2017", "Tactilite T2 Green"};
char *Moptshotg		[]  = {": OFF", ": Kel-Tec KSG-15", "Jackhammer", "SPASS 15 D", "SPASS 15 SI", "SPASS 15 MSC", "M1187 D", "M1187 SL", "M1187 Tropical", "M1187 Infinitum", "M1187 Lebaran 2017", "M1187 Mech", "M1187 PBWC 2017", "M1187 Green", "M1187 Comic", "M1187 Naga", "M1187 Beach", "M1187 Chicano", "Zombie Slayer Infinitum"};
char *Moptlaunc		[]	= {": OFF", ": RPG-7", ": M-79", ": HK-69"};

void RebuildMenu(LPDIRECT3DDEVICE9 pDevice)
{
	AddItem("[•Information•]"	, Moptfolder	, &Feature.Folders.Info			, 2		, MENUFOLDER);
	if(Feature.Folders.Info)
	{
		AddText("[<•>] Get Date", GetDate());
		AddText("[<•>] Get Time", GetTime());
	//	AddText("[<•>] Expired Cheat", output2);
		AddText("[<•>] Hide Menu", ": INSERT");
		AddText("[<•>] Force Exit", ": F12");
	}

	AddItem("[•Simple Hack•]"		, Moptfolder	, &Feature.Folders.Direct3D		, 2		, MENUFOLDER);
	if(Feature.Folders.Direct3D)
	{
		AddItem("[<•>] Move D3D9"			, Moptmd3d9,  &Feature.Direct3D.MoveD3D9	, 2,  MENUCAT);
		AddItem("[<•>] CrossHair"			, Moptonoff,  &Feature.Direct3D.CrossHair	, 2,  MENUCAT);
		AddItem("[<•>] ESP Bone(F1)"		, Moptonoff,  &Feature.ESP.Bone				, 2,  MENUCAT);
		AddItem("[<•>] AimReal(CAPSLOCK)"	, Moptbullet, &Feature.AIM.Real				, 3,  MENUCAT);
		AddItem("[<•>] No Recoil(F3)"		, Moptonoff,  &Feature.Weapon.NoRecoil		, 2,  MENUCAT);
		AddItem("[<•>] QuickChange"			, Moptonoff,  &Feature.Weapon.QuickChange	, 2,  MENUCAT);
	}
	AddItem("[•Medium Hard•]"		, Moptfolder	, &Feature.Folders.Medium		, 2		, MENUFOLDER);
	if(Feature.Folders.Medium)
	{
		AddItem("[<•>] Jump Hight"			, Moptonoff,  &Feature.Player.JumpHight		, 2,  MENUCAT);
		AddItem("[<•>] Hide Nick"			, Moptonoff,  &Feature.Player.HideNick		, 2,  MENUCAT);
		AddItem("[<•>] Accuracy"			, Moptonoff,  &Feature.Weapon.Accuracy		, 2,  MENUCAT);
		AddItem("[<•>] Auto Macro"			, Moptonoff,  &Feature.Weapon.AutoMacro		, 2,  MENUCAT);
		AddItem("[<•>] Suicide(END)"		, Moptonoff,  &Feature.Player.AutoSuicide	, 2,  MENUCAT);
		AddItem("[<•>] No FallDamage"		, Moptonoff,  &Feature.Player.NoFallDamage	, 2,  MENUCAT);
		AddItem("[<•>] RebornChara"			, Moptonoff,  &Feature.Player.Reborn		, 2,  MENUCAT);
	}
	AddItem("[•Hard Hack•]"			, Moptfolder	, &Feature.Folders.Hard			, 2		, MENUFOLDER);
	if(Feature.Folders.Hard)
	{
		AddItem("[<•>] Aim Bullet(HOME)"	, Moptbullet, &Feature.AIM.Bullet			, 3,  MENUCAT);
		AddItem("[<•>] Auto Shot"			, Moptonoff,  &Feature.Weapon.AutoShot		, 2,  MENUCAT);
		AddItem("[<•>] Auto Fire"			, Moptonoff,  &Feature.AIM.AutoFire			, 2,  MENUCAT);
		AddItem("[<•>] Net Fire"			, Moptonoff,  &Feature.AIM.NetFire			, 2,  MENUCAT);
		AddItem("[<•>] Auto Killer"			, Moptbullet, &Feature.AIM.AutoKiller		, 3,  MENUCAT);
		AddItem("[<•>] Rapid Fire"			, Moptrapid,  &Feature.Weapon.RapidFire		, 5,  MENUCAT);
		AddItem("[<•>] Teleport Mode"		, Mopttelept, &Feature.Player.Teleport		, 2,  MENUCAT);
		AddItem("[<•>] Shield Bomb"			, Moptreborn, &Feature.Player.Shield		, 2,  MENUCAT);
	}
	AddItem("[•ESP Hack•]"			, Moptfolder	, &Feature.Folders.ESP			, 2		, MENUFOLDER);
	if(Feature.Folders.ESP)
	{
		AddItem("[<•>] ESP Line"			, Moptonoff,  &Feature.ESP.Line				, 2,  MENUCAT);
		AddItem("[<•>] ESP Name"			, Moptonoff,  &Feature.ESP.NameTag			, 2,  MENUCAT);
		AddItem("[<•>] ESP Health"			, Moptonoff,  &Feature.ESP.Health			, 2,  MENUCAT);
		AddItem("[<•>] Tag Name GM"			, Moptonoff,  &Feature.ESP.TagGM			, 2,  MENUCAT);
	}
	AddItem("[•GBMode Hack•]"		, Moptfolder	, &Feature.Folders.GBMode		, 2		, MENUFOLDER);
	if(Feature.Folders.GBMode)
	{
		AddItem("[<•>] Open Server Full"	, Moptonoff,  &Feature.Misc.OpenSFull		, 2,  MENUCAT);
		AddItem("[<•>] Unlock Pass Room"	, Moptonoff,  &Feature.Misc.UnlockPW		, 2,  MENUCAT);
		AddItem("[<•>] Anti Kick RM"		, Moptonoff,  &Feature.Misc.AntiKick		, 2,  MENUCAT);
		AddItem("[<•>] Auto Invite"			, Moptonoff,  &Feature.Misc.AutoInvite		, 2,  MENUCAT);
		AddItem("[<•>] Auto Ready"			, Moptonoff,  &Feature.Misc.AutoReady		, 2,  MENUCAT);
		AddItem("[<•>] Auto Bundir"			, Moptonoff,  &Feature.Misc.AutoBundir		, 2,  MENUCAT);
	}
	AddItem("[•Replace Hack•]"		, Moptfolder	, &Feature.Folders.Replace		, 2		, MENUFOLDER);
	if(Feature.Folders.Replace)
	{
		AddItem("[<•>] Assault"				, Moptasslt,  &Feature.Replace.Assault		, 40, MENUCAT);
		AddItem("[<•>] SubMachine"			, Moptsubma,  &Feature.Replace.Smg			, 28, MENUCAT);
		AddItem("[<•>] Sniper"				, Moptsnipe,  &Feature.Replace.Sniper		, 26, MENUCAT);
		AddItem("[<•>] ShotGun"				, Moptshotg,  &Feature.Replace.Shotgun		, 19, MENUCAT);
		AddItem("[<•>] Launcher"			, Moptlaunc,  &Feature.Replace.Launcher		, 4,  MENUCAT);
	}
	AddText("WAWA ANDRA","");
}

void DrawD3DFont(LPDIRECT3DDEVICE9 pDevice)
{
	if (DrawFont == 1) 
	{
		D3DXCreateFontA(pDevice, 15, 0, FW_EXTRABOLD, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Comic Sans MS", &pFont);
		D3DXCreateFontA(pDevice, 14, 0, FW_EXTRALIGHT + FW_BOLD, 2, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCSTR)"Segoe UI", &g_pFont);
		D3DXCreateFontA(pDevice, 15, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Hud_Small_Font", &mFont);
		D3DXCreateLine(pDevice,&g_pLine);
		D3DXCreateSprite(pDevice, &textSprite);
		DrawFont = 0;
	}
}

void DrawD3DMenu(LPDIRECT3DDEVICE9 pDevice)
{
	if (Drawing == 0)
	{
		if(Mmax==0) 
		RebuildMenu(pDevice);
		MenuShow(mx,my,pDevice);
		MenuNav();
	}
}