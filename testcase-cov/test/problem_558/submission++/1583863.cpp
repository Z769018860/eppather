#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef long long LL;
const int N = 5e5 + 5, inf = 1e9;
int read(){
	int x = 0, w = 1; char ch = 0;
	while(ch < '0' || ch > '9'){
		ch = getchar();
		if(ch == '-') w = -1;
	}
	while(ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return x * w;
}
int n, m, k;
int ch[N][2], fa[N]; 
bool rev[N];
int ok[N], cnt[N], icnt[N], val[N];
LL lans[N], rans[N], sum[N], ians[N];
bool isroot(int x){
	return (ch[fa[x]][0] != x) && (ch[fa[x]][1] != x);
}
void pushup(int x){
	if(!x) return;
	sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + val[x];
	cnt[x] = cnt[ch[x][0]] + cnt[ch[x][1]] + icnt[x] + ok[x];
	lans[x] = lans[ch[x][0]] + lans[ch[x][1]] + ians[x] + (sum[ch[x][0]] + val[x]) * (cnt[ch[x][1]] + icnt[x] + ok[x]);
	rans[x] = rans[ch[x][1]] + rans[ch[x][0]] + ians[x] + (sum[ch[x][1]] + val[x]) * (cnt[ch[x][0]] + icnt[x] + ok[x]);
}
void reverse(int x){
	rev[x] ^= 1, swap(lans[x], rans[x]), swap(ch[x][0], ch[x][1]);
}
void pushdown(int x){
	if(!rev[x]) return;
	if(ch[x][0]) reverse(ch[x][0]);
	if(ch[x][1]) reverse(ch[x][1]);
	rev[x] = 0;
}
void rotate(int x){
	int y = fa[x], z = fa[y];
	if(!isroot(y)) ch[z][ch[z][1] == y] = x;
	int r = ch[y][0] == x, l = r ^ 1;
	fa[x] = z, fa[y] = x, fa[ch[x][r]] = y;
	ch[y][l] = ch[x][r], ch[x][r] = y;
	pushup(y), pushup(x);
}
int stk[N], top;
void splay(int x){
	int t = x;
	for(;;){
		stk[++top] = t; if(isroot(t)) break; t = fa[t];
	}
	while(top) pushdown(stk[top--]);
	while(!isroot(x)){
		int y = fa[x], z = fa[y];
		if(!isroot(y)){
			if((ch[z][1] == y) == (ch[y][1] == x)) rotate(y);
			else rotate(x);
		}
		rotate(x);
	}
	pushup(x);
}
void access(int x){
	for(int t = 0; x; x = fa[x]){
		splay(x), ians[x] += lans[ch[x][1]] - lans[t], icnt[x] += cnt[ch[x][1]] - cnt[t], ch[x][1] = t, pushup(x), t = x;
	}
}
void makeroot(int x){
	access(x), splay(x), reverse(x);
}
void split(int x, int y){
	makeroot(x), access(y), splay(y);
}
void link(int x,int y){
	makeroot(x);
	makeroot(y);
	fa[x] = y;
	ians[y] += lans[x], icnt[y] += cnt[x];
	pushup(y);
}
void cut(int x, int y){
	split(x, y);
	fa[x] = ch[y][0] = 0;
	pushup(y);
}
unordered_map <LL, int> ID;
struct edge{
	int u, v;
}e[N];
char op[2];
int main(){
	n = read(), m = read(), k = read();
	int ecnt = n;
	for(int i = 1, u, v, w; i <= m; i++){
		u = read(), v = read(), w = read();
		if(u > v) swap(u, v);
		int id = ++ecnt;
		e[id].u = u, e[id].v = v;
		val[id] = sum[id] = w;
		ID[(LL)u * (n + 1) + v] = id;
		link(u, id), link(id, v);
	}
	for(int i = 1, u, v, w; i <= k; i++){
		scanf("%s", op);
		if(op[0] == 'L'){
			u = read(), v = read(), w = read();
			if(u > v) swap(u, v);
			int id = ++ecnt;
			e[id].u = u, e[id].v = v;
			val[id] = sum[id] = w;
			ID[(LL)u * (n + 1) + v] = id;
			link(u, id), link(id, v);
		}
		else if(op[0] == 'C'){
			u = read(), v = read();
			if(u > v) swap(u, v);
			int id = ID[(LL)u * (n + 1) + v];
			cut(e[id].u, id), cut(id, e[id].v);
		}
		else if(op[0] == 'F') u = read(), split(u, u), ok[u] ^= 1, pushup(u);
		else u = read(), makeroot(u), splay(u), printf("%lld\n", lans[u]);
	}
	return 0;
}