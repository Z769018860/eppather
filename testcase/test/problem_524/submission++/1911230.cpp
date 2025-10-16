#include <bits/stdc++.h>

#define AC true
#define dub double
#define ull unsigned long long
#define mar(x) for(int i = head[x]; i; i = e[i].nxt)
#define car(a) memset(a, 0, sizeof(a))
constexpr int inf = 1e9 + 7;
constexpr int MAXN = 5e5;
constexpr dub eps = 1e-5;
constexpr int mod = 998244353;
#define db if(1)
bool ___f1___;
using namespace std;

void cmi(int &x, int y){x > y && (x = y);}
void cmx(int &x, int y){x < y && (x = y);}
inline int read( ){
    int x = 0 ; short w = 0 ; char ch = 0;
    while( !isdigit(ch) ) { w|=ch=='-';ch=getchar();}
    while( isdigit(ch) ) {x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return w ? -x : x;
}
int n, tot;
int a[MAXN], b[MAXN];
struct BIT{
    #define lowbit(x) x & (-x)
    int tr[MAXN];
    void add(int x, int val){
        while(x <= tot){tr[x] += val; x += lowbit(x);}
    }
    int ask(int x){
        int res = 0;
        while(x){res += tr[x]; x -= lowbit(x);}
        return res;
    }
} T_T;

bool ___f2___;
signed main( ){
#ifdef local
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
#endif
    int cnt = 0;
    n = read( );
    for(int i = 1; i <= n; i++){
        char c; cin >> c;
        if(c == 'X') cnt++;
        else{
            int res = 0, w = 1;
            if(c == '-') w = -1, c = getchar( );
            while(c < '0' or c > '9') c = getchar( );
            while(c >= '0' and c <= '9'){
                res = res * 10 + c - '0';
                c = getchar( );
            }
            tot++;
            a[tot] = b[tot] = res * w;
        }
    }
    if(n == 1){
        puts("L");
        return 0;
    }
    if(cnt == 0){
        sort(b + 1, b + tot + 1);
        n = tot;
        int res = 0;
        tot = unique(b + 1, b + tot + 1) - b - 1;
        for(int i = n; i >= 1; i--){
            a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
            T_T.add(a[i], 1);
            res += T_T.ask(a[i] - 1);
        }
        if(res & 1) puts("W");
        else puts("L");
        return 0;
    }
    if(cnt & 1) puts("W");
    else puts("L");
#ifdef local
    putchar('\n');
    printf("MLE:%lld\n",((&___f2___)-(&___f1___))/1024/1024);
    printf("TLE:%d\n",(int)clock( ));
#endif
    return (0-0);
}