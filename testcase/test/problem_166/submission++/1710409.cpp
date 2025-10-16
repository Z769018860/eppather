#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
const int mod=998244353;
int n,m,wl,w[600010],a[600010],b[600010],jc[600010],inv[600010],mjc[600010],minv[600010];
#define get(n) wl=1;while(wl<n)wl<<=1
#define add(x,y) (x+y>=mod?x+y-mod:x+y)
#define sub(x,y) (x<y?x-y+mod:x-y)
#define mul(f,g,n) for(int i=0;i<n;i++)f[i]=1ll*f[i]*g[i]%mod
int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=1ll*a*ans%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return ans;
}
void init(int n){
    int t=1;
    while((1<<t)<n)t++;
    t=min(t-1,21);
    w[0]=1;w[1<<t]=qpow(31,1<<21-t);
    for(int i=t;i;i--)w[1<<i-1]=1ll*w[1<<i]*w[1<<i]%mod;
    for(int i=1;i<(1<<t);i++)w[i]=1ll*w[i&(i-1)]*w[i&-i]%mod;
}
void DIF(int a[],int n){
    for(int mid=n>>1;mid>=1;mid>>=1){
        for(int i=0,k=0;i<n;i+=mid<<1,k++){
            for(int j=0;j<mid;j++){
                int x=1ll*a[i+j+mid]*w[k]%mod;
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
                a[i+j+mid]=1ll*sub(a[i+j],x)*w[k]%mod;
                a[i+j]=add(a[i+j],x);
            }
        }
    }
    int inv=qpow(n,mod-2);
    for(int i=0;i<n;i++)a[i]=1ll*a[i]*inv%mod;
    reverse(a+1,a+n);
}
void move(int n,int m,int f[],int g[]){
    jc[0]=mjc[0]=inv[0]=minv[0]=1;
	for(int i=1;i<=2*n+1;i++)jc[i]=1ll*jc[i-1]*i%mod,mjc[i]=1ll*mjc[i-1]*(m-n-1+i)%mod;
	inv[n<<1|1]=qpow(jc[n<<1|1],mod-2);minv[n<<1|1]=qpow(mjc[n<<1|1],mod-2);
	for(int i=2*n;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod,minv[i]=1ll*minv[i+1]*(m-n+i)%mod;
	get(n+1<<1);
	for(int i=0;i<=n;i++){
		f[i]=1ll*f[i]*inv[i]%mod*inv[n-i]%mod;
		if(n-i&1)f[i]=sub(0,f[i]);
	}
	for(int i=0;i<=(n<<1);i++)g[i]=1ll*minv[i+1]*mjc[i]%mod;
	DIF(f,wl);DIF(g,wl);mul(f,g,wl);DIT(f,wl);
	for(int i=n;i<=(n<<1);i++){
		g[i-n]=1ll*mjc[i+1]*minv[i-n]%mod*f[i]%mod;
	}
    for(int i=n+1;i<=wl;i++)g[i]=0;
    for(int i=0;i<wl;i++)f[i]=0;
}
int main(){
	scanf("%d%d",&n,&m);init(n+1<<1);
	for(int i=0;i<=n;i++)scanf("%d",&a[i]);
	move(n,m,a,b);
    for(int i=0;i<=n;i++)printf("%d ",b[i]);puts("");
	return 0;
}