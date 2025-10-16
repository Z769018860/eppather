#include <bits/stdc++.h>
using namespace std;
namespace Slongod{

using ull = unsigned long long;
const int N = 2e6+7 , MX = 40;


mt19937_64 rd(time(nullptr));
int bits(int x){return x << 1;}
ull newnode()
{
    ull re = 0;
    for (int i = 0; i < MX; i++) {
        re = re * 3 + (rd() % 3);
    } return re;
}
ull add(ull a , ull b)
{
    int fa[MX] , fb[MX]; ull re = 0;
    for (int i = 0; i < MX; i++) {
        fa[i] = int(a % 3); a /= 3;
        fb[i] = int(b % 3); b /= 3;
    }
    for (int i = MX-1; i >= 0; i--) {
        re = re * 3 + (fa[i] + fb[i]) % 3;
    } return re;
}

int n , m; ull nodeid[N] , sum[N];
unordered_map <ull,int> mymap , yourmap;

void init()
{
    for (int i = 1; i <= n; i++) {
        ull tmp = newnode();
        nodeid[i] = tmp;
        mymap[tmp] = i;
        yourmap[add(tmp , tmp)] = i;
    }
}

void main()
{
    cin >> n >> m; init();
    for (int i = 1 , u , fa , ans = 0; i <= m; i++) {
        cin >> u >> fa;
        u ^= ans; fa ^= ans;
        sum[i] = add(sum[fa] , nodeid[u]);
        if (!sum[i]) {
            ans = -1;
        } else if (mymap.count(sum[i])) {
            ans = mymap[sum[i]];
        } else if (yourmap.count(sum[i])) {
            ans = yourmap[sum[i]];
        } else {
            ans = -2;
        } cout << ans << '\n';
    }
}
}int main()
{
    ios :: sync_with_stdio(0);
    cin.tie(0) , cout.tie(0);
    return Slongod :: main(),0;
}