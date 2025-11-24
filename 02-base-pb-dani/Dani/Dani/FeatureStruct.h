//Created by DANI XCT / WA DANI IDI/MENU XXN PART 2
class cFeature
{
public:
	//cFeature(){
	//	Folders.Direct3D=1;
	//};
	struct cFolders
	{
		int Info;
		int Direct3D;
		int Hard;
		int ESP;
		int Medium;
		int GBMode;
		int Replace;
	}Folders;

	struct cDirect3D
	{
		int MoveD3D9;
		int CrossHair;
	}Direct3D;

	struct cESP
	{
		int Bone;
		int Line;
		int NameTag;
		int Health;
		int TagGM;
	}ESP;

	struct cAIM
	{
		int Bullet;
		int Real;
		int AutoFire;
		int AutoKiller;
		int NetFire;
	}AIM;

	struct cMisc
	{
		int AutoInvite;
		int OpenSFull;
		int UnlockPW;
		int AntiKick;
		int AutoReady;
		int AutoBundir;
	}Misc;

	struct cPlayer
	{
		int JumpHight;
		int HideNick;
		int Teleport;
		int Reborn;
		int Shield;
		int NoFallDamage;
		int AutoSuicide;
		int NightVision;
	}Player;

	struct cWeapon
	{
		int AutoMacro;
		int NoRecoil;
		int Accuracy;
		int QuickChange;
		int AutoShot;
		int RapidFire;
	}Weapon;

	struct cReplace
	{
		int Damage;
		int Assault;
		int Launcher;
		int Smg;
		int Sniper;
		int Shotgun;
	}Replace;
};
extern cFeature Feature;