//CREATED BY SC0D3 Solusi Game No Di Indoneisa
char Header				[88]= "        WWW.SC0D3CIT.COM";
char *Moptfolder		[]	= {"Open", "Close"};
char *Moptonoff			[]	= {"OFF", "ON"};
char *MoptSantet		[]	= {"OFF", "H"};
char *Moptcharms		[]	= {"OFF", "Light", "Asus", "Phantom"};
char *Moptlines			[]  = {"OFF", "Bottom", "Center", "Top"};
char *Mopthpbar			[]  = {"OFF", "1", "2", "3"};
char *Mopttarget		[]	= {"Head", "Body"};
char *Mopthotkey		[]	= {"OFF", "L-CTRL", "L-Alt", "L-SHIFT", "CAPSLOCK", "TAB"};
char *Mopthkmode		[]	= {"Hold", "Toggle"};
char *Moptrapid			[]	= {"OFF", "Lv. 1", "Lv. 3", "Lv. 5", "Lv. 10"};
char *Moptbrust			[]	= {"OFF", "5", "10", "25", "50", "100"};
char *Moptshield		[]  = {"OFF", "Press R-CTRL"};
char *MoptMove          []  = {"OFF" ,"Press R-CTRL"};
char *Mopttelep			[]  = {"OFF", "Press H"};
char *MoptM             []  = {"OFF" ,":ON"};
char *Moptassault		[]  = {"OFF", "AK Sopmod D", "AK 47 FC Red", "AK Sopmod Medical", "AK Sopmod Sakura", "AUG A3", "AUG A3 EV", "AUG A3 Gold", "AUG A3 Chicano", "AUG A3 Beach", "AUG A3 Naga", "AUG A3 Comic", "AUG A3 Midnight3", "AUG A3 PBWC 2017", "AUG A3 CNPB T5", "AUG A3 Mech", "AUG A3 Lebaran 2017", "AUG A3 Infinitum", "AUG A3 Grafitty", "AUG A3 Tropical", "Pindad SS2 V5 Infinitum", "SC 2010 Lebaran 2017", "SC 2010 Infinitum", "SC 2010 Green", "SC 2010 X-Mas", "Water Gun", "MSBS", "MSBS Silver", "MSBS Gold", "M4 SR-16 Lv1", "M4 SR-16 Lv2", "M4 SR-16 Lv3", "M4 SR-16 FC", "Famas G2", "Famas G2 Comando", "Famas G2 Sniper", "Famas G2 M203", "Famas G2 Comando Gold", "Famas G2 Comando E-Sport", "Famas G2 Comando PBWC 2017"};
char *Moptsubmg			[]  = {"OFF", "P90 Ext D", "P90 Ext Mech", "P90 Ext Infinitum", "P90 Ext Lebaran 2017", "P90 Ext CNPB T5", "P90 Ext Midnight3", "P90 Ext Green", "P90 Ext Naga", "OA 93 Grafitty", "OA 93 Infinitum", "OA 93 Mech", "OA 93 PBWC 2017", "OA 93 Midnight3", "OA 93 Tropical", "Kriss SV Tropical", "Kriss SV Grafitty", "Kriss SV Infinitum", "Kriss SV Lebaran 2017", "Kriss SV PBWC 2017", "Kriss SV Midnight3", "Kriss SV Green", "Kriss SV Comic", "Kriss SV Naga", "Kriss SV Beach", "Kriss SV Chicano", "Kriss SV E-Sport", "Kriss SV Love"};
char *Moptsniper		[]  = {"OFF", "Rangemaster .338", "Rangemaster 7,62", "Rangemaster 7,62 STBY", "Barrett M82A1", "Barrett M82A1 Premium", "AS 50 Infinitum", "AS 50 Midnight3", "L115A1", "L115A1 SE", "L115A1 E-Sport", "Cheytac M200", "Cheytac M200 Tropical", "Cheytac M200 CNPB T5", "Cheytac M200 PBWC 2017", "Cheytac M200 Comic", "Cheytac M200 Naga", "Cheytac M200 Chicano", "PGM Hecate2 Beach", "Tactilite T2", "Tactilite T2 Grafitty", "Tactilite T2 Infinitum", "Tactilite T2 Lebaran 2017", "Tactilite T2 Mech", "Tactilite T2 PBWC 2017", "Tactilite T2 Green"};
char *Moptshotgun		[]  = {"OFF", "Kel-Tec KSG-15", "Jackhammer", "SPASS 15 D", "SPASS 15 SI", "SPASS 15 MSC", "M1187 D", "M1187 SL", "M1187 Tropical", "M1187 Infinitum", "M1187 Lebaran 2017", "M1187 Mech", "M1187 PBWC 2017", "M1187 Green", "M1187 Comic", "M1187 Naga", "M1187 Beach", "M1187 Chicano", "Zombie Slayer Infinitum"};
char *MoptRPG           []  = {"OFF" , "RPG 7"};
char *MoptRplc8		    []  = {"OFF","1","2","3","4","5","6","7","8","9"};
char *MoptRplc7		    []  = {"OFF", "Medical Kit", "Hallowen Medical Kit", "OporAyam Medical Kit"};
char *MoptM79           []  = {"OFF" ,"M 79"};

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
	DrawTransparentBox(mx-10, my-4, Mxofs+52, 20, Black, pDevice);
	DrawBorder(mx-10, my-4, Mxofs+52, 20, 1, Yellow, pDevice);
	DrawTransparentBox(mx-10, my+20, Mxofs+52,(Mmax*17)+1, Black, pDevice);
	DrawBorder(mx-10, my+20, Mxofs+52, (Mmax*17)+1, 1, Yellow, pDevice);
}
void MenuShow(float x, float y, LPDIRECT3DDEVICE9 pDevice)
{
	int i, val;
	DWORD color;
	SetRect( &rect, x+Mxofs/2, y, x+Mxofs /2 , y );
	if(!Mvisible) return;
	if (Header[0]) 
	{	
		pFont->DrawText(NULL,Header,-1,&rect,DT_NOCLIP | DT_CENTER, D3DCOLOR_ARGB(255, 0, 180, 255));
		y+=Mysize+5;
	}
	for (i=0; i<Mmax; i++) 
	{
		val=(D3MENU[i].var)?(*D3MENU[i].var):0;
		if (i==Mpos){
			color=D3DCOLOR_ARGB(255, RainbowR, RainbowG, RainbowB);
		}
		else if (D3MENU[i].typ==MENUFOLDER){
			color=D3DCOLOR_ARGB(255, 0, 180, 255);
		}
		else if (D3MENU[i].typ==MENUTEXT){
			color=D3DCOLOR_ARGB(255, 255, 125, 0);
		}
		else
		color=(val)?D3DCOLOR_ARGB(255, 0, 255, 0):D3DCOLOR_ARGB(255, 255, 255, 255);
		SetRect( &rect3, x, y, x , y );
		SetRect( &rect2, x+Mxofs, y, x+Mxofs , y );
		pFont->DrawText(NULL,D3MENU[i].txt,-1,&rect3, DT_NOCLIP,color);
		if (D3MENU[i].opt) {
			if (D3MENU[i].typ==MENUTEXT)
				pFont->DrawText(NULL,(char *)D3MENU[i].opt,-1,&rect2, DT_NOCLIP, color);
			else
				pFont->DrawText(NULL,(char *)D3MENU[i].opt[val],-1,&rect2, DT_NOCLIP, color);
		}
		y+=Mysize;
	}
	//MenuBox(mx,my,pDevice);
}

void MenuNav(void)
{
	if (IsKeyPressed(VK_INSERT, 0)&1)
	{
		Mvisible=(!Mvisible);
	}
	if(Visual.Direct3D.MoveD3D9)
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

char* GetDate()
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	char *logbuf = new char[ 256 ];
	sprintf(logbuf,"%d-%d-%d",st.wYear,st.wMonth,st.wDay);
	return logbuf;
}

char* GetTime()
{
	struct tm * current_tm;
	time_t current_time;
	time (&current_time);
	current_tm = localtime(&current_time);
	char *logbuf = new char[ 256 ];
	sprintf(logbuf, "%02d:%02d:%02d", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec );
	return logbuf;
}
char* FPS(int en)
{
	static int	 FPScounter = 0;
	static float FPSfLastTickCount = 0.0f;
	static float FPSfCurrentTickCount;
	static char  cfps[6] = "";

	if(!en)
	{
		FPSfCurrentTickCount = clock() * 0.001f;
		FPScounter++;

		if((FPSfCurrentTickCount - FPSfLastTickCount) > 1.0f)
		{
			FPSfLastTickCount = FPSfCurrentTickCount;
			sprintf(cfps,"%d",FPScounter);
			FPScounter = 0;
		}
	}
	return cfps;
}

void RebuildMenu(LPDIRECT3DDEVICE9 pDevice)
{
	//AddItem("Information"  , Moptfolder , &Folder.Information ,2, MENUFOLDER);
	//if(Folder.Information)
	{
		AddText("Date"				,GetDate());
		AddText("Time"				,GetTime());
		AddText("FPS"				,FPS(0));
	}
	AddItem("ESP Menu"			, Moptfolder	, &Folder.ESP			, 2		, MENUFOLDER);
	if(Folder.ESP)
	{
		AddItem("ESP Bone"			     	, Moptonoff,  &Visual.ESP.Bone					, 2,  MENUCAT);
		AddItem("ESP Head Dot"				, Moptonoff,  &Visual.ESP.Head					, 2,  MENUCAT);
		AddItem("ESP Line Enemy"			, Moptlines,  &Visual.ESP.Line					, 4,  MENUCAT);
		AddItem("ESP NameTag"				, Moptonoff,  &Visual.ESP.Name					, 2,  MENUCAT);
		AddItem("ESP Healthbar"			    , Mopthpbar,  &Visual.ESP.Health				, 4,  MENUCAT);
		AddItem("ESP Ping Server"			, Moptonoff,  &Visual.ESP.Ping					, 2,  MENUCAT);
		AddItem("ESP Kill Death"			, Moptonoff,  &Visual.ESP.KillDeath				, 2,  MENUCAT);
	}
	AddItem("Assist Menu"		, Moptfolder	, &Folder.Assist		, 2		, MENUFOLDER);
	if(Folder.Assist)
	{
		AddItem("Aim Vischek"		, Moptonoff,  &GameHack.Assist.Mode					, 2,  MENUCAT);
		AddItem("Target Lock"			, Mopttarget, &GameHack.Assist.Target				, 2,  MENUCAT);
		AddItem("Aim Real"	, Moptonoff,  &GameHack.Assist.AimReal				, 2,  MENUCAT);
		AddItem("Auto HeadShot"		, Moptonoff,  &GameHack.Assist.Hs					, 2,  MENUCAT);
		AddItem("Hotkey Mode"			, Mopthkmode, &GameHack.Assist.HotkeyMode			, 2,  MENUCAT);
		AddItem("Assist Hotkey"		, Mopthotkey, &GameHack.Assist.Hotkey				, 6,  MENUCAT);
	}
	AddItem("Server Menu"			, Moptfolder	, &Folder.Misc		, 2		, MENUFOLDER);
	if(Folder.Misc)
	{
		AddItem("Bypass Server"		, Moptonoff,  &Other.Misc.AntiSF					, 2,  MENUCAT);
		AddItem("Unlock PW Room"		, Moptonoff,  &Other.Misc.UnlockPW					, 2,  MENUCAT);
		AddItem("Anti Kick RM"			, Moptonoff,  &Other.Misc.AntiKick					, 2,  MENUCAT);
	}
	AddItem("Weapon Menu"		, Moptfolder	, &Folder.Weapon		, 2		, MENUFOLDER);
	if(Folder.Weapon)
	{
	    AddItem("Quick Change"			, Moptonoff,  &GameHack.Weapon.QuickChange			, 2,  MENUCAT);
		AddItem("No Recoil(F3)"		, Moptonoff,  &GameHack.Weapon.NoRecoil				, 2,  MENUCAT);
		AddItem("Accuracy"				, Moptonoff,  &GameHack.Weapon.Accuracy				, 2,  MENUCAT);
		AddItem("Fast Reload"			, Moptonoff,  &GameHack.Weapon.FastReload			, 2,  MENUCAT);
		AddItem("Full Sub Ammo"		, Moptonoff,  &GameHack.Weapon.FullSubAmmo			, 2,  MENUCAT);
		AddItem("Macro Weapon"			, Moptonoff,  &GameHack.Weapon.AutoMacro			, 2,  MENUCAT);
		AddItem("Set Brust"			, Moptbrust,  &GameHack.Weapon.SetBrust				, 6,  MENUCAT);
		AddItem("Auto Shot"			, Moptonoff,  &GameHack.Assist.AutoShot				, 2,  MENUCAT);
	}
	AddItem("Player Menu"		, Moptfolder	, &Folder.Player		, 2		, MENUFOLDER);
	if(Folder.Player)
	{
		AddItem("Jump Hack"			, Moptonoff,  &GameHack.Player.JumpHack			, 2,  MENUCAT);
		AddItem("Fall Damage"			, Moptonoff,  &GameHack.Player.FallDamage			, 2,  MENUCAT);
		AddItem("Hide Nick"			, Moptonoff,  &GameHack.Player.HideNick				, 2,  MENUCAT);
		AddItem("Fake Rank"			, Moptonoff,  &GameHack.Player.SkillUp				, 2,  MENUCAT);
		AddItem("DC All Player"			, Moptonoff,  &GameHack.Player.EnemyDC			, 2,  MENUCAT);
		AddItem("Reborn(R-CTRL)"		, Moptonoff,  &GameHack.Player.Reborn				, 2,  MENUCAT);
		AddItem("Suicide(END)"			, Moptonoff,  &GameHack.Player.Suicide				, 2,  MENUCAT);
	}
	AddItem("Hard Menu"		, Moptfolder	, &Folder.Brutal		, 2		, MENUFOLDER);
	if(Folder.Brutal)
	{
		AddItem("Bullet Tele"			, MoptM,  &GameHack.Brutal.BulletTele			, 2,  MENUCAT);
		AddText("DIWAJBKAN MEMEGANG SENJATA","");
		AddText("ATAU AKAN DC","");
		AddItem("Auto Fire"			, Moptonoff,  &GameHack.Assist.AutoFire				, 2,  MENUCAT);
		AddItem("Teleport"			, Mopttelep,  &GameHack.Brutal.Teleport				, 2,  MENUCAT);
		AddItem("Santet Killer"			, MoptSantet,  &GameHack.Weapon.Santet			, 2,  MENUCAT);
		AddText("DIWAJBKAN MEMEGANG PISO","");
		AddText("ATAU AKAN DC","");
		AddItem("Rapid Fire"			, Moptrapid,  &GameHack.Weapon.RapidFire			, 5,  MENUCAT);
	}
   AddItem("Replace Menu"		, Moptfolder	, &Folder.Replace		, 2		, MENUFOLDER);
	if(Folder.Replace)
	{
		AddItem("Shield BM"			, Moptshield, &GameHack.Brutal.ShieldBomb			, 2,  MENUCAT);
		AddText("ON-KAN SBLM PLAY MATCH","");
		AddItem("Replace. Assault"			, Moptassault,&Other.Replace.ReplaceAssault			, 40, MENUCAT);
		AddItem("Replace. SubMachine"		, Moptsubmg,  &Other.Replace.ReplaceSmg				, 28, MENUCAT);
		AddItem("Replace. Sniper"			, Moptsniper, &Other.Replace.ReplaceSniper			, 26, MENUCAT);
		AddItem("Replace. Shotgun"			, Moptshotgun,&Other.Replace.ReplaceShotgun			, 19, MENUCAT);
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