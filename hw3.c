#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_VERTICES 10000 //���� �ִ밳��
#define MAX_EDGES 50000000 //���� �ִ밳��
typedef struct {
	int cost;
	int u;
	int v;
}edge;
int n = 0;
int ver_num, ed_num;
int parent[MAX_VERTICES];
int edgeNum;//MST�� �� EDGE ���� ����ؼ� ���߿� VERTEX-1�� ���� ���� ���̴�.!
edge minheap[MAX_EDGES+1];
int find(int v);
void union_set(int i, int j);
void kruskal(FILE *fp);
edge pop();
void push(edge e);
void main(int argc, char **argv)
{
	clock_t start, end;
	FILE*fp, *fp2;
	edge *edptr;
	int i;
	int u, v, cost;
	start = clock();
	if (argc != 2) {
		printf("usage: ./hw3 input_filename\n");
		return;
	}//requirement 2-3
	fp = fopen(argv[1], "rt");

	if (fp == NULL) {
		printf("The input file does not exist.\n");
		return;
	}//requirement 2-4
	fp2 = fopen("hw3_result.txt", "wt");//3-6
	//------------------------------------------------------------------------
	fscanf(fp,"%d",&ver_num);
	for (i = 0; i < ver_num; i++)
	{
		parent[i] = -1;
	}//parent �ʱ�ȭ ����
	fscanf(fp, "%d", &ed_num);
	edptr = (edge*)malloc(sizeof(edge)*(ed_num+1));//egde ����+1 ��ŭ �����Ҵ�----------�Ŀ� ���� ����!!!!!!!
	for (i = 1; i < ed_num+1 ; i++)
	{
		fscanf(fp, "%d %d %d", &u, &v, &cost);
		edptr[i].u = u;
		edptr[i].v = v;
		edptr[i].cost = cost;
		push(edptr[i]);
	}//  ������ �� ������ ��뿡 ���� ������ ���� ���� �迭�� �������.//���� �ֱ� ���ؼ� ������ 1���� ������ ����!
	kruskal(fp2);
	free(edptr);//�����Ҵ�����
	end = clock();
	printf("output written to hw3_result.txt.\n");
	printf("running time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
	fclose(fp);
	fclose(fp2);
}
void push(edge e) {
	int j;
	n++;
	j = n;
	while (j != 1 && e.cost < minheap[j / 2].cost) {
		minheap[j].cost = minheap[j / 2].cost;
		minheap[j].u = minheap[j / 2].u;
		minheap[j].v = minheap[j / 2].v;
		j /= 2;
	}
	minheap[j].cost = e.cost;
	minheap[j].u = e.u;
	minheap[j].v = e.v;
}
edge pop() {
	edge tmp;
	edge popEdge;
	int p = 1, c = 2;
	popEdge = minheap[1];
	tmp = minheap[n--];
	while (c <= n) {
		if ((c < n) && (minheap[c].cost > minheap[c + 1].cost)) c++;
		if (tmp.cost <= minheap[c].cost) break;
		minheap[p] = minheap[c];
		p = c;
		c *= 2;
	}
	minheap[p] = tmp;
	return popEdge;
}
int find(int v)//v�� ���ϴ� ������ ��ȯ
{
	while (parent[v] >= 0) {
		v = parent[v]; // ��Ʈ ������ �ݺ�
	}
	return v; // ������ ��ǥ ���Ҹ� ��ȯ
}
void union_set(int i, int j)//union �Լ�
{
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j])
	{
		parent[i] = j;
		parent[j] = temp;
	}
	else 
	{
		parent[j] = i;
		parent[i] = temp;
	}
}
void kruskal(FILE *fp)
{
	edge e;
	int sum=0;
	int u, v;
	while ((edgeNum < (ver_num - 1)) || ( n == 0))//vertex-1�� ���� �� ������ ����Ѵ�.!! �Ǵ� pop�� ������ ���� ��
	{
		e = pop();
		u = find(e.u);
		v = find(e.v);
		if (u!= v) {// ����Ŭ ������ �ȵǴ� ���
			edgeNum++;
			sum += e.cost;
			union_set(u,v);
			fprintf(fp, "%d %d %d\n", e.u, e.v, e.cost);
		}
	}
	fprintf(fp, "%d\n", sum);
	if (edgeNum != ver_num - 1) {
		fprintf(fp, "DISCONNECTED\n");
	}
	else 
	{
		fprintf(fp, "CONNECTED\n");
	}
}