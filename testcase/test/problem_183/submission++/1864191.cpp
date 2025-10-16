#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <dlfcn.h>
#include <string.h>
#include <gmp.h>
#include <string>
#include <unordered_map>

using namespace std;

static_assert(sizeof(unsigned long) == 8);



struct DLL 
{
    void *handle;
    unordered_map<string, void *> syms;
    DLL(const char *file) : handle(dlopen(file, RTLD_LAZY)) {}
    ~DLL() { dlclose(handle); }
    void *find_name(const char *name) 
    {
        if (unordered_map<string, void *>::iterator it = syms.find(name); it != syms.end()) 
            return it->second;
        else
            return syms[name] = dlsym(handle, name);
    }
    template <typename R = void, typename... T>
    R call(const char *name, T... t) 
    {
        auto func = reinterpret_cast<R(*)(T...)>(find_name(name));
        return func(t...);
    };
};

DLL GMP("/usr/lib/x86_64-linux-gnu/libgmp.so.10");

struct fastIO
{
    static const int BUFF_SZ = 1 << 18;
    char inbuf[BUFF_SZ], outbuf[BUFF_SZ];
    fastIO()
    {
        setvbuf(stdin, inbuf, _IOFBF, BUFF_SZ);
        setvbuf(stdout, outbuf, _IOFBF, BUFF_SZ);
    }
} IO;
int radix_a, radix_b;
char A[1000005], B[1000005];
int main()
{
    scanf("%d%d%s", &radix_a, &radix_b, A);
    mpz_t a;
    GMP.call("__gmpz_init", a);
    GMP.call("__gmpz_set_str", a, A, radix_a);
    GMP.call("__gmpz_get_str", B, radix_b, a);
    if (radix_b <= 36)
        for (int i = 0, len_b = strlen(B); i < len_b; ++i)
            B[i] = toupper(B[i]);
    
    puts(B);
    GMP.call("__gmpz_clear", a);
}
