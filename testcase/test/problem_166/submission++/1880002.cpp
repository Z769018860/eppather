#include<bits/stdc++.h>
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
using namespace std;
typedef long long ll;
const int N=1e5+5,M=6e5+5,P=998244353,G=3,IG=(P+1)/G;
int n,m,dp=1,fac,lim,f[N],A[M],B[M],rev[M],ifac[N];
int Ksm(int x,int k)
{
	int ret=1;
	for(;k;k>>=1,x=(ll)x*x%P)
		if(k&1)
			ret=(ll)ret*x%P;
	return ret;
}
void NTT(int* A,bool f)
{
	rep(i,0,lim-1)
		if(i<rev[i])
			swap(A[i],A[rev[i]]);
	for(int mid=1;mid<lim;mid<<=1)
	{
		int sz=mid<<1,Wn=Ksm(f?G:IG,(P-1)/sz);
		for(int i=0;i<lim;i+=sz)
			for(int j=0,W=1;j<mid;j++,W=(ll)W*Wn%P)
			{
				int A0=A[i+j],A1=(ll)W*A[i+j+mid]%P;
				A[i+j]=(A0+A1)%P,A[i+j+mid]=(A0+P-A1)%P;
			}
	}
	if(!f)
	{
		int inv=Ksm(lim,P-2);
		rep(i,0,lim-1)
			A[i]=(ll)A[i]*inv%P;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	rep(i,0,n)
		scanf("%d",&f[i]);
	fac=1;
	rep(i,1,n)
		fac=(ll)fac*i%P;
	ifac[n]=Ksm(fac,P-2);
	for(int i=n-1;~i;i--)
		ifac[i]=(ll)ifac[i+1]*(i+1)%P;
	rep(i,0,n)
	{
		A[i]=(ll)f[i]*ifac[i]%P*ifac[n-i]%P;
		if(n-i&1)
			A[i]=(P-A[i])%P;
	}
	rep(i,0,n<<1)
		B[i]=Ksm(m-n+i,P-2);
	for(lim=1;lim<=n*3;lim<<=1);
	rep(i,1,lim-1)
		rev[i]=rev[i>>1]>>1|(i&1?lim>>1:0);
	NTT(A,1),NTT(B,1);
	rep(i,0,lim-1)
		A[i]=(ll)A[i]*B[i]%P;
	NTT(A,0);
	rep(i,1,n+1)
		dp=(ll)dp*(m-i+1)%P;
	rep(i,0,n)
	{
		printf("%d ",(ll)dp*A[n+i]%P);
		dp=(ll)dp*(m+i+1)%P*Ksm(m+i-n,P-2)%P;
	}
	return 0;
}