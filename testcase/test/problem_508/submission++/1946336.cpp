

#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e6+10;
int n,m,q,fa[N],g[N],gd[N];
inline int find(int x){
	if (x==fa[x]) return x;
	int t=find(fa[x]);
	g[x]=(g[x]+g[fa[x]])%m;
	return fa[x]=t;
}
inline void exgcd(int a,int b,int &x,int &y){
	if (!b) return x=1,y=0,void();
	exgcd(b,a%b,y,x),y-=a/b*x;
}
void solve(){
	cin>>n>>m>>q;
	for (int i=1;i<=n;++i) fa[i]=i,gd[i]=m;
	while (q--){
		int op;cin>>op;
		switch (op){
			case 1:{
				int u,v,w;cin>>u>>v>>w;
				if (find(u)^find(v)){
					g[find(u)]=(g[u]+g[v]+w)%m;
					gd[find(v)]=__gcd(2*w%m,__gcd(gd[find(v)],gd[find(u)]));
					fa[find(u)]=find(v);
				}else{
					gd[find(u)]=__gcd(2*w%m,__gcd(gd[find(u)],(g[u]+g[v]+w)%m));
				}
				break;
			}
			case 2:{
				int u,v,x,b,c;cin>>u>>v>>x>>b>>c;
				if (find(u)^find(v)){
					cout<<"0\n";
					continue;
				}
				int ans=0,q=gd[find(u)];b%=gd[find(u)];
				int dis=((g[u]+g[v])%q-x%q+q)%q;
				int mod=__gcd(q,b),A,B;
				if (dis%mod){
					cout<<"0\n";
					continue;
				}
				b/=mod,q/=mod,dis/=mod,exgcd(b,q,A,B);
				A=1ll*A*dis%q,A=(A+q)%q;
				if (A<c) ans+=(c-A-1)/q+1;
				cout<<ans<<'\n';
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