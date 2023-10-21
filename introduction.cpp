
/*
// insertion sort 구현
// C++

#include<iostream>
using namespace std;

void insertion_sort(int *arr, int n) {
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = arr[i];    // 두번째 인덱스부터 key값으로 설정
		for (j = i - 1; 0 <= j && key < arr[j]; j--) {
			arr[j + 1] = arr[j];    // 오른쪽으로 한 칸씩 이동.
		}
		arr[j + 1] = key;  // 마지막 j-- 연산 때문에 다시 +1을 해준 뒤 그 위치에 최종 삽입.
	}
}

void main()
{
	int n;
	cout << "입력받을 숫자 개수 : ";
	cin >> n;
	
	cout << "정렬할 숫자 입력" << endl;
	int *arr = (int *)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	insertion_sort(arr, n);
}
*/



/*
// merge sort

#include<iostream>
#define MAX_SIZE 100
using namespace std;

void merge(int*a, int, int, int);

void merge_sort(int *arr, int l, int h)
{
	int mid;
	if (l < h) {
		mid = (l + h) / 2;
		merge_sort(arr, l, mid);
		merge_sort(arr, mid + 1, h);
		merge(arr, l, mid, h);
	}
}

void merge(int *arr, int left, int mid, int right) {
	int tmp[MAX_SIZE];

	int i, j, k;
	i = left;  j = mid + 1; k = left;

	while (i <= mid && j <= right) {
		if (arr[i] < arr[j]) { tmp[k++] = arr[i++];  }
		else { tmp[k++] = arr[j++]; }
	}
	if (i > mid) {  // 남아있는 레코드 마저 복사 - 오른쪽
		while (j <= right) tmp[k++] = arr[j++];
	}
	else {   // 남아있는 레코드 마저 복사 - 왼쪽
		while (i <= mid) tmp[k++] = arr[i++];
	}
	for (i = left; i <= right; i++)  // 복사 (tmp -> arr)
		arr[i] = tmp[i];
}

int main(void)
{
	int arr[] = { 8, 2, 4, 9, 3, 6 };
	int l = 0;
	int h = sizeof(arr) / sizeof(arr[0]);
	merge_sort(arr, l, h-1);   // 첫번째인덱스, 마지막인덱스

	for (int i = 0; i < h; i++)
		printf("%3d", arr[i]);
}
*/



/*
// quick sort 코드
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
#define SWAP(x, y, t)  ( t = x, x = y, y = t)


int n;
int list[MAX_SIZE];

int partition(int list[], int left, int right)
{
	int tmp;
	int pivot = list[left];   // 피봇 설정 (맨 왼쪽값)
	int p = left;   // 피봇 인덱스 저장
	right++;

	while (left < right) {     
		do {
			left++;
		} while (left <= right && list[left] < pivot);

		do {
			right--;
		} while (right >= p && list[right] > pivot);

		if (left < right) SWAP(list[left], list[right], tmp);  // 선택된 두 레코드 교환
	}

	SWAP(list[p], list[right], tmp);   // 인덱스 right이 가리키는 레코드와 피봇 교환

	return right;
}

void quick_sort(int list[], int left, int right)
{
	int q;
	if (left < right) {
		q = partition(list, left, right);

		quick_sort(list, left, q - 1);       // 왼쪽 부분리스트를 퀵정렬
		quick_sort(list, q + 1, right);      // 오른쪽 부분리스트를 퀵정렬
	}
}

void main()
{
	int i;
	n = MAX_SIZE;
	for (i = 0; i < n; i++)      // 난수 생성 및 출력
		list[i] = rand() % n;   // 난수 발생 범위 0~n
	printf("==정렬전\n");
	for (i = 0; i < n; i++)
		printf("%4d", list[i]);

	printf("\n\n==정렬후\n");
	quick_sort(list, 0, n - 1);   // 퀵정렬 호출
	for (i = 0; i < n; i++)
		printf("%4d", list[i]);
	printf("\n\n");
}
*/




/*
// 백준 11004번
#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;
//#define MAX_SIZE 5,000,001
#define SWAP(x, y, t)  ( t = x, x = y, y = t)


int partition(vector<int> list, int left, int right)
{
	int tmp;
	int pivot = list[left];   // 피봇 설정 (맨 왼쪽값)
	int p = left;   // 피봇 인덱스 저장
	right++;

	while (left < right) {
		do {
			left++;
		} while (left <= right && list[left] < pivot);

		do {
			right--;
		} while (right >= p && list[right] > pivot);

		if (left < right) SWAP(list[left], list[right], tmp);  // 선택된 두 레코드 교환
	}

	SWAP(list[p], list[right], tmp);   // 인덱스 right이 가리키는 레코드와 피봇 교환

	return right;
}

void quick_sort(vector<int> list, int left, int right)
{
	int q;
	if (left < right) {
		q = partition(list, left, right);

		quick_sort(list, left, q - 1);       // 왼쪽 부분리스트를 퀵정렬
		quick_sort(list, q + 1, right);      // 오른쪽 부분리스트를 퀵정렬
	}
}
int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);
	vector<int> list;
	for (int i = 0; i < n; i++) {
		scanf("%d", &list[i]);
	}
	quick_sort(list, 0, n - 1);   // 퀵정렬 호출
	printf("%d", list[k]);
}
*/

/*
#include<iostream>
#include<stdio.h>
//#include<vector>
//using namespace std;
#define MAX_SIZE 5000001
#define SWAP(x, y, t)  ( t = x, x = y, y = t)

int list[MAX_SIZE];

int partition(int list[], int left, int right)
{
	int tmp;
	int pivot = list[left];   // 피봇 설정 (맨 왼쪽값)
	int p = left;   // 피봇 인덱스 저장
	right++;

	while (left < right) {
		do {
			left++;
		} while (left <= right && list[left] < pivot);

		do {
			right--;
		} while (right >= p && list[right] > pivot);

		if (left < right) SWAP(list[left], list[right], tmp);  // 선택된 두 레코드 교환
	}

	SWAP(list[p], list[right], tmp);   // 인덱스 right이 가리키는 레코드와 피봇 교환

	return right;
}

void quick_sort(int list[], int left, int right)
{
	int q;
	if (left < right) {
		q = partition(list, left, right);

		quick_sort(list, left, q - 1);       // 왼쪽 부분리스트를 퀵정렬
		quick_sort(list, q + 1, right);      // 오른쪽 부분리스트를 퀵정렬
	}
}
int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &list[i]);
	}
	quick_sort(list, 0, n - 1);   // 퀵정렬 호출
	printf("%d\n", list[k]);  // 정렬 후 k번째 수 출력

	printf("\n정렬후\n");
	for (int i = 0; i < n; i++) {
		printf("%3d", list[i]);
	}
}
*/


/*
// 시간초과 문제 때문에 수정한 코드
// partition 함수와 quick_sort를 따로 작성하지 않고 하나로 합쳤다.

#include<stdio.h>

int list[5000001];

void SWAP(int x, int y) {
	int tmp;
	tmp = list[x];
	list[x] = list[y];
	list[y] = tmp;
}

void quick_sort(int left, int right)
{
	int pivot = list[left];   // 피봇 설정 (맨 왼쪽값)
	int p = left;   // 피봇 인덱스 저장
	int low = left;
	int high = right + 1;

	if (left < right) {
		while (low < high) {
			low++;
			while (low <= high && list[low] < pivot) low++;

			high--;
			while (high >= p && list[high] > pivot) high--;

			if (low < high) SWAP(low, high);  // 선택된 두 레코드 교환
		}
		SWAP(p, high);   // 인덱스 right이 가리키는 레코드와 피봇 교환

		quick_sort(left, high - 1);       // 왼쪽 부분리스트를 퀵정렬
		quick_sort(high + 1, right);      // 오른쪽 부분리스트를 퀵정렬
	}

}

int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &list[i]);
	}
	quick_sort(0, n - 1);   // 퀵정렬 호출
	printf("%d\n", list[k - 1]);  // 정렬 후 k번째 수 출력
}
*/


/*
#include<stdio.h>
#define SWAP(x, y, t)  ( t = x, x = y, y = t)

int list[5000001];

void quick_sort(int left, int right)
{
	int tmp = NULL;
	int pivot = list[left];   // 피봇 설정 (맨 왼쪽값)
	int p = left;   // 피봇 인덱스 저장
	int low = left;
	int high = right + 1;

	while (low < high) {
		low++;
		while (low <= high && list[low] < pivot) low++;

		high--;
		while (high >= p && list[high] > pivot) high--;

		if (low < high) SWAP(list[left], list[right], tmp);  // 선택된 두 레코드 교환
	}
	SWAP(list[p], list[right], tmp);   // 인덱스 right이 가리키는 레코드와 피봇 교환

	if (left < high - 1) quick_sort(left, high - 1);       // 왼쪽 부분리스트를 퀵정렬
	if (high + 1 < right) quick_sort(high + 1, right);      // 오른쪽 부분리스트를 퀵정렬
}

int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &list[i]);
	}
	quick_sort(0, n - 1);   // 퀵정렬 호출
	printf("%d\n", list[k - 1]);  // 정렬 후 k번째 수 출력
}
*/




/*
// Longest Common Subsequence
// LCS(Longest Common Subsequence, 최장 공통 부분 수열)

#include<iostream>
#include<stdio.h>
#include<string>
#include<algorithm>
#define SIZE 1000
using namespace std;

int map[SIZE + 1][SIZE + 1] = { -1, };

//		   A C A Y K P (x)
//		0  0 0 0 0 0 0
//  C   0
//  A   0
//  P   0
//  C   0
//  A   0
//  K   0
// (y)


int main(void)
{
	string x, y;
	cin >> x;
	cin >> y;

	int i, j;
	for (j = 0; j <= y.length(); j++)  // 0행 0으로 채우기
		map[0][j] = 0;

	for (i = 0; i <= x.length(); i++)  // 0열 0으로 채우기
		map[i][0] = 0;

	for (i = 1; i <= x.length(); i++) {
		for (j = 1; j <= y.length(); j++) {
			if (x[i-1] == y[j-1]) map[i][j] = map[i - 1][j - 1] + 1;
			else {
				map[i][j] = max(map[i - 1][j], map[i][j - 1]);
			}
		}
	}

	
	// LCS 연산 후 map 출력
	printf("\n == map == \n");
	for (i = 0; i <= x.length(); i++) {
		for (j = 0; j <= y.length(); j++) {
			printf("%3d", map[i][j]);
		}
		printf("\n");
	}

	printf("%d", map[x.length()][y.length()]);  // 최종결과 출력 - map에서 map[SIZE][SIZE] 값이 최종 LCS 결과
}
*/






