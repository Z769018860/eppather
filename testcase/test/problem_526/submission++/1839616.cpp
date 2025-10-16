#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e3 + 5;
int a[maxn];
int b[maxn];
int c[maxn];
int d[maxn];
int vis[maxn];
int gcd(int x,int y) {
    if(y == 0) return x;
    return gcd(y,x % y);
}
int p[maxn][maxn];
int cnt = 0,cnt1 = 0;
bool dfs(int u) {
    for(int i = 1;i <= cnt1;i++) {
        int i1 = c[i];
        if(p[u][i1] == 1 && vis[i1] == 0) {
            vis[i1] = 1;
            if(!d[i1] || dfs(d[i1])) {
                d[i1] = u;
                return true;
            }
        }
    }
    return false;
}
signed main() {
    int n;
    cin>>n;
    for(int i = 1;i <= n;i++) {
        cin>>a[i];
        if(a[i] % 2 == 0) {
            b[++cnt] = i;
        } else {
            c[++cnt1] = i;
        }
    }
    for(int i = 1;i <= cnt;i++) {
        for(int j = 1;j <= cnt1;j++) {
            int i1 = b[i];
            int j1 = c[j];
            
            if(gcd(a[i1],a[j1]) * gcd(a[i1] + 1,a[j1] + 1) == 1) {
                p[i1][j1] = 1;
                
            }
        }
    }
    int ans = 0;
    for(int i = 1;i <= cnt;i++) {
        int i1 = b[i];
        memset(vis,0,sizeof(vis));
        if(dfs(i1)) ans++;
    }
    cout<<n - ans<<endl;
    return 0;
}