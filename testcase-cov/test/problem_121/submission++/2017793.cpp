#include <bits/stdc++.h>
#include <random>
using namespace std;
const int N=1e6+10;
int n,m;
mt19937 rnd(time(0));
pair<int,int> stk[N];
int fa[N],sz[N],top=0;
map<pair<int,int>,int > lstt;
struct Query{
  int t,op,u,v;
}q[N];
int find(int x){
  while(x^fa[x])x=fa[x];
  return x;
}
void merge(int x,int y){
  x=find(x),y=find(y);
  if(x==y)return;
  if(sz[x] > sz[y])swap(x,y);
  stk[++top] = make_pair(x,fa[x]);
  fa[x] = y;
}
struct ST{
  int l,r;
  vector<pair<int,int> > g;
}t[N<<2];
void build(int p,int l,int r){
  t[p].l = l, t[p].r=r;
  if(l==r)return;
  int mid = l+r>>1;
  build(p<<1,l,mid),build(p<<1|1,mid+1,r);
}
void insert(int p,int l,int r,pair<int,int> x){
  if(t[p].l>=l&&t[p].r<=r){t[p].g.push_back(x);return;}
  int mid = t[p].l + t[p].r >> 1;
  if(l<=mid)insert(p<<1,l,r,x);
  if(r>mid)insert(p<<1|1,l,r,x);
}
void dfs(int p,int l,int r){
  int cur = top;
  for(pair<int,int> x : t[p].g) merge(x.first,x.second);
  if(l==r){
    if(q[l].op == 2){
      if(find(q[l].u) == find(q[l].v))cout<<"Y\n";
      else cout <<"N\n";
    }
  }else{
    int mid = l+r>>1;
    dfs(p<<1,l,mid),dfs(p<<1|1,mid+1,r);
  }
  while(top!=cur)fa[stk[top].first] = stk[top].second,top--;
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
  cin >> n >> m;
  for(int i=1;i<=n;++i)fa[i] = i,sz[i] = rnd()>>1ll;
  build(1,1,m);
  for(int i=1;i<=m;++i){
    cin >> q[i].op >> q[i].u >> q[i].v,q[i].t=i;
    int u = q[i].u,v = q[i].v;
    if(u>v)swap(u,v);
    pair<int,int> c = make_pair(u,v);
    if(q[i].op == 0)
      lstt[c] = i;
    else if(q[i].op == 1){
      insert(1,lstt[c],i,c);
      lstt.erase(c);
    }
  }
  if(lstt.size())
    for(auto x : lstt)insert(1,x.second,m,x.first);
  dfs(1,1,m);
  return 0;
}