#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define pb push_back

using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

template<typename T> inline void read(T &x){
	x = 0;
	bool F = 0;
	char c = getchar();
	for (;!isdigit(c);c = getchar()) if (c == '-') F = 1;
	for (;isdigit(c);c = getchar()) x = x*10+(c^48);
	if (F) x = -x;
}

template<typename T> inline void checkmax(T &a, const T &b){if (a<b) a = b;}

template<typename T> inline void checkmin(T &a, const T &b){if (a>b) a = b;}

const int N = 1e4+5;
int sum[N], ans[N];
int n, m;

int main(){
	read(n), read(m); for (int i = 1;i<=n;i++) read(sum[i]), sum[i] += sum[i-1];
	for (int i = 0;i<=n;i++){
		ans[i] = -2e9;
		for (int j = i;j<=n;j++) checkmax(ans[i], sum[j]-sum[j-i]);
	}
	for (int i = n-1;i>=0;i--) checkmax(ans[i], ans[i+1]); int x;
	while (m--) read(x), printf("%d\n", ans[x]);
	return 0;
}
