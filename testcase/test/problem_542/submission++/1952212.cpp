#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
 
using namespace std;
using namespace std::chrono;
 
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...) 
#endif

int setbit(int x) {return __builtin_popcount(x);}
int setbit(long long x) {return __builtin_popcountll(x);}
int highbit(int x) {return (x==0?-1:31-__builtin_clz(x));}
int highbit(long long x) {return (x==0?-1:63-__builtin_clzll(x));}
int lowbit(int x) {return (x==0?-1:__builtin_ctz(x));}
int lowbit(long long x) {return (x==0?-1:__builtin_ctzll(x));}
#define ll long long
#define int ll
#define inf 2147483647
#define inf_long_long 9223372036854775807/4
#define endl "\n"
#define mod 1000000007
#define fastinput ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define umap unordered_map
#define pii pair<int,int>
#define ppiii pair<pii, int>
#define pipii pair<int, pii>
#define sz(x) ((int) x.size())
#define forn(i,a,b) for(int i=a;i<=b;i++)
#define for0(i,a,b) for(int i=a;i>=b;i--)
typedef vector<int> vi;
typedef vector<pii> vp;
typedef tuple<int,int,int> tiii;
typedef __int128 i128;
template<typename T,typename U>
T ceil(T x, U y) {return (x>0?(x+y-1)/y:x/y);}
vector<int> factorials;
vector<int> invf;
int bp(int a, int b) {if (b==0) {return 1;} int ret = bp(a, b/2); ret*=ret; ret%=mod; if (b%2==1) {ret*=a; ret%=mod;} return ret;}
int bpm(int a, int b) {if (b==0) {return 1;} int ret = bpm(a, b/2); ret*=ret; ret%=mod; if (b%2==1) {ret*=a; ret%=mod;} return ret;}
int gcd(int a, int b) {if (a==0) {return b;} if (b==0) {return a;}return gcd(b%a, a);}
int lcm(int a, int b) {return a/gcd(a,b)*b;}
int inv(int a) {return bpm(a, mod-2);}
void calcfacmod(int n) {factorials.resize(n+1);factorials[0] = 1;for (int i = 1; i <= n; i++) {factorials[i] = factorials[i-1]*i;factorials[i]%=mod;}}
mt19937_64 rngg(chrono::steady_clock::now().time_since_epoch().count());
int RNG() {return rngg()%inf_long_long;}
void calcfac(int n) {calcfacmod(n);}

template<typename T>
void modpos(T &a) {T amt = (-a)/mod;amt++; amt = max(T(0), amt); a += amt*mod; a%=mod;}

int choose(int a, int b) {if (a<b) {return 1;}if (b==a || b==0) {return 1;}return (((factorials[a]*invf[b])%mod)*invf[a-b])%mod;}
void calcinvfac(int n) {invf.resize(n);for (int i = 0; i < n; i++) {invf[i] = inv(factorials[i]);}}
int paths(int a, int b) {return choose(a+b, a);}







signed main() {
	fastinput;
	int ul;
	cin >> ul;
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	vector<int> tmp;
	vector<int> t;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i]%k==0) {
			a[i] = 1;
			tmp.pb(i);
		} else {
			a[i] = 0;
			t.pb(i);
		}
	}
	
	if (!a[0] || !a[n - 1]) {
		cout << "No";
		return 0;
	}
	if (sz(tmp) < 2 * k || n % k != 0 || k * k > n) {
		cout << "No";
	} else {
		vector<int> c;
		for (int i = 0; i < sz(tmp); i++) {
			if (i < k || i >= sz(tmp) - k) {
				c.pb(tmp[i]);
			} else {
				t.pb(tmp[i]);
			}
		}
		
		
		sort(t.begin(), t.end());
		int w = 1;
		vector<vector<int> > p(k);
		int ind = 0;
		for (int i = 0; i < sz(t); i++) {
			if (ind != k-1) {
				if ((sz(p[ind])+2)%k==0 && t[i] >= c[ind + 1]) {
					ind ++;
				}
			}
			p[ind].pb(t[i]);
		}
		for (int i = 0; i < k; i++) {
			if (sz(p[i])%k!=k-2) {
				w = 0;
				break;
			}
			int l = c[i];
			int r = c[i + k];
			for (auto num : p[i]) {
				if (l <= num && num <= r) {

				} else {
					w= 0;
					break;
				}
			}
		}
		if (w) {
			
			cout << "Yes" << endl;
			cout << k << endl;
			for (int i = 0; i < k; i++) {
				cout << sz(p[i]) + 2 << " " << c[i]+1 << " ";
				for (auto d : p[i]) {
					cout << d+1 << " ";
				}
				cout << c[i + k]+1 << endl;
			}
		} else {
			w = 1;
			p.clear();
			p.resize(k);
			int lll = c[1];
			int rr = c[2 * k - 2];
			int ind = 1;
			for (int i = 0; i < sz(t); i++) {
				if (t[i] < lll || t[i] > rr || ind == k || t[i] < c[ind]) {
					
					p[0].pb(t[i]);
				} else {
					if (t[i] > c[ind + k - 1]) {
						p[0].pb(t[i]);
						continue;
					}
					p[ind].pb(t[i]);
					if (sz(p[ind])==k - 2) {
						ind ++;
					}
				}
			}
			
			for (int i = 1; i < k; i++) {
				int l = c[i];
				int r = c[i + k - 1];
				if (sz(p[i])!=k-2) {
					w = 0;
					break;
				}
				for (auto num : p[i]) {
					if (l <= num && num <= r) {
					} else {
						w = 0;
					}
				}
			}
			
			if (w) {
				cout << "Yes" << endl;
				cout << k << endl;
				cout << sz(p[0]) + 2 << " " << c[0]+1 << " ";
				for (auto num : p[0]) {
					cout << num+1 << " ";
				}
				cout << c[2 * k - 1]+1 << endl;
				for (int i = 1; i < k; i++) {
					cout << sz(p[i]) + 2 << " " << c[i]+1 << " ";
					for (auto num : p[i]) {
						cout << num+1 << " ";
					}
					cout << c[i + k - 1]+1 << endl;
				}
			} else {
				cout << "No";
			}
		}
	}
}
