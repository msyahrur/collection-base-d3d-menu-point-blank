//Created by DANI XCT / WA DANI IDI/MENU XXN PART 2
bool IsInBattle()
{
	if(pGameCharaManager->getLocalChara() > NULL)return true;
	return false;
}

bool IsAliveDeath(int Index)
{
	if (!pGameContext->getUserDeath(Index) && pGameContext->getMySlotIdx() != Index){
		if (pGameContext->getMySlotIdx() %2 != Index % 2){
			return true; 
		}
	}
	return false;
}

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

TStageGame GetStageGame()
{
	DWORD Stage = *(DWORD*)AddyEngine->GetAddyValueByKey("GameStatus.Base");
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

TSlotWeapon GetSlotWeapon()
{
	int Slot = (int)pGameCharaBase->getGameCharaWeaponContext()->getCurrentWeaponIndex();
	switch (Slot) 
	{
		case 0: return Primary; break;
		case 1: return Secondary; break;
		case 2: return Melle; break;
		case 3: return Explosive; break;
		case 4: return Special; break;
		case 5: return ExplosiveC4; break;
		case 6: return Teuapal; break;
	}
}

struct _WeaponValue
{
	DWORD Value;
	_WeaponValue(DWORD dwValue)
	{
		this->Value = dwValue;
	}
	signed int WeaponSlot()
	{
		return (this->Value % 100000000 / 1000000);
	}
	signed int WeaponType()
	{
		return (this->Value % 1000000 / 1000);
	}
	signed int WeaponIndex()
	{
		return (this->Value % 1000);
	}
};

DWORD GetPlayerTarget(int Index)
{
	CGameCharaBase* pTarget = pGameCharaManager->getCharaByNetIdx(Index);
	if (pTarget->getGameCharaCollisionContext() && pTarget->getGameCharaCollisionContext()->getCrossHairTarget())
	{
		return pTarget->getGameCharaCollisionContext()->getCrossHairTarget();
	}
	return NULL;
}

DWORD MakePTR(BYTE *MemoryTarget, DWORD FunctionTarget)
{
	DWORD dwOldProtect,dwBkup;
	DWORD dwRetn = *(DWORD*)(MemoryTarget);

	VirtualProtect(MemoryTarget, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*((DWORD *)(MemoryTarget)) = FunctionTarget;
	VirtualProtect(MemoryTarget, 4, dwOldProtect, &dwBkup);
	return dwRetn;
}

inline void MakeJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen)
{
    DWORD dwOldProtect, dwBkup, dwRelAddr;
	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	dwRelAddr = (DWORD)(dwJumpTo - (DWORD)pAddress) - 5;
	*pAddress = 0xE9;
	*((DWORD *)(pAddress + 0x1)) = dwRelAddr;
	for (DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
	return;
}

void _patchMEM(void* MemoryTarget, char* Value,int len)
{
	DWORD dwOldProtect, dwBkup;
    VirtualProtect(MemoryTarget, len, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	memcpy((void*)MemoryTarget,(void*)Value,len);
    VirtualProtect(MemoryTarget, len, dwOldProtect, &dwBkup);
}

void _patchMEM(void *Addres, int Byte)
{
	__try {
		DWORD OldProtect;
		VirtualProtect(Addres, Byte, PAGE_EXECUTE_READWRITE, &OldProtect);
		*(BYTE*)Addres=Byte;
		VirtualProtect(Addres, Byte, PAGE_EXECUTE_READWRITE,&OldProtect);
	}__except (EXCEPTION_EXECUTE_HANDLER){} 
}

void hexDump (char *desc, void *addr, int len, FILE* pFile) {
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;
    if (desc != NULL)
        fprintf (pFile, "%s:\n", desc);
    for (i = 0; i < len; i++) {
        if ((i % 16) == 0)
		{
            if (i != 0)
                fprintf (pFile, "  %s\n", buff);
            fprintf (pFile, "  %04x ", i);
        }
        fprintf (pFile, " %02x", pc[i]);
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }
    while ((i % 16) != 0) {
        fprintf (pFile, "   ");
        i++;
    }
    fprintf (pFile, "  %s\n", buff);
}

string hexDump (char *desc, void *addr, int len) {
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;
	char szPrntBuffer[100];
	string output;
	if(IsBadReadPtr((void*)addr,4))
	{
		sprintf (szPrntBuffer,"%s: 0x0", desc);
		output += szPrntBuffer;
		return output;
	}
    if (desc != NULL){
        sprintf (szPrntBuffer,"%s:\n", desc);
		output += szPrntBuffer;
	}
    for (i = 0; i < len; i++)
	{
        if ((i % 16) == 0)
		{
            if (i != 0){
                sprintf (szPrntBuffer,"  %s\n", buff);
				output += szPrntBuffer;
			}
            sprintf (szPrntBuffer,"  %08X ", (int)addr + i);
			output += szPrntBuffer;
        }
        sprintf (szPrntBuffer," %02x", pc[i]);
		output += szPrntBuffer;
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }
    while ((i % 16) != 0) {
        sprintf (szPrntBuffer,"   ");
		output += szPrntBuffer;
        i++;
    }
    sprintf (szPrntBuffer,"  %s", buff);
	output += szPrntBuffer;
	return output;
}

void *DetourFunction (BYTE *src, const BYTE *dst, const int len)
{
    BYTE *jmp;
    DWORD dwback;
    DWORD jumpto, newjump;

    VirtualProtect(src,len,PAGE_READWRITE,&dwback);
    
    if(src[0] == 0xE9)
    {
        jmp = (BYTE*)malloc(10);
        jumpto = (*(DWORD*)(src+1))+((DWORD)src)+5;
        newjump = (jumpto-(DWORD)(jmp+5));
        jmp[0] = 0xE9;
       *(DWORD*)(jmp+1) = newjump;
        jmp += 5;
        jmp[0] = 0xE9;
       *(DWORD*)(jmp+1) = (DWORD)(src-jmp);
    }
    else
    {
        jmp = (BYTE*)malloc(5+len);
        memcpy(jmp,src,len);
        jmp += len;
        jmp[0] = 0xE9;
       *(DWORD*)(jmp+1) = (DWORD)(src+len-jmp)-5;
    }
    src[0] = 0xE9;
   *(DWORD*)(src+1) = (DWORD)(dst - src) - 5;

    for(int i = 5; i < len; i++)
        src[i] = 0x90;
    VirtualProtect(src,len,dwback,&dwback);
    return (jmp-len);
}
