#include<stdio.h>
#include<set>
#include<map>
typedef unsigned int uint;
typedef unsigned long long ull;
#define MOD 19260817u
constexpr uint plus(const uint &x,const uint &y) {
    if(x+y>=MOD) {
        return x+y-MOD;
    }
    return x+y;
}
constexpr uint minus(const uint &x,const uint &y) {
    if(x<y) {
        return x-y+MOD;
    }
    return x-y;
}
constexpr uint power(uint x,uint y) {
    uint s(1);
    while(y>0) {
        if(y&1) {
            s=(ull)s*x%MOD;
        }
        x=(ull)x*x%MOD;
        y>>=1;
    }
    return s;
}
struct modint {
    uint val;
    int pow;
    constexpr modint():val(0),pow(0) {}
    constexpr explicit modint(const uint &__val):val(__val),pow(0) {}
    constexpr explicit operator uint() const {
        return pow?0:val;
    }
    constexpr modint operator*=(const uint &__x) {
        if(__builtin_expect(__x==0,0)) {
            ++pow;
        }
        else {
            val=(ull)val*__x%MOD;
        }
        return *this;
    }
    constexpr modint operator/=(const uint &__x) {
        if(__builtin_expect(__x==0,0)) {
            --pow;
        }
        else {
            val=(ull)val*power(__x,MOD-2)%MOD;
        }
        return *this;
    }
};
int len[100005];
int dat[100005];
std::map<int,std::set<int>> seq[100005];
std::map<int,uint> val[100005];
std::map<int,modint> tot;
constexpr uint calc(const uint n) {
    return ((ull)n*(n+1)>>1)%MOD;
}
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    uint sum(1);
    for(int i=1;i<=n;i++) {
        scanf("%d",len+i);
        sum=(ull)calc(len[i])*sum%MOD;
    }
    uint ans(0);
    const auto modify([sum,&ans](const int x,const int y,const int z){
        int &d(dat[len[x-1]+y]);
        if(d) {
            auto &tmp(seq[x][d]);
            tmp.erase(y);
            auto it(tmp.lower_bound(y));
            const int nxt(it==tmp.end()?len[x]-len[x-1]+1:*it);
            const int pre(it==tmp.begin()?0:*--it);
            auto &t(tot[d]);auto &v(val[x][d]);
            ans=plus(ans,uint(t));
            t/=v;
            v=minus(v,calc(y-pre-1));
            v=minus(v,calc(nxt-y-1));
            v=plus(v,calc(nxt-pre-1));
            t*=v;
            ans=minus(ans,uint(t));
        }
        d=z;
        if(!tot.count(z)) {
            tot[z]=modint(sum);
        }
        if(!val[x].count(z)) {
            val[x][z]=calc(len[x]-len[x-1]);
        }
        auto &tmp(seq[x][z]);
        auto it(tmp.lower_bound(y));
        const int nxt(it==tmp.end()?len[x]-len[x-1]+1:*it);
        const int pre(it==tmp.begin()?0:*--it);
        auto &t(tot[z]);auto &v(val[x][z]);
        ans=plus(ans,uint(t));
        t/=v;
        v=minus(v,calc(nxt-pre-1));
        v=plus(v,calc(y-pre-1));
        v=plus(v,calc(nxt-y-1));
        t*=v;
        ans=minus(ans,uint(t));
        tmp.insert(y);
    });
    for(int i=1;i<=n;i++) {
        len[i]+=len[i-1];
        for(int j=len[i-1]+1;j<=len[i];j++) {
            int x;
            scanf("%d",&x);
            modify(i,j-len[i-1],x);
        }
    }
    printf("%u\n",ans);
    for(int i=1;i<=m;i++) {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        modify(x,y,z);
        printf("%u\n",ans);
    }
    return 0;
}