#ifndef CLOCK_H_
#define CLOCK_H_

#include <SDL2/SDL.h>


//  STRUCTURES  //////////////////////////////////////////////////////

typedef struct
{
    int running;
    int fps;
    Uint32 last_tick;
}
Clock;


//  PROTOTYPES  //////////////////////////////////////////////////////

// wait until next tick and return time elapsed in milliseconds
int next_tick(Clock *clock);

#endif
