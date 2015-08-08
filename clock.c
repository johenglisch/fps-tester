#include "clock.h"

#include <assert.h>


int next_tick(Clock *clock)
{
    assert(clock != NULL);
    assert(clock->fps > 0);

    Uint32 now;
    Uint32 diff = 0;
    Uint32 frame = 1000 / (Uint32)(clock->fps);

    if (clock->running == 0)
    {
        clock->running = 1;
        clock->last_tick = SDL_GetTicks();
        return 0;
    }

    now = SDL_GetTicks();
    if (now < clock->last_tick)
    {
        clock->last_tick = now;
        return 0;
    }

    diff = now - clock->last_tick;
    if (diff < frame)
    {
        SDL_Delay(frame - diff);
        now = SDL_GetTicks();
        diff = now - clock->last_tick;
    }

    clock->last_tick = now;
    return (int) diff;
}
