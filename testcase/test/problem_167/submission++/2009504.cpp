#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+5; 
const int mod = 998244353;
typedef long long ll;
inline ll read()
{
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
ll a[N],n;
ll num[N];
ll jc[N],tr[N];

inline ll lowbit(ll x)
{
	return x&-x;
}
void add(ll x,ll v)
{
	for(int i=x;i<=n;i+=lowbit(i))
	{
		tr[i]+=v;
	}
}
inline ll sum(ll x)
{
	ll ans=0;
	for(int i=x;i;i-=lowbit(i))
	{
		ans+=tr[i];
	}
	return ans;
}
void init()
{
	jc[0]=1;
	for(int i=1;i<=n;i++){
		jc[i]=(jc[i-1]*i)%mod;
		add(i,1);
	}
}
int main()
{
	cin.tie(0);cout.tie(0);
	n=read();init(); 
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
		ans=(ans+((sum(a[i])-1)*jc[n-i])%mod)%mod;
		add(a[i],-1);
	}
	cout<<ans+1;
	return 0;
}
