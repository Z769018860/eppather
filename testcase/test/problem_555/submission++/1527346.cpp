#include<bits/stdc++.h>
#define rep(i, n) for(int i = 0; i < n; i++)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
const ll Mod = 998244353;
ll qpow(ll b, ll p){
	ll ret = 1;
	while(p){
		if(p & 1)
			ret = ret * b % Mod;
		p >>= 1;
		b = b * b % Mod;
	}
	return ret;
}
void update(ll &a, ll b){
	a += b;
	if(a >= Mod)
		a -= Mod;
}
void Output(vi v){
	cerr << "( ";
	rep(i, (int)v.size())
		cerr << v[i] << " ";
	cerr << ")" << endl;
}

vi operator +(vi a, vi b){
	vi ret(max(a.size(), b.size()));
	rep(i, max((int)a.size(), (int)b.size())){
		if(i < (int)a.size())
			ret[i] = a[i];
		if(i < (int)b.size())
			update(ret[i], b[i]);
	}
	return ret;
}

ll w[44444];
vi dft(vi v, bool idft = 0){
	int lmt = 0;
	for(; (1 << lmt) < (int)v.size(); lmt++);
	vi ret(1 << lmt);
	rep(i, (int)v.size()){
		int to = 0;
		rep(j, lmt) to += ((i >> j) & 1) << (lmt - j - 1);
		ret[to] = v[i];
	}
	w[0] = 1, w[1] = qpow(3ll, (Mod - 1) / (1 << lmt));
	if(idft)
		w[1] = qpow(w[1], Mod - 2);
	for(int i = 2; i < (1 << lmt); i++)
		w[i] = w[i - 1] * w[1] % Mod;
	for(int len = 2; len <= (1 << lmt); len <<= 1)
		for(int l = 0; l < (1 << lmt); l += len)
			for(int i = l; i < l + len / 2; i++){
				ll a = ret[i], b = w[(1 << lmt) / len * (i - l)] * ret[i + len / 2] % Mod;
				ret[i] = (a + b) % Mod;
				ret[i + len / 2] = (a + Mod - b) % Mod;
			}
	if(idft){
		ll invn = qpow(1 << lmt, Mod - 2);
		rep(i, (int)ret.size())
			ret[i] = ret[i] * invn % Mod;
	}
	return ret;
}
vi operator *(vi a, vi b){
	int n = (int)a.size() + (int)b.size();
	a.resize(n), b.resize(n);
	a = dft(a), b = dft(b);
	rep(i, (int)a.size())
		a[i] = a[i] * b[i] % Mod;
	a = dft(a, 1);
	return a;
}

ll A, B;
ll N;
int D, M, k;
vi ModD(vi a){
	for(int i = (int)a.size() - 1; i >= D; i--)
		update(a[i - D], a[i]), a[i] = 0;
	a.resize(D);
	return a;
}

vi pw[1010];
vi pwD[66];
vi pwDsum[66];
void precalc(){
	pw[0] = {1};
	pw[1] = {B, A};
	for(int i = 2; i <= D; i++){
		pw[i] = ModD(pw[i - 1] * pw[1]);

	}
	pwD[0] = pw[D];
	for(int i = 1; i <= 62; i++){
		pwD[i] = ModD(pwD[i - 1] * pwD[i - 1]);

	}
	pwDsum[0] = {1};
	for(int i = 1; i <= 62; i++){
		pwDsum[i] = ModD(pwDsum[i - 1] + pwDsum[i - 1] * pwD[i - 1]); 

	}
}

ll calc(int x, int y, ll n){
	if(n < x + y)
		return 0;
	int r = (x + y) % D;
	ll lmt = (n - r) / D + 1;
	vi sum = {}, pro = pw[r];
	for(ll i = 62; i >= 0; i--)
		if(lmt & (1ll << i)){


			sum = ModD(sum + pwDsum[i] * pro);
			pro = ModD(pro * pwD[i]);
			lmt -= (1ll << i);
		}
	return sum[y];
}

pair<ll, ll> a[55];
ll f[55];
ll fact[1111], invfact[1111];

ll C(ll x, ll y){
	ll ret = qpow(A, y) * qpow(B, x) % Mod * invfact[x] % Mod;
	for(ll j = y + x; j > y; j--)
		ret = j % Mod * ret % Mod;
	return ret;
}

int main(){
	fact[0] = 1;
	for(int i = 1; i <= 1000; i++)
		fact[i] = fact[i - 1] * i % Mod;
	invfact[1000] = qpow(fact[1000], Mod - 2);
	for(int i = 1000; i >= 1; i--)
		invfact[i - 1] = invfact[i] * i % Mod;
	ios::sync_with_stdio(false);
	cin >> A >> B >> N >> D >> M >> k;
	precalc();
	ll ans = calc(0, 0, N);
	rep(i, k)
		cin >> a[i].first >> a[i].second;
	sort(a, a + k);
	rep(i, k){
		f[i] = C(a[i].first, a[i].second);
		rep(j, i)
			if(a[j].first <= a[i].first && a[j].second <= a[i].second)
				f[i] = (f[i] + Mod - (f[j] * C(a[i].first - a[j].first, a[i].second - a[j].second)) % Mod) % Mod;
		ans = (ans + Mod - calc((D - a[i].first % D) % D, (D - a[i].second % D) % D, N - (a[i].first + a[i].second)) * f[i] % Mod) % Mod;
	}
	cout << ans << endl;
	return 0;
}