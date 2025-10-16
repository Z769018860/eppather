#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n;
signed main(){
    cin>>T;
    while(T--){
        cin>>n;
        if(n>=4)puts("Yes");
        else puts("No");
        if(n>=4&&!(n&1))puts("Yes");
        else puts("No");
    }
    return 0;
}