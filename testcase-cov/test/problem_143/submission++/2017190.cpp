#include<bits/stdc++.h>
using namespace std;
using i7=__int128;
long long x;
int T=100000,pr[12]={2,3,5,7,11,13,17,19,23,29,31,37};
i7 qpow(i7 a,long long b,i7 mod) {
    i7 res=1;
    while (b) {
        if (b&1ll) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
bool chk() {
    if (x<=40ll) {
        for (int i=0;i<12;i++) if (x==1ll*pr[i]) return true;
        return false;
    }
    int op=0;
    long long y=x-1;
    while ((y^1ll)&1ll) {
        y>>=1;
        op++;
    }
    for (int i=0;i<12;i++) {
        i7 tmp=qpow((i7)pr[i],y,x);
        if ((tmp==1ll)||(tmp==x-1ll)) continue;
        bool f=false;
        for (int j=1;j<op;j++) {
            tmp=tmp*tmp%x;
            if (tmp==x-1ll) {
                f=true;
                break;
            }
        }
        if (!f) return false;
    }
    return true;
}
int main() {
    while (cin>>x) {
        if (x==1) printf("N\n");
        else if (x<=3) printf("Y\n");
        else {
            if (chk()) printf("Y\n");
            else printf("N\n");
        }
    }
    return 0;
}
