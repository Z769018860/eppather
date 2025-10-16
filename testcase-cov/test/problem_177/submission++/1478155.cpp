#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
#define N 52
typedef unsigned char uc;
typedef uc pm[N],*pt;typedef const uc *cp;
inline void mul(cp a,cp b,pt c,int n){for(int i=1;i<=n;i++)c[i]=a[b[i]];}
inline void inv(cp a,pt c,int n){for(int i=1;i<=n;i++)c[a[i]]=i;}
inline void miv(cp a,cp b,pt c,int n){for(int i=1;i<=n;i++)c[b[i]]=a[i];}
inline void Out(cp a,int n){for(int i=1;i<=n;i++)cerr<<(int)a[i]<<" ";cerr<<endl;}
pm t1;
inline void ivm(cp a,cp b,pt c,int n){for(int i=1;i<=n;i++)t1[a[i]]=i;for(int i=1;i<=n;i++)c[i]=t1[b[i]];}
inline void Get(pt c,int n){for(int i=1,x;i<=n;i++)scanf("%d",&x),c[i]=x;}
struct Int{
	int a[82];
	inline void operator*=(const int &v)
	{
		for(int i=0;i<=80;i++)a[i]*=v;
		for(int i=0;i<=80;i++)while(a[i]>9)a[i]-=10,++a[i+1];
	}
	inline void Out(){int i,fl=0;for(i=80;i>=0;i--){fl|=a[i];if(fl)printf("%d",a[i]);}if(!fl)printf("0");}
}ans;
struct Group{
	int sz,ps,cn=0;bool vis[N];pm t[N],S[N];Group *nex;
	inline void ini(int ssz,int pps,Group *nx){sz=ssz;ps=pps;vis[ps]=1;nex=nx;for(int i=1;i<=sz;i++)t[ps][i]=i;}
	inline int Orb(){int i,res=0;for(i=1;i<=sz;i++)res+=vis[i];return res;}
	inline bool hv(cp s){int p=s[ps];pm tmp;return vis[p]&&((nex==NULL)||(ivm(t[p],s,tmp,sz),nex->hv(tmp)));}
	void dfs(cp s)
	{

		int p=s[ps];pm tmp;
		if(vis[p]){if(nex!=NULL)ivm(t[p],s,tmp,sz),nex->Ins(tmp);}
		else{vis[p]=1;memcpy(t[p],s,sizeof(uc)*(sz+1));for(int i=1;i<=cn;i++)mul(S[i],s,tmp,sz),dfs(tmp);}
	}
	inline void Ins(cp s){if(!hv(s)){memcpy(S[++cn],s,sizeof(uc)*(sz+1));pm tmp;for(int i=1;i<=sz;i++)if(vis[i])mul(s,t[i],tmp,sz),dfs(tmp);}}
}G[N];
int n,m;
int main(){
	scanf("%d%d",&n,&m);int i;pm res;
	for(i=1;i<=n;i++)G[i].ini(n,i,(i==n)?NULL:(&G[i+1]));
	while(m--)Get(res,n),G[1].Ins(res);
	ans.a[0]=1;for(i=1;i<=n;i++)ans*=G[i].Orb();ans.Out();return 0;
}