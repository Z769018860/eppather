#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define RN 100005
#define RM 200005



typedef int I;
typedef char C;
typedef double F;
typedef int L;

typedef struct
{
    L a;
    I b;
}
P;



typedef struct
{
    I nxt;
    I to;
    I len;
}
Edge;
Edge edge_pool[RM];
I    ecnt;

#define enode(x) edge_pool[x]
#define enxt(x)  enode(x).nxt
#define eto(x)   enode(x).to
#define elen(x)  enode(x).len



P heap[RN];
I htop;

static inline I cmph(P a, P b)
{
    return a.a < b.a;
}

static inline void uph(I x)
{
    P tmp = heap[x];
    for (I f; cmph(tmp, heap[f = x >> 1]) && f; x = f)
    {
        heap[x] = heap[f];
    }
    heap[x] = tmp;
}

static inline void downh(I x)
{
    P tmp = heap[x];
    for (I s; (s = x << 1) <= htop; x = s)
    {
        if (s < htop && cmph(heap[s + 1], heap[s]))
            s++;
        if (cmph(tmp, heap[s]))
            break;
        heap[x] = heap[s];
    }
    heap[x] = tmp;
}

static inline void pushh(P x)
{
    heap[++htop] = x;
    uph(htop);
}

static inline void poph(void)
{
    heap[1] = heap[htop--];
    downh(1);
}



L dis[RN];
C vis[RN];

void dijkstra(I s)
{
    extern I head[RN];
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));

    dis[s] = 0;
    pushh((P){0, s});

    while (htop)
    {
        P u = heap[1];   
        poph();
        if (vis[u.b])
            continue;
        vis[u.b] = 1;
        for (I i = head[u.b]; i; i = enxt(i))
        {
            I v = eto(i);
            if (dis[v] > u.a + elen(i))
            {
                dis[v] = u.a + elen(i);
                if (!vis[v])
                {
                    pushh((P){dis[v], v});
                }
            }
        }
    }
}



I head[RN];
I n, m, s, t;

int main(void)
{
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (I i = 1; i <= m; i++)
    {
        I u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        enode(++ecnt) = (Edge){head[u], v, w};
        head[u] = ecnt;
        enode(++ecnt) = (Edge){head[v], u, w};
        head[v] = ecnt;
    }
    dijkstra(s);
    printf("%d\n", dis[t]);
    return 0;
}