#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#define N 262147
#define ll long long
#define p 998244353
using namespace std;

struct Z{
    int v;
    inline Z(const int _v=0):v(_v){}
};

inline Z operator + (const Z& lhs,const Z& rhs){ return lhs.v+rhs.v<p ? lhs.v+rhs.v : lhs.v+rhs.v-p; }
inline Z operator - (const Z& lhs,const Z& rhs){ return lhs.v<rhs.v ? lhs.v-rhs.v+p : lhs.v-rhs.v; }
inline Z operator - (const Z& x){ return x.v?p-x:0; }
inline Z operator * (const Z& lhs,const Z& rhs){ return (ll)lhs.v*rhs.v%p; }
inline Z& operator += (Z& lhs,const Z& rhs){ lhs.v = lhs.v+rhs.v<p ? lhs.v+rhs.v : lhs.v+rhs.v-p; return lhs; }
inline Z& operator -= (Z& lhs,const Z& rhs){ lhs.v = lhs.v<rhs.v ? lhs.v-rhs.v+p : lhs.v-rhs.v; return lhs; }
inline Z& operator *= (Z& lhs,const Z& rhs){ lhs.v = (ll)lhs.v*rhs.v%p; return lhs; }

inline Z power(Z a,int t){
    Z res = 1;
    while(t){
        if(t&1) res *= a;
        a *= a;
        t >>= 1;
    }
    return res;
}

int ms,d;
Z pwm,q;
bool not0[8][8];

struct mat{
    Z a[8][8];
    inline mat(){ memset(a,0,sizeof(a)); }

    inline mat operator * (const mat& b) const{
        mat res = mat();
        for(int i=0;i!=ms;++i)
        for(int j=0;j!=ms;++j)
        for(int k=0;k!=ms;++k)
            res.a[i][j] += a[i][k]*b.a[k][j];
        return res;    
    }
};

struct pcoef{
    Z a[9];
    int t;
    inline Z operator [] (const int& x) const{ return a[x]; }
    inline Z& operator [] (const int& x){ return a[x]; }

    inline Z eval(const Z& x){
        Z res = a[t];
        for(int i=t-1;~i;--i) res = a[i]+res*x;
        return res;
    }
}P[9];

struct poly{
    vector<Z> a;
    inline Z operator [] (const int& x) const{ return a[x]; }
    inline Z& operator [] (const int& x){ return a[x]; }
};

inline mat getmat(int x){
    mat res = mat();
    Z p0 = P[0].eval(x);
    for(int i=0;i!=ms-1;++i) res.a[i+1][i] = p0;
    for(int i=0;i!=ms;++i) res.a[i][ms-1] = -P[ms-i].eval(x);
    return res;
}

Z rt[N];
int rev[N];
int siz;

inline int getlen(int n){ return 1<<(32-__builtin_clz(n)); }

void init(int n){
    int lim = 1;
    while(lim<=n) lim <<= 1,++siz;
    for(int i=1;i!=lim;++i) rev[i] = (rev[i>>1]>>1)|((i&1)<<(siz-1));
    Z w = power(3,(p-1)>>siz);
    rt[lim>>1] = 1;
    for(int i=lim>>1|1;i!=lim;++i) rt[i] = rt[i-1]*w;
    for(int i=(lim>>1)-1;i;--i) rt[i] = rt[i<<1];
    for(int i=0;i!=ms-1;++i) not0[i+1][i] = 1;
    for(int i=0;i!=ms;++i) not0[i][ms-1] = 1;
}

inline void dft(Z *f,int lim){
    static unsigned long long a[N];
    int x,shift = siz-__builtin_ctz(lim);
    for(int i=0;i!=lim;++i) a[rev[i]>>shift] = f[i].v;
    for(int mid=1;mid!=lim;mid<<=1)
    for(int j=0;j!=lim;j+=(mid<<1))
    for(int k=0;k!=mid;++k){
        x = a[j|k|mid]*rt[mid|k].v%p;
        a[j|k|mid] = a[j|k]+p-x;
        a[j|k] += x;
    }
    for(int i=0;i!=lim;++i) f[i] = a[i]%p;
}

inline void idft(Z *f,int lim){
    reverse(f+1,f+lim);
    dft(f,lim);
    int x = p-((p-1)>>__builtin_ctz(lim));
    for(int i=0;i!=lim;++i) f[i] *= x;
}

struct pmat{ 
    vector<Z> a[8][8];
    int deg;
    inline void resize(int n){
        for(int i=0;i!=ms;++i)
        for(int j=0;j!=ms;++j)
            a[i][j].resize(n);
        deg = n-1;
    }
};

inline pmat comp(pmat f,Z qs){
    Z pw = qs;
    for(int k=1;k<=f.deg;++k){
        for(int i=0;i!=ms;++i)
        for(int j=0;j!=ms;++j)
            f.a[i][j][k] *= pw;
        pw *= qs;
    }
    return f;
}

pmat operator * (const pmat& f,const pmat& g){
    static Z A[8][8][N],B[8][8][N],C[N];
    pmat res;
    int n = f.deg+1,m = g.deg+1;
    res.resize(n+m-1);
    int lim = getlen(n+m);
    for(int i=0;i!=ms;++i)
    for(int j=0;j!=ms;++j){
        memcpy(A[i][j],f.a[i][j].begin().base(),n<<2);
        memcpy(B[i][j],g.a[i][j].begin().base(),m<<2);
        memset(A[i][j]+n,0,(lim-n+1)<<2);
        memset(B[i][j]+m,0,(lim-m+1)<<2);
        dft(A[i][j],lim),dft(B[i][j],lim);
    }
    for(int i=0;i!=ms;++i)
    for(int j=0;j!=ms;++j){
        memset(C,0,lim<<2);
        for(int k=0;k<=ms;++k)
        for(int l=0;l!=lim;++l)
            C[l] += A[i][k][l]*B[k][j][l];
        idft(C,lim);
        memcpy(res.a[i][j].begin().base(),C,(n+m-1)<<2);
    }
    return res;
}

inline poly operator * (const poly& f,const poly& g){
    poly res;
    static Z A[N],B[N];
    int n = f.a.size()-1,m = g.a.size()-1;
    int lim = getlen(n+m);
    memset(A,0,lim<<2),memset(B,0,lim<<1);
    memcpy(A,f.a.begin().base(),(n+1)<<2);
    memcpy(B,g.a.begin().base(),(m+1)<<2);
    dft(A,lim),dft(B,lim);
    for(int i=0;i!=lim;++i) A[i] *= B[i];
    idft(A,lim);
    res.a.resize(n+m+1);
    memcpy(res.a.begin().base(),A,(n+m+1)<<2);
    return res;
}

inline poly comp(poly f,Z qs){
    Z pw = qs;
    for(int i=1;i<f.a.size();++i){
        f[i] *= pw;
        pw *= qs;
    }
    return f;
}

pair<pmat,poly> getf(int s){
    static pmat f,fx,fb,fd;
    poly g,gd,gb,gx;
    f.resize(d+1),g.a.resize(d+1);
    for(int j=0;j<=d;++j){
        g[j] = P[0][j];
        for(int i=0;i!=ms-1;++i) f.a[i+1][i][j] = P[0][j];
        for(int i=0;i!=ms;++i) f.a[i][ms-1][j] = -P[ms-i][j];
    }
    fb = f,gb = g;
    int x = s,top = 0,st[30],l = 1;
    while(x){
        st[++top] = x;
        x >>= 1;
    }
    Z pw = q;
    while(--top){
        f = f*comp(f,pw),g = g*comp(g,pw);
        l <<= 1,pw *= pw;
        if(!(st[top]&1)) continue;
        fx = comp(fb,pw),gx = comp(gb,pw);
        memset(fd.a,0,sizeof(fd.a));
        fd.resize(fx.deg+f.deg+1);
        gd.a.resize(gx.a.size()+g.a.size()-1);
        memset(gd.a.begin().base(),0,gd.a.size()<<2);
        for(int i=0;i!=ms;++i)
        for(int j=0;j!=ms;++j)
        for(int k=0;k!=ms;++k){
            if(!not0[k][j]) continue;
            for(int p1=0;p1<=f.deg;++p1)
            for(int p2=0;p2<=fx.deg;++p2)
                fd.a[i][j][p1+p2] += f.a[i][k][p1]*fx.a[k][j][p2];
        }
        for(int p1=0;p1<g.a.size();++p1)
        for(int p2=0;p2<gx.a.size();++p2)
            gd[p1+p2] += g[p1]*gx[p2];
        f = fd,g = gd;
        ++l,pw *= q;
    }
    return make_pair(f,g);
}

inline pair<mat,Z> czt(const pair<pmat,poly>& f,int n,int m,Z z){
    static Z g[N],h[N],pw[N],suf[N];
    static mat A[N];
    int lim = getlen(n+m);
    memset(g,0,lim<<2);
    pw[0] = g[0] = g[1] = Z(1);
    for(int i=2;i<=n+m;++i) g[i] = g[i-1]*z;
    for(int i=2;i<=n+m;++i) g[i] *= g[i-1];
    int len = max(n,m);
    suf[len+1] = 1;
    for(int i=len;i;--i) suf[i] = suf[i+1]*g[i];
    Z pre = power(suf[1],p-2),tmp;
    for(int i=1;i<=len;++i){
        pw[i] =  pre*suf[i+1];
        pre *= g[i];
    }
    reverse(g,g+n+m+1);
    dft(g,lim);
    for(int j=0;j!=ms;++j)
    for(int k=0;k!=ms;++k){
        for(int i=0;i<=n;++i) h[i] = f.first.a[j][k][i]*pw[i];
        memset(h+n+1,0,(lim-n+1)<<2);
        dft(h,lim);
        for(int i=0;i!=lim;++i) h[i] *= g[i];
        idft(h,lim);
        for(int i=0;i<=m;++i) A[i].a[j][k] = h[n+m-i]*pw[i];
    }
    for(int i=0;i<=n;++i) h[i] = f.second[i]*pw[i];
    memset(h+n+1,0,(lim-n+1)<<2);
    dft(h,lim);
    for(int i=0;i!=lim;++i) h[i] *= g[i];
    idft(h,lim);
    Z res2 = 1;
    for(int i=0;i<=m;++i) res2 *= h[n+m-i]*pw[i];
    mat res1 = A[0];
    for(int i=1;i<=m;++i) res1 = res1*A[i];
    return make_pair(res1,res2);
}

Z solve(const Z *a,int n){
    int tn = n-ms+1,s,t;
    s = ceil(sqrt(tn*1.0/d)),t = tn/s-1;
    pair<mat,Z> tmp = czt(getf(s),s*d,t,power(q,s));
    mat mul = tmp.first;
    Z pwq = power(q,(tn/s)*s),res = 0,pd = tmp.second;
    for(int i=(tn/s)*s;i!=tn;++i){
        mul = mul*getmat(pwq.v);
        pd *= P[0].eval(pwq);
        pwq *= q;
    }
    for(int i=0;i!=ms;++i) res += a[i]*mul.a[i][ms-1];
    return res*power(pd,p-2);
}

int n;
Z a[9];

int main(){
    scanf("%d%d%d%d",&n,&ms,&d,&q.v);
    init(200000);
    pwm = power(q,ms);
    for(int i=0;i!=ms;++i) scanf("%d",&a[i].v);
    for(int i=0;i<=ms;++i){
        P[i].t = d;
        for(int j=0;j<=d;++j) scanf("%d",&P[i][j].v);
    }
    Z tmp = pwm;
    for(int j=1;j<=d;++j){
        for(int i=0;i<=ms;++i) P[i][j] *= tmp;
        tmp *= pwm;
    }
    printf("%d",solve(a,n).v);
    return 0;
}

