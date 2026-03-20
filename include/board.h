#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

#define NEXT_PIECE_X 17
#define NEXT_PIECE_Y 14

#define START_POS_X 5
#define START_POS_Y 0

// Returns if position on board has block drawn to it.
bool board_is_filled(int x, int y);

// Returns if all blocks on row are filled
bool board_row_filled(int y);

#endif // BOARD_H