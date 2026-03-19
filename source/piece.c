#include "piece.h"

// Helper function to check if a position collides or is out of bounds
inline bool collides(BG_POINT point){
    if( (point.x < 0) || (point.x >= 10) || (point.y < 0) || (point.y >= 20) ){
        return true;
    }
    // Check board
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
    piece temp = *p;
    
    for(int b = 0; b < BLOCKS_IN_PIECE; b++){
        temp.blocks[b].x += x;
        temp.blocks[b].y += y;
        if(collides(temp.blocks[b])){
            return false;
        }
    }
    erase_piece(*p);
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
    
    // Do the rotation
    update_rotation(&temp);
    // Check collision
    for(int b = 1; b < BLOCKS_IN_PIECE; b++){
        if(collides(temp.blocks[b])){
            return false;
        }
    }

    erase_piece(*p);
    *p = temp;
    draw_piece(*p);
    return true;
}
