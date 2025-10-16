#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef struct node
{
    int pos;
    int dis;
    bool operator<(const node &x) const
    {
        return x.dis < dis;
    }
} node;
typedef struct edge
{
    int v, w;
} edge;
vector<edge> connects[200001];
bool vis[200001];
int dist[200001];
const int INF = 1e18;
void init(int n)
{
    for (int i = 1; i <= n; i++)
    {
        dist[i] = INF;
        vis[i] = false;
    }
}
void prim(int n)
{
    dist[1] = 0;
    priority_queue<node> q;
    q.push({1, dist[1]});
    while (!q.empty())
    {
        int top = q.top().pos;
        q.pop();
        vis[top] = 1;
        for (auto &p : connects[top])
        {
            int v = p.v;
            int w = p.w;
            if (vis[v])
                continue;
            if (dist[v] > w)
            {
                dist[v] = w;
                q.push({v, dist[v]});
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += dist[i];
    }
    if (ans >= INF)
    {
        cout << "orz" << endl;
    }
    else
        cout << ans << endl;
}
signed main()
{
    int n, m;
    cin >> n >> m;
    init(n);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        connects[u].push_back({v, w});
        connects[v].push_back({u, w});
    }
    prim(n);
    system("pause");
    return 0;
}