#include<iostream>
#include<cstdio>
#include<vector>
#define int long long
#define maxn 3000005
#define __USE_KAHAN
#define fopen(x) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout);

using namespace std;

int n, m, q, mod[maxn], f[maxn], h[maxn], sz[maxn];
int op, u, v, w, b, c;
vector<int> g[maxn];

int gcd(int x, int y) {
	return y == 0 ? x : gcd(y, x % y);
}

int find(int x) {
	return x == f[x] ? x : find(f[x]);
}

void modify(int r, int w) {
	h[r] += w;
	h[r] %= m;
	for(int j : g[r]) {
		modify(j, w);
	}
}

void t(int x, int y, int w) {
	int fx = find(x), fy = find(y);
	if(sz[fx] > sz[fy]) swap(x, y), swap(fx, fy);
	int hx = h[x], hy = h[y];
	
	mod[fy] = gcd(mod[fy], gcd(mod[fx], w * 2));
	
	sz[fy] += sz[fx];
	g[fy].push_back(fx);
	modify(fx, (h[y] - h[x] + w) % m);
	f[fx] = fy;
	
	
	
}

struct ret {
    int r, p, q;
};

ret exgcd(long long p, long long q) {
    if(q == 0) {
        return (ret){p, 1, 0};
    }
    ret kkk = exgcd(q, p % q);
    return (ret){kkk.r, kkk.q, kkk.p - (p / q) * kkk.q};
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin >> n >> m >> q;
	for(int i = 1; i <= n; i++) {
		f[i] = i, mod[i] = m, h[i] = 0;
		sz[i] = 1;
	}
	while(q--) {
		cin >> op;
		if(op == 1) {
			cin >> u >> v >> w;
			int hu = h[u], hv = h[v], fu = find(u), fv = find(v);
			if(fu != fv) {
				t(u, v, w);
			}
			else {
				int q1 = (h[u] + h[v] + w) % mod[fu], q2 = w * 2 % mod[fu];
				
				mod[fu] = gcd(mod[fu], gcd(q1, q2));
				
			}
		}
		else {
			cin >> u >> v >> w >> b >> c;
			if(find(u) != find(v)) {
				cout << "0\n";
				continue;
			}
			int fu = find(u);
			int cnt = 0;
			int uvm = (h[u] + h[v]) % mod[fu];
			
			
			
		
			int r = (uvm - w % mod[fu] + mod[fu]) % mod[fu];
			ret k = exgcd(b, mod[fu]);
			
			if(r % k.r != 0) { 
				cout << "0\n";
				continue;
			}
			k.p *= r / k.r;
			k.p %= mod[fu] / k.r;
			k.p += mod[fu] / k.r;
			k.p %= mod[fu] / k.r;
			int cn =  (c - (k.p) - 1) / (mod[fu] / k.r) + 1;
			if(k.p >= c) cn = 0;
			cout << cn << '\n';
		}
	}
} 