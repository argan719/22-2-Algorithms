
/*
// 2108번
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath> // 반올림
#define MAX 8001
using namespace std;

int main(void) {
	int n, i;
	int v;

	vector<int> mode;  // 최빈값 위한 벡터
	int cnt[MAX] = { 0, };    // -4000 -> 0 4000 -> 8000

	scanf("%d", &n);
	vector<int> arr;

	double sum = 0;
	int max = -4000;
	int cnt_max = 0;

	// 정수 입력받기
	for (i = 0; i < n; i++) {
		scanf("%d", &v);
		arr.push_back(v);
		sum += v;
		cnt[v + 4000]++;
		if (cnt_max < cnt[v + 4000]) cnt_max = cnt[v + 4000];  // 최빈 횟수(몇 번 나와야 최빈값이냐?)
		if (max < v) max = v;
	}
	sort(arr.begin(), arr.end());  // 정렬

	double aver = sum / n;  // 산술평균 구하기
	int range = *(arr.end() - 1) - *(arr.begin());   // 범위 구하기 

	// 최빈값 구하기
	for (i = 0; i <= max + 4000; i++) {  // 시간 단축을 위해 8000까지 돌지 않고 최댓값 구한다음 그 값까지만 돌도록
		if (cnt_max == cnt[i]) mode.push_back(i - 4000);
	}


	printf("%.0f\n", floor(aver + 0.5));  // 산술평균 출력
	printf("%d\n", arr[n / 2]);   // 중앙값 출력

	sort(mode.begin(), mode.end());  // 정렬
	// 최빈값 출력
	if (mode.size() == 1) printf("%d\n", *(mode.begin()));
	else printf("%d\n", mode.at(1));

	printf("%d\n", abs(range));    // 범위 출력
}

*/




/*
// 11049번
// 행렬 곱셈 순서 (Matrix Chain Order)
#include<iostream>
#define SIZE 501
#define MAX 2147483647  // (2^31 - 1) + 1
using namespace std;

// n = 5 라면,
//	0	*	*	*	정답
//		0	*	*	*
//			0	*	*
//				0	*
//					0

// field는 이런구조
// 정답 칸 값을 출력하면 됨 field[1][n] (field 인덱스 1부터 시작)
// field[1][n] 값이 내가 구하고자 하는 값임 = matrix chain order 최저비용

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

	for (l = 1; l < n; l++) {  // n=5라면 (0,0) (1,1)..(4,4) 라인을 제외하고 4번의 횡단이동 필요
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

	cout <<  field[1][n];   // 결과출력
}
*/




/*
// 11047번 - 동전 수, greedy 이용

#include<iostream>
using namespace std;

int main(void) {
	int n, k, i;
	int val;

	cin >> n;
	cin >> k;
	int *arr = (int*)malloc(sizeof(int)*n);  // n개만큼 배열생성
	// n개의 동전 가치 입력
	for (i = 0; i < n; i++) {
		cin >> arr[i];
	}

	int cnt = 0;
	i = n - 1;  // 가장 가치가 높은 동전부터 시작 - 배열의 맨 마지막 인덱스부터 시작
	while (k != 0) {
		cnt += k / arr[i];   // 나누기 한 몫을 count에 더해주고
		k = k % arr[i];     // k는 나누기 한 후 나머지 값으로 만들어줌
		i--;
		if (i < 0) break;
	}
	cout << cnt;   // 결과 출력 - 필요한 동전 개수의 최소값
}
*/



/*
// 12865번 - Knapsack 문제 DP이용

#include<iostream>
#define ROW 101
#define COLUMN 100001
using namespace std;

typedef struct p {
	int w;  // 물건의 무게
	int v;  // 물건의 가치
}Product;

int main(void) {
	int n, k;
	cin >> n >> k;

	Product p[ROW];  // 구조체 배열 생성
	int matrix[ROW][COLUMN];   // 2차원 배열 생성

	// N개의 물건에 대해 무게,가치 입력
	for (int i = 1; i <= n; i++) {
		cin >> p[i].w >> p[i].v;
	}

	// bottom-up과정. 행은 물건의 개수 (0~n) 열은 무게 (0~k)
	int tmp;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			if (i == 0 || j == 0) matrix[i][j] = 0;   // 0행과 0열은 0으로 채움
			else {
				if (p[i].w > j) matrix[i][j] = matrix[i - 1][j];   // 현재 담으려는 물건의 무게가 열 값보다 크다면 위쪽값 그대로 가져옴
				else {  // 삼항연산자 이용
					(p[i].v + matrix[i - 1][j - p[i].w] < matrix[i - 1][j]) ? tmp = matrix[i - 1][j] : tmp = p[i].v + matrix[i - 1][j - p[i].w];
					matrix[i][j] = tmp;
				}  // 그렇지 않은 경우, i번째 보석값 + p[ i - 1 ,w - i ]  or  p[i - 1, w]   둘 중 큰 값으로 선택한다.
			}  // i번째 보석값 + p [ i-1, w-i] 가 의미하는 건 i번째 보석값의 무게를 뺀 열의 i - 1행임.
		  // 즉, i 번째 보석을 넣을 자리를 제외하고 (그 무게만큼 뺀 상태에서) 최적인 애를 갖다 쓰는 거임. 거기다가 i번째 가치 더해 줌.
		}  // p[i-1, w] 는 바로 위에 칸에 해당함. '그 전꺼에서의 최적값'이 더 크다면 위에 있는 값 그대로 가져오는 거임.
	}
	cout << matrix[n][k];    // 행렬의 맨 오른쪽 밑에 값이 최종 결과이므로 그대로 출력하면 답이 된다.
}
*/






// 백준 21568번
// Extended Euclid Algorithm

// 해결 못함


/*
#include<iostream>
#include <stdio.h>
using namespace std;

void EE(int a, int b, int c) {
	int r1 = a, r2 = b, s1 = 1, s2 = 0, t1 = 0, t2 = 1;
	int r, s, t, q;

	while (r2) {
		q = r1 / r2;
		// gcd 계산
		r = r1 % r2;
		r1 = r2, r2 = r;

		// s 계산
		s = s1 - q * s2;
		s1 = s2, s2 = s;

		// t 계산
		t = t1 - q * t2;
		t1 = t2, t2 = t;

		//if (a*s1 + b * t1 == c)  cout << s1 << " " << t1;

	}
	s = s1; t = t1;
	printf("gcd(%d, %d) = %d, s = %d, t = %d \n", a, b, r1, s, t);

}

int main() {
	int a, b, c;
	// A, B, C 값 입력받기   Ax+By = C
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
	// A, B, C 값 입력받기   Ax+By = C
	cin >> a >> b >> c;
	EE(a, b, c);
}
*/



/*
// 2839번

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
// 1931번
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
// 1541번
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
// 2217번
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
// 1946번
#include<iostream>
#include<vector>
#define MAX 100001
using namespace std;

int score[MAX];  // 전역변수이므로 0으로 초기화 됨

int main(void) {
	ios::sync_with_stdio(false);

	int testcase;
	int n;
	int x, y;  // 1차점수, 2차점수
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
		// x값(1차성적)을 인덱스로 활용하면 정렬할 필요가 없다!
		max = score[1];
		t++;
		for (int i = 2; i <= n; i++) {
			if (max > score[i]) {
				max = score[i];
				t++;
			}
		}
		// 그리고 for문 2개 돌릴 필요가 없다! 
		// 1차에서 정렬한 순서대로 간다면 2차 점수가 무조건 더 높아야지만 (max보다 높아야지만) 뽑히는 거임
		cout << t << endl;  // 여기서 바로 찍어주면 되는 거였음. 
		// 예시 보고 잘못 이해함 - testcase마다 찍어주는 게 아니라 나중에 한꺼번에 출력해줘야 하는 건줄 알았음.
	}

}
*/



/*
// 1715번
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

// 16953번
#include<iostream>
using namespace std;

int main(void) {
	int a, b;
	cin >> a >> b;

	int n;
	
	int count = 0;
	while (a != b) {
		if (a > b) count = -2;
		else if (b % 10 == 1) {    // 10으로 나눈 나머지 = 맨 마지막 자릿수
			b = b / 10;
			count += 1;
		}
		else if (b % 2 == 0) {   // b가 2로 나눠떨어지는 경우
			b = b / 2;
			count += 1;
		}
	}
	cout << count + 1;
}


*/











/*
// 2023-07-05 시작

// 2839번-DP

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
	cin >> n;  // 전체 무게 입력받기

	d[3] = d[5] = 1;
	for (int i = 1; i <= n; i++) {    // i=6부터 돌릴라했는데 4입력시 -1 나와야 하는데 0나와서 걍 1부터 돌림.
		dp(i);
	}

	if (d[n] >= 5000) cout << -1;
	else cout << d[n];
}


*/



/*
// 1463번
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
// 1003번
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
// 11726번
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
// 1149번

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
// 2579번 - 이어서 하기
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
// 1439번

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

	// 자릿수까지 고려한 값을 arr[26] 배열에 넣어놓고
	for (int i = 0; i < word.size(); i++) {
		p = 1;
		for (int k = word[i].length()-1; 0<=k ; k--) {
			arr[word[i][k] - 65] += p;
			p = p * 10;
		}
	}
	// 그걸 sorting 해서
	sort(arr, arr + 26);
	
	p = 9;
	for (int i = 25; 0<=i; i--) {
		// 알파벳이 존재하면 (0이 아니면)
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
pair<int, int> info[MAX];  // 보석의 무게,가격
int bag[MAX];  // 가방의 무게(용량)

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	long long sum = 0;

	cin >> N >> K;

	// 보석의 무게, 가격
	for (int i = 0; i < N; i++) {
		cin >> info[i].first >> info[i].second;
	}
	// 가방에 담을 수 있는 최대 무게
	for (int i = 0; i < K; i++) {
		cin >> bag[i];
	}

	sort(info, info + N);  // 보석 무게 오름차순
	sort(bag, bag + K);  // 가방 용량 오름차순 - (디폴트가 pair first 기준 오름차순정렬)

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
// 1049번
#include<iostream>
#include<algorithm>
using namespace std;

int pack[51]; // 패키지(6개)가격
int one[51];  // 낱개 가격

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M;
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		cin >> pack[i] >> one[i];
	}

	sort(pack, pack + M);  // 오름차순 정렬- 패키지 가격 기준
	sort(one, one + M);  // 오름차순 정렬 - 낱개 가격 기준
	// 패키지 가격은 항상 낱개가격*6보다 작거나 같음. 클 수는 없다.
	// 즉 낱개 가격이 기준이 되서 정렬을 해야 하고
	// 낱개 가격이 가장 저렴한 곳 * N 이 싼지
	// 패키지 가격이 가장 저렴한 곳의 패키지 가격이 싼지 비교하면 되지 않을까?
	


	int result = 0;
	// 패키지 가격과 낱개*6개 가격 비교
	if (pack[0] >= one[0] * 6) {    // 낱개가 더 싸거나 가격이 똑같은 경우 - 근데 이럴 경우 거의 없음.
		result = one[0] * N;
	}
	else {  // 패키지가 더 싼 경우
		int n = N / 6;
		if (N % 6 > 0) { // 딱 6배수로 안 나눠떨어지는 경우
			result = min(pack[0], one[0] * (N % 6));   // 패키지를 하나 더 추가하는게 싼지, 낱개로 부족한 것만 더 사는게 싼지 비교
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
	if (N == 1) cout << arr[0];   // 입력받은 수가 한개일 경우
	else {
		while (i < N) {
			if (arr[i] > 0) break;
			if (arr[i] <= 0 && arr[i + 1] > 0) {  // 음수가 끝나는 지점(양수로 넘어가는 지점)
				sum += arr[i];
				i += 1;
			}
			else {  // 두개가 다 음수인경우 - 두 개를 묶어야 됨(곱하는게 가장 좋음)
				sum += arr[i] * arr[i + 1];
				i += 2;
			}
		}
		i = N - 1;   // 뒤에서부터 시작-왜냐 절댓값이 큰거끼리 곱해야 가장 커지기 때문. 가장 큰수부터 그 왼쪽꺼랑 곱해야 함.
		while (i >= 0) {
			if (arr[i - 1] == 1) {  // 1인 경우 그냥 1을 따로 더하는 게 나음(1은 묶으면 안됨)
				sum += arr[i]; 
				i -= 1;
				while (arr[i]) { // 정렬했기 때문에 1끼리 모여있을거임. 1끝날 때까지 1은 각각 더해야 됨.
					sum += arr[i];
					i -= 1;
				}
			}
			else if (arr[i - 1] > 0) {  //두개가 다 양수인경우 - 두 개를 묶어야 됨
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
// 11000번
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
	// 계속 맨 왼쪽 맨 위 값을 기준으로 A와 B가 다른지 탐색
	for (i = 0; i < N-2; i++) {
		for (k = 0; k < M - 2; k++) {  // 3x3이라서 M-3까지밖에 이동못함. - 커널로 전체행렬을 훑는다고 생각해봐
			if (A[i][k] != B[i][k]) {
				//if (N <= 2 || M <= 2) { cout << -1; break; }  	// 근데 N, M이 1,2인 경우는 change함수에서 3개까지 없으니까 범위 벗어날텐데 어캄? - 그래서 이 코드 추가
				// 근데 다른 사람 코드 보니까 이런 코드가 없음. 틀리는 이유가 이것 때문일 수도
				// 애초에 for문에서 N-2, M-2라서 N,M이 2보다 작거나 같다면 for문으로 들어올 수가 없음.
				change(i, k); cnt++;
			}
		}
	}

	bool flag = true;
	// 나머지 점 안 찍힌 부분들이 B랑 다른지 확인 가 아니라 전체 다 확인해야 하는 거임. 
	// 점 찍힌 부분들이 전부 B랑 일치한다는 보장이 없지
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

int chu[1001];  // 저울추 무게 저장

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
			// 이 부분 마의 구간
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
// 2437번
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
			if (chu[i] > n) break;   // 더해지는 수가 n 보다 커져버리면 종료. n이 안된거니까 - 이때 n값이 답.
			sum += chu[i];
			while (sum >= n) {  // 여태까지 합한 추 무게로 n을 들 수 있을 때까지 계속 반복 - n이 더 크면 그때 새로운 추 추가
				n++;
			}
		}
		// 만약 끝까지 다 됐다면 sum+1부터 측정이 안되는 거겠지
		if (i == N) cout << sum + 1;
		else cout << n;
	}
}

*/



/*
// 2847번
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
// 1700번 - 미완료
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;


int name[101];
int flow[101];
pair<int, int> multitab[101];  // MAX번째, 전기용품 이름
int check[101];

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int N, K;
	cin >> N >> K;

	int n;
	for (int i = 0; i < K; i++) {
		cin >> n;
		if (name[n] < i) name[n] = i;  // 각 전기용품의 MAX번째 저장  (순서는 0번째부터 시작)
		flow[i] = n;  // 순서 유지한채 저장 (0번이 첫번째가 되는거임)
	}

	int cnt = 0;
	int idx = 0;
	int max = 0;
	int k;
	int max_idx = 0;

	for(int i=0;i<K;i++) {
		if (idx < N) {
			multitab[idx++] = make_pair(name[flow[i]], flow[i]);  // MAX번째, 이름
		}
		else {
			if (check[flow[i]]) continue;   // 지금 꽂으려는게 이미 꽂혀 있다면 그냥 스킵
			else {
				max = 0;
				for (k = 0; k < N; k++) {
					if (multitab[k].first < i) {  // 앞으로 더 이상 안 나오는 애가 지금 꽂혀있다면 얘를 빼야함
						cout << multitab[k].second << " 이거 뽑고" << endl;
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
					cout << "MAX값: " << multitab[max_idx].second << endl;
					cout << multitab[max_idx].second << " 이거 뽑고" << endl;
					check[multitab[max_idx].second] = 0;
					multitab[max_idx].first = name[flow[i]];
					multitab[max_idx].second = flow[i];

				}
				cnt++;
			}
		}
		//cout << "현재 멀티탭 상황: " << "사이즈: " << multitab.size() << " top: " << multitab.top().first << " " << multitab.top().second << endl;
		check[flow[i]] = 1;
		cout << flow[i] << " 이거 꽂음" << endl;
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
		if (cnt == K) {  // K개만큼을 다 뺏다면 더 이상 pop X. 계속 push
			num.push(input[i]);
		}
		else if (num.top() < input[i]) { 
			while (num.top() < input[i]) {  // 지금 넣으려는 값보다 크거나 같은 값이(스택에서) 나올 때까지 계속 pop
				num.pop();
				cnt++;
				if (cnt == K) break;
				if (num.empty()) break;
			}
			num.push(input[i]);  // 현재 값 push
		}
		else num.push(input[i]); // 스택의 top보다 현재 넣으려는 값이 더 작거나 같다면 그냥 현재 넣으려는 값 push 
	}

	// 만약 숫자들이 내림차순으로 되어 있어서 위의 과정을 진행했지만 전체 N개에서 K개만큼 못 뺏다면 K개 뺄 때까지 계속 pop
	while (cnt < K) {
		num.pop();
		cnt++;
	}

	// 스택 거꾸로 출력
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
// 3109번
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
		int nx = x + dx[i];   // i-1(오른쪽대각선위)  i(오른쪽)  i+1(오른쪽대각선아래)
		int ny = y + dy[i];  // k+1

		if (nx >= 0 && ny >= 0 && nx < R && ny < C)
		{
			if (grid[nx][ny]  && !visit[nx][ny])  // 벽이 아니고 아직 방문 안했다면
			{
				dfs(nx, ny);   // 더 탐색
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
			if (c == 'x') grid[i][k] = 0;  // 벽
			else grid[i][k] = 1;  // 길
		}
	}

	for (int i = 0; i < R; i++) {
		flag = false;
		dfs(i, 0);   // 각 행의 첫 열을 보냄 (처음 열)
	}
	cout << cnt;
}
*/





/*
// 1783번 - 진행중
#include<iostream>
using namespace std;

int main(void) {
	int N, M;
	cin >> N >> M;

	int move = 0;   // 이동횟수
	int cnt = 1;  // 여행한 칸수

	if (M == 1) cout << 1;
	else if (M - 1 == 1) {  // 세로길이가 전체 2칸인 경우=오른쪽으로 1칸 이동만 가능한 경우
		if (N >= 3) cout << 2;
		else cout << 1;
	}
	else {
		while (move < 4) {
			if ((M - 1) % 2 != 0) {  // 2칸 이동 가능

			}
			else {

			}
		}

		// 4개 이동방법을 다 해야함. 안그럼안됨
		if (move >= 4) {
			
		}
	}
	

}
*/




/*
// 2212번
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
	sort(sensor, sensor + N);   // 오름차순

	// 센서 간의 거리 차이를 모두 계산해서 정렬해야함
	// 좌표값은 음수도 가능
	for (int i = 0; i < N - 1; i++) {
		dist[i] = abs(sensor[i] - sensor[i + 1]);
	}
	sort(dist, dist + N - 1, greater<int>());  // 센서 간 거리 내림차순

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

	int len = t.length() - s.length();   // T와 S 문자열 길이 차

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
// 1260번
#include<iostream>
#include<queue>
using namespace std;
typedef struct graph {
	int N;   // 정점개수
	int M;    // 간선개수
	int** matrix;       // 행렬
}Graph;
int *visited;

void GInit(Graph* pGraph, int numberOfVertex) {
	visited = (int*)malloc(sizeof(int) * numberOfVertex);
	pGraph->matrix = (int **)malloc(sizeof(int *) * numberOfVertex);   // 행 동적할당
	for (int i = 0; i < numberOfVertex; i++) {
		pGraph->matrix[i] = (int *)malloc(sizeof(int) * numberOfVertex);  // 열 동적할당
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
// 2606번
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
// 2667번
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
		cnt++;  // 단지 수 
		visited[x][y] = 1;

		dfs(x - 1, y);  // 좌
		dfs(x + 1, y);  // 우
		dfs(x, y - 1);  // 하
		dfs(x, y + 1);  // 상

	}
	return cnt;
}

int main(void) {
	cin >> N;
	string s;
	vector<int> house;

	// 2차원 배열에 0,1 숫자로 저장
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
// 1012번
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
// 11724번
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
// 10026번
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
// 4963번
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

		dfs(x - 1, y);  // 좌
		dfs(x + 1, y);  // 우
		dfs(x, y + 1); // 위
		dfs(x, y - 1); // 아래
		
		dfs(x - 1, y - 1);  // 왼쪽 위 대각선
		dfs(x - 1, y + 1);  // 오른쪽 위 대각선
		dfs(x + 1, y - 1); // 왼쪽 아래 대각선
		dfs(x + 1, y + 1); // 오른쪽 아래 대각선

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
// 2468번
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
// 11725번
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
// 1987번
#include<iostream>
#include<string>
using namespace std;

int matrix[21][21];
int R, C;
int alphabet[26];
int max_cnt;
int r, c;
// 상 하 좌 우
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
	// 1행1열.시작점
	alphabet[matrix[0][0]] = 1;
	dfs(0, 0, 1);  // 카운트는 1부터 시작
	cout << max_cnt;
}
*/




/*
// 2583번
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
// 2644번
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

	cin >> a >> b;   // 촌수 계산해야 하는 두 명 번호

	int x, y;
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		// 양방향
		matrix[x][y] = 1;
		matrix[y][x] = 1;
	}
	
	dfs(a, 0);
	if (!result) cout << -1;
	else cout << result;
}
*/


/*
// 1520번
#include<iostream>
#define MAX 501
using namespace std;

int M, N;
int matrix[MAX][MAX];
int dp[MAX][MAX];

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0,0, -1, 1 };

int dfs(int x, int y) {
	if (x == M - 1 && y == N - 1) { return 1; }  // 도착했으니 경로수 +1 을 하기 위해서 1 리턴
	if (dp[x][y] != -1) return dp[x][y];  // 한번 설정된 적이 있으면 그냥 그 값 그대로 리턴


	dp[x][y] = 0;  // 한번 방문했으니 일단 0으로 설정 (-1과 구분)  // 경로가 있을지 없을지는 밑에 for문을 돌려봐야 아는 거임. 일단 0
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




// 1707번
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