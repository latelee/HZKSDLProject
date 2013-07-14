#include "my_graphic.h"
#include "sdl_graphic.h"
#include "include/SDL/SDL.h"
#include "sdl_font18.h"
#include "sdl_font24.h"
#include "sdl_font48.h"
#include "font_utils.h"

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

int sdl_test()
{
    sdl_init();

    sdl_old();

    font_18_test();
    font_24_test();
    //font_48_test();
    foo_test();

    sdl_doit();
    sdl_exit();

    return 0;
}