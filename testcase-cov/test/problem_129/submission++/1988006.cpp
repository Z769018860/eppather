#include <bits/stdc++.h>
#define sz(a) ((int)a.size())
using namespace std;
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  string st;
  cin >> st;
  for (int i = 0; i < sz(st);) {
    int j = i, k = i + 1;
    for (; k < sz(st) && st[k] >= st[j]; k++) j = (st[k] == st[j]) ? j + 1 : i;
    for (; i <= j;) i += k - j, cout << i << ' ';
  }
}