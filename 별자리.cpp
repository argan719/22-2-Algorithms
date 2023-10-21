


//  Kruskal �̿�
#include<stdio.h>
#include<math.h>  // sqrt
#define MAX 100
#define SWAP(x, y, t) ( t = x, x = y, y = t )


// ��
typedef struct {
	double x;  // ���� x��ǥ��
	double y;  // ���� y��ǥ��
	int idx;  // parent�� ��Ī ���� ������ �ε��� ����(0���� ����) (for findParent, unionParent)
}Star;

// �� ���� �Ÿ�
typedef struct {
	Star a;  // ù��° ���
	Star b;  // �ι�° ���
	double val;  // ��� �� �Ÿ�
}Distance;

Star arr[MAX];   // �� ���� ���� �迭
Distance distance[MAX];  // �׷���
int parent[MAX];  // ���Ἲ�� - �θ���

int numberOfVertex;  // ��� ����
int numberOfEdge;   // ���� ����

void AddEdge(int i, Star e) {  // �� ���� �Է�. �߰�
	arr[i] = e;
}

int getParent(int x) {   // �θ� �� ����
	if (parent[x] == x) return x;    // parent [x] = x �� ��� ��Ʈ��带 �ǹ�
	return parent[x] = getParent(parent[x]);  // ���ȣ��� �θ��ȣ���� Ÿ�� �ö�
}

// ���� �θ��带 �������� Ȯ��
int findParent(int a, int b) {    // Ʈ���� ��Ʈ��� ã�� - ���� ���̸� ���� ����. 1�� �����Ѵ�.
	if (getParent(a) == getParent(b)) return 1;
	else return 0;
}

void unionParent(int a, int b) {  // ���Ἲ�� ����
	a = getParent(a);  // a�� �θ��� ��
	b = getParent(b);   // b�� �θ��� ��
	if (a < b) parent[b] = a;  // �� ���� ������ �����ֱ�
	else parent[a] = b;
}


void main()
{
	int i, k, j;
	Distance tmp;
	Star e;
	// ���� ���� �Է�
	printf("���� ���� : ");
	scanf("%d", &numberOfVertex);
	numberOfEdge = 0;

	// parent �� �ʱ�ȭ - �ε���=��
	for (i = 1; i <= numberOfVertex; i++)
		parent[i] = i;
	
	// ���� ��ǥ �Է�
	printf("�� ���� ��ǥ(x, y)\n");
	for (i = 0; i < numberOfVertex; i++) {
		scanf("%lf %lf", &e.x, &e.y);
		e.idx = i;
		AddEdge(i, e);
	}

	// �� ���� �Ÿ� ��� �� ����
	int idx = 0;
	for (i = 0; i < numberOfVertex - 1; i++) {
		for (j = i + 1; j < numberOfVertex; j++) {
			distance[idx].a = arr[i];  // ù ��° ���
			distance[idx].b = arr[j];  // �� ��° ���
			// ��� �� �Ÿ� : sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
			distance[idx].val = sqrt((arr[i].x - arr[j].x) * (arr[i].x - arr[j].x) + (arr[i].y - arr[j].y) * (arr[i].y - arr[j].y));
			idx++;
			numberOfEdge++;
		}
	}

	// �� ���� �Ÿ� ������������ ���� (bubble sort)
	Distance t;
	for (i = numberOfEdge - 1; 0 < i; i--) {
		for (j = 0; j < i; j++) {
			if (distance[j].val > distance[j + 1].val) SWAP(distance[j], distance[j + 1], t);
		}
	}

	// greedy 
	// �׷����� ��� ������ ����ġ�� ������������ �����ѵ�
	// ���� �������� �ϳ��� �׷����� �߰��س�����.
	// �� ����Ŭ�� �����ϴ� ������ �߰����� �ʰ� ������ ���� ������ ������ �ϳ� ���� �� �ּ� ���� Ʈ���� �ϼ��ȴ�.
	double sum = 0;
	for (i = 0; i < numberOfEdge; i++)
	{
		// ����Ŭ�� �߻����� ���� ���� ����
		// ���� �θ��� ��� union������ �����ϸ� ����Ŭ�� �����ȴ�.
		// ���� �θ� �ٸ� ����� ��쿡�� union������ �����Ѵ�.
		if (!findParent(distance[i].a.idx, distance[i].b.idx))   // i�� i+1�� �ƴ϶� Star a, Star b ��
		{
			unionParent(distance[i].a.idx, distance[i].b.idx);
			sum += distance[i].val;
		}
	}
	printf("\n\n���ڸ��� ����� �ּ� ��� : %.2f\n\n", sum);  // �ִܰŸ� ���� ����ġ�� ��
}






/*
// Prim �̿�

#include<stdio.h>
#include<math.h>  // sqrt
#define MAX_VERTICES 100
#define INF 1000

#define TRUE 1
#define FALSE 0


// ��
typedef struct {
	double x;
	double y;
	int idx;   // matrix������ �࿭ �� ��Ī ���� ������ �ε��� ����(0���� ����) = matrix ������ �࿭��
}Star;

Star arr[MAX_VERTICES];  // �� ����

int numberOfVertex;

double matrix[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
double dist[MAX_VERTICES];   // ���� ����ġ ����
double sum = 0;

void init()
{
	for (int i = 0; i < numberOfVertex; i++) {
		for (int j = 0; j < numberOfVertex; j++) {
			if (i == j) matrix[i][j] = 0;     // ���β� 0 (0�� 0��, 1�� 1��..)
			else matrix[i][j] = INF;     // ������ INF�� �ʱ�ȭ
		}
	}
}
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++)
		if (!visited[i]) {
			v = i;
			break;
		}
	for (i = 0; i < n; i++)
		if (!visited[i] && (dist[i] < dist[v])) v = i;
	return v;
}

void prim(int s, int n) {
	int i, u, v;
	for (u = 0; u < n; u++)
		dist[u] = INF;
	dist[s] = 0;
	for (i = 0; i < n; i++) {
		u = get_min_vertex(n);  // dist �� ���� ���� ���� ����
		visited[u] = TRUE;
		if (dist[u] == INF) return;
		printf("%d ", u);   // ���� ���� ������ Ÿ�� ���ο� �������� �̵� - ������ ���� ���
		sum += dist[u];  // �ּ� ���(�ִܰŸ� ����ġ ��)
		for (v = 0; v < n; v++)
			if (matrix[u][v] != INF)
				if (!visited[v] && matrix[u][v] < dist[v])
					dist[v] = matrix[u][v];  // ���� ���õ� ������ ��� ������ ����ġ ����
	}
}

void AddEdge(int a, int b, double val) {  // ù��° ���� idx, �ι�° ���� idx, �� �� ������ �Ÿ�
	matrix[a][b] = val;
	matrix[b][a] = val;
}


void main()
{
	int i, j;
	Star e;
	printf("���� ���� : ");
	scanf("%d", &numberOfVertex);
	init();

	printf("�� ���� ��ǥ(x, y)\n");
	for (i = 0; i < numberOfVertex; i++) {
		scanf("%lf %lf", &e.x, &e.y);
		e.idx = i;
		arr[i] = e;
	}

	// �Ÿ� ���ϱ�
	double distance;
	for (i = 0; i < numberOfVertex - 1; i++) {
		for (j = i + 1; j < numberOfVertex; j++) {
			distance = sqrt((arr[i].x - arr[j].x) * (arr[i].x - arr[j].x) + (arr[i].y - arr[j].y) * (arr[i].y - arr[j].y));
			AddEdge(arr[i].idx, arr[j].idx, distance);
		}
	}

	prim(0, numberOfVertex);
	printf("\n\n���ڸ��� ����� �ּ� ��� : %.2f\n\n", sum);
}
*/


