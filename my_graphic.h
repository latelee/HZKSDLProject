#ifndef MY_GRAPHIC_H
#define MY_GRAPHIC_H

#include <stdio.h>
#include "my_types.h"

// somebody must implement these functions
extern int graphic_init(void);
extern void pixel(int x, int y, uint32 color);
extern void myrefresh();
// if you are using color index to show color, do it
extern void init_color(uint32 palette[], int len);

///////////////////////////////////////////////////////////////////////////////

void line(int x1, int y1, int x2, int y2, uint32 color);
void rect(int x1, int y1, int x2, int y2, uint32 color);
void circle(int x, int y, int radius, uint32 color);
void fillcircle(int x, int y, int radius, uint32 color);

///////////////////////////////////////////////////////////////////////////////

void put_string_ascii(int x, int y, const char *s, uint32 color);
void put_string_hz(FILE *fp, int x, int y, const char *s, uint32 color);
void put_font(FILE *fp, int x, int y, const char *s, uint32 color);

#endif // MY_GRAPHIC_H