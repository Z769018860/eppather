

#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<map>

#ifdef fio
void IO(){
    freopen("2.in","r",stdin);
    freopen("2.out","w",stdout);
}
#else
void IO(){return;}
#endif


#define For(i,l,r) for(int i=(l);i<=(r);++i)
#define rof(i,r,l) for(int i=(r);i>=(l);--i)
#define ckmax(a,b) a=max(a,b)
#define ckmin(a,b) a=min(a,b)
#define pii pair<int,int>

using namespace std;

const int N=2e6+10;
struct dsu{
    int f[N],siz[N];
    vector<pii> s;
    inline void init(int n){
        For(i,1,n){
            f[i]=i;
            siz[i]=1;
        }
    }
    inline int get_f(int t){
        while(f[t]!=t)t=f[t];
        return t;
    }
    inline void merge(int x,int y){
        x=get_f(x);
        y=get_f(y);
        if(x==y)return;
        if(siz[x]>siz[y])swap(x,y);
        s.push_back({x,siz[x]});
        f[x]=y;
        siz[y]+=siz[x];
    }
    inline bool together(int x,int y){
        return get_f(x)==get_f(y);
    }
    inline void goback(int sz){
        while(s.size()>sz){
            siz[f[s.back().first]]-=s.back().second;
            f[s.back().first]=s.back().first;
            s.pop_back();
        }
    }
    inline int size(){
        return s.size();
    }
}T;
int l[N<<2],r[N<<2];
vector<pii> upd[N<<2];
pii ask[N];
int ans[N];
void build(int t,int from,int to){
    int mid=(from+to)>>1;
    l[t]=from;r[t]=to;
    if(from==to)return;
    build(t*2,from,mid);
    build(t*2+1,mid+1,to);
}
void insert(int t,int from,int to,pii k){
    int mid=r[t*2];
    if(l[t]==from&&r[t]==to){
        upd[t].push_back(k);
        return;
    }
    if(to<=mid)insert(t*2,from,to,k);
    else if(from>mid)insert(t*2+1,from,to,k);
    else{
        insert(t*2,from,mid,k);
        insert(t*2+1,mid+1,to,k);
    }
}
void solve(int t){
    int tmp=T.size();
    for(auto [x,y]:upd[t])
        T.merge(x,y);
    if(l[t]==r[t]){
        if(ask[l[t]].first){
            if(T.together(ask[l[t]].first,ask[l[t]].second)){
                cout<<"Y"<<endl;
            }
            else cout<<"N"<<endl;
        }
    }
    else{
        solve(t*2);
        solve(t*2+1);
    }
    T.goback(tmp);
}
int n,m;
map<pii,int> ed;
signed main(){
    IO();
    ios::sync_with_stdio(NULL);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    T.init(n);
    build(1,1,m);
    For(i,1,m){
        int op,x,y;
        cin>>op>>x>>y;
        if(x>y)swap(x,y);
        if(op==0){
            ed[{x,y}]=i;
        }
        else if(op==1){
            insert(1,ed[{x,y}],i-1,{x,y});
            ed[{x,y}]=0;
        }
        else{
            ask[i]={x,y};
        }
    }
    for(auto [i,lst]:ed)
        if(lst)
            insert(1,lst,m,i);
    solve(1);
    return 0;
}