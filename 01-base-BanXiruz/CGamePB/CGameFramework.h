//Created by Refaldy Muhammad | CEO. Cheat Purworejo | Date Relase : March 17, 2018 | Website : www.citpurworejo.com
class i3PhysixResult
{
public:
	float GetDistanceResult()
	{
		typedef float (__thiscall * tReadData)(DWORD BaseData);
		tReadData ReadData = (tReadData)(AddyEngine->GetAddyValueByKey("PhysixResult.Function.ReadData"));
		return ReadData((DWORD)this + AddyEngine->GetAddyValueByKey("PhysixResult.Pointer.Distance"));
	}
};

class i3InputMouse
{
public:
	DWORD GetButtonState()
	{
		typedef DWORD (__thiscall * tGetButtonState)(i3InputMouse* Base);
		tGetButtonState GetButtonState = (tGetButtonState)(AddyEngine->GetAddyValueByKey("i3InputMouse.Function.GetButtonState"));
		return GetButtonState(this);
	}
};

class CGameFramework
{
public:
	i3PhysixResult* RaycastClosest(i3CollideeLine* pLine, DWORD dwOption){
		typedef i3PhysixResult* (__thiscall * tRaycastClosest)(CGameFramework* Base, i3CollideeLine* pLine, DWORD dwOption);
		tRaycastClosest RaycastClosest = (tRaycastClosest)(AddyEngine->GetAddyValueByKey("GameFramework.Function.RaycastClosest"));
		return RaycastClosest(this, pLine, dwOption);
	}
	i3InputMouse* geti3InputMouse(void)
	{
		return (i3InputMouse*)*(DWORD*)(this + AddyEngine->GetAddyValueByKey("GameFramework.Pointer.I3InputMouse"));
	}
	void SetNightVisionEnable(int N) 
	{ 
		__try
		{
			return ((void(__thiscall*)(CGameFramework*, int))ResultSetNightVisionEnable)(this, N);
		}__except (EXCEPTION_EXECUTE_HANDLER){}
	}
}; CGameFramework* pGameFramework = NULL;