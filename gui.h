#ifndef GUI_H_
#define GUI_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "scene.h"
#include "error.h"


//  CONSTANTS  ///////////////////////////////////////////////////////

// All size and position values are considered Millipixels
#define PIXEL_SCALE 1000

#define RENDERER_FLAGS (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
#define WINDOW_FLAGS SDL_WINDOW_FULLSCREEN


//  STRUCTURES  //////////////////////////////////////////////////////

typedef struct
{
    SDL_Window *win;
    SDL_Renderer *render;
    TTF_Font *font;
    SDL_Color font_colour;
}
Display;


//  PROTOTYPES  //////////////////////////////////////////////////////

result init_display(Display *disp, Scene *scene);
void quit_display(Display *disp);

result draw_scene(Display *disp, Scene *scene);
result draw_text(Display *disp, const char *text, int x, int y);

SDL_Texture *load_image(Display *disp, const char *filename);

#endif
