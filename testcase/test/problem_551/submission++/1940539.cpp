#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,T;
signed main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        if(n>=4)printf("Yes\n");
        else printf("No\n");
        if(n>=4&&!(n&1))printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}