









#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ll long long
#define INF 0x3f3f3f3f
#define re register
#define il inline
#define gc getchar
inline int read()
{
	int f=1,k=0;
	char c = getchar();
	while (c <'0' || c > '9')
	{
		if (c=='-') f=-1;
		c=getchar();
	}
	while(c >= '0' && c <= '9')  k = (k << 1)+(k << 3)+(c^48),c=getchar();
	return k*f;
}
const int N = 2e5+5;
int n,m,deg[N];
vector<int> v[N],v1[N];
int cnt[N];
int main()
{	 
	cin >> n >> m;
	for (int i = 1;i <= m;i++)
	{
		int u =  read(),v = read();
		v1[u].push_back(v);v1[v].push_back(u);
		deg[u] ++ ,deg[v] ++;
	}
	for (int i = 1;i <= n;i++)
		for (int j : v1[i])
			if (deg[i] < deg[j] || (deg[i] == deg[j] && i < j)) v[i].push_back(j);
	int res = 0;
	for (int i = 1;i <= n;i++)
	{
		for (int j:v1[i])
			for (int k:v[j])
				if (deg[i] <deg[k] || (deg[i] == deg[k] && i < k))
					 res += cnt[k]++;
		for (int j:v1[i])
			for (int k:v[j]) cnt[k] = 0;
	}
	cout << res << endl;
	return 0;
}