//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
DWORD ModifyTargetBase[100] = {0};
typedef float (__thiscall * tGetLocalTime)(DWORD Base);
tGetLocalTime pGetLocalTime;
float __fastcall hkGetLocalTime(DWORD Base){

	float retVal = pGetLocalTime(Base);
	for(int i = 0; i < 100; i++)
	{
		if(ModifyTargetBase[i] > NULL && ModifyTargetBase[i] == Base){
			if(i == 0)retVal = 2.519999862f;
			if(i == 1 || i == 2){
				if(GetAsyncKeyState(VK_R)){
					__asm {
						lea edx,retVal
						mov [edx + 3],0x41
					}
				}
			}
			break;
		}
	}
	return retVal;
}

bool bHookedLT = false;
void HookLocalTime()
{
if(bHookedLT)return;
	pGetLocalTime = (tGetLocalTime)MakePTR((PBYTE)AddyEngine->GetAddyValueByKey("XFHPB.Import.i3AiContext::getLocalTime"),(DWORD)hkGetLocalTime);
	bHookedLT = true;
}

DWORD pSetEnd;
_declspec(naked) void hkSetEnd(){
	__asm 
	{
		sub esp, 0x8
		push esi
	}
	DWORD dwOrigLine;
	__asm
	{
		mov eax,[esp + 0x10];
		mov [dwOrigLine],eax
	}
	dwOrigLine = SetEndVector->GetSetEndVector(dwOrigLine);
	__asm
	{
		mov eax,[dwOrigLine];
		mov [esp + 0x10],eax
	}
	__asm 
	{
		pop esi
		add esp, 0x8
	}
	__asm jmp pSetEnd;
}

bool bHookedTele = false;
void HookSetEnd()
{
	SetEndVector = new pSetEndVector();
	if(bHookedTele)return;
	pSetEnd = MakePTR((PBYTE)AddyEngine->GetAddyValueByKey("XFHPB.Import.i3CollideeLine::SetEnd"),(DWORD)hkSetEnd);
	bHookedTele = true;
}

float LongJumperDist;
bool JumperDist = false;
bool JumperDist2 = false;
DWORD pUpdateJumpJMP;
_declspec (naked) void JumperThread()
{
	if (JumperDist == true)
	{
		__asm
		{
			fld dword ptr[LongJumperDist]
				mov esp, ebp
				jmp dword ptr[pUpdateJumpJMP]
		}
	}
	__asm
	{
		fld dword ptr[ebp - 04]
			mov esp, ebp
			jmp dword ptr[pUpdateJumpJMP]
	}
}

void HookJumpHight()
{
	pUpdateJumpJMP = AddyEngine->GetAddyValueByKey("XFHPB.Function.UpdateJumpJMP");
	MakeJMP((PBYTE)AddyEngine->GetAddyValueByKey("XFHPB.Function.UpdateJumpX"), (DWORD)JumperThread, 5);
}

DWORD HookAutoMacro(void)
{
	while(true)
	{
		if(Feature.Weapon.AutoMacro)
		{
			if(GetSlotWeapon() == Primary)
			{
				if(pGameFramework->geti3InputMouse()->GetButtonState() == 1)
				{
					keybd_event(0x33, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
					{
						Sleep(50);
					}
						keybd_event(0x33, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
						keybd_event(0x31, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
					{
						Sleep(50);
					}
					keybd_event(0x31, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				}
			}
		}
		Sleep(50);
	}
	return false;
}

void MouseMoveAbsolute(DWORD Delay,INPUT *buffer, int x, int y)
{
    buffer->mi.dx = (x * (0xFFFF / SCREEN_WIDTH));
    buffer->mi.dy = (y * (0xFFFF / SCREEN_HEIGHT));
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);

    SendInput(1, buffer, sizeof(INPUT));
	mouse_event(MOUSEEVENTF_LEFTUP, Xx, Yy, 0, 0);
	keybd_event(VK_RETURN, 0x9C, KEYEVENTF_KEYUP, 0);
	if(Ticks <= GetTickCount())
	{
		keybd_event(VK_RETURN, 0x9C, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTDOWN, Xx, Yy, 0, 0);
		Ticks = GetTickCount() + Delay;
	}
}

void __fastcall hkSetEvent(void *p, void *Unknown, int a1, const void* a2, const void* a3,const void* a4, const char* a5, int a6)
{
	if(DebugMode == true)
	{
		sprintf(LastEvent, "void __thiscall CGameContext::SetEvent(int, const void*, const void*,const void*, const char*, int)\na1: 0x%X\n%s\n%s\n%s\n%s\na6: 0x%X", a1, hexDump("a2", (void*)a2, 0x20).c_str(), hexDump("a3", (void*)a3, 0x20).c_str(), hexDump("a4", (void*)a4, 0x20).c_str(), hexDump("a5", (void*)a5, 0x20).c_str(), a6);
		myFunctionLog << LastEvent << endl;
	}

	if(Feature.Player.Shield)
	{
		if(a1 == 0x97)
		{
			return;
		}
	}
	return oSetEvent(p, a1, a2, a3, a4, a5, a6); 
}

void __fastcall HookSetEvent()
{
	__try{
		oSetEvent = (tSetEvent)DetourFunction((PBYTE)(AddyEngine->GetAddyValueByKey("GameContext.Function.setEvent")),(PBYTE)hkSetEvent,10);
	}__except (EXCEPTION_EXECUTE_HANDLER){}
}