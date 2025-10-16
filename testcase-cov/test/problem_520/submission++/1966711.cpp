#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5;
const ll inf=8e18;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,a[Maxn+5]; ll f[Maxn+5],Y[Maxn+5],tag;
inline ll sqr(int x) {return 1ll*x*x;}
int q[Maxn+5],head=1,tail=0;

inline double Slope(int p,int q)
{
    if(a[p]==a[q]) return (Y[p]<=Y[q]?inf:-inf);
    return 1.0*(Y[q]-Y[p])/(a[q]-a[p]);
}
inline void Insert(int i)
{
    Y[i]=f[i]+1ll*a[i]*a[i];
    while(head<tail && Slope(q[tail-1],q[tail])>=Slope(q[tail],i)) tail--;
    q[++tail]=i;
}
inline ll Get(int i)
{
    while(head<tail && Slope(q[head],q[head+1])<=2.0*a[i]) head++;
    int j=q[head]; return f[j]+tag+sqr(a[i]-a[j]);
}

int main()
{
    

    n=read(); For(i,1,n) a[i]=read(); sort(a+1,a+n+1);
    For(i,0,n) For(j,0,n) f[i]=inf; f[1]=sqr(a[2]-a[1]),Insert(1);
    For(i,3,n) f[i-1]=Get(i),tag+=sqr(a[i]-a[i-1]),f[i-1]-=tag,Insert(i-1);
    ll ans=inf;
    For(i,1,n-1) if(f[i]<inf) ans=min(ans,f[i]+tag+sqr(a[n]-a[i]));
    cout<<ans<<endl;
    return 0;
}