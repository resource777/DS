#include<stdio.h>
#include<string.h>
#include<time.h>

int maxheap[1000000];
int maxheapc[1000000];
int minheap[1000000];
int minheapc[1000000];
int n1 = 0;

int pop();
int pop1();
void push(int data);
void asc(FILE*fp);//min
void des(FILE*fp);//max

void main(int argc, char **argv)
{
	clock_t start, end;
	FILE*fp, *fp2;
	int ret, data;
	char command[8];

	start = clock();

	if (argc != 2) {
		printf("usage: ./hw2 input_filename\n");
		return;
	}//requirement 2-3
	fp = fopen(argv[1], "rt");

	if (fp == NULL) {
		printf("The input file does not exist.\n");
		return;
	}//requirement 2-4

	fp2 = fopen("hw2_result.txt", "wt");//3-4

	while (1) {
		ret = fscanf(fp, " %s", command);
		if (ret == EOF) break;
		if (strcmp(command, "INSERT") == 0) {
			fscanf(fp, "%d", &data);
			push(data);
		}
		else if (strcmp(command, "ASCEND") == 0) {
			asc(fp2);
		}
		else if (strcmp(command, "DESCEND") == 0) {
			des(fp2);
		}
	}

	end = clock();
	//2-6
	printf("output written to hw2_result.txt.\n");
	printf("running time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

	fclose(fp);
	fclose(fp2);
}

void push(int data) {
	int i, j;
	n1++;
	i = n1;
	j = i;
	while (i != 1 && data > maxheap[i / 2]) {
		maxheap[i] = maxheap[i / 2];
		i /= 2;
	}
	while(j != 1  && data < minheap[j / 2]) {
		minheap[j] = minheap[j / 2];
		j /= 2;
	}
	maxheap[i] = data;
	minheap[j] = data;
}
int pop() {
	int p = 1, c = 2;
	int data, tmp;
	data = maxheap[1];
	tmp = maxheap[n1--];
	while (c <= n1) {
		if ((c < n1) && (maxheap[c] < maxheap[c + 1])) c++;
		if (tmp >= maxheap[c]) break;
		maxheap[p] = maxheap[c];
		p = c;
		c *= 2;
	}
	maxheap[p] = tmp;
	return data;
}
int pop1() {
	int p = 1, c = 2;
	int data, tmp;
	data = minheap[1];
	tmp = minheap[n1--];
	while (c <= n1) {
		if ((c < n1) && (minheap[c] > minheap[c + 1])) c++;
		if (tmp <= minheap[c]) break;
		minheap[p] = minheap[c];
		p = c;
		c *= 2;
	}
	minheap[p] = tmp;
	return data;
}
void asc(FILE *fp) {//min heap 사용
	int i=1;
	int ncopy = n1;
	while (i <= n1) {
		minheapc[i] = minheap[i];
		i++;
	}
	
	i = 1;
	while (i <= ncopy)
	{
		if (ncopy == 0) break;
		fprintf(fp, "%d ", pop1());
		i++;
	}
	n1 = ncopy;
	fprintf(fp, "\n");

	i = 1;
	while (i <= ncopy) {
		minheap[i] = minheapc[i];
		i++;
	}
}
void des(FILE *fp) {//max heap 사용
	int i=1;
	int ncopy = n1;
	while (i <= ncopy) {
		maxheapc[i] = maxheap[i];
		i++;
	}
	i = 1;
	while (i <= ncopy) {
		if (ncopy == 0) break;
		fprintf(fp, "%d ", pop());
		i++;
	}
	n1 = ncopy;
	fprintf(fp, "\n");

	i = 1;
	while (i <= ncopy) {
		maxheap[i] = maxheapc[i];
		i++;
	}
}
