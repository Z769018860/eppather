#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <deque>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <tuple>
using namespace std;
#define int long long
#define P pair
#define pi P<int,int>
#define ff first
#define ss second
#define mp make_pair
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define V vector
#define vi V<int>
#define v2i V<vi>
#define v3i V<v2i>
#define vpi V<pi>
#define vsi V<si>
#define vb V<bool>
#define v2b V<vb>
#define pb push_back
#define S set
#define MS multiset
#define si S<int>
#define msi MS<int>
#define ins insert
#define era erase
#define M map
#define mii M<int,int>
#define Q queue
#define PQ priority_queue
#define qi Q<int>
#define qpi Q<pi>
#define pqi PQ<int>
#define rpqi PQ<int,vi,greater<int> >
#define pqpi PQ<pi>
#define rpqpi PQ<pi,vpi,greater<pi> >
const int MOD=998244353;
const int INF=922337203685477580;

int t;
int n, k;
vi arr;
vi st;
vi ed;

bool solve1() {
	int cs = 0;
	v2i un(k);
	for (int i = 0; i < k; i++) un[i].pb(st[i]);
	for (int i = 0; i < n; i++) {
		if (arr[i]) continue;
		if (cs == k-1) {
			un[k-1].pb(i); continue;
		}
		if (i < st[cs+1]-1) {
			un[cs].pb(i); continue;
		}
		if (sz(un[cs])%k == k-2) {
			un[cs].pb(i); cs++; continue;
		}
		un[cs].pb(i);
	}
	for (int i = 0; i < k; i++) {
		un[i].pb(ed[i]);
	}
	for (auto i: un) {
		if (sz(i)%k) return 0;
		if (!is_sorted(all(i))) return 0;
	}
	cout << "Yes\n" << k << "\n";
	for (auto i : un) {
		cout << sz(i) << " ";
		for (auto j : i) cout << j+1 << " ";
		cout << "\n";
	}
	return 1;
}

bool solve2() {
	int cs = 1;
	v2i un(k);
	for (int i = 1; i < k; i++) un[i].pb(st[i]);
	for (int i = st[1]; i < n; i++) {
		if (arr[i]) continue;
		if (cs == k-1 && sz(un[cs])%k < k-1) {
			un[cs].pb(i); continue;
		} else if (cs == k-1) {break;}
		if (sz(un[cs])%k == k-2) {
			un[cs].pb(i); cs++; continue;
		}
		if (i < st[cs+1]-1) {
			un[cs].pb(i); continue;
		}
		un[cs].pb(i);
	}
	for (int i = 1; i < k; i++) {
		un[i].pb(ed[i-1]);
	}
	vi nb(n, 0);
	for (auto i : un) {
		for (auto j : i) nb[j] = 1;
	}
	for (int i = 0; i < n; i++) {
		if (!nb[i]) un[0].pb(i);
	}
	for (auto i: un) {
		if (sz(i)%k) return 0;
		if (!is_sorted(all(i))) return 0;
	}
	cout << "Yes\n" << k << "\n";
	int us = 0;
	for (auto i : un) {
		cout << sz(i) << " ";
		us += sz(i);
		for (auto j : i) cout << j+1 << " ";
		cout << "\n";
	}
	return 1;
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> t;
	cin >> n >> k; arr = vi(n);
	if (n%k) {cout << "No\n"; return 0;}
	for (int i = 0; i < n; i++) cin >> arr[i];
	for (int i = 0; i < n; i++) arr[i] %= k;
	if (arr[0] || arr[n-1]) {cout << "No\n"; return 0;}
	for (int i = 0; i < n; i++) {
		if (!arr[i]) st.pb(i);
		if (!arr[i]) ed.pb(i);
	}
	while (sz(st) > k) st.pop_back();
	reverse(all(ed));
	while (sz(ed) > k) ed.pop_back();
	reverse(all(ed));
	if (sz(st) < k || sz(ed) < k) {cout << "No\n"; return 0;}
	for (auto i : st) {
		if (binary_search(all(ed), i)) {
			cout << "No\n"; return 0;
		}
	}
	arr = vi(n, 0);
	for (auto i : st) arr[i] = 1;
	for (auto i : ed) arr[i] = 1;
	if (!solve2() && !solve1()) cout << "No\n";
	return 0;
}