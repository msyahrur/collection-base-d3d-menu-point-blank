//CREATED BY SC0D3 Solusi Game No Di Indoneisa
bool GetUserBone(D3DXVECTOR3 &Out,int BoneIndex, int CharaIndex)
{
	if( pGameCharaManager->getCharaByNetIdx(CharaIndex) && 
		pGameCharaManager->getCharaByNetIdx(CharaIndex)->getGameCharaBoneContext())
	{
		Out = pGameCharaManager->getCharaByNetIdx(CharaIndex)->getGameCharaBoneContext()->getBonePosition(BoneIndex);
		return true;
	}
	return false;
}

typedef void (__thiscall * ti3CollideeLine_Initialize)(i3CollideeLine* pLine);
ti3CollideeLine_Initialize i3CollideeLine_Initialize;
typedef void (__thiscall * ti3CollideeLine_SetStart)(i3CollideeLine* pLine, D3DXVECTOR3 *Value);
ti3CollideeLine_SetStart i3CollideeLine_SetStart;
typedef void (__thiscall * ti3CollideeLine_SetEnd)(i3CollideeLine* pLine, D3DXVECTOR3 *Value);
ti3CollideeLine_SetEnd i3CollideeLine_SetEnd;

void InitializeVisibleCheck()
{
	static bool bInitViscek = false;
	if(bInitViscek) return;
	HMODULE hScene = GetModuleHandle("i3SceneDx.dll");
	while(!hScene)Sleep(50);
	i3CollideeLine_Initialize = (ti3CollideeLine_Initialize)(DWORD)GetProcAddress(hScene,"??0i3CollideeLine@@QAE@XZ"); 
	i3CollideeLine_SetStart = (ti3CollideeLine_SetStart)(DWORD)GetProcAddress(hScene,"?SetStart@i3CollideeLine@@QAEXPATVEC3D@@@Z");
	i3CollideeLine_SetEnd = (ti3CollideeLine_SetEnd)(DWORD)GetProcAddress(hScene,"?SetEnd@i3CollideeLine@@QAEXPATVEC3D@@@Z");
	bInitViscek = true;
}

bool GetPlayerVisibleStatus(int ActorIndex, int TargetIndex, int BoneTargetIndex)
{
	if(bEnableVisibleCheck == false) return true;
	i3CollideeLine Line;
	D3DXVECTOR3 vTarget, vLocal;

	GetUserBone(vLocal,5,ActorIndex);
	GetUserBone(vTarget,BoneTargetIndex,TargetIndex);

	vLocal.y += 0.1f;

	i3CollideeLine_Initialize(&Line);
	i3CollideeLine_SetStart(&Line,&vLocal);
	i3CollideeLine_SetEnd(&Line,&vTarget);

	i3PhysixResult* pResult = pGameFramework->RaycastClosest(&Line,NULL);
	if(!pResult)return false;

	return(pResult->GetDistanceResult() >= DistanceBetweenVector(vTarget,vLocal));
}

void _fastcall DrawString(int x, int y, DWORD color, const char *fmt, ...)
{
	RECT FontPos = { x, y, x + 30, y + 20 };
	char buf[1024] = {'\0'};
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	
	pFont->DrawText(0, buf, -1, &FontPos, DT_NOCLIP, color);
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

void DrawTransparentBox(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{  
    g_pLine->SetWidth(h); 
    g_pLine->SetAntialias(0); 

    D3DXVECTOR2 VertexList[2]; 
    VertexList[0].x = x; 
    VertexList[0].y = y + (h >> 1); 
    VertexList[1].x = x + w; 
    VertexList[1].y = y + (h >> 1); 

    g_pLine->Begin(); 
    g_pLine->Draw(VertexList, 2, Color);
    g_pLine->End();
}

void DrawLineColor( long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, DWORD Color)
{	
	D3DXVECTOR2 vLine[ 2 ];
	g_pLine->SetAntialias( true ); 

	g_pLine->SetWidth( dwWidth ); 
	g_pLine->Begin();

		vLine[ 0 ][ 0 ] = Xa; 
		vLine[ 0 ][ 1 ] = Ya;
		vLine[ 1 ][ 0 ] = Xb;
		vLine[ 1 ][ 1 ] = Yb;

	g_pLine->Draw( vLine, 2, Color ); 
	g_pLine->End(); 
}

void DrawBone(int CharaIndex, int BoneIndexStart, int BoneIndexEnd, DWORD Color)
{
	D3DXVECTOR3 OnWorldA,OnScreenA;
	D3DXVECTOR3 OnWorldB,OnScreenB;
	if(GetUserBone(OnWorldA,BoneIndexStart,CharaIndex) && pRenderContext->WorldToScreen(OnWorldA,OnScreenA,npDevice) && GetUserBone(OnWorldB,BoneIndexEnd,CharaIndex) && pRenderContext->WorldToScreen(OnWorldB,OnScreenB,npDevice))
	{
		DrawLineColor(OnScreenA.x,OnScreenA.y,OnScreenB.x,OnScreenB.y,1,Color);
	}
}

void CallEspBone(int Index, DWORD Color)
{
	DrawBone(Index,7,6,Color);//Kepala - leher
	DrawBone(Index,6,5,Color);// Leher - Dada
	DrawBone(Index,5,4,Color);// Dada - perut
	DrawBone(Index,4,2,Color);// Perut - pantat
	DrawBone(Index,2,0,Color);// Perut - root
	DrawBone(Index,6,11,Color);//Tangan kanan
	DrawBone(Index,6,10,Color);//tangan kiri
	DrawBone(Index,0,13,Color);//Paha kanan
	DrawBone(Index,0,12,Color);//Paha kiri
	DrawBone(Index,13,15,Color);//Lutut kiri
	DrawBone(Index,12,14,Color);//Lutut kanan
	DrawBone(Index,15,9,Color);//telapak kaki kiri
	DrawBone(Index,14,8,Color);//telapak kaki kanan
}

void DrawStringC(LPD3DXFONT g_pFont, long x, long y, float Health, char *text, ...)
{
	DWORD Color = Green;
	if(Health < 90)Color = Yellow;
	if(Health < 80)Color = Orange;
	if(Health < 40)Color = Red;
	if(Health > 120)Color = 120;
	D3DCOLOR BordColor = Black;
    RECT rct;
    rct.left     = x - 1;
    rct.right    = x + 1;
    rct.top      = y - 1 ;
    rct.bottom    = y + 1;
    if(!text) { return; }
    va_list va_alist;
    char logbuf[1000] = {0};
    va_start (va_alist, text);
    _vsnprintf(logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), text, va_alist);
    va_end (va_alist);
    RECT FontRect = { x, y, x, y };
    g_pFont->DrawTextA(NULL, logbuf, -1, &rct, DT_NOCLIP + DT_CENTER, Color);
}

void DrawESPLine(long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, float Health, LPDIRECT3DDEVICE9 pDevice)
{
	DWORD Color = Green;
	if(Health < 90)Color = Yellow;
	if(Health < 80)Color = Orange;
	if(Health < 40)Color = Red;
	if(Health > 120)Color = 120;
	D3DXVECTOR2 vLine[ 2 ];
	g_pLine->SetAntialias( true );

	g_pLine->SetWidth( (float)dwWidth );
	g_pLine->Begin();

	vLine[ 0 ][ 0 ] = (float)Xa;
	vLine[ 0 ][ 1 ] = (float)Ya;
	vLine[ 1 ][ 0 ] = (float)Xb;
	vLine[ 1 ][ 1 ] = (float)Yb;

	g_pLine->Draw( vLine, 2, Color );
	g_pLine->End();
}

void HealthBarnew(float x, float y, float Health, LPDIRECT3DDEVICE9 pDevice)
{
	DWORD HPcol = Green;
	if(Health < 90)HPcol = Yellow;
	if(Health < 80)HPcol = Orange;
	if(Health < 40)HPcol = Red;
	if(Health > 120)Health = 120;
	DrawBorder(x-1,y-1,52,5,1,Black,pDevice );
	FillRGB(x,y,Health/2,3,HPcol,pDevice );
}

void HealthEqui(int x, int y, float Health, LPDIRECT3DDEVICE9 pDevice)
{
	const D3DCOLOR colours[] = { Red, Red, Red, Red, Orange, Orange, Orange, Orange, Yellow, Yellow, Yellow, Yellow, Green, Green, Green, Green, Green, Green, Blue, Blue };
	int boxSizeX = 2;
	int boxSizeY = 7;
	int boxGap = 1;

for ( int i = 0 ; i < 20; i++ )
	{
		if ( Health > ( 5 * i ) )
	DrawBorder(x-1,y-1,62,9,1,colours[i],pDevice );		
	}

for ( int i = 0 ; i < 20; i++ )
	{
		if ( Health > ( 5 * i ) )
			FillRGB(x,y, boxSizeX, boxSizeY,colours[i],pDevice);
		else
            FillRGB(x,y, boxSizeX, boxSizeY,Grey,pDevice);
		x = x + boxSizeX+ boxGap;
	}
}

void HealthEqui2(int x, int y, float Health, LPDIRECT3DDEVICE9 pDevice)
{
const int SizeY[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
const D3DCOLOR colours[] = { Red, Red, Red, Red, Orange, Orange, Orange, Orange, Yellow, Yellow, Yellow, Yellow, Green, Green, Green, Green, Green, Green, Blue, Blue };
int boxSizeX = 2;
	int boxSizeY = 6;
	int boxGap = 1;
for ( int i = 0 ; i < 20; i++ )
	{
		if ( Health > ( 5 * i ) )
			FillRGB(x,y, boxSizeX, SizeY[i],colours[i],pDevice);
		else
            FillRGB(x,y, boxSizeX, SizeY[i],D3DCOLOR_ARGB(255,128,128,128),pDevice);
		x = x + boxSizeX+ boxGap;
	}
}

void _fastcall DrawKD(int x, int y, DWORD color, const char *fmt, ...)
{
	RECT FontPos = { x, y, x + 30, y + 20 };
	char buf[1024] = {'\0'};
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	
	g_pFont->DrawText(0, buf, -1, &FontPos, DT_NOCLIP, color);
}

void _fastcall PingServer(int x, int y, float Health, IDirect3DDevice9* pDevice)
{
	if( !pDevice )
		return;
	for (int index = 0; index <= (Health-1); index++)
	{
	D3DCOLOR HPcol = Green;
	if(Health == 3)HPcol = Orange;
	if(Health == 2)HPcol = Orange;
	if(Health == 1)HPcol = Red;
	FillRGB(x + (index*4),y,3,14,HPcol,pDevice);
	}
}

void Crosshair(LPDIRECT3DDEVICE9 pDevice, D3DVIEWPORT9 pViewPort, D3DCOLOR Color)
{
	pDevice->GetViewport(&pViewPort);
	D3DRECT RectA, RectB;
	RectA.x1 = (pViewPort.Width/2)-6;
	RectA.x2 = (pViewPort.Width/2)+6;
	RectA.y1 = (pViewPort.Height/2);
	RectA.y2 = (pViewPort.Height/2)+1;
	RectB.x1 = (pViewPort.Width/2);
	RectB.x2 = (pViewPort.Width/2)+1;
	RectB.y1 = (pViewPort.Height/2)-6;
	RectB.y2 = (pViewPort.Height/2)+6;
	pDevice->Clear(1, &RectA, D3DCLEAR_TARGET, Color, 0,  0);
	pDevice->Clear(1, &RectB, D3DCLEAR_TARGET, Color, 0,  0);
}