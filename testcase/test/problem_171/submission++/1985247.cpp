#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <array>
#include <queue>
#include <memory.h>
#include <tuple>
#include <set>
#include <unordered_set>
#include <bitset>
#include <chrono>
#include <assert.h>
#include <numeric>
#include <functional>
using namespace std;
using ll = long long;
using ull = unsigned long long;
namespace SuffixArray {
	vector<int> rk, sa, cnt, height, oldrk, px, id;
	void BuildSA(string s) {
		function<bool(int , int , int)> Comp = [&](int x , int y , int w) {
			return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
		};
		int n = s.length(), m = 300;
		rk.clear(), sa.clear(), cnt.clear(), height.clear(), oldrk.clear(), px.clear(), id.clear();
		oldrk.resize(max(m + 1, 2 * n + 1));
		sa.resize(max(m + 1, n + 1));
		rk.resize(max(m + 1, n + 1));
		cnt.resize(max(m + 1, n + 1));
		height.resize(max(m + 1, n + 1));
		px.resize(max(m + 1, n + 1));
		id.resize(max(m + 1, n + 1));
		
		for (int i = 1; i <= n; ++i)
			++cnt[rk[i] = s[i]];
		for (int i = 1; i <= m; ++i)
			cnt[i] += cnt[i - 1];
		for (int i = n; i >= 1; --i)
			sa[cnt[rk[i]]--] = i;
		for (int w = 1, p;; w <<= 1, m = p) {
			p = 0;
			for (int i = n; i > n - w; --i)
				id[++p] = i;
			for (int i = 1; i <= n; ++i)
				if (sa[i] > w)
					id[++p] = sa[i] - w;
			fill(cnt.begin(), cnt.end(), 0);
			for (int i = 1; i <= n; ++i)
				++cnt[px[i] = rk[id[i]]];
			for (int i = 1; i <= m; ++i)
				cnt[i] += cnt[i - 1];
			for (int i = n; i >= 1; --i)
				sa[cnt[px[i]]--] = id[i];
			copy(rk.begin(), rk.end(), oldrk.begin());
			p = 0;
			for (int i = 1; i <= n; ++i)
				rk[sa[i]] = Comp(sa[i], sa[i - 1], w) ? p : ++p;
			if (p == n) {
				for (int i = 1; i <= n; ++i)
					sa[rk[i]] = i;
				break;
			}
		}
		for (int i = 1, k = 0; i <= n; ++i) {
			if (rk[i] == 0)
				continue;
			if (k)
				--k;
			while (s[i + k] == s[sa[rk[i] - 1] + k])
				++k;
			height[rk[i]] = k;
		}
	}
}
void solve() {
	int t;
	cin >> t;
	vector<string> vec(t);
	for(auto &it : vec) cin >> it;
	string s;
	int n = 0 , m = vec.size();
	vector<int> end{1};
	const char SC = '|';
	for(auto &it : vec) {
		s += SC;
		s += it;
		n += it.size() + 1;
		end.emplace_back(n - 1);
	}
	using namespace SuffixArray;
	BuildSA(s);
	vector<int> cnt(m + 1 , 0);
	auto add = [&](int pos) {
		int v = lower_bound(end.begin() + 1 , end.end() , pos) - end.begin();
		++cnt[v];
	};
	auto del = [&](int pos) {
		int v = lower_bound(end.begin() + 1 , end.end() , pos) - end.begin();
		--cnt[v];
	};
	multiset<int> S;
	int ans = 0;
	int j = 2;
	for(int i = 2 ; i <= n ; ++i) {
		if(sa[i] == SC) continue;
		while(j <= n && *min_element(cnt.begin() + 1 , cnt.end()) == 0) {
			if(sa[j] == SC) {
				++j;
				continue;
			}
			S.insert(height[j]);
			add(sa[j]);
			++j;
		}
		int v = *min_element(cnt.begin() + 1 , cnt.end());
		S.erase(S.find(height[i]));
		assert(v >= 0);
		if(v > 0) {
			ans = max(ans , *S.begin());
		}
		del(sa[i]);
	}
	cout << ans << '\n';
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}