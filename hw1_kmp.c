#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char str[10000000];
char pat[3000];
int t[10000000];//�����Լ�
int idx[10000000];//��ġ�� ù �ε��� �����ϴ� ��
int cnt;//��ġ�� Ƚ�� ����

void kmp(int slen,int plen);
void fail(int plen);
int main() {
	int i;
	int slen;
	int plen;
	FILE * fps = fopen("string.txt", "rt");//string.txt �б�
	FILE * fpp = fopen("pattern.txt", "rt");//pattern.txt �б�
	FILE * kmptxt = fopen("result_kmp.txt", "wt");// ����� �ؽ�Ʈ���� ����

	if (fps == NULL || fpp == NULL) {
		if(fps==NULL&&fpp!=NULL)
                {
                        printf("The string file does not exist.\n");
		        return 0;
                }
                else if(fps!=NULL&&fpp==NULL)
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
	fgets(str, sizeof(str), fps);
	fgets(pat, sizeof(pat), fpp);

	slen = strlen(str);
	plen = strlen(pat);
        
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

	
	fail(plen);
	kmp(slen, plen);
	
	fprintf(kmptxt, "%d\n", cnt);
	for (i = 0; i < cnt - 1; i++)
	{
		fprintf(kmptxt, "%d ", idx[i]);
	}
	fprintf(kmptxt, "%d\n", idx[cnt - 1]);


	fclose(fps);
	fclose(fpp);
	fclose(kmptxt);
        return 0;
}

void kmp(int slen,int plen)
{
	
	int i, j,k=0;
	int chk = -1;//��ġ ���� �÷���
	
	while (i < slen&&j < plen) {
		if (str[i] == pat[j]) {
		        i++;
                        j++;
		}
		else if (j == 0) i++;
		else {
			j = t[j-1] + 1;
		}
                if(j==plen){
                        idx[k++]=i-j;
                        j=t[j-1]+1;
                        cnt++;
                }
	}
	
}

void fail(int plen)
{
	int i, j;
	t[0] = -1;
	for (j = 1; j < plen; j++)
	{
		i = t[j - 1];
		while ((pat[j] != pat[i + 1]) &&( i > -1))
		{
			i = t[i];
		}
		if (pat[j] == pat[i + 1])
		{
			t[j] = i + 1;
		}
		else
		{
			t[j] = -1;
		}
	}

}
