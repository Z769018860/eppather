#include<bits/stdc++.h>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
typedef long long lol;
typedef pair<int, int> pii;
typedef unsigned int uin;

const int N (1e4 + 5), M (13);
int n, m;
char t[N];
int s[M * N], tot = 128;

int pos[N * M], sa[N * M], x[N * M], y[N * M], c[N * M], rk[N * M], h[N * M];

bool check (int x) 
{
	set<int> sec;
	for (int i (2); i <= n; ++ i ) 
		if (h[i] >= x) 
		{
			if (sec.empty()) sec.insert (pos[sa[i - 1]]);
			sec.insert (pos[sa[i]]);
			if ((int) sec.size() >= m) return true;
		}
		else 
			sec.clear();
	return false;
}

int main ()
{
	scanf ("%d", &m);
	for (int i (1); i <= m; ++ i ) 
	{
		scanf ("%s", t + 1);
		int len (strlen (t + 1));
		for (int j (1); j <= len; ++ j ) 
			s[ ++ n ] = t[j], pos[n] = i;
		s[ ++ n ] = ++ tot;
	}

	
	for (int i (1); i <= n; ++ i ) c[x[i] = s[i]] ++ ;
	for (int i (2); i <= tot; ++ i ) c[i] += c[i - 1];
	for (int i (n); i ; -- i ) sa[c[x[i]] -- ] = i;

	for (int k (1); k < n; k <<= 1 ) 
	{
		int cnt (0);
		for (int i (n - k + 1); i <= n; ++ i ) y[ ++ cnt ] = i;
		for (int i (1); i <= n; ++ i ) 
			if (sa[i] > k) 
				y[ ++ cnt ] = sa[i] - k;

		memset (c, 0, (tot + 1) << 2);
		for (int i (1); i <= n; ++ i ) c[x[i]] ++ ;
		for (int i (2); i <= tot; ++ i ) c[i] += c[i - 1];
		for (int i (n); i ; -- i ) sa[c[x[y[i]]] -- ] = y[i];
		swap (x, y);
		
		x[sa[1]] = tot = 1;
		for (int i (2); i <= n; ++ i ) x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && ((sa[i] + k > n && sa[i - 1] + k > n) || (sa[i] + k <= n && sa[i - 1] + k <= n && y[sa[i] + k] == y[sa[i - 1] + k]))) ? tot : ++ tot;
		if (tot == n) break;
	}
	
	
	for (int i (1); i <= n; ++ i ) rk[sa[i]] = i;
	for (int i (1), k (1); i <= n; ++ i ) 
	{
		if (rk[i] == 1) continue;
		if (k < i) k = i;
		int j (sa[rk[i] - 1]);
		while (k <= n && k - i + j <= n && s[k] == s[k - i + j]) k ++ ;
		h[rk[i]] = k - i;
	}
	
	int l (0), r (N - 1);
	while (l < r) 
	{
		int mid ((l + r + 1) >> 1);
		if (check (mid)) l = mid;
		else r = mid - 1;
	}
	printf ("%d", l);
	
	return 0;
}
