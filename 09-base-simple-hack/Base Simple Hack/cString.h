bool BoxNotice,Chat=true;
bool FuncWallHack,FuncCrossHair,FuncESPBone,FuncESPHealth,FuncESPName,FuncESPLine,FuncAimBullet,FuncAutoBone,FuncWutmo,FuncJumpHeight,FuncInvicible,FuncNoRecoil,FuncFastKnife,FuncWsHt,FuncCTPlant,FuncFastKiller,FuncFastBomberMan,FuncAutoKill,FuncZombie,FuncR_AllMode=false;
/*void _fastcall WelcomeNotice()
{
	
	if (getStageGame() == CHANNEL) 
	{
		CGameFramework::g_pFramework()->MsgBox("Selamat Datang Di Cheat VIP EliteWorld\nSilahakan Gunakan Keyboard Untuk Melakukan On Of Fiture Menu\nSemua fiture dapat digunakan\nUntuk mengecek Durasi, Nama pembeli, Resseler penjualan tersedia di fb saya fb.com/sabu43\nBanned ID bukan tanggung jawab kami, gunakan sebijak mungkin\nJika ada notice Koneski Game Bersamalah, Berarti anda memakai cheat yang sangat rusuh,secepat nya tekan F12 di keyboard agar char anda tidak melayang.\nHati-hati terhadap GM yang kadang memakai char yang kadang di room tidak ada namanya\nJangan melempar pertanyaan BODOH di Admin, Mas Kenapa saya di VK AbUSE? anda DC di VK Karena yang VK Memlih opsi ABUSE saat melalukan Vote Kick\n\nSalam Admin:\nZakiEliteWorld","Notice");
		BoxNotice = false;
	}
	
	if (WHClean && GMCT){
		CGameFramework::g_pFramework()->MsgBox("WallHack Sudah Diaktifkan, Fiture Ini Mempermudah Dimana Musuh Berada, Karena Tembus Tembok","LyCorNgTeamVIP.Net");
		GMCT = false;
	}
	
	if (Cross && GMCT){
		CGameFramework::g_pFramework()->MsgBox("CrossHair Sudah Diaktifkan, Dimana Titik Hijau Berada Kalo Menggunakan Sniferr Titik Hijau Di Tengah Menghilang Nah Ini Fiture Untuk Mempermuncul Titik Hijau","LyCorNgTeamVIP.Net");
		GMCT = false;
	}
	
	if (CallAmmo && GMCT){
		CGameFramework::g_pFramework()->MsgBox("ESP-Bone Sudah Diaktifkan, ESP Bone Untuk Melihat Musub Dengan Tulang Tulang Yang Sangat Jelas","LyCorNgTeamVIP.Net");
		GMCT = false;
	}
					if (CallAmmo && GMCT){
		CGameFramework::g_pFramework()->MsgBox("Unlimited Ammo Sudah Diaktifkan, Jangan Coba-coba Untuk Mengambil Senjata Sesama Tim Kalau Tidak Ingin Terdeteksi Menggunakan Program Ilegal\nKalau Ingin Mengambil Senjata Sesama Tim Non-Aktifkan Terlebih Dahulu Unlimited Ammo, Lalu Aktifkan Kembali","LyCorNgTeamVIP.Net");
		GMCT = false;
	}

						if (CallAmmo && GMCT){
		CGameFramework::g_pFramework()->MsgBox("Unlimited Ammo Sudah Diaktifkan, Jangan Coba-coba Untuk Mengambil Senjata Sesama Tim Kalau Tidak Ingin Terdeteksi Menggunakan Program Ilegal\nKalau Ingin Mengambil Senjata Sesama Tim Non-Aktifkan Terlebih Dahulu Unlimited Ammo, Lalu Aktifkan Kembali","LyCorNgTeamVIP.Net");
		GMCT = false;
	}
							if (CallAmmo && GMCT){
		CGameFramework::g_pFramework()->MsgBox("Unlimited Ammo Sudah Diaktifkan, Jangan Coba-coba Untuk Mengambil Senjata Sesama Tim Kalau Tidak Ingin Terdeteksi Menggunakan Program Ilegal\nKalau Ingin Mengambil Senjata Sesama Tim Non-Aktifkan Terlebih Dahulu Unlimited Ammo, Lalu Aktifkan Kembali","LyCorNgTeamVIP.Net");
		GMCT = false;
	}

	if (CallAmmo && GMCT){
		CGameFramework::g_pFramework()->MsgBox("Unlimited Ammo Sudah Diaktifkan, Jangan Coba-coba Untuk Mengambil Senjata Sesama Tim Kalau Tidak Ingin Terdeteksi Menggunakan Program Ilegal\nKalau Ingin Mengambil Senjata Sesama Tim Non-Aktifkan Terlebih Dahulu Unlimited Ammo, Lalu Aktifkan Kembali","LyCorNgTeamVIP.Net");
		GMCT = false;
	}

	if (AutoKill && KMCT)
	{
		CGameFramework::g_pFramework()->MsgBox("Fitur Rusuh Telah Di Aktifkan, Resiko Banned Akibat Di SS/Video Kemungkinan Besar Terjadi\nJika Masih Sayang Dengan Char Anda Tebih Baik Di Non-Aktifkan","LyCorNgTeamVIP.Net");
		KMCT = false;
	}

	if (ReplaceCCD && RMCT)
	{
		CGameFramework::g_pFramework()->MsgBox("Fitur Ini Hanya Untuk Bergaya-gaya Saja, Namun Fang Blade Dapat Menambah Damagae Up","LyCorNgTeamVIP.Net");
		RMCT = false;}

	if(Helpfs)
	{
		CGameFramework::g_pFramework()->MsgBox("1. Jika Di Bomb Mission Pilih Dulu ReSmoke Sesuai Anda Mau.\n2. Setelah Itu Tekan F12 Untuk Fast Kill 1 HIT.\n3. Di round selanjutnya setelah WIN Tekan F12 UntukMenonaktifkan Dan Seterusya. \n4. Enjoy & Kill Have Fun :)","Tutorial Fast Killer");
		Helpfs=0;
	}

	if(Helplc)
	{
		CGameFramework::g_pFramework()->MsgBox("1. Aktivekan Zombie Killer Saat Suicide 1 Kali lagi Onkan sampai HP 00 .\n2. Aktivekan Weapon Brutal Dan Tekan Klik Kiri.\n2. Enjoy & Kill Have Fun.","Tutorial Brutal RPG");
		Helplc=0;
	}
}*/

void _fastcall Func_SetAnnounceMessage ()
{
//---------------------------------------------------// ================// 
CGameFramework::g_pFramework()->SetAnnounceMessage("|~ Selamat Datang Di Cheat VIP EliteWorld Silahakan Gunakan Keyboard Untuk Melakukan On Of Fiture Menu Semua fiture dapat digunakan Untuk mengecek Durasi Nama pembeli Resseler penjualan tersedia di fb saya fb.com/sabu43 Banned ID bukan tanggung jawab kami gunakan sebijak mungkin Jika ada notice Koneski Game Bersamalah Berarti anda memakai cheat yang sangat rusuh || secepat nya tekan F12 di keyboard agar char anda tidak melayang || Hati-hati terhadap GM yang kadang memakai char yang kadang di room tidak ada namanya Salam Admin: ZakiEliteWorld ~|");		
}
