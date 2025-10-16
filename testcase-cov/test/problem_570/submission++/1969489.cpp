#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int f[(1<<22)+10];
int ksm(int a,int b)
{
    int ans=1;
    while(b)
    {
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)
    {
        int x;
        cin>>x;
        f[x]++;
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<(1<<n);j++)
            if(j>>i&1^1)
                f[j]+=f[j|1<<i];
    int ans=0;
    for(int i=1;i<(1<<n);i++)
    {
        if(__builtin_popcount(i)&1) ans=(ans+ksm(f[i],k))%mod;
        else ans=(ans-ksm(f[i],k)+mod)%mod;
    }
    cout<<ans;
    return 0;
}

