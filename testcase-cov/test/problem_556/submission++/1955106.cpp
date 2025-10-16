#include<bits/stdc++.h>
using namespace std;
#define poly vector<long long>
#define fix(f,n) f.resize(n+1)
int n,m,rev[2100001],inv[150001],w[2100001];
long long a,b;
const int mod=998244353,G=3;
auto add=[](long long x,long long y){return x+y>=mod?x+y-mod:x+y;};
auto del=[](long long x,long long y){return x<y?x-y+mod:x-y;};
long long power(long long a,long long b){
	long long res=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) res=res*a%mod;
	return res;
}
void init(int n){
	inv[1]=w[n]=1,w[n|1]=power(G,(mod-1)/n);
	for(int i=2;i<n;i++) w[n|i]=1ll*w[n|i-1]*w[n|1]%mod;
	for(int i=n-1;i>=1;i--) w[i]=w[i<<1];
	for(int i=2;i<=150000;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
}
void ntt(poly &f,int c,int n){
	fix(f,n-1);
	for(int i=0;i<n;i++) if(i<rev[i]) swap(f[i],f[rev[i]]);
	for(int k=2;k<=n;k<<=1){
		for(int i=0;i<n;i+=k){
			for(int j=i,*p=w+k;j<i+(k>>1);j++){
				int x=f[j],y=f[j+(k>>1)]*(*p++)%mod;
				f[j+(k>>1)]=del(x,y);
				f[j]=add(x,y);
			}
		}
	}
	if(!c) reverse(f.begin()+1,f.begin()+n); 
}
poly operator+(poly f,poly g){
	fix(f,max(f.size(),g.size())-1);
	for(int i=0;i<g.size();i++) f[i]=add(f[i],g[i]);
	return f;
}
poly operator-(poly f,poly g){
	fix(f,max(f.size(),g.size())-1);
	for(int i=0;i<g.size();i++) f[i]=del(f[i],g[i]);
	return f;
}
poly operator*(poly f,long long g){
	for(int i=0;i<f.size();i++) f[i]=f[i]*g%mod;
	return f;
}
poly operator*(poly f,poly g){
	int m=f.size()+g.size()-2,n=1<<__lg(m)+1,inv=0;
	for(int i=0;i<n;i++) rev[i]=(rev[i>>1]>>1)|(i&1?n>>1:0);
	ntt(f,1,n);
	ntt(g,1,n);
	inv=power(n,mod-2);
	for(int i=0;i<n;i++) f[i]=f[i]*g[i]%mod;
	ntt(f,0,n);
	fix(f,m);
	for(int i=0;i<=m;i++) f[i]=f[i]*inv%mod;
	return f;
}
poly Der(poly f){
	for(int i=1;i<f.size();i++) f[i-1]=f[i]*i%mod;
	f.pop_back();
	return f;
}
poly Int(poly f){
	f.push_back(0);
	for(int i=f.size()-1;i>=1;i--) f[i]=f[i-1]*inv[i]%mod;
	f[0]=0;
	return f;
}
poly Inv(poly f){
	int n=f.size(),lst=f.size()-1,inv=0;
	poly g(1,power(f[0],mod-2));
	fix(f,n*2);
	for(int m=2;m/2<n;m<<=1){
		poly h(f.begin(),f.begin()+m);
		for(int i=0;i<m*2;i++) rev[i]=(rev[i>>1]>>1)|(i&1?m:0);
		ntt(g,1,m*2);
		ntt(h,1,m*2);
		inv=power(m*2,mod-2);
		for(int i=0;i<m*2;i++) g[i]=del(add(g[i],g[i]),g[i]*g[i]%mod*h[i]%mod);
		ntt(g,0,m*2);
		fix(g,m);
		for(int i=0;i<=m;i++) g[i]=g[i]*inv%mod;
	}
	fix(g,lst);
	return g;
}
poly operator/(poly f,poly g){
	int n=f.size()-1,m=g.size()-1;
	if(n-m+1<0) return poly();
	reverse(f.begin(),f.end());
	reverse(g.begin(),g.end());
	fix(f,n-m+1);
	fix(g,n-m+1);
	poly h=f*Inv(g);
	fix(h,n-m);
	reverse(h.begin(),h.end());
	return h;
}
poly operator%(poly f,poly g){
	poly h=f-f/g*g;
	fix(h,1ll*g.size()-2);
	return h;
}
poly Ln(poly f){
	poly g=Der(f)*Inv(f);
	fix(g,1ll*f.size()-2);
	return Int(g);
}
poly Exp(poly f){
	int n=f.size(),lst=f.size()-1;
	poly g(1,1);
	fix(f,n*2);
	for(int m=2;m/2<n;m<<=1){
		poly h(f.begin(),f.begin()+m);
		h[0]++;
		fix(g,m);
		g=g*(h-Ln(g));
	}
	fix(g,lst);
	return g;
}
poly Sqrt(poly f){
	int n=f.size(),lst=f.size()-1;
	poly g(1,sqrt(f[0]));
	fix(f,n*2);
	for(int m=2;m/2<n;m<<=1){
		poly h(f.begin(),f.begin()+m);
		fix(g,m);
		g=(g+h*Inv(g))*((mod+1)/2);
	}
	fix(g,lst);
	return g;
}
poly Pow(poly f,char *k){
	long long n=f.size()-1,b=0,k1=0,k2=0,k3=0,val=0;
	while(b<=n&&!f[b]) b++;
	for(int i=1;k[i];i++) k1=(k1*10+k[i]-48)%mod,k2=(k2*10+k[i]-48)%(mod-1);
	for(int i=1;k[i]&&i<=6;i++) k3=k3*10+k[i]-48;
	if(b*k1>n||k3>n&&!f[0]){
		for(int i=0;i<=n;i++) f[i]=0;
		return f;
	}
	for(int i=0;i<=n;i++) f[i]=(i+b<=n?f[i+b]:0);
	val=power(f[0],k2);
	b*=k1;
	f=Exp(Ln(f*power(f[0],mod-2))*k1);
	for(int i=n;i>=b;i--) f[i]=f[i-b]*val%mod;
	for(int i=0;i<b;i++) f[i]=0;
	return f;
}
int main(){
	init(1<<20);
	scanf("%d%d",&n,&m);
	poly f(n+1),g(n+1);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&a,&b),b=(b?b+1:n+1)*a;
		if(a<=n) g[a]=add(g[a],1);
		if(b<=n) g[b]=del(g[b],1);
	}
	for(int i=1;i<=n;i++) for(int j=1;i*j<=n;j++) f[i*j]=add(f[i*j],g[i]*inv[j]%mod);
	f=Exp(f);
	for(int i=1;i<=n;i++) printf("%lld\n",f[i]);
	return 0;
}