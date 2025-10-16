#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<string>
#include<bitset>
#include<cmath>
#include<queue>
#include<stack>
#include<set>
#include<map>

#define int long long
#define ls p << 1
#define rs p << 1 | 1

using namespace std;

inline int read() {
	char c = 0;
	int r = 0, f = 1;
	while(!isdigit(c)) if((c = getchar()) == '-') f = -f;
	while(isdigit(c)) r = (r << 3) + (r << 1) + (c ^ 48), c = getchar();
	return r * f;
}

const int N = 1e5 + 5;

inline int gcd(int a, int b) {
	if(a && b) return a < b ? gcd(b % a, a) : gcd(a % b, b);
	return a | b;
}

int a[N];

struct segtree{
	int sum[N << 2];
	
	inline void pushup(int p) {
		sum[p] = gcd(sum[ls], sum[rs]);
	}
	
	void build(int p, int l, int r) {
		if(l == r) {
			sum[p] = a[l];
			return;
		}
		int mid = l + r >> 1;
		build(ls, l, mid), build(rs, mid + 1, r);
		pushup(p);
	}
	
	void modify(int p, int l, int r, int x, int c) {
		if(l == r) {
			sum[p] = c;
			return;
		}
		int mid = l + r >> 1;
		if(x <= mid) modify(ls, l, mid, x, c);
		else modify(rs, mid + 1, r, x, c);
		pushup(p);
	}
	
	int find(int p, int l, int r, int gl = 0, int gr = 0) {
		if(l == r) return l;
		int mid = l + r >> 1, tmpl = gcd(gl, sum[ls]), tmpr = gcd(sum[rs], gr);
		if(tmpl <= tmpr) return find(ls, l, mid, gl, tmpr);
		return find(rs, mid + 1, r, tmpl, gr);
	}
	
	int queryl(int p, int l, int r, int x, int gr = 0) {
		if(l == r) return gcd(sum[p], gr);
		int mid = l + r >> 1, tmpr = gcd(sum[rs], gr), tmpl = gcd(sum[ls], tmpr);
		if(x <= mid) return queryl(ls, l, mid, x, tmpr);
		int res = queryl(rs, mid + 1, r, x, gr);
		if(tmpl == tmpr) return (mid - l + 1) * tmpl + res;
		return queryl(ls, l, mid, x, tmpr) + res;
	}
	
	int queryr(int p, int l, int r, int x, int gl = 0) {
		if(l == r) return gcd(gl, sum[p]);
		int mid = l + r >> 1, tmpl = gcd(gl, sum[ls]), tmpr = gcd(tmpl, sum[rs]);
		if(mid < x) return queryr(rs, mid + 1, r, x, tmpl);
		int res = queryr(ls, l, mid, x, gl);
		if(tmpl == tmpr) return res + (r - mid) * tmpr;
		return res + queryr(rs, mid + 1, r, x, tmpl);
	}
}tr;

signed main() {
	int n = read(), Q = read();
	for(int i = 1;i <= n;i++) a[i] = read();
	tr.build(1, 1, n);
	while(Q--) {
		int p = read();
		tr.modify(1, 1, n, p, read());
		p = tr.find(1, 1, n);
		printf("%lld\n", tr.queryl(1, 1, n, p) + tr.queryr(1, 1, n, p) - tr.sum[1]);
	}
	return 0;
}