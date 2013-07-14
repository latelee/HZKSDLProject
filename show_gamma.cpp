#include "show_gamma.h"

static int gamma_y[4096] = {0};

static int SetGammaData(int rgiDataXY[8][2])
{
    int x = 0, y = 0;
    int x1 = 0, y1 = 0;
    int x2 = 0, y2 = 0;
    int ret = -1;
    int tmp = 0;

    /// 8个点
    for (int i = 0; i < 8; i++)
    {
        /// 第一个点
        if (i == 0)     /// 补回原点(0, 0)
        {
            x1 = 0;
            y1 = 0;
        }
        else
        {
            x1 = rgiDataXY[i - 1][0] * 4095 / 255;
            y1 = rgiDataXY[i - 1][1] * 4095 / 255;
        }
        /// 第二个点
        x2 = rgiDataXY[i][0] * 4095 / 255;
        y2 = rgiDataXY[i][1] * 4095 / 255;

        /// 计算两点间(包含这两点)所有的Y值
        for (x = x1; x <= x2; x++)
        {
            y = (y2 - y1) * (x - x1) / (x2 - x1) + y1;
            gamma_y[x] = y;
        }
    }
    return 0;
}

static void InitDefGamma(int rgiGamma[8][2])
{
    rgiGamma[0][0] = 32;
    rgiGamma[0][1] = 32;

    rgiGamma[1][0] = 64;
    rgiGamma[1][1] = 64;

    rgiGamma[2][0] = 96;
    rgiGamma[2][1] = 96;

    rgiGamma[3][0] = 128;
    rgiGamma[3][1] = 128;

    rgiGamma[4][0] = 160;
    rgiGamma[4][1] = 160;

    rgiGamma[5][0] = 192;
    rgiGamma[5][1] = 192;

    rgiGamma[6][0] = 222;
    rgiGamma[6][1] = 222;

    rgiGamma[7][0] = 255;
    rgiGamma[7][1] = 255;
}

void ShowGamma(void)
{
    int rgiGamma[8][2] = {0};

    InitDefGamma(rgiGamma);
    SetGammaData(rgiGamma);

    for (int i = 0; i < 258; i++)
        pixel(i, (WINDOW_HEIGHT-1) - gamma_y[i], 0xffffff);
    myrefresh();
}