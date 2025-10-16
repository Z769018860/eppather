#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
#define N 227
int mod;
inline int M(int x){return (x>=mod)?(x-mod):x;}
inline void Ad(int &x,int v){x=M(x+v);}
inline int M1(int x){return (x<0)?(x+mod):x;}
inline void Dc(int &x,int v){x=M1(x-v);}
inline int ksm(int p,int k){int res=1;while(k){if(k&1)res=1ll*res*p%mod;k>>=1;p=1ll*p*p%mod;}return res;}
inline void cls(int A[],int d){memset(A,0,sizeof(int)*(d+1));}
inline void cpy(int A[],int B[],int d){memcpy(A,B,sizeof(int)*(d+1));}
int n;
int f[N],t1[N],t2[N];
inline int Deg(int A[],int u){while((~u)&&(!A[u]))--u;return u;}
inline int Mod(int A[],int B[],int n,int m,int C[])
{
	int i,j,v,iv=ksm(B[m],mod-2);for(i=0;i<=n;i++)t1[i]=A[i];
	for(i=n;i>=m;i--)if(v=t1[i]){v=1ll*iv*v%mod;for(j=m;j>=0;j--)Dc(t1[i-(m-j)],1ll*v*B[j]%mod);}
	for(i=0;i<m;i++)C[i]=t1[i],t1[i]=0;return Deg(C,m-1);
}
inline int D1v(int A[],int B[],int n,int m,int C[])
{
	int i,j,v,iv=ksm(B[m],mod-2);for(i=0;i<=n;i++)t1[i]=A[i];
	for(i=n;i>=m;i--)if(v=t1[i]){v=1ll*iv*v%mod;C[i-m]=v;for(j=m;j>=0;j--)Dc(t1[i-(m-j)],1ll*v*B[j]%mod);}cls(t1,m);return Deg(C,n-m);
}
inline int Gcd(int A[],int B[],int n,int m,int C[])
{
	int i,v;memcpy(t1,A,sizeof(int)*(n+1));memcpy(t2,B,sizeof(int)*(m+1));
	while(n=Deg(t1,n),m=Deg(t2,m),((~n)||(~m)))
	{
		if(n<m){for(i=0;i<=m;i++)swap(t1[i],t2[i]);swap(n,m);}if(m==(-1))break;
		v=1ll*ksm(t2[m],mod-2)*t1[n]%mod;for(i=m;i>=0;i--)Dc(t1[n-(m-i)],1ll*v*t2[i]%mod);
	}
	for(i=0;i<=n;i++)C[i]=t1[i],t2[i]=t1[i]=0;return Deg(C,n);
}
inline int Mul(int A[],int B[],int n,int m,int C[])
{
	int i,j,v1,v2;for(i=0;i<=n+m;i++)C[i]=0;
	for(i=0;i<=n;i++)if(v1=A[i])for(j=0;j<=m;j++)if(v2=B[j])Ad(C[i+j],1ll*v1*v2%mod);return Deg(C,n+m);
}
int t3[N],t4[N],t5[N];
inline int Ksm(int A[],int B[],int n,int m,int k,int C[])
{
	n=Mod(A,B,n,m,t3);t4[0]=1;int d=0,d1;
	while(k)
	{
		if(k&1)d1=Mul(t4,t3,d,n,t5),cls(t4,d),d=Mod(t5,B,d1,m,t4),cls(t5,d1);
		k>>=1;if(k)d1=Mul(t3,t3,n,n,t5),cls(t3,n),n=Mod(t5,B,d1,m,t3),cls(t5,d1);
	}
	cls(t3,n);for(int i=0;i<=d;i++)C[i]=t4[i];cls(t4,d);return Deg(C,d);
}
int g[N],w[N],ans[N],cn=0,t6[N],t7[N],A[N];
inline void Dive(int f[],int n)
{
	t6[1]=1;t6[0]=1ll*rand()*rand()%mod;
	int d=Ksm(t6,f,1,n,(mod-1)>>1,t7),m;Dc(t7[0],1);d=Deg(t7,d);if(d==(-1))return Dive(f,n);
	m=Gcd(f,t7,n,d,A);if(m==0){cls(t7,d);return Dive(f,n);}
}
void Dich(int f[],int n)
{
	if(!n)return;if(n==1){ans[++cn]=1ll*M1(-f[0])*ksm(f[1],mod-2)%mod;return;}
	Dive(f,n);int *X,*Y,d=Deg(A,n);X=new int[d+1];cpy(X,A,d);cls(A,d);Y=new int[n-d+1]();D1v(f,X,n,d,Y);Dich(X,d);Dich(Y,n-d);
}
int main(){
	srand(19260817);
	scanf("%d%d",&n,&mod);int i,d;
	for(i=0;i<=n;i++)scanf("%d",&f[i]);g[1]=1;d=Ksm(g,f,1,n,mod,w);Dc(w[1],1);d=Deg(w,max(d,1));
	memset(g,0,sizeof(g));n=Gcd(f,w,n,d,g);memset(f,0,sizeof(f));memset(w,0,sizeof(w));Dich(g,n);
	printf("%d\n",cn);sort(ans+1,ans+cn+1);for(i=1;i<=cn;i++)printf("%d ",ans[i]);return 0;
}