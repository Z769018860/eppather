#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3f
#define N 1000005
using namespace std;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9')f=(ch=='-'?-1:f),ch=getchar();
    while(ch>='0' && ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
void write(ll x){
    if(x<0)x=-x,putchar('-');
    if(x/10)write(x/10);
    putchar(x%10+'0');
}
ll d[N];
ll e=1,head[N],nex[N],to[N],edg[N];
ll ans[N],cur[N],dep[N];
void add(ll u,ll v,ll w){
    to[++e]=v;nex[e]=head[u];head[u]=e;edg[e]=w;
    to[++e]=u;nex[e]=head[v];head[v]=e;
}
queue<ll> q;
ll opt;
ll dfs(ll x,ll res,ll T){
    if(x==T)return res;
    ll ans=0;
    for(ll i=cur[x];i && res;i=nex[i]){
        ll v=to[i];cur[x]=i;
        if(!edg[i] || dep[v]!=dep[x]+1)continue;
        ll k=dfs(v,min(res,edg[i]),T);
        edg[i]-=k;edg[i^1]+=k;res-=k;ans+=k;
        if(!k)dep[v]=inf;
    }
    return ans;
}
ll bfs(ll S,ll T){
    while(q.size())q.pop();cur[S]=head[S];q.push(S);
    for(ll i=1;i<=T+5;i++)dep[i]=inf;dep[S]=0;
    while(q.size()){
        ll u=q.front();q.pop();
        for(ll i=head[u];i;i=nex[i]){
            ll v=to[i];
            
            if(dep[v]!=inf || !edg[i])continue;
            dep[v]=dep[u]+1;q.push(v);cur[v]=head[v];
            
            if(v==T)return true;
        }
    }
    return false;
}
int main(){
    #ifdef EAST_CLOUD
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    #endif
    ll n=read(),m=read(),S=read(),T=read(),FS=n+1,FT=n+2,init=0;
    add(T,S,inf);
    for(ll i=1;i<=m;i++){
        ll u=read(),v=read(),a=read(),b=read();
        d[u]-=a;d[v]+=a;add(u,v,b-a);
    }
    for(ll i=1;i<=n;i++){
        if(d[i]>0)add(FS,i,d[i]),init+=d[i];
        else if(d[i]<0)add(i,FT,-d[i]);
    }
    ll maxflow=0;
    while(bfs(FS,FT))maxflow+=dfs(FS,inf,FT);
    if(maxflow<init){cout<<"please go home to sleep"<<endl;return 0;}
    maxflow=edg[3];edg[2]=edg[3]=0;
    while(bfs(T,S))maxflow-=dfs(T,inf,S);
    cout<<maxflow;
    return 0;
}