#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll N=1e6+5;
ll n,m,q;
ll type,u,v,w,x,b,c;
ll f[N],gw[N],dist[N];
ll fx,fy;
ll ans;
inline void read(ll &x)
{
	ll f=1;char c;
	for(x=0,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48); x*=f;
}
inline ll mn(ll _x,ll _y){return _x<_y?_x:_y;}
inline ll mx(ll _x,ll _y){return _x>_y?_x:_y;}
inline ll ab(ll _x){return _x<0?-_x:_x;}
inline ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}
inline ll fd(ll x){
	if(f[x]==x) return x;
	ll r=fd(f[x]);
	dist[x]=(dist[x]+dist[f[x]])%m;
	return f[x]=r;
}
inline void exgcd(ll a,ll b,ll &x,ll &y){
	if(!b){x=1;y=0;return ;}
	exgcd(b,a%b,y,x);y-=a/b*x;
	return ;
}
int main()
{
	read(n);read(m);read(q);
	for(int i=1;i<=n;i++){f[i]=i;gw[i]=m;dist[i]=0;}
	while(q--){
		read(type);read(u);read(v);
		fx=fd(u);fy=fd(v);
		if(type==1){
			read(w); 
			if(fx==fy){
				gw[fx]=gcd(gw[fx],2ll*w);
				gw[fx]=gcd(gw[fx],(dist[u]+dist[v]+w)%m); 
			}
			else{
				f[fy]=fx;
				gw[fx]=gcd(gw[fx],gw[fy]);
				gw[fx]=gcd(gw[fx],2ll*w);
				dist[fy]=(dist[u]+dist[v]+w)%m;
			}
		}
		else{
			read(x);read(b);read(c);
			if(fx!=fy){puts("0");continue;}
			b%=gw[fx];
			ll A=b,B=gw[fx],d=gcd(A,B);
			ll C=dist[u]+dist[v]-x+B;
			if(C%d){puts("0");continue;}
			ll tx,ty;A/=d;B/=d;C/=d;
			exgcd(A,B,tx,ty);
			tx=(tx*C%B+B)%B;
			ans=0;
			if(tx<c) ans=(c-1-tx)/B+1;
			printf("%lld\n",ans); 
		}
	}
	return 0;
}

