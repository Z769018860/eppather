#include <string.h>
#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>

#include <sys/mman.h>
#include <sys/stat.h>

typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;
typedef size_t usize;

u32 bit_ceil(u32 x) {
  return 1 << (32 - __builtin_clz(x - 1));
}

typedef struct {
  u32 mod, mod2, r, r2, ir;
} Mont32T;

Mont32T mont32_init(u32 mod) {
  Mont32T ret;

  ret.mod = mod, ret.mod2 = mod * 2;

  u64 r = (1ull << 32) % mod;
  ret.r = r, ret.r2 = r * r % mod;

  u32 x = 1;
  for (i32 i = 0; i < 5; ++i)
    x *= 2 - x * mod;
  ret.ir = -x;
  return ret;
}

inline u32 mont32_reduce(u64 x, const Mont32T *m) {
  return (x + (u64)((u32)x * m->ir) * m->mod) >> 32;
}

inline u32 mont32_add(u32 a, u32 b, const Mont32T *m) {
  u32 v1 = a + b, v2 = v1 - m->mod2;
  return (i32)v2 < 0 ? v1 : v2;
}

inline u32 mont32_sub(u32 a, u32 b, const Mont32T *m) {
  u32 v1 = a - b, v2 = v1 + m->mod2;
  return (i32)v1 < 0 ? v2 : v1;
}

inline u32 mont32_mul(u32 a, u32 b, const Mont32T *m) {
  return mont32_reduce((u64)a * b, m);
}

inline u32 mont32_trans(u32 x, const Mont32T *m) {
  return mont32_reduce((u64)m->r2 * x, m);
}

inline u32 mont32_get(u32 x, const Mont32T *m) {
  u32 v1 = mont32_reduce(x, m), v2 = v1 - m->mod;
  return (i32)v2 < 0 ? v1 : v2;
}

inline u32 mont32_qpowx(u32 a, u64 n, u32 r, const Mont32T *m) {
  for (; n > 0; n /= 2) {
    if (n % 2 == 1)
      r = mont32_mul(r, a, m);
    a = mont32_mul(a, a, m);
  }
  return r;
}

u32 mont32_qpow(u32 a, u64 n, const Mont32T *m) {
  return mont32_qpowx(a, n, mont32_trans(1, m), m);
}

inline u32 mont32_inv(u32 x, const Mont32T *m) {
  return mont32_qpow(x, m->mod - 2, m);
}

typedef struct {
  const Mont32T *m;
  u32 rt[32], irt[32], rate2[32], irate2[32];
} NttInfo;

NttInfo ntt_prepare(u32 G, const Mont32T *m) {
  NttInfo info;
  const u32 one = mont32_trans(1, m);
  const u32 rank2 = __builtin_ctz(m->mod - 1);
  info.m = m;
  G = mont32_trans(G, m);
  info.rt[rank2] = mont32_qpow(G, (m->mod - 1) >> rank2, m);
  info.irt[rank2] = mont32_inv(info.rt[rank2], m);
  for (u32 i = rank2; i != 1; --i) {
    info.rt[i - 1] = mont32_mul(info.rt[i], info.rt[i], m);
    info.irt[i - 1] = mont32_mul(info.irt[i], info.irt[i], m);
  }
  u32 prod = one, iprod = one;
  for (u32 i = 0; i != rank2 - 1; ++i) {
    info.rate2[i] = mont32_mul(prod, info.rt[i + 2], m);
    info.irate2[i] = mont32_mul(iprod, info.irt[i + 2], m);
    prod = mont32_mul(prod, info.irt[i + 2], m);
    iprod = mont32_mul(iprod, info.rt[i + 2], m);
  }
  return info;
}

void ntt(u32 *f, usize n, const NttInfo info) {
  const Mont32T *m = info.m;
  const u32 one = mont32_trans(1, m);
  for (u32 l = n / 2; l != 0; l /= 2) {
    u32 r = one;
    for (u32 i = 0, k = 0; i != n; i += l * 2, ++k) {
      for (u32 j = 0; j != l; ++j) {
        u32 x = f[i + j], y = mont32_mul(f[i + j + l], r, m);
        f[i + j] = mont32_add(x, y, m);
        f[i + j + l] = mont32_sub(x, y, m);
      }
      r = mont32_mul(r, info.rate2[__builtin_ctz(~k)], m);
    }
  }
}

void intt(u32 *f, usize n, const NttInfo info) {
  const Mont32T *m = info.m;
  const u32 one = mont32_trans(1, m);
  for (u32 l = 1; l != n; l *= 2) {
    u32 r = one;
    for (u32 i = 0, k = 0; i != n; i += l * 2, ++k) {
      for (u32 j = 0; j != l; ++j) {
        u32 x = f[i + j], y = f[i + j + l];
        f[i + j] = mont32_add(x, y, m);
        f[i + j + l] = mont32_mul(mont32_sub(x, y, m), r, m);
      }
      r = mont32_mul(r, info.irate2[__builtin_ctz(~k)], m);
    }
  }
}

void dot(u32 *f, const u32 *g, usize n, const Mont32T m) {
  for (u32 i = 0; i != n; ++i)
    f[i] = mont32_mul(f[i], g[i], &m);
}

typedef struct {
  struct stat sb;
  char *p;
} FastI;


extern int fileno(FILE *__stream) __THROW __wur;
#define MADV_SEQUENTIAL 2
extern int madvise(void *__addr, size_t __len, int __advice) __THROW;

FastI fasti_init(FILE *file) {
  FastI fin;
  i32 fd = fileno(file);
  fstat(fd, &fin.sb);
  fin.p = (char *)mmap(NULL, fin.sb.st_size + 4, PROT_READ, MAP_PRIVATE, fd, 0);
  madvise(fin.p, fin.sb.st_size, MADV_SEQUENTIAL);
  return fin;
}

void fasti_destory(FastI *fin) {
  munmap(fin->p, fin->sb.st_size + 4);
}

u32 fasti_get_u32(FastI *fin) {
  u32 x = 0;
  while (*(fin->p) <= ' ')
    fin->p++;
  while (*(fin->p) >= '0')
    x = x * 10 + *(fin->p) - '0', fin->p++;
  return x;
}

typedef struct {
  FILE *f;
  usize bufsz;
  char *buf;
  u32 *pre, p;
} FastO;

FastO fasto_init(FILE *file, u32 size) {
  FastO fout;
  fout.f = file;
  fout.bufsz = size;
  fout.buf = (char *)malloc(size);
  fout.pre = (u32 *)malloc(sizeof(u32) * 10000);
  fout.p = 0;
  for (u32 i = 0; i != 10000; ++i) {
    u32 k = i;
    for (u32 j = 0; j != 4; ++j) {
      fout.pre[i] = fout.pre[i] << 8 | k % 10 | '0';
      k /= 10;
    }
  }
  return fout;
}

void fasto_flush(FastO *fout) {
  fwrite(fout->buf, 1, fout->p, fout->f);
  fout->p = 0;
}

void fasto_destory(FastO *fout) {
  fasto_flush(fout);
}

void fasto_reserve(FastO *fout, u32 len) {
  if (fout->bufsz - fout->p < len)
    fasto_flush(fout);
}

void fasto_push(FastO *fout, const char *s, u32 len) {
  if (len < fout->bufsz / 2) {
    fasto_reserve(fout, len);
    memcpy(&fout->buf[fout->p], s, len);
    fout->p += len;
  } else {
    fasto_flush(fout);
    fwrite(s, 1, len, fout->f);
  }
}

void fasto_put_u32(u32 x, FastO *fout) {
  char arr[32];
  u32 s = 31;
  arr[s] = ' ';
  while (x >= 10000) {
    memcpy(&arr[s -= 4], &fout->pre[x % 10000], 4);
    x /= 10000;
  }
  memcpy(&arr[s -= 4], &fout->pre[x], 4);
  s += x < 100 ? (x < 10 ? 3 : 2) : (x < 1000 ? 1 : 0);
  fasto_push(fout, &arr[s], 32 - s);
}

i32 main() {
  
  
  const Mont32T mod = {998244353, 1996488706, 301989884, 932051910, 998244351};

  FastI fin = fasti_init(stdin);
  FastO fout = fasto_init(stdout, 1 << 16);

  u32 n = fasti_get_u32(&fin), m = fasti_get_u32(&fin);

  n++, m++;
  u32 l = bit_ceil(n + m - 1);
  u32 *f = (u32 *)_mm_malloc(sizeof(u32) * l, 32);
  u32 *g = (u32 *)_mm_malloc(sizeof(u32) * l, 32);

  for (u32 i = 0; i != n; ++i) {
    f[i] = mont32_trans(fasti_get_u32(&fin), &mod);
  }
  for (u32 i = 0; i != m; ++i) {
    g[i] = mont32_trans(fasti_get_u32(&fin), &mod);
  }

  const NttInfo info = ntt_prepare(3, &mod);
  ntt(f, l, info);
  ntt(g, l, info);
  dot(f, g, l, mod);
  intt(f, l, info);

  const u32 ivn = mont32_inv(mont32_trans(l, &mod), &mod);
  for (u32 i = 0; i != n + m - 1; ++i) {
    u32 x = mont32_mul(f[i], ivn, &mod);
    
    fasto_put_u32(mont32_get(x, &mod), &fout);
  }

  _mm_free(f), _mm_free(g);
  fasti_destory(&fin);
  fasto_destory(&fout);
  return 0;
}
