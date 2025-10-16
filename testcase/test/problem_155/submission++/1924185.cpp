#include <bits/stdc++.h>

std::ostream&operator<<(std::ostream&os,std::int8_t x){return os<<(int)x;}
std::ostream&operator<<(std::ostream&os,std::uint8_t x){return os<<(int)x;}
std::ostream&operator<<(std::ostream&os,const __int128_t &v){if(!v)os<<"0";__int128_t tmp=v<0?(os<<"-",-v):v;std::string s;while(tmp)s+='0'+(tmp%10),tmp/=10;return std::reverse(s.begin(),s.end()),os<<s;}
std::ostream&operator<<(std::ostream&os,const __uint128_t &v){if(!v)os<<"0";__uint128_t tmp=v;std::string s;while(tmp)s+='0'+(tmp%10),tmp/=10;return std::reverse(s.begin(),s.end()),os<<s;}

#define checkpoint() (void(0))
#define debug(...) (void(0))
#define debugArray(x,n) (void(0))
#define debugMatrix(x,h,w) (void(0))

#ifdef __LOCAL

#undef checkpoint
#undef debug
#undef debugArray
#undef debugMatrix
template<class T>std::ostream &operator<<(std::ostream&,const std::vector<T>&);
template<class T>std::ostream &operator<<(std::ostream&,const std::set<T>&);
template<class T,class U>std::ostream &operator<<(std::ostream&os,const std::pair<T,U>&x){return os<<"("<<x.first<<", "<<x.second<<")";}
template<class T,std::size_t _Nm>std::ostream&operator<<(std::ostream &os,const std::array<T, _Nm> &arr) {os<<'['<<arr[0];for(std::size_t _=1;_<_Nm;++_)os<<", "<<arr[_];return os<<']';}
template<class Tup,std::size_t... I>void print(std::ostream&os,const Tup &x,std::index_sequence<I...>){(void)(int[]){(os<<std::get<I>(x)<<", ",0)...};}
template<class... Args>std::ostream &operator<<(std::ostream&os,const std::tuple<Args...> &x) {static constexpr std::size_t N = sizeof...(Args);os<<"(";if constexpr(N>=2)print(os,x,std::make_index_sequence<N-1>());return os<<std::get<N-1>(x)<<")";}
template<class T>std::ostream &operator<<(std::ostream&os,const std::vector<T>&vec){os<<'[';for(int _=0,__= vec.size();_<__;++_)os<<(_ ?", ":"")<<vec[_];return os<<']';}
template<class T>std::ostream &operator<<(std::ostream&os,const std::set<T>&s){os<<'{';int _=0;for(const auto &x:s)os<<(_++ ? ", " : "")<<x; return os << '}';}
const std::string COLOR_RESET="\033[0m",BRIGHT_GREEN="\033[1;32m",BRIGHT_RED="\033[1;31m",BRIGHT_CYAN="\033[1;36m",NORMAL_CROSSED="\033[0;9;37m",ITALIC="\033[3m",BOLD="\033[1m",RED_BACKGROUND="\033[1;41m",NORMAL_FAINT="\033[0;2m";
#define func_LINE_FILE  NORMAL_FAINT<<" in "<<BOLD<<__func__<<NORMAL_FAINT<<ITALIC<<" (L"<<__LINE__<<") "<< __FILE__<<COLOR_RESET
#define checkpoint() std::cerr<<BRIGHT_RED<<"< check point! >"<<func_LINE_FILE<<'\n'
template <class T, class... Args> void debug__(const std::string &s, const T &a, const Args &...x) {std::cerr << BRIGHT_CYAN << s << COLOR_RESET << " = ";std::cerr << a;(std::cerr << ... << (std::cerr << ", ", x));std::cerr << func_LINE_FILE << '\n';}
#define debug(...) debug__(#__VA_ARGS__,__VA_ARGS__)
#define debugArray(x, n) do{std::cerr<<BRIGHT_CYAN<<#x<<COLOR_RESET<<" = ["<<x[0];for(int _=1;_<(int)(n);++_)std::cerr<<", "<<x[_];std::cerr<<"]"<<func_LINE_FILE<<'\n';}while(0)
#define debugMatrix(x, h, w) do{std::cerr<<BRIGHT_CYAN<<#x<<"\n"<<COLOR_RESET<<"= ";for(int _=0;(_)<(int)(h);++_){std::cerr<<((_?"   [":"[["));for(int __=0;__<(int)(w);++__)std::cerr<<((__?", ":""))<<x[_][__];std::cerr<<"]"<<(_+1==(int)(h)?"]":",\n");}std::cerr<<func_LINE_FILE<<'\n';}while(0)
#endif

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
 CE IL U plus(U l, U r) const { \
  if (l+= r; l >= M) l-= M; \
  return l; \
 }
#define DIFF(U, C, M) \
 CE IL U diff(U l, U r) const { \
  if (l-= r; l >> C) l+= M; \
  return l; \
 }
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
 template <class T, enable_if_t<is_modint_v<T> && !is_same_v<T, MInt>, nullptr_t> = nullptr> CE MInt(T v): x(B::md.set(v.val() % B::md.mod)) {}
 CE MInt(__int128_t n): x(B::md.set((n < 0 ? ((n= (-n) % B::md.mod) ? B::md.mod - n : n) : n % B::md.mod))) {}
 CE MInt operator-() const { return MInt() - *this; }
#define FUNC(name, op) \
 CE MInt name const { \
  MInt ret; \
  ret.x= op; \
  return ret; \
 }
 FUNC(operator+(const MInt &r), B::md.plus(x, r.x))
 FUNC(operator-(const MInt &r), B::md.diff(x, r.x))
 FUNC(operator*(const MInt &r), B::md.mul(x, r.x))
 FUNC(pow(u64 k), math_internal::pow(x, k, B::md))
#undef FUNC
 CE MInt operator/(const MInt &r) const { return *this * r.inv(); }
 CE MInt &operator+=(const MInt &r) { return *this= *this + r; }
 CE MInt &operator-=(const MInt &r) { return *this= *this - r; }
 CE MInt &operator*=(const MInt &r) { return *this= *this * r; }
 CE MInt &operator/=(const MInt &r) { return *this= *this / r; }
 CE bool operator==(const MInt &r) const { return B::md.norm(x) == B::md.norm(r.x); }
 CE bool operator!=(const MInt &r) const { return !(*this == r); }
 CE bool operator<(const MInt &r) const { return B::md.norm(x) < B::md.norm(r.x); }
 CE inline MInt inv() const { return mod_inv<Int>(val(), B::md.mod); }
 CE inline Uint val() const { return B::md.get(x); }
 friend ostream &operator<<(ostream &os, const MInt &r) { return os << r.val(); }
 friend istream &operator>>(istream &is, MInt &r) {
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
template <class mod_t, size_t LM> mod_t get_inv(int n) {
 static_assert(is_modint_v<mod_t>);
 static const auto m= mod_t::mod();
 static mod_t dat[LM];
 static int l= 1;
 if (l == 1) dat[l++]= 1;
 while (l <= n) dat[l++]= dat[m % l] * (m - m / l);
 return dat[n];
}
template <unsigned short MAX_N= 21> struct SetPowerSeries {
#define SUBSET_REP(i, j, n) \
 for (int _= (n), _e= (n); _>>= 1;) \
  for (int __= 0, _2= _ << 1; __ < _e; __+= _2) \
   for (int j= __, i= j | _, ___= i; j < ___; ++j, ++i)
 template <typename T> static inline void ranked_zeta_tr(const T f[], T ret[][MAX_N + 1], const int sz) {
  for (int S= sz, c; S--;) ret[S][c= __builtin_popcount(S)]= f[S], std::fill_n(ret[S], c, 0);
  SUBSET_REP(S, U, sz)
  for (int d= __builtin_popcount(S); d--;) ret[S][d]+= ret[U][d];
 }
 template <typename T> static inline void conv_na(const T f[], const T g[], T ret[], const int sz) {
  for (int s= sz, t; s--;)
   for (ret[t= s]= f[s] * g[0]; t; --t&= s) ret[s]+= f[s ^ t] * g[t];
 }
 template <typename T> static inline void conv_tr(const T f[], const T g[], T ret[], const int sz) {
  static T F[1 << MAX_N][MAX_N + 1], G[1 << MAX_N][MAX_N + 1];
  T tmp[MAX_N + 1];
  ranked_zeta_tr(f, F, sz), ranked_zeta_tr(g, G, sz);
  const int n= __builtin_ctz(sz);
  for (int S= sz, c, d, e, bg; S--;) {
   c= __builtin_popcount(S), bg= std::min(2 * c, n);
   for (d= bg; d >= c; d--)
    for (tmp[d]= 0, e= d - c; e <= c; ++e) tmp[d]+= F[S][e] * G[S][d - e];
   for (d= bg; d >= c; d--) F[S][d]= tmp[d];
  }
  SUBSET_REP(S, U, sz)
  for (int c= __builtin_popcount(U), d= std::min(2 * c, n); d > c; d--) F[S][d]-= F[U][d];
  for (int S= sz; S--;) ret[S]= F[S][__builtin_popcount(S)];
 }
 template <typename T, class F> static inline void onconv_na(const T g[], T ret[], const F &phi, const int sz) {
  for (int s= 1, t; s < sz; phi(s, ret[s]), ++s)
   for (ret[t= s]= 0; t; --t&= s) ret[s]+= ret[s ^ t] * g[t];
 }
 template <typename T, class F> static inline void onconv_tr(const T g[], T ret[], const F &phi, const int sz) {
  static T G[1 << MAX_N][MAX_N + 1], mat[MAX_N + 1][1 << MAX_N];
  const int n= __builtin_ctz(sz);
  ranked_zeta_tr(g, G, sz), std::fill_n(mat[0], sz, ret[0]);
  for (int d= n; d; d--) std::fill_n(mat[d], sz, 0);
  for (int I= sz; I>>= 1;) phi(I, mat[1][I]= ret[0] * g[I]);
  for (int d= 2; d <= n; ++d) {
   SUBSET_REP(S, U, sz) mat[d - 1][S]+= mat[d - 1][U];
   for (int S= sz; S--;)
    if (int c= __builtin_popcount(S); c <= d && d <= 2 * c)
     for (int e= d; e--;) mat[d][S]+= mat[e][S] * G[S][d - e];
   SUBSET_REP(S, U, sz) mat[d][S]-= mat[d][U];
   for (int S= sz; S--;) __builtin_popcount(S) == d ? phi(S, mat[d][S]), 0 : (mat[d][S]= 0);
  }
  for (int S= sz; --S;) ret[S]= mat[__builtin_popcount(S)][S];
 }
public:
 template <typename T>  
 static inline void subset_sum(std::vector<T> &f) {
  SUBSET_REP(S, U, f.size()) f[S]+= f[U];
 }
 template <typename T>  
 static inline void subset_sum_inv(std::vector<T> &f) {
  SUBSET_REP(S, U, f.size()) f[S]-= f[U];
 }
 template <class T>  
 static inline std::vector<T> convolve(const std::vector<T> &f, const std::vector<T> &g) {
  const int sz= f.size(), n= __builtin_ctz(sz);
  std::vector<T> ret(sz);
  if (n <= 10) return conv_na(f.data(), g.data(), ret.data(), sz), ret;
  assert(sz == 1 << n && sz == (int)g.size());
  return conv_tr(f.data(), g.data(), ret.data(), sz), ret;
 }
 
 template <class T, class F= void (*)(int, T &)>  
 static inline std::vector<T> semi_relaxed_convolve(
     const std::vector<T> &g, T init, const F &phi= [](int, T &) {}) {
  const int sz= g.size(), n= __builtin_ctz(sz);
  std::vector<T> ret(sz);
  ret[0]= init;
  if (n <= 12) return onconv_na(g.data(), ret.data(), phi, sz), ret;
  assert(sz == 1 << n);
  return onconv_tr(g.data(), ret.data(), phi, sz), ret;
 }
 
 template <class T, class F>  
 static inline std::vector<T> self_relaxed_convolve(int n, const F &phi) {
  assert(__builtin_popcount(n) == 1);
  int I= 1, ed= std::min(1 << 13, n);
  std::vector<T> ret(n, 0);
  for (int s, t, u= 1; I < ed; I<<= 1)
   for (t= s= 0; s < I; phi(u, ret[u]), t= ++s, ++u)
    for (ret[u]= 0; t; --t&= s) ret[u]+= ret[u ^ t] * ret[t];
  T *h= ret.data();
  for (; I < n; I<<= 1)
   phi(I, ret[I]), onconv_tr(
                       h, h + I, [&](int s, T &x) { phi(s | I, x); }, I);
  return ret;
 }
 
 
 template <class T, class EGF>  
 static inline std::vector<T> composite(const std::vector<T> &f, const EGF &F) {
  const int sz= f.size(), m= __builtin_ctz(sz), sz2= sz >> 1;
  assert(sz == 1 << m), assert(f.at(0) == 0);
  std::vector<T> ret(sz);
  T *h= ret.data() + sz;
  const T *g= f.data();
  for (int i= 0; i <= m; ++i) ret[sz - (1 << i)]= F[m - i];
  int l= 1, ed= std::min(sz, 1 << 11), j;
  for (; l < ed; l<<= 1)
   for (j= sz2; j >= l; j>>= 1) conv_na(h - j, g + l, h - j - j + l, l);
  for (; l < sz; l<<= 1)
   for (j= sz2; j >= l; j>>= 1) conv_tr(h - j, g + l, h - j - j + l, l);
  return ret;
 }
 
 template <class T>  
 static inline std::vector<T> exp(const std::vector<T> &f) {
  const int sz= f.size();
  assert(!(sz & (sz - 1))), assert(f.at(0) == 0);
  T h[sz];
  const T *g= f.data();
  int l= 1, ed= std::min(sz, 1 << 11);
  for (h[0]= 1; l < ed; l<<= 1) conv_na(h, g + l, h + l, l);
  for (; l < sz; l<<= 1) conv_tr(h, g + l, h + l, l);
  return std::vector<T>(h, h + sz);
 }
 
 template <class T>  
 static inline std::vector<T> log(const std::vector<T> &f) {
  const int sz= f.size();
  assert(!(sz & (sz - 1))), assert(f.at(0) == T(1));
  int I= 2, ed= std::min(sz, 1 << 13);
  T h[sz];
  const T *g= f.data();
  for (std::copy_n(g, ed, h); I < ed; I<<= 1)
   for (int s= 1, u= s | I; s < I; ++s, ++u)
    for (int t= s; t; --t&= s) h[u]-= h[u ^ t] * f[t];
  for (; I < sz; I<<= 1)
   h[I]= g[I], onconv_tr(
                   g, h + I, [&](int s, T &x) { x= g[I | s] - x; }, I);
  return h[0]= 0, std::vector<T>(h, h + sz);
 }
 
 template <class T>  
 static inline std::vector<T> pow(std::vector<T> f, uint64_t k) {
  const int sz= f.size(), n= __builtin_ctz(sz);
  assert(sz == 1 << n);
  T F[MAX_N + 1]= {1}, pw= 1, bs= f[0];
  int i= 1, ed= std::min<uint64_t>(n, k);
  for (; i <= ed; ++i) F[i]= F[i - 1] * (k - i + 1);
  for (auto e= k - --i; e; e>>= 1, bs*= bs)
   if (e & 1) pw*= bs;
  for (; i >= 0; --i, pw*= f[0]) F[i]*= pw;
  return f[0]= 0, composite(f, F);
 }
 
 template <class T> static inline std::vector<T> polynomial_composite(std::vector<T> f, std::vector<T> P) {
  const int sz= f.size(), n= __builtin_ctz(sz);
  assert(sz == 1 << n);
  T F[MAX_N + 1]= {};
  int e= P.size();
  if (!e) return std::vector<T>(sz);
  for (int j= 0;; ++j, --e) {
   for (int i= e; i--;) (F[j]*= f[0])+= P[i];
   if (j == n || e == 1) break;
   for (int i= 1; i < e; ++i) P[i - 1]= P[i] * i;
  }
  return f[0]= 0, composite(f, F);
 }
 
 template <class T>  
 static inline std::vector<T> egf(std::vector<T> f) {
  static constexpr int M= 1 << 11;
  const int sz= f.size(), n= __builtin_ctz(sz), sz4= sz >> 2;
  assert(sz == 1 << n);
  if (n == 1) return {0, f[1]};
  int l= sz4, m;
  T *in= f.data() + l, *dp= in + l, tmp[sz4 / 2], *dp2;
  for (int s; l > M; conv_tr(dp, in, dp, l), in-= (l>>= 1))
   for (m= sz4; dp2= dp + (m - l), m > l; m>>= 1)
    for (s= l, conv_tr(dp2 + m - l, in, tmp, l); s--;) dp2[s]+= tmp[s];
  for (int s; l; conv_na(dp, in, dp, l), in-= (l>>= 1))
   for (m= sz4; dp2= dp + (m - l), m > l; m>>= 1)
    for (s= l, conv_na(dp2 + m - l, in, tmp, l); s--;) dp2[s]+= tmp[s];
  std::vector<T> ret(n + 1, 0);
  for (int i= n + 1; --i;) ret[i]= dp[(1 << (n - i)) - 1];
  return ret;
 }
 
 template <class T>  
 static inline std::vector<T> egf(const std::vector<T> &f, std::vector<T> g) {
  static constexpr int M= 1 << 11;
  const int sz= f.size(), n= __builtin_ctz(sz), sz2= sz >> 1, sz4= sz >> 2;
  assert(sz == 1 << n), assert(sz == (int)g.size());
  if (n == 1) return {g[1], f[1] * g[0] + f[0] * g[1]};
  int l= sz2, m;
  const T *in= f.data() + sz2;
  T *dp= g.data(), tmp[sz2 / 2], *dp2;
  for (int s; l > M; conv_tr(dp, in, dp, l), in-= (l>>= 1))
   for (m= sz2; dp2= dp + (m - l), m > l; m>>= 1)
    for (s= l, conv_tr(dp2 + m - l, in, tmp, l); s--;) dp2[s]+= tmp[s];
  for (int s; l; conv_na(dp, in, dp, l), in-= (l>>= 1))
   for (m= sz2; dp2= dp + (m - l), m > l; m>>= 1)
    for (s= l, conv_na(dp2 + m - l, in, tmp, l); s--;) dp2[s]+= tmp[s];
  std::vector<T> ret(n + 1);
  for (int i= n + 1; i--;) ret[i]= dp[(1 << (n - i)) - 1];
  return ret;
 }
#undef SUBSET_REP
};
template <unsigned short MAX_V= 21> class UndirectedGraphSetPowerSeries {
 using SPS= SetPowerSeries<MAX_V>;
 template <class T> using sps= std::vector<T>;
 template <class T> using poly= std::vector<T>;
 const unsigned V, sz;
 unsigned adj[MAX_V][MAX_V]= {0}, edge[MAX_V]= {0};
 template <class T> static inline T pow(T x, int k) {
  for (T ret(1);; x*= x)
   if (k & 1 ? ret*= x : 0; !(k>>= 1)) return ret;
 }
 template <class F> inline void bfs(int s, const F &f) const {
  for (int t= s, u, j; t;)
   for (f(u= 1 << __builtin_ctz(t)); u;) j= __builtin_ctz(u), t^= 1 << j, u^= 1 << j, u|= edge[j] & t;
 }
 template <class T, class G> static inline void transform_articulation(sps<T> &f, const G &g) {
  const int sz2= f.size() / 2;
  sps<T> tmp(sz2);
  for (int I= sz2; I; I>>= 1) {
   for (int t= 0; t < sz2; t+= I)
    for (int u= I, t2= t << 1; u--;) tmp[t | u]= f[t2 | I | u];
   tmp= g(tmp);
   for (int t= 0; t < sz2; t+= I)
    for (int u= I, t2= t << 1; u--;) f[t2 | I | u]= tmp[t | u];
  }
 }
 template <class T, bool b> inline void transform_bridge(sps<T> &f) const {
  const int sz2= sz / 2;
  sps<T> tmp(sz2), tmp2;
  for (int i= V, I= sz2; --i; I>>= 1) {
   for (int t= 0; t < sz2; t+= I)
    for (int u= I, t2= t << 1; u--;) tmp[t | u]= f[t2 | I | u];
   tmp2.assign(sz2, 0);
   for (int t= 0; t < sz2; t+= I)
    for (int j= i, J= I, t2= t << 1; J>>= 1, j--;)
     for (int s= J, J2= J * 2; s < I; s+= J2)
      for (int u= s + J; u-- > s;) {
       if constexpr (b) tmp2[t | u]+= f[t2 | u] * adj[i][j];
       else tmp2[t | u]-= f[t2 | u] * adj[i][j];
      }
   tmp= SPS::convolve(tmp, SPS::exp(tmp2));
   for (int t= 0; t < sz2; t+= I)
    for (int u= I, t2= t << 1; u--;) f[t2 | I | u]= tmp[t | u];
  }
 }
public:
 UndirectedGraphSetPowerSeries(int n): V(n), sz(1 << V) {}
 UndirectedGraphSetPowerSeries(const std::vector<std::vector<int>> &g): V(g.size()), sz(1 << V) {
  for (int i= V; i--;)
   for (int j= i; j--;) assert(g[i][j] == g[j][i]);
  for (int i= V; i--;)
   for (int j= V; j--;) adj[i][j]= g[i][j];
  for (int i= V; i--;)
   for (int j= V; j--;) edge[i]|= !(!(adj[i][j])) << j;
 }
 int *operator[](int u) const { return adj[u]; }
 void add_edge(int u, int v, int cnt= 1) {
  adj[u][v]= (adj[v][u]+= cnt), edge[u]|= (1 << v), edge[v]|= (1 << u);
  if (!(adj[u][v])) edge[u]^= (1 << v), edge[v]^= (1 << u);
 }
 template <class T> static inline sps<T> only_connected(const sps<T> &f) { SPS::log(f); }
 template <class T> static inline sps<T> disjoint_union(const sps<T> &f) { SPS::exp(f); }
 template <class T> static inline sps<T> only_biconnected(sps<T> f) { return transform_articulation(f, SPS::template log<T>), f; }
 template <class T> static inline sps<T> articulation_union(sps<T> f) { return transform_articulation(f, SPS::template exp<T>), f; }
 template <class T> inline sps<T> only_2edge_connected(sps<T> f) const { return transform_bridge<T, false>(f), f; }
 template <class T> inline sps<T> bridge_union(sps<T> f) const { return transform_bridge<T, true>(f), f; }
 inline sps<int> selfloop_rank() const {
  sps<int> ret(sz, 0);
  for (int i= V; i--;) ret[1 << i]= adj[i][i];
  return SPS::subset_sum(ret), ret;
 }
 inline sps<int> edge_space_rank() const {
  sps<int> ret(sz, 0);
  for (int i= V; i--;)
   for (int j= i; j--;) ret[(1 << i) | (1 << j)]= adj[i][j];
  return SPS::subset_sum(ret), ret;
 }
 inline sps<int> connected_component_num() const {
  sps<int> ret(sz, 0);
  for (int s= sz; s--;) bfs(s, [&](int) { ret[s]++; });
  return ret;
 }
 inline sps<int> cycle_space_rank() const {
  sps<int> e= edge_space_rank(), k= connected_component_num(), ret(sz, 0);
  for (int s= sz; s--;) ret[s]= e[s] + k[s] - __builtin_popcount(s);
  return ret;
 }
 template <class T> static inline sps<T> space_size(const sps<int> &rank) {
  sps<T> ret(rank.size());
  for (int s= rank.size(); s--;) ret[s]= pow<T>(2, rank[s]);
  return ret;
 }
 template <class T> inline sps<T> edge_space_size() const { return space_size<T>(edge_space_rank()); }
 template <class T> inline sps<T> cycle_space_size() const { return space_size<T>(cycle_space_rank()); }
 template <class T> inline void considering_selfloop(sps<T> &f) const {
  auto tmp= space_size<T>(selfloop_rank());
  for (int s= sz; s--;) f[s]*= tmp[s];
 }
 template <class T> inline sps<T> connected_graph() const { return SPS::log(edge_space_size<T>()); }
 template <class T> inline sps<T> euler_graph() const { return SPS::log(cycle_space_size<T>()); }
 template <class T> inline sps<T> biparate_graph() const {
  sps<T> tmp= edge_space_size<T>(), ret(sz, 1);
  for (int s= sz; s--;) ret[s]/= tmp[s];
  ret= SPS::convolve(ret, ret);
  for (int s= sz; s--;) ret[s]*= tmp[s];
  ret= SPS::log(ret);
  for (int s= sz; s--;) ret[s]/= 2;
  return ret;
 }
 template <class T> inline sps<T> biconnected_graph() const {
  sps<T> ret= connected_graph<T>();
  return transform_articulation(ret, SPS::template log<T>), ret;
 }
 template <class T> inline sps<T> tree() const {
  sps<int> e= edge_space_rank();
  sps<T> ret= {0, 1};
  ret.reserve(sz);
  for (int I= 2; I < sz; I<<= 1) {
   sps<T> g(ret);
   for (int s= I; --s;) g[s]*= e[s | I] - e[s] - e[I];
   g= SPS::exp(g);
   std::copy(g.begin(), g.end(), std::back_inserter(ret));
  }
  return ret;
 }
 template <class T> inline sps<T> forest() const { return SPS::exp(tree<T>()); }
 template <class T> inline sps<T> rooted_tree() const {
  auto ret= tree<T>();
  for (int s= sz; s--;) ret[s]*= __builtin_popcount(s);
  return ret;
 }
 template <class T> inline sps<T> cycle_graph() const {
  T dp[sz][V - 1];
  sps<T> ret(sz, 0);
  for (int i= V, I= sz; I>>= 1, --i;) {
   for (int s= I; --s;) std::fill_n(dp[s], i, 0);
   for (int j= i; j--;) dp[1 << j][j]= adj[i][j];
   for (int s= 1; s < I; s++)
    for (int t= s, j, u, r, k; t; ret[s | I]+= dp[s][j] * adj[j][i])
     for (t^= 1 << (j= __builtin_ctz(t)), u= r= s ^ (1 << j); u; dp[s][j]+= dp[r][k] * adj[k][j]) u^= 1 << (k= __builtin_ctz(u));
  }
  for (int i= V; i--;)
   for (int j= i; j--;) ret[(1 << i) | (1 << j)]-= adj[i][j];
  for (int s= sz; --s;) ret[s]/= 2;
  return ret;
 }
 template <class T> inline sps<T> cactus_graph() const {
  auto ret= cycle_graph<T>();
  for (int i= V; i--;)
   for (int j= i; j--;) ret[(1 << i) | (1 << j)]+= adj[i][j];
  return transform_articulation(ret, SPS::template exp<T>), ret;
 }
 template <class T> inline sps<T> two_edge_connected_graph() const {
  sps<T> ret= connected_graph<T>();
  return transform_bridge<T, false>(ret), ret;
 }
 template <class T> inline sps<T> acyclic_orientations() const {
  auto k= connected_component_num();
  sps<T> g(sz, 0);
  for (int s= sz; --s;)
   if (k[s] == __builtin_popcount(s)) g[s]= k[s] & 1 ? 1 : -1;
  return SPS::template semi_relaxed_convolve<T>(g, 1);
 }
 template <class T> inline std::vector<T> colorings_using_exactly_k_colors_num() const {
  if (V == 0) return {0};  
  auto k= connected_component_num();
  std::vector<T> indep(sz, 0);
  for (int s= sz; --s;) indep[s]= k[s] == __builtin_popcount(s);
  return SPS::egf(indep);
 }
 template <class T> inline poly<T> chromatic_polynomial() const {
  auto e= colorings_using_exactly_k_colors_num<T>();
  if (e.back() == 0) return {0};
  poly<T> ret(V + 1, 0);
  T tmp[V]= {1};
  for (int i= 1, j; i < V; ++i)
   for (j= i; j--; tmp[j]*= -i) ret[j + 1]+= tmp[j] * e[i], tmp[j + 1]+= tmp[j];
  for (int j= V; j--;) ret[j + 1]+= tmp[j];
  return ret;
 }
 template <class T> inline T tutte_polynomial(T x, T y) const {
  int sum[sz], s, t, lim= 2, i, j;
  T fum[10'000]= {0, 1};
  std::vector<T> g= {0}, h;
  for (g.reserve(sz), h.reserve(sz), i= 0; i < V; ++i) {
   for (sum[0]= j= 0; j < i; j++)
    for (s= t= 1 << j; s--;) sum[s | t]= sum[s] + adj[i][j];
   for (h.resize(s= 1 << i); s--; h[s]= g[s] * fum[sum[s]])
    for (; lim <= sum[s]; lim++) fum[lim]= fum[lim - 1] * y + 1;
   h= SPS::exp(h), std::copy(h.begin(), h.end(), std::back_inserter(g));
  }
  for (x-= 1, t= ~0, j= 0, i= V; i--;) j+= adj[i][i];
  for (bfs((s= sz) - 1, [&](int u) { t^= u; }); --s&= t;) g[s]*= x;
  return SPS::exp(g)[sz - 1] * pow(y, j);
 }
};
using namespace std;
signed main() {
 cin.tie(0);
 ios::sync_with_stdio(false);
 using Mint= ModInt<998244353>;
 int n;
 cin >> n;
 UndirectedGraphSetPowerSeries<21> g(n);
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