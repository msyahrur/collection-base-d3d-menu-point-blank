//Created by DANI XCT / WA DANI IDI/MENU XXN PART 2
#define BLACK			D3DCOLOR_ARGB(150, 000, 000, 000)
#define TRANSPARANT		D3DCOLOR_ARGB(140, 000, 000, 000)
#define WHITE			D3DCOLOR_ARGB(255, 255, 255, 255)
#define RED				D3DCOLOR_ARGB(255, 255, 000, 000)
#define GREEN			D3DCOLOR_ARGB(255, 000, 255, 000)
#define YELLOW			D3DCOLOR_ARGB(255, 255, 255, 000) 
#define ORANGE			D3DCOLOR_ARGB(255, 255, 125, 000)
#define BLUE			D3DCOLOR_ARGB(255, 000, 000, 255)
#define GREY			D3DCOLOR_ARGB(255, 128, 128, 128)
#define PINK			D3DCOLOR_XRGB(255, 000, 255)
#define SKYBLUE			D3DCOLOR_ARGB(255, 0,   180, 255)
#define DEEPSKYBLUE     D3DCOLOR_ARGB(255, 30,  144, 255)
#define LIME			D3DCOLOR_ARGB(255, 198, 255,   0)
#define AQUA            D3DCOLOR_ARGB(255, 0, 180, 255)

int				RainbowR		= 100;
int				RainbowG		= 100;
int				RainbowB		= 100;
float			RainbowTexts	= 100;
#define			RAINBOW			D3DCOLOR_ARGB(255, RainbowR, RainbowG, RainbowB)

void RainBow(){
	if(RainbowTexts!=100)
	{RainbowR-=2,RainbowG-=3,RainbowB-=3;}
	if(RainbowTexts!=255)
	{RainbowR+=2,RainbowG+=3,RainbowB+=4;}
}