#include <cstdio>
#include <string>
#include <dlfcn.h>
#include <gmp.h>

struct SharedObject
{
    void *handle;
    SharedObject(const char *path) noexcept
    {
        handle = dlopen(path, RTLD_LAZY);
    }
    SharedObject(const std::string &path) noexcept
    {
        handle = dlopen(path.c_str(), RTLD_LAZY);
    }
    ~SharedObject() noexcept
    {
        dlclose(handle);
    }
    void *getProc(const char *name) const noexcept
    {
        return dlsym(handle, name);
    }
    void *getProc(const std::string &name) const noexcept
    {
        return dlsym(handle, name.c_str());
    }
};

#define DECL_GMP(n) Z_##n z_##n;
#define LD_GMP(n) z_##n = reinterpret_cast<Z_##n>(gmp_so.getProc("__gmpz_" #n));

typedef void (*Z_init) (mpz_t);
typedef void (*Z_clear) (mpz_t);
typedef int (*Z_set_str) (mpz_t, const char *, int);
typedef char * (*Z_get_str) (char *, int, const mpz_t);

DECL_GMP(init)
DECL_GMP(clear)
DECL_GMP(set_str)
DECL_GMP(get_str)

void loadGMP(const SharedObject &gmp_so) noexcept
{
    LD_GMP(init)
    LD_GMP(clear)
    LD_GMP(set_str)
    LD_GMP(get_str)
}

char buf[350002];
SharedObject gmp_so("/usr/lib/x86_64-linux-gnu/libgmp.so.10");

int main()
{
    loadGMP(gmp_so);
    int a, b;
    mpz_t n;
    z_init(n);
    std::scanf("%d %d", &a, &b);
    std::getchar();
    if (b > 10 && b <= 36) b = -b;
    std::fgets(buf, 350002, stdin);
    z_set_str(n, buf, a);
    z_get_str(buf, b, n);
    z_clear(n);
    std::puts(buf);
    return 0;
}
