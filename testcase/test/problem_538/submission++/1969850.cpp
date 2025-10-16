#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=3e5,B=80;
const ll inf=4e18;

int n,s[Maxn+5],m; ll a[Maxn+5],k;
ll mn,mnp,mx,mxp;

inline void Solve()
{
    cin>>a[0]>>a[1]>>k; mx=-inf*2,mxp=-1,mn=inf*2,mnp=-1;
    For(i,2,B)
    {
        __int128 res=(__int128)a[i-1]*k+a[i-2];
        if(res>=inf) a[i]=inf+i;
        else if(res<=-inf) a[i]=-inf-i;
        else a[i]=res;
    }
    For(i,1,n)
    {
        if(s[i]>B) {if(mnp==-1) mnp=s[i]; if(mxp==-1) mxp=s[i]; break;}
        int p=s[i];
        if(a[p]<mn) mn=a[p],mnp=p;
        if(a[p]>mx) mx=a[p],mxp=p;
    }
    
    if(a[B-1]==0 && a[B]==0)
    {
        For(i,1,n) if(s[i]>B)
        {
            if(mn>0) mnp=s[i]; if(mx<0) mxp=s[i];
            break;
        }
    }
    else {if(s[n]>B) {if(a[B]<0) mnp=s[n]; else mxp=s[n];}}
    cout<<mxp<<' '<<mnp<<endl;
}

int main()
{
    ios::sync_with_stdio(false);
    

    cin>>n; For(i,1,n) cin>>s[i]; cin>>m;
    while(m--) Solve();
    return 0;
}