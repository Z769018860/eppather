

#include<bits/stdc++.h>
using namespace std;
#define mid ((l+r)>>1)
#define rep(i,j,k) for (int i=j;i<=k;++i)
#define per(i,j,k) for (int i=j;i>=k;--i)
int const N=1e6+10;
int n,m,ly[N];
string s;
struct node{int l,r,p;}ans[N<<1];
int const mod=1e9+7;
int const Base=31;
int bse[N],qz[N];
inline void init(){
    bse[0]=1;
    rep(i,1,n) bse[i]=1ll*bse[i-1]*Base%mod;
    rep(i,1,n) qz[i]=(1ll*qz[i-1]*Base%mod+(s[i]-'a'+1))%mod;
}
inline int query(int l,int r){
    return (qz[r]+mod-(1ll*qz[l-1]*bse[r-l+1]%mod))%mod;
}
inline int cmpl(int x,int y){
    int l=1,r=min(x,y),ans=0;
    while (l<=r)
        if (query(x-mid+1,x)==query(y-mid+1,y)) l=(ans=mid)+1;
        else r=mid-1;
    return ans;
}
inline int cmpr(int x,int y){
    int l=1,r=n-max(x,y)+1,ans=0;
    while (l<=r)
        if (query(x,x+mid-1)==query(y,y+mid-1)) l=(ans=mid)+1;
        else r=mid-1;
    return ans;
}
inline int cmp(int x,int y){
    int u=cmpr(x,y);
    if (max(x,y)+u>n) return x>y;
    else return s[x+u]<s[y+u];
}
inline void add(int u,int v){
    int L=cmpl(u,v),R=cmpr(u,v);
    if (L+R>=v-u+1) ans[++m]=(node){u-L+1,v+R-1,v-u};
}
inline void Lyndon(int c){
    ly[n]=n;
    stack<int>s;s.push(n);
    per(i,n-1,1){
        while (s.size() && cmp(i,s.top())==c) s.pop();
        if (!s.size()) ly[i]=n;
        else ly[i]=s.top()-1;
        s.push(i);
    }
}
void solve(){
    cin>>s,n=s.length(),s=" "+s,init();
    rep(t,0,1){
        Lyndon(t);
        rep(i,1,n-1) add(i,ly[i]+1);
    }
    sort(ans+1,ans+m+1,[](node x,node y){
        return (x.l^y.l)?(x.l<y.l):((x.r^y.r)?(x.r<y.r):(x.p<y.p));
    });
    int tot=0;
    rep(i,1,m) tot+=!!((ans[i].l^ans[i-1].l)|(ans[i].r^ans[i-1].r));
    cout<<tot<<'\n';
    rep(i,1,m) if ((ans[i].l!=ans[i-1].l) || (ans[i].r!=ans[i-1].r)) cout<<ans[i].l<<' '<<ans[i].r<<' '<<ans[i].p<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t=1;
    
    while (t--) solve();
    return 0;
}