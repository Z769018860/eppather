#include "bits/stdc++.h"
using namespace std;

#define ll long long
#define ln '\n'

const ll N = 1e4 + 5;
const ll LG = 68;
const ll INF = 5e18 + 5;
const ll MOD = 998244353;

ll pfx[N], sfx[N], a[N];

void solve(){
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) pfx[i] = pfx[i-1] + a[i];
    for (int i = n; i >= 1; i--) sfx[i] = sfx[i+1] + a[i];

    for (int i = 1; i <= n; i++) pfx[i] = min(pfx[i], pfx[i-1]);
    for (int i = n; i >= 1; i--) sfx[i] = min(sfx[i+1], sfx[i]);
    reverse(sfx+1, sfx+n+1);

    ll tot = accumulate(a+1, a+n+1, 0LL);

    while (m--){
        int x; cin >> x;
        ll ans = INF;

        for (int i = 0; i <= n-x; i++){
            ans = min(ans, pfx[i] + sfx[n-x-i]);
        }
        cout << tot - ans << ln;
    }

}




int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);


    
    

    solve();
}
