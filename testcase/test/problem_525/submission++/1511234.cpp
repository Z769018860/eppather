
#include <cstdio>
#include <algorithm>
#define fd(i, a, b) for (i = a; i >= b; i--)
using namespace std;

const int maxn = 30010;
int phi[maxn], prime[maxn], ans[maxn * 2 + 10];
bool pri[maxn];
int k, l, cnt;

int main(){
    
    

    phi[1] = 1;
    for(int i = 2; i <= 30000; i++){
        if(!pri[i])
            prime[++cnt] = i, phi[i] = i - 1;
        for(int j = 1; j <= cnt; j++){
            if ((long long)i * prime[j] > 30000) break;
            pri[i*prime[j]] = 1;
            if (i%prime[j] == 0){
                phi[i*prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i*prime[j]] = phi[i] * (prime[j] - 1);
        }
    }

    scanf("%d", &k);
    if(k == 1){
        printf("-1\n");
        return 0;
    }
    ans[2 * phi[k]] = 1;
    ans[phi[k]] = k - 1;
    printf("%d\n", 2 * phi[k]);
    for(int i = 0; i <= 2 * phi[k]; i++){
        int t = ans[i];
        t %= k;
        (t += k) %= k;
        printf("%d ", t);
    }
}