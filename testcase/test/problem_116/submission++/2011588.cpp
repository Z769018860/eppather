#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=55,M=1e5+5,inf=1e18;
struct node{
    int to,sm;
}p[M];
int idx=1,st,ed,dep[M],S,T,n,m,in[M],out[M],dbh[M],bh[M],ls[M],dys;
vector<int>e[M];
void add(int x,int y,int z){
    e[x].push_back(++idx);
    p[idx]=(node){y,z};
    e[y].push_back(++idx);
    p[idx]=(node){x,0};
}
deque<int>q;
bool bfs(){
    memset(dep,0,sizeof(dep));
    q.clear();
    q.push_back(st);
    dep[st]=1;
    while(q.size()){
        int x=q.front();
        q.pop_front();
        for(int i=0;i<e[x].size();i++){
            int v=e[x][i],c=p[v].to;
            if(dep[c]||!p[v].sm)continue;
            dep[c]=dep[x]+1;
            if(c==ed)return 1;
            q.push_back(c);
        }
    }
    return 0;
}
int dfs(int x,int sm){
    if(x==ed)return sm;
    int ans=sm,res=0;
    for(int i=0;i<e[x].size()&&ans;i++){
        int v=e[x][i],c=p[v].to;
        if(dep[c]==dep[x]+1&&p[v].sm){
            int k=dfs(c,min(ans,p[v].sm));
            if(!k)dep[c]=0;
            ans-=k;res+=k;
            p[v].sm-=k;p[v^1].sm+=k;
        }
    }
    return res;
}
int dinic(){
    int res=0;
    while(bfs())res+=dfs(st,inf);
    return res;
}
void add(int x,int y,int l,int r){
    add(x,y,r-l);
    in[y]+=l;out[x]+=l;
}
void init(){
    st=M-2,ed=M-1;
    add(T,S,inf);dys=idx;
    for(int i=0;i<M;i++){
        if(in[i]>out[i])add(st,i,in[i]-out[i]);
        if(in[i]<out[i])add(i,ed,out[i]-in[i]);
    }
}
int solve(){
    dinic();
    for(int i=0;i<e[st].size();i++){
        int v=e[st][i];
        if(p[v].sm)return 0;
    }
    st=S,ed=T;
    return 1;
}
signed main(){
    cin>>n>>m>>S>>T;
    for(int i=1;i<=m;i++){
        int x,y,l,r;
        cin>>x>>y>>l>>r;
        ls[i]=l;
        add(x,y,l,r);
        bh[i]=idx;
    }
    init();
    if(solve()){
        cout<<dinic();
    }else puts("please go home to sleep");
}