#include <bits/stdc++.h>
using namespace std;
const int _ = 1e6 + 10;
string A, B;
char txt[_], pat[_];
int n, m, kmp[_], ans;
int main() {
    cin >> A >> B;
    n = A.length();
    for (int i = 1; i <= n; i++) {
        txt[i] = A[i-1];
    }
    m = B.length();
    for (int i = 1; i <= m; i++) {
        pat[i] = B[i-1];
    }
    for (int i = 2; i <= m; i++) {
        kmp[i] = kmp[i-1];
        while (kmp[i] && pat[kmp[i] + 1] != pat[i]) kmp[i] = kmp[kmp[i]];
        if (pat[kmp[i] + 1] == pat[i]) kmp[i]++;
    }
    for (int i = 1, j = 0; i <= n; i++) {
        while (j && pat[j + 1] != txt[i]) j = kmp[j];
        if (pat[j + 1] == txt[i]) j++;
        if (j == m) ans++;
    }
    cout << ans << endl;
}