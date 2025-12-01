//----------------------------------------------------------------------------------------
//---------------------------------------------------------// [MRC]
//----------------------------------------------------------------------------------------
#include <windows.h>
#include "[MRC]CModule.h"
#include "[MRC]COffset.h"
//----------------------------------------------------------------------------------------
#define ResultGetMatrix				0x20
#define ResultGetWorld				0x12C0
#define ResultGetWorldview			0x80
#define ResultRDataContex			0x9A0
//----------------------------------------------------------------------------------------
LPD3DXLINE pLine    = NULL;
LPD3DXFONT pFonts	= NULL;
LPD3DXFONT fName	= NULL;
LPD3DXFONT fSmall	= NULL;
LPD3DXFONT Title    = NULL;
LPD3DXFONT fTime	= NULL;
LPD3DXFONT      g_pFont = NULL;
LPD3DXFONT      g_pFont2 = NULL;
LPD3DXLINE      g_Line = NULL;
LPD3DXFONT vkstring    = NULL;
LPD3DXFONT Obstring    = NULL;
LPD3DXFONT HICFontGUI = NULL;
LPDIRECT3DDEVICE9 pDevice;
D3DVIEWPORT9    g_ViewPort;
LPD3DXFONT pFont = NULL;
D3DVIEWPORT9 Viewport;
D3DXVECTOR3 vStart,vEnd;
D3DXVECTOR3 vvStart,vvEnd;
D3DXVECTOR3 vStart2,vEnd2;
D3DXVECTOR3 vvStart2,vvEnd2;
D3DXVECTOR3 vStart10,vEnd10;
D3DXVECTOR3 vvStart10,vvEnd10;
//----------------------------------------------------------------------------------------
DWORD TeamColor;
D3DVECTOR Player;
D3DVECTOR HeadPos;
D3DVECTOR PlayerScaled;
D3DVECTOR HeadScaled;
D3DVECTOR BonePos;
D3DVECTOR ScreenPos;
//----------------------------------------------------------------------------------------
class GM;
class PlayerInfo;
class RenderContext;
class RenderData;
class CGameBase;
class CBonesContext;
class CBone;
class cGameStageInfo;
//----------------------------------------------------------------------------------------
DWORD dwGFX			= (DWORD)GetModuleHandle("i3GfxDx.dll");
RenderContext *pRC	= (RenderContext*)(dwGFX + ADR_g_pRenderContext);
//----------------------------------------------------------------------------------------
class RenderData{
public:
char _0x0000[ResultGetMatrix];
D3DXMATRIX ViewMatrix;
D3DXMATRIX ProjMatrix;
char _0x00A0[ResultGetWorld];
D3DXMATRIX World;
};
//----------------------------------------------------------------------------------------
class RenderContext{
public:
RenderData* pRenderData; 
char unknown4[ResultRDataContex];
D3DXVECTOR3 bone;
D3DXVECTOR3 bone1;
D3DXVECTOR3 bone2;
};
//----------------------------------------------------------------------------------------
class Bone
{
public:
	D3DXMATRIX m_Bone;
};

class CGameCharaBoneContext
{
public:
	char nop[0x150];
	Bone* m_Bone;
};

class CGameCharaBase
{
public:
	char nop[0x558];
	CGameCharaBoneContext* m_BoneContext;
};
//----------------------------------------------------------------------------------------
struct CHealth{
float CurHP;
};
//----------------------------------------------------------------------------------------
struct CPlayers
{
	bool Layer;
    float yaw;
    float pitch;
	char unkn[0x60];
    D3DXVECTOR3 pos;
	D3DXVECTOR3 Targetpos;
};
//----------------------------------------------------------------------------------------
struct CPlayersX
{
    float yaw;
    float pitch;
    D3DXVECTOR3 pos;
    char unkno8[0x60];
};
//----------------------------------------------------------------------------------------
struct CRank{
BYTE iRank;
};
//----------------------------------------------------------------------------------------
struct CNames{
char szNames[33];
};
//----------------------------------------------------------------------------------------
class GM{
public:
BYTE iRank;
char _0x0001[15];
WORD iHack;
};
//----------------------------------------------------------------------------------------
struct CTeam{
BYTE iTeam;
};
//----------------------------------------------------------------------------------------
class CLog;
class CLog{
public:
BYTE iLog;
};
//----------------------------------------------------------------------------------------
class CDeathPlayer{
public:
BYTE Death[16];
};
//----------------------------------------------------------------------------------------
class CLocalPlayerID{
public:
BYTE ID;
};
//----------------------------------------------------------------------------------------
extern RenderContext *pRC;
//-------------------------------------------------------------------------------//
static struct key_s{
	bool bPressed;
	DWORD dwStartTime;}
kPressingKey[256];
BOOL IsKeyPressed(int Key,DWORD dwTimeOut){
	if( HIWORD( GetKeyState( Key ) ) ){
		if( !kPressingKey[Key].bPressed || ( kPressingKey[Key].dwStartTime && ( kPressingKey[Key].dwStartTime + dwTimeOut ) <= GetTickCount( ) ) ){
			kPressingKey[Key].bPressed = TRUE;
			if( dwTimeOut > NULL )
				kPressingKey[Key].dwStartTime = GetTickCount( );
			return TRUE;}}else
		kPressingKey[Key].bPressed = FALSE;
	return FALSE;}
//----------------------------------------------------------------------------------------
void  MakeJMP( BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen ){
__try {
    DWORD dwOldProtect, dwBkup, dwRelAddr;
    VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    dwRelAddr = (DWORD) (dwJumpTo - (DWORD) pAddress) - 5;
    *pAddress = 0xE9;
    *((DWORD *)(pAddress + 0x1)) = dwRelAddr;
    for(DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
    VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
    return;}__except ( EXCEPTION_EXECUTE_HANDLER ) {
	return ;}}
//----------------------------------------------------------------------------------------
void LongPtr ( DWORD adress, DWORD offset, DWORD offset2, int Value ){
	__try{
		DWORD OldPtr;
		OldPtr = *(PDWORD)((DWORD)adress) + offset;
		OldPtr = *(PDWORD)((DWORD)OldPtr) + offset2;
		*(int*)(OldPtr) = Value;}
	__except (EXCEPTION_EXECUTE_HANDLER){}}
//----------------------------------------------------------------------------------------
void _WriteMEM(DWORD Adr, DWORD Ptr1, DWORD Ptr2, DWORD Ptr3, DWORD WriteValue){
	DWORD Temp=0;
	if (IsBadReadPtr((PDWORD)Adr, 4) == 0){ 
		Temp = *(PDWORD)((DWORD)(Adr)) + Ptr1;
		if (IsBadReadPtr((PDWORD)Temp,4) == 0){ 
			Temp = *(PDWORD)((DWORD)(Temp)) + Ptr2;
			if (IsBadReadPtr((PDWORD)Temp,4) == 0){ 
				Temp = *(PDWORD)((DWORD)(Temp)) + Ptr3;
				if (IsBadReadPtr((PDWORD)Temp,4) == 0){
					*(PDWORD)Temp = WriteValue;
				}}}}}
//----------------------------------------------------------------------------------------
void MemWrite(void *adr, void *byte, int size){
	DWORD X;
    VirtualProtect(adr, size, PAGE_EXECUTE_READWRITE, &X);
	memcpy(adr, byte, size);   
    VirtualProtect(adr,size,X,&X);}
//----------------------------------------------------------------------------------------
int WritePtr (unsigned long ads, unsigned long ptr, int value){
	__try{
		unsigned long WrtPointer = false;
		WrtPointer = *(unsigned long*)((ads))+ptr;
		*(int*)(WrtPointer) = value;
		return true;}
	__except (EXCEPTION_EXECUTE_HANDLER){
		return false;}}
//----------------------------------------------------------------------------------------
BYTE Weapon,Pistol,Knife,Bomb,Smoke,Dual;
void __ReadMem(DWORD Base,DWORD Ofs1,DWORD Ofs2, DWORD Ofs3, int opt){
	DWORD Temp =0;
	if (IsBadReadPtr((PDWORD)Base,4)==0){
		Temp=*(PDWORD)((DWORD)(Base))+Ofs1;
		if (IsBadReadPtr((PDWORD)Temp,4)==0){
			Temp=*(PDWORD)((DWORD)(Temp))+Ofs2;
			if (IsBadReadPtr((PDWORD)Temp,4)==0){
				Temp=*(PDWORD)((DWORD)(Temp))+Ofs3;
				if (IsBadReadPtr((PDWORD)Temp,4)==0){
					switch (opt){
					case 1:Weapon = *(PBYTE)Temp;
					case 2:Pistol = *(PBYTE)Temp;
					case 3:Knife = *(PBYTE)Temp;
					case 4:Bomb = *(PBYTE)Temp;
					case 5:Smoke = *(PBYTE)Temp;
					case 6:Dual = *(PBYTE)Temp;
					}}}}}}
//----------------------------------------------------------------------------------------
void PrivateOnly(void *adr, void *ptr, int size){ 
	DWORD NextProtection;
	VirtualProtect(adr,size,PAGE_EXECUTE_READWRITE, &NextProtection);
	Sleep(1);
	Sleep(1);
	RtlCopyMemory(adr,ptr,size);
	Sleep(1);
	Sleep(1);
	VirtualProtect(adr,size,NextProtection, &NextProtection);}
//----------------------------------------------------------------------------------------
DWORD _ReadMEM(DWORD dwPtr,DWORD A1,DWORD B1,DWORD C1){
	DWORD C=0;
	if (IsBadReadPtr((PDWORD)dwPtr,4)==0){
		C=*(PDWORD)((DWORD)(dwPtr))+A1;
		if (IsBadReadPtr((PDWORD )C,4)==0){
			C=*(PDWORD)((DWORD)(C ))+ B1;
			if (IsBadReadPtr((PDWORD)C,4)==0){
				C=*(PDWORD)((DWORD)(C ))+ C1;
				if (IsBadReadPtr((PDWORD)C,4)==0){
					return *(PDWORD)C; 
				}}}}
	return C;}
//----------------------------------------------------------------------------------------
void Hooked(PDWORD target, PDWORD newfunc){
	DWORD Jmpto=(DWORD)(newfunc)-(DWORD)target-5;
	DWORD a;
	VirtualProtect(target, 8, PAGE_EXECUTE_READWRITE, &a);
	*(PBYTE)(target)=0xE9;
	*(PDWORD)((DWORD)(target)+1)=Jmpto;
	VirtualProtect(target, 8, a, &a);}
//----------------------------------------------------------------------------------------
DWORD ReadFunct(DWORD dwPtr, DWORD dwOfs){ 
DWORD C; 
if(IsBadReadPtr((PDWORD)(dwPtr),4)==0){ 
C=*(PDWORD)((DWORD)(dwPtr))+dwOfs; 
if(IsBadReadPtr((PDWORD)(C),4)==0){ 
return *(PDWORD)C; 
}
}
return C;
}
//----------------------------------------------------------------------------------------
DWORD MakePTR(BYTE *MemoryTarget, DWORD FunctionTarget)
{
	DWORD dwOldProtect,dwBkup;
	DWORD dwRetn = *(DWORD*)(MemoryTarget);

	VirtualProtect(MemoryTarget, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*((DWORD *)(MemoryTarget)) = FunctionTarget;
	VirtualProtect(MemoryTarget, 4, dwOldProtect, &dwBkup);
	return dwRetn;
}
//----------------------------------------------------------------------------------------
DWORD Read(DWORD dwPtr, DWORD dwOfs)
{ 
	DWORD C; 
	if(IsBadReadPtr((PDWORD)(dwPtr),4)==0){ 
		C=*(PDWORD)((DWORD)(dwPtr))+dwOfs; 
		if(IsBadReadPtr((PDWORD)(C),4)==0){ 
			return *(PDWORD)C; 
		} 
	} 
	return C;
}
//----------------------------------------------------------------------------------------
bool MakePoint(unsigned long ADRexec, int OFSexec, int PTRexec){
	if (!IsBadReadPtr((void*)ADRexec, sizeof(unsigned long))){
		if (!IsBadReadPtr((void*)(*(unsigned long*)ADRexec + OFSexec), sizeof(unsigned long))){
			*(int*)(*(unsigned long*)ADRexec + OFSexec) = PTRexec;
		}
	}
	return 0;
}
//----------------------------------------------------------------------------------------
void PacthHook(void *adr, void *ptr, int size)
{
	DWORD CheckProtection = 0;
	VirtualProtect(adr,size,PAGE_EXECUTE_READWRITE, &CheckProtection);
	RtlMoveMemory(adr,ptr,size);
	VirtualProtect(adr,size,CheckProtection, &CheckProtection);
}
DWORD FindDmaAddy(int PointerLevel, DWORD Offsets[], DWORD BaseAddress) {
DWORD Ptr = *(DWORD*)(BaseAddress);
if(Ptr == 0) return NULL;
for(int i = 0; i < PointerLevel; i ++)
{
if(i == PointerLevel-1)
{
Ptr = (DWORD)(Ptr+Offsets[i]);
if(Ptr == 0) return NULL;
return Ptr;
}
else
{
Ptr = *(DWORD*)(Ptr+Offsets[i]);
if(Ptr == 0) return NULL;
}
}
return Ptr;
}
void  VersiLongKnife( BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen )
{
__try {
    DWORD dwOldProtect, dwBkup, dwRelAddr;
    VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    dwRelAddr = (DWORD) (dwJumpTo - (DWORD) pAddress) - 5;
    *pAddress = 0xE9;
    *((DWORD *)(pAddress + 0x1)) = dwRelAddr;
    for(DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
    VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);
    return;
}__except ( EXCEPTION_EXECUTE_HANDLER ) {
	return ;
}}
void XwhriteX (void *adr, void *ptr, int size)
{
DWORD CheckProtection = 0;
VirtualProtect(adr, size, PAGE_EXECUTE_READWRITE, &CheckProtection);
RtlMoveMemory(adr, ptr, size);
VirtualProtect(adr, size, CheckProtection, &CheckProtection);
}
//----------------------------------------------------------------------------------------
//---------------------------------------------------------// [MRC]
//----------------------------------------------------------------------------------------