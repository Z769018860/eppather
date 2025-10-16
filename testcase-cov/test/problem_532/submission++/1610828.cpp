#include <map>
#include <set>
#include <queue>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#define pii pair <int , int>
#define pll pair <LL , LL>
#define mp make_pair
#define fs first
#define sc second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;





template <typename T>
void read(T &x) {
	T f=1;x=0;char s=getchar();
	while(s<'0'||s>'9') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=(x<<3)+(x<<1)+(s-'0');s=getchar();}
	x *= f;
}

template <typename T>
void write(T x , char s='\n') {
	if(!x) {putchar('0');putchar(s);return;}
	if(x<0) {putchar('-');x=-x;}
	T tmp[25]={},t=0;
	while(x) tmp[t++]=x%10,x/=10;
	while(t-->0) putchar(tmp[t]+'0');
	putchar(s); 
}

const int MAXN = 2e6 + 5;
const int mod = 1e9 + 7;

inline int Add(int x , int y) {x += y;return x >= mod?x - mod:x;}
inline int Sub(int x , int y) {x -= y;return x < 0?x + mod:x;}
inline int Mul(int x , int y) {return 1ll * x * y % mod;}

int A , B , C , X0 , f[MAXN] , vis[MAXN] , cir[MAXN];
int v1[MAXN] , v2[MAXN] , suf1[MAXN] , suf2[MAXN];
LL L1 , R1 , L2 , R2;

int main() {
    read(A),read(B),read(C),read(X0),read(L1),read(R1),read(L2),read(R2);
    memset(vis , -1 , sizeof vis);
    f[0] = X0;
    int pre = 0 , l = 0;
    for (int i = 1; i <= C + 1; ++i) {
        f[i] = (1ll * A * f[i - 1] % C + B) % C + 1;
        if(vis[f[i]] == -1) vis[f[i]] = i;
        else {
            for (int j = vis[f[i]]; j < i; ++j) cir[f[j]] = 1;
            pre = vis[f[i]] - 1;
            l = i - vis[f[i]];
            break;
        }
    }
    for (int i = 1; i <= C; ++i) if(vis[i] != -1) {
        if(cir[i]) {
            v1[i] = (max(R1 - pre , 0ll) / l + (vis[i] - pre <= (R1 - pre) % l) - max(L1 - 1 - pre , 0ll) / l - (vis[i] - pre <= (L1 - 1 - pre) % l)) % mod;
            v2[i] = (max(R2 - pre , 0ll) / l + (vis[i] - pre <= (R2 - pre) % l) - max(L2 - 1 - pre , 0ll) / l - (vis[i] - pre <= (L2 - 1 - pre) % l)) % mod;
        }
        else v1[i] = (L1 <= vis[i] && vis[i] <= R1) , v2[i] = (L2 <= vis[i] && vis[i] <= R2);
    }
    for (int i = C; i >= 1; --i) {
        suf1[i] = Add(suf1[i + 1] , v1[i]);
        suf2[i] = Add(suf2[i + 1] , v2[i]);
    }
    int ans = 0;
    for (int i = 1; i <= C; ++i) {
        
        ans = Sub(ans , Mul(2 , Mul(v1[i] , v2[i])));
        if(!v1[i] && !v2[i]) continue;
        int ls = i;
        for (int j = i * 2; ls <= C; j += i) {
            int t = (j / i);
            int x = ceil((t * i + sqrt((long double)t * t * i * i - 4.0 * i * i)) / 2.0 + 1e-9);
            ans = Add(ans , Mul(t , Mul(Sub(suf1[ls] , suf1[min(C + 1 , x)]) , v2[i])));
            ans = Add(ans , Mul(t , Mul(Sub(suf2[ls] , suf2[min(C + 1 , x)]) , v1[i])));
            ls = x;
        }
    }
    write(ans);
    return 0;
}