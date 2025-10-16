#include <bits/stdc++.h>

using namespace std;

#if __cplusplus >= 201103L
    struct pairhash {
        static uint64_t splitmix64(uint64_t x) {
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
        }

        template<class T, class U>
        size_t operator() (const pair<T,U> &p) const {
            static const uint64_t FIXED_RANDOM = (uint64_t)chrono::steady_clock::now().time_since_epoch().count();
            return splitmix64(p.first + FIXED_RANDOM) ^ splitmix64(p.second+ FIXED_RANDOM);
        }
    };
    struct custom_hash {
        static uint64_t splitmix64(uint64_t x) {
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
        }

        size_t operator()(uint64_t x) const {
            static const uint64_t FIXED_RANDOM = (uint64_t)chrono::steady_clock::now().time_since_epoch().count();
            return splitmix64(x + FIXED_RANDOM);
        }
    };
    mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
    inline int randint(int l, int r) {
        return uniform_int_distribution<int>(l,r)(rng);
    }
    inline double randdouble(double l, double r) {
        return uniform_real_distribution<double>(l,r)(rng);
    }
    inline long long randll(long long l, long long r) {
        mt19937_64 rng2((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
        return uniform_int_distribution<long long>(l, r)(rng2);
    }
#endif
 
#ifndef ONLINE_JUDGE
#  define LOG(x) (cerr << #x << " = " << (x) << endl)
#else
#  define LOG(x) 0
#endif

#define fastio ios::sync_with_stdio(false); cin.tie(0);
#define ll long long
#define ull unsigned long long
#define ll128 __int128_t
#define PI 3.14159265358979323846
#define abs(a) ((a>0)?a:-(a))
#define pii pair<int,int>
#define pll pair<ll,ll>

const long double pi = acos(-1.0);
const long double eps = (double)1e-2;

const int mod = 998244353;

template<class T>
T qpow(T a, int b) {
    T res = 1;
    while (b) {
        if (b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}
int norm(int x) {
    if (x < 0) {
        x += mod;
    }
    if (x >= mod) {
        x -= mod;
    }
    return x;
}
struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    Z(ll x) : x(norm((int)(x % mod))) {}
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(mod - x));
    }
    Z inv() const {
        assert(x != 0);
        return qpow(*this, mod - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = (int)((ll)(x) * rhs.x % mod);
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Z &a) {
        ll v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Z &a) {
        return os << a.val();
    }
};
const int maxn = 1e7+5;

ll n;
Z inv6 = (Z)(1) / 6;

Z sum2(ll x) {
    return (Z)(x) * (x+1) * (2*x+1) * inv6;
}
Z sum2(ll L, ll R) {
    return sum2(R) - sum2(L-1);
}
Z sum1(ll x) {
    return (x * (x+1)) / 2;
}
Z sum1(ll L, ll R) {
    return sum1(R) - sum1(L-1);
}
Z sum0(ll L, ll R) {
    return R - L + 1;
}
int main() {
    cin >> n;
    ll L = 1;
    Z ans = 0;
    while (L <= n) {
        ll R = n / (n / L);
        
        ans += (2 * sum2(L, R) + 3 * sum1(L, R) + 5 * sum0(L, R)) * (n / L);
        
        
        
        L = R + 1;
    }
    cout << ans << endl;
}