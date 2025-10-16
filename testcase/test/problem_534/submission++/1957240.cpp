#include<bits/stdc++.h>
using namespace std;
const int N=15100;
vector<int>to[N<<2];
int dp[N<<2],ep[N];
int F[20][N],q,V,T;
int v[N],w[N],in[N<<2];
__inline void build(int p,int l,int r)
{
    if(l==r){ep[l]=p;return;}
    int mid=l+r>>1;
    dp[p<<1]=dp[p<<1|1]=dp[p]+1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
}
__inline void modi(int p,int l,int r,int L,int R,int i)
{
    if(L<=l&&r<=R)return to[p].push_back(i);
    int mid=l+r>>1;if(L<=mid)modi(p<<1,l,mid,L,R,i);
    if(R> mid)modi(p<<1|1,mid+1,r,L,R,i);
}
int ans=0;
__inline void ask(int l,int val)
{
    vector<int>awa;for(int u=ep[l];!in[u];u>>=1)awa.push_back(u);
    reverse(awa.begin(),awa.end());
    for(auto k:awa)
    {
        memcpy(F[dp[k]],F[dp[k]-1],sizeof F[0]);in[k]=1;
        for(auto i:to[k])
        {
            for(int j=V;j>=v[i];--j)
                if(F[dp[k]][j-v[i]]>=0)F[dp[k]][j]=max(F[dp[k]][j],F[dp[k]][j-v[i]]+w[i]);
            
        }
    }
    if(F[dp[ep[l]]][val]==-1)cout<<"0 0\n",ans=0;
    else cout<<"1 "<<F[dp[ep[l]]][val]<<"\n",ans=F[dp[ep[l]]][val]^1;
}
int main()
{
    memset(F,-1,sizeof F);
    F[0][0]=0;cin>>q>>V>>T;
    in[0]=1,dp[1]=1;build(1,1,q);
    for(int i=1;i<=q;++i)
    {
        int o,val,e;
        cin>>o;
        if(o==1)
        {
            cin>>v[i]>>w[i]>>e;
            v[i]-=T*ans,w[i]-=T*ans,e-=T*ans;
            modi(1,1,q,i,e,i);
        }
        else
        {
            cin>>val;val-=T*ans;
            ask(i,val);
        }
    }
}