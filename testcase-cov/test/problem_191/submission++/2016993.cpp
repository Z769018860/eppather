
#ifdef dxx
#define dbg(...) fprintf(stderr,__VA_ARGS__)
#define dex(a) dbg(#a"=%lld onL%d infun %s\n",(ll)a,__LINE__,__FUNCTION__)
#include<cstdlib>
#define pause sys##tem("read -p \"panss2continue..\"")
#define _GLIBCXX_DEBUG
#endif

#include<cstdio>
#include<cstring>
#include<random>
#include<algorithm>

#define fi first
#define se second
const int NV=1e5;
using ll=long long;
using std::max;
using std::min;
template<class T> void cmax(T&a,T b){a=max(a,b);}
template<class T> void cmin(T&a,T b){a=min(a,b);}

std::mt19937 rnd(134678342);

namespace xm{
    std::vector<int> G[NV+5],G2[NV+5];
    int deg[NV+5],cnt[NV+5];
    void _(){
        int N,M;

        scanf("%d%d",&N,&M);
        for(int i=1;i<=M;++i){
            int s,t;
            scanf("%d%d",&s,&t);
            G[s].push_back(t);
            G[t].push_back(s);
            ++deg[s];
            ++deg[t];
        }
        for(int i=1;i<=N;++i)
        for(int t:G[i])
            if(deg[t]<deg[i]||deg[t]==deg[i]&&t<i)
                G2[i].push_back(t);
        ll ans=0;
        for(int i=1;i<=N;++i){
            for(int t:G2[i]) for(int v:G[t])
                if(deg[v]<deg[i]||deg[v]==deg[i]&&v<i)
                    ans+=cnt[v]++;
            for(int t:G2[i]) for(int v:G[t]) cnt[v]=0;
        }
        printf("%lld\n",ans);
    }
}

int main(){
    xm::_();
    return 0;
}
