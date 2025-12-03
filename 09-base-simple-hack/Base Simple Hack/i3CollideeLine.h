class i3CollideeLine
{
public:

	const D3DXMATRIX* GetProjectMatrix(void )
	{
		return ((const D3DXMATRIX*(__thiscall*)(i3CollideeLine*))((DWORD)GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetProjectMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ")))(this);
	}	
	
	const D3DXMATRIX* GetViewMatrix(void)
	{
		return ((const D3DXMATRIX*(__thiscall*)(i3CollideeLine*))((DWORD)GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetViewMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ")))(this);
	}

	const D3DXMATRIX* GetWorldMatrix(void)
	{
		return ((const D3DXMATRIX*(__thiscall*)(i3CollideeLine*))((DWORD)GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetWorldMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ")))(this);
	}


	static i3RenderContext* g_pRenderContext()
	{ 
		return (i3CollideeLine*)(*(DWORD*)GetProcAddress(LoadLibrary("i3GfxDx.dll"),"?g_pRenderContext@@3PAVi3RenderContext@@A")); 
	}

	static i3CollideeLine*CollideeLine(i3CollideeLine* pLine)
	{
		typedef i3CollideeLine* (__thiscall * tgeti3CollideeLine)(i3CollideeLine*);
		tgeti3CollideeLine geti3CollideeLine = (tgeti3CollideeLine)((DWORD)GetProcAddress(LoadLibrary("i3SceneDx.dll"),"??0i3CollideeLine@@QAE@XZ"));
		return (i3CollideeLine*)(&i3CollideeLine(),pLine);
	}
};