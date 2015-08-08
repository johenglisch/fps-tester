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

    font = TTF_OpenFont(FONT, 16);
    if (font == NULL) goto_fail(TTF_GetError());
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);

    disp->win = win;
    disp->render = render;
    disp->font = font;
    disp->font_colour.r = 0xff;
    disp->font_colour.b = 0x00;
    disp->font_colour.g = 0x00;
    disp->font_colour.a = 0x80;

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


result draw_text(Display *disp, const char *text, int x, int y)
{
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect dest;

    surface = TTF_RenderText_Solid(disp->font, text, disp->font_colour);
    if (surface == NULL) goto_fail(TTF_GetError());
    texture = SDL_CreateTextureFromSurface(disp->render, surface);
    if (texture == NULL) goto_fail(SDL_GetError());

    dest.x = x;
    dest.y = y;
    dest.w = surface->w;
    dest.h = surface->h;

    if (SDL_RenderCopy(disp->render, texture, NULL, &dest) != 0)
    {
        goto_fail(SDL_GetError());
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    return SUCCESS;

fail:
    if (texture != NULL) SDL_DestroyTexture(texture);
    if (surface != NULL) SDL_FreeSurface(surface);
    return FAILURE;
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
