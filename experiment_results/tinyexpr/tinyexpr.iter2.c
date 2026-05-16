typedef struct te_expr {
    int type;
    union {double value; const double *bound; const void *function;};
    void *parameters[1];
} te_expr;
enum {
    TE_VARIABLE = 0,
    TE_FUNCTION0 = 8, TE_FUNCTION1, TE_FUNCTION2, TE_FUNCTION3,
    TE_FUNCTION4, TE_FUNCTION5, TE_FUNCTION6, TE_FUNCTION7,
    TE_CLOSURE0 = 16, TE_CLOSURE1, TE_CLOSURE2, TE_CLOSURE3,
    TE_CLOSURE4, TE_CLOSURE5, TE_CLOSURE6, TE_CLOSURE7,
    TE_FLAG_PURE = 32
};
typedef struct te_variable {
    const char *name;
    const void *address;
    int type;
    void *context;
} te_variable;
double te_interp(const char *expression, int *error);
te_expr *te_compile(const char *expression, const te_variable *variables, int var_count, int *error);
double te_eval(const te_expr *n);
void te_print(const te_expr *n);
void te_free(te_expr *n);
typedef long unsigned int size_t;
typedef int wchar_t;

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
typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;
extern size_t __ctype_get_mb_cur_max (void) ;
extern double atof (const char *__nptr)
      ;
extern int atoi (const char *__nptr)
      ;
extern long int atol (const char *__nptr)
      ;
extern long long int atoll (const char *__nptr)
      ;
extern double strtod (const char * restrict __nptr,
        char ** restrict __endptr)
      ;
extern float strtof (const char * restrict __nptr,
       char ** restrict __endptr) ;
extern long double strtold (const char * restrict __nptr,
       char ** restrict __endptr)
      ;
extern long int strtol (const char * restrict __nptr,
   char ** restrict __endptr, int __base)
      ;
extern unsigned long int strtoul (const char * restrict __nptr,
      char ** restrict __endptr, int __base)
      ;
extern long long int strtoq (const char * restrict __nptr,
        char ** restrict __endptr, int __base)
      ;
extern unsigned long long int strtouq (const char * restrict __nptr,
           char ** restrict __endptr, int __base)
      ;
extern long long int strtoll (const char * restrict __nptr,
         char ** restrict __endptr, int __base)
      ;
extern unsigned long long int strtoull (const char * restrict __nptr,
     char ** restrict __endptr, int __base)
      ;
extern char *l64a (long int __n) ;
extern long int a64l (const char *__s)
      ;

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
typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;
typedef __loff_t loff_t;
typedef __ino_t ino_t;
typedef __dev_t dev_t;
typedef __gid_t gid_t;
typedef __mode_t mode_t;
typedef __nlink_t nlink_t;
typedef __uid_t uid_t;
typedef __off_t off_t;
typedef __pid_t pid_t;
typedef __id_t id_t;
typedef __ssize_t ssize_t;
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;
typedef __key_t key_t;
typedef __clock_t clock_t;
typedef __clockid_t clockid_t;
typedef __time_t time_t;
typedef __timer_t timer_t;
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
typedef __uint8_t u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;
static inline __uint16_t
__uint16_identity (__uint16_t __x)
{
  return __x;
}
static inline __uint32_t
__uint32_identity (__uint32_t __x)
{
  return __x;
}
static inline __uint64_t
__uint64_identity (__uint64_t __x)
{
  return __x;
}
typedef struct
{
  unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
} __sigset_t;
typedef __sigset_t sigset_t;
struct timeval
{
  __time_t tv_sec;
  __suseconds_t tv_usec;
};
struct timespec
{
  __time_t tv_sec;
  __syscall_slong_t tv_nsec;
};
typedef __suseconds_t suseconds_t;
typedef long int __fd_mask;
typedef struct
  {
    __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];
  } fd_set;
typedef __fd_mask fd_mask;

extern int select (int __nfds, fd_set * restrict __readfds,
     fd_set * restrict __writefds,
     fd_set * restrict __exceptfds,
     struct timeval * restrict __timeout);
extern int pselect (int __nfds, fd_set * restrict __readfds,
      fd_set * restrict __writefds,
      fd_set * restrict __exceptfds,
      const struct timespec * restrict __timeout,
      const __sigset_t * restrict __sigmask);

typedef __blksize_t blksize_t;
typedef __blkcnt_t blkcnt_t;
typedef __fsblkcnt_t fsblkcnt_t;
typedef __fsfilcnt_t fsfilcnt_t;
typedef union
{
  unsigned long long int __value64;
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
typedef union pthread_attr_t pthread_attr_t;
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
  long long int __align;
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

extern long int random (void) ;
extern void srandom (unsigned int __seed) ;
extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) ;
extern char *setstate (char *__statebuf) ;
struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };
extern int random_r (struct random_data * restrict __buf,
       int32_t * restrict __result) ;
extern int srandom_r (unsigned int __seed, struct random_data *__buf)
      ;
extern int initstate_r (unsigned int __seed, char * restrict __statebuf,
   size_t __statelen,
   struct random_data * restrict __buf)
      ;
extern int setstate_r (char * restrict __statebuf,
         struct random_data * restrict __buf)
      ;
extern int rand (void) ;
extern void srand (unsigned int __seed) ;
extern int rand_r (unsigned int *__seed) ;
extern double drand48 (void) ;
extern double erand48 (unsigned short int __xsubi[3]) ;
extern long int lrand48 (void) ;
extern long int nrand48 (unsigned short int __xsubi[3])
      ;
extern long int mrand48 (void) ;
extern long int jrand48 (unsigned short int __xsubi[3])
      ;
extern void srand48 (long int __seedval) ;
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
      ;
extern void lcong48 (unsigned short int __param[7]) ;
struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    unsigned long long int __a;
  };
extern int drand48_r (struct drand48_data * restrict __buffer,
        double * restrict __result) ;
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data * restrict __buffer,
        double * restrict __result) ;
extern int lrand48_r (struct drand48_data * restrict __buffer,
        long int * restrict __result)
      ;
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data * restrict __buffer,
        long int * restrict __result)
      ;
extern int mrand48_r (struct drand48_data * restrict __buffer,
        long int * restrict __result)
      ;
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data * restrict __buffer,
        long int * restrict __result)
      ;
extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
      ;
extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) ;
extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
      ;
extern __uint32_t arc4random (void)
      ;
extern void arc4random_buf (void *__buf, size_t __size)
      ;
extern __uint32_t arc4random_uniform (__uint32_t __upper_bound)
      ;
extern void *malloc (size_t __size) 
      ;
extern void *calloc (size_t __nmemb, size_t __size)
      ;
extern void *realloc (void *__ptr, size_t __size)
      ;
extern void free (void *__ptr) ;
extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
      
    ;

extern void *alloca (size_t __size) ;

extern void *valloc (size_t __size) 
      ;
extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
      ;
extern void *aligned_alloc (size_t __alignment, size_t __size)
      
      ;
extern void abort (void) ;
extern int atexit (void (*__func) (void)) ;
extern int at_quick_exit (void (*__func) (void)) ;
extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
      ;
extern void exit (int __status) ;
extern void quick_exit (int __status) ;
extern void _Exit (int __status) ;
extern char *getenv (const char *__name) ;
extern int putenv (char *__string) ;
extern int setenv (const char *__name, const char *__value, int __replace)
      ;
extern int unsetenv (const char *__name) ;
extern int clearenv (void) ;
extern char *mktemp (char *__template) ;
extern int mkstemp (char *__template) ;
extern int mkstemps (char *__template, int __suffixlen) ;
extern char *mkdtemp (char *__template) ;
extern int system (const char *__command) ;
extern char *realpath (const char * restrict __name,
         char * restrict __resolved) ;
typedef int (*__compar_fn_t) (const void *, const void *);
extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
      ;
extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) ;
extern int abs (int __x) ;
extern long int labs (long int __x) ;
extern long long int llabs (long long int __x)
      ;
extern div_t div (int __numer, int __denom)
      ;
extern ldiv_t ldiv (long int __numer, long int __denom)
      ;
extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
      ;
extern char *ecvt (double __value, int __ndigit, int * restrict __decpt,
     int * restrict __sign) ;
extern char *fcvt (double __value, int __ndigit, int * restrict __decpt,
     int * restrict __sign) ;
extern char *gcvt (double __value, int __ndigit, char *__buf)
      ;
extern char *qecvt (long double __value, int __ndigit,
      int * restrict __decpt, int * restrict __sign)
      ;
extern char *qfcvt (long double __value, int __ndigit,
      int * restrict __decpt, int * restrict __sign)
      ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
      ;
extern int ecvt_r (double __value, int __ndigit, int * restrict __decpt,
     int * restrict __sign, char * restrict __buf,
     size_t __len) ;
extern int fcvt_r (double __value, int __ndigit, int * restrict __decpt,
     int * restrict __sign, char * restrict __buf,
     size_t __len) ;
extern int qecvt_r (long double __value, int __ndigit,
      int * restrict __decpt, int * restrict __sign,
      char * restrict __buf, size_t __len)
      ;
extern int qfcvt_r (long double __value, int __ndigit,
      int * restrict __decpt, int * restrict __sign,
      char * restrict __buf, size_t __len)
      ;
extern int mblen (const char *__s, size_t __n) ;
extern int mbtowc (wchar_t * restrict __pwc,
     const char * restrict __s, size_t __n) ;
extern int wctomb (char *__s, wchar_t __wchar) ;
extern size_t mbstowcs (wchar_t * restrict __pwcs,
   const char * restrict __s, size_t __n) 
    ;
extern size_t wcstombs (char * restrict __s,
   const wchar_t * restrict __pwcs, size_t __n)
     
  
  ;
extern int rpmatch (const char *__response) ;
extern int getsubopt (char ** restrict __optionp,
        char *const * restrict __tokens,
        char ** restrict __valuep)
      ;
extern int getloadavg (double __loadavg[], int __nelem)
      ;


typedef float float_t;
typedef double double_t;
extern int __fpclassify (double __value) 
     ;
extern int __signbit (double __value) 
     ;
extern int __isinf (double __value) 
  ;
extern int __finite (double __value) 
  ;
extern int __isnan (double __value) 
  ;
extern int __iseqsig (double __x, double __y) ;
extern int __issignaling (double __value) 
     ;
 extern double acos (double __x) ; extern double __acos (double __x) ;
 extern double asin (double __x) ; extern double __asin (double __x) ;
 extern double atan (double __x) ; extern double __atan (double __x) ;
 extern double atan2 (double __y, double __x) ; extern double __atan2 (double __y, double __x) ;
 extern double cos (double __x) ; extern double __cos (double __x) ;
 extern double sin (double __x) ; extern double __sin (double __x) ;
 extern double tan (double __x) ; extern double __tan (double __x) ;
 extern double cosh (double __x) ; extern double __cosh (double __x) ;
 extern double sinh (double __x) ; extern double __sinh (double __x) ;
 extern double tanh (double __x) ; extern double __tanh (double __x) ;
 extern double acosh (double __x) ; extern double __acosh (double __x) ;
 extern double asinh (double __x) ; extern double __asinh (double __x) ;
 extern double atanh (double __x) ; extern double __atanh (double __x) ;
 extern double exp (double __x) ; extern double __exp (double __x) ;
extern double frexp (double __x, int *__exponent) ; extern double __frexp (double __x, int *__exponent) ;
extern double ldexp (double __x, int __exponent) ; extern double __ldexp (double __x, int __exponent) ;
 extern double log (double __x) ; extern double __log (double __x) ;
 extern double log10 (double __x) ; extern double __log10 (double __x) ;
extern double modf (double __x, double *__iptr) ; extern double __modf (double __x, double *__iptr) ;
 extern double expm1 (double __x) ; extern double __expm1 (double __x) ;
 extern double log1p (double __x) ; extern double __log1p (double __x) ;
extern double logb (double __x) ; extern double __logb (double __x) ;
 extern double exp2 (double __x) ; extern double __exp2 (double __x) ;
 extern double log2 (double __x) ; extern double __log2 (double __x) ;
 extern double pow (double __x, double __y) ; extern double __pow (double __x, double __y) ;
extern double sqrt (double __x) ; extern double __sqrt (double __x) ;
 extern double hypot (double __x, double __y) ; extern double __hypot (double __x, double __y) ;
 extern double cbrt (double __x) ; extern double __cbrt (double __x) ;
extern double ceil (double __x) ; extern double __ceil (double __x) ;
extern double fabs (double __x) ; extern double __fabs (double __x) ;
extern double floor (double __x) ; extern double __floor (double __x) ;
extern double fmod (double __x, double __y) ; extern double __fmod (double __x, double __y) ;
extern int isinf (double __value) 
  ;
extern int finite (double __value) 
  ;
extern double drem (double __x, double __y) ; extern double __drem (double __x, double __y) ;
extern double significand (double __x) ; extern double __significand (double __x) ;
extern double copysign (double __x, double __y) ; extern double __copysign (double __x, double __y) ;
extern double nan (const char *__tagb) ; extern double __nan (const char *__tagb) ;
extern int isnan (double __value) 
  ;
extern double j0 (double) ; extern double __j0 (double) ;
extern double j1 (double) ; extern double __j1 (double) ;
extern double jn (int, double) ; extern double __jn (int, double) ;
extern double y0 (double) ; extern double __y0 (double) ;
extern double y1 (double) ; extern double __y1 (double) ;
extern double yn (int, double) ; extern double __yn (int, double) ;
 extern double erf (double) ; extern double __erf (double) ;
 extern double erfc (double) ; extern double __erfc (double) ;
extern double lgamma (double) ; extern double __lgamma (double) ;
extern double tgamma (double) ; extern double __tgamma (double) ;
extern double gamma (double) ; extern double __gamma (double) ;
extern double lgamma_r (double, int *__signgamp) ; extern double __lgamma_r (double, int *__signgamp) ;
extern double rint (double __x) ; extern double __rint (double __x) ;
extern double nextafter (double __x, double __y) ; extern double __nextafter (double __x, double __y) ;
extern double nexttoward (double __x, long double __y) ; extern double __nexttoward (double __x, long double __y) ;
extern double remainder (double __x, double __y) ; extern double __remainder (double __x, double __y) ;
extern double scalbn (double __x, int __n) ; extern double __scalbn (double __x, int __n) ;
extern int ilogb (double __x) ; extern int __ilogb (double __x) ;
extern double scalbln (double __x, long int __n) ; extern double __scalbln (double __x, long int __n) ;
extern double nearbyint (double __x) ; extern double __nearbyint (double __x) ;
extern double round (double __x) ; extern double __round (double __x) ;
extern double trunc (double __x) ; extern double __trunc (double __x) ;
extern double remquo (double __x, double __y, int *__quo) ; extern double __remquo (double __x, double __y, int *__quo) ;
extern long int lrint (double __x) ; extern long int __lrint (double __x) ;

extern long long int llrint (double __x) ; extern long long int __llrint (double __x) ;
extern long int lround (double __x) ; extern long int __lround (double __x) ;

extern long long int llround (double __x) ; extern long long int __llround (double __x) ;
extern double fdim (double __x, double __y) ; extern double __fdim (double __x, double __y) ;
extern double fmax (double __x, double __y) ; extern double __fmax (double __x, double __y) ;
extern double fmin (double __x, double __y) ; extern double __fmin (double __x, double __y) ;
extern double fma (double __x, double __y, double __z) ; extern double __fma (double __x, double __y, double __z) ;
extern double scalb (double __x, double __n) ; extern double __scalb (double __x, double __n) ;
extern int __fpclassifyf (float __value) 
     ;
extern int __signbitf (float __value) 
     ;
extern int __isinff (float __value) 
  ;
extern int __finitef (float __value) 
  ;
extern int __isnanf (float __value) 
  ;
extern int __iseqsigf (float __x, float __y) ;
extern int __issignalingf (float __value) 
     ;
 extern float acosf (float __x) ; extern float __acosf (float __x) ;
 extern float asinf (float __x) ; extern float __asinf (float __x) ;
 extern float atanf (float __x) ; extern float __atanf (float __x) ;
 extern float atan2f (float __y, float __x) ; extern float __atan2f (float __y, float __x) ;
 extern float cosf (float __x) ; extern float __cosf (float __x) ;
 extern float sinf (float __x) ; extern float __sinf (float __x) ;
 extern float tanf (float __x) ; extern float __tanf (float __x) ;
 extern float coshf (float __x) ; extern float __coshf (float __x) ;
 extern float sinhf (float __x) ; extern float __sinhf (float __x) ;
 extern float tanhf (float __x) ; extern float __tanhf (float __x) ;
 extern float acoshf (float __x) ; extern float __acoshf (float __x) ;
 extern float asinhf (float __x) ; extern float __asinhf (float __x) ;
 extern float atanhf (float __x) ; extern float __atanhf (float __x) ;
 extern float expf (float __x) ; extern float __expf (float __x) ;
extern float frexpf (float __x, int *__exponent) ; extern float __frexpf (float __x, int *__exponent) ;
extern float ldexpf (float __x, int __exponent) ; extern float __ldexpf (float __x, int __exponent) ;
 extern float logf (float __x) ; extern float __logf (float __x) ;
 extern float log10f (float __x) ; extern float __log10f (float __x) ;
extern float modff (float __x, float *__iptr) ; extern float __modff (float __x, float *__iptr) ;
 extern float expm1f (float __x) ; extern float __expm1f (float __x) ;
 extern float log1pf (float __x) ; extern float __log1pf (float __x) ;
extern float logbf (float __x) ; extern float __logbf (float __x) ;
 extern float exp2f (float __x) ; extern float __exp2f (float __x) ;
 extern float log2f (float __x) ; extern float __log2f (float __x) ;
 extern float powf (float __x, float __y) ; extern float __powf (float __x, float __y) ;
extern float sqrtf (float __x) ; extern float __sqrtf (float __x) ;
 extern float hypotf (float __x, float __y) ; extern float __hypotf (float __x, float __y) ;
 extern float cbrtf (float __x) ; extern float __cbrtf (float __x) ;
extern float ceilf (float __x) ; extern float __ceilf (float __x) ;
extern float fabsf (float __x) ; extern float __fabsf (float __x) ;
extern float floorf (float __x) ; extern float __floorf (float __x) ;
extern float fmodf (float __x, float __y) ; extern float __fmodf (float __x, float __y) ;
extern int isinff (float __value) 
  ;
extern int finitef (float __value) 
  ;
extern float dremf (float __x, float __y) ; extern float __dremf (float __x, float __y) ;
extern float significandf (float __x) ; extern float __significandf (float __x) ;
extern float copysignf (float __x, float __y) ; extern float __copysignf (float __x, float __y) ;
extern float nanf (const char *__tagb) ; extern float __nanf (const char *__tagb) ;
extern int isnanf (float __value) 
  ;
extern float j0f (float) ; extern float __j0f (float) ;
extern float j1f (float) ; extern float __j1f (float) ;
extern float jnf (int, float) ; extern float __jnf (int, float) ;
extern float y0f (float) ; extern float __y0f (float) ;
extern float y1f (float) ; extern float __y1f (float) ;
extern float ynf (int, float) ; extern float __ynf (int, float) ;
 extern float erff (float) ; extern float __erff (float) ;
 extern float erfcf (float) ; extern float __erfcf (float) ;
extern float lgammaf (float) ; extern float __lgammaf (float) ;
extern float tgammaf (float) ; extern float __tgammaf (float) ;
extern float gammaf (float) ; extern float __gammaf (float) ;
extern float lgammaf_r (float, int *__signgamp) ; extern float __lgammaf_r (float, int *__signgamp) ;
extern float rintf (float __x) ; extern float __rintf (float __x) ;
extern float nextafterf (float __x, float __y) ; extern float __nextafterf (float __x, float __y) ;
extern float nexttowardf (float __x, long double __y) ; extern float __nexttowardf (float __x, long double __y) ;
extern float remainderf (float __x, float __y) ; extern float __remainderf (float __x, float __y) ;
extern float scalbnf (float __x, int __n) ; extern float __scalbnf (float __x, int __n) ;
extern int ilogbf (float __x) ; extern int __ilogbf (float __x) ;
extern float scalblnf (float __x, long int __n) ; extern float __scalblnf (float __x, long int __n) ;
extern float nearbyintf (float __x) ; extern float __nearbyintf (float __x) ;
extern float roundf (float __x) ; extern float __roundf (float __x) ;
extern float truncf (float __x) ; extern float __truncf (float __x) ;
extern float remquof (float __x, float __y, int *__quo) ; extern float __remquof (float __x, float __y, int *__quo) ;
extern long int lrintf (float __x) ; extern long int __lrintf (float __x) ;

extern long long int llrintf (float __x) ; extern long long int __llrintf (float __x) ;
extern long int lroundf (float __x) ; extern long int __lroundf (float __x) ;

extern long long int llroundf (float __x) ; extern long long int __llroundf (float __x) ;
extern float fdimf (float __x, float __y) ; extern float __fdimf (float __x, float __y) ;
extern float fmaxf (float __x, float __y) ; extern float __fmaxf (float __x, float __y) ;
extern float fminf (float __x, float __y) ; extern float __fminf (float __x, float __y) ;
extern float fmaf (float __x, float __y, float __z) ; extern float __fmaf (float __x, float __y, float __z) ;
extern float scalbf (float __x, float __n) ; extern float __scalbf (float __x, float __n) ;
extern int __fpclassifyl (long double __value) 
     ;
extern int __signbitl (long double __value) 
     ;
extern int __isinfl (long double __value) 
  ;
extern int __finitel (long double __value) 
  ;
extern int __isnanl (long double __value) 
  ;
extern int __iseqsigl (long double __x, long double __y) ;
extern int __issignalingl (long double __value) 
     ;
 extern long double acosl (long double __x) ; extern long double __acosl (long double __x) ;
 extern long double asinl (long double __x) ; extern long double __asinl (long double __x) ;
 extern long double atanl (long double __x) ; extern long double __atanl (long double __x) ;
 extern long double atan2l (long double __y, long double __x) ; extern long double __atan2l (long double __y, long double __x) ;
 extern long double cosl (long double __x) ; extern long double __cosl (long double __x) ;
 extern long double sinl (long double __x) ; extern long double __sinl (long double __x) ;
 extern long double tanl (long double __x) ; extern long double __tanl (long double __x) ;
 extern long double coshl (long double __x) ; extern long double __coshl (long double __x) ;
 extern long double sinhl (long double __x) ; extern long double __sinhl (long double __x) ;
 extern long double tanhl (long double __x) ; extern long double __tanhl (long double __x) ;
 extern long double acoshl (long double __x) ; extern long double __acoshl (long double __x) ;
 extern long double asinhl (long double __x) ; extern long double __asinhl (long double __x) ;
 extern long double atanhl (long double __x) ; extern long double __atanhl (long double __x) ;
 extern long double expl (long double __x) ; extern long double __expl (long double __x) ;
extern long double frexpl (long double __x, int *__exponent) ; extern long double __frexpl (long double __x, int *__exponent) ;
extern long double ldexpl (long double __x, int __exponent) ; extern long double __ldexpl (long double __x, int __exponent) ;
 extern long double logl (long double __x) ; extern long double __logl (long double __x) ;
 extern long double log10l (long double __x) ; extern long double __log10l (long double __x) ;
extern long double modfl (long double __x, long double *__iptr) ; extern long double __modfl (long double __x, long double *__iptr) ;
 extern long double expm1l (long double __x) ; extern long double __expm1l (long double __x) ;
 extern long double log1pl (long double __x) ; extern long double __log1pl (long double __x) ;
extern long double logbl (long double __x) ; extern long double __logbl (long double __x) ;
 extern long double exp2l (long double __x) ; extern long double __exp2l (long double __x) ;
 extern long double log2l (long double __x) ; extern long double __log2l (long double __x) ;
 extern long double powl (long double __x, long double __y) ; extern long double __powl (long double __x, long double __y) ;
extern long double sqrtl (long double __x) ; extern long double __sqrtl (long double __x) ;
 extern long double hypotl (long double __x, long double __y) ; extern long double __hypotl (long double __x, long double __y) ;
 extern long double cbrtl (long double __x) ; extern long double __cbrtl (long double __x) ;
extern long double ceill (long double __x) ; extern long double __ceill (long double __x) ;
extern long double fabsl (long double __x) ; extern long double __fabsl (long double __x) ;
extern long double floorl (long double __x) ; extern long double __floorl (long double __x) ;
extern long double fmodl (long double __x, long double __y) ; extern long double __fmodl (long double __x, long double __y) ;
extern int isinfl (long double __value) 
  ;
extern int finitel (long double __value) 
  ;
extern long double dreml (long double __x, long double __y) ; extern long double __dreml (long double __x, long double __y) ;
extern long double significandl (long double __x) ; extern long double __significandl (long double __x) ;
extern long double copysignl (long double __x, long double __y) ; extern long double __copysignl (long double __x, long double __y) ;
extern long double nanl (const char *__tagb) ; extern long double __nanl (const char *__tagb) ;
extern int isnanl (long double __value) 
  ;
extern long double j0l (long double) ; extern long double __j0l (long double) ;
extern long double j1l (long double) ; extern long double __j1l (long double) ;
extern long double jnl (int, long double) ; extern long double __jnl (int, long double) ;
extern long double y0l (long double) ; extern long double __y0l (long double) ;
extern long double y1l (long double) ; extern long double __y1l (long double) ;
extern long double ynl (int, long double) ; extern long double __ynl (int, long double) ;
 extern long double erfl (long double) ; extern long double __erfl (long double) ;
 extern long double erfcl (long double) ; extern long double __erfcl (long double) ;
extern long double lgammal (long double) ; extern long double __lgammal (long double) ;
extern long double tgammal (long double) ; extern long double __tgammal (long double) ;
extern long double gammal (long double) ; extern long double __gammal (long double) ;
extern long double lgammal_r (long double, int *__signgamp) ; extern long double __lgammal_r (long double, int *__signgamp) ;
extern long double rintl (long double __x) ; extern long double __rintl (long double __x) ;
extern long double nextafterl (long double __x, long double __y) ; extern long double __nextafterl (long double __x, long double __y) ;
extern long double nexttowardl (long double __x, long double __y) ; extern long double __nexttowardl (long double __x, long double __y) ;
extern long double remainderl (long double __x, long double __y) ; extern long double __remainderl (long double __x, long double __y) ;
extern long double scalbnl (long double __x, int __n) ; extern long double __scalbnl (long double __x, int __n) ;
extern int ilogbl (long double __x) ; extern int __ilogbl (long double __x) ;
extern long double scalblnl (long double __x, long int __n) ; extern long double __scalblnl (long double __x, long int __n) ;
extern long double nearbyintl (long double __x) ; extern long double __nearbyintl (long double __x) ;
extern long double roundl (long double __x) ; extern long double __roundl (long double __x) ;
extern long double truncl (long double __x) ; extern long double __truncl (long double __x) ;
extern long double remquol (long double __x, long double __y, int *__quo) ; extern long double __remquol (long double __x, long double __y, int *__quo) ;
extern long int lrintl (long double __x) ; extern long int __lrintl (long double __x) ;

extern long long int llrintl (long double __x) ; extern long long int __llrintl (long double __x) ;
extern long int lroundl (long double __x) ; extern long int __lroundl (long double __x) ;

extern long long int llroundl (long double __x) ; extern long long int __llroundl (long double __x) ;
extern long double fdiml (long double __x, long double __y) ; extern long double __fdiml (long double __x, long double __y) ;
extern long double fmaxl (long double __x, long double __y) ; extern long double __fmaxl (long double __x, long double __y) ;
extern long double fminl (long double __x, long double __y) ; extern long double __fminl (long double __x, long double __y) ;
extern long double fmal (long double __x, long double __y, long double __z) ; extern long double __fmal (long double __x, long double __y, long double __z) ;
extern long double scalbl (long double __x, long double __n) ; extern long double __scalbl (long double __x, long double __n) ;
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


extern void *memcpy (void * restrict __dest, const void * restrict __src,
       size_t __n) ;
extern void *memmove (void *__dest, const void *__src, size_t __n)
      ;
extern void *memccpy (void * restrict __dest, const void * restrict __src,
        int __c, size_t __n)
     ;
extern void *memset (void *__s, int __c, size_t __n) ;
extern int memcmp (const void *__s1, const void *__s2, size_t __n)
      ;
extern int __memcmpeq (const void *__s1, const void *__s2, size_t __n)
      ;
extern void *memchr (const void *__s, int __c, size_t __n)
       ;
extern char *strcpy (char * restrict __dest, const char * restrict __src)
      ;
extern char *strncpy (char * restrict __dest,
        const char * restrict __src, size_t __n)
      ;
extern char *strcat (char * restrict __dest, const char * restrict __src)
      ;
extern char *strncat (char * restrict __dest, const char * restrict __src,
        size_t __n) ;
extern int strcmp (const char *__s1, const char *__s2)
      ;
extern int strncmp (const char *__s1, const char *__s2, size_t __n)
      ;
extern int strcoll (const char *__s1, const char *__s2)
      ;
extern size_t strxfrm (char * restrict __dest,
         const char * restrict __src, size_t __n)
     ;
struct __locale_struct
{
  struct __locale_data *__locales[13];
  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;
  const char *__names[13];
};
typedef struct __locale_struct *__locale_t;
typedef __locale_t locale_t;
extern int strcoll_l (const char *__s1, const char *__s2, locale_t __l)
      ;
extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    locale_t __l) 
      ;
extern char *strdup (const char *__s)
      ;
extern char *strndup (const char *__string, size_t __n)
      ;
extern char *strchr (const char *__s, int __c)
      ;
extern char *strrchr (const char *__s, int __c)
      ;
extern char *strchrnul (const char *__s, int __c)
      ;
extern size_t strcspn (const char *__s, const char *__reject)
      ;
extern size_t strspn (const char *__s, const char *__accept)
      ;
extern char *strpbrk (const char *__s, const char *__accept)
      ;
extern char *strstr (const char *__haystack, const char *__needle)
      ;
extern char *strtok (char * restrict __s, const char * restrict __delim)
      ;
extern char *__strtok_r (char * restrict __s,
    const char * restrict __delim,
    char ** restrict __save_ptr)
      ;
extern char *strtok_r (char * restrict __s, const char * restrict __delim,
         char ** restrict __save_ptr)
      ;
extern char *strcasestr (const char *__haystack, const char *__needle)
      ;
extern void *memmem (const void *__haystack, size_t __haystacklen,
       const void *__needle, size_t __needlelen)
      
    
    ;
extern void *__mempcpy (void * restrict __dest,
   const void * restrict __src, size_t __n)
      ;
extern void *mempcpy (void * restrict __dest,
        const void * restrict __src, size_t __n)
      ;
extern size_t strlen (const char *__s)
      ;
extern size_t strnlen (const char *__string, size_t __maxlen)
      ;
extern char *strerror (int __errnum) ;
extern int strerror_r (int __errnum, char *__buf, size_t __buflen) 
    ;
extern char *strerror_l (int __errnum, locale_t __l) ;

extern int bcmp (const void *__s1, const void *__s2, size_t __n)
      ;
extern void bcopy (const void *__src, void *__dest, size_t __n)
   ;
extern void bzero (void *__s, size_t __n) ;
extern char *index (const char *__s, int __c)
      ;
extern char *rindex (const char *__s, int __c)
      ;
extern int ffs (int __i) ;
extern int ffsl (long int __l) ;
extern int ffsll (long long int __ll)
      ;
extern int strcasecmp (const char *__s1, const char *__s2)
      ;
extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
      ;
extern int strcasecmp_l (const char *__s1, const char *__s2, locale_t __loc)
      ;
extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, locale_t __loc)
      ;

extern void explicit_bzero (void *__s, size_t __n) 
    ;
extern char *strsep (char ** restrict __stringp,
       const char * restrict __delim)
      ;
extern char *strsignal (int __sig) ;
extern char *__stpcpy (char * restrict __dest, const char * restrict __src)
      ;
extern char *stpcpy (char * restrict __dest, const char * restrict __src)
      ;
extern char *__stpncpy (char * restrict __dest,
   const char * restrict __src, size_t __n)
      ;
extern char *stpncpy (char * restrict __dest,
        const char * restrict __src, size_t __n)
      ;
extern size_t strlcpy (char * restrict __dest,
         const char * restrict __src, size_t __n)
   ;
extern size_t strlcat (char * restrict __dest,
         const char * restrict __src, size_t __n)
   ;


typedef char * __gnuc_va_list;
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
typedef __ssize_t cookie_read_function_t (void *__cookie, char *__buf,
                                          size_t __nbytes);
typedef __ssize_t cookie_write_function_t (void *__cookie, const char *__buf,
                                           size_t __nbytes);
typedef int cookie_seek_function_t (void *__cookie, __off64_t *__pos, int __w);
typedef int cookie_close_function_t (void *__cookie);
typedef struct _IO_cookie_io_functions_t
{
  cookie_read_function_t *read;
  cookie_write_function_t *write;
  cookie_seek_function_t *seek;
  cookie_close_function_t *close;
} cookie_io_functions_t;
typedef __gnuc_va_list va_list;
typedef __fpos_t fpos_t;
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
extern int remove (const char *__filename) ;
extern int rename (const char *__old, const char *__new) ;
extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) ;
extern int fclose (FILE *__stream) ;
extern FILE *tmpfile (void)
   ;
extern char *tmpnam (char[20]) ;
extern char *tmpnam_r (char __s[20]) ;
extern char *tempnam (const char *__dir, const char *__pfx)
   ;
extern int fflush (FILE *__stream);
extern int fflush_unlocked (FILE *__stream);
extern FILE *fopen (const char * restrict __filename,
      const char * restrict __modes)
   ;
extern FILE *freopen (const char * restrict __filename,
        const char * restrict __modes,
        FILE * restrict __stream) ;
extern FILE *fdopen (int __fd, const char *__modes) 
   ;
extern FILE *fopencookie (void * restrict __magic_cookie,
     const char * restrict __modes,
     cookie_io_functions_t __io_funcs) 
   ;
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
   ;
extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) 
   ;
extern void setbuf (FILE * restrict __stream, char * restrict __buf) 
   ;
extern int setvbuf (FILE * restrict __stream, char * restrict __buf,
      int __modes, size_t __n) ;
extern void setbuffer (FILE * restrict __stream, char * restrict __buf,
         size_t __size) ;
extern void setlinebuf (FILE *__stream) ;
extern int fprintf (FILE * restrict __stream,
      const char * restrict __format, ...) ;
extern int printf (const char * restrict __format, ...);
extern int sprintf (char * restrict __s,
      const char * restrict __format, ...);
extern int vfprintf (FILE * restrict __s, const char * restrict __format,
       __gnuc_va_list __arg) ;
extern int vprintf (const char * restrict __format, __gnuc_va_list __arg);
extern int vsprintf (char * restrict __s, const char * restrict __format,
       __gnuc_va_list __arg);
extern int snprintf (char * restrict __s, size_t __maxlen,
       const char * restrict __format, ...);
extern int vsnprintf (char * restrict __s, size_t __maxlen,
        const char * restrict __format, __gnuc_va_list __arg);
extern int vasprintf (char ** restrict __ptr, const char * restrict __f,
        __gnuc_va_list __arg);
extern int __asprintf (char ** restrict __ptr,
         const char * restrict __fmt, ...);
extern int asprintf (char ** restrict __ptr,
       const char * restrict __fmt, ...);
extern int vdprintf (int __fd, const char * restrict __fmt,
       __gnuc_va_list __arg);
extern int dprintf (int __fd, const char * restrict __fmt, ...);
extern int fscanf (FILE * restrict __stream,
     const char * restrict __format, ...) ;
extern int scanf (const char * restrict __format, ...) ;
extern int sscanf (const char * restrict __s,
     const char * restrict __format, ...) ;
extern int fscanf (FILE * restrict __stream, const char * restrict __format, ...) ;
extern int scanf (const char * restrict __format, ...) ;
extern int sscanf (const char * restrict __s, const char * restrict __format, ...) ;
extern int vfscanf (FILE * restrict __s, const char * restrict __format,
      __gnuc_va_list __arg);
extern int vscanf (const char * restrict __format, __gnuc_va_list __arg);
extern int vsscanf (const char * restrict __s,
      const char * restrict __format, __gnuc_va_list __arg);
extern int vfscanf (FILE * restrict __s, const char * restrict __format, __gnuc_va_list __arg);
extern int vscanf (const char * restrict __format, __gnuc_va_list __arg);
extern int vsscanf (const char * restrict __s, const char * restrict __format, __gnuc_va_list __arg);
extern int fgetc (FILE *__stream) ;
extern int getc (FILE *__stream) ;
extern int getchar (void);
extern int getc_unlocked (FILE *__stream) ;
extern int getchar_unlocked (void);
extern int fgetc_unlocked (FILE *__stream) ;
extern int fputc (int __c, FILE *__stream) ;
extern int putc (int __c, FILE *__stream) ;
extern int putchar (int __c);
extern int fputc_unlocked (int __c, FILE *__stream) ;
extern int putc_unlocked (int __c, FILE *__stream) ;
extern int putchar_unlocked (int __c);
extern int getw (FILE *__stream) ;
extern int putw (int __w, FILE *__stream) ;
extern char *fgets (char * restrict __s, int __n, FILE * restrict __stream);
extern __ssize_t __getdelim (char ** restrict __lineptr,
                             size_t * restrict __n, int __delimiter,
                             FILE * restrict __stream) ;
extern __ssize_t getdelim (char ** restrict __lineptr,
                           size_t * restrict __n, int __delimiter,
                           FILE * restrict __stream) ;
extern __ssize_t getline (char ** restrict __lineptr,
                          size_t * restrict __n,
                          FILE * restrict __stream) ;
extern int fputs (const char * restrict __s, FILE * restrict __stream);
extern int puts (const char *__s);
extern int ungetc (int __c, FILE *__stream) ;
extern size_t fread (void * restrict __ptr, size_t __size,
       size_t __n, FILE * restrict __stream);
extern size_t fwrite (const void * restrict __ptr, size_t __size,
        size_t __n, FILE * restrict __s) ;
extern size_t fread_unlocked (void * restrict __ptr, size_t __size,
         size_t __n, FILE * restrict __stream);
extern size_t fwrite_unlocked (const void * restrict __ptr, size_t __size,
          size_t __n, FILE * restrict __stream);
extern int fseek (FILE *__stream, long int __off, int __whence);
extern long int ftell (FILE *__stream) ;
extern void rewind (FILE *__stream) ;
extern int fseeko (FILE *__stream, __off_t __off, int __whence);
extern __off_t ftello (FILE *__stream) ;
extern int fgetpos (FILE * restrict __stream, fpos_t * restrict __pos);
extern int fsetpos (FILE *__stream, const fpos_t *__pos) ;
extern void clearerr (FILE *__stream) ;
extern int feof (FILE *__stream) ;
extern int ferror (FILE *__stream) ;
extern void clearerr_unlocked (FILE *__stream) ;
extern int feof_unlocked (FILE *__stream) ;
extern int ferror_unlocked (FILE *__stream) ;
extern void perror (const char *__s) ;
extern int fileno (FILE *__stream) ;
extern int fileno_unlocked (FILE *__stream) ;
extern int pclose (FILE *__stream) ;
extern FILE *popen (const char *__command, const char *__modes)
   ;
extern char *ctermid (char *__s) ;
extern void flockfile (FILE *__stream) ;
extern int ftrylockfile (FILE *__stream) ;
extern void funlockfile (FILE *__stream) ;
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);


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
      ;
extern const __int32_t **__ctype_tolower_loc (void)
      ;
extern const __int32_t **__ctype_toupper_loc (void)
      ;
extern int isalnum (int) ;
extern int isalpha (int) ;
extern int iscntrl (int) ;
extern int isdigit (int) ;
extern int islower (int) ;
extern int isgraph (int) ;
extern int isprint (int) ;
extern int ispunct (int) ;
extern int isspace (int) ;
extern int isupper (int) ;
extern int isxdigit (int) ;
extern int tolower (int __c) ;
extern int toupper (int __c) ;
extern int isblank (int) ;
extern int isascii (int __c) ;
extern int toascii (int __c) ;
extern int _toupper (int) ;
extern int _tolower (int) ;
extern int isalnum_l (int, locale_t) ;
extern int isalpha_l (int, locale_t) ;
extern int iscntrl_l (int, locale_t) ;
extern int isdigit_l (int, locale_t) ;
extern int islower_l (int, locale_t) ;
extern int isgraph_l (int, locale_t) ;
extern int isprint_l (int, locale_t) ;
extern int ispunct_l (int, locale_t) ;
extern int isspace_l (int, locale_t) ;
extern int isupper_l (int, locale_t) ;
extern int isxdigit_l (int, locale_t) ;
extern int isblank_l (int, locale_t) ;
extern int __tolower_l (int __c, locale_t __l) ;
extern int tolower_l (int __c, locale_t __l) ;
extern int __toupper_l (int __c, locale_t __l) ;
extern int toupper_l (int __c, locale_t __l) ;

typedef double (*te_fun2)(double, double);
enum {
    TOK_NULL = TE_CLOSURE7+1, TOK_ERROR, TOK_END, TOK_SEP,
    TOK_OPEN, TOK_CLOSE, TOK_NUMBER, TOK_VARIABLE, TOK_INFIX
};
enum {TE_CONSTANT = 1};
typedef struct state {
    const char *start;
    const char *next;
    int type;
    union {double value; const double *bound; const void *function;};
    void *context;
    const te_variable *lookup;
    int lookup_len;
} state;
static te_expr *new_expr(const int type, const te_expr *parameters[]) {
    const int arity = ( ((type) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((type) & 0x00000007) : 0 );
    const int psize = sizeof(void*) * arity;
    const int size = (sizeof(te_expr) - sizeof(void*)) + psize + ((((type) & TE_CLOSURE0) != 0) ? sizeof(void*) : 0);
    te_expr *ret = malloc(size);
    if ((ret) == ((void *)0)) { ; return ((void *)0); };
    memset(ret, 0, size);
    if (arity && parameters) {
        memcpy(ret->parameters, parameters, psize);
    }
    ret->type = type;
    ret->bound = 0;
    return ret;
}
void te_free_parameters(te_expr *n) {
    if (!n) return;
    switch (((n->type)&0x0000001F)) {
        case TE_FUNCTION7: case TE_CLOSURE7: te_free(n->parameters[6]);
        case TE_FUNCTION6: case TE_CLOSURE6: te_free(n->parameters[5]);
        case TE_FUNCTION5: case TE_CLOSURE5: te_free(n->parameters[4]);
        case TE_FUNCTION4: case TE_CLOSURE4: te_free(n->parameters[3]);
        case TE_FUNCTION3: case TE_CLOSURE3: te_free(n->parameters[2]);
        case TE_FUNCTION2: case TE_CLOSURE2: te_free(n->parameters[1]);
        case TE_FUNCTION1: case TE_CLOSURE1: te_free(n->parameters[0]);
    }
}
void te_free(te_expr *n) {
    if (!n) return;
    te_free_parameters(n);
    free(n);
}
static double pi(void) {return 3.14159265358979323846;}
static double e(void) {return 2.71828182845904523536;}
static double fac(double a) {
    if (a < 0.0)
        return nanf("");
    if (a > (0x7fffffff * 2U + 1U))
        return (1.0/0.0);
    unsigned int ua = (unsigned int)(a);
    unsigned long int result = 1, i;
    for (i = 1; i <= ua; i++) {
        if (i > (0x7fffffffffffffffL * 2UL + 1UL) / result)
            return (1.0/0.0);
        result *= i;
    }
    return (double)result;
}
static double ncr(double n, double r) {
    if (n < 0.0 || r < 0.0 || n < r) return nanf("");
    if (n > (0x7fffffff * 2U + 1U) || r > (0x7fffffff * 2U + 1U)) return (1.0/0.0);
    unsigned long int un = (unsigned int)(n), ur = (unsigned int)(r), i;
    unsigned long int result = 1;
    if (ur > un / 2) ur = un - ur;
    for (i = 1; i <= ur; i++) {
        if (result > (0x7fffffffffffffffL * 2UL + 1UL) / (un - ur + i))
            return (1.0/0.0);
        result *= un - ur + i;
        result /= i;
    }
    return result;
}
static double npr(double n, double r) {return ncr(n, r) * fac(r);}
static const te_variable functions[] = {
    {"abs", fabs, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"acos", acos, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"asin", asin, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"atan", atan, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"atan2", atan2, TE_FUNCTION2 | TE_FLAG_PURE, 0},
    {"ceil", ceil, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"cos", cos, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"cosh", cosh, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"e", e, TE_FUNCTION0 | TE_FLAG_PURE, 0},
    {"exp", exp, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"fac", fac, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"floor", floor, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"ln", log, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"log", log10, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"log10", log10, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"ncr", ncr, TE_FUNCTION2 | TE_FLAG_PURE, 0},
    {"npr", npr, TE_FUNCTION2 | TE_FLAG_PURE, 0},
    {"pi", pi, TE_FUNCTION0 | TE_FLAG_PURE, 0},
    {"pow", pow, TE_FUNCTION2 | TE_FLAG_PURE, 0},
    {"sin", sin, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"sinh", sinh, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"sqrt", sqrt, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"tan", tan, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {"tanh", tanh, TE_FUNCTION1 | TE_FLAG_PURE, 0},
    {0, 0, 0, 0}
};
static const te_variable *find_builtin(const char *name, int len) {
    int imin = 0;
    int imax = sizeof(functions) / sizeof(te_variable) - 2;
    while (imax >= imin) {
        const int i = (imin + ((imax-imin)/2));
        int c = strncmp(name, functions[i].name, len);
        if (!c) c = '\0' - functions[i].name[len];
        if (c == 0) {
            return functions + i;
        } else if (c > 0) {
            imin = i + 1;
        } else {
            imax = i - 1;
        }
    }
    return 0;
}
static const te_variable *find_lookup(const state *s, const char *name, int len) {
    int iters;
    const te_variable *var;
    if (!s->lookup) return 0;
    for (var = s->lookup, iters = s->lookup_len; iters; ++var, --iters) {
        if (strncmp(name, var->name, len) == 0 && var->name[len] == '\0') {
            return var;
        }
    }
    return 0;
}
static double add(double a, double b) {return a + b;}
static double sub(double a, double b) {return a - b;}
static double mul(double a, double b) {return a * b;}
static double divide(double a, double b) {return a / b;}
static double negate(double a) {return -a;}
static double comma(double a, double b) {(void)a; return b;}
void next_token(state *s) {
    s->type = TOK_NULL;
    do {
        if (!*s->next){
            s->type = TOK_END;
            return;
        }
        if ((s->next[0] >= '0' && s->next[0] <= '9') || s->next[0] == '.') {
            s->value = strtod(s->next, (char**)&s->next);
            s->type = TOK_NUMBER;
        } else {
            if (isalpha((unsigned char)s->next[0])) {
                const char *start;
                start = s->next;
                while (isalpha((unsigned char)s->next[0]) || isdigit((unsigned char)s->next[0]) || (s->next[0] == '_')) s->next++;
                const te_variable *var = find_lookup(s, start, s->next - start);
                if (!var) var = find_builtin(start, s->next - start);
                if (!var) {
                    s->type = TOK_ERROR;
                } else {
                    switch(((var->type)&0x0000001F))
                    {
                        case TE_VARIABLE:
                            s->type = TOK_VARIABLE;
                            s->bound = var->address;
                            break;
                        case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:
                        case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
                            s->context = var->context;
                        case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:
                        case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
                            s->type = var->type;
                            s->function = var->address;
                            break;
                    }
                }
            } else {
                switch (s->next++[0]) {
                    case '+': s->type = TOK_INFIX; s->function = add; break;
                    case '-': s->type = TOK_INFIX; s->function = sub; break;
                    case '*': s->type = TOK_INFIX; s->function = mul; break;
                    case '/': s->type = TOK_INFIX; s->function = divide; break;
                    case '^': s->type = TOK_INFIX; s->function = pow; break;
                    case '%': s->type = TOK_INFIX; s->function = fmod; break;
                    case '(': s->type = TOK_OPEN; break;
                    case ')': s->type = TOK_CLOSE; break;
                    case ',': s->type = TOK_SEP; break;
                    case ' ': case '\t': case '\n': case '\r': break;
                    default: s->type = TOK_ERROR; break;
                }
            }
        }
    } while (s->type == TOK_NULL);
}
static te_expr *list(state *s);
static te_expr *expr(state *s);
static te_expr *power(state *s);
static te_expr *base(state *s) {
    te_expr *ret;
    int arity;
    switch (((s->type)&0x0000001F)) {
        case TOK_NUMBER:
            ret = new_expr(TE_CONSTANT, 0);
            if ((ret) == ((void *)0)) { ; return ((void *)0); };
            ret->value = s->value;
            next_token(s);
            break;
        case TOK_VARIABLE:
            ret = new_expr(TE_VARIABLE, 0);
            if ((ret) == ((void *)0)) { ; return ((void *)0); };
            ret->bound = s->bound;
            next_token(s);
            break;
        case TE_FUNCTION0:
        case TE_CLOSURE0:
            ret = new_expr(s->type, 0);
            if ((ret) == ((void *)0)) { ; return ((void *)0); };
            ret->function = s->function;
            if ((((s->type) & TE_CLOSURE0) != 0)) ret->parameters[0] = s->context;
            next_token(s);
            if (s->type == TOK_OPEN) {
                next_token(s);
                if (s->type != TOK_CLOSE) {
                    s->type = TOK_ERROR;
                } else {
                    next_token(s);
                }
            }
            break;
        case TE_FUNCTION1:
        case TE_CLOSURE1:
            ret = new_expr(s->type, 0);
            if ((ret) == ((void *)0)) { ; return ((void *)0); };
            ret->function = s->function;
            if ((((s->type) & TE_CLOSURE0) != 0)) ret->parameters[1] = s->context;
            next_token(s);
            ret->parameters[0] = power(s);
            if ((ret->parameters[0]) == ((void *)0)) { te_free(ret); return ((void *)0); };
            break;
        case TE_FUNCTION2: case TE_FUNCTION3: case TE_FUNCTION4:
        case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
        case TE_CLOSURE2: case TE_CLOSURE3: case TE_CLOSURE4:
        case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
            arity = ( ((s->type) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((s->type) & 0x00000007) : 0 );
            ret = new_expr(s->type, 0);
            if ((ret) == ((void *)0)) { ; return ((void *)0); };
            ret->function = s->function;
            if ((((s->type) & TE_CLOSURE0) != 0)) ret->parameters[arity] = s->context;
            next_token(s);
            if (s->type != TOK_OPEN) {
                s->type = TOK_ERROR;
            } else {
                int i;
                for(i = 0; i < arity; i++) {
                    next_token(s);
                    ret->parameters[i] = expr(s);
                    if ((ret->parameters[i]) == ((void *)0)) { te_free(ret); return ((void *)0); };
                    if(s->type != TOK_SEP) {
                        break;
                    }
                }
                if(s->type != TOK_CLOSE || i != arity - 1) {
                    s->type = TOK_ERROR;
                } else {
                    next_token(s);
                }
            }
            break;
        case TOK_OPEN:
            next_token(s);
            ret = list(s);
            if ((ret) == ((void *)0)) { ; return ((void *)0); };
            if (s->type != TOK_CLOSE) {
                s->type = TOK_ERROR;
            } else {
                next_token(s);
            }
            break;
        default:
            ret = new_expr(0, 0);
            if ((ret) == ((void *)0)) { ; return ((void *)0); };
            s->type = TOK_ERROR;
            ret->value = nanf("");
            break;
    }
    return ret;
}
static te_expr *power(state *s) {
    int sign = 1;
    while (s->type == TOK_INFIX && (s->function == add || s->function == sub)) {
        if (s->function == sub) sign = -sign;
        next_token(s);
    }
    te_expr *ret;
    if (sign == 1) {
        ret = base(s);
    } else {
        te_expr *b = base(s);
        if ((b) == ((void *)0)) { ; return ((void *)0); };
        ret = new_expr((TE_FUNCTION1 | TE_FLAG_PURE), (const te_expr*[]){b});
        if ((ret) == ((void *)0)) { te_free(b); return ((void *)0); };
        ret->function = negate;
    }
    return ret;
}
static te_expr *factor(state *s) {
    te_expr *ret = power(s);
    if ((ret) == ((void *)0)) { ; return ((void *)0); };
    while (s->type == TOK_INFIX && (s->function == pow)) {
        te_fun2 t = s->function;
        next_token(s);
        te_expr *p = power(s);
        if ((p) == ((void *)0)) { te_free(ret); return ((void *)0); };
        te_expr *prev = ret;
        ret = new_expr((TE_FUNCTION2 | TE_FLAG_PURE), (const te_expr*[]){ret, p});
        if ((ret) == ((void *)0)) { te_free(p), te_free(prev); return ((void *)0); };
        ret->function = t;
    }
    return ret;
}
static te_expr *term(state *s) {
    te_expr *ret = factor(s);
    if ((ret) == ((void *)0)) { ; return ((void *)0); };
    while (s->type == TOK_INFIX && (s->function == mul || s->function == divide || s->function == fmod)) {
        te_fun2 t = s->function;
        next_token(s);
        te_expr *f = factor(s);
        if ((f) == ((void *)0)) { te_free(ret); return ((void *)0); };
        te_expr *prev = ret;
        ret = new_expr((TE_FUNCTION2 | TE_FLAG_PURE), (const te_expr*[]){ret, f});
        if ((ret) == ((void *)0)) { te_free(f), te_free(prev); return ((void *)0); };
        ret->function = t;
    }
    return ret;
}
static te_expr *expr(state *s) {
    te_expr *ret = term(s);
    if ((ret) == ((void *)0)) { ; return ((void *)0); };
    while (s->type == TOK_INFIX && (s->function == add || s->function == sub)) {
        te_fun2 t = s->function;
        next_token(s);
        te_expr *te = term(s);
        if ((te) == ((void *)0)) { te_free(ret); return ((void *)0); };
        te_expr *prev = ret;
        ret = new_expr((TE_FUNCTION2 | TE_FLAG_PURE), (const te_expr*[]){ret, te});
        if ((ret) == ((void *)0)) { te_free(te), te_free(prev); return ((void *)0); };
        ret->function = t;
    }
    return ret;
}
static te_expr *list(state *s) {
    te_expr *ret = expr(s);
    if ((ret) == ((void *)0)) { ; return ((void *)0); };
    while (s->type == TOK_SEP) {
        next_token(s);
        te_expr *e = expr(s);
        if ((e) == ((void *)0)) { te_free(ret); return ((void *)0); };
        te_expr *prev = ret;
        ret = new_expr((TE_FUNCTION2 | TE_FLAG_PURE), (const te_expr*[]){ret, e});
        if ((ret) == ((void *)0)) { te_free(e), te_free(prev); return ((void *)0); };
        ret->function = comma;
    }
    return ret;
}
double te_eval(const te_expr *n) {
    if (!n) return nanf("");
    switch(((n->type)&0x0000001F)) {
        case TE_CONSTANT: return n->value;
        case TE_VARIABLE: return *n->bound;
        case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:
        case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
            switch(( ((n->type) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((n->type) & 0x00000007) : 0 )) {
                case 0: return ((double(*)(void))n->function)();
                case 1: return ((double(*)(double))n->function)(te_eval(n->parameters[0]));
                case 2: return ((double(*)(double, double))n->function)(te_eval(n->parameters[0]), te_eval(n->parameters[1]));
                case 3: return ((double(*)(double, double, double))n->function)(te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]));
                case 4: return ((double(*)(double, double, double, double))n->function)(te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]));
                case 5: return ((double(*)(double, double, double, double, double))n->function)(te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]), te_eval(n->parameters[4]));
                case 6: return ((double(*)(double, double, double, double, double, double))n->function)(te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]), te_eval(n->parameters[4]), te_eval(n->parameters[5]));
                case 7: return ((double(*)(double, double, double, double, double, double, double))n->function)(te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]), te_eval(n->parameters[4]), te_eval(n->parameters[5]), te_eval(n->parameters[6]));
                default: return nanf("");
            }
        case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:
        case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
            switch(( ((n->type) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((n->type) & 0x00000007) : 0 )) {
                case 0: return ((double(*)(void*))n->function)(n->parameters[0]);
                case 1: return ((double(*)(void*, double))n->function)(n->parameters[1], te_eval(n->parameters[0]));
                case 2: return ((double(*)(void*, double, double))n->function)(n->parameters[2], te_eval(n->parameters[0]), te_eval(n->parameters[1]));
                case 3: return ((double(*)(void*, double, double, double))n->function)(n->parameters[3], te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]));
                case 4: return ((double(*)(void*, double, double, double, double))n->function)(n->parameters[4], te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]));
                case 5: return ((double(*)(void*, double, double, double, double, double))n->function)(n->parameters[5], te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]), te_eval(n->parameters[4]));
                case 6: return ((double(*)(void*, double, double, double, double, double, double))n->function)(n->parameters[6], te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]), te_eval(n->parameters[4]), te_eval(n->parameters[5]));
                case 7: return ((double(*)(void*, double, double, double, double, double, double, double))n->function)(n->parameters[7], te_eval(n->parameters[0]), te_eval(n->parameters[1]), te_eval(n->parameters[2]), te_eval(n->parameters[3]), te_eval(n->parameters[4]), te_eval(n->parameters[5]), te_eval(n->parameters[6]));
                default: return nanf("");
            }
        default: return nanf("");
    }
}
static void optimize(te_expr *n) {
    if (n->type == TE_CONSTANT) return;
    if (n->type == TE_VARIABLE) return;
    if ((((n->type) & TE_FLAG_PURE) != 0)) {
        const int arity = ( ((n->type) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((n->type) & 0x00000007) : 0 );
        int known = 1;
        int i;
        for (i = 0; i < arity; ++i) {
            optimize(n->parameters[i]);
            if (((te_expr*)(n->parameters[i]))->type != TE_CONSTANT) {
                known = 0;
            }
        }
        if (known) {
            const double value = te_eval(n);
            te_free_parameters(n);
            n->type = TE_CONSTANT;
            n->value = value;
        }
    }
}
te_expr *te_compile(const char *expression, const te_variable *variables, int var_count, int *error) {
    state s;
    s.start = s.next = expression;
    s.lookup = variables;
    s.lookup_len = var_count;
    next_token(&s);
    te_expr *root = list(&s);
    if (root == ((void *)0)) {
        if (error) *error = -1;
        return ((void *)0);
    }
    if (s.type != TOK_END) {
        te_free(root);
        if (error) {
            *error = (s.next - s.start);
            if (*error == 0) *error = 1;
        }
        return 0;
    } else {
        optimize(root);
        if (error) *error = 0;
        return root;
    }
}
double te_interp(const char *expression, int *error) {
    te_expr *n = te_compile(expression, 0, 0, error);
    double ret;
    if (n) {
        ret = te_eval(n);
        te_free(n);
    } else {
        ret = nanf("");
    }
    return ret;
}
static void pn (const te_expr *n, int depth) {
    int i, arity;
    printf("%*s", depth, "");
    switch(((n->type)&0x0000001F)) {
    case TE_CONSTANT: printf("%f\n", n->value); break;
    case TE_VARIABLE: printf("bound %p\n", n->bound); break;
    case TE_FUNCTION0: case TE_FUNCTION1: case TE_FUNCTION2: case TE_FUNCTION3:
    case TE_FUNCTION4: case TE_FUNCTION5: case TE_FUNCTION6: case TE_FUNCTION7:
    case TE_CLOSURE0: case TE_CLOSURE1: case TE_CLOSURE2: case TE_CLOSURE3:
    case TE_CLOSURE4: case TE_CLOSURE5: case TE_CLOSURE6: case TE_CLOSURE7:
         arity = ( ((n->type) & (TE_FUNCTION0 | TE_CLOSURE0)) ? ((n->type) & 0x00000007) : 0 );
         printf("f%d", arity);
         for(i = 0; i < arity; i++) {
             printf(" %p", n->parameters[i]);
         }
         printf("\n");
         for(i = 0; i < arity; i++) {
             pn(n->parameters[i], depth + 1);
         }
         break;
    }
}
void te_print(const te_expr *n) {
    pn(n, 0);
}
