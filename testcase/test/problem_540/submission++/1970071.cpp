#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e6;

int n,m,f[505],g[505][505];

inline void Solve()
{
    Rof(i,500,0) if(n>=f[i])
    {
        For(a,m+1,m+i) For(b,m+1,m+i) if(a!=b) g[a][b]=1;
        m+=i,n-=f[i]; break;
    }
}

int main()
{
    
    

    For(i,3,500) f[i]=1ll*i*(i-1)*(i-2)/6;
    cin>>n; while(n) Solve();
    cout<<m<<endl;
    For(i,1,m)
    {
        For(j,i+1,m) putchar(g[i][j]+'0'),putchar(' ');
        putchar('\n');
    }
    return 0;
}