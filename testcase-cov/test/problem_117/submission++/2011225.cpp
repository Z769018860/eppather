#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
namespace Flow {
    int S,T,h[50006],cnt=1;
    struct QWQ{int v,w,c,nxt;} e[125005*2*2];
    void add(int u,int v,int w,int c=0) {
        e[++cnt]={v,w,c,h[u]},h[u]=cnt;
        e[++cnt]={u,0,-c,h[v]},h[v]=cnt;
    }
    void init(int s,int t,int fl=1) {S=s,T=t;if(fl) memset(h,0,sizeof(h)),cnt=1;}
    int d[50006],cur[50006];queue<int> q;
    bool bfs() {
        memset(d,0x3f,sizeof(d));memcpy(cur,h,sizeof(h));
        while(q.size()) {q.pop();}q.push(S);d[S]=0;
        while(q.size()) {
            int u=q.front();q.pop();
            for(int i=h[u];i;i=e[i].nxt) {
                int v=e[i].v,w=e[i].w;if(!w||d[v]<(int)1e18) continue;
                q.push(v);d[v]=d[u]+1;if(v==T) return 1;
            }
        }return 0;
    }
    int dfs(int u,int sum) {
        if(u==T) return sum;int res=0,k;
        for(int& i=cur[u];i;i=e[i].nxt) {
            int v=e[i].v,w=e[i].w;cur[u]=i;
            if(!w||d[v]!=d[u]+1) continue;
            k=dfs(v,min(sum,w)),e[i].w-=k,e[i^1].w+=k,sum-=k,res+=k;
            if(!sum) return res;
        }return res;
    }
    int Dinic() {
        int maxflow=0;
        while(bfs()) maxflow+=dfs(S,(int)2e18);
        return maxflow;
    }
}
int n,m,s,t,a[50006],l[125005];
signed main(){
    cin>>n>>m>>s>>t;
    Flow::init(n+1,n+2);
    for(int i=1,u,v,lw,rw;i<=m;i++) {
        u=rd(),v=rd(),lw=rd(),rw=rd();
        Flow::add(u,v,rw-lw);a[u]-=lw,a[v]+=lw,l[i]=lw;
    }
    int sum=0;
    for(int i=1;i<=n;i++) {
        if(a[i]>0) Flow::add(n+1,i,a[i]),sum+=a[i];
        if(a[i]<0) Flow::add(i,n+2,-a[i]);
    }
    Flow::add(t,s,(int)2e18);
    if(Flow::Dinic()!=sum) return puts("please go home to sleep"),0;
    int ret=Flow::e[Flow::cnt].w;
    Flow::init(t,s,0);
    Flow::e[Flow::cnt].w=Flow::e[Flow::cnt-1].w=0;
    cout<<ret-Flow::Dinic();
    return 0;
}