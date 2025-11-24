//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
class CGameContext
{
public:
	DWORD getMySlotIdx(void)
	{
		return *(DWORD*)(this + AddyEngine->GetAddyValueByKey("GameContext.Pointer.MySlotIdx"));
	}
	bool isRedTeam(int CharaIndex)
	{
		if(CharaIndex % 2 == 0)return true;
		else return false;
	}
	bool getUserDeath(int iSlot) {
		auto Func = (bool(__thiscall*)(CGameContext*, int))ResultUserDeath;
		return Func(this, iSlot);
	}
	const char* getNickForSlot(int CharaIndex)
	{
		typedef const char* (__thiscall * tgetNickForSlot)(CGameContext* Base, int Index);
		tgetNickForSlot getNickForSlot = (tgetNickForSlot)(AddyEngine->GetAddyValueByKey("GameContext.Function.getNickForSlot"));
		return getNickForSlot(this,CharaIndex);
	}
	void setEvent (int EventIndex, const void* pArg, const void* a3,const void* a4, const char* a5, int a6)
	{
		typedef void (__thiscall* tsetEvent)(CGameContext* Base, int EventIndex, const void* pArg, const void* a3,const void* a4, const char* a5, int a6);
		tsetEvent setEvent = (tsetEvent)(AddyEngine->GetAddyValueByKey("GameContext.Function.setEvent"));
		return setEvent(this, EventIndex, pArg, a3, a4, a5, a6);
	}
	void SetInviteUser(int Index)
	{
		typedef void (__thiscall * tSetInviteUser)(CGameContext* Base, int Index);
		tSetInviteUser SetInviteUser = (tSetInviteUser)( AddyEngine->GetAddyValueByKey("GameContext.Function.SetInviteUser"));
		return SetInviteUser(this, Index);
	}
	void SetChannelUserCount(int idxChannel, DWORD Count)
	{
		*(DWORD*)( this + AddyEngine->GetAddyValueByKey("GameContext.Pointer.ChannelUserCount") + (idxChannel * 4) ) = Count;
	}
	void SetMaxChannelUserCount(DWORD Count)
	{
		*(DWORD*)( this + AddyEngine->GetAddyValueByKey("GameContext.Pointer.MaxChannelUserCount")) = Count;
	}
}; CGameContext* pGameContext = NULL;