#include<algorithm>
#include<iostream>
#include<cstdio>
#define int long long 
using namespace std;
const long long N=100002;
const long long mod=998244353;

char buf[1<<21],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
int rd()
{
    int res=0,f=1;
    char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())
		if(ch=='-') f=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())
		res=(res<<3)+(res<<1)+ch-'0';
	return res*f;
}

void wt(int x,char ch=0)
{
	if(x<0) putchar('-'),wt(-x);
	else
	{
		if(x>=10) wt(x/10);
		putchar(x%10+'0'); 
	}
	if(ch) putchar(ch);
	return ;
}

string rdstr()
{
	string s("");
	char ch=getchar();
	for(;(ch<'0'||ch>'9')&&(ch!='X')&&(ch!='-');ch=getchar());
	for(;(ch>='0'&&ch<='9')||(ch=='X')||(ch=='-');ch=getchar())
		s.push_back(ch);
	return s;
}

int n,m;
string s[N];
int a[N];

#define lowbit(x) (x&(-x))

int tr[N];

void add(int x,int val)
{
	for(;x<=n;x+=lowbit(x))
		tr[x]+=val;
	return ;
}

int ask(int x)
{
	int res=0;
	for(;x;x-=lowbit(x))
		res+=tr[x];
	return res;
}

int lsh[N];

signed main()
{
	
	
	n=rd();
	int cnt=0;
	if(n==1)
	{
		cout<<"L";
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		s[i]=rdstr();
		if(s[i]=="X")
		{
			cnt++;
		}
		else
		{
			int f=1;
			for(char c:s[i])
			{
				if(c=='-') f=-1;
				else
					a[i]=a[i]*10+c-'0';
			}
			a[i]*=f;
		}
	}	
	if(cnt==0)
	{
		for(int i=1;i<=n;i++) lsh[++lsh[0]]=a[i];
		
		
		sort(lsh+1,lsh+1+lsh[0]);
		lsh[0]=unique(lsh+1,lsh+1+lsh[0])-lsh-1;
		for(int i=1;i<=n;i++) a[i]=lower_bound(lsh+1,lsh+1+lsh[0],a[i])-lsh;
		int ans=0;
		for(int i=n;i>=1;i--)
		{
			ans+=ask(a[i]-1);
			add(a[i],1);
		}
		
		if(ans%2==0)
		{
			cout<<"L";
		}
		else cout<<"W";
	}
	else
	{
		if(cnt%2==0)
		{
			cout<<"L";
		}
		else cout<<"W";
	}
	
	
    return 0;
}