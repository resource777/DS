#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char str[10000000];
char pat[3000];

int idx[10000000];//매치된 첫 인덱스 저장하는 곳
int cnt;//매치된 횟수 저장

void naive(char str[], char pat[]);

int main() {
	
	int i;
        int slen;
        int plen;
	FILE * fps = fopen("string.txt", "rt");//string.txt 읽기
	FILE * fpp = fopen("pattern.txt", "rt");//pattern.txt 읽기
	FILE * naitxt = fopen("result_naive.txt", "wt");// 출력할 텍스트파일 열기

	if (fps == NULL || fpp == NULL) {
		if(fps==NULL && fpp !=NULL)
                {
                        printf("The string file does not exist.\n");
		        return 0;
                }
                else if(fps!=NULL &&fpp==NULL)
                {
                        printf("The pattern file does not exist.\n");
                        return 0;
                }
                else
                {
                        printf("The string file and the pattern file do not exist.\n");
                        return 0;       
                }
	}       
	fgets(str,sizeof(str),fps);
	fgets(pat,sizeof(pat),fpp);
        slen=strlen(str);
        plen=strlen(pat);

        if(str[slen-1]=='\n')
        {
                str[slen-1]=0;
                slen--;
        }
        if(pat[plen-1]=='\n')
        {
                pat[plen-1]=0;
                plen--;
        }

	naive(str, pat);
	fprintf(naitxt, "%d\n", cnt);
	for ( i = 0; i < cnt-1; i++)
	{
		fprintf(naitxt, "%d ", idx[i]);
	}
	fprintf(naitxt, "%d\n", idx[cnt-1]);



	fclose(fps);
	fclose(fpp);
	fclose(naitxt);

}

void naive(char str[], char pat[])
{
	int i,j,k=0;
	int chk = -1;//일치 여부 플래그
	int slen = strlen(str);
	int plen = strlen(pat);

	for ( i = 0; i < slen-plen+1; i++)
	{
		for (j = 0; j < plen; j++)
		{
			if (str[i + j] == pat[j]) {
				chk = 1;
				continue;
			}
			else 
			{
				chk = -1;
				break;
			}

		}
		if (chk != -1) {
			idx[k++] = i;
			cnt++;
		}
	}
	
}
