#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
const int N=1e2+9;
const int M=5e2+9;
const int K=13;
const int INF=0x3f3f3f3f;
const int S=1024;
template<typename T>inline void read(T &x){
	x=0;T f=1;char ch=getchar();
	while(ch<48||ch>57){if(ch=='-'){f=-1;}ch=getchar();}
	while(ch>=48&&ch<=57){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
int n,m,k,h[N],e[M*2],w[M*2],ne[M*2],idx,f[S][N],s[K];
priority_queue<pair<int,int> > q;
void add(int a,int b,int c){
    e[idx]=b;
    w[idx]=c;
    ne[idx]=h[a];
    h[a]=idx++;
}
void dijkstra(int A){
    for(int i=1;i<=n;i++){
        q.push({-f[A][i],i});
    }
    while(q.size()){
        int u=q.top().second;
        q.pop();
        for(int i=h[u];~i;i=ne[i]){
            int v=e[i];
            int wc=w[i];
            if(f[A][v]>f[A][u]+wc){
                f[A][v]=f[A][u]+wc;
                q.push({-f[A][v],v});
            }
        }
    }
    while(q.size()&&-q.top().first>f[A][q.top().second]) q.pop();
}
int main(){
    memset(h,-1,sizeof h);
    read(n),read(m),read(k);
    for(int i=1;i<=m;i++){
        int u,v,wc;
        read(u),read(v),read(wc);
        add(u,v,wc);
        add(v,u,wc);
    }
    int TOT=(1<<k);
    for(int S=1;S<TOT;++S){
        for(int i=1;i<=n;i++){
            f[S][i]=INF;
        }
    }
    for(int i=0;i<k;i++){
        read(s[i]);
        f[1<<i][s[i]]=0;
    }
    for(int S=1;S<TOT;S++){
        for(int i=1;i<=n;i++){
            for(int A=(S-1)&S;A;A=(A-1)&S){
                f[S][i]=min(f[S][i],f[A][i]+f[S^A][i]);
            }
        }
        dijkstra(S);
    }
    int ans=INF;
    for(int i=1;i<=n;i++){
        ans=min(ans,f[TOT-1][i]);
    }
    printf("%d",ans);
    return 0;
}