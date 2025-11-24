//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
bool GetUserBone(D3DXVECTOR3 &Out,int BoneIndex, int CharaIndex)
{
	if(pGameCharaManager->getCharaByNetIdx(CharaIndex) &&
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

void DrawBone(int CharaIndex, int BoneIndexStart, int BoneIndexEnd, DWORD Color)
{
	D3DXVECTOR3 OnWorldA,OnScreenA;
	D3DXVECTOR3 OnWorldB,OnScreenB;
	if(GetUserBone(OnWorldA,BoneIndexStart,CharaIndex) && pRenderContext->WorldToScreen(OnWorldA,OnScreenA,npDevice) && GetUserBone(OnWorldB,BoneIndexEnd,CharaIndex) && pRenderContext->WorldToScreen(OnWorldB,OnScreenB,npDevice))
	{
		DrawLineColor(OnScreenA.x,OnScreenA.y,OnScreenB.x,OnScreenB.y,1,Color);
	}
}

void DrawPlayerBone(int Index, float Health, LPDIRECT3DDEVICE9 pDevice)
{
	DWORD HPcol = GREEN;
	if(Health < 85)HPcol = YELLOW;
	if(Health < 50)HPcol = ORANGE;
	if(Health < 25)HPcol = RED;
	if(Health > 100)Health = 100;
	DrawBone(Index, 7, 6, HPcol);
	DrawBone(Index, 6, 5, HPcol);
	DrawBone(Index, 5, 4, HPcol);
	DrawBone(Index, 4, 2, HPcol);
	DrawBone(Index, 2, 0, HPcol);
	DrawBone(Index, 6, 11, HPcol);
	DrawBone(Index, 6, 10, HPcol);
	DrawBone(Index, 0, 13, HPcol);
	DrawBone(Index, 0, 12, HPcol);
	DrawBone(Index, 13, 15, HPcol);
	DrawBone(Index, 12, 14, HPcol);
	DrawBone(Index, 15, 9, HPcol);
	DrawBone(Index, 14, 8, HPcol);
}

void DrawCrossHair(LPDIRECT3DDEVICE9 pDevice)
{
	int ScreenCenterX = (GetSystemMetrics(0)/2);
	int ScreenCenterY = (GetSystemMetrics(1)/2);
	
	D3DCOLOR redt2 = D3DCOLOR_XRGB( 0, 0, 255 ); // Biru
	D3DRECT rec3 = {ScreenCenterX-15, ScreenCenterY, ScreenCenterX+15, ScreenCenterY+1};
	D3DRECT rec4 = {ScreenCenterX, ScreenCenterY-15, ScreenCenterX+1, ScreenCenterY+15};
	pDevice->Clear(1, &rec3, D3DCLEAR_TARGET,redt2, 0, 0);
	pDevice->Clear(1, &rec4, D3DCLEAR_TARGET,redt2, 0, 0);
	
	D3DCOLOR redt3 = D3DCOLOR_XRGB( 0, 255, 255); //Cyan
	D3DRECT rec5 = {ScreenCenterX-11, ScreenCenterY, ScreenCenterX+11, ScreenCenterY+1};
	D3DRECT rec6 = {ScreenCenterX, ScreenCenterY-11, ScreenCenterX+1, ScreenCenterY+11};
	pDevice->Clear(1, &rec5, D3DCLEAR_TARGET,redt3, 0, 0);
	pDevice->Clear(1, &rec6, D3DCLEAR_TARGET,redt3, 0, 0);

	D3DCOLOR redt4 = D3DCOLOR_XRGB( 0, 255, 0 ); //Hijau
	D3DRECT rec7 = {ScreenCenterX-9, ScreenCenterY, ScreenCenterX+9, ScreenCenterY+1};
	D3DRECT rec8 = {ScreenCenterX, ScreenCenterY-9, ScreenCenterX+1, ScreenCenterY+9};
	pDevice->Clear(1, &rec7, D3DCLEAR_TARGET,redt4, 0, 0);
	pDevice->Clear(1, &rec8, D3DCLEAR_TARGET,redt4, 0, 0);

	D3DCOLOR redt5 = D3DCOLOR_XRGB( 255, 255, 0 ); //Kuning
	D3DRECT rec9 = {ScreenCenterX-7, ScreenCenterY, ScreenCenterX+7, ScreenCenterY+1};
	D3DRECT rec10 = {ScreenCenterX, ScreenCenterY-7, ScreenCenterX+1, ScreenCenterY+7};
	pDevice->Clear(1, &rec9, D3DCLEAR_TARGET,redt5, 0, 0);
	pDevice->Clear(1, &rec10, D3DCLEAR_TARGET,redt5, 0, 0);

	D3DCOLOR redt6 = D3DCOLOR_XRGB( 255, 165, 0 ); //Oranye
	D3DRECT rec11 = {ScreenCenterX-5, ScreenCenterY, ScreenCenterX+5, ScreenCenterY+1};
	D3DRECT rec12 = {ScreenCenterX, ScreenCenterY-5, ScreenCenterX+1, ScreenCenterY+5};
	pDevice->Clear(1, &rec11, D3DCLEAR_TARGET,redt6, 0, 0);
	pDevice->Clear(1, &rec12, D3DCLEAR_TARGET,redt6, 0, 0);

	D3DCOLOR redt7 = D3DCOLOR_XRGB( 255, 0, 0 ); //Merah
	D3DRECT rec13 = {ScreenCenterX-3, ScreenCenterY, ScreenCenterX+3, ScreenCenterY+1};
	D3DRECT rec14 = {ScreenCenterX, ScreenCenterY-3, ScreenCenterX+1, ScreenCenterY+3};
	pDevice->Clear(1, &rec13, D3DCLEAR_TARGET,redt7, 0, 0);
	pDevice->Clear(1, &rec14, D3DCLEAR_TARGET,redt7, 0, 0);
}

void iDrawString(int x, int y, D3DCOLOR dwColour, DWORD Flag, LPD3DXFONT Font, const char* text, ...)
{
	D3DCOLOR colour = dwColour;

	RECT rct;
	rct.left     = x - 1;   
	rct.right    = x + 1;   
	rct.top      = y - 1 ;   
	rct.bottom   = y + 1;

	va_list va_alist;
	char logbuf[256] = {0};
	va_start(va_alist, text);
	_vsnprintf(logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), text, va_alist);
	va_end(va_alist);

	textSprite->Begin(D3DXSPRITE_ALPHABLEND);
	Font->DrawText(textSprite, logbuf, -1, &rct, Flag|DT_NOCLIP, colour);
	textSprite->End();	
}

void DrawOutlineString(int x, int y, D3DCOLOR dwColour, DWORD Flag, LPD3DXFONT Font, const char* text, ...)
{
	iDrawString(x, y, dwColour, DT_NOCLIP | DT_CENTER, mFont, text);
	iDrawString(x-1, y, 0xFF000000, DT_NOCLIP | DT_CENTER, mFont, text);
	iDrawString(x+1, y, 0xFF000000, DT_NOCLIP | DT_CENTER, mFont, text);
	iDrawString(x, y-1, 0xFF000000, DT_NOCLIP | DT_CENTER, mFont, text);
	iDrawString(x, y+1, 0xFF000000, DT_NOCLIP | DT_CENTER, mFont, text);
	iDrawString(x, y, dwColour, DT_NOCLIP | DT_CENTER, mFont, text);
}

void DrawStringC(LPD3DXFONT g_pFont, long x, long y, float Health, char *text, ...)
{
	DWORD HPcol = GREEN;
	if(Health < 85)HPcol = YELLOW;
	if(Health < 50)HPcol = ORANGE;
	if(Health < 25)HPcol = RED;
	if(Health > 100)Health = 100;
	D3DCOLOR BordColor = BLACK;
    RECT rct;
    rct.left     = x - 1;
    rct.right    = x + 1;
    rct.top      = y - 1 ;
    rct.bottom   = y + 1;
    if(!text){return;}
    va_list va_alist;
    char logbuf[1000] = {0};
    va_start (va_alist, text);
    _vsnprintf(logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), text, va_alist);
    va_end (va_alist);
    RECT FontRect = {x, y, x, y};
    g_pFont->DrawTextA(NULL, logbuf, -1, &rct, DT_NOCLIP + DT_CENTER, HPcol);
}