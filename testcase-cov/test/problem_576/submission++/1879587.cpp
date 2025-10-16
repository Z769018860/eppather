#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;
namespace Faster {


inline int read() {
    int num = 0, sgn = 1;
    char ch = getchar();
    for (; ch < 48 || ch > 57; ch = getchar())
        if (ch == '-')
            sgn = -1;
    for (; ch >= 48 && ch <= 57; ch = getchar()) num = (num << 3) + (num << 1) + (ch & 15);
    return sgn * num;
}
inline void write(int num) {
    static int sta[39], top = 0;
    if (num < 0)
        putchar('-'), num *= -1;
    do
        sta[++top] = num % 10, num /= 10;
    while (num);
    while (top) putchar(sta[top--] | 48);
    return;
}
} using namespace Faster;
const int N = 1e5 + 9;
int n, q;
struct segtree {
#define ls p << 1
#define rs p << 1 | 1
	int g[N << 2];
	void build(int p, int l, int r) {
		if (l == r) return g[p] = read(), void();
		int mid = l + r >> 1; build(ls, l, mid), build(rs, mid + 1, r); g[p] = __gcd(g[ls], g[rs]);
	}
	void update(int p, int l, int r, int pos) {
		if (l == r) return g[p] = read(), void();
		int mid = l + r >> 1; pos <= mid ? update(ls, l, mid, pos) : update(rs, mid + 1, r, pos); g[p] = __gcd(g[ls], g[rs]);
	}
	int find(int p, int l, int r, int a, int b) {
		if (l == r) return l;
		int aa = __gcd(a, g[ls]), bb = __gcd(b, g[rs]), mid = l + r >> 1;
		return aa <= bb ? find(ls, l, mid, a, bb) : find(rs, mid + 1, r, aa, b);
	}
	int get_pre(int p, int l, int r, int pos, int gg) {
		if (l == r) return __gcd(gg, g[p]);
		int mid = l + r >> 1, pre = __gcd(gg, g[rs]);
		if (pos <= mid) return get_pre(ls, l, mid, pos, pre);
		else if (g[ls] % pre == 0) return (mid - l + 1) * pre + get_pre(rs, mid + 1, r, pos, gg);
		return get_pre(ls, l, mid, pos, pre) + get_pre(rs, mid + 1, r, pos, gg);
	}
	int get_suf(int p, int l, int r, int pos, int gg) {
		if (l == r) return __gcd(gg, g[p]);
		int mid = l + r >> 1, suf = __gcd(gg, g[ls]);
		if (pos > mid) return get_suf(rs, mid + 1, r, pos, suf);
		else if (g[rs] % suf == 0) return (r - mid) * suf + get_suf(ls, l, mid, pos, gg);
		return get_suf(ls, l, mid, pos, gg) + get_suf(rs, mid + 1, r, pos, suf);
	}
} tr;
signed main() {
	n = read(), q = read();
	tr.build(1, 1, n);
	while (q--) {
		tr.update(1, 1, n, read());
		int pos = tr.find(1, 1, n, 0, 0);
		printf("%lld\n", tr.get_pre(1, 1, n, pos, 0) + tr.get_suf(1, 1, n, pos, 0) - tr.g[1]);
	}
    return 0;
}
