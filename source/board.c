#include "board.h"
#include "graphics.h"

bool board_is_filled(int x, int y){
    return get_block_map()[y*MAP_WIDTH + x] != 0;
}

bool board_row_filled(int y)
{
    for (int x = 0; x < BOARD_WIDTH; x++){
        if (!board_is_filled(x,y)){
            return false;
        }
    }
    return true;
}
