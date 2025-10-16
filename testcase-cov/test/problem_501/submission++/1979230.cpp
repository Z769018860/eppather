
#include <bits/stdc++.h>
#define rep(i, f, t) for(int i(f); i <= t; ++i)
#define re(i, t) for(int i(1); i <= t; ++i)
#define per(i, t, f) for(int i(t); i >= f; --i)
#define pe(i, t) for(int i(t); i >= 1; --i) 
#define nx(i, u) for(int i(head[u]); i; i = e[i].nxt)
typedef long long ll; 
using namespace std;
typedef pair <int, int> pii;
#define pb push_back
#define fi first
#define se second
#define ix(l, r) ((l + r) | (l != r)) 
#define ls (ix(l, mid))
#define rs (ix(mid + 1, r))
#define mp(i, j) (make_pair(i, j))

#define inf (int)(1e9+7)
#define INF 0x3f3f3f3f3f3f3f3f
namespace IO {
char buf[1 << 21], *p1 = buf, *p2 = buf, buf1[1 << 21];
inline char gc() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}
template<class I>
inline void read(I &x) {x = 0;I f = 1;char c = gc();while (c < '0' || c > '9') {if (c == '-') {f = -1;} c = gc();}while (c >= '0' && c <= '9') {x = x * 10 + c - '0';c = gc();}x *= f;}
template<class I>
inline void write(I x) {if (x == 0) {putchar('0');return;}I tmp = x > 0 ? x : -x;if (x < 0) {putchar('-');}int cnt = 0;while (tmp > 0) {buf1[cnt++] = tmp % 10 + '0';tmp /= 10;}while (cnt > 0)putchar(buf1[--cnt]);}
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')
} using namespace IO;
#define look_memory cerr<<abs(&sT-&eD)/1024.0/1024<<'\n'
int sT;    

ll n;
int a[30];

int main () {
	read(n); 
	rep(rt, 0, 60) {
		ll now = n >> rt;
		int len = 1;
		a[len] = 1;
		per(i, 60, 2) {
			ll w = (1ll << i) - 1;
			if(i == 6) continue;
			while(now % w == 0) {
				now /= w;
				a[++len] = i;
			}
		}
		if(now == 1) {
			int ans = rt;
			a[++len] = 1;
			re(i, len) ans += a[i];
			outn(ans);
			re(i, len) {
				re(j, a[i]) {
					if(i & 1) out(1);
					else out(3);
				}
				if(i == 1) {
					re(j, rt) out(2);
				}
			}
			exit(0);
		}
		if(now & 1) break;
	}
	puts("qnq");
}	