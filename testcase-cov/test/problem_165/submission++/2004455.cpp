


#include<bits/stdc++.h>
using namespace std;
#define int long long

#define f(i, a, b) for(int i = (a); i <= (b); i++)
#define cl(i, n) i.clear(),i.resize(n);
#define endl '\n'
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int inf = 1e18;


mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count()); 
int rnd(int l, int r) {return rng() % (r-l+1) + l; }
#define watch(x) cerr  << (#x) << ' '<<'i'<<'s'<<' ' << x << endl
void pofe(int number, int bitnum) {
    string s; f(i, 0, bitnum) {s += char(number & 1) + '0'; number >>= 1; } 
    reverse(s.begin(), s.end()); cerr << s << endl; 
    return;
}
double runtime() {return 1.0*clock()/CLOCKS_PER_SEC;}
template <typename TYP> void cmax(TYP &x, TYP y) {if(x < y) x = y;}
template <typename TYP> void cmin(TYP &x, TYP y) {if(x > y) x = y;}


const int N=3e3,mod=998244353; 
int dp[2][N+10]; int x[N+10],y[N+10]; int coe[N+10]; 
int qpow(int th,int op) {int res=1; while(op){if(op&1)res=res*th%mod; th=th*th%mod; op>>=1;}return res;}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    
    
    
    
    
    
    int T; cin >> T; int n=0; 
    dp[0][0]=1;
    while(T--) {
        int q;cin>>q;
        if(q==1) {
            ++n; cin>>x[n]>>y[n]; 
            coe[n] = y[n];
            f(i,1,n-1) coe[n]=coe[n]*qpow(mod+x[n]-x[i],mod-2)%mod; 
            f(i,1,n-1) coe[i]=coe[i]*qpow(mod+x[i]-x[n],mod-2)%mod;
            f(i,0,n) dp[n&1][i]=(dp[(n&1)^1][i]*(mod-x[n])%mod+(i>0?dp[(n&1)^1][i-1]:0))%mod;
        }   
        else {
            int k;cin>>k; bool ok=0; 
            f(i,1,n)if(x[i]==k) {cout<<y[i]<<endl;ok=1; }
            if(ok) continue; 
            int ans=0,v=0; 
            f(i,0,n) (v += qpow(k,i)*dp[n&1][i])%=mod;
            f(i,1,n) (ans+=v*qpow(mod+k-x[i],mod-2)%mod*coe[i])%=mod;
            cout<<ans<<endl;
        } 
    }   
    
    
    return 0;
}