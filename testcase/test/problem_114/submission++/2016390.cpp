#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll inf=1e17;

int n;
vector<ll>B;
inline void Insert(ll x){
    for(auto b:B) x=min(x,x^b);
    for(auto &b:B) b=min(b,x^b);
    if(x) B.emplace_back(x);
}
inline ll Getmx(){
    ll res=0;
    for(auto b:B) res^=b;
    return res;
}
inline ll Getmn(){
    ll res=inf;
    for(auto b:B) res=min(res,b);
    return res;
}
inline ll Getkth(ll k){
    sort(B.begin(),B.end());
    int sz=B.size();
    if(sz<n) k--;
    if(pow(2,sz)<=k) return -1;
    if(!k) return 0;
    ll res=0;
    for(auto b:B){
        if(k&1) res^=b;
        k>>=1;
    }
    return res;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        ll x;
        scanf("%lld",&x);
        Insert(x);
    }
    ll q;
    cin>>q;
    while(q--){
        ll x;
        cin>>x;
        cout<<Getkth(x)<<endl;
    }
    return 0;
}
