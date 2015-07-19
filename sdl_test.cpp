#include "my_graphic.h"
#include "sdl_graphic.h"
#include "include/SDL/SDL.h"
#include "sdl_font18.h"
#include "sdl_font24.h"
#include "sdl_font48.h"
#include "sdl_font72.h"
#include "font_utils.h"
#include "show_gamma.h"

#pragma comment(lib, "lib/SDL.lib")
#pragma comment(lib, "lib/SDLmain.lib")

void sdl_old(void)
{
    line(350+1, 1, 350+200, 200, 0xff0000);
    line(340, 0, 340, 479, 0xcbcbcb);
    rect(350+100, 20, 350+200, 100, 0x00ff00);

    put_string_ascii(350, 200, "AbcD", 0x0000ff);
    FILE* fp = fopen("HZK/HZK24K", "rb");
    if (fp == NULL)
        return;
    put_font(fp, 350, 250, "引刀成一快,不负少年头", 0xffffff);
}

int rgb2YCbCr(unsigned int rgbColor, int* Y, int* Cb, int* Cr)
{
    unsigned char r, g, b;
    int y, cb, cr;
    r = (rgbColor&0x00ff0000) >> 16;
    g = (rgbColor&0x0000ff00) >> 8;
    b = rgbColor & 0xff;

    y = (int)( 0.299    * r + 0.587   * g + 0.114   * b);
    cb = (int)(-0.16874 * r - 0.33126 * g + 0.50000 * b + 128);
    if (cb < 0)
        cb = 0;
    cr = (int)( 0.50000 * r - 0.41869 * g - 0.08131 * b + 128);
    if (cr < 0)
        cr = 0;

    *Y = y;
    *Cb = cb;
    *Cr = cr;

    return 0;
}

void show_rainbow()
{
    // 0x7FFF00, 0xFF7D40, 0xFF00FF,
    unsigned int rgbColor[] = {0xFF0000, 0xFF6100, 0xFFFF00, 0x00FF00, 0x00FFFF, 
        0x0000FF, 0xA020F0, 0x000000, 0xFFFFFF, 0xF4A460};

    int cnt = sizeof(rgbColor)/sizeof(rgbColor[0]);
    int y = 0, u = 0, v = 0;
    int k = 0;
    for (int i = 0; i < cnt; i++)
    {
        for (int j = 0; j <  WINDOW_HEIGHT / 10; j++)
            line(0, 0 + k + j, WINDOW_WIDTH-1, 0 + k + j, rgbColor[i]);
            //line(0 + k + j, 0, 0 + k + j, WINDOW_HEIGHT - 1, rgbColor[i]);
        rgb2YCbCr(rgbColor[i], &y, &u, &v);
        //printf("%d y: 0x%x u: 0x%x v: 0x%x\n", i, y, u, v);
        printf("0x%x,", (y<<16) | (u<<8) | (v));
        k += WINDOW_HEIGHT / 10;
    }
}

#include <math.h>
// 正弦波
void draw_sin_con()
{
    double y = 0;
    int x = 0;
    int m = 0;

    for(y=1;y>=0;y-=0.1)
    {
        m=asin(y)*10;

        for(x=1;x<m;x++)
        {
            printf(" ");
        }
        printf("*");

        for(;x<31-m;x++)
        {
            printf(" ");
        }
        printf("*\n");
    }
    for(y=-0.1;y>=-1;y-=0.1)
    {
        m=abs(asin(y)*10)+31;
        for(x=1;x<=m;x++)
        {
            printf(" ");
        }
        printf("*");
        for(;x<93-m;x++)
        {
            printf(" ");
        }
        printf("*\n");
    }
}

void draw_sin()
{
#define PI 3.14159265

    double param = 0;
    int org_y = 240;
    int x = 0;
    int y = 0;
    int i = 0;

    sdl_init();

    line(0, org_y, 400, org_y, 0xffffff);

    for (i = 1; i < 10; i++)
    {
        for(x = 0; x < 360; x++)
        {
            y = (int)(sin(x*PI/180 * i) * 100);
            printf("%d %d\n", x, y);
            pixel(x, org_y - y, 0xff0000);
            myrefresh();
        }
        Sleep(1000);
    }

    sdl_doit();
    sdl_exit();

}

int sdl_test()
{
    sdl_init();

    sdl_old();

    font_18_test();
    font_24_test();
    font_48_test();
	font_72_test();
    //foo_test();
    //bar_test();
    //ShowGamma();
    //ttf_test();
    //show_rainbow();

    sdl_doit();
    sdl_exit();

    return 0;
}