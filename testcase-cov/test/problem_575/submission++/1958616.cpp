#include<bits/stdc++.h>
#include<bits/extc++.h>
#define LL long long
#define uint unsigned
#define LLL __int128_t
#define ldb long double
#define uLL unsigned long long
using namespace std;
char wS[262144],rdc[262144],*rS,*rT,*wT=wS;
#define gc() (rS==rT?rT=rdc+fread(rS=rdc,1,262144,stdin),rS==rT?EOF:*rS++:*rS++)
#define flush() fwrite(wS,1,wT-wS,stdout),wT=wS
inline void pc(const char&x){*wT++=x;if(__builtin_expect(wS+262144==wT,0))flush();}
template<class T=int>inline T read(){
    T x(0);char c;bool f(1);while(!isdigit(c=gc()))if(c==45)f=!f;
    if(f)do x=x*10+(c&15);while(isdigit(c=gc()));
    else do x=x*10-(c&15);while(isdigit(c=gc()));
    return x;
}
template<>inline char read(){char c;while((c=gc())<33);return c;}
template<>inline string read(){char c;string s;while((c=gc())<33);do s+=c;while((c=gc())>32);return s;}
inline int read(char*const s){char c,*t=s;while((c=gc())<33);do *t++=c;while((c=gc())>32);return *t=0,t-s;}
template<class T>inline void write(T x){
    int wtop=0;char wbuf[numeric_limits<T>::digits10+1];
    if(x>=0)do wbuf[wtop++]=(x%10)|48;while(x/=10);
    else{pc(45);do wbuf[wtop++]=-(x%10)|48;while(x/=10);}
    for(;wtop;pc(wbuf[--wtop]));
}
template<>inline void write(char x){pc(x);}
template<>inline void write(char*s){for(;*s;pc(*s++));}
template<>inline void write(const char*s){for(;*s;pc(*s++));}
template<>inline void write(string s){for(auto c:s)pc(c);}
template<class T,class...U>inline void write(const T&x,const U&...y){write(x),write(y...);}
typedef pair<int,int> PII;
typedef tuple<int,int,int> TIII;
typedef tuple<int,int,int,int> TIIII;
typedef vector<int> poly;
const int Mod=998244353,G=3,img=86583718,winv=932051910;
const int Lim=64,inv2=(Mod+1)/2,inv3=(Mod+1)/3,rinv=Mod-2;
const LL Mod2=(LL)Mod*Mod;
poly w0={1},W0;
vector<poly>Tr,Ts;
inline int fadd(int x,const int&y){return (x+=y-2*Mod)>=0?x:x+2*Mod;}
inline int fsub(int x,const int&y){return (x-=y)>=0?x:x+2*Mod;}
inline int reduce(LL x){return (x+(LL)((uint)x*rinv)*Mod)>>32;}
inline int qpow(int x,int y){
	int res=1;
	for(;y;y>>=1,x=(LL)x*x%Mod)
		if(y&1)res=(LL)res*x%Mod;
	return res;
}
template<int T>inline void dft(poly&P){
	const int m=P.size(),n=m/T,n2=n/2;
    int L=w0.size();
	if(L*2<n)for(w0.resize(n2);L*2<n;L<<=1){
		const int cr=qpow(G,Mod/(L<<2));
		for(int i=0;i<L;++i)w0[i+L]=(LL)cr*w0[i]%Mod;
	}
	if(W0.size()<w0.size()){
		const int pr=W0.size(),ed=w0.size();
		W0.resize(ed);
		for(int i=pr;i<ed;++i)W0[i]=reduce((LL)winv*w0[i]);
	}
	for(int k=n,st1,st2;st1=k*T,st2=st1>>1,k>1;k>>=1)
		for(int i=0,ie=n/k;i<ie;++i)
			for(int p=i*st1,pe=p+st2;p<pe;++p){
				const int q=p+st2,z=reduce((LL)P[q]*W0[i]);
				P[q]=fsub(P[p],z),P[p]=fadd(P[p],z);
			}
    for(int &i:P)i>=Mod&&(i-=Mod);
}
template<int T>inline void idft(poly&P){
	const int m=P.size(),n=m/T,ni=qpow(n,Mod-2),n2=n/2;
	poly rev(n);
	for(int i=1;i<n;++i)rev[i]=(rev[i>>1]>>1)+(i&1)*n2;
	for(int &i:P)i=(LL)i*ni%Mod;
	for(int i=1;i<n;++i)if(i<rev[i])swap_ranges(P.begin()+T*i,P.begin()+T*(i+1),P.begin()+T*rev[i]);
	for(int i=1;i<n2;++i)swap_ranges(P.begin()+T*i,P.begin()+T*(i+1),P.begin()+T*(n-i));
	dft<T>(P);
	for(int i=1;i<n;++i)if(i<rev[i])swap_ranges(P.begin()+T*i,P.begin()+T*(i+1),P.begin()+T*rev[i]);
}
template<int T>inline void mul_mod(poly&P,poly&Q){
	const int m=P.size(),n=m/T;
	dft<T>(P),dft<T>(Q);
	for(int i=0;i<n;++i){
		vector<uLL>ans(T<<1);
		for(int j=0;j<T;++j){
			for(int k=0;k<T;++k)
				ans[j+k]+=(LL)P[i*T+j]*Q[i*T+k];
			if(!((~j)&7))for(int k=j;k<j+T;++k)
				if(ans[k]>=(Mod2<<3))ans[k]-=Mod2<<3;
		}
		const int c=((i&1)?Mod-w0[i>>1]:w0[i>>1]);
		for(int j=0;j<T;++j)
			P[i*T+j]=(ans[j]+ans[j+T]%Mod*c)%Mod;
	}
	idft<T>(P);
}
template<size_t... m>inline void solve(index_sequence<m...>,int n,poly&P,poly&Q){
	static void (*ptrs[])(poly&,poly&)={&mul_mod<m+1>...};
	ptrs[n-1](P,Q);
}
inline poly Mul(poly P,poly Q){
	int pn=P.size(),qn=Q.size(),rn=pn+qn-1,b=1;
	while((Lim<<b)<rn)++b;
	int T=((rn-1)>>b)+1,m=T<<b;
	P.resize(m),Q.resize(m);
	solve(make_index_sequence<Lim>{},T,P,Q);
	return P.resize(rn),P;
}
const int N=1e5+5;
int n;
char s[N];
int f[N],A[N],ivf[N],frc[N];
inline void solve(int l,int r){
    if(l==r)return f[l]=l?s[l]!='<'?A[l-1]&1?Mod-f[l]:f[l]:0:1,void();
    int mid=(l+r)>>1;
    solve(l,mid);
    poly L(mid-l+1),R(r-l+1);
    for(int i=l;i<=mid;++i)L[i-l]=A[i]&1?Mod-f[i]:f[i];
    copy(ivf+1,ivf+r-l+1,R.begin()+1),L=Mul(L,R);
    for(int i=mid+1;i<=r;++i)(f[i]+=L[i-l])>=Mod&&(f[i]-=Mod);
    solve(mid+1,r);
}
signed main(){
	n=read(s+1)+1,frc[0]=1;
    for(int i=1;i<=n;++i)frc[i]=(LL)frc[i-1]*i%Mod,A[i]=A[i-1]+(s[i]=='>');
    ivf[n]=qpow(frc[n],Mod-2);
    for(int i=n;i;--i)ivf[i-1]=(LL)i*ivf[i]%Mod;
    solve(0,n);
    write((LL)f[n]*frc[n]%Mod);
	return flush(),0;
}
