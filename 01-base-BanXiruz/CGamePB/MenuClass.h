//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
int Drawing = 0;
int Mpos = 0;	
int Mmax = 0;
int DrawFont = 1;
int Mvisible = 1;
int Mysize = 17; 
int Mxofs = 145;
int my = 20;
int	mx = 25;
char Header [88] = "        VIP-Laverzoka";

struct{
	int  *var;
	int  maxvalue;
	int  typ;
	char *txt;
	char **opt;
}

#define MENUMAXINDEX	100
#define MENUFOLDER		1
#define MENUTEXT		2
#define MENUITEM		3
#define	MENUCAT			4

D3MENU[MENUMAXINDEX];

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

void MenuBox(float x, float y, LPDIRECT3DDEVICE9 pDevice)
{
	DrawTransparentBox(mx-10, my-4, Mxofs+52, 20, D3DCOLOR_ARGB(200, 72, 72, 72), pDevice);
	DrawBorder(mx-10, my-4, Mxofs+52, 20, 1, D3DCOLOR_ARGB(255,   0, 180, 255), pDevice);
	DrawTransparentBox(mx-10, my+20, Mxofs+52,(Mmax*17)+1, D3DCOLOR_ARGB(200, 72, 72, 72), pDevice);
	DrawBorder(mx-10, my+20, Mxofs+52, (Mmax*17)+1, 1, D3DCOLOR_ARGB(255,   0, 180, 255), pDevice);
}

void MenuShow(float x, float y, LPDIRECT3DDEVICE9 pDevice)
{
	int i, val;
	DWORD color;
	SetRect( &rect, x+Mxofs/2, y, x+Mxofs /2 , y );
	if(!Mvisible) return;
	if (Header[0]) 
	{	
		pFont->DrawText(NULL,Header,-1,&rect,DT_NOCLIP | DT_CENTER, D3DCOLOR_ARGB(255, 0, 180, 255));
		y+=Mysize+5;
	}
	for (i=0; i<Mmax; i++) 
	{
		val=(D3MENU[i].var)?(*D3MENU[i].var):0;
		if (i==Mpos){
			color=D3DCOLOR_ARGB(255, RainbowR, RainbowG, RainbowB);
		}
		else if (D3MENU[i].typ==MENUFOLDER){
			color=D3DCOLOR_ARGB(255, 0, 180, 255);
		}
		else if (D3MENU[i].typ==MENUTEXT){
			color=D3DCOLOR_ARGB(255, 255, 255, 000);
		}
		else
		color=(val)?D3DCOLOR_ARGB(255, 0, 255, 0):D3DCOLOR_ARGB(255, 255, 255, 255);
		SetRect( &rect3, x, y, x , y );
		SetRect( &rect2, x+Mxofs, y, x+Mxofs , y );
		pFont->DrawText(NULL,D3MENU[i].txt,-1,&rect3, DT_NOCLIP,color);
		if (D3MENU[i].opt) {
			if (D3MENU[i].typ==MENUTEXT)
				pFont->DrawText(NULL,(char *)D3MENU[i].opt,-1,&rect2, DT_NOCLIP, color);
			else
				pFont->DrawText(NULL,(char *)D3MENU[i].opt[val],-1,&rect2, DT_NOCLIP, color);
		}
		y+=Mysize;
	}
	//MenuBox(mx,my,pDevice);
}

void MenuNav(void)
{
	if (IsKeyPressed(VK_INSERT, 0)&1)
	{
		Mvisible=(!Mvisible);
	}
	if(Feature.Direct3D.MoveD3D9 && GetAsyncKeyState(VK_LCONTROL))
		{
		POINT Mpos;
		GetCursorPos(&Mpos);
		ScreenToClient(GetForegroundWindow(), &Mpos);
		mx = Mpos.x;
		my = Mpos.y+2;
	}
	if (!Mvisible) return;
	if (IsKeyPressed(VK_UP, 0)&1)
	{
		do{
			Mpos--;
			if (Mpos<0)  Mpos=Mmax-1;
			playsoundmem((LPCSTR)MOVE);
		}
		while (D3MENU[Mpos].typ==MENUTEXT);	
	}
	else if (IsKeyPressed(VK_DOWN, 0)&1)
	{
		do{
			Mpos++;
			if (Mpos==Mmax) Mpos=0;
			playsoundmem((LPCSTR)MOVE);
		}
		while (D3MENU[Mpos].typ==MENUTEXT);		
	}
	else if (D3MENU[Mpos].var)
	{
		int dir=0;
		if ( ( IsKeyPressed(VK_LEFT, 0)&1 ) && *D3MENU[Mpos].var > 0 ) dir=-1, playsoundmem((LPCSTR)SWITCH);
		if ( ( IsKeyPressed(VK_RIGHT, 0)&1 ) && *D3MENU[Mpos].var < (D3MENU[Mpos].maxvalue-1)) dir=1, playsoundmem((LPCSTR)SWITCH);
		if (dir) {
			*D3MENU[Mpos].var += dir;
			if (D3MENU[Mpos].typ==MENUFOLDER) Mmax=0;
			if (D3MENU[Mpos].typ==MENUCAT) Mmax=0;  
		}
	}
}

char* GetDate(void)
{
	struct tm * current_tm;
	time_t current_time;time (&current_time);
	current_tm = localtime (&current_time);
	char *month	[]={"Jan.","Feb.","Mar.","Apr.","May","June","July","Aug.","Sept.","Oct.","Nov.","Dec."};
	char *logbuf = new char[ 256 ];

	sprintf( logbuf, ": %s %02d, 20%d",month[current_tm->tm_mon],current_tm->tm_mday,current_tm->tm_year-100);
	return logbuf;
}

char* GetTime(void)
{
	static char ctime[20] = "" ;
	struct tm * current_tm;
	time_t current_time;
	time (&current_time);
	current_tm = localtime (&current_time);
	if(current_tm->tm_hour>12)
		sprintf( ctime, ": %d:%02d:%02d PM", current_tm->tm_hour - 12, current_tm->tm_min, current_tm->tm_sec );
	else
		sprintf( ctime, ": %d:%02d:%02d AM", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec );
	return ctime;
}