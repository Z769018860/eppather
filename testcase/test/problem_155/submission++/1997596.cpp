
#include <bits/stdc++.h>

std::ostream&operator<<(std::ostream&os,std::int8_t x){return os<<(int)x;}
std::ostream&operator<<(std::ostream&os,std::uint8_t x){return os<<(int)x;}
std::ostream&operator<<(std::ostream&os,const __int128_t &v){if(!v)os<<"0";__int128_t tmp=v<0?(os<<"-",-v):v;std::string s;while(tmp)s+='0'+(tmp%10),tmp/=10;return std::reverse(s.begin(),s.end()),os<<s;}
std::ostream&operator<<(std::ostream&os,const __uint128_t &v){if(!v)os<<"0";__uint128_t tmp=v;std::string s;while(tmp)s+='0'+(tmp%10),tmp/=10;return std::reverse(s.begin(),s.end()),os<<s;}
#define checkpoint() (void(0))
#define debug(...) (void(0))
#define debugArray(x,n) (void(0))
#define debugMatrix(x,h,w) (void(0))

#include <type_traits>
template <class Int> constexpr inline Int mod_inv(Int a, Int mod) {
 static_assert(std::is_signed_v<Int>);
 Int x= 1, y= 0, b= mod;
 for (Int q= 0, z= 0; b;) z= x, x= y, y= z - y * (q= a / b), z= a, a= b, b= z - b * q;
 return assert(a == 1), x < 0 ? mod - (-x) % mod : x % mod;
}
namespace math_internal {
using namespace std;
using u8= unsigned char;
using u32= unsigned;
using i64= long long;
using u64= unsigned long long;
using u128= __uint128_t;
#define CE constexpr
#define IL inline
#define NORM \
 if (n >= mod) n-= mod; \
 return n
#define PLUS(U, M) \
 CE IL U plus(U l, U r) const { return l+= r, l < (M) ? l : l - (M); }
#define DIFF(U, C, M) \
 CE IL U diff(U l, U r) const { return l-= r, l >> C ? l + (M) : l; }
#define SGN(U) \
 static CE IL U set(U n) { return n; } \
 static CE IL U get(U n) { return n; } \
 static CE IL U norm(U n) { return n; }
template <class u_t, class du_t, u8 B, u8 A> struct MP_Mo {
 u_t mod;
 CE MP_Mo(): mod(0), iv(0), r2(0) {}
 CE MP_Mo(u_t m): mod(m), iv(inv(m)), r2(-du_t(mod) % mod) {}
 CE IL u_t mul(u_t l, u_t r) const { return reduce(du_t(l) * r); }
 PLUS(u_t, mod << 1)
 DIFF(u_t, A, mod << 1)
 CE IL u_t set(u_t n) const { return mul(n, r2); }
 CE IL u_t get(u_t n) const {
  n= reduce(n);
  NORM;
 }
 CE IL u_t norm(u_t n) const { NORM; }
private:
 u_t iv, r2;
 static CE u_t inv(u_t n, int e= 6, u_t x= 1) { return e ? inv(n, e - 1, x * (2 - x * n)) : x; }
 CE IL u_t reduce(const du_t &w) const { return u_t(w >> B) + mod - ((du_t(u_t(w) * iv) * mod) >> B); }
};
struct MP_Na {
 u32 mod;
 CE MP_Na(): mod(0){};
 CE MP_Na(u32 m): mod(m) {}
 CE IL u32 mul(u32 l, u32 r) const { return u64(l) * r % mod; }
 PLUS(u32, mod) DIFF(u32, 31, mod) SGN(u32)
};
struct MP_Br {  
 u32 mod;
 CE MP_Br(): mod(0), s(0), x(0) {}
 CE MP_Br(u32 m): mod(m), s(95 - __builtin_clz(m - 1)), x(((u128(1) << s) + m - 1) / m) {}
 CE IL u32 mul(u32 l, u32 r) const { return rem(u64(l) * r); }
 PLUS(u32, mod) DIFF(u32, 31, mod) SGN(u32) private: u8 s;
 u64 x;
 CE IL u64 quo(u64 n) const { return (u128(x) * n) >> s; }
 CE IL u32 rem(u64 n) const { return n - quo(n) * mod; }
};
struct MP_Br2 {  
 u64 mod;
 CE MP_Br2(): mod(0), x(0) {}
 CE MP_Br2(u64 m): mod(m), x((u128(1) << 84) / m) {}
 CE IL u64 mul(u64 l, u64 r) const { return rem(u128(l) * r); }
 PLUS(u64, mod << 1)
 DIFF(u64, 63, mod << 1)
 static CE IL u64 set(u64 n) { return n; }
 CE IL u64 get(u64 n) const { NORM; }
 CE IL u64 norm(u64 n) const { NORM; }
private:
 u64 x;
 CE IL u128 quo(const u128 &n) const { return (n * x) >> 84; }
 CE IL u64 rem(const u128 &n) const { return n - quo(n) * mod; }
};
struct MP_D2B1 {
 u8 s;
 u64 mod, d, v;
 CE MP_D2B1(): s(0), mod(0), d(0), v(0) {}
 CE MP_D2B1(u64 m): s(__builtin_clzll(m)), mod(m), d(m << s), v(u128(-1) / d) {}
 CE IL u64 mul(u64 l, u64 r) const { return rem((u128(l) * r) << s) >> s; }
 PLUS(u64, mod) DIFF(u64, 63, mod) SGN(u64) private: CE IL u64 rem(const u128 &u) const {
  u128 q= (u >> 64) * v + u;
  u64 r= u64(u) - (q >> 64) * d - d;
  if (r > u64(q)) r+= d;
  if (r >= d) r-= d;
  return r;
 }
};
template <class u_t, class MP> CE u_t pow(u_t x, u64 k, const MP &md) {
 for (u_t ret= md.set(1);; x= md.mul(x, x))
  if (k & 1 ? ret= md.mul(ret, x) : 0; !(k>>= 1)) return ret;
}
#undef NORM
#undef PLUS
#undef DIFF
#undef SGN
#undef CE
}
namespace math_internal {
struct m_b {};
struct s_b: m_b {};
}
template <class mod_t> constexpr bool is_modint_v= std::is_base_of_v<math_internal::m_b, mod_t>;
template <class mod_t> constexpr bool is_staticmodint_v= std::is_base_of_v<math_internal::s_b, mod_t>;
namespace math_internal {
#define CE constexpr
template <class MP, u64 MOD> struct SB: s_b {
protected:
 static CE MP md= MP(MOD);
};
template <class Int, class U, class B> struct MInt: public B {
 using Uint= U;
 static CE inline auto mod() { return B::md.mod; }
 CE MInt(): x(0) {}
 template <class T, typename= enable_if_t<is_modint_v<T> && !is_same_v<T, MInt>>> CE MInt(T v): x(B::md.set(v.val() % B::md.mod)) {}
 CE MInt(__int128_t n): x(B::md.set((n < 0 ? ((n= (-n) % B::md.mod) ? B::md.mod - n : n) : n % B::md.mod))) {}
 CE MInt operator-() const { return MInt() - *this; }
#define FUNC(name, op) \
 CE MInt name const { \
  MInt ret; \
  return ret.x= op, ret; \
 }
 FUNC(operator+(const MInt & r), B::md.plus(x, r.x))
 FUNC(operator-(const MInt & r), B::md.diff(x, r.x))
 FUNC(operator*(const MInt & r), B::md.mul(x, r.x))
 FUNC(pow(u64 k), math_internal::pow(x, k, B::md))
#undef FUNC
 CE MInt operator/(const MInt& r) const { return *this * r.inv(); }
 CE MInt& operator+=(const MInt& r) { return *this= *this + r; }
 CE MInt& operator-=(const MInt& r) { return *this= *this - r; }
 CE MInt& operator*=(const MInt& r) { return *this= *this * r; }
 CE MInt& operator/=(const MInt& r) { return *this= *this / r; }
 CE bool operator==(const MInt& r) const { return B::md.norm(x) == B::md.norm(r.x); }
 CE bool operator!=(const MInt& r) const { return !(*this == r); }
 CE bool operator<(const MInt& r) const { return B::md.norm(x) < B::md.norm(r.x); }
 CE inline MInt inv() const { return mod_inv<Int>(val(), B::md.mod); }
 CE inline Uint val() const { return B::md.get(x); }
 friend ostream& operator<<(ostream& os, const MInt& r) { return os << r.val(); }
 friend istream& operator>>(istream& is, MInt& r) {
  i64 v;
  return is >> v, r= MInt(v), is;
 }
private:
 Uint x;
};
template <u64 MOD> using ModInt= conditional_t < (MOD < (1 << 30)) & MOD, MInt<int, u32, SB<MP_Mo<u32, u64, 32, 31>, MOD>>, conditional_t < (MOD < (1ull << 62)) & MOD, MInt<i64, u64, SB<MP_Mo<u64, u128, 64, 63>, MOD>>, conditional_t<MOD<(1u << 31), MInt<int, u32, SB<MP_Na, MOD>>, conditional_t<MOD<(1ull << 32), MInt<i64, u32, SB<MP_Na, MOD>>, conditional_t<MOD <= (1ull << 41), MInt<i64, u64, SB<MP_Br2, MOD>>, MInt<i64, u64, SB<MP_D2B1, MOD>>>>>>>;
#undef CE
}
using math_internal::ModInt;
namespace sps {
namespace sps_internal {
using namespace std;
#define ZETA(s, l) \
 if constexpr (!t) A[s + l]+= A[s]; \
 else if constexpr (t == 1) A[s + l]-= A[s]; \
 else if constexpr (t == 2) A[s]+= A[s + l]; \
 else A[s]-= A[s + l]
template <int t, class T> void rec(T A[], int l) {
 if (l > 127) {
  l>>= 1, rec<t>(A, l), rec<t>(A + l, l);
  for (int s= 0; s < l; ++s) ZETA(s, l);
 } else
  for (int k= 1; k < l; k<<= 1)
   for (int i= 0; i < l; i+= k + k)
    for (int j= 0; j < k; ++j) ZETA(i + j, k);
}
#undef ZETA
template <class T> void subset_zeta(vector<T>& f) { rec<0>(f.data(), f.size()); }
template <class T> void subset_mobius(vector<T>& f) { rec<1>(f.data(), f.size()); }
template <class T> void supset_zeta(vector<T>& f) { rec<2>(f.data(), f.size()); }
template <class T> void supset_mobius(vector<T>& f) { rec<3>(f.data(), f.size()); }
template <class T> vector<T> or_convolve(vector<T> f, vector<T> g) {
 subset_zeta(f), subset_zeta(g);
 for (int s= f.size(); s--;) f[s]*= g[s];
 return subset_mobius(f), f;
}
template <class T> vector<T> and_convolve(vector<T> f, vector<T> g) {
 supset_zeta(f), supset_zeta(g);
 for (int s= f.size(); s--;) f[s]*= g[s];
 return supset_mobius(f), f;
}
template <int t, class T> void rec_r(T A[], int l, int n, int c= 0) {
 if (l >= (n << 4)) {
  l>>= 1, rec_r<t>(A, l, n, c), rec_r<t>(A + l, l, n, c + 1);
  for (int s= l / n; s--;)
   if constexpr (!t)
    for (int d= 0, e= __builtin_popcount(s) + c + 1; d < e; ++d) A[s * n + d + l]+= A[s * n + d];
   else
    for (int d= __builtin_popcount(s) + c + 1; d < n; ++d) A[s * n + d + l]-= A[s * n + d];
 } else
  for (int k= 1, m= l / n; k < m; k<<= 1)
   for (int i= 0; i < m; i+= k + k)
    for (int j= 0; j < k; ++j)
     if constexpr (!t)
      for (int u= i + j, s= u + k, d= 0, e= __builtin_popcount(s) + c; d < e; ++d) A[s * n + d]+= A[u * n + d];
     else
      for (int u= i + j, s= u + k, d= __builtin_popcount(s) + c; d < n; ++d) A[s * n + d]-= A[u * n + d];
}
template <class T> void rnk_zeta(const T f[], T F[], int n) {
 for (int s= 1 << n; s--;) F[s * (n + 1) + __builtin_popcount(s)]= f[s];
 rec_r<0>(F, (n + 1) << n, n + 1);
}
template <class T> void rnk_mobius(T F[], T f[], int n) {
 rec_r<1>(F, (n + 1) << n, n + 1);
 for (int s= 1 << n; s--;) f[s]= F[s * (n + 1) + __builtin_popcount(s)];
}
template <class T> void cnv_(T A[], const T B[], int n) {
 for (int s= 1 << (n - 1); s--;) {
  T t, *a= A + s * n;
  const T* b= B + s * n;
  for (int c= __builtin_popcount(s), d= min(2 * c, n - 1), e; d >= c; a[d--]= t)
   for (t= 0, e= d - c; e <= c; ++e) t+= a[e] * b[d - e];
 }
}
template <class T> void cnv_na(const T f[], const T g[], T h[], int N) {
 for (int s= N, t; s--;)
  for (h[t= s]= f[s] * g[0]; t; --t&= s) h[s]+= f[s ^ t] * g[t];
}

template <class T> vector<T> convolve(const vector<T>& f, const vector<T>& g) {
 const int N= f.size(), n= __builtin_ctz(N);
 assert(!(N & (N - 1))), assert(N == (int)g.size());
 vector<T> h(N);
 if (n < 11) return cnv_na(f.data(), g.data(), h.data(), N), h;
 vector<T> F((n + 1) << n), G((n + 1) << n);
 return rnk_zeta(f.data(), F.data(), n), rnk_zeta(g.data(), G.data(), n), cnv_(F.data(), G.data(), n + 1), rnk_mobius(F.data(), h.data(), n), h;
}
template <class T> void div_na(T f[], const T g[], int N) {
 for (int s= 1; s < N; ++s)
  for (int t= s; t; --t&= s) f[s]-= f[s ^ t] * g[t];
}

template <class T> vector<T> inv(const vector<T>& f) {
 const int N= f.size(), n= __builtin_ctz(N);
 assert(!(N & (N - 1))), assert(f[0] == 1);
 vector<T> h(N);
 if (n < 11) return h[0]= 1, div_na(h.data(), f.data(), N), h;
 vector<T> F((n + 1) << n), G((n + 1) << n);
 rnk_zeta(f.data(), G.data(), n);
 for (int s= N; s--;) {
  T *a= F.data() + s * (n + 1), *b= G.data() + s * (n + 1);
  a[0]= 1;
  for (int d= 0, c= __builtin_popcount(s); d++ < n;)
   for (int e= max(0, d - c); e < d; ++e) a[d]-= a[e] * b[d - e];
 }
 return rnk_mobius(F.data(), h.data(), n), h;
}

template <class T> vector<T> div(vector<T> f, const vector<T>& g) {
 const int N= f.size(), n= __builtin_ctz(N);
 assert(!(N & (N - 1))), assert(N == (int)g.size()), assert(g[0] == 1);
 if (n < 12) return div_na(f.data(), g.data(), N), f;
 vector<T> F((n + 1) << n), G((n + 1) << n);
 rnk_zeta(f.data(), F.data(), n), rnk_zeta(g.data(), G.data(), n);
 for (int s= N; s--;) {
  T *a= F.data() + s * (n + 1), *b= G.data() + s * (n + 1);
  for (int d= 0, c= __builtin_popcount(s); d++ < n;)
   for (int e= max(0, d - c); e < d; ++e) a[d]-= a[e] * b[d - e];
 }
 return rnk_mobius(F.data(), f.data(), n), f;
}
template <class T, class P> void oncnv_(const T f[], T h[], const P& phi, int n) {
 vector<T> F((n + 1) << n), G((n + 1) << n);
 rnk_zeta(f, F.data(), n), fill_n(G.data(), 1 << n, h[0]);
 T* a= G.data() + (1 << n);
 for (int l= 1 << n; l>>= 1;) phi(l, a[l]= h[0] * f[l]), h[l]= a[l];
 for (int d= 2, s; d <= n; ++d) {
  for (rec<0>(a, 1 << n), a+= (s= 1 << n); s--;)
   if (int c= __builtin_popcount(s); c <= d && d <= 2 * c)
    for (int e= d; e--;) a[s]+= G[e << n | s] * F[s * (n + 1) + d - e];
  for (rec<1>(a, 1 << n), s= 1 << n; s--;)
   if (__builtin_popcount(s) == d) phi(s, a[s]), h[s]= a[s];
   else a[s]= 0;
 }
}

template <class T, class P> vector<T> semi_relaxed_convolve(const vector<T>& f, T init, const P& phi) {
 const int N= f.size(), n= __builtin_ctz(N);
 assert(!(N & (N - 1)));
 vector<T> h(N);
 if (h[0]= init; n < 12) {
  for (int s= 1, t; s < N; phi(s, h[s]), ++s)
   for (t= s; t; --t&= s) h[s]+= h[s ^ t] * f[t];
 } else oncnv_(f.data(), h.data(), phi, n);
 return h;
}

template <class T, class P> vector<T> self_relaxed_convolve(const P& phi, int n) {
 const int e= min(n, 12);
 int i= 0, l= 1;
 vector<T> f(1 << n);
 for (int u= 1; i < e; l<<= 1, ++i)
  for (int s= 0; s < l; phi(u, f[u]), ++s, ++u)
   for (int t= s; t; --t&= s) f[u]+= f[u ^ t] * f[t];
 for (; i < n; l<<= 1, ++i)
  oncnv_(
      f.data(), f.data() + l, [&](int s, T& x) { phi(s | l, x); }, i);
 return f;
}

template <class T> vector<T> exp(const vector<T>& f) {
 const int N= f.size(), n= __builtin_ctz(N), e= min(N, 1 << 11);
 assert(!(N & (N - 1))), assert(f[0] == 0);
 vector<T> h(N);
 int i= 0, l= 1;
 for (h[0]= 1; l < e; l<<= 1, ++i) cnv_na(h.data(), f.data() + l, h.data() + l, l);
 for (; l < N; l<<= 1, ++i) {
  vector<T> F((i + 1) << i), G((i + 1) << i);
  rnk_zeta(h.data(), F.data(), i), rnk_zeta(f.data() + l, G.data(), i), cnv_(F.data(), G.data(), i + 1), rnk_mobius(F.data(), h.data() + l, i);
 }
 return h;
}

template <class T> vector<T> log(const vector<T>& f) {
 const int N= f.size(), n= __builtin_ctz(N);
 assert(!(N & (N - 1))), assert(f[0] == 1);
 vector<T> h(N);
 int i= n - 1, l= N >> 1;
 if (i > 11) {
  vector<T> G(n << (n - 1));
  rnk_zeta(f.data(), G.data(), n - 1);
  for (; i > 11; l>>= 1, --i) {
   vector<T> F((i + 1) << i);
   rnk_zeta(f.data() + l, F.data(), i);
   for (int s= l; s--;) {
    T *a= F.data() + s * (i + 1), *b= G.data() + s * n;
    for (int d= 0, c= __builtin_popcount(s); d++ < i;)
     for (int e= max(0, d - c); e < d; ++e) a[d]-= a[e] * b[d - e];
   }
   rnk_mobius(F.data(), h.data() + l, i);
  }
 }
 for (; l; l>>= 1) copy_n(f.data() + l, l, h.data() + l), div_na(h.data() + l, f.data(), l);
 return h;
}

template <class T> vector<T> egf_comp(const vector<T>& F, const vector<T>& f) {
 const int N= f.size(), n= __builtin_ctz(N), e= min(N, 1 << 11);
 assert(!(N & (N - 1))), assert(f[0] == 0);
 vector<T> h(N);
 T* b= h.data() + N;
 for (int i= n - F.size(); i++ < n;) h[N - (1 << i)]= F[n - i];
 int i= 0, l= 1;
 for (; l < e; l<<= 1, ++i)
  for (int j= N >> 1; j >= l; j>>= 1) cnv_na(b - j, f.data() + l, b - j - j + l, l);
 if (l < N) {
  vector<T> A(n << (n - 1)), B(n << (n - 1));
  for (; l < N; l<<= 1, ++i) {
   fill_n(B.data(), (i + 1) << i, 0), rnk_zeta(f.data() + l, B.data(), i);
   for (int j= N >> 1; j >= l; j>>= 1) fill_n(A.data(), (i + 1) << i, 0), rnk_zeta(b - j, A.data(), i), cnv_(A.data(), B.data(), i + 1), rnk_mobius(A.data(), b - j - j + l, i);
  }
 }
 return h;
}

template <class T> vector<T> poly_comp(vector<T> P, vector<T> f) {
 const int N= f.size(), n= __builtin_ctz(N);
 assert(!(N & (N - 1)));
 vector<T> F(n + 1);
 for (int j= 0, e= P.size();; ++j, --e) {
  for (int i= e; i--;) (F[j]*= f[0])+= P[i];
  if (j == n || e <= 1) break;
  for (int i= 1; i < e; ++i) P[i - 1]= P[i] * i;
 }
 return f[0]= 0, egf_comp(F, f);
}
template <class T> vector<T> _egfT(T* b, T* h, int M, int n) {
 T *a, *d;
 vector<T> c(n + 1);
 int l= M;
 if (int i= __builtin_ctz(M); i > 10) {
  vector<T> F((i + 1) << i), G((i + 1) << i);
  for (int m, s; i > 10; fill_n(F.data(), (i + 1) << i, 0), rnk_zeta(h, F.data(), i), cnv_(F.data(), G.data(), i + 1), rnk_mobius(F.data(), h, i), b-= (l>>= 1), --i)
   for (fill_n(G.data(), (i + 1) << i, 0), rnk_zeta(b, G.data(), i), m= M; m > l; m>>= 1)
    for (a= h + (m - l), fill_n(F.data(), (i + 1) << i, 0), rnk_zeta(a + m - l, F.data(), i), cnv_(F.data(), G.data(), i + 1), rec_r<1>(F.data(), (i + 1) << i, i + 1), s= l; s--;) a[s]+= F[s * (i + 1) + __builtin_popcount(s)];
 }
 for (; l; cnv_na(h, b, h, l), b-= (l>>= 1))
  for (int m= M, s, t; m > l; m>>= 1)
   for (a= h + (m - l), d= a + (m - l), s= l; s--;)
    for (a[t= s]+= d[s] * b[0]; t; --t&= s) a[s]+= d[s ^ t] * b[t];
 for (int i= 1; i <= n; ++i) c[i]= h[(1 << (n - i)) - 1];
 return c;
}

template <class T> vector<T> egf_T(vector<T> f) {
 const int N= f.size(), n= __builtin_ctz(N);
 assert(!(N & (N - 1)));
 if (n == 0) return {1};
 if (n == 1) return {0, f[1]};
 return _egfT(f.data() + (N >> 2), f.data() + (N >> 1), N >> 2, n);
}

template <class T> vector<T> egf_T(const vector<T>& f, vector<T> g) {
 const int N= f.size(), n= __builtin_ctz(N);
 assert(!(N & (N - 1)));
 if (n == 0) return {g[1]};
 return _egfT(f.data() + (N >> 1), g.data(), N >> 1, n);
}
}
using sps_internal::subset_zeta, sps_internal::subset_mobius, sps_internal::supset_zeta, sps_internal::supset_mobius, sps_internal::or_convolve, sps_internal::and_convolve, sps_internal::convolve, sps_internal::semi_relaxed_convolve, sps_internal::self_relaxed_convolve, sps_internal::inv, sps_internal::div, sps_internal::exp, sps_internal::log, sps_internal::egf_comp, sps_internal::poly_comp, sps_internal::egf_T;
}
class UndirectedGraphSetPowerSeries {
 template <class T> using Sps= std::vector<T>;
 template <class T> using Poly= std::vector<T>;
 const int n, N;
 std::vector<int> adj, es;
 template <class T> static inline T pow(T x, int k) {
  for (T ret(1);; x*= x)
   if (k& 1 ? ret*= x : 0; !(k>>= 1)) return ret;
 }
 template <class F> inline void bfs(int s, const F& f) const {
  for (int t= s, u, j; t;)
   for (f(u= 1 << __builtin_ctz(t)); u;) j= __builtin_ctz(u), t^= 1 << j, u^= 1 << j, u|= es[j] & t;
 }
 template <class T, class G> static inline void transform_articulation(Sps<T>& f, const G& g) {
  const int M= f.size() / 2;
  Sps<T> tmp(M);
  for (int I= M; I; I>>= 1) {
   for (int t= 0; t < M; t+= I)
    for (int u= I, t2= t << 1; u--;) tmp[t | u]= f[t2 | I | u];
   tmp= g(tmp);
   for (int t= 0; t < M; t+= I)
    for (int u= I, t2= t << 1; u--;) f[t2 | I | u]= tmp[t | u];
  }
 }
 template <class T, bool b> inline void transform_bridge(Sps<T>& f) const {
  const int M= N / 2;
  Sps<T> tmp(M), tmp2;
  for (int i= n, I= M; --i; I>>= 1) {
   for (int t= 0; t < M; t+= I)
    for (int u= I, t2= t << 1; u--;) tmp[t | u]= f[t2 | I | u];
   tmp2.assign(M, 0);
   for (int t= 0; t < M; t+= I)
    for (int j= i, J= I, t2= t << 1; J>>= 1, j--;)
     for (int s= J, J2= J * 2; s < I; s+= J2)
      for (int u= s + J; u-- > s;) {
       if constexpr (b) tmp2[t | u]+= f[t2 | u] * adj[i * n + j];
       else tmp2[t | u]-= f[t2 | u] * adj[i * n + j];
      }
   tmp= sps::convolve(tmp, sps::exp(tmp2));
   for (int t= 0; t < M; t+= I)
    for (int u= I, t2= t << 1; u--;) f[t2 | I | u]= tmp[t | u];
  }
 }
public:
 UndirectedGraphSetPowerSeries(int n): n(n), N(1 << n), adj(n * n), es(n) {}
 UndirectedGraphSetPowerSeries(const std::vector<std::vector<int>>& g): n(g.size()), N(1 << n), adj(n * n), es(n) {
  for (int i= n; i--;)
   for (int j= i; j--;) assert(g[i][j] == g[j][i]);
  for (int i= n; i--;)
   for (int j= n; j--;) adj[i * n + j]= g[i][j];
  for (int i= n; i--;)
   for (int j= n; j--;) es[i]|= !(!(adj[i * n + j])) << j;
 }
 void add_edge(int u, int v, int cnt= 1) {
  adj[u * n + v]= (adj[v * n + u]+= cnt), es[u]|= (1 << v), es[v]|= (1 << u);
  if (!(adj[u * n + v])) es[u]^= (1 << v), es[v]^= (1 << u);
 }
 const auto operator[](int u) const { return adj.begin() + (u * n); }
 template <class T> static inline Sps<T> only_connected(const Sps<T>& f) { return sps::log(f); }
 template <class T> static inline Sps<T> disjoint_union(const Sps<T>& f) { return sps::exp(f); }
 template <class T> static inline Sps<T> only_biconnected(Sps<T> f) { return transform_articulation(f, sps::log<T>), f; }
 template <class T> static inline Sps<T> articulation_union(Sps<T> f) { return transform_articulation(f, sps::exp<T>), f; }
 template <class T> inline Sps<T> only_2edge_connected(Sps<T> f) const { return transform_bridge<T, false>(f), f; }
 template <class T> inline Sps<T> bridge_union(Sps<T> f) const { return transform_bridge<T, true>(f), f; }
 inline Sps<int> edge_num() const {
  Sps<int> ret(N, 0);
  for (int i= n; i--;)
   for (int j= i; j--;) ret[(1 << i) | (1 << j)]= adj[i * n + j];
  return sps::subset_zeta(ret), ret;
 }
 inline Sps<int> connected_component_num() const {
  Sps<int> ret(N, 0);
  for (int s= N; s--;) bfs(s, [&](int) { ret[s]++; });
  return ret;
 }
 inline Sps<int> cycle_space_rank() const {
  Sps<int> e= edge_num(), k= connected_component_num(), ret(N, 0);
  for (int s= N; s--;) ret[s]= e[s] + k[s] - __builtin_popcount(s);
  return ret;
 }
 inline Sps<int> odd_deg_num() const {
  Sps<int> ret(N, 0);
  for (int i= n, I= N; I>>= 1, i--;)
   for (int t= 0, I2= I << 1; t < N; t+= I2)
    for (int u= I, cnt, v, j; u--; ret[t | I | u]+= cnt & 1)
     for (cnt= 0, v= t | u; v; v^= 1 << j) cnt+= adj[i * n + (j= __builtin_ctz(v))];
  return ret;
 }
 inline Sps<int> selfloop_num() const {
  Sps<int> ret(N, 0);
  for (int i= 0, I= 1; i < n; ++i, I<<= 1)
   for (int u= I; u--;) ret[I | u]= ret[u] + adj[i * n + i];
  return ret;
 }
 template <class T> static inline Sps<T> space_size(const Sps<int>& rank) {
  Sps<T> ret(rank.size());
  for (int s= rank.size(); s--;) ret[s]= pow<T>(2, rank[s]);
  return ret;
 }
 template <class T> inline Sps<T> graph() const { return space_size<T>(edge_num()); }
 template <class T> inline Sps<T> cycle_space_size() const { return space_size<T>(cycle_space_rank()); }
 template <class T> inline Sps<T> connected_graph() const { return sps::log(graph<T>()); }
 template <class T> inline Sps<T> eulerian_graph() const { return sps::log(cycle_space_size<T>()); }
 template <class T> inline Sps<T> connected_biparate_graph() const {
  Sps<T> tmp= graph<T>(), ret(N, 1);
  for (int s= N; s--;) ret[s]/= tmp[s];
  ret= sps::convolve(ret, ret);
  for (int s= N; s--;) ret[s]*= tmp[s];
  ret= sps::log(ret);
  for (int s= N; s--;) ret[s]/= 2;
  return ret;
 }
 template <class T> inline Sps<T> tree() const {
  Sps<int> e= edge_num();
  Sps<T> ret= {0, 1};
  ret.reserve(N);
  for (int I= 2; I < N; I<<= 1) {
   Sps<T> g(ret);
   for (int s= I; --s;) g[s]*= e[s | I] - e[s] - e[I];
   g= sps::exp(g), std::copy(g.begin(), g.end(), std::back_inserter(ret));
  }
  return ret;
 }
 template <class T> inline Sps<T> forest() const { return sps::exp(tree<T>()); }
 template <class T> inline Sps<T> cycle_graph() const {
  T dp[N][n - 1];
  Sps<T> ret(N, 0);
  for (int i= n, I= N; I>>= 1, --i;) {
   for (int s= I; --s;) std::fill_n(dp[s], i, 0);
   for (int j= i; j--;) dp[1 << j][j]= adj[i * n + j];
   for (int s= 1; s < I; ++s)
    for (int t= s, j, u, r, k; t; ret[s | I]+= dp[s][j] * adj[j * n + i])
     for (t^= 1 << (j= __builtin_ctz(t)), u= r= s ^ (1 << j); u; dp[s][j]+= dp[r][k] * adj[k * n + j]) u^= 1 << (k= __builtin_ctz(u));
  }
  for (int i= n; i--;)
   for (int j= i; j--;) ret[(1 << i) | (1 << j)]-= adj[i * n + j];
  for (int s= N; --s;) ret[s]/= 2;
  return ret;
 }
 template <class T> inline Sps<T> biconnected_graph() const {
  Sps<T> ret= connected_graph<T>();
  return transform_articulation(ret, sps::log<T>), ret;
 }
 template <class T> inline Sps<T> two_edge_connected_graph() const {
  Sps<T> ret= connected_graph<T>();
  return transform_bridge<T, false>(ret), ret;
 }
 template <class T> inline Sps<T> cactus_graph() const {
  auto ret= cycle_graph<T>();
  for (int i= n; i--;)
   for (int j= i; j--;) ret[(1 << i) | (1 << j)]+= adj[i * n + j];
  return transform_articulation(ret, sps::exp<T>), ret;
 }
 template <class T> inline Sps<T> acyclic_orientations() const {
  auto k= connected_component_num();
  Sps<T> g(N, 0);
  for (int s= N; --s;)
   if (k[s] == __builtin_popcount(s)) g[s]= k[s] & 1 ? -1 : 1;
  return g[0]= 1, sps::inv(g);
 }
 template <class T> inline std::vector<T> colorings_using_exactly_k_colors_num() const {
  if (n == 0) return {0};  
  auto k= connected_component_num();
  std::vector<T> indep(N, 0);
  for (int s= N; --s;) indep[s]= k[s] == __builtin_popcount(s);
  return sps::egf_T(indep);
 }
 template <class T> inline Poly<T> chromatic_polynomial() const {
  auto e= colorings_using_exactly_k_colors_num<T>();
  if (e.back() == 0) return {0};
  Poly<T> ret(n + 1, 0);
  T tmp[n]= {1};
  for (int i= 1, j; i < n; ++i)
   for (j= i; j--; tmp[j]*= -i) ret[j + 1]+= tmp[j] * e[i], tmp[j + 1]+= tmp[j];
  for (int j= n; j--;) ret[j + 1]+= tmp[j];
  return ret;
 }
 template <class T> inline T tutte_polynomial(T x, T y) const {
  int sum[N], s, t, lim= 2, i, j;
  T fum[10'000]= {0, 1};
  std::vector<T> g= {0}, h;
  for (g.reserve(N), h.reserve(N), i= 0; i < n; ++i) {
   for (sum[0]= j= 0; j < i; j++)
    for (s= t= 1 << j; s--;) sum[s | t]= sum[s] + adj[i * n + j];
   for (h.resize(s= 1 << i); s--; h[s]= g[s] * fum[sum[s]])
    for (; lim <= sum[s]; lim++) fum[lim]= fum[lim - 1] * y + 1;
   h= sps::exp(h), std::copy(h.begin(), h.end(), std::back_inserter(g));
  }
  for (x-= 1, t= ~0, j= 0, i= n; i--;) j+= adj[i * n + i];
  for (bfs((s= N) - 1, [&](int u) { t^= u; }); --s&= t;) g[s]*= x;
  return sps::exp(g)[N - 1] * pow(y, j);
 }
};
using namespace std;
signed main() {
 cin.tie(0);
 ios::sync_with_stdio(false);
 using Mint= ModInt<998244353>;
 int n;
 cin >> n;
 UndirectedGraphSetPowerSeries g(n);
 for (int i= 0; i < n; ++i)
  for (int j= 0; j < n; ++j) {
   bool c;
   cin >> c;
   if (c && i < j) g.add_edge(i, j);
  }
 Mint x, y;
 cin >> x >> y;
 cout << g.tutte_polynomial(x, y) << '\n';
 return 0;
}
