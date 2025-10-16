 
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<queue>
#include<map>
#include<stack>
#include<cmath>
#include<set>
#include<bitset>
#include<complex>
#include<cstdlib>
#include<assert.h>
#define inc(i,l,r) for(int i=l;i<=r;i++)
#define dec(i,l,r) for(int i=l;i>=r;i--)
#define link(x) for(edge *j=h[x];j;j=j->next)
#define mem(a) memset(a,0,sizeof(a))
#define ll long long
#define eps 1e-8
#define succ(x) (1<<x)
#define lowbit(x) (x&(-x))
#define mid (x+y>>1)
#define sqr(x) ((x)*(x))
#define NM 140005
#define nm 4194304
using namespace std;
const double pi=acos(-1);
const ll inf=998244353;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f*x;
}


inline void reduce(ll&x){x+=x>>63&inf;}
inline ll qpow(ll x,ll t){
    ll s=1;
    for(;t;t>>=1,x=x*x%inf)if(t&1)s=s*x%inf;
    return s;
}
int n,m,p;
ll a[nm],inv[NM];

void fmt(ll*a){
    for(int k=0;k<m;k++)
	inc(i,0,n)if(i>>k&1)
	    reduce(a[i]+=a[i^succ(k)]-inf);
}
void ifmt(ll*a){
    for(int k=0;k<m;k++)
	inc(i,0,n)if(i>>k&1)
	    reduce(a[i]-=a[i^succ(k)]);
}


int main(){
    m=read();n=read();p=read();
    inv[1]=1;
    inc(i,2,p)inv[i]=inv[inf%i]*(inf-inf/i)%inf;
    inc(i,1,n)a[read()]++;
    n=succ(m)-1;
    fmt(a);
    inc(i,0,n){
	ll t=a[i],cnt=a[i];
	inc(k,2,p){
	    cnt=cnt*(t-k+1)%inf*inv[k]%inf;
	    reduce(a[i]+=cnt-inf);
	}
    }
    ifmt(a);
    printf("%lld\n",a[n]);
    return 0;
}