#include<bits/stdc++.h>
using namespace std;
#define for1(i,j,k) for (int i=j;i<=k;i++)
#define pb push_back
const int maxn=5e4+9;
const int inf=-1e9;
vector<vector<int>>f;
vector<int>a[maxn];
int n,m;
int w[maxn],v[maxn];
void dfs(int u,int par){
for (auto v1:a[u]){
for1(j,0,m-w[v1]){
f[v1][j+w[v1]]=f[u][j]+v[v1];
}
dfs(v1,u);
}
if (u!=par)for1(j,0,m)f[par][j]=max(f[par][j],f[u][j]);
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    
    cin>>n>>m;
    for1(i,1,n){
    int p;
    cin>>p;
    a[p].pb(i);
    }
    for1(i,1,n)cin>>w[i];
    for1(i,1,n)cin>>v[i];
    f.resize(n+1);
    for1(i,0,n)f[i].resize(m+1);
    for1(i,0,n)for1(j,0,m)f[i][j]=inf;
    f[0][0]=0;
    dfs(0,0);
    int ans=inf;
    for1(j,0,m)ans=max(ans,f[0][j]);
    cout<<ans;
}
