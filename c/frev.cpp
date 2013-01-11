#include <stdio.h>
#include <string.h>
	
// 打印使用说明
void usage ();

// 读文件反转内容后写入新文件
// filename: 准备反转内容的文件
// outfilename: 反转后内容准备写入的文件
// bit_rev: 是否对每个字节进行按位取反
int frev (char *filename, char *outfilename, bool bit_rev);


int main(int argc, char **argv)
{
	if (argc < 1) {
		usage ();
		return 0;
	}
	
	// 自动在输入文件名后加入 ".out" 扩展名作为输出文件名
	char *outfilename = new char[strlen (argv[1]) + 6];
	strcpy (outfilename, argv[1]);
	strcat (outfilename, ".out");
	
	// 默认进行按位反转
	// 为了省事，命令行参数不提供对此参数的制定。一律对每个字节进行按位反转
	bool bit_rev = true;

	int result = frev (argv[1], outfilename, bit_rev);
	delete outfilename;
	
	(0 == result) ? printf ("convert ok.\r\n") : printf ("convert failed.\r\n");
	
	return result;
}

void usage ()
{
	printf ("frev v1.0\r\n"\
			"	frev <intput filename>\r\n"
		);
}

int frev (char *filename, char *outfilename, bool bit_rev)
{
	FILE *fp = fopen (filename, "rb");
	
	if (NULL != fp)
	{
		fseek (fp, 0L, SEEK_END);
		long flen = ftell (fp);
		fseek (fp, 0L, SEEK_SET);
		
		if (flen > 0) {
			char *buf = new char[flen];
			
			if (NULL != buf) {
				fread (buf, flen, 1, fp);
				FILE *fout = fopen (outfilename, "wb");
				
				if (NULL != fout) {
					while (flen > 0)
					{
						flen--;
						fputc (~buf[flen], fout);
					}
					//fwrite (buf, flen, 1, fout);
				fclose (fout);
				}
				
				delete buf;
			}
		}

		fclose (fp);
		
		return 0;
	}
	
	return 1;
}