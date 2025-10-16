#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=500+5;
int n,ans,a[N],vis[N],matched[N];
vector<int>b[N];
inline bool Hungary(int x,int id){
    for (auto v:b[x]){
        if (vis[v]==id) continue;
        vis[v]=id;
        if (!matched[v] || Hungary(matched[v],id))
            return matched[v]=x,1;
    }
    return 0;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for (int i=1;i<=n;++i) cin>>a[i];
    for (int i=1;i<=n;++i)
        for (int j=1;j<=n;++j)
            if (__gcd(a[i],a[j])*__gcd(a[i]+1,a[j]+1)==1) b[i].push_back(j);
    for (int i=1;i<=n;++i)
        if (a[i]&1) ans+=Hungary(i,i);
    return cout<<n-ans<<'\n',0;
}