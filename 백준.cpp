
/*
// 2108��
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath> // �ݿø�
#define MAX 8001
using namespace std;

int main(void) {
	int n, i;
	int v;

	vector<int> mode;  // �ֺ� ���� ����
	int cnt[MAX] = { 0, };    // -4000 -> 0 4000 -> 8000

	scanf("%d", &n);
	vector<int> arr;

	double sum = 0;
	int max = -4000;
	int cnt_max = 0;

	// ���� �Է¹ޱ�
	for (i = 0; i < n; i++) {
		scanf("%d", &v);
		arr.push_back(v);
		sum += v;
		cnt[v + 4000]++;
		if (cnt_max < cnt[v + 4000]) cnt_max = cnt[v + 4000];  // �ֺ� Ƚ��(�� �� ���;� �ֺ��̳�?)
		if (max < v) max = v;
	}
	sort(arr.begin(), arr.end());  // ����

	double aver = sum / n;  // ������ ���ϱ�
	int range = *(arr.end() - 1) - *(arr.begin());   // ���� ���ϱ� 

	// �ֺ� ���ϱ�
	for (i = 0; i <= max + 4000; i++) {  // �ð� ������ ���� 8000���� ���� �ʰ� �ִ� ���Ѵ��� �� �������� ������
		if (cnt_max == cnt[i]) mode.push_back(i - 4000);
	}


	printf("%.0f\n", floor(aver + 0.5));  // ������ ���
	printf("%d\n", arr[n / 2]);   // �߾Ӱ� ���

	sort(mode.begin(), mode.end());  // ����
	// �ֺ� ���
	if (mode.size() == 1) printf("%d\n", *(mode.begin()));
	else printf("%d\n", mode.at(1));

	printf("%d\n", abs(range));    // ���� ���
}

*/




/*
// 11049��
// ��� ���� ���� (Matrix Chain Order)
#include<iostream>
#define SIZE 501
#define MAX 2147483647  // (2^31 - 1) + 1
using namespace std;

// n = 5 ���,
//	0	*	*	*	����
//		0	*	*	*
//			0	*	*
//				0	*
//					0

// field�� �̷�����
// ���� ĭ ���� ����ϸ� �� field[1][n] (field �ε��� 1���� ����)
// field[1][n] ���� ���� ���ϰ��� �ϴ� ���� = matrix chain order �������

int n;
int matrix[SIZE];

int main(void) {
	cin >> n;
	int x, y;
	for (int i = 0; i < n; i++) {
		cin >> x;
		cin >> y;
		matrix[i] = x;
		matrix[i + 1] = y;
	}

	int l, i, j, k;
	int q;
	int field[SIZE][SIZE] = { MAX, };

	for (l = 1; l < n; l++) {  // n=5��� (0,0) (1,1)..(4,4) ������ �����ϰ� 4���� Ⱦ���̵� �ʿ�
		for (i = 1, j = l + 1; j <= n; i++, j++) {
			field[i][j] = MAX;
			for (k = i; k < j; k++) {
				if (i == j) field[i][j] = 0;
				else {
					q = field[i][k] + field[k + 1][j] + matrix[i - 1] * matrix[k] * matrix[j];
					//cout << "q : " << q << endl;
					if (q < field[i][j]) field[i][j] = q;
					//printf("field[%d][%d] : %d\n", i, j, field[i][j]);
				}
			}
		}
	}

	cout <<  field[1][n];   // ������
}
*/




/*
// 11047�� - ���� ��, greedy �̿�

#include<iostream>
using namespace std;

int main(void) {
	int n, k, i;
	int val;

	cin >> n;
	cin >> k;
	int *arr = (int*)malloc(sizeof(int)*n);  // n����ŭ �迭����
	// n���� ���� ��ġ �Է�
	for (i = 0; i < n; i++) {
		cin >> arr[i];
	}

	int cnt = 0;
	i = n - 1;  // ���� ��ġ�� ���� �������� ���� - �迭�� �� ������ �ε������� ����
	while (k != 0) {
		cnt += k / arr[i];   // ������ �� ���� count�� �����ְ�
		k = k % arr[i];     // k�� ������ �� �� ������ ������ �������
		i--;
		if (i < 0) break;
	}
	cout << cnt;   // ��� ��� - �ʿ��� ���� ������ �ּҰ�
}
*/



/*
// 12865�� - Knapsack ���� DP�̿�

#include<iostream>
#define ROW 101
#define COLUMN 100001
using namespace std;

typedef struct p {
	int w;  // ������ ����
	int v;  // ������ ��ġ
}Product;

int main(void) {
	int n, k;
	cin >> n >> k;

	Product p[ROW];  // ����ü �迭 ����
	int matrix[ROW][COLUMN];   // 2���� �迭 ����

	// N���� ���ǿ� ���� ����,��ġ �Է�
	for (int i = 1; i <= n; i++) {
		cin >> p[i].w >> p[i].v;
	}

	// bottom-up����. ���� ������ ���� (0~n) ���� ���� (0~k)
	int tmp;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			if (i == 0 || j == 0) matrix[i][j] = 0;   // 0��� 0���� 0���� ä��
			else {
				if (p[i].w > j) matrix[i][j] = matrix[i - 1][j];   // ���� �������� ������ ���԰� �� ������ ũ�ٸ� ���ʰ� �״�� ������
				else {  // ���׿����� �̿�
					(p[i].v + matrix[i - 1][j - p[i].w] < matrix[i - 1][j]) ? tmp = matrix[i - 1][j] : tmp = p[i].v + matrix[i - 1][j - p[i].w];
					matrix[i][j] = tmp;
				}  // �׷��� ���� ���, i��° ������ + p[ i - 1 ,w - i ]  or  p[i - 1, w]   �� �� ū ������ �����Ѵ�.
			}  // i��° ������ + p [ i-1, w-i] �� �ǹ��ϴ� �� i��° �������� ���Ը� �� ���� i - 1����.
		  // ��, i ��° ������ ���� �ڸ��� �����ϰ� (�� ���Ը�ŭ �� ���¿���) ������ �ָ� ���� ���� ����. �ű�ٰ� i��° ��ġ ���� ��.
		}  // p[i-1, w] �� �ٷ� ���� ĭ�� �ش���. '�� ���������� ������'�� �� ũ�ٸ� ���� �ִ� �� �״�� �������� ����.
	}
	cout << matrix[n][k];    // ����� �� ������ �ؿ� ���� ���� ����̹Ƿ� �״�� ����ϸ� ���� �ȴ�.
}
*/






// ���� 21568��
// Extended Euclid Algorithm

// �ذ� ����


/*
#include<iostream>
#include <stdio.h>
using namespace std;

void EE(int a, int b, int c) {
	int r1 = a, r2 = b, s1 = 1, s2 = 0, t1 = 0, t2 = 1;
	int r, s, t, q;

	while (r2) {
		q = r1 / r2;
		// gcd ���
		r = r1 % r2;
		r1 = r2, r2 = r;

		// s ���
		s = s1 - q * s2;
		s1 = s2, s2 = s;

		// t ���
		t = t1 - q * t2;
		t1 = t2, t2 = t;

		//if (a*s1 + b * t1 == c)  cout << s1 << " " << t1;

	}
	s = s1; t = t1;
	printf("gcd(%d, %d) = %d, s = %d, t = %d \n", a, b, r1, s, t);

}

int main() {
	int a, b, c;
	// A, B, C �� �Է¹ޱ�   Ax+By = C
	cin >> a >> b >> c;
	EE(a, b, c);
}
*/



/*
#include<stdio.h>
#include<iostream>
using namespace std;

int EE()
{

}

int main()
{
	int a, b, c;
	// A, B, C �� �Է¹ޱ�   Ax+By = C
	cin >> a >> b >> c;
	EE(a, b, c);
}
*/



/*
// 2839��

#include<iostream>
using namespace std;

int main(void)
{
	int tot = 0;
	int tmp;
	int n;
	cin >> n;
	
	if (n < 3) cout << -1;
	else {
		tot = n / 5;
		while (tot >= 0) {
			tmp = n - 5 * tot;
			
			if (tmp % 3 == 0) {
				tot += tmp / 3;
				cout << tot; return 0;
			}
			tot--;
		}
		cout << -1;
	}
}
*/


/*
// 1931��
#include<iostream>
#include<stdio.h>
#include<algorithm> 
#include<vector>
using namespace std;

int main(void) {
	int n;
	cin >> n;
	int i;
	int s, e;

	vector<pair<int, int>> vec;

	for (i = 0; i < n; i++) {
		scanf("%d %d", &s,  &e);
		vec.push_back(make_pair(e, s));
	}
	sort(vec.begin(), vec.end());

	i = vec[0].first;
	int room = 1;
	for (int j = 1; j < n; j++) {
		if (vec[j].second >= i) {
			room++;
			i = vec[j].first;
		}
	}
	cout << room;
}
*/



/*
// 11399
#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

int main(void) {
	int n;
	int t;
	cin >> n;

	vector<int> vec;
	vector<int> ::iterator it;
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		vec.push_back(t);
	}

	int sum = 0;
	int tot = 0;
	sort(vec.begin(), vec.end());
	it = vec.begin();
	while (it != vec.end()) {
		sum = sum + *it;
		tot += sum;
		it++;
	}
	printf("%d", tot);
}
*/


/*
// 1541��
#include<iostream>
#include<string>
using namespace std;

int main(void) {
	string str;
	cin >> str;

	int flag = 0;
	string num = "";
	int tot = 0;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '-' || str[i] == '+') {
			if (!flag) tot += stoi(num);
			else tot -= stoi(num);
			if(str[i] == '-' ) flag = 1;
			num = "";
		}
		else {
			num += str[i];
		}

	}
	if (!flag) tot += stoi(num);
	else tot -= stoi(num);

	cout << tot;
}
*/



/*
// 2217��
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(void) {
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<int> rope;
	int val;

	for (int i = 0; i < n; i++) {
		cin >> val;
		rope.push_back(val);
	}

	sort(rope.rbegin(), rope.rend());

	int max = rope[0];

	for (int i = 1; i < n; i++) {
		if ((i + 1)*rope[i] > max) max = (i + 1)*rope[i];
	}

	cout << max;
}
*/



/*
// 1946��
#include<iostream>
#include<vector>
#define MAX 100001
using namespace std;

int score[MAX];  // ���������̹Ƿ� 0���� �ʱ�ȭ ��

int main(void) {
	ios::sync_with_stdio(false);

	int testcase;
	int n;
	int x, y;  // 1������, 2������
	int t;
	int max;
	cin >> testcase;
	for (int i = 0; i < testcase; i++) {
		t = 0;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> x >> y;
			score[x] = y;
		}
		// x��(1������)�� �ε����� Ȱ���ϸ� ������ �ʿ䰡 ����!
		max = score[1];
		t++;
		for (int i = 2; i <= n; i++) {
			if (max > score[i]) {
				max = score[i];
				t++;
			}
		}
		// �׸��� for�� 2�� ���� �ʿ䰡 ����! 
		// 1������ ������ ������� ���ٸ� 2�� ������ ������ �� ���ƾ����� (max���� ���ƾ�����) ������ ����
		cout << t << endl;  // ���⼭ �ٷ� ����ָ� �Ǵ� �ſ���. 
		// ���� ���� �߸� ������ - testcase���� ����ִ� �� �ƴ϶� ���߿� �Ѳ����� �������� �ϴ� ���� �˾���.
	}

}
*/



/*
// 1715��
#include<iostream>
#include<queue>
#include<stdio.h>
using namespace std;

int main(void) {
	priority_queue<int, vector<int>, greater<int>> pq;

	int n, t;
	cin >> n;
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		pq.push(t);
	}

	int sum = 0;
	int a, b;
	while (pq.size() > 1) {
		a = pq.top(); pq.pop();
		b = pq.top(); pq.pop();
		sum += a + b;
		pq.push(a+b);
	}

	cout << sum;
}
*/



/*

// 16953��
#include<iostream>
using namespace std;

int main(void) {
	int a, b;
	cin >> a >> b;

	int n;
	
	int count = 0;
	while (a != b) {
		if (a > b) count = -2;
		else if (b % 10 == 1) {    // 10���� ���� ������ = �� ������ �ڸ���
			b = b / 10;
			count += 1;
		}
		else if (b % 2 == 0) {   // b�� 2�� ������������ ���
			b = b / 2;
			count += 1;
		}
	}
	cout << count + 1;
}


*/











/*
// 2023-07-05 ����

// 2839��-DP

#include<iostream>
#include<algorithm>
using namespace std;
int d[5001];

int dp(int k) {
	if (k <= 0) return 5000;
	if (d[k] != 0) return d[k];

	return d[k] = min(dp(k - 3) + 1, dp(k - 5) + 1);
}

int main()
{
	int n;
	cin >> n;  // ��ü ���� �Է¹ޱ�

	d[3] = d[5] = 1;
	for (int i = 1; i <= n; i++) {    // i=6���� �������ߴµ� 4�Է½� -1 ���;� �ϴµ� 0���ͼ� �� 1���� ����.
		dp(i);
	}

	if (d[n] >= 5000) cout << -1;
	else cout << d[n];
}


*/



/*
// 1463��
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	int n;
	cin >> n;

	vector<int>dp(n + 1);
	dp[1] = 0;
	for (int i = 2; i <= n; i++) {
		dp[i] = dp[i - 1] + 1;
		if (!(i % 2)) dp[i] = min(dp[i], dp[i / 2] + 1);
		if (!(i % 3)) dp[i] = min(dp[i], dp[i / 3] + 1);
	}
	
	cout << dp[n];
}
*/



/*
// 1003��
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int>test_case(41);
vector<int>fibo(41);

int fibo_dp(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	
	if (fibo[n] == 0) fibo[n] = fibo_dp(n - 1) + fibo_dp(n - 2);
	return fibo[n];
}


int main()
{
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> test_case[i];
	}
	for (int i = 0; i < n; i++) {
		if (test_case[i] == 0) cout << 1 << " " << 0 << endl;
		else if (test_case[i] == 1) cout << 0 << " " << 1 << endl;
		else cout << fibo_dp(test_case[i] - 1) << " " << fibo_dp(test_case[i]) << endl;
	}
}

*/



/*
// 11726��
#include<iostream>
#include<algorithm>
using namespace std;

int d[1001];


int main()
{
	int n;
	cin >> n;

	d[1] = d[0] = 1;

	for (int i = 2; i <= n; i++) {
		d[i] = (d[i - 1]  + d[i - 2]) % 10007;
	}

	cout << d[n];

}
*/




/*
// 1149��

#include<iostream>
#include<algorithm>

using namespace std;
int house[1001][3];

int main()
{
	int n;
	cin >> n;

	int r, g, b;

	for (int i = 1; i <= n; i++) {
		cin >> r >> g >> b;
		house[i][0] = min(house[i - 1][1], house[i - 1][2]) + r;
		house[i][1] = min(house[i - 1][0], house[i - 1][2]) + g;
		house[i][2] = min(house[i - 1][0], house[i - 1][1]) + b;
	}

	cout << min(min(house[n][0], house[n][1]), house[n][2]);
}

*/





/*
// 2579�� - �̾ �ϱ�
#include<iostream>
#include<algorithm>
using namespace std;

int score[301];
int map[301][2];

int main()
{
	int n;
	cin >> n;
	int i;

	for (i = 1; i <= n; i++) {
		cin >> map[i][0];
	}

	for (i = n; 1 <= i; ) {

	
	}
	cout << score[i];

}

*/




/*
// 1439��

#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

int main(void) {
	string s;
	cin >> s;

	int one = 0;
	int zero = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] != s[i+1]) {
			if (s[i] == '1') one++;
			else zero++;
		}
	}

	cout << min(one,zero);
}
*/




/*
// 1339
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

int arr[26];
vector<string>word;

int greedy() {
	int p;
	int sum = 0;

	// �ڸ������� ����� ���� arr[26] �迭�� �־����
	for (int i = 0; i < word.size(); i++) {
		p = 1;
		for (int k = word[i].length()-1; 0<=k ; k--) {
			arr[word[i][k] - 65] += p;
			p = p * 10;
		}
	}
	// �װ� sorting �ؼ�
	sort(arr, arr + 26);
	
	p = 9;
	for (int i = 25; 0<=i; i--) {
		// ���ĺ��� �����ϸ� (0�� �ƴϸ�)
		if (arr[i]) sum += arr[i] * p;
		p--;
	}
	return sum;
}

int main(void) {
	int n;
	cin >> n;

	string str;

	for (int k = 0; k < n; k++) {
		cin >> str;
		word.push_back(str);
	}

	cout << greedy();
}

*/




/*
// 1202
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#define MAX 300001
using namespace std;

priority_queue<int> pq;
pair<int, int> info[MAX];  // ������ ����,����
int bag[MAX];  // ������ ����(�뷮)

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	long long sum = 0;

	cin >> N >> K;

	// ������ ����, ����
	for (int i = 0; i < N; i++) {
		cin >> info[i].first >> info[i].second;
	}
	// ���濡 ���� �� �ִ� �ִ� ����
	for (int i = 0; i < K; i++) {
		cin >> bag[i];
	}

	sort(info, info + N);  // ���� ���� ��������
	sort(bag, bag + K);  // ���� �뷮 �������� - (����Ʈ�� pair first ���� ������������)

	int j = 0;
	for (int i = 0; i < K; i++) {
		while (bag[i] >= info[j].first && j < N) 
			pq.push(info[j++].second);
		if (!pq.empty()) { sum += pq.top(); pq.pop(); }
	}

	cout << sum;
}

*/



/*
// 1049��
#include<iostream>
#include<algorithm>
using namespace std;

int pack[51]; // ��Ű��(6��)����
int one[51];  // ���� ����

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M;
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		cin >> pack[i] >> one[i];
	}

	sort(pack, pack + M);  // �������� ����- ��Ű�� ���� ����
	sort(one, one + M);  // �������� ���� - ���� ���� ����
	// ��Ű�� ������ �׻� ��������*6���� �۰ų� ����. Ŭ ���� ����.
	// �� ���� ������ ������ �Ǽ� ������ �ؾ� �ϰ�
	// ���� ������ ���� ������ �� * N �� ����
	// ��Ű�� ������ ���� ������ ���� ��Ű�� ������ ���� ���ϸ� ���� ������?
	


	int result = 0;
	// ��Ű�� ���ݰ� ����*6�� ���� ��
	if (pack[0] >= one[0] * 6) {    // ������ �� �ΰų� ������ �Ȱ��� ��� - �ٵ� �̷� ��� ���� ����.
		result = one[0] * N;
	}
	else {  // ��Ű���� �� �� ���
		int n = N / 6;
		if (N % 6 > 0) { // �� 6����� �� ������������ ���
			result = min(pack[0], one[0] * (N % 6));   // ��Ű���� �ϳ� �� �߰��ϴ°� ����, ������ ������ �͸� �� ��°� ���� ��
		}
		result += pack[0] * n;
	}

	cout << result;
}

*/



/*
// 1744
#include<iostream>
#include<algorithm>
using namespace std;

int arr[51];

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + N);
	
	int sum = 0;
	int i = 0;
	if (N == 1) cout << arr[0];   // �Է¹��� ���� �Ѱ��� ���
	else {
		while (i < N) {
			if (arr[i] > 0) break;
			if (arr[i] <= 0 && arr[i + 1] > 0) {  // ������ ������ ����(����� �Ѿ�� ����)
				sum += arr[i];
				i += 1;
			}
			else {  // �ΰ��� �� �����ΰ�� - �� ���� ����� ��(���ϴ°� ���� ����)
				sum += arr[i] * arr[i + 1];
				i += 2;
			}
		}
		i = N - 1;   // �ڿ������� ����-�ֳ� ������ ū�ų��� ���ؾ� ���� Ŀ���� ����. ���� ū������ �� ���ʲ��� ���ؾ� ��.
		while (i >= 0) {
			if (arr[i - 1] == 1) {  // 1�� ��� �׳� 1�� ���� ���ϴ� �� ����(1�� ������ �ȵ�)
				sum += arr[i]; 
				i -= 1;
				while (arr[i]) { // �����߱� ������ 1���� ����������. 1���� ������ 1�� ���� ���ؾ� ��.
					sum += arr[i];
					i -= 1;
				}
			}
			else if (arr[i - 1] > 0) {  //�ΰ��� �� ����ΰ�� - �� ���� ����� ��
				sum += arr[i] * arr[i - 1];
				i -= 2;
			}
			else {
				sum += arr[i];
				i -= 1;
			}
		}
		cout << sum;

	}
}

*/




/*
// 11000��
#include<iostream>
#include<algorithm>
#include<queue>
#define MAX 200001
using namespace std;

pair<int, int> time[MAX];
priority_queue<int, vector<int>, greater<int>> end_time;   

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> time[i].first >> time[i].second;
	}
	sort(time, time + N);  

	int t = 1;
	int i;
	end_time.push(time[0].second);
	for (i = 1; i < N; i++) {
		if (time[i].first >= end_time.top()) end_time.pop();
		else t++;
		end_time.push(time[i].second);
	}
	cout << t;
}

*/




/*
#include<iostream>
#define MAX 51
using namespace std;

char A[MAX][MAX];
char B[MAX][MAX];
int N, M;

void change(int i, int k) {
	for (int a = i; a <= i + 2; a++) {
		for (int b = k; b <= k + 2; b++) {
			if (A[a][b] == '1') A[a][b] = '0';
			else A[a][b] = '1';
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	char n;
	int i, k;
	for (i = 0; i < N; i++) {
		for (int k = 0; k < M; k++) {
			cin >> A[i][k];
		}
	}
	for (i = 0; i < N; i++) {
		for (int k = 0; k < M; k++) {
			cin >> B[i][k];
		}
	}

	int cnt = 0;
	// ��� �� ���� �� �� ���� �������� A�� B�� �ٸ��� Ž��
	for (i = 0; i < N-2; i++) {
		for (k = 0; k < M - 2; k++) {  // 3x3�̶� M-3�����ۿ� �̵�����. - Ŀ�η� ��ü����� �ȴ´ٰ� �����غ�
			if (A[i][k] != B[i][k]) {
				//if (N <= 2 || M <= 2) { cout << -1; break; }  	// �ٵ� N, M�� 1,2�� ���� change�Լ����� 3������ �����ϱ� ���� ����ٵ� ��į? - �׷��� �� �ڵ� �߰�
				// �ٵ� �ٸ� ��� �ڵ� ���ϱ� �̷� �ڵ尡 ����. Ʋ���� ������ �̰� ������ ����
				// ���ʿ� for������ N-2, M-2�� N,M�� 2���� �۰ų� ���ٸ� for������ ���� ���� ����.
				change(i, k); cnt++;
			}
		}
	}

	bool flag = true;
	// ������ �� �� ���� �κе��� B�� �ٸ��� Ȯ�� �� �ƴ϶� ��ü �� Ȯ���ؾ� �ϴ� ����. 
	// �� ���� �κе��� ���� B�� ��ġ�Ѵٴ� ������ ����
	for (i = 0; i < N; i++) {
		for (k = 0; k < M; k++) {
			if (A[i][k] != B[i][k]) { flag = false; break; }
		}
	}
	if (flag) cout << cnt;
	else cout << -1;

}

*/


/*
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int chu[1001];  // ������ ���� ����

int main(void) {
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> chu[i];
	}

	int i = 2;
	int sum = 0;
	bool flag = true;
	bool flag2 = true;
	sort(chu, chu + N);

	int n, idx, k;
	int t = 0;
	if (chu[0] != 1) cout << 1;
	else {
		while (flag) {
			for (idx = t; chu[idx] <= i; idx++) {
				if (chu[idx] == i) {
					i++; t = idx + 1;
				}
			}
			// �� �κ� ���� ����
			if (chu[idx] > i) {
				while (flag2) {
					idx--;
					n = i - chu[idx - 1];
					if (n < 1) { flag2 = false; break; }
					for (k = 0; k < idx - 1; k++) {
						if (chu[k] == n) break;
						else sum += chu[k];

						if (sum == n) break;
					}
					if (k == idx - 1) flag2 = true;
					else { i++; flag2 = false; }
				}

			}
		}
		cout << i;
	}

}
*/



/*
// 2437��
#include<iostream>
#include<algorithm>
using namespace std;
int chu[1001]; 

int main(void) {
	int N, i;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> chu[i];
	}
	sort(chu, chu + N);

	int sum = 0;
	int n = 1;
	if (chu[0] != 1) cout << 1;
	else {
		for (i = 0; i < N; i++) {
			if (chu[i] > n) break;   // �������� ���� n ���� Ŀ�������� ����. n�� �ȵȰŴϱ� - �̶� n���� ��.
			sum += chu[i];
			while (sum >= n) {  // ���±��� ���� �� ���Է� n�� �� �� ���� ������ ��� �ݺ� - n�� �� ũ�� �׶� ���ο� �� �߰�
				n++;
			}
		}
		// ���� ������ �� �ƴٸ� sum+1���� ������ �ȵǴ� �Ű���
		if (i == N) cout << sum + 1;
		else cout << n;
	}
}

*/



/*
// 2847��
#include<iostream>
using namespace std;

int score[101];

int main(void) {
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> score[i];
	}

	int cnt = 0;
	for (int i = N - 1; 0 <= i; i--) {
		while (score[i] <= score[i - 1]) {
			score[i - 1]--;
			cnt++;	
		}
	}

	cout << cnt;
}
*/






/*
// 1700�� - �̿Ϸ�
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;


int name[101];
int flow[101];
pair<int, int> multitab[101];  // MAX��°, �����ǰ �̸�
int check[101];

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N, K;
	cin >> N >> K;

	int n;
	for (int i = 0; i < K; i++) {
		cin >> n;
		if (name[n] < i) name[n] = i;  // �� �����ǰ�� MAX��° ����  (������ 0��°���� ����)
		flow[i] = n;  // ���� ������ä ���� (0���� ù��°�� �Ǵ°���)
	}

	int cnt = 0;
	int idx = 0;
	int max = 0;
	int k;
	int max_idx = 0;

	for(int i=0;i<K;i++) {
		if (idx < N) {
			multitab[idx++] = make_pair(name[flow[i]], flow[i]);  // MAX��°, �̸�
		}
		else {
			if (check[flow[i]]) continue;   // ���� �������°� �̹� ���� �ִٸ� �׳� ��ŵ
			else {
				max = 0;
				for (k = 0; k < N; k++) {
					if (multitab[k].first < i) {  // ������ �� �̻� �� ������ �ְ� ���� �����ִٸ� �긦 ������
						cout << multitab[k].second << " �̰� �̰�" << endl;
						check[multitab[k].second] = 0;
						multitab[k].first = name[flow[i]];
						multitab[k].second = flow[i];
						break;
					}
					if (multitab[k].first > max) {
						max = multitab[k].first; max_idx = k;
					}
				}
				if (k == N) {
					cout << "MAX��: " << multitab[max_idx].second << endl;
					cout << multitab[max_idx].second << " �̰� �̰�" << endl;
					check[multitab[max_idx].second] = 0;
					multitab[max_idx].first = name[flow[i]];
					multitab[max_idx].second = flow[i];

				}
				cnt++;
			}
		}
		//cout << "���� ��Ƽ�� ��Ȳ: " << "������: " << multitab.size() << " top: " << multitab.top().first << " " << multitab.top().second << endl;
		check[flow[i]] = 1;
		cout << flow[i] << " �̰� ����" << endl;
	}

	cout << cnt;
}
*/





/*
// 2812
#include<iostream>
#include<algorithm>
#include<stack>
#define MAX 500001
using namespace std;

int input[MAX];
int main(void) {
	int N, K;
	char c;

	cin >> N >> K;

	stack<int> num;
	for (int i = 0; i < N; i++) {
		cin >> c;
		input[i] = c - '0';
	}

	int cnt = 0;
	num.push(input[0]);
	for (int i = 1; i < N; i++) {
		if (cnt == K) {  // K����ŭ�� �� ���ٸ� �� �̻� pop X. ��� push
			num.push(input[i]);
		}
		else if (num.top() < input[i]) { 
			while (num.top() < input[i]) {  // ���� �������� ������ ũ�ų� ���� ����(���ÿ���) ���� ������ ��� pop
				num.pop();
				cnt++;
				if (cnt == K) break;
				if (num.empty()) break;
			}
			num.push(input[i]);  // ���� �� push
		}
		else num.push(input[i]); // ������ top���� ���� �������� ���� �� �۰ų� ���ٸ� �׳� ���� �������� �� push 
	}

	// ���� ���ڵ��� ������������ �Ǿ� �־ ���� ������ ���������� ��ü N������ K����ŭ �� ���ٸ� K�� �� ������ ��� pop
	while (cnt < K) {
		num.pop();
		cnt++;
	}

	// ���� �Ųٷ� ���
	for (int i = N-K-1; 0 <= i; i--) {
		input[i] = num.top();
		num.pop();
	}
	for (int i = 0; i < N-K; i++) {
		cout << input[i];
	}
}

*/






/*
// 3109��
#include<iostream>
#define ROW 10001
#define COL 501
using namespace std;

int grid[ROW][COL];
int visit[ROW][COL];
int R, C;

int cnt;
int dx[] = { -1, 0, 1 };
int dy[] = { 1, 1, 1};

bool flag;
void dfs(int x, int y) {

	visit[x][y] = 1;
	if (y == C - 1) {
		cnt++; 
		flag = true;
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		int nx = x + dx[i];   // i-1(�����ʴ밢����)  i(������)  i+1(�����ʴ밢���Ʒ�)
		int ny = y + dy[i];  // k+1

		if (nx >= 0 && ny >= 0 && nx < R && ny < C)
		{
			if (grid[nx][ny]  && !visit[nx][ny])  // ���� �ƴϰ� ���� �湮 ���ߴٸ�
			{
				dfs(nx, ny);   // �� Ž��
				if (flag) return;
			}
		}
	}
}

int main(void) {
	cin >> R >> C;

	int i, k;
	char c;
	for (i = 0; i < R; i++) {
		for (k = 0; k < C; k++) {
			cin >> c;
			if (c == 'x') grid[i][k] = 0;  // ��
			else grid[i][k] = 1;  // ��
		}
	}

	for (int i = 0; i < R; i++) {
		flag = false;
		dfs(i, 0);   // �� ���� ù ���� ���� (ó�� ��)
	}
	cout << cnt;
}
*/





/*
// 1783�� - ������
#include<iostream>
using namespace std;

int main(void) {
	int N, M;
	cin >> N >> M;

	int move = 0;   // �̵�Ƚ��
	int cnt = 1;  // ������ ĭ��

	if (M == 1) cout << 1;
	else if (M - 1 == 1) {  // ���α��̰� ��ü 2ĭ�� ���=���������� 1ĭ �̵��� ������ ���
		if (N >= 3) cout << 2;
		else cout << 1;
	}
	else {
		while (move < 4) {
			if ((M - 1) % 2 != 0) {  // 2ĭ �̵� ����

			}
			else {

			}
		}

		// 4�� �̵������ �� �ؾ���. �ȱ׷��ȵ�
		if (move >= 4) {
			
		}
	}
	

}
*/




/*
// 2212��
#include<iostream>
#include<algorithm>
using namespace std;

int sensor[10001];
int dist[10001];

int main(void) {
	int N, K;
	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		cin >> sensor[i];
	}
	sort(sensor, sensor + N);   // ��������

	// ���� ���� �Ÿ� ���̸� ��� ����ؼ� �����ؾ���
	// ��ǥ���� ������ ����
	for (int i = 0; i < N - 1; i++) {
		dist[i] = abs(sensor[i] - sensor[i + 1]);
	}
	sort(dist, dist + N - 1, greater<int>());  // ���� �� �Ÿ� ��������

	int sum = 0;
	int cnt = 1;
	for (int i = 0; i < N; i++) {
		if(cnt > K-1) sum += dist[i];
		else cnt++;
	}

	cout << sum;
}
*/




/*
// 12904
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main(void) {
	string s;
	string t;

	cin >> s >> t;

	int len = t.length() - s.length();   // T�� S ���ڿ� ���� ��

	int i = 0;
	for (int k = t.length() - 1; i < len; k--, i++) {
		if (t[k] == 'B') { 
			reverse(t.begin(), t.begin() + k ); 
		}
		else if (t[k] == 'A') continue;
		else {
			cout << 0; break;
		}
	}
	
	int a;
	if (i >= len) {
		for (a = 0; a < s.length(); a++) {
			if (s[a] != t[a]) { cout << 0;  break;}
		}
		if (a >= s.length()) cout << 1;
	}
}
*/




/*
// 1260��
#include<iostream>
#include<queue>
using namespace std;
typedef struct graph {
	int N;   // ��������
	int M;    // ��������
	int** matrix;       // ���
}Graph;
int *visited;

void GInit(Graph* pGraph, int numberOfVertex) {
	visited = (int*)malloc(sizeof(int) * numberOfVertex);
	pGraph->matrix = (int **)malloc(sizeof(int *) * numberOfVertex);   // �� �����Ҵ�
	for (int i = 0; i < numberOfVertex; i++) {
		pGraph->matrix[i] = (int *)malloc(sizeof(int) * numberOfVertex);  // �� �����Ҵ�
		for (int k = 0; k < numberOfVertex; k++) {
			pGraph->matrix[i][k] = 0;
			visited[k] = 0;
		}
	}
}

void GClear(Graph* pGraph) {
	for (int i = 1; i < pGraph->N; i++) {
		visited[i] = 0;
	}
}

void GAdd(Graph* pGraph, int from, int to) {
	if (!pGraph->matrix[from][to]) {
		pGraph->matrix[from][to] = 1;
		pGraph->matrix[to][from] = 1;
	}
}

void DFS(Graph g, int V) {
	visited[V] = 1;
	cout << V << " ";

	for (int k = 1; k < g.N; k++) {
		if (g.matrix[V][k] && !visited[k]) {
			DFS(g, k);
		}
	}
}

void BFS(Graph g, int V) {
	visited[V] = 1;
	queue<int> q;
	q.push(V);
	int f;

	while(!q.empty()) {
		f = q.front();
		q.pop();
		cout << f << " ";
		for (int k = 1; k < g.N; k++) {
			if (g.matrix[f][k] && !visited[k]) {
				visited[k] = 1;
				q.push(k);
			}
		}
	}

}

int main(void) {
	int N, M, V;
	Graph graph;

	cin >> N >> M >> V;

	graph.N = N + 1;
	graph.M = M;
	GInit(&graph, N+1);
	int from, to;
	for (int i = 0; i < M; i++) {
		cin >> from >> to;
		GAdd(&graph, from, to);
	}

	DFS(graph, V);
	cout << "\n";
	GClear(&graph);
	BFS(graph, V);

}
*/




/*
// 2606��
#include<iostream>
#define MAX 102
using namespace std;

int N, C;
int matrix[MAX][MAX];
int visited[MAX];

int cnt;
void AddEdge(int f, int t) {
	matrix[f][t] = 1;
	matrix[t][f] = 1;
}

void DFS(int v) {
	visited[v] = 1;
	for (int i = 1; i <= C; i++) {
		if (!visited[i] && matrix[v][i]) {
			cnt++;
			DFS(i);
		}
	}
}

int main(void) {
	cin >> C;
	cin >> N;

	int f, t;
	for (int i = 0; i < N; i++) {
		cin >> f >> t;
		AddEdge(f, t);
	}
	DFS(1);
	cout << cnt;
}

*/




/*
// 2667��
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#define MAX 30
using namespace std;

int N;
int matrix[MAX][MAX];
int visited[MAX][MAX];

int cnt;
int dfs(int x, int y) {
	if (x < 0 || x > N || y < 0 || y > N) return 0;

	if (!visited[x][y] && matrix[x][y]) {
		cnt++;  // ���� �� 
		visited[x][y] = 1;

		dfs(x - 1, y);  // ��
		dfs(x + 1, y);  // ��
		dfs(x, y - 1);  // ��
		dfs(x, y + 1);  // ��

	}
	return cnt;
}

int main(void) {
	cin >> N;
	string s;
	vector<int> house;

	// 2���� �迭�� 0,1 ���ڷ� ����
	for (int i = 0; i < N; i++) {
		cin >> s;
		for (int k = 0; k < N; k++)
			matrix[i+1][k+1] = s[k] - '0';
	}

	int t;
	for (int i = 1; i <= N; i++) {
		for (int k = 1; k <= N; k++) {
			cnt = 0;
			t = dfs(i, k);
			if (t != 0) house.push_back(t);
		}
	}

	cout << house.size() << endl;
	sort(house.begin(), house.end());
	for (int i = 0; i < house.size(); i++) {
		cout << house[i] << endl;
	}
}
*/




/*
// 1012��
#include<iostream>
#include<vector>
#define MAX 51
using namespace std;

int matrix[MAX][MAX];
int visited[MAX][MAX];

int M, N;
int cnt;

bool dfs(int x, int y)
{
	if (x < 0 || x >= M || y < 0 || y >= N) return false;

	if (matrix[x][y] && !visited[x][y]) {
		visited[x][y] = 1;

		dfs(x - 1, y);
		dfs(x + 1, y);
		dfs(x, y - 1);
		dfs(x, y + 1);

		return true;
	}
	else return false;
	
}

void init() {
	for (int i = 0; i < M; i++) {
		for (int k = 0; k < N; k++) {
			matrix[i][k] = 0;
			visited[i][k] = 0;
		}
	}
}

int main(void) {

	int T, K;
	cin >> T;

	int x, y;
	vector<int> result;

	while (T > 0) {
		cin >> M >> N >> K;

		for (int i = 0; i < K; i++) {
			cin >> x >> y;
			matrix[x][y] = 1;
		}

		cnt = 0;
		for (int i = 0; i < M; i++) {
			for (int k = 0; k < N; k++) {
				if (dfs(i, k)) cnt++;
			}
		}

		result.push_back(cnt);
		T--;
		init();
	}
	
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << "\n";
	}
}
*/




/*
// 11724��
#include<iostream>
#define MAX 1002
using namespace std;

int N, M;
int matrix[MAX][MAX];
int visited[MAX];

void dfs(int v) {

	visited[v] = 1;
	for (int k = 1; k <= N; k++) {
		if (matrix[v][k] && !visited[k]) {
			matrix[v][k] = 0;
			matrix[k][v] = 0;
			dfs(k);
		}		
	}

}

int main(void) {
	cin >> N >> M;

	int u, v;
	for (int i = 0; i < M; i++) {
		cin >> u >> v;
		matrix[u][v] = 1;
		matrix[v][u] = 1;
	}

	int cnt = 0;
	for (int i = 1; i <= N; i++) {

		if (visited[i] == 0) {
			cnt++;
			dfs(i);
		}
	}

	cout << cnt;
}
*/



/*
// 10026��
#include<iostream>
#include<string>
#include<vector>
#define MAX 101
using namespace std;

int matrix[MAX][MAX];
int visited[MAX][MAX];
// R=0, G=1, B=2
int N;
int color;

bool dfs(int c, int x, int y) {
	
	if (x < 0 || x >= N || y < 0 || y >= N) return false;
	
	if (!visited[x][y] && matrix[x][y] == c) {
		visited[x][y] = 1;
	
		dfs(color, x + 1, y);
		dfs(color, x - 1, y);
		dfs(color, x, y + 1);
		dfs(color, x, y - 1);

		return true;
	}
	else return false;

}

bool dfs(int x, int y) {

	if (x < 0 || x >= N || y < 0 || y >= N) return false;

	if (!visited[x][y] && (matrix[x][y] == 0 || matrix[x][y] == 1)) {
		visited[x][y] = 1;

		dfs(x + 1, y);
		dfs(x - 1, y);
		dfs(x, y + 1);
		dfs(x, y - 1);

		return true;
	}
	else return false;

}

void init() {
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			visited[i][k] = 0;
		}
	}
}

int main(void)
{
	cin >> N;
	string s;
	for (int i = 0; i < N; i++) {
		cin >> s;
		for (int k = 0; k < N; k++) {
			if (s[k] == 'R') matrix[i][k] = 0;
			else if (s[k] == 'G') matrix[i][k] = 1;
			else matrix[i][k] = 2;
		}
	}

	int area[3] = { 0, };

	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			color = matrix[i][k];
			if (dfs(color, i, k)) area[color]++;
		}
	}

	int n = 0;
	for (int i = 0; i < 3; i++) {
		n += area[i];
	}

	init();
	int rg = 0;
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			if (matrix[i][k] != 2) {
				if (dfs(i, k)) rg++;
			}
		}
	}
	
	rg += area[2];
	cout << n << " " << rg;
}
*/



/*
// 4963��
#include<iostream>
#include<string>
#include<vector>
#define MAX 51
using namespace std;

int W, H;
int matrix[MAX][MAX];

bool dfs(int x, int y) {
	if (x < 0 || x >= H || y < 0 || y >= W) return false;

	if (matrix[x][y] == 1) {
		matrix[x][y] = 0;

		dfs(x - 1, y);  // ��
		dfs(x + 1, y);  // ��
		dfs(x, y + 1); // ��
		dfs(x, y - 1); // �Ʒ�
		
		dfs(x - 1, y - 1);  // ���� �� �밢��
		dfs(x - 1, y + 1);  // ������ �� �밢��
		dfs(x + 1, y - 1); // ���� �Ʒ� �밢��
		dfs(x + 1, y + 1); // ������ �Ʒ� �밢��

		return true;
	}
	else return false;
}

void init() {
	for (int i = 0; i < MAX; i++) {
		for (int k = 0; k < MAX; k++) {
			matrix[i][k] = 0;
		}
	}
}

int main(void) {

	int i, k;
	vector<int> island;
	int cnt;
	while (1) {
		cnt = 0;
		cin >> W >> H;
		if (W == 0 && H == 0) break;

		for (i = 0; i < H; i++) {
			for (k = 0; k < W; k++) {
				cin >> matrix[i][k];
			}
		}

		for (i = 0; i < H; i++) {
			for (k = 0; k < W; k++) {
				if (dfs(i, k)) cnt++;
			}
		}
		island.push_back(cnt);
		init();
	}

	for (int v = 0; v < island.size(); v++) {
		cout << island[v] << "\n";
	}

}
*/



/*
// 2468��
#include<iostream>
#define MAX 101
using namespace std;

int N;
int matrix[MAX][MAX];
int visited[MAX][MAX];

bool dfs(int h, int x, int y) {
	if (x < 0 || x >= N || y < 0 || y >= N) return false;

	if (!visited[x][y] && matrix[x][y] > h) {
		visited[x][y] = 1;

		dfs(h, x - 1, y);
		dfs(h, x + 1, y);
		dfs(h, x, y - 1);
		dfs(h, x, y + 1);

		return true;
	}
	else return false;
}

void init() {
	for (int i = 0; i < N; i++) {
		for(int k = 0; k < N; k++) {
			visited[i][k] = 0;
		}
	}
}

int main(void) {
	cin >> N;
	int max = 0;
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			cin >> matrix[i][k];
			if (max < matrix[i][k]) max = matrix[i][k];
		}
	}

	int height = 0;
	int cnt;
	int cnt_max = 0;
	while (height <= max) {
		cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) {
				if (dfs(height, i, k)) cnt++;
			}
		}
		if (cnt > cnt_max) cnt_max = cnt;
		init();
		height++;
	}

	cout << cnt_max;
}
*/



/*
// 11725��
#include<iostream>
#include<vector>
#define MAX 100002
using namespace std;
int N;
vector<int> map[MAX];
int visited[MAX];
int result[MAX];

void dfs(int v) {
	if (!visited[v]) {
		visited[v] = 1;

		for (int i = 0; i < map[v].size(); i++) {
			if (result[map[v][i]] == 0) {
				result[map[v][i]] = v;
				dfs(map[v][i]);
			}
		}
	}
}

int main(void) {
	cin >> N;

	int x, y;
	for (int i = 1; i < N; i++) {
		cin >> x >> y;
		map[x].push_back(y);
		map[y].push_back(x);
	}

	for (int i = 1; i <= N; i++) {
		dfs(i);
	}
	
	for (int i = 2; i <= N; i++) {
		cout << result[i] << "\n";
	}

}
*/



/*
// 1987��
#include<iostream>
#include<string>
using namespace std;

int matrix[21][21];
int R, C;
int alphabet[26];
int max_cnt;
int r, c;
// �� �� �� ��
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int compare(int a, int b) {
	if (a > b) return a; return b;
}

void dfs(int x, int y, int cnt) {
	max_cnt = compare(max_cnt, cnt);

	for (int i = 0; i < 4; i++) {
		r = x + dx[i];
		c = y + dy[i];

		if (r >= 0 && r < R && c >= 0 && c < C) {
			if (!alphabet[matrix[r][c]]) {
				alphabet[matrix[r][c]] = 1;
				dfs(r, c, cnt + 1);
				alphabet[matrix[r][c]] = 0;
			}
		}
	}
}

int main(void) {
	cin >> R >> C;
	string s;

	for (int i = 0; i < R; i++) {
		cin >> s;
		for (int k = 0; k < C; k++) {
			matrix[i][k] = s[k] - 'A';
		}
	}

	// A = 65
	// 1��1��.������
	alphabet[matrix[0][0]] = 1;
	dfs(0, 0, 1);  // ī��Ʈ�� 1���� ����
	cout << max_cnt;
}
*/




/*
// 2583��
#include<iostream>
#include<vector>
#include<algorithm>
#define MAX 101
using namespace std;
typedef struct{
	int lx;
	int ly;
	int rx;
	int ry;
}pos;

vector<pos>rectangle;
int matrix[MAX][MAX];
int N, M, K;
int visited[MAX][MAX];
int area;

int dfs(int x, int y) {
	if (x < 0 || x >= M || y < 0 || y >= N) return 0;

	if (!visited[x][y] && !matrix[x][y]) {
		area++;
		visited[x][y] = 1;

		dfs(x - 1, y);
		dfs(x + 1, y);
		dfs(x, y - 1);
		dfs(x, y + 1);

		return area;
	}
	else return 0;
}

int main(void) {
	cin >> M >> N >> K;
	pos p;
	for (int i = 0; i < K; i++) {
		cin >> p.lx >> p.ly >> p.rx >> p.ry;
		rectangle.push_back(p);
	}

	for (int i = 0; i < rectangle.size(); i++) {
		p = rectangle[i];
		for (int x = p.lx; x < p.rx; x++) {
			for (int y = p.ly; y < p.ry; y++) {
				matrix[M-1-y][x] = 1;
			}
		}
	}

	int cnt = 0;
	int a;
	vector<int> result;
	for (int i = 0; i < M; i++) {
		for (int k = 0; k < N; k++) {
			area = 0;
			a = dfs(i, k);
			if (a != 0) {
				cnt++;
				result.push_back(a);
			}
		}
	}

	sort(result.begin(), result.end());
	cout << cnt << "\n";
	for (int i = 0; i < result.size(); i++)
		cout << result[i] << " ";
}
*/




/*
// 2644��
#include<iostream>
#define MAX 101
using namespace std;

int matrix[MAX][MAX];
int N;
int a, b;
int result;
int visited[MAX];

void dfs(int v, int cnt) {
	visited[v] = 1;
	for (int i = 1; i <= N; i++) {
		if (matrix[v][i] && !visited[i]) {
			if (i == b) result = cnt+1;
			else dfs(i, cnt + 1);
		}
	}
}
int main(void) {
	cin >> N;

	cin >> a >> b;   // �̼� ����ؾ� �ϴ� �� �� ��ȣ

	int x, y;
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		// �����
		matrix[x][y] = 1;
		matrix[y][x] = 1;
	}
	
	dfs(a, 0);
	if (!result) cout << -1;
	else cout << result;
}
*/


/*
// 1520��
#include<iostream>
#define MAX 501
using namespace std;

int M, N;
int matrix[MAX][MAX];
int dp[MAX][MAX];

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0,0, -1, 1 };

int dfs(int x, int y) {
	if (x == M - 1 && y == N - 1) { return 1; }  // ���������� ��μ� +1 �� �ϱ� ���ؼ� 1 ����
	if (dp[x][y] != -1) return dp[x][y];  // �ѹ� ������ ���� ������ �׳� �� �� �״�� ����


	dp[x][y] = 0;  // �ѹ� �湮������ �ϴ� 0���� ���� (-1�� ����)  // ��ΰ� ������ �������� �ؿ� for���� �������� �ƴ� ����. �ϴ� 0
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if(nx >= 0 && nx < M && ny >= 0 && ny < N){
			if (matrix[nx][ny] < matrix[x][y]) dp[x][y] += dfs(nx, ny);
		}
	}

	return dp[x][y];
}

int main(void) {
	cin >> M >> N;

	for (int i = 0; i < M; i++) {
		for (int k = 0; k < N; k++) {
			cin >> matrix[i][k];
			dp[i][k] = -1;
		}
	}
	cout << dfs(0, 0);
}
*/




// 1707��
#include<iostream>
#include<vector>
#define MAX 20001
using namespace std;

int matrix[MAX][MAX];
int visited[MAX];
int V, E, K;
int cnt;

void dfs(int x) {
	visited[x] = 1;

	for (int i = 1; i <= V; i++) {
		if (!visited[i] && matrix[x][i]) dfs(i);
	}
}

void init() {
	cnt = 0;
	for (int i = 0; i < MAX; i++) {
		visited[i] = 0;
		for (int k = 0; k < MAX; k++) {
			matrix[i][k] = 0;
		}
	}
}
int main(void) {
	cin >> K;
	vector<int>result;

	int a, b;
	for (int k = 0; k < K; k++) {
		cin >> V >> E;
		for (int i = 0; i < E; i++) {
			cin >> a >> b;
			matrix[a][b] = 1;
			matrix[b][a] = 1;
		}

		for (int i = 1; i <= V; i++) {
			if (!visited[i]) { dfs(i); cnt++; }
		}
		result.push_back(cnt);
		init();
	}

	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << endl;
		if (result[i] == 2) cout << "YES";
		else cout << "NO";
		cout << "\n";
	}


}