#include <iostream>
#include <cstdio>
#include <bitset>
#include <algorithm>
#define int long long
using namespace std;

const int N = 1e6 + 100;
int n;

signed main() {
	cin >> n;
	bitset<N> s;
	s[0] = 1;
	for(int i = 1;i <= n;i ++) {
		int x , y;
		cin >> x >> y;
		bitset<N> kk;
		for(int j = x;j <= y;j ++) {
			int now = j * j;
			kk |= (s << now);
		}
		s = kk;
	}
	int ans = 0;
	for(int i = 1;i <= 1e6;i ++)
		if(s[i] == 1) ans ++;
	cout << ans;
	return 0;
}