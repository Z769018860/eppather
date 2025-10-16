#include <bits/stdc++.h>

using namespace std;

const int MAXN=1e7+50,P=311021,NN=1e7;

int Phi[MAXN],d1[MAXN],d2[MAXN];
bool st[MAXN];
int prime[MAXN];
int Sum[MAXN];
int tot;
int Pow[MAXN];
int main()
{
	st[1]=true;
	Phi[1]=1;
	int t;
	for(int i=2;i<=NN;i++)
	{
		if(st[i]==false)
		{
			prime[++tot]=i; 
			if(i==2)
			{
				d2[i]=1;
			}
			else
			{
				d1[i]=1;
			}
			Phi[i]=i-1;
		}
		for(int j=1;i*prime[j]<=NN;j++)
		{
			t=i*prime[j];
			st[t]=true;
			if(i%prime[j]==0)
			{
				Phi[t]=Phi[i]*prime[j];
				d1[t]=d1[i];
				d2[t]=d2[i];
				if(j==1)
				d2[t]++;
				break;
			}
			Phi[t]=Phi[i]*(prime[j]-1);
			d1[t]=d1[i];
			d2[t]=d2[i];
			if(j==1)
			d2[t]++;
			else
			d1[t]++;
		}
	}
	Pow[0]=1;
	for(int i=1;i<=NN;i++)
	{
		Pow[i]=Pow[i-1]+Pow[i-1];
		if(Pow[i]>=P)
		Pow[i]-=P;
	}
	for(int i=1;i<=NN;i++)
	{
		if(d2[i]<=1)
		t=Pow[d1[i]];
		else if(d2[i]==2)
		t=Pow[d1[i]]*2;
		else if(d2[i]>=3)
		t=Pow[d1[i]]*4;
		Sum[i]=(Sum[i-1]+Pow[(Phi[i]-t)>>1])%P;
	}
	
	int Q;
	scanf("%d",&Q);
	while(Q--)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%d\n",(Sum[r]-Sum[l-1]+P)%P);
	}
}



