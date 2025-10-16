#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
int n,m,mod=998244353,limit,r[300001],inv3;
vector<int>a[300001],P[300001];
int X[300001],Y[300001],Z[300001],NOW,w[300001];
inline int add(int x,int y)
{
	return x+y>=mod?x+y-mod:x+y;
}
inline int del(int x,int y)
{
	return x-y<0?x-y+mod:x-y;
}
inline int mypow(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1)ans=1ll*ans*x%mod;
		y>>=1;
		x=1ll*x*x%mod;
	}
	return ans;
}
inline void ntt(int *A,int type)
{
	for(int i=0;i<limit;++i)if(i<r[i])swap(A[i],A[r[i]]);
	for(int mid=1;mid<limit;mid<<=1)
	{
		int L=mid<<1;
		for(int i=0;i<limit;i+=L)
		{
			for(int j=0;j<mid;++j)
			{
				int x=A[i+j],y=1ll*w[mid+j]*A[i+mid+j]%mod;
				A[i+j]=add(x,y),A[i+mid+j]=del(x,y);
			}
		}
	}
	if(type==-1)
	{
		reverse(A+1,A+limit);
	} 
}
inline vector<int> operator * (vector<int> a,vector<int> b)
{
	int N=a.size()+b.size()-2;
	limit=1;
	int l=0;
	while(limit<=N)limit<<=1,++l;
    for(int i=0;i<limit;++i)X[i]=Y[i]=0;
    for(int i=0;i<a.size();++i)X[i]=a[i];
    for(int i=0;i<b.size();++i)Y[i]=b[i];
	for(int i=0;i<limit;++i)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	for(int j=1;j<limit;j<<=1)
	{
		w[j]=1;
		int wn=mypow(3,mod/2/j);
		for(int i=1;i<j;++i)w[j+i]=1ll*w[j+i-1]*wn%mod;
	}
	ntt(X,1);
	ntt(Y,1);
	for(int i=0;i<limit;++i)Z[i]=1ll*X[i]*Y[i]%mod;
	ntt(Z,-1);
	int inv=mypow(limit,mod-2);
	for(int i=0;i<limit;++i)Z[i]=1ll*Z[i]*inv%mod;
   	vector<int>ans;
    for(int i=0;i<=a.size()+b.size()-2;++i)ans.push_back(Z[i]);
	while(ans.size()>1&&ans.back()==0)ans.pop_back();
	return ans;
}
inline vector<int> build(int now,int l,int r)
{
	if(l==r)
	{
		vector<int>jjx;
		jjx.push_back(del(1,a[now][l]));
		jjx.push_back(a[now][l]);
		return jjx;
	}
	int mid=(l+r)>>1;
	return build(now,l,mid)*build(now,mid+1,r);
}
inline void read(int& a)
{
	int s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch>'9')
	{
		if (ch == '-')
			w = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	a = s * w;
}
signed main()
{
	
	
	read(n),read(m);
	n+=30;
	int aa,xx,yy;
	for(int i=1;i<=m;++i)
	{
		read(aa),read(xx),read(yy);
		xx=1ll*xx*mypow(yy,mod-2)%mod;
		a[aa].push_back(xx);
	}
	int ans=0;
	for(int i=0;i<=n;++i)
	{
        NOW=i;
		int siz=a[i].size();
		if(siz)P[i]=build(i,0,siz-1);
        else P[i].push_back(1);
		
		
		if(i>0)P[i]=P[i]*P[i-1];
		siz=P[i].size(); 
		for(int j=0;j<siz;++j)
		{
			ans=add(ans,1ll*j*P[i][j]%mod);
			
		}
		if(siz&1)P[i].push_back(0),++siz;
		siz>>=1;
		for(int j=0;j<siz;++j)P[i][j]=add(P[i][j<<1],P[i][j<<1|1]);
		while(P[i].size()>siz)P[i].pop_back();
		
	}
	cout<<ans;
}