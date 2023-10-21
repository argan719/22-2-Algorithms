


// 미로 탐색 DFS, DFS 
// bfs.h bfs.cpp Stack.cpp Stack.h
// N x M 크기의 배열로 표현되는 미로
// 1이면 길, 0이면 벽


// 공간복잡도를 줄이기 위해 visited 배열 생성하지 않고 matrix값을 바꾸는 걸로 방문여부 확인 - 한번 지나간 값은 1 -> 0로 
// 나중에 다시 탐색하게 될 때를 대비해 값 원래대로 바꿔줘야 함 0 -> 1로

#include<stdio.h>
#include<stdlib.h>
#include "Stack.h"  // 스택
#include "bfs.h"  // 너비우선탐색

StackType stack;
pos p;

int **matrix;
int n, m;
int move;  // 움직인 칸수
int flag = 0;


// visited 쓰지 않고 한번 지나간 칸의 matrix값 변경
// 맵 초기화 - 입력받은 크기로 메모리 동적할당
void Init(int n, int m) {
	matrix = (int**)malloc(sizeof(int *) * n);
	for (int i = 0; i < n; i++)
		matrix[i] = (int*)malloc(sizeof(int) * m);
}

void dfs(int x, int y) {

	// 인덱스가 맵의 범위를 벗어나면 return
	if (x < 0 || x >= n || y < 0 || y >= m) return;

	// 이동칸수 계산하기 위함
	// (미로탈출 성공)마지막 인덱스 도착-도착지점 도달하면 다시 처음위치로 되돌아가면서 그때 이동칸수 ++하면서 계산 
	if (x == n - 1 && y == m - 1 && matrix[x][y]) {
		move++;
		matrix[x][y] = 0;
		p.xpos = x; p.ypos = y;  push(&stack, p);
		flag = 1;   // flag 1로 변경
	}

	if (matrix[x][y]) {  // 값이 1이라면, 갈 수 있는 길이라면 
		if (flag == 1 && matrix[x][y]) return;    // flag =1, 되돌아가는 중이기 때문에 다시 탐색으로 빠지면 안됨.

		matrix[x][y] = 0;  // 한번 지나간 칸 0으로 변경

		dfs(x - 1, y);   // 상
		dfs(x + 1, y);   // 하
		dfs(x, y - 1);   // 좌
		dfs(x, y + 1);   // 우
		 
		// 도착지점 이미 도달한 상태. 이동칸수++ , 이동한 칸 스택에 push
		// 그냥 출력하면 뒤에서부터 거꾸로 출력되기 때문에 스택에 넣어서 나중에 한꺼번에 출력해준다.
		if (flag == 1) { move++;  p.xpos = x; p.ypos = y;  push(&stack, p); }

		matrix[x][y] = 1; // 경로가 막혀서 되돌아오면 여기부터 다른길로 다시 탐색해야하기 때문에 다시 1로 변경
	}
}


void main()
{
	char s[30];
	// 미로 크기 입력
	printf("N x M : ");
	scanf("%d %d", &n, &m);
	Init(n, m);  // DFS 미로 초기화

	// 미로 입력 - 사용자로부터 0,1 값을 입력받아 미로를 구성한다.
	printf("미로 입력\n");
	for (int i = 0; i < n; i++) {
		scanf("%s", &s);
		for (int k = 0; k < m; k++) 
			matrix[i][k] = s[k] - '0';
	}

	// 입력받은 미로 확인
	printf("미로 출력\n");
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < m; k++) {
			printf("%4d ", matrix[i][k]);
		}
		printf("\n");
	}
	printf("\n");
	init(n, m, matrix);  // BFS 미로, visited 배열 초기화


	init(&stack);  // 스택 초기화
	move = 0;  // 총 이동한 칸수 count
	dfs(0, 0);   // 시작지점 (0,0)

	// DFS로 실행한 미로찾기
	printf("** DFS를 이용한 미로찾기 결과 **\n\n");
	if(flag == 0) printf("미로탈출 실패!\n");
	else {
		while (!is_empty(&stack)) {
			p = pop(&stack);
			printf("[ %d, %d ] -> ", p.xpos, p.ypos);    // 이동했던 경로 출력
		}
		printf("미로탈출 성공!\n");
		printf("\n\n이동한 칸 수 : %d\n", move);    // 결과출력
	}

	// BFS로 실행한 미로찾기 
	printf("\n\n\n** BFS를 이용한 미로찾기 결과 **\n\n");
	bfs_main(n, m);
	printf("\n\n");
}









