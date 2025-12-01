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
//==============================================================================================================================================
char PointBlankSTR[100];
DWORD LAmmo = NULL;

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
				if(GetKeyboardPressState(DIK_R)){
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
	pGetLocalTime = (tGetLocalTime)MakePTR((PBYTE)AddyEngine->GetAddyValueByKey(/*XFHPB.Import.i3AiContext::getLocalTime*/XorStr<0x4C,39,0xB4791064>("\x14\x0B\x06\x1F\x12\x7F\x1B\x3E\x24\x3A\x24\x23\x76\x30\x69\x1A\x35\x1E\x31\x31\x14\x04\x1A\x17\x5E\x5F\x01\x02\x1C\x25\x05\x08\x0D\x01\x3A\x06\x1D\x14"+0xB4791064).s),(DWORD)hkGetLocalTime);
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
	if(bHookedTele)return;
	SetEndVector = new pSetEndVector();
	pSetEnd = MakePTR((PBYTE)AddyEngine->GetAddyValueByKey(/*XFHPB.Import.i3CollideeLine::SetEnd*/XorStr<0xEE,36,0xA8B55D96>("\xB6\xA9\xB8\xA1\xB0\xDD\xBD\x98\x86\x98\x8A\x8D\xD4\x92\xCF\xBE\x91\x93\x6C\x68\x66\x66\x61\x49\x6F\x69\x6D\x33\x30\x58\x69\x79\x4B\x61\x74"+0xA8B55D96).s),(DWORD)hkSetEnd);
	bHookedTele = true;
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
