#ifndef SDL_GRAPHIC_H
#define SDL_GRAPHIC_H

#include <stdio.h>
#include "my_types.h"
#include "include/SDL/SDL.h"
#include "my_graphic.h"

#ifdef __cplusplus
extern "C" {
#endif

int sdl_init(void);
void sdl_doit();
void sdl_exit();

void SDL_Pixel(SDL_Surface* surface, int x, int y, Uint32 color);

#ifdef __cplusplus
};
#endif

#endif // SDL_GRAPHIC_H