#include "game.h"
#include "piece.h"
#include "board.h"
#include "text.h"
#include <tonc.h>
#include <maxmod.h>
#include "soundbank.h"

#define BLINK_TIME 6 // length of row cleared blinking
#define BLINK_COUNT 4
bool blinking = false;

int level = 1;
int score = 0;
int tick_timer = 0;
int cleared_lines_this_level = 0; // increment to 0 and roll over to next level


int filled_rows[4]; // array to keep what rows to clear
int filled_rows_count = 0;

piece next_piece;
piece curr_piece;

// print score on screen
inline void print_score(){
    draw_int(score, 19, 0); // draw score
    draw_int(level, 19, 1); // draw level
}

// Helper Function to set timer based on current level (speeds up game)
inline void reset_timer(){
    if(level < 30){
        tick_timer = 30-level;
    }else{
        tick_timer = 1; // full speed
    }
    print_score();
}

// Helper function to clear out rows, clears, collapses, and scores
inline void clear_filled_rows(){
    // clear and collapse
    int rows_collapsed = 0;
    for(int i = BOARD_HEIGHT-1; i >= 0; i--){
        if(rows_collapsed != 0){
            board_row_swap(i,i-rows_collapsed);
        }
        while(board_row_filled(i)){
            board_clear_row(i);
            rows_collapsed++;
            board_row_swap(i,i-rows_collapsed);
        }
    }
    if(rows_collapsed == 0) return; // nothing to score
    // scoreing
    switch (rows_collapsed){
        case 1:
            score += 40 * (rows_collapsed + 1);
        break;
        case 2:
            score += 100 * (rows_collapsed + 1);
        break;
        case 3:
            score += 300 * (rows_collapsed + 1);
        break;
        case 4:
            score += 1200 * (rows_collapsed + 1);
        break;
        default: break;
    }
    // advance level
    cleared_lines_this_level++;
    if(cleared_lines_this_level >= level * 10){
        cleared_lines_this_level -= level * 10;
        level++;
    }
    print_score();
}

// hides rows
inline void hide_filled_rows(bool hide){
    for(int i=0; i<filled_rows_count; i++){
        board_hide_row(filled_rows[i], hide);
    }
}

void game_init(){
    next_piece = new_piece();
    draw_piece(next_piece);
    curr_piece = make_piece(X,(BG_POINT){0,0});
    reset_timer();
    init_numeric();
    print_score();
}

// Micro state machine to make blocks blink when cleared
void blinking_tick(){
    static int blink = 0;
    static int blink_timer = BLINK_TIME;
    blink_timer--;
    if(blink_timer == 0){
        blink++;
        blink_timer = BLINK_TIME;
        hide_filled_rows(blink%2);
    }
    if(blink == BLINK_COUNT * 2){ // end of blinking state
        clear_filled_rows();
        blink = 0;
        blink_timer = BLINK_TIME;
        blinking = false;
        filled_rows_count = 0;
    }
}

void game_tick(){
    if(blinking){ // blinks when rows cleared
        blinking_tick();
        return;
    }

    // Piece draws wrong if tried to move while dead
    if(curr_piece.type == X) goto skip_input; // fixes error in dumb way, just move it away.

    // error moving, if it doesn't move right
    bool moved = true;

    // handle input
    if(key_hit(KEY_A)){// Rotate CW
        moved = rotate_piece(&curr_piece,1);
        mmEffect(SFX_ROT_CW);
    }
    if(key_hit(KEY_B)){// Rotate CCW
        moved = rotate_piece(&curr_piece,-1);
        mmEffect(SFX_ROT_CCW);
    }
    if(key_hit(KEY_START)){// swap tile used for block
        swap_tile(CBB_1,BLOCK_TILE,BLOCK2_TILE);
    }


    if(key_hit(KEY_RIGHT)){// Move R
        moved = move_piece(&curr_piece, 1, 0);
    }
    if(key_hit(KEY_LEFT)){// Move L
        moved = move_piece(&curr_piece, -1, 0);
    }

    if(!moved){
        mmEffect(SFX_BAD);
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
                get_filled_rows(filled_rows, &filled_rows_count);

                if(filled_rows_count > 0){
                    blinking = true;
                    if(filled_rows_count == 4){
                        // Tetris
                        mmEffect(SFX_TETRIS);
                    }else{
                        mmEffect(SFX_POINT);
                    }
                }else{
                    mmEffect(SFX_THUNK);
                }

                curr_piece.type = X; // kills piece to get a new one
            }
        }
    }

}
