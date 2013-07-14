#include <stdlib.h>             /**< abs */
#include <string.h>
#include "my_graphic.h"

void line(int x1, int y1, int x2, int y2, uint32 color)
{
	int tmp;
	int dx = x2 - x1;
	int dy = y2 - y1;

	if (abs(dx) < abs(dy))
    {
		if (y1 > y2)
        {
			tmp = x1; x1 = x2; x2 = tmp;
			tmp = y1; y1 = y2; y2 = tmp;
			dx = -dx; dy = -dy;
		}
		x1 <<= 16;
		/* dy is apriori >0 */
		dx = (dx << 16) / dy;
		while (y1 <= y2)
        {
			pixel(x1 >> 16, y1, color);
			x1 += dx;
			y1++;
		}
	}
    else
    {
		if (x1 > x2)
        {
			tmp = x1; x1 = x2; x2 = tmp;
			tmp = y1; y1 = y2; y2 = tmp;
			dx = -dx; dy = -dy;
		}
		y1 <<= 16;
		dy = dx ? (dy << 16) / dx : 0;
		while (x1 <= x2)
        {
			pixel(x1, y1 >> 16, color);
			y1 += dy;
			x1++;
		}
	}
    myrefresh();
}

void rect(int x1, int y1, int x2, int y2, uint32 color)
{
	line(x1, y1, x2, y1, color);
	line(x2, y1, x2, y2, color);
	line(x2, y2, x1, y2, color);
	line(x1, y2, x1, y1, color);
}

static void _circle_8(int x, int y, int xc, int yc, uint32 color)
{
	pixel(x + xc, y + yc, color);
	pixel(x - xc, y + yc, color);
	pixel(x + xc, y - yc, color);
	pixel(x - xc, y - yc, color);
	pixel(x + yc, y + xc, color);
	pixel(x - yc, y + xc, color);
	pixel(x + yc, y - xc, color);
	pixel(x - yc, y - xc, color);
}

// Bresenham
void circle(int x, int y, int radius, uint32 color)
{
	int xc = 0;
	int yc = radius;
	int d = 3 - (radius << 1);	// 3 - radius*2
	
	while (xc <= yc)
    {
		_circle_8(x, y, xc, yc, color);
		if (d < 0)
        {
			d += (xc << 2)+ 6;	// d = d+xc*4+6
		}
        else
        {
			d += ( (xc - yc) << 2) + 10;	// d=d+(xc-yc)*4+10
			yc--;
		}
		xc++;
	}

    myrefresh();
}

void fillcircle(int x, int y, int radius, uint32 color)
{
	int i  = 0;
	int xc = 0;
	int yc = radius;
	int d  = 3 - (radius << 1);	// 3 - radius*2
	
	while (xc <= yc)
    {
		for (i = xc; i <= yc; i++)
			_circle_8(x, y, xc, i, color);	// fill it
		if (d < 0)
        {
			d += (xc << 2)+ 6;	// d = d+xc*4+6
		}
        else
        {
			d += ( (xc - yc) << 2) + 10;	// d=d+(xc-yc)*4+10
			yc--;
		}
		xc++;
	}
}

/******************************************************************************
                                   点阵显示 
汉字字库为UCDOS中的字库文件
******************************************************************************/


// 16 or 24
#define HZK24
// #define HZK16

#ifdef HZK24 /* 24 */
#include "include/ascii24.h"
#define ASCII_CODE ascii24
#define FONT_SIZE  24			/* size: 24 */
#endif

#ifdef HZK16	/* 16 */

#include "include/ascii16.h"
#define ASCII_CODE ascii16
#define FONT_SIZE  16			/* size: 16 */
#endif

// todo here

#if !defined (HZK24) && !defined (HZK16)
#error "you must define HZK16 or HZK24!"
#endif

#define BYTES (FONT_SIZE/8)			/* for HZ: 3 bytes  2 bytes*/
#define BUF_SIZE (BYTES * FONT_SIZE)		/* HZ buff 3*24 = 72 bytes 2*16 = 32 bytes */

#define ASCII_BYTES (BYTES-1)		/* 2 1*/
#define ASCII_SIZE (FONT_SIZE * ASCII_BYTES)	/* ASCII buffer: 24*2 = 48 bytes 16 * 1 = 16 bytes */
#define ASCII_WIDTH (FONT_SIZE/2)		/* ASCII: 16*8 24*12 */

/**
 * __display_ascii - Display an ASCII code
 * @x: Column
 * @y: Row
 * @ascii: Which ASCII code to display
 * @color: Color index or Color
 * This routine display an ASCII code that stored in an array(eg, ASCII_CODE).
 * 16x8 ASCII code takes 1 byte, 24*12 ASCII code takes 2 bytes, so we need
 * -ASCII_BYTES-.
 */
static void __display_ascii(int x, int y, const unsigned char *ascii, uint32 color)
{
	int i, j, k;
	unsigned char *p_ascii;
	int offset;

	offset = (*ascii - 0x20 ) * ASCII_SIZE; /* find the code in the array */
	p_ascii = ASCII_CODE + offset;

	for(i = 0; i < FONT_SIZE; i++)
    {
		for(j =0; j < ASCII_BYTES; j++)
        {
			for(k = 0; k < 8; k++)
            {
				if( p_ascii[i * ASCII_BYTES + j] & (0x80>>k))
					pixel(x + j*8 + k, y + i, color);
				//else
				//	pixel (x + j*8 + k, y + i, XORMODE);
			}
        }
    }
   myrefresh();
}

/**
 * put_string_ascii - Display an ASCII string
 * @x: Column
 * @y: Row
 * @s: Which string to display
 * @color: Color index or Color
 */
void put_string_ascii(int x, int y, const char *s, uint32 color)
{
    unsigned char* p = (unsigned char* )s;
	while (*p != 0)
    {
		__display_ascii(x, y, p, color);
		x += ASCII_WIDTH;
		p++;
	}
}

/* not test */
void put_string_center_ascii(int x, int y, const char *s, uint32 color)
{
	int sl = (int)strlen (s);
    put_string_ascii(x - (sl / 2) * ASCII_WIDTH,
                    y - FONT_SIZE / 2, s, color);
}

/**
 * __display_font_16 - Display a 16x16 (chinese) character
 * @fp: File pointer points to HZK(ie, HZK16)
 * @x: Column
 * @y: Row
 * @font: Which (chinese) character to display
 * @color: Color index or Color
 * This routine ONLY display 16*16 character.
 * Every character takes two bytes, we show the first 8 bits, then the second 8 bits,
 * then the whole world will be shown before us.
 */
static void __display_font_16 (FILE *fp, int x, int y, const unsigned char *font, uint32 color)
{
	int i, j, k;
	unsigned char mat[BUF_SIZE]={0};
	int qh,wh;
	unsigned long offset;

	qh = *font - 0xa0;
	wh = *(font + 1) - 0xa0;
	offset = ( 94 * (qh - 1) + (wh - 1) ) * BUF_SIZE; /* offset of the character in HZK */

	/* read it */
	fseek(fp, offset, SEEK_SET);
	fread(mat, BUF_SIZE, 1, fp);

	/* show it */
	for(i = 0; i < FONT_SIZE; i++)
    {
		for(j = 0; j < BYTES; j++)
        {
			for(k = 0; k < 8; k++)
            {
				if(mat[i * BYTES + j] & (0x80>>k))
					pixel(x + j*8 + k, y + i, color);
				//else
				//	pixel(x + j*8 + k, y + i, XORMODE);
			}
        }
    }

   myrefresh();
}

/**
 * __display_font_24 - Display a 24x24 (chinese) character
 * @fp: File pointer points to HZK(ie, HZK24)
 * @x: Column
 * @y: Row
 * @font: Which (chinese) character to display
 * @color: Color index or Color
 */
static void __display_font_24(FILE *fp, int x, int y, const unsigned char *font, uint32 color)
{
	unsigned int i, j;
	unsigned char mat[FONT_SIZE][BYTES]={{0}};
	int qh,wh;
	unsigned long offset;

	qh = *font - 0xaf;
	wh = *(font+1) - 0xa0;
	offset = (94 * (qh-1) + (wh-1) ) * BUF_SIZE;

	fseek(fp, offset, SEEK_SET);
	fread(mat, BUF_SIZE, 1, fp);

	for(i = 0; i < FONT_SIZE; i++)
    {
		for(j = 0; j < FONT_SIZE; j++)
        {
			if(mat[j][i>>3] & (0x80>>(i&7)))
			// if (mat[j][i/8] & (0x80>>i%8)) /* org */
				pixel(x + j, y + i, color);
			//else
			//	pixel(x + j, y + i, XORMODE);
		}
    }
   myrefresh();
}

/**
 * put_string_hz - Display a (chinese) character string
 * @fp: File pointer points to HZK(ie, HZK24 or HZK16)
 * @x: Column
 * @y: Row
 * @s: Which string to display
 * @color: Color index or Color
 */
void put_string_hz(FILE *fp, int x, int y, const char *s, uint32 color)
{
    unsigned char* p = (unsigned char *)s;
	while (*p != 0) {
		#ifdef HZK24
		__display_font_24(fp, x, y, p, color); /* for HZK24 */
		#else
		__display_font_16(fp, x, y, p, color);
		#endif
		x += FONT_SIZE;
		s += 2;	/* 2 bytes */
	}
}

/* not test */
void put_string_center_hz (FILE *fp, int x, int y, const char *s, uint32 color)
{
	int sl = (int)strlen (s);
    put_string_hz (fp, x - (sl/2) * FONT_SIZE, y - FONT_SIZE/2, s, color);
}

/**
 * put_font - Display an ASCII or/and (chinese) character string
 * @fp: File pointer points to HZK(ie, HZK24 or HZK16)
 * @x: Column
 * @y: Row
 * @s: Which string to display
 * @color: Color index or Color
 */
void put_font(FILE *fp, int x, int y, const char *s, uint32 color)
{
    unsigned char* p = (unsigned char *)s;

	while (*p != 0) {
		if ( (*p>0xa0) && (*(p+1)>0xa0) ) {
			#ifdef HZK24
			__display_font_24(fp, x, y, p, color); 	/* for HZK24 */
			#else
			__display_font_16(fp, x, y, p, color);	/* for HZK16 */
			#endif
			x += FONT_SIZE;
			p += 2;	/* 2 bytes */
		} else {
			__display_ascii(x, y, p, color);
			x += ASCII_WIDTH;
			p++;	/* 1 byte */
		}
	}
}
/* not test */
void put_font_center(FILE *fp, int x, int y, const char *s, uint32 color)
{
	int sl = (int)strlen (s);
    put_font (fp, x - (sl/2) * FONT_SIZE, y - FONT_SIZE/2, s, color);
}
