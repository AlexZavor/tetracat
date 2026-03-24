#include "graphics.h"
#include "bkg.h"

SCR_ENTRY *block_map= se_mem[SBB_1];

void init_graphics(){
	// initialize background (BG0)
	REG_BG0CNT= BG_CBB(CBB_0) | BG_SBB(SBB_0) | BG_REG_32x32 | BG_PRIO(1);
	REG_BG0HOFS= 0;
	REG_BG0VOFS= 0;
	// Load Tiles
	memcpy32(tile_mem[CBB_0], bkgTiles, bkgTilesLen/4);
	// Load Pallet
	memcpy16(pal_bg_bank, bkgPal, bkgPalLen/2);
	// Load Map
	memcpy16(se_mem[SBB_0], bkgMap, bkgMapLen/2);

	// initialize foreground (blocks, BG1)
	REG_BG1CNT= BG_CBB(CBB_1) | BG_SBB(SBB_1) | BG_REG_32x32 | BG_PRIO(0);
	REG_BG1HOFS= -40; // Shifts over so top left of play area is 0,0
	REG_BG1VOFS= 0;

	// create the tiles: Empty(transparent), block1, block2
	const TILE tiles[3]=
	{
		{{0x00000000, 0x00000000, 0x00000000, 0x00000000,
		  0x00000000, 0x00000000, 0x00000000, 0x00000000}},
		{{0x13333333, 0x21111113, 0x21111113, 0x21111113,
		  0x21111113, 0x21111113, 0x21111113, 0x22222221}},
		{{0x11111111, 0x12222221, 0x12111321, 0x12111121,
		  0x12111121, 0x12111121, 0x12222221, 0x11111111}},
	};
	tile_mem[CBB_1][0]= tiles[0];
	tile_mem[CBB_1][BLOCK_TILE]= tiles[BLOCK_TILE];
	tile_mem[CBB_1][BLOCK2_TILE]= tiles[BLOCK2_TILE];

	// Create Pallets
	//   Text
	pal_bg_bank[TEXT_PALLET][1] = RGB15(31,31,31); // white
    //   Red
	pal_bg_bank[RED_PALLET][1]= RGB15(24,  0,  0); // Standard
	pal_bg_bank[RED_PALLET][2]= RGB15(15,  0,  0); // Shadow
	pal_bg_bank[RED_PALLET][3]= RGB15(31, 15, 15); // Highlight
    //   Green
	pal_bg_bank[GREEN_PALLET][1]= RGB15( 0, 24,  0); // Standard
	pal_bg_bank[GREEN_PALLET][2]= RGB15( 0, 15,  0); // Shadow
	pal_bg_bank[GREEN_PALLET][3]= RGB15(15, 31, 15); // Highlight
    //   Purple
	pal_bg_bank[PURPLE_PALLET][1]= RGB15(24,  0, 24); // Standard
	pal_bg_bank[PURPLE_PALLET][2]= RGB15(15,  0, 15); // Shadow
	pal_bg_bank[PURPLE_PALLET][3]= RGB15(31, 15, 31); // Highlight
    //   Yellow
	pal_bg_bank[YELLOW_PALLET][1]= RGB15(24, 24,  0); // Standard
	pal_bg_bank[YELLOW_PALLET][2]= RGB15(15, 15,  0); // Shadow
	pal_bg_bank[YELLOW_PALLET][3]= RGB15(31, 31, 15); // Highlight
    //   Teal
	pal_bg_bank[TEAL_PALLET][1]= RGB15( 0, 24, 24); // Standard
	pal_bg_bank[TEAL_PALLET][2]= RGB15( 0, 15, 15); // Shadow
	pal_bg_bank[TEAL_PALLET][3]= RGB15(15, 31, 31); // Highlight
    //   Orange
	pal_bg_bank[ORANGE_PALLET][1]= RGB15(31, 15,  0); // Standard
	pal_bg_bank[ORANGE_PALLET][2]= RGB15(20, 8,  0); // Shadow
	pal_bg_bank[ORANGE_PALLET][3]= RGB15(31, 24, 15); // Highlight
    //   Blue
	pal_bg_bank[BLUE_PALLET][1]= RGB15( 0,  0, 24); // Standard
	pal_bg_bank[BLUE_PALLET][2]= RGB15( 0,  0, 15); // Shadow
	pal_bg_bank[BLUE_PALLET][3]= RGB15(15, 15, 31); // Highlight
    // Err
	pal_bg_bank[ERROR_PALLET][1]= RGB15( 0,  0,  0); // Standard
	pal_bg_bank[ERROR_PALLET][2]= RGB15(31, 20, 20); // Shadow
	pal_bg_bank[ERROR_PALLET][3]= RGB15(31, 10, 10); // Highlight

}

inline void write_tile(int index, TILE tile){
	tile_mem[CBB_1][index]= tile;
}

inline SCR_ENTRY *get_block_map()
{
    return block_map;
}

void swap_tile(int char_block, int t1, int t2){
    TILE temp;
    memcpy32(&temp, &tile_mem[char_block][t1], sizeof(TILE)/4);
    memcpy32(&tile_mem[char_block][t1], &tile_mem[char_block][t2], sizeof(TILE)/4);
    memcpy32(&tile_mem[char_block][t2], &temp, sizeof(TILE)/4);
}

