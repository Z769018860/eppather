#include<bits/stdc++.h>
using namespace std;
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
typedef long long ll;
const ll maxn=1e6+10;
int n,q,m,r,tot,cnt;
ll v[maxn],in[maxn],out[maxn],head[maxn],x,num[maxn],sum[maxn];
struct node {
	int to,next;
} edge[2*maxn];
void add(int u,int v) {
	edge[tot].to=v;
	edge[tot].next=head[u];
	head[u]=tot++;
}
void dfs(int pos,int fa) {
	num[++cnt]=pos;
	in[pos]=cnt;
	for(int i=head[pos]; i!=-1; i=edge[i].next) {
		int v=edge[i].to;
		if(v!=fa) dfs(v,pos);
	}
	out[pos]=cnt;
}
int lowbit(int x) {
	return x&(-x);
}
void update(int x,int y) {
	while(x<=n) {
		sum[x]+=y;
		x+=lowbit(x);
	}
}
ll ask(int x) {
	ll res=0;
	while(x) {
		res+=sum[x];
		x-=lowbit(x);
	}
	return res;
}
int main() {
	scanf("%d%d%d",&n,&m,&r);
	for(int i=1; i<=n; i++)
		scanf("%lld",&v[i]),head[i]=-1;
	for(int i=1; i<n; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dfs(r,-1);
	for(int i=1; i<=n; i++)
		update(in[i],v[i]);
	while(m--) {
		int op,x,y;
		scanf("%d",&op);
		if(op==1) {
			scanf("%d%d",&x,&y);
			update(in[x],y);
		} else {
			scanf("%d",&x);
			printf("%lld\n",ask(out[x])-ask(in[x]-1));
		}
	}
	return 0;
}