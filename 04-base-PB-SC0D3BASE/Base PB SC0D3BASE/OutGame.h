static BYTE Room, IsGM = 0;
__declspec (naked) void ForceAcess() {
	{	
		__asm {
			push 0
				push 0
				lea ecx, IsGM
				push ecx
				jmp ResultGetEnteredServerJMP
		}
	}
}

void CallFuncOutGame()
{
	if(Other.Misc.AntiSF && !IsInBattle())
	{
		pGameContext->SetMaxChannelUserCount(1000);
		for(int i = 0; i < 10; i++)
		{
			pGameContext->SetChannelUserCount(i, 0);
		}
		_patchMEM((void*)(AddyEngine->GetAddyValueByKey("XFHPB.Values.GaugeMultiplier")), (char*)"\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	}
	else
	{
		_patchMEM((void*)(AddyEngine->GetAddyValueByKey("XFHPB.Values.GaugeMultiplier")), (char*)"\x00\x00\x00\x00\x00\x00\x59\x40", 8);
	}
	if(Other.Misc.UnlockPW)
	{
		IsGM = 1; 
	    MakeJMP((PBYTE)ResultGetEnteredServerX, (DWORD)ForceAcess, 0x4); 
	}
	if(Other.Misc.AutoInvite && !IsInBattle())
	{
		static DWORD dwTick = NULL;
		if(dwTick <= GetTickCount()){

			pGameContext->setEvent(EventCode.GetLobbyUserList, NULL, NULL, NULL, NULL, NULL);
			for(int i = 0; i < 8; i++){
				pGameContext->SetInviteUser(i);
			}
			pGameContext->setEvent(EventCode.SendInviteUser, NULL, NULL, NULL, NULL, NULL);
			dwTick = GetTickCount() + 500;
		}
	}
	if(Other.Misc.AntiKick)
	{
		_patchMEM((void*)(AddyEngine->GetAddyValueByKey(/*PhaseReadyRoom.Function.SelfRemoveFromRoom*/XorStr<0x65,43,0x36BAA349>("\x35\x0E\x06\x1B\x0C\x38\x0E\x0D\x09\x17\x3D\x1F\x1E\x1F\x5D\x32\x00\x18\x14\x0C\x10\x15\x15\x52\x2E\x1B\x13\xE6\xD3\xE7\xEE\xEB\xF3\xE3\xC1\xFA\xE6\xE7\xD9\xE3\xE2\xE3"+0x36BAA349).s)), (char*)"\xC3", 1);
	}else{
		_patchMEM((void*)(AddyEngine->GetAddyValueByKey(/*PhaseReadyRoom.Function.SelfRemoveFromRoom*/XorStr<0x65,43,0x36BAA349>("\x35\x0E\x06\x1B\x0C\x38\x0E\x0D\x09\x17\x3D\x1F\x1E\x1F\x5D\x32\x00\x18\x14\x0C\x10\x15\x15\x52\x2E\x1B\x13\xE6\xD3\xE7\xEE\xEB\xF3\xE3\xC1\xFA\xE6\xE7\xD9\xE3\xE2\xE3"+0x36BAA349).s)), (char*)"\x55", 1);
	}
}

bool FuncAbuse1=true;
void CallBypassAbuse()
{
	if(FuncAbuse1==true)
	{
		if(!IsInBattle())
		{
			static bool setAbuse = false;
			if(*(PDWORD)((DWORD)pGameContext + ResultPTRAbuse + 0x8) != NULL) 
				setAbuse = true;
			else
				setAbuse = false;

			static DWORD dwTick = NULL;
			if(setAbuse == true)
			{
				if(dwTick == NULL)
				{
					*(PDWORD)((DWORD)pGameContext + ResultPTRAbuse + 0x8) = 1;
					dwTick =  GetTickCount() + 2000;
				}
				if(dwTick <= GetTickCount())
				{
					*(PDWORD)((DWORD)pGameContext + ResultPTRAbuse + 0x8) = 0;
					setAbuse = false;
					dwTick = NULL;
				}
			}
		}
	}
}