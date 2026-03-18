#ifndef BLOCK_H
#define BLOCK_H

#include <tonc.h>
#include "graphics.h"

typedef enum { 
    Z = RED_PALLET, 
    S = GREEN_PALLET, 
    T = PURPLE_PALLET, 
    O = YELLOW_PALLET, 
    I = TEAL_PALLET, 
    L = ORANGE_PALLET, 
    J = BLUE_PALLET, 
    X = ERROR_PALLET,
} blocktype; // determines color

void drawBlock(BG_POINT point, blocktype b);
void eraseBlock(BG_POINT point);

#endif // BLOCK_H