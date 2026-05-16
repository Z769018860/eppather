#define __attribute__(x)
#define __asm__(x)
#define __extension__
#define __restrict
#define __builtin_expect(expr, c) (expr)
#define __builtin_offsetof(T, m) ((size_t)&(((T*)0)->m))
#define __builtin_va_start va_start
#define __builtin_va_end va_end
#define __builtin_va_arg va_arg
#define __builtin_huge_val() (1.0/0.0)

extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));

typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;
typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;
typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef long int __suseconds64_t;
typedef int __daddr_t;
typedef int __key_t;
typedef int __clockid_t;
typedef void * __timer_t;
typedef long int __blksize_t;
typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;
typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;
typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;
typedef long int __fsword_t;
typedef long int __ssize_t;
typedef long int __syscall_slong_t;
typedef unsigned long int __syscall_ulong_t;
typedef __off64_t __loff_t;
typedef char *__caddr_t;
typedef long int __intptr_t;
typedef unsigned int __socklen_t;
typedef int __sig_atomic_t;

enum
{
  _ISupper = ((0) < 8 ? ((1 << (0)) << 8) : ((1 << (0)) >> 8)),
  _ISlower = ((1) < 8 ? ((1 << (1)) << 8) : ((1 << (1)) >> 8)),
  _ISalpha = ((2) < 8 ? ((1 << (2)) << 8) : ((1 << (2)) >> 8)),
  _ISdigit = ((3) < 8 ? ((1 << (3)) << 8) : ((1 << (3)) >> 8)),
  _ISxdigit = ((4) < 8 ? ((1 << (4)) << 8) : ((1 << (4)) >> 8)),
  _ISspace = ((5) < 8 ? ((1 << (5)) << 8) : ((1 << (5)) >> 8)),
  _ISprint = ((6) < 8 ? ((1 << (6)) << 8) : ((1 << (6)) >> 8)),
  _ISgraph = ((7) < 8 ? ((1 << (7)) << 8) : ((1 << (7)) >> 8)),
  _ISblank = ((8) < 8 ? ((1 << (8)) << 8) : ((1 << (8)) >> 8)),
  _IScntrl = ((9) < 8 ? ((1 << (9)) << 8) : ((1 << (9)) >> 8)),
  _ISpunct = ((10) < 8 ? ((1 << (10)) << 8) : ((1 << (10)) >> 8)),
  _ISalnum = ((11) < 8 ? ((1 << (11)) << 8) : ((1 << (11)) >> 8))
};
extern const unsigned short int **__ctype_b_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern const __int32_t **__ctype_tolower_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern const __int32_t **__ctype_toupper_loc (void)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int isalnum (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isalpha (int) __attribute__ ((__nothrow__ , __leaf__));
extern int iscntrl (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isdigit (int) __attribute__ ((__nothrow__ , __leaf__));
extern int islower (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isgraph (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isprint (int) __attribute__ ((__nothrow__ , __leaf__));
extern int ispunct (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isspace (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isupper (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isxdigit (int) __attribute__ ((__nothrow__ , __leaf__));
extern int tolower (int __c) __attribute__ ((__nothrow__ , __leaf__));
extern int toupper (int __c) __attribute__ ((__nothrow__ , __leaf__));
extern int isblank (int) __attribute__ ((__nothrow__ , __leaf__));
extern int isascii (int __c) __attribute__ ((__nothrow__ , __leaf__));
extern int toascii (int __c) __attribute__ ((__nothrow__ , __leaf__));
extern int _toupper (int) __attribute__ ((__nothrow__ , __leaf__));
extern int _tolower (int) __attribute__ ((__nothrow__ , __leaf__));


extern int *__errno_location (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


struct lconv
{
  char *decimal_point;
  char *thousands_sep;
  char *grouping;
  char *int_curr_symbol;
  char *currency_symbol;
  char *mon_decimal_point;
  char *mon_thousands_sep;
  char *mon_grouping;
  char *positive_sign;
  char *negative_sign;
  char int_frac_digits;
  char frac_digits;
  char p_cs_precedes;
  char p_sep_by_space;
  char n_cs_precedes;
  char n_sep_by_space;
  char p_sign_posn;
  char n_sign_posn;
  char int_p_cs_precedes;
  char int_p_sep_by_space;
  char int_n_cs_precedes;
  char int_n_sep_by_space;
  char int_p_sign_posn;
  char int_n_sign_posn;
};
extern char *setlocale (int __category, const char *__locale) __attribute__ ((__nothrow__ , __leaf__));
extern struct lconv *localeconv (void) __attribute__ ((__nothrow__ , __leaf__));


typedef float float_t;
typedef double double_t;
extern int __fpclassify (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern int __signbit (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern int __isinf (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));
extern int __finite (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));
extern int __isnan (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));
extern int __iseqsig (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
extern int __issignaling (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
 extern double acos (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __acos (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double asin (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __asin (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double atan (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atan (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double atan2 (double __y, double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atan2 (double __y, double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double cos (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cos (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double sin (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sin (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double tan (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __tan (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double cosh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cosh (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double sinh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sinh (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double tanh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __tanh (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double acosh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __acosh (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double asinh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __asinh (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double atanh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atanh (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double exp (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double frexp (double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern double __frexp (double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));
extern double ldexp (double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern double __ldexp (double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));
 extern double log (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double log10 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log10 (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double modf (double __x, double *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern double __modf (double __x, double *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
 extern double expm1 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __expm1 (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double log1p (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log1p (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double logb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __logb (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double exp2 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp2 (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double log2 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log2 (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double pow (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __pow (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
extern double sqrt (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sqrt (double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern double hypot (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __hypot (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
 extern double cbrt (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cbrt (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double ceil (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __ceil (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double fabs (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fabs (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double floor (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __floor (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double fmod (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __fmod (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
extern double copysign (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __copysign (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double nan (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern double __nan (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
extern double j0 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __j0 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double j1 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __j1 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double jn (int, double) __attribute__ ((__nothrow__ , __leaf__)); extern double __jn (int, double) __attribute__ ((__nothrow__ , __leaf__));
extern double y0 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __y0 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double y1 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __y1 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double yn (int, double) __attribute__ ((__nothrow__ , __leaf__)); extern double __yn (int, double) __attribute__ ((__nothrow__ , __leaf__));
 extern double erf (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __erf (double) __attribute__ ((__nothrow__ , __leaf__));
 extern double erfc (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __erfc (double) __attribute__ ((__nothrow__ , __leaf__));
extern double lgamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __lgamma (double) __attribute__ ((__nothrow__ , __leaf__));
extern double tgamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __tgamma (double) __attribute__ ((__nothrow__ , __leaf__));
extern double rint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __rint (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double nextafter (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __nextafter (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
extern double nexttoward (double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __nexttoward (double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
extern double remainder (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __remainder (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
extern double scalbn (double __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalbn (double __x, int __n) __attribute__ ((__nothrow__ , __leaf__));
extern int ilogb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogb (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double scalbln (double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalbln (double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));
extern double nearbyint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __nearbyint (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double round (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __round (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double trunc (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __trunc (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern double __remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));
extern long int lrint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrint (double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrint (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long int lround (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lround (double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llround (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llround (double __x) __attribute__ ((__nothrow__ , __leaf__));
extern double fdim (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __fdim (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
extern double fmax (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmax (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double fmin (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmin (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern double fma (double __x, double __y, double __z) __attribute__ ((__nothrow__ , __leaf__)); extern double __fma (double __x, double __y, double __z) __attribute__ ((__nothrow__ , __leaf__));
extern double scalb (double __x, double __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalb (double __x, double __n) __attribute__ ((__nothrow__ , __leaf__));
extern int __fpclassifyf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern int __signbitf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern int __isinff (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));
extern int __finitef (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));
extern int __isnanf (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));
extern int __iseqsigf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
extern int __issignalingf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
 extern float acosf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __acosf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float asinf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __asinf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float atanf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atanf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float atan2f (float __y, float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atan2f (float __y, float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float cosf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __cosf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float sinf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sinf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float tanf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __tanf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float coshf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __coshf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float sinhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sinhf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float tanhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __tanhf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float acoshf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __acoshf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float asinhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __asinhf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float atanhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atanhf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float expf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __expf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern float __frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));
extern float ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern float __ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));
 extern float logf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __logf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float log10f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log10f (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float modff (float __x, float *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern float __modff (float __x, float *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
 extern float expm1f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __expm1f (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float log1pf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log1pf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float logbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __logbf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float exp2f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __exp2f (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float log2f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log2f (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float powf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __powf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
extern float sqrtf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sqrtf (float __x) __attribute__ ((__nothrow__ , __leaf__));
 extern float hypotf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __hypotf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
 extern float cbrtf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __cbrtf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float ceilf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __ceilf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float fabsf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fabsf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float floorf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __floorf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float fmodf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __fmodf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
extern float copysignf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __copysignf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float nanf (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern float __nanf (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
 extern float erff (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __erff (float) __attribute__ ((__nothrow__ , __leaf__));
 extern float erfcf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __erfcf (float) __attribute__ ((__nothrow__ , __leaf__));
extern float lgammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __lgammaf (float) __attribute__ ((__nothrow__ , __leaf__));
extern float tgammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __tgammaf (float) __attribute__ ((__nothrow__ , __leaf__));
extern float rintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __rintf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float nextafterf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __nextafterf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
extern float nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
extern float remainderf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __remainderf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
extern float scalbnf (float __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalbnf (float __x, int __n) __attribute__ ((__nothrow__ , __leaf__));
extern int ilogbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float scalblnf (float __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalblnf (float __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));
extern float nearbyintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __nearbyintf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float roundf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __roundf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float truncf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __truncf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern float __remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));
extern long int lrintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintf (float __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern long int lroundf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundf (float __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundf (float __x) __attribute__ ((__nothrow__ , __leaf__));
extern float fdimf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __fdimf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
extern float fmaxf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fmaxf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float fminf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fminf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern float fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__ , __leaf__)); extern float __fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__ , __leaf__));
extern int __fpclassifyl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern int __signbitl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern int __isinfl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));
extern int __finitel (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));
extern int __isnanl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));
extern int __iseqsigl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
extern int __issignalingl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
 extern long double acosl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __acosl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double asinl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __asinl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double atanl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atanl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double atan2l (long double __y, long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atan2l (long double __y, long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double cosl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __cosl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double sinl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sinl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double tanl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tanl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double coshl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __coshl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double sinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double tanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double acoshl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __acoshl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double asinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __asinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double atanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double expl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __expl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern long double __frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));
extern long double ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern long double __ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));
 extern long double logl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __logl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double log10l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log10l (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern long double __modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
 extern long double expm1l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __expm1l (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double log1pl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log1pl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double logbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __logbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double exp2l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __exp2l (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double log2l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log2l (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double powl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __powl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
extern long double sqrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sqrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
 extern long double hypotl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __hypotl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
 extern long double cbrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __cbrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double ceill (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __ceill (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double fabsl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fabsl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double floorl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __floorl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double fmodl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fmodl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
extern long double copysignl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __copysignl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double nanl (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nanl (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
 extern long double erfl (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __erfl (long double) __attribute__ ((__nothrow__ , __leaf__));
 extern long double erfcl (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __erfcl (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double lgammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __lgammal (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double tgammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tgammal (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double rintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __rintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
extern long double nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
extern long double remainderl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __remainderl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
extern long double scalbnl (long double __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalbnl (long double __x, int __n) __attribute__ ((__nothrow__ , __leaf__));
extern int ilogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));
extern long double nearbyintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nearbyintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double roundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __roundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double truncl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __truncl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern long double __remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));
extern long int lrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long int lroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
extern long double fdiml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fdiml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
extern long double fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double fminl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fminl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern long double fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__ , __leaf__));
extern int __fpclassifyf128 (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern int __signbitf128 (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern int __isinff128 (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));
extern int __finitef128 (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));
extern int __isnanf128 (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));
extern int __iseqsigf128 (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
extern int __issignalingf128 (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
extern int signgam;
enum
  {
    FP_NAN =
      0,
    FP_INFINITE =
      1,
    FP_ZERO =
      2,
    FP_SUBNORMAL =
      3,
    FP_NORMAL =
      4
  };


typedef long int __jmp_buf[8];
typedef struct
{
  unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
} __sigset_t;
struct __jmp_buf_tag
  {
    __jmp_buf __jmpbuf;
    int __mask_was_saved;
    __sigset_t __saved_mask;
  };
typedef struct __jmp_buf_tag jmp_buf[1];
extern int setjmp (jmp_buf __env) __attribute__ ((__nothrow__));
extern int __sigsetjmp (struct __jmp_buf_tag __env[1], int __savemask) __attribute__ ((__nothrow__));
extern int _setjmp (struct __jmp_buf_tag __env[1]) __attribute__ ((__nothrow__));
extern void longjmp (struct __jmp_buf_tag __env[1], int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));
extern void _longjmp (struct __jmp_buf_tag __env[1], int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));
typedef struct __jmp_buf_tag sigjmp_buf[1];
extern void siglongjmp (sigjmp_buf __env, int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));


typedef __sig_atomic_t sig_atomic_t;
typedef __sigset_t sigset_t;
typedef __pid_t pid_t;
typedef __uid_t uid_t;
typedef __time_t time_t;
struct timespec
{
  __time_t tv_sec;
  __syscall_slong_t tv_nsec;
};
union sigval
{
  int sival_int;
  void *sival_ptr;
};
typedef union sigval __sigval_t;
typedef struct
  {
    int si_signo;
    int si_errno;
    int si_code;
    int __pad0;
    union
      {
 int _pad[((128 / sizeof (int)) - 4)];
 struct
   {
     __pid_t si_pid;
     __uid_t si_uid;
   } _kill;
 struct
   {
     int si_tid;
     int si_overrun;
     __sigval_t si_sigval;
   } _timer;
 struct
   {
     __pid_t si_pid;
     __uid_t si_uid;
     __sigval_t si_sigval;
   } _rt;
 struct
   {
     __pid_t si_pid;
     __uid_t si_uid;
     int si_status;
     __clock_t si_utime;
     __clock_t si_stime;
   } _sigchld;
 struct
   {
     void *si_addr;
    
     short int si_addr_lsb;
     union
       {
  struct
    {
      void *_lower;
      void *_upper;
    } _addr_bnd;
  __uint32_t _pkey;
       } _bounds;
   } _sigfault;
 struct
   {
     long int si_band;
     int si_fd;
   } _sigpoll;
 struct
   {
     void *_call_addr;
     int _syscall;
     unsigned int _arch;
   } _sigsys;
      } _sifields;
  } siginfo_t ;
enum
{
  SI_ASYNCNL = -60,
  SI_DETHREAD = -7,
  SI_TKILL,
  SI_SIGIO,
  SI_ASYNCIO,
  SI_MESGQ,
  SI_TIMER,
  SI_QUEUE,
  SI_USER,
  SI_KERNEL = 0x80
};
enum
{
  ILL_ILLOPC = 1,
  ILL_ILLOPN,
  ILL_ILLADR,
  ILL_ILLTRP,
  ILL_PRVOPC,
  ILL_PRVREG,
  ILL_COPROC,
  ILL_BADSTK,
  ILL_BADIADDR
};
enum
{
  FPE_INTDIV = 1,
  FPE_INTOVF,
  FPE_FLTDIV,
  FPE_FLTOVF,
  FPE_FLTUND,
  FPE_FLTRES,
  FPE_FLTINV,
  FPE_FLTSUB,
  FPE_FLTUNK = 14,
  FPE_CONDTRAP
};
enum
{
  SEGV_MAPERR = 1,
  SEGV_ACCERR,
  SEGV_BNDERR,
  SEGV_PKUERR,
  SEGV_ACCADI,
  SEGV_ADIDERR,
  SEGV_ADIPERR,
  SEGV_MTEAERR,
  SEGV_MTESERR,
  SEGV_CPERR
};
enum
{
  BUS_ADRALN = 1,
  BUS_ADRERR,
  BUS_OBJERR,
  BUS_MCEERR_AR,
  BUS_MCEERR_AO
};
enum
{
  TRAP_BRKPT = 1,
  TRAP_TRACE,
  TRAP_BRANCH,
  TRAP_HWBKPT,
  TRAP_UNK
};
enum
{
  CLD_EXITED = 1,
  CLD_KILLED,
  CLD_DUMPED,
  CLD_TRAPPED,
  CLD_STOPPED,
  CLD_CONTINUED
};
enum
{
  POLL_IN = 1,
  POLL_OUT,
  POLL_MSG,
  POLL_ERR,
  POLL_PRI,
  POLL_HUP
};
typedef union pthread_attr_t pthread_attr_t;
typedef struct sigevent
  {
    __sigval_t sigev_value;
    int sigev_signo;
    int sigev_notify;
    union
      {
 int _pad[((64 / sizeof (int)) - 4)];
 __pid_t _tid;
 struct
   {
     void (*_function) (__sigval_t);
     pthread_attr_t *_attribute;
   } _sigev_thread;
      } _sigev_un;
  } sigevent_t;
enum
{
  SIGEV_SIGNAL = 0,
  SIGEV_NONE,
  SIGEV_THREAD,
  SIGEV_THREAD_ID = 4
};
typedef void (*__sighandler_t) (int);
extern __sighandler_t __sysv_signal (int __sig, __sighandler_t __handler)
     __attribute__ ((__nothrow__ , __leaf__));
extern __sighandler_t signal (int __sig, __sighandler_t __handler) __asm__ ("" "__sysv_signal") __attribute__ ((__nothrow__ , __leaf__));
extern __sighandler_t bsd_signal (int __sig, __sighandler_t __handler)
     __attribute__ ((__nothrow__ , __leaf__));
extern int kill (__pid_t __pid, int __sig) __attribute__ ((__nothrow__ , __leaf__));
extern int killpg (__pid_t __pgrp, int __sig) __attribute__ ((__nothrow__ , __leaf__));
extern int raise (int __sig) __attribute__ ((__nothrow__ , __leaf__));
extern int sigpause (int __sig) __asm__ ("__xpg_sigpause")
  __attribute__ ((__deprecated__ ("Use the sigsuspend function instead")));
extern int sigemptyset (sigset_t *__set) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sigfillset (sigset_t *__set) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sigaddset (sigset_t *__set, int __signo) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sigdelset (sigset_t *__set, int __signo) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sigismember (const sigset_t *__set, int __signo)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
struct sigaction
  {
    union
      {
 __sighandler_t sa_handler;
 void (*sa_sigaction) (int, siginfo_t *, void *);
      }
    __sigaction_handler;
    __sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer) (void);
  };
extern int sigprocmask (int __how, const sigset_t *__restrict __set,
   sigset_t *__restrict __oset) __attribute__ ((__nothrow__ , __leaf__));
extern int sigsuspend (const sigset_t *__set) __attribute__ ((__nonnull__ (1)));
extern int sigaction (int __sig, const struct sigaction *__restrict __act,
        struct sigaction *__restrict __oact) __attribute__ ((__nothrow__ , __leaf__));
extern int sigpending (sigset_t *__set) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sigwait (const sigset_t *__restrict __set, int *__restrict __sig)
     __attribute__ ((__nonnull__ (1, 2)));
extern int sigwaitinfo (const sigset_t *__restrict __set,
   siginfo_t *__restrict __info) __attribute__ ((__nonnull__ (1)));
extern int sigtimedwait (const sigset_t *__restrict __set,
    siginfo_t *__restrict __info,
    const struct timespec *__restrict __timeout)
     __attribute__ ((__nonnull__ (1)));
extern int sigqueue (__pid_t __pid, int __sig, const union sigval __val)
     __attribute__ ((__nothrow__ , __leaf__));
typedef long unsigned int size_t;
typedef struct
  {
    void *ss_sp;
    int ss_flags;
    size_t ss_size;
  } stack_t;
__extension__ typedef long long int greg_t;
typedef greg_t gregset_t[23];
struct _libc_fpxreg
{
  unsigned short int __significand[4];
  unsigned short int __exponent;
  unsigned short int __glibc_reserved1[3];
};
struct _libc_xmmreg
{
  __uint32_t __element[4];
};
struct _libc_fpstate
{
  __uint16_t __cwd;
  __uint16_t __swd;
  __uint16_t __ftw;
  __uint16_t __fop;
  __uint64_t __rip;
  __uint64_t __rdp;
  __uint32_t __mxcsr;
  __uint32_t __mxcr_mask;
  struct _libc_fpxreg _st[8];
  struct _libc_xmmreg _xmm[16];
  __uint32_t __glibc_reserved1[24];
};
typedef struct _libc_fpstate *fpregset_t;
typedef struct
  {
    gregset_t __gregs;
    fpregset_t __fpregs;
    __extension__ unsigned long long __reserved1 [8];
} mcontext_t;
typedef struct ucontext_t
  {
    unsigned long int __uc_flags;
    struct ucontext_t *uc_link;
    stack_t uc_stack;
    mcontext_t uc_mcontext;
    sigset_t uc_sigmask;
    struct _libc_fpstate __fpregs_mem;
    __extension__ unsigned long long int __ssp[4];
  } ucontext_t;
extern int siginterrupt (int __sig, int __interrupt) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__deprecated__ ("Use sigaction with SA_RESTART instead")));
enum
{
  SS_ONSTACK = 1,
  SS_DISABLE
};
extern int sigaltstack (const stack_t *__restrict __ss,
   stack_t *__restrict __oss) __attribute__ ((__nothrow__ , __leaf__));
struct sigstack
  {
    void *ss_sp;
    int ss_onstack;
  };
extern int sighold (int __sig) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__deprecated__ ("Use the sigprocmask function instead")));
extern int sigrelse (int __sig) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__deprecated__ ("Use the sigprocmask function instead")));
extern int sigignore (int __sig) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__deprecated__ ("Use the signal function instead")));
extern __sighandler_t sigset (int __sig, __sighandler_t __disp) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__deprecated__ ("Use the signal and sigprocmask functions instead")));
typedef union
{
  __extension__ unsigned long long int __value64;
  struct
  {
    unsigned int __low;
    unsigned int __high;
  } __value32;
} __atomic_wide_counter;
typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;
struct __pthread_mutex_s
{
  int __lock;
  unsigned int __count;
  int __owner;
  unsigned int __nusers;
  int __kind;
  short __spins;
  short __elision;
  __pthread_list_t __list;
};
struct __pthread_rwlock_arch_t
{
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad3;
  unsigned int __pad4;
  int __cur_writer;
  int __shared;
  signed char __rwelision;
  unsigned char __pad1[7];
  unsigned long int __pad2;
  unsigned int __flags;
};
struct __pthread_cond_s
{
  __atomic_wide_counter __wseq;
  __atomic_wide_counter __g1_start;
  unsigned int __g_refs[2] ;
  unsigned int __g_size[2];
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
};
typedef unsigned int __tss_t;
typedef unsigned long int __thrd_t;
typedef struct
{
  int __data ;
} __once_flag;
typedef unsigned long int pthread_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;
typedef unsigned int pthread_key_t;
typedef int pthread_once_t;
union pthread_attr_t
{
  char __size[56];
  long int __align;
};
typedef union
{
  struct __pthread_mutex_s __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;
typedef union
{
  struct __pthread_cond_s __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;
typedef union
{
  struct __pthread_rwlock_arch_t __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;
typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;
typedef volatile int pthread_spinlock_t;
typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
extern int pthread_sigmask (int __how,
       const __sigset_t *__restrict __newmask,
       __sigset_t *__restrict __oldmask)__attribute__ ((__nothrow__ , __leaf__));
extern int pthread_kill (pthread_t __threadid, int __signo) __attribute__ ((__nothrow__ , __leaf__));
extern int __libc_current_sigrtmin (void) __attribute__ ((__nothrow__ , __leaf__));
extern int __libc_current_sigrtmax (void) __attribute__ ((__nothrow__ , __leaf__));

typedef void* __gnuc_va_list;
typedef __gnuc_va_list va_list;
typedef long int ptrdiff_t;
typedef int wchar_t;
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
} max_align_t;

typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
typedef struct _G_fpos_t
{
  __off_t __pos;
  __mbstate_t __state;
} __fpos_t;
typedef struct _G_fpos64_t
{
  __off64_t __pos;
  __mbstate_t __state;
} __fpos64_t;
struct _IO_FILE;
typedef struct _IO_FILE __FILE;
struct _IO_FILE;
typedef struct _IO_FILE FILE;
struct _IO_FILE;
struct _IO_marker;
struct _IO_codecvt;
struct _IO_wide_data;
typedef void _IO_lock_t;
struct _IO_FILE
{
  int _flags;
  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;
  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;
  struct _IO_marker *_markers;
  struct _IO_FILE *_chain;
  int _fileno;
  int _flags2;
  __off_t _old_offset;
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];
  _IO_lock_t *_lock;
  __off64_t _offset;
  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
  size_t __pad5;
  int _mode;
  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};
typedef __off64_t off_t;
typedef __fpos64_t fpos_t;
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));
extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));
extern int fclose (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern FILE *tmpfile (void) __asm__ ("" "tmpfile64")
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
extern char *tmpnam (char[20]) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *tempnam (const char *__dir, const char *__pfx)
   __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (__builtin_free, 1)));
extern int fflush (FILE *__stream);
extern FILE *fopen (const char *__restrict __filename, const char *__restrict __modes) __asm__ ("" "fopen64")
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
extern FILE *freopen (const char *__restrict __filename, const char *__restrict __modes, FILE *__restrict __stream) __asm__ ("" "freopen64")
  __attribute__ ((__nonnull__ (3)));
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__nonnull__ (1)));
extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...) __attribute__ ((__nonnull__ (1)));
extern int printf (const char *__restrict __format, ...);
extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));
extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nonnull__ (1)));
extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);
extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));
extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));
extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));
extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) __attribute__ ((__nonnull__ (1)));
extern int scanf (const char *__restrict __format, ...) ;
extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));
extern int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf") __attribute__ ((__nonnull__ (1)));
extern int scanf (const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf") ;
extern int sscanf (const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__ , __leaf__));
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) __attribute__ ((__nonnull__ (1)));
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")
     __attribute__ ((__format__ (__scanf__, 2, 0))) __attribute__ ((__nonnull__ (1)));
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__format__ (__scanf__, 2, 0)));
extern int fgetc (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int getc (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int getchar (void);
extern int getc_unlocked (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int getchar_unlocked (void);
extern int fputc (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));
extern int putc (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));
extern int putchar (int __c);
extern int putc_unlocked (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));
extern int putchar_unlocked (int __c);
extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     __attribute__ ((__access__ (__write_only__, 1, 2))) __attribute__ ((__nonnull__ (3)));
extern int fputs (const char *__restrict __s, FILE *__restrict __stream)
  __attribute__ ((__nonnull__ (2)));
extern int puts (const char *__s);
extern int ungetc (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));
extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream)
  __attribute__ ((__nonnull__ (4)));
extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s) __attribute__ ((__nonnull__ (4)));
extern int fseek (FILE *__stream, long int __off, int __whence)
  __attribute__ ((__nonnull__ (1)));
extern long int ftell (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern void rewind (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int fseeko (FILE *__stream, __off64_t __off, int __whence) __asm__ ("" "fseeko64") __attribute__ ((__nonnull__ (1)));
extern __off64_t ftello (FILE *__stream) __asm__ ("" "ftello64")
  __attribute__ ((__nonnull__ (1)));
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos) __asm__ ("" "fgetpos64")
  __attribute__ ((__nonnull__ (1)));
extern int fsetpos (FILE *__stream, const fpos_t *__pos) __asm__ ("" "fsetpos64")
  __attribute__ ((__nonnull__ (1)));
extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void perror (const char *__s) __attribute__ ((__cold__));
extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int pclose (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern FILE *popen (const char *__command, const char *__modes)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (pclose, 1))) ;
extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__access__ (__write_only__, 1)));
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);


typedef struct
  {
    int quot;
    int rem;
  } div_t;
typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;
__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;
extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__ , __leaf__)) ;
extern double atof (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern int atoi (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern long int atol (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
__extension__ extern long long int atoll (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern double strtod (const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern float strtof (const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long double strtold (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int strtol (const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern unsigned long int strtoul (const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
__extension__
extern long long int strtoll (const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern char *l64a (long int __n) __attribute__ ((__nothrow__ , __leaf__)) ;
extern long int a64l (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

typedef __ino64_t ino_t;
typedef __dev_t dev_t;
typedef __gid_t gid_t;
typedef __mode_t mode_t;
typedef __nlink_t nlink_t;
typedef __id_t id_t;
typedef __ssize_t ssize_t;
typedef __key_t key_t;
typedef __clock_t clock_t;
typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
typedef __useconds_t useconds_t;
typedef __suseconds_t suseconds_t;
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
typedef __uint8_t u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;
typedef int register_t __attribute__ ((__mode__ (__word__)));
typedef __blksize_t blksize_t;
typedef __blkcnt64_t blkcnt_t;
typedef __fsblkcnt64_t fsblkcnt_t;
typedef __fsfilcnt64_t fsfilcnt_t;

extern long int random (void) __attribute__ ((__nothrow__ , __leaf__));
extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));
extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int rand (void) __attribute__ ((__nothrow__ , __leaf__));
extern void srand (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));
extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__ , __leaf__));
extern double drand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int lrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int mrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void srand48 (long int __seedval) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;
extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (1, 2))) ;
extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__)) __attribute__ ((__alloc_size__ (2)));
extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));
extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern void *aligned_alloc (size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_align__ (1)))
     __attribute__ ((__alloc_size__ (2))) ;
extern void abort (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int at_quick_exit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern void quick_exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern void _Exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern char *getenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int putenv (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int setenv (const char *__name, const char *__value, int __replace)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int unsetenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern char *mktemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int mkstemp (char *__template) __asm__ ("" "mkstemp64")
     __attribute__ ((__nonnull__ (1))) ;
extern int system (const char *__command) ;
extern char *realpath (const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__ , __leaf__)) ;
typedef int (*__compar_fn_t) (const void *, const void *);
extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;
extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
extern int abs (int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;
extern int mblen (const char *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));
extern int mbtowc (wchar_t *__restrict __pwc,
     const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));
extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__ , __leaf__));
extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__))
    __attribute__ ((__access__ (__read_only__, 2)));
extern size_t wcstombs (char *__restrict __s,
   const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__access__ (__write_only__, 1, 3)))
  __attribute__ ((__access__ (__read_only__, 2)));
extern int getsubopt (char **__restrict __optionp,
        char *const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;
extern int posix_openpt (int __oflag) ;
extern int grantpt (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int unlockpt (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern char *ptsname (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;


extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memmove (void *__dest, const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
    __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__access__ (__write_only__, 1, 4)));
extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int __memcmpeq (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcoll (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
    __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) __attribute__ ((__access__ (__write_only__, 1, 3)));
extern char *strdup (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
extern char *strchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *strrchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern size_t strcspn (const char *__s, const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strspn (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strpbrk (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strstr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
extern size_t strlen (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));
extern int strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__ ("" "__xpg_strerror_r") __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)))
    __attribute__ ((__access__ (__write_only__, 2, 3)));

struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
  long int __tm_gmtoff;
  const char *__tm_zone;
};
struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };
struct sigevent;

extern clock_t clock (void) __attribute__ ((__nothrow__ , __leaf__));
extern time_t time (time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));
extern double difftime (time_t __time1, time_t __time0)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern time_t mktime (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));
extern size_t strftime (char *__restrict __s, size_t __maxsize,
   const char *__restrict __format,
   const struct tm *__restrict __tp)
   __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3, 4)));
extern char *strptime (const char *__restrict __s,
         const char *__restrict __fmt, struct tm *__tp)
     __attribute__ ((__nothrow__ , __leaf__));
extern struct tm *gmtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));
extern struct tm *localtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));
extern struct tm *gmtime_r (const time_t *__restrict __timer,
       struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));
extern struct tm *localtime_r (const time_t *__restrict __timer,
          struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));
extern char *asctime (const struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));
extern char *ctime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));
extern char *asctime_r (const struct tm *__restrict __tp,
   char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));
extern char *ctime_r (const time_t *__restrict __timer,
        char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));
extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;
extern char *tzname[2];
extern void tzset (void) __attribute__ ((__nothrow__ , __leaf__));
extern int daylight;
extern long int timezone;
extern int nanosleep (const struct timespec *__requested_time,
        struct timespec *__remaining);
extern int clock_getres (clockid_t __clock_id, struct timespec *__res) __attribute__ ((__nothrow__ , __leaf__));
extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       const struct timespec *__req,
       struct timespec *__rem);
extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) __attribute__ ((__nothrow__ , __leaf__));
extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) __attribute__ ((__nothrow__ , __leaf__));
extern int timer_delete (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));
extern int timer_settime (timer_t __timerid, int __flags,
     const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) __attribute__ ((__nothrow__ , __leaf__));
extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     __attribute__ ((__nothrow__ , __leaf__));
extern int timer_getoverrun (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));
extern int timespec_get (struct timespec *__ts, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int getdate_err;
extern struct tm *getdate (const char *__string);

typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;
typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;
typedef signed char int_fast8_t;
typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
typedef long int intptr_t;
typedef unsigned long int uintptr_t;
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
typedef struct lua_State lua_State;
typedef double lua_Number;
typedef long long lua_Integer;
typedef unsigned long long lua_Unsigned;
typedef intptr_t lua_KContext;
typedef int (*lua_CFunction) (lua_State *L);
typedef int (*lua_KFunction) (lua_State *L, int status, lua_KContext ctx);
typedef const char * (*lua_Reader) (lua_State *L, void *ud, size_t *sz);
typedef int (*lua_Writer) (lua_State *L, const void *p, size_t sz, void *ud);
typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);
typedef void (*lua_WarnFunction) (void *ud, const char *msg, int tocont);
typedef struct lua_Debug lua_Debug;
typedef void (*lua_Hook) (lua_State *L, lua_Debug *ar);
extern const char lua_ident[];
extern lua_State *(lua_newstate) (lua_Alloc f, void *ud, unsigned seed);
extern void (lua_close) (lua_State *L);
extern lua_State *(lua_newthread) (lua_State *L);
extern int (lua_closethread) (lua_State *L, lua_State *from);
extern lua_CFunction (lua_atpanic) (lua_State *L, lua_CFunction panicf);
extern lua_Number (lua_version) (lua_State *L);
extern int (lua_absindex) (lua_State *L, int idx);
extern int (lua_gettop) (lua_State *L);
extern void (lua_settop) (lua_State *L, int idx);
extern void (lua_pushvalue) (lua_State *L, int idx);
extern void (lua_rotate) (lua_State *L, int idx, int n);
extern void (lua_copy) (lua_State *L, int fromidx, int toidx);
extern int (lua_checkstack) (lua_State *L, int n);
extern void (lua_xmove) (lua_State *from, lua_State *to, int n);
extern int (lua_isnumber) (lua_State *L, int idx);
extern int (lua_isstring) (lua_State *L, int idx);
extern int (lua_iscfunction) (lua_State *L, int idx);
extern int (lua_isinteger) (lua_State *L, int idx);
extern int (lua_isuserdata) (lua_State *L, int idx);
extern int (lua_type) (lua_State *L, int idx);
extern const char *(lua_typename) (lua_State *L, int tp);
extern lua_Number (lua_tonumberx) (lua_State *L, int idx, int *isnum);
extern lua_Integer (lua_tointegerx) (lua_State *L, int idx, int *isnum);
extern int (lua_toboolean) (lua_State *L, int idx);
extern const char *(lua_tolstring) (lua_State *L, int idx, size_t *len);
extern lua_Unsigned (lua_rawlen) (lua_State *L, int idx);
extern lua_CFunction (lua_tocfunction) (lua_State *L, int idx);
extern void *(lua_touserdata) (lua_State *L, int idx);
extern lua_State *(lua_tothread) (lua_State *L, int idx);
extern const void *(lua_topointer) (lua_State *L, int idx);
extern void (lua_arith) (lua_State *L, int op);
extern int (lua_rawequal) (lua_State *L, int idx1, int idx2);
extern int (lua_compare) (lua_State *L, int idx1, int idx2, int op);
extern void (lua_pushnil) (lua_State *L);
extern void (lua_pushnumber) (lua_State *L, lua_Number n);
extern void (lua_pushinteger) (lua_State *L, lua_Integer n);
extern const char *(lua_pushlstring) (lua_State *L, const char *s, size_t len);
extern const char *(lua_pushexternalstring) (lua_State *L,
  const char *s, size_t len, lua_Alloc falloc, void *ud);
extern const char *(lua_pushstring) (lua_State *L, const char *s);
extern const char *(lua_pushvfstring) (lua_State *L, const char *fmt,
                                                      va_list argp);
extern const char *(lua_pushfstring) (lua_State *L, const char *fmt, ...);
extern void (lua_pushcclosure) (lua_State *L, lua_CFunction fn, int n);
extern void (lua_pushboolean) (lua_State *L, int b);
extern void (lua_pushlightuserdata) (lua_State *L, void *p);
extern int (lua_pushthread) (lua_State *L);
extern int (lua_getglobal) (lua_State *L, const char *name);
extern int (lua_gettable) (lua_State *L, int idx);
extern int (lua_getfield) (lua_State *L, int idx, const char *k);
extern int (lua_geti) (lua_State *L, int idx, lua_Integer n);
extern int (lua_rawget) (lua_State *L, int idx);
extern int (lua_rawgeti) (lua_State *L, int idx, lua_Integer n);
extern int (lua_rawgetp) (lua_State *L, int idx, const void *p);
extern void (lua_createtable) (lua_State *L, int narr, int nrec);
extern void *(lua_newuserdatauv) (lua_State *L, size_t sz, int nuvalue);
extern int (lua_getmetatable) (lua_State *L, int objindex);
extern int (lua_getiuservalue) (lua_State *L, int idx, int n);
extern void (lua_setglobal) (lua_State *L, const char *name);
extern void (lua_settable) (lua_State *L, int idx);
extern void (lua_setfield) (lua_State *L, int idx, const char *k);
extern void (lua_seti) (lua_State *L, int idx, lua_Integer n);
extern void (lua_rawset) (lua_State *L, int idx);
extern void (lua_rawseti) (lua_State *L, int idx, lua_Integer n);
extern void (lua_rawsetp) (lua_State *L, int idx, const void *p);
extern int (lua_setmetatable) (lua_State *L, int objindex);
extern int (lua_setiuservalue) (lua_State *L, int idx, int n);
extern void (lua_callk) (lua_State *L, int nargs, int nresults,
                           lua_KContext ctx, lua_KFunction k);
extern int (lua_pcallk) (lua_State *L, int nargs, int nresults, int errfunc,
                            lua_KContext ctx, lua_KFunction k);
extern int (lua_load) (lua_State *L, lua_Reader reader, void *dt,
                          const char *chunkname, const char *mode);
extern int (lua_dump) (lua_State *L, lua_Writer writer, void *data, int strip);
extern int (lua_yieldk) (lua_State *L, int nresults, lua_KContext ctx,
                               lua_KFunction k);
extern int (lua_resume) (lua_State *L, lua_State *from, int narg,
                               int *nres);
extern int (lua_status) (lua_State *L);
extern int (lua_isyieldable) (lua_State *L);
extern void (lua_setwarnf) (lua_State *L, lua_WarnFunction f, void *ud);
extern void (lua_warning) (lua_State *L, const char *msg, int tocont);
extern int (lua_gc) (lua_State *L, int what, ...);
extern int (lua_error) (lua_State *L);
extern int (lua_next) (lua_State *L, int idx);
extern void (lua_concat) (lua_State *L, int n);
extern void (lua_len) (lua_State *L, int idx);
extern unsigned (lua_numbertocstring) (lua_State *L, int idx, char *buff);
extern size_t (lua_stringtonumber) (lua_State *L, const char *s);
extern lua_Alloc (lua_getallocf) (lua_State *L, void **ud);
extern void (lua_setallocf) (lua_State *L, lua_Alloc f, void *ud);
extern void (lua_toclose) (lua_State *L, int idx);
extern void (lua_closeslot) (lua_State *L, int idx);
extern int (lua_getstack) (lua_State *L, int level, lua_Debug *ar);
extern int (lua_getinfo) (lua_State *L, const char *what, lua_Debug *ar);
extern const char *(lua_getlocal) (lua_State *L, const lua_Debug *ar, int n);
extern const char *(lua_setlocal) (lua_State *L, const lua_Debug *ar, int n);
extern const char *(lua_getupvalue) (lua_State *L, int funcindex, int n);
extern const char *(lua_setupvalue) (lua_State *L, int funcindex, int n);
extern void *(lua_upvalueid) (lua_State *L, int fidx, int n);
extern void (lua_upvaluejoin) (lua_State *L, int fidx1, int n1,
                                               int fidx2, int n2);
extern void (lua_sethook) (lua_State *L, lua_Hook func, int mask, int count);
extern lua_Hook (lua_gethook) (lua_State *L);
extern int (lua_gethookmask) (lua_State *L);
extern int (lua_gethookcount) (lua_State *L);
struct lua_Debug {
  int event;
  const char *name;
  const char *namewhat;
  const char *what;
  const char *source;
  size_t srclen;
  int currentline;
  int linedefined;
  int lastlinedefined;
  unsigned char nups;
  unsigned char nparams;
  char isvararg;
  unsigned char extraargs;
  char istailcall;
  int ftransfer;
  int ntransfer;
  char short_src[60];
  struct CallInfo *i_ci;
};
typedef ptrdiff_t l_mem;
typedef size_t lu_mem;
typedef unsigned char lu_byte;
typedef signed char ls_byte;
typedef lu_byte TStatus;
typedef double l_uacNumber;
typedef long long l_uacInt;
typedef void (*voidf)(void);
typedef unsigned int l_uint32;
typedef struct CallInfo CallInfo;
typedef union Value {
  struct GCObject *gc;
  void *p;
  lua_CFunction f;
  lua_Integer i;
  lua_Number n;
  lu_byte ub;
} Value;
typedef struct TValue {
  Value value_; lu_byte tt_;
} TValue;
typedef union StackValue {
  TValue val;
  struct {
    Value value_; lu_byte tt_;
    unsigned short delta;
  } tbclist;
} StackValue;
typedef StackValue *StkId;
typedef union {
  StkId p;
  ptrdiff_t offset;
} StkIdRel;
typedef struct GCObject {
  struct GCObject *next; lu_byte tt; lu_byte marked;
} GCObject;
typedef struct TString {
  struct GCObject *next; lu_byte tt; lu_byte marked;
  lu_byte extra;
  ls_byte shrlen;
  unsigned int hash;
  union {
    size_t lnglen;
    struct TString *hnext;
  } u;
  char *contents;
  lua_Alloc falloc;
  void *ud;
} TString;
typedef union UValue {
  TValue uv;
  long double u; void *s; long long l;
} UValue;
typedef struct Udata {
  struct GCObject *next; lu_byte tt; lu_byte marked;
  unsigned short nuvalue;
  size_t len;
  struct Table *metatable;
  GCObject *gclist;
  UValue uv[1];
} Udata;
typedef struct Udata0 {
  struct GCObject *next; lu_byte tt; lu_byte marked;
  unsigned short nuvalue;
  size_t len;
  struct Table *metatable;
  union {long double u; void *s; long long l;} bindata;
} Udata0;
typedef l_uint32 Instruction;
typedef struct Upvaldesc {
  TString *name;
  lu_byte instack;
  lu_byte idx;
  lu_byte kind;
} Upvaldesc;
typedef struct LocVar {
  TString *varname;
  int startpc;
  int endpc;
} LocVar;
typedef struct AbsLineInfo {
  int pc;
  int line;
} AbsLineInfo;
typedef struct Proto {
  struct GCObject *next; lu_byte tt; lu_byte marked;
  lu_byte numparams;
  lu_byte flag;
  lu_byte maxstacksize;
  int sizeupvalues;
  int sizek;
  int sizecode;
  int sizelineinfo;
  int sizep;
  int sizelocvars;
  int sizeabslineinfo;
  int linedefined;
  int lastlinedefined;
  TValue *k;
  Instruction *code;
  struct Proto **p;
  Upvaldesc *upvalues;
  ls_byte *lineinfo;
  AbsLineInfo *abslineinfo;
  LocVar *locvars;
  TString *source;
  GCObject *gclist;
} Proto;
typedef struct UpVal {
  struct GCObject *next; lu_byte tt; lu_byte marked;
  union {
    TValue *p;
    ptrdiff_t offset;
  } v;
  union {
    struct {
      struct UpVal *next;
      struct UpVal **previous;
    } open;
    TValue value;
  } u;
} UpVal;
typedef struct CClosure {
  struct GCObject *next; lu_byte tt; lu_byte marked; lu_byte nupvalues; GCObject *gclist;
  lua_CFunction f;
  TValue upvalue[1];
} CClosure;
typedef struct LClosure {
  struct GCObject *next; lu_byte tt; lu_byte marked; lu_byte nupvalues; GCObject *gclist;
  struct Proto *p;
  UpVal *upvals[1];
} LClosure;
typedef union Closure {
  CClosure c;
  LClosure l;
} Closure;
typedef union Node {
  struct NodeKey {
    Value value_; lu_byte tt_;
    lu_byte key_tt;
    int next;
    Value key_val;
  } u;
  TValue i_val;
} Node;
typedef struct Table {
  struct GCObject *next; lu_byte tt; lu_byte marked;
  lu_byte flags;
  lu_byte lsizenode;
  unsigned int asize;
  Value *array;
  Node *node;
  struct Table *metatable;
  GCObject *gclist;
} Table;
static int luaO_utf8esc (char *buff, l_uint32 x);
static lu_byte luaO_ceillog2 (unsigned int x);
static lu_byte luaO_codeparam (unsigned int p);
static l_mem luaO_applyparam (lu_byte p, l_mem x);
static int luaO_rawarith (lua_State *L, int op, const TValue *p1,
                             const TValue *p2, TValue *res);
static void luaO_arith (lua_State *L, int op, const TValue *p1,
                           const TValue *p2, StkId res);
static size_t luaO_str2num (const char *s, TValue *o);
static unsigned luaO_tostringbuff (const TValue *obj, char *buff);
static lu_byte luaO_hexavalue (int c);
static void luaO_tostring (lua_State *L, TValue *obj);
static const char *luaO_pushvfstring (lua_State *L, const char *fmt,
                                                       va_list argp);
static const char *luaO_pushfstring (lua_State *L, const char *fmt, ...);
static void luaO_chunkid (char *out, const char *source, size_t srclen);
typedef enum {
  TM_INDEX,
  TM_NEWINDEX,
  TM_GC,
  TM_MODE,
  TM_LEN,
  TM_EQ,
  TM_ADD,
  TM_SUB,
  TM_MUL,
  TM_MOD,
  TM_POW,
  TM_DIV,
  TM_IDIV,
  TM_BAND,
  TM_BOR,
  TM_BXOR,
  TM_SHL,
  TM_SHR,
  TM_UNM,
  TM_BNOT,
  TM_LT,
  TM_LE,
  TM_CONCAT,
  TM_CALL,
  TM_CLOSE,
  TM_N
} TMS;

static const char *luaT_objtypename (lua_State *L, const TValue *o);
static const TValue *luaT_gettm (Table *events, TMS event, TString *ename);
static const TValue *luaT_gettmbyobj (lua_State *L, const TValue *o,
                                                       TMS event);
static void luaT_init (lua_State *L);
static void luaT_callTM (lua_State *L, const TValue *f, const TValue *p1,
                            const TValue *p2, const TValue *p3);
static lu_byte luaT_callTMres (lua_State *L, const TValue *f,
                               const TValue *p1, const TValue *p2, StkId p3);
static void luaT_trybinTM (lua_State *L, const TValue *p1, const TValue *p2,
                              StkId res, TMS event);
static void luaT_tryconcatTM (lua_State *L);
static void luaT_trybinassocTM (lua_State *L, const TValue *p1,
       const TValue *p2, int inv, StkId res, TMS event);
static void luaT_trybiniTM (lua_State *L, const TValue *p1, lua_Integer i2,
                               int inv, StkId res, TMS event);
static int luaT_callorderTM (lua_State *L, const TValue *p1,
                                const TValue *p2, TMS event);
static int luaT_callorderiTM (lua_State *L, const TValue *p1, int v2,
                                 int inv, int isfloat, TMS event);
static void luaT_adjustvarargs (lua_State *L, struct CallInfo *ci,
                                                 const Proto *p);
static void luaT_getvararg (CallInfo *ci, StkId ra, TValue *rc);
static void luaT_getvarargs (lua_State *L, struct CallInfo *ci, StkId where,
                                              int wanted, int vatab);
static void __attribute__((noreturn)) luaM_toobig (lua_State *L);
static void *luaM_realloc_ (lua_State *L, void *block, size_t oldsize,
                                                          size_t size);
static void *luaM_saferealloc_ (lua_State *L, void *block, size_t oldsize,
                                                              size_t size);
static void luaM_free_ (lua_State *L, void *block, size_t osize);
static void *luaM_growaux_ (lua_State *L, void *block, int nelems,
                               int *size, unsigned size_elem, int limit,
                               const char *what);
static void *luaM_shrinkvector_ (lua_State *L, void *block, int *nelem,
                                    int final_n, unsigned size_elem);
static void *luaM_malloc_ (lua_State *L, size_t size, int tag);
typedef struct Zio ZIO;
typedef struct Mbuffer {
  char *buffer;
  size_t n;
  size_t buffsize;
} Mbuffer;
static void luaZ_init (lua_State *L, ZIO *z, lua_Reader reader,
                                        void *data);
static size_t luaZ_read (ZIO* z, void *b, size_t n);
static const void *luaZ_getaddr (ZIO* z, size_t n);
struct Zio {
  size_t n;
  const char *p;
  lua_Reader reader;
  void *data;
  lua_State *L;
};
static int luaZ_fill (ZIO *z);
struct lua_longjmp;
typedef struct stringtable {
  TString **hash;
  int nuse;
  int size;
} stringtable;
struct CallInfo {
  StkIdRel func;
  StkIdRel top;
  struct CallInfo *previous, *next;
  union {
    struct {
      const Instruction *savedpc;
      volatile sig_atomic_t trap;
      int nextraargs;
    } l;
    struct {
      lua_KFunction k;
      ptrdiff_t old_errfunc;
      lua_KContext ctx;
    } c;
  } u;
  union {
    int funcidx;
    int nyield;
    int nres;
  } u2;
  l_uint32 callstatus;
};
struct lua_State {
  struct GCObject *next; lu_byte tt; lu_byte marked;
  lu_byte allowhook;
  TStatus status;
  StkIdRel top;
  struct global_State *l_G;
  CallInfo *ci;
  StkIdRel stack_last;
  StkIdRel stack;
  UpVal *openupval;
  StkIdRel tbclist;
  GCObject *gclist;
  struct lua_State *twups;
  struct lua_longjmp *errorJmp;
  CallInfo base_ci;
  volatile lua_Hook hook;
  ptrdiff_t errfunc;
  l_uint32 nCcalls;
  int oldpc;
  int nci;
  int basehookcount;
  int hookcount;
  volatile sig_atomic_t hookmask;
  struct {
    int ftransfer;
    int ntransfer;
  } transferinfo;
};
typedef struct LX {
  lu_byte extra_[(sizeof(void *))];
  lua_State l;
} LX;
typedef struct global_State {
  lua_Alloc frealloc;
  void *ud;
  l_mem GCtotalbytes;
  l_mem GCdebt;
  l_mem GCmarked;
  l_mem GCmajorminor;
  stringtable strt;
  TValue l_registry;
  TValue nilvalue;
  unsigned int seed;
  lu_byte gcparams[6];
  lu_byte currentwhite;
  lu_byte gcstate;
  lu_byte gckind;
  lu_byte gcstopem;
  lu_byte gcstp;
  lu_byte gcemergency;
  GCObject *allgc;
  GCObject **sweepgc;
  GCObject *finobj;
  GCObject *gray;
  GCObject *grayagain;
  GCObject *weak;
  GCObject *ephemeron;
  GCObject *allweak;
  GCObject *tobefnz;
  GCObject *fixedgc;
  GCObject *survival;
  GCObject *old1;
  GCObject *reallyold;
  GCObject *firstold1;
  GCObject *finobjsur;
  GCObject *finobjold1;
  GCObject *finobjrold;
  struct lua_State *twups;
  lua_CFunction panic;
  TString *memerrmsg;
  TString *tmname[TM_N];
  struct Table *mt[9];
  TString *strcache[53][2];
  lua_WarnFunction warnf;
  void *ud_warn;
  LX mainth;
} global_State;
union GCUnion {
  GCObject gc;
  struct TString ts;
  struct Udata u;
  union Closure cl;
  struct Table h;
  struct Proto p;
  struct lua_State th;
  struct UpVal upv;
};
static void luaE_setdebt (global_State *g, l_mem debt);
static void luaE_freethread (lua_State *L, lua_State *L1);
static lu_mem luaE_threadsize (lua_State *L);
static CallInfo *luaE_extendCI (lua_State *L, int err);
static void luaE_shrinkCI (lua_State *L);
static void luaE_checkcstack (lua_State *L);
static void luaE_incCstack (lua_State *L);
static void luaE_warning (lua_State *L, const char *msg, int tocont);
static void luaE_warnerror (lua_State *L, const char *where);
static TStatus luaE_resetthread (lua_State *L, TStatus status);
int luaZ_fill (ZIO *z) {
  size_t size;
  lua_State *L = z->L;
  const char *buff;
  ((void) 0);
  buff = z->reader(L, z->data, &size);
  ((void) 0);
  if (buff == ((void *)0) || size == 0)
    return (-1);
  z->n = size - 1;
  z->p = buff;
  return ((unsigned char)((*(z->p++))));
}
void luaZ_init (lua_State *L, ZIO *z, lua_Reader reader, void *data) {
  z->L = L;
  z->reader = reader;
  z->data = data;
  z->n = 0;
  z->p = ((void *)0);
}
static int checkbuffer (ZIO *z) {
  if (z->n == 0) {
    if (luaZ_fill(z) == (-1))
      return 0;
    else {
      z->n++;
      z->p--;
    }
  }
  return 1;
}
size_t luaZ_read (ZIO *z, void *b, size_t n) {
  while (n) {
    size_t m;
    if (!checkbuffer(z))
      return n;
    m = (n <= z->n) ? n : z->n;
    memcpy(b, z->p, m);
    z->n -= m;
    z->p += m;
    b = (char *)b + m;
    n -= m;
  }
  return 0;
}
const void *luaZ_getaddr (ZIO* z, size_t n) {
  const void *res;
  if (!checkbuffer(z))
    return ((void *)0);
  if (z->n < n)
    return ((void *)0);
  res = z->p;
  z->n -= n;
  z->p += n;
  return res;
}

static const lu_byte luai_ctype_[(0x7f * 2 + 1) + 2] = {
  0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
  0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
  0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16,
  0x16, 0x16, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
  0x04, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x05,
  0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
  0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
  0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x05,
  0x04, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x05,
  0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
  0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
  0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
enum OpMode {iABC, ivABC, iABx, iAsBx, iAx, isJ};
typedef enum {
OP_MOVE,
OP_LOADI,
OP_LOADF,
OP_LOADK,
OP_LOADKX,
OP_LOADFALSE,
OP_LFALSESKIP,
OP_LOADTRUE,
OP_LOADNIL,
OP_GETUPVAL,
OP_SETUPVAL,
OP_GETTABUP,
OP_GETTABLE,
OP_GETI,
OP_GETFIELD,
OP_SETTABUP,
OP_SETTABLE,
OP_SETI,
OP_SETFIELD,
OP_NEWTABLE,
OP_SELF,
OP_ADDI,
OP_ADDK,
OP_SUBK,
OP_MULK,
OP_MODK,
OP_POWK,
OP_DIVK,
OP_IDIVK,
OP_BANDK,
OP_BORK,
OP_BXORK,
OP_SHLI,
OP_SHRI,
OP_ADD,
OP_SUB,
OP_MUL,
OP_MOD,
OP_POW,
OP_DIV,
OP_IDIV,
OP_BAND,
OP_BOR,
OP_BXOR,
OP_SHL,
OP_SHR,
OP_MMBIN,
OP_MMBINI,
OP_MMBINK,
OP_UNM,
OP_BNOT,
OP_NOT,
OP_LEN,
OP_CONCAT,
OP_CLOSE,
OP_TBC,
OP_JMP,
OP_EQ,
OP_LT,
OP_LE,
OP_EQK,
OP_EQI,
OP_LTI,
OP_LEI,
OP_GTI,
OP_GEI,
OP_TEST,
OP_TESTSET,
OP_CALL,
OP_TAILCALL,
OP_RETURN,
OP_RETURN0,
OP_RETURN1,
OP_FORLOOP,
OP_FORPREP,
OP_TFORPREP,
OP_TFORCALL,
OP_TFORLOOP,
OP_SETLIST,
OP_CLOSURE,
OP_VARARG,
OP_GETVARG,
OP_ERRNNIL,
OP_VARARGPREP,
OP_EXTRAARG
} OpCode;

static int luaP_isOT (Instruction i);
static int luaP_isIT (Instruction i);
static const lu_byte luaP_opmodes[((int)(OP_EXTRAARG) + 1)] = {
  (((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iAsBx))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iAsBx))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABx))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABx))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (ivABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((1) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((1) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((1) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (isJ))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((1) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((1) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((1) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((1) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((1) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((1) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((1) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((1) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((1) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((1) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((1) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((1) << 6) | ((1) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((1) << 6) | ((1) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((1) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABx))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABx))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABx))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABx))
 ,(((0) << 7) | ((0) << 6) | ((1) << 5) | ((0) << 4) | ((0) << 3) | (ivABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABx))
 ,(((0) << 7) | ((1) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((1) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABx))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iABC))
 ,(((0) << 7) | ((0) << 6) | ((0) << 5) | ((0) << 4) | ((0) << 3) | (iAx))
};
int luaP_isOT (Instruction i) {
  OpCode op = (((OpCode)(((i)>>0) & ((~((~(Instruction)0)<<(7)))<<(0)))));
  switch (op) {
    case OP_TAILCALL: return 1;
    default:
      return (luaP_opmodes[op] & (1 << 6)) && (((void)0), ((((int)((((i)>>(((((0 + 7) + 8) + 1) + 8))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))) == 0;
  }
}
int luaP_isIT (Instruction i) {
  OpCode op = (((OpCode)(((i)>>0) & ((~((~(Instruction)0)<<(7)))<<(0)))));
  switch (op) {
    case OP_SETLIST:
      return (luaP_opmodes[(((OpCode)(((i)>>0) & ((~((~(Instruction)0)<<(7)))<<(0)))))] & (1 << 5)) && (((void)0), ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(6)))<<(0)))))))) == 0;
    default:
      return (luaP_opmodes[(((OpCode)(((i)>>0) & ((~((~(Instruction)0)<<(7)))<<(0)))))] & (1 << 5)) && (((void)0), ((((int)((((i)>>((((0 + 7) + 8) + 1))) & ((~((~(Instruction)0)<<(8)))<<(0)))))))) == 0;
  }
}
static int luaG_getfuncline (const Proto *f, int pc);
static const char *luaG_findlocal (lua_State *L, CallInfo *ci, int n,
                                                    StkId *pos);
static void __attribute__((noreturn)) luaG_typeerror (lua_State *L, const TValue *o,
                                                const char *opname);
static void __attribute__((noreturn)) luaG_callerror (lua_State *L, const TValue *o);
static void __attribute__((noreturn)) luaG_forerror (lua_State *L, const TValue *o,
                                               const char *what);
static void __attribute__((noreturn)) luaG_concaterror (lua_State *L, const TValue *p1,
                                                  const TValue *p2);
static void __attribute__((noreturn)) luaG_opinterror (lua_State *L, const TValue *p1,
                                                 const TValue *p2,
                                                 const char *msg);
static void __attribute__((noreturn)) luaG_tointerror (lua_State *L, const TValue *p1,
                                                 const TValue *p2);
static void __attribute__((noreturn)) luaG_ordererror (lua_State *L, const TValue *p1,
                                                 const TValue *p2);
static void __attribute__((noreturn)) luaG_errnnil (lua_State *L, LClosure *cl, int k);
static void __attribute__((noreturn)) luaG_runerror (lua_State *L, const char *fmt, ...);
static const char *luaG_addinfo (lua_State *L, const char *msg,
                                                  TString *src, int line);
static void __attribute__((noreturn)) luaG_errormsg (lua_State *L);
static int luaG_traceexec (lua_State *L, const Instruction *pc);
static int luaG_tracecall (lua_State *L);
typedef void (*Pfunc) (lua_State *L, void *ud);
static void __attribute__((noreturn)) luaD_errerr (lua_State *L);
static void luaD_seterrorobj (lua_State *L, TStatus errcode, StkId oldtop);
static TStatus luaD_protectedparser (lua_State *L, ZIO *z,
                                                  const char *name,
                                                  const char *mode);
static void luaD_hook (lua_State *L, int event, int line,
                                        int fTransfer, int nTransfer);
static void luaD_hookcall (lua_State *L, CallInfo *ci);
static int luaD_pretailcall (lua_State *L, CallInfo *ci, StkId func,
                                              int narg1, int delta);
static CallInfo *luaD_precall (lua_State *L, StkId func, int nResults);
static void luaD_call (lua_State *L, StkId func, int nResults);
static void luaD_callnoyield (lua_State *L, StkId func, int nResults);
static TStatus luaD_closeprotected (lua_State *L, ptrdiff_t level,
                                                     TStatus status);
static TStatus luaD_pcall (lua_State *L, Pfunc func, void *u,
                                        ptrdiff_t oldtop, ptrdiff_t ef);
static void luaD_poscall (lua_State *L, CallInfo *ci, int nres);
static int luaD_reallocstack (lua_State *L, int newsize, int raiseerror);
static int luaD_growstack (lua_State *L, int n, int raiseerror);
static void luaD_shrinkstack (lua_State *L);
static void luaD_inctop (lua_State *L);
static int luaD_checkminstack (lua_State *L);
static void luaD_anchorobj (lua_State *L, Table *anchor, GCObject *obj);
static void __attribute__((noreturn)) luaD_throw (lua_State *L, TStatus errcode);
static void __attribute__((noreturn)) luaD_throwbaselevel (lua_State *L, TStatus errcode);
static TStatus luaD_rawrunprotected (lua_State *L, Pfunc f, void *ud);
static void luaC_fix (lua_State *L, GCObject *o);
static void luaC_freeallobjects (lua_State *L);
static void luaC_step (lua_State *L);
static void luaC_runtilstate (lua_State *L, int state, int fast);
static void luaC_fullgc (lua_State *L, int isemergency);
static GCObject *luaC_newobj (lua_State *L, lu_byte tt, size_t sz);
static GCObject *luaC_newobjdt (lua_State *L, lu_byte tt, size_t sz,
                                                 size_t offset);
static void luaC_barrier_ (lua_State *L, GCObject *o, GCObject *v);
static void luaC_barrierback_ (lua_State *L, GCObject *o);
static void luaC_checkfinalizer (lua_State *L, GCObject *o, Table *mt);
static void luaC_changemode (lua_State *L, int newmode);
void *luaM_growaux_ (lua_State *L, void *block, int nelems, int *psize,
                     unsigned size_elems, int limit, const char *what) {
  void *newblock;
  int size = *psize;
  if (nelems + 1 <= size)
    return block;
  if (size >= limit / 2) {
    if ((__builtin_expect(((size >= limit) != 0), 0)))
      luaG_runerror(L, "too many %s (limit is %d)", what, limit);
    size = limit;
  }
  else {
    size *= 2;
    if (size < 4)
      size = 4;
  }
  ((void)0);
  newblock = luaM_saferealloc_(L, block, ((size_t)((*psize))) * size_elems,
                                         ((size_t)((size))) * size_elems);
  *psize = size;
  return newblock;
}
void *luaM_shrinkvector_ (lua_State *L, void *block, int *size,
                          int final_n, unsigned size_elem) {
  void *newblock;
  size_t oldsize = ((size_t)((*size))) * size_elem;
  size_t newsize = ((size_t)((final_n))) * size_elem;
  ((void)0);
  newblock = luaM_saferealloc_(L, block, oldsize, newsize);
  *size = final_n;
  return newblock;
}
void __attribute__((noreturn)) luaM_toobig (lua_State *L) {
  luaG_runerror(L, "memory allocation error: block too big");
}
void luaM_free_ (lua_State *L, void *block, size_t osize) {
  global_State *g = (L->l_G);
  ((void)0);
  ((*g->frealloc)(g->ud, block, osize, 0));
  g->GCdebt += ((l_mem)(osize));
}
static void *tryagain (lua_State *L, void *block,
                       size_t osize, size_t nsize) {
  global_State *g = (L->l_G);
  if (((((((((&g->nilvalue))->tt_)) & 0x0F)) == (0)) && !g->gcstopem)) {
    luaC_fullgc(L, 1);
    return ((*g->frealloc)(g->ud, block, osize, nsize));
  }
  else return ((void *)0);
}
void *luaM_realloc_ (lua_State *L, void *block, size_t osize, size_t nsize) {
  void *newblock;
  global_State *g = (L->l_G);
  ((void)0);
  newblock = ((*g->frealloc)(g->ud, block, osize, nsize));
  if ((__builtin_expect(((newblock == ((void *)0) && nsize > 0) != 0), 0))) {
    newblock = tryagain(L, block, osize, nsize);
    if (newblock == ((void *)0))
      return ((void *)0);
  }
  ((void)0);
  g->GCdebt -= ((l_mem)(nsize)) - ((l_mem)(osize));
  return newblock;
}
void *luaM_saferealloc_ (lua_State *L, void *block, size_t osize,
                                                    size_t nsize) {
  void *newblock = luaM_realloc_(L, block, osize, nsize);
  if ((__builtin_expect(((newblock == ((void *)0) && nsize > 0) != 0), 0)))
    luaD_throw(L, 4);
  return newblock;
}
void *luaM_malloc_ (lua_State *L, size_t size, int tag) {
  if (size == 0)
    return ((void *)0);
  else {
    global_State *g = (L->l_G);
    void *newblock = ((*g->frealloc)(g->ud, ((void *)0), ((size_t)((tag))), size));
    if ((__builtin_expect(((newblock == ((void *)0)) != 0), 0))) {
      newblock = tryagain(L, ((void *)0), ((size_t)((tag))), size);
      if (newblock == ((void *)0))
        luaD_throw(L, 4);
    }
    g->GCdebt -= ((l_mem)(size));
    return newblock;
  }
}
static Proto *luaF_newproto (lua_State *L);
static CClosure *luaF_newCclosure (lua_State *L, int nupvals);
static LClosure *luaF_newLclosure (lua_State *L, int nupvals);
static void luaF_initupvals (lua_State *L, LClosure *cl);
static UpVal *luaF_findupval (lua_State *L, StkId level);
static void luaF_newtbcupval (lua_State *L, StkId level);
static void luaF_closeupval (lua_State *L, StkId level);
static StkId luaF_close (lua_State *L, StkId level, TStatus status, int yy);
static void luaF_unlinkupval (UpVal *uv);
static lu_mem luaF_protosize (Proto *p);
static void luaF_freeproto (lua_State *L, Proto *f);
static const char *luaF_getlocalname (const Proto *func, int local_number,
                                         int pc);
static unsigned luaS_hashlongstr (TString *ts);
static int luaS_eqstr (TString *a, TString *b);
static void luaS_resize (lua_State *L, int newsize);
static void luaS_clearcache (global_State *g);
static void luaS_init (lua_State *L);
static void luaS_remove (lua_State *L, TString *ts);
static Udata *luaS_newudata (lua_State *L, size_t s,
                                              unsigned short nuvalue);
static TString *luaS_newlstr (lua_State *L, const char *str, size_t l);
static TString *luaS_new (lua_State *L, const char *str);
static TString *luaS_createlngstrobj (lua_State *L, size_t l);
static TString *luaS_newextlstr (lua_State *L,
  const char *s, size_t len, lua_Alloc falloc, void *ud);
static size_t luaS_sizelngstr (size_t len, int kind);
static TString *luaS_normstr (lua_State *L, TString *ts);
static lu_byte luaH_get (Table *t, const TValue *key, TValue *res);
static lu_byte luaH_getshortstr (Table *t, TString *key, TValue *res);
static lu_byte luaH_getstr (Table *t, TString *key, TValue *res);
static lu_byte luaH_getint (Table *t, lua_Integer key, TValue *res);
static const TValue *luaH_Hgetshortstr (Table *t, TString *key);
static int luaH_psetint (Table *t, lua_Integer key, TValue *val);
static int luaH_psetshortstr (Table *t, TString *key, TValue *val);
static int luaH_psetstr (Table *t, TString *key, TValue *val);
static int luaH_pset (Table *t, const TValue *key, TValue *val);
static void luaH_setint (lua_State *L, Table *t, lua_Integer key,
                                                    TValue *value);
static void luaH_set (lua_State *L, Table *t, const TValue *key,
                                                 TValue *value);
static void luaH_finishset (lua_State *L, Table *t, const TValue *key,
                                              TValue *value, int hres);
static Table *luaH_new (lua_State *L);
static void luaH_resize (lua_State *L, Table *t, unsigned nasize,
                                                    unsigned nhsize);
static void luaH_resizearray (lua_State *L, Table *t, unsigned nasize);
static lu_mem luaH_size (Table *t);
static void luaH_free (lua_State *L, Table *t);
static int luaH_next (lua_State *L, Table *t, StkId key);
static lua_Unsigned luaH_getn (lua_State *L, Table *t);
static LClosure* luaU_undump (lua_State* L, ZIO* Z, Table *anchor,
                                 const char* name, int fixed);
static int luaU_dump (lua_State* L, const Proto* f, lua_Writer w,
                         void* data, int strip);
typedef struct {
  lua_State *L;
  ZIO *Z;
  const char *name;
  Table *h;
  size_t offset;
  lua_Unsigned nstr;
  lu_byte fixed;
} LoadState;
static void __attribute__((noreturn)) error (LoadState *S, const char *why) {
  luaO_pushfstring(S->L, "%s: bad binary format (%s)", S->name, why);
  luaD_throw(S->L, 3);
}
static void loadBlock (LoadState *S, void *b, size_t size) {
  if (luaZ_read(S->Z, b, size) != 0)
    error(S, "truncated chunk");
  S->offset += size;
}
static void loadAlign (LoadState *S, unsigned align) {
  unsigned padding = align - ((unsigned int)((S->offset % align)));
  if (padding < align) {
    lua_Integer paddingContent;
    loadBlock(S, &paddingContent, padding);
    ((void)0);
  }
}
static const void *getaddr_ (LoadState *S, size_t size) {
  const void *block = luaZ_getaddr(S->Z, size);
  S->offset += size;
  if (block == ((void *)0))
    error(S, "truncated fixed buffer");
  return block;
}
static lu_byte loadByte (LoadState *S) {
  int b = (((S->Z)->n--)>0 ? ((unsigned char)((*(S->Z)->p++))) : luaZ_fill(S->Z));
  if (b == (-1))
    error(S, "truncated chunk");
  S->offset++;
  return ((lu_byte)((b)));
}
static lua_Unsigned loadVarint (LoadState *S, lua_Unsigned limit) {
  lua_Unsigned x = 0;
  int b;
  limit >>= 7;
  do {
    b = loadByte(S);
    if (x > limit)
      error(S, "integer overflow");
    x = (x << 7) | (b & 0x7f);
  } while ((b & 0x80) != 0);
  return x;
}
static size_t loadSize (LoadState *S) {
  return ((size_t)((loadVarint(S, (sizeof(size_t) < sizeof(lua_Integer) ? ((size_t)(~(size_t)0)) : ((size_t)((0x7fffffffffffffffLL))))))));
}
static int loadInt (LoadState *S) {
  return ((int)((loadVarint(S, ((size_t)((0x7fffffff)))))));
}
static lua_Number loadNumber (LoadState *S) {
  lua_Number x;
  loadBlock(S,&x,((size_t)((1)))*sizeof((&x)[0]));
  return x;
}
static lua_Integer loadInteger (LoadState *S) {
  lua_Unsigned cx = loadVarint(S, (0x7fffffffffffffffLL * 2ULL + 1ULL));
  if ((cx & 1) != 0)
    return ((lua_Integer)(~(cx >> 1)));
  else
    return ((lua_Integer)(cx >> 1));
}
static void loadString (LoadState *S, Proto *p, TString **sl) {
  lua_State *L = S->L;
  TString *ts;
  TValue sv;
  size_t size = loadSize(S);
  if (size == 0) {
    lua_Unsigned idx = loadVarint(S, (0x7fffffffffffffffLL * 2ULL + 1ULL));
    TValue stv;
    if (idx == 0) {
      ((void)0);
      return;
    }
    if (((luaH_getint(S->h, ((lua_Integer)(idx)), &stv)) & 0x0F) != 4)
      error(S, "invalid string index");
    *sl = ts = (((void)0), ((((void)0), (&((((union GCUnion *)((((&stv)->value_).gc))))->ts)))));
    ( ((((p)->marked) & ((1<<(5)))) && (((ts)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(((void)0), (&(((union GCUnion *)((p)))->gc))),(((void)0), (&(((union GCUnion *)((ts)))->gc)))) : ((void)((0))));
    return;
  }
  else if ((size -= 1) <= 40) {
    char buff[40 + 1];
    loadBlock(S,buff,((size_t)((size + 1)))*sizeof((buff)[0]));
    *sl = ts = luaS_newlstr(L, buff, size);
    ( ((((p)->marked) & ((1<<(5)))) && (((ts)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(((void)0), (&(((union GCUnion *)((p)))->gc))),(((void)0), (&(((union GCUnion *)((ts)))->gc)))) : ((void)((0))));
  }
  else if (S->fixed) {
    const char *s = ((char *)(getaddr_(S,((size_t)((size + 1))) * sizeof(char))));
    *sl = ts = luaS_newextlstr(L, s, size, ((void *)0), ((void *)0));
    ( ((((p)->marked) & ((1<<(5)))) && (((ts)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(((void)0), (&(((union GCUnion *)((p)))->gc))),(((void)0), (&(((union GCUnion *)((ts)))->gc)))) : ((void)((0))));
  }
  else {
    *sl = ts = luaS_createlngstrobj(L, size);
    ( ((((p)->marked) & ((1<<(5)))) && (((ts)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(((void)0), (&(((union GCUnion *)((p)))->gc))),(((void)0), (&(((union GCUnion *)((ts)))->gc)))) : ((void)((0))));
    loadBlock(S,(((void)0), ((ts)->contents)),((size_t)((size + 1)))*sizeof(((((void)0), ((ts)->contents)))[0]));
  }
  S->nstr++;
  { TValue *io = (&sv); TString *x_ = (ts); ((io)->value_).gc = (((void)0), (&(((union GCUnion *)((x_)))->gc))); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)L, ((void)0)); };
  luaH_setint(L, S->h, ((lua_Integer)(S->nstr)), &sv);
  ( (((((((void)0), (&(((union GCUnion *)((S->h)))->gc))))->marked) & ((1<<(5)))) && (((ts)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrierback_(L,(((void)0), (&(((union GCUnion *)((S->h)))->gc)))) : ((void)((0))));
}
static void loadCode (LoadState *S, Proto *f) {
  int n = loadInt(S);
  loadAlign(S, sizeof(f->code[0]));
  if (S->fixed) {
    f->code = ((Instruction *)(getaddr_(S,((size_t)((n))) * sizeof(Instruction))));
    f->sizecode = n;
  }
  else {
    f->code = (((sizeof(n) >= sizeof(size_t) && ((size_t)(((n)))) + 1 > ((size_t)(~(size_t)0))/(sizeof(Instruction))) ? luaM_toobig(S->L) : ((void)((0)))), ((Instruction*)(luaM_malloc_(S->L, ((size_t)((n)))*sizeof(Instruction), 0))));
    f->sizecode = n;
    loadBlock(S,f->code,((size_t)((n)))*sizeof((f->code)[0]));
  }
}
static void loadFunction(LoadState *S, Proto *f);
static void loadConstants (LoadState *S, Proto *f) {
  int i;
  int n = loadInt(S);
  f->k = (((sizeof(n) >= sizeof(size_t) && ((size_t)(((n)))) + 1 > ((size_t)(~(size_t)0))/(sizeof(TValue))) ? luaM_toobig(S->L) : ((void)((0)))), ((TValue*)(luaM_malloc_(S->L, ((size_t)((n)))*sizeof(TValue), 0))));
  f->sizek = n;
  for (i = 0; i < n; i++)
    ((&f->k[i])->tt_=(((0) | ((0) << 4))));
  for (i = 0; i < n; i++) {
    TValue *o = &f->k[i];
    int t = loadByte(S);
    switch (t) {
      case ((0) | ((0) << 4)):
        ((o)->tt_=(((0) | ((0) << 4))));
        break;
      case ((1) | ((0) << 4)):
        ((o)->tt_=(((1) | ((0) << 4))));
        break;
      case ((1) | ((1) << 4)):
        ((o)->tt_=(((1) | ((1) << 4))));
        break;
      case ((3) | ((1) << 4)):
        { TValue *io=(o); ((io)->value_).n=(loadNumber(S)); ((io)->tt_=(((3) | ((1) << 4)))); };
        break;
      case ((3) | ((0) << 4)):
        { TValue *io=(o); ((io)->value_).i=(loadInteger(S)); ((io)->tt_=(((3) | ((0) << 4)))); };
        break;
      case ((4) | ((0) << 4)):
      case ((4) | ((1) << 4)): {
        ((void)0);
        loadString(S, f, &f->source);
        if (f->source == ((void *)0))
          error(S, "bad format for constant string");
        { TValue *io = (o); TString *x_ = (f->source); ((io)->value_).gc = (((void)0), (&(((union GCUnion *)((x_)))->gc))); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)S->L, ((void)0)); };
        f->source = ((void *)0);
        break;
      }
      default: error(S, "invalid constant");
    }
  }
}
static void loadProtos (LoadState *S, Proto *f) {
  int i;
  int n = loadInt(S);
  f->p = (((sizeof(n) >= sizeof(size_t) && ((size_t)(((n)))) + 1 > ((size_t)(~(size_t)0))/(sizeof(Proto *))) ? luaM_toobig(S->L) : ((void)((0)))), ((Proto **)(luaM_malloc_(S->L, ((size_t)((n)))*sizeof(Proto *), 0))));
  f->sizep = n;
  for (i = 0; i < n; i++)
    f->p[i] = ((void *)0);
  for (i = 0; i < n; i++) {
    f->p[i] = luaF_newproto(S->L);
    ( ((((f)->marked) & ((1<<(5)))) && (((f->p[i])->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(S->L,(((void)0), (&(((union GCUnion *)((f)))->gc))),(((void)0), (&(((union GCUnion *)((f->p[i])))->gc)))) : ((void)((0))));
    loadFunction(S, f->p[i]);
  }
}
static void loadUpvalues (LoadState *S, Proto *f) {
  int i;
  int n = loadInt(S);
  f->upvalues = (((sizeof(n) >= sizeof(size_t) && ((size_t)(((n)))) + 1 > ((size_t)(~(size_t)0))/(sizeof(Upvaldesc))) ? luaM_toobig(S->L) : ((void)((0)))), ((Upvaldesc*)(luaM_malloc_(S->L, ((size_t)((n)))*sizeof(Upvaldesc), 0))));
  f->sizeupvalues = n;
  for (i = 0; i < n; i++)
    f->upvalues[i].name = ((void *)0);
  for (i = 0; i < n; i++) {
    f->upvalues[i].instack = loadByte(S);
    f->upvalues[i].idx = loadByte(S);
    f->upvalues[i].kind = loadByte(S);
  }
}
static void loadDebug (LoadState *S, Proto *f) {
  int i;
  int n = loadInt(S);
  if (S->fixed) {
    f->lineinfo = ((ls_byte *)(getaddr_(S,((size_t)((n))) * sizeof(ls_byte))));
    f->sizelineinfo = n;
  }
  else {
    f->lineinfo = (((sizeof(n) >= sizeof(size_t) && ((size_t)(((n)))) + 1 > ((size_t)(~(size_t)0))/(sizeof(ls_byte))) ? luaM_toobig(S->L) : ((void)((0)))), ((ls_byte*)(luaM_malloc_(S->L, ((size_t)((n)))*sizeof(ls_byte), 0))));
    f->sizelineinfo = n;
    loadBlock(S,f->lineinfo,((size_t)((n)))*sizeof((f->lineinfo)[0]));
  }
  n = loadInt(S);
  if (n > 0) {
    loadAlign(S, sizeof(int));
    if (S->fixed) {
      f->abslineinfo = ((AbsLineInfo *)(getaddr_(S,((size_t)((n))) * sizeof(AbsLineInfo))));
      f->sizeabslineinfo = n;
    }
    else {
      f->abslineinfo = (((sizeof(n) >= sizeof(size_t) && ((size_t)(((n)))) + 1 > ((size_t)(~(size_t)0))/(sizeof(AbsLineInfo))) ? luaM_toobig(S->L) : ((void)((0)))), ((AbsLineInfo*)(luaM_malloc_(S->L, ((size_t)((n)))*sizeof(AbsLineInfo), 0))));
      f->sizeabslineinfo = n;
      loadBlock(S,f->abslineinfo,((size_t)((n)))*sizeof((f->abslineinfo)[0]));
    }
  }
  n = loadInt(S);
  f->locvars = (((sizeof(n) >= sizeof(size_t) && ((size_t)(((n)))) + 1 > ((size_t)(~(size_t)0))/(sizeof(LocVar))) ? luaM_toobig(S->L) : ((void)((0)))), ((LocVar*)(luaM_malloc_(S->L, ((size_t)((n)))*sizeof(LocVar), 0))));
  f->sizelocvars = n;
  for (i = 0; i < n; i++)
    f->locvars[i].varname = ((void *)0);
  for (i = 0; i < n; i++) {
    loadString(S, f, &f->locvars[i].varname);
    f->locvars[i].startpc = loadInt(S);
    f->locvars[i].endpc = loadInt(S);
  }
  n = loadInt(S);
  if (n != 0)
    n = f->sizeupvalues;
  for (i = 0; i < n; i++)
    loadString(S, f, &f->upvalues[i].name);
}
static void loadFunction (LoadState *S, Proto *f) {
  f->linedefined = loadInt(S);
  f->lastlinedefined = loadInt(S);
  f->numparams = loadByte(S);
  f->flag = ((lu_byte)((loadByte(S) & ~4)));
  if (S->fixed)
    f->flag |= 4;
  f->maxstacksize = loadByte(S);
  loadCode(S, f);
  loadConstants(S, f);
  loadUpvalues(S, f);
  loadProtos(S, f);
  loadString(S, f, &f->source);
  loadDebug(S, f);
}
static void checkliteral (LoadState *S, const char *s, const char *msg) {
  char buff[sizeof("\x1bLua") + sizeof("\x19\x93\r\n\x1a\n")];
  size_t len = strlen(s);
  loadBlock(S,buff,((size_t)((len)))*sizeof((buff)[0]));
  if (memcmp(s, buff, len) != 0)
    error(S, msg);
}
static void __attribute__((noreturn)) numerror (LoadState *S, const char *what, const char *tname) {
  const char *msg = luaO_pushfstring(S->L, "%s %s mismatch", tname, what);
  error(S, msg);
}
static void checknumsize (LoadState *S, int size, const char *tname) {
  if (size != loadByte(S))
    numerror(S, "size", tname);
}
static void checknumformat (LoadState *S, int eq, const char *tname) {
  if (!eq)
    numerror(S, "format", tname);
}
static void checkHeader (LoadState *S) {
  checkliteral(S, &"\x1bLua"[1], "not a binary chunk");
  if (loadByte(S) != (5*16+5))
    error(S, "version mismatch");
  if (loadByte(S) != 0)
    error(S, "format mismatch");
  checkliteral(S, "\x19\x93\r\n\x1a\n", "corrupted chunk");
  { int i; checknumsize(S, sizeof(i), "int"); loadBlock(S,&i,((size_t)((1)))*sizeof((&i)[0])); checknumformat(S, i == -0x5678, "int"); };
  { Instruction i; checknumsize(S, sizeof(i), "instruction"); loadBlock(S,&i,((size_t)((1)))*sizeof((&i)[0])); checknumformat(S, i == 0x12345678, "instruction"); };
  { lua_Integer i; checknumsize(S, sizeof(i), "Lua integer"); loadBlock(S,&i,((size_t)((1)))*sizeof((&i)[0])); checknumformat(S, i == -0x5678, "Lua integer"); };
  { lua_Number i; checknumsize(S, sizeof(i), "Lua number"); loadBlock(S,&i,((size_t)((1)))*sizeof((&i)[0])); checknumformat(S, i == ((lua_Number)((-370.5))), "Lua number"); };
}
LClosure *luaU_undump (lua_State *L, ZIO *Z, Table *anchor, const char *name,
                       int fixed) {
  LoadState S;
  LClosure *cl;
  if (*name == '@' || *name == '=')
    name = name + 1;
  else if (*name == "\x1bLua"[0])
    name = "binary string";
  S.name = name;
  S.L = L;
  S.Z = Z;
  S.fixed = ((lu_byte)((fixed)));
  S.offset = 1;
  checkHeader(&S);
  S.h = anchor;
  S.nstr = 0;
  cl = luaF_newLclosure(L, loadByte(&S));
  luaD_anchorobj(L, anchor, (((void)0), (&(((union GCUnion *)((cl)))->gc))));
  cl->p = luaF_newproto(L);
  ( ((((cl)->marked) & ((1<<(5)))) && (((cl->p)->marked) & (((1<<(3)) | (1<<(4)))))) ? luaC_barrier_(L,(((void)0), (&(((union GCUnion *)((cl)))->gc))),(((void)0), (&(((union GCUnion *)((cl->p)))->gc)))) : ((void)((0))));
  loadFunction(&S, cl->p);
  if (cl->nupvalues != cl->p->sizeupvalues)
    error(&S, "corrupted chunk");
  ;
  return cl;
}
typedef struct {
  lua_State *L;
  lua_Writer writer;
  void *data;
  size_t offset;
  int strip;
  int status;
  Table *h;
  lua_Unsigned nstr;
} DumpState;
static void dumpBlock (DumpState *D, const void *b, size_t size) {
  if (D->status == 0) {
    ((void) 0);
    D->status = (*D->writer)(D->L, b, size, D->data);
    ((void) 0);
    D->offset += size;
  }
}
static void dumpAlign (DumpState *D, unsigned align) {
  unsigned padding = align - ((unsigned int)((D->offset % align)));
  if (padding < align) {
    static lua_Integer paddingContent = 0;
    ((void)0);
    dumpBlock(D, &paddingContent, padding);
  }
  ((void)0);
}
static void dumpByte (DumpState *D, int y) {
  lu_byte x = (lu_byte)y;
  dumpBlock(D,&x,(1)*sizeof((&x)[0]));
}
static void dumpVarint (DumpState *D, lua_Unsigned x) {
  lu_byte buff[((((int)((sizeof(lua_Unsigned) * 8))) + 6) / 7)];
  unsigned n = 1;
  buff[((((int)((sizeof(lua_Unsigned) * 8))) + 6) / 7) - 1] = x & 0x7f;
  while ((x >>= 7) != 0)
    buff[((((int)((sizeof(lua_Unsigned) * 8))) + 6) / 7) - (++n)] = ((lu_byte)(((x & 0x7f) | 0x80)));
  dumpBlock(D,buff + ((((int)((sizeof(lua_Unsigned) * 8))) + 6) / 7) - n,(n)*sizeof((buff + ((((int)((sizeof(lua_Unsigned) * 8))) + 6) / 7) - n)[0]));
}
static void dumpSize (DumpState *D, size_t sz) {
  dumpVarint(D, ((lua_Unsigned)(sz)));
}
static void dumpInt (DumpState *D, int x) {
  ((void)0);
  dumpVarint(D, ((unsigned int)((x))));
}
static void dumpNumber (DumpState *D, lua_Number x) {
  dumpBlock(D,&x,(1)*sizeof((&x)[0]));
}
static void dumpInteger (DumpState *D, lua_Integer x) {
  lua_Unsigned cx = (x >= 0) ? 2u * ((lua_Unsigned)(x))
                             : (2u * ~((lua_Unsigned)(x))) + 1;
  dumpVarint(D, cx);
}
static void dumpString (DumpState *D, TString *ts) {
  if (ts == ((void *)0)) {
    dumpVarint(D, 0);
    dumpVarint(D, 0);
  }
  else {
    TValue idx;
    int tag = luaH_getstr(D->h, ts, &idx);
    if (!(((tag) & 0x0F) == 0)) {
      dumpVarint(D, 0);
      dumpVarint(D, ((lua_Unsigned)((((void)0), (((&idx)->value_).i)))));
    }
    else {
      TValue key, value;
      size_t size;
      const char *s = (((ts)->shrlen >= 0) ? (((void)(((size) = ((size_t)(((ts)->shrlen)))))), (((char *)((&(ts)->contents))))) : (((void)(((size) = (ts)->u.lnglen))), (ts)->contents));
      dumpSize(D, size + 1);
      dumpBlock(D,s,(size + 1)*sizeof((s)[0]));
      D->nstr++;
      { TValue *io = (&key); TString *x_ = (ts); ((io)->value_).gc = (((void)0), (&(((union GCUnion *)((x_)))->gc))); ((io)->tt_=(((x_->tt) | (1 << 6)))); ((void)D->L, ((void)0)); };
      { TValue *io=(&value); ((io)->value_).i=(((lua_Integer)(D->nstr))); ((io)->tt_=(((3) | ((0) << 4)))); };
      luaH_set(D->L, D->h, &key, &value);
    }
  }
}
static void dumpCode (DumpState *D, const Proto *f) {
  dumpInt(D, f->sizecode);
  dumpAlign(D, sizeof(f->code[0]));
  ((void)0);
  dumpBlock(D,f->code,(((unsigned int)((f->sizecode))))*sizeof((f->code)[0]));
}
static void dumpFunction (DumpState *D, const Proto *f);
static void dumpConstants (DumpState *D, const Proto *f) {
  int i;
  int n = f->sizek;
  dumpInt(D, n);
  for (i = 0; i < n; i++) {
    const TValue *o = &f->k[i];
    int tt = ((((o)->tt_)) & 0x3F);
    dumpByte(D, tt);
    switch (tt) {
      case ((3) | ((1) << 4)):
        dumpNumber(D, (((void)0), (((o)->value_).n)));
        break;
      case ((3) | ((0) << 4)):
        dumpInteger(D, (((void)0), (((o)->value_).i)));
        break;
      case ((4) | ((0) << 4)):
      case ((4) | ((1) << 4)):
        dumpString(D, (((void)0), ((((void)0), (&((((union GCUnion *)((((o)->value_).gc))))->ts))))));
        break;
      default:
        ((void)0);
    }
  }
}
static void dumpProtos (DumpState *D, const Proto *f) {
  int i;
  int n = f->sizep;
  dumpInt(D, n);
  for (i = 0; i < n; i++)
    dumpFunction(D, f->p[i]);
}
static void dumpUpvalues (DumpState *D, const Proto *f) {
  int i, n = f->sizeupvalues;
  dumpInt(D, n);
  for (i = 0; i < n; i++) {
    dumpByte(D, f->upvalues[i].instack);
    dumpByte(D, f->upvalues[i].idx);
    dumpByte(D, f->upvalues[i].kind);
  }
}
static void dumpDebug (DumpState *D, const Proto *f) {
  int i, n;
  n = (D->strip) ? 0 : f->sizelineinfo;
  dumpInt(D, n);
  if (f->lineinfo != ((void *)0))
    dumpBlock(D,f->lineinfo,(((unsigned int)((n))))*sizeof((f->lineinfo)[0]));
  n = (D->strip) ? 0 : f->sizeabslineinfo;
  dumpInt(D, n);
  if (n > 0) {
    dumpAlign(D, sizeof(int));
    dumpBlock(D,f->abslineinfo,(((unsigned int)((n))))*sizeof((f->abslineinfo)[0]));
  }
  n = (D->strip) ? 0 : f->sizelocvars;
  dumpInt(D, n);
  for (i = 0; i < n; i++) {
    dumpString(D, f->locvars[i].varname);
    dumpInt(D, f->locvars[i].startpc);
    dumpInt(D, f->locvars[i].endpc);
  }
  n = (D->strip) ? 0 : f->sizeupvalues;
  dumpInt(D, n);
  for (i = 0; i < n; i++)
    dumpString(D, f->upvalues[i].name);
}
static void dumpFunction (DumpState *D, const Proto *f) {
  dumpInt(D, f->linedefined);
  dumpInt(D, f->lastlinedefined);
  dumpByte(D, f->numparams);
  dumpByte(D, f->flag);
  dumpByte(D, f->maxstacksize);
  dumpCode(D, f);
  dumpConstants(D, f);
  dumpUpvalues(D, f);
  dumpProtos(D, f);
  dumpString(D, D->strip ? ((void *)0) : f->source);
  dumpDebug(D, f);
}
static void dumpHeader (DumpState *D) {
  dumpBlock(D,"\x1bLua",sizeof("\x1bLua") - sizeof(char));
  dumpByte(D, (5*16+5));
  dumpByte(D, 0);
  dumpBlock(D,"\x19\x93\r\n\x1a\n",sizeof("\x19\x93\r\n\x1a\n") - sizeof(char));
  { int i = -0x5678; dumpByte(D, sizeof(int)); dumpBlock(D,&i,(1)*sizeof((&i)[0])); };
  { Instruction i = 0x12345678; dumpByte(D, sizeof(Instruction)); dumpBlock(D,&i,(1)*sizeof((&i)[0])); };
  { lua_Integer i = -0x5678; dumpByte(D, sizeof(lua_Integer)); dumpBlock(D,&i,(1)*sizeof((&i)[0])); };
  { lua_Number i = ((lua_Number)((-370.5))); dumpByte(D, sizeof(lua_Number)); dumpBlock(D,&i,(1)*sizeof((&i)[0])); };
}
int luaU_dump (lua_State *L, const Proto *f, lua_Writer w, void *data,
               int strip) {
  DumpState D;
  D.h = luaH_new(L);
  { TValue *io = ((&(L->top.p)->val)); Table *x_ = (D.h); ((io)->value_).gc = (((void)0), (&(((union GCUnion *)((x_)))->gc))); ((io)->tt_=(((((5) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
  L->top.p++;
  D.L = L;
  D.writer = w;
  D.offset = 0;
  D.data = data;
  D.strip = strip;
  D.status = 0;
  D.nstr = 0;
  dumpHeader(&D);
  dumpByte(&D, f->sizeupvalues);
  dumpFunction(&D, f);
  dumpBlock(&D, ((void *)0), 0);
  return D.status;
}
enum RESERVED {
  TK_AND = ((0x7f * 2 + 1) + 1), TK_BREAK,
  TK_DO, TK_ELSE, TK_ELSEIF, TK_END, TK_FALSE, TK_FOR, TK_FUNCTION,
  TK_GLOBAL, TK_GOTO, TK_IF, TK_IN, TK_LOCAL, TK_NIL, TK_NOT, TK_OR,
  TK_REPEAT, TK_RETURN, TK_THEN, TK_TRUE, TK_UNTIL, TK_WHILE,
  TK_IDIV, TK_CONCAT, TK_DOTS, TK_EQ, TK_GE, TK_LE, TK_NE,
  TK_SHL, TK_SHR,
  TK_DBCOLON, TK_EOS,
  TK_FLT, TK_INT, TK_NAME, TK_STRING
};
typedef union {
  lua_Number r;
  lua_Integer i;
  TString *ts;
} SemInfo;
typedef struct Token {
  int token;
  SemInfo seminfo;
} Token;
typedef struct LexState {
  int current;
  int linenumber;
  int lastline;
  Token t;
  Token lookahead;
  struct FuncState *fs;
  struct lua_State *L;
  ZIO *z;
  Mbuffer *buff;
  Table *h;
  struct Dyndata *dyd;
  TString *source;
  TString *envn;
  TString *brkn;
  TString *glbn;
} LexState;
static void luaX_init (lua_State *L);
static void luaX_setinput (lua_State *L, LexState *ls, ZIO *z,
                              TString *source, int firstchar);
static TString *luaX_newstring (LexState *ls, const char *str, size_t l);
static void luaX_next (LexState *ls);
static int luaX_lookahead (LexState *ls);
static void __attribute__((noreturn)) luaX_syntaxerror (LexState *ls, const char *s);
static const char *luaX_token2str (LexState *ls, int token);
void luaE_setdebt (global_State *g, l_mem debt) {
  l_mem tb = ((g)->GCtotalbytes - (g)->GCdebt);
  ((void)0);
  if (debt > ((l_mem)((((lu_mem)(1)) << (((int)((sizeof(l_mem) * 8))) - 1)) - 1)) - tb)
    debt = ((l_mem)((((lu_mem)(1)) << (((int)((sizeof(l_mem) * 8))) - 1)) - 1)) - tb;
  g->GCtotalbytes = tb + debt;
  g->GCdebt = debt;
}
CallInfo *luaE_extendCI (lua_State *L, int err) {
  CallInfo *ci;
  ci = (((CallInfo *)(luaM_realloc_(L, ((void *)0), ((size_t)((0))) * sizeof(CallInfo), ((size_t)((1))) * sizeof(CallInfo)))));
  if ((__builtin_expect(((ci == ((void *)0)) != 0), 0))) {
    if (err)
      luaD_throw(L, 4);
    return ((void *)0);
  }
  ci->next = L->ci->next;
  ci->previous = L->ci;
  L->ci->next = ci;
  if (ci->next)
    ci->next->previous = ci;
  ci->u.l.trap = 0;
  L->nci++;
  return ci;
}
static void freeCI (lua_State *L) {
  CallInfo *ci = L->ci;
  CallInfo *next = ci->next;
  ci->next = ((void *)0);
  while ((ci = next) != ((void *)0)) {
    next = ci->next;
    luaM_free_(L, (ci), sizeof(*(ci)));
    L->nci--;
  }
}
void luaE_shrinkCI (lua_State *L) {
  CallInfo *ci = L->ci->next;
  CallInfo *next;
  if (ci == ((void *)0))
    return;
  while ((next = ci->next) != ((void *)0)) {
    CallInfo *next2 = next->next;
    ci->next = next2;
    L->nci--;
    luaM_free_(L, (next), sizeof(*(next)));
    if (next2 == ((void *)0))
      break;
    else {
      next2->previous = ci;
      ci = next2;
    }
  }
}
void luaE_checkcstack (lua_State *L) {
  if (((L)->nCcalls & 0xffff) == 200)
    luaG_runerror(L, "C stack overflow");
  else if (((L)->nCcalls & 0xffff) >= (200 / 10 * 11))
    luaD_errerr(L);
}
static void luaE_incCstack (lua_State *L) {
  L->nCcalls++;
  if ((__builtin_expect(((((L)->nCcalls & 0xffff) >= 200) != 0), 0)))
    luaE_checkcstack(L);
}
static void resetCI (lua_State *L) {
  CallInfo *ci = L->ci = &L->base_ci;
  ci->func.p = L->stack.p;
  (((&(ci->func.p)->val))->tt_=(((0) | ((0) << 4))));
  ci->top.p = ci->func.p + 1 + 20;
  ci->u.c.k = ((void *)0);
  ci->callstatus = (1u << (12 + 3));
  L->status = 0;
  L->errfunc = 0;
}
static void stack_init (lua_State *L1, lua_State *L) {
  int i;
  L1->stack.p = ((StackValue*)(luaM_malloc_(L, ((size_t)(((2*20) + 5)))*sizeof(StackValue), 0)));
  L1->tbclist.p = L1->stack.p;
  for (i = 0; i < (2*20) + 5; i++)
    (((&(L1->stack.p + i)->val))->tt_=(((0) | ((0) << 4))));
  L1->stack_last.p = L1->stack.p + (2*20);
  resetCI(L1);
  L1->top.p = L1->stack.p + 1;
}
static void freestack (lua_State *L) {
  if (L->stack.p == ((void *)0))
    return;
  L->ci = &L->base_ci;
  freeCI(L);
  ((void)0);
  luaM_free_(L, (L->stack.p), (((size_t)((((int)(((L)->stack_last.p - (L)->stack.p))) + 5))))*sizeof(*(L->stack.p)));
}
static void init_registry (lua_State *L, global_State *g) {
  TValue aux;
  Table *registry = luaH_new(L);
  { TValue *io = (&g->l_registry); Table *x_ = (registry); ((io)->value_).gc = (((void)0), (&(((union GCUnion *)((x_)))->gc))); ((io)->tt_=(((((5) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
  luaH_resize(L, registry, 3, 0);
  ((&aux)->tt_=(((1) | ((0) << 4))));
  luaH_setint(L, registry, 1, &aux);
  { TValue *io = (&aux); lua_State *x_ = (L); ((io)->value_).gc = (((void)0), (&(((union GCUnion *)((x_)))->gc))); ((io)->tt_=(((((8) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
  luaH_setint(L, registry, 3, &aux);
  { TValue *io = (&aux); Table *x_ = (luaH_new(L)); ((io)->value_).gc = (((void)0), (&(((union GCUnion *)((x_)))->gc))); ((io)->tt_=(((((5) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
  luaH_setint(L, registry, 2, &aux);
}
static void f_luaopen (lua_State *L, void *ud) {
  global_State *g = (L->l_G);
  ((void)(ud));
  stack_init(L, L);
  init_registry(L, g);
  luaS_init(L);
  luaT_init(L);
  luaX_init(L);
  g->gcstp = 0;
  ((&g->nilvalue)->tt_=(((0) | ((0) << 4))));
  ((void)L);
}
static void preinit_thread (lua_State *L, global_State *g) {
  (L->l_G) = g;
  L->stack.p = ((void *)0);
  L->ci = ((void *)0);
  L->nci = 0;
  L->twups = L;
  L->nCcalls = 0;
  L->errorJmp = ((void *)0);
  L->hook = ((void *)0);
  L->hookmask = 0;
  L->basehookcount = 0;
  L->allowhook = 1;
  (L->hookcount = L->basehookcount);
  L->openupval = ((void *)0);
  L->status = 0;
  L->errfunc = 0;
  L->oldpc = 0;
  L->base_ci.previous = L->base_ci.next = ((void *)0);
}
lu_mem luaE_threadsize (lua_State *L) {
  lu_mem sz = ((lu_mem)(sizeof(LX)))
            + ((unsigned int)((L->nci))) * sizeof(CallInfo);
  if (L->stack.p != ((void *)0))
    sz += ((unsigned int)((((int)(((L)->stack_last.p - (L)->stack.p))) + 5))) * sizeof(StackValue);
  return sz;
}
static void close_state (lua_State *L) {
  global_State *g = (L->l_G);
  if (!(((((((&g->nilvalue))->tt_)) & 0x0F)) == (0)))
    luaC_freeallobjects(L);
  else {
    resetCI(L);
    luaD_closeprotected(L, 1, 0);
    L->top.p = L->stack.p + 1;
    luaC_freeallobjects(L);
    ((void)L);
  }
  luaM_free_(L, ((L->l_G)->strt.hash), (((size_t)(((L->l_G)->strt.size))))*sizeof(*((L->l_G)->strt.hash)));
  freestack(L);
  ((void)0);
  (*g->frealloc)(g->ud, g, sizeof(global_State), 0);
}
extern lua_State *lua_newthread (lua_State *L) {
  global_State *g = (L->l_G);
  GCObject *o;
  lua_State *L1;
  ((void) 0);
  { if ((L->l_G)->GCdebt <= 0) { (void)0; luaC_step(L); (void)0;}; ((void)0); };
  o = luaC_newobjdt(L, 8, sizeof(LX), __builtin_offsetof (LX, l));
  L1 = (((void)0), (&((((union GCUnion *)((o))))->th)));
  { TValue *io = ((&(L->top.p)->val)); lua_State *x_ = (L1); ((io)->value_).gc = (((void)0), (&(((union GCUnion *)((x_)))->gc))); ((io)->tt_=(((((8) | ((0) << 4))) | (1 << 6)))); ((void)L, ((void)0)); };
  (L->top.p++, ((void)(L), ((void)0)));
  preinit_thread(L1, g);
  L1->hookmask = L->hookmask;
  L1->basehookcount = L->basehookcount;
  L1->hook = L->hook;
  (L1->hookcount = L1->basehookcount);
  memcpy(((void *)((char *)(L1) - (sizeof(void *)))), ((void *)((char *)((&(g)->mainth.l)) - (sizeof(void *)))),
         (sizeof(void *)));
  ((void)L);
  stack_init(L1, L);
  ((void) 0);
  return L1;
}
void luaE_freethread (lua_State *L, lua_State *L1) {
  LX *l = (((LX *)(((lu_byte *)((L1))) - __builtin_offsetof (LX, l))));
  luaF_closeupval(L1, L1->stack.p);
  ((void)0);
  ((void)L);
  freestack(L1);
  luaM_free_(L, (l), sizeof(*(l)));
}
TStatus luaE_resetthread (lua_State *L, TStatus status) {
  resetCI(L);
  if (status == 1)
    status = 0;
  status = luaD_closeprotected(L, 1, status);
  if (status != 0)
    luaD_seterrorobj(L, status, L->stack.p + 1);
  else
    L->top.p = L->stack.p + 1;
  luaD_reallocstack(L, ((int)((L->ci->top.p - L->stack.p))), 0);
  return status;
}
extern int lua_closethread (lua_State *L, lua_State *from) {
  TStatus status;
  ((void) 0);
  L->nCcalls = (from) ? ((from)->nCcalls & 0xffff) : 0;
  status = luaE_resetthread(L, L->status);
  if (L == from)
    luaD_throwbaselevel(L, status);
  ((void) 0);
  return ((int)((status)));
}
extern lua_State *lua_newstate (lua_Alloc f, void *ud, unsigned seed) {
  int i;
  lua_State *L;
  global_State *g = ((global_State*)((*f)(ud, ((void *)0), 8, sizeof(global_State))));
  if (g == ((void *)0)) return ((void *)0);
  L = &g->mainth.l;
  L->tt = ((8) | ((0) << 4));
  g->currentwhite = (1<<(3));
  L->marked = ((lu_byte)(((g)->currentwhite & ((1<<(3)) | (1<<(4))))));
  preinit_thread(L, g);
  g->allgc = (((void)0), (&(((union GCUnion *)((L)))->gc)));
  L->next = ((void *)0);
  ((L)->nCcalls += 0x10000);
  g->frealloc = f;
  g->ud = ud;
  g->warnf = ((void *)0);
  g->ud_warn = ((void *)0);
  g->seed = seed;
  g->gcstp = 2;
  g->strt.size = g->strt.nuse = 0;
  g->strt.hash = ((void *)0);
  ((&g->l_registry)->tt_=(((0) | ((0) << 4))));
  g->panic = ((void *)0);
  g->gcstate = 8;
  g->gckind = 0;
  g->gcstopem = 0;
  g->gcemergency = 0;
  g->finobj = g->tobefnz = g->fixedgc = ((void *)0);
  g->firstold1 = g->survival = g->old1 = g->reallyold = ((void *)0);
  g->finobjsur = g->finobjold1 = g->finobjrold = ((void *)0);
  g->sweepgc = ((void *)0);
  g->gray = g->grayagain = ((void *)0);
  g->weak = g->ephemeron = g->allweak = ((void *)0);
  g->twups = ((void *)0);
  g->GCtotalbytes = sizeof(global_State);
  g->GCmarked = 0;
  g->GCdebt = 0;
  { TValue *io=(&g->nilvalue); ((io)->value_).i=(0); ((io)->tt_=(((3) | ((0) << 4)))); };
  (g->gcparams[3] = luaO_codeparam(250));
  (g->gcparams[4] = luaO_codeparam(200));
  (g->gcparams[5] = luaO_codeparam((200 * sizeof(Table))));
  (g->gcparams[0] = luaO_codeparam(20));
  (g->gcparams[2] = luaO_codeparam(70));
  (g->gcparams[1] = luaO_codeparam(50));
  for (i=0; i < 9; i++) g->mt[i] = ((void *)0);
  if (luaD_rawrunprotected(L, f_luaopen, ((void *)0)) != 0) {
    close_state(L);
    L = ((void *)0);
  }
  return L;
}
extern void lua_close (lua_State *L) {
  ((void) 0);
  L = (&((L->l_G))->mainth.l);
  close_state(L);
}
void luaE_warning (lua_State *L, const char *msg, int tocont) {
  lua_WarnFunction wf = (L->l_G)->warnf;
  if (wf != ((void *)0))
    wf((L->l_G)->ud_warn, msg, tocont);
}
void luaE_warnerror (lua_State *L, const char *where) {
  TValue *errobj = (&(L->top.p - 1)->val);
  const char *msg = ((((((((errobj))->tt_)) & 0x0F)) == (4)))
                  ? ((((((void)0), ((((void)0), (&((((union GCUnion *)((((errobj)->value_).gc))))->ts))))))->shrlen >= 0) ? (((char *)((&((((void)0), ((((void)0), (&((((union GCUnion *)((((errobj)->value_).gc))))->ts))))))->contents)))) : ((((void)0), ((((void)0), (&((((union GCUnion *)((((errobj)->value_).gc))))->ts))))))->contents)
                  : "error object is not a string";
  luaE_warning(L, "error in ", 1);
  luaE_warning(L, where, 1);
  luaE_warning(L, " (", 1);
  luaE_warning(L, msg, 1);
  luaE_warning(L, ")", 0);
}
static void reallymarkobject (global_State *g, GCObject *o);
static void atomic (lua_State *L);
static void entersweep (lua_State *L);
static l_mem objsize (GCObject *o) {
  lu_mem res;
  switch (o->tt) {
    case ((5) | ((0) << 4)): {
      res = luaH_size((((void)0), (&((((union GCUnion *)((o))))->h))));
      break;
    }
    case ((6) | ((0) << 4)): {
      LClosure *cl = (((void)0), (&((((union GCUnion *)((o))))->cl.l)));
      res = (__builtin_offsetof (LClosure, upvals) + sizeof(UpVal *) * ((unsigned int)((cl->nupvalues))));
      break;
    }
    case ((6) | ((2) << 4)): {
      CClosure *cl = (((void)0), (&((((union GCUnion *)((o))))->cl.c)));
      res = (__builtin_offsetof (CClosure, upvalue) + sizeof(TValue) * ((unsigned int)((cl->nupvalues))));
      break;
    }
    case ((7) | ((0) << 4)): {
      Udata *u = (((void)0), (&((((union GCUnion *)((o))))->u)));
      res = (((u->nuvalue) == 0 ? __builtin_offsetof (Udata0, bindata) : __builtin_offsetof (Udata, uv) + (sizeof(UValue) * (u->nuvalue))) + (u->len));
      break;
    }
    case (((9 +1)) | ((0) << 4)): {
      res = luaF_protosize((((void)0), (&((((union GCUnion *)((o))))->p))));
      break;
    }
    case ((8) | ((0) << 4)): {
      res = luaE_threadsize((((void)0), (&((((union GCUnion *)((o))))->th))));
      break;
    }
    case ((4) | ((0) << 4)): {
      TString *ts = (((void)0), (&((((union GCUnion *)((o))))->ts)));
      res = (__builtin_offsetof (TString, contents) + ((((unsigned int)((ts->shrlen)))) + 1) * sizeof(char));
      break;
    }
    case ((4) | ((1) << 4)): {
      TString *ts = (((void)0), (&((((union GCUnion *)((o))))->ts)));
      res = luaS_sizelngstr(ts->u.lnglen, ts->shrlen);
      break;
    }
    case ((9) | ((0) << 4)): {
      res = sizeof(UpVal);
      break;
    }
    default: res = 0; ((void)0);
  }
  return ((l_mem)(res));
}
static GCObject **getgclist (GCObject *o) {
  switch (o->tt) {
    case ((5) | ((0) << 4)): return &(((void)0), (&((((union GCUnion *)((o))))->h)))->gclist;
    case ((6) | ((0) << 4)): return &(((void)0), (&((((union GCUnion *)((o))))->cl.l)))->gclist;
    case ((6) | ((2) << 4)): return &(((void)0), (&((((union GCUnion *)((o))))->cl.c)))->gclist;
    case ((8) | ((0) << 4)): return &(((void)0), (&((((union GCUnion *)((o))))->th)))->gclist;
    case (((9 +1)) | ((0) << 4)): return &(((void)0), (&((((union GCUnion *)((o))))->p)))->gclist;
    case ((7) | ((0) << 4)): {
      Udata *u = (((void)0), (&((((union GCUnion *)((o))))->u)));
      ((void)0);
      return &u->gclist;
    }
    default: ((void)0); return 0;
  }
}
static void linkgclist_ (GCObject *o, GCObject **pnext, GCObject **list) {
  ((void)0);
  *pnext = *list;
  *list = o;
  ((o->marked) &= ((lu_byte)((~(((1<<(5)) | ((1<<(3)) | (1<<(4)))))))));
}
static void clearkey (Node *n) {
  ((void)0);
  if ((((n)->u.key_tt) & (1 << 6)))
    (((n)->u.key_tt) = (9 +2));
}
static int iscleared (global_State *g, const GCObject *o) {
  if (o == ((void *)0)) return 0;
  else if (((o->tt) & 0x0F) == 4) {
    { if ((((o)->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (((void)0), (&(((union GCUnion *)((o)))->gc)))); };
    return 0;
  }
  else return (((o)->marked) & (((1<<(3)) | (1<<(4)))));
}
void luaC_barrier_ (lua_State *L, GCObject *o, GCObject *v) {
  global_State *g = (L->l_G);
  ((void)0);
  if (((g)->gcstate <= 2)) {
    reallymarkobject(g, v);
    if ((((o)->marked & 7) > 1)) {
      ((void)0);
      ((v)->marked = ((lu_byte)((((v)->marked & (~7)) | 2))));
    }
  }
  else {
    ((void)0);
    if (g->gckind != 1)
      (o->marked = ((lu_byte)(((o->marked & ~((1<<(5)) | ((1<<(3)) | (1<<(4))))) | ((lu_byte)(((g)->currentwhite & ((1<<(3)) | (1<<(4))))))))));
  }
}
void luaC_barrierback_ (lua_State *L, GCObject *o) {
  global_State *g = (L->l_G);
  ((void)0);
  ((void)0);
  if (((o)->marked & 7) == 6)
    ((o->marked) &= ((lu_byte)((~(((1<<(5)) | ((1<<(3)) | (1<<(4)))))))));
  else
    linkgclist_((((void)0), (&(((union GCUnion *)((o)))->gc))), getgclist(o), &(g->grayagain));
  if ((((o)->marked & 7) > 1))
    ((o)->marked = ((lu_byte)((((o)->marked & (~7)) | 5))));
}
void luaC_fix (lua_State *L, GCObject *o) {
  global_State *g = (L->l_G);
  ((void)0);
  ((o->marked) &= ((lu_byte)((~(((1<<(5)) | ((1<<(3)) | (1<<(4)))))))));
  ((o)->marked = ((lu_byte)((((o)->marked & (~7)) | 4))));
  g->allgc = o->next;
  o->next = g->fixedgc;
  g->fixedgc = o;
}
GCObject *luaC_newobjdt (lua_State *L, lu_byte tt, size_t sz, size_t offset) {
  global_State *g = (L->l_G);
  char *p = ((char *)((luaM_malloc_(L, (sz), ((tt) & 0x0F)))));
  GCObject *o = ((GCObject *)(p + offset));
  o->marked = ((lu_byte)(((g)->currentwhite & ((1<<(3)) | (1<<(4))))));
  o->tt = tt;
  o->next = g->allgc;
  g->allgc = o;
  return o;
}
GCObject *luaC_newobj (lua_State *L, lu_byte tt, size_t sz) {
  return luaC_newobjdt(L, tt, sz, 0);
}
static void reallymarkobject (global_State *g, GCObject *o) {
  g->GCmarked += objsize(o);
  switch (o->tt) {
    case ((4) | ((0) << 4)):
    case ((4) | ((1) << 4)): {
      (o->marked = ((lu_byte)(((o->marked & ~((1<<(3)) | (1<<(4)))) | (1<<(5))))));
      break;
    }
    case ((9) | ((0) << 4)): {
      UpVal *uv = (((void)0), (&((((union GCUnion *)((o))))->upv)));
      if (((uv)->v.p != &(uv)->u.value))
        ((uv->marked) &= ((lu_byte)((~(((1<<(5)) | ((1<<(3)) | (1<<(4)))))))));
      else
        (uv->marked = ((lu_byte)(((uv->marked & ~((1<<(3)) | (1<<(4)))) | (1<<(5))))));
      { ((void)(&(g)->mainth.l), ((void)0)); if (((((uv->v.p)->tt_) & (1 << 6)) && ((((((void)0), (((uv->v.p)->value_).gc)))->marked) & (((1<<(3)) | (1<<(4))))))) reallymarkobject(g,(((void)0), (((uv->v.p)->value_).gc))); };
      break;
    }
    case ((7) | ((0) << 4)): {
      Udata *u = (((void)0), (&((((union GCUnion *)((o))))->u)));
      if (u->nuvalue == 0) {
        { if (u->metatable) { if ((((u->metatable)->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (((void)0), (&(((union GCUnion *)((u->metatable)))->gc)))); }; };
        (u->marked = ((lu_byte)(((u->marked & ~((1<<(3)) | (1<<(4)))) | (1<<(5))))));
        break;
      }
    }
    case ((6) | ((0) << 4)): case ((6) | ((2) << 4)): case ((5) | ((0) << 4)):
    case ((8) | ((0) << 4)): case (((9 +1)) | ((0) << 4)): {
      linkgclist_((((void)0), (&(((union GCUnion *)((o)))->gc))), getgclist(o), &(g->gray));
      break;
    }
    default: ((void)0); break;
  }
}
static void markmt (global_State *g) {
  int i;
  for (i=0; i < 9; i++)
    { if (g->mt[i]) { if ((((g->mt[i])->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (((void)0), (&(((union GCUnion *)((g->mt[i])))->gc)))); }; };
}
static void markbeingfnz (global_State *g) {
  GCObject *o;
  for (o = g->tobefnz; o != ((void *)0); o = o->next)
    { if ((((o)->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (((void)0), (&(((union GCUnion *)((o)))->gc)))); };
}
static void remarkupvals (global_State *g) {
  lua_State *thread;
  lua_State **p = &g->twups;
  while ((thread = *p) != ((void *)0)) {
    if (!(((thread)->marked) & (((1<<(3)) | (1<<(4))))) && thread->openupval != ((void *)0))
      p = &thread->twups;
    else {
      UpVal *uv;
      ((void)0);
      *p = thread->twups;
      thread->twups = thread;
      for (uv = thread->openupval; uv != ((void *)0); uv = uv->u.open.next) {
        ((void)0);
        if (!(((uv)->marked) & (((1<<(3)) | (1<<(4)))))) {
          ((void)0);
          { ((void)(&(g)->mainth.l), ((void)0)); if (((((uv->v.p)->tt_) & (1 << 6)) && ((((((void)0), (((uv->v.p)->value_).gc)))->marked) & (((1<<(3)) | (1<<(4))))))) reallymarkobject(g,(((void)0), (((uv->v.p)->value_).gc))); };
        }
      }
    }
  }
}
static void cleargraylists (global_State *g) {
  g->gray = g->grayagain = ((void *)0);
  g->weak = g->allweak = g->ephemeron = ((void *)0);
}
static void restartcollection (global_State *g) {
  cleargraylists(g);
  g->GCmarked = 0;
  { if (((((&(g)->mainth.l))->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g, (((void)0), (&(((union GCUnion *)(((&(g)->mainth.l))))->gc)))); };
  { ((void)(&(g)->mainth.l), ((void)0)); if (((((&g->l_registry)->tt_) & (1 << 6)) && ((((((void)0), (((&g->l_registry)->value_).gc)))->marked) & (((1<<(3)) | (1<<(4))))))) reallymarkobject(g,(((void)0), (((&g->l_registry)->value_).gc))); };
  markmt(g);
  markbeingfnz(g);
}
static void genlink (global_State *g, GCObject *o) {
  ((void)0);
  if (((o)->marked & 7) == 5) {
    linkgclist_((((void)0), (&(((union GCUnion *)((o)))->gc))), getgclist(o), &(g->grayagain));
  }
  else if (((o)->marked & 7) == 6)
    ((o)->marked = ((lu_byte)((((o)->marked & (~7)) | 4))));
}
static void traverseweakvalue (global_State *g, Table *h) {
  Node *n, *limit = (&(h)->node[((size_t)((((1u<<((h)->lsizenode))))))]);
  int hasclears = (h->asize > 0);
  for (n = (&(h)->node[0]); n < limit; n++) {
    if (((((((((&(n)->i_val)))->tt_)) & 0x0F)) == (0)))
      clearkey(n);
    else {
      ((void)0);
      { if ((((n)->u.key_tt) & (1 << 6)) && ((((((n)->u.key_val).gc))->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g,(((n)->u.key_val).gc)); };
      if (!hasclears && iscleared(g, (((((&(n)->i_val))->tt_) & (1 << 6)) ? (((void)0), ((((&(n)->i_val))->value_).gc)) : ((void *)0))))
        hasclears = 1;
    }
  }
  if (g->gcstate == 0)
    linkgclist_((((void)0), (&(((union GCUnion *)((h)))->gc))), &(h)->gclist, &(g->grayagain));
  else if (hasclears)
      linkgclist_((((void)0), (&(((union GCUnion *)((h)))->gc))), &(h)->gclist, &(g->weak));
  else
    genlink(g, (((void)0), (&(((union GCUnion *)((h)))->gc))));
}
static int traversearray (global_State *g, Table *h) {
  unsigned asize = h->asize;
  int marked = 0;
  unsigned i;
  for (i = 0; i < asize; i++) {
    GCObject *o = ((*(((lu_byte*)((h)->array)) + sizeof(unsigned) + (i)) & (1 << 6)) ? ((h)->array - 1 - (i))->gc : ((void *)0));
    if (o != ((void *)0) && (((o)->marked) & (((1<<(3)) | (1<<(4)))))) {
      marked = 1;
      reallymarkobject(g, o);
    }
  }
  return marked;
}
static int traverseephemeron (global_State *g, Table *h, int inv) {
  int hasclears = 0;
  int hasww = 0;
  unsigned int i;
  unsigned int nsize = ((1u<<((h)->lsizenode)));
  int marked = traversearray(g, h);
  for (i = 0; i < nsize; i++) {
    Node *n = inv ? (&(h)->node[nsize - 1 - i]) : (&(h)->node[i]);
    if (((((((((&(n)->i_val)))->tt_)) & 0x0F)) == (0)))
      clearkey(n);
    else if (iscleared(g, ((((n)->u.key_tt) & (1 << 6)) ? (((n)->u.key_val).gc) : ((void *)0)))) {
      hasclears = 1;
      if ((((((&(n)->i_val))->tt_) & (1 << 6)) && ((((((void)0), ((((&(n)->i_val))->value_).gc)))->marked) & (((1<<(3)) | (1<<(4)))))))
        hasww = 1;
    }
    else if ((((((&(n)->i_val))->tt_) & (1 << 6)) && ((((((void)0), ((((&(n)->i_val))->value_).gc)))->marked) & (((1<<(3)) | (1<<(4))))))) {
      marked = 1;
      reallymarkobject(g, (((void)0), ((((&(n)->i_val))->value_).gc)));
    }
  }
  if (g->gcstate == 0)
    linkgclist_((((void)0), (&(((union GCUnion *)((h)))->gc))), &(h)->gclist, &(g->grayagain));
  else if (hasww)
    linkgclist_((((void)0), (&(((union GCUnion *)((h)))->gc))), &(h)->gclist, &(g->ephemeron));
  else if (hasclears)
    linkgclist_((((void)0), (&(((union GCUnion *)((h)))->gc))), &(h)->gclist, &(g->allweak));
  else
    genlink(g, (((void)0), (&(((union GCUnion *)((h)))->gc))));
  return marked;
}
static void traversestrongtable (global_State *g, Table *h) {
  Node *n, *limit = (&(h)->node[((size_t)((((1u<<((h)->lsizenode))))))]);
  traversearray(g, h);
  for (n = (&(h)->node[0]); n < limit; n++) {
    if (((((((((&(n)->i_val)))->tt_)) & 0x0F)) == (0)))
      clearkey(n);
    else {
      ((void)0);
      { if ((((n)->u.key_tt) & (1 << 6)) && ((((((n)->u.key_val).gc))->marked) & (((1<<(3)) | (1<<(4)))))) reallymarkobject(g,(((n)->u.key_val).gc)); };
      { ((void)(&(g)->mainth.l), ((void)0)); if ((((((&(n)->i_val))->tt_) & (1 << 6)) && ((((((void)0), ((((&(n)->i_val))->value_).gc)))->marked) & (((1<<(3)) | (1<<(4))))))) reallymarkobject(g,(((void)0), ((((&(n)->i_val))->value_).gc))); };
    }
  }
  genlink(g, (((void)0), (&(((union GCUnion *)((h)))->gc))));
}
static int getmode (global_State *g, Table *h) {
  const TValue
