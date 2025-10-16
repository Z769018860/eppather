

#include<bits/stdc++.h>
using namespace std;
#define mid ((l+r)>>1)
int const N=2e5+10;
int const M=N<<6;
int n,q,k,trip,rt,f[N][20],g[N][20],pj[N],num[N],pr[N],vis[N],ct,lc[M],rc[M],c[M];
inline int lowbit(int m){
    while (m%k==0) m/=k;
    return m%k;
}
inline int lowbitv(int m){
    int ret=1;
    while (m%k==0) ret*=k,m/=k;
    return ret*(m%k);
}
inline void update(int &x,int l,int r,int ll,int rr,int v){
	if (!x) x=++ct;
	if (ll<=l && r<=rr) return c[x]^=v,void();
	if (ll<=mid) update(lc[x],l,mid,ll,rr,v);
	if (mid<rr) update(rc[x],mid+1,r,ll,rr,v);
}
inline int query(int x,int l,int r,int p){
	if (l==r || !x) return c[x];
	if (p<=mid) return c[x]^query(lc[x],l,mid,p);
	else return c[x]^query(rc[x],mid+1,r,p);
}
inline void init(){
	for (int i=1;i<=k;++i)
		for (int x=i;!(x&1);x>>=1,++pr[i]);
	
	for (int i=1;i<k;++i){
		if (vis[i] || pr[i]<pr[k]) continue;
		vector<int>q;q.push_back(i),vis[i]=1;
		for (int c=i*2%k;c^i;c=c*2%k) q.push_back(c),vis[c]=1;
		int lm=k/2,cnt=0;
		for (auto i:q) cnt+=i>lm;
		for (int i=0;i<(int)q.size();++i){
			int u=q[i],v=q[(i)?(i-1):(q.size()-1)];
			pj[u]=cnt,num[u]=q.size();
			f[u][0]=v,g[u][0]=(v>lm);
		}
		for (int s=1;s<=18;++s)
			for (auto i:q) f[i][s]=f[f[i][s-1]][s-1],
				g[i][s]=g[i][s-1]+g[f[i][s-1]][s-1];
	}
}
inline int findtop(int x){
    int lg=0,top,jw;for (x;x%k==0;x/=k,lg++);
    top=x%k,jw=(x-top)/k,trip=1+jw/pj[top]*num[top],jw%=pj[top];
    for (int i=18;i>=0;--i)
        if (g[top][i]<=jw) jw-=g[top][i],trip+=(1<<i),top=f[top][i];
    while (lg--) top*=k;return top;
}
inline void add(int x,int v){
	while (x<=n && pr[lowbit(x)]<pr[k])
		update(rt,1,n,x,x,v),x+=lowbitv(x);
	if (x>n) return;
	int st=findtop(x),rg=query(rt,1,n,st),tp=rg;
	update(rg,1,n,trip,n,v);
	if (!tp) update(rt,1,n,st,st,rg);
}
inline int findans(int x){
    int ret=0;
    while (x){
        if (pr[lowbit(x)]<pr[k]) ret^=query(rt,1,n,x);
        else{
            int st=findtop(x),rg=query(rt,1,n,st);
            if (rg) ret^=query(rg,1,n,trip);
        }
        x-=lowbitv(x);
    }
    return ret;
}
void solve(){
	cin>>n>>q>>k,init();
	while (q--){
		int op;cin>>op;
		switch (op){
			case 1:{
				int x,v;cin>>x>>v;
				add(x,v);
				break;
			}
			case 2:{
				int x;cin>>x;
				cout<<findans(x)<<'\n';
				break;
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	
	while (t--) solve();
	cerr<<"Running Time: "<<(double)clock()/CLOCKS_PER_SEC<<" s\n";
	return 0;
}