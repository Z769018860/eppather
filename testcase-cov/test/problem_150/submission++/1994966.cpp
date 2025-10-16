#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
#include<random>
const int Q=1<<18|5;
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
inline int max(cint x,cint y){return x>y?x:y;}
inline int min(cint x,cint y){return x<y?x:y;}
constexpr int mod=998244353;
inline int inc(cint x,cint y){return x+y<mod?x+y:x+y-mod;}
inline int dec(cint x,cint y){return x>=y?x-y:x-y+mod;}
inline int mul(cint x,cint y){return 1ll*x*y%mod;}
inline void Inc(rg&x,cint y){x+=y-mod;x+=(x>>31)&mod;}
inline void Dec(rg&x,cint y){x-=y;x+=(x>>31)&mod;}
inline void Mul(rg&x,cint y){x=1ll*x*y%mod;}
inline int pow(rg x,rg y){rg res=1;for(;y;y>>=1,Mul(x,x))(y&1)&&(Mul(res,x),1);return res;}
inline int Inv(cint x){return pow(x,mod-2);}
inline int norm1(cint x){return x+((x>>31)&mod);}
inline int norm2(rg x){x-=mod;return x+((x>>31)&mod);}
inline void Norm1(rg&x){x+=(x>>31)&mod;}
inline void Norm2(rg&x){x-=mod;x+=(x>>31)&mod;}
inline void swap(rg&x,rg&y){cint t=x;x=y;y=t;}
namespace poly{
	constexpr int G=3,iG=332748118;
	int _pl[Q<<1],*igp[25];using T=int;using cT=const T;
	inline void init(cint N){
		T*cr=_pl;for(rg i=1,ct=0;i<N;i<<=1,++ct){
			igp[ct]=cr;cr+=i;igp[ct][0]=1;if(i>1)igp[ct][1]=pow(iG,(mod-1)/(i<<1));
			for(rg j=2;j<i;++j)Mul(igp[ct][j]=igp[ct][j-1],igp[ct][1]);
		}
	}
	inline void NTT(T*f,cint N){
		for(rg i=N>>1,ct=__builtin_ctz(i);i>=2;i>>=2,ct-=2){
			cint o=i>>1;for(rg j=0;j<N;j+=(i<<1)){
				T*f0=f+j,*f1=f0+o,*f2=f1+o,*f3=f2+o;
				cint*w0=igp[ct],*w1=w0+o,*w2=igp[ct-1];
				for(rg k=0;k<o;++k){
					cT A=inc(*f0,*f2),B=mul(*w0++,dec(*f0,*f2));
					cT C=inc(*f1,*f3),D=mul(*w1++,dec(*f1,*f3));
					*f0++=inc(A,C);*f2++=inc(B,D);
					*f1++=mul(*w2,dec(A,C));*f3++=mul(*w2,dec(B,D));++w2;
				}
			}
		}
		if(!(__builtin_ctz(N>>1)&1)){
			for(rg j=0;j<N;j+=2){
				T&f0=f[j],&f1=f[j+1];
				cT A=inc(f0,f1),B=dec(f0,f1);f0=A;f1=B;
			}
		}
	}
	inline void INTT(T*f,cint N){
		for(rg i=1,ct=0;i<<1<N;i<<=2,ct+=2){
			for(rg j=0;j<N;j+=(i<<2)){
				T*f0=f+j,*f1=f0+i,*f2=f1+i,*f3=f2+i;
				cint*w0=igp[ct],*w1=igp[ct+1],*w2=w1+i;
				for(rg k=0;k<i;++k){
					cT v0=mul(*w0,*f1),v1=mul(*w0,*f3);++w0;
					cT A=inc(*f0,v0),B=dec(*f0,v0);
					cT C=mul(*w1++,inc(*f2,v1)),D=mul(*w2++,dec(*f2,v1));
					*f0++=inc(A,C);*f1++=inc(B,D);*f2++=dec(A,C);*f3++=dec(B,D);
				}
			}
		}
		if(!(__builtin_ctz(N>>1)&1)){
			cint*w=igp[__builtin_ctz(N>>1)];
			for(rg j=0;j<N>>1;++j){
				T&f0=f[j],&f1=f[j+(N>>1)];
				cT A=f0,B=mul(*w++,f1);f0=inc(A,B);f1=dec(A,B);
			}
		}
		std::reverse(f+1,f+N);cT iN=Inv(N);
		for(rg i=0;i<N;++i)Mul(f[i],iN);
	}
	int pool[Q*20],*cur=pool;
	inline int*alloc(cint N=Q){return(cur+=N,cur-N);}inline void dealloc(cint N=Q){cur-=N;}
	inline void Gconv(cint*const f,cint n,cint*const g,cint m,rg*h){
		cint len=n+m-1;rg N=1;for(;N<len;N<<=1);init(N);rg*A=alloc(N),*B=alloc(N);
		memset(A,0,N<<2);memset(B,0,N<<2);memcpy(A,f,n<<2);memcpy(B,g,m<<2);
		NTT(A,N);NTT(B,N);for(rg i=0;i<N;++i)Mul(A[i],B[i]);
		INTT(A,N);memcpy(h,A,len<<2);dealloc(N);dealloc(N);
	}
	inline void Ginv(cint*const f,cint n,rg*g){
		memset(g,0,n<<2);assert(f[0]);g[0]=Inv(f[0]);rg NN=1;for(;NN<n<<1;NN<<=1);
		rg*A=alloc(NN),*B=alloc(NN);for(rg N=2;N<n<<1;N<<=1){
			cint L=N<<1,nx=N>>1,nt=N<n?N:n;memcpy(A,f,nt<<2);memset(A+nt,0,(L-nt)<<2);
			memcpy(B,g,nx<<2);memset(B+nx,0,(L-nx)<<2);init(L);NTT(A,L);NTT(B,L);
			for(rg i=0;i<L;++i)B[i]=mul(B[i],dec(2,mul(B[i],A[i])));INTT(B,L);memcpy(g,B,nt<<2);
		}
		dealloc(NN);dealloc(NN);
	}
	namespace SQRT{
		namespace cip{
			std::random_device sd;int w;std::mt19937 rnd(sd());
			inline int Rnd(cint l,cint r){return std::uniform_int_distribution<int>(l,r)(rnd);}
			struct cpl{
				int x,y;cpl()=default;cpl(cint X,cint Y):x(X),y(Y){}
				inline cpl operator*(const cpl&rhs)const{return cpl(inc(mul(x,rhs.x),mul(y,mul(rhs.y,w))),inc(mul(x,rhs.y),mul(y,rhs.x)));}
				inline cpl operator*=(const cpl&rhs){return *this=*this*rhs;}
			};
			inline cpl powc(cpl x,rg y){cpl res=cpl(1,0);for(;y;y>>=1,x*=x)if(y&1)res*=x;return res;}
			inline int Gsqrt(cint x){
				if(pow(x,(mod-1)>>1)==mod-1)return -1;
				rg y=Rnd(0,mod-1);w=dec(mul(y,y),x);
				for(;pow(w,(mod-1)>>1)!=mod-1;y=Rnd(0,mod-1),w=dec(mul(y,y),x));
				cint res=powc(cpl(y,1),(mod+1)>>1).x;return min(res,mod-res);
			}
		}
		inline void Gsqrt(rg*f,cint n,rg*g){
			static constexpr int iv2=(mod+1)>>1;
			memset(g,0,n<<2);g[0]=cip::Gsqrt(f[0]);assert(~g[0]);
			rg NN=1;for(;NN<n<<1;NN<<=1);
			rg*A=alloc(NN),*B=alloc(NN);for(rg N=2;N<n<<1;N<<=1){
				cint L=N<<1,nx=N>>1,nt=N<n?N:n;Ginv(g,nt,B);memset(B+nt,0,(L-nt)<<2);
				for(rg i=0;i<nt;++i)B[i]=mul(iv2,B[i]);memcpy(A,f,nt<<2);memset(A+nt,0,(L-nt)<<2);
				init(L);NTT(A,L);NTT(B,L);for(rg i=0;i<L;++i)Mul(A[i],B[i]);INTT(A,L);
				for(rg i=0;i<nt;++i)g[i]=inc(mul(iv2,g[i]),A[i]);
			}
			dealloc(NN);dealloc(NN);
		}
	}using SQRT::Gsqrt;
	inline void Gder(cint*const f,cint n,rg*g){for(rg i=1;i<n;++i)g[i-1]=mul(f[i],i);g[n-1]=0;}
	namespace CALCK{
		int*t[Q];const int*F;
		inline void bld(cint l,cint r){
			if(l==r)return t[l][0]=1,t[l][1]=dec(0,F[l]),void();
			cint mid=l+r>>1;bld(l,mid);t[mid+1]=t[l]+((mid-l+1)<<1);
			bld(mid+1,r);cint lenl=mid-l+2,lenr=r-mid+1;
			poly::Gconv(t[l],lenl,t[mid+1],lenr,t[l]);
		}
		inline void calcK(cint*const f,cint n,cint m,rg*g){
			cint N=(n+1>m?n+1:m)+10;rg*A=alloc(N),*B=alloc(N),*C=alloc(N);
			memset(A,0,N<<2);memset(B,0,N<<2);memset(C,0,N<<2);
			F=f;t[0]=alloc((n+1)<<1);bld(0,n-1);
			for(rg i=0;i<=n;++i)A[i]=t[0][i];
			for(rg i=0;i<=n;++i)B[i]=A[i];std::reverse(B,B+n+1);
			poly::Gder(B,n+1,C);std::reverse(C,C+n);
			poly::Ginv(A,m,B);poly::Gconv(C,n,B,m,A);for(rg i=0;i<m;++i)g[i]=A[i];
			dealloc((n+1)<<1);dealloc(N);dealloc(N);dealloc(N);
		}
	}using CALCK::calcK;
	inline void Gint(cint*const f,cint n,rg*g){
		rg*iv=alloc(n+1);iv[1]=1;for(rg i=2;i<=n;++i)iv[i]=mul(iv[mod%i],mod-mod/i);
		for(rg i=0;i<n;++i)g[i+1]=mul(f[i],iv[i+1]);g[0]=0;dealloc(n+1);
	}
	inline void Gln(cint*const f,cint n,rg*g){
		assert(f[0]==1);rg N=1;for(;N<n+n-1;N<<=1);init(N);
		rg*A=alloc(N),*B=alloc(N);Ginv(f,n,A);Gder(f,n,B);
		memset(A+n,0,(N-n)<<2);memset(B+n,0,(N-n)<<2);
		NTT(A,N);NTT(B,N);for(rg i=0;i<N;++i)Mul(A[i],B[i]);
		INTT(A,N);memset(B+n,0,(N-n)<<2);Gint(A,n,g);dealloc(N);dealloc(N);
	}
	namespace EXP{
		int*F,*G,*iv;using ull=unsigned long long;constexpr ull LIMU=17e18;
		inline void Ic(ull&x,const ull y){((x+=y)>=LIMU)&&(x%=mod);}
		inline void _exp(cint l,cint r){
			if(r-l<=64){
				Mul(G[l],iv[l]);for(rg i=l+1;i<=r;++i){
				ull s=0;for(rg j=l;j<i;++j)Ic(s,1ull*F[i-1-j]*G[j]);
				Inc(G[i],s%mod);Mul(G[i],iv[i]);}return;
			}
			rg D=1;if(r-l<=128)D=16;else if(r-l<=256)D=32;else if(r-l<=512)D=64;else if(r-l<=1024)D=128;
			else for(;(D<<5)<r-l;D<<=1);cint len=D<<1;cint cnt=(r-l+D-1)/D;
			rg*A[32],*B[32];for(rg i=0;i<cnt-1;++i)A[i]=alloc(len);
			for(rg i=0;i<cnt-1;++i)B[i]=alloc(len);rg*C=alloc(len);
			for(rg i=0;i<cnt;++i){
				cint iL=l+i*D,iR=iL+D-1<r?iL+D-1:r;memset(C,0,len<<2);
				for(rg j=0;j<i;++j){for(rg k=0;k<len;++k)Inc(C[k],mul(A[j][k],B[i-j-1][k]));}
				init(len);INTT(C,len);for(rg k=iL;k<=iR;++k)Inc(G[k],C[k-1-l-(i-1)*D]);_exp(iL,iR);
				if(i==cnt-1)return;init(len);memset(A[i],0,len<<2);memset(B[i],0,len<<2);
				for(rg j=iL;j<=iR;++j)A[i][j-iL]=G[j];NTT(A[i],len);
				for(rg j=i*D;j<(i+2)*D;++j)B[i][j-i*D]=F[j];NTT(B[i],len);
			}
			dealloc(len);for(rg i=0;i<cnt-1;++i)dealloc(len);
			for(rg i=0;i<cnt-1;++i)dealloc(len);
		}
		inline void Gexp(cint*const f,cint n,rg*g){
			assert(!f[0]);memset(g,0,n<<2);
			iv=alloc(n+1);iv[0]=iv[1]=1;for(rg i=2;i<=n;++i)iv[i]=mul(iv[mod%i],mod-mod/i);
			F=alloc(n+1);Gder(f,n,F);G=g;g[0]=1;_exp(0,n-1);dealloc(n+1);dealloc(n+1);
		}
	}using EXP::Gexp;
	inline void Gpow(cint*const f,cint n,rg*g,cint k){rg*A=alloc(n);Gln(f,n,A);for(rg i=0;i<n;++i)Mul(A[i],k);Gexp(A,n,g);}
	inline int Gval(cint*const f,cint n,cint*const g,cint m,cint K){
		rg NN=0;{cint len=(n<m?n:m)+m-1;rg N=1;for(;N<len;N<<=1);NN=N;}
		rg*A=alloc(NN),*B=alloc(NN),*C=alloc(NN);rg kn=K;rg nt=n,mt=m;
		memcpy(B,f,nt<<2);memcpy(C,g,mt<<2);for(;kn;kn>>=1){
			cint len=(nt<mt?mt:nt)+mt-1;rg N=1;for(;N<len;N<<=1);init(N);
			memcpy(A,C,mt<<2);memset(A+mt,0,(N-mt)<<2);
			for(rg i=1;i<N;i+=2)A[i]=norm2(mod-A[i]);
			NTT(A,N);memset(B+nt,0,(N-nt)<<2);memset(C+mt,0,(N-mt)<<2);
			NTT(B,N);for(rg i=0;i<N;++i)Mul(B[i],A[i]);INTT(B,N);
			NTT(C,N);for(rg i=0;i<N;++i)Mul(C[i],A[i]);INTT(C,N);
			rg nz=0;for(rg i=(kn&1);i<nt+mt-1;i+=2)B[nz=i>>1]=B[i];nt=nz+1;
			rg mz=0;for(rg i=0;i<mt+mt-1;i+=2)C[mz=i>>1]=C[i];mt=mz+1;
		}
		cint res=mul(B[0],Inv(C[0]));dealloc(NN);dealloc(NN);dealloc(NN);return res;
	}
	inline int Clrec(cint*const f,cint*const g,cint n,cint K){
		rg*A=alloc(n+1),*B=alloc(n+n+1);for(rg i=1;i<=n;++i)A[i]=norm2(mod-f[i]);A[0]=1;
		Gconv(A,n+1,g,n+1,B);cint res=Gval(B,n,A,n+1,K);dealloc(n+1);dealloc(n+n+1);return res;
	}
	inline void Glrec(cint*const f,cint n,rg*g,rg&m){
		m=0;rg*A=alloc(n+1),*B=alloc(n+1);
		rg p=0,dt=0,ln=0;for(rg i=0;i<n;++i){
			unsigned long long v=0;rg c=0;for(rg j=1;j<=m;++j)
			v+=1ull*g[j]*f[i-j],(++c==17)&&(v%=mod,c=0);v%=mod;if(v==f[i])continue;
			if(!m){m=i+1;p=i;dt=dec(f[i],v);for(rg j=0;j<=m;++j)g[j]=0;continue;}
			bool F=0;rg lx;if(m-i<ln-p)F=1,memcpy(B,g,(m+1)<<2),lx=m;
			cint cf=mul(dec(f[i],v),Inv(dt));if(m<ln+i-p)m=ln+i-p;
			Inc(g[i-p],cf);for(rg j=1;j<=ln;++j)Dec(g[i-p+j],mul(cf,A[j]));
			if(F)dt=dec(f[i],v),ln=lx,p=i,memcpy(A,B,(ln+1)<<2);
		}
		dealloc(n+1);dealloc(n+1);
	}
	inline void Ginc(cint*const f,cint n,cint*const g,cint m,rg*h){
		cint len=max(n,m);rg*A=alloc(len);memset(A,0,len<<2);
		for(rg i=0;i<n;++i)A[i]=f[i];for(rg i=0;i<m;++i)Inc(A[i],g[i]);
		for(rg i=0;i<len;++i)h[i]=A[i];dealloc(len);
	}
	inline void Gdec(cint*const f,cint n,cint*const g,cint m,rg*h){
		cint len=max(n,m);rg*A=alloc(len);memset(A,0,len<<2);
		for(rg i=0;i<n;++i)A[i]=f[i];for(rg i=0;i<m;++i)Dec(A[i],g[i]);
		for(rg i=0;i<len;++i)h[i]=A[i];dealloc(len);
	}
}
int n,m,f[Q],g[Q],h[Q];
char _ED_;inline void main(){
	read(n);++n;read(m);for(rg i=0;i<n;++i)read(f[i]),h[i]=f[i];
	poly::Gsqrt(f,n,g);poly::Ginv(g,n,f);poly::Gint(f,n,g);poly::Gexp(g,n,f);
	h[0]=2;poly::Gdec(h,n,f,n,g);poly::Gln(g,n,f);Inc(f[0],1);
	poly::Gpow(f,n,h,m);poly::Gder(h,n,g);
	for(rg i=0;i<n-1;++i)write(g[i],' ');pc('\n');
}}