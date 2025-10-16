#include<bits/stdc++.h>
using namespace std;

const int N=1e7+5;
const int mod=311021;

int _,l,r;
int f[N],prime[N],r2[N],rp[N],ph[N],pw[N];
bool is_prime[N];

void init()
{
	ph[1]=1;
	int idx=0;
	for(int i=2;i<N;i++)
	{
		if(!is_prime[i])
		{
			prime[++idx]=i,ph[i]=i-1;
			if(i==2)r2[i]=1;
			else rp[i]=1;
		}
		for(int j=1;j<=idx&&i*prime[j]<N;j++)
		{
			int k=i*prime[j];
			is_prime[k]=1;
			if(i%prime[j]==0)
			{
				ph[k]=ph[i]*prime[j],rp[k]=rp[i];
				if(prime[j]==2)r2[k]=r2[i]+1;
				else r2[k]=r2[i];
				break;
			}
			ph[k]=ph[i]*(prime[j]-1);
			if(prime[j]==2)r2[k]=1,rp[k]=rp[i];
			else r2[k]=r2[i],rp[k]=rp[i]+1;
		}
	}
	pw[0]=1;
	for(int i=1;i<N;i++)pw[i]=1ll*pw[i-1]*2%mod;
	for(int i=1;i<N;i++)
	{
		int v=pw[rp[i]];
		if(r2[i]==2)v*=2;
		else if(r2[i]>=3)v*=4;
		f[i]=pw[ph[i]-v>>1];
	}
	for(int i=1;i<N;i++)f[i]=(f[i-1]+f[i])%mod;
}

int main()
{
	init();
	scanf("%d",&_);
	while(_--)
	{
		scanf("%d%d",&l,&r);
		cout<<((f[r]-f[l-1])%mod+mod)%mod,putchar('\n');
	}
	return 0;
}