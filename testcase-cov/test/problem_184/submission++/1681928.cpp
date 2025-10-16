#include <bits/stdc++.h>
using namespace std;
using lint = long long;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int MAXN = 800005;
const int mod = 998244353; 

vector<int> unit_monge_mult(vector<int> &a, vector<int> &rb) {
	int n = sz(a);
	if (n == 1)
		return a;
	int m = n / 2;
	auto split = [&](vector<int> &v) {
		vector<int> L, LR, R, RR;
		for (int i = 0; i < n; i++) {
			if (v[i] < m) {
				L.push_back(v[i]);
				LR.push_back(i);

			} else {
				R.push_back(v[i] - m);
				RR.push_back(i);
			}
		}
		return make_tuple(L, R, LR, RR);
	};
	auto [al, ar, ral, rar] = split(a);
	auto [bl, br, rbl, rbr] = split(rb);
	auto cl = unit_monge_mult(al, bl);
	auto cr = unit_monge_mult(ar, br);
	vector<int> ret(n), iret(n);
	vector<int> isLeftA(n), isLeftB(n);
	{
		for (int i = 0; i < sz(cl); i++) {
			ret[ral[i]] = rbl[cl[i]];
			isLeftA[ral[i]] = 1;
			isLeftB[rbl[i]] = 1;
		}
		for (int i = 0; i < sz(cr); i++) {
			ret[rar[i]] = rbr[cr[i]];
		}
		for (int i = 0; i < n; i++)
			iret[ret[i]] = i;
	}
	auto right_delta = [&](int x, int y) {
		if (!isLeftB[y]) {
			return iret[y] < x ? 1 : 0;
		}
		return iret[y] >= x ? 1 : 0;
	};
	auto up_delta = [&](int x, int y) {
		if (!isLeftA[x])
			return ret[x] < y ? 1 : 0;
		else
			return ret[x] >= y ? 1 : 0;
	};
	int j = n, sum = 0;
	for (int i = 0; i < n; i++) {
		while (j > 0 && sum - right_delta(i, j - 1) >= 0) {
			sum -= right_delta(i, --j);
		}
		int new_sum = sum + up_delta(i, j);
		if (j > 0 && sum == 0 && new_sum > 0) {
			ret[i] = j - 1;
		}
		sum = new_sum;
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n), rb(n);
	for (auto &x : a) {
		cin >> x;
		x--;
	}
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		rb[x - 1] = i;
	}
	auto c = unit_monge_mult(a, rb);
	for (auto &x : c)
		cout << x + 1 << " ";
}