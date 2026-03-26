#include <tonc.h>
#include <maxmod.h> // used for SFX only, working on music player
#include "piece.h"
#include "graphics.h"
#include "game.h"

// Maxmod built files (make clean and remake if there's issues)
#include "soundbank.h"
#include "soundbank_bin.h"

// TODO: is Modulo really slow?

int main()
{
	// Init interrupts and VBlank irq.
	irq_init(NULL);
	irq_add(II_VBLANK, mmVBlank);
	irq_enable(IRQ_VBLANK);
    mmInitDefault( (mm_addr)soundbank_bin, 8 ); // init maxmod

	init_graphics();
	REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 ;

	// Draw basic blocks off screen
	for(int i = Z; i < X; i++){
		draw_piece(make_piece(i,(BG_POINT){-3,(i*3)-5}));
	}

	game_init();
	mmEffect(SFX_STARTUP);

	while(1)
	{
		mmFrame(); // update maxmod, once per frame
		VBlankIntrWait();
		key_poll();

		game_tick();
	}
	return 0;
}
