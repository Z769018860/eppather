#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=1<<30;
const int N=2e3, M=3e5;
int n, m, s, t, c[N], h[N], cnt[N], cur[N]; bool v[N];
struct edge{int x, y, c, pre;} a[M]; int alen, last[N];
void ins(int x, int y, int c) {a[++alen]={x, y, c, last[x]}; last[x]=alen;}
struct cmp{bool operator () (int a, int b) const {return h[a]<h[b];}};
void bfs() {
	memset(h, 0x3f, sizeof(h));
	h[t]=0; queue<int> Q; Q.push(t);
	while(!Q.empty()) {
		int x=Q.front(); Q.pop(); v[x]=0;
		for(int k=last[x];k;k=a[k].pre) {
			int y=a[k].y;
			if(a[k^1].c&&h[y]>h[x]+1) {
				h[y]=h[x]+1;
				if(v[y]==0) Q.push(y), v[y]=true;
			}
		}
	}
}
priority_queue<int, vector<int>, cmp> q;
void push(int x) {
	for(int k=cur[x];k;k=a[k].pre) {
		int y=a[k].y; cur[x]=k;
		if(a[k].c&&h[y]+1==h[x]&&h[y]<0x3f3f3f3f3f3f3f3f) {
			int mn=min(a[k].c, c[x]);
			a[k].c-=mn; a[k^1].c+=mn;
			c[x]-=mn; c[y]+=mn; 
			if(v[y]==0&&y!=t&&y!=s) q.push(y), v[y]=true;
			if(c[x]==0) return ; 
		}
	}
	cur[x]=last[x];
}
void change(int x) {
	h[x]=0x3f3f3f3f3f3f3f3f;
	for(int k=last[x];k;k=a[k].pre) {
		int y=a[k].y; 
		if(a[k].c&&h[y]+1<h[x]) h[x]=h[y]+1;
	}
}
int HLPP() {
	bfs();
	memcpy(cur, last, sizeof(cur));
	if(h[s]==0x3f3f3f3f3f3f3f3f) return 0;
	h[s]=n; for(int i=1;i<=n;i++) if(h[i]<0x3f3f3f3f3f3f3f3f) cnt[h[i]]++;
	for(int k=last[s];k;k=a[k].pre) {
		int y=a[k].y, z=a[k].c;
		if(z&&h[y]<0x3f3f3f3f3f3f3f3f) {
			c[s]-=z; c[y]+=z; 
			a[k].c-=z; a[k^1].c+=z;
			if(y!=t&&y!=s&&!v[y]) q.push(y), v[y]=true;
		}
	}
	while(!q.empty()) {
		int x=q.top(); q.pop();
		v[x]=0; push(x);
		if(c[x]) {
			cnt[h[x]]--;
			if(cnt[h[x]]==0) {
				for(int i=1;i<=n;i++) 
					if(i!=s&&i!=t&&h[i]>h[x]&&h[i]<n+1) h[i]=n+1;
			}
			change(x); cnt[h[x]]++; q.push(x); v[x]=1;
		}
	}
	return c[t];
}
signed main() {
	scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
	alen=1; memset(last, 0, sizeof(last));
	for(int i=1;i<=m;i++) {
		int x, y, c; scanf("%lld%lld%lld", &x, &y, &c);
		ins(x, y, c); ins(y, x, 0);
	}
	printf("%lld", HLPP());
	return 0;
}