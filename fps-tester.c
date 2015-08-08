#include "fps-tester.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "config.h"
#include "tools.h"
#include "clock.h"
#include "entity.h"
#include "gui.h"
#include "scene.h"
#include "error.h"

#define SMILEY_COUNT 7
#define FPS_SETTINGS 5


int main()
{
    Entity smileys[SMILEY_COUNT];
    Scene scene =
    {
        .size = { .w=1024000, .h=768000 },
        .bg_colour = 0x87CEEB,
        .entities = NULL,
    };

    int fps_list[FPS_SETTINGS] = { 15, 24, 30, 60, 120 };
    ulong fps_index = 0;
    Clock clock =
    {
        .running = 0,
        .fps = fps_list[fps_index],
        .last_tick = 0,
    };
    Display gui;

    SDL_Event event;
    SDL_Texture *small_face = NULL;
    SDL_Texture *face = NULL;
    SDL_Texture *big_face = NULL;
    char window_title[TITLE_LEN];

    int return_code = EXIT_FAILURE;
    int dt = 0;
    result res = FAILURE;

    res = init_display(&gui, &scene);
    if (res == FAILURE) goto_fail("Could not start up graphical interface.");

    small_face = load_image(&gui, "images/smiley-small.png");
    face = load_image(&gui, "images/smiley.png");
    big_face = load_image(&gui, "images/smiley-big.png");
    if (small_face == NULL || face == NULL || big_face == NULL)
    {
        goto_fail("Could not load all textures.");
    }

    smileys[0].pos.x = 290000;
    smileys[0].pos.y = 210000;
    smileys[0].size.w = 30000;
    smileys[0].size.h = 30000;
    smileys[0].speed.dx = 200;
    smileys[0].speed.dy = 235;
    smileys[0].img = small_face;
    add_entity(&scene, &smileys[0]);

    smileys[1].pos.x = 30000;
    smileys[1].pos.y = 200000;
    smileys[1].size.w = 50000;
    smileys[1].size.h = 50000;
    smileys[1].speed.dx = -165;
    smileys[1].speed.dy = 145;
    smileys[1].img = face;
    add_entity(&scene, &smileys[1]);

    smileys[2].pos.x = 50000;
    smileys[2].pos.y = 80000;
    smileys[2].size.w = 50000;
    smileys[2].size.h = 50000;
    smileys[2].speed.dx = 90;
    smileys[2].speed.dy = -50;
    smileys[2].img = face;
    add_entity(&scene, &smileys[2]);

    smileys[3].pos.x = 100000;
    smileys[3].pos.y = 150000;
    smileys[3].size.w = 50000;
    smileys[3].size.h = 50000;
    smileys[3].speed.dx = -80;
    smileys[3].speed.dy = -90;
    smileys[3].img = face;
    add_entity(&scene, &smileys[3]);

    smileys[4].pos.x = 295000;
    smileys[4].pos.y = 100000;
    smileys[4].size.w = 50000;
    smileys[4].size.h = 50000;
    smileys[4].speed.dx = 120;
    smileys[4].speed.dy = 0;
    smileys[4].img = face;
    add_entity(&scene, &smileys[4]);

    smileys[5].pos.x = 42000;
    smileys[5].pos.y = 42000;
    smileys[5].size.w = 150000;
    smileys[5].size.h = 150000;
    smileys[5].speed.dx = 30;
    smileys[5].speed.dy = 45;
    smileys[5].img = big_face;
    add_entity(&scene, &smileys[5]);

    smileys[6].pos.x = 255000;
    smileys[6].pos.y = 127000;
    smileys[6].size.w = 150000;
    smileys[6].size.h = 150000;
    smileys[6].speed.dx = 350;
    smileys[6].speed.dy = -325;
    smileys[6].img = big_face;
    add_entity(&scene, &smileys[6]);

    LoopStatus loop_status = RUNNING;
    do
    {
        dt = next_tick(&clock);
        if (dt == 0) continue;

        snprintf(
                window_title, TITLE_LEN, TITLE " - %d/%d fps", 1000 / dt,
                fps_list[fps_index]);

        update_scene(&scene, dt);

        if (draw_scene(&gui, &scene) != SUCCESS)
        {
            goto_fail("Could not draw scene");
        }

        if (draw_text(&gui, window_title, 10, 10) != SUCCESS)
        {
            goto_fail("Could not draw status text");
        }

        SDL_RenderPresent(gui.render);
        SDL_SetWindowTitle(gui.win, window_title);

        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) loop_status = STOPPED;
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        loop_status = STOPPED;
                        break;
                    case SDLK_PLUS:
                        if (fps_index < FPS_SETTINGS - 1)
                        {
                            fps_index += 1;
                            clock.fps = fps_list[fps_index];
                        }
                        break;
                    case SDLK_MINUS:
                        if (fps_index > 0)
                        {
                            fps_index -= 1;
                            clock.fps = fps_list[fps_index];
                        }
                        break;
                }
            }
        }
    }
    while (loop_status == RUNNING);

    return_code = EXIT_SUCCESS;
    // fall through to cleanup

fail:
    clear_scene(&scene);
    SDL_DestroyTexture(big_face);
    SDL_DestroyTexture(face);
    quit_display(&gui);
    return return_code;
}
