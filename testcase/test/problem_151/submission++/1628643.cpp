#include <bits/stdc++.h>

using i64 = int64_t;
using u32 = uint32_t;
using u64 = uint64_t;
constexpr int N = 1 << 17;
constexpr int P = 998244353;
struct mint {
    int x;
    constexpr inline mint(int x = 0) : x(x) {}
    constexpr inline mint operator-() const { return x > 0 ? P - x : 0; }
    constexpr inline mint operator+(mint o) const { return x + o.x < P ? x + o.x : x + o.x - P; }
    constexpr inline mint operator-(mint o) const { return x - o.x < 0 ? x - o.x + P : x - o.x; }
    constexpr inline mint operator*(mint o) const { return int(uint64_t(x) * o.x % P); }
    constexpr inline mint &operator+=(mint o) { return *this = *this + o; }
    constexpr inline mint &operator-=(mint o) { return *this = *this - o; }
    constexpr inline mint &operator*=(mint o) { return *this = *this * o; }
    constexpr inline mint inv() const { return pow(P - 2); }
    constexpr inline mint cbrt() const { return pow((P + P - 1) / 3); }
    constexpr inline mint pow(int k) const {
        mint a = x;
        mint b = 1;
        for (; k; k >>= 1) {
            if (k & 1)
                b *= a;
            a *= a;
        }
        return b;
    }
    constexpr inline mint sqrt() const {
        if (pow(P >> 1).x != 1) return 0;
        mint a = pow(60);
        mint b = pow(119);
        for (int k = 21; k >= 0; --k)
            if (b.pow(1 << k).x != 1) {
                a *= mint(3).pow(P >> (k + 2));
                b *= mint(3).pow(P >> (k + 1));
            }
        return std::min(a.x, P - a.x);
    }
};
mint w[N];
mint fac[N];
mint inv[N];
void __attribute__((constructor)) init() {
    w[N / 2] = 1;
    constexpr mint g = mint(3).pow(P / N);
    for (int i = N / 2 + 1; i < N; ++i) w[i] = w[i - 1] * g;
    for (int i = N / 2 - 1; i > 0; --i) w[i] = w[i << 1];
    fac[0] = fac[1] = 1;
    inv[0] = inv[1] = 1;
    for (int i = 2; i < N; ++i) fac[i] = fac[i - 1] * i;
    for (int i = 2; i < N; ++i) inv[i] = inv[P % i] * (P - P / i);
}
void fft(mint f[], int n) {
    for (int k = n / 2; k; k /= 2)
        for (int i = 0; i < n; i += k + k)
            for (int j = 0; j < k; ++j) {
                mint x = f[i + j];
                mint y = f[i + j + k];
                f[i + j] = x + y;
                f[i + j + k] = (x - y) * w[k + j];
            }
}
void ift(mint f[], int n) {
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += k + k)
            for (int j = 0; j < k; ++j) {
                mint x = f[i + j];
                mint y = f[i + j + k] * w[k + j];
                f[i + j] = x + y;
                f[i + j + k] = x - y;
            }
    mint inv = P - (P - 1) / n;
    std::reverse(f + 1, f + n);
    for (int i = 0; i < n; ++i) f[i] *= inv;
}
void Der(const mint a[], mint f[], int n) {
    for (int i = 1; i < n; ++i)
        f[i - 1] = a[i] * i;
    f[n - 1] = 0;
}
void Int(const mint a[], mint f[], int n) {
    for (int i = n - 1; i; --i)
        f[i] = a[i - 1] * inv[i];
    f[0] = 0;
}
void Inv(const mint a[], mint f[], int n) {
        if (n == 1) {
        f[0] = a[0].inv();
    } else {
        Inv(a, f, n / 2);
        mint A[n];
        mint F[n];
        for (int i = 0; i < n; ++i) A[i] = a[i];
        fft(A, n);
        for (int i = 0; i < n / 2; ++i) F[i] = f[i];
        fft(F, n);
        for (int i = 0; i < n; ++i) A[i] *= F[i];
        ift(A, n);
        for (int i = 0; i < n / 2; ++i) A[i] = -A[n / 2 + i], A[n / 2 + i] = 0;
        fft(A, n);
        for (int i = 0; i < n; ++i) A[i] *= F[i];
        ift(A, n);
        for (int i = 0; i < n / 2; ++i) f[n / 2 + i] = A[i];
    }
}
void Inv(const mint a[], const mint b[], mint g[], int n) {
        if (n == 1) {
        g[0] = b[0] * a[0].inv();
    } else {
        mint A[n];
        mint F[n];
        mint G[n];
        for (int i = 0; i < n / 2; ++i) G[i] = b[i];
        fft(G, n);
        Inv(a, F, n / 2);
        fft(F, n);
        for (int i = 0; i < n; ++i) G[i] *= F[i];
        ift(G, n);
        for (int i = n / 2; i < n; ++i) G[i] = 0;
        for (int i = 0; i < n / 2; ++i) g[i] = G[i];
        fft(G, n);
        for (int i = 0; i < n; ++i) A[i] = a[i];
        fft(A, n);
        for (int i = 0; i < n; ++i) A[i] *= G[i];
        ift(A, n);
        for (int i = 0; i < n / 2; ++i) A[i] = b[n / 2 + i] - A[n / 2 + i], A[n / 2 + i] = 0;
        fft(A, n);
        for (int i = 0; i < n; ++i) A[i] *= F[i];
        ift(A, n);
        for (int i = 0; i < n / 2; ++i) g[n / 2 + i] = A[i];
    }
}
void Log(const mint a[], mint f[], int n) {
    mint b[n];
    mint g[n];
    Der(a, b, n);
    Inv(a, b, g, n);
    Int(g, f, n);
}
void Sqrt(const mint a[], mint f[], int n) {
        if (n == 1) {
        f[0] = a[0].sqrt();
    } else {
        Sqrt(a, f, n / 2);
        mint B[n];
        for (int i = 0; i < n / 2; ++i) B[i] = f[i];
        fft(B, n);
        for (int i = 0; i < n; ++i) B[i] *= B[i];
        ift(B, n);
        for (int i = n / 2; i < n; ++i) B[i] = (a[i] - B[i]) * ((P + 1) / 2);
        Inv(f, B + n / 2, f + n / 2, n / 2);
    }
}
void Cbrt(const mint a[], mint f[], int n) {
        if (n == 1) {
        f[0] = a[0].cbrt();
    } else {
        Cbrt(a, f, n / 2);
        mint A[n];
        mint B[n];
        for (int i = 0; i < n / 2; ++i) B[i] = f[i];
        fft(B, n);
        for (int i = 0; i < n; ++i) A[i] = B[i] * B[i] * 3;
        ift(A, n);
        for (int i = 0; i < n; ++i) B[i] *= B[i] * B[i];
        ift(B, n);
        for (int i = n / 2; i < n; ++i) B[i] = (a[i] - B[i]);
        Inv(A, B + n / 2, f + n / 2, n / 2);
    }
}
int main() {
#ifdef LOCAL
    auto flush = [&]() {};
    auto ii = [&]() {
        int x;
        std::cin >> x;
        return x;
    };
    auto oo = [&](auto x, char c = 10) {
        std::cout << x << c << std::flush;
    };
#else
    char bufI[1 << 19], *ptrI = bufI, *endI = bufI + sizeof(bufI);
    char bufO[1 << 19], *ptrO = bufO, *endO = bufO + sizeof(bufO);
    fread(bufI, 1, sizeof(bufI), stdin);
    auto load = [&]() {
        memcpy(bufI, ptrI, endI - ptrI);
        fread(endI - ptrI + bufI, 1, ptrI - bufI, stdin);
        ptrI = bufI;
    };
    auto flush = [&]() {
        fwrite(bufO, 1, ptrO - bufO, stdout);
        ptrO = bufO;
    };
    auto ii = [&]() {
        if (endI - ptrI < 32) load();
        int x{};
        int n{};
        for (; *ptrI < 48; ++ptrI) n = *ptrI == 45;
        for (; *ptrI > 47; ++ptrI) x = x * 10 + *ptrI - 48;
        return n ? -x : +x;
    };
    auto oo = [&](auto x, char c = 10) {
        if (endO - ptrO < 32) flush();
        if (x < 0) x = -x, *ptrO++ = '-';
        char buf[20];
        char *end = buf + 20;
        char *ptr = buf + 20;
        *--ptr = c;
        for (; x >= 10; x /= 10)
            *--ptr = char(48 + x % 10);
        *--ptr = char(48 + x);
        memcpy(ptrO, ptr, end - ptr);
        ptrO += end - ptr;
    };
#endif
    int m = ii() + 1;
    int n = 2 << std::__lg(m);
    mint a[n];
    mint f[n];
    for (int i = 0; i < m; ++i) a[i] = ii();
    Cbrt(a, f, n);
    for (int i = 0; i < m; ++i) oo(f[i].x, ' ');
    flush();
}
