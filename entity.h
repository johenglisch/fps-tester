#ifndef ENTITY_H_
#define ENTITY_H_

#include <SDL2/SDL.h>


//  STRUCTURES  //////////////////////////////////////////////////////

typedef struct
{
    int x;
    int y;
}
Position;

typedef struct
{
    int w;
    int h;
}
Size;

typedef struct
{
    int dx;
    int dy;
}
Velocity;

typedef struct
{
    Position pos;
    Size size;
    Velocity speed;
    SDL_Texture *img;
}
Entity;


//  PROTOTYPES  //////////////////////////////////////////////////////

void move_entity(Entity *entity, int time_ms);
void bounce_off_wall(Entity *entity, Size *room);

#endif
