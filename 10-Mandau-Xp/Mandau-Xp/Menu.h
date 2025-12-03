//Bagus Tuyul
char Header				[88]= "";
char *Moptfolder		[]	= {">", "Close"};
char *Moptonoff			[]	= {">", ":ON"};
char *Moptcharms		[]	= {">", "Light", "Asus", "Phantom"};
char *Moptlines			[]  = {">", "Bottom", "Center", "Top"};
char *Mopthpbar			[]  = {">", "1", "2", "3"};
char *Mopttarget		[]	= {"Head", "Body"};
char *Mopthotkey		[]	= {">", "L-CTRL", "L-Alt", "L-SHIFT", "CAPSLOCK", "TAB"};
char *Mopthkmode		[]	= {"Hold", "Toggle"};
char *Moptrapid			[]	= {">", "Lv. 1", "Lv. 3", "Lv. 5", "Lv. 10"};
char *Moptbrust			[]	= {">", "5", "10", "25", "50", "100"};
char *Moptshield		[]  = {">", "F6"};
char *MoptMove          []  = {">" ,":Press R-CTRL"};
char *Mopttelep			[]  = {">", "Press H"};
char *MoptM             []  = {">" ,":ON"};
char *Moptassault		[]  = {">", "AK Sopmod D", "AK 47 FC Red", "AK Sopmod Medical", "AK Sopmod Sakura", "AUG A3", "AUG A3 EV", "AUG A3 Gold", "AUG A3 Chicano", "AUG A3 Beach", "AUG A3 Naga", "AUG A3 Comic", "AUG A3 Midnight3", "AUG A3 PBWC 2017", "AUG A3 CNPB T5", "AUG A3 Mech", "AUG A3 Lebaran 2017", "AUG A3 Infinitum", "AUG A3 Grafitty", "AUG A3 Tropical", "Pindad SS2 V5 Infinitum", "SC 2010 Lebaran 2017", "SC 2010 Infinitum", "SC 2010 Green", "SC 2010 X-Mas", "Water Gun", "MSBS", "MSBS Silver", "MSBS Gold", "M4 SR-16 Lv1", "M4 SR-16 Lv2", "M4 SR-16 Lv3", "M4 SR-16 FC", "Famas G2", "Famas G2 Comando", "Famas G2 Sniper", "Famas G2 M203", "Famas G2 Comando Gold", "Famas G2 Comando E-Sport", "Famas G2 Comando PBWC 2017"};
char *Moptsubmg			[]  = {">", "P90 Ext D", "P90 Ext Mech", "P90 Ext Infinitum", "P90 Ext Lebaran 2017", "P90 Ext CNPB T5", "P90 Ext Midnight3", "P90 Ext Green", "P90 Ext Naga", "OA 93 Grafitty", "OA 93 Infinitum", "OA 93 Mech", "OA 93 PBWC 2017", "OA 93 Midnight3", "OA 93 Tropical", "Kriss SV Tropical", "Kriss SV Grafitty", "Kriss SV Infinitum", "Kriss SV Lebaran 2017", "Kriss SV PBWC 2017", "Kriss SV Midnight3", "Kriss SV Green", "Kriss SV Comic", "Kriss SV Naga", "Kriss SV Beach", "Kriss SV Chicano", "Kriss SV E-Sport", "Kriss SV Love"};
char *Moptsniper		[]  = {">", "Rangemaster .338", "Rangemaster 7,62", "Rangemaster 7,62 STBY", "Barrett M82A1", "Barrett M82A1 Premium", "AS 50 Infinitum", "AS 50 Midnight3", "L115A1", "L115A1 SE", "L115A1 E-Sport", "Cheytac M200", "Cheytac M200 Tropical", "Cheytac M200 CNPB T5", "Cheytac M200 PBWC 2017", "Cheytac M200 Comic", "Cheytac M200 Naga", "Cheytac M200 Chicano", "PGM Hecate2 Beach", "Tactilite T2", "Tactilite T2 Grafitty", "Tactilite T2 Infinitum", "Tactilite T2 Lebaran 2017", "Tactilite T2 Mech", "Tactilite T2 PBWC 2017", "Tactilite T2 Green"};
char *Moptshotgun		[]  = {">", "Kel-Tec KSG-15", "Jackhammer", "SPASS 15 D", "SPASS 15 SI", "SPASS 15 MSC", "M1187 D", "M1187 SL", "M1187 Tropical", "M1187 Infinitum", "M1187 Lebaran 2017", "M1187 Mech", "M1187 PBWC 2017", "M1187 Green", "M1187 Comic", "M1187 Naga", "M1187 Beach", "M1187 Chicano", "Zombie Slayer Infinitum"};
char *MoptRPG           []  = {">" , "RPG 7"};
char *MoptM79           []  = {">" ,"M 79"};

void AddItem(char *txt, char **opt, int *var, int maxvalue, int typ)
{
	D3MENU[Mmax].typ=typ;
	D3MENU[Mmax].txt=txt;
	D3MENU[Mmax].opt=opt;
	D3MENU[Mmax].var=var;
	D3MENU[Mmax].maxvalue=maxvalue;
	Mmax++;
}

void AddText(char *txt, char *opt)
{
	D3MENU[Mmax].typ=MENUTEXT;
	D3MENU[Mmax].txt=txt;
	D3MENU[Mmax].opt=(char **)opt;
	D3MENU[Mmax].var=0;
	D3MENU[Mmax].maxvalue=0;
	Mmax++;
}

void MenuBox(float x, float y, LPDIRECT3DDEVICE9 pDevice)
{
	DrawTransparentBox(mx-5, my+20, 225,(Mmax*17)+1, MCOLOR_BOX, pDevice);
	DrawTransparentBox(mx-5, my-2, 225, 18, MCOLOR_BOX, pDevice);
	DrawTransparentBox(mx-5, 55+(Mmax*17), 225, 18, MCOLOR_BOX, pDevice);
	DrawBorder(mx-5, my-2, 225, 18, 1, MCOLOR_BORDER, pDevice);
	DrawBorder(mx-5, my+20, 225, (Mmax*17)+1, 1, MCOLOR_BORDER, pDevice);
	DrawBorder(mx-5, 55+(Mmax*17), 225, 18, 1, MCOLOR_BORDER, pDevice);
}
void DrawTextR(int x,int y,DWORD color,char *text)
{
    RECT rect, rect1, rect2, rect3, rect4, rect5;
    SetRect( &rect, x, y, x, y );
	SetRect( &rect1, x-1, y, x-1, y );
    SetRect( &rect2, x, y, x, y );
	SetRect( &rect3, x, y+1, x, y+1 );
    SetRect( &rect4, x, y, x, y );
	SetRect( &rect5, x - 0.1, y + 0.2, x - 0.1, y + 0. );
	pFont->DrawTextA(NULL,text,-1,&rect5, DT_LEFT|DT_NOCLIP, color );
    pFont->DrawTextA(NULL,text,-1,&rect,  DT_LEFT|DT_WORDBREAK, Black );
	pFont->DrawTextA(NULL,text,-1,&rect1, DT_LEFT|DT_WORDBREAK, Black );
	pFont->DrawTextA(NULL,text,-1,&rect2, DT_LEFT|DT_WORDBREAK, Black );
	pFont->DrawTextA(NULL,text,-1,&rect3, DT_LEFT|DT_WORDBREAK, Black );
	pFont->DrawTextA(NULL,text,-1,&rect4, DT_LEFT|DT_WORDBREAK, Black );
}

void DrawTextL(int x,int y,DWORD color,char *text)
{
	RECT rect, rect1, rect2, rect3, rect4, rect5;
    SetRect( &rect, x, y, x, y );
	SetRect( &rect1, x-1, y, x-1, y );
    SetRect( &rect2, x, y, x, y );
	SetRect( &rect3, x, y+1, x, y+1 );
    SetRect( &rect4, x, y, x, y );
	SetRect( &rect5, x - 0.1, y + 0.2, x - 0.1, y + 0. );
	pFont->DrawTextA(NULL,text,-1,&rect5, DT_RIGHT|DT_NOCLIP, color );
    pFont->DrawTextA(NULL,text,-1,&rect,  DT_RIGHT|DT_WORDBREAK, Black );
	pFont->DrawTextA(NULL,text,-1,&rect1, DT_RIGHT|DT_WORDBREAK, Black );
	pFont->DrawTextA(NULL,text,-1,&rect2, DT_RIGHT|DT_WORDBREAK, Black );
	pFont->DrawTextA(NULL,text,-1,&rect3, DT_RIGHT|DT_WORDBREAK, Black );
	pFont->DrawTextA(NULL,text,-1,&rect4, DT_RIGHT|DT_WORDBREAK, Black );
}
void MenuShow(float x, float y, LPDIRECT3DDEVICE9 pDevice)
{
	int i, val;
	DWORD color;
	DWORD texty;
	char text[100];
	if (!Mvisible) return;
	//DrawMenu12(x-5, y-5, 200/*<wigth*/, 23/*<heigt*/, 3,Hijau, Hijau, pDevice);
if (Header) 
	{
		//DrawMenu12(x-5, y-5, 200/*<wigth*/, 23/*<heigt*/, 3,Hijau, Hijau, pDevice);// Warna dan lebar tinggi line
		pFont->DrawText(NULL,Header,-1,&rect2,DT_NOCLIP | DT_CENTER, D3DCOLOR_ARGB(255, RainbowR, RainbowG, RainbowB));
		y+=Mysize;
	}
	for (i=0; i<Mmax; i++) 
	{
		//DrawMenu12(x-5, y-5, 200/*<wigth*/, 25/*<heigt*/, 3,ABUABU /*Warna BG*/, Hijau, pDevice);
		val=(D3MENU[i].var)?(*D3MENU[i].var):0;
		sprintf(text, "%s", D3MENU[i].txt);
		if (i==Mpos){
			color=Red;
			texty=Red;

			sprintf(text, "~> %s", D3MENU[i].txt);
		}
		else if (D3MENU[i].typ==MENUFOLDER){
			color=Yellow;
			texty=Yellow;
		}
		else if (D3MENU[i].typ==MENUTEXT){
			color=Green;
			texty=Green;
		}
		else{
			color=(val)?SkyBlue:White;
			texty=(val)?White:White;
		}
		if (D3MENU[i].opt)
		{
			if (D3MENU[i].typ==MENUITEM){
				DrawTextL(x+3, y, texty,text);
				y = y + 2;
			}else{
				DrawTextL(x+3, y, texty,text);
			}
		}
		if (D3MENU[i].opt) {
			if (D3MENU[i].typ==MENUTEXT)
				DrawTextR((x+Mxofs), y, color,(char *)D3MENU[i].opt);
			else
				DrawTextR((x+Mxofs), y, color,(char *)D3MENU[i].opt[val]);
		}
		y+=Mysize;
	}
}
void MenuNav(void)
{
	if (IsKeyPressed(VK_INSERT, 0)&1)
	{
		Mvisible=(!Mvisible);
	}
		if(Visual.Direct3D.MoveD3D9 && GetAsyncKeyState(VK_LCONTROL))
		{
		POINT Mpos;
		GetCursorPos(&Mpos);
		ScreenToClient(GetForegroundWindow(), &Mpos);
		mx = Mpos.x;
		my = Mpos.y+2;
	}
	if (!Mvisible) return;
	if (IsKeyPressed(VK_UP, 0)&1) {
		do {
			Mpos--;
			if (Mpos<0)  Mpos=Mmax-1;
			/*playsoundmem*/((LPCSTR)MOVE);
		} 
		while (D3MENU[Mpos].typ==MENUTEXT);	
	}else if (IsKeyPressed(VK_DOWN, 0)&1) {
		do {
			Mpos++;
			if (Mpos==Mmax) Mpos=0;
			/*playsoundmem*/((LPCSTR)MOVE);
		} while (D3MENU[Mpos].typ==MENUTEXT);		
	} else if (D3MENU[Mpos].var) {
		int dir=0;
		if ((IsKeyPressed(VK_LEFT, 0)&1) && *D3MENU[Mpos].var > 0) dir=-1, /*playsoundmem*/((LPCSTR)SWITCH);
		if ((IsKeyPressed(VK_RIGHT, 0)&1) && *D3MENU[Mpos].var < (D3MENU[Mpos].maxvalue-1)) dir=1, /*playsoundmem*/((LPCSTR)SWITCH);
		if (dir) {
			*D3MENU[Mpos].var += dir;
			if (D3MENU[Mpos].typ==MENUFOLDER) Mmax=0;
			if (D3MENU[Mpos].typ==MENUCAT) Mmax=0;  
		}
	}
}

void RebuildMenu(LPDIRECT3DDEVICE9 pDevice)
{
	//AddText("Simple","Mandau-Xp");
	AddItem("D3D Menu"			, Moptfolder	, &Folder.Direct3D		, 2		, MENUFOLDER);
	if(Folder.Direct3D)
	{
		AddItem("WallHack"				, Moptonoff,  &Visual.Direct3D.WallHack			, 2,  MENUCAT);
		AddItem("Charms"				, Moptcharms, &Visual.Direct3D.Charms			, 4,  MENUCAT);
		AddItem("No Smoke"				, Moptonoff,  &Visual.Direct3D.NoSmoke			, 2,  MENUCAT);
		AddItem("No Fog"				, Moptonoff,  &Visual.Direct3D.NoFog			, 2,  MENUCAT);
		AddItem("CrossHair"				, Moptonoff,  &Visual.Direct3D.CrossHair		, 2,  MENUCAT);
	}
	AddItem("ESP Menu"			, Moptfolder	, &Folder.ESP			, 2		, MENUFOLDER);
	if(Folder.ESP)
	{
		AddItem("Bone"				, Moptonoff,  &Visual.ESP.Bone					, 2,  MENUCAT);
		AddItem("Head"				, Moptonoff,  &Visual.ESP.Head					, 2,  MENUCAT);
		AddItem("Line Enemy"			, Moptlines,  &Visual.ESP.Line					, 4,  MENUCAT);
		AddItem("NameTag"				, Moptonoff,  &Visual.ESP.Name					, 2,  MENUCAT);
		AddItem("Healthbar"			, Mopthpbar,  &Visual.ESP.Health				, 4,  MENUCAT);
		AddItem("Ping Server"			, Moptonoff,  &Visual.ESP.Ping					, 2,  MENUCAT);
		AddItem("Kill Death"			, Moptonoff,  &Visual.ESP.KillDeath				, 2,  MENUCAT);
	}
	AddItem("Assist Menu"		, Moptfolder	, &Folder.Assist		, 2		, MENUFOLDER);
	if(Folder.Assist)
	{
		AddItem("Vicible(HOME)"		, Moptonoff,  &GameHack.Assist.Mode					, 2,  MENUCAT);
		AddItem("Target Lock"			, Mopttarget, &GameHack.Assist.Target				, 2,  MENUCAT);
		AddItem("Assist Hotkey"		, Mopthotkey, &GameHack.Assist.Hotkey				, 6,  MENUCAT);
		AddItem("Hotkey Mode"			, Mopthkmode, &GameHack.Assist.HotkeyMode			, 2,  MENUCAT);
		AddItem("Aim Real(CAPSLOCK)"	, Moptonoff,  &GameHack.Assist.AimReal				, 2,  MENUCAT);
		AddItem("Auto Shot"			, Moptonoff,  &GameHack.Assist.AutoShot				, 2,  MENUCAT);
		AddItem("Auto Fire"			, Moptonoff,  &GameHack.Assist.AutoFire				, 2,  MENUCAT);
	}
	AddItem("Misc Menu"			, Moptfolder	, &Folder.Misc		, 2		, MENUFOLDER);
	if(Folder.Misc)
	{
		AddItem("Bypass Server"		, Moptonoff,  &Other.Misc.AntiSF					, 2,  MENUCAT);
		AddItem("Unlock PW Room"		, Moptonoff,  &Other.Misc.UnlockPW					, 2,  MENUCAT);
		AddItem("Auto Invite"			, Moptonoff,  &Other.Misc.AutoInvite				, 2,  MENUCAT);
		AddText("Gunakan Saat Di Room", "");
		AddItem("Anti Kick RM"			, Moptonoff,  &Other.Misc.AntiKick					, 2,  MENUCAT);
		AddItem("Auto Ready"			, Moptonoff,  &Other.GBMode.AutoReady				, 2,  MENUCAT);
		AddItem("Auto Bundir"			, Moptonoff,  &Other.GBMode.AutoBundir				, 2,  MENUCAT);
		AddText("Resolusi 1024x768", "");
	}
	AddItem("Weapon Menu"		, Moptfolder	, &Folder.Weapon		, 2		, MENUFOLDER);
	if(Folder.Weapon)
	{
	    AddItem("Quick Change"			, Moptonoff,  &GameHack.Weapon.QuickChange			, 2,  MENUCAT);
		AddItem("No Recoil(F3)"		, Moptonoff,  &GameHack.Weapon.NoRecoil				, 2,  MENUCAT);
		AddItem("Accuracy"				, Moptonoff,  &GameHack.Weapon.Accuracy				, 2,  MENUCAT);
		AddItem("Fast Reload"			, Moptonoff,  &GameHack.Weapon.FastReload			, 2,  MENUCAT);
		AddItem("Full Sub Ammo"		, Moptonoff,  &GameHack.Weapon.FullSubAmmo			, 2,  MENUCAT);
		AddItem("Auto Macro"			, Moptonoff,  &GameHack.Weapon.AutoMacro			, 2,  MENUCAT);
		AddItem("Set Brust"			, Moptbrust,  &GameHack.Weapon.SetBrust				, 6,  MENUCAT);
	}
	AddItem("Player Menu"		, Moptfolder	, &Folder.Player		, 2		, MENUFOLDER);
	if(Folder.Player)
	{
		/*AddItem("Jump Hack"			, Moptonoff,  &GameHack.Player.JumpHack			, 2,  MENUCAT);
		AddText("Jangan Lompat Tinggi Tinggi Nanti Akan DC","");*/
		AddItem("Fall Damage"			, Moptonoff,  &GameHack.Player.FallDamage			, 2,  MENUCAT);
		AddItem("Hide Nick"			, Moptonoff,  &GameHack.Player.HideNick				, 2,  MENUCAT);
		AddItem("Fake Rank"			, Moptonoff,  &GameHack.Player.SkillUp				, 2,  MENUCAT);
		//AddItem("Wall Bug"				, Moptonoff,  &GameHack.Player.WallBug				, 2,  MENUCAT);
		//AddItem("Bug Unyu"				, Moptonoff,  &GameHack.Player.BugUnyu				, 2,  MENUCAT);
		AddItem("Suicide(END)"			, Moptonoff,  &GameHack.Player.Suicide				, 2,  MENUCAT);
	}
	AddItem("Brutal Menu"		, Moptfolder	, &Folder.Brutal		, 2		, MENUFOLDER);
	if(Folder.Brutal)
	{
		AddItem("Reborn"		, Moptonoff,  &GameHack.Player.Reborn				, 2,  MENUCAT);
		AddItem("Hokage Ke 4"			, Mopttelep,  &GameHack.Brutal.Teleport				, 2,  MENUCAT);
		AddText("Gunakan Shield Bomb " ,"");
		AddItem("Rapid Fire"			, Moptrapid,  &GameHack.Weapon.RapidFire			, 5,  MENUCAT);
		AddItem("Auto Killer"			, Moptonoff,  &GameHack.Brutal.AutoKiller			, 2,  MENUCAT);
	}
   AddItem("Replace Menu"		, Moptfolder	, &Folder.Replace		, 2		, MENUFOLDER);
	if(Folder.Replace)
	{
		
		AddItem("Wallshot Replace"			, MoptM,  &GameHack.Brutal.BulletTele			, 2,  MENUCAT);
		AddItem("Assault"			, Moptassault,&Other.Replace.ReplaceAssault			, 40, MENUCAT);
		AddItem("SubMachine"		, Moptsubmg,  &Other.Replace.ReplaceSmg				, 28, MENUCAT);
		AddItem("Sniper"			, Moptsniper, &Other.Replace.ReplaceSniper			, 26, MENUCAT);
		AddItem("Shotgun"			, Moptshotgun,&Other.Replace.ReplaceShotgun			, 19, MENUCAT);
		AddText("Onkan Shield diLoby jika main DeathMarch","");
		AddItem("Shield"			, Moptshield, &GameHack.Brutal.ShieldBomb			, 2,  MENUCAT);
		AddText("Tekan V Untuk Ganti Senjata", "");
	}
	 AddItem("Launcher Menu"		, Moptfolder	, &Folder.Launcher		, 2		, MENUFOLDER);
	if(Folder.Launcher)
	{
		AddItem("Launcher RPG 7"			, MoptRPG,&Other.Replace.RPG			, 40, MENUCAT);
		AddText("Gunakan Shield Agar Tidak DC","");
		AddItem("Launcher M 79"			    , MoptM79,&Other.Replace.M79			, 40, MENUCAT);
	}
	AddItem("Other Menu"		, Moptfolder	, &Folder.Other		, 2		, MENUFOLDER);
	if(Folder.Other)
	{
		AddItem("Atur Letak Menu"				, MoptMove,  &Visual.Direct3D.MoveD3D9		, 2,  MENUCAT);
	}
}

void DrawMenuD3D(LPDIRECT3DDEVICE9 pDevice)
{
	if (DrawFont == 1) 
	{
		D3DXCreateFontA(pDevice, 15, 0, FW_MEDIUM, 1, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
		D3DXCreateFontA(pDevice, 15, 0, FW_MEDIUM, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &g_pFont);
		D3DXCreateLine(pDevice,&g_pLine);
		DrawFont = 0;
	}
	if (Drawing == 0)
	{
		if(Mmax==0) 
		RebuildMenu(pDevice);
		MenuShow(mx,my,pDevice);
		MenuNav();
	}
}