#include "text.h"
#include "graphics.h"

#define MAP_OFFSET 16

static enum {
    DISABLED,
    NUMERIC
}mode;

// compressed font "0123456789~-=+()"
const u32 numeric_font[32] = {
    0x00182C2C, 0x34341800, // 0
    0x00081808, 0x08081C00, // 1
    0x00182404, 0x08103C00, // 2
    0x00182408, 0x04241800, // 3
    0x00242424, 0x1E040400, // 4
    0x003C2018, 0x04043800, // 5
    0x00182038, 0x24241800, // 6
    0x003C0408, 0x08101000, // 7
    0x00182418, 0x24241800, // 8
    0x001C241C, 0x04040400, // 9
    0x00000028, 0x14000000, // ~
    0x00000000, 0x3C000000, // -
    0x0000003C, 0x003C0000, // =
    0x00000008, 0x1C080000, // +
    0x00081010, 0x10100800, // (
    0x00100808, 0x08081000, // )
};

inline int get_bit(int b, u32 data){
    return ((data >> b)&0x1) ? 1 : 0;
}


void init_numeric(){
    if(mode == DISABLED){
        mode = NUMERIC;
        for(int t=0; t < 16; t++){
            TILE tile = (TILE){{ 0x00000000, 0x00000000, 0x00000000, 0x00000000,
                                0x00000000, 0x00000000, 0x00000000, 0x00000000}};
            for(int i=0; i < 4; i++){
                u32 data = numeric_font[t*2];
                tile.data[3-i] = 
                    get_bit(7+(i*8), data) << 0 |
                    get_bit(6+(i*8), data) << 4 |
                    get_bit(5+(i*8), data) << 8 |
                    get_bit(4+(i*8), data) << 12 |
                    get_bit(3+(i*8), data) << 16 |
                    get_bit(2+(i*8), data) << 20 |
                    get_bit(1+(i*8), data) << 24 |
                    get_bit(0+(i*8), data) << 28;
                data = numeric_font[(t*2)+1];
                tile.data[7-i] = 
                    get_bit(7+(i*8), data) << 0 |
                    get_bit(6+(i*8), data) << 4 |
                    get_bit(5+(i*8), data) << 8 |
                    get_bit(4+(i*8), data) << 12 |
                    get_bit(3+(i*8), data) << 16 |
                    get_bit(2+(i*8), data) << 20 |
                    get_bit(1+(i*8), data) << 24 |
                    get_bit(0+(i*8), data) << 28;
            }
            write_tile(MAP_OFFSET+t, tile);
        }
    }
}

void draw_char(char c, int x, int y){
    if(c<'9' && c>'0'){
        SCR_ENTRY *map = get_block_map();
        map[MAP_WIDTH*y + x] = (MAP_OFFSET+(c-'0')) | SE_PALBANK(TEXT_PALLET);
    }
}

void d_1(int d, int x, int y){
    SCR_ENTRY *map = get_block_map();
    map[MAP_WIDTH*y + x] = (MAP_OFFSET+d) | SE_PALBANK(TEXT_PALLET);
}

void draw_int(int d, int x, int y){
    if(d == 0){
        d_1(0,x,y);
    }
    while(d){
        d_1(d%10,x,y);
        d/=10;
        x--;
    }
}
