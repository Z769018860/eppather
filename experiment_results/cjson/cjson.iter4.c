typedef long unsigned int size_t;
extern void *memcpy (void *__dest, const void *__src,
       size_t __n);
extern void *memmove (void *__dest, const void *__src, size_t __n);
extern void *memccpy (void *__dest, const void *__src,
        int __c, size_t __n);
extern void *memset (void *__s, int __c, size_t __n);
extern int memcmp (const void *__s1, const void *__s2, size_t __n);
extern int __memcmpeq (const void *__s1, const void *__s2, size_t __n);
extern void *memchr (const void *__s, int __c, size_t __n);
extern char *strcpy (char *__dest, const char *__src);
extern char *strncpy (char *__dest,
        const char *__src, size_t __n);
extern char *strcat (char *__dest, const char *__src);
extern char *strncat (char *__dest, const char *__src,
        size_t __n);
extern int strcmp (const char *__s1, const char *__s2);
extern int strncmp (const char *__s1, const char *__s2, size_t __n);
extern int strcoll (const char *__s1, const char *__s2);
extern size_t strxfrm (char *__dest,
         const char *__src, size_t __n);
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
extern int strcoll_l (const char *__s1, const char *__s2, locale_t __l);
extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    locale_t __l);
extern char *strdup (const char *__s);
extern char *strndup (const char *__string, size_t __n);
extern char *strchr (const char *__s, int __c);
extern char *strrchr (const char *__s, int __c);
extern char *strchrnul (const char *__s, int __c);
extern size_t strcspn (const char *__s, const char *__reject);
extern size_t strspn (const char *__s, const char *__accept);
extern char *strpbrk (const char *__s, const char *__accept);
extern char *strstr (const char *__haystack, const char *__needle);
extern char *strtok (char *__s, const char *__delim);
extern char *__strtok_r (char *__s,
    const char *__delim,
    char **__save_ptr);
extern char *strtok_r (char *__s, const char *__delim,
         char **__save_ptr);
extern char *strcasestr (const char *__haystack, const char *__needle);
extern void *memmem (const void *__haystack, size_t __haystacklen,
       const void *__needle, size_t __needlelen);
extern void *__mempcpy (void *__dest,
   const void *__src, size_t __n);
extern void *mempcpy (void *__dest,
        const void *__src, size_t __n);
extern size_t strlen (const char *__s);
extern size_t strnlen (const char *__string, size_t __maxlen);
extern char *strerror (int __errnum);
extern int strerror_r (int __errnum, char *__buf, size_t __buflen);
extern char *strerror_l (int __errnum, locale_t __l);

extern int bcmp (const void *__s1, const void *__s2, size_t __n);
extern void bcopy (const void *__src, void *__dest, size_t __n);
extern void bzero (void *__s, size_t __n);
extern char *index (const char *__s, int __c);
extern char *rindex (const char *__s, int __c);
extern int ffs (int __i);
extern int ffsl (long int __l);
extern int ffsll (long long int __ll);
extern int strcasecmp (const char *__s1, const char *__s2);
extern int strncasecmp (const char *__s1, const char *__s2, size_t __n);
extern int strcasecmp_l (const char *__s1, const char *__s2, locale_t __loc);
extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, locale_t __loc);

extern void explicit_bzero (void *__s, size_t __n);
extern char *strsep (char **__stringp,
       const char *__delim);
extern char *strsignal (int __sig);
extern char *__stpcpy (char *__dest, const char *__src);
extern char *stpcpy (char *__dest, const char *__src);
extern char *__stpncpy (char *__dest,
   const char *__src, size_t __n);
extern char *stpncpy (char *__dest,
        const char *__src, size_t __n);
extern size_t strlcpy (char *__dest,
         const char *__src, size_t __n);
extern size_t strlcat (char *__dest,
         const char *__src, size_t __n);


typedef void* __gnuc_va_list;
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
typedef __off_t off_t;
typedef __ssize_t ssize_t;
typedef __fpos_t fpos_t;
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
extern int remove (const char *__filename);
extern int rename (const char *__old, const char *__new);
extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new);
extern int fclose (FILE *__stream);
extern FILE *tmpfile (void);
extern char *tmpnam (char __s[20]);
extern char *tmpnam_r (char __s[20]);
extern char *tempnam (const char *__dir, const char *__pfx);
extern int fflush (FILE *__stream);
extern int fflush_unlocked (FILE *__stream);
extern FILE *fopen (const char *__filename,
      const char *__modes);
extern FILE *freopen (const char *__filename,
        const char *__modes,
        FILE *__stream);
extern FILE *fdopen (int __fd, const char *__modes);
extern FILE *fopencookie (void *__magic_cookie,
     const char *__modes,
     cookie_io_functions_t __io_funcs);
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes);
extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc);
extern void setbuf (FILE *__stream, char *__buf);
extern int setvbuf (FILE *__stream, char *__buf,
      int __modes, size_t __n);
extern void setbuffer (FILE *__stream, char *__buf,
         size_t __size);
extern void setlinebuf (FILE *__stream);
extern int fprintf (FILE *__stream,
      const char *__format, ...);
extern int printf (const char *__format, ...);
extern int sprintf (char *__s,
      const char *__format, ...);
extern int vfprintf (FILE *__s, const char *__format,
       __gnuc_va_list __arg);
extern int vprintf (const char *__format, __gnuc_va_list __arg);
extern int vsprintf (char *__s, const char *__format,
       __gnuc_va_list __arg);
extern int snprintf (char *__s, size_t __maxlen,
       const char *__format, ...);
extern int vsnprintf (char *__s, size_t __maxlen,
        const char *__format, __gnuc_va_list __arg);
extern int vasprintf (char **__ptr, const char *__f,
        __gnuc_va_list __arg);
extern int __asprintf (char **__ptr,
         const char *__fmt, ...);
extern int asprintf (char **__ptr,
       const char *__fmt, ...);
extern int vdprintf (int __fd, const char *__fmt,
       __gnuc_va_list __arg);
extern int dprintf (int __fd, const char *__fmt, ...);
extern int fscanf (FILE *__stream,
     const char *__format, ...);
extern int scanf (const char *__format, ...);
extern int sscanf (const char *__s,
     const char *__format, ...);
extern int fscanf (FILE *__stream, const char *__format, ...);
extern int scanf (const char *__format, ...);
extern int sscanf (const char *__s, const char *__format, ...);
extern int vfscanf (FILE *__s, const char *__format,
      __gnuc_va_list __arg);
extern int vscanf (const char *__format, __gnuc_va_list __arg);
extern int vsscanf (const char *__s,
      const char *__format, __gnuc_va_list __arg);
extern int vfscanf (FILE *__s, const char *__format, __gnuc_va_list __arg);
extern int vscanf (const char *__format, __gnuc_va_list __arg);
extern int vsscanf (const char *__s, const char *__format, __gnuc_va_list __arg);
extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);
extern int getchar (void);
extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
extern int fgetc_unlocked (FILE *__stream);
extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);
extern int putchar (int __c);
extern int fputc_unlocked (int __c, FILE *__stream);
extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);
extern int getw (FILE *__stream);
extern int putw (int __w, FILE *__stream);
extern char *fgets (char *__s, int __n, FILE *__stream);
extern __ssize_t __getdelim (char **__lineptr,
                             size_t *__n, int __delimiter,
                             FILE *__stream);
extern __ssize_t getdelim (char **__lineptr,
                           size_t *__n, int __delimiter,
                           FILE *__stream);
extern __ssize_t getline (char **__lineptr,
                          size_t *__n,
                          FILE *__stream);
extern int fputs (const char *__s, FILE *__stream);
extern int puts (const char *__s);
extern int ungetc (int __c, FILE *__stream);
extern size_t fread (void *__ptr, size_t __size,
       size_t __n, FILE *__stream);
extern size_t fwrite (const void *__ptr, size_t __size,
        size_t __n, FILE *__s);
extern size_t fread_unlocked (void *__ptr, size_t __size,
         size_t __n, FILE *__stream);
extern size_t fwrite_unlocked (const void *__ptr, size_t __size,
          size_t __n, FILE *__stream);
extern int fseek (FILE *__stream, long int __off, int __whence);
extern long int ftell (FILE *__stream);
extern void rewind (FILE *__stream);
extern int fseeko (FILE *__stream, __off_t __off, int __whence);
extern __off_t ftello (FILE *__stream);
extern int fgetpos (FILE *__stream, fpos_t *__pos);
extern int fsetpos (FILE *__stream, const fpos_t *__pos);
extern void clearerr (FILE *__stream);
extern int feof (FILE *__stream);
extern int ferror (FILE *__stream);
extern void clearerr_unlocked (FILE *__stream);
extern int feof_unlocked (FILE *__stream);
extern int ferror_unlocked (FILE *__stream);
extern void perror (const char *__s);
extern int fileno (FILE *__stream);
extern int fileno_unlocked (FILE *__stream);
extern int pclose (FILE *__stream);
extern FILE *popen (const char *__command, const char *__modes);
extern char *ctermid (char *__s);
extern void flockfile (FILE *__stream);
extern int ftrylockfile (FILE *__stream);
extern void funlockfile (FILE *__stream);
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);


typedef float float_t;
typedef double double_t;
extern int __fpclassify (double __value);
extern int __signbit (double __value);
extern int __isinf (double __value);
extern int __finite (double __value);
extern int __isnan (double __value);
extern int __iseqsig (double __x, double __y);
extern int __issignaling (double __value);
extern double acos (double __x); extern double __acos (double __x);
extern double asin (double __x); extern double __asin (double __x);
extern double atan (double __x); extern double __atan (double __x);
extern double atan2 (double __y, double __x); extern double __atan2 (double __y, double __x);
extern double cos (double __x); extern double __cos (double __x);
extern double sin (double __x); extern double __sin (double __x);
extern double tan (double __x); extern double __tan (double __x);
extern double cosh (double __x); extern double __cosh (double __x);
extern double sinh (double __x); extern double __sinh (double __x);
extern double tanh (double __x); extern double __tanh (double __x);
extern double acosh (double __x); extern double __acosh (double __x);
extern double asinh (double __x); extern double __asinh (double __x);
extern double atanh (double __x); extern double __atanh (double __x);
extern double exp (double __x); extern double __exp (double __x);
extern double frexp (double __x, int *__exponent); extern double __frexp (double __x, int *__exponent);
extern double ldexp (double __x, int __exponent); extern double __ldexp (double __x, int __exponent);
extern double log (double __x); extern double __log (double __x);
extern double log10 (double __x); extern double __log10 (double __x);
extern double modf (double __x, double *__iptr); extern double __modf (double __x, double *__iptr);
extern double expm1 (double __x); extern double __expm1 (double __x);
extern double log1p (double __x); extern double __log1p (double __x);
extern double logb (double __x); extern double __logb (double __x);
extern double exp2 (double __x); extern double __exp2 (double __x);
extern double log2 (double __x); extern double __log2 (double __x);
extern double pow (double __x, double __y); extern double __pow (double __x, double __y);
extern double sqrt (double __x); extern double __sqrt (double __x);
extern double hypot (double __x, double __y); extern double __hypot (double __x, double __y);
extern double cbrt (double __x); extern double __cbrt (double __x);
extern double ceil (double __x); extern double __ceil (double __x);
extern double fabs (double __x); extern double __fabs (double __x);
extern double floor (double __x); extern double __floor (double __x);
extern double fmod (double __x, double __y); extern double __fmod (double __x, double __y);
extern int isinf (double __value);
extern int finite (double __value);
extern double drem (double __x, double __y); extern double __drem (double __x, double __y);
extern double significand (double __x); extern double __significand (double __x);
extern double copysign (double __x, double __y); extern double __copysign (double __x, double __y);
extern double nan (const char *__tagb); extern double __nan (const char *__tagb);
extern int isnan (double __value);
extern double j0 (double); extern double __j0 (double);
extern double j1 (double); extern double __j1 (double);
extern double jn (int, double); extern double __jn (int, double);
extern double y0 (double); extern double __y0 (double);
extern double y1 (double); extern double __y1 (double);
extern double yn (int, double); extern double __yn (int, double);
extern double erf (double); extern double __erf (double);
extern double erfc (double); extern double __erfc (double);
extern double lgamma (double); extern double __lgamma (double);
extern double tgamma (double); extern double __tgamma (double);
extern double gamma (double); extern double __gamma (double);
extern double lgamma_r (double, int *__signgamp); extern double __lgamma_r (double, int *__signgamp);
extern double rint (double __x); extern double __rint (double __x);
extern double nextafter (double __x, double __y); extern double __nextafter (double __x, double __y);
extern double nexttoward (double __x, long double __y); extern double __nexttoward (double __x, long double __y);
extern double remainder (double __x, double __y); extern double __remainder (double __x, double __y);
extern double scalbn (double __x, int __n); extern double __scalbn (double __x, int __n);
extern int ilogb (double __x); extern int __ilogb (double __x);
extern double scalbln (double __x, long int __n); extern double __scalbln (double __x, long int __n);
extern double nearbyint (double __x); extern double __nearbyint (double __x);
extern double round (double __x); extern double __round (double __x);
extern double trunc (double __x); extern double __trunc (double __x);
extern double remquo (double __x, double __y, int *__quo); extern double __remquo (double __x, double __y, int *__quo);
extern long int lrint (double __x); extern long int __lrint (double __x);
extern long long int llrint (double __x); extern long long int __llrint (double __x);
extern long int lround (double __x); extern long int __lround (double __x);
extern long long int llround (double __x); extern long long int __llround (double __x);
extern double fdim (double __x, double __y); extern double __fdim (double __x, double __y);
extern double fmax (double __x, double __y); extern double __fmax (double __x, double __y);
extern double fmin (double __x, double __y); extern double __fmin (double __x, double __y);
extern double fma (double __x, double __y, double __z); extern double __fma (double __x, double __y, double __z);
extern double scalb (double __x, double __n); extern double __scalb (double __x, double __n);
extern int __fpclassifyf (float __value);
extern int __signbitf (float __value);
extern int __isinff (float __value);
extern int __finitef (float __value);
extern int __isnanf (float __value);
extern int __iseqsigf (float __x, float __y);
extern int __issignalingf (float __value);
extern float acosf (float __x); extern float __acosf (float __x);
extern float asinf (float __x); extern float __asinf (float __x);
extern float atanf (float __x); extern float __atanf (float __x);
extern float atan2f (float __y, float __x); extern float __atan2f (float __y, float __x);
extern float cosf (float __x); extern float __cosf (float __x);
extern float sinf (float __x); extern float __sinf (float __x);
extern float tanf (float __x); extern float __tanf (float __x);
extern float coshf (float __x); extern float __coshf (float __x);
extern float sinhf (float __x); extern float __sinhf (float __x);
extern float tanhf (float __x); extern float __tanhf (float __x);
extern float acoshf (float __x); extern float __acoshf (float __x);
extern float asinhf (float __x); extern float __asinhf (float __x);
extern float atanhf (float __x); extern float __atanhf (float __x);
extern float expf (float __x); extern float __expf (float __x);
extern float frexpf (float __x, int *__exponent); extern float __frexpf (float __x, int *__exponent);
extern float ldexpf (float __x, int __exponent); extern float __ldexpf (float __x, int __exponent);
extern float logf (float __x); extern float __logf (float __x);
extern float log10f (float __x); extern float __log10f (float __x);
extern float modff (float __x, float *__iptr); extern float __modff (float __x, float *__iptr);
extern float expm1f (float __x); extern float __expm1f (float __x);
extern float log1pf (float __x); extern float __log1pf (float __x);
extern float logbf (float __x); extern float __logbf (float __x);
extern float exp2f (float __x); extern float __exp2f (float __x);
extern float log2f (float __x); extern float __log2f (float __x);
extern float powf (float __x, float __y); extern float __powf (float __x, float __y);
extern float sqrtf (float __x); extern float __sqrtf (float __x);
extern float hypotf (float __x, float __y); extern float __hypotf (float __x, float __y);
extern float cbrtf (float __x); extern float __cbrtf (float __x);
extern float ceilf (float __x); extern float __ceilf (float __x);
extern float fabsf (float __x); extern float __fabsf (float __x);
extern float floorf (float __x); extern float __floorf (float __x);
extern float fmodf (float __x, float __y); extern float __fmodf (float __x, float __y);
extern int isinff (float __value);
extern int finitef (float __value);
extern float dremf (float __x, float __y); extern float __dremf (float __x, float __y);
extern float significandf (float __x); extern float __significandf (float __x);
extern float copysignf (float __x, float __y); extern float __copysignf (float __x, float __y);
extern float nanf (const char *__tagb); extern float __nanf (const char *__tagb);
extern int isnanf (float __value);
extern float j0f (float); extern float __j0f (float);
extern float j1f (float); extern float __j1f (float);
extern float jnf (int, float); extern float __jnf (int, float);
extern float y0f (float); extern float __y0f (float);
extern float y1f (float); extern float __y1f (float);
extern float ynf (int, float); extern float __ynf (int, float);
extern float erff (float); extern float __erff (float);
extern float erfcf (float); extern float __erfcf (float);
extern float lgammaf (float); extern float __lgammaf (float);
extern float tgammaf (float); extern float __tgammaf (float);
extern float gammaf (float); extern float __gammaf (float);
extern float lgammaf_r (float, int *__signgamp); extern float __lgammaf_r (float, int *__signgamp);
extern float rintf (float __x); extern float __rintf (float __x);
extern float nextafterf (float __x, float __y); extern float __nextafterf (float __x, float __y);
extern float nexttowardf (float __x, long double __y); extern float __nexttowardf (float __x, long double __y);
extern float remainderf (float __x, float __y); extern float __remainderf (float __x, float __y);
extern float scalbnf (float __x, int __n); extern float __scalbnf (float __x, int __n);
extern int ilogbf (float __x); extern int __ilogbf (float __x);
extern float scalblnf (float __x, long int __n); extern float __scalblnf (float __x, long int __n);
extern float nearbyintf (float __x); extern float __nearbyintf (float __x);
extern float roundf (float __x); extern float __roundf (float __x);
extern float truncf (float __x); extern float __truncf (float __x);
extern float remquof (float __x, float __y, int *__quo); extern float __remquof (float __x, float __y, int *__quo);
extern long int lrintf (float __x); extern long int __lrintf (float __x);
extern long long int llrintf (float __x); extern long long int __llrintf (float __x);
extern long int lroundf (float __x); extern long int __lroundf (float __x);
extern long long int llroundf (float __x); extern long long int __llroundf (float __x);
extern float fdimf (float __x, float __y); extern float __fdimf (float __x, float __y);
extern float fmaxf (float __x, float __y); extern float __fmaxf (float __x, float __y);
extern float fminf (float __x, float __y); extern float __fminf (float __x, float __y);
extern float fmaf (float __x, float __y, float __z); extern float __fmaf (float __x, float __y, float __z);
extern float scalbf (float __x, float __n); extern float __scalbf (float __x, float __n);
extern int __fpclassifyl (long double __value);
extern int __signbitl (long double __value);
extern int __isinfl (long double __value);
extern int __finitel (long double __value);
extern int __isnanl (long double __value);
extern int __iseqsigl (long double __x, long double __y);
extern int __issignalingl (long double __value);
extern long double acosl (long double __x); extern long double __acosl (long double __x);
extern long double asinl (long double __x); extern long double __asinl (long double __x);
extern long double atanl (long double __x); extern long double __atanl (long double __x);
extern long double atan2l (long double __y, long double __x); extern long double __atan2l (long double __y, long double __x);
extern long double cosl (long double __x); extern long double __cosl (long double __x);
extern long double sinl (long double __x); extern long double __sinl (long double __x);
extern long double tanl (long double __x); extern long double __tanl (long double __x);
extern long double coshl (long double __x); extern long double __coshl (long double __x);
extern long double sinhl (long double __x); extern long double __sinhl (long double __x);
extern long double tanhl (long double __x); extern long double __tanhl (long double __x);
extern long double acoshl (long double __x); extern long double __acoshl (long double __x);
extern long double asinhl (long double __x); extern long double __asinhl (long double __x);
extern long double atanhl (long double __x); extern long double __atanhl (long double __x);
extern long double expl (long double __x); extern long double __expl (long double __x);
extern long double frexpl (long double __x, int *__exponent); extern long double __frexpl (long double __x, int *__exponent);
extern long double ldexpl (long double __x, int __exponent); extern long double __ldexpl (long double __x, int __exponent);
extern long double logl (long double __x); extern long double __logl (long double __x);
extern long double log10l (long double __x); extern long double __log10l (long double __x);
extern long double modfl (long double __x, long double *__iptr); extern long double __modfl (long double __x, long double *__iptr);
extern long double expm1l (long double __x); extern long double __expm1l (long double __x);
extern long double log1pl (long double __x); extern long double __log1pl (long double __x);
extern long double logbl (long double __x); extern long double __logbl (long double __x);
extern long double exp2l (long double __x); extern long double __exp2l (long double __x);
extern long double log2l (long double __x); extern long double __log2l (long double __x);
extern long double powl (long double __x, long double __y); extern long double __powl (long double __x, long double __y);
extern long double sqrtl (long double __x); extern long double __sqrtl (long double __x);
extern long double hypotl (long double __x, long double __y); extern long double __hypotl (long double __x, long double __y);
extern long double cbrtl (long double __x); extern long double __cbrtl (long double __x);
extern long double ceill (long double __x); extern long double __ceill (long double __x);
extern long double fabsl (long double __x); extern long double __fabsl (long double __x);
extern long double floorl (long double __x); extern long double __floorl (long double __x);
extern long double fmodl (long double __x, long double __y); extern long double __fmodl (long double __x, long double __y);
extern int isinfl (long double __value);
extern int finitel (long double __value);
extern long double dreml (long double __x, long double __y); extern long double __dreml (long double __x, long double __y);
extern long double significandl (long double __x); extern long double __significandl (long double __x);
extern long double copysignl (long double __x, long double __y); extern long double __copysignl (long double __x, long double __y);
extern long double nanl (const char *__tagb); extern long double __nanl (const char *__tagb);
extern int isnanl (long double __value);
extern long double j0l (long double); extern long double __j0l (long double);
extern long double j1l (long double); extern long double __j1l (long double);
extern long double jnl (int, long double); extern long double __jnl (int, long double);
extern long double y0l (long double); extern long double __y0l (long double);
extern long double y1l (long double); extern long double __y1l (long double);
extern long double ynl (int, long double); extern long double __ynl (int, long double);
extern long double erfl (long double); extern long double __erfl (long double);
extern long double erfcl (long double); extern long double __erfcl (long double);
extern long double lgammal (long double); extern long double __lgammal (long double);
extern long double tgammal (long double); extern long double __tgammal (long double);
extern long double gammal (long double); extern long double __gammal (long double);
extern long double lgammal_r (long double, int *__signgamp); extern long double __lgammal_r (long double, int *__signgamp);
extern long double rintl (long double __x); extern long double __rintl (long double __x);
extern long double nextafterl (long double __x, long double __y); extern long double __nextafterl (long double __x, long double __y);
extern long double nexttowardl (long double __x, long double __y); extern long double __nexttowardl (long double __x, long double __y);
extern long double remainderl (long double __x, long double __y); extern long double __remainderl (long double __x, long double __y);
extern long double scalbnl (long double __x, int __n); extern long double __scalbnl (long double __x, int __n);
extern int ilogbl (long double __x); extern int __ilogbl (long double __x);
extern long double scalblnl (long double __x, long int __n); extern long double __scalblnl (long double __x, long int __n);
extern long double nearbyintl (long double __x); extern long double __nearbyintl (long double __x);
extern long double roundl (long double __x); extern long double __roundl (long double __x);
extern long double truncl (long double __x); extern long double __truncl (long double __x);
extern long double remquol (long double __x, long double __y, int *__quo); extern long double __remquol (long double __x, long double __y, int *__quo);
extern long int lrintl (long double __x); extern long int __lrintl (long double __x);
extern long long int llrintl (long double __x); extern long long int __llrintl (long double __x);
extern long int lroundl (long double __x); extern long int __lroundl (long double __x);
extern long long int llroundl (long double __x); extern long long int __llroundl (long double __x);
extern long double fdiml (long double __x, long double __y); extern long double __fdiml (long double __x, long double __y);
extern long double fmaxl (long double __x, long double __y); extern long double __fmaxl (long double __x, long double __y);
extern long double fminl (long double __x, long double __y); extern long double __fminl (long double __x, long double __y);
extern long double fmal (long double __x, long double __y, long double __z); extern long double __fmal (long double __x, long double __y, long double __z);
extern long double scalbl (long double __x, long double __n); extern long double __scalbl (long double __x, long double __n);
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
extern size_t __ctype_get_mb_cur_max (void);
extern double atof (const char *__nptr);
extern int atoi (const char *__nptr);
extern long int atol (const char *__nptr);
extern long long int atoll (const char *__nptr);
extern double strtod (const char *__nptr,
        char **__endptr);
extern float strtof (const char *__nptr,
       char **__endptr);
extern long double strtold (const char *__nptr,
       char **__endptr);
extern long int strtol (const char *__nptr,
   char **__endptr, int __base);
extern unsigned long int strtoul (const char *__nptr,
      char **__endptr, int __base);
extern long long int strtoq (const char *__nptr,
        char **__endptr, int __base);
extern unsigned long long int strtouq (const char *__nptr,
           char **__endptr, int __base);
extern long long int strtoll (const char *__nptr,
         char **__endptr, int __base);
extern unsigned long long int strtoull (const char *__nptr,
     char **__endptr, int __base);
extern char *l64a (long int __n);
extern long int a64l (const char *__s);

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
typedef __pid_t pid_t;
typedef __id_t id_t;
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
typedef int register_t;
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

extern int select (int __nfds, fd_set *__readfds,
     fd_set *__writefds,
     fd_set *__exceptfds,
     struct timeval *__timeout);
extern int pselect (int __nfds, fd_set *__readfds,
      fd_set *__writefds,
      fd_set *__exceptfds,
      const struct timespec *__timeout,
      const __sigset_t *__sigmask);

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

extern long int random (void);
extern void srandom (unsigned int __seed);
extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen);
extern char *setstate (char *__statebuf);
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
extern int random_r (struct random_data *__buf,
       int32_t *__result);
extern int srandom_r (unsigned int __seed, struct random_data *__buf);
extern int initstate_r (unsigned int __seed, char *__statebuf,
   size_t __statelen,
   struct random_data *__buf);
extern int setstate_r (char *__statebuf,
         struct random_data *__buf);
extern int rand (void);
extern void srand (unsigned int __seed);
extern int rand_r (unsigned int *__seed);
extern double drand48 (void);
extern double erand48 (unsigned short int __xsubi[3]);
extern long int lrand48 (void);
extern long int nrand48 (unsigned short int __xsubi[3]);
extern long int mrand48 (void);
extern long int jrand48 (unsigned short int __xsubi[3]);
extern void srand48 (long int __seedval);
extern unsigned short int *seed48 (unsigned short int __seed16v[3]);
extern void lcong48 (unsigned short int __param[7]);
struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    unsigned long long int __a;
  };
extern int drand48_r (struct drand48_data *__buffer,
        double *__result);
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__buffer,
        double *__result);
extern int lrand48_r (struct drand48_data *__buffer,
        long int *__result);
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__buffer,
        long int *__result);
extern int mrand48_r (struct drand48_data *__buffer,
        long int *__result);
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__buffer,
        long int *__result);
extern int srand48_r (long int __seedval, struct drand48_data *__buffer);
extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer);
extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer);
extern __uint32_t arc4random (void);
extern void arc4random_buf (void *__buf, size_t __size);
extern __uint32_t arc4random_uniform (__uint32_t __upper_bound);
extern void *malloc (size_t __size);
extern void *calloc (size_t __nmemb, size_t __size);
extern void *realloc (void *__ptr, size_t __size);
extern void free (void *__ptr);
extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size);
extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size);
extern void *alloca (size_t __size);
extern void *valloc (size_t __size);
extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size);
extern void *aligned_alloc (size_t __alignment, size_t __size);
extern void abort (void);
extern int atexit (void (*__func) (void));
extern int at_quick_exit (void (*__func) (void));
extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg);
extern void exit (int __status);
extern void quick_exit (int __status);
extern void _Exit (int __status);
extern char *getenv (const char *__name);
extern int putenv (char *__string);
extern int setenv (const char *__name, const char *__value, int __replace);
extern int unsetenv (const char *__name);
extern int clearenv (void);
extern char *mktemp (char *__template);
extern int mkstemp (char *__template);
extern int mkstemps (char *__template, int __suffixlen);
extern char *mkdtemp (char *__template);
extern int system (const char *__command);
extern char *realpath (const char *__name,
         char *__resolved);
typedef int (*__compar_fn_t) (const void *, const void *);
extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar);
extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar);
extern int abs (int __x);
extern long int labs (long int __x);
extern long long int llabs (long long int __x);
extern div_t div (int __numer, int __denom);
extern ldiv_t ldiv (long int __numer, long int __denom);
extern lldiv_t lldiv (long long int __numer,
        long long int __denom);
extern char *ecvt (double __value, int __ndigit, int *__decpt,
     int *__sign);
extern char *fcvt (double __value, int __ndigit, int *__decpt,
     int *__sign);
extern char *gcvt (double __value, int __ndigit, char *__buf);
extern char *qecvt (long double __value, int __ndigit,
      int *__decpt, int *__sign);
extern char *qfcvt (long double __value, int __ndigit,
      int *__decpt, int *__sign);
extern char *qgcvt (long double __value, int __ndigit, char *__buf);
extern int ecvt_r (double __value, int __ndigit, int *__decpt,
     int *__sign, char *__buf,
     size_t __len);
extern int fcvt_r (double __value, int __ndigit, int *__decpt,
     int *__sign, char *__buf,
     size_t __len);
extern int qecvt_r (long double __value, int __ndigit,
      int *__decpt, int *__sign,
      char *__buf, size_t __len);
extern int qfcvt_r (long double __value, int __ndigit,
      int *__decpt, int *__sign,
      char *__buf, size_t __len);
extern int mblen (const char *__s, size_t __n);
extern int mbtowc (wchar_t *__pwc,
     const char *__s, size_t __n);
extern int wctomb (char *__s, wchar_t __wchar);
extern size_t mbstowcs (wchar_t *__pwcs,
   const char *__s, size_t __n);
extern size_t wcstombs (char *__s,
   const wchar_t *__pwcs, size_t __n);
extern int rpmatch (const char *__response);
extern int getsubopt (char **__optionp,
        char *const *__tokens,
        char **__valuep);
extern int getloadavg (double __loadavg[], int __nelem);


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
extern const unsigned short int **__ctype_b_loc (void);
extern const __int32_t **__ctype_tolower_loc (void);
extern const __int32_t **__ctype_toupper_loc (void);
extern int isalnum (int);
extern int isalpha (int);
extern int iscntrl (int);
extern int isdigit (int);
extern int islower (int);
extern int isgraph (int);
extern int isprint (int);
extern int ispunct (int);
extern int isspace (int);
extern int isupper (int);
extern int isxdigit (int);
extern int tolower (int __c);
extern int toupper (int __c);
extern int isblank (int);
extern int isascii (int __c);
extern int toascii (int __c);
extern int _toupper (int);
extern int _tolower (int);
extern int isalnum_l (int, locale_t);
extern int isalpha_l (int, locale_t);
extern int iscntrl_l (int, locale_t);
extern int isdigit_l (int, locale_t);
extern int islower_l (int, locale_t);
extern int isgraph_l (int, locale_t);
extern int isprint_l (int, locale_t);
extern int ispunct_l (int, locale_t);
extern int isspace_l (int, locale_t);
extern int isupper_l (int, locale_t);
extern int isxdigit_l (int, locale_t);
extern int isblank_l (int, locale_t);
extern int __tolower_l (int __c, locale_t __l);
extern int tolower_l (int __c, locale_t __l);
extern int __toupper_l (int __c, locale_t __l);
extern int toupper_l (int __c, locale_t __l);

typedef long int ptrdiff_t;
typedef struct {
  long long __max_align_ll;
  long double __max_align_ld;
} max_align_t;
typedef struct cJSON
{
    struct cJSON *next;
    struct cJSON *prev;
    struct cJSON *child;
    int type;
    char *valuestring;
    int valueint;
    double valuedouble;
    char *string;
} cJSON;
typedef struct cJSON_Hooks
{
      void *( *malloc_fn)(size_t sz);
      void ( *free_fn)(void *ptr);
} cJSON_Hooks;
typedef int cJSON_bool;
const char* cJSON_Version(void);
void cJSON_InitHooks(cJSON_Hooks* hooks);
cJSON * cJSON_Parse(const char *value);
cJSON * cJSON_ParseWithLength(const char *value, size_t buffer_length);
cJSON * cJSON_ParseWithOpts(const char *value, const char **return_parse_end, cJSON_bool require_null_terminated);
cJSON * cJSON_ParseWithLengthOpts(const char *value, size_t buffer_length, const char **return_parse_end, cJSON_bool require_null_terminated);
char * cJSON_Print(const cJSON *item);
char * cJSON_PrintUnformatted(const cJSON *item);
char * cJSON_PrintBuffered(const cJSON *item, int prebuffer, cJSON_bool fmt);
cJSON_bool cJSON_PrintPreallocated(cJSON *item, char *buffer, const int length, const cJSON_bool format);
void cJSON_Delete(cJSON *item);
int cJSON_GetArraySize(const cJSON *array);
cJSON * cJSON_GetArrayItem(const cJSON *array, int index);
cJSON * cJSON_GetObjectItem(const cJSON * const object, const char * const string);
cJSON * cJSON_GetObjectItemCaseSensitive(const cJSON * const object, const char * const string);
cJSON_bool cJSON_HasObjectItem(const cJSON *object, const char *string);
const char * cJSON_GetErrorPtr(void);
char * cJSON_GetStringValue(const cJSON * const item);
double cJSON_GetNumberValue(const cJSON * const item);
cJSON_bool cJSON_IsInvalid(const cJSON * const item);
cJSON_bool cJSON_IsFalse(const cJSON * const item);
cJSON_bool cJSON_IsTrue(const cJSON * const item);
cJSON_bool cJSON_IsBool(const cJSON * const item);
cJSON_bool cJSON_IsNull(const cJSON * const item);
cJSON_bool cJSON_IsNumber(const cJSON * const item);
cJSON_bool cJSON_IsString(const cJSON * const item);
cJSON_bool cJSON_IsArray(const cJSON * const item);
cJSON_bool cJSON_IsObject(const cJSON * const item);
cJSON_bool cJSON_IsRaw(const cJSON * const item);
cJSON * cJSON_CreateNull(void);
cJSON * cJSON_CreateTrue(void);
cJSON * cJSON_CreateFalse(void);
cJSON * cJSON_CreateBool(cJSON_bool boolean);
cJSON * cJSON_CreateNumber(double num);
cJSON * cJSON_CreateString(const char *string);
cJSON * cJSON_CreateRaw(const char *raw);
cJSON * cJSON_CreateArray(void);
cJSON * cJSON_CreateObject(void);
cJSON * cJSON_CreateStringReference(const char *string);
cJSON * cJSON_CreateObjectReference(const cJSON *child);
cJSON * cJSON_CreateArrayReference(const cJSON *child);
cJSON * cJSON_CreateIntArray(const int *numbers, int count);
cJSON * cJSON_CreateFloatArray(const float *numbers, int count);
cJSON * cJSON_CreateDoubleArray(const double *numbers, int count);
cJSON * cJSON_CreateStringArray(const char *const *strings, int count);
cJSON_bool cJSON_AddItemToArray(cJSON *array, cJSON *item);
cJSON_bool cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);
cJSON_bool cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item);
cJSON_bool cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item);
cJSON_bool cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item);
cJSON * cJSON_DetachItemViaPointer(cJSON *parent, cJSON * const item);
cJSON * cJSON_DetachItemFromArray(cJSON *array, int which);
void cJSON_DeleteItemFromArray(cJSON *array, int which);
cJSON * cJSON_DetachItemFromObject(cJSON *object, const char *string);
cJSON * cJSON_DetachItemFromObjectCaseSensitive(cJSON *object, const char *string);
void cJSON_DeleteItemFromObject(cJSON *object, const char *string);
void cJSON_DeleteItemFromObjectCaseSensitive(cJSON *object, const char *string);
cJSON_bool cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem);
cJSON_bool cJSON_ReplaceItemViaPointer(cJSON * const parent, cJSON * const item, cJSON * replacement);
cJSON_bool cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem);
cJSON_bool cJSON_ReplaceItemInObject(cJSON *object,const char *string,cJSON *newitem);
cJSON_bool cJSON_ReplaceItemInObjectCaseSensitive(cJSON *object,const char *string,cJSON *newitem);
cJSON * cJSON_Duplicate(const cJSON *item, cJSON_bool recurse);
cJSON_bool cJSON_Compare(const cJSON * const a, const cJSON * const b, const cJSON_bool case_sensitive);
void cJSON_Minify(char *json);
cJSON* cJSON_AddNullToObject(cJSON * const object, const char * const name);
cJSON* cJSON_AddTrueToObject(cJSON * const object, const char * const name);
cJSON* cJSON_AddFalseToObject(cJSON * const object, const char * const name);
cJSON* cJSON_AddBoolToObject(cJSON * const object, const char * const name, const cJSON_bool boolean);
cJSON* cJSON_AddNumberToObject(cJSON * const object, const char * const name, const double number);
cJSON* cJSON_AddStringToObject(cJSON * const object, const char * const name, const char * const string);
cJSON* cJSON_AddRawToObject(cJSON * const object, const char * const name, const char * const raw);
cJSON* cJSON_AddObjectToObject(cJSON * const object, const char * const name);
cJSON* cJSON_AddArrayToObject(cJSON * const object, const char * const name);
double cJSON_SetNumberHelper(cJSON *object, double number);
char* cJSON_SetValuestring(cJSON *object, const char *valuestring);
void * cJSON_malloc(size_t size);
void cJSON_free(void *object);
typedef struct {
    const unsigned char *json;
    size_t position;
} error;
static error global_error = { ((void *)0), 0 };
const char * cJSON_GetErrorPtr(void)
{
    return (const char*) (global_error.json + global_error.position);
}
char * cJSON_GetStringValue(const cJSON * const item)
{
    if (!cJSON_IsString(item))
    {
        return ((void *)0);
    }
    return item->valuestring;
}
double cJSON_GetNumberValue(const cJSON * const item)
{
    if (!cJSON_IsNumber(item))
    {
        return nan("");
    }
    return item->valuedouble;
}
const char* cJSON_Version(void)
{
    static char version[15];
    sprintf(version, "%i.%i.%i", 1, 7, 19);
    return version;
}
static int case_insensitive_strcmp(const unsigned char *string1, const unsigned char *string2)
{
    if ((string1 == ((void *)0)) || (string2 == ((void *)0)))
    {
        return 1;
    }
    if (string1 == string2)
    {
        return 0;
    }
    for(; tolower(*string1) == tolower(*string2); (void)string1++, string2++)
    {
        if (*string1 == '\0')
        {
            return 0;
        }
    }
    return tolower(*string1) - tolower(*string2);
}
typedef struct internal_hooks
{
    void *( *allocate)(size_t size);
    void ( *deallocate)(void *pointer);
    void *( *reallocate)(void *pointer, size_t size);
} internal_hooks;
static internal_hooks global_hooks = { malloc, free, realloc };
static unsigned char* cJSON_strdup(const unsigned char* string, const internal_hooks * const hooks)
{
    size_t length = 0;
    unsigned char *copy = ((void *)0);
    if (string == ((void *)0))
    {
        return ((void *)0);
    }
    length = strlen((const char*)string) + sizeof("");
    copy = (unsigned char*)hooks->allocate(length);
    if (copy == ((void *)0))
    {
        return ((void *)0);
    }
    memcpy(copy, string, length);
    return copy;
}
void cJSON_InitHooks(cJSON_Hooks* hooks)
{
    if (hooks == ((void *)0))
    {
        global_hooks.allocate = malloc;
        global_hooks.deallocate = free;
        global_hooks.reallocate = realloc;
        return;
    }
    global_hooks.allocate = malloc;
    if (hooks->malloc_fn != ((void *)0))
    {
        global_hooks.allocate = hooks->malloc_fn;
    }
    global_hooks.deallocate = free;
    if (hooks->free_fn != ((void *)0))
    {
        global_hooks.deallocate = hooks->free_fn;
    }
    global_hooks.reallocate = ((void *)0);
    if ((global_hooks.allocate == malloc) && (global_hooks.deallocate == free))
    {
        global_hooks.reallocate = realloc;
    }
}
static cJSON *cJSON_New_Item(const internal_hooks * const hooks)
{
    cJSON* node = (cJSON*)hooks->allocate(sizeof(cJSON));
    if (node)
    {
        memset(node, '\0', sizeof(cJSON));
    }
    return node;
}
void cJSON_Delete(cJSON *item)
{
    cJSON *next = ((void *)0);
    while (item != ((void *)0))
    {
        next = item->next;
        if (!(item->type & 256) && (item->child != ((void *)0)))
        {
            cJSON_Delete(item->child);
        }
        if (!(item->type & 256) && (item->valuestring != ((void *)0)))
        {
            global_hooks.deallocate(item->valuestring);
            item->valuestring = ((void *)0);
        }
        if (!(item->type & 512) && (item->string != ((void *)0)))
        {
            global_hooks.deallocate(item->string);
            item->string = ((void *)0);
        }
        global_hooks.deallocate(item);
        item = next;
    }
}
static unsigned char get_decimal_point(void)
{
    return '.';
}
typedef struct
{
    const unsigned char *content;
    size_t length;
    size_t offset;
    size_t depth;
    internal_hooks hooks;
} parse_buffer;
static cJSON_bool parse_number(cJSON * const item, parse_buffer * const input_buffer)
{
    double number = 0;
    unsigned char *after_end = ((void *)0);
    unsigned char *number_c_string;
    unsigned char decimal_point = get_decimal_point();
    size_t i = 0;
    size_t number_string_length = 0;
    cJSON_bool has_decimal_point = ((cJSON_bool)0);
    if ((input_buffer == ((void *)0)) || (input_buffer->content == ((void *)0)))
    {
        return ((cJSON_bool)0);
    }
    for (i = 0; ((input_buffer != ((void *)0)) && (((input_buffer)->offset + i) < (input_buffer)->length)); i++)
    {
        switch (((input_buffer)->content + (input_buffer)->offset)[i])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '+':
            case '-':
            case 'e':
            case 'E':
                number_string_length++;
                break;
            case '.':
                number_string_length++;
                has_decimal_point = ((cJSON_bool)1);
                break;
            default:
                goto loop_end;
        }
    }
loop_end:
    number_c_string = (unsigned char *) input_buffer->hooks.allocate(number_string_length + 1);
    if (number_c_string == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    memcpy(number_c_string, ((input_buffer)->content + (input_buffer)->offset), number_string_length);
    number_c_string[number_string_length] = '\0';
    if (has_decimal_point)
    {
        for (i = 0; i < number_string_length; i++)
        {
            if (number_c_string[i] == '.')
            {
                number_c_string[i] = decimal_point;
            }
        }
    }
    number = strtod((const char*)number_c_string, (char**)&after_end);
    if (number_c_string == after_end)
    {
        input_buffer->hooks.deallocate(number_c_string);
        return ((cJSON_bool)0);
    }
    item->valuedouble = number;
    if (number >= 0x7fffffff)
    {
        item->valueint = 0x7fffffff;
    }
    else if (number <= (double)(-0x7fffffff - 1))
    {
        item->valueint = (-0x7fffffff - 1);
    }
    else
    {
        item->valueint = (int)number;
    }
    item->type = (1 << 3);
    input_buffer->offset += (size_t)(after_end - number_c_string);
    input_buffer->hooks.deallocate(number_c_string);
    return ((cJSON_bool)1);
}
double cJSON_SetNumberHelper(cJSON *object, double number)
{
    if (object == ((void *)0))
    {
        return nan("");
    }
    if (number >= 0x7fffffff)
    {
        object->valueint = 0x7fffffff;
    }
    else if (number <= (double)(-0x7fffffff - 1))
    {
        object->valueint = (-0x7fffffff - 1);
    }
    else
    {
        object->valueint = (int)number;
    }
    return object->valuedouble = number;
}
char* cJSON_SetValuestring(cJSON *object, const char *valuestring)
{
    char *copy = ((void *)0);
    size_t v1_len;
    size_t v2_len;
    if ((object == ((void *)0)) || !(object->type & (1 << 4)) || (object->type & 256))
    {
        return ((void *)0);
    }
    if (object->valuestring == ((void *)0) || valuestring == ((void *)0))
    {
        return ((void *)0);
    }
    v1_len = strlen(valuestring);
    v2_len = strlen(object->valuestring);
    if (v1_len <= v2_len)
    {
        if (!( valuestring + v1_len < object->valuestring || object->valuestring + v2_len < valuestring ))
        {
            return ((void *)0);
        }
        strcpy(object->valuestring, valuestring);
        return object->valuestring;
    }
    copy = (char*) cJSON_strdup((const unsigned char*)valuestring, &global_hooks);
    if (copy == ((void *)0))
    {
        return ((void *)0);
    }
    if (object->valuestring != ((void *)0))
    {
        cJSON_free(object->valuestring);
    }
    object->valuestring = copy;
    return copy;
}
typedef struct
{
    unsigned char *buffer;
    size_t length;
    size_t offset;
    size_t depth;
    cJSON_bool noalloc;
    cJSON_bool format;
    internal_hooks hooks;
} printbuffer;
static unsigned char* ensure(printbuffer * const p, size_t needed)
{
    unsigned char *newbuffer = ((void *)0);
    size_t newsize = 0;
    if ((p == ((void *)0)) || (p->buffer == ((void *)0)))
    {
        return ((void *)0);
    }
    if ((p->length > 0) && (p->offset >= p->length))
    {
        return ((void *)0);
    }
    if (needed > 0x7fffffff)
    {
        return ((void *)0);
    }
    needed += p->offset + 1;
    if (needed <= p->length)
    {
        return p->buffer + p->offset;
    }
    if (p->noalloc) {
        return ((void *)0);
    }
    if (needed > (0x7fffffff / 2))
    {
        if (needed <= 0x7fffffff)
        {
            newsize = 0x7fffffff;
        }
        else
        {
            return ((void *)0);
        }
    }
    else
    {
        newsize = needed * 2;
    }
    if (p->hooks.reallocate != ((void *)0))
    {
        newbuffer = (unsigned char*)p->hooks.reallocate(p->buffer, newsize);
        if (newbuffer == ((void *)0))
        {
            p->hooks.deallocate(p->buffer);
            p->length = 0;
            p->buffer = ((void *)0);
            return ((void *)0);
        }
    }
    else
    {
        newbuffer = (unsigned char*)p->hooks.allocate(newsize);
        if (!newbuffer)
        {
            p->hooks.deallocate(p->buffer);
            p->length = 0;
            p->buffer = ((void *)0);
            return ((void *)0);
        }
        memcpy(newbuffer, p->buffer, p->offset + 1);
        p->hooks.deallocate(p->buffer);
    }
    p->length = newsize;
    p->buffer = newbuffer;
    return newbuffer + p->offset;
}
static void update_offset(printbuffer * const buffer)
{
    const unsigned char *buffer_pointer = ((void *)0);
    if ((buffer == ((void *)0)) || (buffer->buffer == ((void *)0)))
    {
        return;
    }
    buffer_pointer = buffer->buffer + buffer->offset;
    buffer->offset += strlen((const char*)buffer_pointer);
}
static cJSON_bool compare_double(double a, double b)
{
    double maxVal = fabs(a) > fabs(b) ? fabs(a) : fabs(b);
    return (fabs(a - b) <= maxVal * ((double)2.22044604925031308084726333618164062e-16L));
}
static cJSON_bool print_number(const cJSON * const item, printbuffer * const output_buffer)
{
    unsigned char *output_pointer = ((void *)0);
    double d = item->valuedouble;
    int length = 0;
    size_t i = 0;
    unsigned char number_buffer[26] = {0};
    unsigned char decimal_point = get_decimal_point();
    double test = 0.0;
    if (output_buffer == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    if (isnan(d) || isinf(d))
    {
        length = sprintf((char*)number_buffer, "null");
    }
    else if(d == (double)item->valueint)
    {
        length = sprintf((char*)number_buffer, "%d", item->valueint);
    }
    else
    {
        length = sprintf((char*)number_buffer, "%1.15g", d);
        if ((sscanf((char*)number_buffer, "%lg", &test) != 1) || !compare_double((double)test, d))
        {
            length = sprintf((char*)number_buffer, "%1.17g", d);
        }
    }
    if ((length < 0) || (length > (int)(sizeof(number_buffer) - 1)))
    {
        return ((cJSON_bool)0);
    }
    output_pointer = ensure(output_buffer, (size_t)length + sizeof(""));
    if (output_pointer == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    for (i = 0; i < ((size_t)length); i++)
    {
        if (number_buffer[i] == decimal_point)
        {
            output_pointer[i] = '.';
            continue;
        }
        output_pointer[i] = number_buffer[i];
    }
    output_pointer[i] = '\0';
    output_buffer->offset += (size_t)length;
    return ((cJSON_bool)1);
}
static unsigned parse_hex4(const unsigned char * const input)
{
    unsigned int h = 0;
    size_t i = 0;
    for (i = 0; i < 4; i++)
    {
        if ((input[i] >= '0') && (input[i] <= '9'))
        {
            h += (unsigned int) input[i] - '0';
        }
        else if ((input[i] >= 'A') && (input[i] <= 'F'))
        {
            h += (unsigned int) 10 + input[i] - 'A';
        }
        else if ((input[i] >= 'a') && (input[i] <= 'f'))
        {
            h += (unsigned int) 10 + input[i] - 'a';
        }
        else
        {
            return 0;
        }
        if (i < 3)
        {
            h = h << 4;
        }
    }
    return h;
}
static unsigned char utf16_literal_to_utf8(const unsigned char * const input_pointer, const unsigned char * const input_end, unsigned char **output_pointer)
{
    long unsigned int codepoint = 0;
    unsigned int first_code = 0;
    const unsigned char *first_sequence = input_pointer;
    unsigned char utf8_length = 0;
    unsigned char utf8_position = 0;
    unsigned char sequence_length = 0;
    unsigned char first_byte_mark = 0;
    if ((input_end - first_sequence) < 6)
    {
        goto fail;
    }
    first_code = parse_hex4(first_sequence + 2);
    if (((first_code >= 0xDC00) && (first_code <= 0xDFFF)))
    {
        goto fail;
    }
    if ((first_code >= 0xD800) && (first_code <= 0xDBFF))
    {
        const unsigned char *second_sequence = first_sequence + 6;
        unsigned int second_code = 0;
        sequence_length = 12;
        if ((input_end - second_sequence) < 6)
        {
            goto fail;
        }
        if ((second_sequence[0] != '\\') || (second_sequence[1] != 'u'))
        {
            goto fail;
        }
        second_code = parse_hex4(second_sequence + 2);
        if ((second_code < 0xDC00) || (second_code > 0xDFFF))
        {
            goto fail;
        }
        codepoint = 0x10000 + (((first_code & 0x3FF) << 10) | (second_code & 0x3FF));
    }
    else
    {
        sequence_length = 6;
        codepoint = first_code;
    }
    if (codepoint < 0x80)
    {
        utf8_length = 1;
    }
    else if (codepoint < 0x800)
    {
        utf8_length = 2;
        first_byte_mark = 0xC0;
    }
    else if (codepoint < 0x10000)
    {
        utf8_length = 3;
        first_byte_mark = 0xE0;
    }
    else if (codepoint <= 0x10FFFF)
    {
        utf8_length = 4;
        first_byte_mark = 0xF0;
    }
    else
    {
        goto fail;
    }
    for (utf8_position = (unsigned char)(utf8_length - 1); utf8_position > 0; utf8_position--)
    {
        (*output_pointer)[utf8_position] = (unsigned char)((codepoint | 0x80) & 0xBF);
        codepoint >>= 6;
    }
    if (utf8_length > 1)
    {
        (*output_pointer)[0] = (unsigned char)((codepoint | first_byte_mark) & 0xFF);
    }
    else
    {
        (*output_pointer)[0] = (unsigned char)(codepoint & 0x7F);
    }
    *output_pointer += utf8_length;
    return sequence_length;
fail:
    return 0;
}
static cJSON_bool parse_string(cJSON * const item, parse_buffer * const input_buffer)
{
    const unsigned char *input_pointer = ((input_buffer)->content + (input_buffer)->offset) + 1;
    const unsigned char *input_end = ((input_buffer)->content + (input_buffer)->offset) + 1;
    unsigned char *output_pointer = ((void *)0);
    unsigned char *output = ((void *)0);
    if (((input_buffer)->content + (input_buffer)->offset)[0] != '\"')
    {
        goto fail;
    }
    {
        size_t allocation_length = 0;
        size_t skipped_bytes = 0;
        while (((size_t)(input_end - input_buffer->content) < input_buffer->length) && (*input_end != '\"'))
        {
            if (input_end[0] == '\\')
            {
                if ((size_t)(input_end + 1 - input_buffer->content) >= input_buffer->length)
                {
                    goto fail;
                }
                skipped_bytes++;
                input_end++;
            }
            input_end++;
        }
        if (((size_t)(input_end - input_buffer->content) >= input_buffer->length) || (*input_end != '\"'))
        {
            goto fail;
        }
        allocation_length = (size_t) (input_end - ((input_buffer)->content + (input_buffer)->offset)) - skipped_bytes;
        output = (unsigned char*)input_buffer->hooks.allocate(allocation_length + sizeof(""));
        if (output == ((void *)0))
        {
            goto fail;
        }
    }
    output_pointer = output;
    while (input_pointer < input_end)
    {
        if (*input_pointer != '\\')
        {
            *output_pointer++ = *input_pointer++;
        }
        else
        {
            unsigned char sequence_length = 2;
            if ((input_end - input_pointer) < 1)
            {
                goto fail;
            }
            switch (input_pointer[1])
            {
                case 'b':
                    *output_pointer++ = '\b';
                    break;
                case 'f':
                    *output_pointer++ = '\f';
                    break;
                case 'n':
                    *output_pointer++ = '\n';
                    break;
                case 'r':
                    *output_pointer++ = '\r';
                    break;
                case 't':
                    *output_pointer++ = '\t';
                    break;
                case '\"':
                case '\\':
                case '/':
                    *output_pointer++ = input_pointer[1];
                    break;
                case 'u':
                    sequence_length = utf16_literal_to_utf8(input_pointer, input_end, &output_pointer);
                    if (sequence_length == 0)
                    {
                        goto fail;
                    }
                    break;
                default:
                    goto fail;
            }
            input_pointer += sequence_length;
        }
    }
    *output_pointer = '\0';
    item->type = (1 << 4);
    item->valuestring = (char*)output;
    input_buffer->offset = (size_t) (input_end - input_buffer->content);
    input_buffer->offset++;
    return ((cJSON_bool)1);
fail:
    if (output != ((void *)0))
    {
        input_buffer->hooks.deallocate(output);
        output = ((void *)0);
    }
    if (input_pointer != ((void *)0))
    {
        input_buffer->offset = (size_t)(input_pointer - input_buffer->content);
    }
    return ((cJSON_bool)0);
}
static cJSON_bool print_string_ptr(const unsigned char * const input, printbuffer * const output_buffer)
{
    const unsigned char *input_pointer = ((void *)0);
    unsigned char *output = ((void *)0);
    unsigned char *output_pointer = ((void *)0);
    size_t output_length = 0;
    size_t escape_characters = 0;
    if (output_buffer == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    if (input == ((void *)0))
    {
        output = ensure(output_buffer, sizeof("\"\""));
        if (output == ((void *)0))
        {
            return ((cJSON_bool)0);
        }
        strcpy((char*)output, "\"\"");
        return ((cJSON_bool)1);
    }
    for (input_pointer = input; *input_pointer; input_pointer++)
    {
        switch (*input_pointer)
        {
            case '\"':
            case '\\':
            case '\b':
            case '\f':
            case '\n':
            case '\r':
            case '\t':
                escape_characters++;
                break;
            default:
                if (*input_pointer < 32)
                {
                    escape_characters += 5;
                }
                break;
        }
    }
    output_length = (size_t)(input_pointer - input) + escape_characters;
    output = ensure(output_buffer, output_length + sizeof("\"\""));
    if (output == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    if (escape_characters == 0)
    {
        output[0] = '\"';
        memcpy(output + 1, input, output_length);
        output[output_length + 1] = '\"';
        output[output_length + 2] = '\0';
        return ((cJSON_bool)1);
    }
    output[0] = '\"';
    output_pointer = output + 1;
    for (input_pointer = input; *input_pointer != '\0'; (void)input_pointer++, output_pointer++)
    {
        if ((*input_pointer > 31) && (*input_pointer != '\"') && (*input_pointer != '\\'))
        {
            *output_pointer = *input_pointer;
        }
        else
        {
            *output_pointer++ = '\\';
            switch (*input_pointer)
            {
                case '\\':
                    *output_pointer = '\\';
                    break;
                case '\"':
                    *output_pointer = '\"';
                    break;
                case '\b':
                    *output_pointer = 'b';
                    break;
                case '\f':
                    *output_pointer = 'f';
                    break;
                case '\n':
                    *output_pointer = 'n';
                    break;
                case '\r':
                    *output_pointer = 'r';
                    break;
                case '\t':
                    *output_pointer = 't';
                    break;
                default:
                    sprintf((char*)output_pointer, "u%04x", *input_pointer);
                    output_pointer += 4;
                    break;
            }
        }
    }
    output[output_length + 1] = '\"';
    output[output_length + 2] = '\0';
    return ((cJSON_bool)1);
}
static cJSON_bool print_string(const cJSON * const item, printbuffer * const p)
{
    return print_string_ptr((unsigned char*)item->valuestring, p);
}
static cJSON_bool parse_value(cJSON * const item, parse_buffer * const input_buffer);
static cJSON_bool print_value(const cJSON * const item, printbuffer * const output_buffer);
static cJSON_bool parse_array(cJSON * const item, parse_buffer * const input_buffer);
static cJSON_bool print_array(const cJSON * const item, printbuffer * const output_buffer);
static cJSON_bool parse_object(cJSON * const item, parse_buffer * const input_buffer);
static cJSON_bool print_object(const cJSON * const item, printbuffer * const output_buffer);
static parse_buffer *buffer_skip_whitespace(parse_buffer * const buffer)
{
    if ((buffer == ((void *)0)) || (buffer->content == ((void *)0)))
    {
        return ((void *)0);
    }
    if ((!((buffer != ((void *)0)) && (((buffer)->offset + 0) < (buffer)->length))))
    {
        return buffer;
    }
    while (((buffer != ((void *)0)) && (((buffer)->offset + 0) < (buffer)->length)) && (((buffer)->content + (buffer)->offset)[0] <= 32))
    {
       buffer->offset++;
    }
    if (buffer->offset == buffer->length)
    {
        buffer->offset--;
    }
    return buffer;
}
static parse_buffer *skip_utf8_bom(parse_buffer * const buffer)
{
    if ((buffer == ((void *)0)) || (buffer->content == ((void *)0)) || (buffer->offset != 0))
    {
        return ((void *)0);
    }
    if (((buffer != ((void *)0)) && (((buffer)->offset + 4) < (buffer)->length)) && (strncmp((const char*)((buffer)->content + (buffer)->offset), "\xEF\xBB\xBF", 3) == 0))
    {
        buffer->offset += 3;
    }
    return buffer;
}
cJSON * cJSON_ParseWithOpts(const char *value, const char **return_parse_end, cJSON_bool require_null_terminated)
{
    size_t buffer_length;
    if (((void *)0) == value)
    {
        return ((void *)0);
    }
    buffer_length = strlen(value) + sizeof("");
    return cJSON_ParseWithLengthOpts(value, buffer_length, return_parse_end, require_null_terminated);
}
cJSON * cJSON_ParseWithLengthOpts(const char *value, size_t buffer_length, const char **return_parse_end, cJSON_bool require_null_terminated)
{
    parse_buffer buffer = { 0, 0, 0, 0, { 0, 0, 0 } };
    cJSON *item = ((void *)0);
    global_error.json = ((void *)0);
    global_error.position = 0;
    if (value == ((void *)0) || 0 == buffer_length)
    {
        goto fail;
    }
    buffer.content = (const unsigned char*)value;
    buffer.length = buffer_length;
    buffer.offset = 0;
    buffer.hooks = global_hooks;
    item = cJSON_New_Item(&global_hooks);
    if (item == ((void *)0))
    {
        goto fail;
    }
    if (!parse_value(item, buffer_skip_whitespace(skip_utf8_bom(&buffer))))
    {
        goto fail;
    }
    if (require_null_terminated)
    {
        buffer_skip_whitespace(&buffer);
        if ((buffer.offset >= buffer.length) || ((&buffer)->content + (&buffer)->offset)[0] != '\0')
        {
            goto fail;
        }
    }
    if (return_parse_end)
    {
        *return_parse_end = (const char*)((&buffer)->content + (&buffer)->offset);
    }
    return item;
fail:
    if (item != ((void *)0))
    {
        cJSON_Delete(item);
    }
    if (value != ((void *)0))
    {
        error local_error;
        local_error.json = (const unsigned char*)value;
        local_error.position = 0;
        if (buffer.offset < buffer.length)
        {
            local_error.position = buffer.offset;
        }
        else if (buffer.length > 0)
        {
            local_error.position = buffer.length - 1;
        }
        if (return_parse_end != ((void *)0))
        {
            *return_parse_end = (const char*)local_error.json + local_error.position;
        }
        global_error = local_error;
    }
    return ((void *)0);
}
cJSON * cJSON_Parse(const char *value)
{
    return cJSON_ParseWithOpts(value, 0, 0);
}
cJSON * cJSON_ParseWithLength(const char *value, size_t buffer_length)
{
    return cJSON_ParseWithLengthOpts(value, buffer_length, 0, 0);
}
static unsigned char *print(const cJSON * const item, cJSON_bool format, const internal_hooks * const hooks)
{
    static const size_t default_buffer_size = 256;
    printbuffer buffer[1];
    unsigned char *printed = ((void *)0);
    memset(buffer, 0, sizeof(buffer));
    buffer->buffer = (unsigned char*) hooks->allocate(default_buffer_size);
    buffer->length = default_buffer_size;
    buffer->format = format;
    buffer->hooks = *hooks;
    if (buffer->buffer == ((void *)0))
    {
        goto fail;
    }
    if (!print_value(item, buffer))
    {
        goto fail;
    }
    update_offset(buffer);
    if (hooks->reallocate != ((void *)0))
    {
        printed = (unsigned char*) hooks->reallocate(buffer->buffer, buffer->offset + 1);
        if (printed == ((void *)0)) {
            goto fail;
        }
        buffer->buffer = ((void *)0);
    }
    else
    {
        printed = (unsigned char*) hooks->allocate(buffer->offset + 1);
        if (printed == ((void *)0))
        {
            goto fail;
        }
        memcpy(printed, buffer->buffer, (((buffer->length) < (buffer->offset + 1)) ? (buffer->length) : (buffer->offset + 1)));
        printed[buffer->offset] = '\0';
        hooks->deallocate(buffer->buffer);
        buffer->buffer = ((void *)0);
    }
    return printed;
fail:
    if (buffer->buffer != ((void *)0))
    {
        hooks->deallocate(buffer->buffer);
        buffer->buffer = ((void *)0);
    }
    if (printed != ((void *)0))
    {
        hooks->deallocate(printed);
        printed = ((void *)0);
    }
    return ((void *)0);
}
char * cJSON_Print(const cJSON *item)
{
    return (char*)print(item, ((cJSON_bool)1), &global_hooks);
}
char * cJSON_PrintUnformatted(const cJSON *item)
{
    return (char*)print(item, ((cJSON_bool)0), &global_hooks);
}
char * cJSON_PrintBuffered(const cJSON *item, int prebuffer, cJSON_bool fmt)
{
    printbuffer p = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };
    if (prebuffer < 0)
    {
        return ((void *)0);
    }
    p.buffer = (unsigned char*)global_hooks.allocate((size_t)prebuffer);
    if (!p.buffer)
    {
        return ((void *)0);
    }
    p.length = (size_t)prebuffer;
    p.offset = 0;
    p.noalloc = ((cJSON_bool)0);
    p.format = fmt;
    p.hooks = global_hooks;
    if (!print_value(item, &p))
    {
        global_hooks.deallocate(p.buffer);
        p.buffer = ((void *)0);
        return ((void *)0);
    }
    return (char*)p.buffer;
}
cJSON_bool cJSON_PrintPreallocated(cJSON *item, char *buffer, const int length, const cJSON_bool format)
{
    printbuffer p = { 0, 0, 0, 0, 0, 0, { 0, 0, 0 } };
    if ((length < 0) || (buffer == ((void *)0)))
    {
        return ((cJSON_bool)0);
    }
    p.buffer = (unsigned char*)buffer;
    p.length = (size_t)length;
    p.offset = 0;
    p.noalloc = ((cJSON_bool)1);
    p.format = format;
    p.hooks = global_hooks;
    return print_value(item, &p);
}
static cJSON_bool parse_value(cJSON * const item, parse_buffer * const input_buffer)
{
    if ((input_buffer == ((void *)0)) || (input_buffer->content == ((void *)0)))
    {
        return ((cJSON_bool)0);
    }
    if (((input_buffer != ((void *)0)) && (((input_buffer)->offset + 4) <= (input_buffer)->length)) && (strncmp((const char*)((input_buffer)->content + (input_buffer)->offset), "null", 4) == 0))
    {
        item->type = (1 << 2);
        input_buffer->offset += 4;
        return ((cJSON_bool)1);
    }
    if (((input_buffer != ((void *)0)) && (((input_buffer)->offset + 5) <= (input_buffer)->length)) && (strncmp((const char*)((input_buffer)->content + (input_buffer)->offset), "false", 5) == 0))
    {
        item->type = (1 << 0);
        input_buffer->offset += 5;
        return ((cJSON_bool)1);
    }
    if (((input_buffer != ((void *)0)) && (((input_buffer)->offset + 4) <= (input_buffer)->length)) && (strncmp((const char*)((input_buffer)->content + (input_buffer)->offset), "true", 4) == 0))
    {
        item->type = (1 << 1);
        item->valueint = 1;
        input_buffer->offset += 4;
        return ((cJSON_bool)1);
    }
    if (((input_buffer != ((void *)0)) && (((input_buffer)->offset + 0) < (input_buffer)->length)) && (((input_buffer)->content + (input_buffer)->offset)[0] == '\"'))
    {
        return parse_string(item, input_buffer);
    }
    if (((input_buffer != ((void *)0)) && (((input_buffer)->offset + 0) < (input_buffer)->length)) && ((((input_buffer)->content + (input_buffer)->offset)[0] == '-') || ((((input_buffer)->content + (input_buffer)->offset)[0] >= '0') && (((input_buffer)->content + (input_buffer)->offset)[0] <= '9'))))
    {
        return parse_number(item, input_buffer);
    }
    if (((input_buffer != ((void *)0)) && (((input_buffer)->offset + 0) < (input_buffer)->length)) && (((input_buffer)->content + (input_buffer)->offset)[0] == '['))
    {
        return parse_array(item, input_buffer);
    }
    if (((input_buffer != ((void *)0)) && (((input_buffer)->offset + 0) < (input_buffer)->length)) && (((input_buffer)->content + (input_buffer)->offset)[0] == '{'))
    {
        return parse_object(item, input_buffer);
    }
    return ((cJSON_bool)0);
}
static cJSON_bool print_value(const cJSON * const item, printbuffer * const output_buffer)
{
    unsigned char *output = ((void *)0);
    if ((item == ((void *)0)) || (output_buffer == ((void *)0)))
    {
        return ((cJSON_bool)0);
    }
    switch ((item->type) & 0xFF)
    {
        case (1 << 2):
            output = ensure(output_buffer, 5);
            if (output == ((void *)0))
            {
                return ((cJSON_bool)0);
            }
            strcpy((char*)output, "null");
            return ((cJSON_bool)1);
        case (1 << 0):
            output = ensure(output_buffer, 6);
            if (output == ((void *)0))
            {
                return ((cJSON_bool)0);
            }
            strcpy((char*)output, "false");
            return ((cJSON_bool)1);
        case (1 << 1):
            output = ensure(output_buffer, 5);
            if (output == ((void *)0))
            {
                return ((cJSON_bool)0);
            }
            strcpy((char*)output, "true");
            return ((cJSON_bool)1);
        case (1 << 3):
            return print_number(item, output_buffer);
        case (1 << 7):
        {
            size_t raw_length = 0;
            if (item->valuestring == ((void *)0))
            {
                return ((cJSON_bool)0);
            }
            raw_length = strlen(item->valuestring) + sizeof("");
            output = ensure(output_buffer, raw_length);
            if (output == ((void *)0))
            {
                return ((cJSON_bool)0);
            }
            memcpy(output, item->valuestring, raw_length);
            return ((cJSON_bool)1);
        }
        case (1 << 4):
            return print_string(item, output_buffer);
        case (1 << 5):
            return print_array(item, output_buffer);
        case (1 << 6):
            return print_object(item, output_buffer);
        default:
            return ((cJSON_bool)0);
    }
}
static cJSON_bool parse_array(cJSON * const item, parse_buffer * const input_buffer)
{
    cJSON *head = ((void *)0);
    cJSON *current_item = ((void *)0);
    if (input_buffer->depth >= 1000)
    {
        return ((cJSON_bool)0);
    }
    input_buffer->depth++;
    if (((input_buffer)->content + (input_buffer)->offset)[0] != '[')
    {
        goto fail;
    }
    input_buffer->offset++;
    buffer_skip_whitespace(input_buffer);
    if (((input_buffer != ((void *)0)) && (((input_buffer)->offset + 0) < (input_buffer)->length)) && (((input_buffer)->content + (input_buffer)->offset)[0] == ']'))
    {
        goto success;
    }
    if ((!((input_buffer != ((void *)0)) && (((input_buffer)->offset + 0) < (input_buffer)->length))))
    {
        input_buffer->offset--;
        goto fail;
    }
    input_buffer->offset--;
    do
    {
        cJSON *new_item = cJSON_New_Item(&(input_buffer->hooks));
        if (new_item == ((void *)0))
        {
            goto fail;
        }
        if (head == ((void *)0))
        {
            current_item = head = new_item;
        }
        else
        {
            current_item->next = new_item;
            new_item->prev = current_item;
            current_item = new_item;
        }
        input_buffer->offset++;
        buffer_skip_whitespace(input_buffer);
        if (!parse_value(current_item, input_buffer))
        {
            goto fail;
        }
        buffer_skip_whitespace(input_buffer);
    }
    while (((input_buffer != ((void *)0)) && (((input_buffer)->offset + 0) < (input_buffer)->length)) && (((input_buffer)->content + (input_buffer)->offset)[0] == ','));
    if ((!((input_buffer != ((void *)0)) && (((input_buffer)->offset + 0) < (input_buffer)->length))) || ((input_buffer)->content + (input_buffer)->offset)[0] != ']')
    {
        goto fail;
    }
success:
    input_buffer->depth--;
    if (head != ((void *)0)) {
        head->prev = current_item;
    }
    item->type = (1 << 5);
    item->child = head;
    input_buffer->offset++;
    return ((cJSON_bool)1);
fail:
    if (head != ((void *)0))
    {
        cJSON_Delete(head);
    }
    return ((cJSON_bool)0);
}
static cJSON_bool print_array(const cJSON * const item, printbuffer * const output_buffer)
{
    unsigned char *output_pointer = ((void *)0);
    size_t length = 0;
    cJSON *current_element = item->child;
    if (output_buffer == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    if (output_buffer->depth >= 1000)
    {
        return ((cJSON_bool)0);
    }
    output_pointer = ensure(output_buffer, 1);
    if (output_pointer == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    *output_pointer = '[';
    output_buffer->offset++;
    output_buffer->depth++;
    while (current_element != ((void *)0))
    {
        if (!print_value(current_element, output_buffer))
        {
            return ((cJSON_bool)0);
        }
        update_offset(output_buffer);
        if (current_element->next)
        {
            length = (size_t) (output_buffer->format ? 2 : 1);
            output_pointer = ensure(output_buffer, length + 1);
            if (output_pointer == ((void *)0))
            {
                return ((cJSON_bool)0);
            }
            *output_pointer++ = ',';
            if(output_buffer->format)
            {
                *output_pointer++ = ' ';
            }
            *output_pointer = '\0';
            output_buffer->offset += length;
        }
        current_element = current_element->next;
    }
    output_pointer = ensure(output_buffer, 2);
    if (output_pointer == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    *output_pointer++ = ']';
    *output_pointer = '\0';
    output_buffer->depth--;
    return ((cJSON_bool)1);
}
static cJSON_bool parse_object(cJSON * const item, parse_buffer * const input_buffer)
{
    cJSON *head = ((void *)0);
    cJSON *current_item = ((void *)0);
    if (input_buffer->depth >= 1000)
    {
        return ((cJSON_bool)0);
    }
    input_buffer->depth++;
    if ((!((input_buffer != ((void *)0)) && (((input_buffer)->offset + 0) < (input_buffer)->length))) || (((input_buffer)->content + (input_buffer)->offset)[0] != '{'))
    {
        goto fail;
    }
    input_buffer->offset++;
    buffer_skip_whitespace(input_buffer);
    if (((input_buffer != ((void *)0)) && (((input_buffer)->offset + 0) < (input_buffer)->length)) && (((input_buffer)->content + (input_buffer)->offset)[0] == '}'))
    {
        goto success;
    }
    if ((!((input_buffer != ((void *)0)) && (((input_buffer)->offset + 0) < (input_buffer)->length))))
    {
        input_buffer->offset--;
        goto fail;
    }
    input_buffer->offset--;
    do
    {
        cJSON *new_item = cJSON_New_Item(&(input_buffer->hooks));
        if (new_item == ((void *)0))
        {
            goto fail;
        }
        if (head == ((void *)0))
        {
            current_item = head = new_item;
        }
        else
        {
            current_item->next = new_item;
            new_item->prev = current_item;
            current_item = new_item;
        }
        if ((!((input_buffer != ((void *)0)) && (((input_buffer)->offset + 1) < (input_buffer)->length))))
        {
            goto fail;
        }
        input_buffer->offset++;
        buffer_skip_whitespace(input_buffer);
        if (!parse_string(current_item, input_buffer))
        {
            goto fail;
        }
        buffer_skip_whitespace(input_buffer);
        current_item->string = current_item->valuestring;
        current_item->valuestring = ((void *)0);
        if ((!((input_buffer != ((void *)0)) && (((input_buffer)->offset + 0) < (input_buffer)->length))) || (((input_buffer)->content + (input_buffer)->offset)[0] != ':'))
        {
            goto fail;
        }
        input_buffer->offset++;
        buffer_skip_whitespace(input_buffer);
        if (!parse_value(current_item, input_buffer))
        {
            goto fail;
        }
        buffer_skip_whitespace(input_buffer);
    }
    while (((input_buffer != ((void *)0)) && (((input_buffer)->offset + 0) < (input_buffer)->length)) && (((input_buffer)->content + (input_buffer)->offset)[0] == ','));
    if ((!((input_buffer != ((void *)0)) && (((input_buffer)->offset + 0) < (input_buffer)->length))) || (((input_buffer)->content + (input_buffer)->offset)[0] != '}'))
    {
        goto fail;
    }
success:
    input_buffer->depth--;
    if (head != ((void *)0)) {
        head->prev = current_item;
    }
    item->type = (1 << 6);
    item->child = head;
    input_buffer->offset++;
    return ((cJSON_bool)1);
fail:
    if (head != ((void *)0))
    {
        cJSON_Delete(head);
    }
    return ((cJSON_bool)0);
}
static cJSON_bool print_object(const cJSON * const item, printbuffer * const output_buffer)
{
    unsigned char *output_pointer = ((void *)0);
    size_t length = 0;
    cJSON *current_item = item->child;
    if (output_buffer == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    if (output_buffer->depth >= 1000)
    {
        return ((cJSON_bool)0);
    }
    length = (size_t) (output_buffer->format ? 2 : 1);
    output_pointer = ensure(output_buffer, length + 1);
    if (output_pointer == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    *output_pointer++ = '{';
    output_buffer->depth++;
    if (output_buffer->format)
    {
        *output_pointer++ = '\n';
    }
    output_buffer->offset += length;
    while (current_item)
    {
        if (output_buffer->format)
        {
            size_t i;
            output_pointer = ensure(output_buffer, output_buffer->depth);
            if (output_pointer == ((void *)0))
            {
                return ((cJSON_bool)0);
            }
            for (i = 0; i < output_buffer->depth; i++)
            {
                *output_pointer++ = '\t';
            }
            output_buffer->offset += output_buffer->depth;
        }
        if (!print_string_ptr((unsigned char*)current_item->string, output_buffer))
        {
            return ((cJSON_bool)0);
        }
        update_offset(output_buffer);
        length = (size_t) (output_buffer->format ? 2 : 1);
        output_pointer = ensure(output_buffer, length);
        if (output_pointer == ((void *)0))
        {
            return ((cJSON_bool)0);
        }
        *output_pointer++ = ':';
        if (output_buffer->format)
        {
            *output_pointer++ = '\t';
        }
        output_buffer->offset += length;
        if (!print_value(current_item, output_buffer))
        {
            return ((cJSON_bool)0);
        }
        update_offset(output_buffer);
        length = ((size_t)(output_buffer->format ? 1 : 0) + (size_t)(current_item->next ? 1 : 0));
        output_pointer = ensure(output_buffer, length + 1);
        if (output_pointer == ((void *)0))
        {
            return ((cJSON_bool)0);
        }
        if (current_item->next)
        {
            *output_pointer++ = ',';
        }
        if (output_buffer->format)
        {
            *output_pointer++ = '\n';
        }
        *output_pointer = '\0';
        output_buffer->offset += length;
        current_item = current_item->next;
    }
    output_pointer = ensure(output_buffer, output_buffer->format ? (output_buffer->depth + 1) : 2);
    if (output_pointer == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    if (output_buffer->format)
    {
        size_t i;
        for (i = 0; i < (output_buffer->depth - 1); i++)
        {
            *output_pointer++ = '\t';
        }
    }
    *output_pointer++ = '}';
    *output_pointer = '\0';
    output_buffer->depth--;
    return ((cJSON_bool)1);
}
int cJSON_GetArraySize(const cJSON *array)
{
    cJSON *child = ((void *)0);
    size_t size = 0;
    if (array == ((void *)0))
    {
        return 0;
    }
    child = array->child;
    while(child != ((void *)0))
    {
        size++;
        child = child->next;
    }
    return (int)size;
}
static cJSON* get_array_item(const cJSON *array, size_t index)
{
    cJSON *current_child = ((void *)0);
    if (array == ((void *)0))
    {
        return ((void *)0);
    }
    current_child = array->child;
    while ((current_child != ((void *)0)) && (index > 0))
    {
        index--;
        current_child = current_child->next;
    }
    return current_child;
}
cJSON * cJSON_GetArrayItem(const cJSON *array, int index)
{
    if (index < 0)
    {
        return ((void *)0);
    }
    return get_array_item(array, (size_t)index);
}
static cJSON *get_object_item(const cJSON * const object, const char * const name, const cJSON_bool case_sensitive)
{
    cJSON *current_element = ((void *)0);
    if ((object == ((void *)0)) || (name == ((void *)0)))
    {
        return ((void *)0);
    }
    current_element = object->child;
    if (case_sensitive)
    {
        while ((current_element != ((void *)0)) && (current_element->string != ((void *)0)) && (strcmp(name, current_element->string) != 0))
        {
            current_element = current_element->next;
        }
    }
    else
    {
        while ((current_element != ((void *)0)) && (case_insensitive_strcmp((const unsigned char*)name, (const unsigned char*)(current_element->string)) != 0))
        {
            current_element = current_element->next;
        }
    }
    if ((current_element == ((void *)0)) || (current_element->string == ((void *)0))) {
        return ((void *)0);
    }
    return current_element;
}
cJSON * cJSON_GetObjectItem(const cJSON * const object, const char * const string)
{
    return get_object_item(object, string, ((cJSON_bool)0));
}
cJSON * cJSON_GetObjectItemCaseSensitive(const cJSON * const object, const char * const string)
{
    return get_object_item(object, string, ((cJSON_bool)1));
}
cJSON_bool cJSON_HasObjectItem(const cJSON *object, const char *string)
{
    return cJSON_GetObjectItem(object, string) ? 1 : 0;
}
static void suffix_object(cJSON *prev, cJSON *item)
{
    prev->next = item;
    item->prev = prev;
}
static cJSON *create_reference(const cJSON *item, const internal_hooks * const hooks)
{
    cJSON *reference = ((void *)0);
    if (item == ((void *)0))
    {
        return ((void *)0);
    }
    reference = cJSON_New_Item(hooks);
    if (reference == ((void *)0))
    {
        return ((void *)0);
    }
    memcpy(reference, item, sizeof(cJSON));
    reference->string = ((void *)0);
    reference->type |= 256;
    reference->next = reference->prev = ((void *)0);
    return reference;
}
static cJSON_bool add_item_to_array(cJSON *array, cJSON *item)
{
    cJSON *child = ((void *)0);
    if ((item == ((void *)0)) || (array == ((void *)0)) || (array == item))
    {
        return ((cJSON_bool)0);
    }
    child = array->child;
    if (child == ((void *)0))
    {
        array->child = item;
        item->prev = item;
        item->next = ((void *)0);
    }
    else
    {
        if (child->prev)
        {
            suffix_object(child->prev, item);
            array->child->prev = item;
        }
    }
    return ((cJSON_bool)1);
}
cJSON_bool cJSON_AddItemToArray(cJSON *array, cJSON *item)
{
    return add_item_to_array(array, item);
}
static void* cast_away_const(const void* string)
{
    return (void*)string;
}
static cJSON_bool add_item_to_object(cJSON * const object, const char * const string, cJSON * const item, const internal_hooks * const hooks, const cJSON_bool constant_key)
{
    char *new_key = ((void *)0);
    int new_type = (0);
    if ((object == ((void *)0)) || (string == ((void *)0)) || (item == ((void *)0)) || (object == item))
    {
        return ((cJSON_bool)0);
    }
    if (constant_key)
    {
        new_key = (char*)cast_away_const(string);
        new_type = item->type | 512;
    }
    else
    {
        new_key = (char*)cJSON_strdup((const unsigned char*)string, hooks);
        if (new_key == ((void *)0))
        {
            return ((cJSON_bool)0);
        }
        new_type = item->type & ~512;
    }
    if (!(item->type & 512) && (item->string != ((void *)0)))
    {
        hooks->deallocate(item->string);
    }
    item->string = new_key;
    item->type = new_type;
    return add_item_to_array(object, item);
}
cJSON_bool cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item)
{
    return add_item_to_object(object, string, item, &global_hooks, ((cJSON_bool)0));
}
cJSON_bool cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item)
{
    return add_item_to_object(object, string, item, &global_hooks, ((cJSON_bool)1));
}
cJSON_bool cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item)
{
    if (array == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    return add_item_to_array(array, create_reference(item, &global_hooks));
}
cJSON_bool cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item)
{
    if ((object == ((void *)0)) || (string == ((void *)0)))
    {
        return ((cJSON_bool)0);
    }
    return add_item_to_object(object, string, create_reference(item, &global_hooks), &global_hooks, ((cJSON_bool)0));
}
cJSON* cJSON_AddNullToObject(cJSON * const object, const char * const name)
{
    cJSON *null = cJSON_CreateNull();
    if (add_item_to_object(object, name, null, &global_hooks, ((cJSON_bool)0)))
    {
        return null;
    }
    cJSON_Delete(null);
    return ((void *)0);
}
cJSON* cJSON_AddTrueToObject(cJSON * const object, const char * const name)
{
    cJSON *true_item = cJSON_CreateTrue();
    if (add_item_to_object(object, name, true_item, &global_hooks, ((cJSON_bool)0)))
    {
        return true_item;
    }
    cJSON_Delete(true_item);
    return ((void *)0);
}
cJSON* cJSON_AddFalseToObject(cJSON * const object, const char * const name)
{
    cJSON *false_item = cJSON_CreateFalse();
    if (add_item_to_object(object, name, false_item, &global_hooks, ((cJSON_bool)0)))
    {
        return false_item;
    }
    cJSON_Delete(false_item);
    return ((void *)0);
}
cJSON* cJSON_AddBoolToObject(cJSON * const object, const char * const name, const cJSON_bool boolean)
{
    cJSON *bool_item = cJSON_CreateBool(boolean);
    if (add_item_to_object(object, name, bool_item, &global_hooks, ((cJSON_bool)0)))
    {
        return bool_item;
    }
    cJSON_Delete(bool_item);
    return ((void *)0);
}
cJSON* cJSON_AddNumberToObject(cJSON * const object, const char * const name, const double number)
{
    cJSON *number_item = cJSON_CreateNumber(number);
    if (add_item_to_object(object, name, number_item, &global_hooks, ((cJSON_bool)0)))
    {
        return number_item;
    }
    cJSON_Delete(number_item);
    return ((void *)0);
}
cJSON* cJSON_AddStringToObject(cJSON * const object, const char * const name, const char * const string)
{
    cJSON *string_item = cJSON_CreateString(string);
    if (add_item_to_object(object, name, string_item, &global_hooks, ((cJSON_bool)0)))
    {
        return string_item;
    }
    cJSON_Delete(string_item);
    return ((void *)0);
}
cJSON* cJSON_AddRawToObject(cJSON * const object, const char * const name, const char * const raw)
{
    cJSON *raw_item = cJSON_CreateRaw(raw);
    if (add_item_to_object(object, name, raw_item, &global_hooks, ((cJSON_bool)0)))
    {
        return raw_item;
    }
    cJSON_Delete(raw_item);
    return ((void *)0);
}
cJSON* cJSON_AddObjectToObject(cJSON * const object, const char * const name)
{
    cJSON *object_item = cJSON_CreateObject();
    if (add_item_to_object(object, name, object_item, &global_hooks, ((cJSON_bool)0)))
    {
        return object_item;
    }
    cJSON_Delete(object_item);
    return ((void *)0);
}
cJSON* cJSON_AddArrayToObject(cJSON * const object, const char * const name)
{
    cJSON *array = cJSON_CreateArray();
    if (add_item_to_object(object, name, array, &global_hooks, ((cJSON_bool)0)))
    {
        return array;
    }
    cJSON_Delete(array);
    return ((void *)0);
}
cJSON * cJSON_DetachItemViaPointer(cJSON *parent, cJSON * const item)
{
    if ((parent == ((void *)0)) || (item == ((void *)0)) || (item != parent->child && item->prev == ((void *)0)))
    {
        return ((void *)0);
    }
    if (item != parent->child)
    {
        item->prev->next = item->next;
    }
    if (item->next != ((void *)0))
    {
        item->next->prev = item->prev;
    }
    if (item == parent->child)
    {
        parent->child = item->next;
    }
    else if (item->next == ((void *)0))
    {
        parent->child->prev = item->prev;
    }
    item->prev = ((void *)0);
    item->next = ((void *)0);
    return item;
}
cJSON * cJSON_DetachItemFromArray(cJSON *array, int which)
{
    if (which < 0)
    {
        return ((void *)0);
    }
    return cJSON_DetachItemViaPointer(array, get_array_item(array, (size_t)which));
}
void cJSON_DeleteItemFromArray(cJSON *array, int which)
{
    cJSON_Delete(cJSON_DetachItemFromArray(array, which));
}
cJSON * cJSON_DetachItemFromObject(cJSON *object, const char *string)
{
    cJSON *to_detach = cJSON_GetObjectItem(object, string);
    return cJSON_DetachItemViaPointer(object, to_detach);
}
cJSON * cJSON_DetachItemFromObjectCaseSensitive(cJSON *object, const char *string)
{
    cJSON *to_detach = cJSON_GetObjectItemCaseSensitive(object, string);
    return cJSON_DetachItemViaPointer(object, to_detach);
}
void cJSON_DeleteItemFromObject(cJSON *object, const char *string)
{
    cJSON_Delete(cJSON_DetachItemFromObject(object, string));
}
void cJSON_DeleteItemFromObjectCaseSensitive(cJSON *object, const char *string)
{
    cJSON_Delete(cJSON_DetachItemFromObjectCaseSensitive(object, string));
}
cJSON_bool cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem)
{
    cJSON *after_inserted = ((void *)0);
    if (which < 0 || newitem == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    after_inserted = get_array_item(array, (size_t)which);
    if (after_inserted == ((void *)0))
    {
        return add_item_to_array(array, newitem);
    }
    if (after_inserted != array->child && after_inserted->prev == ((void *)0)) {
        return ((cJSON_bool)0);
    }
    newitem->next = after_inserted;
    newitem->prev = after_inserted->prev;
    after_inserted->prev = newitem;
    if (after_inserted == array->child)
    {
        array->child = newitem;
    }
    else
    {
        newitem->prev->next = newitem;
    }
    return ((cJSON_bool)1);
}
cJSON_bool cJSON_ReplaceItemViaPointer(cJSON * const parent, cJSON * const item, cJSON * replacement)
{
    if ((parent == ((void *)0)) || (parent->child == ((void *)0)) || (replacement == ((void *)0)) || (item == ((void *)0)))
    {
        return ((cJSON_bool)0);
    }
    if (replacement == item)
    {
        return ((cJSON_bool)1);
    }
    replacement->next = item->next;
    replacement->prev = item->prev;
    if (replacement->next != ((void *)0))
    {
        replacement->next->prev = replacement;
    }
    if (parent->child == item)
    {
        if (parent->child->prev == parent->child)
        {
            replacement->prev = replacement;
        }
        parent->child = replacement;
    }
    else
    {
        if (replacement->prev != ((void *)0))
        {
            replacement->prev->next = replacement;
        }
        if (replacement->next == ((void *)0))
        {
            parent->child->prev = replacement;
        }
    }
    item->next = ((void *)0);
    item->prev = ((void *)0);
    cJSON_Delete(item);
    return ((cJSON_bool)1);
}
cJSON_bool cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem)
{
    if (which < 0)
    {
        return ((cJSON_bool)0);
    }
    return cJSON_ReplaceItemViaPointer(array, get_array_item(array, (size_t)which), newitem);
}
static cJSON_bool replace_item_in_object(cJSON *object, const char *string, cJSON *replacement, cJSON_bool case_sensitive)
{
    if ((replacement == ((void *)0)) || (string == ((void *)0)))
    {
        return ((cJSON_bool)0);
    }
    if (!(replacement->type & 512) && (replacement->string != ((void *)0)))
    {
        cJSON_free(replacement->string);
    }
    replacement->string = (char*)cJSON_strdup((const unsigned char*)string, &global_hooks);
    if (replacement->string == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    replacement->type &= ~512;
    return cJSON_ReplaceItemViaPointer(object, get_object_item(object, string, case_sensitive), replacement);
}
cJSON_bool cJSON_ReplaceItemInObject(cJSON *object, const char *string, cJSON *newitem)
{
    return replace_item_in_object(object, string, newitem, ((cJSON_bool)0));
}
cJSON_bool cJSON_ReplaceItemInObjectCaseSensitive(cJSON *object, const char *string, cJSON *newitem)
{
    return replace_item_in_object(object, string, newitem, ((cJSON_bool)1));
}
cJSON * cJSON_CreateNull(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = (1 << 2);
    }
    return item;
}
cJSON * cJSON_CreateTrue(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = (1 << 1);
    }
    return item;
}
cJSON * cJSON_CreateFalse(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = (1 << 0);
    }
    return item;
}
cJSON * cJSON_CreateBool(cJSON_bool boolean)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = boolean ? (1 << 1) : (1 << 0);
    }
    return item;
}
cJSON * cJSON_CreateNumber(double num)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = (1 << 3);
        item->valuedouble = num;
        if (num >= 0x7fffffff)
        {
            item->valueint = 0x7fffffff;
        }
        else if (num <= (double)(-0x7fffffff - 1))
        {
            item->valueint = (-0x7fffffff - 1);
        }
        else
        {
            item->valueint = (int)num;
        }
    }
    return item;
}
cJSON * cJSON_CreateString(const char *string)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = (1 << 4);
        item->valuestring = (char*)cJSON_strdup((const unsigned char*)string, &global_hooks);
        if(!item->valuestring)
        {
            cJSON_Delete(item);
            return ((void *)0);
        }
    }
    return item;
}
cJSON * cJSON_CreateStringReference(const char *string)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if (item != ((void *)0))
    {
        item->type = (1 << 4) | 256;
        item->valuestring = (char*)cast_away_const(string);
    }
    return item;
}
cJSON * cJSON_CreateObjectReference(const cJSON *child)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if (item != ((void *)0)) {
        item->type = (1 << 6) | 256;
        item->child = (cJSON*)cast_away_const(child);
    }
    return item;
}
cJSON * cJSON_CreateArrayReference(const cJSON *child) {
    cJSON *item = cJSON_New_Item(&global_hooks);
    if (item != ((void *)0)) {
        item->type = (1 << 5) | 256;
        item->child = (cJSON*)cast_away_const(child);
    }
    return item;
}
cJSON * cJSON_CreateRaw(const char *raw)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type = (1 << 7);
        item->valuestring = (char*)cJSON_strdup((const unsigned char*)raw, &global_hooks);
        if(!item->valuestring)
        {
            cJSON_Delete(item);
            return ((void *)0);
        }
    }
    return item;
}
cJSON * cJSON_CreateArray(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if(item)
    {
        item->type=(1 << 5);
    }
    return item;
}
cJSON * cJSON_CreateObject(void)
{
    cJSON *item = cJSON_New_Item(&global_hooks);
    if (item)
    {
        item->type = (1 << 6);
    }
    return item;
}
cJSON * cJSON_CreateIntArray(const int *numbers, int count)
{
    size_t i = 0;
    cJSON *n = ((void *)0);
    cJSON *p = ((void *)0);
    cJSON *a = ((void *)0);
    if ((count < 0) || (numbers == ((void *)0)))
    {
        return ((void *)0);
    }
    a = cJSON_CreateArray();
    for(i = 0; a && (i < (size_t)count); i++)
    {
        n = cJSON_CreateNumber(numbers[i]);
        if (!n)
        {
            cJSON_Delete(a);
            return ((void *)0);
        }
        if(!i)
        {
            a->child = n;
        }
        else
        {
            suffix_object(p, n);
        }
        p = n;
    }
    if (a && a->child) {
        a->child->prev = n;
    }
    return a;
}
cJSON * cJSON_CreateFloatArray(const float *numbers, int count)
{
    size_t i = 0;
    cJSON *n = ((void *)0);
    cJSON *p = ((void *)0);
    cJSON *a = ((void *)0);
    if ((count < 0) || (numbers == ((void *)0)))
    {
        return ((void *)0);
    }
    a = cJSON_CreateArray();
    for(i = 0; a && (i < (size_t)count); i++)
    {
        n = cJSON_CreateNumber((double)numbers[i]);
        if(!n)
        {
            cJSON_Delete(a);
            return ((void *)0);
        }
        if(!i)
        {
            a->child = n;
        }
        else
        {
            suffix_object(p, n);
        }
        p = n;
    }
    if (a && a->child) {
        a->child->prev = n;
    }
    return a;
}
cJSON * cJSON_CreateDoubleArray(const double *numbers, int count)
{
    size_t i = 0;
    cJSON *n = ((void *)0);
    cJSON *p = ((void *)0);
    cJSON *a = ((void *)0);
    if ((count < 0) || (numbers == ((void *)0)))
    {
        return ((void *)0);
    }
    a = cJSON_CreateArray();
    for(i = 0; a && (i < (size_t)count); i++)
    {
        n = cJSON_CreateNumber(numbers[i]);
        if(!n)
        {
            cJSON_Delete(a);
            return ((void *)0);
        }
        if(!i)
        {
            a->child = n;
        }
        else
        {
            suffix_object(p, n);
        }
        p = n;
    }
    if (a && a->child) {
        a->child->prev = n;
    }
    return a;
}
cJSON * cJSON_CreateStringArray(const char *const *strings, int count)
{
    size_t i = 0;
    cJSON *n = ((void *)0);
    cJSON *p = ((void *)0);
    cJSON *a = ((void *)0);
    if ((count < 0) || (strings == ((void *)0)))
    {
        return ((void *)0);
    }
    a = cJSON_CreateArray();
    for (i = 0; a && (i < (size_t)count); i++)
    {
        n = cJSON_CreateString(strings[i]);
        if(!n)
        {
            cJSON_Delete(a);
            return ((void *)0);
        }
        if(!i)
        {
            a->child = n;
        }
        else
        {
            suffix_object(p,n);
        }
        p = n;
    }
    if (a && a->child) {
        a->child->prev = n;
    }
    return a;
}
cJSON * cJSON_Duplicate_rec(const cJSON *item, size_t depth, cJSON_bool recurse);
cJSON * cJSON_Duplicate(const cJSON *item, cJSON_bool recurse)
{
    return cJSON_Duplicate_rec(item, 0, recurse );
}
cJSON * cJSON_Duplicate_rec(const cJSON *item, size_t depth, cJSON_bool recurse)
{
    cJSON *newitem = ((void *)0);
    cJSON *child = ((void *)0);
    cJSON *next = ((void *)0);
    cJSON *newchild = ((void *)0);
    if (!item)
    {
        goto fail;
    }
    newitem = cJSON_New_Item(&global_hooks);
    if (!newitem)
    {
        goto fail;
    }
    newitem->type = item->type & (~256);
    newitem->valueint = item->valueint;
    newitem->valuedouble = item->valuedouble;
    if (item->valuestring)
    {
        newitem->valuestring = (char*)cJSON_strdup((unsigned char*)item->valuestring, &global_hooks);
        if (!newitem->valuestring)
        {
            goto fail;
        }
    }
    if (item->string)
    {
        newitem->string = (item->type&512) ? item->string : (char*)cJSON_strdup((unsigned char*)item->string, &global_hooks);
        if (!newitem->string)
        {
            goto fail;
        }
    }
    if (!recurse)
    {
        return newitem;
    }
    child = item->child;
    while (child != ((void *)0))
    {
        if(depth >= 10000) {
            goto fail;
        }
        newchild = cJSON_Duplicate_rec(child, depth + 1, ((cJSON_bool)1));
        if (!newchild)
        {
            goto fail;
        }
        if (next != ((void *)0))
        {
            next->next = newchild;
            newchild->prev = next;
            next = newchild;
        }
        else
        {
            newitem->child = newchild;
            next = newchild;
        }
        child = child->next;
    }
    if (newitem && newitem->child)
    {
        newitem->child->prev = newchild;
    }
    return newitem;
fail:
    if (newitem != ((void *)0))
    {
        cJSON_Delete(newitem);
    }
    return ((void *)0);
}
static void skip_oneline_comment(char **input)
{
    *input += (sizeof("//") - sizeof(""));
    for (; (*input)[0] != '\0'; ++(*input))
    {
        if ((*input)[0] == '\n') {
            *input += (sizeof("\n") - sizeof(""));
            return;
        }
    }
}
static void skip_multiline_comment(char **input)
{
    *input += (sizeof("/*") - sizeof(""));
    for (; (*input)[0] != '\0'; ++(*input))
    {
        if (((*input)[0] == '*') && ((*input)[1] == '/'))
        {
            *input += (sizeof("*/") - sizeof(""));
            return;
        }
    }
}
static void minify_string(char **input, char **output) {
    (*output)[0] = (*input)[0];
    *input += (sizeof("\"") - sizeof(""));
    *output += (sizeof("\"") - sizeof(""));
    for (; (*input)[0] != '\0'; (void)++(*input), ++(*output)) {
        (*output)[0] = (*input)[0];
        if ((*input)[0] == '\"') {
            (*output)[0] = '\"';
            *input += (sizeof("\"") - sizeof(""));
            *output += (sizeof("\"") - sizeof(""));
            return;
        } else if (((*input)[0] == '\\') && ((*input)[1] == '\"')) {
            (*output)[1] = (*input)[1];
            *input += (sizeof("\"") - sizeof(""));
            *output += (sizeof("\"") - sizeof(""));
        }
    }
}
void cJSON_Minify(char *json)
{
    char *into = json;
    if (json == ((void *)0))
    {
        return;
    }
    while (json[0] != '\0')
    {
        switch (json[0])
        {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                json++;
                break;
            case '/':
                if (json[1] == '/')
                {
                    skip_oneline_comment(&json);
                }
                else if (json[1] == '*')
                {
                    skip_multiline_comment(&json);
                } else {
                    json++;
                }
                break;
            case '\"':
                minify_string(&json, (char**)&into);
                break;
            default:
                into[0] = json[0];
                json++;
                into++;
        }
    }
    *into = '\0';
}
cJSON_bool cJSON_IsInvalid(const cJSON * const item)
{
    if (item == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    return (item->type & 0xFF) == (0);
}
cJSON_bool cJSON_IsFalse(const cJSON * const item)
{
    if (item == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    return (item->type & 0xFF) == (1 << 0);
}
cJSON_bool cJSON_IsTrue(const cJSON * const item)
{
    if (item == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    return (item->type & 0xff) == (1 << 1);
}
cJSON_bool cJSON_IsBool(const cJSON * const item)
{
    if (item == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    return (item->type & ((1 << 1) | (1 << 0))) != 0;
}
cJSON_bool cJSON_IsNull(const cJSON * const item)
{
    if (item == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    return (item->type & 0xFF) == (1 << 2);
}
cJSON_bool cJSON_IsNumber(const cJSON * const item)
{
    if (item == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    return (item->type & 0xFF) == (1 << 3);
}
cJSON_bool cJSON_IsString(const cJSON * const item)
{
    if (item == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    return (item->type & 0xFF) == (1 << 4);
}
cJSON_bool cJSON_IsArray(const cJSON * const item)
{
    if (item == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    return (item->type & 0xFF) == (1 << 5);
}
cJSON_bool cJSON_IsObject(const cJSON * const item)
{
    if (item == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    return (item->type & 0xFF) == (1 << 6);
}
cJSON_bool cJSON_IsRaw(const cJSON * const item)
{
    if (item == ((void *)0))
    {
        return ((cJSON_bool)0);
    }
    return (item->type & 0xFF) == (1 << 7);
}
cJSON_bool cJSON_Compare(const cJSON * const a, const cJSON * const b, const cJSON_bool case_sensitive)
{
    if ((a == ((void *)0)) || (b == ((void *)0)) || ((a->type & 0xFF) != (b->type & 0xFF)))
    {
        return ((cJSON_bool)0);
    }
    switch (a->type & 0xFF)
    {
        case (1 << 0):
        case (1 << 1):
        case (1 << 2):
        case (1 << 3):
        case (1 << 4):
        case (1 << 7):
        case (1 << 5):
        case (1 << 6):
            break;
        default:
            return ((cJSON_bool)0);
    }
    if (a == b)
    {
        return ((cJSON_bool)1);
    }
    switch (a->type & 0xFF)
    {
        case (1 << 0):
        case (1 << 1):
        case (1 << 2):
            return ((cJSON_bool)1);
        case (1 << 3):
            if (compare_double(a->valuedouble, b->valuedouble))
            {
                return ((cJSON_bool)1);
            }
            return ((cJSON_bool)0);
        case (1 << 4):
        case (1 << 7):
            if ((a->valuestring == ((void *)0)) || (b->valuestring == ((void *)0)))
            {
                return ((cJSON_bool)0);
            }
            if (strcmp(a->valuestring, b->valuestring) == 0)
            {
                return ((cJSON_bool)1);
            }
            return ((cJSON_bool)0);
        case (1 << 5):
        {
            cJSON *a_element = a->child;
            cJSON *b_element = b->child;
            for (; (a_element != ((void *)0)) && (b_element != ((void *)0));)
            {
                if (!cJSON_Compare(a_element, b_element, case_sensitive))
                {
                    return ((cJSON_bool)0);
                }
                a_element = a_element->next;
                b_element = b_element->next;
            }
            if (a_element != b_element) {
                return ((cJSON_bool)0);
            }
            return ((cJSON_bool)1);
        }
        case (1 << 6):
        {
            cJSON *a_element = ((void *)0);
            cJSON *b_element = ((void *)0);
            for(a_element = (a != ((void *)0)) ? (a)->child : ((void *)0); a_element != ((void *)0); a_element = a_element->next)
            {
                b_element = get_object_item(b, a_element->string, case_sensitive);
                if (b_element == ((void *)0))
                {
                    return ((cJSON_bool)0);
                }
                if (!cJSON_Compare(a_element, b_element, case_sensitive))
                {
                    return ((cJSON_bool)0);
                }
            }
            for(b_element = (b != ((void *)0)) ? (b)->child : ((void *)0); b_element != ((void *)0); b_element = b_element->next)
            {
                a_element = get_object_item(a, b_element->string, case_sensitive);
                if (a_element == ((void *)0))
                {
                    return ((cJSON_bool)0);
                }
                if (!cJSON_Compare(b_element, a_element, case_sensitive))
                {
                    return ((cJSON_bool)0);
                }
            }
            return ((cJSON_bool)1);
        }
        default:
            return ((cJSON_bool)0);
    }
}
void * cJSON_malloc(size_t size)
{
    return global_hooks.allocate(size);
}
void cJSON_free(void *object)
{
    global_hooks.deallocate(object);
    object = ((void *)0);
}
