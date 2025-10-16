#include<iostream>
#include<map>
#include<algorithm>
#include<stack>
#include<queue>
#include<cstring>
#define int long long
#define pii pair<int,int> 
using namespace std;
const int N=5e7+10;
const int M=5e6+10;
const int mod=998244853;
int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){ if(ch=='-') w=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){ s=s*10+ch-'0'; ch=getchar();}
	return s*w;
}
char c[N];
int po[10];
int a[M],k,ans=0;
int cha(char c)
{
	if(c=='A')
		return 0;
	else if(c=='G')
		return 1;
	else if(c=='C')
		return 2;
	else 
		return 3;
}
signed main()
{
	po[0]=1;
	for(int i=1;i<=10;i++)
		po[i]=po[i-1]*4;
	cin>>c+1;
	int n=strlen(c+1);
	k=read();
	int t=0;
	for(int i=1;i<=k;i++)
		t+=cha(c[i])*po[k-i];
	a[t]++;
	for(int i=k+1;i<=n;i++)
	{
		t=t*4+cha(c[i])-po[k]*cha(c[i-k]);
		a[t]++;
	}
	for(int i=0;i<=po[k];i++)
		ans=max(ans,a[i]);
	cout<<ans;
	return 0;
} 