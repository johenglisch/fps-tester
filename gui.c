#include "gui.h"

#include <SDL2/SDL_image.h>

#include "config.h"
#include "entity.h"


static inline Uint8 html_red(int html);
static inline Uint8 html_green(int html);
static inline Uint8 html_blue(int html);


result init_display(Display *disp, Scene *scene)
{
    SDL_Window *win = NULL;
    SDL_Renderer *render = NULL;
    TTF_Font *font = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) goto_fail(SDL_GetError());
    if (TTF_Init() != 0) goto_fail(TTF_GetError());

    win = SDL_CreateWindow(
            TITLE,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            scene->size.w / PIXEL_SCALE,
            scene->size.h / PIXEL_SCALE,
            WINDOW_FLAGS);
    if (win == NULL) goto_fail(SDL_GetError());

    render = SDL_CreateRenderer(win, -1, RENDERER_FLAGS);
    if (render == NULL) goto_fail(SDL_GetError());

    font = TTF_OpenFont(FONT, 10);
    if (font == NULL) goto_fail(TTF_GetError());

    disp->win = win;
    disp->render = render;
    disp->font = font;
    return SUCCESS;

fail:
    if (render != NULL) SDL_DestroyRenderer(render);
    if (win != NULL) SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
    return FAILURE;
}

void quit_display(Display *disp)
{
    if (disp->render != NULL) SDL_DestroyRenderer(disp->render);
    if (disp->win != NULL) SDL_DestroyWindow(disp->win);
    TTF_Quit();
    SDL_Quit();
}


result draw_scene(Display *disp, Scene *scene)
{
    SDL_Rect dest;
    int sdl_return = 0;

    EntityLink *current = scene->entities;
    Entity *entity = NULL;

    sdl_return = SDL_SetRenderDrawColor(
            disp->render,
            html_red(scene->bg_colour),
            html_green(scene->bg_colour),
            html_blue(scene->bg_colour),
            0xff);
    if (sdl_return < 0) goto_fail(SDL_GetError());

    sdl_return = SDL_RenderClear(disp->render);
    if (sdl_return < 0) goto_fail(SDL_GetError());

    sdl_return = SDL_SetRenderDrawColor(disp->render, 0, 0, 0, 0xff);
    if (sdl_return < 0) goto_fail(SDL_GetError());

    while (current != NULL)
    {
        entity = current->this;

        dest.x = entity->pos.x / PIXEL_SCALE;
        dest.y = entity->pos.y / PIXEL_SCALE;
        dest.w = entity->size.w / PIXEL_SCALE;
        dest.h = entity->size.h / PIXEL_SCALE;

        sdl_return = SDL_RenderCopy(disp->render, entity->img, NULL, &dest);
        if (sdl_return < 0) goto_fail(SDL_GetError());

        current = current->next;
    }

    return SUCCESS;

fail:
    return FAILURE;
}


SDL_Texture *load_image(Display *disp, const char *filename)
{
    SDL_Surface *img_surface;
    SDL_Texture *img_texture;

    img_surface = IMG_Load(filename);
    if (img_surface == NULL) goto_fail(IMG_GetError());

    img_texture = SDL_CreateTextureFromSurface(disp->render, img_surface);
    SDL_FreeSurface(img_surface);
    if (img_texture == NULL) goto_fail(SDL_GetError());

    return img_texture;

fail:
    return NULL;
}


static inline Uint8 html_red(int html)
{
    return (Uint8)((0xff0000 & html) >> 16);
}

static inline Uint8 html_green(int html)
{
    return (Uint8)((0x00ff00 & html) >> 8);
}

static inline Uint8 html_blue(int html)
{
    return (Uint8)(0x0000ff & html);
}
