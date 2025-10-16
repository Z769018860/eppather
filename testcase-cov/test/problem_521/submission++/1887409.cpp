#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
template <typename T> inline void read(T &x){
	static char c = getchar(); static bool f = 0; x = 0;
	for (; c > 57 || c < 48; c = getchar()) f |= c == '-';
	for (; c >= 48 && c <= 57; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
	if (f) x = -x;
}
template <typename T, typename ...Args> inline void read(T &x, Args &...args){
	read(x), read(args...);
}

const int N = 5e5 + 5;
int n;                         
vector <int> e[N], g[N];
int ind[N], idx[N], ans[N], deg[N];
bool vis[N], calc[N];

void dfs(int u, int fa) {
	for (auto v : e[u]) if(v != fa) dfs(v, u), ind[u]++;	
}

void init_graph(int u, int pos){
	for (auto v : e[u]) if(v != pos) g[pos].emplace_back(v), deg[v]++;
}

void bfs()
{
	queue <int> q;
	for (int i = 1; i <= n; i++) if(!ind[i]) q.emplace(i);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		vis[u] = 1;
		for (auto v : e[u])if(!vis[v]){
			ind[v]--;
			if(!calc[u] && !calc[v]){
				init_graph(v, u), init_graph(u, v);
				calc[v] = calc[u] = 1;	
			}

			if(!ind[v]) q.emplace(v);
		}
	}
}

void Top()
{
	int num = 0;
	priority_queue<int, vector<int>, greater<int> > q;
	for (int i = 1; i <= n; i++) if(!deg[i]) q.emplace(i);
	while(!q.empty()){
		int u = q.top();
		q.pop();
		idx[u] = ++num;
		for (auto v : g[u]){
			deg[v]--;
			if(!deg[v]) q.emplace(v);
		}
	}
}

signed main()
{



	read(n);
	for (int i = 1, x, y; i < n; i++){
		read(x), read(y);
		e[x].emplace_back(y);
		e[y].emplace_back(x);		
	}

	dfs(1, 0);

	bfs();
	if((n & 1) && n != 1) {
		cout << "-1\n"; return 0;
	}
	if(n == 1) {
		cout << "-1\n"; return 0;
	}
	for (int i = 1; i <= n; i++) if(!calc[i]){
		cout << "-1\n"; return 0;
	}
	Top();
		
	for (int i = 1; i <= n; i++) ans[i] = i;
	sort (ans + 1, ans + 1 + n, [&] (int x, int y) { return idx[x] < idx[y];});
	
	for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
		
	return 0;
}