#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <ctime>
#include <bitset>
using namespace std;

#define lb(x) ((x) & (-x))
#define int __int128
#define l(p) t[p].l
#define r(p) t[p].r
#define lz(p) t[p].lz
#define double long double
#define ff first
#define ss second
#define mr make_pair
const int mod = 998244353 ;
const int dlt = 1e6 + 2 ;
void cmin(int &x, int y) {
    x = min(x, y) ;
}
void cmax(int &x, int y) {
    x = max(x, y) ;
}
int read() {
    char ch ;int s = 0 ;int w = 1;
    while((ch = getchar()) >'9' || ch < '0' )if(ch == '-')w = -1 ;
    while(ch >= '0' && ch <= '9')s = (s << 1) + (s << 3) + (ch ^ 48) , ch = getchar() ;
    return s * w ;
}
void print(int x) {
    if(x < 0) putchar('-'), x = -x ;                  
    if(x > 9)print(x / 10) ;
    putchar(x % 10 + '0') ;
}                                   
void prn(int x) {      
    print(x) ;                                          
    putchar('\n') ;            
} 
int pows(int x) {
    int k = mod - 2 ;
    int bace = x, ans = 1 ;
    while(k) {
        if(k & 1) ans *= bace, ans %= mod ;
        bace *= bace, bace %= mod ;
        k >>= 1 ;
    }
    return ans ;
}
int pows(int x, int k) {
    int bace = x, ans = 1 ;
    while(k) {
        if(k & 1) ans *= bace, ans %= mod ;
        bace *= bace, bace %= mod ;
        k >>= 1 ;
    }
    return ans ;
}
int T ;
int n, m ;
int a[1000005] ;
int a0, a1, k ;
int s[1000005] ;
map<int, int> mp ;
int Aabs(int x) {
    return x > 0 ? x : -x ;
}
bool check(int x, int z, int f) {
    if(x > 0) {
        if(x > z) return 1 ;
        return 0 ;
    }
    if(x < 0) {
        if(x < f) return 1 ;
        return 0 ;
    }
}
void work() {
    a0 = read(), a1 = read(), k = read() ;
    a[0] = a0, a[1] = a1 ;
    if(a[0] == a[1] && a[0] == 0) {
        print(s[1]) ;cout << ' ' ;prn(s[1]) ;
        return ;
    }
    int now = 1 ;
    int maxnz = max(a[0], a[1]) ;
    int maxnf = min(a[0], a[1]) ;
    
    for(int i = 2 ; ; i++) {
        now = i ;
        a[i] = a[i - 1] * k + a[i - 2] ;
        
        if(a[i] * a[i - 1] > 0 && check(a[i], maxnz, maxnf)) break ;
        cmax(maxnz, a[i]) ;
        cmin(maxnf, a[i]) ;
    }
    int maxn = -1, minn = -1 ;
    for(int i = 0 ; i <= now ; i++) {
        
        if(mp[i]) {
            if(maxn == -1 || a[i] > a[maxn]) maxn = i ;
            if(minn == -1 || a[i] < a[minn]) minn = i ;
        }
    }
    if(a[now] > 0 && s[m] >= now) maxn = s[m] ;
    if(a[now] < 0 && s[m] >= now) minn = s[m] ;
    if(maxn == -1) {
        maxn = s[1] ;
    }
    if(minn == -1) minn = s[1] ;
    print(maxn) ;cout << ' ' ;prn(minn) ;
    return ;
}
signed main() {
    
    
    m = read() ;for(int i = 1 ; i <= m ; i++) s[i] = read(), mp[s[i]] = 1 ;
    T = read() ;
    while(T--) {

        work() ;
    }
    return 0 ;
}

