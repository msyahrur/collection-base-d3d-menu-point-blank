// Source PointBlank Hacks By ZeRo-CyBeRz Hacks [www.zero-cyberz-server.com]
// D3D Menu By UC Forum [www.unknowncheats.me] || Last Edit By Y.L.A.S
//===============================================================//
#pragma warning (disable:4099)


//#include "CGameOFS.h"
int suicideplayers;
LPD3DXFONT pFonts	= NULL;
LPD3DXFONT fName	= NULL;
ID3DXFont*  pFont2;
ID3DXSprite* textSprite;
DWORD TeamColor;
#include "StandardIncludes.h"
//#pragma once using namespace std;
//__declspec( selectany ) D3DVIEWPORT9 ViewPort;
DWORD FindPattern( DWORD dwStart, DWORD dwLen, BYTE* pszPatt, char pszMask[]){ 
unsigned int i = NULL; 
int iLen = strlen( pszMask ) - 1; 
for( DWORD dwRet = dwStart; dwRet < dwStart + dwLen; dwRet++ ){ 
if( *(BYTE*)dwRet == pszPatt[i] || pszMask[i] == '?' ){ 
if( pszMask[i+1] == '\0' ) return( dwRet - iLen ); i++; 
} 
else i = NULL; 
}
return NULL; 
}

ofstream infile;
char dlldir[320];
char *GetDirectoryFile(char *filename)
{
static char path[320];
strcpy(path, dlldir);
strcat(path, filename);
return path;
}
//
//
////--------------------------------------------------------------------
//DWORD TreidxBone,TreBoneContext,SetCurHP,GetNickForSlotss;
//DWORD ResultBalatitanium,ResultRpgKiller;
////66 8B 45 FC 8B E5 5D C3
////-------------------------------------------------------------------
//
///*addres*/DWORD ResultBasePlayer,Resultj,ResultNames,ResultTester,Resultvotekik,ResulVo,ResultBas,ResultBasePlayer2,ResultBaseHealth,ResultBaseHealth2,ResultBaseAmmo,ResultBaseAmmo2,ResultBullet,ResultBugWeapon;
///*PTR*/   DWORD ResultTeam,Resultvokx,ResultT,OFSSkill,ResultName,ResultBone,ResultHealth,ResultPlayer,ResultRANK1,ResultRANK2,ResultRESPAWN,ResultPing,ResultSkill2,ResultKill,ResultScore;
//          DWORD ResultQuick,ResultPlayerMove,ResultAVK,ResultBastp,WTF,ResultPTRAmmo,ResultNorecoil,ResultRespanw,ResultTarget,ResultPTRTarget,ResultGetButton,ResultFallDamage,ResultRafidFire,ResultRafidFire2,ResultReRespawn;
///*Other*/ DWORD ResultDoLine,ResultBss,ResultCamPos ,ResultB,ResultEventFire,ResultSuicide;
//          DWORD ResultPrimary,ResultWallShot,ResultLongKnife,ResultRETLongKnife,ResultSetEvent,PTR_Player,ResultSecondary,ResultMelle,ResultSmoke,ResultExplosive;
///*Hook*/  DWORD ResultBaseAddress,ResultHook,ResultPTRRecoil,ResultBaseIdle2,PTR_Idle,PTR_Idle2,ResultPTRIdle,ResultPlayerSpeed,ResultFireSpeed,RETNeoFireSpeed;
////--------------------------------------------------------------------
//void  unk(void *adr, void *ptr, int size)
//{
//
//	DWORD NextProtection;
//	VirtualProtect(adr, size, PAGE_EXECUTE_READWRITE, &NextProtection);
//	RtlMoveMemory(adr, ptr, size);
//	VirtualProtect(adr, size, NextProtection, &NextProtection);
//}
//
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
void __cdecl Writelog (const char *fmt, ...)
{
if(infile != NULL)
{
if(!fmt) { return; }
va_list va_alist;
char logbuf[256] = {0};
va_start (va_alist, fmt);
_vsnprintf (logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), fmt, va_alist);
va_end (va_alist);
infile << logbuf << endl;
}
}
//
//struct cFun
//{
//	int AutoGO;
//	int FastBomb;
//	int NoFallDamage;
//	int TrocaRapida;
//	int SuperAim;
//	int AutoUP;
//	int AimKey;
//	int AimLocal;
//	int SuperAimbot;
//};
//
//cFun Fun;
//
//DWORD SetAwayInputTime1X ;
//DWORD SetAwayInputTime2X ;
//
DWORD ResultTeam,TeamOffset;
DWORD DWRecoilHoriz = ((*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("PointBlank.exe") + 0xC02A4) + 0x6F4) + 0x704) + 0x7C) + 0x72C) + 0x2B0));



DWORD DWTeam = ((*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3FrameworkDx.dll") + 0x299830) + 0xB8) + 0x108) + 0x20) + 0x133C) + 0xDE4));

DWORD ResultRecoilHorz,ResultRecoilVert,ResultGetOneHorz,ResultGetOneVert;
void Bagus_Updater(void){
		Sleep(1000);
//--------------------------------------------------------------------
		
DWORD ScanRecoilHroz = FindPattern(DWRecoilHoriz,0x5B83A4,(PBYTE)"\x34\x02\x00\x00\x8D\x4C\x24\x34\x83\xC4\x20\xC7\x84\x24\x2C\x02\x00\x00\xFF\xFF\xFF\xFF\x3B\xC1\x74\x0F\x8B\x94\x24\x1C\x02\x00\x00\x42\x52\x50\xE8\x7B\x97","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
DWORD ScanTeam = FindPattern(DWTeam,0x66534A,(PBYTE)"\x68\x8D\x04\x00\x00\x6A\x00","xxxxxxx");

//--------------------------------------------------------------------

//8EBEAFE int __thiscall WeaponBase::GetOneHorzEnable(class CWeaponInfo
//8EBE9BE int __thiscall WeaponBase::GetOneVertEnable(class CWeaponInfo 

//8EBEC5C
//ResultRecoilHorz = ScanRecoilHroz;
//ResultRecoilVert  = ResultRecoilHorz + 0x142;
//ResultGetOneHorz  = ResultRecoilHorz - 0x15E;
//ResultGetOneVert = ResultRecoilHorz - 0x29E;

ResultTeam = ScanTeam + 0x66;
		Writelog("//------------------------------------------------------------------------//");
		Writelog("\tLogger All PointBlank Kaybo Revolution By @Ga-Latino 2018");
		Writelog("\tAssembly|Address|Call|Pointer|Size >> Encrypted By FC- Striker");
		Writelog("\tSystem Enginer PointBlank Revolution >> Decrypted By Neil");
		Writelog("//------------------------------------------------------------------------//");
  /*      Writelog("#define CGameCharaBase.Function.RecoilHorz		0x%X", ResultRecoilHorz);
	    Writelog("#define CGameCharaBase.Function.RecoilVert		0x%X", ResultRecoilVert);
		Writelog("#define CGameCharaBase.Function.GetOneHorzEnable		0x%X", ResultGetOneHorz);
		Writelog("#define CGameCharaBase.Function.ResultGetOneVert		0x%X", ResultGetOneVert);*/
		Writelog("#define CGameCharaBase.Function.ResultTeam		0x%X", ResultTeam);
		

		//G_Player lOCAL -> 39 5C 24 ?? 0F 85 ?? ?? ?? ?? 53 68 ?? ?? ?? ?? 68 ?? ?? ?? ??  53 FF 15 ?? ?? ?? ?? 8D 4C 24 34 89 8C 24 34 02 00 00 89 9C 24 38 02 00 00 C7 84 24 3C 02 00 00 FF 01 00 00 88 5C 24 34 68
	}
////--------------------------------------DECLARATIONES PBKAYBO  -------------------------//
//int ESPBone,CH_ESPB3D,EspHealth,ESPName,ESPLine,EspLine;
//int fly,suicideplayer,TrocaRapida1,NoFallDamage,fasfire,NoRecoilHROZ,NoRecoil,Respanw,NoRecargar,exitgamedeclaration,Blogcheats;
//int HackSpeed = 0;
D3DVIEWPORT9 Viewport;
//
////--------------------------------------ADDRES PBKAYBO ESP BASE PLAYER -------------------------//
//#define PTR_TEAM            0x17E24//6A 00 FF D3 8D 85 E0 FD FF FF C7 45 E8 FF 01 00 00 89 45 E0 33 C0
//
//DWORD  c_pCharaManager = (*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3SceneDx.dll") + 0x242488) + 0x109C) + 0x694) + 0x2A0) + 0xB34) + 0x0);//CMP/8B 8D 3C FF FF FF 8B 85 40 FF FF FF 03 C1 89 4D E8 89 45 EC 8D 45 E8 50 // - 7BC= GameContext
////
//DWORD c_pGameContext =(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3FrameworkDx.dll") + 0x3078AC) + 0x52C) + 0x4D4) + 0x25C) + 0xB38) + 0x0); /*(c_pCharaManager - 0x7BC)*/;
////
////DWORD g_pBattleSlotContextAddres = (*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3FrameworkDx.dll") + 0x304570) + 0x4) + 0x1BC) + 0x64) + 0xA8) + 0x0);
////DWORD getCurHP_Realoi = 0x0744C4C3; //53 33 DB 53 68 ?? ?? ?? ?? 68 3A 01 00 00 53
////	
////
////
////
//DWORD c_pPlayer = (/*(DWORD*)*/*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3FrameworkDx.dll") + 0x207D6C) + 0x714) + 0x136C) + 0x1348) + 0x300) + 0x130);
////void __thiscall UIHudMultiWeapon::ShowMultiWeaponSlot(bool)
////
//#define GetCharaByNetId2(slotIdx)	  *(DWORD*)(*(DWORD*)(c_pCharaManager) + 0x14 + (0xE0 * slotIdx))
//
////
//class CGameCharaBoneContext
//{
//public:
//	D3DMATRIX* getArrayBones()
//	{
//		return ((D3DMATRIX* (__thiscall*)(DWORD))TreidxBone)((DWORD)this + 0x1F8);
//	}
//
//	CGameCharaBoneContext* getBoneContext()
//	{
//		return ((CGameCharaBoneContext* (__thiscall*)(CGameCharaBoneContext*))TreBoneContext)(this + 0X268);
//	}
//};
//
//
//class CBattleSlotContextName {
//public:
//    char* GetNickForSlot(int iSlot) {
//        DWORD bufferType;
//        auto Func = (void(__thiscall*)(CBattleSlotContextName*, DWORD*, int))GetNickForSlotss;
//        Func(this, &bufferType, iSlot);
//        return (char*)(bufferType + 0x8);
//    }
// 
//    static CBattleSlotContextName* Singleton2() {
//        return (CBattleSlotContextName*)(*(DWORD*)(c_pGameContext)); 
//	} }
//	;
//
//
//bool GetUserBone(D3DXVECTOR3 &Out, int BoneIndex, int index)
//{
//	CGameCharaBoneContext* g_pCharaBase = (CGameCharaBoneContext*)( *(DWORD*)(*(DWORD*)(c_pCharaManager) + 0x14 + (index * 0xE0)) );
//	if (g_pCharaBase!=0)
//	{
//		D3DMATRIX Bone = g_pCharaBase->getBoneContext()->getArrayBones()[BoneIndex];
//		Out.x = Bone._41;
//		Out.y = Bone._42;
//		Out.z = Bone._43;
//		return true;
//	}
//	return false;
//}
// bool GetUserBone2(D3DXVECTOR3 &Out, int index, int BoneIndex)
//	{
//		__try
//		{
//			CGameCharaBoneContext* g_pCharaBase = (CGameCharaBoneContext*)( *(DWORD*)(*(DWORD*)(c_pCharaManager) + 0x14 + (index * 0xE0)) );
//	if (g_pCharaBase!=0)
//	{
//				/*Out.x = this->GetCharaByNetIdx(iSlot)->m_pBoneContext()->m_Bone()[getBoneIndex]._41;
//				Out.y = this->GetCharaByNetIdx(iSlot)->m_pBoneContext()->m_Bone()[getBoneIndex]._42;
//				Out.z = this->GetCharaByNetIdx(iSlot)->m_pBoneContext()->m_Bone()[getBoneIndex]._43;*/
//
//				Out.x = *(float*)((DWORD)(g_pCharaBase->getBoneContext()->getArrayBones()) + 0x30 + (0x40 * BoneIndex));
//				Out.y = *(float*)((DWORD)(g_pCharaBase->getBoneContext()->getArrayBones()) + 0x34 + (0x40 * BoneIndex));
//				Out.z = *(float*)((DWORD)(g_pCharaBase->getBoneContext()->getArrayBones()) + 0x38 + (0x40 * BoneIndex));
//				return true;
//			}
//			return false;
//		}
//		__except (EXCEPTION_EXECUTE_HANDLER){ return false; }
//	}
//class i3RenderContext {
//public:
//	char _0x0000[0x53D4];// i3RenderContext::EndRender
//	IDirect3DDevice9* pDevice;
//	D3DXMATRIX* GetProjectMatrix() {
//		return ((D3DXMATRIX*(__thiscall*)(i3RenderContext*))(GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetProjectMatrix@i3RenderContext@@QAEPATMATRIX@@XZ")))(this);
//	}
//	D3DXMATRIX* GetWorldMatrix() {
//		return ((D3DXMATRIX*(__thiscall*)(i3RenderContext*))(GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetWorldMatrix@i3RenderContext@@QAEPATMATRIX@@XZ")))(this);
//	}
//	D3DXMATRIX* GetViewMatrix() {
//		return ((D3DXMATRIX*(__thiscall*)(i3RenderContext*))(GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetViewMatrix@i3RenderContext@@QAEPATMATRIX@@XZ")))(this);
//	}
//
//	static i3RenderContext* Singleton()
//	{
//		return (i3RenderContext*)(*(DWORD*)(GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?g_pRenderContext@@3PAVi3RenderContext@@A")));
//	}
//};
////
//////@@@@@@@@@@@@@@@@@@@@@@@ Verificação in game @@@@@@@@@@@@@@@@@@@@@@@@
//DWORD g_pGameStatus = (*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3FrameworkDx.dll") + 0x307890) + 0x4) + 0x2C) + 0x160) + 0x9C4) + 0x320);
//
//enum TStageGame { SERVER, CHANNEL, LOBBY, AGUARDANDO, JOGANDO };
//TStageGame getStageGame() {
//	DWORD Stage = *(DWORD*)g_pGameStatus;//8B 75 D8 8B C3 C1 E0 02 8B CF 8B 36 03 F0
//	switch (Stage)
//	{
//	case 0: return SERVER; break;
//	case 1: return CHANNEL; break; 
//	case 2: return LOBBY; break;
//	case 3:
//		if (*(DWORD*)c_pPlayer != 0x0)
//			return JOGANDO;
//		else
//			return AGUARDANDO;
//		break;
//	}
//}
//int Cross;
//#pragma once using namespace std;
// D3DVIEWPORT9 ViewPort;
////*---------------------------------------- Declaration FillRGB ----------------------------------------------------*/
//void FillRGB( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice )
//{
//        if( w < 0 )w = 1;
//        if( h < 0 )h = 1;
//        if( x < 0 )x = 1;
//        if( y < 0 )y = 1;
//        D3DRECT rec = { x, y, x + w, y + h };
//        pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
//}
//inline void CrossHair(LPDIRECT3DDEVICE9 pDevice)
//{
//	if (Cross)
//		pDevice->GetViewport(&ViewPort);
//	DWORD ScreenX = ViewPort.Width / 2;
//	DWORD ScreenY = ViewPort.Height / 2;
//	FillRGB(ScreenX - 20, ScreenY, 40, 1, RED, pDevice);
//	FillRGB(ScreenX, ScreenY - 20, 1, 40, RED, pDevice);
//	FillRGB(ScreenX - 17, ScreenY, 34, 1, BLUE, pDevice);
//	FillRGB(ScreenX, ScreenY - 17, 1, 34, BLUE, pDevice);
//	FillRGB(ScreenX - 14, ScreenY, 28, 1, BLUE, pDevice);
//	FillRGB(ScreenX, ScreenY - 14, 1, 28, BLUE, pDevice);
//	FillRGB(ScreenX - 11, ScreenY, 22, 1, GREEN, pDevice);
//	FillRGB(ScreenX, ScreenY - 11, 1, 22, GREEN, pDevice);
//	FillRGB(ScreenX - 9, ScreenY, 18, 1, YELLOW, pDevice);
//	FillRGB(ScreenX, ScreenY - 9, 1, 18, YELLOW, pDevice);
//	FillRGB(ScreenX - 6, ScreenY, 12, 1, D3DCOLOR_ARGB(255, 255, 140, 000), pDevice);
//	FillRGB(ScreenX, ScreenY - 6, 1, 12, D3DCOLOR_ARGB(255, 255, 140, 000), pDevice);
//	FillRGB(ScreenX - 3, ScreenY, 6, 1, RED, pDevice);
//	FillRGB(ScreenX, ScreenY - 3, 1, 6, RED, pDevice);
//
//}
//bool WorldToScreen(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player, D3DVECTOR &PlayerScaled)
//{
//	
//	D3DXVECTOR3 PlayerPos(Player.x, Player.y, Player.z);
//	D3DXVECTOR3 vScreen;
//	pDevice->GetViewport(&Viewport);
//	Viewport.X = Viewport.Y = 0;
//	Viewport.MinZ = 0;
//	Viewport.MaxZ = 1;
//	D3DXVec3Project(&vScreen, &PlayerPos, &Viewport, 
//		i3RenderContext::Singleton()->GetProjectMatrix(), 
//		i3RenderContext::Singleton()->GetViewMatrix(), 
//		i3RenderContext::Singleton()->GetWorldMatrix());
//
//	if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height)
//	{
//		PlayerScaled.x = vScreen.x;
//		PlayerScaled.y = vScreen.y;
//		PlayerScaled.z = vScreen.z;
//		return true;
//	}
//	return false;
//	}
//void DrawLineBone(float StartX, float StartY, float EndX, float EndY, float Width, D3DCOLOR dColor )
//{
//    pLine[0].SetWidth( Width ); 
//    pLine[0].SetGLLines( 0 ); 
//    pLine[0].SetAntialias( 1 ); 
//
//    D3DXVECTOR2 v2Line[2]; 
//    v2Line[0].x = StartX; 
//    v2Line[0].y = StartY; 
//    v2Line[1].x = EndX; 
//    v2Line[1].y = EndY; 
//
//    pLine[0].Begin(); 
//    pLine[0].Draw( v2Line, 2, dColor ); 
//    pLine[0].End(); 
//}
//
//
//void DrawBone(int Idx,int Start,int End,DWORD Col,LPDIRECT3DDEVICE9 pDevice)
//{
//	D3DXVECTOR3 vStart,vEnd;
//	D3DXVECTOR3 vvStart,vvEnd;
//	GetUserBone(vStart, Start, Idx);
//	GetUserBone(vEnd, End, Idx);
//	if (WorldToScreen(pDevice,vStart, vvStart))
//	{
//		if (WorldToScreen(pDevice,vEnd, vvEnd))
//		{
//			DrawLineBone(vvStart.x,vvStart.y,vvEnd.x,vvEnd.y,1,Col);
//		}
//	}
//}
//
//
//void DrawLine(float StartX, float StartY, float EndX, float EndY, int Width, D3DCOLOR dColor )
//{
//    pLine[0].SetWidth( Width ); 
//    pLine[0].SetGLLines( 0 ); 
//    pLine[0].SetAntialias( 1 ); 
//
//    D3DXVECTOR2 v2Line[2]; 
//    v2Line[0].x = StartX; 
//    v2Line[0].y = StartY; 
//    v2Line[1].x = EndX; 
//    v2Line[1].y = EndY; 
//
//    pLine[0].Begin(); 
//    pLine[0].Draw( v2Line, 2, dColor ); 
//    pLine[0].End(); 
//}
//
//	void ESPLINEFUNC(int i,D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
//	{
//		D3DVIEWPORT9 viewP;
//		pDevice->GetViewport(&viewP);
//		DWORD OnTopX = viewP.Width / 2;
//		DWORD OnTopY = viewP.Y;
//		D3DXVECTOR3 vHead,sHead;
//		D3DXVECTOR3 vScreen;
//		if (GetUserBone(vHead,7, i))
//		{
//			if (WorldToScreen(pDevice,vHead, vScreen))
//			{
//				//FillRGB((float)sHead.x, (float)sHead.y, 3, 3,Color, pDevice );
//			//	DrawLine(OnTopX, OnTopY, (int)sHead.x - 1.5, (int)sHead.y - 1.5, 2, Color);
//				DrawLine((float)ViewPort.Width/2, (float)ViewPort.Height, vScreen.x, vScreen.y, 1, ORANGE);
//			}
//		}
//	}
//
//
//void DrawSkeleton(int iSlot/*, float Health,*/ ,LPDIRECT3DDEVICE9 pDevice)
//{
//	DWORD Color = RED;
//	//if (Health < 75)Color = YELLOW;
//	//if (Health < 50)Color = ORANGE;
//	//if (Health < 25)Color = RED;
//	DrawBone(iSlot,6,7, Color,pDevice);
//	DrawBone(iSlot,0,6, Color,pDevice);
//	DrawBone(iSlot,6,10, Color,pDevice);
//	DrawBone(iSlot,6,11, Color,pDevice);
//	DrawBone(iSlot,0,12, Color,pDevice);
//	DrawBone(iSlot,0,13, Color,pDevice);
//	DrawBone(iSlot,12,14, Color,pDevice); 
//	DrawBone(iSlot,13,15, Color,pDevice);
//	DrawBone(iSlot,14,8, Color,pDevice); 
//	DrawBone(iSlot,15,9, Color,pDevice); 
//}
////
#ifndef _XORSTR_H
#define _XORSTR_H
#pragma once
template <int XORSTART, int BUFLEN, int XREFKILLER>
class XorStr
{
private: 
    XorStr();
public: 
    char s[BUFLEN];

    XorStr(const char* xs);
    ~XorStr(){ for(int i=0;i<BUFLEN;i++)s[i]=0;}
};
template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART,BUFLEN,XREFKILLER>::XorStr(const char* xs)
{

    int xvalue = XORSTART;
    int i = 0;
    for(;i<(BUFLEN-1);i++) {
        s[i] = xs[i-XREFKILLER]^xvalue;
        xvalue += 1;
        xvalue %= 256;
    }
    s[BUFLEN-1] = 0;
}
#endif
//int getCurHP ( int Idx )
//{
//	__try{ 
//	DWORD CGameCharaBase = *(DWORD*)(*(DWORD*)(c_pCharaManager) + 0x14 + (Idx * 0xE0));
//    return ((DWORD (__thiscall *)(DWORD))SetCurHP)(CGameCharaBase);
//
//
//		
//	
//	}__except(EXCEPTION_EXECUTE_HANDLER){return(0);} 
//}
//
//class CGameString
//	{
//	public:
//		int getMySlotInfo()
//		{
//			int Slot = *(DWORD*)(this + PTR_TEAM);
//			return Slot;
//		}
//
//		static CGameString* g_pGameContext()
//		{
//			return (CGameString*)(*(DWORD*)c_pGameContext);
//		}
//	};
//
//
//	void DrawString(int x, int y, DWORD color, const char *fmt, ...)
//{
//	RECT FontPos = { x, y, x + 120, y + 16 };
//	char buf[1024] = {'\0'};
//	va_list va_alist;
//
//	va_start(va_alist, fmt);
//	vsprintf_s(buf, fmt, va_alist);
//	va_end(va_alist);
//	
//	fName->DrawTextA(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
//}
//
//	void CallESPNames2(int i, /*D3DCOLOR Color,*/LPDIRECT3DDEVICE9 pDevice)
//	{   D3DXVECTOR3 OnScreen, OnWorld;
//		D3DXVECTOR3 HeadPos, HeadScreen;
//		GetUserBone(HeadPos,7,i);
//			if (WorldToScreen(pDevice,HeadPos, HeadScreen))
//			{
//		
//					char pNames[33];
//					DrawString( (float)HeadScreen.x-50,(float)HeadScreen.y-35,TeamColor, "%S",CBattleSlotContextName::Singleton2()->GetNickForSlot(i));
//		/*	sprintf(pNames, "%S", CBattleSlotContextName::Singleton2()->GetNickForSlot(i));
//			
//		
//DrawOutlineString(OnScreen.x,OnScreen.y-40.0,RED, DT_NOCLIP,fName, pNames);*/
//			}
//		
//	
//	}
//
//	#define BLACK			D3DCOLOR_ARGB(150, 000, 000, 000)
//
//	
//void FillRGB2(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice)
//{
//	if (w < 0)w = 1;
//	if (h < 0)h = 1;
//	if (x < 0)x = 1;
//	if (y < 0)y = 1;
//	D3DRECT rec = { x, y, x + w, y + h };
//	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
//}
//	void DrawBorder(int x, int y, int w, int h, int px, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice)
//{
//	FillRGB2(x, (y + h - px), w, px, BorderColor, pDevice);
//	FillRGB2(x, y, px, h, BorderColor, pDevice);
//	FillRGB2(x, y, w, px, BorderColor, pDevice);
//	FillRGB2((x + w - px), y, px, h, BorderColor, pDevice);
//}
//
//	void HealthBar(LPDIRECT3DDEVICE9 pDevice, float x, float y, float Health)
//{
//	DWORD HPcol = GREEN;
//	if (Health < 90)HPcol = GREEN;
//	if (Health < 70)HPcol = ORANGE;
//	if (Health < 50)HPcol = YELLOW;
//	if (Health < 30) HPcol = RED;
//	if (Health < 15) HPcol = RED;
//	DrawBorder(x - 1, y - 1, 52, 5, 1, BLACK, pDevice);
//	FillRGB2(x, y, Health / 2, 3, HPcol, pDevice);
//}
//	
//
//
//
//	
//
//				void CallESPHealth(int i, /*D3DCOLOR Color,*/LPDIRECT3DDEVICE9 pDevice)
//	{   D3DXVECTOR3 OnScreen, OnWorld;
//		D3DXVECTOR3 HeadPos, HeadScreen;
//		GetUserBone(HeadPos,7,i);
//			if (WorldToScreen(pDevice,HeadPos, HeadScreen))
//			{
//		
//					char pNames[33];
//					HealthBar(pDevice,(int)HeadScreen.x-15,(int)HeadScreen.y-24,getCurHP(i));
//					//DrawString( (float)HeadScreen.x-50,(float)HeadScreen.y-35,RED, "%S",CBattleSlotContextName::Singleton2()->GetNickForSlot(i));
//			
//			}
//		
//	
//	}
//
//void CriarCaixa(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
//{
//
//	D3DRECT rec;
//	rec.x1 = x;
//	rec.x2 = x + w;
//	rec.y1 = y;
//	rec.y2 = y + h;
//	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
//	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DPT_TRIANGLESTRIP);
//	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 1, 1);
//
//}
//void DesenharCaixa(int x, int y, int w, int h, D3DCOLOR COLOR, LPDIRECT3DDEVICE9 pDevice)
//{
//	CriarCaixa(x, y, 1, h, COLOR, pDevice);
//	CriarCaixa(x, y + h, w, 1, COLOR, pDevice);
//	CriarCaixa(x, y, w, 1, COLOR, pDevice);
//	CriarCaixa(x + w, y, 1, h + 1, COLOR, pDevice);
//}
//
//
//void SeguirBone(int iSlot, /*D3DCOLOR Color,*/ LPDIRECT3DDEVICE9 pDevice)
//{
//	D3DXVECTOR3 HeadPos, HeadScreen;
//	D3DXVECTOR3 FootPos, FootScreen;
//
//	if(GetUserBone(HeadPos,7,iSlot)){
//	if(GetUserBone(FootPos,8,iSlot)){
//	if (WorldToScreen(pDevice,HeadPos, HeadScreen))
//	{
//	if (WorldToScreen(pDevice,FootPos, FootScreen))
//	{
//		float w = (FootScreen.y - HeadScreen.y) / 4;
//		DesenharCaixa(HeadScreen.x - w, HeadScreen.y, w * 2, FootScreen.y - HeadScreen.y, TeamColor, pDevice);
//	}}
//	}}
//}
//
//#define TBlack			D3DCOLOR_ARGB(128, 000, 000, 000)
//void FillRGB34( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice )
//{
//	if( w < 0 )w = 1;
//	if( h < 0 )h = 1;
//	if( x < 0 )x = 1;
//	if( y < 0 )y = 1;
//
//	D3DRECT rec = { x, y, x + w, y + h };
//	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
//}
//void DrawHealthBarsVert( D3DXVECTOR3 Head, D3DXVECTOR3 Foot, WORD health,IDirect3DDevice9* pDevice )
//{
//    DWORD dwColor;
//	D3DXVECTOR3 Box =  Head - Foot;
//    if( Box.y < 0 )
//            Box.y *= -1;
//    int BoxWidth = (int)Box.y / 2;
//    int DrawX = (int)Head.x - ( BoxWidth / 2 );
//    int DrawY = (int)Head.y;
//    DWORD dwDrawWidth = health * (Foot.y - Head.y) / 100;
//    if( health > 100 )
//            health = 100;
//    if( health > 75 )
//            dwColor = 0xFF00FF00;
//    else if( health > 40 )
//            dwColor = 0xFFFF9B00;
//    else
//            dwColor = 0xFFFF0000;
//	FillRGB34(DrawX - 6, DrawY - 1, 2, (int)Box.y + 0, TBlack,pDevice);
//	FillRGB34(DrawX - 5, DrawY, 3, dwDrawWidth, dwColor,pDevice);
//}
//
//
//void CallESPHealth1(int iSlot, LPDIRECT3DDEVICE9 pDevice)
//{
//	D3DXVECTOR3 vHead, vFoot, sHead, sFoot;
//	GetUserBone( vHead, 7,iSlot);
//	GetUserBone( vFoot, 8,iSlot);
//	if (WorldToScreen(pDevice, vHead, sHead)&&
//		WorldToScreen(pDevice, vFoot, sFoot))
//		{
//			
//				DrawHealthBarsVert(sHead, sFoot, getCurHP(iSlot), pDevice);
//
//				
//		}
//	}
//
//int cTeamFind(int Idx)
//{
//	for (int a = 0; a <= 14; a += 2)if (Idx == a)return 1;
//	for (int b = 1; b <= 15; b += 2)if (Idx == b)return 2;
//	return 0;
//}
//bool GetUserLife(int iSlot)
//{
//	__try{ 
//	if (!getCurHP > 0)
//		return true;
//	}__except(true){return false;} 
//}
//BYTE GetMySlot()
//{
//	return *(BYTE*)(*(DWORD*)(c_pGameContext)+PTR_TEAM);
//}
//
//int ESPHealth;
//
//struct CTeam
//{
//	BYTE iTeam;
//};
//
//
//
//
//int GetMyCharaIndex()
//{
//	unsigned long BasePlayer_A = *(DWORD*)(c_pGameContext);
//	CTeam *MyTeam = (CTeam*)((BasePlayer_A + PTR_TEAM));
//	return MyTeam->iTeam;
//}
//
//
//void _stdcall BoneESP(LPDIRECT3DDEVICE9 pDevice)
//{
//
//	if(*(DWORD*)c_pPlayer!=0)
//	{
//		D3DXVECTOR3 OnScreen, OnWorld;
//		D3DXVECTOR3 OnScreenV, OnWorldV;
//		int MyTeam = cTeamFind(GetMyCharaIndex());
//		for ( int iSlot = 0; iSlot < 16; iSlot++ )
//		{
//     	int iTeam = cTeamFind(iSlot);
//		if (iTeam == MyTeam)continue;
//		if (iTeam == 1){ TeamColor = TERORI; } 
//	    if (iTeam == 2){ TeamColor = POLICE; }
//		if (!GetUserLife(iSlot))
//				{
//					if (GetUserBone(OnWorld,7,iSlot))
//					{
//						if(WorldToScreen(pDevice,OnWorld,OnScreen))
//						{
//					
//					if(ESPBone == 1)
//					{
//						DrawSkeleton(iSlot, pDevice);
//					}
//					if(ESPName == 1)
//					{
//						CallESPNames2(iSlot,pDevice);
//					}
//						if(ESPLine == 1)
//					{
//						ESPLINEFUNC(iSlot,ORANGE,pDevice);
//					}
//
//
//if(CH_ESPB3D == 1)
//					{
//						SeguirBone(iSlot,pDevice);
//					}
//
//						
//						if (ESPHealth == 1){ CallESPHealth1(iSlot, pDevice); 
//				}
//		
//				}}}}
//	
//	}
//}
////
////
//inline bool InVisible(int iSlot)
//{
//	if (getCurHP(iSlot) > 0) //1
//		return true;
//	return false;
//
//}
////	bool WorldToScreenasep(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player,D3DVECTOR &PlayerScaled)
////	{
////		D3DXVECTOR3 PlayerPos(Player.x,Player.y,Player.z);
////		D3DXMATRIX identity;
////		D3DXVECTOR3 vScreen;
////		pDevice->GetViewport(&Viewport);
////		Viewport.X = Viewport.Y = 0;
////		Viewport.MinZ     = 0;
////		Viewport.MaxZ     = 1;
////		D3DXVec3Project(&vScreen, &PlayerPos, &Viewport,i3RenderContext::Singleton()->GetProjectMatrix(),i3RenderContext::Singleton()->GetViewMatrix(),i3RenderContext::Singleton()->GetWorldMatrix());	
////		if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height)
////		{
////			PlayerScaled.x = vScreen.x;
////			PlayerScaled.y = vScreen.y ;
////			PlayerScaled.z = vScreen.z;
////			return true; 
////		} 
////		return false;
////	}
//////inline bool ADDXW2S2(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 Player, D3DVECTOR &PlayerScaled)
//////{
//////	D3DXVECTOR3 PlayerPos(Player.x, Player.y, Player.z);
//////	D3DXMATRIX identity;
//////	D3DXVECTOR3 vScreen;
//////	pDevice->GetViewport(&Viewport);
//////	Viewport.X = Viewport.Y = 0;
//////	Viewport.MinZ = 0;
//////	Viewport.MaxZ = 1;
//////	D3DXVec3Project(&vScreen, &PlayerPos, &Viewport,
//////		i3RenderContext::Singleton()->GetProjectMatrix(),
//////		i3RenderContext::Singleton()->GetViewMatrix(),
//////		i3RenderContext::Singleton()->GetWorldMatrix());
//////
//////	if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height)
//////	{
//////		PlayerScaled.x = vScreen.x;
//////		PlayerScaled.y = vScreen.y;
//////		PlayerScaled.z = vScreen.z;
//////
//////		return true;
//////	}
//////	return false;
//////}
////////-------------------------------------------------------------------------------------------------------------------------------
////int IdBone = 5;
////
//bool BulletEnable = false; bool AimbotOff01 = false; bool AimbotOff02 = false; bool AimbotOff03 = false;
//////---------------------------------------------------------------------------------------------------------------------------------
//DWORD BackupEDXTele, BackupEDX = 0;
//float fX = 10.0f, fY = 10.0f, fZ = 10.0f;
//	float CalcDistance( D3DXVECTOR3 VecA, D3DXVECTOR3 VecB ){
//return sqrt( ( ( VecA.x - VecB.x ) * ( VecA.x - VecB.x ) ) +
//( ( VecA.y - VecB.y ) * ( VecA.y - VecB.y ) ) +
//( ( VecA.z - VecB.z ) * ( VecA.z - VecB.z ) ) );
//}
//
////
////
//////
//////
////////-------------------------------------------------------------------------------------------------------------------------------
//////
//////
////////
////////
//////////-------------------------GAME HACK PB KAYBO --------------------//
////////
//////////######################### SUICIDIO  ############################
////////
//////typedef void (__thiscall * tCmd_Mati)(DWORD CGameCharaLocalBase, int HPDrain, int a2, int a3);
//////tCmd_Mati Cmd_Mati;
//////
//////
//////void suicide(){
//////	
//////	if(suicideplayers)
//////	{
//////	Cmd_Mati = (tCmd_Mati)(ResultSuicide);
//////	DWORD CGameCharaLocalBase = *(DWORD*)(c_pPlayer);
//////	Cmd_Mati(CGameCharaLocalBase,0xFF,0xFFFF,false);
//////	}}
//////	
//////
/////////-------SPEED ASM HOOK --------//
/////////-------SPEED ASM HOOK --------//
////////D945085F5E5B64890D000000008BE55DC204  -> ESCANEAR EN 5 DE 5000 OFFSET
//DWORD DwAddresBaseMovespeedw = ((*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3FrameworkDx.dll") + 0x003077A4) + 0x4) + 0x2C) + 0x10) + 0x2A8) + 0x10B4));
//DWORD hassck   = (DwAddresBaseMovespeedw + 0x1);
//
//DWORD GetMoveSpeed222X   = (hassck + 0xF);
//
//
//float Low2 = 115;
//__declspec(naked) void Speed_Low(){
//	_asm
//	{
//
//            FLD DWORD PTR SS : [Low2]
//			POP EDI
//			POP ESI
//			POP EBX
//			MOV ESP, EBP
//			JMP DWORD PTR SS : [GetMoveSpeed222X]
//	}
//}
//
//
//
//
//
//float SpeedX2 = 90;
//__declspec(naked) void Speed_OFF()
//{
//	_asm
//	{
//FLD DWORD PTR SS:[SpeedX2]
//POP EDI
//POP ESI
//POP EBX
//MOV DWORD PTR FS:[0],ECX
//MOV ESP,EBP
//JMP DWORD PTR SS : [GetMoveSpeed222X]
//	}
//}
//
//
//
////
////
//void GameHackCreate22()
//{
//
//		
//			
//				if (HackSpeed == 1)
//			{
//			MakeJMP((PBYTE)hassck, (DWORD)Speed_Low, 8);
//			}
//		
//
//			else
//			{
//				MakeJMP((PBYTE)hassck, (DWORD)Speed_OFF, 8);
//			}
//
//
//}
//////ANTI AFK//
//int HackAntiafk = 0;
//int AutoGOx;
/////*
////.text:0067FC63                 push    ebx
////.text:0067FC64                 push    503h <<#################################### esse (503 - 1 = 502)
////.text:0067FC69                 call    sub_57C930
////.text:0067FC6E                 mov     eax, offset unk_CB300C
////.text:0067FC73                 push    1
////.text:0067FC75                 push    eax
////.text:0067FC76                 mov     [ebp-10h], eax
////.text:0067FC79                 call    dword ptr ds:0D488D8h
////.text:0067FC7F                 lea     eax, [ebp-14h]
////.text:0067FC82                 mov     [ebp-4], ebx
////.text:0067FC85                 push    eax
////.text:0067FC86                 push    ebx
////.text:0067FC87                 push    offset asc_B30894 ; "STR_TBL_GUI_READY_NOTICE_SEND_INVITE"
////----------------------------------------------------------------------------------------------------
////.text:0084BBF6 sub_84BBF6 <<################################################ Address da Função
////.text:0084BBF6                                         ; sub_685768+AAp ...
////.text:0084BBF6                 mov     eax, offset loc_AB6DFD
////.text:0084BBFB                 call    sub_A2C5F8
////.text:0084BC00                 mov     eax, [ebp+8]
////.text:0084BC03                 sub     esp, 214h
////.text:0084BC09                 cmp     eax, 8
////.text:0084BC0C                 jnb     short loc_84BC18
////.text:0084BC0E                 mov     byte ptr [eax+ecx+80h], 1
////.text:0084BC16                 jmp     short loc_84BC7D
////.text:0084BC18 ; ---------------------------------------------------------------------------
////.text:0084BC18
////.text:0084BC18 loc_84BC18:                             ; CODE XREF: sub_84BBF6+16j
////.text:0084BC18                 push    ebx
////.text:0084BC19                 xor     ebx, ebx
////.text:0084BC1B                 push    ebx
////.text:0084BC1C                 push    offset asc_B79BB8 ; "void __thiscall InviteContext::CheckInv"...
////*/
//////g_pAutoShot2 0xD0B154 // C3 55 8B EC 83 EC 2C 57 8B F9 80 7F 21 00 -> "void __thiscall iProgressEdit::SetControl(class UIPopupBase *,class i3UIScene *,const char *,const char *,const char *)"   MOV ECX,DWORD PTR DS:[D0B150]
////DWORD pSetEvent = 0x8997F25; //ARRIBA CALL 74 17 33 DB 8B CE 53 53 FF 75 14 FF 75 10 FF 75 0C 50
////#define g_pGameEventSender                 0x908968C//
////
//////0xCF5084
////
////
////class CGameEventSender {
////public:
////	int SetEvent(int Param1, int Param2, int Param3) {
////		auto Func = (int(__thiscall*)(CGameEventSender*, int, int, int, int, int, int))pSetEvent;
////		return Func(this, Param1, Param2, Param3, NULL, NULL, NULL);
////	}
////
////	static CGameEventSender* Singletosn2(){ return (CGameEventSender*)(*(PDWORD)g_pGameEventSender); }//05 00 00 E8 ?? ?? ?? ?? 5F 5E 8B E5 5D C3
////};
////int Autogo2;
////void AutoGO()
////{
////
////
////	CGameEventSender::Singletosn2()->SetEvent(0x508, NULL, NULL);
////
////}
//void afk()
//{
//
//
//
//
//	if (HackAntiafk == 0)
//	{
//		__try
//		{
//			__asm
//			cmp eax, c_pPlayer
//			{
//			//COOR 01
//unk((void*)SetAwayInputTime1X, (void*)(PBYTE)"\x56\x8B\xF1\x74\x14\x80\x3D",7);
//
//unk((void*)SetAwayInputTime2X, (void*)(PBYTE)"\x75\x0B",2);
//
//			}
//		}
//		__except (EXCEPTION_EXECUTE_HANDLER){}
//}else if (HackAntiafk == 1)
//	{
//		__try
//		{
//			__asm
//			cmp eax, c_pPlayer
//			{
//			//COOR 01
//
//unk((void*)SetAwayInputTime1X, (void*)(PBYTE)"\x56\x8B\xF1\x90\x90\x80\x3D",7);
//unk((void*)SetAwayInputTime2X, (void*)(PBYTE)"\x90\x90",2);
//		}
//		}
//		__except (EXCEPTION_EXECUTE_HANDLER){}
//}
//}
//
//
//
//
//
//////
//////
//BYTE IsGM ;
//////
////
//////////D945085F5E5B64890D000000008BE55DC204  -> ESCANEAR EN 5 DE 5000 OFFSET
//DWORD DwAddresBasePasRoom = ((*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3FrameworkDx.dll") + 0x2F0088) + 0x228C) + 0x200) + 0x7AC) + 0x21F8) + 0x2234));
//DWORD PassRoom = (DwAddresBasePasRoom + 0x03);
//DWORD RetPassRoom = (PassRoom + 0x5);
//__declspec (naked) void ForceAcess()//33 C0 50 50 50 68 04 04 00 00
//{
//	__asm
//	{
//		    xor eax, eax
//			push eax
//			push eax
//			lea eax, IsGM
//			push eax
//			jmp RetPassRoom
//	}
//}
//
//
//
//int BruteForce;
////
//void BrutalForcer()
//{
//	if (BruteForce == 1 ){
//		__try{
//			MakeJMP((PBYTE)PassRoom, (DWORD)ForceAcess, 0x4); IsGM = 1;
//		}
//		__except (EXCEPTION_EXECUTE_HANDLER) {}
//	}
//	if (BruteForce == 0){
//		__try{
//			MakeJMP((PBYTE)PassRoom, (DWORD)ForceAcess, 0x4); IsGM = 0;
//		}
//		__except (EXCEPTION_EXECUTE_HANDLER) {}
//
//	}
//}
////
////////######################### FALL DAMAGUE ############################
////
//#define Skills                   0x17E98//float __thiscall BattleSlotContext::GetUseCashItemValue(int,enum //17122 0x17258 //
//DWORD CambioRapidoOfset =        Skills+ 12 ;
// //ADDRES 010F22A0
//#define Ativado0                 0x3F40E1C6 //C6 E1 4C 3D ate C6 E1 4C 40
//#define Desativado               0xB7A7C5AC //AC C5 A7 B7
//#define CuponSize                0x48
//#define g_pAFK                   (c_pGameContext + 0x1D8)
//#define SetFall       (0x17E24 + 0xA8 )
//
//
//void dameueon() {
//		if (*(DWORD*)(c_pGameContext) != 0 && NoFallDamage ){
//		if (*(DWORD*)(*(DWORD*)c_pGameContext + SetFall + GetMySlot() * CuponSize) != 0x454CE1C6 ||
//			*(DWORD*)(*(DWORD*)c_pGameContext + SetFall + GetMySlot() * CuponSize) == 0x454CE1C6)
//			*(DWORD*)(*(DWORD*)c_pGameContext + SetFall + GetMySlot() * CuponSize) = 0x454CE1C6;
//	}
//
//
//			else if (NoFallDamage)
//		*(DWORD*)(*(DWORD*)c_pGameContext + SetFall) = 0x454CE1C6;
////(*(DWORD*)(*(DWORD*)Offg_pBattleSlotContext + CambioRapidoOfset + GetMySlot2() * CuponSize) != Desativado ||
//			//*(DWORD*)(*(DWORD*)Offg_pBattleSlotContext + CambioRapidoOfset + GetMySlot2() * CuponSize) == Desativado)
//			//*(DWORD*)(*(DWORD*)Offg_pBattleSlotContext + CambioRapidoOfset + GetMySlot2() * CuponSize) = Desativado;
//
//}
//
//
//
//void TrocaRapida() {
//
//	
//	if (*(DWORD*)(c_pGameContext) != 0 && TrocaRapida1 ){
//		if (*(DWORD*)(*(DWORD*)c_pGameContext + CambioRapidoOfset + GetMySlot() * CuponSize) != Ativado0 ||
//			*(DWORD*)(*(DWORD*)c_pGameContext + CambioRapidoOfset + GetMySlot() * CuponSize) == Ativado0)
//			*(DWORD*)(*(DWORD*)c_pGameContext + CambioRapidoOfset + GetMySlot() * CuponSize) = Ativado0;
//	}
//
//	else if  (*(DWORD*)(*(DWORD*)c_pGameContext + CambioRapidoOfset + GetMySlot() * CuponSize) != Desativado ||
//			*(DWORD*)(*(DWORD*)c_pGameContext + CambioRapidoOfset + GetMySlot() * CuponSize) == Desativado)
//			*(DWORD*)(*(DWORD*)c_pGameContext + CambioRapidoOfset + GetMySlot() * CuponSize) = Desativado;
//
//}
//////
//////
//////
//////
////void EXITGAME()
////{
////		if (exitgamedeclaration)
////		{
////		
////			ExitProcess(0);
////				
////		}
////}
////
//////
//////
//void NoReloadNeil()
//{
//	if (NoRecargar == 1)
//	{
//		__try
//		{
//			__asm
//			cmp eax, c_pPlayer
//			{
//				//COOR 01
//				*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3FrameworkDx.dll") + 0x30806C) + 0x68) + 0x890) + 0x64) + 0x240) + 0x5C0) = 1693992409;
//				//COOR 02
//				
//
//			}
//		}
//		__except (EXCEPTION_EXECUTE_HANDLER){}
//}else{
//if (NoRecargar == 0 )
//{
//__try
//{ __asm
//cmp eax, c_pPlayer
//{
//				*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3FrameworkDx.dll") + 0x30806C) + 0x68) + 0x890) + 0x64) + 0x240) + 0x5C0)  = 1693468121; 
//
//}}__except (EXCEPTION_EXECUTE_HANDLER){}
//}}}
//int MultiBalas;
//
////
////__declspec(naked) void VariasBalas1()
////{
////	_asm
////	{
////            mov al, [ebp - 31]
////			mov esp, ebp
////			pop ebp
////			retn
////	}
////}
////__declspec(naked) void VariasBalas2()
////{
////	_asm
////	{
////            mov al, [ebp - 13]
////			mov esp, ebp
////			pop ebp
////			retn
////	}
////}
////__declspec(naked) void VariasBalaspff()
////{
////	_asm
////	{
////            mov al, [ebp - 1]
////			mov esp, ebp
////			pop ebp
////			retn
////	}
////}
//////
////void multialasfunc()
////{
////
////	
////		if (MultiBalas == 1)
////			{
////			MakeJMP((PBYTE)ResultBalatitanium, (DWORD)VariasBalas1, 5);
////			}
////		
////		else if (MultiBalas == 2)
////			{
////			MakeJMP((PBYTE)ResultBalatitanium, (DWORD)VariasBalas1, 5);
////			}
////			else
////			{
////				MakeJMP((PBYTE)ResultBalatitanium, (DWORD)VariasBalaspff, 5);
////			}
////
////}
//
//
//void multialasfunc()
//{
//	if (MultiBalas == 0)
//	{
//		__try
//		{
//			__asm
//			cmp eax, c_pPlayer
//			{
//			//COOR 01
//
//unk((void*)ResultBalatitanium, (void*)(PBYTE)"\x8A\x45\xFF",3);
//
//			}
//		}
//		__except (EXCEPTION_EXECUTE_HANDLER){}
//}else if (MultiBalas == 1)
//	{
//		__try
//		{
//			__asm
//			cmp eax, c_pPlayer
//			{
//			//COOR 01
//
//unk((void*)ResultBalatitanium, (void*)(PBYTE)"\x8A\x45\xCF",3);
//
//			}
//		}
//		__except (EXCEPTION_EXECUTE_HANDLER){}
//}else if (MultiBalas == 2)
//	{
//		__try
//		{
//			__asm
//			cmp eax, c_pPlayer
//			{
//			//COOR 01
//
//unk((void*)ResultBalatitanium, (void*)(PBYTE)"\x8A\x45\xED",3);
//
//		}
//		}
//		__except (EXCEPTION_EXECUTE_HANDLER){}
//}
//}
//int toup;
////######################### MODO TOUPEIRA ############################
//DWORD ResultDopera = 0xCDE0;
//void toupeira()
//{
//
//
//	if (toup)
//	{
//		DWORD modotou = ((DWORD)GetModuleHandleA("NxCharacter.2.8.1.dll") + ResultDopera); //ACTULISAR CON IDA 
//		unk((void*)modotou, (void*)(PBYTE)"\x89\x8B\x32",3);
//	
//	}
//	else{
//		
//			DWORD modotou = ((DWORD)GetModuleHandleA("NxCharacter.2.8.1.dll") + ResultDopera);
//		unk((void*)modotou, (void*)(PBYTE)"\x89\x8B\x34",3);
//		}
//	
//}
//
////######################### FLYSPACE  ############################
//
//int FLYHACK100;
//DWORD ResultFly = 0xC153;
//void SUUPÉRFLY() // me fly space eu crio :V descryp 
//{
//
//	
//if (FLYHACK100 && IsKeyPressed(VK_SPACE, 1) )
//	{
//
//	
//		DWORD ModoFly = ((DWORD)GetModuleHandleA("NxCharacter.2.8.1.dll") + ResultFly); //ACTULISAR CON IDA 
//		unk((void*)ModoFly, (void*)(PBYTE)"\xF6\xC4\x13",3);
//	}
//	else{
//		
//			DWORD ModoFly = ((DWORD)GetModuleHandleA("NxCharacter.2.8.1.dll") + ResultFly);
//		unk((void*)ModoFly, (void*)(PBYTE)"\xF6\xC4\x44",3);
//		}
//	
//}
//
//#define ofsSala1 0x20
//#define ofsSala2 0x164
//#define ofsSala3 0x10
//#define g_pSalaConfig 0x971E6FC//0xCF7D40//0xCF3870 //89 35 ?? ?? ?? ?? 5E 5B 64 89 0D
//
//
//
//void ChamaSala3()
//{
//	*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(g_pSalaConfig)+ofsSala1) + ofsSala2) + ofsSala3) = 00;
//}
//void autoshoss()
//{
//	if (Respanw == 1)
//	{
//		__try
//		{
//			__asm
//			cmp eax, c_pPlayer
//			{
//			//COOR 01
//
//unk((void*)ResultRespanw, (void*)(PBYTE)"\xD9\x45\x01",3);
//
//			}
//		}
//		__except (EXCEPTION_EXECUTE_HANDLER){}
//}else{
//if (Respanw == 0 )
//{
//__try
//{ __asm
//cmp eax, c_pPlayer
//{
//unk((void*)ResultRespanw, (void*)(PBYTE)"\xD9\x45\x08",3);
//
//}}__except (EXCEPTION_EXECUTE_HANDLER){}
//}}}
//////
//////
//////
//void NoRecoilFunc()
//{
//	if (NoRecoil == 1)
//	{
//		__try
//		{
//			__asm
//			cmp eax, c_pPlayer
//			{
//				//COOR 01
//				*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3FrameworkDx.dll") + 0x307870) + 0x730) + 0xAEC) + 0xE8) + 0x8EC) + 0x45C) = 2338319429;
//				//COOR 02
//				
//
//			}
//		}
//		__except (EXCEPTION_EXECUTE_HANDLER){}
//}else{
//if (NoRecoil == 0 )
//{
//__try
//{ __asm
//cmp eax, c_pPlayer
//{
//*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3FrameworkDx.dll") + 0x307870) + 0x730) + 0xAEC) + 0xE8) + 0x8EC) + 0x45C) = 2338323525; 
//
//}}__except (EXCEPTION_EXECUTE_HANDLER){}
//}}}
//
//void NoRecoilFunc2()
//{
//	
//
//		if (NoRecoilHROZ == 1 )
//{
//		__try
//		{
//			__asm
//			cmp eax, c_pPlayer
//			{
//				//COOR 01
//				*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3SceneDx.dll") + 0x242484) + 0x1138) + 0x9E4) + 0x78) + 0x8EC) + 0x348) = 3964000764;
//				//COOR 02
//				
//
//			}
//		}
//		__except (EXCEPTION_EXECUTE_HANDLER){}
//	
//
//
//}else{
//if (NoRecoilHROZ == 0 )
//{
//__try
//{ __asm
//cmp eax, c_pPlayer
//{
//*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3SceneDx.dll") + 0x242484) + 0x1138) + 0x9E4) + 0x78) + 0x8EC) + 0x348) = 4232436220;
//
//}}__except (EXCEPTION_EXECUTE_HANDLER){}
//}}}
////
//////---------------------------------------------------------------------------------------------------------------------------------
//DWORD SetEnd = (DWORD)GetProcAddress(GetModuleHandleA(/*i3SceneDx.dll*/XorStr<0x57, 14, 0x3A55486E>("\x3E\x6B\x0A\x39\x3E\x32\x38\x1A\x27\x4E\x05\x0E\x0F" + 0x3A55486E).s), /*?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z*/XorStr<0x2F, 41, 0xB211C470>("\x10\x63\x54\x46\x76\x5A\x51\x76\x5E\x0B\x7A\x55\x57\x50\x54\x5A\x5A\x25\x0D\x2B\x2D\x21\x05\x06\x16\x09\x0C\x12\x1B\x0D\x19\x18\x0A\x13\x62\x16\x13\x14\x15\x0C" + 0xB211C470).s);
//
//DWORD DolineCollision = ((*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*(DWORD*)((int)GetModuleHandle("i3FrameworkDx.dll") + 0x30454C) + 0x740) + 0x9A8) + 0x980) + 0x4D0) + 0x48));
////FF 75 08 8D BE 6C 04 00 00 8B CF ff 15
//_declspec(naked)void HookSetEnd()//O sc não dividida para todos os que estão prontos sim , work br ? yeah 
//{
//	_asm
//	{
//		cmp[BulletEnable], 0;
//		je Skip;
//		mov eax, [esp + 4];
//		mov[eax], edx;
//		mov edx, [fX];
//		mov[eax + 0], edx;
//		mov edx, [fY];
//		mov[eax + 4], edx;
//		mov edx, [fZ];
//		mov[eax + 8], edx;
//		mov edx, [ecx + 8];
//	Skip:
//		jmp Original;
//		nop;
//	Original:
//		mov eax, [esp + 4];
//		fld dword ptr[eax];
//		fstp dword ptr[ecx + 0x18];
//		fld dword ptr[eax + 0x04];
//		fstp dword ptr[ecx + 0x1C];
//		fld dword ptr[eax + 0x08];
//		fstp dword ptr[ecx + 0x20];
//		fld dword ptr[ecx + 0x18];
//		fsub dword ptr[ecx + 0x0C];
//		fstp dword ptr[ecx + 0x24];
//		fld dword ptr[ecx + 0x1C];
//		fsub dword ptr[ecx + 0x10];
//		fstp dword ptr[ecx + 0x28];
//		fld dword ptr[ecx + 0x20];
//		fsub dword ptr[ecx + 0x14];
//		fstp dword ptr[ecx + 0x2C];
//		ret 4;
//	}
//}
//
//bool bHookedTele = false;
//DWORD HookAIM(BYTE *MemoryTarget, DWORD FunctionTarget){
//	Sleep(5);
//	*((DWORD *)(MemoryTarget)) = FunctionTarget;
//	Sleep(5);
//	return 0;
//}
////
//DWORD MakePTR22(BYTE *MemoryTarget, DWORD FunctionTarget)
//{
//
//	DWORD dwRetn = *(DWORD*)(MemoryTarget);
//
//
//	*((DWORD *)(MemoryTarget)) = FunctionTarget;
//
//	return dwRetn;
//}
////
//////-------------------------------------------------------------------------------------------------------------------------------------------------//
//bool BHookedTele, cHookedShot = false;
//////----------------------------------------------------------------------------------------
//
//
//void HookAim()
//{
//	if (BHookedTele)return;
//	DWORD OldProtect;
//	DWORD OFS_Telekill = DolineCollision;
//	VirtualProtect((LPVOID)(OFS_Telekill), sizeof(OFS_Telekill), PAGE_EXECUTE_READWRITE, &OldProtect);
//	*((DWORD *)(OFS_Telekill)) = (DWORD)HookSetEnd;
//	VirtualProtect((LPVOID)(OFS_Telekill), sizeof(OFS_Telekill), OldProtect, &OldProtect);
//	BHookedTele = true;
//}
////
////void HookAim(void){
////	if (BHookedTele)return;
////
////	HookAIM((PBYTE)DolineCollision, (DWORD)HookSetEnd);
////
////	BHookedTele = true;
////}
////
////
////
//static D3DXVECTOR3 EnemyPos;
//////-------------------------------------------------------------------------------------------------------------------------------------------------//
////
////static D3DVIEWPORT9 ViewPorts;
////
//////-----------------------------------------------AIMBOT--------------------------------------------------------------------------------------------------//
////
//	#define PI 3.141592654f
//void PrintTex(char pString[], int x, int y, D3DCOLOR col, ID3DXFont *font){
//
//
//	RECT FontRect = { x, y, x+500, y+30 };
//	fName->DrawText( NULL, pString, -1, &FontRect, DT_LEFT | DT_WORDBREAK, col);
//}
////
//void DrawCircle(int X, int Y, int radius, int numSides, DWORD Color) 
//{
//    D3DXVECTOR2 Line[128]; 
//    float Step = PI * 2.0 / numSides; 
//    int Count = 0; 
//    for(float a=0; a < PI*2.0; a += Step) 
//    { 
//        float X1 = radius * cos(a) + X; 
//        float Y1 = radius * sin(a) + Y; 
//        float X2 = radius * cos(a+Step) + X; 
//        float Y2 = radius * sin(a+Step) + Y; 
//        Line[Count].x = X1; 
//        Line[Count].y = Y1; 
//        Line[Count+1].x = X2; 
//        Line[Count+1].y = Y2; 
//        Count += 2; 
//    } 
//    pLine->Begin(); 
//    pLine->Draw(Line,Count,Color); 
//    pLine->End(); 
//}
//
//
//
//#define Fov_Value 10200
//
//	bool WorldToScreen2(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player, D3DVECTOR &PlayerScaled)
//{
//	D3DXVECTOR3 PlayerPos(Player.x, Player.y, Player.z);
//	D3DXVECTOR3 vScreen;
//	pDevice->GetViewport(&Viewport);
//	Viewport.X = Viewport.Y = 0;
//	Viewport.MinZ = 0;
//	Viewport.MaxZ = 1;
//	D3DXVec3Project(&vScreen, &PlayerPos, &Viewport, 
//		i3RenderContext::Singleton()->GetProjectMatrix(), 
//		i3RenderContext::Singleton()->GetViewMatrix(), 
//		i3RenderContext::Singleton()->GetWorldMatrix());
//
//	if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height)
//	{
//		PlayerScaled.x = vScreen.x;
//		PlayerScaled.y = vScreen.y;
//		PlayerScaled.z = vScreen.z;
//		return true;
//	}
//	return false;
//}
////inline int GetNearestToCrosshairfer(int Idx,int Start,int End)
////{
//
//	inline int GetNearestToCrosshairfer()
//	{
//		
//	int iAimAt = -1;
//		double fMaxDistance = (float)Fov_Value;
//		//D3DVIEWPORT9 ViewPort2;
//		i3RenderContext::Singleton()->pDevice->GetViewport(&ViewPort);
//		D3DXVECTOR3 vBone, vScreen;
//			D3DXVECTOR3 vStart,vEnd;
//	D3DXVECTOR3 vvStart,vvEnd;
//	//	D3DXVECTOR3 Screen((float)(ViewPort2.Width / 2), (float)(ViewPort2.Height / 2), 0.0f);
//	
//	for (int index = 0; index <= 16; index++)
//	{
//		if (CGameString::g_pGameContext()->getMySlotInfo() != index)
//		{
//			if (CGameString::g_pGameContext()->getMySlotInfo() % 2 != index % 2)
//			{
//				D3DXVECTOR3 Screen((float)(Viewport.Width / 2), (float)(Viewport.Height / 2), 0.0f);
//				//D3DXVECTOR3 vBone, vScreen;
//				//GetUserBone(vBone, 7, index ) && !GetUserLife(CGameString::g_pGameContext()->getMySlotInfo()) ;
//
//				//if (WorldToScreen(i3RenderContext::Singleton()->pDevice,vBone, vScreen) && !GetUserLife(CGameString::g_pGameContext()->getMySlotInfo()))//*&&!GetMySlot()*/)/*&&!GetUserLife(index)*/
//				//{
//			
//	GetUserBone(vBone, 7, index) /*&& InVisible(index)*/;
//	
//	if (WorldToScreen2(i3RenderContext::Singleton()->pDevice,vBone, vScreen) && (InVisible(index) /*&& !GetUserLife(CGameString::g_pGameContext()->getMySlotInfo()*/))//*&&!GetMySlot()*/)/*&&!GetUserLife(index)*/
//				{
//
//					D3DXVECTOR3 Pos = (vScreen - Screen);
//					double Dist = ((Pos.x * Pos.x) + (Pos.y * Pos.y) + (Pos.z * Pos.z));
//					if (Dist < fMaxDistance)
//					{
//						fMaxDistance  = Dist;
//						iAimAt = index;
//					}
//				}
//			}
//		}
//	}
//	return iAimAt;
//	}
//D3DXVECTOR3 GetUserBonePos(int BoneIndex ,int index)
//{
//	D3DXVECTOR3 Out;// *(DWORD*)SOURCE GETUSERBONEPOS = 1 DOWRD USE  6 DOWRD  - 1 DWORD = 5 DWORD YO USE 5 DOWRD YOU POINTER
//	CGameCharaBoneContext* g_pCharaBase = (CGameCharaBoneContext*)( *(DWORD*)(*(DWORD*)(c_pCharaManager) + 0x14 + (index * 0xE0)) );
//	if (g_pCharaBase!=0)
//	{
//		D3DMATRIX Bone = g_pCharaBase->getBoneContext()->getArrayBones()[BoneIndex];
//		Out.x = Bone._41;
//		Out.y = Bone._42;
//		Out.z = Bone._43;
//	}
//	return Out;
//}	
//
//int GetPriorityTarget()
//{
//	int Result = -1;
//	float fMaxDistance = 1000.0f;
//		//D3DVIEWPORT9 ViewPort2;
//	//	i3RenderContext::Singleton()->pDevice->GetViewport(&ViewPort);
//	//	D3DXVECTOR3 vBone, vScreen;
//			D3DXVECTOR3 vStart,vEnd;
//	D3DXVECTOR3 vvStart,vvEnd;
//	D3DXVECTOR3 vBone, vScreen;
//	for (int index = 0; index < 16; index++)
//	{
//		if (!GetUserLife(index) && GetMyCharaIndex() != index )
//		{
//			if (GetMyCharaIndex() %2 != index % 2)
//			{
//				
//				D3DXVECTOR3 Screen((float)(Viewport.Width / 2), (float)(Viewport.Height / 2), 0.0f);
//				//D3DXVECTOR3 vBone, vScreen;
//				//GetUserBone(vBone, 7, index ) && !GetUserLife(CGameString::g_pGameContext()->getMySlotInfo()) ;
//
//				//if (WorldToScreen(i3RenderContext::Singleton()->pDevice,vBone, vScreen) && !GetUserLife(CGameString::g_pGameContext()->getMySlotInfo()))//*&&!GetMySlot()*/)/*&&!GetUserLife(index)*/
//				//{
//			
//	GetUserBone(vBone, 7, index) /*&& InVisible(index)*/;
//	
//	if (WorldToScreen(i3RenderContext::Singleton()->pDevice,vBone, vScreen) && (InVisible(index) /*&& !GetUserLife(CGameString::g_pGameContext()->getMySlotInfo()*/))//*&&!GetMySlot()*/)/*&&!GetUserLife(index)*/
//				{
//
//					D3DXVECTOR3 Pos = (vScreen - Screen);
//					double Dist = ((Pos.x * Pos.x) + (Pos.y * Pos.y) + (Pos.z * Pos.z));
//					if (Dist < fMaxDistance)
//					{
//						fMaxDistance  = Dist;
//						fMaxDistance = index;
//					}
//				}
//			}
//		}
//	}
//	return fMaxDistance;
//}
//int aimbot = 0;
//int AimLocal;
//int Accuracy;
////superaimbot? yes superaimot me crash :( :V waths aimbot you use wait
//void _stdcall AcurryHack(LPDIRECT3DDEVICE9 pDevice)
//{
//	
//	HookAim();	
//
//
//if(Accuracy==1 )
//{
//	 
//	BulletEnable = true;
//		D3DXVECTOR3 OnWorld, OnScreen;
//		 
//	
//				
//				int AimSlot =GetPriorityTarget() /*&& (InVisible(AimSlot)*/;
//	if ((AimSlot != -1) && (InVisible(AimSlot)))
//		{
//			int BoneIndexSelector = 0;
//			switch (AimLocal){
//			case 0: BoneIndexSelector = 7.7; break;
//			case 1: BoneIndexSelector = 5.9; break;
//			}
//			D3DXVECTOR3 vEn;
//			D3DXVECTOR3 OnWorld, OnScreen;
//		if (GetUserBone(vEn, BoneIndexSelector, AimSlot) /*&& !GetUserLife(CGameString::g_pGameContext()->getMySlotInfo()*/)
//			{
//						WorldToScreen2(i3RenderContext::Singleton()->pDevice, OnWorld, OnScreen);
//
//				{
//			
//	PrintTex("WANTED", OnScreen.x-10,OnScreen.y-15,YELLOW, pFonts);
//			DrawCircle(OnScreen.x,OnScreen.y,5,5,YELLOW);
//			BulletEnable = true;
//			//AimbotOff03 = true;
//			//GetUserBone(vEn, AimSlot,Aimbone);
//fX = vEn.x;
//fY = vEn.y+0.1f;
//fZ = vEn.z;
//			 		
//					}			
//			}
//			else BulletEnable = false;
//		}	
//		else BulletEnable = false;
//}}
//
//
//void _fastcall RebuildMenuOff()
//{
//	
//	if(getStageGame() == LOBBY)
//	{
//
//		    Cross			 = 0; 
//			
//			TrocaRapida1  = 0;	
//			
//			NoFallDamage  = 0; 
//			HackSpeed = 0; 
//			suicideplayers = 0;
//			NoRecargar =0;
//			fly = 0;
//			ESPBone			 = 0;
//			ESPLine			 = 0;
//			ESPHealth		 = 0;
//			ESPName			 = 0;
//		CH_ESPB3D			 = 0;	  
//			NoRecoil =0;
//			NoRecoilHROZ = 0;
////			MultiBalas =0;
//			//Accuracy = 0;
//		}
//	}
//
//void _fastcall RebuildMenuOff2()
//{
//	
//	if(getStageGame() == AGUARDANDO)
//	{
//
//		    Cross			 = 0; 
//			
//			TrocaRapida1  = 0;	
//			
//			NoFallDamage  = 0; 
//			HackSpeed = 0; 
//			suicideplayers = 0;
//			NoRecargar =0;
//			fly = 0;
//			ESPBone			 = 0;
//			ESPLine			 = 0;
//			ESPHealth		 = 0;
//			ESPName			 = 0;
//		CH_ESPB3D			 = 0;	 
//			NoRecoil =0;
//			NoRecoilHROZ = 0;
////			MultiBalas =0;
//			//Accuracy = 0;
//		}
//	}
//
//void _fastcall RebuildMenuOff3()
//{
//	
//	if(getStageGame() == CHANNEL)
//	{
//		 NoRecargar =0;
//		    Cross			 = 0; 
//			
//			TrocaRapida1  = 0;	
//			
//			NoFallDamage  = 0; 
//			HackSpeed = 0; 
//			suicideplayers = 0;
//			NoRecoilHROZ = 0;
//			fly = 0;
//			ESPBone			 = 0;
//			ESPLine			 = 0;
//			ESPHealth		 = 0;
//			ESPName			 = 0;
//		CH_ESPB3D			 = 0;	 
//			NoRecoil =0;
////			MultiBalas =0;
//		//	Accuracy = 0;
//		}
//	}
//
//
//
//
////
////
////////void __thiscall WeaponShotGunGenderWithDual::ReturnToReady(void)
//////DWORD SetBulletCountForNetwork = 0x95C8F50;
//////int UlimitedAmmo2;
//////inline void CallSetBulletCountForNetwork()
//////{
//////	if (UlimitedAmmo2)
//////	{
//////		
//////		      DWORD WeaponBase = *(DWORD*)(*(DWORD*)(c_pPlayer)+0x2C);
//////		      __asm 
//////		      {
//////			    push	30h
//////				push	30h
//////				push	30h
//////				mov	ecx, [WeaponBase]
//////				call	SetBulletCountForNetwork
//////		      }
//////	   
//////	}
//////}
////
////
//////#define g_pPlayUserDeath     0xCF5430
//////DWORD Cmd_Install = 0x674E5A1;// 6045F1;
//////DWORD Cmd_Uninstall = 0x62279E; //6EC63E;
//////int UninstallC4;
//////int InstallC4;
////#define VK_E 0x45
////#define VK_H 0x48
////		//AddyEngine->AddAddyByPattern("CGameCharaBase.Function.Cmd_Install", ADDY_FUNCTION_GETCALL, 6, NULL,"PointBlank.exe","74 1C 6A ?? 8B CF E8 ?? ?? ?? ?? 6A ?? 53 8B CE");	 //call de abajo
////		//AddyEngine->AddAddyByPattern("CGameCharaBase.Function.Cmd_Uninstall", ADDY_FUNCTION_GETCALL, 7, NULL,"PointBlank.exe","8B 0D ?? ?? ?? ?? 53 E8 ?? ?? ?? ?? 32 C0");	
//////void Install()
//////{
//////	if (InstallC4 && getStageGame() == JOGANDO && IsKeyPressed(VK_E, 1))
//////	{
//////		DWORD BasePlayer = *(DWORD*)c_pPlayer;
//////		__asm 
//////		{
//////			    push 0x1
//////				mov ecx, [BasePlayer]
//////				call[Cmd_Install]
//////		}
//////	}
////
////	/*if (UninstallC4 && getStageGame() == JOGANDO && IsKeyPressed(VK_H, 1))
////	{
////		DWORD Pointer = *(DWORD*)g_pPlayUserDeath;
////		__asm 
////		{
////
////			    mov ecx, [Pointer]
////				push ecx
////				call[Cmd_Uninstall]
////		}*/
////	//}
////
//////class CGameCharaBase
//////{
//////public:
//////
//////	bool Cmd_Install(){return ((bool(__thiscall*)(CGameCharaBase*, bool))0x90CE5A1)(this,true);}
//////
//////		
//////
//////};CGameCharaBase* g_pPlayers = NULL;
//////
//////class CGameCharaManager
//////{
//////public:
//////	
//////	
//////	CGameCharaBase* g_pPlayers(void)
//////	{
//////		return (CGameCharaBase*)(*(DWORD*)((DWORD)this+ 0x14)+(CGameString::g_pGameContext()->getMySlotInfo()* 0x11c));
//////	}
//////
//////	
//////
//////	
//////	static CGameCharaManager* g_pCharaManager()
//////	{
//////		return (CGameCharaManager*)(*(DWORD*)c_pCharaManager);
//////	}
//////}
////////
//////int DefuseBomb;
//////int PlantBomb;
//////	void CallPlantBomb()
//////{		
//////	//if (DefuseBomb){g_pMissionManager->Cmd_Uninstall();	}	
//////	
//////		if (PlantBomb == 1)
//////		{
//////			//DefuseBomb=true;
//////			if (IsKeyPressed(VK_E, 0))
//////			{
//////				//DefuseBomb=false;
//////				g_pPlayers->Cmd_Install();
//////			}
//////		}	
//////	}
//////
//////}
//////
////	void UpdateGameClass()
////{	
//////	GameEventSender* pGameEventSender;
////	pGameEventSender = (GameEventSender*)(GameEventSender::pGameEventSender);
////	//g_pCharaManager = (CGameCharaManager*)(CGameCharaManager::g_pCharaManager());
////
////	//g_pGameEventSender = (CGameEventSender*)(CGameEventSender::g_pGameEventSender());
////	//g_pGameStatus = (CGameStatus*)(CGameStatus::g_pGameStatus());
////	
////	/*if(g_pCharaManager->g_pPlayer())
////	{*/
////		//g_pWeaponBase = g_pCharaManager->g_pPlayer()->m_pWeaponContext();
////	//}
////}
////
////
//////######################### RPG Killer ############################
////
////
////bool RPG7x = false;
////int RPG7;
////
////class CGameCharaBase2
////{
////public:
////	
////	//536C51B
////	bool Cmd_Install(){return ((bool(__thiscall*)(CGameCharaBase2*, bool))0x900E5A1)(this,true);}//74 1C 6A ?? 8B CF E8 ?? ?? ?? ?? 6A ?? 53 8B CE
////	void SetCharaWeapon(DWORD WeaponByte){
////		return ((void(__thiscall*)(CGameCharaBase2*, int, DWORD))ResultRpgKiller)(this, NULL, WeaponByte);//
////	}
////
////
////
////	
////};CGameCharaBase2* g_pPlayerrpg = NULL;
////
////class CGameCharaManagerpg
////{
////public:
////	
////
////	CGameCharaBase2* g_pPlayerrpg(void)
////	{
////		return (CGameCharaBase2*)(*(DWORD*)(*(DWORD*)(c_pCharaManager) + 0x14 + (GetMySlot() * 0x11C)));
////	}
////
////	//DWORD CGameCharaBase = *(DWORD*)(*(DWORD*)(c_pCharaManager) + 0x14 + (Idx * 0x11C));
//// //   return ((DWORD (__thiscall *)(DWORD))SetCurHP)(CGameCharaBase);
////
////
////	static CGameCharaManagerpg* g_pCharaManagerr()
////	{
////		return 
////			(CGameCharaManagerpg*)(*(DWORD*)c_pCharaManager);
////	}
////};CGameCharaManagerpg* g_pCharaManagerr = NULL;
////
////
////
////
////bool RPG7X=false;
////void CallHack()
////{
////
////
////	if (RPG7==1)
////	{//0x1C522//0x5F61F82
////		if (IsKeyPressed(VK_F2,50))
////		{
////			g_pPlayerrpg->SetCharaWeapon(0x1C522);
////			//BombaHack_ON = 1;
////			//RPG7X=true;
////		//}else{if(RPG7X == true){RPG7X = false;}}
////	}
////	}}
////int DefuseBomb;
////int PlantBomb;
////	void CallHack2()
////{		
////	//if (DefuseBomb){g_pMissionManager->Cmd_Uninstall();	}	
////	
////		if (PlantBomb == 1)
////		{
////			//DefuseBomb=true;
////			if (IsKeyPressed(VK_E, 0))
////			{
////				//DefuseBomb=false;
////				g_pPlayerrpg->Cmd_Install();
////			}
////		}	
////	}
////
////
////	void UpdateGameClass()
////{	
////	
////	g_pPlayerrpg = (CGameCharaBase2*)(CGameCharaManagerpg::g_pCharaManagerr()->g_pPlayerrpg());
////	g_pCharaManagerr = (CGameCharaManagerpg*)(CGameCharaManagerpg::g_pCharaManagerr());
////
////	//g_pGameEventSender = (CGameEventSender*)(CGameEventSender::g_pGameEventSender());
////	//g_pGameStatus = (CGameStatus*)(CGameStatus::g_pGameStatus());
////	
////	/*if(g_pCharaManager->g_pPlayer())
////	{*/
////		//g_pWeaponBase = g_pCharaManager->g_pPlayer()->m_pWeaponContext();
////	//}
////	}
//int Aimboot;
//int AimBulletBone;
//int AimKey =0;
//
//inline int GetNearestToCrosshair()
//{
//	int Result = -1;
//	float fMaxDistance = 1000.0f;
//		//D3DVIEWPORT9 ViewPort2;
//	//	i3RenderContext::Singleton()->pDevice->GetViewport(&ViewPort);
//	//	D3DXVECTOR3 vBone, vScreen;
//			D3DXVECTOR3 vStart,vEnd;
//	D3DXVECTOR3 vvStart,vvEnd;
//	D3DXVECTOR3 vBone, vScreen;
//	for (int index = 0; index < 16; index++)
//	{
//		if (!GetUserLife(index) && GetMyCharaIndex() != index )
//		{
//			if (GetMyCharaIndex() %2 != index % 2)
//			{
//				D3DXVECTOR3 Screen((float)(Viewport.Width / 2), (float)(Viewport.Height / 2), 0.0f);
//				D3DXVECTOR3 vBone, vScreen;
//				GetUserBone(vBone, index, 7);
//				if (WorldToScreen2(i3RenderContext::Singleton()->pDevice, vBone, vScreen) && InVisible(index))
//				{
//					D3DXVECTOR3 Pos = (vScreen - Screen);
//					double Dist = ((Pos.x * Pos.x) + (Pos.y * Pos.y) + (Pos.z * Pos.z));
//					if (Dist < fMaxDistance)
//					{
//						fMaxDistance = Dist;
//						Result = index;
//					}
//				}
//			}
//		}
//	}
//	return Result;
//}
//inline void _stdcall CrossAimbot(LPDIRECT3DDEVICE9 pDevice)
//{
//	if (Aimboot && getStageGame() == JOGANDO)
//	{
//		if (GetNearestToCrosshair() != -1)
//		{
//			D3DXVECTOR3 OnWorld, OnScreen;
//			int BoneIndexSelector = 0;
//			switch (AimBulletBone)
//			{
//			case 0: BoneIndexSelector = 7; break;
//			case 1: BoneIndexSelector = 5; break;
//			}
//			GetUserBone(OnWorld, GetNearestToCrosshair(), BoneIndexSelector);
//			/*if (InVisible(GetNearestToCrosshair()) && InVisible(GetMySlot()))
//			{*/
//				WorldToScreen2(pDevice, OnWorld, OnScreen);
//				pDevice->GetViewport(&Viewport);
//				int curx = (int)OnScreen.x;
//				int cury = (int)OnScreen.y;
//				double DistX = (double)curx - Viewport.Width / 2.0f;
//				double DistY = (double)cury - Viewport.Height / 2.0f;
//				DistX /= (float)2;
//				DistY /= (float)2;
//				
//				if (AimKey == 1)
//				{
//				  if (Fun.AimKey == 0 && IsKeyPressed(VK_SHIFT, 1))
//				  {
//					if ((int)DistX > -249 && (int)DistY > -190)
//					{
//					   mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, NULL, NULL);
//					}
//				  }
//				}
//
//				if (AimKey == 0)
//				{
//				  if (Fun.AimKey == 0 && IsKeyPressed(VK_LBUTTON, 1))
//				  {
//					if ((int)DistX > -249 && (int)DistY > -190)
//					{
//					   mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, NULL, NULL);
//					}
//				  }
//				}
//
//		    	if (AimKey == 2)
//				{
//				  if (Fun.AimKey == 0 && IsKeyPressed(VK_MENU, 1))
//				  {
//					if ((int)DistX > -249 && (int)DistY > -190)
//					{
//					   mouse_event(MOUSEEVENTF_MOVE, (int)DistX, (int)DistY, NULL, NULL);
//					}
//				  }
//				}
//		
//
//			}
//		
//	}
//}

void Write_(void *Addres, int Byte)
{__try
{
DWORD OldProtect;
VirtualProtect(Addres, Byte, PAGE_EXECUTE_READWRITE, &OldProtect);
*(BYTE*)Addres=Byte;
VirtualProtect(Addres, Byte, PAGE_EXECUTE_READWRITE,&OldProtect);
}__except (EXCEPTION_EXECUTE_HANDLER){} 
}
bool CallerNoRecoil;
int NoRecoil;

void CallHack()
{

		if (NoRecoil) 
		{
			//34 02 00 00 8D 4C 24 34 83 C4 20 C7 84 24 2C 02 00 00 FF FF FF FF 3B C1 74 0F 8B 94 24 1C 02 00 00 42 52 50 E8 7B 97 //OFFSET
		//33 C4 50 8D 84 24 24 02 00 00 64 A3 00 00 00 00 8B B4 24 34 02 00 00 8B F9 83  +7B ->LOCAL
				
					Write_((void*)ResultGetOneVert,0xFF);
					Write_((void*)ResultGetOneHorz,0xFF);
					Write_((void*)ResultRecoilHorz,0xFF);
					Write_((void*)ResultRecoilVert,0xFF);
					

				}
			

	else

			{
				
					Write_((void*)ResultGetOneVert,0xFC);
					Write_((void*)ResultGetOneHorz,0xFC);
					Write_((void*)ResultRecoilHorz,0xFC);//33 C4 50 8D 84 24 24 02 00 00 64 A3 00 00 00 00 8B B4 24 34 02 00 00 8B F9 83  + 60
					Write_((void*)ResultRecoilVert,0xFC);
					
				}
			}