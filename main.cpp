#include <stdio.h>
#include "my_graphic.h"
#include "sdl_graphic.h"

#include "include/SDL/SDL.h"
#pragma comment(lib, "lib/SDL.lib")
#pragma comment(lib, "lib/SDLmain.lib")

int sdl_test()
{
    sdl_init();

    line(1, 1, 200, 200, 0xff0000);
    rect(100, 20, 200, 100, 0x00ff00);

    put_string_ascii(10, 200, "AbcD", 0x0000ff);
    FILE* fp = fopen("HZK/HZK24K", "rb");
    if (fp == NULL)
        return -1;
    put_font(fp, 10, 250, "引刀成一快,不负少年头Abc", 0xffffff);

    sdl_doit();
    sdl_exit();

    return 0;
}

int main(int argc, char* argv[])
{
    sdl_test();
    return 0;
}
