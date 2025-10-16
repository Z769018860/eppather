


#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef int64_t lld;
typedef pair<lld, lld> pll;
typedef pair<int, int> pii;
typedef long double ld;

#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
pii operator+(pii a, pii b) {
    return {a.ff + b.ff, a.ss + b.ss};
}
pii &operator+=(pii &a, pii b) {
    return a.ff += b.ff, a.ss += b.ss, a;
}
template<typename Iter>
ostream &outIt(ostream &out, Iter b, Iter e) {
    for (Iter i = b; i != e; i++)
        out << *i << " ";

    return out;
}
template<typename T>
ostream &operator<<(ostream &out, vector<T> v) {
    return outIt(out << '[', all(v)) << ']';
}
template<typename T, size_t N>
ostream &operator<<(ostream &out, array<T, N> v) {
    return outIt(out << '[', all(v)) << ']';
}
template<typename T1, typename T2>
ostream &operator<<(ostream &out, pair<T1, T2> p) {
    return out << '(' << p.ff << ", " << p.ss << ')';
}
template<typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &p) {
    return in >> p.ff >> p.ss;
}
struct hashfunc {
    const int RANDOM = (long long)(make_unique<char>().get()) ^
                       chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned long long hash_f(unsigned long long x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    static unsigned hash_combine(unsigned a, unsigned b) {
        return a * 31 + b;
    }
    int operator()(pll x) const {
        return hash_f(x.ff) ^ hash_f(x.ss);
    }
};
lld ttl = 0;
random_device rd;
mt19937 gen(7122); 
uniform_int_distribution<lld> dist;
lld p = 0;
const pll O = {-1, -1};
inline lld M(lld x) {
    return x >= p ? x - p : x;
}
inline lld modmul(lld a, lld b) {
    a %= p, b %= p;
    lld ret = (uint64_t)(a * b) - (uint64_t)p * (uint64_t)(ld(a) * ld(b) / ld(p));
    
    return ret + p * (ret < 0) - p * (ret >= p);
}
inline lld pow(lld a, lld b) {
    lld ans = 1;

    do
        if (b & 1)
            ans = modmul(ans, a);

    while (a = modmul(a, a), b >>= 1);

    return ans;
}
inline pll mul(pll a, pll b, lld sq) {
    return {M(modmul(a.ff, b.ff) + modmul(modmul(a.ss, b.ss), sq)), M(modmul(a.ff, b.ss) + modmul(a.ss, b.ff))};
}
inline pll pow(pll a, lld b, lld sq) {
    pll ans = {1, 0};

    do
        if (b & 1)
            ans = mul(ans, a, sq);

    while (a = mul(a, a, sq), b >>= 1);

    return ans;
}
lld sqrtmod(lld x) {
    if (!x)
        return 0;

    
    lld a, b;

    
    do {
        a = dist(gen), b = M(modmul(a, a) - x + p);
        
        
        
    } while (pow((lld)b, (p - 1) / 2) + 1 != p);

    pll ans = pow({a, 1}, (p + 1) / 2, b);
    
    
    return ans.ff;
}
lld invmod(lld a, lld b = p, lld s0 = 0, lld s1 = 1) {
    
    return b ? invmod(b, a % b, M(s1 - modmul(a / b, s0) + p), s0) : s1;
}
inline pll sum(pll x, pll y, lld a, lld b) {
    if (x == O || y == O)
        return max(x, y);

    if (x.ff == y.ff && (x.ss + y.ss == 0 || x.ss + y.ss == p))
        return O;

    ttl++;
    lld lam;

    if (x == y)
        
        lam = modmul((3 * modmul(x.ff, x.ff) + a) % p, invmod(M(x.ss << 1)));
    else {
        
        lam = modmul(x.ss - y.ss + p, invmod(M(x.ff - y.ff + p)));
    }

    lld z1 = M(M(modmul(lam, lam) - x.ff - y.ff + p + p));
    lld z2 = M(modmul(lam, x.ff - z1 + p) - x.ss + p);
    return {z1, z2};
}
inline pll neg(pll x) {
    if (x == O)
        return x;

    return {x.ff, M(p - x.ss)};
}
inline pll mul(pll x, lld y, lld a, lld b) {
    pll ans = O;

    do
        if (y & 1)
            ans = sum(ans, x, a, b);

    while (x = sum(x, x, a, b), y >>= 1);

    return ans;
}
pll get_point(lld a, lld b) {
    lld x, y;

    
    do {
        x = dist(gen), y = M(modmul(modmul(x, x) + a, x) + b);
        
        
    } while (pow((lld)y, (p - 1) / 2) + 1 == p);

    return {x, sqrtmod(y)};
}
#include <ext/pb_ds/assoc_container.hpp>
__gnu_pbds::cc_hash_table<pll, lld, hashfunc> mps;
const lld step = 63000;
lld try_solve(lld a, lld b) {
    auto x = get_point(a, b);
    lld match = -1;
    
    
    
    auto stepP = mul(x, step, a, b);
    mps.clear();
    lld l = p + 1 - 2 * sqrt(p) - 2, r = p + 1 + 2 * sqrt(p) + 2;

    if (l < 0)
        l = 0;

    pll cur = mul(x, l, a, b);

    for (lld i = l; i <= r; i += step) {
        
        
        if (mps.find(cur) != mps.end())
            mps[cur] = -1;
        else
            mps[cur] = i;

        
        cur = sum(cur, stepP, a, b);
    }

    cur = {-1, -1};
    x = neg(x);

    
    for (lld i = 0; i < step; i++) {
        if (mps.find(cur) != mps.end()) {
            
            
            if (mps[cur] == -1)
                throw - 1;

            if (mps[cur] + i > r);
            else if (match == -1)
                match = mps[cur] + i;
            else
                throw - 1;
        }

        cur = sum(cur, x, a, b);
    }

    
    
    return match;
}
int fail = 0;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int t = 1;

    
    while (t--) {
        lld a, b, x, aa, bb;
        int64_t _a, _b, _p;
        cin >> _p >> _a >> _b;
        a = _a, b = _b, p = _p;
        dist = uniform_int_distribution<lld>(0, p - 1);

        if (p <= 500) {
            
            int ans = 0;

            for (int i = 0; i < p; i++) {
                lld r = ((lld)i * i % p * i % p + (lld)a * i % p + b) % p;

                if (!r)
                    ans++;
                else if (pow(r, (p - 1) / 2) == 1)
                    ans += (p != 2) + 1;
            }

            cout << (int64_t)(ans + 1) << endl;
            cerr << "hi" << endl;
            continue;
        }

        if (M(modmul(modmul(a << 2, a), a) + modmul(9 * b, 3 * b)) == 0) {
            if (!a && !b)
                cout << (int64_t)(p + 1) << endl;
            else {
                lld t = modmul(p - b << 1, invmod(a));

                if (pow(t, (p - 1) / 2) == 1)
                    cout << (int64_t)p << endl;
                else
                    cout << (int64_t)p + 2 << endl;
            }

            continue;
        }

        
        do {
            x = dist(gen);
            
        } while (pow(x, (p - 1) / 2) + 1 != p);

        aa = modmul(a, modmul(x, x)), bb = modmul(modmul(b, x), modmul(x, x));

        for (int i = 1; true; i = !i) {
            try {
                if (i)
                    cout << (int64_t)try_solve(a, b) << endl;
                else
                    cout << (int64_t)(2 * p + 2 - try_solve(aa, bb)) << endl;

                break;
            } catch (int32_t e) {
                fail++;

                if (fail > 2000) {
                    cout << _a << " " << _b << " " << _p << endl;
                    assert(false);
                }

                
                
            }
        }
    }

    cerr << ttl << " " << fail << endl;
}