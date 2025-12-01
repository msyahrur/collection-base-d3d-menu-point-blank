//----------------------------------------------------------------------------------------
//---------------------------------------------------------// [MRC]
//----------------------------------------------------------------------------------------
#include <windows.h>
//----------------------------------------------------------------------------------------
int				RainbowR		= 100;
int				RainbowG		= 100;
int				RainbowB		= 100;
float			RainbowTexts	= 100;
#define			RainbowTextTest D3DCOLOR_ARGB(255, RainbowR, RainbowG, RainbowB)
//----------------------------------------------------------------------------------------
void RainBow(){
	if(RainbowTexts!=100)
	{RainbowR-=2,RainbowG-=3,RainbowB-=3;}
	if(RainbowTexts!=255)
	{RainbowR+=2,RainbowG+=3,RainbowB+=4;}
	}
//----------------------------------------------------------------------------------------
#define Transparent		D3DCOLOR_ARGB(0,   0,   0,     0)
#define GOLD			D3DCOLOR_ARGB(255, 215, 0,     1)
#define Gold			D3DCOLOR_ARGB(255, 255, 215, 000)
//----------------------------------------------------------------------------------------
#define AQUA			D3DCOLOR_ARGB(255, 0,   255, 255)  
#define SKYBLUE			D3DCOLOR_ARGB(255, 0,   180, 255)
//----------------------------------------------------------------------------------------
#define WHITE			D3DCOLOR_ARGB(255, 255, 255, 255)
#define WHITE2			D3DCOLOR_ARGB(100, 255, 255, 255)
#define WWHITE3			D3DCOLOR_ARGB(255, 255, 255, 249)
#define	DARKWHITE		D3DCOLOR_ARGB(255, 135, 135, 135)
#define	DARKWHITE2		D3DCOLOR_ARGB(255, 50,  50,  50)
//----------------------------------------------------------------------------------------
#define RED				D3DCOLOR_ARGB(255, 245, 000, 000)
#define RED2			D3DCOLOR_ARGB(255, 255, 000, 000)
#define RED3			D3DCOLOR_RGBA(255, 000, 000, 255)
//----------------------------------------------------------------------------------------
#define GREEN			D3DCOLOR_ARGB(255, 000, 255, 000)
#define GREEN2			D3DCOLOR_ARGB(100, 000, 255, 000)
#define GREEN3			D3DCOLOR_ARGB(255, 127, 255, 000)
#define GREEN4			D3DCOLOR_RGBA(000, 255, 000, 255)
#define LGREEN			D3DCOLOR_ARGB(51,  255, 0,     1)
#define LIME			D3DCOLOR_ARGB(255, 198, 255,   0)
//----------------------------------------------------------------------------------------
#define BLUE			D3DCOLOR_ARGB(255, 000, 000, 255)
#define DBLUE			D3DCOLOR_ARGB(30,  144, 255,   1)
#define BLUEMAZAY       D3DCOLOR_ARGB(255, 21,  56,  128)
#define LIGHTBLUE		D3DCOLOR_ARGB(255, 19,  84,  199) 
#define DEEPSKYBLUE     D3DCOLOR_ARGB(190, 30,  144, 255)
#define dBlue			D3DCOLOR_RGBA(000, 000, 255, 255)
#define BLUE2			D3DCOLOR_ARGB(100, 000, 000, 255) 
#define DARKBLUE		D3DCOLOR_ARGB(255, 0,   0,   153) 
#define LIGHTBLUE		D3DCOLOR_ARGB(255, 19,  84,  199) 
//----------------------------------------------------------------------------------------
#define BLACK			D3DCOLOR_ARGB(100, 000, 000, 000)
#define mBLACK			D3DCOLOR_ARGB(100, 000, 000, 205)
#define Black			D3DCOLOR_ARGB(255, 000, 000, 000)
#define dBlack			D3DCOLOR_RGBA(128, 128, 128, 255)
#define DEEPSKYBLUE     D3DCOLOR_ARGB(190, 30,  144, 255)
//----------------------------------------------------------------------------------------
#define PURPLE			D3DCOLOR_ARGB(255, 125, 000, 255) 
#define Purple			D3DCOLOR_ARGB(255, 128, 000, 128)
#define dPurple			D3DCOLOR_RGBA(125, 000, 255, 255)
#define PURPLE2			D3DCOLOR_ARGB(100, 125, 000, 255) 
//----------------------------------------------------------------------------------------
#define GREY			D3DCOLOR_ARGB(255, 128, 128, 128) 
#define Grey			D3DCOLOR_ARGB(255, 112, 112, 112)
#define dGrey			D3DCOLOR_RGBA(128, 128, 128, 255)
#define dLightGrey		D3DCOLOR_RGBA(188, 188, 188, 255)
#define MenuGREY        D3DCOLOR_ARGB(255,  30,  30,  30)
#define DARKGREY        D3DCOLOR_ARGB(255,  62,  62,  62)
#define GREY2			D3DCOLOR_ARGB(100, 128, 128, 128) 
//----------------------------------------------------------------------------------------
#define PINK			D3DCOLOR_XRGB(255, 0, 255)
#define Pink			D3DCOLOR_ARGB(255, 255, 192, 203)
//----------------------------------------------------------------------------------------
#define YELLOW			D3DCOLOR_ARGB(255, 255, 255, 000) 
#define Yellow			D3DCOLOR_ARGB(255, 255, 255,  51)
#define dYellow			D3DCOLOR_RGBA(255, 255, 000, 255)
#define YELLOW2			D3DCOLOR_ARGB(100, 255, 255, 000) 
//----------------------------------------------------------------------------------------
#define ORANGE			D3DCOLOR_ARGB(255, 255, 125, 000)
#define Orange			D3DCOLOR_ARGB(255, 255, 140, 000)
#define dOrange			D3DCOLOR_RGBA(255, 125, 000, 255)
#define ORANGE2			D3DCOLOR_ARGB(100, 255, 125, 000)
//----------------------------------------------------------------------------------------
#define DARK			D3DCOLOR_ARGB(255, 047, 047, 047)
#define TBlack			D3DCOLOR_ARGB(128, 000, 000, 000)
#define BTBlack			D3DCOLOR_ARGB(255, 15,  72,  127)
#define BBlack			D3DCOLOR_ARGB(255, 54,  54,   54)
//----------------------------------------------------------------------------------------
//---------------------------------------------------------// [MRC]
//----------------------------------------------------------------------------------------