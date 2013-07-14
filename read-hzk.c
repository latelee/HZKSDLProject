/* 24点阵转换成数组，ASC24.dat字库文件由-字模III-工具生成 
 * 实际显示为12*24，数据形式为16*24。
 * 16*24/8 = 48 = 24*2
*/
#include <stdio.h>

#define ASC24
#ifdef ASC24
#define ZK "ASC24"
#define OUT_FILE "ascii24.h"
#define ARRAY "ascii24"
#else
#define ZK "ASC24.dat"
#define OUT_FILE "ascii24-me.h"
#define ARRAY "ascii24"
#endif

int main(void)
{
	int i;
	int j;
	FILE *fp_c;
	FILE *fp;
	int len;
	unsigned char mat[48] = {0};
	
	fp   = fopen(ZK, "rb");
	fp_c = fopen(OUT_FILE, "wb+");
	
	/* get file size */
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	//printf("len: %d\n", len);
	fprintf(fp_c, "/******************************************************/\n");
	fprintf(fp_c, "/*          Font file powered by Late Lee             */\n");
	fprintf(fp_c, "/*             http://www.latelee.org                 */\n");
	fprintf(fp_c, "/*              %s %s                  */\n", __DATE__, __TIME__);
	fprintf(fp_c, "/******************************************************/\n");
	fprintf(fp_c, "unsigned char %s[] = \n{\n", ARRAY);
	#ifdef ASC24
	/* 读取ASC24 */
	for (i = 0x20*48, j = 1; i < len/2; i+=16, ++j) /* 96 printable ascii code */
	{
		fseek(fp,i,SEEK_SET);
		fread(mat,16,1,fp);
		if (i == 0x20*48)
			fprintf(fp_c, "/*   %d     0x%x     ' %c '     */\n", i/48, i/48, i/48);
		int tmp = (i+16)/48;
		fprintf(fp_c, 
		"0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,\n",
		mat[0],mat[1],mat[2],mat[3],mat[4],mat[5],mat[6],mat[7],mat[8],mat[9],mat[10],mat[11],mat[12],mat[13],mat[14],mat[15]);
		if (tmp == 127)
			break;
		if (j%3 == 0)
		{
			fprintf(fp_c, "\n");
			fprintf(fp_c, "/*   %d     0x%x     ' %c '     */\n", tmp, tmp, tmp);
		}

	}
	#else
	/* 读取由字模生成的字库文件ASC24.dat */
	for (i = 0, j = 1; i < len; i+=16, ++j) /* 95 printable ascii code */
	{
		fseek(fp,i,SEEK_SET);
		fread(mat,16,1,fp);
		if (i == 0)
			fprintf(fp_c, "/*   %d     0x%x     ' %c '     */\n", i/48+0x20, i/48+0x20, i/48+0x20);
		int tmp = (i+16)/48+0x20;
		fprintf(fp_c, 
		"0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,\n",
		mat[0],mat[1],mat[2],mat[3],mat[4],mat[5],mat[6],mat[7],mat[8],mat[9],mat[10],mat[11],mat[12],mat[13],mat[14],mat[15]);
		if (tmp == 127)
			break;
		if (j%3 == 0)
		{
			fprintf(fp_c, "\n");
			fprintf(fp_c, "/*   %d     0x%x     ' %c '     */\n", tmp, tmp, tmp);
		}

	}
	#endif
	fprintf(fp_c, "};\n");
	fprintf(stdout, "Job done!\n");
	return 0;
}