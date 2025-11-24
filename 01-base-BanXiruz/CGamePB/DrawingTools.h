//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
void DrawLineColor(long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, DWORD Color)
{	
	D3DXVECTOR2 vLine[ 2 ];
	g_pLine->SetAntialias(true);
	g_pLine->SetWidth(dwWidth);
	g_pLine->Begin();

		vLine[ 0 ][ 0 ] = Xa;
		vLine[ 0 ][ 1 ] = Ya;
		vLine[ 1 ][ 0 ] = Xb;
		vLine[ 1 ][ 1 ] = Yb;

	g_pLine->Draw(vLine, 2, Color);
	g_pLine->End();
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

void HealthBar(float x, float y, float Health, LPDIRECT3DDEVICE9 pDevice)
{
	DWORD HPcol = GREEN;
	if(Health < 85)HPcol = YELLOW;
	if(Health < 50)HPcol = ORANGE;
	if(Health < 25)HPcol = RED;
	if(Health > 100)Health = 100;
	DrawBorder(x-1,y-1,52,5,1,BLACK,pDevice );
	FillRGB(x,y,Health/2,3,HPcol,pDevice );
}

void DrawESPLine(long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, float Health, LPDIRECT3DDEVICE9 pDevice)
{
	DWORD HPcol = GREEN;
	if(Health < 85)HPcol = YELLOW;
	if(Health < 50)HPcol = ORANGE;
	if(Health < 25)HPcol = RED;
	if(Health > 100)Health = 100;
	D3DXVECTOR2 vLine[ 2 ];
	g_pLine->SetAntialias( true );

	g_pLine->SetWidth( (float)dwWidth );
	g_pLine->Begin();

	vLine[ 0 ][ 0 ] = (float)Xa;
	vLine[ 0 ][ 1 ] = (float)Ya;
	vLine[ 1 ][ 0 ] = (float)Xb;
	vLine[ 1 ][ 1 ] = (float)Yb;

	g_pLine->Draw(vLine, 2, HPcol);
	g_pLine->End();
}