#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e7+10, mod = 1e9+7;
int n, k, pri[maxn], cnt, mnp[maxn], pw[maxn], sig[maxn];
bitset<maxn> isnp;
inline int fpow(int a, int b, int ans = 1){
    for(; b; b >>= 1, a = 1ll*a*a%mod)if(b&1)ans = 1ll*ans*a%mod;
    return ans;
}
int main(){
    cin >> n >> k, pw[1] = sig[1] = 1;
    for(int i = 2; i <= n; ++i){
        if(!isnp[i])pri[++cnt] = i, mnp[i] = i, pw[i] = fpow(i, k), sig[i] = (1+pw[i])%mod;
        for(int j = 1; j <= cnt; ++j){
            int x = i*pri[j];
            if(x > n)break;
            isnp[x] = 1, pw[x] = 1ll*pw[i]*pw[pri[j]]%mod;
            if(i%pri[j] == 0){
                mnp[x] = mnp[i]*pri[j];
                sig[x] = 1ll*sig[i/mnp[i]]*(sig[mnp[i]] + pw[mnp[x]])%mod;
                break;
            }else{
                mnp[x] = pri[j];
                sig[x] = 1ll*sig[i]*sig[pri[j]]%mod;
            }
        }
    }

    int ans = 0;
    for(int i = 1; i <= n; ++i)ans = (ans + sig[i])%mod;
    printf("%d\n", ans);
    return 0;
}