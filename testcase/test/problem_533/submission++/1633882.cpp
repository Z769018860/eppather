#include <iostream>
#include <cstdio>
#include <algorithm>
#include <limits.h>
#include <cstring>
#include <array>
#include <cmath>
using namespace std;

#define fir first
#define sec second
#define pb push_back
#define bs basic_string
#define lowb lower_bound
#define uppb upper_bound
#define cir(x) rep(__tmp, 1, x)
#define repc(i, n) rep(i, 1, n)
#define perc(i, n) per(i, n, 1)
#define rd(x) scanf("%lld", &(x))
#define all(v) (v).begin(), (v).end()
#define erg(i, pre, x) for(LL (i) = (pre)[x];i;(i) = a[i].next)
#define rep(i, l, r) for(LL (i) = (l), _tmp = (r);(i) <= _tmp;(i)++)
#define per(i, l, r) for(LL (i) = (l), _tmp = (r);(i) >= _tmp;(i)--)
typedef long long LL;
typedef pair<LL, LL> PII;
const LL INF = 0x3f3f3f3f3f3f3f3f, INF_BIT = 0x3f;



LL t;
LL sqm;

#define squ(x) ((x) * (x))

LL mi3[40], mi4[35];
void init(){
    mi3[0] = 1;
    rep(i, 1, 38) mi3[i] = mi3[i - 1] * 3;
    mi4[0] = 1;
    rep(i, 1, 30) mi4[i] = mi4[i - 1] * 4;
}

LL sq_f(LL n){
    if(n <= 14) return n / 2 - 1;
    else if(n == 16) return 3 * 3;
    else if(n == 18) return 3 * 4;
    else if(n == 20) return 4 * 4;
    else if(n == 22) return 4 * 5;
    else if(n == 24) return 3 * 3 * 3;
    else if(n == 26) return 3 * 3 * 4;
    else if(n == 28) return 3 * 4 * 4;
    else if(n == 30) return 4 * 4 * 4;
    n /= 2, n -= 15;
    LL cnt34 = 4 + (n - 1) / 5;
    LL cnt3 = n % 5;
    if(cnt3 == 0) cnt3 = 5;
    cnt3 = 5 - cnt3;
    LL cnt4 = cnt34 - cnt3;
    LL p1 = mi3[cnt3], p2 = mi4[cnt4];
    if(p1 == 0 || p2 == 0) return 1e18;
    if((__int128)p1 * p2 > 1e18) return 1e18;
    return p1 * p2;
}

bool check(LL n){ return sq_f(n) >= sqm; }

void solve(){
    init();
    
    
    
    rd(t);
    while(t--){
        rd(sqm);
        
        LL l = 2, r = 156;
        while(l <= r){
            LL mid = l + (r - l) / 2;
            
            if(check(mid * 2)) r = mid - 1;
            else l = mid + 1;
        }
        
        printf("%lld\n", l * 2);
    }
}

int main(){
    
    
    
    
    
    solve();
    return 0;
}