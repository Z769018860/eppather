#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
#define int long long
using namespace std;
const int mod=1000391835649,sq=1<<20;
int n,m,wl,w[4200010],jc[4200010],inv[4200010],mjc[4200010],minv[4200010],f[4200010];
inline int mul(int a,int b){
    return ((a&(sq-1))*b+(((a>>20)*b%mod)<<20))%mod;
}
#define get(n) wl=1;while(wl<n)wl<<=1
#define add(x,y) (x+y>=mod?x+y-mod:x+y)
#define sub(x,y) (x<y?x-y+mod:x-y)
int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=mul(a,ans);
		a=mul(a,a);
		b>>=1;
	}
	return ans;
}
void init(int n){
    int t=1;
    while((1<<t)<n)t++;
    t=min(t-1,24ll);
    w[0]=1;w[1<<t]=qpow(qpow(7,3*4969),1<<24-t);
    for(int i=t;i;i--)w[1<<i-1]=mul(w[1<<i],w[1<<i]);
    for(int i=1;i<(1<<t);i++)w[i]=mul(w[i&(i-1)],w[i&-i]);
}
void DIF(int a[],int n){
    for(int mid=n>>1;mid>=1;mid>>=1){
        for(int i=0,k=0;i<n;i+=mid<<1,k++){
            for(int j=0;j<mid;j++){
                int x=mul(a[i+j+mid],w[k]);
                a[i+j+mid]=sub(a[i+j],x);
                a[i+j]=add(a[i+j],x);
            }
        }
    }
}
void DIT(int a[],int n){
    for(int mid=1;mid<n;mid<<=1){
        for(int i=0,k=0;i<n;i+=mid<<1,k++){
            for(int j=0;j<mid;j++){
                int x=a[i+j+mid];
                a[i+j+mid]=mul(sub(a[i+j],x),w[k]);
                a[i+j]=add(a[i+j],x);
            }
        }
    }
    int inv=qpow(n,mod-2);
    for(int i=0;i<n;i++)a[i]=mul(a[i],inv);
    reverse(a+1,a+n);
}
void move(int n,int m,int f[],int g[]){
    mjc[0]=minv[0]=1;
	for(int i=1;i<=2*n+1;i++)mjc[i]=mul(mjc[i-1],m-n-1+i);
	minv[n<<1|1]=qpow(mjc[n<<1|1],mod-2);
	for(int i=2*n;i>=1;i--)minv[i]=mul(minv[i+1],m-n+i);
	get(n+1<<1);
	for(int i=0;i<=n;i++){
		f[i]=mul(mul(f[i],inv[i]),inv[n-i]);
		if(n-i&1)f[i]=sub(0,f[i]);
	}
	for(int i=0;i<=(n<<1);i++)g[i]=mul(minv[i+1],mjc[i]);
	DIF(f,wl);DIF(g,wl);for(int i=0;i<wl;i++)f[i]=mul(f[i],g[i]);DIT(f,wl);
	for(int i=n;i<=(n<<1);i++){
		g[i-n]=mul(mul(mjc[i+1],minv[i-n]),f[i]);
	}
    for(int i=n+1;i<=wl;i++)g[i]=0;
    for(int i=0;i<wl;i++)f[i]=0;
}
void solve(int n){
    f[0]=1;f[1]=sq+1;
    static int g[4200010],tmp[4200010];
    for(int len=2;len<=n;len<<=1){
        for(int i=0;i<=(len>>1);i++)tmp[i]=f[i];
        move(len>>1,(len>>1)+1,tmp,g);
        for(int i=(len>>1)+1;i<=len;i++)f[i]=g[i-(len>>1)-1],g[i-(len>>1)-1]=0;
        for(int i=0;i<=len;i++)tmp[i]=f[i];
        move(len,mul(len>>1,qpow(n,mod-2)),tmp,g);
        for(int i=0;i<=len;i++)f[i]=mul(f[i],g[i]);
    }
}
void pre(int n){
    jc[0]=inv[0]=1;
    for(int i=1;i<=2*n+1;i++)jc[i]=mul(jc[i-1],i);
    inv[2*n+1]=qpow(jc[2*n+1],mod-2);
    for(int i=2*n;i>=1;i--)inv[i]=mul(inv[i+1],i+1);
    solve(n);
    for(int i=1;i<=n;i++)f[i]=mul(f[i],f[i-1]);
    for(int i=n+1;i>=1;i--)f[i]=f[i-1];f[0]=1;
}
int getjc(int n){
    int ret=n/sq,ans=f[min(ret,sq+1)];
    for(int i=min(ret,sq+1)*sq+1;i<=n;i++)ans=mul(ans,i);
    return ans;
}
signed main(){
    init(1<<22);pre(sq);
    int tim;scanf("%lld",&tim);
    while(tim--){
        scanf("%lld",&n);
        printf("%lld\n",getjc(n));
    }
    return 0;
}