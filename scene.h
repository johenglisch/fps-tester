#ifndef SCENE_H_
#define SCENE_H_

#include "entity.h"
#include "error.h"


//  STRUCTURES  //////////////////////////////////////////////////////

typedef struct EntityLink
{
    Entity *this;
    struct EntityLink *next;
}
EntityLink;

typedef struct
{
    Size size;
    EntityLink *entities;
    int bg_colour;
}
Scene;


//  PROTOTYPES  //////////////////////////////////////////////////////

result add_entity(Scene *scene, Entity *entity);
Entity *pop_entity(Scene *scene);

void clear_scene(Scene *scene);

void update_scene(Scene *scene, int time_ms);

#endif
