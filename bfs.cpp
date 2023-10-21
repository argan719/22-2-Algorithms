

#include<stdio.h>
#include<stdlib.h>
#include "bfs.h"

int **bfs_matrix;   // �̷� ��
int **visited;   // �湮�ߴ��� ���� - �̷ο� �Ȱ��� �������� 2���� �迭�� ����

//����ť
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


// �̷ο� visited ��� �ʱ�ȭ
void init(int n, int m, int **matrix)
{
	int i, k;
	// ũ�� ���� �Ҵ�
	bfs_matrix = (int**)malloc(sizeof(int *) * n);
	visited = (int**)malloc(sizeof(int *) * n);
	for (i = 0; i < n; i++) {
		bfs_matrix[i] = (int*)malloc(sizeof(int) * m);
		visited[i] = (int*)malloc(sizeof(int) * m);
	}
	for (i = 0; i < n; i++) {
		for (k = 0; k < m; k++) {
			visited[i][k] = 0;  // visited���� ���� 0���� �ʱ�ȭ
			bfs_matrix[i][k] = matrix[i][k];   // DFS���� �Է¹��� �̷� BFS �̷η� ����
		}
	}
}

int bfs(int n, int m)
{
	// (0,0) ~ (N-1,M-1)
	QueueType q;  // ����ť ����
	init(&q);  // ����ť �ʱ�ȭ

	NM pos;  // ��ǥ 
	NM tmp;
	pos.x = 0;  pos.y = 0;
	int move = 0;  // �̵�Ƚ��

	visited[pos.x][pos.y] = 1;  // ó��������ġ(0,0)
	move++;
	enqueue(&q, pos);  // ������ġ ť ����
	while (!is_empty(&q)) {
		pos = dequeue(&q);  // dequeue
		tmp = pos;

		if (pos.y < m - 1 && bfs_matrix[pos.x][pos.y + 1] && !visited[pos.x][pos.y + 1]) {   // ��
			visited[pos.x][pos.y + 1] = 1;
			tmp = pos;
			tmp.y++;
			enqueue(&q, tmp);
		}
		if (pos.x < n - 1 && bfs_matrix[pos.x + 1][pos.y] && !visited[pos.x + 1][pos.y]) {  // ��
			visited[pos.x + 1][pos.y] = 1;
			tmp = pos;
			tmp.x++;
			enqueue(&q, tmp);
		}
		if (pos.x > 0 && bfs_matrix[pos.x - 1][pos.y] && !visited[pos.x - 1][pos.y]) {   // ��
			visited[pos.x - 1][pos.y] = 1;
			tmp = pos;
			tmp.x--;
			enqueue(&q, tmp);
		}
		if (pos.y > 0 && bfs_matrix[pos.x][pos.y - 1] && !visited[pos.x][pos.y - 1]) {   // ��
			visited[pos.x][pos.y - 1] = 1;
			tmp = pos;
			tmp.y--;
			enqueue(&q, tmp);
		}

		if (pos.x == tmp.x && pos.y == tmp.y) {}  // �������̶� ��,��,��,��� �̵��� ���̶� �ε����� ���̰� ���ٸ�=4���� if���� ���� ���� ���ߴٸ�
		else {   // �ƴ� ��� �̵��� ���̹Ƿ� �̵�Ƚ��++
			move++;
			printf("[ %d, %d ] -> ", pos.x, pos.y);
		}

		if (tmp.x == n - 1 && tmp.y == m - 1) {
			printf("[ %d, %d ] -> ", tmp.x, tmp.y);
			printf("�̷� Ż�� ����!\n"); return move;
		}
	}
	return -1;
}


void bfs_main(int n, int m)
{
	int a = bfs(n, m);  // �ʺ�켱Ž��
	if (a == -1) printf("�̷�Ż�� ����!\n");
	else printf("\n\n�̵��� ĭ �� : %d\n", a);
}
