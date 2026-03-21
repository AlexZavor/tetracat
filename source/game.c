#include "game.h"
#include "piece.h"
#include "board.h"
#include <tonc.h>

#define FLASH_TIME 5 // length of row cleared flash

int level = 1;
int score = 0;
int tick_timer = 0;

piece next_piece;
piece curr_piece;

// Helper Function to set timer based on current level (speeds up game)
inline void reset_timer(){
    tick_timer = 30;
    //TODO: set timer based on level
}

// Helper function to clear out rows, clears, collapses, and scores
inline void clear_filled_rows(){
    // clear and collapse
    int rows_colapsed = 0;
    for(int i = BOARD_HEIGHT-1; i >= 0; i--){
        if(rows_colapsed != 0){
            board_row_swap(i,i-rows_colapsed);
        }
        while(board_row_filled(i)){
            board_clear_row(i);
            rows_colapsed++;
            board_row_swap(i,i-rows_colapsed);
        }
    }
    if(rows_colapsed == 0) return; // nothing to score
    // scoreing
    switch (rows_colapsed){
        case 1:
            score += 40 * (rows_colapsed + 1);
        break;
        case 2:
            score += 100 * (rows_colapsed + 1);
        break;
        case 3:
            score += 300 * (rows_colapsed + 1);
        break;
        case 4:
            score += 1200 * (rows_colapsed + 1);
        break;
        default: break;
    }
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
    // TODO: draw score

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
        score++;
    }

    if(!tick_timer){// timer hit zero, move block
        reset_timer();
        if (curr_piece.type == X){ // reset for new piece
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
                // new piece check for row clear
                // int filled_rows[4]; // array to keep what rows to clear
                // int filled_rows_count = 0;
                // get_filled_rows(&filled_rows, &filled_rows_count);
                clear_filled_rows();

                curr_piece.type = X; // kills piece to get a new one
            }
        }
    }

}
