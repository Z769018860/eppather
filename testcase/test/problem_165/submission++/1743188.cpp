#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
using namespace std;
const int N=3005,P=998244353;
int n,tot,X[N],Y[N],pre[N],suf[N],prd[N];
int Ksm(int x,int k)
{
	int ret=1;
	for(;k;k>>=1,x=1ll*x*x%P)
		if(k&1)
			ret=1ll*ret*x%P;
	return ret;
}
int F(int x)
{
	int ret=0;
	pre[0]=suf[tot+1]=1;
	rep(i,1,tot)
		pre[i]=1ll*pre[i-1]*(x-X[i]+P)%P;
	for(int i=tot;i;i--)
		suf[i]=1ll*suf[i+1]*(x-X[i]+P)%P;
	rep(i,1,tot)
		ret=(ret+1ll*pre[i-1]*suf[i+1]%P*prd[i]%P*Y[i]%P+P)%P;
	return ret;
}
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		int op;
		scanf("%d",&op);
		if(op==1)
		{
			tot++;
			scanf("%d%d",&X[tot],&Y[tot]);
			rep(i,1,tot-1)
				prd[i]=1ll*prd[i]*Ksm((X[i]-X[tot]+P)%P,P-2)%P;
			prd[tot]=1;
			rep(i,1,tot-1)
				prd[tot]=1ll*prd[tot]*Ksm((X[tot]-X[i]+P)%P,P-2)%P;
		}
		else
		{
			int x;
			scanf("%d",&x);
			printf("%d\n",F(x));
		}
	}
	return 0;
}