#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll LLINF=0x3f3f3f3f3f3f3f3fLL;
const int INF=0x3f3f3f3f;
const int MAX=2e5+10;
ll qpow(ll a,ll b,ll p)
{
	ll res=1;
	while(b>0)
	{
		if(b&1) res=(__int128)res*a%p;
		a=(__int128)a*a%p;
		b>>=1;
	}
	return res;
}
bool miller_rabin(ll n,const initializer_list<ll>& as)
{
	int e=__builtin_ctzll(n-1);
	return all_of(as.begin(),as.end(),[&](ll it)
	{
		if(n<=it) return true;
		ll z=qpow(it,(n-1)>>e,n);  
		if(z==1||z==n-1) return true;
		for(int i=0;i<e-1;i++)
		{
			z=__int128(z)*z%n;
			if(z==1) return false;
			if(z==n-1) return true;
		}
		return false;
	});
}
bool is_prime(ll n)
{
	if(n<=2) return n==2;
	if(!(n&1)) return false;
	if(n<4759123141LL) return miller_rabin(n,{2,7,61});
	return miller_rabin(n,{2,325,9375,28178,450775,9780504,1795265022});
}
int main()
{
	ll x;
	while(~scanf("%lld",&x))
	{
		if(is_prime(x)) puts("Y");
		else puts("N");
	}
	return 0;
}