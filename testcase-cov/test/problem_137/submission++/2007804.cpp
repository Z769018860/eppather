#pragma GCC optimize(3)
#pragma GCC optimize(2)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<deque>
#include<stack>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>
#define YES puts("YES")
#define Yes puts("Yes")
#define NO puts("NO")
#define No puts("No")
#define b_i __int128
#define ll long long
#define ull unsigned long long
#define x first
#define y second
#define pr pair
#define dl double
#define pll pr<ll, ll>
#define pii pr<int, int>
#define pdd pr<dl, dl>
#define ld long dl
#define vc vector
#define vci vc<int>
#define vcl vc<ll>
#define vcd vc<dl>
#define vcs vc<string>
#define vcp vc<pii >
#define ps push
#define pp pop
#define frt front
#define bck back
#define psf push_front
#define psb push_back
#define ppb pop_back
#define ppf pop_front
#define bgn begin
using namespace std;
const ll md = 998244353;
const ll mod = 1e9 + 7;
const dl esp = 1e-12;
const int inf = 2e9;
const ll INF = 2e18;
inline int read(){
	char c = getchar();
	int ans = 0, cnt = 1;
	while(c < '0' || c > '9'){
		if(c == '-') cnt = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		ans *= 10;
		ans += (c - '0');
		c = getchar();
	}
	return ans * cnt;
}
inline void write(int x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
int n, m, f[1000005][25], p[1000005], c[1000005], tot, num, dfn[1000005], d[1000005], lg2[1000005], A, B, C, P, q, ans;
pair<int, pii> e[1000005];
vci g[1000005];
int find(int x){
	if(x == p[x]) return x;
	return p[x] = find(p[x]);
}
void kru() {
    for(int i = 1; i <= n; i++) p[i] = i;
    tot = n;
    for(int i = 1; i <= m; i++){
        int u = find(e[i].y.x), v = find(e[i].y.y), w = e[i].x;
        if(u == v) continue;
        c[++tot] = w;
        g[tot].psb(u);
        g[tot].psb(v);
        p[u] = p[v] = p[tot] = tot;
    }
}
void dfs(int u, int ft, int dt){
    dfn[u] = ++num;
    d[u] = d[ft] + 1;
    f[num][0] = u;
    for(int i = 0; i < g[u].size(); i++){
    	int v = g[u][i];
        dfs(v, u, dt + 1);
        f[++num][0] = u;
    }
}
void ST(){
    for(int i = 2; i <= num; i++)  lg2[i] = lg2[i >> 1] + 1;
    for(int i = 1; i <= 20; i++)
        for(int j = 1; j + (1 << i) - 1 <= num; j++) {
            int k = j + (1 << (i - 1));
            if(d[f[j][i - 1]] < d[f[k][i - 1]]) f[j][i] = f[j][i - 1];
            else f[j][i] = f[k][i - 1];
        }
}
int get(){
	return A = (A * B + C) % P;
}
int lca(int x, int y) {
    x = dfn[x];
    y = dfn[y];
    if(x > y) swap(x, y);
    int k = lg2[y - x + 1];
    if(d[f[x][k]] < d[f[y - (1 << k) + 1][k]]) return f[x][k];
	else return f[y - (1 << k) + 1][k];
}
signed main(){
	
    
    
    
    
	n = read(), m = read();
	for(int i = 1; i <= m; i++) e[i].y.x = read(), e[i].y.y = read(), e[i].x = read();
	sort(e + 1, e + m + 1);
	kru();
    dfs(tot, 0, 0);
    ST();
	q = read(), A = read(), B = read(), C = read(), P = read();
    while(q--) {
        int u = get() % n + 1, v = get() % n + 1;
        ans += c[lca(u, v)];
		ans %= mod;
    }
    write(ans);
	return 0;
}