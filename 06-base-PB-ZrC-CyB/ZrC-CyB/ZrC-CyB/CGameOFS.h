/*Offset PBHacks Last Edit By ZrC-CyB Hacks*/
#include "StandardIncludes.h"

#define G_PRENDER	0x1C2770
#define END_RENDER  0x53A8
#define MAXPLAYER	0x16
#define HPSIZE		0x104
#define IDSIZE		0x1
#define NAMESIZE	0x21
#define RANKSIZE	0x2B
#define WEAPSIZE	0x158

#define PTR_IDLE1	0x1C3
#define PTR_IDLE2	0x1C7
#define PTR_RAPID1	0x504
#define	PTR_RAPID2	0x5F4
#define PTR_FALL	0x510
#define PTR_REPEAT	0x513
#define PTR_QC		0x540
#define PTR_BUTTON1	0x560
#define PTR_BUTTON2	0x94E8
#define PTR_FLY		0x904
#define PTR_WEAPON	0x544
#define PTR_CAMPOS	0x554
#define PTR_RECOIL	0x558
#define CALCWPN1	0xC9C
#define CALCWPN2	0xCA8

#define OFS_HEALTH	0x264
#define OFS_NAMES	0x29E34
#define OFS_PLAYER	0x28364
#define OFS_TEAM	0x2A254
#define OFS_RANK	0x285F0 
#define OFS_RANK2	(OFS_RANK+0x1) 
#define OFS_RESPAWN	(OFS_RANK+0x2)  
#define OFS_DEATH   0x2CDAC
#define OFS_PING	0x3B8AC 
#define OFS_KILL    0x3B908
#define OFS_TSCR	0x3B900
#define OFS_WEAPON	0x28178
#define OFS_WEAPON2	0x2817C
#define OFS_WEAPON3 0x28180
#define OFS_WEAPON4 0x28184
#define OFS_WEAPON5 0x28188
#define OFS_RELOAD	0x28430

#define BASE_PLAYER		0x86B900
#define BASE_PLAYER2	0xC6B900
#define	BASE_IDLE		(BASE_PLAYER-0x8)
#define	BASE_IDLE2		(BASE_PLAYER2-0x8)
#define BASE_WEAPON		(BASE_PLAYER-0x1C)
#define BASE_WEAPON2	(BASE_PLAYER2-0x1C)
#define BASE_MOVE		(BASE_PLAYER-0x28)
#define BASE_MOVE2		(BASE_PLAYER2-0x28)
#define BASE_HEALTH		(BASE_PLAYER-0x34)
#define BASE_HEALTH2	(BASE_PLAYER2-0x34)
#define BASE_AMMO		(BASE_PLAYER-0x38)
#define BASE_AMMO2		(BASE_PLAYER2-0x38)
#define BASE_AMMO3		0xBC9914

#define BASE_VOTE	0x557810
#define SUICIDE		0x7018D0
#define BASE_STR1	0x603E34
#define BASE_STR2	0x68EE4C
#define BASE_UNYU	0xB1A3E7
#define BASE_INVI	0xA2C29C
#define BASE_WST	0x587DE7
#define BASE_RANGE  0x59474D
#define BASE_HOVER	0x643D
#define BASE_DATAR	0x6510
#define THandle1	0x988D6B
#define THandle2	0x492321

#define BASE_AIMBOTX	0xC9B550
#define BASE_AIMBOTY	0xC9B554
#define BASE_GETBUTTON	0xA6F960
#define BASE_BULLET		0xC9B67C
#define CALL_DOLINE		0x58DA70
#define CALL_CAMPOS		0x726660
#define CALL_HITEVENT	0x8EF040
#define CALL_SETWEAPON	0x537050
#define CALL_PutString	0xC77D0
/*-------------------------------------------------------------------------------------------------------------------*/