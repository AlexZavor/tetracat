#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

// Returns if position on board has block drawn to it.
bool board_is_filled(int x, int y);

#endif // BOARD_H