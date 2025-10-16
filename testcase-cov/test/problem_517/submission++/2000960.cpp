#include<bits/stdc++.h>
using namespace std;
#define N 205500
int read(){
    int x=0;char ch=getchar();
    while(ch>'9'||ch<'0')ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x;
}
#define ll long long
namespace Trie{
    int siz[N*31],cnt[N*31][31],num,rt,ch[N*31][2],lz[N*31],d[N*31],tag;
    
    
    void chg(int x,int k){
        lz[x]^=k;
        for(int i=0;i<30;i++)if((k>>i)&1)cnt[x][i]=siz[x]-cnt[x][i];
        if(d[x]>=0&&(k&(1<<d[x])))swap(ch[x][0],ch[x][1]);
    }
    void pushdown(int x){
        if(!lz[x])return ;
        if(!ch[x][0])ch[x][0]=++num,d[num]=d[x]-1;
        if(!ch[x][1])ch[x][1]=++num,d[num]=d[x]-1;
        chg(ch[x][0],lz[x]);chg(ch[x][1],lz[x]);
        lz[x]=0;
    }
    ll gsum(int x){
        ll res=0;pushdown(x);
        for(int i=0;i<30;i++){
            if((tag>>i)&1)res+=1ll*(siz[x]-cnt[x][i])*(1<<i);
            else res+=1ll*cnt[x][i]*(1<<i);
        }
        return res;
    }
    void insert(int &x,int dep,int k){
        if(!x)x=++num,d[x]=dep;
        pushdown(x);
        siz[x]++;for(int i=0;i<30;i++)cnt[x][i]+=(k>>i)&1;

        if(dep<0)return ;
        insert(ch[x][(k>>dep)&1],dep-1,k);
    }
    ll find(int x,int sur){
        if(d[x]==-1)return 1ll*gsum(x)*min(siz[x],sur)/siz[x];
        if(siz[x]<=sur)return gsum(x);
        if(!sur||!x)return 0;

        pushdown(x);

        if(siz[ch[x][0]]>=sur)return find(ch[x][0],sur);
        return find(ch[x][1],sur-siz[ch[x][0]])+gsum(ch[x][0]);
    }
}
namespace Array{
    int now,cnt[N][31],n,m,val[N],tag;
    void insert(int x){
        val[++now]=x^tag;
        for(int i=0;i<30;i++)cnt[now][i]=((val[now]>>i)&1)+cnt[now-1][i];
    }
    ll gsum(int x){
        ll res=0;
        for(int i=0;i<30;i++){
            if((tag>>i)&1)res+=1ll*(x-cnt[x][i])*(1<<i);
            else res+=1ll*cnt[x][i]*(1<<i);
        }
        return res;
    }
    void clear(){
        for(int i=1;i<=now;i++)val[i]^=tag,Trie::insert(Trie::rt,30,val[i]^Trie::tag);
        tag=now=0;
    }
}
void change(int k){
    Trie::tag^=k;
    Array::tag^=k;
}
void sorted(){
    Array::clear();Trie::chg(Trie::rt,Trie::tag);
    Trie::tag=0;
}
ll ask(int x){
    if(x>=Trie::siz[Trie::rt])return Trie::gsum(Trie::rt)+Array::gsum(x-Trie::siz[Trie::rt]);
    return Trie::find(1,x);
}
void add(int x){
    Array::insert(x);
}
ll find(int l,int r){

    return ask(r)-ask(l-1);
}
signed main(){
    int n=read();
    for(int i=1;i<=n;i++){
        add(read());
    }
    int m=read();
    while(m--){
        int opt=read();
        if(opt==1){
            add(read());
        }
        else if(opt==2){
            int l=read(),r=read();
            printf("%lld\n",find(l,r));
        }
        else if(opt==3){
            change(read());
        }
        else {
            sorted();
        }
    }
}