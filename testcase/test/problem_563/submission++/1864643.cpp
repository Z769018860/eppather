#include <bits/stdc++.h>

using namespace std;
static char buf[1000000],*p1=buf,*p2=buf,obuf[1000000],*p3=obuf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define putchar(x) (p3-obuf<1000000)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
template<typename item>
inline void read(register item &x)
{
	bool flag=false;
    x=0;register char c=getchar();
    while(c<'0'||c>'9')
	{
		if(c=='-')
		flag=true;
		c=getchar();
	}
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
    if(flag)
    x=-x;
}
static char cc[10000];
template<typename item>
inline void print(register item x)
{ 
	
	if(x==0)
	{
		cc[0]='0';
		putchar(cc[0]);
		return;
	}
	if(x<0)
	{
		cc[0]='-';
		putchar(cc[0]);
		x=-x;
	}
	register long long len=0;
	while(x)cc[len++]=x%10+'0',x/=10;
	while(len--)putchar(cc[len]);
}

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
	read(Q);
	
	while(Q--)
	{
		int l,r;
		read(l);
		read(r);
		
		print((Sum[r]-Sum[l-1]+P)%P);
		putchar('\n');
	
	}
	
fwrite(obuf,p3-obuf,1,stdout);
}



