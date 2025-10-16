#include<bits/stdc++.h> 
#define L(i, j, k) for(int i = (j); i <= (k); ++i) 
#define R(i, j, k) for(int i = (j); i >= (k); --i) 
#define ll long long 
#define vi vector < int > 
#define sz(a) ((int) (a).size()) 
#define me(a, x) memset(a, x, sizeof(a)) 
using namespace std; 
const int N = 55;
int n, m; 
int a[N][N][N], ia[N][N][N];
int vis[N][N]; 
vector < vi > good[N];
bool check(int cur, vi p) {
	if(cur > n) 
		return false;
	if(!vis[cur][p[cur]]) 
		return true;
	int *t = ia[cur][p[cur]];
	L(i, cur, n) 
		p[i] = t[p[i]];
	return check(cur + 1, p);
}
inline void insert(int i, vi p) {
	if(!check(i, p)) return ;
	good[i].emplace_back(p);
	vi que(n + 1);
	int ql = 1, qr = 0; 
	L(j, i, n) 
		if(vis[i][j]) {
			vi np(n + 1);
			L(k, 1, n) 
				np[k] = p[a[i][j][k]];
			if(!vis[i][p[j]]) {
				L(k, 1, n) 
					a[i][p[j]][k] = np[k], 
					ia[i][p[j]][np[k]] = k;
				que[++qr] = p[j], vis[i][p[j]] = true;
			} else {
				vi rp(n + 1);
				L(k, 1, n) 
					rp[k] = ia[i][p[j]][np[k]]; 
				insert(i + 1, rp);
			}
		}
	while(ql <= qr) {
		int j = que[ql];
		++ql;
		for(auto p : good[i]) {
			vi np(n + 1);
			L(k, 1, n) 
				np[k] = p[a[i][j][k]];
			if(!vis[i][p[j]]) {
				L(k, 1, n) 
					a[i][p[j]][k] = np[k], ia[i][p[j]][np[k]] = k;
				que[++qr] = p[j], vis[i][p[j]] = true;
			} else {
				vi rp(n + 1);
				L(k, 1, n) 
					rp[k] = ia[i][p[j]][np[k]]; 
				insert(i + 1, rp);
			}
		}
	}
}
int fen[N * N], len; 
int main() {
	ios :: sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	L(i, 1, n) {
		vis[i][i] = 1;
		L(j, 1, n) 
			a[i][i][j] = ia[i][i][j] = j;
	}
	while(m--) {
		vi p(n + 1);
		L(i, 1, n) 
			cin >> p[i];
		insert(1, p);
	}
	len = 1, fen[1] = 1;
	L(i, 1, n) {
		int bot = 0;
		L(j, i, n) {
			bot += vis[i][j];
		}
		L(k, 1, len) {
			fen[k] *= bot;
		}
		L(k, 1, len) {
			fen[k + 1] += fen[k] / 10, fen[k] %= 10;
		}
		while(fen[len + 1]) 
			++len, fen[len + 1] += fen[len] / 10, fen[len] %= 10;
	}
	R(i, len, 1) cout << fen[i];
	return 0;
}