#include<stdio.h>
typedef long long LL;
LL b[64], a[64], x, k;
int main(){
    int n, m, cnt=0;
    scanf("%d",&n);
    for(int i=0; i<n; ++i){
        scanf("%lld",&x);
        for(int j=62;j>=0;--j){
            if(x&(1LL<<j)){
                if(!b[j]) {b[j] = x; break;}
                x ^= b[j];}
        }
    }
    for(int i=62; i>=0; --i)
        for(int j=i-1;j>=0 ; --j)
            if(b[i]&(1LL<<j)) b[i] ^= b[j];
    for(int i=0; i<=62; ++i)
        if(b[i]) a[cnt++] = b[i];
    scanf("%d",&m);
    while(m--){
        scanf("%lld",&k);
        if(cnt != n) --k;
        if(k >= (1LL<<cnt)) puts("-1");
        else{
            LL ans = 0;
            for(int i=0; i<cnt; ++i)
                if(k&(1LL<<i)) ans ^= a[i];
            printf("%lld\n",ans);}
    }
    return 0;
}