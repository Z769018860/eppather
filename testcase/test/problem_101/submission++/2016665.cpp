#include<bits/stdc++.h>
using namespace std;
int n,m,s,t,u,v,c,cured[5050],hd[5050],ed[10500][3];
int dep[10500];
bool bfs() {
    static queue<int> qu;
    for (int i=1;i<=n;i++) dep[i]=-1;
    dep[s]=0;
    qu.push(s);
    while (qu.size()) {
        int x=qu.front();
        qu.pop();
        for (int i=hd[x];i;i=ed[i][1]) {
            if (ed[i][2]&&(dep[ed[i][0]]==-1)) {
                dep[ed[i][0]]=dep[x]+1;
                qu.push(ed[i][0]);
            }
        }
    }
    if (dep[t]==-1) return false;
    for (int i=1;i<=n;i++) cured[i]=hd[i];
    return true;
}
long long dinic(int x,long long cur) {
    if (x==t) return cur;
    if (!cur) return 0;
    long long res=0;
    for (int& i=cured[x];i;i=ed[i][1]) {
        if (ed[i][2]&&(dep[ed[i][0]]==dep[x]+1)) {
            long long tmp=dinic(ed[i][0],min(cur,1ll*ed[i][2]));
            ed[i][2]-=tmp;ed[i^1][2]+=tmp;cur-=tmp;res+=tmp;
        }
        if (!cur) break;
    }
    return res;
}
long long solve() {
    long long ans=0;
    while (bfs()) ans+=dinic(s,0x3f3f3f3f3f3f3f);
    return ans;
}
int main() {
    cin>>n>>m>>s>>t;
    for (int i=1;i<=m;i++) {
        cin>>u>>v>>c;
        ed[i*2][0]=v;ed[i*2][1]=hd[u];ed[i*2][2]=c;hd[u]=i*2;
        ed[i*2+1][0]=u;ed[i*2+1][1]=hd[v];ed[i*2+1][2]=0;hd[v]=i*2+1;
    }
    printf("%lld\n",solve());
    return 0;
}
