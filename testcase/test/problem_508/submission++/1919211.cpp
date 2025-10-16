#include<stdio.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1e6+5;
char buf[1<<25],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin)),p1==p2)?EOF:*p1++
template<class R>
void read(R &x){
	char c=getchar();
	for(;c<48||c>57;c=getchar());
	for(x=0;c>47&&c<58;c=getchar())x=(x<<1)+(x<<3)+(c^48);
}
int n,m,q,fa[N],sz[N];
int op,u,v,w,b,c,fu,fv,z;
int A,B,D,G,X,Y;
int g[N],d[N],o;
inline int gcd(int a,int b){
	for(;b;o=a,a=b,b=o%b);
	return a;
}
inline void exgcd(int a,int b){
	if(!b)return X=1,Y=0,void();
	exgcd(b,a%b);
	z=X;X=Y;Y=z-a/b*Y;
}
inline int gf(int x){
	if(fa[x]!=x){
		int F=fa[x];fa[x]=gf(fa[x]);
		(d[x]+=d[F])>=m?d[x]-=m:d[x];
	}
	return fa[x];
}
int main(){
	read(n),read(m),read(q);
	for(int i=1;i<=n;++i)fa[i]=i,g[i]=m,sz[i]=1;
	for(int i=1;i<=q;++i){
		read(op),read(u),read(v),read(w);
		if(op==1){
			fu=gf(u),fv=gf(v);
			if(fu==fv){
				g[fu]=gcd(g[fu],gcd(w<<1,((ll)d[u]+d[v]+w)%m));
				continue;
			}
			if(sz[fu]<sz[fv])swap(fu,fv);
			fa[fv]=fu;
			d[fv]=((ll)d[v]+d[u]+w)%m;
			sz[fu]+=sz[fv];
			g[fu]=gcd(g[fu],gcd(g[fv],w<<1));
		}else{
			read(b),read(c);
			fu=gf(u),fv=gf(v);
			if(fu!=fv){puts("0");continue;} 
			A=g[fu],B=b;
			D=((ll)d[u]+d[v]-w+m)%A;
			G=gcd(A,B);
			if(D%G){puts("0");continue;}
			D/=G,A/=G,B/=G;
			exgcd(A,B);
			X=(1ll*Y*D%A+A)%A;
			if(c>X)printf("%d\n",(c-1-X)/A+1);
			else puts("0");
		}
	}
	return 0;
}