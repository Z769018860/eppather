#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e6,inf=1e9+7;

namespace IO{
	int c;
	unsigned int seed;
	unsigned int randnum(){
		seed^=seed<<13;
		seed^=seed>>17;
		seed^=seed<<5;
		return seed;
	}
	inline int read(int &x){scanf("%d",&x);return x;}
	inline void init_case(int &m,int &a,int &b,int &d,int p[]){
		scanf("%d%u%d%d%d%d",&m,&seed,&a,&b,&c,&d);
		for(int i=1;i<=m;i++){
			if(randnum()%c==0)p[i]=-1;
			else p[i]=randnum()%b;
		}
	}
	inline void update_ans(unsigned int &ans_sum,unsigned int cur_ans,int no){
		const static unsigned int mod=998244353;
		ans_sum^=(long long)no*(no+7)%mod*cur_ans%mod;
	}
}
using IO::read;
using IO::init_case;
using IO::update_ans;

int m,A,B,tp,dx[Maxn+5],vis[Maxn+5],dxv[Maxn+5];
int st1[Maxn+5],top1,st2[Maxn+5],top2;
int mn1[Maxn+5],mn2[Maxn+5];

inline void Set(int x) {dxv[x]=vis[x]=1;}
inline void Trans()
{
    while(top2) st1[++top1]=st2[top2--];
    For(i,1,top1) mn1[i]=min(mn1[i-1],st1[i]);
}
inline int Reset()
{
    if(!top1 && !top2) return 0;
    if(!top1) Trans();
    int k=st1[top1--]; vis[k]=1; return 1;
}
inline void Pop(int x) {vis[x]=0,st2[++top2]=x,mn2[top2]=min(mn2[top2-1],x);}
inline int GetAns()
{
    int id=min(mn1[top1],mn2[top2]);
    if(id<=A) return id;
    for(int i=A+1;;++i) if(!vis[i]) return i;
}
inline void Solve1()
{
    unsigned int ans_sum=0,cur_ans=0; int it=A+1;
    For(i,1,m)
	{
        int k=dx[i];
        if(k==-1) continue;
        else if(!dxv[k]) vis[k]=dxv[k]=1;
        else if(vis[k]) continue;
        else continue;
        while(vis[it]) it++;
        cur_ans=it;
		update_ans(ans_sum,cur_ans,i);
	}
	printf("%u\n",ans_sum);
}
inline void Solve()
{
    unsigned int ans_sum=0,cur_ans=0;
	init_case(m,A,B,tp,dx),top1=top2=0;
    For(i,0,max(A,B)+1) vis[i]=dxv[i]=0;
    For(i,0,A) vis[i]=dxv[i]=1;
    if(tp==1) {Solve1(); return;}
	For(i,1,m)
	{
        int k=dx[i],op=1;
        if(k==-1) op=Reset();
        else if(!dxv[k]) Set(k);
        else if(vis[k]) Pop(k);
        else op=Reset();
        if(op) cur_ans=GetAns(); else cur_ans=0;
		update_ans(ans_sum,cur_ans,i);
	}
	printf("%u\n",ans_sum);
}

int main()
{
    

	int T; read(T); mn1[0]=mn2[0]=inf;
	while(T--) Solve();
	return 0;
}