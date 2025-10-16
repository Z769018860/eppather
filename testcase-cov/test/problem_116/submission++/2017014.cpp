#include<bits/stdc++.h>
#define int long long
const int mod=19930726;
const int INF=0x3f3f3f3f;
using namespace std;
const int N=500,M=100010;
int n,m,S,T,s,t;
int h[N],e[M],f[M],ne[M],idx;
int d[N],cur[N],A[N];
void add(int a,int b,int c,int d){
    e[idx]=b,f[idx]=d-c,ne[idx]=h[a],h[a]=idx++;
    e[idx]=a,f[idx]=0,ne[idx]=h[b],h[b]=idx++;
}
bool bfs(){
    queue<int> q;
    memset(d,-1,sizeof d);
    d[S]=0,cur[S]=h[S];
    q.push(S);
    while(!q.empty()){
        auto u=q.front();
        q.pop();
        for(int i=h[u];~i;i=ne[i]){
            int v=e[i];
            if(d[v]==-1&&f[i]){
                d[v]=d[u]+1;
                cur[v]=h[v];
                if(v==T)return true;
                q.push(v);
            }
        }
    }
    return false;
}
int find(int u,int limit){
    if(u==T)return limit;
    int flow=0;
    for(int i=cur[u];~i&&flow<limit;i=ne[i]){
        cur[u]=i;
        int v=e[i];
        if(d[v]==d[u]+1&&f[i]){
            int t=find(v,min(f[i],limit-flow));
            if(!t)d[v]=-1;
            f[i]-=t,f[i^1]+=t,flow+=t;
        }
    }
    return flow;
}
int dinic(){
    int r=0,flow;
    while(bfs())while(flow=find(S,INF))r+=flow;
    return r;
}
void solve(){
    cin>>n>>m>>s>>t;
    memset(h,-1,sizeof h);
    S=0,T=n+1;
    while(m--){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        add(a,b,c,d);
        A[a]-=c,A[b]+=c;
    }
    int tot=0;
    for(int i=1;i<=n;i++){
        if(A[i]>0)add(S,i,0,A[i]),tot+=A[i];
        else add(i,T,0,-A[i]);
    }
    add(t,s,0,INF);
    if(dinic()!=tot){
        cout<<"please go home to sleep\n";
        return;
    }
    int res=f[idx-1];
    S=s,T=t;
    f[idx-2]=f[idx-1]=0;
    cout<<res+dinic()<<"\n";
}   
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int T=1;
    
    while(T--)solve();
    return 0;
}