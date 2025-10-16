#include<bits/stdc++.h>
using namespace std;
const int N0=105;
const int M0=405;
const int N=505;
const int M=81000;
const int inf=4000000;
int Tcnt,n,m;
int px[N0],py[N0],pr[N0],pw[N0];
int bx[M0],by[M0],bw[M0],bm[M0];
int maxn,S,T,ncnt,aim,mflow;
int to[M],nxt[M],head[N],c[M],ecnt;
bool ans,use[M0];
int dep[N],cur[N];
int read(){
    int t=0;
    char c=getchar();
    while(c<'0' || c>'9')
        c=getchar();
    while(c>='0' && c<='9'){
        t=(t<<1)+(t<<3)+(c^'0');
        c=getchar();
    }
    return t;
}
void init(){
    for(int i=1;i<=ncnt;i++)
        head[i]=0;
    ecnt=1;
    ans=1;
    ncnt=n-1;
    aim=mflow=0;
}
bool check(int ux,int uy,int ur,int vx,int vy){
    return (vx-ux)*(vx-ux)+(vy-uy)*(vy-uy)<=ur*ur;
}
void add(int u,int v,int w){
    to[++ecnt]=v;
    nxt[ecnt]=head[u];
    c[ecnt]=w;
    head[u]=ecnt;
}
void Add(int u,int v,int w){
    add(u,v,w);
    add(v,u,0);
}
bool bfs(){
    for(int i=1;i<=T;i++)
        dep[i]=0;
    dep[S]=1;
    queue<int> Q;
    Q.push(S);
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        for(int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(!dep[v] && c[i]){
                dep[v]=dep[u]+1;
                Q.push(v);
            }
        }
    }
    return dep[T];
}
int dinic(int u,int flow){
    if(u==T)
        return flow;
    int res=0;
    for(int &i=cur[u];i;i=nxt[i]){
        int v=to[i];
        if(dep[v]==dep[u]+1 && c[i]){
            int fv=dinic(v,min(flow,c[i]));
            flow-=fv;
            res+=fv;
            c[i]-=fv;
            c[i^1]+=fv;
            if(!flow)
                break;
        }
    }
    if(!res)
        dep[u]=0;
    return res;
}
int main(){
    
    
    Tcnt=read();
    while(Tcnt--){
        n=read();m=read();
        init();
        for(int i=1;i<=n;i++){
            px[i]=read();py[i]=read();
            pw[i]=read();pr[i]=read();
        }
        maxn=pw[1];
        for(int i=1;i<=m;i++){
            bx[i]=read();by[i]=read();
            bw[i]=read();
            if(check(px[1],py[1],pr[1],bx[i],by[i])){
                maxn+=bw[i];
                bw[i]=0;
            }
            bm[i]=++ncnt;
            use[i]=0;
        }
        S=++ncnt;T=++ncnt;
        for(int i=2;i<=n;i++){
            if(pw[i]>maxn){
                ans=0;
                goto here;
            }
            Add(S,i-1,maxn-pw[i]);
            for(int j=1;j<=m;j++){
                if(!bw[j])
                    continue;
                if(check(px[i],py[i],pr[i],bx[j],by[j])){
                    if(!use[j]){
                        aim+=bw[j];
                        use[j]=1;
                    }
                    Add(i-1,bm[j],inf);
                }
            }
        }
        for(int i=1;i<=m;i++){
            if(!bw[i] || !use[i])
                continue;
            Add(bm[i],T,bw[i]);
        }
        while(bfs()){
            for(int i=1;i<=T;i++)
                cur[i]=head[i];
            mflow+=dinic(S,inf);
        }
        if(mflow!=aim)
            ans=0;
        here:
        ans?printf("ZQC! ZQC!\n"):printf("qaq\n");
    }
    return 0;
}