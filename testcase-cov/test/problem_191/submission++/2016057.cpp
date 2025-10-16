#include <bits/stdc++.h>


using namespace std;

const int N = 1e5 + 10, M = 2e5 + 10;

int n, m, deg[N];
pair<int, int> eg[M];
vector<int> e1[N], e2[N];
int f[N], g[N];
int c1, c2, c3;

void calc() {
  queue<int> qf, qg;
  for (int i = 1; i <= n; i++) {

    for (auto j : e1[i]) {
      for (auto k : e1[j]) {
        if (!f[k]) qf.push(k);
        f[k]++;
      }
    }
    for (auto j : e2[i]) {
      for (auto k : e1[j]) {
        if (k == i) continue;
        if (!g[k]) qg.push(k);
        g[k]++;
      }
    }
    while (!qf.empty()) {
      int t = qf.front();
      qf.pop();
      c1 += f[t] * (f[t] - 1) / 2;
      if (g[t]) c2 += f[t] * g[t];

      f[t] = 0;
    }
    while (!qg.empty()) {
      int t = qg.front();
      qg.pop();
      c3 += g[t] * (g[t] - 1) / 2;

      g[t] = 0;
    }

  }
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> eg[i].first >> eg[i].second;
    deg[eg[i].first]++, deg[eg[i].second]++;
  }
  


  
  for (int i = 1; i <= m; i++) {
    int u = eg[i].first, v = eg[i].second;
    bool cmp = deg[u] < deg[v] || (deg[u] == deg[v] && u < v);
    
    if (cmp) e1[u].emplace_back(v), e2[v].emplace_back(u); 
    else e1[v].emplace_back(u), e2[u].emplace_back(v); 
  }
  
  calc();
  
  cout << c1 + c2 + c3 / 2;
  
  return 0;
}


























