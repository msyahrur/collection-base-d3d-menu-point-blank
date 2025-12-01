//----------------------------------------------------------------------------------------
//---------------------------------------------------------// [MRC]
//----------------------------------------------------------------------------------------
#include <windows.h>
#include "[MRC]CHackEngine.h"
//----------------------------------------------------------------------------------------
int AddFolder[10];
int Drawing		= 0;
int Mpos		= 0;	
int Mmax		= 0;
int DrawFont	= 1;
int Mvisible	= 1;
int Mysize		= 17; // Text Dist Up Down
int Mxofs		= 165;// Text Dist Right Left
int my			= 350; // Menu Dist Up Down
int	mx			= 20; // Menu Dist Right Left
char Mtitle[88]	= "";

LPDIRECT3DVERTEXBUFFER9 Stream_Data;
UINT Offset = 0;
UINT Stride = 0;
LPDIRECT3DDEVICE9 npDevice, pGDevice; 
RECT rect,rect2,rect3;
//----------------------------------------------------------------------------------------
#define 		MENUMAXINDEX	100
#define 		MENUFOLDER		1
#define 		MENUTEXT		2
#define 		MENUITEM		3
#define			MENUCAT			4
#define			MCOLOR_TITLE	(AQUA)
#define			MCOLOR_CURRENT	(ORANGE)
#define			MCOLOR_FOLDER	(AQUA)
#define			MCOLOR_TEXT		(WHITE)
#define			MCOLOR_INACTIVE	(RED)
#define			MCOLOR_ACTIVE	(LIME)
//----------------------------------------------------------------------------------------
struct{
int  *var;
int  maxvalue;
int  typ;
char *txt;
char **opt;
}
//----------------------------------------------------------------------------------------
D3MENU[MENUMAXINDEX];
//----------------------------------------------------------------------------------------
void DrawAddItem(char *txt, char **opt, int *var, int maxvalue, int typ)
{
	D3MENU[Mmax].typ=typ;
	D3MENU[Mmax].txt=txt;
	D3MENU[Mmax].opt=opt;
	D3MENU[Mmax].var=var;
	D3MENU[Mmax].maxvalue=maxvalue;
	Mmax++;
}
//----------------------------------------------------------------------------------------
void DrawAddText(char *txt, char *opt)
{
	D3MENU[Mmax].typ=MENUTEXT;
	D3MENU[Mmax].txt=txt;
	D3MENU[Mmax].opt=(char **)opt;
	D3MENU[Mmax].var=0;
	D3MENU[Mmax].maxvalue=0;
	Mmax++;
}
//----------------------------------------------------------------------------------------
void DrawBox12(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
} 
//----------------------------------------------------------------------------------------
void DrawBorder12(int x, int y, int w, int h, int px,D3DCOLOR col ,LPDIRECT3DDEVICE9 pDevice)
{
	DrawBox12(pDevice,x+px,y+h-px,w-px-px,px,col);
	DrawBox12(pDevice,x,y,px,h,col);
	DrawBox12(pDevice,x+px,y,w-px-px,px,col);
	DrawBox12(pDevice,x+w-px,y,px,h,col);
}
//----------------------------------------------------------------------------------------
void DrawMenu12(int x, int y, int w, int h, int px,D3DCOLOR col1,D3DCOLOR col2, LPDIRECT3DDEVICE9 pDevice)
{
	DrawBox12(pDevice,x,y,w,h,col1);
    DrawBorder12 ( x,y,w,h,px,col2,pDevice);
}
//----------------------------------------------------------------------------------------
void MenuShow(float x, float y, LPDIRECT3DDEVICE9 pDevice)
{
	int i, val;
	DWORD color;
	SetRect( &rect, x+Mxofs/2, y, x+Mxofs /2 , y );
	if (!Mvisible) return;
	if (Mtitle[0]) 
	{
		DrawMenu12(x-5, y-5, 185/*170*//*<width*/, 40/*<height*/, 1, dGrey/*WARNA GROUND ATAS/JUDUL*/, AQUA/*WARNA TEXT FOLDER*/, pDevice);// Warna dan lebar tinggi line
		pFont->DrawText(NULL,Mtitle,-1,&rect,DT_NOCLIP | DT_CENTER, MCOLOR_TITLE);
		y+=Mysize;
	}
	for (i=0; i<Mmax; i++) 
	{
		DrawMenu12(x-5, y-5, 185/*<width*/, 40/*<height*/, 1, dGrey/*WARNA BACKGROUND*/, AQUA/*LINE BORDER BACKGROUND*/, pDevice);// Warna dan tinggi line BEFORE (DARK AND DARK)
		val=(D3MENU[i].var)?(*D3MENU[i].var):0;// determine color
		if (i==Mpos){
			if(RainbowTexts!=100)
			{RainbowR-=2,RainbowG-=3,RainbowB-=3;}
			if(RainbowTexts!=255)
			{RainbowR+=2,RainbowG+=3,RainbowB+=4;}
			color=RainbowTextTest;// MCOLOR_CURRENT
		}
		else if (D3MENU[i].typ==MENUFOLDER){
			color=MCOLOR_FOLDER;
		}
		else if (D3MENU[i].typ==MENUTEXT){
			color=MCOLOR_TEXT;
		}
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
//----------------------------------------------------------------------------------------
void MenuNav(void)
{
	if (IsKeyPressed(VK_INSERT, 0)&1)
	{
		Mvisible=(!Mvisible);
	}
	if (!Mvisible) return;
	if (IsKeyPressed(VK_UP, 0)&1) {
		do {
			Mpos--;
			if (Mpos<0)  Mpos=Mmax-1;
		} 
		while (D3MENU[Mpos].typ==MENUTEXT);	
	}else if (IsKeyPressed(VK_DOWN, 0)&1) {
		do {
			Mpos++;
			if (Mpos==Mmax) Mpos=0;
		} while (D3MENU[Mpos].typ==MENUTEXT);		
	} else if (D3MENU[Mpos].var) {
		int dir=0;
		if ( ( IsKeyPressed(VK_LEFT, 0)&1 ) && *D3MENU[Mpos].var > 0 ) dir=-1;
		if ( ( IsKeyPressed(VK_RIGHT, 0)&1 ) && *D3MENU[Mpos].var < (D3MENU[Mpos].maxvalue-1)) dir=1;
		if (dir) {
			*D3MENU[Mpos].var += dir;
			if (D3MENU[Mpos].typ==MENUFOLDER) Mmax=0;
			if (D3MENU[Mpos].typ==MENUCAT) Mmax=0;  
		}
	}
}
//----------------------------------------------------------------------------------------
char* GetDate()
{
	struct tm * current_tm;
	time_t current_time;time (&current_time);
	current_tm = localtime (&current_time);
	char *month	[]={"Jan.","Feb.","Mar.","Apr.","May.","June.","July","Aug.","Sept.","Oct.","Nov.","Dec."};
	char *logbuf = new char[ 256 ];

	sprintf( logbuf, "%s %02d, 20%d",month[current_tm->tm_mon],current_tm->tm_mday,current_tm->tm_year-100);
	return logbuf;
}
//----------------------------------------------------------------------------------------
char *Moptfolder		  []   = {"[+]",       "[-]"};
char *Moptonoff           []   = {"[OFF]",     "[ON]"};
char *Moptonbdy           []   = {"[HEAD]",    "[BODY]"};
//----------------------------------------------------------------------------------------
void RebuildMenu(LPDIRECT3DDEVICE9 pDevice)
{
//----------------------------------------------------------------------------------------
	 strcpy(Mtitle,"[MRC] POINT BLANK");
		DrawAddText("Date :						 " , GetDate()); 
		DrawAddItem("[Direct Menu]				 " , Moptfolder , &AddFolder[1], 2,MENUFOLDER);
		if(AddFolder[1])
		{
		DrawAddItem("[Wallhack Clean]		     " , Moptonoff  , &WHClean	    , 2,MENUCAT);
		DrawAddItem("[Wallhack Glass]			 " , Moptonoff  , &WHGlass	    , 2,MENUCAT);
		DrawAddItem("[No Fog]					 " , Moptonoff  , &DontFog	    , 2,MENUCAT);
		DrawAddItem("[No Smoke]				     " , Moptonoff  , &DontSmoke	, 2,MENUCAT);
		DrawAddItem("[Crosshair]		   	     " , Moptonoff  , &Cross		, 2,MENUCAT);
		}
		DrawAddItem("[Aim Menu]					 " , Moptfolder	, &AddFolder[2], 2,MENUFOLDER);
		if(AddFolder[2])
		{
		DrawAddItem("Aim Lock					 " , Moptonoff  , &Accuracy		, 2,MENUCAT);
		DrawAddItem("Aim Target					 " , Moptonbdy  , &AimBody	    , 2,MENUCAT);
		}
		DrawAddItem("[Weapon Menu]				 " , Moptfolder , &AddFolder[3], 2,MENUFOLDER);
		if(AddFolder[3])
		{
		DrawAddItem("[Quick Change]				 " , Moptonoff	, &Quick		, 2,MENUCAT);
		DrawAddItem("[No Recoil]				 " , Moptonoff	, &AntiRecoil	, 2,MENUCAT);
		DrawAddItem("[Fast Reload]				 " , Moptonoff	, &FReload		, 2,MENUCAT);
		}
		DrawAddItem("[C4 Menu]					 " , Moptfolder	, &AddFolder[4], 2,MENUFOLDER);
		if(AddFolder[4])
		{
		DrawAddItem("[Plant C4]					 " , Moptonoff	, &Planted		, 2,MENUCAT);
		DrawAddText("[Jalan Pintas" ,	"NUMPAD1]");	
		DrawAddItem("[Defuse C4]				 " , Moptonoff	, &DefuseX		, 2,MENUCAT);
		DrawAddText("[Jalan Pintas" ,	"NUMPAD2]");
		}


}
//----------------------------------------------------------------------------------------
//---------------------------------------------------------// [MRC]
//----------------------------------------------------------------------------------------