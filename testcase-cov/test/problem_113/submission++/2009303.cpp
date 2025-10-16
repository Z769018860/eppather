#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=1023,Top=50;
LL a[N];
void insert(LL x)
{
	for(int i=Top;i;i--)
		if((1ll<<(i-1))&x)
		{
			if(!a[i]) return a[i]=x,void();
			else x^=a[i];
		}
}
LL max_xor()
{
	LL res=0;
	for(int i=Top;i;i--) res=max(res,res^a[i]);
	return res;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(LL i=1,x;i<=n;i++) scanf("%lld",&x),insert(x);
	printf("%lld\n",max_xor());
	return 0;
}