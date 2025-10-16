#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;
const int z = 2507;
const ll inf = 1e16 + 7;
int n, m, s, t, 
	v[z];
ll dis[z];
struct node {
	ll w;
	int id;
};
bool operator<(node a, node b) {
	return a.w > b.w;
}
priority_queue<node> pq;
vector<node> vt[z];
void dij(int s) {
	for(int i = 1; i <= n; ++i)	dis[i] = inf;
	dis[s] = 0;
	pq.push((node){0, s});
	while(!pq.empty()) {
		node t = pq.top();
		pq.pop();
		int my = t.id, l = vt[my].size();
		if(v[my]) continue;
		v[my] = 1;
		for(int i = 0; i < l; ++i) {
			node s = vt[my][i];
			int sn = s.id, 
				sw = s.w;
			if(dis[sn] > dis[my] + sw) {
				dis[sn] = dis[my] + sw;
				pq.push((node){dis[sn], sn});
			}
		}
	}
}
int main(void) {
	cin >> n >> m >> s >> t;
	for(int i = 1, iu, iv, iw; i <= m; ++i) {
		cin >> iu >> iv >> iw;
		vt[iu].push_back((node){iw, iv});
		vt[iv].push_back((node){iw, iu});
	}	
	dij(s);
	cout << dis[t] << "\n";
}