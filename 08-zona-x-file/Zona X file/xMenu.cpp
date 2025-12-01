//====================================================================================================//
#include <stdio.h>
#include "xMenu.h"
#include "xSound.h"
#include "Sound.h"
//cSound Sound;
#pragma warning(disable:4244)
#pragma warning(disable:4996)
#pragma warning(disable:4800)
///////////////////////////////////////////////////////
#define MCOLOR_CURRENT	D3DCOLOR_ARGB(255, 255, 255, 255)//White
#define MCOLOR_TEXT		D3DCOLOR_ARGB(255, 000, 255, 000)//Green
#define MCOLOR_ACTIVE	D3DCOLOR_ARGB(255, 245, 000, 000)//Yellow
#define MENUCOLOR_TITLE	D3DCOLOR_ARGB(255, 000, 255, 000) //Green
#define MCOLOR_FOLDER	D3DCOLOR_ARGB(255, 255, 125, 000) //Orange
#define MCOLOR_INACTIVE	D3DCOLOR_ARGB(255, 19, 84, 199)//Blue
////////////////////////////////////////////////////////
#define RED				D3DCOLOR_ARGB(255, 245, 000, 000)
#define WHITE			D3DCOLOR_ARGB(255, 255, 255, 255)
#define YELLOW			D3DCOLOR_ARGB(255, 255, 255, 000) 
#define GREEN			D3DCOLOR_ARGB(255, 000, 255, 000)
#define ORANGE			D3DCOLOR_ARGB(255, 255, 125, 000)
#define BLACK			D3DCOLOR_ARGB(150, 000, 000, 000)
#define BLUE			D3DCOLOR_ARGB(255, 19, 84, 199) 
#define DEEPSKYBLUE     D3DCOLOR_ARGB(255, 30, 144, 255) //
#define CHOCOLATE2      D3DCOLOR_ARGB(255, 238, 118, 33) //
#define GOLD2			D3DCOLOR_ARGB(255, 238, 201, 0)  //
#define SQUA			D3DCOLOR_ARGB(255, 0, 255, 255)  //
#define DARKGREY        D3DCOLOR_ARGB(255,62,62,62)      //
#define Functions       D3DCOLOR_ARGB(255,26,115,145)//
#define MenuGreen       D3DCOLOR_ARGB(255,43,119,64) //
#define MenuGREY        D3DCOLOR_ARGB(255,30,30,30)  //
#define FUCK_ON			D3DCOLOR_ARGB(255,14,159,47) //
#define FUCK_OFF		D3DCOLOR_ARGB(255,62,120,167)//
#define BLACK			D3DCOLOR_ARGB(150, 000, 000, 000)
#define WHITE			D3DCOLOR_ARGB(255, 255, 255, 255)
#define GREEN			D3DCOLOR_ARGB(255, 000, 255, 000)
#define D3DFONT_BOLD 0x0000
ID3DXFont	*pFont1;
LPDIRECT3DDEVICE9 g_pDevice;






void D3D9Menu::AddItem(char *txt, char **opt, int *var, int maxvalue)
{
  MENU[Mmax]->typ=MENUITEM;
  MENU[Mmax]->txt=txt;
  MENU[Mmax]->opt=opt;
  MENU[Mmax]->var=var;
  MENU[Mmax]->maxvalue=maxvalue;
  Mmax++;
}

void D3D9Menu::AddFolder(char *txt, char **opt, int *var, int maxvalue)
{
  MENU[Mmax]->typ=MENUFOLDER;
  MENU[Mmax]->txt=txt;
  MENU[Mmax]->opt=opt;
  MENU[Mmax]->var=var;
  MENU[Mmax]->maxvalue=maxvalue;
  Mmax++;
}

void D3D9Menu::AddCategory(char *txt, char **opt, int *var, int maxvalue)
{
  MENU[Mmax]->typ=MENUCAT;
  MENU[Mmax]->txt=txt;
  MENU[Mmax]->opt=opt;
  MENU[Mmax]->var=var;
  MENU[Mmax]->maxvalue=maxvalue;
  Mmax++;
}

void D3D9Menu::DrawTextR(int x,int y,DWORD color,char *text)
{
    RECT rect;
    SetRect( &rect, x, y, x, y );
	pFont1->DrawTextA(NULL,text,-1,&rect, DT_LEFT|DT_NOCLIP, color );////////////// ON OFF MENGARAH KE KIRI
	pFont1->DrawTextA(NULL,text,-1,&rect, DT_LEFT|DT_NOCLIP, BLACK );
}

void D3D9Menu::FontCreate(LPDIRECT3DDEVICE9 pDevice)
{
if (g_pDevice != pDevice)
{
g_pDevice = pDevice;
try
{
if (pFont1 != 0)
pFont1->Release();
} catch (...) {}
pFont1 = 0;
D3DXCreateFontA(pDevice, 18, 0, FW_NORMAL, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &pFont1 );
}
}

void D3D9Menu::DrawTextL(int x,int y,DWORD color,char *text)
{
    RECT rect2;
	SetRect( &rect2, x+1, y, x+1, y );
	pFont1->DrawTextA(NULL,text,-1,&rect2, DT_LEFT|DT_NOCLIP, color );// menunya arah ke tengah
	pFont1->DrawTextA(NULL,text,-1,&rect2, DT_LEFT|DT_NOCLIP, BLACK );
}

void D3D9Menu::AddText(char *txt, char *opt)
{
	MENU[Mmax]->typ=MENUTEXT;
	MENU[Mmax]->txt=txt;
	MENU[Mmax]->opt=(char **)opt;
	MENU[Mmax]->var=0;
	MENU[Mmax]->maxvalue=0;
	Mmax++;
}

void D3D9Menu::MenuShow(float x, float y, LPDIRECT3DDEVICE9 pDevice)
{
  int i, val;
  unsigned long color;
  unsigned long texty;
  char text[200];
  if (!aktifmenu) return;
  for (i=0; i<Mmax; i++) {
	   val=(MENU[i]->var)?(*MENU[i]->var):0;
	   sprintf(text, "%s", MENU[i]->txt);
	   if (i==Mpos){
           color=MCOLOR_CURRENT;
		   texty=MCOLOR_CURRENT;
//		   CMenuItem_DrawCronersBox((INT)x - 0,(INT)y - 4,17,152, pDevice);
		   sprintf(text, "~>%s<~", MENU[i]->txt);
	   }
	   else if (MENU[i]->typ==MENUFOLDER){
           color=MCOLOR_FOLDER;
	       texty=MCOLOR_FOLDER;
	   }
	   else if (MENU[i]->typ==MENUTEXT){
           color=MCOLOR_TEXT;
	       texty=MCOLOR_TEXT;
	   }
	   else{
		   color=(val)?MCOLOR_ACTIVE:MCOLOR_INACTIVE;
	       texty=(val)?YELLOW:BLUE;
	   }

	   if (MENU[i]->opt) 
	   {
		   if (MENU[i]->typ==MENUITEM){
				DrawTextL(x+3, y, texty,text);
				y = y + 2;
		   }else{
				DrawTextL(x+3, y, texty,text);
		   }
	   }

       if (MENU[i]->opt) {
		   if (MENU[i]->typ==MENUTEXT)
			   DrawTextR((x+Mxofs), y, color,(char *)MENU[i]->opt);
		   else
			   DrawTextR((x+Mxofs), y, color,(char *)MENU[i]->opt[val]);
	   }

       y+=Mysize;
  }
}

void D3D9Menu::MenuNav(void)
{
	//bool bBothPressed = GetAsyncKeyState(VK_CONTROL) & GetAsyncKeyState(VK_NUMPAD0)&0x8000;

	if (GetAsyncKeyState(VK_INSERT)&1)aktifmenu=(!aktifmenu);
  if (!aktifmenu) return;

  if (GetAsyncKeyState(VK_UP)&1) {
		do {
			//Sound.wav.playsoundmem((LPCSTR)MOVE);
			Mpos--;
			if (Mpos<0)  Mpos=Mmax-1;
		} while (MENU[Mpos]->typ==MENUTEXT);	
  } else if (GetAsyncKeyState(VK_DOWN)&1) {
		do {
			//Sound.wav.playsoundmem((LPCSTR)MOVE);
			Mpos++;
		    if (Mpos==Mmax) Mpos=0;
		} while (MENU[Mpos]->typ==MENUTEXT);		
  } else if (MENU[Mpos]->var) {
		int dir=0;

		if ( ( GetAsyncKeyState(VK_LEFT )&1 ) && *MENU[Mpos]->var > 0 ) dir=-1;//, Sound.wav.playsoundmem((LPCSTR)SWITCH);
		if ( ( GetAsyncKeyState(VK_RIGHT)&1 ) && *MENU[Mpos]->var < (MENU[Mpos]->maxvalue-1)) dir=1;//, Sound.wav.playsoundmem((LPCSTR)SWITCH);
		if (dir) {
			*MENU[Mpos]->var += dir;
			if (MENU[Mpos]->typ==MENUFOLDER) Mmax=0;
			if (MENU[Mpos]->typ==MENUCAT) Mmax=0;  
		}
  }
}





