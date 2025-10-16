#include<bits/stdc++.h>
#define ll long long
#define db double
using namespace std;
int n,m,q,d[1000010],g[1000010],fa[1000010];
inline int gcd(int a,int b){
	if(b==0)return a; return gcd(b,a%b);
}
inline int getfa(int x){
	if(x==fa[x])return x;
	int to=getfa(fa[x]);
	d[x]=(d[x]+d[fa[x]])%m;
	return fa[x]=to;
}
inline void exgcd(int a,int b,int &x,int &y){
	if(b==0) x=1,y=0;
	else exgcd(b,a%b,y,x),y-=a/b*x;
}
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;++i) fa[i]=i,g[i]=m;
	for(int i=1;i<=q;++i){
		int op,u,v,w;cin>>op>>u>>v>>w;
		int fx=getfa(u),fy=getfa(v); 
		if(op==1){
			if(fx!=fy){ fa[fx]=fy;
				d[fx]=((ll)d[u]+d[v]+w)%m;
				g[fy]=gcd(gcd(g[fx],g[fy]),2*w);
			}else g[fx]=gcd(gcd(g[fx],((ll)d[u]+d[v]+w)%m),2*w);
		} else{
			int ans=0,b,c;
			cin>>b>>c;b=b%g[fx];
			if(fx!=fy){puts("0"); continue;}
			int A=b,B=g[fx],G=gcd(A,B),C=(ll)d[u]+d[v]-w+B; 
			if(C%G){puts("0"); continue;}
			int x,y; A/=G; B/=G; C/=G; 
			exgcd(A,B,x,y); x=((ll)x*C%B+B)%B;
			if(x<c)ans=(c-1-x)/B+1; 
			printf("%d\n",ans);
		}
	}
	return 0;
}