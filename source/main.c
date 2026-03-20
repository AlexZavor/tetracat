#include <tonc.h>
#include "piece.h"
#include "graphics.h"
#include "game.h"

// TODO: is Modulo really slow?

int main()
{
	// Init interrupts and VBlank irq.
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);

	init_graphics();
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 ;

	// Draw basic blocks off screen
	for(int i = Z; i < X; i++){
		draw_piece(make_piece(i,(BG_POINT){-3,(i*3)-5}));
	}

	game_init();

	while(1)
	{
		VBlankIntrWait();
		key_poll();

		game_tick();
	}
	return 0;
}
