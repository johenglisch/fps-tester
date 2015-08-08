#include "scene.h"

result add_entity(Scene *scene, Entity *entity)
{
    EntityLink *new_elem = malloc(sizeof(EntityLink));
    if (new_elem == NULL) goto_fail(MEMORY_ERROR);

    new_elem->this = entity;
    new_elem->next = scene->entities;

    scene->entities = new_elem;

    return SUCCESS;

fail:
    return FAILURE;
}

Entity *pop_entity(Scene *scene)
{
    if (scene->entities == NULL) return NULL;

    EntityLink *top_elem = scene->entities;

    Entity *entity = top_elem->this;
    scene->entities = top_elem->next;

    free(top_elem);

    return entity;
}


void clear_scene(Scene *scene)
{
    EntityLink *current = scene->entities;
    while (current != NULL)
    {
        current = current->next;
        free(current);
    }
    scene->entities = NULL;
}


void update_scene(Scene *scene, int time_ms)
{
    EntityLink *current = scene->entities;

    while (current != NULL)
    {
        move_entity(current->this, time_ms);
        bounce_off_wall(current->this, &scene->size);
        current = current->next;
    }
}
