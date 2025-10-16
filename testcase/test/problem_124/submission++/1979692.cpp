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
        for(int j = 1; j <= cnt && i*pri[j] <= n; ++j){
            isnp[i*pri[j]] = 1, pw[i*pri[j]] = 1ll*pw[i]*pw[pri[j]]%mod;
            if(i%pri[j] == 0){
                mnp[i*pri[j]] = mnp[i]*pri[j];
                sig[i*pri[j]] = 1ll*sig[i/mnp[i]]*(sig[mnp[i]] + pw[mnp[i*pri[j]]])%mod;
                break;
            }else{
                mnp[i*pri[j]] = pri[j];
                sig[i*pri[j]] = 1ll*sig[i]*sig[pri[j]]%mod;
            }
        }
    }

    int ans = 0;
    for(int i = 1; i <= n; ++i)ans = (ans + sig[i])%mod;
    printf("%d\n", ans);
    return 0;
}