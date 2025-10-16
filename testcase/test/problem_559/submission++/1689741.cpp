
#include <bits/stdc++.h>
#ifdef dbg
#define D(...) fprintf(stderr, __VA_ARGS__)
#define DD(...) D(#__VA_ARGS__ " = "), debug_helper::debug(__VA_ARGS__), D("\n")
#include "C:\Users\wsyear\Desktop\OI\templates\debug.hpp"
#else
#define D(...) ((void)0)
#define DD(...) ((void)0)
#endif
#define rep(i, j, k) for (int i = (j); i <= (k); ++i)
#define per(i, j, k) for (int i = (j); i >= (k); --i)
#define SZ(v) int((v).size())
#define ALL(v) (v).begin(),(v).end()
#define fi first
#define se second
#define gc getchar
#define pc putchar
using ll = long long;
using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;

using namespace std;

template <class T = int> T read() {
  T x = 0; bool f = 0; char ch = gc();
  while (!isdigit(ch)) f = ch == '-', ch = gc();
  while (isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48), ch = gc();
  return f ? -x: x;
}
template <class T> void write(T x) {
  if (x >= 0) { if (x > 9) write(x / 10); pc(x % 10 + 48); }
  else { pc('-'); if (x < -9) write(-x / 10); pc(48 - x % 10); }
}

int main() {
  int n = read(), m = read();
  int l = read(), d = read();
  while (true) {
    puts("reach_dest");
    fflush(stdout);
    int x = read();
    if (x) break;
    puts("move_left ");
    fflush(stdout);
    x = read(), assert(x);
  }
}