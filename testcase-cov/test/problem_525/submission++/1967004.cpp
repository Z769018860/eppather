#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5;

int n,phi,a[Maxn+5];

int main()
{
    

    cin>>n; phi=n;
    if(n==1) {puts("-1"); return 0;}
    if(n==2) {printf("2\n0 1 1\n"); return 0;}
    for(int i=2,x=n;i<=x;++i) if(x%i==0)
    {
        phi=phi/i*(i-1);
        while(x%i==0) x/=i;
    }
    cout<<phi*2<<endl;
    For(i,0,phi*2-1) cout<<(i==phi?n-1:0)<<' '; cout<<1<<endl;
    return 0;
}