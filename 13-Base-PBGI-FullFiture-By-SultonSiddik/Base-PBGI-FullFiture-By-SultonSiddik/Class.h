/*cClass.h PBHacks Last Edit By Muhammad Zaki Mubarak*/

/*-------------------------------------------------------------------------------------------------------------------*/
#include <windows.h>
#include "Logger.h"

/*-------------------------------------------------------------------------------------------------------------------*/
#define WHITE			D3DCOLOR_ARGB(255, 255, 255, 255)
#define RED				D3DCOLOR_ARGB(255, 245, 000, 000)
#define GREEN			D3DCOLOR_ARGB(255, 000, 255, 000)
#define BLUE			D3DCOLOR_ARGB(255, 000, 000, 255) 
#define BLACK			D3DCOLOR_ARGB(150, 000, 000, 000)
#define mBLACK			D3DCOLOR_ARGB(100, 000, 000, 205)
#define PURPLE			D3DCOLOR_ARGB(255, 125, 000, 255) 
#define GREY			D3DCOLOR_ARGB(255, 128, 128, 128) 
#define DEEPSKYBLUE     D3DCOLOR_ARGB(190,  30, 144, 255)
#define PINK			D3DCOLOR_XRGB(255,   0, 255)
#define YELLOW			D3DCOLOR_ARGB(255, 255, 255, 000) 
#define ORANGE			D3DCOLOR_ARGB(255, 255, 125, 000)
#define WHITE2			D3DCOLOR_ARGB(100, 255, 255, 255)
#define RED2			D3DCOLOR_ARGB(255, 255, 000, 000)
#define GREEN2			D3DCOLOR_ARGB(100, 000, 255, 000)
#define BLUE2			D3DCOLOR_ARGB(100, 000, 000, 255) 
#define BLACK2			D3DCOLOR_ARGB(100, 000, 000, 000)
#define PURPLE2			D3DCOLOR_ARGB(100, 125, 000, 255) 
#define GREY2			D3DCOLOR_ARGB(100, 128, 128, 128) 
#define YELLOW2			D3DCOLOR_ARGB(100, 255, 255, 000) 
#define ORANGE2			D3DCOLOR_ARGB(100, 255, 125, 000)
#define SKYBLUE			D3DCOLOR_ARGB(255,   0, 180, 255)
#define LGRAY		    D3DCOLOR_ARGB(255, 174, 174, 174)  
#define DARKBLUE		D3DCOLOR_ARGB(255,   0,   0, 153) 
#define LIGHTBLUE		D3DCOLOR_ARGB(255,  19,  84, 199) 
#define MAROON			D3DCOLOR_ARGB(255, 142,  30, 0)
#define POLICE          D3DCOLOR_ARGB(255, 125, 160, 200)
#define TERORI          D3DCOLOR_ARGB(255, 225, 100, 100)
#define DARK			D3DCOLOR_ARGB(255, 047, 047, 047)
#define MenuGREY        D3DCOLOR_ARGB(255,  30,  30,  30)
#define DARKGREY        D3DCOLOR_ARGB(255,  62,  62,  62)
#define GOLD2			D3DCOLOR_ARGB(255, 238, 201,   0) 
#define GRE2			D3DCOLOR_ARGB(200,  27,  27,  27) 

/*-------------------------------------------------------------------------------------------------------------------*/
#define Green				D3DCOLOR_ARGB(255, 000, 255, 000)
#define White				D3DCOLOR_ARGB(255, 255, 255, 255)
#define Red					D3DCOLOR_ARGB(255, 255, 000, 000)
#define Blue				D3DCOLOR_ARGB(255, 000, 000, 255)
#define Black				D3DCOLOR_ARGB(255, 000, 000, 000)
#define Black_transparant	D3DCOLOR_ARGB(200, 000, 000, 000)
#define Purple				D3DCOLOR_ARGB(255, 125, 000, 125)
#define Yellow				D3DCOLOR_ARGB(255, 255, 255, 000)
#define Orange				D3DCOLOR_ARGB(255, 255, 125, 000)
#define Grey				D3DCOLOR_ARGB(255, 128, 128, 128)
#define DarkerBlue			D3DCOLOR_ARGB(255, 000, 000, 153)
#define Cyan				D3DCOLOR_ARGB(255, 000, 032, 032)
#define Custom				D3DCOLOR_ARGB(225, 000, 120, 120)
#define Maroon				D3DCOLOR_ARGB(255, 128,   0,   0)

/*-------------------------------------------------------------------------------------------------------------------*/
#define TextOn				D3DCOLOR_ARGB(255, 224, 136,  60)
#define ButtonSelect1		D3DCOLOR_ARGB(255, 238, 201,   0) 
#define ButtonSelect2		D3DCOLOR_ARGB(255, 215, 201,   0)
#define ButtonOff			D3DCOLOR_ARGB(255,  81,  81,  81)
#define ButtonOff2			D3DCOLOR_ARGB(100,  81,  81,  81)
#define ButtonOn			D3DCOLOR_ARGB(255, 124,   0,   0)
#define ButtonOn2			D3DCOLOR_ARGB(100, 124,   0,   0)


enum Colors : D3DCOLOR{
gainsboro				= 0xF5F5F5,
AliceBlue				= 0xFFF0F8FF,
AntiqueWhite			= 0xFFFAEBD7,
Aqua					= 0xFF00FFFF,
Aquamarine				= 0xFF7FFFD4,
Azure					= 0xFFF0FFFF,
Beige					= 0xFFF5F5DC,
Bisque					= 0xFFFFE4C4,
BlanchedAlmond			= 0xFFFFEBCD,
BlueViolet				= 0xFF8A2BE2,
Brown					= 0xFFA52A2A,
BurlyWood				= 0xFFDEB887,
CadetBlue				= 0xFF5F9EA0,
Chartreuse				= 0xFF7FFF00,
Chocolate				= 0xFFD2691E,
Coral					= 0xFFFF7F50,
CornflowerBlue			= 0xFF6495ED,
Cornsilk				= 0xFFFFF8DC,
Crimson					= 0xFFDC143C,
//Cyan					= 0xFF00FFFF,
DarkBlue				= 0xFF00008B,
DarkCyan				= 0xFF008B8B,
DarkGoldenrod			= 0xFFB8860B,
DarkGray				= 0xFFA9A9A9,
DarkGreen				= 0xFF006400,
DarkKhaki				= 0xFFBDB76B,
DarkMagenta				= 0xFF8B008B,
DarkOliveGreen			= 0xFF556B2F,
DarkOrange				= 0xFFFF8C00,
DarkOrchid				= 0xFF9932CC,
DarkRed					= 0xFF8B0000,
DarkSalmon				= 0xFFE9967A,
DarkSeaGreen			= 0xFF8FBC8B,
DarkSlateBlue			= 0xFF483D8B,
DarkSlateGray			= 0xFF2F4F4F,
DarkTurquoise			= 0xFF00CED1,
DarkViolet				= 0xFF9400D3,
DeepPink				= 0xFFFF1493,
DeepSkyBlue				= 0xFF00BFFF,
DimGray					= 0xFF696969,
DodgerBlue				= 0xFF1E90FF,
Firebrick				= 0xFFB22222,
FloralWhite				= 0xFFFFFAF0,
ForestGreen				= 0xFF228B22,
Fuchsia					= 0xFFFF00FF,
Gainsboro				= 0xFFDCDCDC,
GhostWhite				= 0xFFF8F8FF,
GOLD					= 0xFFFFD700,
Goldenrod				= 0xFFDAA520,
GreenYellow				= 0xFFADFF2F,
Honeydew				= 0xFFF0FFF0,
HotPink					= 0xFFFF69B4,
IndianRed				= 0xFFCD5C5C,
Indigo					= 0xFF4B0082,
Ivory					= 0xFFFFFFF0,
Khaki					= 0xFFF0E68C,
Lavender				= 0xFFE6E6FA,
LavenderBlush			= 0xFFFFF0F5,
LawnGreen				= 0xFF7CFC00,
LemonChiffon			= 0xFFFFFACD, 
AQUAMARINE				= 0x7FFFD4,
LightBlue				= 0xFFADD8E6,
LightCoral				= 0xFFF08080,
LightCyan				= 0xFFE0FFFF,
LightGoldenrodYellow	= 0xFFFAFAD2,
LightGray				= 0xFFD3D3D3,
LightGreen				= 0xFF90EE90,
LightPink				= 0xFFFFB6C1,
FahmiTest				= 0xE8FFFF,
LightSalmon				= 0xFFFFA07A,
LightSeaGreen			= 0xFF20B2AA,
LightSkyBlue			= 0xFF87CEFA,
LightSlateGray			= 0xFF778899,
LightSteelBlue			= 0xFFB0C4DE,
LightYellow				= 0xFFFFFFE0,
Lime					= 0xFF00FF00,
LimeGreen				= 0xFF32CD32,
Linen					= 0xFFFAF0E6,
//Magenta					= 0xFFFF00FF,
//Maroon					= 0xFF800000,
MediumAquamarine		= 0xFF66CDAA,
MediumBlue				= 0xFF0000CD,
MediumOrchid			= 0xFFBA55D3,
MediumPurple			= 0xFF9370DB,
MediumSeaGreen			= 0xFF3CB371,
MediumSlateBlue			= 0xFF7B68EE,
MediumSpringGreen		= 0xFF00FA9A,
MediumTurquoise			= 0xFF48D1CC,
MediumVioletRed			= 0xFFC71585,
MidnightBlue			= 0xFF191970,
MintCream				= 0xFFF5FFFA,
MistyRose				= 0xFFFFE4E1,
Moccasin				= 0xFFFFE4B5,
NavajoWhite				= 0xFFFFDEAD,
Navy					= 0xFF000080,
OldLace					= 0xFFFDF5E6,
Olive					= 0xFF808000,
OliveDrab				= 0xFF6B8E23,
//Orange					= 0xFFFFA500,
OrangeRed				= 0xFFFF4500,
Orchid					= 0xFFDA70D6,
PaleGoldenrod			= 0xFFEEE8AA,
PaleGreen				= 0xFF98FB98,
PaleTurquoise			= 0xFFAFEEEE,
PaleVioletRed			= 0xFFDB7093,
PapayaWhip				= 0xFFFFEFD5,
PeachPuff				= 0xFFFFDAB9,
Peru					= 0xFFCD853F,
//Pink					= 0xFFFFC0CB,
Plum					= 0xFFDDA0DD,
PowderBlue				= 0xFFB0E0E6,
RosyBrown				= 0xFFBC8F8F,
BlueRoyal				= 0xFF4169E1,
SaddleBrown				= 0xFF8B4513,
Salmon					= 0xFFFA8072,
SandyBrown				= 0xFFF4A460,
SeaGreen				= 0xFF2E8B57,
SeaShell				= 0xFFFFF5EE,
Sienna					= 0xFFA0522D,
Silver					= 0xFFC0C0C0,
SkyBlue					= 0xFF87CEEB,
SlateBlue				= 0xFF6A5ACD,
SlateGray				= 0xFF708090,
Snow					= 0xFFFFFAFA,
SpringGreen				= 0xFF00FF7F,
SteelBlue				= 0xFF4682B4,
Tan						= 0xFFD2B48C,
Teal					= 0xFF008080,
Thistle					= 0xFFD8BFD8,
Tomato					= 0xFFFF6347,
Transparent				= 0x00FFFFFF,
Turquoise				= 0xFF40E0D0,
Violet					= 0xFFEE82EE,
Wheat					= 0xFFF5DEB3,
WhiteSmoke				= 0xFFF5F5F5,
YellowGreen				= 0xFF9ACD32,
};
/*-------------------------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------------------------------------*/
LPD3DXLINE g_pLine2  = NULL; //D3D Line
/*LPD3DXFONT g_pFont  = NULL;*/ //D3D Font
LPD3DXLINE pLine    = NULL;
D3DVIEWPORT9    g_ViewPort2;


float ScreenCenterX2, ScreenCenterY2 = 0;




/*********** GLOBAL VARIABLE *************/
int MyCurrentWeaponIndex;
int BoneIndexSelector;
int UseTransparentMenu = 1;
int MoveMenu = 0;
int MaxItem = 10;

D3DXVECTOR2 MenuPos;
LPDIRECT3DDEVICE9 npDevice2, pGDevice; 

/*********** GLOBAL FUNCTIONS *************/
//bool IsInBattle();
bool GetPlayerVisibleStatus(int ActorIndex, int TargetIndex, int BoneTargetIndex);
float DistanceBetweenVector( D3DXVECTOR3 VecA, D3DXVECTOR3 VecB );
DWORD GetOriginalEndScene();
DWORD GetOriginalDIP();


/*********** GLOBAL STRUCT *************/



/*-------------------------------------------------------------------------------------------------------------------*/
static LPDIRECT3DDEVICE9 pDevice;



