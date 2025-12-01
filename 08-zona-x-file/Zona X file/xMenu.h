#ifndef _CMENU_H
#define _CMENU_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3dx9.h>

#ifndef D3DFONT_RIGHT
#define D3DFONT_RIGHT		0x0008
#endif

#define 	MENUMAXITEMS	100
#define 	MENUFOLDER		1
#define 	MENUTEXT		2
#define 	MENUITEM		3
#define		MENUCAT			4

typedef struct {
  int  typ;		
  char *txt;	
  char **opt;	
  int  *var;	  
  int  maxvalue;
} tMENU;

class D3D9Menu
{
public:
	D3D9Menu(char *Title = 0)
	{
		Mtitle=Title;	 
		Mpos=0;			
		Mmax=0;		
		Mxofs =150.0f;	// jarak text ke samping
		Mysize=16.0f;	// jarak text ke atas
		aktifmenu=1;
		MENU=(tMENU **)malloc(4*MENUMAXITEMS);
		for (int i=0; i<MENUMAXITEMS; i++) MENU[i]=(tMENU *)malloc(sizeof(tMENU));
	}
	~D3D9Menu() {
		for (int i=0; i<MENUMAXITEMS; i++) free(MENU[i]);
		free(MENU);
	}

	int		Mmax;
	int		aktifmenu;
	tMENU		**MENU;
	void AddItem(char *txt, char **opt, int *var, int maxvalue);
	void AddFolder(char *txt, char **opt, int *var, int maxvalue);
	void AddCategory(char *txt, char **opt, int *var, int maxvalue);
	void MenuAdd(char *txt, char **opt, int *var, int maxvalue, int typ);
	void MenuShow(float x, float y, LPDIRECT3DDEVICE9 pDevice);
	void Crosshair(LPDIRECT3DDEVICE9 pDevice, D3DCOLOR Color);
	void AddText(char *txt, char *opt);
	void MenuNav(void);
	void DrawTextR(int x,int y,DWORD color,char *text);
	void DrawTextF(int x,int y,DWORD color,char *text);
	void DrawTextL(int x,int y,DWORD color,char *text);
	void DrawTextC(int x,int y,DWORD color,char *text);
	void DrawBox(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h);
	void FontCreate(LPDIRECT3DDEVICE9 pDevice);

private:
	
	char	*Mtitle;
	int 	Mpos;
	float	Mxofs;	  
	float	Mysize;	

};
#endif
