

#include <stdio.h>
#include <string.h>
#define oxis 10001
#define bian 200001
int hd[oxis], dt[bian], po[bian];		
int rs[bian], dep[oxis], ies[oxis];		
int t;

int min(int u, int v)
{
	return u < v ? u : v;
}

int dfs(int ni, int fl);			

int main()
{
	
	int i, n, m, s, stamp = 0;
	long long ans = 0ll;
	static int q[200001], stamps[oxis];
#define lc(i) ((i) << 1)
#define rc(i) (1 ^ lc(i))
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for(i = 1; i <= m; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		po[lc(i)] = hd[u];
		hd[u] = lc(i);
		dt[lc(i)] = v;
		rs[lc(i)] = w;
		po[rc(i)] = hd[v];
		hd[v] = rc(i);
		dt[rc(i)] = u;
		rs[rc(i)] = 0;
	}

	
	while (++stamp) {
		
		
		int qbegin = 0, qend = 1;
		dep[s] = 1;
		stamps[s] = stamp;
		q[0] = s;
		while (qbegin != qend) {
			int ni = q[qbegin++];
			int sin_dep = dep[ni] + 1;
			for (i = hd[ni]; i; i = po[i]) {
				int sin = dt[i];
				if (rs[i] &&	
						
						
						stamps[sin] != stamp) {
						
					stamps[sin]	= stamp;
					dep[sin]	= sin_dep;
					q[qend++]	= sin;
				}
			}
		}
		if (stamps[t] != stamp)		
			break;
		for (i = 1; i <= n; ++i)
			ies[i] = hd[i];		
		while ((i = dfs(s, 0x7fffffff)))
			ans += i;		
	}

	
	printf("%lld\n", ans);
	return 0;
}

int dfs(int ni, int fl)
{
	int *i = ies + ni;		
					
					
	int tg = dep[ni] + 1;		
	if (ni == t || fl == 0)
		return fl;		
	do {
		int sin = dt[*i], oppo;
		if (dep[sin] != tg || (oppo = dfs(sin, min(fl, rs[*i]))) <= 0)
			continue;
		rs[*i]		-= oppo;	
		rs[*i ^ 1]	+= oppo;	
		return oppo;
	} while ((*i = po[*i]));
	return 0;
}