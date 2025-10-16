#include<bits/stdc++.h>
#include<bits/extc++.h>
#define pbds __gnu_pbds

using ll = long long;
using ld = long double;

namespace GTI
{
	char gc(void)
   	{
		const int S=1<<16;
		static char buf[S],*s=buf,*t=buf;
		if (s==t) t=buf+fread(s=buf,1,S,stdin);
		if (s==t) return EOF;
		return *s++;
	}
	ll gti(void)
   	{
		ll a=0,b=1,c=gc();
		for (;!isdigit(c);c=gc()) b^=(c=='-');
		for (;isdigit(c);c=gc()) a=a*10+c-'0';
		return b?a:-a;
	}
	int gts(char *s)
   	{
		int len=0,c=gc();
		for (;isspace(c);c=gc());
		for (;!isspace(c)&&c!=EOF;c=gc()) s[len++]=c;
		s[len]=0;
		return len;
	}
	int gtl(char *s)
   	{
		int len=0,c=gc();
		for (;isspace(c);c=gc());
		for (;c!='\n'&&c!=EOF;c=gc()) s[len++]=c;
		s[len]=0;
		return len;
	}
}
using GTI::gti;
using GTI::gts;
using GTI::gtl;

const int M = 19260817, N = 1e5 + 500;

using std::vector;
using std::set;

int fpw(ll a, int b)
{
	a %= M, b %= M - 1;
	if (b < 0) b += M - 1;
	int c = 1;
	for (; b; b >>= 1, a = 1ll * a * a % M)
		if (b & 1)
			c = 1ll * c * a % M;
	return c;
}

int calc(int len) { return len * (len + 1ll) / 2 % M; }
int mod(int val) { return val < 0 ? (val + M) : (val >= M ? (val - M) : val); }

struct cntOfVal
{
	int len,sum;
	set<int> locs;
	void init(int len)
	{
		this->len = len, sum = calc(len);
		locs.clear();
		locs.insert(0), locs.insert(len + 1);
	}
	void insert(int loc)
	{
		auto r = locs.lower_bound(loc), l = r;
		--l;
		sum = mod(sum - calc(*r - *l - 1));
		sum = mod(sum + calc(loc - *l - 1));
		sum = mod(sum + calc(*r - loc - 1));
		locs.insert(loc);
	}
	void remove(int loc)
	{
		auto r = locs.lower_bound(loc), l = r;
		++r, --l;
		sum = mod(sum - calc(loc - *l - 1));
		sum = mod(sum - calc(*r - loc - 1));
		sum = mod(sum + calc(*r - *l - 1));
		locs.erase(loc);
	}
};

using std::unordered_map;
struct ansOfVal
{
	unordered_map<int, cntOfVal> ques;
	int ans, tot, cnt0;
	void init(int n)
	{
		ans = tot = n, cnt0 = 0;
		ques.clear();
	}
	void ansdiv(int x)
	{
		if (x == 0) --cnt0;
		else ans = 1ll * ans * fpw(x, -1) % M;
	}
	void ansmul(int x)
	{
		if (x == 0) ++cnt0;
		else ans = 1ll * ans * x % M;
	}
	int getans_(void) { return cnt0 > 0 ? 0 : ans; }
	void insert(int idq, int loc, int len)
	{
		if (!ques.count(idq))
		{
			ques[idq].init(len);
			ansdiv(calc(len));
		}
		else ansdiv(ques[idq].sum);
		ques[idq].insert(loc);
		ansmul(ques[idq].sum);
	}
	void remove(int idq, int loc)
	{
		ansdiv(ques[idq].sum);
		ques[idq].remove(loc);
		ansmul(ques[idq].sum);
	}
	int getans(void) { return mod(tot - getans_()); }
};
unordered_map<int, ansOfVal> vals;

struct Queue
{
	int n, tot, sum;
	vector<int> ques[N];
	void init(int n, int *len)
	{
		this->n = n, tot = 1, sum = 0;
		for (int i = 1; i <= n; i++)
		{
			ques[i].resize(len[i]+1);
			tot = 1ll * calc(len[i]) % M * tot % M;
		}
	}
	void insert(int val, int idq, int loc)
	{
		ques[idq][loc] = val;
		if (!vals.count(val))
			vals[val].init(tot);
		sum = mod(sum - vals[val].getans());
		vals[val].insert(idq, loc, ques[idq].size() - 1);
		sum = mod(sum + vals[val].getans());
	}
	void remove(int idq, int loc)
	{
		int val = ques[idq][loc];
		sum = mod(sum - vals[val].getans());
		vals[val].remove(idq, loc);
		sum = mod(sum + vals[val].getans());
	}
}que;

int len[N];
int main(void)
{
	int n = gti(), m = gti();
	for (int i = 1; i <= n; i++)
		len[i] = gti();
	que.init(n, len);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= len[i]; j++)
		{
			int val = gti();
			que.insert(val, i, j);
		}
	printf("%d\n", mod(que.sum));
	for (int i = 1; i <= m; i++)
	{
		int x = gti(), y = gti(), z = gti();
		que.remove(x, y);
		que.insert(z, x, y);
		printf("%d\n", mod(que.sum));
	}
	return 0;
}
