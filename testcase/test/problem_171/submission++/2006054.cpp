
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> PII;
template <typename T> inline void read(T &x)
{
	x = 0; int f = 1; char ch;
	while((ch = getchar()) > '9' || ch < '0') if(ch == '-') f = -1;
	while(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ '0'),ch = getchar();
	x *= f;
}

const int N = 2e5 + 5;

class SAM
{
	public:
		int tr[N][26],fail[N],len[N],tot,last,a[N],t[N],mx[N];
		void init()
		{
			for(int i = 0;i <= tot;i++) for(int j = 0;j < 26;j++) tr[i][j] = 0;
			for(int i = 0;i <= tot;i++) len[i] = fail[i] = 0;
			tot = last = 1;
		}
		int ins(int x)
		{
			int u = ++tot,p = last;
			len[u] = len[last] + 1; last = u; mx[u] = 1e9;
			while(p && tr[p][x] == 0) tr[p][x] = u,p = fail[p];
			if(!p) fail[u] = 1;
			else
			{
				int q = tr[p][x];
				if(len[q] == len[p] + 1) fail[u] = q;
				else
				{
					int cq = ++tot;
					len[cq] = len[p] + 1; fail[cq] = fail[q];
					memcpy(tr[cq],tr[q],sizeof(tr[q]));
					fail[u] = fail[q] = cq;
					while(p && tr[p][x] == q) tr[p][x] = cq,p = fail[p];
				}
			}
			return u;
		}
		void build()
    {
      for(int i = 0;i <= tot;i++) a[i] = t[i] = 0;
      for(int i = 1;i <= tot;i++) t[len[i]]++;
      for(int i = 1;i <= tot;i++) t[i] += t[i - 1];
      for(int i = 1;i <= tot;i++) a[t[len[i]]--] = i;
    }
}sam;

int n,m,tmp[N];
string s[15];

int main()
{
	ios::sync_with_stdio(0);
	cin >> m;
	for(int i = 1;i <= m;i++) cin >> s[i];
	sam.init();
	n = s[1].length();
	for(int i = 0;i < n;i++) sam.ins(s[1][i] - 'a');
	sam.build();
	for(int i = 0;i <= sam.tot;i++) sam.mx[i] = 1e9;
	for(int i = 2;i <= m;i++)
	{
		int p = 1,len = 0; n = s[i].length();
		for(int j = 0;j <= sam.tot;j++) tmp[j] = 0;
		for(int j = 0;j < n;j++)
		{
			int x = s[i][j] - 'a';
			while(p && sam.tr[p][x] == 0) p = sam.fail[p],len = sam.len[p];
			if(p) p = sam.tr[p][x],++len;
			else p = 1,len = 0;
			tmp[p] = max(tmp[p],len);
		}
		for(int j = sam.tot;j;j--)
		{
			int u = sam.a[j],faz = sam.fail[u];
			tmp[faz] = max(tmp[faz],min(tmp[u],sam.len[faz]));
			sam.mx[u] = min(sam.mx[u],tmp[u]);
			tmp[u] = 0;
		}
		
	}
	int ret = 0;
	for(int i = 1;i <= sam.tot;i++) ret = max(ret,sam.mx[i]);
	
	if(m == 1) ret = n;
	cout << ret << "\n";
	return (0-0); 
}