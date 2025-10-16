







#include <bits/stdc++.h>
using namespace std;









#ifdef LOCAL_TEST
bool __mem_begin;
#endif
#define int long long
#define mid ((l + r) >> 1)
#ifndef LOCAL_TEST
#define endl '\n'
#endif
#ifdef SEGMENT_TREE
#define lson (p << 1)
#define rson (p << 1 | 1)
#endif
#ifdef NETWORK_FLOW
#define rev(p) (p ^ 1)
#endif

const int MAXN = 1e5 + 5;
int n, a[MAXN];

void work() {
	cin >> n; n++;
	int c = 0, l = 1, r = n;
	while (l <= r) {
		a[++c] = r--;
		if (l <= r) a[++c] = l++;
	}
	reverse(a + 1, a + 1 + c);
	cout << c << endl;
	for (int i = 1; i <= c; ++i) cout << a[i] << ' ';
}

#ifdef LOCAL_TEST
bool __mem_end;
#endif

signed main(void) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	srand(time(nullptr));
#ifdef LOCAL_TEST
	auto __time_begin = clock();
#endif
#ifdef FILE_IO
#ifndef LOCAL_TEST
	freopen(".in", "r", stdin);
	freopen(".out", "w", stdout);
#endif
#endif
#ifdef MULTI_TESTS
	int T = 1; cin >> T; T--;
	while (T--) work();
#endif
	work();
#ifdef LOCAL_TEST
	auto __time_end = clock();
	cerr << "Time: " << __time_end - __time_begin << "ms" << endl;
	cerr << "Memory: " << (&__mem_end - &__mem_begin) / 1024 << "KiB" << endl;
#endif
	return 0;
}