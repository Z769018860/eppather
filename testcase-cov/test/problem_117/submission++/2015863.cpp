#include <bits/stdc++.h>
using namespace std;
long long n, m, S, T, SS, TT, ans;
long long s[100001], d[100001], st, ed;
vector<long long> v[100001], w[100001], an[100001], cost[100001];
bool vis[100001];
inline void ad(int x, int y, long long z) {
    an[x].push_back(v[y].size());
    an[y].push_back(v[x].size());
    v[x].push_back(y);
    v[y].push_back(x);
    w[x].push_back(z);
    w[y].push_back(0);
}
inline bool bfs() {
    queue<int> q;
    memset(s, 0, sizeof(long long) * (TT + 4));
    memset(d, 0, sizeof(long long) * (TT + 4));
q.push(st); d[st]=1;
while (!q.empty()){
int x=q.front(); q.pop();
for (int i=0;i<v[x].size();++i) if (w[x][i] && !d[v[x][i]]) d[v[x][i]]=d[x]+1,q.push(v[x][i]);
} return (!!d[ed]);
}
inline long long dinic(long long x,long long flow){
if (x==ed) return flow; long long owo=flow;
for (int i=s[x];owo && i<v[x].size();++i){
s[x]=i; int y=v[x][i]; long long z=w[x][i];
if (z && d[x]+1==d[y]){
long long k=dinic(y,min(z,owo));
if (!k) d[y]=0; w[x][i]-=k,w[y][an[x][i]]+=k,owo-=k;
}
}
return flow-owo;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> S >> T;
    SS = n + 1;
    TT = n + 2;

    for (int i = 1; i <= m; ++i) {
        int x, y, l, r;
        cin >> x >> y >> l >> r;
        ad(x, y, r - l);
        ad(SS, y, l);
        ad(x, TT, l);
    }

    st = SS;
    ed = TT;

    ad(T,S,1e9);

    while (bfs())
        while (long long now = dinic(st, 1e18));

    ans+=w[S].back();
    w[S].pop_back(); v[S].pop_back(); an[S].pop_back();
    w[T].pop_back(); v[T].pop_back(); an[T].pop_back();

    st = T;
    ed = S;

    while (bfs())
        while (long long now = dinic(st, 1e18))
            ans -= now;

    int tmp = 1;

    for (int i : w[SS])
        if (i)
            tmp = 0;

    for (int i = 1; i < TT; ++i)
        for (int j = 0; j < v[i].size(); ++j)
            if (v[i][j] == TT && w[i][j])
                tmp = 0;

    if (!tmp)
        cout << "please go home to sleep";
    else
        cout << ans;

    return 0;
}