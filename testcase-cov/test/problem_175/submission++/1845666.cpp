#include<bits/stdc++.h>
#define mp make_pair
#define mt make_tuple
#define eb emplace_back
#define pb push_back
#define pc putchar
#define chkmx(a,b) (a)=max((a),(b))
#define chkmn(a,b) (a)=min((a),(b))
#define fi first
#define se second
using namespace std;
template<class T>
void read(T&x){x=0;char c=getchar();bool f=0;for(;!isdigit(c);c=getchar())f^=c=='-';for(;isdigit(c);c=getchar())x=x*10+c-'0';if(f)x=-x;}
template<class T,class ...ARK>void read(T&x,ARK&...ark){read(x);read(ark...);}
template<class T>void readArr(T*arr,int cnt){while(cnt--)read(*arr),arr++;}
template<class T>void write(T x){if(x<0)pc('-'),x=-x;if(x>=10)write(x/10);pc(x%10+'0');}
template<class T,class ...ARK>void write(T x,ARK...ark){write(x);pc(' ');write(ark...);}
template<class ...ARK>void writeln(ARK...ark){write(ark...);pc('\n');}
typedef long long ll;
int mod=998244353;
struct mint{
	int x;mint(int o=0){x=o;}
	mint&operator+=(mint rhs){return (x+=rhs.x)&&(x>=mod)&&(x-=mod),*this;}
	mint&operator-=(mint rhs){return (x-=rhs.x)&&(x<0)&&(x+=mod),*this;}
	mint&operator*=(mint rhs){return x=1ll*x*rhs.x%mod,*this;}
	friend mint operator+(mint a,mint b){return a+=b;}
	friend mint operator-(mint a,mint b){return a-=b;}
	friend mint operator*(mint a,mint b){return a*=b;}
};
mint v;
struct cp{
	array<mint,3>a;
	mint&operator[](int x){return a[x];}
	cp(mint o=0):a({o,0,0}){}
	cp(mint x,mint y,mint z):a({x,y,z}){}
	cp operator*(cp b){
		cp c;for(int i=0;i<3;i++)for(int j=0;j<3;j++)
			if(i+j>=3)c[i+j-3]+=a[i]*b[j]*v;
			else c[i+j]+=a[i]*b[j];
		return c;
	}
};
template<class T>T ksm(T a,ll b){
	T res(1);for(;b;b>>=1,a=a*a)if(b&1)res=res*a;
	return res;
}
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int rint(int l,int r){return uniform_int_distribution<int>(l,r)(rnd);}
bool chk(int n){
	return ksm(mint(n),(mod-1)/3).x==1;
}
int cbrt(int n){
	if(n==0||n==1||mod==3)return n;
	if(mod%3==2)return ksm(mint(n),(2*mod-1)/3).x;
	if(!chk(n))return 0;
	mint a=rint(1,mod-1);
	while(chk((v=n-a*a*a).x)||!v.x)a=rint(1,mod-1);
	return ksm(cp(a,1,0),(1ll*mod*mod+mod+1)/3)[0].x;
}
signed main(){
	int T,n;read(T);
	while(T--){
		read(n,mod);
		writeln(cbrt(n));
	}
}
