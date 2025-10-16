#include <bits/stdc++.h>

using namespace std;

#define Please return
#define AC 0

namespace Fast_IO {
const int BUF_SIZE = 1 << 20;
char BUF_R[BUF_SIZE], *csy1, *csy2;
char read_char() {
    return csy1 == csy2 &&
           (csy2 = (csy1 = BUF_R) + fread(BUF_R, 1, BUF_SIZE, stdin), csy1 == csy2) ? EOF : *csy1 ++;
}
template <class T>
void read_int(T &t) {
    int u = 0;
    char c = read_char();

    for (t = 0; c < 48 || c > 57; c = read_char()) {
        if (c == EOF)
            return;

        if (c == '-')
            u = 1;
    }

    for (; c > 47 && c < 58; c = read_char())
        t = (t << 1) + (t << 3) + (c ^ 48);

    t = u ? -t : t;
}
char BUF_W[BUF_SIZE], *csy = BUF_W;
void write_char(const char &c) {
    if (csy - BUF_W == BUF_SIZE)
        fwrite(BUF_W, 1, BUF_SIZE, stdout), csy = BUF_W;

    *csy ++ = c;
}
template <class T>
void write_int(T x) {
    static int sta[32], top;

    if (x < 0) {
        write_char('-');

        do
            sta[top ++] = - (x % 10);

        while (x /= 10);
    } else
        do
            sta[top ++] = x % 10;

        while (x /= 10);

    while (top)
        write_char(sta[-- top] ^ 48);
}
void flush() {
    if (csy - BUF_W > 0)
        fwrite(BUF_W, 1, csy - BUF_W, stdout);

    csy = BUF_W;
}
}
using namespace Fast_IO;

const int MAX_N = 1000000 + 5;
int n, q, fa[MAX_N], son[MAX_N], bro[MAX_N];
int tot, dep[MAX_N], node[MAX_N], closest[MAX_N];
bool circle[MAX_N], sg[MAX_N];

void dfs(int u) {
    dep[u] = dep[fa[u]] + 1;

    for (int v = son[u]; v; v = bro[v])
        if (v > 1) {
            dfs(v);

            if (circle[v])
                circle[u] = 1;
            else if (!sg[v])
                sg[u] = 1;
        } else {
            tot = dep[u];
            circle[u] = 1;
        }

    if (circle[u])
        node[dep[u]] = u;
}

#define find Kosuzu
int find(const int &x, const int &y) {
    return closest[x] <= y ? closest[x] : 0;
}

int main() {
    read_int(n);
    read_int(q);

    for (int i = 1; i <= n; i ++) {
        read_int(fa[i]);
        bro[i] = son[fa[i]];
        son[fa[i]] = i;
    }

    dfs(1);

    for (int i = tot; i > 0; i --)
        closest[i] = sg[node[i]] ? i : closest[i + 1];

    while (q --) {
        int u, v, c;
        read_int(u);
        read_int(v);

        if (u == 1 || dep[v] < dep[u]) {
            if (c = find(1, dep[v]))
                write_char(((c & 1) ^ 48)), write_char('\n');
            else if ((((c = find(dep[v], dep[fa[u]])) ? c : c = dep[fa[u]] + 1) - dep[v] + 1) & 1)
                write_char(((c & 1) ^ 48)), write_char('\n');
            else if (u != 1 && (c = find(dep[u], tot)))
                write_char((((c - dep[v] + dep[u] + 1) & 1) ^ 48)), write_char('\n');
            else
                write_char(50), write_char('\n');
        } else if (c = find(1, dep[fa[u]])) {
            write_char(((c & 1) ^ 48)), write_char('\n');
        } else
            write_char(((dep[u] & 1) ^ 48)), write_char('\n');
    }

    flush();
    Please AC;
}