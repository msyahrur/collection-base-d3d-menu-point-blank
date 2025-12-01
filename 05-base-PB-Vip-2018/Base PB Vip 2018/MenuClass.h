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
#define WIN32_LEAN_AND_MEAN
#pragma warning (disable: 4244 4996 4800)
#include <windows.h>
#include <d3dx9.h>
#include <stdio.h>

#ifndef D3DFONT_RIGHT
#define D3DFONT_RIGHT		0x0008
#endif

struct sPlayer
{
	int HookMoveSpeed;
	int MoveSpeed;
	int HookJumpSet;
	int JumpSet;
};

struct sWeapon
{
	int SetBrust;
};

struct sGameHack
{
	sPlayer Player;
	sWeapon Weapon;
}; sGameHack GameHack = {0};

/*-------------------------------------------------------------------------------------------------------------------*/
int MenuFolder[100];
int MenuX_Maling	= 0;
int Drawing			= 0;
int Mpos			= 0;	
int Mmax			= 0;
int DrawFont		= 1;
int Mvisible		= 1;
int my=33;
int mx=33;
int Mysize = 20;
int Mxofs = 140;

int Mysize2		= 15; // Text Dist Up Down
int Mxofs2		= 150;// Text Dist Right Left
int my2			= 20; // Menu Dist Up Down
int	mx2			= 20; // Menu Dist Right Left

char Mtitle[81]		= " Nama Cheat Terserah ";


char output[16];
char output2[1226];
char output3[1111];
char Sempakx[1233];

RECT rect,rect2,rect3;

int				RainbowR		= 100;
int				RainbowG		= 100;
int				RainbowB		= 100;
float			RainbowTexts	= 100;
#define			RainbowTextTest D3DCOLOR_ARGB(255, RainbowR, RainbowG, RainbowB)

ID3DXFont	*pFont1;
BOOL Font()
{
	if(pFont1)
		return FALSE;
	else return TRUE;
}

void FontCreate(LPDIRECT3DDEVICE9 pDevice)
{
		D3DXCreateFontA(pDevice, 15, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, /*"Courier"*/"Arial"/*"Franklin Gothic"*/, &pFont1);
}

void FontReset()
{
	pFont1->OnLostDevice();
	pFont1->OnResetDevice();
	pFont1->Release();
	pFont1 = NULL;
}

void OnLostDevice()
{
	pFont1->OnLostDevice();	
}

void FontRelease()
{
	pFont1->Release();
	pFont1 = NULL;
}

#define 		MENUMAXINDEX	100
#define 		MENUFOLDER		1
#define 		MENUTEXT		2
#define 		MENUITEM		3
#define			MENUCAT			4

struct{
int  *var;
int  maxvalue;
int  typ;
char *txt;
char **opt;
}


#define CDllExport extern "C" __declspec( dllexport )
#define DllExport __declspec( dllexport )
D3MENU[MENUMAXINDEX];
LPD3DXFONT pFont;
void AddItem(char *txt, char **opt, int *var, int maxvalue, int typ)
{
	D3MENU[Mmax].typ=typ;
	D3MENU[Mmax].txt=txt;
	D3MENU[Mmax].opt=opt;
	D3MENU[Mmax].var=var;
	D3MENU[Mmax].maxvalue=maxvalue;
	Mmax++;
}

void AddText(char *txt, char *opt)
{
	D3MENU[Mmax].typ=MENUTEXT;
	D3MENU[Mmax].txt=txt;
	D3MENU[Mmax].opt=(char **)opt;
	D3MENU[Mmax].var=0;
	D3MENU[Mmax].maxvalue=0;
	Mmax++;
}

void FillRGB( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice )
{
	if( w < 0 )w = 1;
	if( h < 0 )h = 1;
	if( x < 0 )x = 1;
	if( y < 0 )y = 1;
 
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}

void DrawBorder( int x, int y, int w, int h, int px, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice )
{
	FillRGB( x, (y + h - px), w, px, BorderColor, pDevice );
	FillRGB( x, y, px, h, BorderColor, pDevice );
	FillRGB( x, y, w, px, BorderColor, pDevice );
	FillRGB( (x + w - px), y, px, h, BorderColor, pDevice );
}

void AddTextL(char* text, int x, int y, bool Border, D3DCOLOR color) 
{
	RECT FontRect = { x, y, x, y };

	if(Border){
		SetRect(&FontRect, x - 1, y , x - 1, y);
		pFont->DrawTextA(NULL,text,-1,&FontRect, DT_LEFT|DT_NOCLIP, BLACK);
		SetRect(&FontRect, x + 1, y , x + 1, y);
		pFont->DrawTextA(NULL,text,-1,&FontRect, DT_LEFT|DT_NOCLIP, BLACK);
		SetRect(&FontRect, x , y - 1, x, y - 1);
		pFont->DrawTextA(NULL,text,-1,&FontRect, DT_LEFT|DT_NOCLIP, BLACK);
		SetRect(&FontRect, x , y + 1, x, y + 1);
		pFont->DrawTextA(NULL,text,-1,&FontRect, DT_LEFT|DT_NOCLIP, BLACK);
	}

	SetRect(&FontRect, x, y , x, y);
	pFont->DrawTextA(NULL, text, -1, &FontRect, DT_LEFT|DT_NOCLIP, color);
}

void DrawTextR(int x,int y,DWORD color,char *text)
{
    RECT rect, rect1, rect2, rect3, rect4, rect5;
    SetRect( &rect, x, y, x, y );
	SetRect( &rect1, x-1, y, x-1, y );
    SetRect( &rect2, x, y, x, y );
	SetRect( &rect3, x, y+1, x, y+1 );
    SetRect( &rect4, x, y, x, y );
	SetRect( &rect5, x - 0.1, y + 0.2, x - 0.1, y + 0. );
	pFont->DrawTextA(NULL,text,-1,&rect5, DT_LEFT|DT_NOCLIP, color );
    pFont->DrawTextA(NULL,text,-1,&rect,  DT_LEFT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect1, DT_LEFT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect2, DT_LEFT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect3, DT_LEFT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect4, DT_LEFT|DT_WORDBREAK, BLACK );
}

void DrawTextL(int x,int y,DWORD color,char *text)
{
	RECT rect, rect1, rect2, rect3, rect4, rect5;
    SetRect( &rect, x, y, x, y );
	SetRect( &rect1, x-1, y, x-1, y );
    SetRect( &rect2, x, y, x, y );
	SetRect( &rect3, x, y+1, x, y+1 );
    SetRect( &rect4, x, y, x, y );
	SetRect( &rect5, x - 0.1, y + 0.2, x - 0.1, y + 0. );
	pFont->DrawTextA(NULL,text,-1,&rect5, DT_RIGHT|DT_NOCLIP, color );
    pFont->DrawTextA(NULL,text,-1,&rect,  DT_RIGHT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect1, DT_RIGHT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect2, DT_RIGHT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect3, DT_RIGHT|DT_WORDBREAK, BLACK );
	pFont->DrawTextA(NULL,text,-1,&rect4, DT_RIGHT|DT_WORDBREAK, BLACK );
}

void DrawTextC(int x,int y,DWORD color,char *text )
{
    RECT rect, rect2;
    SetRect( &rect, x, y, x, y );
	SetRect( &rect2, x - 0.1, y + 0.2, x - 0.1, y + 0. );
	pFont->DrawTextA(NULL,text,-1,&rect2, DT_CENTER|DT_NOCLIP, 0x00000000 );
    pFont->DrawTextA(NULL,text,-1,&rect, DT_CENTER|DT_NOCLIP, color );
}

void DrawBox12(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
} 

void DrawBorder12(int x, int y, int w, int h, int px,D3DCOLOR col ,LPDIRECT3DDEVICE9 pDevice)
{
	DrawBox12(pDevice,x+px,y+h-px,w-px-px,px,col);
	DrawBox12(pDevice,x,y,px,h,col);
	DrawBox12(pDevice,x+px,y,w-px-px,px,col);
	DrawBox12(pDevice,x+w-px,y,px,h,col);
}

void DrawMenu12(int x, int y, int w, int h, int px,D3DCOLOR col1,D3DCOLOR col2, LPDIRECT3DDEVICE9 pDevice)
{
	DrawBox12(pDevice,x,y,w,h,col1);
	DrawBorder12 ( x,y,w,h,px,col2,pDevice);
}

void DrawTransparentBox(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	}
	V[4] = { { x, y + h, 0.0f, 0.0f, Color }, { x, y, 0.0f, 0.0f, Color }, { x + w, y + h, 0.0f, 0.0f, Color }, { x + w, y, 0.0f, 0.0f, Color } };
	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(0);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
	return;
}


void MenuBox(float x, float y, LPDIRECT3DDEVICE9 pDevice)
{
	DrawTransparentBox	(x-2, y+20, 205	,(Mmax*15)+9,BLACK, pDevice);
	DrawBorder			(x-4, y+20, 205	,(Mmax*15)+9,	1,BLACK, pDevice);
}
void DrawBoxX( int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 0, 0);
}
void  DrawBorderX(int x, int y, int w, int h, D3DCOLOR Color,IDirect3DDevice9* pDevice)
{
	DrawBoxX(x,  y, 1,  h,Color,pDevice);
	DrawBoxX(x,y+h, w,  1,Color,pDevice);
	DrawBoxX(x,  y, w,  1,Color,pDevice);
	DrawBoxX(x+w,y, 1,h+1,Color,pDevice);
}

/*------------------------------------------- Declaration MenuShow ------------------------------------------------------*/
void MenuShow(float x, float y, LPDIRECT3DDEVICE9 pDevice)
{
		int i, val;
	DWORD color;
	DWORD texty;
	SetRect( &rect, x+Mxofs/2, y, x+Mxofs /2 , y );
	char text[100];
	if (!Mvisible) return;

	DrawBoxX	(x+0, y+21, 220	,(Mmax*20)+8,	BLACK, pDevice);
	DrawBorderX(x+0, y+21, 220	,(Mmax*20)+8,	D3DCOLOR_ARGB(255, 000, 000, 125), pDevice);
	if (Mtitle[0]) 
	{
		DrawBoxX	(x+0, y-2, 220	,21,	BLACK, pDevice);
		DrawBorderX			(x+0, y-2, 220	,21, 	D3DCOLOR_ARGB(255, 000, 000, 125)				, pDevice);
		pFont->DrawText(NULL,Mtitle,-1,&rect,DT_NOCLIP | DT_NOCLIP, YELLOW);
		y+=Mysize+10;
	}
	for (i=0; i<Mmax; i++) 
	{
		val=(D3MENU[i].var)?(*D3MENU[i].var):0;
		sprintf(text, "%s", D3MENU[i].txt);
		if (i==Mpos){
			color=RED;
			texty=RED;
			sprintf(text, "%s", D3MENU[i].txt);
		}
		else if (D3MENU[i].typ==MENUFOLDER){
			
			color=SKYBLUE;
			texty=SKYBLUE;
		}
		else if (D3MENU[i].typ==MENUTEXT){
			color=WHITE;
			texty=WHITE;
		}
		else{
			color=(val)?GREEN:WHITE;
			texty=(val)?WHITE:WHITE;
		}
		if (D3MENU[i].opt)
		{
			if (D3MENU[i].typ==MENUITEM){
				DrawTextR(x+10, y-5, texty,text);
				y = y + 1;
			}else{
				DrawTextR(x+10, y-5, texty,text);
			}
		}
		if (D3MENU[i].opt) {
			if (D3MENU[i].typ==MENUTEXT)
				DrawTextL((x+215), y-5, color,(char *)D3MENU[i].opt);
			else
				DrawTextL((x+215), y-5, color,(char *)D3MENU[i].opt[val]);
		}
		y+=Mysize;
	}
	
}
void MenuNav(void)
{
	if (IsKeyboardKeyDownOnce(DIK_INSERT)&1)
	{
		Mvisible=(!Mvisible);
	}
	if (!Mvisible) return;
	if (IsKeyboardKeyDownOnce(DIK_UP)&1) {
		do {
			Mpos--;
			if (Mpos<0)  Mpos=Mmax-1;
		} 
		while (D3MENU[Mpos].typ==MENUTEXT);	
	}else if (IsKeyboardKeyDownOnce(DIK_DOWN)&1) {
		do {
			Mpos++;
			if (Mpos==Mmax) Mpos=0;
		} while (D3MENU[Mpos].typ==MENUTEXT);		
	} else if (D3MENU[Mpos].var) {
		int dir=0;
		if ( ( IsKeyboardKeyDownOnce(DIK_LEFT)&1 ) && *D3MENU[Mpos].var > 0 ) dir=-1;
		if ( ( IsKeyboardKeyDownOnce(DIK_RIGHT)&1 ) && *D3MENU[Mpos].var < (D3MENU[Mpos].maxvalue-1)) dir=1;
		if (dir) {
			*D3MENU[Mpos].var += dir;
			if (D3MENU[Mpos].typ==MENUFOLDER) Mmax=0;
			if (D3MENU[Mpos].typ==MENUCAT) Mmax=0;  
		}
	}
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

