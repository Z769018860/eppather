#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=500;

int n; ll a[Maxn+5];
int mch[Maxn+5],vis[Maxn+5];
vector<int> v[Maxn+5];

inline int dfs(int x)
{
    if(vis[x]) return 0; vis[x]=1;
    for(auto y:v[x]) if(!mch[y] || dfs(mch[y]))
        return mch[x]=y,mch[y]=x,1;
    return 0;
}

int main()
{
    

    cin>>n; For(i,1,n) cin>>a[i];
    For(i,1,n) if(a[i]&1) For(j,1,n) if(!(a[j]&1))
        if(__gcd(a[i],a[j])==1 && __gcd(a[i]+1,a[j]+1)==1)
            v[i].push_back(j),v[j].push_back(i);
    int cnt=0;
    For(i,1,n) if(a[i]&1)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(i)) cnt++;
    }
    cout<<n-cnt<<endl;
    return 0;
}