
#include <bits/stdc++.h>

using namespace std;

#if __cplusplus < 201400
  #warning "Please use c++14 or higher."
  #define INLINE_V
  #define REGISTER_V register
  #define CPP14CONSTEXPR
  #define gcd __gcd
  #define CPP14ENABLE_IF
#elif __cplusplus < 201700
  #define INLINE_V
  #define REGISTER_V
  #define CPP14CONSTEXPR constexpr
  #define gcd __gcd
  #define CPP14ENABLE_IF ,enable_if_t<_is_integer<T>, int> = 0
#else
  #define INLINE_V inline
  #define REGISTER_V
  #define CPP14CONSTEXPR constexpr
  #define CPP14ENABLE_IF ,enable_if_t<_is_integer<T>, int> = 0
#endif

#if !defined(_WIN32) && !defined(LOCK_GETCHAR)
  #define getchar getchar_unlocked
#endif

#define il inline
#define mkp make_pair
#define fi first
#define se second
#define For(i,j,k) for(REGISTER_V int i=(j);i<=(k);++i) 
#define ForDown(i,j,k) for(REGISTER_V int i=(j);i>=(k);--i) 
#define pb push_back
#define eb emplace_back
#define FileIO(filename) freopen(filename".in","r",stdin);freopen(filename".out","w",stdout)

using ll = long long;
using lll = __int128_t;
using uint = unsigned int;
using ull = unsigned long long;
using ulll = __uint128_t;
using db = double;
using ldb = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#if __cplusplus >= 201400
  template <class T> INLINE_V constexpr bool _is_integer = numeric_limits<T>::is_integer;
  template <> INLINE_V constexpr bool _is_integer<__int128> = true;
  template <> INLINE_V constexpr bool _is_integer<__uint128_t> = true;
  template <> INLINE_V constexpr bool _is_integer<bool> = false;
  template <> INLINE_V constexpr bool _is_integer<char> = false;
  template <class T CPP14ENABLE_IF>
    INLINE_V constexpr T INF = numeric_limits<T>::max() >> 1;
#endif

template<typename T> constexpr il T sq(const T & x){return x*x;}
template<typename T> CPP14CONSTEXPR il T cmin(T & x, const T &y){x=min(x,y);}
template<typename T> CPP14CONSTEXPR il T cmax(T & x, const T &y){x=max(x,y);}
template<typename T> CPP14CONSTEXPR il T qpow(T x, ull y, T mod){T ans=1;x%=mod;while(y){if(y&1)(ans*=x)%=mod;(x*=x)%=mod;y>>=1;}return ans;}
template<typename T> CPP14CONSTEXPR il T qpow(T x, ull y){T ans=1;while(y){if(y&1)ans*=x;x*=x;y>>=1;}return ans;}
template<typename T CPP14ENABLE_IF> il void read(T &x){ x=0;int f=1;int c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}while(isdigit(c)){x=x*10+c-'0';c=getchar();}x*=f;}
template<typename T, typename ... Args> il void read(T &x, Args &... y){ read(x);read(y...); }




namespace {
constexpr ll MAXN = 1e6 + 5;
vector<int> ans[1005];
int tp, n, k, a[MAXN], b[MAXN];
il void solver_main() {
  read(tp, n, k);
  For(i, 1, n) read(a[i]);
  if (n < k * k || n % k || a[1] % k || a[n] % k)
    return puts("No"), void();

  int cnt = 0;
  For(i, 1, n) {
    if (!(a[i] % k)) {
      cnt++;
      b[i] = 1;
      if (cnt == k)
        break;
    }
  }
  cnt = 0;
  ForDown(i, n, 1) {
    if (!(a[i] % k)) {
      cnt++;
      if (b[i])
        return puts("No"), void();
      b[i] = 2;
      if (cnt == k)
        break;
    }
  }
  if (k == 2) {
    int st = -1, ed = -1;
    For(i, 1, n) if (b[i] == 2) {
      ed = i;
      break;
    }
    ForDown(i, n, 1) if (b[i] == 1) {
      st = i;
      break;
    }
    puts("Yes\n2");
    printf("2 %d %d\n", st, ed);
    printf("%d ", n - 2);
    For(i, 1, n) if (i != st && i != ed) printf("%d ", i);
    return;
  }

  

  int p = 0, q = 1, cur = 1;
  For(i, 1, n) {
    if (b[i] == 1) {
      ans[++p].eb(i);
    } else if (b[i] == 2) {
      if (q > p || signed(ans[q].size() + 1) % k)
        return puts("No"), void();
      ans[q++].eb(i);
      cur = max(cur, q);
    } else {
      while (cur < p && signed(ans[cur].size() + 1) % k == 0)
        cur++;
      if (cur < p && signed(ans[cur].size() + 1) % k == 1)
        swap(ans[cur], ans[cur + 1]);
      ans[cur].eb(i);
    }
  }
  puts("Yes");
  printf("%d\n", k);
  For(i, 1, k) {
    printf("%d ", ans[i].size());
    for (int x : ans[i])
      printf("%d ", x);
    puts("");
  }
}
} 

signed main() { return solver_main(), 0; }
