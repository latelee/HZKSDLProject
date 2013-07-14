#include "include/SDL/SDL.h"
#pragma comment(lib, "lib/SDL.lib")
#pragma comment(lib, "lib/SDLmain.lib")


/////////////////////////////////////////////////////////////////

const int WINDOW_WIDTH = 240;
const int WINDOW_HEIGHT = 320;
const char* WINDOW_TITLE = "SDL Hello World";

SDL_Surface g_screen;

int InitGraphic(SDL_Surface* screen)
{
	const SDL_VideoInfo *info;
	Uint8  video_bpp;
	Uint32 videoflags;
        
	// Initialize SDL
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);

	// Alpha blending doesn't work well at 8-bit color
	info = SDL_GetVideoInfo();
	if ( info->vfmt->BitsPerPixel > 8 )
    {
		video_bpp = info->vfmt->BitsPerPixel;
	}
    else
    {
		video_bpp = 16;
	}
	videoflags = SDL_SWSURFACE | SDL_DOUBLEBUF;
	
	// Set 640x480 video mode
	if ( (screen=SDL_SetVideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,video_bpp,videoflags)) == NULL ) {
		fprintf(stderr, "Couldn't set %ix%i video mode: %s\n",640,480,SDL_GetError());
		return 2;
	}

    SDL_WM_SetCaption(WINDOW_TITLE, 0);

    return 0;
}

//////////////////////////////////////////////////////

int sdl_init(void)
{
    return InitGraphic(&g_screen);
}

void sdl_doit()
{
    SDL_Event event;
    int done = 0;

    while (!done)
    {
        /* Slow down polling */
        SDL_Delay(500);

        /* Check for events */
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                /* Any keypress quits the app... */
            case SDL_QUIT:
                done = 1;
                break;
            default:
                break;
            }
        }
    }
}

void sdl_exit()
{
    SDL_Quit();
}