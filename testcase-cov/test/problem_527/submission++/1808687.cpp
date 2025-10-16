#include <cstdio>
#include <iostream>

const int BUF = 12312313;
char Buf[BUF], *buf = Buf;

inline void read (int &now)
{
    for (now = 0; !isdigit (*buf); ++ buf);
    for (; isdigit (*buf); now = now * 10 + *buf - '0', ++ buf);
}

#define Max 1005
int h[Max][Max], l[Max][Max], Answer;

int Main ()
{
    fread (buf, 1, BUF, stdin);
    int N, M, x; read (N), read (M); register int i, j, k;
    for (i = 1; i <= N; ++ i)
        for (j = 1; j < M; ++ j) read (h[i][j]);
    for (i = 1; i < N; ++ i)
        for (j = 1; j <= M; ++ j) read (l[i][j]);
    for (i = 1; i <= N; ++ i)
        for (j = M - 2; j; -- j) 
            if (h[i][j]) h[i][j] += h[i][j + 1];
    for (j = 1; j <= M; ++ j)
        for (i = N - 2; i; -- i) 
            if (l[i][j]) l[i][j] += l[i + 1][j];
    for (i = 1; i < N; ++ i)
        for (j = 1; j < M; ++ j)
            for (k = 1; h[i][j] >= k && l[i][j] >= k; ++ k)    
                if (h[i + k][j] >= k && l[i][j + k] >= k) ++ Answer;
    printf ("%d", Answer);    
    return 0;
}

int ZlycerQan = Main ();
int main (int argc, char *argv[]) {;}