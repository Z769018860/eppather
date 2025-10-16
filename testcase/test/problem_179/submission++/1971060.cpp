#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,s[256][256];
unsigned int SA, SB, SC,lastans;
unsigned int rng() {
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    unsigned int t = SA;
    SA = SB;
    SB = SC;
    SC ^= t ^ SA;
    return SC;
}
ll nim_mul(ll a,ll b,ll p)
{
	if(a<2||b<2)return a*b;
	if(p<9&&(~s[a][b]))return s[a][b];
	p>>=1;
	int a0=a>>p,a1=a&((1ll<<p)-1),b0=b>>p,b1=b&((1ll<<p)-1),ab0=nim_mul(a0,b0,p),ab1=nim_mul(a1,b1,p),ab=nim_mul(a0^a1,b0^b1,p);
	int ret=nim_mul(ab0,1ll<<p-1,p)^ab1^((ab1^ab)<<p);
	if(p<8)s[a][b]=s[b][a]=ret;
	return ret;
}
signed main()
{
	memset(s,-1,sizeof(s));
	cin>>t>>SA>>SB>>SC;
	while(t--)
	{
		unsigned int x = rng() + lastans;
		unsigned int y = rng();
		lastans = nim_mul(x,y,32);
	}
	cout<<lastans;
	return 0;
}
