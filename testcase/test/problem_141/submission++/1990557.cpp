#include <cstdio>
#include <cstring>

#define rep( i, l, r ) for ( int i = l, rep##i = r; i <= rep##i; ++i )
#define per( i, r, l ) for ( int i = r, per##i = l; i >= per##i; --i )

typedef long long LL;

const int MAXN = 4e5, MAXL = 7e5;
char s[MAXL + 10];
int ptrf, ptrb;

struct PalindromeAutomaton {
    int node, len[MAXN + 5], fail[MAXN + 5], ch[MAXN + 5][26];
    int rlas, llas, dep[MAXN + 5];

    PalindromeAutomaton() {
        node = rlas = llas = 1, len[1] = -1, fail[0] = 1;
    }

    inline int pushF(char c) {
        s[--ptrf] = c, c -= 'a';
        int p = llas;

        for (; s[ptrf + len[p] + 1] != s[ptrf]; p = fail[p]);

        if (!ch[p][c]) {
            len[++node] = len[p] + 2;
            int q = fail[p];

            for (; s[ptrf + len[q] + 1] != s[ptrf]; q = fail[q]);

            dep[node] = dep[fail[node] = ch[q][c]] + 1, ch[p][c] = node;
        }

        llas = ch[p][c];

        if (len[llas] == ptrb - ptrf + 1)
            rlas = llas;

        return dep[llas];
    }

    inline int pushB(char c) {
        s[++ptrb] = c, c -= 'a';
        int p = rlas;

        for (; s[ptrb - len[p] - 1] != s[ptrb]; p = fail[p]);

        if (!ch[p][c]) {
            len[++node] = len[p] + 2;
            int q = fail[p];

            for (; s[ptrb - len[q] - 1] != s[ptrb]; q = fail[q]);

            dep[node] = dep[fail[node] = ch[q][c]] + 1, ch[p][c] = node;
        }

        rlas = ch[p][c];

        if (len[rlas] == ptrb - ptrf + 1)
            llas = rlas;

        return dep[rlas];
    }
} pam;

int main() {
    ptrf = (ptrb = 3e5) + 1;
    LL ans = 0;

    for (char c; 'a' <= (c = getchar()) && c <= 'z';
            ans += pam.pushB(c));

    int q, op;
    char tmp[1005];

    for (scanf("%d", &q); q--;) {
        scanf("%d", &op);

        if (op == 1) {
            scanf("%s", tmp);

            for (int i = 0; tmp[i]; ans += pam.pushB(tmp[i++]));
        } else if (op == 2) {
            scanf("%s", tmp);

            for (int i = 0; tmp[i]; ans += pam.pushF(tmp[i++]));
        } else {
            printf("%lld\n", ans);
        }
    }

    return 0;
}