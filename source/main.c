#include <tonc.h>
#include "block.h"
#include "graphics.h"

// Point for moving block
BG_POINT block_pt = {5,8};

int main()
{
	// Init interrupts and VBlank irq.
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);

	init_graphics();
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 ;

	// draw some blocks
	drawBlock((BG_POINT){2,2}, Z);
	drawBlock((BG_POINT){2,3}, O);
	drawBlock((BG_POINT){3,2}, L);
	drawBlock((BG_POINT){3,3}, J);
	drawBlock((BG_POINT){4,2}, T);
	drawBlock((BG_POINT){4,3}, S);
	drawBlock(block_pt, I);

	while(1)
	{
		VBlankIntrWait();
		
		// erase, update, draw
		eraseBlock(block_pt);

		key_poll();
		block_pt.x += key_tri_horz();
		block_pt.y += key_tri_vert();

		drawBlock(block_pt,I);


		if(key_hit(KEY_A)){
			swap_tile(CBB_1,BLOCK_TILE,BLOCK2_TILE);// swap tile used for block
		}
		
	}
	return 0;
}
