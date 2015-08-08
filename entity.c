#include "entity.h"


void move_entity(Entity *entity, int time_ms)
{
    entity->pos.x += entity->speed.dx * time_ms;
    entity->pos.y += entity->speed.dy * time_ms;
}

void bounce_off_wall(Entity *entity, Size *room)
{
    int right_edge = room->w - entity->size.w;
    int bottom_edge = room->h - entity->size.h;

    if (entity->pos.x < 0)
    {
        entity->pos.x *= -1;
        entity->speed.dx *= -1;
    }

    if (entity->pos.x >= right_edge)
    {
        entity->pos.x = 2 * right_edge - entity->pos.x;
        entity->speed.dx *= -1;
    }

    if (entity->pos.y < 0)
    {
        entity->pos.y *= -1;
        entity->speed.dy *= -1;
    }

    if (entity->pos.y >= bottom_edge)
    {
        entity->pos.y = 2 * bottom_edge - entity->pos.y;
        entity->speed.dy *= -1;
    }
}
