#include <bits/stdc++.h>
using namespace std;
#define OPENIOBUF

namespace FastIO
{
	class FastIOBase
	{
	 protected:
#ifdef OPENIOBUF
		static const int BUFSIZE=1<<22;
		char buf[BUFSIZE+1];
		int buf_p=0;
#endif
		FILE *target;
	 public:
#ifdef OPENIOBUF
	 	virtual void flush()=0;
#endif
		FastIOBase(FILE *f): target(f){}
		~FastIOBase()=default;
	};

	class FastOutput: public FastIOBase
	{
#ifdef OPENIOBUF
	 public:
		inline void flush()
			{ fwrite(buf,1,buf_p,target),buf_p=0; }
#endif
	 protected:
		inline void __putc(char x)
		{
#ifdef OPENIOBUF
			if(buf[buf_p++]=x,buf_p==BUFSIZE)flush();
#else
			putc(x,target);
#endif
		}
		template<typename T>
		inline void __write(T x)
		{
			char stk[256],*top=stk;
			if(x<0) return __putc('-'),__write(-x);
			do *(top++)=x%10,x/=10; while(x);
			for(;top!=stk;__putc(*(--top)+'0'));
		}
	 public:
		FastOutput(FILE *f=stdout): FastIOBase(f){}
#ifdef OPENIOBUF
		~FastOutput(){ flush(); }
#endif
		template<typename ...T>
		inline void writesp(const T &...x)
			{ initializer_list<int>{(this->operator<<(x),__putc(' '),0)...}; }
		template<typename ...T>
		inline void writeln(const T &...x)
			{ initializer_list<int>{(this->operator<<(x),__putc('\n'),0)...}; }
		inline FastOutput &operator <<(char x)
			{ return __putc(x),*this; }
		inline FastOutput &operator <<(const char *s)
			{ for(;*s;__putc(*(s++)));return *this; }
		inline FastOutput &operator <<(const string &s)
			{ return (*this)<<s.c_str(); }
		template<typename T,typename=typename enable_if<is_integral<T>::value>::type>
		inline FastOutput &operator <<(const T &x)
			{ return __write(x),*this; }
	}qout;

	class FastInput: public FastIOBase
	{
#ifdef OPENIOBUF
	 public:
		inline void flush()
			{ buf[fread(buf,1,BUFSIZE,target)]='\0',buf_p=0; }
#endif
	 protected:
	 	inline char __getc()
		{
#ifdef OPENIOBUF
			if(buf_p==BUFSIZE) flush();
			return buf[buf_p++];
#else
			return getc(target);
#endif
		}
	 public:
#ifdef OPENIOBUF
		FastInput(FILE *f=stdin): FastIOBase(f){ buf_p=BUFSIZE; }
#else
		FastInput(FILE *f=stdin): FastIOBase(f){}
#endif
		inline char getchar() { return __getc(); }
		template<typename ...T>
		inline void read(T &...x)
			{ initializer_list<int>{(this->operator>>(x),0)...}; }
		inline FastInput &operator >>(char &x)
			{ while(isspace(x=__getc()));return *this; }
		template<typename T,typename=typename enable_if<is_integral<T>::value>::type>
		inline FastInput &operator >>(T &x)
		{
			static char ch,sym;x=sym=0;
			while(isspace(ch=__getc()));if(ch=='-') sym=1,ch=__getc();
			for(;isdigit(ch);x=(x<<1)+(x<<3)+(ch^48),ch=__getc());
			return sym?x=-x:x,*this;
		}
		inline FastInput &operator >>(char *s)
		{
			while(isspace(*s=__getc()));
			for(;!isspace(*s) && *s;*(++s)=__getc());
			return *s='\0',*this;
		}
		inline FastInput &operator >>(string &s)
		{
			char str_buf[(1<<8)+1],*p=str_buf;
			char *const buf_end=str_buf+(1<<8);
			while(isspace(*p=__getc()));
			for(s.clear(),p++;;p=str_buf)
			{
				for(;p!=buf_end && !isspace(*p=__getc()) && *p;p++);
				*p='\0',s.append(str_buf);
				if(p!=buf_end) break;
			}
			return *this;
		}
	}qin;
}
using namespace FastIO;

namespace ZPoly
{
	typedef long long LL;
	const int MOD=65537,G=3,MAXN=2100000;
	inline int qpow(LL a,LL b) { int r=1;for(a%=MOD;b;(b&1)?r=r*a%MOD:0,a=a*a%MOD,b>>=1);return r; }
	inline int madd(int x) { return x; }
	inline int mmul(int x) { return x; }
	inline int msub(int x,int y) { return (x-=y)<0?x+=MOD:x; }
	inline int mdiv(int x,int y) { return (LL)x*qpow(y,MOD-2)%MOD; }
	template<typename ...Args>
	inline int madd(int x,Args ...y) { return (x+=madd(y...))>=MOD?x-=MOD:x; }
	template<typename ...Args>
	inline int mmul(int x,Args ...y) { return (LL)x*mmul(y...)%MOD; }

	class Polynomial
	{
	 private:
		static const int NTT_LIM=180;
		static int nn,g[MAXN],rev[MAXN];
		int deg;
		vector<int> c;
	 public:
		static void init()
		{
			int gn;
			for(int i=2;i<=MAXN;i<<=1)
			{
				g[i>>1]=1,gn=qpow(G,(MOD-1)/i);
				for(int j=(i>>1)+1;j<i;j++) g[j]=mmul(g[j-1],gn);
			}
		}
		static int butterfly(int len,int *r)
		{
			for(nn=1,r[0]=0;nn<len;nn<<=1);
			for(int i=0;i<nn;i++) r[i]=r[i>>1]>>1|((i&1)?(nn>>1):0);
			return nn;
		}
		static void NTT(int *a,int len,int t=1)
		{
			for(int i=0;i<len;i++)
				if(i<rev[i]) swap(a[i],a[rev[i]]);
			for(int i=1;i<len;i<<=1)
				for(int j=0;j<len;j+=i<<1)
					for(int k=0;k<i;k++)
					{
						int x=a[j+k],y=mmul(g[i+k],a[i+j+k]);
						a[j+k]=madd(x,y),a[i+j+k]=msub(x,y);
					}
			if(t==-1)
			{
				int x=qpow(len,MOD-2);
				for(int i=0;i<len;i++) a[i]=mmul(a[i],x);
				reverse(a+1,a+len);
			}
		}
	 private:
		static void __polyinv(const int *a,int *b,int len)
		{
			static int c[MAXN];
			if(len==1) return b[0]=qpow(a[0],MOD-2),void();
			__polyinv(a,b,(len+1)>>1);
			butterfly(len<<1,rev);
			memcpy(c,a,len<<2);
			memset(b+len,0,(nn-len)<<2);
			memset(c+len,0,(nn-len)<<2);
			NTT(b,nn),NTT(c,nn);
			for(int i=0;i<nn;i++) b[i]=mmul(b[i],msub(2,mmul(b[i],c[i])));
			NTT(b,nn,-1),memset(b+len,0,(nn-len)<<2);
		}
		static void __polyln(const int *a,int *b,int len)
		{
			static int c[MAXN];
			__polyinv(a,b,len);
			for(int i=1;i<len;i++) c[i-1]=mmul(i,a[i]);
			butterfly(len<<1,rev);
			memset(b+len,0,(nn-len)<<2);
			memset(c+len,0,(nn-len)<<2);
			NTT(b,nn),NTT(c,nn);
			for(int i=0;i<nn;i++) b[i]=mmul(b[i],c[i]);
			NTT(b,nn,-1),memset(b+len,0,(nn-len)<<2);
			for(int i=len-1;i>0;i--) b[i]=mdiv(b[i-1],i);
			b[0]=0;
		}
		static void __polyexp(const int *a,int *b,int l,int r)
		{
			static int c1[MAXN],c2[MAXN];
			if(l==r-1) return b[l]=(l?mdiv(b[l],l):1),void();
			int len=r-l,mid=(l+r)>>1;
			__polyexp(a,b,l,mid);
			for(int i=0;i<len;i++) c1[i]=a[i];
			memcpy(c2,b+l,(mid-l)<<2);
			memset(c2+mid-l,0,(r-mid)<<2);
			if(len<=NTT_LIM)
				for(int i=len-1;i>=0;i--)
				{
					c1[i]=mmul(c1[i],c2[0]);
					for(int j=0;j<i;j++) c1[i]=madd(c1[i],mmul(c1[j],c2[i-j]));
				}
			else
			{
				butterfly(len,rev);
				NTT(c1,len),NTT(c2,len);
				for(int i=0;i<len;i++) c1[i]=mmul(c1[i],c2[i]);
				NTT(c1,len,-1);
			}
			for(int i=mid;i<r;i++) b[i]=madd(b[i],c1[i-l]);
			__polyexp(a,b,mid,r);
		}
	 public:
		Polynomial(): deg(1),c(1){}
		explicit Polynomial(int d): deg(d),c(d){}
		Polynomial(const vector<int> &v): deg(v.size()),c(v){}
		Polynomial(const initializer_list<int> &l): deg(l.size()),c(l){}
		Polynomial(const Polynomial &p): deg(p.deg),c(p.c){}
		inline int &operator [](int i) { return c[i]; }
		inline int operator [](int i)const { return c[i]; }
		inline int degree()const { return deg; }
		inline void resize(int d) { c.resize(deg=d); }
		inline Polynomial &operator +=(const Polynomial &p)
		{
			if(deg<p.deg) resize(p.deg);
			for(int i=0;i<deg;i++) c[i]=madd(c[i],p[i]);
			return *this;
		}
		inline Polynomial &operator -=(const Polynomial &p)
		{
			if(deg<p.deg) resize(p.deg);
			for(int i=0;i<deg;i++) c[i]=msub(c[i],p[i]);
			return *this;
		}
		inline Polynomial &operator *=(const Polynomial &p)
		{
			static int c1[MAXN],c2[MAXN];
			int n=deg,m=p.deg;
			resize(n+m-1);
			if(n+m<NTT_LIM)
			{
				memcpy(c1,c.data(),n<<2);
				memset(c2,0,(n+m-1)<<2);
				for(int i=0;i<n;i++)
					for(int j=0;j<m;j++)
						c2[i+j]=madd(c2[i+j],mmul(c1[i],p[j]));
				memcpy(c.data(),c2,(n+m-1)<<2);
			}
			else
			{
				butterfly(n+m,rev);
				memcpy(c1,c.data(),n<<2),memcpy(c2,p.c.data(),m<<2);
				memset(c1+n,0,(nn-n)<<2),memset(c2+m,0,(nn-m)<<2);
				NTT(c1,nn),NTT(c2,nn);
				for(int i=0;i<nn;i++) c1[i]=mmul(c1[i],c2[i]);
				NTT(c1,nn,-1),memcpy(c.data(),c1,deg<<2);
			}
			return *this;
		}
		friend inline Polynomial derivative(const Polynomial &p)
		{
			Polynomial q(p.deg-1);
			for(int i=1;i<p.deg;i++) q[i-1]=mmul(p[i],i);
			return q;
		}
		friend inline Polynomial integral(const Polynomial &p)
		{
			Polynomial q(p.deg+1);
			for(int i=1;i<p.deg;i++) q[i+1]=mdiv(p[i],i+1);
			return q;
		}
		friend inline Polynomial inv(const Polynomial &p)
		{
			if(p[0]==0) cerr<<"[x^0]f(x)=0, f(x)^-1 doesn't exist.\n",abort();
			for(nn=1;nn<(p.deg<<1);nn<<=1);
			Polynomial q(nn);
			__polyinv(p.c.data(),q.c.data(),p.deg);
			return q.resize(p.deg),q;
		}
		friend inline Polynomial ln(const Polynomial &p)
		{
			if(p[0]!=1) cerr<<"[x^0]f(x)!=1, ln(f(x)) doesn't exist.\n",abort();
			for(nn=1;nn<(p.deg<<1);nn<<=1);
			Polynomial q(nn);
			__polyln(p.c.data(),q.c.data(),p.deg);
			return q.resize(p.deg),q;
		}
		friend inline Polynomial exp(const Polynomial &p)
		{
			if(p[0]!=0) cerr<<"[x^0]f(x)!=0, exp(f(x)) doesn't exist.\n",abort();
			static int c[MAXN];
			for(nn=1;nn<p.deg;nn<<=1);
			for(int i=0;i<p.deg;i++) c[i]=mmul(i,p[i]);
			Polynomial q(nn);
			__polyexp(c,q.c.data(),0,nn);
			return q.resize(p.deg),q;
		}
		friend inline pair<Polynomial,Polynomial> divr(const Polynomial &f,const Polynomial &g)
		{
			if(f.deg<g.deg) return make_pair(Polynomial{0},f);
			int n=f.deg-1,m=g.deg-1;
			Polynomial fr(n+1),gr(m+1);
			for(int i=0;i<=n;i++) fr[i]=f[n-i];
			for(int i=0;i<=m;i++) gr[i]=g[m-i];
			fr.resize(n-m+1),gr.resize(n-m+1),fr*=inv(gr);
			fr.resize(n-m+1),reverse(fr.c.begin(),fr.c.end());
			gr=f-fr*g,gr.resize(m);
			return make_pair(fr,gr);
		}
		inline Polynomial &operator *=(int k)
			{ for(auto &i: c) i=mmul(i,k);return *this; }
		inline Polynomial &operator %=(const Polynomial &rhs)
			{ return (*this)=divr(*this,rhs).second; }
		inline Polynomial operator +(const Polynomial &rhs)const
			{ return Polynomial(*this)+=rhs; }
		inline Polynomial operator -(const Polynomial &rhs)const
			{ return Polynomial(*this)-=rhs; }
		inline Polynomial operator *(const Polynomial &rhs)const
			{ return Polynomial(*this)*=rhs; }
		inline Polynomial operator /(const Polynomial &rhs)const
			{ return Polynomial(*this)*=inv(rhs); }
		inline Polynomial operator %(const Polynomial &rhs)const
			{ return divr(*this,rhs).second; }
		friend inline Polynomial operator *(const Polynomial &p,int k)
			{ return Polynomial(p)*=k; }
		friend inline Polynomial operator *(int k,const Polynomial &p)
			{ return Polynomial(p)*=k; } 
	};
	int Polynomial::nn=0,Polynomial::g[]={},Polynomial::rev[]={};
}
using namespace ZPoly;

LL n,m;
int a[1000005],b[1000005];
int solve1()
{
	int M=m+1,ans=0;
	Polynomial f{1},g(M+1),base{0,1};
	b[1]=2,b[M]=MOD-1,a[0]=1,g[M]=1;
	for(int i=1;i<M;i++) a[i]=mmul(2,a[i-1]);
	if(n<M-1) return a[n+1]-a[n];
	for(int i=0;i<M;i++) g[i]=msub(0,b[M-i]);
	for(;n;n>>=1,base=base*base%g) if(n&1) f=f*base%g;
	for(int i=0;i<M;i++) ans=msub(ans,mmul(f[i],a[i]));
	f=f*Polynomial{0,1}%g;
	for(int i=0;i<M;i++) ans=madd(ans,mmul(f[i],a[i]));
	return ans;
}
int fac[70005],inv[70005];
inline int C(LL r,LL c)
{
	if(r<c) return 0;
	if(r<MOD && c<MOD) return mmul(fac[r],inv[c],inv[r-c]);
	return mmul(C(r/MOD,c/MOD),C(r%MOD,c%MOD));
}
int solve2()
{
	LL M=m+1;
	fac[0]=1;
	for(int i=1;i<=MOD-1;i++) fac[i]=mmul(fac[i-1],i);
	inv[MOD-1]=qpow(fac[MOD-1],MOD-2);
	for(int i=MOD-1;i>=1;i--) inv[i-1]=mmul(inv[i],i);
	auto f=[M](LL N)
	{
		int tmp=1,res=0;
		for(LL i=0;i<=N/M;i++,tmp=MOD-tmp)
			res=madd(res,mmul(C(i+N-i*M,i),tmp,qpow(2,N-i*M)));
		return res;
	};
	return msub(f(n+1),f(n));
}
int main()
{
	Polynomial::init();
	qin>>n>>m;
	if(m<=30000)
		qout<<solve1();
	else
		qout<<solve2();
	return 0;
}
