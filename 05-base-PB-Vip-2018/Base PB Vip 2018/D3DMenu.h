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
#include "MenuClass.h"
/*------------------------------------------- Declaration Date ------------------------------------------------------*/
char* GetDate()
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	char *logbuf = new char[ 256 ];
	sprintf(logbuf,"%d-%d-%d" ,st.wDay,st.wMonth,st.wYear);
	return logbuf;
}

/*------------------------------------------- Declaration Time ------------------------------------------------------*/
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
typedef struct
{
	int Visual;
	int Esp;
	int Assist;
	int Player;
	int Weapon;
	int Replace;
	int Hard;
	int Special;
	int Brutal;
}tFolders;

tFolders	cFolders;

static char* MoptRapidFire			[]		= {"(OFF)", "Lvl. 10", "Lvl. 30", "Lvl. 50", "Lvl. 100"};
static char* MoptBugWeapon			[]		= {"(OFF)", "1", "2", "3", "4", "5"};
static char* MoptBurst				[]		= {"(OFF)", "5", "10", "25", "50", "100"};
static char* MoptAbuse				[]		= {"(OFF)", "Press TAB"};
static char* MoptShield				[]		= {"(OFF)", "Press HOME"};/* *To Next Stage */
static char* MoptTele				[]		= {"(OFF)", "Press F3"};
static char *Moptfolder				[]		= {"[OPEN]", "[CLOSE]"};
static char *Moptonoff				[]		= {"(OFF)", "(ON)"};
static char *MoptCross				[]		= {"(OFF)", "[+]", "[•]"};
static char *MoptonUnyu				[]		= {"(OFF)", "V1", "V2"};
static char *MoptReborn				[]		= {"(OFF)", "Press C* (ON)"};
static char *MoptKick   			[]		= {"Press DELETE* Off", "(ON)"};
static char *MoptCharms				[]		= {"(OFF)", "Light", "Ghost", "Phantom"};
static char *MoptRank				[]		= {"(OFF)", "Blank", "GM"};
static char *MoptAssistMode			[]		= {"(OFF)","Lock","Bullet"};
static char *MoptAutoKiller			[]		= {"(OFF)","Bullet", "Melee"};
static char *MoptPlantDefuse		[]		= {"(OFF)","Plant", "Defuse"};
static char *MoptAssistTarget		[]		= {"Head", "Body"};
static char *MoptAssistHotkeyMode	[]		= {"Hold", "Toggle"};
static char *MoptSniper				[]		= {"(OFF)","Bareta", "CheyTac M200", "L115A1","SSG-69 S"};
static char *MoptAssault			[]		= {"(OFF)","AUG A3", "AK 47 SOSMOD", "G36C","F2000 SL"};
static char *MoptSMG				[]		= {"(OFF)","Kriss S. V", "P90 M.C", "MP7","Spectre"};
static char *MoptMachineGun			[]		= {"(OFF)","MK 46", "MK 46 Ext"};
static char *MoptShotgun			[]		= {"(OFF)","SPAS-15 Sl", "870MCS Sl", "M1887","870MCS"};
static char *MoptAssistHotkey		[]		= {"(OFF)", "Left Control", "Left Alt", "Left SHIFT", "Caps Lock", "Tab"};
static char *MoptSpeed				[]		= {"(OFF)", "2x", "4x", "6x", "8x", "10x", "12x"};
static char *MoptResetWeapon		[]		= {"(OFF)", "Limit", "Ammo"/*, "Bypass"*/};
static char *MoptVote				[]		= {"xxxxxxxxxxxxxxxx", 
											   "xxxxxxxxxxxxxxxx", 
											   "xxxxxxxxxxxxxxxx", 
											   "xxxxxxxxxxxxxxxx", 
											   "xxxxxxxxxxxxxxxx", 
											   "xxxxxxxxxxxxxxxx", 
											   "xxxxxxxxxxxxxxxx", 
											   "xxxxxxxxxxxxxxxx", 
											   "xxxxxxxxxxxxxxxx", 
											   "xxxxxxxxxxxxxxxx", 
											   "xxxxxxxxxxxxxxxx", 
											   "xxxxxxxxxxxxxxxx", 
											   "xxxxxxxxxxxxxxxx", 
											   "xxxxxxxxxxxxxxxx",
											   "xxxxxxxxxxxxxxxx",
											   "xxxxxxxxxxxxxxxx",
											   "xxxxxxxxxxxxxxxx",
											   "xxxxxxxxxxxxxxxx",
											   "xxxxxxxxxxxxxxxx",
											   "xxxxxxxxxxxxxxxx",
											   "xxxxxxxxxxxxxxxx",
											   "xxxxxxxxxxxxxxxx",
											   "xxxxxxxxxxxxxxxx",
											   "xxxxxxxxxxxxxxxx",
											   "xxxxxxxxxxxxxxxx",
											   "xxxxxxxxxxxxxxxx" };
static char *MoptRplc				[]		= {"None", "FAMAS G2 Comman do E-Sport", "AK-47 F.C Red", "AK SOPMOD D", "AUG A3 EV", "M4 SR-16 Lv1", "M4 SR-16 Lv2",
											   "M4 SR-16 Lv3", "M4 SR-16 F.C", "AUG A3 E-Sport", "AK Sopmod Medical", "AK SOPMOD Sakura", "AUG A3 CoupleBreaker", "AUG A3 PBGC 2016", "AUG A3 PBGC 2016", "Watergun 2016", "AUG A3 Beast", "AUG A3 Sky", "AUG A3 Silencer", 
											   "AUG A3 Sakura", "AUG A3 Serpent", "AUG A3 GRS", "SC 2010 X-MAS", "AUG A3 Lebaran", "AUG A3 Aruna", "AK-47 OLD SPEC", "FAMAS G2", "FAMAS G2 Commando", "FAMAS G2 Siniper", "FAMAS G2 M203", "FAMAS G2 Comman do G"};
static char *MoptRplc2				[]		= {"None", "Kriss S.V E-Sport", "P90 ext D", "Dual Mini-Uzi", "P90 M.C. D", "Dual Micro Mini Uzi Silencer", "M4 CQB-R Lv1", 
											   "M4 CQB-R Lv2", "M4 CQB-R Lv3", "Kriss S.V.", "P90 Ext Mech", "OA-93", "Kriss CoupleBreaker"};
static char *MoptRplc3				[]		= {"None", "Barrett M82A1", "CheyTac M200 Rusia", "Rangemaster 7,62 STBY", "L115A1 E-Sport", 
											   "M4 SRP Lv3", "Winchester M70", "Rangemaster .338", "Rangemaster 7,62", "L115A1 SE", "Tacktitle"};
static char *MoptRplc4				[]		= {"None", "M1887 SL", "SPAS-15 SI. D", "Jackhammer", "Kel-Tec KSG-15", "SPAS-15 MSC", "Zombie Slayer"};
static char *MoptRplc5				[]		= {"None", "Colt Python D", "R.B SS8M + S 454", "IMI Uzi 9 mm", "C. Python", "R.B SS2M 454", "R.B SS5M 454", "R.B SS8M 454"};
static char *MoptRplc6				[]		= {"None", "MK.46 Ext", "MK.46 S1.", "RPD", "L86 LSW"};


void RebuildMenu(LPDIRECT3DDEVICE9 pDevice)
{
	//AddText(" PointBlank\@2017","");
	AddText("Tanggal Dunia CHEAT "			,GetDate());
	AddText("Jam Dunia CHEAT     "				,GetTime());
	AddItem("Visual Menu"			, Moptfolder			, &cFolders.Visual															, 2, MENUFOLDER); 
	if(cFolders.Visual) 
	{
		AddItem("WHClean"			, Moptonoff				, (int*)FeatureEngine->_get("Visual.Direct3D.WallHack")->_ptr()				, 2,  MENUCAT);
		AddItem("Crosshair"			, MoptCross				, (int*)FeatureEngine->_get("Visual.Direct3D.CrossHair")->_ptr()			, 3,  MENUCAT);
		AddItem("NoSmoke"		, Moptonoff				, (int*)FeatureEngine->_get("Visual.Direct3D.NoSmoke")->_ptr()				, 2,  MENUCAT);
		AddItem("Chams"			, MoptCharms			, (int*)FeatureEngine->_get("Visual.Direct3D.Charms")->_ptr()				, 4,  MENUCAT);
		AddItem("NoFog"			, MoptCharms			, (int*)FeatureEngine->_add("Visual.Direct3D.NoFog")->_ptr()				, 4,  MENUCAT);
	}
	AddItem("Wallhack Menu"			, Moptfolder			, &cFolders.Esp																, 2, MENUFOLDER); 
	if(cFolders.Esp) 
	{
		AddItem("Team"			, Moptonoff				, (int*)FeatureEngine->_get("Visual.ESP.Team")->_ptr()						, 2,  MENUCAT);
		AddItem("Name"			, Moptonoff				, (int*)FeatureEngine->_get("Visual.ESP.Name")->_ptr()						, 2,  MENUCAT);
		AddItem("Head"			, Moptonoff				, (int*)FeatureEngine->_get("Visual.ESP.Head")->_ptr()						, 2,  MENUCAT);
		AddItem("Health"		, Moptonoff				, (int*)FeatureEngine->_get("Visual.ESP.Healthbar")->_ptr()					, 2,  MENUCAT);
		AddItem("Line"			, Moptonoff				, (int*)FeatureEngine->_get("Visual.ESP.Line")->_ptr()						, 2,  MENUCAT);
		AddItem("Bone"			, Moptonoff				, (int*)FeatureEngine->_get("Visual.ESP.Bone")->_ptr()						, 2,  MENUCAT);
	}
	AddItem("Aim Menu"			, Moptfolder			, &cFolders.Assist															, 2, MENUFOLDER); 
	if(cFolders.Assist) 
	{
		AddItem("Aim Bulet"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Assist.Mode")->_ptr()					, 2,  MENUCAT);
		AddItem("Aim Mode"		, MoptAssistTarget		, (int*)FeatureEngine->_get("GameHack.Assist.Target")->_ptr()				, 2,  MENUCAT);
		AddItem("Hotkey Mode", MoptAssistHotkeyMode	, (int*)FeatureEngine->_get("GameHack.Assist.HotkeyMode")->_ptr()			, 2,  MENUCAT);
		AddItem("Hotkey"		, MoptAssistHotkey		, (int*)FeatureEngine->_get("GameHack.Assist.Hotkey")->_ptr()				, 6,  MENUCAT);
	}
	AddItem("Player Menu"			, Moptfolder			, &cFolders.Player															, 2, MENUFOLDER); 
	if(cFolders.Player) 
	{
		AddItem("Plant Defuse"			, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.PlantDefuse")->_ptr()				, 2,  MENUCAT);
		AddItem("Night Vision"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.NightVision")->_ptr()		, 2,  MENUCAT);
		AddItem("Auto Headshot"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.AutoHeadshot")->_ptr()			, 2,  MENUCAT);
		AddItem("JumpHight (Terbang)"		, MoptReborn			, (int*)FeatureEngine->_get("GameHack.Player.JumpHeight")->_ptr()				, 2,  MENUCAT);
		AddItem("Invicible"		, MoptBugWeapon			, (int*)FeatureEngine->_get("GameHack.Player.Invicible")->_ptr()				, 6,  MENUCAT);
		AddItem("BugUnyu"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.BugUnyu")->_ptr()				, 2,  MENUCAT);
		AddItem("BugDatar"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.BugDatar")->_ptr()				, 2,  MENUCAT);
		AddItem("Bug Up"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.BugUp")->_ptr()				, 2,  MENUCAT);
		AddItem("ZombieKiller"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.ZombieKiller")->_ptr()				, 2,  MENUCAT);
		AddItem("Skill Up"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.SkillUp")->_ptr()				, 2,  MENUCAT);
		AddItem("auto GM"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.autoGM")->_ptr()				, 2,  MENUCAT);
		AddItem("Reset Weapon"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.ResetWeapon")->_ptr()				, 2,  MENUCAT);
		AddItem("Always Invicible"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.AlwaysInvicible")->_ptr()				, 2,  MENUCAT);
		AddItem("Reborn Hack"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.Reborn")->_ptr()				, 2,  MENUCAT);
		AddItem("Free Move"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.FreeMove")->_ptr()				, 2,  MENUCAT);
		AddItem("Brust Knife"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.BrustKnife")->_ptr()				, 2,  MENUCAT);
		AddItem("Move Speed"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.MoveSpeed")->_ptr()				, 2,  MENUCAT);
		AddItem("HookMoveSpeed"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.HookMoveSpeed")->_ptr()				, 2,  MENUCAT);
		AddItem("Teleport"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Player.Teleport")->_ptr()				, 2,  MENUCAT);
		AddItem("KickPlayer"	, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Misc.KickPlayer")->_ptr()		, 2,  MENUCAT);
		AddItem("KickPlayerSelector"	, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Misc.BypassServerFull")->_ptr()		, 2,  MENUCAT);
		AddItem("KickAllPlaye"	, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Misc.KickAllPlaye")->_ptr()		, 2,  MENUCAT);
		AddItem("Anti Kick"			, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Misc.AntiKick")->_ptr()				, 2,  MENUCAT);
		AddItem("Unlock Pass Room"	, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Misc.BypassRoomPassword")->_ptr()		, 2,  MENUCAT);
		AddItem("Auto Invite Room"	, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Misc.AutoInviteRoom")->_ptr()			, 2,  MENUCAT);
		AddItem("Anti Server Full"	, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Misc.KickPlayerSelector")->_ptr()		, 2,  MENUCAT);
		if(GameHack.Player.HookMoveSpeed){
			AddItem("- Select Speed", MoptSpeed				,  &GameHack.Player.MoveSpeed												, 7,  MENUCAT);
		}
		AddText("Suicide"			,"Press END*");
	}
	AddItem("Weapon Menu"			, Moptfolder			, &cFolders.Weapon															, 2, MENUFOLDER); 
	if(cFolders.Weapon) 
	{
		AddItem("Quick Change"			, Moptonoff				, (int*)FeatureEngine->_add("GameHack.Weapon.QuickChange")->_ptr()				, 2,  MENUCAT);
		AddItem("AutoFillSubAmmo"			, Moptonoff				, (int*)FeatureEngine->_add("GameHack.Weapon.AutoFillSubAmmo")->_ptr()				, 2,  MENUCAT);
		AddItem("Skip Reload"		, Moptonoff				      , (int*)FeatureEngine->_add("GameHack.Weapon.SkipReload")->_ptr()			, 2,  MENUCAT);
		AddItem("NoRecoil"	, Moptonoff				          , (int*)FeatureEngine->_add("GameHack.Weapon.NoRecoil")->_ptr()		, 2,  MENUCAT);
		 AddItem("Accuracy AWP&SG"	, Moptonoff				          , (int*)FeatureEngine->_add("GameHack.Weapon.Accuracy")->_ptr()			, 2,  MENUCAT);
//		AddItem("MacroAllWeapon"			, Moptonoff				, (int*)FeatureEngine->_add("GameHack.Weapon.MacroAllWeapon")->_ptr()				, 2,  MENUCAT);										, 6,  MENUCAT);
		AddItem("FireSpeed"			, Moptonoff				, (int*)FeatureEngine->_add("GameHack.Weapon.FireSpeed")->_ptr()				, 2,  MENUCAT);
		AddItem("RapidFire"	, Moptonoff				,          (int*)FeatureEngine->_add("GameHack.Weapon.RapidFire")->_ptr()				, 2,  MENUCAT);
		AddItem("Auto  Fire"		, Moptonoff				, (int*)FeatureEngine->_add("GameHack.Weapon.AutoFire")->_ptr()			, 2,  MENUCAT);
		AddItem("Auto  Shot"		, MoptRapidFire			, (int*)FeatureEngine->_add("GameHack.Weapon.AutoShot")->_ptr()			, 5,  MENUCAT);
		AddItem("Set  Brust"		, MoptRapidFire			, (int*)FeatureEngine->_add("GameHack.Weapon.SetBrust")->_ptr()			, 5,  MENUCAT);
//		AddItem("Macro SG"			, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Weapon.MacroAllWeapon")->_ptr()		, 2,  MENUCAT);											, 6,  MENUCAT);
		AddItem("NET_FIRE"		, MoptRapidFire			, (int*)FeatureEngine->_add("GameHack.Weapon.NET_FIRE")->_ptr()			, 5,  MENUCAT);
	}
	AddItem("Hard Menu"				, Moptfolder			, &cFolders.Hard															, 2, MENUFOLDER); 
	if(cFolders.Hard)
	{
		AddItem("Fast Killer"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Brutal.FastKiller")->_ptr()			, 2,  MENUCAT);
		AddItem("Health Support"	, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Special.HealthSupport")->_ptr()		, 2,  MENUCAT);
		AddItem("Health Absorber"	, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Special.HealthAbsorber")->_ptr()		, 2,  MENUCAT);
		AddItem("ExplosiveKiller"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Brutal.ExplosiveKiller")->_ptr()			, 2,  MENUCAT);
		AddItem("AutoKiller"		, MoptShield			, (int*)FeatureEngine->_get("GameHack.Brutal.AutoKiller")->_ptr()				, 2,  MENUCAT);
		AddItem("ShieldBM"			, MoptTele				, (int*)FeatureEngine->_get("GameHack.Player.ShieldBM")->_ptr()				, 2,  MENUCAT);
		AddItem("Bullet"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Brutal.Bullet")->_ptr()			, 2,  MENUCAT);
		AddItem("RPGKiller"		, Moptonoff				, (int*)FeatureEngine->_get("GameHack.Brutal.RPGKiller")->_ptr()			, 2,  MENUCAT);
		AddItem("BomberMan"		  , Moptonoff				, (int*)FeatureEngine->_get("GameHack.Brutal.BomberMan")->_ptr()			, 2,  MENUCAT);
		
	}
	AddItem("Replace Menu"			, Moptfolder			, &cFolders.Replace															, 2, MENUFOLDER); 
	if(cFolders.Replace)
	{
		AddItem("Assault"			, MoptRplc				, (int*)FeatureEngine->_get("GameHack.Selector.Assault")->_ptr()			,31,  MENUCAT);
		AddItem("Smg"				, MoptRplc2				, (int*)FeatureEngine->_get("GameHack.Selector.SMG")->_ptr()				,13,  MENUCAT);
		AddItem("Sniper"			, MoptRplc3				, (int*)FeatureEngine->_get("GameHack.Selector.Sniper")->_ptr()				,11,  MENUCAT);
		AddItem("Shotgun"			, MoptRplc4				, (int*)FeatureEngine->_get("GameHack.Selector.Shotgun")->_ptr()			, 7,  MENUCAT);
		AddItem("Secondary"			, MoptRplc5				, (int*)FeatureEngine->_get("GameHack.Selector.Secondary")->_ptr()			, 8,  MENUCAT);
		AddItem("Damage"			, MoptRplc5				, (int*)FeatureEngine->_get("GameHack.Selector.Damage")->_ptr()			, 8,  MENUCAT);
		AddItem("MachineGun"			, MoptRplc5				, (int*)FeatureEngine->_get("GameHack.Selector.MachineGun")->_ptr()			, 8,  MENUCAT);
		AddItem("HealthAbsorber"			, MoptRplc6				, (int*)FeatureEngine->_get("GameHack.Selector.HealthAbsorber")->_ptr()			, 8,  MENUCAT);
		AddItem("HealthSupport"			, MoptRplc2				, (int*)FeatureEngine->_get("GameHack.Selector.HealthSupport")->_ptr()			, 8,  MENUCAT);
	}
}

void MenuHandler( LPDIRECT3DDEVICE9 pDevice )
{
	return;
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