


#include<bits/stdc++.h>
using namespace std;
namespace Acc {
	auto work = []() {
		int n, k, z, m = 60000, r;
		cin >> k, z = n = k;
		if (k == 1) {
			cout << "-1\n";
			return ;
		}
		for (int i = 2; i * i <= n; ++i) {
			if (n % i) continue;
			z = z / i * (i - 1);
			while (n % i == 0) n /= i;
		}
		if (n > 1) z = z / n * (n - 1);
		r = m % z + z;
		cout << m << '\n';
		for (int i = 0; i < m; ++i) {
			cout << (i == r) << ' ';
		}
		cout << k - 1 << '\n';
	};
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), Acc::work();
}