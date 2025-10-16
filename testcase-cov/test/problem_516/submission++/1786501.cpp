#include <bits/stdc++.h>
#define int long long
#define FOR(a,b,c) for (int a=(b),_=(c);a<=_;++a)
#define REP(a,b,c) for (int a=(b),_=(c);a>=_;--a)
#define CLEAR(a,b) memset(a,b,sizeof(a))
using std::cin; using std::cout;
const int MaxN=1e5+10;
int n,m,a[MaxN],b[MaxN*3],k;
int p[MaxN],q[MaxN];
std::set <int> e[MaxN*3];
signed main()
{
    
    
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    std::cin>>n>>m;
    FOR(i,1,k=n) std::cin>>a[i],b[i]=a[i];
    FOR(i,1,m) std::cin>>p[i]>>q[i],b[++k]=p[i],b[++k]=q[i];

    std::sort(b+1,b+1+k); k=std::unique(b+1,b+1+k)-b-1;
    FOR(i,1,n) a[i]=std::lower_bound(b+1,b+1+k,a[i])-b;

    FOR(i,1,n) e[a[i]].insert(i);
    int ans=2147483647;
    for (int x,y,i=1;i<=m;++i)
    {
        x=std::lower_bound(b+1,b+1+k,p[i])-b;
        y=std::lower_bound(b+1,b+1+k,q[i])-b;
        if (ans==1){ std::cout<<ans<<'\n'; continue;}
        if (e[y].empty()) std::swap(e[x],e[y]);
        else
        {
            for (auto it:e[x])
            {
                e[y].insert(it);
            }
            e[x].clear();
            int last=-2147483647;
            for (auto it:e[y]) ans=std::min(ans,it-last),last=it;
        }
        std::cout<<ans<<'\n';
    }
    return 0;
}