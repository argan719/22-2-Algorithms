


//  Kruskal 이용
#include<stdio.h>
#include<math.h>  // sqrt
#define MAX 100
#define SWAP(x, y, t) ( t = x, x = y, y = t )


// 별
typedef struct {
	double x;  // 별의 x좌표값
	double y;  // 별의 y좌표값
	int idx;  // parent값 매칭 위해 별마다 인덱스 설정(0부터 시작) (for findParent, unionParent)
}Star;

// 별 사이 거리
typedef struct {
	Star a;  // 첫번째 노드
	Star b;  // 두번째 노드
	double val;  // 노드 간 거리
}Distance;

Star arr[MAX];   // 별 정보 저장 배열
Distance distance[MAX];  // 그래프
int parent[MAX];  // 연결성분 - 부모노드

int numberOfVertex;  // 노드 개수
int numberOfEdge;   // 간선 개수

void AddEdge(int i, Star e) {  // 별 정보 입력. 추가
	arr[i] = e;
}

int getParent(int x) {   // 부모 값 리턴
	if (parent[x] == x) return x;    // parent [x] = x 인 경우 루트노드를 의미
	return parent[x] = getParent(parent[x]);  // 재귀호출로 부모번호까지 타고 올라감
}

// 같은 부모노드를 가지는지 확인
int findParent(int a, int b) {    // 트리의 루트노드 찾기 - 값은 같이면 같은 집합. 1을 리턴한다.
	if (getParent(a) == getParent(b)) return 1;
	else return 0;
}

void unionParent(int a, int b) {  // 연결성분 생성
	a = getParent(a);  // a의 부모노드 값
	b = getParent(b);   // b의 부모노드 값
	if (a < b) parent[b] = a;  // 더 작은 쪽으로 몰아주기
	else parent[a] = b;
}


void main()
{
	int i, k, j;
	Distance tmp;
	Star e;
	// 별의 개수 입력
	printf("별의 개수 : ");
	scanf("%d", &numberOfVertex);
	numberOfEdge = 0;

	// parent 값 초기화 - 인덱스=값
	for (i = 1; i <= numberOfVertex; i++)
		parent[i] = i;
	
	// 별의 좌표 입력
	printf("각 별의 좌표(x, y)\n");
	for (i = 0; i < numberOfVertex; i++) {
		scanf("%lf %lf", &e.x, &e.y);
		e.idx = i;
		AddEdge(i, e);
	}

	// 별 사이 거리 계산 후 저장
	int idx = 0;
	for (i = 0; i < numberOfVertex - 1; i++) {
		for (j = i + 1; j < numberOfVertex; j++) {
			distance[idx].a = arr[i];  // 첫 번째 노드
			distance[idx].b = arr[j];  // 두 번째 노드
			// 노드 간 거리 : sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
			distance[idx].val = sqrt((arr[i].x - arr[j].x) * (arr[i].x - arr[j].x) + (arr[i].y - arr[j].y) * (arr[i].y - arr[j].y));
			idx++;
			numberOfEdge++;
		}
	}

	// 별 사이 거리 오름차순으로 정렬 (bubble sort)
	Distance t;
	for (i = numberOfEdge - 1; 0 < i; i--) {
		for (j = 0; j < i; j++) {
			if (distance[j].val > distance[j + 1].val) SWAP(distance[j], distance[j + 1], t);
		}
	}

	// greedy 
	// 그래프의 모든 간선을 가중치로 오름차순으로 정렬한뒤
	// 낮은 간선부터 하나씩 그래프에 추가해나간다.
	// 단 사이클을 형성하는 간선은 추가하지 않고 간선의 수가 정점의 수보다 하나 적을 때 최소 신장 트리가 완성된다.
	double sum = 0;
	for (i = 0; i < numberOfEdge; i++)
	{
		// 사이클이 발생하지 않을 때만 선택
		// 같은 부모인 경우 union연산을 수행하면 사이클이 형성된다.
		// 따라서 부모가 다른 노드일 경우에만 union연산을 수행한다.
		if (!findParent(distance[i].a.idx, distance[i].b.idx))   // i랑 i+1이 아니라 Star a, Star b 비교
		{
			unionParent(distance[i].a.idx, distance[i].b.idx);
			sum += distance[i].val;
		}
	}
	printf("\n\n별자리를 만드는 최소 비용 : %.2f\n\n", sum);  // 최단거리 간선 가중치의 합
}






/*
// Prim 이용

#include<stdio.h>
#include<math.h>  // sqrt
#define MAX_VERTICES 100
#define INF 1000

#define TRUE 1
#define FALSE 0


// 별
typedef struct {
	double x;
	double y;
	int idx;   // matrix에서의 행열 값 매칭 위해 별마다 인덱스 설정(0부터 시작) = matrix 에서의 행열값
}Star;

Star arr[MAX_VERTICES];  // 별 저장

int numberOfVertex;

double matrix[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
double dist[MAX_VERTICES];   // 간선 가중치 저장
double sum = 0;

void init()
{
	for (int i = 0; i < numberOfVertex; i++) {
		for (int j = 0; j < numberOfVertex; j++) {
			if (i == j) matrix[i][j] = 0;     // 본인꺼 0 (0행 0열, 1행 1열..)
			else matrix[i][j] = INF;     // 나머지 INF로 초기화
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
		u = get_min_vertex(n);  // dist 중 가장 작은 간선 선택
		visited[u] = TRUE;
		if (dist[u] == INF) return;
		printf("%d ", u);   // 가장 작은 간선을 타고 새로운 정점으로 이동 - 지나간 정점 출력
		sum += dist[u];  // 최소 비용(최단거리 가중치 합)
		for (v = 0; v < n; v++)
			if (matrix[u][v] != INF)
				if (!visited[v] && matrix[u][v] < dist[v])
					dist[v] = matrix[u][v];  // 새로 선택된 정점의 모든 간선의 가중치 저장
	}
}

void AddEdge(int a, int b, double val) {  // 첫번째 별의 idx, 두번째 별의 idx, 두 별 사이의 거리
	matrix[a][b] = val;
	matrix[b][a] = val;
}


void main()
{
	int i, j;
	Star e;
	printf("별의 개수 : ");
	scanf("%d", &numberOfVertex);
	init();

	printf("각 별의 좌표(x, y)\n");
	for (i = 0; i < numberOfVertex; i++) {
		scanf("%lf %lf", &e.x, &e.y);
		e.idx = i;
		arr[i] = e;
	}

	// 거리 구하기
	double distance;
	for (i = 0; i < numberOfVertex - 1; i++) {
		for (j = i + 1; j < numberOfVertex; j++) {
			distance = sqrt((arr[i].x - arr[j].x) * (arr[i].x - arr[j].x) + (arr[i].y - arr[j].y) * (arr[i].y - arr[j].y));
			AddEdge(arr[i].idx, arr[j].idx, distance);
		}
	}

	prim(0, numberOfVertex);
	printf("\n\n별자리를 만드는 최소 비용 : %.2f\n\n", sum);
}
*/


