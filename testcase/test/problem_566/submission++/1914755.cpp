#include <bits/stdc++.h>

#define For(i, l, r) for(register int i = (l), i##end = (int)(r); i <= i##end; ++i)
#define Fordown(i, r, l) for(register int i = (r), i##end = (int)(l); i >= i##end; --i)
#define Set(a, v) memset(a, v, sizeof(a))
#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

typedef long long ll;

inline bool chkmin(int &a, int b) {return b < a ? a = b, 1 : 0;}
inline bool chkmax(int &a, int b) {return b > a ? a = b, 1 : 0;}

inline int read() {
    int x = 0, fh = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') fh = -1;
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x * fh;
}

void File() {
#ifdef zjp_shadow
	freopen ("566.in", "r", stdin);
	freopen ("566.out", "w", stdout);
#endif
}

const int N = 2e5 + 1e3, M = 5e5 + 1e3;

int n, m;

namespace Union_Set {

	int fa[N], Size[N];

	void Init(int maxn) { For (i, 1, maxn) fa[i] = i, Size[i] = 0; }

	int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

	inline bool Union(int x, int y) {
		int rtx = find(x), rty = find(y);
		if (rtx == rty) return false;
		if (Size[rtx] < Size[rty]) swap(rtx, rty);
		Size[rtx] += Size[rty]; fa[rty] = rtx; return true;
	}

}

struct Edge {

	int u, v, w;

	inline bool operator < (const Edge &rhs) const { return w > rhs.w; }

} lt[M];

ll ans, res; int use, need;
void Work(int lim) {
	Union_Set :: Init(n); res = use = 0;
	for (register int L = 1, R = m, cur = 0; L <= R; ) {
		Edge add; register bool choose = false;
		if (lt[L].w >= lim - lt[R].w) add = lt[L ++];
		else add = lt[R --], choose = true, add.w = lim - add.w;

		if (Union_Set :: Union(add.u, add.v)) {
			res += add.w; if (choose) ++ use;
			if (++ cur == need << 1) break;
		}
	}
	res -= 1ll * lim * need;
}

int main () {

	File();

	n = read(); m = read(); need = (n - 1) >> 1; if (!need) return puts("0"), 0;
	For (i, 1, m)
		lt[i] = (Edge) {read(), read(), read()};
	sort(lt + 1, lt + m + 1);

	int l = 0, r = min(lt[1].w * 2 + 1, (int) 1e9);
	while (l <= r) {
		int mid = (l + r) >> 1; Work(mid);
		if (use == need) return printf ("%lld\n", res), 0;
		if (use < need) l = mid + 1, ans = res; else r = mid - 1;
	}
	printf ("%lld\n", ans);

    return 0;
}