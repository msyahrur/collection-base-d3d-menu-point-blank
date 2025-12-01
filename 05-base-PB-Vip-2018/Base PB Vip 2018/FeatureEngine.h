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
struct sFeatures
{
	char Key[100];
	int Value;
	sFeatures(char* Key, int Value)
	{
		strcpy(this->Key, Key);
		this->Value = Value;
	}
	virtual int _val()
	{
		return this->Value;
	}
	virtual void* _ptr()
	{
		return &this->Value;
	}
	virtual void _set(int val)
	{
		this->Value = val;
	}
	virtual void _enable()
	{
		this->Value = 1;
	}
	virtual void _disable()
	{
		this->Value = 0;
	}
	virtual void _toggle()
	{
		this->Value = !this->Value;
	}
	
};

class cFeatureEngine
{
private:
	vector<sFeatures> FeatureList;
	
public:
	virtual sFeatures* _get(char* Key);
	virtual sFeatures* _add(char* Key, bool bHackFlags, int Value);
	virtual bool pIsKeyboardKeyDownOnce(int Index);
};

sFeatures *nullFeature = new sFeatures("", 0);
sFeatures* cFeatureEngine::_get(char* Key)
{
	for(unsigned int i = 0; i < FeatureList.size(); i++)
	{
		sFeatures* Current = &FeatureList[i];
		if(strcmp(Current->Key, Key) == 0){
			return Current;
		}
	}
	return nullFeature;
}

sFeatures* cFeatureEngine::_add(char* Key, bool bHackFlags = true, int Value = 0)
{
	if(bHackFlags == true){
		sFeatures NewFeatures (Key, Value);
		FeatureList.push_back(NewFeatures);
		return this->_get(Key);
	}
	return NULL;
}

bool cFeatureEngine::pIsKeyboardKeyDownOnce(int Index)
{
	return IsKeyboardKeyDownOnce(Index);
}

cFeatureEngine* FeatureEngine;
void InitializeFeatures()
{
	FeatureEngine = new cFeatureEngine;
	FeatureEngine->_add("Visual.Direct3D.WallHack"); 
	FeatureEngine->_add("Visual.Direct3D.CrossHair");
	FeatureEngine->_add("Visual.Direct3D.Charms");
	FeatureEngine->_add("Visual.Direct3D.NoSmoke");
	FeatureEngine->_add("Visual.Direct3D.NoFog");
	
	FeatureEngine->_add("Visual.ESP.Team");
	FeatureEngine->_add("Visual.ESP.Name");
	FeatureEngine->_add("Visual.ESP.Head");
	FeatureEngine->_add("Visual.ESP.Healthbar");
	FeatureEngine->_add("Visual.ESP.Line");
	FeatureEngine->_add("Visual.ESP.Bone");

	FeatureEngine->_add("GameHack.Assist.Mode");
	FeatureEngine->_add("GameHack.Assist.Target");
	FeatureEngine->_add("GameHack.Assist.Hotkey");
	FeatureEngine->_add("GameHack.Assist.HotkeyMode");

	FeatureEngine->_add("GameHack.Weapon.QuickChange");
	FeatureEngine->_add("GameHack.Weapon.AutoFillSubAmmo");
	FeatureEngine->_add("GameHack.Weapon.SkipReload");
	FeatureEngine->_add("GameHack.Weapon.NoRecoil");
	FeatureEngine->_add("GameHack.Weapon.Accuracy");
	FeatureEngine->_add("GameHack.Weapon.FireSpeed");
	FeatureEngine->_add("GameHack.Weapon.RapidFire");
	FeatureEngine->_add("GameHack.Weapon.AutoFire");
	FeatureEngine->_add("GameHack.Weapon.AutoShot");
	FeatureEngine->_add("GameHack.Weapon.SetBrust");
	FeatureEngine->_add("GameHack.Weapon.NET_FIRE");
	FeatureEngine->_add("GameHack.Weapon.MacroAllWeapon");
	
	FeatureEngine->_add("GameHack.Brutal.FastKiller");
	FeatureEngine->_add("GameHack.Brutal.ExplosiveKiller");
	FeatureEngine->_add("GameHack.Brutal.AutoKiller");
	FeatureEngine->_add("GameHack.Brutal.ShieldBM");
	FeatureEngine->_add("GameHack.Brutal.Bullet");
	
	FeatureEngine->_add("GameHack.Brutal.RPGKiller");
	FeatureEngine->_add("GameHack.Brutal.BomberMan");

	FeatureEngine->_add("GameHack.Player.PlantDefuse");
	FeatureEngine->_add("GameHack.Player.NightVision");
	FeatureEngine->_add("GameHack.Player.AutoHeadshot");
	FeatureEngine->_add("GameHack.Player.JumpHeight");
	FeatureEngine->_add("GameHack.Player.Invicible");
	FeatureEngine->_add("GameHack.Player.BugUnyu");
	FeatureEngine->_add("GameHack.Player.BugDatar");
	FeatureEngine->_add("GameHack.Player.BugUp");
	FeatureEngine->_add("GameHack.Player.ZombieKiller");
	
	FeatureEngine->_add("GameHack.Player.SkillUp");
	FeatureEngine->_add("GameHack.Player.autoGM");
	FeatureEngine->_add("GameHack.Player.ResetWeapon");
	FeatureEngine->_add("GameHack.Player.AlwaysInvicible");
	FeatureEngine->_add("GameHack.Player.Reborn");
	FeatureEngine->_add("GameHack.Player.FreeMove");
	FeatureEngine->_add("GameHack.Player.BrustKnife");
	FeatureEngine->_add("GameHack.Player.MoveSpeed");
	FeatureEngine->_add("GameHack.Player.HookMoveSpeed");
	FeatureEngine->_add("GameHack.Player.Teleport");

	FeatureEngine->_add("GameHack.Misc.AutoInviteRoom");
	FeatureEngine->_add("GameHack.Misc.KickAllPlayer");
	FeatureEngine->_add("GameHack.Misc.AntiKick");
	FeatureEngine->_add("GameHack.Misc.BypassServerFull");
	FeatureEngine->_add("GameHack.Misc.KickPlayer");
	FeatureEngine->_add("GameHack.Misc.KickPlayerSelector");
	FeatureEngine->_add("GameHack.Misc.BypassRoomPassword");

	FeatureEngine->_add("GameHack.Selector.Sniper");
	FeatureEngine->_add("GameHack.Selector.Assault");
	FeatureEngine->_add("GameHack.Selector.SMG");
	FeatureEngine->_add("GameHack.Selector.Shotgun");
	FeatureEngine->_add("GameHack.Selector.Secondary");
	FeatureEngine->_add("GameHack.Selector.MachineGun");
	FeatureEngine->_add("GameHack.Selector.Damage");

	FeatureEngine->_add("GameHack.Special.HealthAbsorber");
	FeatureEngine->_add("GameHack.Special.HealthSupport");
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
