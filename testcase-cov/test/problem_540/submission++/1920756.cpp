










#include<bits/stdc++.h>
#define gc getchar
#define x first
#define y second
#define eb emplace_back
#define em emplace
#define rep(i, x, y) for(auto i = (x); i <= (y); i++)
#define all(x) (x).begin(), (x).end()
using std::min; using std::max;
typedef long long ll; typedef unsigned long long ull;

ll read() {
	ll x = 0; bool fh = 0; char ch = gc();
	while (!isdigit(ch)) {
		fh |= ch == '-';
		if (ch < 10) exit(9); 
		ch = gc();
	}
	while (isdigit(ch))
		x = x * 10 + (ch ^ 48), ch = gc();
	return fh ? -x : x;
}
namespace myspace {
	#ifdef local
	template<typename Typ1> void debug(Typ1 arg) {std::cerr << arg << "\n";}
	template<typename Typ1, typename ...Typ2> void debug(Typ1 arg, Typ2 ...args) {
		std::cerr << arg << " ", debug(args...);
	}
	template<typename InputIt> void debug(InputIt first, InputIt last) {
		for(; first != last; first++) std::cerr << *first << " ";
		std::cerr << std::endl;
	}
	#endif
	int writeln(ll arg) {return printf("%lld\n", arg);}
	template<typename ...Typ2> int writeln(ll arg, Typ2 ...args) {
		return printf("%lld ", arg), writeln(args...);
	}
	template<typename InputIt> int writeln(InputIt first, InputIt last) {
		if(first == last) return 0;
		printf("%lld", (ll)*(first++));
		for(; first != last; first++) printf(" %lld", (ll)*first);
		return puts("");
	}
	typedef std::pair<int, int> pii;
	const char YES[] = "YES", NO[] = "NO";
	
	
	
	
	constexpr int DUST = 327, N = 514;
	bool G[N][N];
	int idx = 0;
	void solve1(int &n) {
		if(!n) return;
		idx += 2;
		int u = idx - 1, v = idx;
		G[u][v] = 1;
		while(n--) {
			idx++;
			G[u][idx] = G[v][idx] = 1;
			u++, v++;
		}
	}
	void solve3(int &n) {
		int x;
		for(x = 4; ; x++) if(x * (x - 1) * (x - 2) / 6 > n) break;
		x--;
	n -= x * (x - 1) * (x - 2) / 6;
		idx = x;
		rep(i, 1, x) rep(j, i + 1, x) G[i][j] = 1;
	}
	void solve2(int &n) {
		if(!n) return;
		int x;
		for(x = 3; ; x++) if(x * (x - 1) / 2 > n) break;
		x--;
	n -= x * (x - 1) / 2;
		idx++;
		rep(i, 1, x) G[i][idx] = 1;
	}
	void output() {
		assert(idx <= 500);
		writeln(idx);
		rep(i, 1, idx) {
			rep(j, i + 1, idx) printf("%d ", G[i][j]);
			puts("");
		}
	}
	bool major(int Case = 1) {
		int n = read();
		solve3(n);
		solve2(n);
		solve1(n);
		output();
		return Case ^= Case ^ Case;
	}
	void initial_function(signed argc, char **argv) {
		**argv = argc; 
	}
}
using myspace::DUST;
signed main(signed argc, char **argv) {
	myspace::initial_function(argc, argv);
	int Case = 1, Maxcase = 1;
	for(
#ifdef multiple_testcase
		Maxcase = read()
#endif
				     	;
#ifndef infinite_testcase
						  Case <= Maxcase
#endif
				     					 ; Case++)
#ifdef output_Yes_No
		puts(myspace::major(Case) ? YES : NO);
#else
		myspace::major(Case);
#endif
	return DUST ^ 0x147;
}