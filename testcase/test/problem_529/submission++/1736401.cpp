#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 7;
char s[N];

int main() {
	
  ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

  int T, n, i, j, a, b;
	
  for (cin >> T; T--;) {
    cin >> (s + 1), n = strlen(s + 1);
    for (i = a = b = 1, j = -1; i <= n; ++i) {
      if (s[i] == 'N') j = 1;
      if (s[i - 1] == 'N' && s[i] == 'N') a = b = 0;
    }
    if (j == -1) a = b = 0;
    if (s[1] == 'V') b = 0;
		cout << a << ' ' << b << endl;
  }

  return 0;
}