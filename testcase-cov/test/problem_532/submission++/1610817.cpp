#include <bits/stdc++.h>
#define ll long long
using namespace std;
template<typename T>void read(T &x)
{
    T f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    x*=f;
}
const ll MOD=1e9+7;
inline ll Add(ll x,ll y){return (x+y)%MOD;}
inline ll Dec(ll x,ll y){return (x-y+MOD)%MOD;}
inline ll Mul(ll x,ll y){return 1ll*x*y%MOD;}
ll qpow(ll a,ll b)
{
    ll ret=1;
    while(b)
    {
        if(b&1) ret=Mul(ret,a);
        b>>=1;a=Mul(a,a);
    }
    return ret;
}
ll vis[1000005],Bef;
ll b1[1000005],b2[1000005];
ll x[1000005];
int main() {
    #ifndef ONLINE_JUDGE
    freopen("input","r",stdin);
    freopen("output","w",stdout);
    #endif
    ll A,B,C;
    ll L1,R1,L2,R2,L,R;
    read(A);read(B);read(C);read(x[0]);read(L1);read(R1);read(L2);read(R2);
    for(ll i=1;;i++)
    {
        x[i]=(1ll*x[i-1]*A+B)%C+1;
        if(vis[x[i]]) {L=vis[x[i]],R=i-1;break;}
        vis[x[i]]=i;R=i-1;
    }
    ll n=R-L+1;
    for(;L1<=R1&&L1<L;L1++) b1[x[L1]]++;
    for(;L2<=R2&&L2<L;L2++) b2[x[L2]]++;
    for(ll i=L;i<=R;i++)
    {
        if(i<=R1) b1[x[i]]=(R1-i)/n-(L1-i+n-1)/n+1;
        if(i<=R2) b2[x[i]]=(R2-i)/n-(L2-i+n-1)/n+1;
    }
    for(ll i=1;i<=C;i++) b1[i]=Add(b1[i],b1[i-1]),b2[i]=Add(b2[i],b2[i-1]);
    ll Ans=Mul(2ll*b1[C],b2[C]);
    for(ll i=1;i<=C;i++)
    {
        for(ll j=2;;j++)
        {
            ll B=max((ll)((j+sqrt(1ll*j*j-4))/2*i+1),i+1);
            if(B>C) break;
            Ans=Add(Ans,Add(Mul(Dec(b1[i],b1[i-1]),Dec(b2[C],b2[B-1])),Mul(Dec(b1[C],b1[B-1]),Dec(b2[i],b2[i-1]))));
        }
    }
    printf("%lld",Ans);
    return 0;
}
