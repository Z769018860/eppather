#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

int main()
{
    int n; cin>>n; cout<<n+1<<endl;
    if(n&1)
    {
        for(int i=n/2+2,j=i-1;i<=n+1 || j>=1;i++,j--)
        {
            if(j>=1) cout<<j<<' ';
            if(i<=n+1) cout<<i<<' ';
        } cout<<endl;
    }
    else
    {
        for(int i=n/2+1,j=i-1;i<=n+1 || j>=1;i++,j--)
        {
            if(i<=n+1) cout<<i<<' ';
            if(j>=1) cout<<j<<' ';
        } cout<<endl;
    }
    return 0;
}