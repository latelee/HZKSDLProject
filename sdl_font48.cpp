#include "sdl_font48.h"
#include "sdl_graphic.h"

// 点阵大小
#define CHARACTER_WIDTH 48
#include "font_size.h"

// 逐列式，低位在前
static void display_lattice_column_low(int x, int y, unsigned char* lattice, int len)
{
    int iTemp1 = 0;
    int iTemp2 = 0;
    unsigned char* p = lattice;
    int column = len / HALFWIDTH_SIZE;
    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < CHARACTER_HALFWIDTH; j++)
        {
            // 6的由来：48/8 = 6
            iTemp1 = (p[j*6+i*HALFWIDTH_SIZE + 0]) | (p[j*6 +i*HALFWIDTH_SIZE + 1] << 8) | 
                (p[j*6 +i*HALFWIDTH_SIZE + 2] << 16);
            iTemp2 = (p[j*6+i*HALFWIDTH_SIZE + 3]) | (p[j*6 +i*HALFWIDTH_SIZE + 4] << 8) | 
                (p[j*6 +i*HALFWIDTH_SIZE + 5] << 16);
            for (int k = 0; k < CHARACTER_HEIGHT/2; k++)
            {
                /* 逐位相与，为1者打印 */
                // 上半部分
                if(iTemp1 & (0x000001<<k))
                    pixel(x + j + i*CHARACTER_HALFWIDTH, y + k, 0xffffff);
                else
                    pixel(x + j + i*CHARACTER_HALFWIDTH, y + k, 0x000000);
                // 下半部分
                if(iTemp2 & (0x000001<<k))
                    pixel(x + j + i*CHARACTER_HALFWIDTH, y + k + CHARACTER_HEIGHT/2, 0xffffff);
                else
                    pixel(x + j + i*CHARACTER_HALFWIDTH, y + k + CHARACTER_HEIGHT/2, 0x000000);

            }
        }
    }

    myrefresh();
}

static unsigned char wnt[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x20,0x00,0x80,0x00,0x00,0x00,0x20,0x00,0x80,0x01,0x00,0x00,
0x20,0x00,0x80,0x03,0x00,0x00,0x60,0x00,0x80,0x03,0x00,0x00,0x30,0x00,0xC0,0x01,
0x00,0x00,0x30,0x00,0xC0,0x01,0x00,0x00,0xF0,0x01,0xC0,0x00,0x00,0x00,0xF0,0xFF,
0xFF,0x00,0x00,0x00,0xB0,0xFF,0x7F,0x00,0x30,0x00,0x30,0x84,0x60,0x00,0xF0,0x00,
0x30,0x86,0x60,0x00,0xE0,0x1F,0x18,0xC6,0x30,0x00,0x60,0xFF,0x18,0xC6,0x30,0x00,
0x20,0x46,0x18,0x00,0x18,0x00,0x20,0x46,0x18,0x00,0x18,0x08,0x20,0x42,0xF8,0xFF,
0xFF,0x3F,0x30,0x42,0xF8,0xFF,0xFF,0x3F,0x30,0x62,0x8C,0x00,0x04,0x01,0x30,0x63,
0x0C,0x00,0x04,0x01,0x10,0x63,0x0C,0x00,0x84,0x00,0x10,0x63,0x0C,0x34,0xC0,0x00,
0x10,0x63,0x0C,0x26,0x60,0x00,0x18,0x21,0x0C,0x66,0x70,0x00,0x18,0x20,0x0E,0xC2,
0x38,0x00,0x18,0x60,0x0E,0x83,0x1D,0x00,0x1C,0x7C,0x06,0x83,0x0F,0x00,0xDC,0x1F,
0x06,0x81,0x07,0x00,0xFC,0x07,0x86,0xE1,0x0F,0x00,0xF8,0x01,0x86,0xFB,0x1D,0x00,
0x78,0x00,0x86,0x7F,0x38,0x00,0x30,0x00,0x87,0x1F,0x78,0x00,0x00,0x00,0x07,0x07,
0xF0,0x00,0x00,0x00,0x07,0x02,0xE0,0x01,0x00,0x00,0x07,0x00,0xE0,0x03,0x00,0x00,
0x06,0x00,0xC0,0x03,0x00,0x00,0x02,0x00,0xC0,0x03,0x00,0x00,0x00,0x00,0x80,0x03,
0x00,0x00,0x00,0x00,0x80,0x03,0x00,0x00,0x00,0x00,0x80,0x03,0x00,0x00,0x00,0x00,
0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"最",0*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,
0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,
0x00,0x01,0x80,0x01,0x00,0x00,0x00,0x03,0xC0,0x01,0x00,0x00,0x00,0x03,0xC0,0x00,
0x00,0x00,0x00,0x03,0xE0,0x00,0x00,0x00,0x00,0x03,0x78,0x00,0x00,0x00,0x00,0x03,
0x3C,0x00,0x00,0x00,0x00,0x03,0x1E,0x00,0x00,0x00,0x00,0x81,0x0F,0x00,0x00,0x00,
0x80,0xF9,0x07,0x00,0x00,0x00,0x80,0xF9,0x01,0x00,0x60,0x00,0x80,0xF9,0x01,0x00,
0xE0,0x03,0x80,0x31,0x03,0x00,0xE0,0x3F,0x80,0x01,0x02,0x00,0x20,0xFF,0x83,0x00,
0x06,0x00,0x20,0x88,0xC7,0x00,0x0C,0x00,0x20,0x0C,0xC3,0x00,0x0C,0x00,0x20,0x0C,
0xC3,0x00,0x18,0x00,0x30,0x0C,0xC3,0x07,0x38,0x00,0x30,0x0C,0xE3,0xFF,0x3F,0x00,
0x30,0x04,0xE3,0xFF,0x7F,0x00,0x10,0x04,0x61,0x20,0x60,0x00,0x10,0x04,0x61,0x60,
0xE0,0x00,0x18,0x80,0x61,0x30,0xC0,0x01,0x18,0xE0,0x73,0x30,0xC0,0x01,0xF8,0xFF,
0x71,0x30,0xC0,0x03,0xF8,0x3F,0x30,0x30,0x80,0x03,0xF0,0x03,0x30,0x30,0x80,0x07,
0xF0,0x00,0x30,0x30,0x80,0x0F,0x60,0x00,0x38,0x10,0x00,0x0F,0x00,0x00,0x38,0x00,
0x00,0x0F,0x00,0x00,0x18,0x00,0x00,0x1F,0x00,0x00,0x18,0x00,0x00,0x1F,0x00,0x00,
0x10,0x00,0x00,0x1E,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x0E,
0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,
0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,
0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x04,/*"是",1*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,
0x00,0x03,0x00,0x00,0x00,0x00,0x80,0x03,0x00,0x00,0x00,0x00,0x80,0x03,0x00,0x00,
0x00,0x00,0x80,0x03,0x00,0x00,0x00,0x00,0x80,0x03,0x00,0x00,0x00,0x00,0x80,0x03,
0x00,0x00,0x00,0x00,0x80,0x03,0x00,0x00,0x00,0x00,0x80,0x03,0x00,0x00,0x00,0x00,
0x80,0x03,0x00,0x00,0x00,0x00,0x80,0x03,0x00,0x00,0x00,0x00,0x80,0x01,0x00,0x00,
0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x80,0x01,
0x00,0x00,0x00,0x00,0xC0,0x01,0x00,0x00,0x00,0x00,0xC0,0x01,0x00,0x00,0x00,0x00,
0xC0,0x01,0x00,0x00,0x00,0x00,0xC0,0x01,0x00,0x00,0x00,0x00,0xC0,0x01,0x00,0x00,
0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,
0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,
0xE0,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,
0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,
0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,
0xF0,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,
0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,
0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"一",2*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,
0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,
0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,
0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x01,0x38,
0x00,0x00,0x00,0x80,0x00,0x18,0x00,0x00,0x00,0x60,0x00,0x18,0x00,0x00,0x00,0x70,
0x04,0x18,0x00,0x00,0x00,0x38,0x3C,0x18,0x00,0x00,0x00,0x1C,0xFC,0x1F,0x00,0x00,
0x00,0x0F,0xFC,0x0F,0x00,0x00,0x80,0x07,0x04,0x0C,0x00,0x00,0xE0,0x07,0x04,0x0C,
0x00,0x00,0xFC,0x07,0x04,0x0C,0x00,0x00,0x7C,0x06,0x04,0x0C,0x00,0x00,0x38,0x06,
0x06,0x0C,0x00,0x00,0x00,0x07,0x06,0x04,0x00,0x00,0x00,0x07,0x06,0x06,0x00,0x00,
0x00,0x03,0x06,0x06,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x1F,0x80,0xFF,0xFF,0xFF,
0xFF,0x3F,0x80,0xFB,0xFF,0xFF,0x00,0x00,0x80,0x03,0x03,0x06,0x00,0x00,0x80,0x01,
0x03,0x06,0x00,0x00,0x80,0x81,0x03,0x07,0x00,0x00,0xC0,0x81,0x03,0x07,0x00,0x00,
0xC0,0x81,0x01,0x03,0x00,0x00,0xC0,0x80,0x01,0x03,0x00,0x00,0x80,0x80,0x01,0x03,
0x00,0x00,0x00,0x80,0x01,0x03,0x00,0x00,0x00,0x00,0x01,0x03,0x00,0x00,0x00,0x00,
0x00,0x03,0x00,0x00,0x00,0x00,0x80,0x07,0x00,0x00,0x00,0x00,0x80,0x07,0x00,0x00,
0x00,0x00,0x80,0x07,0x00,0x00,0x00,0x00,0x80,0x07,0x00,0x00,0x00,0x00,0x00,0x07,
0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"年",3*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,
0x20,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,
0x40,0x00,0x18,0x00,0x00,0x00,0x40,0x00,0x0C,0x00,0x00,0x00,0xC0,0x00,0x06,0x00,
0x00,0x00,0xC0,0x00,0x07,0x00,0x00,0x00,0xC0,0x80,0x03,0x00,0x00,0x00,0x40,0xC0,
0x01,0x00,0x00,0x00,0x61,0xE0,0x00,0x00,0x00,0x02,0x61,0xF0,0x00,0x00,0x00,0x06,
0x61,0x3C,0x00,0x00,0x00,0x06,0x61,0xFE,0x01,0x00,0x00,0x86,0xE1,0xEF,0xFF,0x1F,
0x00,0x86,0xF1,0xE3,0xFF,0x1F,0x00,0x86,0xFD,0x60,0x08,0x06,0x02,0xE6,0x3F,0x20,
0x08,0x06,0xFE,0xFF,0x3F,0x30,0x08,0x02,0xFE,0xFF,0x31,0x30,0x0C,0x02,0xFC,0xCF,
0x38,0x30,0x0C,0x02,0x08,0xC3,0x38,0x30,0x0C,0x03,0x80,0xC3,0x18,0x10,0x0C,0x03,
0x80,0xE3,0x38,0x18,0x00,0x03,0x80,0x61,0x78,0x38,0x00,0x06,0xC0,0x61,0xD8,0x38,
0x00,0x1F,0xC0,0x61,0x9C,0xF1,0xFF,0x7F,0xC0,0x71,0x1C,0xE3,0xFF,0x1F,0xC0,0x30,
0x1C,0xE6,0xFF,0x03,0xC0,0x20,0x0C,0xCC,0x00,0x00,0xC0,0x00,0x0C,0x1C,0x00,0x00,
0x00,0x00,0x0E,0x38,0x00,0x00,0x00,0x00,0x0E,0x70,0x00,0x00,0x00,0x00,0x0E,0xF0,
0x00,0x00,0x00,0x00,0x0E,0xE0,0x01,0x00,0x00,0x00,0x0C,0xC0,0x03,0x00,0x00,0x00,
0x04,0xC0,0x07,0x00,0x00,0x00,0x00,0x80,0x0F,0x00,0x00,0x00,0x00,0x80,0x0F,0x00,
0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,
0x0E,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,
0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"春",4*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,
0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x80,0x00,0x00,0x00,
0xE0,0x00,0x40,0x00,0x00,0x00,0x60,0x00,0x20,0x00,0x00,0x00,0x60,0x00,0x30,0x00,
0x00,0x00,0x60,0x00,0x18,0x00,0x00,0x00,0x70,0x00,0x18,0x00,0x00,0x00,0xF8,0x0F,
0x0C,0x00,0x60,0xF0,0xFF,0x1D,0x06,0x00,0xE0,0xFF,0x3F,0x38,0x07,0x00,0xC0,0xFF,
0x30,0xF0,0x03,0x00,0xC0,0x07,0x10,0xE0,0x01,0x00,0x00,0x00,0x18,0xF8,0x01,0x00,
0x00,0x00,0x18,0xBF,0x03,0x00,0x00,0x00,0xF9,0x8F,0x07,0x00,0x00,0x80,0xFF,0x03,
0x0F,0x00,0x00,0x00,0xFF,0x00,0x1E,0x00,0x00,0x00,0x8F,0x01,0x38,0x00,0x00,0x00,
0x80,0x01,0x00,0x00,0x00,0x00,0xC0,0x01,0x00,0x00,0x00,0x04,0xC0,0x01,0x00,0x00,
0x00,0x04,0xC0,0x00,0x00,0x00,0x00,0x0C,0xC0,0x00,0x00,0x00,0x00,0x0E,0xC0,0x00,
0x20,0x00,0x00,0x06,0xC0,0x00,0x40,0x00,0x00,0x06,0x60,0x00,0xC0,0x00,0x00,0x06,
0x63,0x00,0xC0,0x01,0x00,0x02,0x67,0x00,0xC0,0x07,0x00,0x03,0x7F,0x00,0xC0,0x07,
0x00,0x83,0xFD,0x03,0xF8,0x07,0x00,0xE3,0xF0,0xFF,0xFF,0x01,0x80,0x79,0xB0,0xFF,
0x7F,0x00,0x80,0x3F,0x30,0xE0,0x00,0x00,0x80,0x1F,0x30,0x00,0x00,0x00,0x80,0x0F,
0x30,0x00,0x00,0x00,0x00,0x07,0x30,0x00,0x00,0x00,0x00,0x03,0x38,0x00,0x00,0x00,
0x00,0x02,0x38,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x38,0x00,
0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,
0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"好",5*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x08,0x80,0x00,0x00,0x00,0x00,0x04,0xC0,0x00,0x00,0x00,
0x00,0x03,0x60,0x00,0x00,0x00,0x80,0x01,0x20,0x00,0x00,0x00,0xE0,0x00,0x30,0x00,
0x00,0x00,0xF8,0x00,0x18,0x00,0x00,0x00,0xBE,0x00,0x0C,0x00,0x00,0x80,0x8F,0x01,
0x06,0x00,0x00,0xF8,0x03,0x83,0x03,0x00,0xC0,0xFF,0x02,0xC3,0x01,0x00,0x80,0x3F,
0x03,0xE6,0x00,0x00,0x80,0x0F,0x03,0x7C,0x00,0x00,0x00,0x03,0x03,0x3E,0x00,0x00,
0x00,0x00,0x81,0x3F,0x00,0x00,0x00,0x80,0xF1,0x73,0x00,0x00,0x00,0xC0,0xFF,0xE1,
0x00,0x00,0x00,0xC0,0x7F,0xC0,0x00,0x00,0x00,0x80,0x0F,0xC0,0x01,0x00,0x00,0x00,
0x03,0x80,0x03,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,
0x00,0x00,0x00,0x00,0x1E,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x30,0x00,0x00,0x00,
0x38,0x00,0xF0,0xFF,0xFF,0xFF,0x79,0x00,0xF0,0xFF,0xFF,0xFF,0xF3,0x00,0xE0,0x1F,
0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0xE0,0x01,0x00,0x00,0x03,0x00,0xE0,0x01,
0x00,0x00,0x06,0x00,0xE0,0x03,0x00,0x00,0x06,0x00,0xC0,0x03,0x00,0x00,0x0E,0x00,
0xC0,0x03,0x00,0x00,0x1E,0x00,0xC0,0x03,0x00,0x00,0x3C,0x00,0xC0,0x03,0x00,0x00,
0x3C,0x00,0x80,0x03,0x00,0x00,0x78,0x00,0x80,0x03,0x00,0x00,0x70,0x00,0x80,0x03,
0x00,0x00,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,
0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"处",6*/
};

void font_48_test()
{
    display_lattice_column_low(0, 400, wnt, sizeof(wnt));
}