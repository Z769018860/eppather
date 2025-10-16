#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

#ifdef __WIN32
#define LLFORMAT "I64"
#define Rand() ((rand() << 15) | rand())
#else
#define LLFORMAT "ll"
#define Rand() (rand())
#endif

template<typename T> inline bool chkmin(T &a, const T &b) {
    return b < a ? a = b, 1 : 0;
}
template<typename T> inline bool chkmax(T &a, const T &b) {
    return a < b ? a = b, 1 : 0;
}

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int __buffsize = 100000;
char __buff[__buffsize];
char *__buffs, *__buffe;

#define getc() (__buffs == __buffe ? fread(__buff, 1, __buffsize, stdin), __buffe = __buff + __buffsize, *((__buffs = __buff)++) : *(__buffs++))

template<typename T> inline T &Read(T &x) {
    static char c;

    while (1) {
        c = getc();

        if (c == '-' || (c >= '0' && c <= '9'))
            break;
    }

    bool flag = c == '-';
    x = flag ? 0 : c - '0';

    while (1) {
        c = getc();

        if (c < '0' || c > '9')
            break;

        (x *= 10) += c - '0';
    }

    if (flag)
        x = -x;

    return x;
}

#undef getc

const int maxabs = 2.01e5;

struct node {
    int Min;
    int sz;
    int label;
    LL sumlr, sumrl;

    node *c[2];

    node(): Min(0), sz(0), label(0), sumlr(0), sumrl(0) { }

    void update() {
        Min = oo;
        REP(i, 0, 2) {
            chkmin(Min, c[i]->Min);
        }
    }

    void flag_label(int _label) {
        label += _label;
        Min += _label;
    }

    void push_down() {
        if (label) {
            REP(i, 0, 2) c[i]->flag_label(label);
            label = 0;
        }
    }

};

const int max0 = 100000;

node *nd_pool;
int nd_res = 0;

inline node *newnode() {
    if (!nd_res)
        nd_pool = new node[max0], nd_res = max0;

    return nd_pool + (--nd_res);
}

void build(node *&rt, int l, int r) {
    rt = newnode();

    if (r - l <= 1) {
        rt->Min = l;
        return;
    }

    int mid = (l + r) >> 1;
    build(rt->c[0], l, mid);
    build(rt->c[1], mid, r);
    rt->sumlr = 0;
    rt->sumrl = LL(l + mid + 1) * (mid - l) >> 1;
    rt->update();
}

int seg_x, seg_y, seg_z, seg_ret;

void change_sz(node *rt, int l, int r) {
    rt->sz += seg_z;

    if (r - l <= 1) {
        return;
    }

    int mid = (l + r) >> 1;

    if (seg_x < mid)
        change_sz(rt->c[0], l, mid);
    else
        change_sz(rt->c[1], mid, r);
}

int go_x, go_y;

int seg_cur;

inline LL golr(node *rt, int l, int r) {
    if (r - l <= 1) {
        LL ret = (LL)l * max(0, seg_cur - rt->Min);
        chkmin(seg_cur, rt->Min);
        return ret;
    }

    rt->push_down();
    int mid = (l + r) >> 1;

    if (go_x <= l && r <= go_y) {
        if (seg_cur > rt->c[0]->Min) {
            LL ret = golr(rt->c[0], l, mid) + rt->sumlr;
            chkmin(seg_cur, rt->c[1]->Min);
            return ret;
        } else
            return golr(rt->c[1], mid, r);
    }

    LL ret = 0;

    if (go_x < mid)
        ret += golr(rt->c[0], l, mid);

    if (go_y > mid)
        ret += golr(rt->c[1], mid, r);

    return ret;
}

inline LL gorl(node *rt, int l, int r) {
    if (r - l <= 1) {
        LL ret = (l + 1) * (rt->Min < seg_cur);
        chkmin(seg_cur, rt->Min);
        return ret;
    }

    rt->push_down();
    int mid = (l + r) >> 1;

    if (go_x <= l && r <= go_y) {
        if (seg_cur > rt->c[1]->Min) {
            LL ret = gorl(rt->c[1], mid, r) + rt->sumrl;
            chkmin(seg_cur, rt->c[0]->Min);
            return ret;
        } else
            return gorl(rt->c[0], l, mid);
    }

    LL ret = 0;

    if (go_y > mid)
        ret += gorl(rt->c[1], mid, r);

    if (go_x < mid)
        ret += gorl(rt->c[0], l, mid);

    return ret;
}

void modify(node *rt, int l, int r) {
    if (seg_x <= l && r <= seg_y) {
        rt->flag_label(-seg_z);
        return;
    }

    rt->push_down();
    int mid = (l + r) >> 1;

    if (seg_x < mid)
        modify(rt->c[0], l, mid);

    if (seg_y > mid)
        modify(rt->c[1], mid, r);

    seg_cur = rt->c[0]->Min;
    rt->sumlr = golr(rt->c[1], mid, r);
    seg_cur = rt->c[1]->Min;
    rt->sumrl = gorl(rt->c[0], l, mid);
    rt->update();
}

void query_sz(node *rt, int l, int r) {
    if (seg_x <= l && r <= seg_y) {
        seg_ret += rt->sz;
        return;
    }

    int mid = (l + r) >> 1;

    if (seg_x < mid)
        query_sz(rt->c[0], l, mid);

    if (seg_y > mid)
        query_sz(rt->c[1], mid, r);
}

void query_Min(node *rt, int l, int r) {
    if (seg_x <= l && r <= seg_y) {
        chkmin(seg_ret, rt->Min);
        return;
    }

    rt->push_down();
    int mid = (l + r) >> 1;

    if (seg_x < mid)
        query_Min(rt->c[0], l, mid);

    if (seg_y > mid)
        query_Min(rt->c[1], mid, r);
}

const int maxn = 100100;

node *rt;

int n, qn;
int a[maxn + 5];

int main() {
#ifdef matthew99
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    Read(n), Read(qn);
    build(rt, 0, maxabs);
    REP(i, 0, n) {
        Read(a[i]);
        seg_x = a[i], seg_y = maxabs, seg_z = 1;
        go_x = 0, go_y = maxabs;
        change_sz(rt, 0, maxabs);
        modify(rt, 0, maxabs);
    }
    REP(i, 0, qn) {
        int ty;
        Read(ty);

        if (ty == 1) {
            int x, y;
            Read(x), Read(y), --x;
            seg_x = a[x], seg_y = maxabs, seg_z = -1;
            go_x = 0, go_y = maxabs;
            change_sz(rt, 0, maxabs);
            modify(rt, 0, maxabs);
            a[x] = y;
            seg_x = a[x], seg_y = maxabs, seg_z = 1;
            go_x = 0, go_y = maxabs;
            change_sz(rt, 0, maxabs);
            modify(rt, 0, maxabs);
        } else if (ty == 2) {
            int l, r;
            Read(l), Read(r);
            seg_x = 0, seg_y = l, seg_ret = 0;
            query_sz(rt, 0, maxabs);
            int Max = l - seg_ret;

            if (l < r) {
                seg_x = l, seg_y = r, seg_ret = oo;
                query_Min(rt, 0, maxabs);
                chkmin(Max, seg_ret);
            }

            seg_x = r, seg_y = maxabs, seg_ret = oo;
            query_Min(rt, 0, maxabs);
            int Min = seg_ret;

            if (Max <= Min)
                printf("0\n");
            else {
                LL ans = 0;
                go_x = 0, go_y = l;
                seg_cur = Max;
                ans += gorl(rt, 0, maxabs);
                seg_cur = Min;
                ans -= gorl(rt, 0, maxabs);
                go_x = r, go_y = maxabs;
                seg_cur = Max;
                ans += golr(rt, 0, maxabs);
                printf("%" LLFORMAT "d\n", ans);
            }
        }
    }
    return 0;
}