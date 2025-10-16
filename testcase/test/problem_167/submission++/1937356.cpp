#include <bits/stdc++.h>
using namespace std;
#define IC isdigit(c)
#define GC c=gch()
#define il __attribute__((always_inline))
il int gch() {
	static const int SZ = 1 << 22;
	static char buf[SZ] {}, *S = 0, *T = 0;
	return ((S == T) && (T = buf + fread(S = buf, 1, SZ, stdin))), (S == T ? EOF : *(S++));
}
il void rd(auto &x) { int GC; x = 0; bool f = 0;
	for (; !IC; GC) f |= c == '-';
	for (; IC; GC) x = x * 10 + c - 48;
	f ? (x = -x) : 0;
}
il void rd(auto &x, auto &...y) { rd(x); rd(y...); }
#define U(i,l,r) for(int i(l),END##i(r); i<=END##i; ++i)
#define D(i,l,r) for(int i(l),END##i(r); i>=END##i; --i)

const int N = 1000005;
using ll = long long;
const ll P = 998244353;
int n, p[N]; ll fac[N];


namespace BIT {
	int tr[N];
	void add(int p, int v) { for (; p < N; p += p & -p) tr[p] += v; }
	int query(int p) { int v = 0; for (; p; p ^= p & -p) v += tr[p]; return v; }
}

int main() {
	fac[0] = 1;
	U (i, 1, N - 1)
		fac[i] = fac[i - 1] * i % P;
	rd(n);
	U (i, 1, n) rd(p[i]);
	ll ans = 0;
	U (i, 1, n) {
		int v = p[i] - BIT::query(p[i]);
		(ans += (v - 1) * fac[n - i]) %= P;
		BIT::add(p[i], 1);
	}
	(++ans) %= P;
	cout << ans << endl;
}