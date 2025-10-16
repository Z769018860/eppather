#include<bits/stdc++.h>
#define int long long
using namespace std;
long long n,m,mod=998244353,limit,r[1000001],inv3;
struct node
{
 	vector<long long>a;
}; 
node a[1000001],P[1000001];
long long X[1000001],Y[1000001],Z[1000001],NOW;
inline long long mypow(long long x,int y)
{
	long long ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return ans;
}
inline void ntt(long long *A,int type)
{
	for(int i=0;i<limit;++i)if(i<r[i])swap(A[i],A[r[i]]);
	for(int mid=1;mid<limit;mid<<=1)
	{
		int L=mid<<1;
	    long long wn=mypow(3ll,(mod-1)/L);
		if(type==-1) wn=mypow(wn,mod-2);
		for(int i=0;i<limit;i+=L)
		{
			long long w=1ll;
			for(int j=0;j<mid;++j)
			{
				long long x=A[i+j],y=w*A[i+mid+j]%mod;
				A[i+j]=(x+y)%mod,A[i+mid+j]=((x-y)%mod+mod)%mod;
				w=w*wn%mod;
			}
		}
	}
}
inline node operator * (node a,node b)
{
	int N=a.a.size()+b.a.size()-2;
	limit=1;
	int l=0;
	while(limit<=N)limit<<=1,++l;
    for(int i=0;i<limit;++i)X[i]=Y[i]=0;
    for(int i=0;i<a.a.size();++i)X[i]=a.a[i];
    for(int i=0;i<b.a.size();++i)Y[i]=b.a[i];
	for(int i=0;i<limit;++i)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	ntt(X,1);
	ntt(Y,1);
	for(int i=0;i<limit;++i)Z[i]=1ll*X[i]*Y[i]%mod;
	ntt(Z,-1);
	long long inv=mypow(limit,mod-2);
	for(int i=0;i<limit;++i)Z[i]=Z[i]*inv%mod;
    node ans;
    for(int i=0;i<=a.a.size()+b.a.size()-2;++i)ans.a.push_back(Z[i]);
	while(ans.a.size()>1&&ans.a.back()==0)ans.a.pop_back();
	return ans;
}
inline node build(int now,int l,int r)
{
	if(l==r)
	{
		node jjx;
		jjx.a.push_back(((1LL-a[now].a[l])%mod+mod)%mod);
		jjx.a.push_back(a[now].a[l]);
		return jjx;
	}
	int mid=(l+r)>>1;
	node jjx=build(now,l,mid);
	node lbf=build(now,mid+1,r);
	jjx=jjx*lbf;
	return jjx;
}
signed main()
{
	
	
	scanf("%lld%lld",&n,&m);
	n+=30;
	long long aa,xx,yy;
	for(int i=1;i<=m;++i)
	{
		scanf("%lld%lld%lld",&aa,&xx,&yy);
		xx=1ll*xx*mypow(yy,mod-2)%mod;
		a[aa].a.push_back(xx);
	}
	int ans=0;
	for(int i=0;i<=n;++i)
	{
        NOW=i;
		int siz=a[i].a.size();
		if(siz)P[i]=build(i,0,siz-1);
        else P[i].a.push_back(1);
		
		
		if(i>0)P[i]=P[i]*P[i-1];
		siz=P[i].a.size(); 
		for(int j=0;j<siz;++j)ans=(ans+1ll*j*P[i].a[j])%mod;
		if(siz&1)P[i].a.push_back(0),++siz;
		siz>>=1;
		for(int j=0;j<siz;++j)P[i].a[j]=(P[i].a[j<<1]+P[i].a[j<<1|1])%mod;
		while(P[i].a.size()>siz)P[i].a.pop_back();
		
	}
	cout<<ans;
}