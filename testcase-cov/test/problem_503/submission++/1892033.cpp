#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5,Inf = 5e7 + 5,M = 2e7 + 5;
int n,x[N],y[N],s[N],q,A[3 * N],cnt;
int op[3 * N],nx[3 * N],ny[3 * N];
int sum[M],ls[M],rs[M];
inline void Add(int &p,int l,int r,int x,int y,int d) {
	if (!p) p = ++ cnt;
	if (x <= l && r <= y) {
		sum[p] += d;
		return ;
	}
	int mid = l + r >> 1;
	if (x <= mid) Add(ls[p],l,mid,x,y,d);
	if (mid < y) Add(rs[p],mid + 1,r,x,y,d);
}
inline int que(int p,int l,int r,int x) {
	if (!p) return 0;
	if (l == r) return sum[p];
	int mid = l + r >> 1;
	if (x <= mid) return que(ls[p],l,mid,x) + sum[p];
	else return que(rs[p],mid + 1,r,x) + sum[p];
}
inline void solve(int a[],int aa[]) {
	s[0] = 1;
	for (int i = 1; i <= n; i ++) s[i] = s[i - 1] + a[i];
	int rt = 0,now = 1,del = 0,ans = 0;
	for (int i = 1; i < n; i ++) Add(rt,0,Inf << 1,min(s[i],s[i + 1]) + Inf,max(s[i],s[i + 1]) + Inf,1);
	for (int i = 0; i < n; i ++) if (1ll * s[i] * s[i + 1] < 0ll) ans ++;
	for (int i = 1; i <= q; i ++)
		if (op[i] == 1) {
			if (now == 1) continue;
			s[-- now] -= del;
			Add(rt,0,Inf << 1,min(s[now],s[now + 1]) + Inf,max(s[now],s[now + 1]) + Inf,1);
		} else if (op[i] == 2) {
			if (now == n) continue;
			Add(rt,0,Inf << 1,min(s[now],s[now + 1]) + Inf,max(s[now],s[now + 1]) + Inf,-1);
			s[now ++] += del;
		} else if (op[i] == 3) {
			ans -= que(rt,0,Inf << 1,Inf - del);
			if (1ll * s[now - 1] * (s[now] + del) < 0ll) ans --;
			del += aa[i] - a[now];
			a[now] = aa[i]; 
			ans += que(rt,0,Inf << 1,Inf - del);
			if (1ll * s[now - 1] * (s[now]  + del) < 0ll) ans ++;
		} else A[i] += ans;
}
int main() {
	scanf("%d",&n);
	for (int i = 1; i <= n; i ++) scanf("%d%d",&x[i],&y[i]);
	scanf("%d",&q);
	for (int i = 1; i <= q; i ++) {
		char c;
		scanf(" %c",&c); 
		if (c == 'B') op[i] = 1;
		else if (c == 'F') op[i] = 2;
		else if (c == 'C') op[i] = 3,scanf("%d%d",&nx[i],&ny[i]);
		else op[i] = 4;
	}
	solve(x,nx),solve(y,ny);
	for (int i = 1; i <= q; i ++) 
		if (op[i] == 4)
			printf("%d\n",A[i]);
	return 0;
}