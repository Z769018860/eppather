#include <stdio.h>
#include <string.h>


void sa_is(int n, int sig, int* s, int* sa, void *mp) {
#ifdef __cplusplus
    typedef bool st;
#else
    typedef _Bool st;
#endif
#define S 0
#define L 1
    if(sig == n) { for(int i = 1; i <= n; ++i) sa[s[i]] = i; return ; }

    st  *t   = ( st*)mp - 1; mp += sizeof(st) * (n + 1);
    int *lb  = (int*)mp - 1; mp += sizeof(int) * sig;
    int *rb  = (int*)mp - 1; mp += sizeof(int) * sig;
    int *ars = (int*)mp - 1; mp += sizeof(int) * (n + 1);
    int *ns, nn = 0;

    t[n + 1] = S;
    memset(ars + 1, 0, sizeof(int) * (n + 1));
    for(int i = n; i; --i) if(s[i] == s[i + 1]) t[i] = t[i + 1];
    else (t[i] = (s[i] > s[i + 1])) && (t[i + 1] == S) && ++nn;
    
    memset(rb + 1, 0, sizeof(int) * sig);

    ars[1] = 0;
    for(int i = 1, j = 1; i <= n; ++i) ars[i + 1] = (t[i] && !t[i + 1] ? j++ : 0), rb[s[i]] += 1;

    lb[1] = 1;
    for(int i = 2; i <= sig; ++i) rb[i] += rb[i - 1], lb[i] = rb[i - 1] + 1;

    memset(sa + 1, -1, sizeof(int) * n);
    for(int i = 1; i <= n; ++i) if(ars[i]) sa[rb[ s[i] ]--] = i;
    for(int i = 1; i < sig; ++i) rb[i] = lb[i + 1] - 1; rb[sig] = n;
    sa[lb[ s[n] ]++] = n;
    for(int i = 1; i <= n; ++i) if(sa[i] > 1 &&  t[sa[i] - 1]) sa[lb[ s[sa[i] - 1] ]++] = sa[i] - 1;
    for(int i = n; i     ; --i) if(sa[i] > 1 && !t[sa[i] - 1]) sa[rb[ s[sa[i] - 1] ]--] = sa[i] - 1;
    ns = (int*)mp - 1; mp += sizeof(int) * nn;
    memset(ns + 1, -1, sizeof(int) * (nn));  

    int pre = n + 1, nsig = 0; ns[nn] = 0;
    for(int i = 1, j, k; i <= n; ++i) if(ars[sa[i]]) {
        if(s[sa[i]] == s[pre] && t[sa[i]] == t[pre]) {
            for(j = sa[i] + 1, k = pre + 1; s[j] == s[k] && t[j] == t[k]; ++j, ++k) if(ars[j] && ars[k]) break;
            if(s[j] != s[k] || t[j] != t[k] || !ars[j] || !ars[k]) nsig += 1;
        } else nsig += 1;
        ns[ars[sa[i]]] = nsig; pre = sa[i];
    }

    sa_is(nn - 1, nsig, ns, ars, mp);  

    lb[1] = 1;
    memset(rb + 1, 0, sizeof(int) * sig);
    for(int i = 1, j = 1; i <= n; ++i) rb[s[i]] += 1;
    for(int i = 2; i <= sig; ++i) rb[i] += rb[i - 1], lb[i] = rb[i - 1] + 1;

    memset(sa + 1, -1, sizeof(int) * n);
    for(int i = 1, j = 1; i <= n; ++i) if(t[i] && !t[i + 1]) ns[j++] = i + 1;
    for(int i = nn - 1; i; --i) sa[rb[ s[ ns[ars[i]] ] ]--] = ns[ars[i]];
    for(int i = 1; i < sig; ++i) rb[i] = lb[i + 1] - 1; rb[sig] = n;
    sa[lb[ s[n] ]++] = n;
    for(int i = 1; i <= n; ++i) if(sa[i] > 1 &&  t[sa[i] - 1]) sa[lb[ s[sa[i] - 1] ]++] = sa[i] - 1;
    for(int i = n; i     ; --i) if(sa[i] > 1 && !t[sa[i] - 1]) sa[rb[ s[sa[i] - 1] ]--] = sa[i] - 1;

#undef S
#undef L
    return ;
}


#define $n 1000005

int s[$n], sa[$n];
int buc[$n];

unsigned char mempool[$n * 40];

int sta[100], top = 0;
inline void write_int(int a) {
    while(a) sta[++top] = a % 10, a /= 10;
    while(top) putchar(sta[top--] ^ 48);
    return ;
}

int main() {
    int* s1 = s + 1, n;
    do *s1 = getchar(); while(*s1 == ' ' || *s1 == '\r' || *s1 == '\n');
    do *++s1 = getchar(); while(*s1 != ' ' && *s1 != '\r' && *s1 != '\n' && *s1 != EOF);
    *s1 = '\0';
    n = s1 - s - 1;
    
    for(int i = 1; i <= n; ++i) buc[s[i]] = 1;
    for(int i = 1; i <= 122; ++i) buc[i] += buc[i - 1];
    for(int i = 1; i <= n; ++i) s[i] = buc[s[i]];
    sa_is(n, buc[122], s, sa, mempool);
    
    
    for(int i = 1; i < n; ++i) write_int(sa[i]), putchar(32);
    write_int(sa[n]); putchar(10);
    
    return 0;
}