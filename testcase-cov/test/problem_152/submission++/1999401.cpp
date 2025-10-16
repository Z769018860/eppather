#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
const int Q=1<<20|5;
const int INF=(1<<30);
typedef long long ll;
#define rg register int
#define cint const int
const int SZ=1<<21;
char ibuf[SZ|5],*IP1=ibuf,*IP2=ibuf;
#define gc() (__builtin_expect(IP1==IP2,0)&&(IP2=(IP1=ibuf)+fread(ibuf,1,SZ,stdin),__builtin_expect(IP1==IP2,0))?EOF:*IP1++)
char obuf[SZ|5],*OP1=obuf;const char*OP2=obuf+SZ;
inline void pc(const char c){*OP1++=c;__builtin_expect(OP1==OP2,0)&&(fwrite(obuf,1,SZ,stdout),OP1=obuf);}
inline bool ig(const char c){return c>=48&&c<=57;}
inline void read(rg&oi){char c;rg f=1,res=0;while(c=gc(),(!ig(c))&&c^'-');c^'-'?res=(c^48):f=-1;while(c=gc(),ig(c))res=res*10+(c^48);oi=f*res;}
inline void print(rg oi){char io[23];rg l=0;if(oi<0)pc('-'),oi=~oi+1;do io[++l]=(oi%10+48);while(oi/=10);for(;l;--l)pc(io[l]);}
inline void write(cint oi,const char c){print(oi);pc(c);}
namespace Solve{inline void main();}signed main(){Solve::main();fwrite(obuf,1,OP1-obuf,stdout);return 0;}
namespace Solve{char _ST_;
constexpr int mod=1e9+9;
inline int inc(cint x,cint y){return x+y<mod?x+y:x+y-mod;}
inline int dec(cint x,cint y){return x>=y?x-y:x-y+mod;}
inline int mul(cint x,cint y){return 1ll*x*y%mod;}
inline void Inc(rg&x,cint y){x+=y-mod;x+=(x>>31)&mod;}
inline void Dec(rg&x,cint y){x-=y;x+=(x>>31)&mod;}
inline void Mul(rg&x,cint y){x=1ll*x*y%mod;}
inline int pow(rg x,rg y){rg res=1;for(;y;y>>=1,Mul(x,x))(y&1)&&(Mul(res,x),1);return res;}
inline int Inv(cint x){return pow(x,mod-2);}
namespace Sconv{
	ll tmp[Q];
	inline void FWT(rg*f,cint N){
		for(rg i=0;i<N;++i)tmp[i]=f[i];
		for(rg i=1;i<N;i<<=1)for(rg j=0;j<N;j+=i<<1){
		ll*f0=tmp+j,*f1=f0+i;for(rg k=0;k<i;++k)*f1+++=*f0++;}
		for(rg i=0;i<N;++i)f[i]=tmp[i]%mod,f[i]+=(f[i]>>31)&mod;
	}
	inline void IFWT(rg*f,cint N){
		for(rg i=0;i<N;++i)tmp[i]=f[i];
		for(rg i=1;i<N;i<<=1)for(rg j=0;j<N;j+=i<<1){
		ll*f0=tmp+j,*f1=f0+i;for(rg k=0;k<i;++k)*f1++-=*f0++;}
		for(rg i=0;i<N;++i)f[i]=tmp[i]%mod,f[i]+=(f[i]>>31)&mod;
	}
#define ps(x) __builtin_popcount(x)
	int A[std::__lg(Q)+1][Q],B[std::__lg(Q)+1][Q];ll C[Q];int D[Q];
	inline void Gconv(cint*const f,cint*const g,cint N,rg*h){
		cint n=std::__lg(N);for(rg i=0;i<=n;++i)memset(A,0,N<<2),memset(B,0,N<<2);
		for(rg i=0;i<N;++i)A[ps(i)][i]=f[i],B[ps(i)][i]=g[i];
		for(rg i=0;i<=n;++i)FWT(A[i],N),FWT(B[i],N);for(rg i=0;i<=n;++i){
			for(rg j=0;j<=i;++j)for(rg k=0;k<N;++k)C[k]+=1ll*A[j][k]*B[i-j][k];
			for(rg j=0;j<N;++j)D[j]=C[j]%mod,C[j]=0;IFWT(D,N);for(rg j=0;j<N;++j)if(ps(j)==i)h[j]=D[j];
		}
	}
#undef ps
}
int n,N,f[Q],g[Q],h[Q];
char _ED_;inline void main(){
	fprintf(stderr,"static memory:%.6lf MB\n",(&_ST_-&_ED_)/1024./1024.);
	read(n);N=1<<n;for(rg i=0;i<N;++i)read(f[i]);
	for(rg i=0;i<N;++i)read(g[i]);Sconv::Gconv(f,g,N,h);
	for(rg i=0;i<N;++i)write(h[i],' ');pc('\n');
}}