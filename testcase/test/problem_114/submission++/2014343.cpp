#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=1023,Top=50;
LL a[N],b[N],flag;
void ins(LL x)
{
	for(int i=Top;i;i--)
		if(x&(1ll<<i-1))
		{
			if(!a[i]) return a[i]=x,void();
			else x^=a[i];
		}
	flag=1;
}
LL query(LL k)
{
	if(!(k-=flag)) return 0;
	LL cnt=0,res=0;
	for(int i=1;i<=Top;i++)
	{
		for(int j=i-1;j;j--)
			if((1ll<<j-1)&a[i]) a[i]^=a[j];
		if(a[i]) b[++cnt]=a[i];
	}
	if(k>=(1ll<<cnt)) return -1;
	for(int i=1;i<=cnt;i++)
	{
		if(k&(1ll<<i-1)) 
			res^=b[i];
	}
	return res;
}
int main()
{
	int n,m;
	scanf("%d",&n);
	flag=false;
	for(LL i=1,x;i<=n;i++) scanf("%lld",&x),ins(x);
	scanf("%d",&m);
	while(m--)
	{
		LL k;
		scanf("%lld",&k);
		printf("%lld\n",query(k));
	}
	return 0;
}