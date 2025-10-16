#include<bits/stdc++.h>
#define pb push_back
#define MP make_pair
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
typedef long long ll;
template<typename T>void readmain(T &x){
    bool neg=false;unsigned int c=getchar();
    for(;(c^48)>9;c=getchar())if(c=='-')neg=true;
    for(x=0;(c^48)<10;c=getchar())x=(x<<3)+(x<<1)+(c^48);
    if(neg)x=-x;
}
template<typename T>T& read(T &x){readmain(x);return x;}
template<typename T,typename ...Tr>void read(T &x,Tr&... r){readmain(x);read(r...);}

int Prime[12]={2,3,5,7,11,13,17,19,23,29,31,37};
ll power(ll a,ll b,ll mod){
    ll res=1,tmp=a;
    while(b){
        if(b&1)res=(__int128)res*tmp%mod;
        tmp=(__int128)tmp*tmp%mod;
        b>>=1;
    }
    return res;
}
bool miller_rabin(ll n){
    if(n==1)return 0;
    if(n==2)return 1;
    if(n%2==0)return 0;
    ll a=n-1;int b=__builtin_ctzll(a);
    a>>=b;
    for(int i=0;i<12;i++){
        ll x=power(Prime[i],a,n);
        if(x<=1)continue;
        for(int j=1;j<b&&x!=n-1;j++)x=(__int128)x*x%n;
        if(x!=n-1)return 0;
    }
    return 1;
}
int main(){
    ll x;
    while(scanf("%lld",&x)==1){puts(miller_rabin(x)?"Y":"N");}
    return 0;
}