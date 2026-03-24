#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <tonc.h>

// Tile and Screen block locations
#define CBB_0  0
#define SBB_0 31
#define CBB_1  1
#define SBB_1 30
#define MAP_WIDTH 32

// Tile Locations
#define BLOCK_TILE 1
#define BLOCK2_TILE 2

// Pallet Indexs
#define BACKGROUND_PALLET 0
#define TEXT_PALLET 1
#define RED_PALLET 2
#define GREEN_PALLET 3
#define PURPLE_PALLET 4
#define YELLOW_PALLET 5
#define TEAL_PALLET 6
#define ORANGE_PALLET 7
#define BLUE_PALLET 8
#define ERROR_PALLET 9


// initializes game graphics, tiles, pallets, background maps
void init_graphics();

// Swap two tiles in char block
void swap_tile(int char_block, int old, int new);

// writes data in tile to tile memory
void write_tile(int index, TILE tile);

SCR_ENTRY *get_block_map();

#endif // GRAPHICS_H