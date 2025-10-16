#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e7,Mod=311021;

int prm[Maxn+5],tot,phi[Maxn+5]; bool vis[Maxn+5];
int q,ans[Maxn+5],pw[Maxn+5]; short w[Maxn+5];

inline void Prime()
{
    phi[1]=1; For(i,2,Maxn)
    {
        if(!vis[i]) prm[++tot]=i,phi[i]=i-1,w[i]=1;
        for(int j=1;j<=tot && i*prm[j]<=Maxn;++j)
        {
            vis[i*prm[j]]=1;
            if(i%prm[j]==0)
            {
                phi[i*prm[j]]=phi[i]*prm[j];
                w[i*prm[j]]=w[i]; break;
            }
            phi[i*prm[j]]=phi[i]*(prm[j]-1),w[i*prm[j]]=w[i]+1;
        }
    }
    pw[0]=1; For(i,1,Maxn) pw[i]=pw[i-1]*2%Mod;
}

int main()
{
    

    Prime(),ans[1]=1,ans[2]=1; cin>>q;
    For(i,3,Maxn)
    {
        int res=phi[i]-pw[w[i]-(i%2==0)+(i%4==0)+(i%8==0)];
        ans[i]=pw[res/2];
    }
    For(i,1,Maxn) ans[i]=(ans[i]+ans[i-1])%Mod;
    while(q--)
    {
        int l,r; cin>>l>>r;
        int all=(ans[r]-ans[l-1]+Mod)%Mod;
        printf("%d\n",all);
    }
    return 0;
}