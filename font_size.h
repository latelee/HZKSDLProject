//#ifndef _FONT_SIZE_H
//#define _FONT_SIZE_H

/**
 * 包含此文件前必须定义CHARACTER_WIDTH
 * 这里所说的“宽”是指全角字符而言，如18*18点阵，全角字符宽为18，高为18，
 * 半角字符宽为9，高为18(但其占用空间为3字节，即24位)。高始终8字节对齐。
 */

#define ALIGN(x, a) (((x)+(a)-1)&~((a)-1))          // 字节对齐(此处点阵只使用8字节对齐)
#define CHARACTER_HALFWIDTH (CHARACTER_WIDTH/2)     // 半角宽度
#define CHARACTER_HEIGHT ALIGN(CHARACTER_WIDTH, 8)  // 点阵高度
#define FULLWIDTH_SIZE (ALIGN(CHARACTER_WIDTH, 8)*CHARACTER_WIDTH/8)    // 全角占用字节数
#define HALFWIDTH_SIZE (ALIGN(CHARACTER_WIDTH, 8)*CHARACTER_WIDTH/2/8)  // 半角占用字节数

// 点阵缓冲区“宽”：总大小/半角大小 * 半角宽
//#endif /* _FONT_SIZE_H */