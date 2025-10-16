#include <bits/stdc++.h>
typedef long long LL;
typedef unsigned long long ULL;
typedef std::pair<int, int> pii;
#define fi first
#define se second
#define MP std::make_pair
int read()
{
	int s = 0, f = 1;
	char c = getchar();
	while (!(c >= '0' && c <= '9'))
		f ^= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9')
		s = s * 10 + (c - '0'), c = getchar();
	return f ? s : -s; 
}
ULL readull()
{
	ULL s = 0;
	char c = getchar();
	while (!(c >= '0' && c <= '9')) c = getchar();
	while (c >= '0' && c <= '9')
		s = s * 10 + (c - '0'), c = getchar();
	return s; 
}
template<typename T>
void write(T x, char end = '\n')
{
	if (x == 0) return putchar('0'), putchar(end), void();
	if (x < 0) putchar('-'), x = -x;
	static int d[100], cur;
	for (cur = 0; x; x /= 10) d[++cur] = x % 10;
	for (int i = cur; i; i--) putchar('0' + d[i]);
	putchar(end);
}
const int MAXN = 1000005, MOD = 998244353, B = 101;
auto fplus = [](int x, int y){ return x + y >= MOD ? x + y - MOD : x + y; };
auto fminus = [](int x, int y){ return x >= y ? x - y : x + MOD - y; };
auto Fplus = [](int &x, int y){ return x = fplus(x, y); };
auto Fminus = [](int &x, int y){ return x = fminus(x, y); };
char s[MAXN];
int n, pw[MAXN], hsh[MAXN], lyd[MAXN][2];
int st[MAXN], tp = 0;
auto hash = [](int l, int r){ return fminus(hsh[r], (LL)hsh[l - 1] * pw[r - l + 1] % MOD); };
struct Node
{
    int l, r, p;
    Node(){}
    Node(int _l, int _r, int _p)
    : l(_l), r(_r), p(_p) {}
    bool operator==(const Node &a)
    { return l == a.l && r == a.r && p == a.p; }
} ;
int lcp(int i, int j)
{
    int l = 0, r = std::min(n - i + 1, n - j + 1);
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (hash(i, i + mid - 1) == hash(j, j + mid - 1))
            l = mid;
        else r = mid - 1;
    }
    return l;
}
int lcs(int i, int j)
{
    int l = 0, r = std::min(i, j);
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (hash(i - mid + 1, i) == hash(j - mid + 1, j)) 
            l = mid;
        else r = mid - 1;
    }
    return l;
}
bool cmp(int i, int j, bool inv)
{
    int l = lcp(i, j);
    if (i + l > n) return true;
    if (j + l > n) return false;
    return inv ? (s[i + l] > s[j + l]) : (s[i + l] < s[j + l]);
}
std::vector<Node> ans;
int main()
{
	scanf("%s", s + 1), n = strlen(s + 1);
    pw[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        pw[i] = (LL)pw[i - 1] * B % MOD;
        hsh[i] = ((LL)hsh[i - 1] * B + (s[i] - 'a' + 1)) % MOD;
    }
    for (int o = 0; o <= 1; o++)
    {
        st[tp = 0] = n + 1;
        for (int i = n; i; i--)
        {
            while (tp && cmp(i, st[tp], o)) tp--;
            lyd[i][o] = st[tp] - i, st[++tp] = i;
        }
        for (int l = 1; l <= n; l++)
        {
            if (lyd[l][o] == lyd[l][o ^ 1]) continue; 
            int r = l + lyd[l][o] - 1;
            int lenl = lcs(l - 1, r), lenr = lcp(l, r + 1);
            
            if (lenl + lenr >= lyd[l][o])
                ans.emplace_back(l - lenl, r + lenr, lyd[l][o]);
        }
    }
    std::sort(ans.begin(), ans.end(), [](Node x, Node y){
        return x.l == y.l ? x.r < y.r : x.l < y.l;
    });
    ans.resize(std::unique(ans.begin(), ans.end()) - ans.begin());
    write(ans.size());
    for (Node a : ans) write(a.l, ' '), write(a.r, ' '), write(a.p);
	return 0;
}