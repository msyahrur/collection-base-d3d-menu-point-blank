#include <windows.h>
#include "Hack.h"
#include "Texture.h"
#include "xMenu.h"
#include "TrialProtect.h"
#include "ColorByte.h"
#include "cMenuCC.h"
D3D9Menu	*_GyC = NULL;

LPDIRECT3DDEVICE9 npDevice, pGDevice; 
#define HOOK(func,addy) o##func = (t##func)DetourB8((DWORD)addy,(DWORD)hk##func,	12) 
#define UNHOOK(func,addy) o##func = (t##func)DetourB8((DWORD)addy,(DWORD)o##func,	12) 
int mx = 50; // POSISI AWAL MENU 84
int my = 50; // silahkan edit 100
int	d3d,ehack,phack,ahack,auhack,rhack;
int AimSlot,AimHead,AimHeadCrot = 0;
time_t TimeValue;
CHAR TimeAndDate[MAX_PATH];
INT Fps = 0;
FLOAT LastTickCount = 0.0f;
FLOAT CurrentTickCount;
CHAR FrameRate[50] = "";
//----------------------------------------------------------------------------//
class ClassGfx;
class ClassGfx
{
public:
char Fix[168];
DWORD cES;
char Mix[156];
DWORD cDip;
//char Lor[148];
//DWORD cLor;
};
#define hD3D "i3GfxDx.dll"
DWORD AdressAndByte,GetEngine,Calculate = NULL;

#define StartRoutine(Function) CreateThread(0,0,(LPTHREAD_START_ROUTINE)Function,0,0,0);

typedef HRESULT (WINAPI* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene;

typedef HRESULT (WINAPI* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
tDrawIndexedPrimitive oDrawIndexedPrimitive = NULL;

//------------------------------------------------------------------


void DrawLine(float x, float y, float x2, float y2, float width, DWORD color)
{
    D3DXVECTOR2 vLine[2];
    pLine->SetWidth( width );
    pLine->SetAntialias( false );
    pLine->SetGLLines( true );
    vLine[0].x = x;
    vLine[0].y = y;
    vLine[1].x = x2;
    vLine[1].y = y2;
    pLine->Begin();
    pLine->Draw( vLine, 2, color );
    pLine->End();
}
#define PISSS 3.14159265
void DrawSumer(int X, int Y, int radius, int numSides, DWORD Color) 
{ 

    D3DXVECTOR2 Line[130]; 
    float Step = PISSS * 2.0 / numSides; 
    int Count = 0; 
    for (float a=0; a < PISSS*2.0; a += Step) 
    { 
        float X1 = radius * cos(a) + X; 
        float Y1 = radius * sin(a) + Y; 
        float X2 = radius * cos(a+Step) + X; 
        float Y2 = radius * sin(a+Step) + Y; 
        Line[Count].x = X1; 
        Line[Count].y = Y1; 
        Line[Count+1].x = X2; 
        Line[Count+1].y = Y2; 
        Count += 2; 
    } 
    pLine->Begin(); 
    pLine->Draw(Line,Count,Color); 
    pLine->End(); 
}//wkwkw Lanjut Coding
void DrawXTarget(float x, float y, float x2, float y2, float width, DWORD color)//--Lanjut
{
    D3DXVECTOR2 vLine[2];
    pLine->SetWidth( width );
    pLine->SetAntialias( false );
    pLine->SetGLLines( true );
    vLine[0].x = x;
    vLine[0].y = y;
    vLine[1].x = x2;
    vLine[1].y = y2;
    pLine->Begin();
    pLine->Draw( vLine, 2, color );
    pLine->End();
}//Lanjut

//========================================================================
#define 	            MENUMAXINDEX	100
#define 	            MENUFOLDER		1
#define 	            MENUTEXT		2
//#define 	            MENUITEM		3
#define 	            MENUBASE		10
int Mpos=0;			  // current highlighted menuitem	
int Active=0;			  // number of menu items
int Mxofs =150;	  // 
int Mysize =17;  // heigh of a menuline
int ShowMenu = 1;
char Mtitle[81]= "";
//============================================
RECT rect,rect2,rect3;

struct{
int  *var;
int  maxvalue;
int  typ;
char *txt;
char **opt;
}
#define 	            MENUMAXINDEX	100
#define 	            MENUFOLDER		1
#define 	            MENUTEXT		2
#define 	            MENUITEM		3
#define 	            MENUBASE		10
//-------------------------------------------------------------------//
#define TEAL			D3DCOLOR_ARGB(255, 0,	255, 255)
#define PINK			D3DCOLOR_ARGB(255, 255, 240,   0)
#define LIME			D3DCOLOR_ARGB(255, 198, 255,   0)
#define SKYBLUE			D3DCOLOR_ARGB(255, 0,   180, 255)
#define MAROON			D3DCOLOR_ARGB(255, 142, 30,    0)
#define LGRAY			D3DCOLOR_ARGB(255, 174, 174, 174) 
#define DGRAY			D3DCOLOR_ARGB(255, 71,  65,   64) 
#define BROWN2			D3DCOLOR_ARGB(255, 77,  46,   38)
#define SHIT			D3DCOLOR_ARGB(255, 74,  38,   38) 
#define MCOLOR_TITLE    D3DCOLOR_ARGB(255, 255, 240,   0)//Orange
#define MCOLOR_CURRENT	D3DCOLOR_ARGB(255, 000, 255, 000)
#define MCOLOR_TEXT		D3DCOLOR_ARGB(255, 000, 255, 000)//Orange
#define MCOLOR_ACTIVE	D3DCOLOR_ARGB(255, 000, 255, 000)//Orange
#define MENUCOLOR_TITLE D3DCOLOR_ARGB(255, 255, 255, 000) 
#define MCOLOR_FOLDER	D3DCOLOR_ARGB(255, 000, 255, 000)//RED
#define MCOLOR_INACTIVE	D3DCOLOR_ARGB(255, 125, 000, 255)//Ungu
//------------------------------------------------------------------//
D3MENU[MENUMAXINDEX];
void DrawAddItem(char *txt, char **opt, int *var, int maxvalue, int typ){
  D3MENU[Active].typ=typ;
  D3MENU[Active].txt=txt;
  D3MENU[Active].opt=opt;
  D3MENU[Active].var=var;
  D3MENU[Active].maxvalue=maxvalue;
  Active++;
}
void DrawAddText(char *txt, char *opt){
  D3MENU[Active].typ=MENUTEXT;
  D3MENU[Active].txt=txt;
  D3MENU[Active].opt=(char **)opt;
  D3MENU[Active].var=0;
  D3MENU[Active].maxvalue=0;
  Active++;
}

void DrawMenuShow(LPDIRECT3DDEVICE9 pDevice,int x, int y,	ID3DXFont *pFont)
{

  int i, val;
  DWORD color;
    SetRect( &rect, x+Mxofs/2, y, x+Mxofs /2 , y );
  if (!ShowMenu) return;

  if (Mtitle[0]) {

	  pFont->DrawText(NULL,Mtitle,-1,&rect,DT_NOCLIP | DT_CENTER, MCOLOR_TITLE);

	  y+=Mysize;
  }
  for (i=0; i<Active; i++) {
	   val=(D3MENU[i].var)?(*D3MENU[i].var):0;
	   // determine color
       if (i==Mpos)
           color=MCOLOR_CURRENT;
       else if (D3MENU[i].typ==MENUFOLDER)
           color=MCOLOR_FOLDER;
       else if (D3MENU[i].typ==MENUTEXT)
           color=MCOLOR_TEXT;
       else
		   color=(val)?MCOLOR_ACTIVE:MCOLOR_INACTIVE;
     SetRect( &rect3, x, y, x , y );
     SetRect( &rect2, x+Mxofs, y, x+Mxofs , y );
	   pFont->DrawText(NULL,D3MENU[i].txt,-1,&rect3, DT_NOCLIP,color);
       if (D3MENU[i].opt) {
		   if (D3MENU[i].typ==MENUTEXT)
		   	   pFont->DrawText(NULL,(char *)D3MENU[i].opt,-1,&rect2, DT_NOCLIP | DT_RIGHT, color);
		   else
			   pFont->DrawText(NULL,(char *)D3MENU[i].opt[val],-1,&rect2, DT_NOCLIP | DT_RIGHT, color);
	   }
       y+=Mysize;
  }
}
void DrawMenuNav(LPDIRECT3DDEVICE9 pDevice)
{
	if (GetAsyncKeyState(VK_INSERT)&1) ShowMenu=(!ShowMenu);
	if (!ShowMenu) return;
	if (GetAsyncKeyState(VK_UP)&1) {
		do {
			Mpos--;
			if (Mpos<0)  Mpos=Active-1;
		} while (D3MENU[Mpos].typ==MENUTEXT);
	
	} else if (GetAsyncKeyState(VK_DOWN)&1) {
		do {
			Mpos++;
		    if (Mpos==Active) Mpos=0;
		} while (D3MENU[Mpos].typ==MENUTEXT);
  } else if (D3MENU[Mpos].var) {
		int dir=0;
		
		if (GetAsyncKeyState(VK_LEFT )&1 && *D3MENU[Mpos].var > 0                      ) dir=-1;
		
		if (GetAsyncKeyState(VK_RIGHT)&1 && *D3MENU[Mpos].var < (D3MENU[Mpos].maxvalue-1)) dir=1;
		if (dir) {
			*D3MENU[Mpos].var += dir;
			if (D3MENU[Mpos].typ==MENUFOLDER) Active=0;
		}
	}
}
/********************************************************************************/
char *optColor1[12] = {"OFF","RED","BLUE","GREEN","AQUA","PURPLE","WHITE","YELLOW","PINK","TURQUOISE","ORANGE","BLACK"};
char *Moptfolder1[2] = {"OPEN", "CLOSE"};
char *Moptonoff[2]  = {"OFF", "ON"};
char *MoptAimlock []  = {"OFF", "ON"};
char *MoptAutohs []  = {"OFF", "ON"};
char *MoptTarget []  = {"Head", "Boddy"};
char *MoptAimbullet []  = {"OFF", "ON"};
char *MoptAa[2]  = {"OFF", "ON"};
char *MoptAa2[2]  = {"OFF", "ON"};
char *MoptAa3[2]  = {"F5", "F5"};

int Box1 = 0;
int Box2 = 0;
int Box3 = 0;
int Box5 = 0;
int Box6 = 0;
int uyeh = 0;
int Box7 ,Box4= 0;
int BoxAem=0;
void DrawRebuildMenu(LPDIRECT3DDEVICE9 pDevice)
{
	    strcpy(Mtitle,"Zona X Sytem");
		DrawAddText("","");
		DrawAddText("","");
		//DrawAddItem("Easy Menu"    ,Moptfolder, &Folder1, 2, MENUFOLDER);
	//if (Folder1)
	//{ 
		DrawAddItem("Wallhack",           Moptonoff , &WallCrot  , 2 , MENUBASE);
		DrawAddItem("Wallhack Glass",             Moptonoff , &Weapon ,   2 , MENUBASE);
		DrawAddItem("Chams TR ",                 optColor1 , &ChamsTR  , 12, MENUBASE);
		DrawAddItem("Chams CT ",                 optColor1 , &ChamsCT   ,12, MENUBASE);
		DrawAddItem("Chams Weapon",             Moptonoff , &chamsWeapon ,   2 , MENUBASE);
		DrawAddItem("NoSmoke",            Moptonoff , &UnSmoke   , 2 , MENUBASE);
		DrawAddItem("NoFog",              Moptonoff , &NoFog     , 2 , MENUBASE);
		DrawAddItem("CrossHair",          Moptonoff , &CrossEnds , 2 , MENUBASE);
		DrawAddItem("Time & Date",          Moptonoff , &DateTimes , 2 , MENUBASE);
//	}

//	DrawAddItem("DMS Hack"    ,Moptfolder, &Folder4, 2, MENUFOLDER);
//	if (Folder4)
	//{ 	
		DrawAddItem("Aim Bullet",          Moptonoff , &Accuracy  , 2 , MENUBASE);

		DrawAddText("Fast Exit : F12","");
	
	//}
}





//------------------------------ Date & Times
void Times(int x,int y,D3DCOLOR color)
{
	static char cdate[20] = "" ;
	char *logbuf = new char[ 500 ];
	struct tm * current_tm;
	RECT FontPos = { x, y, x + 1000, y + 500 };
	time_t current_time;
	time (&current_time);
	current_tm = localtime (&current_time);
	char *month	[]={"Januari","Februari","Maret","April","Mei","Juni","Juli","Agustus","September","Oktober","November","Desember"};
	sprintf( cdate,"=>Welcome->DAPET BASE BILANG TQ :V <= - %02d %s 20%d - %02d:%02d:%02d",current_tm->tm_mday,month[current_tm->tm_mon],current_tm->tm_year-100, current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec);
	fName->DrawTextA(NULL, cdate, -1, &FontPos, DT_NOCLIP, color); 
}
//-----------------------------------------------------------------------------------------------------------------------------------
HRESULT WINAPI hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
while(!npDevice) {
npDevice = pDevice;                      
}
Accuracy_Hack(pDevice);
if(texRed == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bRed, sizeof(bRed), &texRed);
	if(texBlue == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bBlue, sizeof(bBlue), &texBlue);
	if(texGreen == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bGreen, sizeof(bGreen), &texGreen);
	if(texAqua == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bAqua, sizeof(bAqua), &texAqua);
	if(texPurple == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bPurple, sizeof(bPurple), &texPurple);
	if(texWhite == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bWhite, sizeof(bWhite), &texWhite);
	if(texYellow == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bYellow, sizeof(bYellow), &texYellow);
	if(texPink == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bPink, sizeof(bPink), &texPink);
	if(texTurquoise == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bTurquoise, sizeof(bTurquoise), &texTurquoise);
	if(texOrange == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bOrange, sizeof(bOrange), &texOrange);
	if(texBlack == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bBlack, sizeof(bBlack), &texBlack);

if ( RenderText == 1 ) {
D3DXCreateFontA(pDevice, 18, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &pFonts );
RenderText = 0;
}
//======================================================== Date & Times ===========================================================
if(DateTimes)
{
Times(450,752,PINK);
}
//======================================================== CALL DRAW MENU =========================================================
//-------------------------Void--Exit--Game--------------//
if(GetAsyncKeyState(VK_F12)&1){
ExitProcess(0);
}




//----------Batas Void--------------------//
pDevice->GetViewport(&g_ViewPort);
if(!fName)  D3DXCreateFont(pDevice, 13, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &fName);//15
if(!fSmall) D3DXCreateFont(pDevice, 11, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &fSmall);//18
if(!Title)	D3DXCreateFont(pDevice, 18, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &Title);//13
if(!pLine)	D3DXCreateLine( pDevice, &pLine );
if(uyeh == 0)
{
if (Active==0) 
DrawRebuildMenu(pDevice);
DrawMenuShow(pDevice,50,70,pFonts);
DrawMenuNav(pDevice);
}



return oEndScene(pDevice);
}

bool XStrWarna = true;
IDirect3DPixelShader9 *WarnaIjo, *WarnaBiru, *WarnaOrens, *WarnaUngu, *WarnaMerah, *WarnaPutih, *WarnaKuning, *WarnaHitam;
HRESULT HackTaxture(IDirect3DPixelShader9 **LegendOfIndonesia, IDirect3DDevice9 *Device, float red, float green, float blue, float alpha )
{
    ID3DXBuffer *FrediAP = NULL;
    char MyShader[ 256 ];
    sprintf( MyShader, "ps.1.1\ndef c0, %f, %f, %f, %f\nmov r0,c0", red/255, green/255, blue/255, alpha/255 );
    D3DXAssembleShader( MyShader, sizeof( MyShader ), NULL, NULL, 0, &FrediAP , NULL );
    if( FAILED( Device->CreatePixelShader((const DWORD*)FrediAP ->GetBufferPointer(), LegendOfIndonesia)) )return E_FAIL;
    return S_OK;
}
//-------------------------------------------------------------------------------///
DWORD CallpDevice;
HRESULT WINAPI hkDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{  
if(pDevice->GetStreamSource(0, &Stream_Data, &Offset, &Stride) == D3D_OK)
Stream_Data->Release();


if(XStrWarna)
{
HackTaxture( &WarnaBiru,	pDevice, 0, 0, 255 , 255 );
HackTaxture( &WarnaIjo,		pDevice, 0, 255, 0,255 );
HackTaxture( &WarnaOrens,	pDevice, 255, 128, 0,255 );
HackTaxture( &WarnaUngu,	pDevice, 255, 0, 255,255 );
HackTaxture( &WarnaMerah,	pDevice, 255, 0, 0, 255 );
HackTaxture( &WarnaPutih,	pDevice, 255, 255, 255,255 );
HackTaxture( &WarnaKuning,	pDevice, 255, 255, 0 , 255);
HackTaxture( &WarnaHitam,	pDevice, 0, 0, 0 , 255 );
XStrWarna=false;
}
//------------------------------------------//
if(WallCrot){
CallpDevice = 1;
pDevice->SetRenderState(D3DRS_ZENABLE,CallpDevice);
}

if(WallCrot){
if (allp){
CallpDevice = 0;
pDevice->SetRenderState(D3DRS_ZENABLE,CallpDevice);
}
}

if(Weapon)
	{
		if(allp)   
	 {            
		pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
        oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
		 
		}}

if(ChamsCT){
		if(playersswat)         
		{
			pDevice->SetRenderState(D3DRS_ZENABLE, false);
			if(ChamsCT ==1) pDevice->SetTexture(0, texRed);
			if(ChamsCT ==2) pDevice->SetTexture(0, texBlue);
			if(ChamsCT ==3) pDevice->SetTexture(0, texGreen);
			if(ChamsCT ==4) pDevice->SetTexture(0, texAqua);
			if(ChamsCT ==5) pDevice->SetTexture(0, texPurple);
			if(ChamsCT ==6) pDevice->SetTexture(0, texWhite);
			if(ChamsCT ==7) pDevice->SetTexture(0, texYellow);
			if(ChamsCT ==8) pDevice->SetTexture(0, texPink);		
			if(ChamsCT ==9) pDevice->SetTexture(0, texTurquoise);
			if(ChamsCT ==10) pDevice->SetTexture(0, texOrange);
			if(ChamsCT ==11) pDevice->SetTexture(0, texBlack);
			oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
			if(ChamsCT2 ==1) pDevice->SetTexture(0, texRed);
			if(ChamsCT2 ==2) pDevice->SetTexture(0, texBlue);
			if(ChamsCT2 ==3) pDevice->SetTexture(0, texGreen);
			if(ChamsCT2 ==4) pDevice->SetTexture(0, texAqua);
			if(ChamsCT2 ==5) pDevice->SetTexture(0, texPurple);
			if(ChamsCT2 ==6) pDevice->SetTexture(0, texWhite);
			if(ChamsCT2 ==7) pDevice->SetTexture(0, texYellow);
			if(ChamsCT2 ==8) pDevice->SetTexture(0, texPink);		
			if(ChamsCT2 ==9) pDevice->SetTexture(0, texTurquoise);
			if(ChamsCT2 ==10) pDevice->SetTexture(0, texOrange);
			if(ChamsCT2 ==11) pDevice->SetTexture(0, texBlack);
			pDevice->SetRenderState(D3DRS_ZENABLE, true);
		}
	}
	if(ChamsTR){
		if(playersterror)			
		{
			pDevice->SetRenderState(D3DRS_ZENABLE, false);	
			if(ChamsTR ==1) pDevice->SetTexture(0, texRed);
			if(ChamsTR ==2) pDevice->SetTexture(0, texBlue);
			if(ChamsTR ==3) pDevice->SetTexture(0, texGreen);
			if(ChamsTR ==4) pDevice->SetTexture(0, texAqua);
			if(ChamsTR ==5) pDevice->SetTexture(0, texPurple);
			if(ChamsTR ==6) pDevice->SetTexture(0, texWhite);
			if(ChamsTR ==7) pDevice->SetTexture(0, texYellow);
			if(ChamsTR ==8) pDevice->SetTexture(0, texPink);		
			if(ChamsTR ==9) pDevice->SetTexture(0, texTurquoise);
			if(ChamsTR ==10) pDevice->SetTexture(0, texOrange);
			if(ChamsTR ==11) pDevice->SetTexture(0, texBlack);
			oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);		
			if(ChamsTR2 ==1) pDevice->SetTexture(0, texRed);
			if(ChamsTR2 ==2) pDevice->SetTexture(0, texBlue);
			if(ChamsTR2 ==3) pDevice->SetTexture(0, texGreen);
			if(ChamsTR2 ==4) pDevice->SetTexture(0, texAqua);
			if(ChamsTR2 ==5) pDevice->SetTexture(0, texPurple);
			if(ChamsTR2 ==6) pDevice->SetTexture(0, texWhite);
			if(ChamsTR2 ==7) pDevice->SetTexture(0, texYellow);
			if(ChamsTR2 ==8) pDevice->SetTexture(0, texPink);		
			if(ChamsTR2 ==9) pDevice->SetTexture(0, texTurquoise);
			if(ChamsTR2 ==10) pDevice->SetTexture(0, texOrange);
			if(ChamsTR2 ==11) pDevice->SetTexture(0, texBlack);
			pDevice->SetRenderState(D3DRS_ZENABLE, true);
		}
	}

if(chamsWeapon)
{
	if(Weaponz){
npDevice->SetRenderState( D3DRS_ZENABLE, false ); 
npDevice->SetPixelShader( WarnaHitam );
oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount); 
npDevice->SetRenderState( D3DRS_ZENABLE, true ); 
npDevice->SetPixelShader( WarnaMerah ); 


		}}

if(UnSmoke){
if ((NumVertices == 192) || (NumVertices == 256))	  
{
return D3D_OK;
return 0;
}
}

if(NoFog)
{
pDevice->SetRenderState(D3DRS_FOGENABLE, false);
}
return oDrawIndexedPrimitive(pDevice, PrimType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}//*/

void Kampret(PDWORD target, PDWORD newfunc)
{
DWORD Jmpto=(DWORD)(newfunc)-(DWORD)target-5;
DWORD a;
VirtualProtect(target, 8, PAGE_EXECUTE_READWRITE, &a);
*(PBYTE)(target)=0xE9;
*(PDWORD)((DWORD)(target)+1)=Jmpto;
VirtualProtect(target, 8, a, &a);
}
void patchPTR(unsigned long adr, unsigned long Ofset, DWORD dwValue)
{ DWORD A=0;
if (IsBadReadPtr((PDWORD)adr,4)==0)
{ A=*(PDWORD)((DWORD)(adr))+Ofset;
if (IsBadReadPtr((PDWORD)A,4)==0)
{*(PDWORD)A=dwValue;
}}}
class EngineHook
{
public:
char unk1[21376];
LPDIRECT3DDEVICE9 DeviceGame;
char unk2[168];
DWORD EndScence;
char unk3[158];
DWORD DrawPrimIndx;
};
class CD3D9
{
public:
char _0x0000[168];
DWORD dwES;
char _0x00AC[156];
DWORD dwDIP;
};
void MoveMemo(void *adr, void *ptr, int size)
{
DWORD NextProtection;
VirtualProtect(adr,size,PAGE_EXECUTE_READWRITE, &NextProtection);
Sleep(1);
//Sleep(1);
MoveMemory((void *)(adr),(int*)(PBYTE)"\x89\x8B\x38",3);
Sleep(1);
//Sleep(1);
VirtualProtect(adr,size,NextProtection, &NextProtection);
}
void _PrivateOnly(void *adr, void *ptr, int size)
{
DWORD NextProtection;
VirtualProtect(adr,size,PAGE_EXECUTE_READWRITE, &NextProtection);
Sleep(1);
//Sleep(1);
RtlCopyMemory(adr,ptr,size);
//RtlCopyMemory((void *)(adr + 0x68876F),(int*)(PBYTE)"\xBE",1);
Sleep(1);
//Sleep(1);
VirtualProtect(adr,size,NextProtection, &NextProtection);
}

DWORD hGfxDx = (DWORD)GetModuleHandle("i3GfxDx.dll");
DWORD WINAPI HookKampret(LPVOID Param)
{

if (hGfxDx > 0){
DWORD tmp1 = (DWORD)(hGfxDx + 0x1EA7B0);
DWORD tmp2 = 0;
Sleep(1);
while(!npDevice)
{
if(IsBadReadPtr((PDWORD)tmp1,4)==NULL)tmp2 = *(PDWORD)((DWORD)(tmp1))+ 0x53A8;//0x544C;
Sleep(1);
if(IsBadReadPtr((PDWORD)tmp2,4)==NULL)
{
Sleep(1);
DWORD OldProtect;
VirtualProtect((void*)(tmp2), 4, PAGE_EXECUTE_READWRITE, &OldProtect);
memcpy(&npDevice, (void *)tmp2, 4);
VirtualProtect((void*)(tmp2), 4, OldProtect, NULL);
}}
Sleep(1);
DWORD *g_pDevice = (DWORD*)npDevice;
g_pDevice = (DWORD*)g_pDevice[0];


*(PDWORD)&oEndScene = g_pDevice[42];
*(PDWORD)&oDrawIndexedPrimitive = g_pDevice[82];
Sleep(1);
Kampret((PDWORD)(g_pDevice[1] - 5), (PDWORD)(g_pDevice[4] - 5));
Sleep(1);
Kampret((PDWORD)(g_pDevice[2] - 5), (PDWORD)(g_pDevice[5] - 5));
Sleep(1);
Kampret((PDWORD)(g_pDevice[3] - 5), (PDWORD)(g_pDevice[6] - 5));
Sleep(1);
Kampret((PDWORD)(g_pDevice[4] - 5), (PDWORD)hkEndScene);
Sleep(1);
Kampret((PDWORD)(g_pDevice[5] - 5), (PDWORD)hkDrawIndexedPrimitive);
Sleep(1);
while(1)
{
g_pDevice[42] = (DWORD)g_pDevice[1] - 5;
g_pDevice[82] = (DWORD)g_pDevice[2] - 5;
Sleep(1000);
}}
return 0;
}
//--------------------------------------------------------------------//


void *DetourCreateFAKE(BYTE *src, const BYTE *dst, const int len)
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
BOOL bCompareFAKE(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
for(;*szMask;++szMask,++pData,++bMask)
if(*szMask=='x' && *pData!=*bMask) 
return false;
return (*szMask) == NULL;
}
DWORD FindPatternFAKE(DWORD dwAddress,DWORD dwLen,BYTE *bMask,char * szMask)
{
	for(DWORD i=0; i < dwLen; i++)
		if( bCompareFAKE((BYTE*)(dwAddress+i),bMask,szMask))
			return (DWORD)(dwAddress+i);

	return 0;
}
//=============================================//
typedef HRESULT(APIENTRY* oPresent) (IDirect3DDevice9*, const RECT *, const RECT *, HWND, const RGNDATA *);
HRESULT APIENTRY Present_hook(IDirect3DDevice9*, const RECT *, const RECT *, HWND, const RGNDATA *);
oPresent pPresent = 0;
//=============================================//
HRESULT APIENTRY Present_hook(IDirect3DDevice9* pDevice, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
{
 //menu...


	
if(texRed == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bRed, sizeof(bRed), &texRed);
	if(texBlue == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bBlue, sizeof(bBlue), &texBlue);
	if(texGreen == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bGreen, sizeof(bGreen), &texGreen);
	if(texAqua == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bAqua, sizeof(bAqua), &texAqua);
	if(texPurple == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bPurple, sizeof(bPurple), &texPurple);
	if(texWhite == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bWhite, sizeof(bWhite), &texWhite);
	if(texYellow == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bYellow, sizeof(bYellow), &texYellow);
	if(texPink == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bPink, sizeof(bPink), &texPink);
	if(texTurquoise == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bTurquoise, sizeof(bTurquoise), &texTurquoise);
	if(texOrange == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bOrange, sizeof(bOrange), &texOrange);
	if(texBlack == NULL) D3DXCreateTextureFromFileInMemory(pDevice, (LPCVOID)&bBlack, sizeof(bBlack), &texBlack);

if ( RenderText == 1 ) {
D3DXCreateFontA(pDevice, 18, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &pFonts );
RenderText = 0;
}
//======================================================== Date & Times ===========================================================
if(DateTimes)
{
Times(450,752,PINK);
}
//======================================================== CALL DRAW MENU =========================================================
//-------------------------Void--Exit--Game--------------//
if(GetAsyncKeyState(VK_F12)&1){
ExitProcess(0);
}




//----------Batas Void--------------------//
pDevice->GetViewport(&g_ViewPort);
if(!fName)  D3DXCreateFont(pDevice, 13, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &fName);//15
if(!fSmall) D3DXCreateFont(pDevice, 11, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &fSmall);//18
if(!Title)	D3DXCreateFont(pDevice, 18, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &Title);//13
if(!pLine)	D3DXCreateLine( pDevice, &pLine );
if(uyeh == 0)
{
if (Active==0) 
DrawRebuildMenu(pDevice);
DrawMenuShow(pDevice,50,70,pFonts);
DrawMenuNav(pDevice);
}




  return pPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}
//=============================================//
DWORD*vtbl=0;
DWORD end,pre;
int HookpDevice(void)
{
DWORD hD3D9=(DWORD)LoadLibraryA("d3d9.dll");
DWORD table=FindPatternFAKE(hD3D9,0x128000,(PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86","xx????xx????xx");
 
memcpy(&vtbl,(void*)(table+2),4); 
pre = vtbl[17];  
pPresent=(oPresent)DetourCreateFAKE((PBYTE)pre,(PBYTE)Present_hook,5); 
return 0;
}
//=============================================//
bool ck =true;
BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
DisableThreadLibraryCalls(hDll);
if (dwReason==DLL_PROCESS_ATTACH)
{
CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)HookpDevice,NULL,NULL,NULL); 
}
return TRUE;
}





//BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
//{
//DisableThreadLibraryCalls(hDll);
//if (dwReason == DLL_PROCESS_ATTACH)
//{
//	//MessageBox (0, "Selamat Menggunakan Cheat VIP kami"," Torial ", MB_OKCANCEL|MB_ICONINFORMATION);
//	//MessageBox (0, "Jika Ada masalah contek Fahmi Andrian"," Fahmi Andrian ", MB_OKCANCEL|MB_ICONINFORMATION);
//
////StartRoutine(dltProtectRemote);//------------>Remote Hosting
////StartRoutine(CheckValidHardwareID);//-Remote HWID
//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HookKampret, 0, 0, 0);
////StartRoutine(ThreadFloodVK);
//
////StartRoutine(HookSuicide);
////StartRoutine(HOOKAIM);
////StartRoutine(HOOKAIMLOCK);
////StartRoutine (HOOKAUTOSHOT);
//}
//return TRUE;
//}
#include "Internal.h"

