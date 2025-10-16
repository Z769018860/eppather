#include<queue>
#include<cstdio>
#include<bitset>
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

const int N = 1e6+8;
bitset<N> f, g;
int n;

int main(){
	f[0] = 1; read(n); int l, r;
	for (int i = 1;i<=n;i++){
		read(l), read(r); g = 0;
		for (int j = l;j<=r;j++) g |= (f<<(j*j));
		f = g;
	}
	printf("%d\n", f.count());
	return 0;
}
