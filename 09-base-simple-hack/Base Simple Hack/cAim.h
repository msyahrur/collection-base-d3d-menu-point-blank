//-----------------------------------------------------------------------------------------//
#include "cLass.h"
//-----------------------------------------------------------------------------------------//
int GetPriorityTarget()
{
	int Result = -1;
	float fMaxDistance = 5000.0f;
	D3DXVECTOR3 Head,HeadMe,HeadPos ;
	for(int iSlot = 0; iSlot < 0x16; iSlot++)
	{
		if (IsAliveDeath(iSlot))
		{
			if ( CGameContext::g_pGameContext()->setMySlotIdx() %2 != iSlot % 2 && GetUserBone( Head,7,iSlot)  )
			{
				GetUserBone(HeadMe, 7 , CGameContext::g_pGameContext()->setMySlotIdx());
				GetUserBone(HeadPos, 7 , iSlot);
				if (CalcDistance(HeadMe, HeadPos) < fMaxDistance)
				{
					fMaxDistance = CalcDistance( HeadPos,HeadMe);
					Result = iSlot;
				}
			}
		}
	}
return Result;
}
//-----------------------------------------------------------------------------------------//
float fX = 0, fY = 0, fZ = 0;
bool BulletEnable;
DWORD dwTempEcx, dwTempEbx;
_declspec(naked) void _fastcall ASMSetEnd() 
{ 	
	if (BulletEnable) 
		{ 
			_asm 
			{ 
				mov     [dwTempEcx], ecx;
				mov     [dwTempEbx], ebx;
				mov     ecx, [ebp+0x0C];
				mov     ebx, [fX];
				mov     [ecx], ebx;
				mov     ebx, [fY];
				mov     [ecx+0x04], ebx;
				mov     ebx, [fZ];
				mov     [ecx+0x08], ebx;
				mov     ecx, [dwTempEcx];
				mov     ebx, [dwTempEbx];
			} 
		} 
		_asm 
		{ 	
			mov     eax, [ebp + 0x0C]; 
			push    eax; 
			mov     ecx, [ebp - 0x0C]; 
			jmp     ResultRETpEnd; 
		} 

}
//-----------------------------------------------------------------------------------------//
bool bIsAimTargetValid = false;
void _fastcall DisableAimAssist()
{
	if(bIsAimTargetValid == true){
		SetEndVector->Disable();
		bIsAimTargetValid = false;
	}
}
//-----------------------------------------------------------------------------------------//
void _fastcall CallAimBullet(IDirect3DDevice9 *pDevice,int getBoneIndex)
{     
	int AimSlot = GetPriorityTarget();
	if(AimSlot != -1)
	{
		D3DXVECTOR3 OnWorld,OnScreen;
		if(GetUserBone(OnWorld, getBoneIndex,AimSlot))
		{
			BulletEnable = true;
			fX = OnWorld.x ;
			fY = OnWorld.y + 0.1f;
			fZ = OnWorld.z ;
			if(WorldToScreen(pDevice,OnWorld,OnScreen))
			{
				if(GetPlayerTarget(CGameContext::g_pGameContext()->setMySlotIdx()))
				{
				PrintText(OnScreen.x,OnScreen.y,RED,"Lock Target : %s",CGameContext::g_pGameContext()->getNickForSlot(AimSlot));
				Circle (OnScreen.x, OnScreen.y,6,true,RED,pDevice);
				FillRGB(OnScreen.x-10, OnScreen.y, 7, 1,RED,pDevice);
				FillRGB(OnScreen.x+4, OnScreen.y, 7, 1,RED,pDevice);
				FillRGB(OnScreen.x, OnScreen.y-10, 1, 7,RED,pDevice);
				FillRGB(OnScreen.x, OnScreen.y+4, 1, 7,RED,pDevice);
				DrawLine(512,384,OnScreen.x,OnScreen.y,1,RED);
				}else{
				PrintText(OnScreen.x,OnScreen.y,GREEN,"Lock Target : %s",CGameContext::g_pGameContext()->getNickForSlot(AimSlot));
				Circle (OnScreen.x, OnScreen.y,6,true,RainbowTextTest,pDevice);
				FillRGB(OnScreen.x-10, OnScreen.y, 7, 1,RainbowTextTest,pDevice);
				FillRGB(OnScreen.x+4, OnScreen.y, 7, 1,RainbowTextTest,pDevice);
				FillRGB(OnScreen.x, OnScreen.y-10, 1, 7,RainbowTextTest,pDevice);
				FillRGB(OnScreen.x, OnScreen.y+4, 1, 7,RainbowTextTest,pDevice);
				DrawLine(512,384,OnScreen.x,OnScreen.y,1,RainbowTextTest);
				}
			}	
		}else BulletEnable = false;
	}else BulletEnable = false;
}
//-----------------------------------------------------------------------------------------//
void _fastcall CallerAimBullet(IDirect3DDevice9 *pDevice)
{
		if(AimBullet==0&&!AimBullet){BulletEnable = false;}	
		if (AimBullet)
		{	
			FastKiller=0;
			FastBomberMan=0;
			if(AimBullet==1)
			{
				CallAimBullet(pDevice,7);
			}
			if(AimBullet==2)
			{
				CallAimBullet(pDevice,5);
			}
		}

}
//-----------------------------------------------------------------------------------------//
void _fastcall CallAutoBone()
{

	if(IsInBattle()) // OFF
		{	
	if(AutoBone){
	if(AutoBone == 1)
	{
		AimBullet = 0;
		DWORD pMyTarget = GetPlayerTarget(GetMySlotAUTOHS());
		if(pMyTarget > 0)
		{
			DWORD TargetIndex = GetTargetIndex(pMyTarget);
			D3DXVECTOR3 OnWorld;
			if(GetUserBone(OnWorld, 7, TargetIndex))
			{
				BulletEnable = true;
				fX = OnWorld.x ;
				fY = OnWorld.y + 0.1f;//di plus biar pas kepala
				fZ = OnWorld.z ;
			}else BulletEnable = false;
		}else BulletEnable = false;
	}
	if(AutoBone == 2)
	{
		AimBullet = 0;
		DWORD pMyTarget = GetPlayerTarget(GetMySlotAUTOHS());
		if(pMyTarget > 0)
		{
			DWORD TargetIndex = GetTargetIndex(pMyTarget);
			D3DXVECTOR3 OnWorld;
			if(GetUserBone(OnWorld, 5, TargetIndex))
			{
				BulletEnable = true;
				fX = OnWorld.x ;
				fY = OnWorld.y + 0.1f;//di plus biar pas kepala
				fZ = OnWorld.z ;
			}else BulletEnable = false;
		}else BulletEnable = false;
	}
	}
	}
}
//-----------------------------------------------------------------------------------------//