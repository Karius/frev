#include <stdio.h>
#include <string.h>
	
// ��ӡʹ��˵��
void usage ();

// ���ļ���ת���ݺ�д�����ļ�
// filename: ׼����ת���ݵ��ļ�
// outfilename: ��ת������׼��д����ļ�
// bit_rev: �Ƿ��ÿ���ֽڽ��а�λȡ��
int frev (char *filename, char *outfilename, bool bit_rev);


int main(int argc, char **argv)
{
	if (argc < 1) {
		usage ();
		return 0;
	}
	
	// �Զ��������ļ�������� ".out" ��չ����Ϊ����ļ���
	char *outfilename = new char[strlen (argv[1]) + 6];
	strcpy (outfilename, argv[1]);
	strcat (outfilename, ".out");
	
	// Ĭ�Ͻ��а�λ��ת
	// Ϊ��ʡ�£������в������ṩ�Դ˲������ƶ���һ�ɶ�ÿ���ֽڽ��а�λ��ת
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