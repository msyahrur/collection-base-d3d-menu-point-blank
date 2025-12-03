static bool FuncMessageBypass,FuncMessageBox,FuncTextBox=false;
void  CallFuncOutGame()
{

//------------------------------------------------------------------------------------------------------------//
//----------------------------------------------Tittle In Server----------------------------------------------//		
//------------------------------------------------------------------------------------------------------------//
if (GetStageGame() == SERVER) 
	{	
		CGameFramework::g_pFramework()->SetAnnounceMessage("Selamat Datang Di Cheat VIP EliteWorldCyber Silahakan Gunakan Keyboard Untuk Melakukan On Of Fiture Menu Semua fiture dapat digunakan | Salam Admin: Zaki Mubarak");
	}
//------------------------------------------------------------------------------------------------------------//
//-------------------------------Tittle In Loby & Bypass ServerFull Channel List------------------------------//
//------------------------------------------------------------------------------------------------------------//
if (GetStageGame() == CHANNEL) 
	{
		//DetourFunction((PBYTE)ResultGetChannelUserCount, (PBYTE)CallGetChannelUserCount,0x5);
		//for(int i = 0; i < 10; i++){CGameContext::g_pGameContext()->SetChannelUserCount(i,0);}
		CGameFramework::g_pFramework()->SetAnnounceMessage("Bypass Server Full Channel, Server List Menjadi Kosong || Suta Wijaya");
		if(FuncMessageBypass == false)
		{
			CGameFramework::g_pFramework()->MsgBox("Bypass Server Full was Actived","Notice");
			FuncMessageBypass = true;
		}
			Write_((void*)(LogGaugeMultiplier),(char*)"\x00\x00\x00\x00\x00\x00\x00\x00", 8);
}else{
		if(FuncMessageBypass == true){FuncMessageBypass = false;}
		Write_((void*)(LogGaugeMultiplier), (char*)"\x00\x00\x00\x00\x00\x00\x59\x40", 8);
	}
//------------------------------------------------------------------------------------------------------------//
//------------------------------------Tittle In Loby & Bypass Password Room-----------------------------------//
//------------------------------------------------------------------------------------------------------------//
	if (GetStageGame() == LOBBY) 
	{			CGameFramework::g_pFramework()->SetAnnounceMessage("#AKUMAINKOTOR Bypass Room Password Active & Bypass Skip Abuse OK|| Gunakan Cheat Dengan Bijak Dengan Aman & Jangan Terlalu Brutal || EliteWorldCyber");
		IsGM = 1; 
		DetourFunction((PBYTE)ResultGetEnteredServerX, (PBYTE)ForceAcess,0x4); 
		if(FuncMessageBox == false)
		{
			CGameFramework::g_pFramework()->MsgBox("Gunakan Dengan Bijak\nBannned ID Bukan Tanggung Jawab Kami\n{col: 255.255.0.255}Admin Developer{/col}","Informations");
			FuncMessageBox = true;
		}
	}else{
		if(FuncMessageBox == true){FuncMessageBox = false;}
	IsGM = 0;
		DetourFunction((PBYTE)ResultGetEnteredServerX, (PBYTE)ForceAcess,0x4);
	}
////------------------------------------------------------------------------------------------------------------//	
	//if (GetStageGame() == AWAITING) 
	//{	
	//	//static DWORD dwTick = NULL;
	//	//if(dwTick <= GetTickCount())
	//	//{
	//	//	CGameContext::g_pGameContext()->SetEvent(0x83, NULL, NULL);
	//	//	for(int i = 0; i < 8; i++){CGameContext::g_pGameContext()->GetUserInfoInvite(i);}
	//	//	CGameContext::g_pGameContext()->SetEvent(0x84, NULL, NULL);
	//	//	dwTick = GetTickCount() + 500;
	//	//}
	//	MEMpatch((BYTE*)Result__CreateRoomMasterKick, RET, sizeof(RET));
	//	if(FuncTextBox == false){
	//	/*PrintChatBox();
	//	CGameFramework::g_pFramework()->GetChatBox()->_PutStringBackUpBuffer("{col: 255.255.0.255}Bypass: {/col}{col:255.0.255.255}Password Room Unlocker,Anti Kick Room Master,Auto Invite Players.{/col}");*/
	//	FuncTextBox = true;
	//	}
	//}else{
	//	MEMpatch((BYTE*)Result__CreateRoomMasterKick, PUSH_EBP, sizeof(PUSH_EBP));
	//	//if(FuncTextBox == true){FuncTextBox = false;}
	//}
	//
//------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------Welcome--------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//

//------------------------------------------------End cOutGame------------------------------------------------//
}