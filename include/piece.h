#ifndef PIECE_H
#define PIECE_H

#include "block.h"

#define BLOCKS_IN_PIECE 4 // Thaaaats Tetris

typedef struct{
    BG_POINT blocks[BLOCKS_IN_PIECE];
    s32 rotation;
    blocktype type;
} piece;

// Create new piece in start orientation
piece make_piece(blocktype type, BG_POINT start_location);

// Get new piece, picks psudo-random piece, placed in new piece location
piece new_piece();

// Moves piece to top of the game board, returns false if collides immediately (Game Over Condition)
bool start_piece(piece* p);

// Draw piece
void draw_piece(piece p);
// Erase Piece
void erase_piece(piece p);

// Moves piece, does erase, move and draw
bool move_piece(piece* p, s32 x, s32 y);
// rotates piece (1=CW, -1=CCW), does erase, move and draw
bool rotate_piece(piece* p, s32 r);

#endif // PIECE_H