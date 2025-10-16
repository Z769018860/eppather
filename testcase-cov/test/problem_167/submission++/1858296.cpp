
#include<iostream>
#include<queue>
#include<set>
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,a,b) for(ll i=a;i<=b;i++)
#define per(i,a,b) for(ll i=a;i>=b;i--)
#define i128 __int128_t
const ll MAXN = 1e6 + 5;
const ll mod = 998244353;
const ll inf=1e18;
inline ll rd(){ll ret=0,f=1;char c;while(c=getchar(),!isdigit(c)){f=c=='-'?-1:1;}while(isdigit(c)) ret=ret*10+c-'0',c=getchar();return ret*f;}
inline void WT(i128 x){if(x>9) WT(x/10);putchar(x%10|'0');}
inline void wt(i128 x){WT(x);printf("\n");}
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}
ll n;ll m;ll k;
int _=0,acc=0;
ll ans;
ll gcd(ll a,ll b){return !b?a:gcd(b,a%b);}
ll fm(ll x,ll cnt){ll ret=1;while(cnt){if(cnt&1) ret=ret*(x%mod)%mod;x=x%mod*(x%mod)%mod;cnt>>=1;}return ret;}
ll fac[1000005];
ll tra[1000005];
ll num[1000005];
ll q_lr(int l,int r){
    ll ret1,ret2;ret1=ret2=0;
    l-=1;
    while(l) {
        ret1+=tra[l];
        l-=l&-l;
    }
    while(r){
        ret2+=tra[r];
        r-=r&-r;
    }
    return ret2-ret1;
}
void upd(int x,ll val){
    while(x<=n){
        tra[x]+=val;
        x+=x&-x;
    }    
}
ll cantor(){
    ll ret=0;
    per(i,n,1){
        ret=(ret+(q_lr(1,num[i])*fac[n-i])%mod)%mod;
        upd(num[i],1);
    }
    return ((1+ret)%mod+mod)%mod;
}
void solve() {
	n=rd();
    rep(i,1,n) num[i]=rd();
    fac[0]=1;
    rep(i,1,n) fac[i]=fac[i-1]*i%mod;
    cout<<cantor()<<endl;
}			
signed main() {
	 #ifndef ONLINE_JUDGE
        freopen("D:/vscode/in.txt", "r", stdin);
        freopen("D:/vscode/out.txt","w",stdout);
    #endif
	int t;	
	if(acc) ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);         
	if(_){
		cin>>t;int k=t;
        while(t--){
		    solve();
		}
	}else { solve();}
}
