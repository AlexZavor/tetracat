#include "block.h"

inline bool in_area(BG_POINT point){
    return !((point.x < 0) || (point.x >= 20) || (point.y < 0) || (point.y >= 20));
}

inline void draw_block(BG_POINT point, blocktype b){
    // if(in_area(point))
        get_block_map()[point.y*MAP_WIDTH + point.x] = BLOCK_TILE | SE_PALBANK(b);
}

inline void erase_block(BG_POINT point){
    // if(in_area(point))
        get_block_map()[point.y*MAP_WIDTH + point.x] = 0;
}