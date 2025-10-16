#include <bits/stdc++.h>
typedef long long ll;

char In[1 << 21], *p1 = In, *p2 = In, c, Out[1 << 22], *Op = Out, St[10], *Tp = St;
#define Getc (p1==p2&&(p2=(p1=In)+fread(In,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline ll Gll(ll x = 0) {
    while (!isdigit(c = Getc))
        ;

    for (; isdigit(c); c = Getc)
        x = x * 10 + (c ^ 48);

    return x;
}
inline void Pll(ll x) {
    do
        *Tp++ = x % 10 ^ 48;

    while (x /= 10)
        ;

    do
        *Op++ = *--Tp;

    while (Tp != St)
        ;

    *Op++ = '\n';
}

ll f[155];
int main() {
    for (int i = 2, j; i <= 150; ++i)
        for (f[i] = i - 1, j = 2; j <= 6 && j <= i - 1; ++j)
            f[i] = std::max(f[i], f[i - j] * (j - 1));

    for (int T = Gll(); T--;)
        Pll((std::lower_bound(f + 1, f + 151, Gll()) - f) << 1);

    return fwrite(Out, 1, Op - Out, stdout), 0;
}