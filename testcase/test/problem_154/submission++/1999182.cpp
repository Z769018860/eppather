#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> poly;
typedef vector<poly> Poly; 
const ll maxn=3e5+5, mo=998244353, N=3e5;

ll rev[maxn], iinv[maxn], v[maxn];

ll qpow(ll a,ll p) {
    ll res=1;
    while(p) {
        if(p&1) res=res*a%mo;
        p>>=1, a=a*a%mo;
    }
    return res;
}

poly add(poly a,poly b,ll n) {
    while(a.size()<n) a.push_back(0);
    while(b.size()<n) b.push_back(0);
    for(ll i=0;i<n;i++) a[i]=(a[i]+b[i])%mo;
    while(a.size()>n) a.pop_back();
    return a;
}

poly sub(poly a,poly b,ll n) {
    while(a.size()<n) a.push_back(0);
    while(b.size()<n) b.push_back(0);
    for(ll i=0;i<n;i++) a[i]=(a[i]-b[i]+mo)%mo;
    while(a.size()>n) a.pop_back();
    return a;
}

void DFT(poly& a,ll n,ll o) {
    for(ll i=0;i<n;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
    for(ll len=2;len<=n;len<<=1) {
        ll wn=qpow(3,(mo-1)/len);
        if(o==-1) wn=qpow(wn,mo-2);
        for(ll i=0;i<n;i+=len) {
            for(ll l=i,wx=1;l<i+len/2;l++, wx=wx*wn%mo) {
                ll r=l+len/2;
                ll x=a[l], y=a[r]*wx%mo;
                a[l]=(x+y)%mo, a[r]=(x-y+mo)%mo;
            }
        }
    }
    if(o==-1) {
        ll inv=qpow(n,mo-2);
        for(ll i=0;i<n;i++) a[i]=a[i]*inv%mo;
    }
    return ;
}

poly mul(poly a,poly b,ll tn) {
    while(a.size()>tn) a.pop_back();
    while(b.size()>tn) b.pop_back();
    ll n=tn*2, len=1, pw=0;
    while(len<n) len<<=1, pw++;
    for(ll i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<pw-1);
    while(a.size()<len) a.push_back(0);
    while(b.size()<len) b.push_back(0);
    DFT(a,len,1), DFT(b,len,1);
    for(ll i=0;i<len;i++) a[i]=a[i]*b[i]%mo;
    DFT(a,len,-1);
    while(a.size()>tn) a.pop_back();
    return a;
}

poly Mul(poly a,poly b,ll tn) {
    while(a.size()>tn) a.pop_back();
    while(b.size()>tn) b.pop_back();
    ll n=tn*2, len=1, pw=0;
    while(len<n) len<<=1, pw++;
    for(ll i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<pw-1);
    while(a.size()<len) a.push_back(0);
    while(b.size()<len) b.push_back(0);
    DFT(a,len,1), DFT(b,len,1);
    for(ll i=0;i<len;i++) a[i]=a[i]*a[i]%mo*b[i]%mo;
    DFT(a,len,-1);
    while(a.size()>tn) a.pop_back();
    return a;
}

poly inv(poly g,ll n) {
    if(n==1) return {qpow(g[0],mo-2)};
    poly f0=inv(g,(n+1)/2);
    return sub(add(f0,f0,n),Mul(f0,g,n),n);
}

poly der(poly a,ll n) {
    while(a.size()>n) a.pop_back();
    while(a.size()<n) a.push_back(0);
    for(ll i=0;i<n-1;i++) a[i]=a[i+1]*(i+1)%mo; a[n-1]=0;
    return a;
}

poly lle(poly a,ll n) {
    while(a.size()>n) a.pop_back();
    while(a.size()<n) a.push_back(0);
    for(ll i=n-1;i>0;i--) a[i]=a[i-1]*iinv[i]%mo; a[0]=0;
    return a;
}

poly ln(poly a,ll n) {
    return lle(mul(der(a,n),inv(a,n),n),n);
}

poly exp(poly g,ll n) {
    if(n==1) return {1};
    poly f0=exp(g,(n+1)/2);
    return mul(f0,add(sub({1},ln(f0,n),n),g,n),n);
}

poly sqrt(poly g,ll n) {
    if(n==1) return {1};
    poly f0=sqrt(g,(n+1)/2);
    return sub(f0,mul(sub(mul(f0,f0,n),g,n),inv(add(f0,f0,n),n),n),n);
}

pair<poly,poly> div(poly f,poly g,ll n,ll m) {
    reverse(f.begin(),f.begin()+n), reverse(g.begin(),g.begin()+m);
    poly q(0), r(0);
    q=mul(f,inv(g,n-m+1),n-m+1);
    reverse(f.begin(),f.begin()+n), reverse(g.begin(),g.begin()+m), reverse(q.begin(),q.begin()+n-m+1);
    r=sub(f,mul(g,q,n),n);
    return {q,r};
}

poly power (poly a,ll n,ll k) {
    poly b=ln(a,n);
    for(ll i=0;i<n;i++) b[i]=b[i]*k%mo;
    return exp(b,n);
}

void FWT_or(Poly& a,ll n,ll o) {
    for(ll len=2;len<=(1<<n);len<<=1) {
        for(ll i=0;i<(1<<n);i+=len) {
            for(ll l=i;l<i+len/2;l++) {
                ll r=l+len/2;
                for(ll d=0;d<=n;d++) a[r][d]= (a[r][d]+(mo+o)*a[l][d]%mo)%mo;
            }
        }
    }
    return ;
}

int main() {
    
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    for(ll i=1;i<=N;i++) iinv[i]=qpow(i,mo-2);
    ll n,m,k; cin>>n>>m>>k;
    ll fac=1, ifac=1;
    for(ll i=1;i<=k;i++) fac=fac*i%mo;
    ifac=qpow(fac,mo-2);
    Poly f(1<<n);
    for(ll i=0;i<(1<<n);i++) f[i].resize(n+1);
    for(ll i=0;i<m;i++) {
        ll x; cin>>x; 
        ll cnt=0;
        for(ll j=0;j<n;j++) if((x>>j)&1) cnt++;
        f[x][cnt]++;
    }
    FWT_or(f,n,1);
    for(ll i=0;i<(1<<n);i++) {
        poly fk(n+1);
        for(ll j=0;j<=n;j++) fk[j]=f[i][j];
        for(ll j=2;j<=k;j++) {
            for(ll p=n;p>=0;p--) {
                ll tmp=0;
                for(ll q=j-1;q<=p;q++) tmp+= fk[q]*f[i][p-q];
                fk[p]=tmp%mo;
            }
        }
        poly fr=der(f[i],n+1);
        f[i][0]=1;
        for(ll j=1;j<=n;j++) {
            f[i][j]=0;
            for(ll k=0;k<j;k++) f[i][j]=(f[i][j]+fr[k]*(f[i][j-k-1]+mo-fk[j-k-1]*ifac%mo)%mo)%mo;
            f[i][j]=f[i][j]*iinv[j]%mo;
        }
    }
    FWT_or(f,n,-1);
    cout<<f[(1<<n)-1][n]<<'\n';
    return 0;
}