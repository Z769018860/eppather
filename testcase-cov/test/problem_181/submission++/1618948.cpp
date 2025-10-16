#include<bits/stdc++.h>
using namespace std;
template<typename T>inline bool read(T&x){
x=0;char c=getchar();int f=1;while(!isdigit(c)&&(c!='-')&&(c!=EOF))c=getchar();
if(c==EOF)return 0;if(c=='-')f=-1,c=getchar();
while(isdigit(c)){x=x*10+(c&15);c=getchar();}x*=f;return 1;
}template<typename T,typename...Args>inline bool read(T&x,Args&...args){bool res=1;res&=read(x);res&=read(args...);return res;}
typedef long long LL;typedef unsigned long long u64;typedef unsigned u32;typedef long double LD;typedef pair<int,int> pii;typedef pair<LL,LL> pll;
#define pln putchar('\n')
#define For(i,a,b)  for(int i=(a),(i##i)=(b);i<=(i##i);++i)
#define Fodn(i,a,b) for(int i=(a),(i##i)=(b);i>=(i##i);--i)
const int M=1000000007,INF=0x3f3f3f3f;const long long INFLL=0x3f3f3f3f3f3f3f3fLL;
const int N=1000009;

struct exlucas{
    struct dat{
        const int p,pt,phi,t;
        vector<int>r;
        int Pow(int x,int y)const{
            int res=1;
            while(y>0){
                if(y%2!=0)res=LL(res)*x%pt;
                y/=2;x=LL(x)*x%pt;
            }
            return res;
        }
        dat(int _p,int _pt,int _t):p(_p),pt(_pt),phi(_pt/_p*(_p-1)),t(_t),r(pt){
            r[0]=1;
            for(int i=1;i<pt;++i)if(i%p==0)r[i]=r[i-1];
            else r[i]=r[i-1]*LL(i)%pt;
        }
        int f(LL n)const{
            if(n<p)return r[n];
            return Pow(r.back(),n/pt%phi)*LL(r[n%pt])%pt*f(n/p)%pt;
        }
        LL g(LL n)const{
            LL res=0;
            while(n>0)res+=n/p,n/=p;
            return res;
        }
        int C(LL n,LL m){
            LL v=g(n)-g(m)-g(n-m);
            if(v>=t)return 0;
            return LL(f(n))*Pow(f(m),phi-1)%pt*Pow(f(n-m),phi-1)%pt*Pow(p,v)%pt;
        }
    };
    vector<dat>mp;
    vector<LL>u;
    const int p;
    exlucas(int _p):p(_p){
        for(int i=2;i*i<=_p;++i)if(_p%i==0){
            int m=1,cnt=0;
            while(_p%i==0)_p/=i,m*=i,++cnt;
            mp.emplace_back(i,m,cnt);
        }
        if(_p>1)mp.emplace_back(_p,_p,1);
        u.resize(mp.size());
        for(int i=0;i<int(u.size());++i){
            u[i]=1;
            for(int j=0;j<int(mp.size());++j)if(i!=j){
                u[i]=u[i]*mp[j].pt%p*mp[i].Pow(mp[j].pt,mp[i].phi-1)%p;
            }
        }
    }
    int C(LL n,LL m){
        if(n<m||m<0)return 0;
        int res=0;
        for(int i=0;i<int(u.size());++i)res=(res+u[i]*mp[i].C(n,m))%p;
        return res;
    }
};


signed main(){
    int t,m;read(t,m);
    exlucas C(m);
    for(int i=1;i<=t;++i){
        LL n,k;read(n,k);
        printf("%d\n",C.C(n,k));
    }
    return 0;
}