#include <bits/stdc++.h>
#define ll long long
#define N 52
using namespace std;
ll rint(){
	ll ret=0;
	char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) ret=ret*10+(c-'0'),c=getchar();
	return ret;
}
void rout(ll x){
	if(x<10) putchar(x+48);
	else rout(x/10),putchar((x%10)+48);
	return;
}
ll ksm(ll x,ll y,ll p)
{
	ll ret=1;
	x%=p;
	while(y>0)
	{
		if(y&1)
		{
			ret=(ret*x)%p;
		}
		x=(x*x)%p;
		y>>=1;
	}
	return ret;
}
ll n,p,a[N],totp[62][N][N],f[62][N][N*N],g[2][N][N*N],digs[62],digm[62],dp[62][N],C[N][N],mx;
int main(){
	ll i,j,k,l,x,pw;
	n=rint(),p=rint();
	for(i=0;i<N;i++)
	{
		C[i][0]=1;
		for(j=1;j<=i;j++)
		{
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%p;
		}
	}
	for(i=0;i<=n;i++)
	{
		a[i]=rint();
	}
	for(i=0,pw=1;pw<=1e18;i++,pw*=p)
	{
		for(k=0;k<p&&k<=1e18/pw+2;k++)
		{
			for(j=0;j<=n;j++)
			{
				totp[i][j][k]=ksm(a[j],pw*k,p);
			}
		}
		for(j=0;j<p;j++)
		{
			for(k=0;k<=n*(p-1);k++)
			{
				g[0][j][k]=0;
			}
		}
		g[0][0][0]=1;
		for(j=0;j<=n;j++)
		{
			ll u=j&1,v=(j&1)^1;
			for(k=0;k<p;k++)
			{
				for(l=0;l<=n*(p-1);l++)
				{
					g[v][k][l]=0;
					for(x=0;x<=k&&x*j<=l;x++)
					{
						g[v][k][l]+=g[u][k-x][l-x*j]*totp[i][j][x]*C[k][x];
					}
					g[v][k][l]%=p;
				}
			}
		}
		ll u=(n&1)^1;
		for(j=0;j<p;j++)
		{
			for(k=0;k<=n*(p-1);k++)
			{
				f[i][j][k]=g[u][j][k];
			}
		}
	}
	mx=i;
	ll T=rint();
	while(T--)
	{
		ll m=rint(),s=rint();
		for(i=0;i<mx;i++)
		{
			digm[i]=m%p;
			m/=p;
			digs[i]=s%p;
			s/=p;
		}
		memset(dp,0,sizeof(dp));
		dp[0][0]=1;
		for(i=0;i<mx;i++)
		{
			for(k=0;k<=n*(p-1);k++)
			{
				if(f[i][digm[i]][k])
				{
					for(j=(digs[i]+p-(k%p))%p;j<=n;j+=p)
					{
						(dp[i+1][(j+k)/p]+=dp[i][j]*f[i][digm[i]][k])%=p;
					}
				}
			}
		}
		rout(dp[mx][0]),putchar('\n');
	}
	return 0;
}