#include "hal.h"

static volatile uint32_t jiffy = 0;
static int fps = 0;
static int nr_draw = 0;

void
incr_nr_draw(void) {
	nr_draw ++;
}

int
get_fps() {
	return fps;
}

void
timer_event(void) {
	jiffy ++;
	if(jiffy % (HZ / 2) == 0) {
		fps = nr_draw * 2 + 1;
		nr_draw = 0;
	}
}

inline uint32_t SDL_GetTicks() {
	/* TODO: Return the time in millisecond. */

    uint32_t time = (jiffy * 1000) / HZ
	return time;
}

void SDL_Delay(uint32_t ms) {
	/* TODO: Return from this function after waiting for `ms' milliseconds. */

    uint32_t time1 = SDL_GetTicks();
    while(1){
        uint32_t time2 = SDL_GetTicks();
        if(time2 - time1 == ms)
            return;
    }
}
