int X_WM,Y_WM;
bool IsMinimized = false;
bool MinZ = false;
bool OnWM = false;
#define WindowName "Point Blank"
void _fastcall CallerWMode(){
	HWND Minimize = FindWindowA(NULL,WindowName);
//================================Verifikasi tanggal===================================================
		
if(WM_Resolution == 0)
{
	X_WM = 700;
	Y_WM = 600;
OnWM = false;
	}
if(WM_Resolution == 1)
{
	X_WM = 800;
	Y_WM = 600;
OnWM = false;
}
if(WM_Resolution == 2)
{
	X_WM = 1024;
	Y_WM = 650;
OnWM = false;
}
if(WM_Resolution == 3)
{
	X_WM = 1300;
	Y_WM = 700;
OnWM = false;
}

if(GetAsyncKeyState(VK_F12)&1)
{
	
	ShowWindow(Minimize,SW_MINIMIZE);
}
if(TheMNZ)
{
	
	ShowWindow(Minimize,SW_MINIMIZE);
	TheMNZ = 0;
}
if(WndMode == 0)
{
	if(OnWM == true){
SetWindowLong(Minimize, GWL_STYLE, WS_POPUP|WS_SYSMENU|WS_VISIBLE);
SetWindowPos(Minimize, HWND_TOPMOST, 0, 0, GetSystemMetrics(0), GetSystemMetrics(1), SWP_SHOWWINDOW);
OnWM = false;
}
}
if(WndMode == 1)
{
X_WM = 1024;
Y_WM = 700;
	if(OnWM == false){

SetWindowLongA(Minimize, GWL_STYLE,WS_POPUP | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE | WS_MAXIMIZEBOX);
SetWindowPos(Minimize, HWND_TOP,(GetSystemMetrics(0)/2) - (X_WM / 2),(GetSystemMetrics(1)/2) - (Y_WM / 2),X_WM,Y_WM,SWP_FRAMECHANGED | SWP_SHOWWINDOW);
OnWM = true;
}
}

}