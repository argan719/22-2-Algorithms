
/*
// insertion sort ����
// C++

#include<iostream>
using namespace std;

void insertion_sort(int *arr, int n) {
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = arr[i];    // �ι�° �ε������� key������ ����
		for (j = i - 1; 0 <= j && key < arr[j]; j--) {
			arr[j + 1] = arr[j];    // ���������� �� ĭ�� �̵�.
		}
		arr[j + 1] = key;  // ������ j-- ���� ������ �ٽ� +1�� ���� �� �� ��ġ�� ���� ����.
	}
}

void main()
{
	int n;
	cout << "�Է¹��� ���� ���� : ";
	cin >> n;
	
	cout << "������ ���� �Է�" << endl;
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
	if (i > mid) {  // �����ִ� ���ڵ� ���� ���� - ������
		while (j <= right) tmp[k++] = arr[j++];
	}
	else {   // �����ִ� ���ڵ� ���� ���� - ����
		while (i <= mid) tmp[k++] = arr[i++];
	}
	for (i = left; i <= right; i++)  // ���� (tmp -> arr)
		arr[i] = tmp[i];
}

int main(void)
{
	int arr[] = { 8, 2, 4, 9, 3, 6 };
	int l = 0;
	int h = sizeof(arr) / sizeof(arr[0]);
	merge_sort(arr, l, h-1);   // ù��°�ε���, �������ε���

	for (int i = 0; i < h; i++)
		printf("%3d", arr[i]);
}
*/



/*
// quick sort �ڵ�
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
#define SWAP(x, y, t)  ( t = x, x = y, y = t)


int n;
int list[MAX_SIZE];

int partition(int list[], int left, int right)
{
	int tmp;
	int pivot = list[left];   // �Ǻ� ���� (�� ���ʰ�)
	int p = left;   // �Ǻ� �ε��� ����
	right++;

	while (left < right) {     
		do {
			left++;
		} while (left <= right && list[left] < pivot);

		do {
			right--;
		} while (right >= p && list[right] > pivot);

		if (left < right) SWAP(list[left], list[right], tmp);  // ���õ� �� ���ڵ� ��ȯ
	}

	SWAP(list[p], list[right], tmp);   // �ε��� right�� ����Ű�� ���ڵ�� �Ǻ� ��ȯ

	return right;
}

void quick_sort(int list[], int left, int right)
{
	int q;
	if (left < right) {
		q = partition(list, left, right);

		quick_sort(list, left, q - 1);       // ���� �κи���Ʈ�� ������
		quick_sort(list, q + 1, right);      // ������ �κи���Ʈ�� ������
	}
}

void main()
{
	int i;
	n = MAX_SIZE;
	for (i = 0; i < n; i++)      // ���� ���� �� ���
		list[i] = rand() % n;   // ���� �߻� ���� 0~n
	printf("==������\n");
	for (i = 0; i < n; i++)
		printf("%4d", list[i]);

	printf("\n\n==������\n");
	quick_sort(list, 0, n - 1);   // ������ ȣ��
	for (i = 0; i < n; i++)
		printf("%4d", list[i]);
	printf("\n\n");
}
*/




/*
// ���� 11004��
#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;
//#define MAX_SIZE 5,000,001
#define SWAP(x, y, t)  ( t = x, x = y, y = t)


int partition(vector<int> list, int left, int right)
{
	int tmp;
	int pivot = list[left];   // �Ǻ� ���� (�� ���ʰ�)
	int p = left;   // �Ǻ� �ε��� ����
	right++;

	while (left < right) {
		do {
			left++;
		} while (left <= right && list[left] < pivot);

		do {
			right--;
		} while (right >= p && list[right] > pivot);

		if (left < right) SWAP(list[left], list[right], tmp);  // ���õ� �� ���ڵ� ��ȯ
	}

	SWAP(list[p], list[right], tmp);   // �ε��� right�� ����Ű�� ���ڵ�� �Ǻ� ��ȯ

	return right;
}

void quick_sort(vector<int> list, int left, int right)
{
	int q;
	if (left < right) {
		q = partition(list, left, right);

		quick_sort(list, left, q - 1);       // ���� �κи���Ʈ�� ������
		quick_sort(list, q + 1, right);      // ������ �κи���Ʈ�� ������
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
	quick_sort(list, 0, n - 1);   // ������ ȣ��
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
	int pivot = list[left];   // �Ǻ� ���� (�� ���ʰ�)
	int p = left;   // �Ǻ� �ε��� ����
	right++;

	while (left < right) {
		do {
			left++;
		} while (left <= right && list[left] < pivot);

		do {
			right--;
		} while (right >= p && list[right] > pivot);

		if (left < right) SWAP(list[left], list[right], tmp);  // ���õ� �� ���ڵ� ��ȯ
	}

	SWAP(list[p], list[right], tmp);   // �ε��� right�� ����Ű�� ���ڵ�� �Ǻ� ��ȯ

	return right;
}

void quick_sort(int list[], int left, int right)
{
	int q;
	if (left < right) {
		q = partition(list, left, right);

		quick_sort(list, left, q - 1);       // ���� �κи���Ʈ�� ������
		quick_sort(list, q + 1, right);      // ������ �κи���Ʈ�� ������
	}
}
int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &list[i]);
	}
	quick_sort(list, 0, n - 1);   // ������ ȣ��
	printf("%d\n", list[k]);  // ���� �� k��° �� ���

	printf("\n������\n");
	for (int i = 0; i < n; i++) {
		printf("%3d", list[i]);
	}
}
*/


/*
// �ð��ʰ� ���� ������ ������ �ڵ�
// partition �Լ��� quick_sort�� ���� �ۼ����� �ʰ� �ϳ��� ���ƴ�.

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
	int pivot = list[left];   // �Ǻ� ���� (�� ���ʰ�)
	int p = left;   // �Ǻ� �ε��� ����
	int low = left;
	int high = right + 1;

	if (left < right) {
		while (low < high) {
			low++;
			while (low <= high && list[low] < pivot) low++;

			high--;
			while (high >= p && list[high] > pivot) high--;

			if (low < high) SWAP(low, high);  // ���õ� �� ���ڵ� ��ȯ
		}
		SWAP(p, high);   // �ε��� right�� ����Ű�� ���ڵ�� �Ǻ� ��ȯ

		quick_sort(left, high - 1);       // ���� �κи���Ʈ�� ������
		quick_sort(high + 1, right);      // ������ �κи���Ʈ�� ������
	}

}

int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &list[i]);
	}
	quick_sort(0, n - 1);   // ������ ȣ��
	printf("%d\n", list[k - 1]);  // ���� �� k��° �� ���
}
*/


/*
#include<stdio.h>
#define SWAP(x, y, t)  ( t = x, x = y, y = t)

int list[5000001];

void quick_sort(int left, int right)
{
	int tmp = NULL;
	int pivot = list[left];   // �Ǻ� ���� (�� ���ʰ�)
	int p = left;   // �Ǻ� �ε��� ����
	int low = left;
	int high = right + 1;

	while (low < high) {
		low++;
		while (low <= high && list[low] < pivot) low++;

		high--;
		while (high >= p && list[high] > pivot) high--;

		if (low < high) SWAP(list[left], list[right], tmp);  // ���õ� �� ���ڵ� ��ȯ
	}
	SWAP(list[p], list[right], tmp);   // �ε��� right�� ����Ű�� ���ڵ�� �Ǻ� ��ȯ

	if (left < high - 1) quick_sort(left, high - 1);       // ���� �κи���Ʈ�� ������
	if (high + 1 < right) quick_sort(high + 1, right);      // ������ �κи���Ʈ�� ������
}

int main(void)
{
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &list[i]);
	}
	quick_sort(0, n - 1);   // ������ ȣ��
	printf("%d\n", list[k - 1]);  // ���� �� k��° �� ���
}
*/




/*
// Longest Common Subsequence
// LCS(Longest Common Subsequence, ���� ���� �κ� ����)

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
	for (j = 0; j <= y.length(); j++)  // 0�� 0���� ä���
		map[0][j] = 0;

	for (i = 0; i <= x.length(); i++)  // 0�� 0���� ä���
		map[i][0] = 0;

	for (i = 1; i <= x.length(); i++) {
		for (j = 1; j <= y.length(); j++) {
			if (x[i-1] == y[j-1]) map[i][j] = map[i - 1][j - 1] + 1;
			else {
				map[i][j] = max(map[i - 1][j], map[i][j - 1]);
			}
		}
	}

	
	// LCS ���� �� map ���
	printf("\n == map == \n");
	for (i = 0; i <= x.length(); i++) {
		for (j = 0; j <= y.length(); j++) {
			printf("%3d", map[i][j]);
		}
		printf("\n");
	}

	printf("%d", map[x.length()][y.length()]);  // ������� ��� - map���� map[SIZE][SIZE] ���� ���� LCS ���
}
*/






