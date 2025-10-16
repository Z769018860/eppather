#include <bits/stdc++.h>
typedef long long ll;
inline void read(int &x){int c(0);while(!isdigit(c))c=getchar();x=0;while(isdigit(c))x=x*10+(c-'0'),c=getchar();}
constexpr int N(21),MOD(998244353);
void Norm(int &x){if(x>=MOD)x-=MOD;}
int ksm(int x,int y){int ans(1);for(;y;y>>=1,x=(ll)x*x%MOD)if(y&1)ans=(ll)ans*x%MOD;return ans;}
void FWT(int *A,int n)
{
	for(int j(1);j<1<<n;j<<=1)
	for(int k(0);k<1<<n;k+=j<<1)
	for(int l(0);l<j;++l)
		Norm(A[k|l|j]+=A[k|l]);
}
void IFWT(int *A,int n)
{
	for(int j(1);j<1<<n;j<<=1)
	for(int k(0);k<1<<n;k+=j<<1)
	for(int l(0);l<j;++l)
		Norm(A[k|l|j]+=MOD-A[k|l]);
}
void mul(const int *a,const int *b,int *c,int n)
{
	static int A[N+1][1<<N],B[N+1][1<<N],C[N+1][1<<N];
	for(int i(0);i<=n;++i)
	{
		memset(A[i],0,sizeof(int)<<n);
		memset(B[i],0,sizeof(int)<<n);
		memset(C[i],0,sizeof(int)<<n);
	}
	for(int i(0);i<1<<n;++i)
		A[__builtin_popcount(i)][i]=a[i],B[__builtin_popcount(i)][i]=b[i];
	for(int i(0);i<=n;++i)
		FWT(A[i],n),FWT(B[i],n);
	for(int j(0);j<=n;++j)
	for(int k(0);j+k<=n;++k)
	for(int i(0);i<1<<n;++i)
		C[j+k][i]=(C[j+k][i]+(ll)A[j][i]*B[k][i])%MOD;
	for(int i(0);i<=n;++i)
		IFWT(C[i],n);
	for(int i(0);i<1<<n;++i)
		c[i]=C[__builtin_popcount(i)][i];
}
void exp(const int *A,int *B,int n)
{
	static int ans[N+1][1<<N];
	for(int i(0);i<=n;++i)
		memset(ans[i],0,sizeof(int)<<i);
	for(int j(0);j<=n;++j)
		ans[0][0]=1;
	for(int i(1);i<=n;++i)
	{
		memcpy(ans[i],ans[i-1],sizeof(int)<<(i-1));
		mul(ans[i-1],A+(1<<(i-1)),ans[i]+(1<<(i-1)),i-1);
	}
	for(int i(0);i<1<<n;++i)
		B[i]=ans[n][i];
}
int fa[N];
int getf(int u){return u==fa[u]?u:fa[u]=getf(fa[u]);}
int main(void)
{
	int n;
	read(n);
	static int E[N];
	std::iota(fa,fa+n,0);
	for(int i(0),e;i<n;++i)
	for(int j(0);j<n;++j)
	{
		read(e),E[i]|=e<<j;
		if(e)
			fa[getf(i)]=getf(j);
	}
	int x,y;
	read(x),read(y);
	static int A[1<<N],B[1<<N];
	static int prog[N+1];
	for(int i(1);i<=n;++i)
		prog[i]=((ll)prog[i-1]*y+1)%MOD;
	for(int u(0);u<n;++u)
	{
		for(int S(0);S<1<<u;++S)
			B[S]=(ll)A[S]*prog[__builtin_popcount(E[u]&S)]%MOD;
		exp(B,A+(1<<u),u);
	}
	int msk(0);
	for(int u(0);u<n;++u)
	if(fa[u]==u)
		msk|=1<<u;
	for(int S(0);S<1<<n;++S)
	if(!(S&msk))
		A[S]=A[S]*ll(x-1+MOD)%MOD;
	exp(A,A,n);
	printf("%d\n",A[(1<<n)-1]);
	return 0;
}