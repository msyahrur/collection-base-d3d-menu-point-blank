/*++

Copyright (c) Main Cit 96 Corporation.  All rights reserved.

Module Name:

   cD3D.h

Abstract:

    Type definitions for the basic sized types.

Author:

Revision History:

--*/
/**************************************************************************************************************************************************************/
int lm,rm,flm,frm;
void PrintText(float x, float y, D3DCOLOR fontColor, char *text, ...)
{
	RECT rct;
	rct.left = x - 1;
	rct.right = x + 1;
	rct.top = y - 1 ;
	rct.bottom = y + 1;
	if(!text) { return; }
	va_list va_alist;
	char logbuf[256] = {0};
	va_start (va_alist, text);
	_vsnprintf (logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), text, va_alist);
	va_end (va_alist);
	RECT FontRect = { x, y, x, y };
	pFont->DrawText(NULL, logbuf, -1, &rct, DT_NOCLIP, fontColor);
} 

void DrawString(int x, int y, DWORD color, const char *fmt, ...)
{
	RECT FontPos = { x, y, x + 30, y + 20 };
	char buf[1024] = {'\0'};
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	
	pFont->DrawText(0, buf, -1, &FontPos, DT_NOCLIP, color);
}

void DrawStringVote(int x, int y, DWORD color, DWORD Style,const char *fmt, ...){
	RECT FontPos = { x, y, x + 120, y + 16 };
	char buf[1024] = {'\0'};
	va_list va_alist;
	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	pFont->DrawText(NULL, buf, -1, &FontPos, DT_LEFT | DT_WORDBREAK, color);
}

void Draw_Text(char* st,int x,int y,DWORD color,ID3DXFont* pFont)
{
    RECT Reth;
    SetRect(&Reth, x, y, x, y );
    pFont->DrawTextA(NULL,st,-1,&Reth,DT_NOCLIP|DT_LEFT,color);
}

void DrawLine (float StartX, float StartY, float EndX, float EndY, int Width, D3DCOLOR dColor)
{
	pLine[0].SetWidth(Width);
	pLine[0].SetGLLines(0);
	pLine[0].SetAntialias(1);

	D3DXVECTOR2 v2Line[2];
	v2Line[0].x = StartX;
	v2Line[0].y = StartY;
	v2Line[1].x = EndX;
	v2Line[1].y = EndY;

	pLine[0].Begin();
	pLine[0].Draw(v2Line, 2, dColor);
	pLine[0].End();
}

void DrawLineHealth( long Xa, long Ya, long Xb, long Yb, DWORD dwWidth,float Health)
{
	DWORD Color = GREEN;
    if (Health > 99) Health = 100; 
    if (Health < 5) Health = 5;  
    if (Health < 90 )Color = GREEN;   
    if (Health < 70 )Color = D3DCOLOR_ARGB(255, 255, 255, 0);   
    if (Health < 50 )Color = D3DCOLOR_ARGB(255, 255, 165, 0);   
    if (Health < 30) Color = RED;   
    if (Health < 10) Color = D3DCOLOR_ARGB(255, 165, 0, 0);  
	D3DXVECTOR2 vLine[ 2 ];
	pLine->SetAntialias( 0 );
	pLine->SetWidth( (float)dwWidth );
	pLine->Begin();
	vLine[ 0 ][ 0 ] = (float)Xa;
	vLine[ 0 ][ 1 ] = (float)Ya;
	vLine[ 1 ][ 0 ] = (float)Xb;
	vLine[ 1 ][ 1 ] = (float)Yb;
	pLine->Draw( vLine, 2, Color );
	pLine->End();
}

void  FillRGB( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice )
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

void FillRGBBOX( float x, float y, float w, float h, D3DCOLOR color){
if( w < 0 )w = 1;
if( h < 0 )h = 1;
if( x < 0 )x = 1;
if( y < 0 )y = 1;
D3DRECT rec = { x, y, x + w, y + h };
pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}
DWORD TeamColor;

void DrawBorders( float x, float y, float w, float h, int px, float Health){
FillRGBBOX( x, (y + h - px), w, px, TeamColor);
FillRGBBOX( x, y, px, h, TeamColor);
FillRGBBOX( x, y, w, px, TeamColor);
FillRGBBOX( (x + w - px), y, px, h, TeamColor); 
}

void DrawBoxz(int x, int y, int w, int h, D3DCOLOR BoxColor, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice){
	FillRGB(x, y, w, h, BoxColor, pDevice);
	DrawBorder(x, y, w, h, 1, BorderColor, pDevice);
}

void DrawBorders( int x, int y, int w, int h, int px, D3DCOLOR BorderColor,IDirect3DDevice9* pDevice ) 
{ 
	if( !pDevice )
		return;
    FillRGB( x, (y + h - px), w, px,     BorderColor, pDevice ); // Height Kanan
    FillRGB( x, y, px, h,                BorderColor, pDevice ); // Width Atas
    FillRGB( x, y, w, px,                BorderColor, pDevice ); // Height Kiri
    FillRGB( (x + w - px), y, px, h,     BorderColor, pDevice ); // Width Bawah
}

void DrawStringESP(LPDIRECT3DDEVICE9 pDevice, float x, float y, DWORD COLOR, LPD3DXFONT pFont, const char *fmt, ...)
{

	RECT FontPos = { x, y, x + 30, y + 20 };
	char buf[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, fmt);
	vsprintf(buf, fmt, va_alist);
	va_end(va_alist);
	pFont->DrawTextA(NULL, buf, -1, &FontPos, DT_NOCLIP, COLOR);
}

#define PI 3.14159265//Defining what PI is. PI is a Circle 
int CenterX = GetSystemMetrics( 0 ) / 2-1;//Gets screen X resolution then cutting it in half to get the center.
int CenterY = GetSystemMetrics( 1 ) / 2-1;//Gets screen Y resolution then cutting it in half to get the center.

D3DTLVERTEX CreateD3DTLVERTEX (float X, float Y, float Z, float RHW, D3DCOLOR color, float U, float V)
{
	D3DTLVERTEX v;

	v.fX = X;
	v.fY = Y;
	v.fZ = Z;
	v.fRHW = RHW;
	v.Color = color;
	v.fU = U;
	v.fV = V;

	return v;
}

#define PISSS 3.14159265
void Circle( float x, float y, float rad, bool center, DWORD color ,LPDIRECT3DDEVICE9 pDevice)
{
	const int NUMPOINTS = 34;

	if(!center)
	{
		x -= rad;
		y -= rad;
	}

	D3DTLVERTEX Circle[NUMPOINTS + 1];
	int i;
	float X;
	float Y;
	float Theta;
	float WedgeAngle;
	WedgeAngle = (float)( (2*PISSS) / NUMPOINTS );
	for( i=0; i<=NUMPOINTS; i++ )
	{
		Theta = i * WedgeAngle;
		X = (float)( x + rad * cos(Theta) );
		Y = (float)( y - rad * sin(Theta) );
		Circle[i] = CreateD3DTLVERTEX( X, Y, 0.0f, 1.0f, color, 0.0f, 0.0f );
	}
	pDevice	->	SetFVF			( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
	pDevice	->	SetTexture		( 0, 0 );
	pDevice	->	DrawPrimitiveUP	( D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]) );
}

void CriarCaixa(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{

	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DPT_TRIANGLESTRIP);
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 1, 1);

}
//-----------------------------------------------------------------------------------------//
void DesenharCaixa(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
	CriarCaixa(x, y, 1, h, Color, pDevice);
	CriarCaixa(x, y + h, w, 1, Color, pDevice);
	CriarCaixa(x, y, w, 1, Color, pDevice);
	CriarCaixa(x + w, y, 1, h + 1, Color, pDevice);
}
//-----------------------------------------------------------------------------------------//
void CallESPBox(int iSlot, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 HeadPos, HeadScreen;
	D3DXVECTOR3 FootPos, FootScreen;

	if(GetUserBone(HeadPos,7,iSlot)){
	if(GetUserBone(FootPos,8,iSlot)){
	if (WorldToScreen(pDevice,HeadPos, HeadScreen))
	{
	if (WorldToScreen(pDevice,FootPos, FootScreen))
	{
		float w = (FootScreen.y - HeadScreen.y) / 4;
		DesenharCaixa(HeadScreen.x - w, HeadScreen.y, w * 2, FootScreen.y - HeadScreen.y, Color, pDevice);
	}}
	}}
}
//-----------------------------------------------------------------------------------------//
void DrawLineBone(float StartX, float StartY, float EndX, float EndY, int Width, D3DCOLOR dColor)
{
	pLine[0].SetWidth(Width);
	pLine[0].SetGLLines(0);
	pLine[0].SetAntialias(1);

	D3DXVECTOR2 v2Line[2];
	v2Line[0].x = StartX;
	v2Line[0].y = StartY;
	v2Line[1].x = EndX;
	v2Line[1].y = EndY;

	pLine[0].Begin();
	pLine[0].Draw(v2Line, 2, dColor);
	pLine[0].End();
}
//-----------------------------------------------------------------------------------------//
void DrawHealthBar(D3DXVECTOR3 Head, D3DXVECTOR3 Foot, float Health, LPDIRECT3DDEVICE9 pDevice)
{
	DWORD Color = D3DCOLOR_ARGB(255, 0, 255, 0);
	if (Health >= 99) Health = 100;
	if (Health <= 7) Health = 7;

	if (Health <= 90)Color = GREEN;
	if (Health <= 70)Color = D3DCOLOR_ARGB(255, 255, 255, 0);
	if (Health <= 50)Color = D3DCOLOR_ARGB(255, 255, 165, 0);
	if (Health <= 30) Color = RED;
	if (Health <= 10) Color = D3DCOLOR_ARGB(255, 165, 0, 0);

	Head.y = Head.y + 1;
	Foot.y = Foot.y + 1;

	D3DXVECTOR3 Box = Head - Foot;

	if (Box.y < 0)
		Box.y *= -1;


	FillRGB((int)Head.x - ((int)Box.y / 4) - 6, (int)Head.y - 1, 1.2, (int)Box.y + 1, BLACKNESS, pDevice);
	FillRGB((int)Head.x - ((int)Box.y / 4) - 5, (int)Head.y, 3.1, Health * (Foot.y - Head.y) / 100, Color, pDevice);
}
//-----------------------------------------------------------------------------------------//
void CallESPHealth(int iSlot, LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 vHead, vFoot, sHead, sFoot;
	if (GetUserBone(vHead,7, iSlot))
	{
	if (GetUserBone(vFoot,8, iSlot))
	{
	if (WorldToScreen(pDevice,vHead, sHead))
	{
		if (WorldToScreen(pDevice,vFoot, sFoot))
		{
		DrawHealthBar(sHead, sFoot, CGameCharaManager::g_pCharaManager()->GetCharaByNetIdx(iSlot)->getCurHP_Real(), pDevice);
		}
	}
	}
	}
}
//-----------------------------------------------------------------------------------------//
void CallESPLine(int i,D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
		D3DVIEWPORT9 viewP;
		pDevice->GetViewport(&viewP);
		DWORD OnTopX = viewP.Width / 2;
		DWORD OnTopY = viewP.Y;
		D3DXVECTOR3 vHead,sHead;
	if (GetUserBone(vHead,7, i))
	{
		if (WorldToScreen(pDevice,vHead, sHead))
		{
		FillRGB((float)sHead.x, (float)sHead.y, 3, 3,Color, pDevice );
		DrawLineBone(OnTopX, OnTopY, (int)sHead.x - 1.5, (int)sHead.y - 1.5, 2, Color);
		}
	}
	}
//-----------------------------------------------------------------------------------------//
void DrawBone(int iSlot,int Start,int End,DWORD Color,LPDIRECT3DDEVICE9 pDevice)
{
D3DXVECTOR3 vStart,vEnd;
D3DXVECTOR3 vvStart,vvEnd;
if(GetUserBone(vStart,Start,iSlot))
{
if(GetUserBone(vEnd,End,iSlot))
{
if(WorldToScreen(pDevice,vStart,vvStart))
{
if(WorldToScreen(pDevice,vEnd,vvEnd))
{
DrawLineBone(vvStart.x,vvStart.y,vvEnd.x,vvEnd.y,1,Color);
}}}}}
//-----------------------------------------------------------------------------------------//
void CallESPBone(int iSlot,DWORD Color,LPDIRECT3DDEVICE9 pDevice)
{
	DrawBone(iSlot, 6, 7, Color, pDevice);
	DrawBone(iSlot, 0, 6, Color, pDevice);
	DrawBone(iSlot, 6, 10, Color, pDevice);
	DrawBone(iSlot, 6, 11, Color, pDevice);
	DrawBone(iSlot, 0, 12, Color, pDevice);
	DrawBone(iSlot, 0, 13, Color, pDevice);
	DrawBone(iSlot, 12, 14, Color, pDevice);
	DrawBone(iSlot, 13, 15, Color, pDevice);
	DrawBone(iSlot, 14, 8, Color, pDevice);
	DrawBone(iSlot, 15, 9, Color, pDevice);
}
//-----------------------------------------------------------------------------------------//
void CallESPBoneDino(int iSlot,D3DCOLOR Color,LPDIRECT3DDEVICE9 pDevice)
{
    DrawBone(iSlot, 9, 8, Color,pDevice); 
    DrawBone(iSlot, 8, 7, Color,pDevice); 
    DrawBone(iSlot, 7, 6, Color,pDevice); 
    DrawBone(iSlot, 5, 4, Color,pDevice); 
    DrawBone(iSlot, 4, 3, Color,pDevice); 
    DrawBone(iSlot, 3, 0, Color,pDevice); 
    DrawBone(iSlot, 0, 10, Color,pDevice); 
    DrawBone(iSlot, 0, 11, Color,pDevice); 

}
//-----------------------------------------------------------------------------------------//
/*void _fastcall KickPlayerName (int Idx,int Reason)
{
		DWORD KickUser		= ResultSetEvent;
		DWORD BaseECX		= *(DWORD*)(g_pGameContext);
		PlayerKickData KickData;
		PlayerKickData* pKickData;
		KickData.Index = Idx;
		KickData.Reason = Reason;
		pKickData = &KickData;
		__asm{
			push 0
			mov eax,[pKickData]
			add eax,4
			push eax
			mov edx,[pKickData]
			push edx
			push 0xA1
			mov ecx,[BaseECX]
			call [KickUser]
		}
}*/
//-----------------------------------------------------------------------------------------//
void DoVote(int IdxChar,int IdxReason)
{
	DWORD dwBZakilayer = *(PDWORD)Resultg_pGameContext;
	BYTE pIdxChar[8];
	*(PBYTE)(pIdxChar) = IdxChar; 
	DWORD dwIdxChar = (DWORD)pIdxChar;
	DWORD dwPush = ResultSetEvent;
	_asm
	{
		push 0;
		push IdxReason;
		push 0;
		jmp DoIt;
		nop
DoIt:
		push dwIdxChar;
		push dwIdxChar;
		push 0x1FC; // 0xA1
		mov ecx, dwBZakilayer;
		jmp Finish;
Finish:
		call dwPush;
	}
}
//-----------------------------------------------------------------------------------------//
BOOL IsInFiturBox(int x,int y,int w,int h)
{
	POINT MousePosition; 
	GetCursorPos(&MousePosition); 
	ScreenToClient(GetForegroundWindow(),&MousePosition);
	return(MousePosition.x > (x - 18) && MousePosition.x < (x + w - 18) && MousePosition.y > (y - 10) && MousePosition.y < (y + h - 10));
}
//-----------------------------------------------------------------------------------------//
void CallESPNames(int i,int Reason, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 HeadPos, HeadScreen;
	if(GetUserBone(HeadPos,7,i)){
	if (WorldToScreen(pDevice,HeadPos, HeadScreen))
	{
		PrintText((int)HeadScreen.x-10.0,(int)HeadScreen.y - 40.0,RED,"%s",CGameContext::Singleton()->getNickForSlot(i));
	}
	}
}
//-----------------------------------------------------------------------------------------//
void Box3D(int HeadX, int HeadY, int bottomX, int bottomY, float Distance_Player, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
{
	float drawW = 245 / Distance_Player;
	float drawW2 = 135 / Distance_Player;
	float drawW3 = 55 / Distance_Player;

	DrawLine(bottomX - drawW, bottomY, bottomX + drawW, bottomY, 1, Color);
	DrawLine(HeadX - drawW, HeadY, HeadX + drawW, HeadY, 1, Color);
	DrawLine(HeadX - drawW, HeadY, bottomX - drawW, bottomY, 1, Color);
	DrawLine(HeadX + drawW, HeadY, bottomX + drawW, bottomY, 1, Color);
	DrawLine(HeadX - drawW2, HeadY - drawW3, bottomX - drawW2, bottomY - drawW3, 1, Color);
	DrawLine(bottomX - drawW, bottomY, bottomX - drawW2, bottomY - drawW3, 1, Color);
	DrawLine(HeadX - drawW, HeadY, HeadX - drawW2, HeadY - drawW3, 1, Color);
	DrawLine((HeadX + drawW) + drawW2, HeadY - drawW3, (bottomX + drawW) + drawW2, bottomY - drawW3, 1, Color);
	DrawLine(bottomX + drawW, bottomY, (bottomX + drawW) + drawW2, bottomY - drawW3, 1, Color);
	DrawLine(HeadX + drawW, HeadY, (HeadX + drawW) + drawW2, HeadY - drawW3, 1, Color);
	DrawLine(HeadX - drawW2, HeadY - drawW3, (HeadX + drawW) + drawW2, HeadY - drawW3, 1, Color);
	DrawLine(bottomX - drawW2, bottomY - drawW3, (bottomX + drawW) + drawW2, bottomY - drawW3, 1, Color);
}
//-----------------------------------------------------------------------------------------//
void Desenhar3D(int x, int y, int w, int h, D3DCOLOR COLOR, LPDIRECT3DDEVICE9 pDevice)
{
	CriarCaixa(x, y, 1, h, COLOR, pDevice);
	CriarCaixa(x, y + h, w, 1, COLOR, pDevice);
	CriarCaixa(x, y, w, 1, COLOR, pDevice);
	CriarCaixa(x + w, y, 1, h + 1, COLOR, pDevice);
}
//-----------------------------------------------------------------------------------------//
void CallESPBox3D(int iSlot, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{

	D3DXVECTOR3 HeadPos, HeadScreen;
	D3DXVECTOR3 FootPos, FootScreen;

	if(GetUserBone(HeadPos,7,iSlot)){
	if(GetUserBone(FootPos,7,iSlot)){
	if (WorldToScreen(pDevice,HeadPos, HeadScreen))
	{
		if (WorldToScreen(pDevice,FootPos, FootScreen))
		{

		float Distance = (FootScreen.y - HeadScreen.y);
		Box3D((int)HeadScreen.x, (int)HeadScreen.y, (int)FootScreen.x, (int)FootScreen.y, Distance, Color, pDevice);
		}
	}}}
}
//-----------------------------------------------------------------------------------------//
void DrawD3DBorder(int x, int y, int w, int h, int px, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice)
{
	FillRGB(x, (y + h - px), w, px, BorderColor, pDevice);
	FillRGB(x, y, px, h, BorderColor, pDevice);
	FillRGB(x, y, w, px, BorderColor, pDevice);
	FillRGB(x + w - px, y, px, h, BorderColor, pDevice);
}
//-----------------------------------------------------------------------------------------//
//void HealthEqui(LPDIRECT3DDEVICE9 pDevice, int x, int y, float Health)
//{
//const D3DCOLOR colours[] = { D3DCOLOR_ARGB(255,255,000,000), D3DCOLOR_ARGB(255,255,000,000), D3DCOLOR_ARGB(255,255,000,000), D3DCOLOR_ARGB(255,255,000,000), ORANGE, ORANGE, ORANGE, ORANGE, YELLOW, YELLOW, YELLOW, YELLOW,  D3DCOLOR_ARGB(255,000,255,000),   D3DCOLOR_ARGB(255,000,255,000),   D3DCOLOR_ARGB(255,000,255,000),   D3DCOLOR_ARGB(255,000,255,000),   D3DCOLOR_ARGB(255,000,255,000),   D3DCOLOR_ARGB(255,000,255,000), BLUE, BLUE };	// this is our order
//int boxSizeX = 2;	
//	int boxSizeY = 6;
//	int boxGap = 1;
//	for ( int i = 0 ; i < 20; i++ )
//	{
//		if ( Health > ( 5 * i ) )
//			FillRGB(x,y, boxSizeX, 4,colours[i],pDevice);
//		else
//            FillRGB(x,y, boxSizeX, 4,D3DCOLOR_ARGB(255,128,128,128),pDevice);
//		x = x + boxSizeX+ boxGap;	
//	}
//}
//-----------------------------------------------------------------------------------------//
void Healthbarnew(LPDIRECT3DDEVICE9 pDevice,float x, float y, float Health)
{
	DWORD Color = D3DCOLOR_ARGB(255, 0, 255, 0);
	if (Health >= 99) Health = 100;
	if (Health <= 7) Health = 7;
	if (Health <= 90)Color = GREEN;
	if (Health <= 70)Color = D3DCOLOR_ARGB(255, 255, 255, 0);
	if (Health <= 50)Color = D3DCOLOR_ARGB(255, 255, 165, 0);
	if (Health <= 30) Color = RED;
	if (Health <= 10) Color = D3DCOLOR_ARGB(255, 165, 0, 0);
	DrawBorder(x-1,y-1,52,5,1,BLACK,pDevice );
	FillRGB(x,y,Health/2,3,Color,pDevice );
}
//-----------------------------------------------------------------------------------------//
void CallESPHealthBar(int iSlot,LPDIRECT3DDEVICE9 pDevice)
{
	if(GetUserBone(vStart,15,iSlot))
	{
		if(GetUserBone(vEnd,9,iSlot))
		{
			if (WorldToScreen(pDevice,vStart,OnXScreen))
			{
				if (WorldToScreen(pDevice,vEnd,OnYScreen))
				{
					Healthbarnew(pDevice,(float)OnXScreen.x-25, (float)OnYScreen.y+10,CGameCharaManager::g_pCharaManager()->GetCharaByNetIdx(iSlot)->getCurHP_Real());
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------------------//
void CallESPHealthSTR(int iSlot, D3DCOLOR Color,LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 vHead, vScreen;
	if(GetUserBone(vHead,7,iSlot))
	{
		if (WorldToScreen(pDevice,vHead,vScreen))
		{
		DrawStringESP(pDevice, (int)vScreen.x + 1, (int)vScreen.y - 55, Color, pFont, "HP: %0.f", CGameCharaManager::g_pCharaManager()->GetCharaByNetIdx(iSlot)->getCurHP_Real());
		}
}
}
//-----------------------------------------------------------------------------------------//
void DrawESPLine ( long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, D3DCOLOR Color )
{
	D3DXVECTOR2 vLine[ 2 ];
	pLine->SetAntialias( true );

	pLine->SetWidth( (float)dwWidth );
	pLine->Begin();

	vLine[ 0 ][ 0 ] = (float)Xa;
	vLine[ 0 ][ 1 ] = (float)Ya;
	vLine[ 1 ][ 0 ] = (float)Xb;
	vLine[ 1 ][ 1 ] = (float)Yb;

	pLine->Draw( vLine, 2, Color );
	pLine->End();
}
//-----------------------------------------------------------------------------------------//
#define YELLOW			D3DCOLOR_ARGB(255, 255, 255, 000) 
#define ORANGE			D3DCOLOR_ARGB(255, 255, 125, 000)
void HealthBar(float x, float y, float Health, LPDIRECT3DDEVICE9 pDevice)
{
	DWORD HPcol = GREEN;
	if (Health < 90)HPcol = YELLOW;
	if (Health < 80) HPcol = ORANGE;
	if (Health < 40) HPcol = RED;
	if(Health > 100)Health = 100;
	DrawBorder(x-1,y-1,52,5,1,BLACK,pDevice );
	FillRGB(x,y,Health/2,3,HPcol,pDevice );
}
//-----------------------------------------------------------------------------------------//
void PingServer(int x, int y, float Health, IDirect3DDevice9* pDevice)
{
	if( !pDevice )
		return;
	for (int index = 0; index <= (Health-1); index++)
	{
	D3DCOLOR HPcol = GREEN;
	if (Health == 3 )HPcol = ORANGE;
	if (Health == 2 )HPcol = ORANGE;
	if (Health == 1) HPcol = RED;
	FillRGB(x + (index*4),y,3,14,HPcol,pDevice);
	}
}
//-----------------------------------------------------------------------------------------//
void CallPingServer(int iSlot,LPDIRECT3DDEVICE9 pDevice)
{
	if(GetUserBone(vStart,15,iSlot))
	{
		if(GetUserBone(vEnd,9,iSlot))
		{
			if (WorldToScreen(pDevice,vStart,OnXScreen))
			{
				if (WorldToScreen(pDevice,vEnd,OnYScreen))
				{
					PingServer((float)OnXScreen.x-23, (float)OnYScreen.y + 20,CGameContext::g_pGameContext()->GetPing(iSlot),pDevice);
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------------------//
void CallESPKillDeath(int iSlot, D3DCOLOR Color,LPDIRECT3DDEVICE9 pDevice)
{
	D3DXVECTOR3 vHead, vScreen;
	if(GetUserBone(vHead,7,iSlot))
	{
		if (WorldToScreen(pDevice,vHead,vScreen))
		{
		DrawString(vScreen.x-50,vScreen.y-20,Color,"Kill[%d] Death[%d]",CGameContext::g_pGameContext()->getIndividualScore(iSlot)->Kill,CGameContext::g_pGameContext()->getIndividualScore(iSlot)->Dead);
		}
}
}
//-----------------------------------------------------------------------------------------//
void LinePlayerTarget(D3DXVECTOR3 vEnemy,D3DXVECTOR3 vScreen,LPDIRECT3DDEVICE9 pDevice)
{
	if(WorldToScreen(pDevice,vEnemy,vScreen))
	{
		Circle (OnScreen.x, OnScreen.y,6,true,RainbowTextTest,pDevice);
		FillRGB(OnScreen.x-10, OnScreen.y, 7, 1,RainbowTextTest,pDevice);
		FillRGB(OnScreen.x+4, OnScreen.y, 7, 1,RainbowTextTest,pDevice);
		FillRGB(OnScreen.x, OnScreen.y-10, 1, 7,RainbowTextTest,pDevice);
		FillRGB(OnScreen.x, OnScreen.y+4, 1, 7,RainbowTextTest,pDevice);
		//if(GetPlayerTarget(CGameContext::g_pGameContext()->setMySlotIdx())){
			DrawLine(512,384,vScreen.x,vScreen.y,1,RED);
	//	}else{
	//		DrawLine(512,384,vScreen.x,vScreen.y,1,RainbowTextTest);
	//	}

	}
}
//-----------------------------------------------------------------------------------------//
void Crosshair(LPDIRECT3DDEVICE9 pDevice, D3DCOLOR Color)
{
	if(Cross == 1){
	D3DVIEWPORT9 viewP;
	pDevice->GetViewport( &viewP );
	int x = viewP.Width / 2; 
	int y = viewP.Height / 2; 
	Circle (x,y,6,true,Color,pDevice);
	FillRGB(x-10, y, 7, 1,Color,pDevice);
	FillRGB(x+4, y, 7, 1,Color,pDevice);
	FillRGB(x, y-10, 1, 7,Color,pDevice);
	FillRGB(x, y+4, 1, 7,Color,pDevice);
	}
}
//-----------------------------------------------------------------------------------------//
void CrosshairNEW(LPDIRECT3DDEVICE9 pDevice, D3DCOLOR Color)
{
		D3DVIEWPORT9 viewP;
		pDevice->GetViewport( &viewP );
		DWORD ScreenCenterX = viewP.Width / 2; 
		DWORD ScreenCenterY = viewP.Height / 2; 
		D3DRECT rec16 = {ScreenCenterX-2, ScreenCenterY-2, ScreenCenterX+ 2, ScreenCenterY+2};
		D3DRECT rec17 = {ScreenCenterX-2, ScreenCenterY-2, ScreenCenterX+ 2,ScreenCenterY+2};  
		pDevice->Clear( 1, &rec16, D3DCLEAR_TARGET, D3DXCOLOR(Color), 0,  0 );//red
		pDevice->Clear( 1, &rec17, D3DCLEAR_TARGET, D3DXCOLOR(Color), 0,  0 );
}
//-----------------------------------------------------------------------------------------//
void DrawBox(INT x, INT y, INT w, INT h, INT px, DWORD Fill, DWORD Border, LPDIRECT3DDEVICE9 pDevice)
{
	FillRGB(x, y, w, h, Fill, pDevice);
	DrawBorder(x, y, w, h, px, Border, pDevice);
}
//-----------------------------------------------------------------------------------------//
POINT cPos;				//
INT CheckTabs(INT x, INT y, INT w, INT h)
{
	GetCursorPos(&cPos);
	ScreenToClient(GetForegroundWindow(),&cPos);
	if(cPos.x > x && cPos.x < x + w && cPos.y > y && cPos.y < y + h)
	{
		if(IsKeyPressed(VK_LBUTTON,3000))
		{
			return 1;
		}
		return 2;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------//
void TeksOFF(INT x, INT y, CHAR *text, LPDIRECT3DDEVICE9 pDevice)
{
	INT Check = CheckTabs(x, y, 10 + 8 * strlen(text), 10);
	DWORD ColorText = RainbowTextTest;

	DrawString( x + 13, y - 1, ColorText, text);
}
void TeksON(INT x, INT y, CHAR *text, LPDIRECT3DDEVICE9 pDevice)
{
	INT Check = CheckTabs(x, y, 10 + 8 * strlen(text), 10);
	DWORD ColorText = GREEN;

	DrawString( x + 13, y - 1, ColorText, text);
}
//-----------------------------------------------------------------------------------------//
void TextCenter(INT x, INT y, DWORD Color, CONST CHAR *fmt, ...)
{
	RECT rect = {x, y, x, y};

	CHAR buf[1024] = {0};
	va_list va_alist;

	va_start(va_alist, fmt);
	vsnprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), fmt, va_alist);
	va_end(va_alist);

	pFont->DrawText(NULL, buf, -1, &rect, DT_NOCLIP | DT_CENTER, Color);
}
//-----------------------------------------------------------------------------------------//
void RHTabButton(INT x, INT y, INT w, INT h, INT &var, CHAR *text, LPDIRECT3DDEVICE9 pDevice)
{
	INT Check = CheckTabs(x, y, w, h);
	DWORD ColorText = GREEN;
	
	if(var || Check == 0)
	ColorText = GREEN;
	else
	ColorText = RainbowTextTest;

	if(Check == 1)
	{
		Direct_MENU=0; 
		var = !var;
	}

	DrawBox(x, y, w, h + 2, 1,BLACK, GREEN, pDevice);
	TextCenter(x + (w / 2), y + (h - 14) / 2, ColorText, text);
}
//-----------------------------------------------------------------------------------------//
void RHCheckBox(FLOAT x, FLOAT y, INT &var, CHAR *text, LPDIRECT3DDEVICE9 pDevice)
{
	INT Check = CheckTabs(x, y, 15 * strlen(text), 15);
	DWORD ColorText = WHITE;

	if(Check == 0)
		ColorText = GREEN;
		else
		ColorText = RainbowTextTest;
	if(Check == 1)
		var = !var;
  	if(!var)
		TeksOFF(x + 90, y, "OFF", pDevice);
	if(var)
		TeksON(x + 90, y,"ON", pDevice);
	
	if(var==0)
	DrawBox(x+2, y+4, 5, 5, 3, NULL, RED , pDevice);
	else
	DrawBox(x+2, y+4, 5, 5, 3, NULL, GREEN , pDevice);

	DrawString( x + 13, y - 1, ColorText, text);
}
//-----------------------------------------------------------------------------------------//