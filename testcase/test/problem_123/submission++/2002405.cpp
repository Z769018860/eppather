#include <iostream>
#include <queue>
using namespace std;
#define inf 1e9
const int N = 2e5+10;
struct edge{int v,w;};
vector <edge>e[N];
priority_queue<pair<int,int>> q;
int n,m,d[N],vis[N];
long long int ans = 0;
bool prim(int s){
    int cnt=0;
    for(int i=0;i<=n;i++) d[i]=inf;
    d[s]=0; q.push({0,s});
    while(q.size()){
        int u = q.top().second;q.pop();
        if(vis[u]) continue;
        vis[u]=1;
        ans+=d[u],cnt++;
        for(auto ed:e[u]){
            int v =ed.v,w =ed.w;
            if(d[v]>w){
                d[v] =w;
                q.push({-d[v],v});
            }
        }
    }
    return cnt==n;
}
int main(){
    scanf("%d%d",&n,&m);
    while(m--){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        e[a].push_back({b,c});
        e[b].push_back({a,c});
    }
    if(prim(1)) printf("%lld\n",ans);
    else puts("orz");
    return 0;
}
