#include <bits/stdc++.h>
using namespace std;
#define debug(fmt, ...) \
  fprintf(stderr, "[%d] : " fmt "\n", __LINE__, ##__VA_ARGS__)
namespace io {
const int MAXBUF = 1 << 23;
char buf[MAXBUF], *p1 = buf, *p2 = buf;
char pbuf[MAXBUF], *pp = pbuf;
inline char getc() {
  return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, MAXBUF, stdin)),
         p1 == p2 ? EOF : *p1++;
}
inline void putc(char c) {
  (pp == pbuf + MAXBUF) && (fwrite(pbuf, 1, MAXBUF, stdout), pp = pbuf),
      *pp++ = c;
}
inline void flush() {
  fwrite(pbuf, 1, pp - pbuf, stdout), pp = pbuf;
}
struct _ { ~_() { flush(); }} __;
} 
using io::getc;
using io::putc;
template <class _Tp>
inline _Tp& read(_Tp& x) {
  bool sign = false;
  char ch = getc();
  for (; !isdigit(ch); ch = getc()) sign |= (ch == '-');
  for (x = 0; isdigit(ch); ch = getc()) x = x * 10 + (ch ^ 48);
  return sign ? (x = -x) : x;
}
template <class _Tp>
inline void write(_Tp x) {
  if (x < 0) putc('-'), x = -x;
  if (x > 9) write(x / 10);
  putc((x % 10) ^ 48);
}
template <class _Tx, class _Ty>
inline void chkmin(_Tx& x, const _Ty& y) { if (y < x) x = y; }
template <class _Tx, class _Ty>
inline void chkmax(_Tx& x, const _Ty& y) { if (x < y) x = y; }
bool Mbe;
using ll = long long;
using ull = unsigned long long;
constexpr int N = 510, mod = 1e9 + 7;
int n, m, p, a[N][N], b[N][N];
inline int adj(int x) { return x + ((x >> 31) & mod); }
bool Med;
int main() {
  
  read(n), read(p), read(m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      read(a[i][j]);
      a[i][j] = adj(a[i][j]);
    }
  }
  for (int i = 0; i < p; ++i) {
    for (int j = 0; j < m; ++j) {
      read(b[j][i]);
      b[j][i] = adj(b[j][i]);
    }
  }
  constexpr ull mod8 = (ull)8 * mod * mod;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      ull v[8] = {};
      int *A = a[i], *B = b[j];
      for (int t = 0; t < p; t += 64) {
        for (int x = t; x < min(p, t + 64); x += 8) {
          v[0] += (ull)A[x + 0] * B[x + 0];
          v[1] += (ull)A[x + 1] * B[x + 1];
          v[2] += (ull)A[x + 2] * B[x + 2];
          v[3] += (ull)A[x + 3] * B[x + 3];
          v[4] += (ull)A[x + 4] * B[x + 4];
          v[5] += (ull)A[x + 5] * B[x + 5];
          v[6] += (ull)A[x + 6] * B[x + 6];
          v[7] += (ull)A[x + 7] * B[x + 7];
        }
        if (v[0] >= mod8) v[0] -= mod8;
        if (v[1] >= mod8) v[1] -= mod8;
        if (v[2] >= mod8) v[2] -= mod8;
        if (v[3] >= mod8) v[3] -= mod8;
        if (v[4] >= mod8) v[4] -= mod8;
        if (v[5] >= mod8) v[5] -= mod8;
        if (v[6] >= mod8) v[6] -= mod8;
        if (v[7] >= mod8) v[7] -= mod8;
      }
      ull ans = 0;
      for (int x = 0; x < 8; ++x)
        if ((ans += v[x]) >= mod8) ans -= mod8;
      write(ans % mod);
      putc(" \n"[j == m - 1]);
    }
  }
  return 0;
}