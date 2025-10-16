#include <cstdio>
#include <random>

struct Ring {
    int a,b,c;
    Ring(int _a = 0,int _b = 0,int _c = 0): a(_a),b(_b),c(_c) {}
};
int a,p;
std::mt19937 rnd(20070803);

inline int read() {
#define gc c = getchar()
    int d = 0,f = 0,gc;
    for(;c < 48 || c > 57;gc) f |= (c == '-');
    for(;c > 47 && c < 58;gc) d = (d << 1) + (d << 3) + (c ^ 48);
#undef gc
    return f ? -d : d;
}

inline int Mul(int a,int b) { return 1LL * a * b % p; }
inline int Mul(int a,int b,int c) { return Mul(Mul(a,b),c); }
inline int Add(int a,int b) { a += b; return a < p ? a : a - p; }
inline int Add(int a,int b,int c) { return Add(Add(a,b),c); }

inline Ring Mul(Ring x,Ring y) {
    return Ring(Add(Mul(x.a,y.a),Mul(a,x.b,y.c),Mul(a,x.c,y.b)),
                Add(Mul(x.a,y.b),Mul(x.b,y.a),Mul(a,x.c,y.c)),
                Add(Mul(x.a,y.c),Mul(x.b,y.b),Mul(x.c,y.a)));
}

inline int fpow(int a,int b) {
    int res = 1;
    for(;b;b >>= 1,a = Mul(a,a)) if(b & 1) res = Mul(res,a);
    return res;
}

inline Ring fpow(Ring a,int b) {
    Ring res = a; b --;
    for(;b;b >>= 1,a = Mul(a,a)) if(b & 1) res = Mul(res,a);
    return res;
}

inline int getRnd() { return rnd() % (p - 1) + 1;}

inline void solve() {
    if(a == 0 || p == 2 || p == 3) { printf("%d\n",a); return ; }
    if(p % 3 == 2) { printf("%d\n",fpow(a,(2 * p - 1) / 3)); return ; }
    if(fpow(a,(p - 1) / 3) != 1) { puts("0"); return ; }
    for(;;) {
        Ring z = fpow(Ring(getRnd(),getRnd(),getRnd()),(p - 1) / 3);
        if(!z.a && !z.c && z.b) { printf("%d\n",fpow(z.b,p - 2)); return ; }
    }
}

int main() {
    for(int T = read();T;T --) {
        a = read(),p = read();
        solve();
    }
    return 0;
}