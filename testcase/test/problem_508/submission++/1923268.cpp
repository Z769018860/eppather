#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>

#define ll long long
#define db double
#define rg register int

using namespace std;

int n,m,q;
int d[1000005]; 
int g[1000005]; 
int fa[1000005]; 

inline int qr(){
	register char ch; register bool sign=0; rg res=0;
	while(!isdigit(ch=getchar()))if(ch=='-')sign=1;
	while(isdigit(ch))res=res*10+(ch^48),ch=getchar();
	if(sign)return -res; else return res;
}

inline int gcd(int a,int b){
	if(b==0)return a; return gcd(b,a%b);
}

inline int getfa(int x){
	if(x==fa[x])return x;
	rg to=getfa(fa[x]);
	d[x]=(d[x]+d[fa[x]])%m;
	return fa[x]=to; 
}

inline void exgcd(int a,int b,int &x,int &y){
	if(b==0) x=1,y=0;
	else exgcd(b,a%b,y,x),y-=a/b*x; 
}

int main(){
	n=qr(); m=qr(); q=qr();
	for(rg i=1;i<=n;++i) fa[i]=i,g[i]=m;
	for(rg i=1;i<=q;++i){
		rg op=qr(),u=qr(),v=qr(),w=qr();
		rg fx=getfa(u),fy=getfa(v);
		if(op==1){
			if(fx!=fy){ fa[fx]=fy;
				d[fx]=((ll)d[u]+d[v]+w)%m; 
				g[fy]=gcd(gcd(g[fx],g[fy]),2*w);
			}else g[fx]=gcd(gcd(g[fx],((ll)d[u]+d[v]+w)%m),2*w);
		} else{
			rg ans=0,b=qr()%g[fx],c=qr();
			if(fx!=fy){puts("0"); continue;}
			rg A=b,B=g[fx],G=gcd(A,B),C=(ll)d[u]+d[v]-w+B;
			if(C%G){puts("0"); continue;} 
			rg x,y; A/=G; B/=G; C/=G;
			exgcd(A,B,x,y); x=((ll)x*C%B+B)%B; 
			if(x<c)ans=(c-1-x)/B+1;
			printf("%d\n",ans); 
		}
	}
	return 0;
}
