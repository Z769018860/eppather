#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define db double
#define pint pair<int,int>
#define mk(x,y) make_pair(x,y)
#define fir first
#define sec second
#define Rep(x,y,z) for(int x=y;x<=z;x++)
#define Red(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
char buf[1<<12],*pp1=buf,*pp2=buf,nc;int ny;
inline char gc() {return pp1==pp2&&(pp2=(pp1=buf)+fread(buf,1,1<<12,stdin),pp1==pp2)?EOF:*pp1++;}

inline int read(){
	int x=0;for(ny=1;nc=gc(),(nc<48||nc>57)&&nc!=EOF;)if(nc==45)ny=-1;if(nc<0)return nc;
	for(x=nc-48;nc=gc(),47<nc&&nc<58&&nc!=EOF;x=(x<<3)+(x<<1)+(nc^48));return x*ny;
}
int k,n,ans=1;
inline int Solve2(int p,int cnt,int k){
	int n=1,phi;Rep(i,1,cnt)n*=p;phi=n/p*(p-1);
	if(p==2&&n>4&&k%2==0)phi/=2;return phi/__gcd(phi,k);
}
inline int Solve(int p,int cnt,int k){int tmp=1;for(;cnt>0;cnt-=k)tmp+=Solve2(p,cnt,k);return tmp;}
int main(){


	k=read(),read(),n=read();
	for(int i=2;i*i<=n;i++)if(n%i==0){
		int cnt=0;while(n%i==0)cnt++,n/=i;
		ans*=Solve(i,cnt,k);
	}if(n>1)ans*=Solve(n,1,k);
	cout<<ans<<'\n';
	return 0;
}


