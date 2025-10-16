#include<bits/stdc++.h>

using namespace std;

#define Reimu inline void 
#define Marisa inline int 
#define Sanae inline bool 
#define Reisen inline LL  

typedef long long LL;
typedef unsigned long long ULL;
typedef __int128 Suika;

inline ostream &operator<<(ostream &cout, Suika x) {
	static const LL LIM = 1e18;
	if (x < 0) cout << '-', x = -x;
	return x < LIM ? cout << LL(x) : cout << LL(x / LIM) << setw(18) << setfill('0') << LL(x % LIM);
}

typedef pair<int, int> Pii;
typedef tuple<int, int, int> Tiii;
#define fi first
#define se second

#define ALL(vec) vec.begin(), vec.end()
#define TY(type) const type&

#define BT(func) __builtin_##func
#define BTL(func) __builtin_##func##ll

template<typename Ty>
Reimu clear(Ty &x) { Ty().swap(x); }

const int N = 100010;

int n, K, __;
int a[N], _[N * 3], X[N], Y[N];
set<int> S[N * 3];

Marisa get(int x) { return lower_bound(_ + 1, _ + __ + 1, x) - _; }

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> K;
	for (int i = 1; i <= n; ++i) cin >> a[i], _[++__] = a[i];
	for (int i = 1; i <= K; ++i) cin >> X[i] >> Y[i], _[++__] = X[i], _[++__] = Y[i];
	sort(_ + 1, _ + __ + 1); __ = unique(_ + 1, _ + __ + 1) - _ - 1;
	int ans = INT_MAX;
	for (int i = 1; i <= n; ++i) {
		auto &s = S[get(a[i])];
		if (!s.empty()) ans = min(ans, i - *s.rbegin());
		s.emplace(i);
	}
	for (int i = 1; i <= K; ++i) {
		auto &s1 = S[get(X[i])], &s2 = S[get(Y[i])];
		if (s1.size() > s2.size()) s2.swap(s1);
		for (int x: s1) {
			auto it = s2.emplace(x).fi;
			if (it != s2.begin()) ans = min(ans, *it - *prev(it));
			if (next(it) != s2.end()) ans = min(ans, *next(it) - *it);
		}
		s1.clear();
		cout << ans << '\n';
	}
	return 0;
}