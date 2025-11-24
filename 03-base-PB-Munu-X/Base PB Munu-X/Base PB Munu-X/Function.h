//--------------------------------------------------------------------------//
#include "AdressLog.h"
//--------------------------------------------------------------------------//
LPDIRECT3DDEVICE9 pDevice;
LPDIRECT3DDEVICE9 pGDevice = NULL;
//--------------------------------------------------------------------------//
class RenderContext;
RenderContext *pRC	= (RenderContext*)(HookBaseRender);
//--------------------------------------------------------------------------//
void UknownScript(PDWORD target, PDWORD newfunc){
DWORD Jmpto=(DWORD)(newfunc)-(DWORD)target-5;
DWORD a;
VirtualProtect(target, 8, PAGE_EXECUTE_READWRITE, &a);
*(PBYTE)(target)=0xE9;
*(PDWORD)((DWORD)(target)+1)=Jmpto;
VirtualProtect(target, 8, a, &a);
}
//--------------------------------------------------------------------------//