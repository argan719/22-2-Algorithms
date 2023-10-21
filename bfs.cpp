

#include<stdio.h>
#include<stdlib.h>
#include "bfs.h"

int **bfs_matrix;   // 미로 맵
int **visited;   // 방문했는지 여부 - 미로와 똑같은 사이즈의 2차원 배열로 설정

//원형큐
#define MAX_QUEUE_SIZE 100
typedef struct xy {
	int x;
	int y;
}NM;

typedef NM element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void error(const char* message) {
	printf("%s", message);
	exit(1);
}
void init(QueueType* q) {
	q->front = q->rear = 0;
}
int is_empty(QueueType* q) {
	return (q->front == q->rear);
}
int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("overflow");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
element dequeue(QueueType* q) {
	if (is_empty(q))
		error("underflow");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}


// 미로와 visited 행렬 초기화
void init(int n, int m, int **matrix)
{
	int i, k;
	// 크기 동적 할당
	bfs_matrix = (int**)malloc(sizeof(int *) * n);
	visited = (int**)malloc(sizeof(int *) * n);
	for (i = 0; i < n; i++) {
		bfs_matrix[i] = (int*)malloc(sizeof(int) * m);
		visited[i] = (int*)malloc(sizeof(int) * m);
	}
	for (i = 0; i < n; i++) {
		for (k = 0; k < m; k++) {
			visited[i][k] = 0;  // visited값은 전부 0으로 초기화
			bfs_matrix[i][k] = matrix[i][k];   // DFS에서 입력받은 미로 BFS 미로로 복사
		}
	}
}

int bfs(int n, int m)
{
	// (0,0) ~ (N-1,M-1)
	QueueType q;  // 원형큐 생성
	init(&q);  // 원형큐 초기화

	NM pos;  // 좌표 
	NM tmp;
	pos.x = 0;  pos.y = 0;
	int move = 0;  // 이동횟수

	visited[pos.x][pos.y] = 1;  // 처음시작위치(0,0)
	move++;
	enqueue(&q, pos);  // 시작위치 큐 삽입
	while (!is_empty(&q)) {
		pos = dequeue(&q);  // dequeue
		tmp = pos;

		if (pos.y < m - 1 && bfs_matrix[pos.x][pos.y + 1] && !visited[pos.x][pos.y + 1]) {   // 우
			visited[pos.x][pos.y + 1] = 1;
			tmp = pos;
			tmp.y++;
			enqueue(&q, tmp);
		}
		if (pos.x < n - 1 && bfs_matrix[pos.x + 1][pos.y] && !visited[pos.x + 1][pos.y]) {  // 하
			visited[pos.x + 1][pos.y] = 1;
			tmp = pos;
			tmp.x++;
			enqueue(&q, tmp);
		}
		if (pos.x > 0 && bfs_matrix[pos.x - 1][pos.y] && !visited[pos.x - 1][pos.y]) {   // 상
			visited[pos.x - 1][pos.y] = 1;
			tmp = pos;
			tmp.x--;
			enqueue(&q, tmp);
		}
		if (pos.y > 0 && bfs_matrix[pos.x][pos.y - 1] && !visited[pos.x][pos.y - 1]) {   // 좌
			visited[pos.x][pos.y - 1] = 1;
			tmp = pos;
			tmp.y--;
			enqueue(&q, tmp);
		}

		if (pos.x == tmp.x && pos.y == tmp.y) {}  // 기존값이랑 상,하,좌,우로 이동한 값이랑 인덱스의 차이가 없다면=4개의 if문에 전부 들어가지 못했다면
		else {   // 아닌 경우 이동한 것이므로 이동횟수++
			move++;
			printf("[ %d, %d ] -> ", pos.x, pos.y);
		}

		if (tmp.x == n - 1 && tmp.y == m - 1) {
			printf("[ %d, %d ] -> ", tmp.x, tmp.y);
			printf("미로 탈출 성공!\n"); return move;
		}
	}
	return -1;
}


void bfs_main(int n, int m)
{
	int a = bfs(n, m);  // 너비우선탐색
	if (a == -1) printf("미로탈출 실패!\n");
	else printf("\n\n이동한 칸 수 : %d\n", a);
}
