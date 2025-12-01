//===============================================================//
// Source PointBlank Hacks By ZeRo-CyBeRz Hacks [www.zero-cyberz-server.com]
// D3D Menu By UC Forum [www.unknowncheats.me] || Last Edit By Y.L.A.S
//===============================================================//
#include "StandardIncludes.h"
#include "CMenu.h"
#include "CSound.h"
#include "Sounds.h"
#include "KeyPresent.h"
//-----------------------------------------------------------------------------
// Name: PostReset()
// Desc: Creates Fonts and other Resources for Menu
//-----------------------------------------------------------------------------

void cMenu::PostReset(LPDIRECT3DDEVICE9 pDevice)
{
	if(font == NULL)
	{
	font = new CD3DFont("Hud_Small_Font", 7, D3DFONT_BOLD);
	font->InitDeviceObjects(pDevice);
	font->RestoreDeviceObjects();
	this->FontCreated = true;
	}
}

//-----------------------------------------------------------------------------
// Name: PreReset()
// Desc: Releases Fonts / objects for menu
//-----------------------------------------------------------------------------

void cMenu::PreReset(void)
{
	font->InvalidateDeviceObjects();
	font->DeleteDeviceObjects();
	font = NULL;
	this->FontCreated = false;
}

//-----------------------------------------------------------------------------
// Name: Init()
// Desc: Load Menu Defaults / Prepare Menu For Usage
//-----------------------------------------------------------------------------

void cMenu::Init()
{
	if (opt.options.reset)INIT=false;
	if(!INIT){
		opt.options.move=0;		// BUG FIX FOR RESET DISABLE MOVE BEFORE SETTING COORDINATES
		X=25;
		Y=15;
		WIDTH=176;			    // MENU WIDTH
		I_OFS=4;			    // OFSET FOR ITEM
		S_OFS=WIDTH-4;			// OFSET FOR STATE
		T_SPC=16;				// Space from Title and Start of Items
		F_SPC=16;				// Footer Spacing Hook Menu
		I_SPC=15;				// Item Spacing
		I_CUR=0;				// Set current Item
		SHOW=true;				// false=hide  true=show
		INIT=true;				// STOP INITATION
	}
}

//-----------------------------------------------------------------------------
// Name: FPS()
// Desc: Keeps Track of Current Frames Persecond Make sure if its already called to specify a 1 as parameter
//-----------------------------------------------------------------------------

char* cMenu::FPS(int en)
{
	static int	 FPScounter = 0;
	static float FPSfLastTickCount = 0.0f;
	static float FPSfCurrentTickCount;
	static char  cfps[6] = "";

	if(!en)
	{
		FPSfCurrentTickCount = clock() * 0.001f;
		FPScounter++;

		if((FPSfCurrentTickCount - FPSfLastTickCount) > 1.0f)
		{
			FPSfLastTickCount = FPSfCurrentTickCount;
			sprintf(cfps,"%d FPS",FPScounter);
			FPScounter = 0;
		}
	}
	return cfps;
}

//-----------------------------------------------------------------------------
// Name: TIME()
// Desc: Outputs Current Time in USA Format
//-----------------------------------------------------------------------------

char* cMenu::TIME(void)
{
	static char ctime[20] = "" ;
	struct tm * current_tm;
	time_t current_time;
	time (&current_time);
	current_tm = localtime (&current_time);
	if(current_tm->tm_hour>12)
		sprintf( ctime, "%d:%02d:%02d PM", current_tm->tm_hour - 12, current_tm->tm_min, current_tm->tm_sec );
	else
		sprintf( ctime, "%d:%02d:%02d AM", current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec );
	return ctime;
}

//-----------------------------------------------------------------------------
// Name: DATE()
// Desc: Outputs Current Date in USA Format
//-----------------------------------------------------------------------------

char* cMenu::DATE(void)
{
	struct tm * current_tm;
	time_t current_time;time (&current_time);
	current_tm = localtime (&current_time);
	char *month	[]={"Jan.","Feb.","Mar.","Apr.","May","June","July","Aug.","Sept.","Oct.","Nov.","Dec."};
	char *logbuf = new char[ 256 ];

	sprintf( logbuf, "%s %02d, 20%d",month[current_tm->tm_mon],current_tm->tm_mday,current_tm->tm_year-100);
	return logbuf;
}

//-----------------------------------------------------------------------------
// Name: oprintf()
// Desc: equiv to sprintf but for output into of dest
//-----------------------------------------------------------------------------

char* cMenu::oprintf (const char *fmt, ...)
{
	static char buffer[225] = "";
	va_list va_alist;
	va_start (va_alist, fmt);
	_vsnprintf (buffer,sizeof(buffer), fmt, va_alist);
	va_end (va_alist);
	return buffer;
}
//-----------------------------------------------------------------------------
// Name: Save()
// Desc: Saves Menu Item states for later Restoration
//-----------------------------------------------------------------------------

void cMenu::Save(char* szSection, char* szKey, int iValue,LPCSTR file)
{
	char szValue[255];
	sprintf(szValue, "%d", iValue);
	WritePrivateProfileString(szSection,  szKey, szValue, file); 
}

//-----------------------------------------------------------------------------
// Name: Load()
// Desc: Loads Menu Item States From Previously Saved File
//-----------------------------------------------------------------------------

int cMenu::Load(char* szSection, char* szKey, int iDefaultValue,LPCSTR file)
{
	int iResult = GetPrivateProfileInt(szSection,  szKey, iDefaultValue, file); 
	return iResult;
}

//-----------------------------------------------------------------------------
// Name: additem()
// Desc: BaseFunction for aitem,acat,and atext
//-----------------------------------------------------------------------------

void cMenu::additem(char *title, char *states,int type, int *var, int show, int when)
{
	if(show==when)
	{
		strcpy(items[NO].title,title);
		getfield(states,items[NO].state,*var+1);
		items[NO].type=type;
		items[NO].max=nofields(states);
		items[NO].val=var;

		NO++;
	}
	if(type!=T_TEXT)
	{
		if (opt.options.load)
			*var = Load("Items", title, *var,Tools.GetDirectoryFile("settings.ini"));
		if (opt.options.save)
			Save("Items", title, *var,Tools.GetDirectoryFile("settings.ini"));
		if (opt.options.reset)
			*var=0;
	}
}

//-----------------------------------------------------------------------------
// Name: acat()
// Desc: Adds Folder/Category to Item index
//-----------------------------------------------------------------------------

void cMenu::acat(char *title, char *states,int *var)
{
	additem(title,states,T_CAT,var,0,0);
}

//-----------------------------------------------------------------------------
// Name: aitem()
// Desc: Adds regular item to Item index
//-----------------------------------------------------------------------------

void cMenu::aitem(char *title, char *states,int *var,int show,int when)
{
	additem(title,states,T_ITEM,var,show,when);
}

//-----------------------------------------------------------------------------
// Name: atext()
// Desc: Adds Text item to item index
//-----------------------------------------------------------------------------

void cMenu::atext(char *title, char *states,int show,int when)
{
	additem(title,states,T_TEXT,&opt.text,show,when);
}

void cMenu::atext(char *title, char *states)
{
	additem(title,states,T_TEXT,&opt.text,1,1);
}

//-----------------------------------------------------------------------------
// Name: nofields()
// Desc: Calculates Number of Fields in a String based on deliminator
//-----------------------------------------------------------------------------

int cMenu::nofields(char *str)
{
	char *ptr;
	int  no;
	for(no=1; (ptr=strchr(str,(char)'|'))!=NULL; no++)str=ptr+1;
	
	return no;
}

//-----------------------------------------------------------------------------
// Name: getfield()
// Desc: Grabs Field in string based on deliminator
//-----------------------------------------------------------------------------

void cMenu::getfield(char *str,char *dst,int no)
{
	char *ptr;
	int  i;
	for(i=1; (ptr=strchr(str,(char)'|'))!=NULL ; i++) 
	{
		if(i==no) break;
		str=ptr+1;
	}
	if(ptr)
	{
		i=(int)(ptr-str);
		strncpy(dst,str,i);
		dst[i]=0;
	}
	else
		strcpy(dst,str);
}

//-----------------------------------------------------------------------------
// Name: DrawBox()
// Desc: Fills Rectangle using DrawPrimitive Up
//-----------------------------------------------------------------------------

void cMenu::DrawBox( int x, int y, int w, int h, D3DCOLOR Color,LPDIRECT3DDEVICE9 pDevice)
{
	/*if( w < 0 )w = 1; 
    if( h < 0 )h = 1; 
    if( x < 0 )x = 1; 
    if( y < 0 )y = 1; 
    D3DRECT rec = { x, y, x + w, y + h }; 
    pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, Color, 0, 0 );
	struct Vertex 
	{
		float x,y,z,ht;
		DWORD Color;
	}
	V[4] = 
	{
		{(float)x,(float)(y+h), 0.0f, 0.0f, Color},
		{(float)x,(float)y, 0.0f, 0.0f, Color},
		{(float)(x+w),(float)(y+h), 0.0f, 0.0f, Color},
		{(float)(x+w),(float)y, 0.0f, 0.0f, Color}
	};
	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(NULL);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1); 
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
	pDevice->SetRenderState(D3DRS_DESTBLEND,4);
	pDevice->SetRenderState(D3DRS_SRCBLEND,3);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,V,sizeof(Vertex));
	return;*/
	Tools.g_pLine->SetWidth(h); 
    Tools.g_pLine->SetAntialias(1); 

    D3DXVECTOR2 VertexList[2]; 
    VertexList[0].x = x; 
    VertexList[0].y = y + (h >> 1); 
    VertexList[1].x = x + w; 
    VertexList[1].y = y + (h >> 1); 

	Tools.g_pLine->Begin(); 
	Tools.g_pLine->Draw(VertexList, 2, Color);//(FLOAT)DrawColor.a/255.0)); 
	Tools.g_pLine->End();
	return;
}

void cMenu::DrawBox_C( int x, int y, int w, int h, D3DCOLOR Color,LPDIRECT3DDEVICE9 pDevice)
{
	if( w < 0 )w = 1; 
    if( h < 0 )h = 1; 
    if( x < 0 )x = 1; 
    if( y < 0 )y = 1; 
    D3DRECT rec = { x, y, x + w, y + h }; 
    pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, Color, 0, 0 );
	/*struct Vertex 
	{
		float x,y,z,ht;
		DWORD Color;
	}
	V[4] = 
	{
		{(float)x,(float)(y+h), 0.0f, 0.0f, Color},
		{(float)x,(float)y, 0.0f, 0.0f, Color},
		{(float)(x+w),(float)(y+h), 0.0f, 0.0f, Color},
		{(float)(x+w),(float)y, 0.0f, 0.0f, Color}
	};
	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(NULL);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1); 
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
	pDevice->SetRenderState(D3DRS_DESTBLEND,4);
	pDevice->SetRenderState(D3DRS_SRCBLEND,3);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,V,sizeof(Vertex));
	return;*/
}

//-----------------------------------------------------------------------------
// Name: DrawBorder()
// Desc: Fills outside of Rectangle using 4 calls to DrawBox
//-----------------------------------------------------------------------------

void cMenu::DrawBorder(int x, int y, int w, int h, int s, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
    DrawBox_C(x, y-1, w, s, Color, pDevice );
    DrawBox_C(x-1, y, s, h, Color, pDevice );
    DrawBox_C((x+w), y, s, h, Color, pDevice );
    DrawBox_C(x, (y+h), w, s, Color, pDevice );
	return;
}

//-----------------------------------------------------------------------------
// Name: DrawGameTextPixelFlag()
//-----------------------------------------------------------------------------

void cMenu::DrawGameTextPixelFlag(int x, int y, DWORD color, DWORD flags, char *szFormat, ... )
{
    if( !szFormat )return;

    char logbuf[256] = { 0 };

    va_list va_alist;
    va_start (va_alist, szFormat);
    _vsnprintf(logbuf, sizeof(logbuf), szFormat, va_alist);
    va_end (va_alist);

    if( flags == DT_RIGHT )
    {
        SIZE Size = {0,0};
        if(font->GetTextExtent(logbuf, &Size) == S_OK)
        {
            x -= Size.cx;
        }
        flags = 0;
    } else if( flags == DT_CENTER )
    {
        SIZE Size = {0,0};
        if(font->GetTextExtent(logbuf, &Size) == S_OK)
        {
            x -= (Size.cx/2);
        }
        flags = 0;
    }
    font->DrawText((float)x+1, (float)y, D3DCOLOR_ARGB( 255, 0, 0, 0 ), logbuf, flags);
    font->DrawText((float)x-1, (float)y, D3DCOLOR_ARGB( 255, 0, 0, 0 ), logbuf, flags);
    font->DrawText((float)x, (float)y+1, D3DCOLOR_ARGB( 255, 0, 0, 0 ), logbuf, flags);
    font->DrawText((float)x, (float)y-1, D3DCOLOR_ARGB( 255, 0, 0, 0 ), logbuf, flags);
    font->DrawText((float)x, (float)y, color, logbuf, flags);
}

//-----------------------------------------------------------------------------
// Name: ShowMenu()
// Desc: Core Menu Function Displays Menu Calls Other Menu functions and navigation
//-----------------------------------------------------------------------------

void cMenu::ShowMenu(LPDIRECT3DDEVICE9 pDevice)
{
	//-----------------------------------------------------------------------------
	// Desc: Check Hotkeys
	//-----------------------------------------------------------------------------
	int	lm		=	IsKeyPressed(VK_LBUTTON, 0)&1;
	int	rm		=	IsKeyPressed(VK_RBUTTON, 0)&1;
	int	left	=	IsKeyPressed(VK_LEFT, 0)&1;
	int	right	=	IsKeyPressed(VK_RIGHT, 0)&1;
	int	up		=	IsKeyPressed(VK_UP, 0)&1;
	int	down	=	IsKeyPressed(VK_DOWN, 0)&1;
	//-----------------------------------------------------------------------------
	// Desc: Prepare/Reset Menu
	//-----------------------------------------------------------------------------

	Init();

	//-----------------------------------------------------------------------------
	// Desc: Show The Menu
	//-----------------------------------------------------------------------------
	if(IsKeyPressed(VK_INSERT, 0)&1) SHOW=(!SHOW);
	if(SHOW){

		//-----------------------------------------------------------------------------
		// Desc: Get Mouse Coordinates and translate
		//-----------------------------------------------------------------------------
		
		//-----------------------------------------------------------------------------
		// Desc: Move Menu
		//-----------------------------------------------------------------------------

		GetCursorPos(&mpos);// Update Mouse Coordinates
		ScreenToClient(GetForegroundWindow(),&mpos); // Translate to Current Window

		if(opt.options.move && GetAsyncKeyState(VK_LCONTROL))	// If Options for Left Control is Set
		{
			X =(((X<=mpos.x+4) && (X>=mpos.x)) || ((X>=mpos.x-4) && (X<=mpos.x)))?(X=mpos.x):(X+=((mpos.x-X)/4));
			Y =(((Y<=mpos.y+4) && (Y>=mpos.y)) || ((Y>=mpos.y-4) && (Y<=mpos.y)))?(Y=mpos.y):(Y+=((mpos.y-Y)/4));
		}

		//-----------------------------------------------------------------------------
		// Desc: Draw Menu Header
		//-----------------------------------------------------------------------------

		DrawBox(X,Y+3,WIDTH,T_SPC,C_BOX2,pDevice);// Render Menu Header Backround
		DrawBorder(X,Y+3,WIDTH,T_SPC,1,WHITE2,pDevice);// set-up border
		DrawGameTextPixelFlag(MC_FCTR(X,MC_MAXX),Y+5,C_TITLE,DT_CENTER|DT_SHADOW,"ZrC-CyB Hacks Update 2016");
         
		//-----------------------------------------------------------------------------
		// Desc: Fill Item Array and Render Menu Border and Box
		//-----------------------------------------------------------------------------

		DrawBox(X,MC_MSY,WIDTH,(NO*I_SPC),C_BOX,pDevice);// Render Menu Backround for items
		DrawBorder(X,MC_MSY,WIDTH,(NO*I_SPC),1,WHITE2,pDevice);// set-up border

		NO=0;
		acat("[Visual]","[Open]|[Close]",&opt.d3d.Main);
//			aitem("Bypass","[Off]|[On]",&opt.d3d.Bypass,opt.d3d.Main,1);
			aitem("Hide Menu","[Insert]",&opt.d3d.Exit,opt.d3d.Main,1);
//			aitem("Wallhack","[Off]|[On]",&opt.d3d.Wall,opt.d3d.Main,1);
			aitem("Wallhack","[Off]|[On]",&opt.d3d.Wall,opt.d3d.Main,1);
//			aitem("Champ Player","[Off]|[On]",&opt.d3d.Champ,opt.d3d.Main,1);
			aitem("Crosshair","[Off]|[On]",&opt.d3d.Cross,opt.d3d.Main,1);
			aitem("Cross Color","[White]|[Red]|[Green]|[Blue]|[Grey]|[Yellow]|[Orange]",&opt.d3d.CrosCol,opt.d3d.Main,1);

		acat("[Esp]","[Open]|[Close]",&opt.d3d.Esp);
			aitem("Esp Name","[Off]|[On]",&opt.d3d.EspName,opt.d3d.Esp,1);
			aitem("Name Color","[White]|[Red]|[Green]|[Blue]|[Grey]|[Yellow]|[Orange]",&opt.d3d.cEspNameCol,opt.d3d.Esp,1);
			aitem("Esp Head","[Off]|[On]",&opt.d3d.EspHead,opt.d3d.Esp,1);
			aitem("Head Color","[White]|[Red]|[Green]|[Blue]|[Grey]|[Yellow]|[Orange]",&opt.d3d.cEspHeadCol,opt.d3d.Esp,1);
			aitem("Esp Health","[Off]|[On]",&opt.d3d.EspHealth,opt.d3d.Esp,1);
			aitem("Esp Line","[Off]|[On]",&opt.d3d.EspLine,opt.d3d.Esp,1);
			aitem("Esp Box","[Off]|[On]",&opt.d3d.EspBox,opt.d3d.Esp,1);
			aitem("Esp Bone","[Off]|[On]",&opt.d3d.EspBone,opt.d3d.Esp,1);
			aitem("Bone Color","[White]|[Red]|[Green]|[Blue]|[Grey]|[Yellow]|[Orange]",&opt.d3d.cEspBoneCol,opt.d3d.Esp,1);

		acat("[Aimbot]","[Open]|[Close]",&opt.d3d.Aim);
			aitem("Target Aim","[Head]|[Body]",&opt.d3d.BoneTarget,opt.d3d.Aim,1);
			aitem("Aim Bot [ALT Right]","[Off]|[On]",&opt.d3d.AimBot,opt.d3d.Aim,1);
			aitem("Aim Bullet [Shift Left]","[Off]|[On]",&opt.d3d.AimBullet,opt.d3d.Aim,1);
//			aitem("Autoshoot","[Off]|[On]",&opt.d3d.AutoShot,opt.d3d.Aim,1);
//			aitem("Headshoot [Capslock]","[Off]|[On]",&opt.d3d.HeadShot,opt.d3d.Aim,1);
//			aitem("Auto Body [Shift Right]","[Off]|[On]",&opt.d3d.AutoBody,opt.d3d.Aim,1);
//			aitem("Bullet Killer [Mouse Right]","[Off]|[On]",&opt.d3d.KillerKey,opt.d3d.Aim,1);
//			aitem("Switch","[Primary]|[Secondary]",&opt.d3d.Switch,opt.d3d.Aim,1);
//			aitem("Bomb Killer [Delete]","[Off]|[On]",&opt.d3d.ScdKillerKey,opt.d3d.Aim,1);
		
		opt.d3d.Exit = 1;
		acat("[Player]","[Open]|[Close]",&opt.d3d.Player);
			aitem("GM Acces","[Off]|[1]|[2]",&opt.d3d.AccGM,opt.d3d.Player,1);
//			aitem("Fly Hack [Space]","[Off]|[On]",&opt.d3d.FlyHack,opt.d3d.Player,1);
//			aitem("No Respawn","[Off]|[On]",&opt.d3d.NoRespawn,opt.d3d.Player,1);
			aitem("Bug Character Hand [F6]","[Off]|[On]",&opt.d3d.BugWs,opt.d3d.Player,1);
//			aitem("Bug Character Flat [F7]","[Off]|[On]",&opt.d3d.BugDt,opt.d3d.Player,1);
//			aitem("Zombie [ALT Kiri Off]","[Off]|[HOME]",&opt.d3d.Zombie00,opt.d3d.Player,1);
//			aitem("Repeat Hack","[Off]|[On]",&opt.d3d.Repeat,opt.d3d.Player,1);
//			aitem("VoteKick","[Off]|[On]",&opt.d3d.AutoVote,opt.d3d.Player,1);
//			aitem("Wallshoot [BombKiller]","[Off]|[On]",&opt.d3d.Wst,opt.d3d.Player,1);
//			aitem("Invicible [Diam]","[Off]|[On]",&opt.d3d.Invi,opt.d3d.Player,1);
//			aitem("No Drop","[Off]|[On]",&opt.d3d.Fall,opt.d3d.Player,1);
			aitem("AFK Room","[Off]|[On]",&opt.d3d.Afk,opt.d3d.Player,1);
			aitem("Free Move","[Off]|[On]",&opt.d3d.Move,opt.d3d.Player,1);
			aitem("Plant CT","[Off]|[On]",&opt.d3d.PlantCT,opt.d3d.Player,1);
			aitem("Defuse CT","[Off]|[On]",&opt.d3d.DefuseCT,opt.d3d.Player,1);
			aitem("Free Plant C4","[Off]|[Site A]|[Site B]",&opt.d3d.Plant,opt.d3d.Player,1);
			aitem("Suicide","[Off]|[End]|[Auto]",&opt.d3d.Suicide,opt.d3d.Player,1);
			aitem("Exit Game","[F12]",&opt.d3d.Exit,opt.d3d.Player,1);

		acat("[Weapon]","[Open]|[Close]",&opt.d3d.Weapon);
//			aitem("Status Bomb","[Off]|[On]",&opt.d3d.OnBomb,opt.d3d.Weapon,1);
//			aitem("Replace Bomb [F2]","[Off]|[Lolipop]",&opt.d3d.Bomb,opt.d3d.Weapon,1);
//			aitem("Status RPG","[Off]|[On]",&opt.d3d.OnRpg,opt.d3d.Weapon,1);
//			aitem("Replace RPG [Mouse Left]","[Off]|[HK69]|[RPG-7]",&opt.d3d.Rpg,opt.d3d.Weapon,1);
//			aitem("No Recoil","[Off]|[On]",&opt.d3d.NoSpread,opt.d3d.Weapon,1);
//			aitem("Inf Ammo","[Off]|[On]",&opt.d3d.InfAmmo,opt.d3d.Weapon,1);
			aitem("Fast Reload","[Off]|[On]",&opt.d3d.RldM,opt.d3d.Weapon,1);
//			aitem("No Reload","[Off]|[On]",&opt.d3d.NoReload,opt.d3d.Weapon,1);
//			aitem("Fast Shoot","[Off]|[On]",&opt.d3d.FsSht,opt.d3d.Weapon,1);
//			aitem("Brutal Knife","[Off]|[On]",&opt.d3d.BstPs,opt.d3d.Weapon,1);
//			aitem("Quick Change","[Off]|[On]",&opt.d3d.Quick,opt.d3d.Weapon,1);
//			aitem("Rapid Fire","[Off]|[On]",&opt.d3d.FrSpd,opt.d3d.Weapon,1);

		acat("[Options]","[Open]|[Close]",&opt.options.main);
			aitem("Move Menu","[Off]|[Ctrl Left]",&opt.options.move,opt.options.main,1);
			aitem("Save Set","[Off]|[Saving]",&opt.options.save,opt.options.main,1);
			aitem("Load Set","[Off]|[Loading]",&opt.options.load,opt.options.main,1);
			aitem("Reset Menu","[Off]|[Resetting]",&opt.options.reset,opt.options.main,1);

		opt.options.save=0;
		opt.options.load=0;

		//-----------------------------------------------------------------------------
		// Desc: Loop Threw Item Index and Render Items
		//-----------------------------------------------------------------------------

		for(int no=0; no<NO; no++)
		{
			D3DCOLOR text;
			D3DCOLOR text2;
			D3DCOLOR text3;

			text=(*(items[no].val)>0)?C_ON:C_OFF;
			text2=(*(items[no].val)>0)?C_ON2:C_OFF2;
			text3=(*(items[no].val)>0)?C_ON2:C_OFF3;

			if(items[no].type==T_CAT)
				text=C_CAT;

			if(I_CUR==no){
				DrawBox_C(X,MC_ITEMY(no),WIDTH,I_SPC,C_CUR,pDevice);
			}

			if(mpos.x>X && mpos.x<MC_MAXX && mpos.y>MC_ITEMY(no) && mpos.y<MC_ITEMY(no)+I_SPC){
				DrawBox_C(X,MC_ITEMY(no),WIDTH,I_SPC,C_CUR,pDevice);
			}

			if(items[no].type!=T_CAT){
				DrawBox_C(X+5, MC_ITEMY(no)+5, 5, 5, text3, pDevice);
				DrawBorder(X+5, MC_ITEMY(no)+5, 5, 5,1, WHITE2,pDevice);
			}

			if(items[no].type==T_CAT){
				text2=C_CAT;
				DrawGameTextPixelFlag(X+I_OFS,MC_ITEMY(no)+2,text,DT_SHADOW,items[no].title);
			}
			else{
				DrawGameTextPixelFlag(X+I_OFS+12,MC_ITEMY(no)+2,text,DT_SHADOW,items[no].title);
			}
			DrawGameTextPixelFlag(X+S_OFS,MC_ITEMY(no)+2,text2,DT_RIGHT|DT_SHADOW,items[no].state);
		}

		//-----------------------------------------------------------------------------
		// Desc: Draw Info and FrameRate()
		//-----------------------------------------------------------------------------

		// Draw Info
		DrawBox(X,MC_ITEMY1(NO)+(F_SPC/2)-2,WIDTH/2,(F_SPC),C_BOX,pDevice);
		DrawBorder(X,MC_ITEMY1(NO)+(F_SPC/2)-2,WIDTH/2,(F_SPC),1,WHITE2,pDevice);
		DrawGameTextPixelFlag(X+(WIDTH)/4,MC_ITEMY1(NO)+(F_SPC/2)+1,C_INFO,DT_CENTER,"PB-IND");
		// Draw FrameRate
		DrawBox(X+(WIDTH)/2,MC_ITEMY1(NO)+(F_SPC/2)-2,WIDTH/2,(F_SPC),C_BOX,pDevice);
		DrawBorder(X+(WIDTH)/2,MC_ITEMY1(NO)+(F_SPC/2)-2,WIDTH/2,(F_SPC),1,WHITE2,pDevice);
		DrawGameTextPixelFlag(X+((WIDTH)/4)*3,MC_ITEMY1(NO)+(F_SPC/2)+1,C_INFO,DT_CENTER,FPS(0));

		//-----------------------------------------------------------------------------
		// Desc: Draw Menu Date and Time()
		//-----------------------------------------------------------------------------

		// Draw Date
		DrawBox(X,MC_ITEMY2(NO)+(F_SPC/2)-2,WIDTH/2,(F_SPC),C_BOX,pDevice);
		DrawBorder(X,MC_ITEMY2(NO)+(F_SPC/2)-2,WIDTH/2,(F_SPC),1,WHITE2,pDevice);
		DrawGameTextPixelFlag(X+(WIDTH)/4,MC_ITEMY2(NO)+(F_SPC/2)+1,C_INFO,DT_CENTER,DATE());
		// Draw Time
		DrawBox(X+(WIDTH)/2,MC_ITEMY2(NO)+(F_SPC/2)-2,WIDTH/2,(F_SPC),C_BOX,pDevice);
		DrawBorder(X+(WIDTH)/2,MC_ITEMY2(NO)+(F_SPC/2)-2,WIDTH/2,(F_SPC),1,WHITE2,pDevice);
		DrawGameTextPixelFlag(X+((WIDTH)/4)*3,MC_ITEMY2(NO)+(F_SPC/2)+1,C_INFO,DT_CENTER,TIME());

		//-----------------------------------------------------------------------------
		// Desc: Draw Menu Footer()
		//-----------------------------------------------------------------------------

		DrawBox(X,MC_ITEMY3(NO)+(F_SPC/2)-2,WIDTH,(F_SPC),C_BOX2,pDevice);// Draw Footer Filled
		DrawBorder(X,MC_ITEMY3(NO)+(F_SPC/2)-2,WIDTH,(F_SPC),1,WHITE2,pDevice);// Footer Border
		DrawGameTextPixelFlag(MC_FCTR(X,MC_MAXX),MC_ITEMY3(NO)+(F_SPC/2),C_FOOTER,DT_CENTER|DT_SHADOW,"~|| www.zero-cyberz-server.com ||~");
//		DrawGameTextPixelFlag(MC_FCTR(X,MC_MAXX),MC_ITEMY3(NO)+(F_SPC/2),C_FOOTER,DT_CENTER|DT_SHADOW,"www.example.com");

		//-----------------------------------------------------------------------------
		// Desc: Mouse Navigation
		//-----------------------------------------------------------------------------

		int mno = 999; // Item Mouse is on

		if(mpos.x>X && mpos.x<MC_MAXX && mpos.y<MC_ITEMY(NO) && mpos.y>Y)
			mno = ((mpos.y-T_SPC)>Y)?((mpos.y - Y - T_SPC - (T_SPC/2)) / I_SPC):(999);

		if(mno!=999 && rm && (*items[mno].val)>0)
		{
			(*items[mno].val)-=1;
			Sound.wav.playsoundmem((LPCSTR)SWITCH);
		}

		if(mno!=999 && lm && (*items[mno].val)<(items[mno].max-1))
		{
			(*items[mno].val)+=1;
			Sound.wav.playsoundmem((LPCSTR)SWITCH);
		}

		//-----------------------------------------------------------------------------
		// Desc: Keyboard Navigation()
		//-----------------------------------------------------------------------------

		if(left && (*items[I_CUR].val)>0)
		{
			(*items[I_CUR].val)-=1;
			Sound.wav.playsoundmem((LPCSTR)SWITCH);
		}

		if(right && (*items[I_CUR].val)<(items[I_CUR].max-1))
		{
			(*items[I_CUR].val)+=1;
			Sound.wav.playsoundmem((LPCSTR)SWITCH);
		}

		if(up){
			do{
				I_CUR=(I_CUR==0)?(NO-1):(I_CUR-1);
			}while (items[I_CUR].type==T_TEXT);
			Sound.wav.playsoundmem((LPCSTR)MOVE);
		}

		if(down || items[I_CUR].type==T_TEXT){
			do{
				I_CUR=(I_CUR+1)%NO;
			}while (items[I_CUR].type==T_TEXT);
			Sound.wav.playsoundmem((LPCSTR)MOVE);
		}

		//-----------------------------------------------------------------------------
		// Desc: Menu Saftey / Sanity Checks and ReEncryption
		//-----------------------------------------------------------------------------

		if(I_CUR>NO)I_CUR=NO-1; // Prevent Selection From Hiding be hind hidden item

		//-----------------------------------------------------------------------------

		//Draw a Cursor; Full credits to Credzis
		Tools.DrawMouse(D3DXVECTOR2((float)mpos.x,(float)mpos.y),D3DCOLOR_ARGB(255, 0, 255, 0));
		//-----------------------------------------------------------------------------
	}
}