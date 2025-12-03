//Bagus Tuyul
struct sFolder{
	int Direct3D;
	int ESP;
	int Assist;
	int Misc;
	int Weapon;
	int Player;
	int Brutal;
	int Replace;
	int GBMode;
	int Other;
	int Launcher;
}; sFolder Folder;

struct sDirect3D
{
	int MoveD3D9;
	int WallHack;
	int Charms;
	int NoSmoke;
	int NoFog;
	int CrossHair;
};

struct sESP
{
	int Bone;
	int Head;
	int Line;
	int Name;
	int Health;
	int Ping;
	int KillDeath;
};

struct sAssist
{
	int Mode;
	int Target;
	int Hotkey;
	int HotkeyMode;
	int AimReal;
	int AutoShot;
	int AutoFire;
};

struct sMisc
{
	int AntiSF;
	int UnlockPW;
	int AutoInvite;
	int AntiKick;
};

struct sWeapon
{
	int QuickChange;
	int FastReload;
	int NoRecoil;
	int Accuracy;
	int FullSubAmmo;
	int RapidFire;
	int SetBrust;
	int AutoMacro;
};

struct sPlayer
{
	int FallDamage;
	int HideNick;
	int SkillUp;
	int WallBug;
	int BugUnyu;
	int Reborn;
	int Suicide;
	int JumpHack;
};

struct sBrutal
{
	int ShieldBomb;
	int Teleport;
	int AutoKiller;
	int BulletTele;
	int NetFire;
};

struct sReplace
{
	int Damage;
	int ReplaceAssault;
	int ReplaceSmg;
	int ReplaceSniper;
	int ReplaceShotgun;
	int RPG;
	int M79;
};

struct sGBMode
{
	int AutoReady;
	int AutoBundir;
};

struct sVisual
{
	sDirect3D Direct3D;
	sESP ESP;
};
sVisual Visual = {0};

struct sGameHack
{
	sAssist Assist;
	sWeapon Weapon;
	sPlayer Player;
	sBrutal Brutal;
};
sGameHack GameHack = {0};

struct sOther
{
	sMisc Misc;
	sReplace Replace;
	sGBMode GBMode;
};
sOther Other;

void CallAutoOff()
{
	if(!IsInBattle()){
		GameHack.Assist.AimReal=0;
		GameHack.Assist.AutoShot=0;
		GameHack.Assist.AutoFire=0;
		GameHack.Weapon.AutoMacro=0;
		GameHack.Weapon.RapidFire=0;
		GameHack.Weapon.FullSubAmmo=0;
		GameHack.Weapon.SetBrust=0;
		GameHack.Player.FallDamage=0;
		GameHack.Player.WallBug=0;
		GameHack.Player.BugUnyu=0;
		GameHack.Player.Reborn=0;
		GameHack.Player.JumpHack=0;
		GameHack.Player.Suicide=0;
		GameHack.Brutal.Teleport=0;
		GameHack.Brutal.AutoKiller=0;
		Other.Replace.Damage=0;
		Other.Replace.ReplaceAssault=0;
		Other.Replace.ReplaceSmg=0;
		Other.Replace.ReplaceSniper=0;
		Other.Replace.ReplaceShotgun=0;
	}
}