







#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=5005;
const int M=5e5+5;

inline int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

int n,m,cnt,a[M];
map<int,int> mp[N];
vector<pii> s[M<<2];
pii bk[M];

#define ls (t<<1)
#define rs (t<<1|1)
#define md ((l+r)>>1)

void upd(int l,int r,int t,int x,int y,pii k){
	if(l>y || r<x) return;
	if(l>=x&&r<=y) return s[t].push_back(k),void();
	upd(l,md,ls,x,y,k),upd(md+1,r,rs,x,y,k);
}

namespace dsu{
	int fa[N],sz[N];
	int sta[M],top;
	int find(int x){return x==fa[x] ? x : find(fa[x]);}
	void unity(int x,int y){
		int fx=find(x),fy=find(y);
		if(fx==fy) return;
		if(sz[fx]>sz[fy]) swap(fx,fy);
		sta[++top]=fx,sz[fy]+=sz[fx],fa[fx]=fy;
	}
}
using namespace dsu;

void dfs(int l,int r,int t){
	int tt=top;
	for(auto pr:s[t]) unity(pr.fi,pr.se);
	
	if(l==r){
		if(bk[l].fi) puts(find(bk[l].fi)==find(bk[l].se) ? "Y" : "N");
		while(top>tt){
			int fx=sta[top--];
			sz[fa[fx]]-=sz[fx],fa[fx]=fx;
		}
		return;
	}
	
	dfs(l,md,ls),dfs(md+1,r,rs);
	while(top>tt){
		int fx=sta[top--];
		sz[fa[fx]]-=sz[fx],fa[fx]=fx;
	}
}

signed main(){
	n=wrd(),m=wrd();
	for(int i=1;i<=n;++i) fa[i]=i,sz[i]=1;
	for(int i=1;i<=m;++i){
		int o=wrd(),x=wrd(),y=wrd();
		if(x>y) swap(x,y);
		if(!o) mp[x][y]=++cnt,a[cnt]=i;
		else if(o==1) upd(1,m,1,a[mp[x][y]],i-1,pii{x,y}),mp[x][y]=0;
		else bk[i]={x,y};
	}
	for(int i=1;i<=n;++i){
		for(auto j:mp[i]){
			if(a[j.se]) upd(1,m,1,a[j.se],m,pii{i,j.fi});
		}
	}
	return dfs(1,m,1),0;
}