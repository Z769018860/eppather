#include <bits/stdc++.h>

#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <typename T>
void read(T &);
template <typename T>
void write(const T &);

typedef unsigned int uint;
const int N = 155;
const int g = 258;

int pw[1 << 17], lg[1 << 16];
uint nimmult(uint x, uint y, int k);
uint nimmult2(uint x, uint y);
class Nimber {
 public:
  uint v;
  operator uint() { return v; }
  Nimber(uint v = 0) : v(v) {}
  Nimber operator+(const Nimber &a) { return v ^ a.v; }
  Nimber operator*(const Nimber &a) { return nimmult2(v, a.v); }
};

uint SA, SB, SC;
uint rng() {
  SA ^= SA << 16;
  SA ^= SA >> 5;
  SA ^= SA << 1;
  uint t = SA;
  SA = SB;
  SB = SC;
  SC ^= t ^ SA;
  return SC;
}

void init();

int T;

int main() {
  init();
  read(T), read(SA), read(SB), read(SC);
  int lasans = 0;
  while (T--) {
    unsigned int x = rng() + lasans;
    unsigned int y = rng();
    Nimber xx = x, yy = y;
    lasans = xx * yy;
  }
  write(lasans), EL;
  return 0;
}

void init() {
  pw[0] = 1;
  for (int i = 1; i < 65535; ++i) pw[i] = nimmult(pw[i - 1], g, 4);
  for (int i = 65535; i < 65535 * 2; ++i) pw[i] = pw[i - 65535];
  for (int i = 0; i < 65535; ++i) lg[pw[i]] = i;
}
uint nimmult(uint x, uint y, int k) {
  if (!x || !y) return 0;
  if (k == 0) return 1;
  uint m = 1ull << (1 << (k - 1)), a = x / m, b = x % m, c = y / m, d = y % m;
  uint ac = nimmult(a, c, k - 1), bd = nimmult(b, d, k - 1);
  return ((nimmult(a ^ b, c ^ d, k - 1) ^ bd) * m) ^ nimmult(ac, m / 2, k - 1) ^ bd;
}
uint getmult(uint x, uint y) { return (x && y) ? pw[lg[x] + lg[y]] : 0; }
uint nimmult2(uint x, uint y) {
  const uint m = 1 << 16;
  uint a = x / m, b = x % m, c = y / m, d = y % m;
  uint ac = getmult(a, c), bd = getmult(b, d);
  return ((getmult(a ^ b, c ^ d) ^ bd) * m) ^ getmult(ac, m / 2) ^ bd;
}

template <typename T>
void read(T &Re) {
  T k = 0;
  char ch = getchar();
  int flag = 1;
  while (!std::isdigit(ch)) {
    if (ch == '-') flag = -1;
    ch = getchar();
  }
  while (std::isdigit(ch)) k = k * 10 + ch - '0', ch = getchar();
  Re = flag * k;
}
template <typename T>
void write(const T &Wr) {
  if (Wr < 0) {
    putchar('-'), write(-Wr);
  } else if (Wr < 10) {
    putchar(Wr + '0');
  } else {
    write(Wr / 10), putchar((Wr % 10) + '0');
  }
}
