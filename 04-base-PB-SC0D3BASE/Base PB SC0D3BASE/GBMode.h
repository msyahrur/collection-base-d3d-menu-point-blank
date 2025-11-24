#define Xx 880 //lebar
#define Yy 680 //tinggi
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

INPUT buffer[1];
DWORD Ticks,TimeReady;
DWORD Tick = NULL;

#pragma warning(disable:4551)
void MouseMoveAbsolute(DWORD Delay,INPUT *buffer, int x, int y)
{
    buffer->mi.dx = (x * (0xFFFF / SCREEN_WIDTH));
    buffer->mi.dy = (y * (0xFFFF / SCREEN_HEIGHT));
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);

    SendInput(1, buffer, sizeof(INPUT));
	mouse_event(MOUSEEVENTF_LEFTUP, Xx, Yy, 0, 0);
	keybd_event(VK_RETURN, 0x9C, KEYEVENTF_KEYUP, 0);
		if (Ticks <= GetTickCount())
			{
		        keybd_event(VK_RETURN, 0x9C, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTDOWN, Xx, Yy, 0, 0);
				Ticks = GetTickCount() + Delay;
			}

}

enum TStageGame {SERVER, CHANNEL, LOBBY, AWAITING, PLAYING };

TStageGame GetStageGame() {
	DWORD Stage = *(DWORD*)Resultg_pGameStatus;
	switch (Stage)
	{
	case 0: return SERVER; break;
	case 1: return CHANNEL; break;
	case 2: return LOBBY; break;
	case 3:
		if(IsInBattle())
			return PLAYING;
		else
			return AWAITING;
		break;
	}
}

bool Hackid(int Index)
{
	if (!pGameContext->getUserDeath(Index) && pGameContext->setMySlotIdx() != Index){
		if (pGameContext->setMySlotIdx() %2 != Index % 2){
			return true; 
		}
	}
	return false;
}

void CallGBMode()
{
	if(Other.GBMode.AutoReady)
	{
		if (GetStageGame() == AWAITING) 
		{
			switch(Other.GBMode.AutoReady)
			{
				case 1: TimeReady=500 ; break;
				case 2: TimeReady=1500; break;
				case 3: TimeReady=2500; break;
				case 4: TimeReady=3500; break;
				case 5: TimeReady=4500; break;
			}
			MouseMoveAbsolute(TimeReady,buffer, Xx, Yy);
		}
	}

	if(Other.GBMode.AutoBundir)
	{
		if(IsInBattle)
		{
			if (Tick <= GetTickCount())
      	  		{
					keybd_event(VK_4, 0x85, 0, 0);
					mouse_event(MOUSEEVENTF_LEFTDOWN, 1024, 1024, 0, 0);
					keybd_event(VK_RETURN, 0x9C, 0, 0);
					Tick = GetTickCount() + 1350 ;
				}
			else
			{
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				keybd_event(VK_4, 0x85, KEYEVENTF_KEYUP, 0);
				keybd_event(VK_RETURN, 0x9C, KEYEVENTF_KEYUP, 0);
			}
		}
	}
}