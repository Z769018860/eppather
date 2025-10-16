#include <bits/stdc++.h>
#define rint register int
#define rep(i, x, y) for (int i = x; i <= y; ++i)
#define repe(i, x) for (edge *i = fst[x]; i; i = i->nxt)

inline int Gint(rint x = 0) {
    static char In[1 << 20], *p1 = In, *p2 = In, c;
#define Getc (p1 == p2 && (p2 = (p1 = In) + fread(In, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)

    while (!isdigit(c = Getc))
        ;

    for (; isdigit(c); c = Getc)
        x = x * 10 + (c ^ 48);

    return x;
}
char Out[2000010], *Outp = Out;
inline void Pint(int x) {
    *Outp++ = x ^ 48, *Outp++ = '\n';
}

using namespace std;
const int N = 1e6 + 10;
struct edge {
    int v;
    edge *nxt;
} pool[N], *tp = pool, *fst[N];
bool f[N];
int n, m, deg[N], q[N], h = 1, t, id[N], pre[N];

int main() {
    n = Gint(), m = Gint();
    rep(u, 1, n) {
        int v = Gint();
        *tp = (edge) { v, fst[u] }, fst[u] = tp++, ++deg[v];
    }

    rep(i, 1, n) if (!deg[i])
        q[++t] = i;

    for (int u, v; h <= t;)
        repe(i, u = q[h++]) if (f[v = i->v] |= !f[u], !--deg[v])
            q[++t] = v;

    if (!deg[1] || f[1]) {
        for (; m--; printf("%d\n", f[1]))
            ;

        return 0;
    }

    n = n - t, t = 0;

    for (int x = 1, v; t < n; id[x] = t, pre[t] = !t || f[x] ? t : pre[t - 1], ++t, x = v)
        repe(i, x) if (deg[v = i->v])
            break;

    id[1] = n, pre[n] = pre[n - 1];

    for (int u, v; m--;)
        if (u = id[Gint()], v = id[Gint()], t = pre[n], u == n)
            if (t < v)
                Pint((v - t + 1) & 1 ? (n - v + 1) & 1 : 2);
            else
                Pint((n - t + 1) & 1);
        else if (u < v)
            if (t >= v)
                Pint((n - t + 1) & 1);
            else if (t <= u)
                if ((v - u + 1) & 1)
                    Pint((n - v + 1) & 1);
                else
                    Pint(t ? (n - v + u - t) & 1 : 2);
            else if ((v - t + 1) & 1)
                Pint((n - v + 1) & 1);
            else
                Pint(pre[u] ? (n - v + u - pre[u]) & 1 : 2);
        else
            Pint((n - max(t, u) + 1) & 1);

    fwrite(Out, 1, Outp - Out, stdout);
    return 0;
}