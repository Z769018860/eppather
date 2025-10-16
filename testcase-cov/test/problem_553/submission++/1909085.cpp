#include<bits/stdc++.h>
#define ll long long
#define gmax(x,y) x=max(x,y)
#define gmin(x,y) x=min(x,y)
#define F first
#define S second
#define P pair
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define rep(i,a,b) for(int i=a;i<b;i++)
#define V vector
#define RE return
#define ALL(a) a.begin(),a.end()
#define MP make_pair
#define PB emplace_back
#define PF push_front
#define FILL(a,b) memset(a,b,sizeof(a))
#define lwb lower_bound
#define upb upper_bound
#define lc (x<<1)
#define rc ((x<<1)|1)
#define sz(x) ((int)x.size())
#define pc putchar
using namespace std;
const ll INF=1e18;
int n,m;
P<int,int> p[100005];
P<ll,int> hav[100005],to[100005];
int len,tl;
signed main(){


	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>n>>t;
	FOR(i,1,n)cin>>p[i].F>>p[i].S;
	sort(p+1,p+n+1);
	hav[++len]=MP(0,0);
	FOR(i,1,n){
		tl=0;
		FOR(j,1,len){
			to[++tl]=hav[j];
			bool f=0;
			for(int k=29;k>=0;k--)if((p[i].S&(1<<k))&&(hav[j].S&(1<<k))){
				f=1;
				to[++tl]=MP(hav[j].F+p[i].F,hav[j].S|p[i].S|((1<<k)-1));
				break;
			}
			if(!f)to[++tl]=MP(hav[j].F+p[i].F,hav[j].S|p[i].S);
		}
		to[++tl]=p[i];
		sort(to+1,to+tl+1);
		len=0;
		int mx=0;
		FOR(i,1,tl){
			if(to[i].S>mx){
				mx=to[i].S;
				hav[++len]=to[i];
			}
		}
	}
	cin>>m;
	FOR(i,1,m){
		int x;
		cin>>x;
		if(!x){
			cout<<0<<'\n';continue;
		}
		ll ans=INF;
		FOR(j,1,len)if(hav[j].S>=x){
			gmin(ans,hav[j].F);
		}
		if(ans==INF)cout<<-1<<'\n';else cout<<ans<<'\n';
	}
	RE 0;
}
