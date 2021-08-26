#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_VERTICES 10000 //정점 최대개수
#define MAX_EDGES 50000000 //엣지 최대개수
typedef struct {
	int cost;
	int u;
	int v;
}edge;
int n = 0;
int ver_num, ed_num;
int parent[MAX_VERTICES];
int edgeNum;//MST에 들어갈 EDGE 수를 계산해서 나중에 VERTEX-1의 값과 비교할 것이다.!
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
	}//parent 초기화 진행
	fscanf(fp, "%d", &ed_num);
	edptr = (edge*)malloc(sizeof(edge)*(ed_num+1));//egde 개수+1 만큼 동적할당----------후에 프리 예정!!!!!!!
	for (i = 1; i < ed_num+1 ; i++)
	{
		fscanf(fp, "%d %d %d", &u, &v, &cost);
		edptr[i].u = u;
		edptr[i].v = v;
		edptr[i].cost = cost;
		push(edptr[i]);
	}//  엣지의 두 정점과 비용에 대한 정보를 담은 엣지 배열을 만들었다.//힙에 넣기 위해서 번지를 1부터 했음을 참고!
	kruskal(fp2);
	free(edptr);//동적할당해제
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
int find(int v)//v가 속하는 집합을 반환
{
	while (parent[v] >= 0) {
		v = parent[v]; // 루트 노드까지 반복
	}
	return v; // 집합의 대표 원소를 반환
}
void union_set(int i, int j)//union 함수
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
	while ((edgeNum < (ver_num - 1)) || ( n == 0))//vertex-1과 같아 질 때까지 계속한다.!! 또는 pop할 엣지가 없을 때
	{
		e = pop();
		u = find(e.u);
		v = find(e.v);
		if (u!= v) {// 사이클 형성이 안되는 경우
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