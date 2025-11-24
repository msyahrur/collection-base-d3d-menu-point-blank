//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
class i3CollideeLine
{
public:
	char _pad1[0x7C];
	D3DXVECTOR3 vStart;
	D3DXVECTOR3 vEnd;
	D3DXVECTOR3 vDir;
};

class CRenderContext
{
public:
	D3DXMATRIX* GetProjectMatrix(void)
	{
		typedef D3DXMATRIX* (__thiscall * tGetProjectMatrix)(CRenderContext* Base);
		tGetProjectMatrix GetProjectMatrix = (tGetProjectMatrix)(AddyEngine->GetAddyValueByKey("RenderContext.Function.GetProjectMatrix"));
		return GetProjectMatrix(this);
	}
	D3DXMATRIX* GetViewMatrix(void)
	{
		typedef D3DXMATRIX* (__thiscall * tGetViewMatrix)(CRenderContext* Base);
		tGetViewMatrix GetViewMatrix = (tGetViewMatrix)(AddyEngine->GetAddyValueByKey("RenderContext.Function.GetViewMatrix"));
		return GetViewMatrix(this);
	}
	D3DXMATRIX* GetWorldMatrix(void)
	{
		typedef D3DXMATRIX* (__thiscall * tGetWorldMatrix)(CRenderContext* Base);
		tGetWorldMatrix GetWorldMatrix = (tGetWorldMatrix)(AddyEngine->GetAddyValueByKey("RenderContext.Function.GetWorldMatrix"));
		return GetWorldMatrix(this);
	}
	bool WorldToScreen(D3DXVECTOR3 PlayerPos,D3DXVECTOR3 &Output,LPDIRECT3DDEVICE9 pDevice)
	{
		D3DXVECTOR3 vScreen;
		pDevice->GetViewport(&g_ViewPort);
		g_ViewPort.X = g_ViewPort.Y = 0;
		g_ViewPort.MinZ = 0;
		g_ViewPort.MaxZ = 1;
		D3DXVec3Project(&vScreen, &PlayerPos, &g_ViewPort, this->GetProjectMatrix(), this->GetViewMatrix(), this->GetWorldMatrix());

		if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < g_ViewPort.Width && vScreen.y < g_ViewPort.Height)
		{
			Output.x = vScreen.x;
			Output.y = vScreen.y;
			Output.z = vScreen.z;
			return true; 
		}
		return false;
	}
}; CRenderContext* pRenderContext = NULL;