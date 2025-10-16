#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
#define lowbit(x) (x&(-x))
using namespace std;
const int N=8e6+10;

const int mod=998244353;
int fa[N];
int sum[N];
int dist[N];
int find(int x)
{
    if(fa[x]==x)
        return x;
    else {
        int tt=find(fa[x]);
        dist[x]+=dist[fa[x]];
        fa[x]=tt;
        return fa[x];
    }
}
void add(int x,int y)
{
    int xx=find(x);
    int yy=find(y);
    dist[xx]=sum[yy];
    fa[xx]=yy;
    sum[yy]+=sum[xx];
}
void solve()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    int ans=0;
    while(m--){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==0){
            add(x,y);
        }
        else {
            if(find(x)==find(y)){
                ans=ans*2+1;
            }
            else ans*=2;
            ans%=mod;
        }
    }
    cout << ans%mod <<endl;
}
signed main()
{
    IOS;
    int T=1;
    
    while(T--){
        solve();
    }
    return 0;
}


