#pragma GCC optimize(2)
#include <bits/stdc++.h>
#include <ext/rope>

#define lowbit(x) (x&-x)
#define SZ(x) ((int)x.size())
#define all(x) x.begin(),x.end()
#define lc (o<<1)
#define rc (o<<1|1)
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;

typedef long double ld;
typedef long long LL;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<LL> vll;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int INF = 0x3f3f3f3f;
const LL INF_ll = 0x3f3f3f3f3f3f3f3fLL;
const double PI = acos(-1.0);
const double EPS = 1e-8;
int read(){
    int x = 0,f = 1;
    char ch = getchar();
    for(;!isdigit(ch);ch = getchar()) if(ch=='-') f = -1;
    for(;isdigit(ch);ch = getchar()) x = (x<<1) + (x<<3) + (ch^48);
    return x*f;
}
int gcd(int a,int b){ return b?gcd(b,a%b):a; }
int solve(int p,int q,int a){
    int phi = p-1;
    for(int i = 1;i < q;++i) phi *= p;
    int g = gcd(phi,a),res = phi/g;
    if(p==2 && q > 2 && a%2==0) res >>= 1;
    return res;
}
signed main(void){
    int p = read(),q = read(),n = read(),ans = 1;
    for(int i = 2;i*i <= n;++i)
        if(n%i==0){
            int c = 0;while(n%i==0) n/=i,++c;
            int tmp = 1;while(c > 0){ tmp += solve(i, c, p);c -= p; }
            ans *= tmp;
        }
    if(n > 1) ans *= solve(n,1,p) + 1;
    printf("%d\n",ans);
    return 0;
}
