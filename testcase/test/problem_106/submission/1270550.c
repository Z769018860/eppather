#include <stdio.h>
#include <string.h>

#define RN 50005
#define RS 131080

int ar[30 * RN];
int *cura = ar;

int *zkw[RS];
int sizz[RS];
int st;

void build(int *arr, int siz)
{
    for (st = 1; st < siz; st <<= 1);
    
    for (int i = 0; i < siz; i++)
    {
        zkw[st + i]    = cura++;
        zkw[st + i][0] = arr[i];
        sizz[st + i]   = 1;
    }
    for (int i = siz; i < st; i++)
    {
        zkw[st + i]    = cura++;
        zkw[st + i][0] = 2147483647;
        sizz[st + i]   = 1;
    }
    int l = st >> 1, r = st - 1, len = 2;
    while (l)
    {
        for (int i = l; i <= r; i++)
        {
            zkw[i] = cura;
            cura  += len;
            sizz[i] = len;
            int me = 0, ls = 0, rs = 0;
            while (ls < len >> 1 && rs < len >> 1)
                zkw[i][me++] = zkw[i << 1][ls] < zkw[i << 1 ^ 1][rs] ?
                               zkw[i << 1][ls++] :
                               zkw[i << 1 ^ 1][rs++];
            while (ls < len >> 1)
                zkw[i][me++] = zkw[i << 1][ls++];
            while (rs < len >> 1)
                zkw[i][me++] = zkw[i << 1 ^ 1][rs++];
        }
        r = l - 1, l >>= 1, len <<= 1;
    }
}

static inline int lower_bound(int *arr, int l, int r, int val)
{
    while (l <= r)
    {
        int mid = l + ((r - l) >> 1);
        if (arr[mid] >= val)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return l;
}

static inline int upper_bound(int *arr, int l, int r, int val)
{
    while (l <= r)
    {
        int mid = l + ((r - l) >> 1);
        if (arr[mid] > val)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return l;
}

void modify(int pos, int val)
{
    int x = st + pos;
    int pre = zkw[x][0];
    zkw[x][0] = val;
    x >>= 1;
    while (x)
    {
        int old = lower_bound(zkw[x], 0, sizz[x] - 1, pre);
        int now = upper_bound(zkw[x], 0, sizz[x] - 1, val);
        
        if      (old < now)
        {
            int siz = now - old - 1;
            memmove(zkw[x] + old, zkw[x] + old + 1, sizeof(int) * siz);
            zkw[x][now - 1] = val;
        }
        else if (old > now)
        {
            int siz = old - now;
            memmove(zkw[x] + now + 1, zkw[x] + now, sizeof(int) * siz);
            zkw[x][now] = val;
        }
        else zkw[x][now] = val;
        x >>= 1;
    }
}

int getrnk(int l, int r, int k)
{
    int ret = 0;
    for (l = l + st - 1, r = r + st + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
        if (~l & 1)
            ret += lower_bound(zkw[l ^ 1], 0, sizz[l ^ 1] - 1, k);
        if (r & 1)
            ret += lower_bound(zkw[r ^ 1], 0, sizz[r ^ 1] - 1, k);
    }
    return ret + 1;
}

int getkth(int cl, int cr, int k)
{
    int l = 0, r = 100000000;
    while (l <= r)
    {
        int mid = l + ((r - l) >> 1);
        if (getrnk(cl, cr, mid) > k)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return r;
}

int getpre(int l, int r, int k)
{
    int ret = -2147483647;
    for (l = l + st - 1, r = r + st + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
        if (~l & 1)
        {
            int p = lower_bound(zkw[l ^ 1], 0, sizz[l ^ 1] - 1, k);
            if (p)
                ret = ret > zkw[l ^ 1][p - 1] ? ret : zkw[l ^ 1][p - 1];
        }
        if (r & 1)
        {
            int p = lower_bound(zkw[r ^ 1], 0, sizz[r ^ 1] - 1, k);
            if (p)
                ret = ret > zkw[r ^ 1][p - 1] ? ret : zkw[r ^ 1][p - 1];
        }
    }
    return ret;
}

int getsuf(int l, int r, int k)
{
    int ret = 2147483647;
    for (l = l + st - 1, r = r + st + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
        if (~l & 1)
        {
            int p = lower_bound(zkw[l ^ 1], 0, sizz[l ^ 1] - 1, k + 1);
            if (p < sizz[l ^ 1])
                ret = ret < zkw[l ^ 1][p] ? ret : zkw[l ^ 1][p];
        }
        if (r & 1)
        {
            int p = lower_bound(zkw[r ^ 1], 0, sizz[r ^ 1] - 1, k + 1);
            if (p < sizz[r ^ 1])
                ret = ret < zkw[r ^ 1][p] ? ret : zkw[r ^ 1][p];
        }
    }
    return ret;
}

int n, m;
int arr[RN];

int main(void)
{
    scanf("%d%d", &n, &m);
    arr[0] = 2147483647;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);
    }
    build(arr, n + 1);
    for (int i = 1; i <= m; i++)
    {
        int opr, a, b, c;
        scanf("%d", &opr);
        switch(opr)
        {
            case 1:
            scanf("%d%d%d", &a, &b, &c);
            printf("%d\n", getrnk(a, b, c));
            break;
            case 2:
            scanf("%d%d%d", &a, &b, &c);
            printf("%d\n", getkth(a, b, c));
            break;
            case 3:
            scanf("%d%d", &a, &b);
            modify(a, b);
            break;
            case 4:
            scanf("%d%d%d", &a, &b, &c);
            printf("%d\n", getpre(a, b, c));
            break;
            case 5:
            scanf("%d%d%d", &a, &b, &c);
            printf("%d\n", getsuf(a, b, c));
            break;
        }
    }
    return 0;
}