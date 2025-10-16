
#include <stdio.h>
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#define maxn 100010
inline void swap(int &a, int &b) { a ^= b, b ^= a, a ^= b; }
inline void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}
inline int read()
{
    int k = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        k = (k << 1) + (k << 3) + c - 48;
        c = getchar();
    }
    return k * f;
}
int ch[maxn][2], fa[maxn]; 
int val[maxn];             
int npl[maxn];             
int root[maxn];            
int extra_memory;
int n, m;
int op, a, b;
int get_root(int x)
{
    return root[x] == x ? x : root[x] = get_root(root[x]);
}
int merge(int a, int b)
{
    if (!a || !b)
        return a + b;
    
    if (val[a] > val[b] || (val[a] == val[b] && a > b))
        swap(a, b);
    
    ch[a][1] = merge(ch[a][1], b); 
    fa[ch[a][1]] = a;              
    if (npl[ch[a][0]] < npl[ch[a][1]])
        swap(ch[a][0], ch[a][1]);
    
    root[ch[a][0]] = root[ch[a][1]] = root[a] = a;
    npl[a] = npl[ch[a][1]] + 1; 
    return a;                   
}
void insert(int x, int e)
{
    
    val[extra_memory] = e;
    npl[extra_memory] = 1;
    x = merge(x, extra_memory);
    extra_memory++;
}
int top(int x)
{
    
    int y = get_root(x);
    return val[y];
}
void pop(int x)
{
    val[x] = -1;
    fa[ch[x][0]] = fa[ch[x][1]] = 0;
    root[ch[x][0]] = root[ch[x][1]] = root[x] = merge(ch[x][0], ch[x][1]);
}
int main()
{
    n = read(), m = read();
    extra_memory = n + 1;
    for (int i = 1; i <= n; ++i)
        npl[i] = 1, root[i] = i, val[i] = read();
    while (m--)
    {
        op = read();
        if (op == 1)
        {
            a = read(), b = read();
            if (val[a] == -1 || val[b] == -1)
                continue;
            int roota = get_root(a), rootb = get_root(b);
            if (roota == rootb)
                continue;
            root[roota] = root[rootb] = merge(roota, rootb);
        }
        else
        {
            a = read();
            if (val[a] == -1)
                puts("-1");
            else
            {
                int root = get_root(a);
                write(val[root]);
                putchar('\n');
                pop(root);
            }
        }
    }
}