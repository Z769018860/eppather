



#include <type_traits>
#include <cstdint>

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;
using i128 = __int128_t;
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = __uint128_t;
using usize = std::size_t;
using f32 = float;
using f64 = double;
using f80 = long double;
template <class T>
using TI = std::type_identity_t<T>;

#include <cstdio>
#include <sys/mman.h>
#include <sys/stat.h>

struct MmapBuf {
  struct stat sb;
  std::FILE *const f;
  const u8 *p, *beg, *end;
  MmapBuf(std::FILE *const f, usize) : f(f) {
    i32 fd = fileno(f);
    fstat(fd, &sb);
    beg = (u8 *)mmap(nullptr, sb.st_size + 4, PROT_READ, MAP_PRIVATE, fd, 0);
    p = beg, end = p + sb.st_size;
    madvise(const_cast<u8 *>(beg), sb.st_size + 4, MADV_SEQUENTIAL);
  }
  ~MmapBuf() {
    munmap(const_cast<u8 *>(beg), sb.st_size + 4);
  }
  bool eof() const {
    return end <= p;
  }
  void reserve(usize) {}
  u8 top() const {
    return *p;
  }
  u8 pop() {
    return *p++;
  }
};



#include <vector>

struct AtoiHelper {
  std::vector<u16> pre;
  AtoiHelper() : pre(0x10000, -1) {
    for (u32 i = 0; i != 0x100; ++i) {
      for (u32 j = 0; j != 10; ++j) {
        u32 t = i * 0x100 | j | 0x30;
        if ('0' <= i && i <= '9')
          pre[t] = j * 10 + i - 0x30;
        else
          pre[t] = j | 0x100;
      }
    }
  }
  u64 getu(u8 c, const u8 *&p0) {
    const u8 *p = p0;
    u64 x = c & 0xf;
    while (true) {
      u16 t = *reinterpret_cast<const u16 *>(p);
      auto ft = pre[t];
      p += 2;
      if (ft < 100) { 
        x = x * 100 + ft;
      } else { 
        if (ft < 0x1000)
          x = x * 10 + ft - 0x100;
        else
          --p;
        break;
      }
    }
    return p0 = p, x;
  }
};


template <class Buf>
struct Reader {
  Buf buf;
  AtoiHelper atoi;
  Reader(std::FILE *f, usize size = 1 << 18) : buf(f, size) {}
  bool eof() const {
    return buf.eof();
  }
  template <std::integral T>
  Reader &operator>>(T &x) {
    while (true) {
      buf.reserve(0x40);
      u8 c = buf.pop();
      if (std::signed_integral<T> && c == '-') {
        x = -T(atoi.getu(0, buf.p));
        break;
      }
      if ('0' <= c && c <= '9') {
        x = atoi.getu(c, buf.p);
        break;
      }
    }
    return *this;
  }
};



#include <array>

struct ItoaHelper {
  std::vector<u32> pre;
  ItoaHelper() : pre(10000) {
    for (u32 i = 0; i < 10000; ++i) {
      u32 ti = i;
      for (u32 j = 0; j != 4; ++j) {
        pre[i] = pre[i] << 8 | ti % 10 | 0x30;
        ti /= 10;
      }
    }
  }
  void putu(u64 x, u8 *&p) {
    std::array<u8, 32> tmp;
    u8 *s0 = tmp.data() + 30, *s1 = s0;
    while (x >= 10000) {
      *reinterpret_cast<u32 *>(s0 -= 4) = pre[x % 10000];
      x /= 10000;
    }
    *reinterpret_cast<u32 *>(s0 -= 4) = pre[x % 10000];
    s0 += x < 100 ? (x < 10 ? 3 : 2) : (x < 1000 ? 1 : 0);
    p = std::copy(s0, s1, p);
  }
};

#include <cassert>
#include <string>

struct Writer {
  std::FILE *const f;
  std::vector<u8> buf;
  ItoaHelper itoa;
  u8 *p, *end;
  Writer(std::FILE *const f, usize size = 1 << 18) : f(f), buf(size) {
    assert(size >= 0x100);
    p = buf.data(), end = p + size;
  }
  ~Writer() {
    flush();
  }
  void flush() {
    std::fwrite(buf.data(), 1, p - buf.data(), f);
    p = buf.data();
  }
  void reserve(usize n) {
    if (end - p < i64(n))
      flush();
  }
  void _put_s(const char *s, usize n) {
    if (n >= buf.size() / 4) {
      flush();
      std::fwrite(s, 1, n, f);
    } else {
      reserve(n);
      p = std::copy(s, s + n, p);
    }
  }
  template <std::integral T>
  Writer &operator<<(T x) {
    reserve(0x40);
    if (std::signed_integral<T> && x < 0) {
      *p++ = '-';
      itoa.putu(-x, p);
    } else {
      itoa.putu(x, p);
    }
    return *this;
  }
  Writer &operator<<(char x) {
    reserve(0x40);
    *p++ = x;
    return *this;
  }
  Writer &operator<<(const std::string &x) {
    _put_s(x.data(), x.size());
    return *this;
  }
  template <usize N>
  Writer &operator<<(const char (&s)[N]) {
    _put_s(s, N - 1);
    return *this;
  }
};




template <class U>
struct Mont {
  using S = std::make_signed_t<U>;
  using UU = std::conditional_t<std::is_same_v<U, u32>, u64, u128>;
  const U MOD, MOD2, R, IR, R2, ONE;
  explicit constexpr Mont(U mod)
      : MOD(mod), MOD2(mod * 2), R(getR(mod)), IR(-getNR(mod)), R2(UU(R) * R % MOD), ONE(trans(1)) {
  }
  constexpr static U getR(U mod) {
    return (UU(1) << (sizeof(U) * 8)) % mod;
  }
  constexpr static U getNR(U mod) {
    U x = 1;
    for (u32 i = 0; i != 6; ++i)
      x *= 2 - x * mod;
    return x;
  }
  inline constexpr U trans(U x) const {
    
    return reduce(UU(x) * R2);
  }
  inline constexpr U reduce(UU x) const {
    return (x + UU(U(x) * IR) * MOD) >> (sizeof(U) * 8);
  }
  inline constexpr U add(U a, U b) const {
    U v1 = a + b, v2 = v1 - MOD2;
    return S(v2) < 0 ? v1 : v2;
  }
  inline constexpr U sub(U a, U b) const {
    U v1 = a - b, v2 = v1 + MOD2;
    return S(v2) >= 0 ? v2 : v1;
  }
  inline constexpr U mul(U a, U b) const {
    return reduce(UU(a) * b);
  }
  inline constexpr U qpow(U a, u64 n, U r) const {
    for (; n > 0; n /= 2) {
      if (n % 2 == 1)
        r = mul(r, a);
      a = mul(a, a);
    }
    return r;
  }
  inline constexpr U qpow(U a, u64 n) const {
    return qpow(a, n, ONE);
  }
  inline constexpr U inv(U x) const {
    return qpow(x, MOD - 2);
  }
  inline constexpr U div(U a, U b) const {
    return reduce(qpow(b, MOD - 2, a));
  }
  inline constexpr U get(U x) const {
    U v1 = reduce(x), v2 = v1 - MOD;
    return S(v2) < 0 ? v1 : v2;
  }
  inline constexpr U div2(U x) const {
    return (x % 2 == 1 ? x + MOD : x) >> 1;
  }
  inline constexpr bool cmp(U a, U b) const {
    return get(a) == get(b);
  }
  inline constexpr bool ncmp(U a, U b) const {
    return !cmp(a, b);
  }
  inline constexpr U neg(U x) const {
    return x != 0 ? MOD2 - x : 0;
  }
};
using Mont32 = Mont<u32>;
using Mont64 = Mont<u64>;
template <class ModT>
using ModU = ModT::U;
template <class ModT>
using ModUU = ModT::UU;

#include <bit>

inline bool basic_primality_test(u64 n) {
  if (n < 64)
    return (0x28208a20a08a28ac >> n) & 1;
  if ((0xdf75d77d >> (n % 30)) & 1)
    return false;
  if (n % 7 == 0 || n % 11 == 0)
    return false;
  return true;
}
template <class U>
inline bool miller_rabin_base(const Mont<U> &_M, TI<U> a, u32 s, TI<U> n) {
  const Mont<U> M = _M;
  U ad = M.qpow(a, n >> s), ad0 = M.get(ad);
  if (ad0 == 1 || ad0 == n - 1 || ad0 == 0)
    return true;
  for (u32 i = 1; i != s; ++i) {
    ad = M.mul(ad, ad), ad0 = M.get(ad);
    if (ad0 == n - 1)
      return true;
    if (ad0 == 1)
      break;
  }
  return false;
}
bool miller_rabin(u64 n) {
  if (!basic_primality_test(n))
    return false;
  u32 s = std::countr_zero(n - 1);
  constexpr std::array bases32 = {2, 7, 61};
  constexpr std::array bases64 = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  if (n < (1 << 30)) {
    auto M = Mont32{u32(n)};
    for (u32 a : bases32) {
      if (!miller_rabin_base(M, a, s, n))
        return false;
    }
  } else {
    auto M = Mont64{n};
    for (u64 a : bases64) {
      if (!miller_rabin_base(M, a, s, n))
        return false;
    }
  }
  return true;
}

i32 main() {
  Reader<MmapBuf> fin(stdin);
  Writer fout(stdout);
  while (!fin.eof()) {
    u64 n;
    fin >> n;
    fout << (miller_rabin(n) ? "Y\n" : "N\n");
  }
  return 0;
}
