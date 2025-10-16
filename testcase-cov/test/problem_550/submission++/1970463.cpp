#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

int T,n,m,k;

int main()
{
    

    cin>>T;
    while(T--)
    {
        cin>>n>>m>>k;
        ll ans=1ll*n*(1ll*m*m/4)+1ll*m*(1ll*n*n/4);
        printf("%lld\n",ans);
    }    
    return 0;
}