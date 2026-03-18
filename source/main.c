#include <tonc.h>
#include "bkg.h"

#define CBB_0  0
#define SBB_0 31
#define CBB_1  1
#define SBB_1 30
#define MAP_WIDTH 32

#define BLOCK_TILE 1
#define RED_PALLET 2

BG_POINT bg0_pt= { 0, 0 };
SCR_ENTRY *bg0_map= se_mem[SBB_0];
SCR_ENTRY *bg1_map= se_mem[SBB_1];


void init_map()
{
	// initialize a background
	REG_BG0CNT= BG_CBB(CBB_0) | BG_SBB(SBB_0) | BG_REG_32x32 | BG_PRIO(1);
	REG_BG0HOFS= 0;
	REG_BG0VOFS= 0;
	// Load Tiles
	memcpy32(tile_mem[CBB_0], bkgTiles, bkgTilesLen/4);
	// Load Pallet
	memcpy16(pal_bg_bank, bkgPal, bkgPalLen/2);
	// Load Map
	memcpy16(bg0_map, bkgMap, bkgMapLen/2);

	// initialize foreground (blocks)
	REG_BG1CNT= BG_CBB(CBB_1) | BG_SBB(SBB_1) | BG_REG_32x32 | BG_PRIO(0);
	REG_BG1HOFS= -40; // Shifts over so top left of play area is 0,0
	REG_BG1VOFS= 0;

	// create the tiles: Empty(transparent), block
	const TILE tiles[2]=
	{
		{{0x00000000, 0x00000000, 0x00000000, 0x00000000,
		  0x00000000, 0x00000000, 0x00000000, 0x00000000}},
		{{0x11111111, 0x12222221, 0x12111321, 0x12111121,
		  0x12111121, 0x12111121, 0x12222221, 0x11111111}},
	};
	tile_mem[CBB_1][0]= tiles[0];
	tile_mem[CBB_1][BLOCK_TILE]= tiles[BLOCK_TILE];

	// Create Pallets
	pal_bg_bank[RED_PALLET][1]= RGB15(24,  0,  0); // Standard
	pal_bg_bank[RED_PALLET][2]= RGB15(15,  0,  0); // Shadow
	pal_bg_bank[RED_PALLET][3]= RGB15(31, 15, 15); // Highlight

	// Place block on map
	int x,y;
	x = 5; y = 5;
	bg1_map[x*MAP_WIDTH + y] = BLOCK_TILE | SE_PALBANK(RED_PALLET);
}

int main()
{
	// Init interrupts and VBlank irq.
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);

	init_map();
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 ;

	while(1)
	{
		VBlankIntrWait();

		key_poll();
		bg0_pt.x += key_tri_horz();
		bg0_pt.y += key_tri_vert();

		// Does nothing each frame :P
	}
	return 0;
}
