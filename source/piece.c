#include "piece.h"
#include "board.h"

// Helper function to check if a position collides or is out of bounds
inline bool collides(BG_POINT point){
    if( (point.x < 0) || (point.x >= BOARD_WIDTH) || (point.y < 0) || (point.y >= BOARD_HEIGHT) ){
        return true;
    }
    // Check board
    if(board_is_filled(point.x, point.y)){
        return true;
    }
    return false;
}

// Helper function for adding vectors
inline BG_POINT add(BG_POINT p1, BG_POINT p2){
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

void update_rotation(piece* p){
    BG_POINT start_location = p->blocks[0];
    switch (p->type){
        case Z:
            switch (p->rotation){
                case 0:
                case 2:
                    p->blocks[1] = start_location;
                        p->blocks[1].x--;
                    p->blocks[2] = start_location;
                        p->blocks[2].y++;
                    p->blocks[3] = start_location;
                        p->blocks[3].y++;
                        p->blocks[3].x++;
                break;
                case 1:
                case 3:
                    p->blocks[1] = start_location;
                        p->blocks[1].y--;
                    p->blocks[2] = start_location;
                        p->blocks[2].x--;
                    p->blocks[3] = start_location;
                        p->blocks[3].y++;
                        p->blocks[3].x--;
                break;
                default:break;
            }
        break;
        case T:
            switch (p->rotation){
                case 0:
                    p->blocks[1] = start_location;
                        p->blocks[1].x--;
                    p->blocks[2] = start_location;
                        p->blocks[2].x++;
                    p->blocks[3] = start_location;
                        p->blocks[3].y++;
                break;
                case 1:
                    p->blocks[1] = start_location;
                        p->blocks[1].x--;
                    p->blocks[2] = start_location;
                        p->blocks[2].y--;
                    p->blocks[3] = start_location;
                        p->blocks[3].y++;
                break;
                case 2:
                    p->blocks[1] = start_location;
                        p->blocks[1].x--;
                    p->blocks[2] = start_location;
                        p->blocks[2].y--;
                    p->blocks[3] = start_location;
                        p->blocks[3].x++;
                break;
                case 3:
                    p->blocks[1] = start_location;
                        p->blocks[1].y++;
                    p->blocks[2] = start_location;
                        p->blocks[2].y--;
                    p->blocks[3] = start_location;
                        p->blocks[3].x++;
                break;
            }
        break;
        case S:
            switch (p->rotation){
                case 0:
                case 2:
                    p->blocks[1] = start_location;
                        p->blocks[1].x++;
                    p->blocks[2] = start_location;
                        p->blocks[2].y++;
                    p->blocks[3] = start_location;
                        p->blocks[3].y++;
                        p->blocks[3].x--;
                break;
                case 1:
                case 3:
                    p->blocks[1] = start_location;
                        p->blocks[1].y++;
                    p->blocks[2] = start_location;
                        p->blocks[2].x--;
                    p->blocks[3] = start_location;
                        p->blocks[3].y--;
                        p->blocks[3].x--;
                break;
                default:break;
            }
        break;
        case O:
            p->blocks[1] = start_location;
                p->blocks[1].x++;
            p->blocks[2] = start_location;
                p->blocks[2].x++;
                p->blocks[2].y++;
            p->blocks[3] = start_location;
                p->blocks[3].y++;
        break;
        case I:
            switch (p->rotation){
                case 0:
                case 2:
                    p->blocks[1] = start_location;
                        p->blocks[1].x++;
                    p->blocks[2] = start_location;
                        p->blocks[2].x++;
                        p->blocks[2].x++;
                    p->blocks[3] = start_location;
                        p->blocks[3].x--;
                break;
                case 1:
                case 3:
                    p->blocks[1] = start_location;
                        p->blocks[1].y++;
                    p->blocks[2] = start_location;
                        p->blocks[2].y--;
                        p->blocks[2].y--;
                    p->blocks[3] = start_location;
                        p->blocks[3].y--;
                break;
                default:break;
            }
        break;
        case L:
            switch (p->rotation){
                case 0:
                    p->blocks[1] = start_location;
                        p->blocks[1].x--;
                    p->blocks[2] = start_location;
                        p->blocks[2].x++;
                    p->blocks[3] = start_location;
                        p->blocks[3].x--;
                        p->blocks[3].y++;
                break;
                case 1:
                    p->blocks[1] = start_location;
                        p->blocks[1].x--;
                        p->blocks[1].y--;
                    p->blocks[2] = start_location;
                        p->blocks[2].y--;
                    p->blocks[3] = start_location;
                        p->blocks[3].y++;
                break;
                case 2:
                    p->blocks[1] = start_location;
                        p->blocks[1].x--;
                    p->blocks[2] = start_location;
                        p->blocks[2].y--;
                        p->blocks[2].x++;
                    p->blocks[3] = start_location;
                        p->blocks[3].x++;
                break;
                case 3:
                    p->blocks[1] = start_location;
                        p->blocks[1].y++;
                    p->blocks[2] = start_location;
                        p->blocks[2].y--;
                    p->blocks[3] = start_location;
                        p->blocks[3].y++;
                        p->blocks[3].x++;
                break;
            }
        break;
        case J:
            switch (p->rotation){
                case 0:
                    p->blocks[1] = start_location;
                        p->blocks[1].x--;
                    p->blocks[2] = start_location;
                        p->blocks[2].x++;
                    p->blocks[3] = start_location;
                        p->blocks[3].x++;
                        p->blocks[3].y++;
                break;
                case 1:
                    p->blocks[1] = start_location;
                        p->blocks[1].x--;
                        p->blocks[1].y++;
                    p->blocks[2] = start_location;
                        p->blocks[2].y--;
                    p->blocks[3] = start_location;
                        p->blocks[3].y++;
                break;
                case 2:
                    p->blocks[1] = start_location;
                        p->blocks[1].x--;
                    p->blocks[2] = start_location;
                        p->blocks[2].y--;
                        p->blocks[2].x--;
                    p->blocks[3] = start_location;
                        p->blocks[3].x++;
                break;
                case 3:
                    p->blocks[1] = start_location;
                        p->blocks[1].y++;
                    p->blocks[2] = start_location;
                        p->blocks[2].y--;
                    p->blocks[3] = start_location;
                        p->blocks[3].y--;
                        p->blocks[3].x++;
                break;
            }
        break;
            
        
    
        default:
            p->blocks[1] = start_location;
            p->blocks[2] = start_location;
            p->blocks[3] = start_location;
        break;  
    }
}

piece make_piece(blocktype type, BG_POINT start_location){
    piece p;
    p.type = type;
    p.rotation = 0;
    p.blocks[0] = start_location;
    update_rotation(&p);
    return p;
}

piece new_piece(){
    // TODO: Random gen
    static blocktype type = Z;
    type++;
    if(type == X){
        type = Z;
    }
    return make_piece(type, (BG_POINT){NEXT_PIECE_X, NEXT_PIECE_Y});;
}

bool start_piece(piece *p){
    piece temp = *p;

    erase_piece(*p);

    temp.blocks[0].x = START_POS_X;
    temp.blocks[0].y = START_POS_Y;

    update_rotation(&temp);
    
    for(int b = 0; b < BLOCKS_IN_PIECE; b++){
        if(collides(temp.blocks[b])){
            draw_piece(temp);
            return false;
        }
    }

    *p = temp;
    draw_piece(temp); // just draws anyways. I think it looks better

    return true;
}

inline void draw_piece(piece p){
    for(int b = 0; b < BLOCKS_IN_PIECE; b++){
        draw_block(p.blocks[b], p.type);
    }
}
inline void erase_piece(piece p){
    for(int b = 0; b < BLOCKS_IN_PIECE; b++){
        erase_block(p.blocks[b]);
    }
}

inline bool move_piece(piece* p, s32 x, s32 y){
    if((x==0)&&(y==0)) return true;
    piece temp = *p;

    erase_piece(*p);
    
    for(int b = 0; b < BLOCKS_IN_PIECE; b++){
        temp.blocks[b].x += x;
        temp.blocks[b].y += y;
        if(collides(temp.blocks[b])){
            draw_piece(*p);
            return false;
        }
    }

    *p = temp;
    draw_piece(*p);

    return true;
}

bool rotate_piece(piece *p, s32 r){
    if(p->type == O)return true;// silly
    piece temp = *p;
    // Rotation wrapping
    temp.rotation += r;
    if (temp.rotation<0){// negative wrap
        temp.rotation = 3;
    }
    temp.rotation %= 4; // positive wrap
    
    erase_piece(*p);

    // Do the rotation
    update_rotation(&temp);
    // Check collision
    for(int b = 1; b < BLOCKS_IN_PIECE; b++){
        if(collides(temp.blocks[b])){
            draw_piece(*p);
            return false;
        }
    }

    *p = temp;
    draw_piece(*p);
    return true;
}
