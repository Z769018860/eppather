#include<bits/stdc++.h>
#define rep(i, n) for(int i = 0; i < n;++i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int inf = 0x3f3f3f3f;
const int Mod = 1e9 + 7;
const int inv2 = (Mod+1) / 2;
inline int sign(int a){ return (a&1) ? (Mod-1) : 1; }
inline void uadd(int &a, int b){ a += b-Mod; a += (a>>31) & Mod; }
inline void usub(int &a, int b){ a -= b, a += (a>>31) & Mod; }
inline void umul(int &a, int b){ a = (int)(1ll * a * b % Mod); }
inline int add(int a, int b){ a += b-Mod; a += (a>>31) & Mod; return a; }
inline int sub(int a, int b){ a -= b, a += (a>>31) & Mod; return a; }
inline int mul(int a, int b){ a = (int)(1ll * a * b % Mod); return a; }
int qpow(int b, int p){ int ret = 1; while(p){ if(p&1) umul(ret, b); umul(b, b), p >>= 1; } return ret; }
const int fN = 100;
int fact[fN], invfact[fN], pw2[fN], invpw2[fN];
void initfact(int n){
	pw2[0] = 1; for(int i = 1; i <= n; ++i) pw2[i] = mul(pw2[i-1], 2);
	invpw2[0] = 1; for(int i = 1; i <= n; ++i) invpw2[i] = mul(invpw2[i-1], (Mod+1) / 2);
	fact[0] = 1; for(int i = 1; i <= n; ++i) fact[i] = mul(fact[i-1], i);
	invfact[n] = qpow(fact[n], Mod-2); for(int i = n; i > 0; --i) invfact[i-1] = mul(invfact[i], i);
}
int binom(int n, int m){ return mul(fact[n], mul(invfact[m], invfact[n-m])); }
const double pi = acos(-1);

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	int T, N, K;
	cin >> T >> N >> K;
	vector<int> A(N);
	for(int &a : A)
		cin >> a;
	
	if(A.front() % K != 0 || A.back() % K != 0){
		cout << "No\n";
		return 0;
	}
	int num = 0;
	for(int a : A)
		num += int(a % K == 0);
	if(num < 2 * K){
		cout << "No\n";
		return 0;
	}

	vector<bool> lv(N, false), rr(N, false);

	num = 0;
	for(int i = 0; num < K; i++){
		if(A[i] % K == 0){
			lv[i] = true;
			num++;
		}
	}

	num = 0;
	for(int i = N - 1; num < K; i--){
		if(A[i] % K == 0){
			rr[i] = true;
			num++;
		}
	}

	num = 0;
	bool yes = true;
	vector<vector<int>> ans(K);
	for(int i = 0, j = 0, k = 0; i < N; i++){
		if(lv[i]){
			ans[j++].push_back(i);
		} else if(rr[i]){
			int c = k++;
			num = max(num, k);
			if(ans[c].size() % K != K - 1){
				yes = false;
				break;
			} else {
				ans[c].push_back(i);
			}
		} else {
			if(num != j - 1 && ans[num].size() % K == K - 1)
				num++;
			ans[num].push_back(i);
		}
	}
	
	if(yes){
		cout << "Yes\n" << K << '\n';
		for(int i = 0; i < K; i++){
			cout << ans[i].size() << ' ';
			for(int x : ans[i])
				cout << x + 1 << ' ';
			cout << '\n';
		}
		return 0;
	}

	for(int i = 0; i < K; i++)
		ans[i].clear();
	lv[0] = false;
	rr[N - 1] = false;
	yes = true;
	num = 0;
	ans[K - 1].push_back(0);
	for(int i = 1, j = 0, k = 0; i < N - 1; i++){
		if(lv[i]){
			ans[j++].push_back(i);
		} else if(rr[i]){
			int c = k++;
			num = max(num, k);
			if(ans[c].size() % K != K - 1){
				yes = false;
				break;
			} else {
				ans[c].push_back(i);
			}
		} else {
			if(num < j - 1 && ans[num].size() % K == K - 1)
				num++;
			if(j == 0 || (num == j - 1 && ans[num].size() % K == K - 1))
				ans[K - 1].push_back(i);
			else 
				ans[num].push_back(i);
		}
	}
	ans[K - 1].push_back(N - 1);

	if(yes){
		cout << "Yes\n" << K << '\n';
		for(int i = 0; i < K; i++){
			cout << ans[i].size() << ' ';
			for(int x : ans[i])
				cout << x + 1 << ' ';
			cout << '\n';
		}
		return 0;
	} else {
		cout << "No\n";
	}

	return 0;
}