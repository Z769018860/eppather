#include <bits/stdc++.h>
using namespace std;
namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
	void flush() {fwrite(obuf, 1, oS - obuf, stdout); oS = obuf;}
	void putc(char x) {*oS++ = x; if(oS == oT) flush();}
	template <class I> void read(I &x) {
		for(f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if(c == '-') f = -1;
		for(x = 0; c <= '9' && c >= '0'; c = gc()) x = (x << 1) + (x << 3) + (c & 15); x *= f;
	}
	template <class I> void print(I x) {
		if(!x) putc('0'); if(x < 0) putc('-'), x = -x;
		while(x) qu[++qr] = x % 10 + '0', x /= 10;
		while(qr) putc(qu[qr--]);
	}
	template <class I> void print(I x, char c) {print(x), putc(c);}
	struct Flusher_ {~Flusher_(){flush();}} io_flusher_;
}
using io :: read;
using io :: putc;
using io :: print;
#define ll long long
const int N = 1005;
int n, m, a[N][N], b[N][N], d1[N][N], d2[N][N], u1[N][N], u2[N][N], c[N];
vector <int> vec[N];
bool ir(int x, int y) {return x >= 1 && x <= n && y >= 1 && y <= m;}
void add(int x, int z) {for(; x <= n; x += x & -x) c[x] += z;}
int ask(int x) {int res = 0; for(; x; x -= x & -x) res += c[x]; return res;}
int ask(int l, int r) {return l > r ? 0 : ask(r) - ask(l - 1);}

int main() {
    read(n), read(m);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j < m; j++)
            read(a[i][j]);
    for(int i = 1; i < n; i++)
        for(int j = 1; j <= m; j++)
            read(b[i][j]);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            d1[i][j] = j, d2[i][j] = i;
    for(int i = 1; i <= n; i++)
        for(int j = m - 1; j >= 1; j--)
            if(a[i][j]) d1[i][j] = d1[i][j + 1];
    for(int i = n - 1; i >= 1; i--)
        for(int j = 1; j <= m; j++)
            if(b[i][j]) d2[i][j] = d2[i + 1][j];
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            u1[i][j] = j, u2[i][j] = i;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j < m; j++)
            if(a[i][j]) u1[i][j + 1] = u1[i][j];
    for(int i = 1; i < n; i++)
        for(int j = 1; j <= m; j++)
            if(b[i][j]) u2[i + 1][j] = u2[i][j];
    ll ans = 0;
    for(int t = 1; t <= n; t++) {
        int x = t, y = 1;
        for(int i = 1; i <= n; i++) vec[i].clear();
        for(int i = 0; ; i++) {
            if(!ir(x + i, y + i)) break;
            int l = max(u2[x + i][y + i], u1[x + i][y + i] - y + x), r = x + i;
            ans += ask(l, r), add(x + i, 1), vec[min(d2[x + i][y + i], d1[x + i][y + i] - y + x)].push_back(x + i);
            for(auto j : vec[x + i]) add(j, -1);
        }
    }
    for(int t = 2; t <= m; t++) {
        int x = 1, y = t;
        for(int i = 1; i <= n; i++) vec[i].clear();
        for(int i = 0; ; i++) {
            if(!ir(x + i, y + i)) break;
            int l = max(u2[x + i][y + i], u1[x + i][y + i] - y + x), r = x + i;
            ans += ask(l, r), add(x + i, 1), vec[min(d2[x + i][y + i], d1[x + i][y + i] - y + x)].push_back(x + i);
            for(auto j : vec[x + i]) add(j, -1);
        }
    }
    print(ans, '\n');
    return 0;
}