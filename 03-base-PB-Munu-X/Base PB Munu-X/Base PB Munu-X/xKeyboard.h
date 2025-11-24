//--------------------------------------------------------------------------//
void MenuX_Standar(LPDIRECT3DDEVICE9 pDevice){
Current = 1;
Folder("Visual Grafix",Moptfolder,MenuFolder[0],2);
if(MenuFolder[0]){
Item("WallHack"		, SwiftONOF		,Nh_Teknology32	,2 ,pDevice);
Item("Chams Teror"	, optColor2		,Nh_Teknology30	,10,pDevice);
Item("Chams Swat"	, optColor2		,Nh_Teknology31 ,10,pDevice);
Item("Remove Smoke"	, SwiftONOF		,Nh_Teknology33 ,2 ,pDevice);
Item("CrossHair"	, optcrosshair	,Nh_Teknology34 ,3 ,pDevice);
}
//--------------------------------------------------------------------------//
Folder("ESP Fiture" ,Moptfolder,MenuFolder[1],2);
if(MenuFolder[1]){
Item("ESP Line"		, SwiftONOF		,Nh_Teknology1	,2 ,pDevice);
Item("ESP Health"	, SwiftONOF		,Nh_Teknology2	,2 ,pDevice);
Item("ESP Bone"		, SwiftONOF		,Nh_Teknology3	,2 ,pDevice);
Item("ESP Box"		, SwiftONOF		,Nh_Teknology26	,2 ,pDevice);
Item("ESP Observer"	, SwiftONOF		,Nh_Teknology27	,2 ,pDevice);
}
//--------------------------------------------------------------------------//
Folder("AIM Fiture" ,Moptfolder,MenuFolder[2],2);
if(MenuFolder[2]){
Item("AIM Bullet"	, SwiftONOF		,Nh_Teknology8,2 ,pDevice);
Item("Target AIM"	, MopTarget		,Nh_Teknology7,2 ,pDevice);
Item("Target Random", SwiftONOF		,Nh_NEWAIM	  ,2 ,pDevice);
Item("WPSmoke Killer", SwiftONOF    ,PisoTeleKill1,2 ,pDevice);
}
//--------------------------------------------------------------------------//
Folder("Player Fiture",Moptfolder,MenuFolder[3],2);
if(MenuFolder[3]){ 
Item("Weapon Bugs (Unyu)"	,SwiftONOF	,WeaponBug_			,2 ,pDevice);
Item("Wall Bugs (WTW) "		,SwiftONOF	,WTW				,2 ,pDevice);
Item("Smart Ammo "			,SwiftONOF	,SmartAmmoX			,2 ,pDevice);
Item("Norecoil "			,SwiftONOF	,Recoil				,2 ,pDevice);
Item("Fast Change "			,SwiftONOF	,QuickChange		,2 ,pDevice);
Item("Fast Reload "			,SwiftONOF	,Reload				,2 ,pDevice);
Item("Fast Knife "			,SwiftONOF	,BrussKnife			,2 ,pDevice);
Item("Fast Exit [F12]"		,SwiftONOF	,GameFastExit		,2 ,pDevice);
}
//--------------------------------------------------------------------------//
Folder("Weapon Fiture",Moptfolder,MenuFolder[4],2);
if(MenuFolder[4]){ 
Item("Weapon Bugs (Unyu)"	,SwiftONOF	,WeaponBug_			,2 ,pDevice);
Item("Wall Bugs (WTW) "		,SwiftONOF	,WTW				,2 ,pDevice);
Item("Smart Ammo "			,SwiftONOF	,SmartAmmoX			,2 ,pDevice);
Item("Norecoil "			,SwiftONOF	,Recoil				,2 ,pDevice);
Item("Fast Change "			,SwiftONOF	,QuickChange		,2 ,pDevice);
Item("Fast Reload "			,SwiftONOF	,Reload				,2 ,pDevice);
Item("Fast Knife "			,SwiftONOF	,BrussKnife			,2 ,pDevice);
Item("Fast Exit [F12]"		,SwiftONOF	,GameFastExit		,2 ,pDevice);
}
//--------------------------------------------------------------------------//
Folder("Extream Fiture",Moptfolder,MenuFolder[5],2);
if(MenuFolder[5]){ 
Item("Weapon Bugs (Unyu)"	,SwiftONOF	,WeaponBug_			,2 ,pDevice);
Item("Wall Bugs (WTW) "		,SwiftONOF	,WTW				,2 ,pDevice);
Item("Smart Ammo "			,SwiftONOF	,SmartAmmoX			,2 ,pDevice);
Item("Norecoil "			,SwiftONOF	,Recoil				,2 ,pDevice);
Item("Fast Change "			,SwiftONOF	,QuickChange		,2 ,pDevice);
Item("Fast Reload "			,SwiftONOF	,Reload				,2 ,pDevice);
Item("Fast Knife "			,SwiftONOF	,BrussKnife			,2 ,pDevice);
Item("Fast Exit [F12]"		,SwiftONOF	,GameFastExit		,2 ,pDevice);
}
//--------------------------------------------------------------------------//
Folder(".::Setting::.",Moptfolder,MenuFolder[6],2);
if(MenuFolder[6]){
Item("Menu Mouse "			,SwiftONOF, MenuX_MouseShow	, 2 ,pDevice);
}}
//--------------------------------------------------------------------------//
void Navigation(LPDIRECT3DDEVICE9 pDevice){
if(Menu && NHT3XT){
if(IsKeyPressed(VK_DOWN,0))
MenuSelection++;
if(IsKeyPressed(VK_UP,0))
MenuSelection--;
MenuX_Standar(pDevice);
if(MenuSelection >qntHacks - 1)
MenuSelection = 0;
if(MenuSelection < 0)
MenuSelection = qntHacks - 1;
}}
//--------------------------------------------------------------------------//
void MenuSettings(){
menux = 10;
menuy = 10;
mxofs = 180;
qntHacks = 0;
}
//--------------------------------------------------------------------------//
VOID RenderMenu_S(LPDIRECT3DDEVICE9 pDevice){
MenuSettings();
if(Menu && NHT3XT){
FillGradients (20, 10,(Current * 20),163,Menu_background,Menu_background,pDevice);
pMenu.Rectangle(20, 10, 163, (Current * 20), Menu_rectangle, pDevice);
pMenu.Rectangle(19, 9, 165, (Current * 20), Menu_special, pDevice);
/* Windows Title */
FillGradients (20,10,20,163,White,Grey,pDevice);
pMenu.Rectangle(20, 10, 163, 20, Menu_rectangle, pDevice);
pMenu.DrawString(".::Menu Keyboard::.", 100, 12, TitleText, 1);
/* Main select */
DrawBorder(menux + 11, menuy + 20 + (MenuSelection * 20), mxofs - 19, 15, 2, Red, pDevice);
}
Navigation(pDevice);
}
//--------------------------------------------------------------------------//