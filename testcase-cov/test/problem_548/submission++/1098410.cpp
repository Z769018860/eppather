#include<bits/stdc++.h>
#define PB emplace_back
#define MP make_pair
#define fi first
#define se second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL; 
typedef pair<LL, int> pii;
const int N = 500003, mod = 232792561, G = 71;
template<typename T>
void read(T &x){
	int ch = getchar(); x = 0; bool f = false;
	for(;ch < '0' || ch > '9';ch = getchar()) f |= ch == '-';
	for(;ch >= '0' && ch <= '9';ch = getchar()) x = x * 10 + ch - '0';
	if(f) x = -x;
} template<typename T>
bool chmax(T &a, const T &b){if(a < b) return a = b, 1; return 0;}
template<typename T>
bool chmin(T &a, const T &b){if(a > b) return a = b, 1; return 0;}
int ksm(int a, int b){
	int res = 1;
	for(;b;b >>= 1, a = (LL)a * a % mod)
		if(b & 1) res = (LL)res * a % mod;
	return res;
} int n, m, len, tot, A[22][22], a[N], c[22], x[22], v[22], S[22][22], T[22][22]; LL k; 
bool check(int p){
	for(int i = 0;i <= p;++ i)
		if(A[i][p] <= p && (LL)x[i] * x[p] % mod != x[A[i][p]]) return false;
	for(int i = 0;i < p;++ i)
		for(int j = i;j < p;++ j)
			if(A[i][j] == p && (LL)x[i] * x[j] % mod != x[p]) return false;
	return true; 
} void dfs(int d){
	if(tot == m) return;
	if(d == m){
		bool flg = false;
		for(int i = 0;i < m;++ i) flg |= x[i];
		if(!flg) return;
		for(int i = 0;i < m;++ i) S[tot][i] = x[i]; ++ tot;
		return;
	} x[d] = 0; if(check(d)) dfs(d+1); x[d] = 1;
	for(int i = 0;i < c[d];++ i, x[d] = (LL)x[d] * v[d] % mod)
		if(check(d)) dfs(d+1);
}
void DFT(int *a, int(*S)[22]){
	static LL b[22];
	for(int mid = 1;mid < len;mid *= m)
		for(int i = 0;i < len;i += mid * m)
			for(int j = 0;j < mid;++ j){
				memset(b, 0, sizeof b);
				for(int p1 = 0;p1 < m;++ p1)
					for(int p2 = 0;p2 < m;++ p2)
						b[p1] += (LL)S[p1][p2] * a[i+j+p2*mid];
				for(int p = 0;p < m;++ p) a[i+j+p*mid] = b[p] % mod;
			}
} void calcinv(int (*S)[22], int (*T)[22]){
	for(int i = 0;i < m;++ i) T[i][i] = 1;
	for(int i = 0;i < m;++ i){
		if(!S[i][i]){ int p = i;
			for(int j = i+1;j < m;++ j)
				if(S[j][i]){p = j; break;}
			assert(p != i); swap(S[i], S[p]); swap(T[i], T[p]);
		} int inv = ksm(S[i][i], mod-2);
		for(int j = 0;j < m;++ j){
			S[i][j] = (LL)S[i][j] * inv % mod;
			T[i][j] = (LL)T[i][j] * inv % mod;
		} for(int j = 0;j < m;++ j) if(j != i){
			LL tmp = mod - S[j][i];
			for(int k = 0;k < m;++ k){
				S[j][k] = (S[j][k] + tmp * S[i][k]) % mod;
				T[j][k] = (T[j][k] + tmp * T[i][k]) % mod;
			}
		}
	}
}
int main(){
	read(n); read(m); read(k);
	len = ksm(m, n); k = (k + 1) % (mod - 1);
	for(int i = 0;i < m;++ i)
		for(int j = 0;j < m;++ j)
			read(A[i][j]);
	for(int i = 0;i < len;++ i) read(a[i]);
	for(int i = 0;i < m;++ i){
		c[i] = 1; for(int x = A[i][i];x != i;x = A[x][i]) ++ c[i];
		v[i] = ksm(G, (mod - 1) / c[i]);
	} dfs(0);
	DFT(a, S); for(int i = 0;i < len;++ i) a[i] = ksm(a[i], k);
	calcinv(S, T); DFT(a, T);
	for(int i = 0;i < len;++ i) printf("%d\n", a[i]);
}