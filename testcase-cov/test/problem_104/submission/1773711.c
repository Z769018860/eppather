#include<stdio.h>
#define rch(x) x = getchar()
#define N 100100
int read() {
    int res = 0, f = 1;
    char rch(c);
    while(c<'0'||c>'9')
        f = (c=='-'?-1:1), rch(c);
    while(c>='0'&&c<='9')
        res = res*10+c-48, rch(c);
    return res*f;
}
int n, m, p[N], ch[N][2], val[N], cnt[N], sz[N], tot, rt;
int get(int x) {
    return x==ch[p[x]][1];
}
int nn(int v) {
    tot++;
    val[tot] = v, cnt[tot] = 1, sz[tot] = 1;
    return tot;
}
void maintain(int x) {
    sz[x] = cnt[x]+sz[ch[x][0]]+sz[ch[x][1]];
}
void clear(int x) {
    ch[x][0] = ch[x][1] = p[x] = val[x] = sz[x] = cnt[x] = 0;
}
void rotate(int x) {
    int y = p[x], z = p[y], side = get(x);
    ch[y][side] = ch[x][1-side];
    if (ch[x][1-side]) 
        p[ch[x][1-side]] = y;
    ch[x][1-side] = y;
    p[y] = x;
    p[x] = z;
    if (z)
        ch[z][y == ch[z][1]] = x;
    maintain(y);
    maintain(x);
}
void splay(int x) {
    for(int f = p[x]; (f = p[x]); rotate(x))
        if(p[f])
            rotate(get(f)==get(x)?f:x);
    rt = x;
}
int pre() {
    int cur = ch[rt][0];
    if (!cur) return cur;
    while (ch[cur][1])
        cur = ch[cur][1];
    splay(cur);
    return cur;
}
int nxt() {
    int cur = ch[rt][1];
    if (!cur) return cur;
    while (ch[cur][0])
        cur = ch[cur][0];
    splay(cur);
    return cur;
}
int merge(int x, int y) {
    p[x] = p[y] = 0;
    if(!x||!y)
        return x|y;
    x = pre();
    ch[x][1] = y;
    p[y] = x;
    return x;
}
void ins(int v) {
    if (!rt) {
        rt = nn(v);
        return;
    }
    int cur = rt, f = 0;
    while (1) {
        if (val[cur] == v) {
            cnt[cur]++;
            maintain(cur);
            maintain(f);
            splay(cur);
            break;
        }
        f = cur;
        cur = ch[cur][val[cur] < v];
        if (!cur) {
            cur = nn(v);
            p[cur] = f;
            ch[f][val[f]<v] = cur;
            maintain(f);
            splay(cur);
            break;
        }
    }
}
void del(int v) {
    int cur = rt;
    while(1) {
        if(val[cur]==v)
            break;
        if(!cur)
            return;
        cur = ch[cur][val[cur] < v];
    }
    splay(cur);
    if(cnt[rt] > 1)
        cnt[rt]--;
    else {
        int temp = rt;
        rt = merge(ch[rt][0], ch[rt][1]);
        maintain(rt);
        clear(temp);
    }
}
int rk(int v){
    int cur = rt, res = 1, f = 0;
    while(cur) {
        if(val[cur]==v) {
            res+=sz[ch[cur][0]];
            break;
        }
        if(v>val[cur])
            res+=cnt[cur]+sz[ch[cur][0]];
        f = cur;
        cur = ch[cur][val[cur] < v];
    }
    if(cur)
        splay(cur);
    else if(f)
        splay(f);
    return res;
}
int kth(int k) {
    int cur = rt, passed = 0;
    while(1) {
        if(passed+sz[ch[cur][0]] >= k)
            cur = ch[cur][0];
        else if(passed+sz[ch[cur][0]] + cnt[cur] >= k)
            break;
        else    
            passed+=sz[ch[cur][0]] + cnt[cur], cur = ch[cur][1];
    }
    splay(cur);
    return val[cur];
}
signed main() {
    int q = read();
    while(q--) {
        int op = read(), x = read();
        switch(op) {
            case 1: ins(x);
            break;
            case 2: del(x);
            break;
            case 3: printf("%d\n",rk(x));
            break;
            case 4: printf("%d\n",kth(x));
            break;
            case 5: ins(x), printf("%d\n",val[pre()]), del(x);
            break;
            default: ins(x), printf("%d\n",val[nxt()]), del(x);
        }
    }
}