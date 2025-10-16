
#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pii pair<int, int>
#define ll long long
#define ui unsigned int
using namespace std;
ui N, K, m, b, c;
ui p[100005], v[100005], pw[100005]; 
int id1[100005], id2[100005];
ui g[200005], w[200005];
unordered_map<int, ui> ss[200005];
ui hh[200005];
int id(ll x) {
	if(x > m) return id2[N / x];
	return id1[x];
}
ui quickpow(ui x, ui o) {
    ui ans = 1, now = x;
    while(o) {
        if(o & 1) ans *= now;
        now *= now;
        o >>= 1;
    }
    return ans;
}
void init() {
	p[0] = pw[0] = 1;
	for(int i = 2; i <= m; i++) {
		if(!v[i]) { p[++c] = i; pw[c] = quickpow(i, K); }
		for(int j = 1; i * p[j] <= m; j++) {
			v[i * p[j]] = 1;
			if(i % p[j] == 0) break;
		}
	}
	for(ll i = 1, j; i <= N; i = j + 1) {
		j = N / (N / i); w[++b] = N / i; (N / i > m ? id2[j] : id1[N / i]) = b;
		g[b] = w[b] - 1;
	}
	for(int j = 1; j <= c; j++)
		for(int i = 1; i <= b && (ll)p[j] * (ll)p[j] <= w[i]; i++) {
			int k = id(w[i] / p[j]);
			g[i] -= g[k] - j + 1;
		}
}
ui S(ui n, int j) {
	if(ss[id(n)].count(j)) return ss[id(n)][j];
	if(n <= 1 || p[j] > n || j > m) return 0;
	ui res = (g[id(n)] - j + 1) * pw[j - 1];
	for(int k = j; k <= c && (ll)p[k] * (ll)p[k] <= n; k++) {
		ll pw1 = p[k], pw2 = pw1 * p[k];
		for(int l = 1; pw2 <= n; l++) {
			res += S(n / pw1, k + 1) + pw[k];
			pw1 = pw2; pw2 *= p[k];
		}
	}
	
	return ss[id(n)][j] = res;
}
ui h(ui n) {
	if(hh[id(n)]) return hh[id(n)];
	if(n <= 1) return 0;
	hh[id(n)] = S(n, 1);
	for(int i = 2, j; i <= n; i = j + 1) {
		j = n / (n / i); hh[id(n)] -= (j - i + 1) * h(n / i);
	}
	return hh[id(n)];
}
int main(){
	cin >> N >> K; m = floor(pow((long double)N, 0.5)); init();
	ui ans = 0;
	for(ui i = 1, j; i <= N; i = j + 1) {
		j = N / (N / i);
		ans += (N / i) * (N / i) * (h(j) - h(i - 1));
	}
	cout << ans << endl;
    return 0;
}



