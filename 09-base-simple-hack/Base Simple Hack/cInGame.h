static bool FuncMessageNotice,FuncAnnounceMessage=false;
//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//
void  CallFuncInGame()
{
if (IsInBattle()) 
	{	
		//CGameContext::g_pGameContext()->SetPing((char)0x3);
		if(FuncMessageNotice == false)
		{
		//	CGameFramework::g_pFramework()->MsgBox("{col:255.255.0.255}Selamat Datang Di Cheat VIP CyberFamouse\n{col:0.255.0.255}Silahakan Gunakan Keyboard Untuk Melakukan On Of Fiture Menu\n{col:150.0.255.255}Semua fiture dapat digunakan\nUntuk mengecek Durasi, Nama pembeli,Resseler penjualan tersedia di fb saya fb.com/LyCorNgTeamVIP\n{col:255.0.0.255}Banned ID bukan tanggung jawab kami, gunakan sebijak mungkin\nJika ada notice Koneski Game Bersamalah, Berarti anda memakai cheat yang sangat rusuh,secepat nya tekan F12 di keyboard agar char anda tidak melayang.\nHati-hati terhadap GM yang kadang memakai char yang kadang di room tidak ada namanya\n{col:255.0.255.255}Jangan melempar pertanyaan BODOH di Admin, Mas Kenapa saya di VK AbUSE? anda DC di VK Karena yang VK Memlih opsi ABUSE saat melalukan Vote Kick\n\nSalam Admin:\Zaki Mubarak","Notice");
			//PrintChatBox("{col:255.255.0.255}Selamat Datang Di EliteWorldCyber™ {/col}");
			//PrintChatBox("{col:0.255.0.255}Terima Kasih Telah Memakai Cheat EliteWorld {/col}");
			//PrintChatBox("{col:0.0.255.255}Sebelum Pake Cheat Diharapkan Ngerti Pakainya :) {/col}"); 
			//PrintChatBox("{col:150.0.255.255}Diharapkan Jangan Brutal :P {/col}");
			//PrintChatBox("{col:255.0.0.255}Jika Mau Perpanjang PM EliteWorldCyber Yoww {/col}");
			//PrintChatBox("{col:255.0.255.255}Credit : EliteWorldCyber.blogspot.com {/col}");
			FuncMessageNotice = true;
		}
	}else{FuncMessageNotice = false;}
//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//
	if(IsInBattle())
	{	
	if(CGameContext::g_pGameContext()->getUserDeath(CGameContext::g_pGameContext()->setMySlotIdx()))
	{	
		if(FuncAnnounceMessage == false)
		{
			//CGameCharaCameraContext::NoRespawn();
		//	CGameFramework::g_pFramework()->SetAnnounceMessage("Mampus Loe Sekarat");
			//PrintChatBox("{col:255.0.255.255}Your Chara Suicide{/col}" );
			FuncAnnounceMessage = true;
		}
	}else{
		if(FuncAnnounceMessage == true)
		{
			//CGameFramework::g_pFramework()->SetAnnounceMessage("Alhamdulillah Damang");
			FuncAnnounceMessage = false;
		}
	}
	}

//if(IsInBattle()){	
//if(AimBullet==1)
//{	
//	if(FuncAimBullet == false)
//	{
//		CGameFramework::g_pFramework()->GetChatBox()->_PutStringBackUpBuffer("{col:244,205,52,255}AimBullet ON{/col}"); 
//		FuncAimBullet = true;
//	}
//}else{
//	if(FuncAimBullet == true)
//	{
//		//CGameFramework::g_pFramework()->GetChatBox()->_PutStringBackUpBuffer("{col:255.0.255.255}AimBullet OFF{/col}");
//		FuncAimBullet = false;
//	}
//}}
//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//
}