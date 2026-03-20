#include "board.h"
#include "graphics.h"

bool board_is_filled(int x, int y){
    return get_block_map()[y*MAP_WIDTH + x] != 0;
}
