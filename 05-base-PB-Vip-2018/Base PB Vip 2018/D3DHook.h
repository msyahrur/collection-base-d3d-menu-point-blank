//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//--        // Created By : MhmmdYogiSaputra                                                               --  
//--        // Facebook   : https://www.facebook.com/gigntng                                               --
//--        // Youtube    : https://www.youtube.com/channel/UCoCztOogokhBSJoAFWiW1yA                       --
//--       // Website    : http://www.pintercit.me/                                                        --
//--                                                                                                       --
//--        // CopyRight 2018  ( Woy Ngentod Jangan Di Ganti CopyRight Dan Created Hargain Anjing Kontol ) --
//--                                                                                                       -- 
//------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
DWORD pEndScene;
DWORD pDrawIndexedPrimitive;
#define StartRoutine(Function) CreateThread(0,0,(LPTHREAD_START_ROUTINE)Function,0,0,0);

int cInit = 0;
_declspec(naked)void hkEndRender()
{
	__asm {
		mov eax,[ecx+0x53A8]
		mov ecx,[eax]
		mov edx,[ecx+0xA8]
		mov [pEndScene],edx
		cmp [cInit],0
		je InitES
		cmp [cInit],1
		je Normal
		cmp [cInit],2
		je ReInitES
InitES:
        push eax
		call hkEndScene
		mov [cInit],1
		retn
Normal:
        push eax
        call edx
		mov [cInit],2
		retn
ReInitES:
		push eax
		call hkEndScene
        retn           

	}
}

DWORD m_pCaps, SelectShader = 0;
class i3Shader
{
public:
};

class i3RenderContext_DIP;
class i3Vertex;
class i3DrawPrimSize;
class m_pCaps;
class i3RenderContext_DIP
{
public:
char _0x0000[20]; //0x0000 
	DWORD DrawCount; //0x0014 
char _0x0018[224];
	DWORD DrawPrimCount; //0x00F8 
char _0x00FC[100];
	BYTE VertexCount; //0x0160 
char _0x0161[1987];
	i3Vertex* Vertex; //0x0924 
char _0x0928[448];
	i3Shader* Shader; //0x0AE8 
char _0x0AEC[18620];
	LPDIRECT3DDEVICE9 pDevice; //0x53A8 
char _0x53AC[168];
	DWORD DrawSize; //0x5454 
char _0x5458[4];
	i3DrawPrimSize* DrawPrimitiveSize; //0x545C 
char _0x5460[8];
	DWORD dwSize; //0x5468 
	DWORD isReady; //0x546C 
};//Size=0x5DEC

class i3Vertex
{
public:
char _0x0000[368];
	DWORD NumVertices; //0x0170 

};//Size=0x0174

class i3DrawPrimSize
{
public:
char _0x0000[392];
	DWORD Count; //0x0188 
char _0x018C[84];
	LPDIRECT3DVERTEXBUFFER9 VertexBufferData; //0x01E0 

};

class cCaps
{
public:
char _0x0000[336];
	DWORD ShaderMode; //0x0150 

};//Size=0x0184

typedef void (__thiscall* tSelectShader)(void *p, i3Shader* , int);
tSelectShader oSelectShader;

/*
i3Shader *Shader = 0x240
StartIdx = 0x248
PrimCount = 0x24C
*/

i3Shader* __fastcall myDrawIndexedPrim(void *p, void *Unknown, i3Shader *Shader, D3DPRIMITIVETYPE I3G_PRIMITIVE, unsigned int startIdx, unsigned int primCount)
{
	oSelectShader = (tSelectShader)SelectShader;
	i3RenderContext_DIP* pRC = (i3RenderContext_DIP*)(p);
	
	pRC->DrawPrimCount += primCount;
	pRC->DrawCount++;

	cCaps* pCaps = (cCaps*)(*(DWORD*)(m_pCaps));
	if(pCaps->ShaderMode > 0)
	{
		oSelectShader(p, Shader, 0);
	}
	if(pRC->VertexCount > 0 && pRC->isReady == 1)
	{
		DWORD dwOffset = pRC->dwSize * pRC->DrawPrimitiveSize->Count;
		if(pRC->DrawSize > 0){
			for(unsigned i = 0; i < pRC->DrawSize; i++)
			{
				pRC->pDevice->SetStreamSource(1, pRC->DrawPrimitiveSize->VertexBufferData, dwOffset, 0);
				hkDrawIndexedPrimitive(pRC->pDevice, I3G_PRIMITIVE, 0, 0, pRC->Vertex->NumVertices, startIdx, primCount);
				dwOffset += pRC->DrawPrimitiveSize->Count;
			}
		}
	}
	else {
		hkDrawIndexedPrimitive(pRC->pDevice, I3G_PRIMITIVE, 0, 0, pRC->Vertex->NumVertices, startIdx, primCount);
	}
	return pRC->Shader;
}

typedef int (__thiscall* tResetDevice)(void *p);
tResetDevice oResetDevice;
int __fastcall hkResetDevice(void *p, void *Unknown)
{
	
	ResetDevice();
	return oResetDevice(p);
}

void HookResetDevice()
{
	HMODULE hGfxDx	  = LoadLibraryA			 (/*i3GfxDx.dll*/XorStr<0x9B,12,0x3A6562DC>("\xF2\xAF\xDA\xF8\xE7\xE4\xD9\x8C\xC7\xC8\xC9"+0x3A6562DC).s);
	oResetDevice = (tResetDevice)DetourB8((DWORD)(GetProcAddress(hGfxDx, "?ResetDevice@i3RenderContext@@QAEHXZ")),(DWORD)hkResetDevice, 7);
}

DWORD xMakePTR(BYTE *MemoryTarget, DWORD FunctionTarget)
{
	DWORD dwOldProtect,dwBkup;
	DWORD dwRetn = *(DWORD*)(MemoryTarget);

	VirtualProtect(MemoryTarget, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*((DWORD *)(MemoryTarget)) = FunctionTarget;
	VirtualProtect(MemoryTarget, 4, dwOldProtect, &dwBkup);
	return dwRetn;
}

DWORD GetOriginalEndScene()
{
	return pEndScene;
}
DWORD GetOriginalDIP()
{
	return pDrawIndexedPrimitive;
}

IDirect3D9 * HookDirect3DCreate9(VOID)
{
    DWORD Base = (DWORD)LoadLibraryW(L"d3d9.dll");
 
    for(DWORD i = 0; i < 0x128000; i++ )
    {
      if ( (*(BYTE *)(Base+i+0x00))==0xC7
        && (*(BYTE *)(Base+i+0x01))==0x06
        && (*(BYTE *)(Base+i+0x06))==0x89
        && (*(BYTE *)(Base+i+0x07))==0x86
        && (*(BYTE *)(Base+i+0x0C))==0x89
        && (*(BYTE *)(Base+i+0x0D))==0x86 )
        return (IDirect3D9*)(Base + i + 2);
    }
    return NULL;
}

IDirect3D9 *pD3D;
void __fastcall ThreadHookX()
{
	while(!pD3D){
		pD3D = HookDirect3DCreate9();
	}
	DWORD *VD3D				= (DWORD*)pD3D;
	VD3D					= (DWORD*)VD3D[0];
	oEndScene				= (tEndScene)				DetourFunction((PBYTE)VD3D[42], (PBYTE)hkEndScene				,5);
	oReset					= (tReset)					DetourFunction((PBYTE)VD3D[16], (PBYTE)hkReset					,5);
	Sleep(10);
}

//INT ThreadX()
//{
//    DWORD D3D9 = NULL;
//    DWORD Address;
//    DWORD* vTable;
//    while( D3D9 == NULL )
//    {
//        D3D9 = ( DWORD ) GetModuleHandle( "d3d9.dll" );
//    }
//    Address = _DDFramework->FindPattern( D3D9, 0x128000, ( BYTE* ) "\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
//    memcpy( &vTable, ( void* ) ( Address + 2 ), 4 );
//	oDrawIndexedPrimitive = ( tDrawIndexedPrimitive ) DetourFunction( ( PBYTE ) vTable[ 82 ], ( PBYTE ) hkEndScene , 5);
//    oEndScene = ( tEndScene ) DetourFunction( ( PBYTE ) vTable[ 42 ], ( PBYTE ) hkEndScene , 5);
//    return 0;
//}

void ThreadHook()
{
	DWORD dwFramework = (DWORD)GetModuleHandleA(/*i3FrameWorkDx.dll*/XorStr<0x22,18,0x41CBDFF2>("\x4B\x10\x62\x57\x47\x4A\x4D\x7E\x45\x59\x47\x69\x56\x01\x54\x5D\x5E"+0x41CBDFF2).s);
	DWORD dwScene	  = (DWORD)GetModuleHandleA(/*i3SceneDx.dll*/XorStr<0xAA,14,0x8DADBF8C>("\xC3\x98\xFF\xCE\xCB\xC1\xD5\xF5\xCA\x9D\xD0\xD9\xDA"+0x8DADBF8C).s);
	HMODULE hGfxDx	  = LoadLibraryA(/*i3GfxDx.dll*/XorStr<0x9B,12,0x3A6562DC>("\xF2\xAF\xDA\xF8\xE7\xE4\xD9\x8C\xC7\xC8\xC9"+0x3A6562DC).s);

	m_pCaps		 = (DWORD)GetProcAddress(hGfxDx,/*?m_pCaps@i3RenderContext@@1PAVi3GfxCaps@@A*/XorStr<0x62,43,0x8B7A8862>("\x5D\x0E\x3B\x15\x25\x06\x18\x1A\x2A\x02\x5F\x3F\x0B\x01\x14\x14\x00\x30\x1B\x1B\x02\x12\x00\x0D\x3A\x3B\x4D\x2D\x3F\x29\xE9\xB2\xC5\xE5\xFC\xC6\xE7\xF7\xFB\xC9\xCA\xCA"+0x8B7A8862).s);
	SelectShader = (DWORD)GetProcAddress(hGfxDx,/*?SelectShader@i3RenderContext@@QAEXPAVi3Shader@@H@Z*/XorStr<0xC5,52,0xC83CBDC7>("\xFA\x95\xA2\xA4\xAC\xA9\xBF\x9F\xA5\xAF\xAB\xB5\xA3\x92\xBA\xE7\x87\xB3\xB9\xBC\xBC\xA8\x98\xB3\xB3\xAA\xBA\x98\x95\xA2\xA3\xB5\xA4\xA3\xBF\xB8\xA8\xBC\x82\xDF\xBE\x86\x8E\x94\x94\x80\xB3\xB4\xBD\xB6\xAD"+0xC83CBDC7).s);
	
	xMakePTR((PBYTE)AddyEngine->GetAddyValueByKey(/*XFHPB.Import.i3RenderContext::DrawIndexedPrim*/XorStr<0xF1,46,0xB5196AF6>("\xA9\xB4\xBB\xA4\xB7\xD8\xBE\x95\x89\x95\x89\x88\xD3\x97\xCC\x52\x64\x6C\x67\x61\x77\x45\x68\x66\x7D\x6F\x73\x78\x37\x34\x4B\x62\x70\x65\x5A\x7A\x71\x73\x6F\x7D\x7D\x4A\x69\x75\x70"+0xB5196AF6).s) ,(DWORD)myDrawIndexedPrim);
}

void CallerThread()
{
	LogAddyValues();
	SearchPatterns();

	HookSetEnd();
	HookLocalTime();
	InitializeFeatures();
	InitializeVisibleCheck();

	StartRoutine(Hook_MouseMacro);

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ThreadHookX, NULL, NULL, NULL);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ThreadHook,NULL,NULL,NULL);
	//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&ThreadX, NULL, 0, NULL);
}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
//--        // Created By : MhmmdYogiSaputra                                                               --  
//--        // Facebook   : https://www.facebook.com/gigntng                                               --
//--        // Youtube    : https://www.youtube.com/channel/UCoCztOogokhBSJoAFWiW1yA                       --
//--       // Website    : http://www.pintercit.me/                                                        --
//--                                                                                                       --
//--        // CopyRight 2018  ( Woy Ngentod Jangan Di Ganti CopyRight Dan Created Hargain Anjing Kontol ) --
//--                                                                                                       -- 
//------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------