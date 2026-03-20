#include "game.h"
#include "piece.h"
#include <tonc.h>

#define FLASH_TIME 5 // length of row cleared flash

int level = 1;
int score = 0;
int tick_timer = 0;

piece next_piece;
piece curr_piece;

// Helper Function to set timer based on current level (speeds up game)
void reset_timer(){
    tick_timer = 30;
    //TODO: set timer based on level
}

void game_init(){
    level = 1;
    score = 0;
    next_piece = new_piece();
    draw_piece(next_piece);
    curr_piece = make_piece(X,(BG_POINT){0,0});
    reset_timer();
}

void game_tick(){

    // Piece draws wrong if tried to move while dead
    if(curr_piece.type == X) goto skip_input; // fixes error in dumb way, just move it away.

    // handle input
    if(key_hit(KEY_A)){// Rotate CW
        rotate_piece(&curr_piece,1);
    }
    if(key_hit(KEY_B)){// Rotate CCW
        rotate_piece(&curr_piece,-1);
    }
    if(key_hit(KEY_START)){// swap tile used for block
        swap_tile(CBB_1,BLOCK_TILE,BLOCK2_TILE);
    }


    if(key_hit(KEY_RIGHT)){// Move R
        move_piece(&curr_piece, 1, 0);
    }
    if(key_hit(KEY_LEFT)){// Move L
        move_piece(&curr_piece, -1, 0);
    }

skip_input:

    tick_timer--;

    if(key_is_down(KEY_DOWN) && (curr_piece.type != X)){
        tick_timer = 0;// just cuts timer to move down at max speed
    }

    if(!tick_timer){// timer hit zero, move block
        reset_timer();
        if (curr_piece.type == X){
			curr_piece = next_piece;
			next_piece = new_piece();
			bool started = start_piece(&curr_piece);
            if(!started){
                while(1);// game over death spiral
            }
			draw_piece(next_piece);
		}else{
            bool moved = move_piece(&curr_piece, 0, 1);//moves down once every tick
            if (!moved){
                curr_piece.type = X; // kills piece to get a new one
            }
        }
    }

}
