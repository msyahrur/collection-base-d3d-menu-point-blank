#include <windows.h>
#include <process.h>
#include <d3d9.h>

#include <d3dx9.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma warning(disable:4244 4996 4101)

#ifndef __VIRTUALIZERSDK__

#define __VIRTUALIZERSDK__

 #ifdef __BORLANDC__

 extern "C" _stdcall __declspec(dllimport) void VirtualizerStart(void);

 extern "C" _stdcall __declspec(dllimport) void VirtualizerEnd(void);

 extern "C" _stdcall __declspec(dllimport) void VirtualizerMutate1Start(void);

 extern "C" _stdcall __declspec(dllimport) void VirtualizerMutate2Start(void);

 extern "C" _stdcall __declspec(dllimport) void VirtualizerMutate3Start(void);
 
 #else

 extern "C" void _stdcall VirtualizerStart(void);

 extern "C" void _stdcall VirtualizerEnd(void);

 extern "C" void _stdcall VirtualizerMutate1Start(void);

 extern "C" void _stdcall VirtualizerMutate2Start(void);

 extern "C" void _stdcall VirtualizerMutate3Start(void);

 #endif


/* Definition for Borland C/C++  */

#ifdef __BORLANDC__
 
 #define VIRTUALIZER_START __emit__ (0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x0C, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20);
 #define VIRTUALIZER_END  __emit__ (0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x0D, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20);
 #define VIRTUALIZER_MUTATE1_START __emit__ (0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x0C, 0x00, 0x00, 0x00, \
                                    0x01, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20);
 #define VIRTUALIZER_MUTATE2_START __emit__ (0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x0C, 0x00, 0x00, 0x00, \
                                    0x02, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20);
 #define VIRTUALIZER_MUTATE3_START __emit__ (0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x0C, 0x00, 0x00, 0x00, \
                                    0x03, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20);
 #define __VIRTUALIZER_MACROS__

 #endif


/* Definition for Intel cpp compiler */
 
#ifndef __VIRTUALIZER_MACROS__
 
 #ifdef __ICL
 
 #define VIRTUALIZER_START \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x43 \
  __asm __emit 0x56\
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x0C \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x43 \
  __asm __emit 0x56 \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
 
 #define VIRTUALIZER_END \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x43 \
  __asm __emit 0x56 \
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x0D \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x43 \
  __asm __emit 0x56 \
  __asm __emit 0x20 \
  __asm __emit 0x20 \

  #define VIRTUALIZER_MUTATE1_START \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x43 \
  __asm __emit 0x56\
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x0C \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x01 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x43 \
  __asm __emit 0x56 \
  __asm __emit 0x20 \
  __asm __emit 0x20 \

  #define VIRTUALIZER_MUTATE2_START \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x43 \
  __asm __emit 0x56\
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x0C \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x02 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x43 \
  __asm __emit 0x56 \
  __asm __emit 0x20 \
  __asm __emit 0x20 \

  #define VIRTUALIZER_MUTATE3_START \
  __asm __emit 0xEB \
  __asm __emit 0x10 \
  __asm __emit 0x43 \
  __asm __emit 0x56\
  __asm __emit 0x20 \
  __asm __emit 0x20 \
  __asm __emit 0x0C \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x03 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x00 \
  __asm __emit 0x43 \
  __asm __emit 0x56 \
  __asm __emit 0x20 \
  __asm __emit 0x20 \

 #define __VIRTUALIZER_MACROS__
 
 #endif

#endif
 
 
/* Definition for LCC by Jacob Navia */
 
#ifndef __VIRTUALIZER_MACROS__
 
 #ifdef __LCC__
 
 #define VIRTUALIZER_START __asm__ (" .byte\t0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x0C, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");
 #define VIRTUALIZER_END  __asm__ (" .byte\t0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x0D, 0x00, 0x00, 0x00, \
                                    0x00, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");
 #define VIRTUALIZER_MUTATE1_START __asm__ (" .byte\t0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x0C, 0x00, 0x00, 0x00, \
                                    0x01, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");
 #define VIRTUALIZER_MUTATE2_START __asm__ (" .byte\t0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x0C, 0x00, 0x00, 0x00, \
                                    0x02, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");
 #define VIRTUALIZER_MUTATE3_START __asm__ (" .byte\t0xEB, 0x10, 0x43, 0x56, 0x20, 0x20, 0x0C, 0x00, 0x00, 0x00, \
                                    0x03, 0x00, 0x00, 0x00, 0x43, 0x56, 0x20, 0x20");
 
 #define __VIRTUALIZER_MACROS__
 
 #endif
 
#endif
 

/* Definition for Visual C++ and others */

#ifndef __VIRTUALIZER_MACROS__
 
 #define VIRTUALIZER_START \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x43 \
  __asm _emit 0x56 \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x0C \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x43 \
  __asm _emit 0x56 \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
 
 #define VIRTUALIZER_END \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x43 \
  __asm _emit 0x56 \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x0D \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x43 \
  __asm _emit 0x56 \
  __asm _emit 0x20 \
  __asm _emit 0x20 \

  #define VIRTUALIZER_MUTATE1_START \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x43 \
  __asm _emit 0x56 \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x0C \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x01 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x43 \
  __asm _emit 0x56 \
  __asm _emit 0x20 \
  __asm _emit 0x20 \

  #define VIRTUALIZER_MUTATE2_START \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x43 \
  __asm _emit 0x56 \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x0C \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x02 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x43 \
  __asm _emit 0x56 \
  __asm _emit 0x20 \
  __asm _emit 0x20 \

  #define VIRTUALIZER_MUTATE3_START \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x43 \
  __asm _emit 0x56 \
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x0C \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x03 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x43 \
  __asm _emit 0x56 \
  __asm _emit 0x20 \
  __asm _emit 0x20 \

 #endif

#endif
#define WHITE			D3DCOLOR_ARGB(255, 255, 255, 255)
#define RED				D3DCOLOR_ARGB(255, 245, 000, 000)
#define GREEN			D3DCOLOR_ARGB(255, 000, 255, 000)
#define BLUE			D3DCOLOR_ARGB(255, 000, 000, 255) 
#define BLACK			D3DCOLOR_ARGB(150, 000, 000, 000)
#define mBLACK			D3DCOLOR_ARGB(100, 000, 000, 205)
#define PURPLE			D3DCOLOR_ARGB(255, 125, 000, 255) 
#define GREY			D3DCOLOR_ARGB(255, 128, 128, 128) 
#define YELLOW			D3DCOLOR_ARGB(255, 255, 255, 000) 
#define ORANGE			D3DCOLOR_ARGB(255, 255, 125, 000)
#define WHITE2			D3DCOLOR_ARGB(100, 255, 255, 255)
#define RED2			D3DCOLOR_ARGB(255, 255, 000, 000)
#define GREEN2			D3DCOLOR_ARGB(100, 000, 255, 000)
#define BLUE2			D3DCOLOR_ARGB(100, 000, 000, 255) 
#define BLACK2			D3DCOLOR_ARGB(100, 000, 000, 000)
#define PURPLE2			D3DCOLOR_ARGB(100, 125, 000, 255) 
#define GREY2			D3DCOLOR_ARGB(100, 128, 128, 128) 
#define YELLOW2			D3DCOLOR_ARGB(100, 255, 255, 000) 
#define ORANGE2			D3DCOLOR_ARGB(100, 255, 125, 000)
#define SKYBLUE			D3DCOLOR_ARGB(255, 0,   180, 255)
#define LGRAY		    D3DCOLOR_ARGB(255, 174, 174, 174)  
#define DARKBLUE		D3DCOLOR_ARGB(255, 0,   0,   153) 
#define LIGHTBLUE		D3DCOLOR_ARGB(255, 19, 84, 199) 
#define MAROON			D3DCOLOR_ARGB(255, 142, 30, 0)
#define POLICE          D3DCOLOR_ARGB(255, 125, 160, 200)
#define TERORI          D3DCOLOR_ARGB(255, 225, 100, 100)
//#define MENUCOLOR_TITLE	0xffff1111//#define MENUCOLOR_TITLE	D3DCOLOR_ARGB(255, 255, 000, 000)
#define 	ANJING			1
int 		Mmax=0;			  // number of menu items

#ifndef __VIRTUALKEYBOARD__
#define __VIRTUALKEYBOARD__
typedef SHORT(__stdcall* MyHotKey)(int);
MyHotKey oMyHotKey;



SHORT  Initialize_HookedMyHotkey(void)
{
	BYTE * pGAKS = reinterpret_cast<BYTE*>(GetAsyncKeyState);
	BYTE Orig[10];
	memcpy(Orig, pGAKS, 10);
	bool bChanged = false;
	while (!bChanged)
	{
		for (UINT i = 0; i != 10; ++i)
			if (pGAKS[i] != Orig[i])
				bChanged = true;
		Sleep(100);
	}
	DWORD dwOld = 0;
	VirtualProtect(pGAKS, 10, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy(pGAKS, Orig, 10);
	VirtualProtect(pGAKS, 10, dwOld, &dwOld);
	return TRUE;
}

static struct key_s
{
	bool bPressed;
	DWORD dwSTime;
}
kPressed[256];
SHORT IsKeyPressed(int Key, DWORD dwT){
	VIRTUALIZER_START VIRTUALIZER_MUTATE1_START	VIRTUALIZER_MUTATE2_START VIRTUALIZER_MUTATE3_START
	oMyHotKey = (MyHotKey)GetAsyncKeyState;
	if (HIWORD(oMyHotKey(Key)))
	{
		if (!kPressed[Key].bPressed || (kPressed[Key].dwSTime && (kPressed[Key].dwSTime + dwT) <= GetTickCount()))
		{
			kPressed[Key].bPressed = TRUE;
			if (dwT > NULL)
				kPressed[Key].dwSTime = GetTickCount();
			return TRUE;
		}
	}
	else
		kPressed[Key].bPressed = FALSE;
	return FALSE;
	VIRTUALIZER_END	
}

#endif
//=>
char *Moptfolder        []  = {"[0/1]", "[1/1]"}; 
char *Moptonoff         []  = {"Off", "On"};

char *MoptonoffAIM   []  = {"Off", "On", };
char *MoptonoffAIM2  []  = {"Head", "Body"};
//=>
ID3DXFont* pFont = NULL;
LPD3DXLINE pLine = NULL;
//D3DVIEWPORT9 Viewport;
typedef HRESULT (WINAPI* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene;

typedef HRESULT (WINAPI* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
tDrawIndexedPrimitive oDrawIndexedPrimitive = NULL;

typedef HRESULT(WINAPI* tReset)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
tReset oReset = NULL;

LPDIRECT3DVERTEXBUFFER9 Stream_Data;
UINT Offset = 0;
UINT Stride = 0;
//-----------------------------------------------------
//RECT rect,rect2,rect3;
int D3D = 0;
int Folder1=0;
int Folder2=0;
int Folder3=0;
int Folder4=0;
int Folder5=0;
int Folder6=0;
int Folder7=0;
int Mpos=0;			  // current highlighted menuitem	
int Active=0;			  // number of menu items
int Mxofs =30;	  // Semakin Besar maka Akan Semakin ke kanan
int Mysize =15;  // heigh of a menuline
int ShowMenu = 1;
char Mtitle[81]= "";
int			Mvisible=1;
struct{
int  *var;
int  maxvalue;
int  typ;
char *txt;
char **opt;
}
#define 	MENUMAXITEMS	100
#define 	 MENUBASE		10
#define 	MENUFOLDER			1
#define 	ANJING			1
#define 	MENUTEXT		2
#define 	MENUITEM		3
#define 	MENUWEWITEM		10
#define 	MENUMAXINDEX	100
//-------------------------------------------------------------------//
//#define     MCOLOR_TITLE	D3DCOLOR_ARGB(255, 255, 255, 000)//Yellow
//#define     MCOLOR_CURRENT	D3DCOLOR_ARGB(255, 125, 000, 255)//Purple/Ungu
//#define     MCOLOR_FOLDER	D3DCOLOR_ARGB(255, 238, 201, 0)
//#define     MCOLOR_TEXT		D3DCOLOR_ARGB(255, 000, 255, 000)//Green
//#define     MCOLOR_INACTIVE	D3DCOLOR_ARGB(255, 255, 255, 255)//White
//#define     MCOLOR_ACTIVE	D3DCOLOR_ARGB(255, 245, 000, 000)//RED*/

#define MCOLOR_CURRENT	0xffff0000//#define MCOLOR_CURRENT	D3DCOLOR_ARGB(255, 255, 125, 000)
#define MCOLOR_TEXT		0xffe0e0e0//#define MCOLOR_TEXT		D3DCOLOR_ARGB(255, 255, 255, 255) //D3DCOLOR_ARGB(255, 255, 255, 255)
#define MCOLOR_ACTIVE	D3DCOLOR_ARGB(255, 000, 255, 000)
#define MENUCOLOR_TITLE D3DCOLOR_ARGB(255, 000, 255, 000)//#define MENUCOLOR_TITLE	D3DCOLOR_ARGB(255, 255, 000, 000)
#define MCOLOR_FOLDER	D3DCOLOR_ARGB(255, 255, 255, 000)
#define MCOLOR_INACTIVE	D3DCOLOR_ARGB(255, 0, 180, 255)//	0xffa0a0a0//#define MCOLOR_INACTIVE	D3DCOLOR_ARGB( 250, 25, 220, 251) //D3DCOLOR_ARGB(255, 255, 255, 000) //D3DCOLOR_ARGB(255, 255,	255, 255)


#define 	MENUMAXITEMS	100
//------------------------------------------------------------------//*/
D3MENU[MENUMAXINDEX];
void DrawAddItem(char *txt, char **opt, int *var, int maxvalue, int typ){
  D3MENU[Active].typ=typ;
  D3MENU[Active].txt=txt;
  D3MENU[Active].opt=opt;
  D3MENU[Active].var=var;
  D3MENU[Active].maxvalue=maxvalue;
  Active++;
}

	 RECT rect;
	 RECT rect2;
	 RECT rect3;
struct {
  int  typ;		  // type of menuline, folder, item
  char *txt;	  // text to show
  char **opt;	  // array of options
  int  *var;	  // variable containing current status
  int  maxvalue;  // maximumvalue,  normally 1  gives  0=off  1=on
} MENU[MENUMAXITEMS];

void DrawAddText(char *txt, char *opt){
  D3MENU[Active].typ=MENUTEXT;
  D3MENU[Active].txt=txt;
  D3MENU[Active].opt=(char **)opt;
  D3MENU[Active].var=0;
  D3MENU[Active].maxvalue=0;
  Active++;
}
void MenuAddItem(char *txt, char **opt, int *var, int maxvalue, int typ)
{
  MENU[Mmax].typ=typ;
  MENU[Mmax].txt=txt;
  MENU[Mmax].opt=opt;
  MENU[Mmax].var=var;
  MENU[Mmax].maxvalue=maxvalue;
  Mmax++;
}
void todossss(char *txt, char *opt)
{
	MENU[Mmax].typ=MENUTEXT;
	MENU[Mmax].txt=txt;
	MENU[Mmax].opt=(char **)opt;
	MENU[Mmax].var=0;
	MENU[Mmax].maxvalue=0;
	Mmax++;
}


void DrawMenuShow(int x, int y,	ID3DXFont *pFont)
{

  int i, val;
  DWORD color;
    SetRect( &rect, x+Mxofs/2, y, x+Mxofs /2 , y );
  if (!Mvisible) return;

  if (Mtitle[0]) {

	  pFont->DrawText(NULL,Mtitle,-1,&rect,DT_NOCLIP | DT_TOP, MENUCOLOR_TITLE);

	  y+=Mysize;
  }

  for (i=0; i<Mmax; i++) {
	   val=(MENU[i].var)?(*MENU[i].var):0;
	   // determine color
       if (i==Mpos)
		   color=GREEN;
       else if (MENU[i].typ==MENUFOLDER)
           color=MCOLOR_FOLDER;
	   else if (MENU[i].typ==ANJING)
           color=MCOLOR_INACTIVE;
       else if (MENU[i].typ==MENUTEXT)
           color=MCOLOR_TEXT;
       else
		   color=(val)?RED:WHITE;
     SetRect( &rect3, x, y, x , y );
     SetRect( &rect2, x+Mxofs, y, x+Mxofs , y );
	   pFont->DrawText(NULL,MENU[i].txt,-1,&rect3, DT_NOCLIP | DT_RIGHT,color);
       if (MENU[i].opt) {
		   if (MENU[i].typ==MENUTEXT)
		   	   pFont->DrawText(NULL,(char *)MENU[i].opt,-1,&rect2, DT_NOCLIP | DT_LEFT, color);
		   else
			   pFont->DrawText(NULL,(char *)MENU[i].opt[val],-1,&rect2, DT_NOCLIP | DT_LEFT, color);
	   }
       y+=Mysize;
  }
}

//void MenuNav(void)
//{
//   if(IsKeyPressed(VK_INSERT,0)) Mvisible=(!Mvisible);
////	if (nongol) Mvisible=(!Mvisible);
//  if (!Mvisible) return;
//
//  if(IsKeyPressed(VK_UP,0)) {
//		do {
//			Mpos--;
//			if (Mpos<0)  Mpos=Mmax-1;
//		} while (MENU[Mpos].typ==MENUTEXT);		// skip textitems
//  } else if(IsKeyPressed(VK_DOWN,0)) {
//		do {
//			Mpos++;
//		    if (Mpos==Mmax) Mpos=0;
//		} while (MENU[Mpos].typ==MENUTEXT);		// skip textitems
//  } else if (MENU[Mpos].var) {
//		int dir=0;
//		// bugfix: thx to Dxt-Wieter20
//		if(IsKeyPressed(VK_LEFT,0) && *MENU[Mpos].var > 0 ) dir=-1;
//		if(IsKeyPressed(VK_RIGHT,0) && *MENU[Mpos].var < (MENU[Mpos].maxvalue-1)) dir=1;
//		if (dir) {
//			*MENU[Mpos].var += dir;
//			if (MENU[Mpos].typ==MENUFOLDER) Mmax=0;  // change on menufolder, force a rebuild
//		}
//  }
//}
void MenuNav(void)
{
	VIRTUALIZER_START VIRTUALIZER_MUTATE1_START	VIRTUALIZER_MUTATE2_START VIRTUALIZER_MUTATE3_START
   if (GetAsyncKeyState(VK_INSERT)&1) 
	   Mvisible=(!Mvisible);
//	if (nongol) Mvisible=(!Mvisible);
  if (!Mvisible) return;

  if (GetAsyncKeyState(VK_UP)&1) {
		do {
			Mpos--;
			if (Mpos<0)  Mpos=Mmax-1;
		} while (MENU[Mpos].typ==MENUTEXT);		// skip textitems
  } else if (GetAsyncKeyState(VK_DOWN)&1) {
		do {
			Mpos++;
		    if (Mpos==Mmax) Mpos=0;
		} while (MENU[Mpos].typ==MENUTEXT);		// skip textitems
  } else if (MENU[Mpos].var) {
		int dir=0;
		// bugfix: thx to Dxt-Wieter20
		if (GetAsyncKeyState(VK_LEFT )&1 && *MENU[Mpos].var > 0                      ) dir=-1;
		if (GetAsyncKeyState(VK_RIGHT)&1 && *MENU[Mpos].var < (MENU[Mpos].maxvalue-1)) dir=1;
		if (dir) {
			*MENU[Mpos].var += dir;
			if (MENU[Mpos].typ==MENUFOLDER) Mmax=0;  // change on menufolder, force a rebuild
		}
  }
    VIRTUALIZER_END
}