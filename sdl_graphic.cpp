#include "sdl_graphic.h"
#include "include/SDL/SDL.h"
#pragma comment(lib, "lib/SDL.lib")
#pragma comment(lib, "lib/SDLmain.lib")

/////////////////////////////////////////////////////////////////using color index

#define XORMODE	0x80000000

static unsigned int colormap [256];

union multiptr {
    unsigned char *p8;
    unsigned short *p16;
    unsigned long *p32;
};

static void setColor(SDL_Surface* surface, Uint32 colidx, Uint32 value)
{
    Uint8 red, green, blue;
    Uint32 pixel;
    red = (value >> 16) & 0xff;
    green = (value >> 8) & 0xff;
    blue = value & 0xff;
    pixel = SDL_MapRGB(surface->format, red, green, blue);  
    colormap[colidx] = pixel;
}

static inline void __setpixel(union multiptr loc, int bpp, Uint32 xormode, Uint32 color)
{
    switch(bpp)
    {
    case 4:
        if (xormode)
            *loc.p32 ^= color;
        else
            *loc.p32 = color;
        break;
    case 1:
    default:
        if (xormode)
            *loc.p8 ^= color;
        else
            *loc.p8 = color;
        break;
    case 2:
        if (xormode)
            *loc.p16 ^= color;
        else
            *loc.p16 = color;
        break;

    }
}

// xormode×÷ÓÃ£¿
static void SDL_PixelIdx(SDL_Surface* surface, int x, int y, Uint32 colidx)
{
    Uint32 xormode = 0;
    int bpp = surface->format->BytesPerPixel;
    union multiptr loc;
    loc.p8 = (unsigned char *)surface->pixels + y * surface->pitch + x * bpp;

    xormode = colidx & XORMODE;
    colidx &= ~XORMODE;
    //printf("xormode: %d %d\n", xormode, colidx);
    if ( SDL_MUSTLOCK(surface) )
    {  
        if ( SDL_LockSurface(surface) < 0 )
            return;  
    }

    __setpixel(loc, bpp, xormode, colormap[colidx]);

    if ( SDL_MUSTLOCK(surface) )
        SDL_UnlockSurface(surface);
}

////////////////////////////////end of color index

static void SDL_PixelNolock(SDL_Surface* surface, int x, int y, Uint32 color)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 4:
        *(Uint32 *)p = color;
        break;
    case 1:
        *p = color;
        break;
    case 2:
        *(Uint16 *)p = color;
        break;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (color >> 16) & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = color & 0xff;
        }
        else
        {
            p[0] = color & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = (color >> 16) & 0xff;
        }
        break;
    }
}

static void SDL_PixelColor(SDL_Surface* surface, int x, int y, Uint32 color)
{
    if (SDL_MUSTLOCK(surface))
    {
        if (SDL_LockSurface(surface) < 0)
        {
            return;
        }
    }

    SDL_PixelNolock(surface, x, y, color);

    if (SDL_MUSTLOCK(surface))
    {
        SDL_UnlockSurface(surface);
    }
}

void SDL_Pixel(SDL_Surface* surface, int x, int y, Uint32 color)
{
#ifdef USING_COLORIDX
    SDL_PixelIdx(surface, x, y, color);
#else
    SDL_PixelColor(surface, x, y, color);
#endif
}

/////////////////////////////////////////////////////////////////
const int WINDOW_WIDTH = 480;
const int WINDOW_HEIGHT = 320;
const char* WINDOW_TITLE = "SDL Hello World -- by Late Lee";

SDL_Surface* g_screen = NULL;

int InitGraphic(SDL_Surface** screen)
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
    if ( (*screen=SDL_SetVideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,video_bpp,videoflags)) == NULL ) {
        fprintf(stderr, "Couldn't set %ix%i video mode: %s\n",WINDOW_WIDTH,WINDOW_HEIGHT,SDL_GetError());
        return 2;
    }

    SDL_WM_SetCaption(WINDOW_TITLE, 0);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

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
                //case SDL_KEYDOWN:
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

int graphic_init(void)
{
    return InitGraphic(&g_screen);
}

void pixel(int x, int y, Uint32 color)
{
    SDL_Pixel(g_screen, x, y, color);
}

void myrefresh()
{
    SDL_Flip(g_screen);
}

void init_color(Uint32 palette[], int len)
{
    int i = 0;
    for (i = 0; i < len; i++)
        setColor(g_screen, i, palette[i]);
}

/*-----------------------------setup the color index-----------------------------------*/
/* 0.black 1.xx 2.white 3.xx 4.xx 5.xx 6.purple 7.red 8.green 9.blue 10. yellow 11. gold */
static unsigned int palette [] =
{
    0x000000, 0xffe080, 0xffffff, 0xe0c0a0, 0x304050, 0x80b8c0,
    0x6600cc, 0xff0000, 0x008000, 0x0000ff, 0xffff00, 0xffd700, 
    0xcbcbcb, 
};
#define NR_COLORS (sizeof (palette) / sizeof (palette [0]))

void setupColor()
{
    init_color(palette, NR_COLORS);
}
