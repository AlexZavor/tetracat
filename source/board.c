#include "board.h"
#include "graphics.h"
#include "block.h"

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

void board_clear_row(int y)
{
    for (int x = 0; x < BOARD_WIDTH; x++){
        erase_block((BG_POINT){x,y});
    }
}

void get_filled_rows(int *rows, int *count){
    for(int row = 0; row < BOARD_HEIGHT; row ++){
        bool filled = board_row_filled(row);
        if(filled){
            rows[*count] = row;
            (*count)++;
        }
    }
}

void board_row_swap(int r1, int r2){
    SCR_ENTRY temp[BOARD_WIDTH];
    memcpy16(temp, &get_block_map()[r1*MAP_WIDTH], BOARD_WIDTH);
    memcpy16(&get_block_map()[r1*MAP_WIDTH], &get_block_map()[r2*MAP_WIDTH], BOARD_WIDTH);
    memcpy16(&get_block_map()[r2*MAP_WIDTH], temp, BOARD_WIDTH);
}
