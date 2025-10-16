
#include <bits/stdc++.h>

std::ostream&operator<<(std::ostream&os,std::int8_t x){return os<<(int)x;}
std::ostream&operator<<(std::ostream&os,std::uint8_t x){return os<<(int)x;}
std::ostream&operator<<(std::ostream&os,const __int128_t &v){if(!v)os<<"0";__int128_t tmp=v<0?(os<<"-",-v):v;std::string s;while(tmp)s+='0'+(tmp%10),tmp/=10;return std::reverse(s.begin(),s.end()),os<<s;}
std::ostream&operator<<(std::ostream&os,const __uint128_t &v){if(!v)os<<"0";__uint128_t tmp=v;std::string s;while(tmp)s+='0'+(tmp%10),tmp/=10;return std::reverse(s.begin(),s.end()),os<<s;}
#define checkpoint() (void(0))
#define debug(...) (void(0))
#define debugArray(x,n) (void(0))
#define debugMatrix(x,h,w) (void(0))

template <class T> struct DirichletSeries {
 using Self= DirichletSeries;
 uint64_t N;  
 size_t K, L;
 std::valarray<T> x, X;
 DirichletSeries(uint64_t N, bool unit= false): N(N), K(N > 1 ? std::max(std::ceil(std::pow((double)N / std::log2(N), 2. / 3)), std::sqrt(N) + 1) : 1), L((N - 1 + K) / K), x(K + 1), X(K + L + 1) {
  if (assert(N > 0); unit) x[1]= 1, X= 1;
 }
 template <class F, typename= std::enable_if_t<std::is_convertible_v<std::invoke_result_t<F, uint64_t>, T>>> DirichletSeries(uint64_t N, const F &sum): DirichletSeries(N) {
  for (size_t i= 1; i <= K; ++i) X[i]= sum(i);
  for (size_t i= 1; i <= L; ++i) X[K + i]= sum(uint64_t((double)N / i));
  for (size_t i= K; i; --i) x[i]= X[i] - X[i - 1];
 }
 Self operator-() const {
  Self ret(N);
  return ret.x= -x, ret.X= -X, ret;
 }
 Self &operator+=(T r) { return x[1]+= r, X+= r, *this; }
 Self &operator-=(T r) { return x[1]-= r, X-= r, *this; }
 Self &operator*=(T r) { return x*= r, X*= r, *this; }
 Self &operator/=(T r) {
  if (T iv= T(1) / r; iv == 0) x/= r, X/= r;
  else x*= iv, X*= iv;
  return *this;
 }
 Self &operator+=(const Self &r) { return assert(N == r.N), assert(K == r.K), assert(L == r.L), x+= r.x, X+= r.X, *this; }
 Self &operator-=(const Self &r) { return assert(N == r.N), assert(K == r.K), assert(L == r.L), x-= r.x, X-= r.X, *this; }
 Self operator+(T r) const { return Self(*this)+= r; }
 Self operator-(T r) const { return Self(*this)-= r; }
 Self operator*(T r) const { return Self(*this)*= r; }
 Self operator/(T r) const { return Self(*this)/= r; }
 Self operator+(const Self &r) const { return Self(*this)+= r; }
 Self operator-(const Self &r) const { return Self(*this)-= r; }
 friend Self operator+(T l, Self r) { return r+= l; }
 friend Self operator-(T l, Self r) { return r.x[1]-= l, r.X-= l, r.x= -r.x, r.X= -r.X, r; }
 friend Self operator*(T l, const Self &r) { return r * l; }
 friend Self operator/(T l, const Self &r) { return (Self(r.N, true)/= r)*= l; }
 Self operator*(const Self &r) const {
  assert(N == r.N), assert(K == r.K), assert(L == r.L);
  Self ret(N);
  uint64_t n;
  for (size_t i= K, j; i; --i)
   for (j= K / i; j; --j) ret.x[i * j]+= x[i] * r.x[j];
  for (size_t l= L, m, i; l; ret.X[K + l--]-= sum(m) * r.sum(m))
   for (i= m= std::sqrt(n= (double)N / l); i; --i) ret.X[K + l]+= x[i] * r.sum((double)n / i) + r.x[i] * sum((double)n / i);
  for (size_t i= 1; i <= K; ++i) ret.X[i]= ret.X[i - 1] + ret.x[i];
  return ret;
 }
 Self operator/(const Self &r) const { return Self(*this)/= r; }
 Self &operator*=(const Self &r) { return *this= *this * r; }
 Self &operator/=(const Self &r) {
  assert(N == r.N), assert(K == r.K), assert(L == r.L);
  for (size_t i= 1, j, ed; i <= K; i++)
   for (x[i]/= r.x[1], j= 2, ed= K / i; j <= ed; j++) x[i * j]-= x[i] * r.x[j];
  X[1]= x[1];
  for (size_t i= 2; i <= K; ++i) X[i]= X[i - 1] + x[i];
  uint64_t n;
  for (size_t l= L, m; l; X[K + l--]/= r.x[1])
   for (m= std::sqrt(n= (double)N / l), X[K + l]+= r.sum(m) * sum(m) - x[1] * r.sum(n); m > 1;) X[K + l]-= r.x[m] * sum((double)n / m) + x[m] * r.sum((double)n / m), --m;
  return *this;
 }
 Self square() const {
  Self ret(N);
  size_t i, j, l= std::sqrt(K);
  uint64_t n;
  T tmp;
  for (i= l; i; --i)
   for (j= K / i; j > i; --j) ret.x[i * j]+= x[i] * x[j];
  ret.x+= ret.x;
  for (i= l; i; --i) ret.x[i * i]+= x[i] * x[i];
  for (l= L; l; ret.X[K + l]+= ret.X[K + l], ret.X[K + l--]-= tmp * tmp)
   for (tmp= sum(i= std::sqrt(n= (double)N / l)); i; --i) ret.X[K + l]+= x[i] * sum((double)n / i);
  for (size_t i= 1; i <= K; ++i) ret.X[i]= ret.X[i - 1] + ret.x[i];
  return ret;
 }
 Self pow(uint64_t M) const {
  if (N / M > M)
   for (auto ret= Self(N, true), b= *this;; b= b.square()) {
    if (M & 1) ret*= b;
    if (!(M>>= 1)) return ret;
   }
  size_t n= 0, m, i, l, p= 2;
  uint64_t e, j;
  while (n <= M && (1ULL << n) <= N) ++n;
  T pw[65]= {1}, b= x[1], tmp;
  for (e= M - n + 1;; b*= b)
   if (e & 1 ? pw[0]*= b : T(); !(e>>= 1)) break;
  for (m= 1; m < n; ++m) pw[m]= pw[m - 1] * x[1];
  Self ret(*this);
  std::valarray<T> D= (ret.X-= x[1]), E(std::begin(D), K + 1), Y(std::begin(D) + K, L + 1), y= x, z(K + 1), Z(L + 1);
  auto A= [&](uint64_t n) { return n > K ? D[K + (double)N / n] : D[n]; };
  auto B= [&](uint64_t n) { return n > K ? Y[(double)N / n] : E[n]; };
  for (tmp= pw[n - 2] * M, l= L; l; l--) ret.X[K + l]*= tmp;
  for (i= 2; i <= K; ++i) ret.x[i]*= tmp;
  for (ret.x[1]= pw[n - 1], l= L; l; l--) ret.X[K + l]+= ret.x[1];
  for (m= 1, b= M, l= std::min<uint64_t>(L, uint64_t((double)N / p) / 2); m + 1 < n;) {
   for (b*= M - m, b/= ++m, tmp= b * pw[n - 1 - m]; l; ret.X[K + l--]+= Z[l] * tmp) {
    for (i= j= std::sqrt(e= (double)N / l); i >= p; --i) Z[l]+= y[i] * A((double)e / i);
    for (i= std::min(j, e / p); i >= 2; --i) Z[l]+= x[i] * B((double)e / i);
    if (j >= p) Z[l]-= A(j) * B(j);
   }
   for (i= K; i >= p; --i)
    for (l= K / i; l >= 2; l--) z[i * l]+= y[i] * x[l];
   for (i= p= 1 << m; i <= K; ++i) ret.x[i]+= z[i] * tmp;
   if (m + 1 == n) break;
   if (l= std::min<uint64_t>(L, uint64_t((double)N / p) / 2), y.swap(z), Y.swap(Z), std::fill_n(std::begin(Z) + 1, l, 0); p * 2 <= K) std::fill(std::begin(z) + p * 2, std::end(z), 0);
   if (p <= K)
    for (E[p]= y[p], i= p + 1; i <= K; ++i) E[i]= E[i - 1] + y[i];
  }
  for (size_t i= 1; i <= K; ++i) ret.X[i]= ret.X[i - 1] + ret.x[i];
  return ret;
 }
 inline T sum() const { return X[K + 1]; }
 inline T sum(uint64_t n) const { return n > K ? X[K + (double)N / n] : X[n]; }
 inline T operator()(uint64_t n) const { return n > K ? x[K + (double)N / n] : x[n]; }
};

template <class T> DirichletSeries<T> get_1(uint64_t N) {
 DirichletSeries<T> ret(N);
 for (size_t i= ret.L; i; --i) ret.X[ret.K + i]= uint64_t((double)N / i);
 return std::fill(std::begin(ret.x) + 1, std::end(ret.x), T(1)), std::iota(std::begin(ret.X), std::begin(ret.X) + ret.K + 1, 0), ret;
}

template <class T> DirichletSeries<T> get_mu(uint64_t N) { return DirichletSeries<T>(N, true)/= get_1<T>(N); }

template <class T> DirichletSeries<T> get_Id(uint64_t N) {
 DirichletSeries<T> ret(N);
 __uint128_t a;
 for (size_t l= ret.L; l; --l) a= (double)N / l, ret.X[ret.K + l]= (a * (a + 1)) >> 1;
 std::iota(std::begin(ret.x), std::end(ret.x), 0);
 for (size_t i= 1; i <= ret.K; ++i) ret.X[i]= ret.X[i - 1] + ret.x[i];
 return ret;
}

template <class T> DirichletSeries<T> get_Id2(uint64_t N) {
 DirichletSeries<T> ret(N);
 __uint128_t a, b, c;
 for (size_t l= ret.L; l; --l) a= (double)N / l, b= (a * (a + 1)) >> 1, c= (a + a + 1), ret.X[ret.K + l]= c % 3 == 0 ? T(c / 3) * b : T(b / 3) * c;
 for (uint64_t i= ret.K; i; --i) ret.x[i]= i * i;
 for (size_t i= 1; i <= ret.K; ++i) ret.X[i]= ret.X[i - 1] + ret.x[i];
 return ret;
}

template <class T> DirichletSeries<T> get_d(uint64_t N) { return get_1<T>(N).square(); }

template <class T> DirichletSeries<T> get_sigma(uint64_t N) { return get_1<T>(N) * get_Id<T>(N); }

template <class T> DirichletSeries<T> get_phi(uint64_t N) { return get_Id<T>(N)/= get_1<T>(N); }
template <class T>  
DirichletSeries<T> get_1sq(uint64_t N) {
 DirichletSeries<T> ret(N);
 for (size_t i= 1, e= ret.x.size(); i * i <= e; ++i) ret.x[i * i]= 1;
 for (size_t i= 1; i <= ret.K; ++i) ret.X[i]= ret.X[i - 1] + ret.x[i];
 for (size_t l= ret.L; l; --l) ret.X[ret.K + l]= uint64_t(std::sqrt((double)N / l));
 return ret;
}

template <class T> DirichletSeries<T> get_lambda(uint64_t N) { return get_1sq<T>(N)/= get_1<T>(N); }

template <class T> DirichletSeries<T> get_absmu(uint64_t N) { return get_1<T>(N)/= get_1sq<T>(N); }
template <class T> struct ListRange {
 using Iterator= typename std::vector<T>::const_iterator;
 Iterator bg, ed;
 Iterator begin() const { return bg; }
 Iterator end() const { return ed; }
 size_t size() const { return std::distance(bg, ed); }
 const T &operator[](int i) const { return bg[i]; }
};
namespace nt_internal {
using namespace std;
vector<int> ps, lf;
void sieve(int N) {
 static int n= 2;
 if (n > N) return;
 if (lf.resize((N + 1) >> 1); n == 2) ps.push_back(n++);
 int M= (N - 1) / 2;
 for (int j= 1, e= ps.size(); j < e; ++j) {
  int p= ps[j];
  if (int64_t(p) * p > N) break;
  for (auto k= int64_t(p) * max(n / p / 2 * 2 + 1, p) / 2; k <= M; k+= p) lf[k]+= p * !lf[k];
 }
 for (; n <= N; n+= 2)
  if (!lf[n >> 1]) {
   ps.push_back(lf[n >> 1]= n);
   for (auto j= int64_t(n) * n / 2; j <= M; j+= n) lf[j]+= n * !lf[j];
  }
}
ListRange<int> enumerate_primes() { return {ps.cbegin(), ps.cend()}; }
ListRange<int> enumerate_primes(int N) {
 sieve(N);
 return {ps.cbegin(), upper_bound(ps.cbegin(), ps.cend(), N)};
}
int least_prime_factor(int n) { return n & 1 ? sieve(n), lf[(n >> 1)] : 2; }

template <class T, class F> vector<T> completely_multiplicative_table(int N, const F &f) {
 vector<T> ret(N + 1);
 sieve(N);
 for (int n= 3, i= 1; n <= N; n+= 2, ++i) ret[n]= lf[i] == n ? f(n, 1) : ret[lf[i]] * ret[n / lf[i]];
 if (int n= 4; 2 <= N)
  for (T t= ret[2]= f(2, 1); n <= N; n+= 2) ret[n]= t * ret[n >> 1];
 return ret[1]= 1, ret;
}
}
using nt_internal::enumerate_primes, nt_internal::least_prime_factor, nt_internal::completely_multiplicative_table;

template <class T> static std::vector<T> pow_table(int N, uint64_t k) {
 if (k == 0) return std::vector<T>(N + 1, 1);
 auto f= [k](int p, int) {
  T ret= 1, b= p;
  for (auto e= k;; b*= b) {
   if (e & 1) ret*= b;
   if (!(e>>= 1)) return ret;
  }
 };
 return completely_multiplicative_table<T>(N, f);
}
template <class T> struct CumSumQuotient {
 uint64_t N;
 size_t K;
 std::valarray<T> X;
 CumSumQuotient(uint64_t N): N(N), K(std::sqrt(N)), X(K + K + 1) {}
 T &operator[](uint64_t i) { return i > K ? X[K + double(N) / i] : X[i]; }
 T operator()(uint64_t i) const { return i > K ? X[K + double(N) / i] : X[i]; }
 CumSumQuotient &operator+=(const CumSumQuotient &r) { return X+= r.X, *this; }
 CumSumQuotient &operator-=(const CumSumQuotient &r) { return X-= r.X, *this; }
 CumSumQuotient &operator*=(T a) { return X*= a, *this; }
 CumSumQuotient operator-() const {
  CumSumQuotient ret= *this;
  return ret.X= -ret.X, ret;
 }
 CumSumQuotient operator+(const CumSumQuotient &r) const { return CumSumQuotient(*this)+= r; }
 CumSumQuotient operator-(const CumSumQuotient &r) const { return CumSumQuotient(*this)-= r; }
 CumSumQuotient operator*(T a) const { return CumSumQuotient(*this)*= a; }
 friend CumSumQuotient operator*(T a, const CumSumQuotient &x) { return x * a; }
 void add(uint64_t i, T v) {
  for (size_t j= std::min<uint64_t>(N / i, K) + K; j >= i; --j) X[j]+= v;
 }
 T sum() const { return X[K + 1]; }
 T sum(uint64_t i) const { return i > K ? X[K + double(N) / i] : X[i]; }
};
template <class T> std::vector<CumSumQuotient<T>> sums_of_powers_on_primes(uint64_t N, size_t D) {
 size_t K= std::sqrt(N);
 std::vector ret(D + 1, CumSumQuotient<T>(N));
 for (size_t n= 1, d= 0; n <= K; ++n, d= 0)
  for (T prd= n; d <= D; prd*= (n + ++d)) ret[d].X[n]= prd / (d + 1);
 for (size_t n= 1, d= 0; n <= K; ++n, d= 0)
  for (T prd= N / n; d <= D; prd*= ((N / n) + ++d)) ret[d].X[n + K]= prd / (d + 1);
 if (D >= 2) {
  std::vector<T> stir(D + 1, 0);
  stir[1]= 1;
  for (size_t d= 2; d <= D; stir[d++]= 1) {
   for (size_t j= d; --j;) stir[j]= stir[j - 1] + stir[j] * (d - 1);
   for (size_t j= 1; j < d; ++j) ret[d].X-= stir[j] * ret[j].X;
  }
 }
 for (size_t d= 0; d <= D; ++d) ret[d].X-= 1;
 for (int p: enumerate_primes(K)) {
  uint64_t q= uint64_t(p) * p, M= N / p;
  T pw= 1;
  for (size_t d= 0, t= K / p, u= std::min<uint64_t>(K, N / q); d <= D; ++d, pw*= p) {
   auto &X= ret[d].X;
   T tk= X[p - 1];
   for (size_t n= 1; n <= t; ++n) X[n + K]-= (X[n * p + K] - tk) * pw;
   for (size_t n= t + 1; n <= u; ++n) X[n + K]-= (X[double(M) / n] - tk) * pw;
   for (uint64_t n= K; n >= q; --n) X[n]-= (X[double(n) / p] - tk) * pw;
  }
 }
 return ret;
}
template <class T, class F> T additive_sum(const CumSumQuotient<T> &P, const F &f) {
 T ret= P.sum();
 for (uint64_t d= 2, nN, nd; nN; d= nd) ret+= P(nN= double(P.N) / d) * ((nd= double(P.N) / nN + 1) - d);
 for (uint64_t p: enumerate_primes(P.K))
  for (uint64_t pw= p * p, e= 2; pw <= P.N; ++e, pw*= p) ret+= (f(p, e) - f(p, e - 1)) * (P.N / pw);
 return ret;
}
template <class T, class F> T multiplicative_sum(CumSumQuotient<T> P, const F &f) {
 auto ps= enumerate_primes(P.K);
 size_t psz= ps.size();
 for (size_t j= psz; j--;) {
  uint64_t p= ps[j], M= P.N / p, q= p * p;
  size_t t= P.K / p, u= std::min<uint64_t>(P.K, P.N / q);
  T tk= P.X[p - 1];
  for (auto i= q; i <= P.K; ++i) P.X[i]+= (P.X[double(i) / p] - tk) * f(p, 1);
  for (size_t i= u; i > t; --i) P.X[i + P.K]+= (P.X[double(M) / i] - tk) * f(p, 1);
  for (size_t i= t; i; --i) P.X[i + P.K]+= (P.X[i * p + P.K] - tk) * f(p, 1);
 }
 P.X+= 1;
 auto dfs= [&](auto &rc, uint64_t n, size_t bg, T cf) -> T {
  if (cf == T(0)) return T(0);
  T ret= cf * P(n);
  for (auto i= bg; i < psz; ++i) {
   uint64_t p= ps[i], q= p * p, nn= n / q;
   if (!nn) break;
   for (int e= 2; nn; nn/= p, ++e) ret+= rc(rc, nn, i + 1, cf * (f(p, e) - f(p, 1) * f(p, e - 1)));
  }
  return ret;
 };
 return dfs(dfs, P.N, 0, 1);
}

std::vector<std::tuple<uint64_t, uint64_t, uint64_t>> enumerate_quotients(uint64_t N) {
 uint64_t sq= std::sqrt(N), prev= N, x;
 std::vector<std::tuple<uint64_t, uint64_t, uint64_t>> ret;
 for (int q= 1, n= (sq * sq + sq <= N ? sq : sq - 1); q <= n; ++q) ret.emplace_back(q, x= double(N) / (q + 1), prev), prev= x;
 for (int l= sq; l >= 1; --l) ret.emplace_back(double(N) / l, l - 1, l);
 return ret;
}
using namespace std;
signed main() {
 cin.tie(0);
 ios::sync_with_stdio(0);
 unsigned N, k;
 cin >> N >> k;
 auto pi= sums_of_powers_on_primes<unsigned>(N, 0)[0];
 auto eq= enumerate_quotients(N);
 auto primes= enumerate_primes(sqrt(N));
 CumSumQuotient<unsigned> f(N);
 for (int i= primes.size(); i--;) {
  unsigned p= primes[i], p2= p * p, pk= 1;
  for (unsigned e= k, b= p;; b*= b) {
   if (e & 1) pk*= b;
   if (!(e>>= 1)) break;
  }
  for (int j= eq.size(); j--;) {
   unsigned n= get<0>(eq[j]);
   if (n < p2) break;
   auto &cur= f[n];
   for (unsigned pw= p; uint64_t(pw) * p <= n; pw*= p) {
    unsigned m= n / pw;
    cur+= pk * (pi(m) - i) + f[m];
   }
  }
 }
 for (auto [q, l, r]: eq) f[q]+= pi(q);
 DirichletSeries<unsigned> F(N, f);
 cout << (get_phi<unsigned>(N) * F).sum() * 2 - F.sum() << '\n';
 return 0;
}
