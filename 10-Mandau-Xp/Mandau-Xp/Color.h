//Bagus Tuyul
#define White				D3DCOLOR_ARGB(255, 255, 255, 255)
#define Green				D3DCOLOR_ARGB(255, 000, 255, 000)
#define Blue				D3DCOLOR_ARGB(255, 000, 000, 255) 
#define SkyBlue				D3DCOLOR_ARGB(255, 000, 180, 255)
#define Yellow				D3DCOLOR_ARGB(255, 255, 255, 000) 
#define Orange				D3DCOLOR_ARGB(255, 255, 125, 000)
#define Red					D3DCOLOR_ARGB(255, 255, 000, 000)
#define Black				D3DCOLOR_ARGB(255, 000, 000, 000)
#define Transparant			D3DCOLOR_ARGB(170, 000, 000, 000)
#define Purple				D3DCOLOR_ARGB(255, 125, 000, 125)
#define Grey				D3DCOLOR_ARGB(255, 128, 128, 128)
#define LGrey				D3DCOLOR_ARGB(255, 174, 174, 174)  
#define SkyBlue				D3DCOLOR_ARGB(255, 000, 180, 255)
#define DeepSkyBlue			D3DCOLOR_ARGB(190,  30, 144, 255)
#define Pink				D3DCOLOR_XRGB(255, 000, 255)

int				RainbowR		= 100;
int				RainbowG		= 100;
int				RainbowB		= 100;
float			RainbowTexts	= 100;
#define	RainbowTextTest D3DCOLOR_ARGB(255, RainbowR, RainbowG, RainbowB)

void DrawRainBow()
{
	if(RainbowTexts!=100)
	{RainbowR-=2,RainbowG-=3,RainbowB-=3;}
	if(RainbowTexts!=255)
	{RainbowR+=2,RainbowG+=3,RainbowB+=4;}
}