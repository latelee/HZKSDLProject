#include <windows.h>
#include <time.h>

#include "include/SDL/SDL.h"
#include "sdl_graphic.h"

int sdl_test()
{
    sdl_init();
    sdl_doit();
    sdl_exit();

    return 0;
}

int main(int argc, char* argv[])
{
    sdl_test();

    return 0;
}