#include<bits/stdc++.h>
#define int long long
#define ll long long
#define pb push_back
#define fi first
#define se second
#define inf 1e9
#define pii pair<int,int>
#define F(i,a,b) for(int i=a;i<=(b);i++)
#define dF(i,a,b) for(int i=a;i>=(b);i--)
#define wh(lzm) while(lzm--)
#define lowbit(x) (x&(-x))
#define HH printf("\n")
#define eb emplace_back
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
const int maxn=1000005;
int n,m,lzm,f[maxn],d[maxn],p[maxn];
int find(int x){
	if(x==f[x]) return f[x];
	int nxt=find(f[x]);
	d[x]=(d[x]+d[f[x]])%m;
	return f[x]=nxt;
}
void exgcd(int a,int b,int &x,int &y){
	if(!b) return x=1,y=0,void();
	exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(int a,int b){
	int x,y;
	exgcd(a,b,x,y);
	return x;
}
void upd(int &x,int y){
	x=__gcd(x,y);
}
signed main(){
	n=read(),m=read(),lzm=read();
	F(i,1,n) f[i]=i,p[i]=m;
	wh(lzm){
		int op=read(),u=read(),v=read();
		if(op&1){
			int x=find(u),y=find(v),w=read();
			int T=(d[u]+d[v]+w)%m;
			if(x==y) upd(p[x],T);
			else{
				d[x]=T,upd(p[x],w<<1);
				upd(p[y],p[x]);
				f[x]=y;
			}
		}
		else{
			int x=read(),B=read(),C=read();
			if(find(u)^find(v)){
				puts("0");
				continue;
			}
			int k=p[find(u)],tt=__gcd(B,k);
			x=(x+d[u]+d[v])%m;
			if(x%tt||find(u)!=find(v)){
				puts("0");
				continue;
			}
			x/=tt,B/=tt,k/=tt;
			int tmp=(k-inv(B%k,k))*x%k;
			printf("%lld\n",(k-1+C-tmp)/k);
		}
	}
}