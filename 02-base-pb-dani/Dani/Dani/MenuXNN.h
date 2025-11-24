//Created by DANI XCT / WA DANI IDI/MENU XXN PART 2
char *Moptfolder	[]	= {" [+]", " [-]"};
char *Moptonoff		[]	= {"•", "ON"};
char *Moptmd3d9		[]	= {"•", "Press L-CTRL"};
char *Moptreborn	[]	= {"•", "Press R-CTRL"};
char *Mopttelept	[]	= {"•", "Press H"};
char *Moptbullet	[]	= {"•", "Head", ": Body"};
char *Moptrapid		[]	= {"•", "Lv. 1", ": Lv. 3", ": Lv. 5", ": Lv. 10"};
char *Moptasslt		[]  = {"• Aktifin Dulu Shiel BM Di Loby", " AK Sopmod D", "AK 47 FC Red", "AK Sopmod Medical", "AK Sopmod Sakura", "AUG A3", "AUG A3 EV", "AUG A3 Gold", "AUG A3 Chicano", "AUG A3 Beach", "AUG A3 Naga", "AUG A3 Comic", "AUG A3 Midnight3", "AUG A3 PBWC 2017", "AUG A3 CNPB T5", "AUG A3 Mech", "AUG A3 Lebaran 2017", "AUG A3 Infinitum", "AUG A3 Grafitty", "AUG A3 Tropical", "Pindad SS2 V5 Infinitum", "SC 2010 Lebaran 2017", "SC 2010 Infinitum", "SC 2010 Green", "SC 2010 X-Mas", "Water Gun", "MSBS", "MSBS Silver", "MSBS Gold", "M4 SR-16 Lv1", "M4 SR-16 Lv2", "M4 SR-16 Lv3", "M4 SR-16 FC", "Famas G2", "Famas G2 Comando", "Famas G2 Sniper", "Famas G2 M203", "Famas G2 Comando Gold", "Famas G2 Comando E-Sport", "Famas G2 Comando PBWC 2017"};
char *Moptsubma		[]  = {"• Aktifin Dulu Shiel BM Di Loby", "P90 Ext D", "P90 Ext Mech", "P90 Ext Infinitum", "P90 Ext Lebaran 2017", "P90 Ext CNPB T5", "P90 Ext Midnight3", "P90 Ext Green", "P90 Ext Naga", "OA 93 Grafitty", "OA 93 Infinitum", "OA 93 Mech", "OA 93 PBWC 2017", "OA 93 Midnight3", "OA 93 Tropical", "Kriss SV Tropical", "Kriss SV Grafitty", "Kriss SV Infinitum", "Kriss SV Lebaran 2017", "Kriss SV PBWC 2017", "Kriss SV Midnight3", "Kriss SV Green", "Kriss SV Comic", "Kriss SV Naga", "Kriss SV Beach", "Kriss SV Chicano", "Kriss SV E-Sport", "Kriss SV Love"};
char *Moptsnipe		[]  = {"• Aktifin Dulu Shiel BM Di Loby", "Rangemaster .338", "Rangemaster 7,62", "Rangemaster 7,62 STBY", "Barrett M82A1", "Barrett M82A1 Premium", "AS 50 Infinitum", "AS 50 Midnight3", "L115A1", "L115A1 SE", "L115A1 E-Sport", "Cheytac M200", "Cheytac M200 Tropical", "Cheytac M200 CNPB T5", "Cheytac M200 PBWC 2017", "Cheytac M200 Comic", "Cheytac M200 Naga", "Cheytac M200 Chicano", "PGM Hecate2 Beach", "Tactilite T2", "Tactilite T2 Grafitty", "Tactilite T2 Infinitum", "Tactilite T2 Lebaran 2017", "Tactilite T2 Mech", "Tactilite T2 PBWC 2017", "Tactilite T2 Green"};
char *Moptshotg		[]  = {"• Aktifin Dulu Shiel BM Di Loby", "Kel-Tec KSG-15", "Jackhammer", "SPASS 15 D", "SPASS 15 SI", "SPASS 15 MSC", "M1187 D", "M1187 SL", "M1187 Tropical", "M1187 Infinitum", "M1187 Lebaran 2017", "M1187 Mech", "M1187 PBWC 2017", "M1187 Green", "M1187 Comic", "M1187 Naga", "M1187 Beach", "M1187 Chicano", "Zombie Slayer Infinitum"};
char *Moptlaunc		[]	= {"• Aktifin Dulu Shiel BM Di Loby ", "RPG-7", ": M-79", ": HK-69"};

void RebuildMenu(LPDIRECT3DDEVICE9 pDevice)
{
	AddItem("[XMG Information]"	, Moptfolder	, &Feature.Folders.Info			, 2		, MENUFOLDER);
	if(Feature.Folders.Info)
	{
		AddText("Date", GetDate());
		AddText("Time", GetTime());
		//AddText("[<•>] Expired Cheat", output2);
		AddText("Menu", ": INSERT");
		AddText("EXIT", ": F12");
	}
	AddItem("[XMG EASY HACK]"		, Moptfolder	, &Feature.Folders.ESP	, 2		, MENUFOLDER);
	if(Feature.Folders.ESP)
	{
		AddItem("[F1]:ESP Bone"		, Moptonoff,  &Feature.ESP.Bone				, 2,  MENUCAT);
		AddItem("[F2]:ESP Name"		, Moptonoff,  &Feature.ESP.NameTag	        , 2,  MENUCAT);
		AddItem("ESP Line"			, Moptonoff,  &Feature.ESP.Line	            , 2,  MENUCAT);
		AddItem("ESP Healt"			, Moptonoff,  &Feature.ESP.Health	        , 2,  MENUCAT);
		AddItem("CrossHair"			, Moptonoff,  &Feature.Direct3D.CrossHair	, 2,  MENUCAT);
	}
	AddItem("[XMG AIM HACK]"		, Moptfolder	, &Feature.Folders.Direct3D		, 2		, MENUFOLDER);
	if(Feature.Folders.Direct3D)
	{
		AddItem("[HOME]:Aim Bullet"	        , Moptbullet, &Feature.AIM.Bullet			, 3,  MENUCAT);
		AddItem("[F3]AimReal"	            , Moptbullet, &Feature.AIM.Real			    , 3,  MENUCAT);
		AddItem("[F3]:No RecoiL"	        , Moptonoff,  &Feature.Weapon.NoRecoil		, 2,  MENUCAT);
		AddItem("[F4]:QuickChange"			, Moptonoff,  &Feature.Weapon.QuickChange	, 2,  MENUCAT);
	}
	AddItem("[XMG PLAYER HACK]"		, Moptfolder	, &Feature.Folders.Medium		, 2		, MENUFOLDER);
	if(Feature.Folders.Medium)
	{
		AddItem("Jump Hack"			    , Moptonoff,  &Feature.Player.JumpHight		, 2,  MENUCAT);
		AddText("Jump Hack Berfungsi Untuk Terbang /lompat tinggi", "");
		AddItem("[F5]:Auto Macro"		, Moptonoff,  &Feature.Weapon.AutoMacro		, 2,  MENUCAT);
		AddItem("Rapid Fire"			, Moptrapid,  &Feature.Weapon.RapidFire		, 5,  MENUCAT);
		AddItem("Accuracy"              , Moptonoff,  &Feature.Weapon.Accuracy      , 2,  MENUCAT);
		AddItem("No FallDamage"		    , Moptonoff,  &Feature.Player.NoFallDamage	, 2,  MENUCAT);
		AddItem("RebornChara"			, Moptonoff,  &Feature.Player.Reborn		, 2,  MENUCAT);
		AddItem("[END]:Suicide"		, Moptonoff,  &Feature.Player.AutoSuicide	    , 2,  MENUCAT);
		AddItem("Nick Hidden"		, Moptonoff,  &Feature.Player.HideNick		    , 2,  MENUCAT);
		AddItem("Anti Kick"		    , Moptonoff,  &Feature.Misc.AntiKick		    , 2,  MENUCAT);
		AddItem("Open Server Full"	    , Moptonoff,  &Feature.Misc.OpenSFull		, 2,  MENUCAT);
		AddItem("Unlock Pw Room"	    , Moptonoff,  &Feature.Misc.UnlockPW		, 2,  MENUCAT);
	}
		AddItem("[XMG HARD HACK]"			, Moptfolder	, &Feature.Folders.Hard			, 2		, MENUFOLDER);
	if(Feature.Folders.Hard)
	{
		AddItem("Auto Fire"			        , Moptonoff,  &Feature.AIM.AutoFire			, 2,  MENUCAT);
		AddItem("[F7]:Auto Killer"	 		, Moptbullet, &Feature.AIM.AutoKiller		, 3,  MENUCAT);
		AddItem("Net_Fire"			        , Moptonoff,  &Feature.AIM.NetFire			, 2,  MENUCAT);
		AddItem("Hokage Ke-4"		        , Mopttelept, &Feature.Player.Teleport		, 2,  MENUCAT);
		AddText("Hogake Ke-4 Berfungsi Untuk Memindahkan Diri Ke Tempat Musuh", " ");
		AddItem("Shield BM"			        , Moptreborn, &Feature.Player.Shield		, 2,  MENUCAT);
		AddText("Aktifkan Shiel BM Nya Di Lobby Jika Ingin Menggunakan Replace", "");
		AddItem("Assault"				, Moptasslt,  &Feature.Replace.Assault		, 40, MENUCAT);
		AddItem("S M G"			        , Moptsubma,  &Feature.Replace.Smg			, 28, MENUCAT);
		AddItem("A W P"				    , Moptsnipe,  &Feature.Replace.Sniper		, 26, MENUCAT);
		AddItem("S G"				    , Moptshotg,  &Feature.Replace.Shotgun		, 19, MENUCAT);
		AddItem("M-79"			        , Moptlaunc,  &Feature.Replace.Launcher		, 3,  MENUCAT);
		                                    AddText("Replace Weapon Pencet ", " [V]<<<");
	}
	AddItem("[XMG Menu AutoGB•]"		, Moptfolder	, &Feature.Folders.GBMode		, 2		, MENUFOLDER);
	if(Feature.Folders.GBMode)
	{
		AddItem("Auto Invite"			    , Moptonoff,  &Feature.Misc.AutoInvite		, 2,  MENUCAT);
		AddItem("Auto Ready"			    , Moptonoff,  &Feature.Misc.AutoReady		, 2,  MENUCAT);
		AddItem("Auto Bundir"			    , Moptonoff,  &Feature.Misc.AutoBundir		, 2,  MENUCAT);

	}
	
	{
		AddItem("Move Menu"			, Moptmd3d9,  &Feature.Direct3D.MoveD3D9	    , 2,  MENUCAT);
		//AddText("•>FAST EXIT", ": F12");
	}
	//AddText("Hard","Feature");
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