/*++

Copyright (c) Main Cit 96 Corporation.  All rights reserved.

Module Name:

 cWorldToMatrix.h

Abstract:

    Type definitions for the basic sized types.

Author:

Revision History:

--*/

static LPDIRECT3DDEVICE9 pDevice;
class i3RenderContext
{
public:


	const D3DXMATRIX* GetProjectMatrix(void )
	{
		return ((const D3DXMATRIX*(__thiscall*)(i3RenderContext*))((DWORD)GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetProjectMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ")))(this);
	}	
	
	const D3DXMATRIX* GetViewMatrix(void)
	{
		return ((const D3DXMATRIX*(__thiscall*)(i3RenderContext*))((DWORD)GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetViewMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ")))(this);
	}

	const D3DXMATRIX* GetWorldMatrix(void)
	{
		return ((const D3DXMATRIX*(__thiscall*)(i3RenderContext*))((DWORD)GetProcAddress(LoadLibrary("i3GfxDx.dll"), "?GetWorldMatrix@i3RenderContext@@QAEPAT_tagi3Matrix@@XZ")))(this);
	}

	static i3RenderContext* g_pRenderContext()
	{ 
		return (i3RenderContext*)(*(DWORD*)GetProcAddress(LoadLibrary("i3GfxDx.dll"),"?g_pRenderContext@@3PAVi3RenderContext@@A")); 
	}
};

bool WorldToScreen(IDirect3DDevice9 *pDevice, D3DVECTOR Player,D3DVECTOR &PlayerScaled)
{
	D3DXVECTOR3 PlayerPos(Player.x,Player.y,Player.z);
	D3DXMATRIX identity;
    D3DXVECTOR3 vScreen;
	D3DVIEWPORT9 ViewP;
	pDevice->GetViewport(&ViewP);
	ViewP.X = ViewP.Y = 0;
    ViewP.MinZ     = 0;
    ViewP.MaxZ     = 1;
	D3DXVec3Project(&vScreen, &PlayerPos, &ViewP, 
		i3RenderContext::g_pRenderContext()->GetProjectMatrix(),
		i3RenderContext::g_pRenderContext()->GetViewMatrix(),
		i3RenderContext::g_pRenderContext()->GetWorldMatrix());
  
 if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < ViewP.Width && vScreen.y < ViewP.Height)
 {
     PlayerScaled.x = vScreen.x;
     PlayerScaled.y = vScreen.y ;
     PlayerScaled.z = vScreen.z;

  return true; 
 }
 return false;
}