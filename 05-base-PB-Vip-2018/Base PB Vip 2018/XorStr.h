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
#ifndef _XOR_H
#define _XOR_H

#pragma once

template <int XORSTART, int BUFLEN, int XREFKILLER>
class XorStr
{
private: 
    XorStr();
public: 
    char s[BUFLEN];

    XorStr(const char* xs);
    ~XorStr(){ for(int i=0;i<BUFLEN;i++)s[i]=0;}
};

template <int XORSTART, int BUFLEN, int XREFKILLER>
XorStr<XORSTART,BUFLEN,XREFKILLER>::XorStr(const char* xs)
{

    int xvalue = XORSTART;
    int i = 0;
    for(;i<(BUFLEN-1);i++) {
        s[i] = xs[i-XREFKILLER]^xvalue;
        xvalue += 1;
        xvalue %= 256;
    }
    s[BUFLEN-1] = 0;


}

#define XOR(a) a

#endif

/*-------------------------------------------------------------------------------------------------------------------*/
//.text:100CBF50 ; public: class i3Shader * __thiscall i3RenderContext::DrawIndexedPrim(class i3Shader *, enum  I3G_PRIMITIVE, unsigned int, unsigned int)
//.text:100CBF50                 public ?DrawIndexedPrim@i3RenderContext@@QAEPAVi3Shader@@PAV2@W4I3G_PRIMITIVE@@II@Z
//.text:100CBF50 ?DrawIndexedPrim@i3RenderContext@@QAEPAVi3Shader@@PAV2@W4I3G_PRIMITIVE@@II@Z proc near
//.text:100CBF50
//.text:100CBF50 var_228         = dword ptr -228h
//.text:100CBF50 var_224         = dword ptr -224h
//.text:100CBF50 var_220         = dword ptr -220h
//.text:100CBF50 var_21C         = dword ptr -21Ch
//.text:100CBF50 var_2C          = dword ptr -2Ch
//.text:100CBF50 var_28          = dword ptr -28h
//.text:100CBF50 var_1C          = dword ptr -1Ch
//.text:100CBF50 var_18          = dword ptr -18h
//.text:100CBF50 var_14          = dword ptr -14h
//.text:100CBF50 var_10          = dword ptr -10h
//.text:100CBF50 var_C           = dword ptr -0Ch
//.text:100CBF50 var_8           = dword ptr -8
//.text:100CBF50 var_4           = dword ptr -4
//.text:100CBF50 arg_0           = dword ptr  4
//.text:100CBF50 arg_4           = dword ptr  8
//.text:100CBF50 arg_8           = dword ptr  0Ch
//.text:100CBF50 arg_C           = dword ptr  10h
//.text:100CBF50
//.text:100CBF50                 push    0FFFFFFFFh
//.text:100CBF52                 push    offset loc_10152E8B
//.text:100CBF57                 mov     eax, large fs:0
//.text:100CBF5D                 push    eax
//.text:100CBF5E                 sub     esp, 21Ch
//.text:100CBF64                 mov     eax, dword_101EC198
//.text:100CBF69                 xor     eax, esp
//.text:100CBF6B                 mov     [esp+228h+var_10], eax
//.text:100CBF72                 push    ebx
//.text:100CBF73                 push    ebp
//.text:100CBF74                 push    esi
//.text:100CBF75                 push    edi
//.text:100CBF76                 mov     eax, dword_101EC198
//.text:100CBF7B                 xor     eax, esp
//.text:100CBF7D                 push    eax
//.text:100CBF7E                 lea     eax, [esp+23Ch+var_C]
//.text:100CBF85                 mov     large fs:0, eax
//.text:100CBF8B                 mov     ebx, [esp+23Ch+arg_C]
//.text:100CBF92                 mov     esi, ecx
//.text:100CBF94                 add     [esi+0F8h], ebx
//.text:100CBF9A                 mov     ecx, [esp+23Ch+arg_0]
//.text:100CBFA1                 mov     ebp, 1
//.text:100CBFA6                 add     [esi+14h], ebp
//.text:100CBFA9                 mov     eax, ?m_pCaps@i3RenderContext@@1PAVi3GfxCaps@@A ; i3GfxCaps * i3RenderContext::m_pCaps
//.text:100CBFAE                 mov     eax, [eax+150h]
//.text:100CBFB4                 xor     edi, edi
//.text:100CBFB6                 cmp     eax, edi
//.text:100CBFB8                 jz      short loc_100CBFC3 //Pertama
//.text:100CBFBA                 push    edi
//.text:100CBFBB                 push    ecx
//.text:100CBFBC                 mov     ecx, esi
//.text:100CBFBE                 call    ?SelectShader@i3RenderContext@@QAEXPAVi3Shader@@H@Z ; i3RenderContext::SelectShader(i3Shader *,int)
//.text:100CBFC3
//.text:100CBFC3 loc_100CBFC3:                           ; CODE XREF: i3RenderContext::DrawIndexedPrim(i3Shader *,I3G_PRIMITIVE,uint,uint)+68j
//.text:100CBFC3                 cmp     byte ptr [esi+160h], 0
//.text:100CBFCA                 jz      loc_100CC112 //Kedua
//.text:100CBFD0                 cmp     [esi+546Ch], ebp
//.text:100CBFD6                 jnz     loc_100CC112 //Kedua
//.text:100CBFDC                 cmp     [esp+23Ch+arg_8], edi
//.text:100CBFE3                 jz      loc_100CC085 //Ketiga
//.text:100CBFE9                 push    edi
//.text:100CBFEA                 push    offset aClassI3shade_0 ; "class i3Shader *__thiscall i3RenderCont"...
//.text:100CBFEF                 push    0AA7h
//.text:100CBFF4                 push    edi
//.text:100CBFF5                 call    ds:?SetEnv@i3Error@@YAXPBDH0W4I3LOG_TYPE@@@Z ; i3Error::SetEnv(char const *,int,char const *,I3LOG_TYPE)
//.text:100CBFFB                 lea     ecx, [esp+30h]
//.text:100CBFFF                 mov     [esp+23Ch+var_C], ecx
//.text:100CC006                 mov     [esp+23Ch+var_8], edi
//.text:100CC00D                 mov     [esp+23Ch+var_4], 1FFh
//.text:100CC018                 mov     byte ptr [esp+30h], 0
//.text:100CC01D                 push    offset aStartidx0 ; "StartIdx == 0"
//.text:100CC022                 mov     edx, ecx
//.text:100CC024                 push    offset aAssertedS ; "Asserted : %s"
//.text:100CC029                 push    edx
//.text:100CC02A                 mov     [esp+248h+arg_8], edi
//.text:100CC031                 call    sub_100B1390
//.text:100CC036                 mov     eax, [esp+248h+var_C]
//.text:100CC03D                 mov     ecx, [esp+248h+var_8]
//.text:100CC044                 lea     edx, [esp+34h]
//.text:100CC048                 add     ecx, eax
//.text:100CC04A                 push    edx
//.text:100CC04B                 mov     [esp+38h], eax
//.text:100CC04F                 mov     [esp+3Ch], ecx
//.text:100CC053                 call    ds:?Log@i3Error@@YAXABV?$literal_base_range@PBD@i3@@@Z ; i3Error::Log(i3::literal_base_range<char const *> const &)
//.text:100CC059                 mov     eax, [esp+248h+var_8]
//.text:100CC060                 lea     ecx, [esp+40h]
//.text:100CC064                 add     esp, 20h
//.text:100CC067                 mov     [esp+228h+arg_C], 0FFFFFFFFh
//.text:100CC072                 cmp     eax, ecx
//.text:100CC074                 jz      short loc_100CC085 //Ketiga
//.text:100CC076                 mov     edx, [esp+228h]
//.text:100CC07D                 inc     edx
//.text:100CC07E                 push    edx
//.text:100CC07F                 push    eax
//.text:100CC080                 call    sub_1009ED30
//.text:100CC085
//.text:100CC085 loc_100CC085:                           ; CODE XREF: i3RenderContext::DrawIndexedPrim(i3Shader *,I3G_PRIMITIVE,uint,uint)+93j
//.text:100CC085                                         ; i3RenderContext::DrawIndexedPrim(i3Shader *,I3G_PRIMITIVE,uint,uint)+124j
//.text:100CC085                 mov     eax, [esi+545Ch]
//.text:100CC08B                 mov     ebx, [eax+188h]
//.text:100CC091                 mov     ebp, [esi+5468h]
//.text:100CC097                 mov     ecx, [eax+1E0h]
//.text:100CC09D                 imul    ebp, ebx
//.text:100CC0A0                 cmp     [esi+5454h], edi
//.text:100CC0A6                 mov     [esp+14h], ecx
//.text:100CC0AA                 jle     loc_100CC143
//.text:100CC0B0
//.text:100CC0B0 loc_100CC0B0:                           ; CODE XREF: i3RenderContext::DrawIndexedPrim(i3Shader *,I3G_PRIMITIVE,uint,uint)+1BEj
//.text:100CC0B0                 mov     ecx, [esp+14h]
//.text:100CC0B4                 mov     eax, [esi+53A8h]
//.text:100CC0BA                 mov     edx, [eax]
//.text:100CC0BC                 mov     edx, [edx+190h]
//.text:100CC0C2                 push    0
//.text:100CC0C4                 push    ebp
//.text:100CC0C5                 push    ecx
//.text:100CC0C6                 push    1
//.text:100CC0C8                 push    eax
//.text:100CC0C9                 call    edx
//.text:100CC0CB                 mov     edx, [esp+23Ch+arg_C]
//.text:100CC0D2                 mov     eax, [esi+53A8h]
//.text:100CC0D8                 mov     ecx, [eax]
//.text:100CC0DA                 push    edx
//.text:100CC0DB                 mov     edx, [esp+240h+arg_8]
//.text:100CC0E2                 push    edx
//.text:100CC0E3                 mov     edx, [esi+924h]
//.text:100CC0E9                 mov     edx, [edx+170h]
//.text:100CC0EF                 push    edx
//.text:100CC0F0                 mov     edx, [esp+248h+arg_4]
//.text:100CC0F7                 push    0
//.text:100CC0F9                 push    0
//.text:100CC0FB                 push    edx
//.text:100CC0FC                 push    eax
//.text:100CC0FD                 mov     eax, [ecx+148h]
//.text:100CC103                 call    eax
//.text:100CC105                 inc     edi
//.text:100CC106                 add     ebp, ebx
//.text:100CC108                 cmp     edi, [esi+5454h]
//.text:100CC10E                 jl      short loc_100CC0B0 //Keempat
//.text:100CC110                 jmp     short loc_100CC143
//.text:100CC112 ; ---------------------------------------------------------------------------
//.text:100CC112
//.text:100CC112 loc_100CC112:                           ; CODE XREF: i3RenderContext::DrawIndexedPrim(i3Shader *,I3G_PRIMITIVE,uint,uint)+7Aj
//.text:100CC112                                         ; i3RenderContext::DrawIndexedPrim(i3Shader *,I3G_PRIMITIVE,uint,uint)+86j
//.text:100CC112                 mov     edx, [esp+23Ch+arg_8]
//.text:100CC119                 mov     eax, [esi+53A8h]
//.text:100CC11F                 mov     ecx, [eax]
//.text:100CC121                 push    ebx
//.text:100CC122                 push    edx
//.text:100CC123                 mov     edx, [esi+924h]
//.text:100CC129                 mov     edx, [edx+170h]
//.text:100CC12F                 push    edx
//.text:100CC130                 mov     edx, [esp+248h+arg_4]
//.text:100CC137                 push    edi
//.text:100CC138                 push    edi
//.text:100CC139                 push    edx
//.text:100CC13A                 push    eax
//.text:100CC13B                 mov     eax, [ecx+148h]
//.text:100CC141                 call    eax
//.text:100CC143
//.text:100CC143 loc_100CC143:                           ; CODE XREF: i3RenderContext::DrawIndexedPrim(i3Shader *,I3G_PRIMITIVE,uint,uint)+15Aj
//.text:100CC143                                         ; i3RenderContext::DrawIndexedPrim(i3Shader *,I3G_PRIMITIVE,uint,uint)+1C0j
//.text:100CC143                 mov     eax, [esi+0AE8h]
//.text:100CC149                 mov     ecx, [esp+258h+var_28]
//.text:100CC150                 mov     large fs:0, ecx
//.text:100CC157                 pop     ecx
//.text:100CC158                 pop     edi
//.text:100CC159                 pop     esi
//.text:100CC15A                 pop     ebp
//.text:100CC15B                 pop     ebx
//.text:100CC15C                 mov     ecx, [esp+244h+var_2C]
//.text:100CC163                 xor     ecx, esp
//.text:100CC165                 call    sub_1013955F
//.text:100CC16A                 add     esp, 228h
//.text:100CC170                 retn    10h
//.text:100CC170 ?DrawIndexedPrim@i3RenderContext@@QAEPAVi3Shader@@PAV2@W4I3G_PRIMITIVE@@II@Z endp ; sp = -1Ch

/*---- Key Press CAPITAL-----*/
#define VK_A           0x41
#define VK_B           0x42
#define VK_A           0x41
#define VK_B           0x42
#define VK_C           0x43
#define VK_D           0x44
#define VK_E           0x45
#define VK_F           0x46
#define VK_G           0x47
#define VK_H           0x48
#define VK_I           0x49
#define VK_J           0x4A
#define VK_K           0x4B
#define VK_L           0x4C
#define VK_M           0x4D
#define VK_N           0x4E
#define VK_O           0x4F
#define VK_P           0x50
#define VK_Q           0x51
#define VK_R           0x52
#define VK_S           0x53
#define VK_T           0x54
#define VK_U           0x55
#define VK_V           0x56
#define VK_W           0x57
#define VK_X           0x58
#define VK_Y           0x59
#define VK_Z           0x5A
/*---- Key Press Number List Key Pad -----*/
#define VK_0           0x30
#define VK_1           0x31
#define VK_2           0x32
#define VK_3           0x33
#define VK_4           0x34
#define VK_5           0x35
#define VK_6           0x36
#define VK_7           0x37
#define VK_8           0x38
#define VK_9           0x39

//// Replace Assault Byte Hack
//DWORD AssaulthByte[263]=
//{
//	100003001, //= SG-550 Ext.
//	100003002, //= AK-47 Ext.
//	100003003, //= M4A1 Ext.
//	100003004, //= K-2
//	100003009, //= F2000 Ext.
//	100003010, //= M4A1 Camoflage with Silencer
//	100003011, //= K-201 Ext.
//	100003013, //= G36C Ext.
//	100003014, //= SG-550 Camoflage
//	100003015, //= AK SOPMOD
//	100003017, //= AK-47 Silver
//	100003018, //= SG-550 Metallic Blue
//	100003019, //= SG-550 Silver
//	100003020, //= SG-550 White
//	100003021, //= M4A1 Silver
//	100003022, //= M4A1 White
//	100003023, //= M4A1 Gold
//	100003024, //= M4A1 Gold+
//	100003025, //= AK-47 Silver + 
//	100003026, //= SG-550 Metallic Blue + 
//	100003027, //= G36C Ext.
//	100003028, //= AUG A3 EV 
//	100003029, //= G36C Sl.
//	100003030, //= SG-550 Mb +20% 
//	100003031, //= G36C Silver +20%
//	100003032, //= F2000 Silver
//	100003033, //= AK SOPMOD +20%
//	100003034, //= G36C Silver
//	100003035, //= SG-550 S D. 
//	100003036, //= AUG A3 
//	100003037, //= AUG A3 Gold 
//	100003038, //= G36C Ext. D 
//	100003039, //= AK SOPMOD D 
//	100003040, //= AUG A3 D 
//	100003041, //= AK SOPMOD CG 
//	100003042, //= M4 SR-16 lvl-1 
//	100003043, //= M4 SR-16 lvl-2 
//	100003044, //= M4 SR-16 lvl-3 
//	100003045, //= M4 SR-16 Full Custom 
//	100003046, //= F2000 Silver
//	100003047, //= K-2 
//	100003048, //= AUG A3 Black 
//	100003049, //= FAMAS G2 
//	100003050, //= FAMAS G2 Com 
//	100003051, //= FAMAS G2 M203 
//	100003052, //= FAMAS G2 Sniper
//	100003053, //= SS2-V4 Para Sniper 
//	100003054, //= AK-47 G. D 
//	100003055, //= M4A1 Wh. D 
//	100003056, //= SG-550 Sl. D 
//	100003057, //= Vz. 52 
//	100003058, //= AK-47 Full Custom 
//	100003059, //= AK-47 Non Ext
//	100003060, //= M4A1 Non Ext 
//	100003061, //= SS2-V4 Para Sniper Gold
//	100003062, //= FAMAS G2 Commando E-Sports
//	100003063, //= AUG A3 E-Sports
//	100003064, //= Famas G2 Commando Gold
//	100003065, //= AUG A3 Blue
//	100003066, //= SG550
//	100003067, //= G36C
//	100003068, //= AK-47 FC Red
//	100003069, //= SCAR-H CQC
//	100003070, //= SCAR-H STD SILENCER
//	100003071, //= AUG A3 PBIC
//	100003072, //= AK-47 OLD SPEC
//	100003073, //= SG 550 S EV
//	100003074, //= AK SOPMOD EV
//	100003075, //= AUG A3 EV
//	100003076, //= AK-47 SI+ EV
//	100003077, //= F-2000 SI EV
//	100003078, //= AK-47 Ext EV
//	100003079, //= M4A1 Ext EV
//	100003080, //= M4A1 S. EV
//	100003081, //= M4A1 SI EV
//	100003082, //= M4 SR-16 Lvl-1 EV
//	100003083, //= M4 SR-16 Lvl-2 EV
//	100003084, //= M4 SR-16 Lvl-3 EV
//	100003085, //= SCAR-H CQC EV
//	100003086, //= AK-47 Goddess
//	100003087, //= Famas G2 Silver
//	100003088, //= SCAR-H LB SNIPER
//	100003089, //= AUG A3 Gold
//	100003090, //= Famas G2M White Digital
//	100003091, //= Famas G2 Commando PBTN
//	100003092, //= AK SOPMOD R(RUSSIA)
//	100003093, //= AUG A3 Blitz
//	100003094, //= SCAR-L Carbine
//	100003095, //= SCAR-L Recon
//	100003096, //= SCAR-L FC
//	100003097, //= AUG A3 GRS
//	100003098, //= M4A1 GRS
//	100003099, //= AK SOPMOD GRS
//	100003100, //= Famas G2 GRS
//	100003101, //= AK SOPMOD PBNC
//	100003102, //= HK-417
//	100003103, //= M4 SR-16 FC 
//	100003104, //= AUG A3 GSL
//	100003105, //= Famas G2 Commando GSL
//	100003106, //= AUG A3 White Italy
//	100003107, //= AUG A3 Black P.
//	100003108, //= AUG A3 GRS EV
//	100003109, //= AUG A3 TW1st?
//	100003110, //= AUG A3 TW1st P.
//	100003111, //= AUG A3 Bralizian Edition
//	100003112, //= AUG A3 Turkey
//	100003113, //= Famas G2 GRS EV
//	100003114, //= M4A1 Elite?
//	100003115, //= AN-94
//	100003116, //= F2000 Reload
//	100003117, //= SG550 Reload
//	100003118, //= Pindad SS2-V4 Para Sniper Reload
//	100003119, //= AK47 Elite
//	100003120, //= AUG A3 PBIC2013
//	100003121, //= M4A1 PBIC2013
//	100003122, //= AK47 PBIC2013
//	100003123, //= TAR-21
//	100003124, //= AK-47 G.
//	100003125, //= AK47 F.C
//	100003126, //= AK SOPMOD CG
//	100003127, //= M4A1 S.
//	100003128, //= AUG A3 Azerbaijan
//	100003129, //= AUG A3 Bloody
//	100003130, //= AUG A3 G Bloody
//	100003131, //= AUG A3 LATIN3
//	100003142, //= AUG A3 1st Anniversary
//	100003143, //= FG 42
//	100003144, //= AUG A3 R
//	100003145, //= FG 42 Gold
//	100003146, //= G36C Elite
//	100003147, //= AUG A3 Inferno
//	100003148, //= AUG A3 PBNC5
//	100003149, //= AUG A3 GSL2014
//	100003150, //= TAR-21 Midnight
//	100003151, //= TAR-21 BR Camo
//	100003152, //= AK SOPMOD BR Camo
//	100003153, //= SC-2010
//	100003154, //= SC-2010 Gold
//	100003155, //= AUG A3 Brazuca
//	100003156, //= SS2-V4 Para Sniper G (GW)
//	100003157, //= AUG A3 Champion
//	100003158, //= AUG A3 W.O.E
//	100003159, //= AUG A3 PBIC2014
//	100003160, //= AUG A3 BR 4th Anniversary
//	100003161, //= AUG A3 NonLogo LATIN3
//	100003162, //= TAR-21 NonLogo Midnight
//	100003163, //= AUG A3 PC Cafe
//	100003164, //= AUG A3 G E-Sport
//	100003165, //= AUG A3 Toy
//	100003166, //= SC-2010 D
//	100003167, //= AN-94 Gold
//	100003168, //= HK-417 Gold
//	100003169, //= TAR-21 Gold
//	100003170, //= SCAR-L Carbine Gold
//	100003171, //= AUG A3 LATIN4
//	100003173, //= AUG A3 Cangaceiro
//	100003174, //= XM8
//	100003175, //= SCAR-L Carbine D
//	100003176, //= SCAR-L Recon D
//	100003177, //= XM8 G.
//	100003178, //= AUG A3 Couple Breker
//	100003179, //= 
//	100003180, //= AUG A3 GRS2
//	100003181, //= AUG A3 Sheep
//	100003182, //= TAR-21 Sheep
//	100003184, //= AUG A3 Newborn 2015
//	100003186, //= AUG A3 GSL2015
//	100003188, //= AUG A3 Ongame
//	100003189, //= AUG A3 Redemption
//	100003207, //= AUG A3 Labaran2015
//	100003208, //= M4A1 GRS EV	
//	100003209, //= Vz-52 BlackPuerl
//	100003210, //= AUG A3 Egypt
//	100003211, //= AUG A3 Jordan
//	100003212, //= AUG A3 Saudi
//	100003213, //= AUG A3 UAE
//	100003214, //= AUG A3 PBNC2015
//	100003215, //= AUG A3 PBTC2015
//	100003217, //= AUG A3 Mech
//	100003218, //= AUG A3 DarkDays
//	100003219, //= SCAR-L FC PBNC2015 US
//	100003220, //= AUG A3 PBIC2015
//	100003221, //= 
//	100003222, //= AK SOPMOD G.
//	100003223, //= AUG A3 VeraCruz
//	100003224, //= M14 EBR
//	100003225, //= AUG A3 Basketball
//	100003226, //= AK SOPMOD Combat Medic
//	100003227, //= SC-2010 Combat Medic
//	100003228, //= AUG A3 Cobra
//	100003229, //= AUG A3 Camo Soldier
//	100003230, //= G36C Camo Soldier
//	100003231, //= 
//	100003232, //= AUG A3 Steam
//	100003233, //= AUG A3 Halloween
//	100003234, //= AUG A3 SPY Normal
//	100003236, //= AUG A3 LATIN5
//	100003237, //= AUG A3 Obsidian
//	100003238, //= K2C
//	100003239, //= K2C G.
//	100003240, //= AUG A3 SPY Deluxe
//	100003241, //= M14 EBR G.
//	100003242, //= AUG A3 DFN
//	100003243, //= AUG A3 XMAS2015
//	100003244, //= SC-2010 XMAS2015
//	100003245, //= AUG A3 Arena Deluxe
//	100003246, //= AK-12
//	100003247, //= AK-12 Gold
//	100003248, //= AUG A3 Sky
//	100003249, //= AUG A3 Silencer 
//	100003250, //= AUG A3 Cupid
//	100003251, //= AUG A3 Sakura
//	100003252, //= AK SOPMOD Sakura
//	100003253, //= AUG A3 Serpent
//	100003254, //= Water Gun 2016
//	100003255, //= AUG A3 GRS3
//	100003256, //= AUG A3 Beast
//	100003257, //= AUG A3 PBGC 2016
//	100003258, //= AUG A3 GSL 2016
//	100003259, //= AUG A3 Tiger
//	100003260, //= AUG A3 Tiger Deluxe
//	100003261, //= AUG A3 Midnight 2
//	100003262, //= AUG A3 Joker
//	100003263, //= AUG A3 E-Sports 2
//	100003264, //= FAMAS G2 M203 E-Sports 2
//	100003265, //= AUG A3 Dragon
//	100003266, //= AUG A3 PBWC 2016
//	100003267, //= AUG A3 Mummy
//	100003268, //= Pindad SS2-V5 
//	100003269, //= Pindad SS2-V5 SL.
//	100003270, //= Pindad SS2-V5 G.
//	100003271, //= AUG A3 Aruna
//	100003272, //= AUG A3 Strike
//	100003273, //= SC-2010 Strike
//	100003274, //= AUG A3 Demonic 
//	100003275, //= AUG A3 Dolphin
//	100003276, //= SC-2010 Dolphin
//	100003277, //= AUG A3 Blue Diamond
//	100003278, //= AUG A3 Lebaran 2016
//	100003279, //= AUG A3 Alien
//	100003280, //= AUG A3 Woody
//	100003281, //= XM8 Woody
//	100003282, //= FAMAS G2 Commado Newborn 2016
//	100003283, //= AUG A3 Puzzle
//	100003284, //= Groza
//	100003285, //= Groza Gold 
//	100003286, //= Groza Silver
//	100003287, //= SC-2010 Dracula
//	100003288, //= Groza Russian
//	100003289, //= Groza Russian Deluxe
//	100003290, //= AUG A3 Liberty
//	100003291, //= AUG A3 PBIC 2016
//	100003292, //= SC-2010 PBIC 2016
//	100003293, //= K2C PBIC 2016
//	100003294, //= AUG A3 PBTC2016
//	100003295, //= AUG A3 DarkSteel
//	100003296, //= AUG A3 PBNC 2016
//	100003297, //= Pindad SS2 V5 PBNC 2016 
//	100003298, //= AUG A3 PBST 2016
//	100003299, //= AUG A3 Supreme
//	100003300, //= AUG A3 Halloween 2016
//	100003301, //= AK-12 Gorgeous
//	100003302 //= AUG A3 Gorgeous
//};
//
//// Replace SMG Byte Hack
//DWORD SMGByte[239]=
//{
//	200004001, //= MP5K Ext. 
//	200004002, //= Spectre Ext. 
//	200004003, //= K-1 Ext. 
//	200004004, //= MP7 Ext. 
//	200004006, //= K-1 
//	200004007, //= MP5K G. 
//	200004008, //= UMP45 Ext. 
//	200004009, //= Spectre W. 
//	200004010, //= P90 MC 
//	200004011, //= P90 Ext. 
//	200004012, //= KrissSuperV 
//	200004013, //= Kriss SV 
//	200004014, //= MP5K Silver 
//	200004015, //= MP5K White
//	200004015, //= Spectre White
//	200004019, //= Kriss SV 
//	200004020, //= Spectre Silver 
//	200004021, //= K-1 Silver
//	200004022, //= MP7 Sllver 
//	200004023, //= UMP45 Sl. 
//	200004024, //= MP5K Gold D. 
//	200004025, //= Spectre W D. 
//	200004026, //= Kriss SV Gold 
//	200004027, //= P90 MC Camoflage
//	200004028, //= Kriss SV Gold Dummy 
//	200004029, //= p90 ext D 
//	200004030, //= Kriss SV D 
//	200004031, //= Kriss SV D Dummy
//	200004032, //= P90 MC D 
//	200004033, //= AKS47U Ext. 
//	200004034, //= M4 CQB-R lvl-1 
//	200004035, //= M4 CQB-R lvl-2 
//	200004036, //= M4 CQB-R lvl-3 
//	200004037, //= MP7 Silver 
//	200004038, //= MP7 Camoflage 
//	200004039, //= Kriss SV Black 
//	200004040, //= Kriss SV Black Dummy
//	200004041, //= MP5K Silver D 
//	200004042, //= Spectre Silver D 
//	200004043, //= SS1-R5 Carbine 
//	200004045, //= MP7 Ext. D 
//	200004046, //= UMP45 Ext. D 
//	200004047, //= Kriss SV Batik 
//	200004048, //= Kriss SV Batik Dummy
//	200004049, //= SS1-R5 Carbine Gold
//	200004050, //= Kriss SV Batik D
//	200004051, //= Kriss SV Batik D Dummy 
//	200004052, //= Kriss SV E-Sport 
//	200004053, //= Kriss SV E-Sport Dummy 
//	200004054, //= Kriss SV Vector 
//	200004055, //= Kriss SV Vector Dummy
//	200004056, //= MP7 Non Ext
//	200004057, //= Spectre Non Ext
//	200004058, //= UMP45 Black 
//	200004059, //= MP7 SE2 
//	200004060, //= Kriss SV PBIC 2012 
//	200004061, //= Kriss SV. PBIC 2012 Dummy
//	200004062, //= Spectre W. EV
//	200004063, //= MP5K G EV
//	200004064, //= P90 MCS EV
//	200004065, //= Kriss SV. EV
//	200004066, //= MP7 Ext EV
//	200004067, //= MP5K SI EV
//	200004068, //= UMP45 SI EV
//	200004069, //= P90 Ext EV
//	200004070, //= M4 CQB-R Lvl-1 EV
//	200004071, //= M4 CQB-R Lvl-2 EV
//	200004072, //= M4 CQB-R Lvl-3 EV
//	200004073, //= Kriss SV. Dummy
//	200004074, //= Spectre SI. EV
//	200004075, //= P90 Gold 
//	200004076, //= AKS74U (Count)
//	200004077, //= P90 White PBSC
//	200004078, //= P90 PBTN 
//	200004079, //= Kriss S.V PBTN 
//	200004080, //= Kriss S.V PBTN Dummy 
//	200004081, //= MP7 GRS
//	200004082, //= P90 MC GRS
//	200004083, //= Kriss SV. GRS
//	200004084, //= Kriss SV. GRS(Single non Dual)
//	200004085, //= P90 Newborn
//	200004086, //= P90 MC PBNC
//	200004087, //= Kriss SV. GSL
//	200004088, //= Kriss SV. GSL Dummy
//	200004089, //= P90 GSL
//	200004090, //= Kriss SV. Black P.
//	200004091, //= Kriss SV. Black P. Dummy
//	200004092, //= UMP45 Black P.
//	200004093, //= Kriss SV. GRS EV (Red without Garena Logo Skin)
//	200004094, //= Kriss SV. GRS EV Dummy
//	200004095, //= P90 MC GRS EV (Red without Garena Logo Skin)
//	200004096, //= AKS74U Reload
//	200004097, //= UMP45 Reload
//	200004098, //= Spectre Reload
//	200004099, //= Pindad SS1-R5 Carbine Reload
//	200004100, //= MP5K Reload
//	200004101, //= Kriss S.V 4th Anniversarry
//	200004102, //= Kriss S.V 4th Anniversarry Dummy
//	200004103, //= Kriss S.V PBIC2013
//	200004104, //= Kriss S.V PBIC2013 Dummy 
//	200004105, //= MP7 GRS EV (Red without Garena Logo Skin)
//	200004106, //= PP-19 Bizon
//	200004107, //= MP9 Ext
//	200004108, //= Kriss S.V Silencer
//	200004109, //= Kriss S.V Silencer Dummy
//	200004110, //= Kriss S.V Turkey
//	200004111, //= Kriss S.V Turkey Dummy
//	200004112, //= P90 M.C Bloody
//	200004113, //= P90 M.C. LATIN3
//	200004114, //= P90 Ext BR Camo
//	200004121, //= Kriss S.V 1st Anniversary
//	200004122, //= Kriss S.V 1st Anniversary Dummy
//	200004123, //= Kriss S.V R
//	200004124, //= Kriss S.V R Dummy
//	200004125, //= P90 Newborn 2014
//	200004126, //= Kriss S.V Inferno
//	200004127, //= Kriss S.V Inferno Dummy
//	200004128, //= P90 Inferno
//	200004129, //= P90 Ext PBNC5
//	200004130, //= Kriss S.V GSL2014
//	200004131, //= Kriss S.V GSL2014 Dummy
//	200004132, //= Kriss S.V Garena Midnight Blue
//	200004133, //= Kriss S.V Garena Midnight Blue Dummy
//	200004134, //= OA-93
//	200004135, //= OA-93 Dummy
//	200004136, //= OA-93 Gold
//	200004137, //= OA-93 Gold Dummy
//	200004138, //= P90 Brazuca
//	200004139, //= Kriss S.V Brazuca
//	200004140, //= Kriss S.V Brazuca Dummy
//	200004141, //= P90 Ext 5th Anniversary
//	200004142, //= Kriss S.V Champion
//	200004143, //= Kriss S.V Champion Dummy
//	200004144, //= Kriss S.V W.O.E
//	200004145, //= Kriss S.V W.O.E Dummy
//	200004146, //= P90 Ext PBIC2014
//	200004147, //= P90 White NonLogo PBSC
//	200004148, //= P90 M.C NonLogo LATIN3
//	200004149, //= Kriss S.V NonLogo Midnight
//	200004150, //= Kriss S.V NonLogo Midnight Dummy
//	200004151, //= Kriss S.V PC Cafe
//	200004152, //= Kriss S.V PC Cafe Dummy
//	200004153, //= Kriss S.V PBSC2014 (Red Down)
//	200004154, //= Kriss S.V PBSC2014 Dummy
//	200004155, //= Kriss S.V G E-Sport
//	200004156, //= Kriss S.V G E-Sport Dummy
//	200004157, //= Kriss S.V Toy
//	200004158, //= Kriss S.V Toy Dummy
//	200004159, //= OA-93 D
//	200004160, //= OA-93 D Dummy
//	200004161, //= MP9 Ext Gold
//	200004162, //= PP-19 Bizon Gold
//	200004163, //= P90 Ext LATIN4
//	200004164, //= MP9 Ext XMAS
//	200004165, //= OA-93 XMAS
//	200004166, //= OA-93 XMAS Dummy
//	200004167, //= PP-19 Bizon XMAS
//	200004168, //= Kriss S.V XMAS
//	200004169, //= Kriss S.V XMAS Dummy
//	200004170, //= Kriss S.V Cuple Breker
//	200004171, //= Kriss S.V Cuple Breker Dummy
//	200004172, //= Kriss S.V CNY 2015
//	200004173, //= Kriss S.V CNY 2015 Dummy
//	200004174, //= P90 M.C Sheep
//	200004175, //= Kriss S.V GRS2
//	200004176, //= Kriss S.V GRS2 Dummy
//	200004177, //= P90 Ext. Newborn 2015
//	200004180, //= OA-93 GSL2015
//	200004181, //= OA-93 GSL2015 Dummy
//	200004182, //= P90 GSL2015
//	200004185, //= Kriss S.V Ongame
//	200004185, //= Kriss S.V Ongame Dummy
//	200004187, //= P90 Ongame
//	200004188, //= Kriss SV. Redemption
//	200004189, //= Kriss SV. Redemption Dummy
//	200004190, //= P90 Ext Redemption
//	200004191, //= Kriss S.V Summer
//	200004192, //= Kriss S.V Summer Dummy
//	200004193, //= EVO3
//	200004194, //= EVO3 G.
//	200004195, //= P90 MC Rose
//	200004205, //= Kriss S.V PBNC 2015
//	200004216, //= Kriss S.V PBIC 2015
//	200004218, //= P90 Ext. PBIC 2015
//	200004228, //= OA-93 Medical
//	200004230, //= P90 Ext. Medical
//	200004237, //= Kriss S.V Halloween
//	200004239, //= P90 Ext Halloween
//	200004249, //= Kriss S.V X-MAS 2015
//	200004251, //= OA-93 X-MAS 2015
//	200004253, //= Kriss S.V Monkey
//	200004255, //= P90 MC Sky 
//	200004256, //= Kriss S.V GRS3
//	200004258, //= Kriss S.V Beast
//	200004260, //= Kriss S.V PBGC 2016
//	200004262, //= P90 Ext PBGC 2016
//	200004263, //= Kriss S.V GSL 2016
//	200004265, //= Kriss S.V Midnight 2
//	200004267, //= Kriss S.V Joker
//	200004269, //= P90 Ext Joker
//	200004270, //= Kriss S.V E-Sports 2
//	200004272, //= P90 Ext. Dragon
//	200004273, //= OA-93 PBWC 2016
//	200004275, //= Kriss S.V PBWC 2016
//	200004277, //= P90 M.C PBWC 2016
//	200004278, //= Kriss S.V Mummy 
//	200004280, //= Kriss S.V Aruna
//	200004282, //= P90 Ext Silence Aruna
//	200004283, //= Kriss S.V Strike
//	200004285, //= P90 Ext Silence Strike
//	200004286, //= Kriss S.V Demonic
//	200004288, //= P90 Ext Silence Demonic
//	200004289, //= Kriss S.V Dolphin
//	200004291, //= P90 Ext. Dolphin
//	200004292, //= OA-93 Blue Diamond
//	200004294, //= P90 Ext. Lebaran 2016
//	200004295, //= Kriss S.V Lebaran 2016
//	200004297, //= P90 Ext. Alien
//	200004298, //= Kriss S.V Alien
//	200004300, //= OA-93 Woody
//	200004302, //= OA-93 Newborn 2016
//	200004304, //= Kriss S.V Puzzle
//	200004306, //= P90 Ext. Puzzle
//	200004307, //= PP-19 Russian
//	200004308, //= PP-19 Russian Deluxe
//	200004309, //= OA-93 Liberty
//	200004311, //= P90 Ext. Liberty
//	200004312, //= Kriss S.V PBIC 2016
//	200004314, //= OA-93 PBIC 2016
//	200004316, //= Kriss S.V PBTC2016
//	200004318, //= Kriss S.V DarkSteel
//	200004320, //= P90 Ext. DarkSteel
//	200004321, //= Kriss S.V PBNC 2016
//	200004323, //= Kriss S.V PBST 2016
//	200004325, //= Kriss S.V Supreme 
//	200004327, //= P90 Ext. Supreme 
//	200004328, //= OA-93 Halloween 2016
//	200004330, //= Kriss S.V Gorgeous
//	200004332 //= OA-93 Gorgeous
//};
//
//// Replace Sniper Byte Hack
//DWORD SniperByte[186]=
//{
//	300005001, //= Dragunov
//	300005002, //= PSG-1 
//	300005003, //= SSG-69 
//	300005004, //= SSG-69 Camoflage
//	300005005, //= L115A1 
//	300005006, //= Dragunov Gold 
//	300005007, //= PSG-1 S. 
//	300005008, //= SSG-69 Silver 
//	300005009, //= PSG-1 Silver 
//	300005010, //= Dragunov Silver 
//	300005011, //= Dragunov CS. 
//	300005012, //= Dragunov CG. 
//	300005014, //= Dragunov Gold D. 
//	300005015, //= L115A1 Gold 
//	300005016, //= PSG1 S. D 
//	300005017, //= L115A1 D 
//	300005018, //= M4 SPR Lvl-1 
//	300005019, //= M4 SRP Lvl-2 
//	300005020, //= M4 SRP Lvl-3 
//	300005021, //= Rangemaster .338 
//	300005022, //= Rangemaster 7.62 
//	300005023, //= Rangemaster 7.62 STBY 
//	300005024, //= PSG1 Gold
//	300005025, //= SSG-69 Camoflage
//	300005026, //= L115A1 Black 
//	300005027, //= SSG-69 Silver D 
//	300005028, //= Dragunov D 
//	300005029, //= VSK94 
//	300005030, //= CheyTac M200 
//	300005031, //= Winchester M70 
//	300005032, //= Barrett M82A1
//	300005033, //= L115A1 E-Sport 
//	300005034, //= DSR-1
//	300005035, //= SVU
//	300005036, //= L115A1 SE
//	300005038, //= PSG1 S EV
//	300005039, //= Dragunov G. EV
//	300005040, //= Dragunov SI EV
//	300005041, //= L115A1 EV
//	300005042, //= PSG1 SI EV
//	300005043, //= SSG-69 SI EV
//	300005044, //= M4 SPR Lvl-1 EV
//	300005045, //= M4 SPR Lvl-2 EV
//	300005046, //= M4 SPR Lvl-3 EV
//	300005047, //= Dragunov Red
//	300005048, //= VSK94 (Count)
//	300005049, //= Dragunov CG. (P)
//	300005050, //= L115A1 PBTN
//	300005051, //= (Something)
//	300005052, //= CheyTac M200 GRS
//	300005053, //= L115A1 PBNC
//	300005054, //= SVU S(Camo)
//	300005055, //= CheyTac M200 GSL
//	300005056, //= L115A1 Black P.
//	300005057, //= CheyTac M200 Bloody
//	300005058, //=
//	300005059, //= PSG1 Reload
//	300005060, //= Rangermaster 338 Reload
//	300005061, //= Rangermaster 762 Reload
//	300005062, //= Rangermaster 762 STBY Reload
//	300005063, //= Cheytac M200 Turkey
//	300005064, //= L115A1 LATIN3
//	300005065, //= L115A1 BR Camo
//	300005068, //= XM2010
//	300005069, //= (Something)
//	300005070, //= (Something)
//	300005071, //= Cheytac M200 1st Anniversary
//	300005072, //= Walther WA2000
//	300005073, //= Cheytac M200 R
//	300005074, //= Walther WA2000 Gold
//	300005075, //= PSG1 Elite
//	300005076, //= Dragunov Elite
//	300005077, //= SVU Elite
//	300005078, //= VSK94 Elite
//	300005079, //= Cheytac M200 Inferno
//	300005080, //= Cheytac M200 PBNC5
//	300005081, //= L115A1 GSL2014
//	300005082, //= Barrett M82A1
//	300005083, //= Cheytac M200 Brazuca
//	300005084, //= Cheytac M200 Champion
//	300005085, //= Cheytac M200 W.O.E
//	300005086, //= Dragunov W.O.E
//	300005087, //= Cheytac M200 PBIC2014
//	300005088, //= L115A1 NonLogo LATIN3
//	300005089, //= L115A1 PC Cafe
//	300005090, //= Cheytac M200 Merdeka
//	300005091, //= Cheytac M200 G E-Sport
//	300005092, //= L115A1 Toy
//	300005093, //= VSK94 Gold
//	300005094, //= SVU Gold
//	300005095, //= DSR-1 Gold
//	300005096, //= Cheytac M200 LATIN4
//	300005097, //= Cheytac M200 Cangaceiro
//	300005098, //
//	300005099, //= CheyTac Couple Breaker
//	300005100, //= Cheytac M200 GRS2
//	300005101, //= L115A1 NewBorn2015
//	300005102, //= CheyTac M200 GSL2015
//	300005103, //= Cheytac M200 PBNC6
//	300005104, //= Cheytac M200 Ongame
//	300005105, //= Cheytac M200 Redemption
//	300005106, //= L115A1 Summer
//	300005107, //= Dragunov Rose
//	300005108, //= Cheytac M200 LionFlame
//	300005109, //= L115A1 TigerFang
//	300005110, //= Cheytac M200 Brazil
//	300005111, //= Cheytac M200 PBST2015
//	300005112, //= Cheytac M200 4Game
//	300005113, //= Cheytac M200 4Game-SE
//	300005114, //= Cheytac M200 PBNC2015
//	300005115, //= Cheytac M200 PBTC2015
//	300005116, //= SVU PBTC2015
//	300005117, //= L115A1 Mech
//	300005118, //= Cheytac M200 DarkDays
//	300005119, //= XM2010 PBNC2015 US
//	300005120, //= Cheytac M200 PBIC2015
//	300005121, //= Cheytac M200 G.
//	300005122, //= Cheytac M200 VeraCruz
//	300005123, //= Tactilite T2
//	300005124, //= Cheytac M200 Sheep
//	300005125, //= Cheytac M200 Combat Medic
//	300005126, //= L115A1 Basketball
//	300005127, //= L115A1 Cobra
//	300005128, //= RangeMaster.338 Camo Soldier
//	300005129, //= Cheytac M200 Steam
//	300005130, //= Cheytac M200 Halloween
//	300005131, //= Tactilite T2 G.
//	300005132, //= DSR-1 SPY
//	300005133, //= Cheytac M200 LATIN5
//	300005134, //= Cheytac M200 Obsidian
//	300005135, //= DSR-1 Spy Deluxe
//	300005136, //= Cheytac M200 DFN
//	300005137, //= Cheytac M200 XMAS2015
//	300005138, //= Tactilite T2 XMAS2015
//	300005139, //= Cheytac M200 Monkey
//	300005140, //= Cheytac M200 Areana Normal
//	300005141, //= Cheytac M200 Areana Deluxe
//	300005142, //= Cheytac M200 VeraCruz2016
//	300005143, //= Cheytac M200 Cupid2016
//	300005144, //= Cheytac M200 Silencer
//	300005145, //= PGM Hatchete2
//	300005146, //= PGM Hatchete2 G.
//	300005147, //= Cheytac M200 Cupid
//	300005148, //= CheyTac M200 Sakura
//	300005149, //= CheyTac M200 Serpent
//	300005150, //= Tactilite T2 GRS3
//	300005151, //= CheyTac M200 Beast
//	300005152, //= CheyTac M200 PBGC 2016
//	300005153, //= CheyTac M200 GSL 2016
//	300005154, //= Tactilite T2 GSL 2016
//	300005155, //= CheyTac M200 Tiger
//	300005156, //= CheyTac M200 Tiger Deluxe
//	300005157, //= S-50
//	300005158, //= CheyTac M200 Midnight 2
//	300005159, //= AS-50 Gold
//	300005160, //= CheyTac M200 Joker
//	300005161, //= Tactilite T2 E-Sports 2
//	300005162, //= Tactilite T2 Dragon
//	300005163, //= CheyTac M200 PBWC 2016
//	300005164, //= -
//	300005165, //= CheyTac M200 Aruna
//	300005166, //= CheyTac M200 Strike
//	300005167, //= CheyTac M200 Demonic
//	300005168, //= Cheytac M200 Dolphin
//	300005169, //= L115A1 Dolphin
//	300005170, //= CheyTac M200 Blue Diamond
//	300005171, //= Tactilite T2 Blue Diamond
//	300005172, //= CheyTac M200 Lebaran 2016 
//	300005173, //= Cheytac M200 Alien
//	300005174, //= L115A1 Alien
//	300005175, //= Cheytac M200 Woody
//	300005176, //= Tactilite T2 Newborn 2016
//	300005177, //= Tactilite T2 Puzzle
//	300005178, //= Dragunov Russian
//	300005179, //= Dragunov Russian Deluxe
//	300005180, //= Tactilite T2 Liberty
//	300005181, //= Cheytac M200 PBIC 2016
//	300005182, //= Tactilite T2 PBIC 2016
//	300005183, //= Cheytac M200 PBTC2016
//	300005184, //= AS-50 PBTC2016
//	300005185, //= Cheytac M200 DarkSteel
//	300005186, //= Cheytac M200 PBNC 2016
//	300005187, //= Cheytac M200 PBST 2016 
//	300005188, //= Cheytac M200 Supreme 
//	300005189, //= Cheytac M200 Halloween 2016
//	300005190 //= Cheytac M200 Azerbaijan 
//};
//
//// Replace Shotgun Byte Hack
//DWORD ShotgunByte[78]=
//{
//	400006001, //= 870MCS 
//	400006002, //= C.J Shotgun(870MCS W)
//	400006003, //= SPAS-15 
//	400006004, //= 870MCS W. 
//	400006005, //= M1887 
//	400006006, //= SPAS-15 SL
//	400006007, //= 870MCS T. 
//	400006008, //= 870MCS SL 
//	400006009, //= SPAS-15 SL + 
//	400006010, //= M1887 W. 
//	400006011, //= 870MCS W. D 
//	400006012, //= SPAS-15 D 
//	400006013, //= M26 LSS
//	400006014, //= 870MCS SI D 
//	400006015, //= 870MCS D 
//	400006016, //= SPAS-15 SI D 
//	400006017, //= M1887 D 
//	400006018, //= SPAS-15 MSC 
//	400006019, //= JackHammer 
//	400006020, //= Kel-Tec KSG-15
//	400006021, //= M1887 SL
//	400006022, //= SPAS-15 EV
//	400006023, //= 870MCS W EV
//	400006024, //= SPAS-15 SL EV
//	400006026, //= M1887 W GRS
//	400006027, //= M1887 PBNC
//	400006028, //= M1887 GRS EV
//	400006029, //= SPAS-15 PBSC2013
//	400006030, //= M1887 Bloody
//	400006032, //= SPAS-15 Elite
//	400006033, //= M1887 W 1st Anniversary
//	400006034, //= M1887 R
//	400006035, //= M1887 PBNC5
//	400006036, //= Kel-Tec KSG 15 GSL2014
//	400006037, //= M1887 Brazuca
//	400006038, //= M1887 PBIC2014
//	400006039, //= UTS-15
//	400006040, //= SPAS-15 NonLogo PBSC2013
//	400006041, //= M1887 Lion-Heart
//	400006042, //= Zombie Slayer
//	400006043, //= Remington ETA
//	400006044, //= Remington ETA G.
//	400006045, //= 
//	400006046, //= UTS-15 D
//	400006047, //= Ceberus
//	400006048, //= UTS-15 G.
//	400006049, //= M1887 GSL2015
//	400006051, //= WATER GUN
//	400006052, //= M1887 Summer
//	400006053, //= M1887 PBNC2015
//	400006054, //= SPAS-15 PBNC2015
//	400006055, //= M1887 PBTC2015
//	400006056, //= SPAS-15 MSC PBNC2015 US
//	400006057, //= M1887 Mech
//	400006058, //= M1887 PBIC 2015
//	400006060, //= M1887 Medical
//	400006063, //= M1887 Arena
//	400006064, //= M1887 Arena Deluxe
//	400006065, //= M1887 Cupid
//	400006066, //= M1887 GRS3
//	400006067, //= M1887 Beast 
//	400006068, //= M1887 PBGC 2016 
//	400006069, //= M1887 Joker
//	400006070, //= M1887 Dragon
//	400006071, //= M1887 Aruna
//	400006072, //= M1887 Dolphin 
//	400006073, //= SPAS-15 Blue Diamond?
//	400006074, //= M1887 Lebaran 2016
//	400006075, //= M1887 Woody
//	400006076, //= M1887 Newborn 2016
//	400006077, //= M1887 Liberty 
//	400006078, //= M1887 PBIC 2016
//	400006079, //= M1887 PBTC2016
//	400006080, //= M1887 DarkSteel
//	400006081, //= M1887 PBNC 2016
//	400006082, //= M1887 Supreme
//	400006083, //= M1887 Gorgeous
//	400006084 //= Cerberus Gorgeous Shotgun
//};
//
//// Replace Machingun Byte Hack
//DWORD MachingunByte[13]=
//{
//	500010001, //= Mk 46 Ext.
//	500010002, //= Mk 46 Silver
//	500010003, //= RPD
//	500010004, //= L86 LSW
//	500010005, //= MK.46 Ext EV
//	500010006, //= RPD (Count)
//	500010007, //= RPD SI
//	500010008, //= RPD EV
//	500010009, //= L86 LSW XMAS
//	500010011, //= Ultimax-100
//	500010012, //= Ultimax-100 Gold
//	500010013, //= Ultimax-100 Madness
//	500010014 //= Ultimax-100 Mummy
//};
//
//// Replace Dual Byte Hack
//DWORD DualByte[8]=
//{
//	200018004, //= Dual Uzi 
//	200018005, //= Dual Mini-Uzi 
//	200018006, //= Dual Micro Uzi 
//	200018007, //= Dual Uzi Silencer
//	200018008, //= Dual Mini-Uzi Silencer
//	200018009, //= Dual Micro-Uzi Silencer 
//	200018011, //= Dual Mini-Uzi Silencer Silver
//	200018013 //= Dual Mini Uzi Gold
//};
//
//// Replace Launcher Byte Hack
//DWORD LauncherByte[3]=
//{
//	100016001, //= RPG-7
//	100016002, //= RPG-7(1 Ammo)
//	100016003 //= RPG-7
//};
//
//// Replace Secondary Byte Hack
//DWORD SecondaryByte[102]=
//{
//	601002001, //= Desert Eagle 
//	601002002, //= Mk 23 Ext.
//	601002003, //= K-5 
//	601002005, //= D-Eagle Silver 
//	601002006, //= P99 
//	601002007, //= Colt Python 
//	601002008, //= D-Eagle Gold
//	601002009, //= K-5 
//	601002010, //= Colt Python Gold+
//	601002011, //= Glock 18 
//	601002012, //= Colt Python D 
//	601002013, //= RB 454 SS2M 
//	601002014, //= RB 454 SS5M 
//	601002015, //= RB 454 SS8M 
//	601002016, //= RB 454 SS8M+S 
//	601002017, //= Colt Python G 
//	601002018, //= Colt Python GD 
//	601002019, //= Mk 23 Ext. D 
//	601002020, //= Colt Python D 
//	601002021, //= Glock 18 D 
//	601002022, //= Colt 45 
//	601002023, //= IMI Uzi 9mm 
//	601002024, //= Kriss Vector SDP 
//	601002025, //= HK45 (Single)
//	601002026, //= HK69
//	601002027, //= MK23 SI
//	601002028, //= M79
//	601002029, //= GL-06
//	601002030, //= Desert Eagle EV
//	601002031, //= Colt 17 (Count)
//	601002032, //= Desert Eagle GRS 
//	601002033, //= Glock 18 PBNC
//	601002034, //= R.B 454 SS8M+S PBSC2013
//	601002035, //= MK.23 Reload
//	601002036, //= Desert Eagle Reload
//	601002037, //= Glock 18 Turkey
//	601002038, //= HK45 Halloween
//	601002039, //= Glock 18 Azerbaijan
//	601002040, //= C. Python PBNC5
//	601002041, //= Glock 18 BR Camo
//	601002042, //= Desert Eagle (Bug)
//	601002047, //= Glock 18 BR Camo
//	601002048, //= Desert Eagle BR Camo
//	601002049, //= C.Python Brazuca
//	601002050, //= R.B 454 SS8M NonLogo PBSC2013
//	601002051, //= D-Eagle G E-Sport
//	601002052, //= C.Python Toy
//	601002057, //= D-Eagle Ongame
//	601002054, //= GL-06 CNY-2015 
//	601002061, //= Glock 18 PBST2015
//	601002062, //= Glock 18 4Game
//	601002063, //= Glock 18 4Game-SE
//	601002064, //= D-Eagle Lebaran2015
//	601002065, //= 
//	601002066, //= 
//	601002067, //= C.Python PBNC2015
//	601002068, //= R.B 454 SS8M Scope Mech
//	601002069, //= Kriss Vector SDP DarkDays
//	601002070, //= R.B 454 SS8M+S PBIC2015
//	601002071, //= Glock 18 G.
//	601002072, //= C.Python VeraCruz
//	601002073, //= R.B 454 SS8M+S Cobra
//	601002074, //= Kriss Vector SDP Camo Soldier
//	601002075, //= MK.23 SPY Normal
//	601002076, //= C.Python LATIN5
//	601002077, //= MK.23 SPY Deluxe
//	601002080, //= C. Phyton Arena Deluxe
//	601002081, //= R.B 454 SS8M+S Sky	
//	601002082, //= C. Python Sakura
//	601002083, //= C. Python Beast
//	601002084, //= C. Python GSL 2016
//	601002085, //= Desert Eagle Tige
//	601002086, //= Desert Eagle Tiger Deluxe
//	601002087, //= C. Phython PBWC 2016
//	601002088, //= Glock 18 Mummy
//	601002089, //= MK.23 Blue Diamond
//	601002091, //= MK.23 Alien
//	601002092, //= C. Python Newborn 2016 
//	601002093, //= Kriss Vector SDP Puzzle
//	601002094, //= U22 Neos
//	601002095, //= U22 Neos Silver
//	601002096, //= U22 Neos Gold
//	601002097, //= C. Python PBIC 2016
//	601002098, //= C. Python DarkSteel
//	601002099, //= R.B 454 SS8M+S PBST 2016
//	601002100, //= C. Python Supreme
//	601014001, //= Dual Handgun 
//	601014002, //= Dual D-Eagle 
//	601014004, //= Dual D-Eagle G. 
//	601014005, //= Dual Handgun D. 
//	601014006, //= Dual D-Eagle D 
//	601014007, //= Dual HK45 
//	601014009, //= Dual D-Eagle EV
//	601014010, //= Dual D-Eagle G(P)
//	601014011, //= Dual D-Eagle GRS
//	601014015, //= Dual D-Eagle BR Camo
//	601014016, //= Dual D-Eagle G E-Sport
//	601014017, //= Scorpion VZ.61 
//	601014018, //= Scorpion VZ.61 Gold
//	601014019, //= Desert Eagle Lebaran 2016
//	601014020, //= Scorpion VZ.61 Woody  
//	601014021 //= Scorpion Vz.61 Gorgeous
//};
//
//// Replace Melee Byte Hack
//DWORD MeleeByte[117]=
//{
//	702001001, //= M-7
//	702001002, //= M-9?
//	702001003, //= HAK (Bug)
//	702001004, //= Amok Kukri?
//	702001006, //= Mini Axe (Dummy)
//	702001007, //= Mini Axe
//	702001008, //= Mini Axe (Event)
//	702001009, //= M-7 Gold?
//	702001010, //= HAK Silver
//	702001011, //= Amok Kukri D?
//	702001012, //= Mini Axe D
//	702001013, //= Mini Axe?
//	702001014, //= GH5007
//	702001016, //= Bone Knife [Single]?
//	702001017, //= Fang Blade?
//	702001018, //= Ballistic Knife?
//	702001019, //= Ballistic Knife (Dummy)
//	702001020, //= Ballistic Knife (Event)
//	702001021, //= Keris?
//	702001023, //= Keris S.?
//	702001024, //= Candy Cane
//	702001025, //= Field Shovel
//	702001027, //= Amok Kukri EV
//	702001028, //= Mini Axe
//	702001037, //= Balistic Knife GRS
//	702001038, //= Balistic Knife GRS (Single)
//	702001041, //= Arabian Sword?
//	702001042, //= M-9 PBNC?
//	702001043, //= GH5007 Gold
//	702001044, //= GH5007 PBSC2013
//	702001046, //= Amok Kukri Turkey
//	702001047, //= Keris XMAS
//	702001049, //= Arabian Sword2
//	702001050, //= FangBlade PBNC5
//	702001051, //= FangBlade GSL2014
//	702001052, //= FangBlade Brazuca
//	702001053, //= Frying Pan
//	702001054, //= Frying Pan Dummy
//	702001055, //= Hair Dryer
//	702001056, //= Hair Dryer Dummy
//	702001057, //= FangBlade Inferno
//	702001058, //= Chinese Cleaver
//	702001059, //= GH5007 NonLogo PBSC2013
//	702001060, //= Chinese Cleaver Dummy
//	702001063, //= Field Shovel Dummy
//	702001064, //= Badminton Racket
//	702001065, //= Keris G E-Sport
//	702001066, //= Death Scythe
//	702001067, //= Fang Blade LATIN4
//	702001070, //= GH5007 Cangaceiro
//	702001071, //= Goat Hammer
//	702001072, //= Goat Hammer Dummy
//	702001073, //= Chinese Cleaver CNY 2015 
//	702001074, //= Chinese Cleaver CNY 2015 Dummy
//	702001075, //= Bone Knife GRS2(Singgle)
//	702001076, //= Fang Blade Newborn
//	702001069, //= Ice Trident
//	702001079, //= Fang Blade Ongame
//	702001080, //= Field Shovel Royal
//	702001082, //= Arbian Sword Midnight
//	702001097, //= Hair Dryer Indonesia
//	702001098, //= Hair Dryer
//	702001101, //= Fang Blade PBNC 2015
//	702001103, //= Bambu Runcing
//	702001104, //= Keris PBIC 2015
//	702001120, //= Monkey Hammer
//	702001123, //= Fangblade Arena
//	702001124, //= Fang Blade Arena Deluxe
//	702001127, //= Fang Blade Sakura 
//	702001129, //= Keris Beast
//	702001130, //= Fang Blade PBGC 2016
//	702001131, //= Keris GSL 2016
//	702001132, //= Fang Blade Tiger
//	702001133, //= Fang Blade Tiger Deluxe
//	702001136, //= Fang Blade Dragon
//	702001137, //= Amok Kukri PBWC 2016
//	702001138, //= Combat Machete PBWC 2016
//	702001139, //= Amok Kukri Mummy
//	702001140, //= Mini Axe Poison
//	702001143, //= Amok Kukri Poison
//	702001144, //= Keris Aruna
//	702001145, //= Combat Machete Strike
//	702001146, //= Death Scythe Demonic
//	702001147, //= Karambit
//	702001148, //= Centong Sayur 
//	702001149, //= Fang Blade Alien
//	702001150, //= Combat Machete Newborn 2016
//	702001151, //= Ballistic Knife Russian
//	702001153, //= Ballistic Knife Russian Deluxe
//	702001155, //= Combat Machete PBIC 2016
//	702001159, //= Fang Blade DarkSteel
//	702001160, //= Arabian Sword PBNC 2016 
//	702001161, //= Fang Blade Supreme
//	702001162, //= Halloween Hammer
//	700015001, //= Dual Knife?
//	700015002, //= Dual Knife D?
//	700015003, //= Dual Bone Knife?
//	700015004, //= Dual Knife EV
//	700015005, //= Dual Bone Knife GRS
//	700015006, //= Dual Knife PBNC
//	702015007, //= Dual Bone Knife?GRS2
//	702023001, //= Barefist Knuckle
//	702023002, //= Black Knuckles?
//	702023003, //= Brass Knuckles?
//	702023004, //= Silver Knuckles?
//	702023005, //= Pumpkin knuckles?
//	702023006, //= Spiked Knuckle?
//	702023007, //= Ballock Knuckle
//	702023009, //= Garena Knuckles
//	702023010, //= Zombies Knuckle
//	702015008, //= Dual Kunai 
//	702015009, //= Bone Knife PBNC 2015
//	702015011, //= Dual Knife Sky
//	702015012, //= Dual Kunai Serpent
//	702015013, //= Boneknife Joker
//	702015014, //= Boneknife E-Sports 2
//	702015015 //= Dual Sword
//};
//
//// Replace Granad Byte Hack
//DWORD ThornSpecialByte[22]=
//{
//	904007002, //= Smoke
//	904007003, //= Flashbang
//	904007005, //= WP Smoke
//	904007007, //= WP Smoke D.
//	904007010, //= Smoke Plus?
//	904007011, //= Medical Kit
//	904007012, //= WP Smoke Plus?
//	904007013, //= FlashBang Plus?
//	904007014, //= Halloween Medical Kit?
//	904007015, //= Chocolate Medical Kit
//	904007017, //= WP Smoke
//	904007021, //= Medical Kit Lotus
//	904007022, //= WP Smoke Plus
//	904007025, //= Medical Kit Opor Ayam
//	904007029, //= Medical Kit PBNC5
//	904007031, //= Medical Kit Easter
//	904007032, //= Medical Kit Lotus2014
//	904007043, //= Medical Kit Kurma
//	904007051, //= Medical Kit PBNC 2015
//	904007059, //= Smoke Pink
//	904007060, //= Smoke Blue
//	904007061 //= Smoke Yellow
//};
//
//// Replace Smoke Byte Hack
//DWORD ThornNormalByte[43]=
//{
//	803007001, //= K-400
//	803007004, //= C-5
//	803007006, //= C-5 D
//	803007008, //= K-413 Dual Grenade D
//	803007009, //= Granat Coklat
//	803007016, //= C-5 EV
//	803007018, //= K-413 G
//	803007019, //= Ketupat Grenade
//	803007020, //= 
//	803007023, //= Lantern/Fanoos Grenade
//	803007024, //= Bread/Ma?amoul Grenade
//	803007026, //= Decoy Bomb
//	803007027, //= M-14 Mine
//	803007028, //= K-479
//	803007030, //= K-400 Easter
//	803007033, //= Soccer Grenade
//	803007034, //= K-413 T
//	803007035, //= M-14 Mine D
//	803007036, //= K-413 Traditional
//	803007037, //= K-413 PC Cafe
//	803007038, //= ShuttleCock Grenade
//	803007039, //= SepakTakraw Grenade
//	803007040, //= M18A1 Claymore
//	803007041, //= CyberIndo K-413 Dual Grenade
//	803007042, //= Goat Grenade
//	803007043, //= K-413 Chocolate
//	803007044, //= C5 CNY-2015
//	803007045, //= K-413 Chocolate
//	803007047, //= K413 Redemption
//	803007052, //= Snowman Grenade
//	803007053, //= Water Bomb
//	803007054, //= K-413 Tiger
//	803007055, //= K-413 Tiger Deluxe
//	803007056, //= C-5 PBWC 2016
//	803007057, //= K-400 Mummy
//	803007058, //= K-413 Blue Diamond
//	803007062, //= Alien Grenade
//	803007063, //= K-413 Puzzle
//	803007064, //= K-413 Russian
//	803007065, //= K-413 Russian Deluxe
//	803007066, //= FootBall Bomb2016
//	803007067, //= C-5 PBIC 2016
//	803007068 //= C-5 PBNC 2016
//};
//
//DWORD CharaByte[47]=
//{
//	1001001003, //= Tarantula
//	1001002004, //= Keen Eyes
//	1001001005, //= Red Bulls
//	1001002006, //= Acid Pool
//	1001001007, //= D-Fox (+20% EXP)
//	1001002008, //= Leopard (+20% EXP)
//	1001002009, //= Hide (+30% Point)
//	1001001010, //= Viper Red (+30% Point)
//	1001001011, //= Reinforced D-Fox
//	1001002012, //= Reinforced Leopard
//	1001001013, //= Reinforced Viper Red
//	1001002014, //= Reinforced Hide
//	1001001015, //= Reinforced Combo D-Fox (+20% EXP)
//	1001002016, //= Reinforced Combo Leopard (+20% EXP)
//	1001001017, //= Reinforced Combo Viper Red (+30% Point)
//	1001002018, //= Reinforced Combo Hide (+30% Point)
//	1001002019, //= Reinforced Acid Poll
//	1001002020, //= Reinforced Keen Eyes
//	1001001021, //= Reinforced Red Bulls
//	1001001022, //= Reinforced Tarantula
//	1001001025, //= D-Fox
//	1001002026, //= Leopard
//	1001002027, //= Hide
//	1001001028, //= Viper Red
//	1001002033, //= Chou
//	1001001034, //= Rica
//	1001002035, //= Reinforced Chou
//	1001001036, //= Reinforced Rica
//	1001002047, //= Keen Eyes GRS
//	1001002048, //= Acid Pol GRS
//	1001001049, //= Tarantula GRS
//	1001001050, //= Red Bulls GRS
//	1001002051, //= Hide Kopassus
//	1001002052, //= Leopard Bope
//	1001002053, //= Hide Cup
//	1001001054, //= World Tarantula
//	1001001055, //= Viper Shadow
//	1001002056, //= Hide Recon
//	1001002057, //= Hide Black
//	1001002058, //= Viper Kopassus
//	1001002062, //= Infected Acid Pol
//	1001002063, //= Infected Keen Eyes
//	1001002064, //= Infected Hide
//	1001002065, //= Infected Leopard
//	1001001295, //= Revolutionist Viper Red (New)
//	1001001283, //= Pirate Tarantula (New)
//	1001002294 //= Hide GIGN (New)
//};
//
//DWORD BeretByte[22]=
//{
//	1103003001, //= Assault Beret
//	1103003002, //= Sniper Beret
//	1103003003, //= Shoting Beret
//	1103003004, //= SMG Beret
//	1103003005, //= Shotgun Beret
//	1103003006, //= Champion Beret
//	1103003007, //= Red Star Beret
//	1103003008, //= Yellow Star Beret
//	1103003009, //= Cross Knife Beret
//	1103003010, //= PBTN Beret
//	1103003011, //= PB Black Beret
//	1103003012, //= PBTN Champion Beret
//	1103003013, //= Kopassus Beret
//	1103003014, //= Bope Beret
//	1103003015, //= PBNC5 Beret
//	1103003016, //= Special General Beret
//	1103003018, //= Sky Beret
//	1103003019, //= Beret Aruna
//	1103003020, //= Beret Strike
//	1103003021, //= Beret Russian
//	1103003022, //= Beret Russian Deluxe
//	1103003023 //= Beret PBNC 2016
//};
//
//DWORD DinosaurusByte[9]=
//{
//	1006003023, //= T-Rex
//	1006003024, //= Raptor Dino
//	1006003029, //= Sting Dino
//	1006003031, //= Acid Dino
//	1006003030, //= Tank Dino
//	1006003032, //= Elite Dino
//	1006003044, //= Mercury Dino (Reinforced Raptor)
//	1006003045, //= Mars Dino (Reinforced Sting)
//	1006003046 //= Vulcan Dino (Reinforced Acid)
//};
//
//DWORD HeadgearByte[9]=
//{
//	1102003001, //= Default Headgear
//	1102003002, //= Normal Headgear
//	1102003003, //= Reinforced Headgear
//	1102003004, //= Heat Headgear
//	1102003005, //= Radar Track
//	1102003006, //= Target Headgear
//	1102003007, //= Reinforced Headgear
//	1102003008, //= Super Headgear
//	1102003009 //= Angel Ring
//};
//
//DWORD MaskByte[224]=
//{
//	1104003001, //= White Mask set
//	1104003002, //= Black Mask Set
//	1104003003, //= Blue Tiger mask set of Russia army
//	1104003004, //= Mask set of Korea marine corps
//	1104003005, //= Desert mask set of France army
//	1104003006, //= Flame pattern mask set
//	1104003007, //= Two tone mask set
//	1104003008, //= Iron mask set
//	1104003009, //= Target mask set
//	1104003010, //= Pumpkin ghost mask set
//	1104003011, //= Jewel pink mask set
//	1104003012, //= Smilegold mask set
//	1104003013, //= Skull mask set
//	1104003014, //= Pierrot mask set
//	1104003015, //= Blue Eye Alien Mask Set
//	1104003016, //= Red Eye Alien Mask Set
//	1104003017, //= Red Cross Mask Set
//	1104003018, //= Jason Mask Set
//	1104003019, //= Panda Mask Set
//	1104003020, //= Egg Mask
//	1104003021, //= Death Mask Set
//	1104003022, //= Argentina Mask Set
//	1104003023, //= Brazil Mask Set
//	1104003024, //= England Mask Set
//	1104003025, //= France Mask Set
//	1104003026, //= Germany Mask Set
//	1104003027, //= Italia Mask Set
//	1104003028, //= Japan Mask Set
//	1104003029, //= S. Africa Mask Set
//	1104003030, //= S. Korea Mask Set
//	1104003031, //= Spain Mask Set
//	1104003032, //= Tiger Mask
//	1104003033, //= Jester_BW Mask
//	1104003034, //= Wrestling Mask
//	1104003035, //= Russia Mask
//	1104003036, //= Ukraine Mask
//	1104003037, //= Belorus Mask
//	1104003038, //= Kazahstan Mask
//	1104003039, //= Red Devil Mask Set
//	1104003040, //= Besiktas FC Mask
//	1104003041, //= Bursapor FC Mask
//	1104003042, //= Fenerbahce FC Mask
//	1104003043, //= Galatasaray FC Mask
//	1104003044, //= Trabzonspor FC Mask
//	1104003045, //= Frail Skull Head Mask
//	1104003046, //= Latin Bahamas
//	1104003047, //= Latin Bolivia
//	1104003048, //= Latin Cayman
//	1104003049, //= Latin Chile
//	1104003050, //= Latin Colombia
//	1104003051, //= Latin Costarica
//	1104003052, //= Latin Honduras
//	1104003053, //= Latin Jamaica
//	1104003054, //= Latin Mexico
//	1104003055, //= Latin Nicaragua
//	1104003056, //= Latin Panama
//	1104003057, //= Latin Paraguay
//	1104003058, //= Latin Dominican
//	1104003059, //= Latin Equador
//	1104003060, //= Latin FR Guyana
//	1104003061, //= Latin Guatemala
//	1104003062, //= Latin Guyana
//	1104003063, //= Latin Haiti
//	1104003064, //= Latin Peru
//	1104003065, //= Latin Puertorico
//	1104003066, //= Latin Suriname
//	1104003067, //= Latin Trinidad
//	1104003068, //= Latin Uruguay
//	1104003069, //= Latin Venezuela
//	1104003070, //= Latin Argentina
//	1104003071, //= Dino Skull Mask
//	1104003072, //= Raptr Mask
//	1104003073, //= Canada Mask
//	1104003074, //= UK Mask
//	1104003075, //= USA Mask
//	1104003076, //= Indonesia Mask
//	1104003077, //= PBTN Memorial Mask
//	1104003078, //= Butterfly Mask
//	1104003079, //= Red Eyes Mask
//	1104003080, //= AZZURRO E BIANCO Mask
//	1104003081, //= AZZURRO E ROSSA Mask
//	1104003082, //= BIANCA E NERA Mask
//	1104003083, //= BIANCO E AZZURRO Mask
//	1104003084, //= BLU E NERA Mask
//	1104003085, //= BLU E ROSSA Mask
//	1104003086, //= CROCE NERA Mask
//	1104003087, //= GIALLO E AMARANTO Mask
//	1104003088, //= NERA BIANCA E ROSSA Mask
//	1104003089, //= NERA E BIANCA Mask
//	1104003090, //= NERA E BLU Mask
//	1104003091, //= NERA E ROSA Mask
//	1104003092, //= NERA GIALLA E BIANCA Mask
//	1104003093, //= ROSSO E GIALLA Mask
//	1104003094, //= STELLA Mask
//	1104003095, //= VIOLA Mask
//	1104003096, //= Smile Cartoon Mask Set (Troll Meme)
//	1104003097, //= Angry Cartoon Mask Set (Respect Meme)
//	1104003098, //= Crazy Cartoon Mask Set (Ffuu Meme
//	1104003099, //= Trex Headgear
//	1104003100, //= Trojan Mask
//	1104003101, //= Frail Skull Gold Mask
//	1104003102, //= Besiktas FC Mask 2012
//	1104003103, //= Bursapor FC Mask 2012
//	1104003104, //= Fenerbahce FC Mask 2012
//	1104003105, //= Galatasaray FC Mask 2012
//	1104003106, //= Trabzonspor FC Mask 2012
//	1104003107, //= IC'12 Mask
//	1104003108, //= Blue tiger mask set of Russia army EV
//	1104003109, //= Mask set of Korea marine corps EV
//	1104003110, //= Desert mask set of France army EV
//	1104003111, //= Black Mask Set EV
//	1104003112, //= White Mask set EV
//	1104003113, //= Gatotkaca Mask
//	1104003114, //= Blue tiger mask set of Russian army
//	1104003115, //= Mask set of Korea marine corps
//	1104003116, //= Desert mask set of France army
//	1104003117, //= Gatotkaca Gold Mask
//	1104003118, //= PBSC Mask
//	1104003119, //= PBTN DIGITAL MASK
//	1104003120, //= Death Mask Set (GW)
//	1104003121, //= Garena Gold Mask
//	1104003122, //= Garena Red Mask
//	1104003123, //= Garena White Mask
//	1104003124, //= Black Snake Mask
//	1104003125, //= Egg Tarantula Mask
//	1104003126, //= GSL Mask
//	1104003127, //= Egg RedBulls Mas
//	1104003128, //= PBNC4 Mask
//	1104003129, //= PBIC2013 Mask
//	1104003130, //= PBSC2013 Mask
//	1104003131, //= Sheep Mask (Topeng Kambing)
//	1104003132, //= Zombie Mask
//	1104003133, //= Azerbaijan Mas
//	1104003134, //= LATIN3 Mask
//	1104003135, //= LATIN3 Premium Mask
//	1104003136, //= Unicorn Mask
//	1104003137, //= 1st Anniversary Mask
//	1104003138, //= Mask Soccer Eagle
//	1104003139, //= Mask Soccer Storm
//	1104003140, //= Mask Soccer Lion
//	1104003141, //= Mask Soccer Canary
//	1104003142, //= WC 2014 Argentina Mask
//	1104003143, //= WC 2014 Brazil Mask
//	1104003144, //= WC 2014 Chile Mask
//	1104003145, //= WC 2014 Colombia Mas
//	1104003146, //= WC 2014 Equador Mask
//	1104003147, //= WC 2014 England Mask
//	1104003148, //= WC 2014 France Mask
//	1104003149, //= WC 2014 Germany Mask
//	1104003150, //= WC 2014 Italy Mask
//	1104003151, //= WC 2014 Japan Mask
//	1104003152, //= WC 2014 Korea Mask
//	1104003153, //= WC 2014 Spain Mask
//	1104003154, //= WC 2014 U.S.A Mask
//	1104003155, //= WC 2014 Uruguay Mask
//	1104003156, //= WC 2014 Honduras Mask
//	1104003157, //= WC 2014 Mexico Mask
//	1104003158, //= WC 2014 CostaRica Mask
//	1104003159, //= GSL 2014 Mask
//	1104003160, //= WC 2014 Greece Mask
//	1104003161, //= WC 2014 Netherlands Mask
//	1104003162, //= WC 2014 Belgium Mask
//	1104003163, //= WC 2014 Bosnia and Herzegovina Mask
//	1104003164, //= WC 2014 Switzerland Mask
//	1104003165, //= WC 2014 Croatia Mask
//	1104003166, //= WC 2014 Portugal Mask
//	1104003167, //= WC 2014 Ghana Mask
//	1104003168, //= WC 2014 Nigeria Mask
//	1104003169, //= WC 2014 Algeria Mask
//	1104003170, //= WC 2014 Cameroon Mask
//	1104003171, //= WC 2014 Cote d'Ivoire Mask
//	1104003172, //= WC 2014 Iran Mask
//	1104003173, //= WC 2014 Australia Mask
//	1104003174, //= WC 2014 Russia Mask
//	1104003176, //= Egg KeenEyes Mask
//	1104003176, //= Egg AcidPol Mask
//	1104003177, //= Mask Midnight
//	1104003178, //= Brazuca Mask
//	1104003179, //= Indonesia Mask (GW)
//	1104003180, //= Mask Sol Premium
//	1104003182, //= PBIC2014 Mask
//	1104003183, //= Mask NonLogo PBSC
//	1104003184, //= Mask NonLogo LATIN3
//	1104003185, //= Mask NonLogo LATIN3 Premium
//	1104003186, //= Mask NonLogo Midnight
//	1104003189, //= MASK GRS2
//	1104003195, //= Mask Songkran
//	1104003201, //= Mask Madness 
//	1104003202, //= Mask Madness Premium
//	1104003204, //= Mask Training Camp
//	1104003205, //= Mask Training Camp Premium
//	1104003209, //= Mask PBIC 2015 Premium
//	1104003210, //= Mask PBIC 2015 
//	1104003214, //= Mask Hallowen
//	1104003222, //= Mask Arena
//	1104003223, //= Mask Arena Deluxe
//	1104003224, //= Mask Cupid
//	1104003225, //= Mask Serpent
//	1104003227, //= Mask GRS3
//	1104003228, //= Mask PBGC 2016
//	1104003229, //= Mask GSL 2016
//	1104003230, //= Mask Tiger Deluxe
//	1104003231, //= Mask Midnight 2
//	1104003232, //= Mask Joker
//	1104003233, //= Mask E-Sports 2
//	1104003234, //= Mask Mummy
//	1104003235, //= Mask Aruna
//	1104003236, //= Mask Demonic
//	1104003237, //= Mask Blue Diamond
//	1104003238, //= Mask Puzzle
//	1104003241, //= Mask Liberty
//	1104003242, //= PBIC2016 Mask
//	1104003243, //= PBIC2016 Half Mask
//	1104003244, //= Mask PBTC2016
//	1104003245, //= Mask PBST 2016
//	1104003247, //= Mask Furious
//	1104003248, //= Mask Clown Brazil
//	1104003249, //= Mask Skull Half
//	1104003250, //= Mask Chain
//	1104003251, //= Mask Phantom
//	1104003253, //= Mask Night Hunter
//	1104003254, //= Mask Eagle '17
//	1104003255, //= Mask Lion '17
//	1104003256 //= Mask Canary '17
//};
//
//DWORD ITEMByte[38]=
//{
//	100001030, //10% EXP UP
//	100002030, //30% EXP UP
//	100003030, //50% EXP UP
//	100004030, //30% points
//	100005000, //Clan Name Recolor
//	100006000, //Mudar Cor Name
//	100007030, //Respawn 30%
//	100008030, //Muni??o 40%
//	100009030, //Rank UP
//	100010030, //Nickname temporary
//	100011030, //Bom Perderdor
//	100012030, //Clan EXP 150%
//	100013030, //change Color sight
//	100014030, //change Color sight
//	100015030, //Color Chat
//	100017030, //Enemy Drop
//	100018030, //EXP 100% (12:00-15:00)
//	100019030, //EXP 100%(15:00-18:00)
//	100020030, //EXP 100%(18:00-21:00)
//	100021030, //EXP 100%(21:00-00:00)
//	100022030, //Gold 100%(12:00-15:00)
//	100023030, //Gold 100%(15:00-18:00)
//	100024030, //Gold 100%(18:00-21:00)
//	100025030, //Gold 100%(21:00-00:00)
//	100026030, //Change Speed
//	100027030, //reload 20%
//	100028030, //Hiper HP +10%
//	100029030, //invincible +1 sec
//	100030030, //Colete +5%
//	100031030, //Iron bullet
//	100032030, //Hallow Point
//	100033030, //Anti Flash BanG Mask
//	100034030, //C4 Speed Up
//	100035030, //Explosive Extra
//	100036030, //Hallow Point Plus
//	100037030, //EXP 200%
//	100038030, //GOLD 200%
//	100040030 //Life 5%
//};
//
//DWORD OtherItemByte[6]=
//{
//	105009016, //= SupplyBase AMMO
//	104009003, //= SupplyBase
//	104009017, //= M197
//	104009018, //= Domination Object 2
//	104009019, //= Domination Object 2
//	104011010 //= Compound Bow Black Grenade Shell
//};
//
//DWORD CompoundBowByte[6]=
//{
//	100026001, //= Compound Bow Blue
//	100026002, //= Compound Bow
//	100026003, //= Compound Bow Silver
//	100026004, //= Compound Bow Gold
//	100026005, //= Compound Bow Blue New
//	100026006 //= Compound Bow B
//};

////STR_TBL_DESIGNATION_APPENDIX_BADGECOUNT_TEXT Tittle Count : -4 . +4 +8 +C +10
//char* MapHackByte[]=
//{
//	"\x00",//Random Map
//	"\x08",//Portacaba
//	"\x10",//RedRock
//	"\x18",//Library
//	"\x20",//M-Station
//	"\x28",//Midnight Zone
//	"\x30",//Uptown
//	"\x38",//Burning Hall
//	"\x40",//D-Squad
//	"\x48",//Crackdown
//	"\x50",//Saints Mansion
//	"\x58",//Eastern Road
//	"\x60",//Downtown
//	"\x68",//Luxville
//	"\x70",//Blow City
//	"\x78",//Stormtube
//	"\x80",//Giran
//	"\x88",//Breakdown
//	"\x90",//Training Camp
//	"\x98",//Sentry Base
//	"\xA0",//Desert Camp
//	"\xA8",//Kick Point
//	"\xB0",//Face Rock
//	"\xB8",//Supply Base
//	"\xC0",//SandStorm
//	"\xC8",//Downtown
//	"\xD0",//Luxville
//	"\xD8",//Outpost
//	"\xE0",//Blow City
//	"\xE8",//Stormtube
//	"\xF0",//Sentry Base
//	"\xF8",//Hospital
//	"\x01",//Midtown
//	"\x09",//MALL
//	"\x11",//SandStorm
//	"\x19",//Breakdown
//	"\x21",//Giran Beta A
//	"\x29",//Giran
//	"\x31",//Helispot
//	"\x39",//Black Phanter
//	"\x41",//Breeding Nest
//	"\x49",//D Uptown
//	"\x51",//Dino Breakdown
//	"\x59",//DeatTown
//	"\x61",//No Stage name [Tutorial]
//	"\x69",//Mall
//	"\x71",//Safari
//	"\x79",//DragonAlley
//	"\x81",//Machu Picchu
//	"\x89",//Cargo Ship
//	"\x91"//Two Towers
//};
//
//char* ModeHackByte[]=
//{
//	"\x00",//Random Mode
//	"\x08",//Deat Match
//	"\x10",//Bom Misions
//	"\x18",//Destroy
//	"\x20",//Elyminate
//	"\x28",//Defense Misions
//};
//
//char* WeaponModeHackByte[]=
//{
//	"\x00",//NULL
//	"\x78",//Weapon All
//	"\x7A",//Weapon Shotgun 
//	"\x51",//Weapon Sniper 
//};

/*-------------------------------------------------------------------------------------------------------------------*/
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