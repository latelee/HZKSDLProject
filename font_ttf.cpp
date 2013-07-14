#include <stdlib.h>
#include "font_utils.h"
#include "sdl_graphic.h"

// 横向
static void display(int x, int y, unsigned char* lattice, int width, int height)
{
    char tmp = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //tmp = lattice[i * width + j];
            tmp = *lattice++;
            if (tmp & 0x01)
                pixel(x + j, y + i, 0); // 黑色为字
            else
                pixel(x + j, y + i, 0xffffff);
            //Sleep(10);
            //myrefresh();
        }
        //Sleep(1000);
        //myrefresh();
    }
    myrefresh();
}

// 竖向
static void display1(int x, int y, unsigned char* lattice, int width, int height)
{
    char tmp = 0;
    for (int i = 0; i < width; i++)
    {
        // 显示一列
        for (int j = 0; j < height; j++)
        {
            tmp = lattice[j * width + i];
            if (tmp & 0x01)
                pixel(x + i, y + j, 0xffffff);
            //Sleep(10);
            //myrefresh();
        }
        Sleep(30);
        myrefresh();
    }
    myrefresh();
}

void ttf_test()
{
    int size = 0;
    unsigned char* buffer = NULL;
    int width = 0;  //= 1600;
    int height = 38;    // 此处的高必须与生成的点阵的高度一致

    FILE* fp = fopen("bitmap.bin", "rb");
    if (fp == NULL)
    {
        printf("error open file.\n");
        return;
    }
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    buffer = (unsigned char*)malloc(size);
    memset(buffer, '\0', size);

    fread(buffer, 1, size, fp);

    width = size / height;

    printf("width: %d height: %d\n", width, height);
    display(1, 100, buffer, width, height);
}
