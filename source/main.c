#include <tonc.h>
#include "piece.h"
#include "graphics.h"

int main()
{
	// Init interrupts and VBlank irq.
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);

	init_graphics();
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 ;

	// draw some blocks
	// draw_block((BG_POINT){2,2}, Z);
	// draw_block((BG_POINT){2,3}, O);
	// draw_block((BG_POINT){3,2}, L);
	// draw_block((BG_POINT){3,3}, J);
	// draw_block((BG_POINT){4,2}, T);
	// draw_block((BG_POINT){4,3}, S);
	// draw_block((BG_POINT){5,2}, I);

	// Draw basic blocks off screen
	for(int i = Z; i < X; i++){
		draw_piece(make_piece(i,(BG_POINT){-3,(i*3)-5}));
	}

	// Test Piece to debug piece physics
	blocktype t = Z;
	piece test = make_piece(t, (BG_POINT){5,15});
	draw_piece(test);

	while(1)
	{
		VBlankIntrWait();
		static u32 frame = 0;
		frame++;
		frame%=600; // only count up 10 seconds to prevent weird rollover behavior
		// TODO: is Modulo really slow?
		
		if (frame&0x2){// every four frames (just to slow down)
			key_poll();
			
			// erase, update, draw
			move_piece(&test,key_tri_horz(),key_tri_vert());

			if(key_hit(KEY_A)){// Rotate CW
				rotate_piece(&test,1);
			}
			if(key_hit(KEY_B)){// Rotate CCW
				rotate_piece(&test,-1);
			}
			if(key_hit(KEY_START)){// swap tile used for block
				swap_tile(CBB_1,BLOCK_TILE,BLOCK2_TILE);
			}
			if(key_hit(KEY_SELECT)){// Swap piece for new one
				erase_piece(test);
				test = make_piece((t++)%X, (BG_POINT){5,15});
				draw_piece(test);
			}
		}
		
	}
	return 0;
}
