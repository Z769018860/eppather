#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2500;

int T,n,p; ll m,k;
int fac[55],inv[55],pw[55][55],g[105][205];
int a[55],f[Maxn+5][55],b[105],c[105];

int main()
{
    
    

    cin>>n>>p; fac[0]=inv[0]=1;
    For(i,0,n) cin>>a[i];
    For(i,1,p-1)
    {
        fac[i]=fac[i-1]*i%p;
        For(j,1,p-1) if(i*j%p==1) {inv[i]=inv[i-1]*j%p; break;}
    }
    For(i,0,p-1) {pw[i][0]=1; For(j,1,p) pw[i][j]=pw[i][j-1]*i%p;}
    f[0][0]=1;
    For(i,0,n) Rof(j,n*p,0) Rof(k,p-1,0) for(int l=1;l<=k && i*l<=j;++l)
        f[j][k]=(f[j][k]+f[j-i*l][k-l]*inv[l]*pw[a[i]][l])%p;
    For(i,0,n*p) For(j,0,p-1) f[i][j]=f[i][j]*fac[j]%p;
    cin>>T; while(T--)
    {
        cin>>m>>k; memset(g,0,sizeof(g)),g[0][0]=1;
        int s=0; while(m || k) b[++s]=m%p,c[s]=k%p,m/=p,k/=p;
        For(i,1,s) For(j,0,100) if(g[i-1][j])
            for(int k=(c[i]-j%p+p)%p;k<=n*p;k+=p)
            {
                int res=g[i-1][j]*f[k][b[i]]%p;
                g[i][(j+k)/p]=(g[i][(j+k)/p]+res)%p;
            }
        cout<<g[s][0]<<endl;
    }
    return 0;
}