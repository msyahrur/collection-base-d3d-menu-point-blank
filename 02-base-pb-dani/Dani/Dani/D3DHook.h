//Created by DANI XCT / WA DANI IDI/MENU XXN PART 2
#define StartRoutine(Function) CreateThread(0,0,(LPTHREAD_START_ROUTINE)Function,0,0,0);
DWORD pEndScene;
int cInit = 0;
_declspec(naked)void hkEndRender()
{
	__asm {
		mov eax,[ecx+0x53A8]
		mov ecx,[eax]
		mov edx,[ecx+0xA8]
		mov [pEndScene],edx
		cmp [cInit],0
		je InitES
		cmp [cInit],1
		je Normal
		cmp [cInit],2
		je ReInitES
InitES:
        push eax
		call hkEndScene
		mov [cInit],1
		retn
Normal:
        push eax
        call edx
		mov [cInit],2
		retn
ReInitES:
		push eax
		call hkEndScene
        retn           
	}
}

DWORD GetOriginalEndScene()
{
	return pEndScene;
}

void ThreadHook()
{
	MakePTR((PBYTE)AddyEngine->GetAddyValueByKey("XFHPB.Import.i3RenderContext::EndRender"),(DWORD)hkEndRender);
}