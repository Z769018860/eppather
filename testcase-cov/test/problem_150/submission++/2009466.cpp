#include<bits/stdc++.h>
using namespace std;
#define fft
#define il inline
#define fi first
#define se second
#define lhx make_pair
#define eb emplace_back
#define rep(i,l,r) for(int i=(l); i<=(r); ++i)
#define rep_(i,l,r) for(int i=(l); i>=(r); --i)
typedef long long lr;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
constexpr int N=524300,M=20002000,mod0=1e9+7,mod1=998244353,mod2=1004535809,mod3=2013265921;
constexpr db pi=acos(-1.0),eps=1e-9;
constexpr int inf32=0x3f3f3f3f,Inf32=0xcfcfcfcf;
constexpr lr inf64=0x3f3f3f3f3f3f3f3f,Inf64=0xcfcfcfcfcfcfcfcf;
template<typename T>il T Max(T x,T y)
{
    return (x>y)? x:y;
}
template<typename T>il T Min(T x,T y)
{
    return (x<y)? x:y;
}
template<typename T>il T gcd(T x,T y)
{
    return (!y)? x:gcd(y,x%y);
}
template<typename T>il T Abs(T x)
{
    return (x>0)? x:(-x);
}
struct Complex
{
	db a,b;
	il Complex operator +(const Complex &c)const
	{
		return (Complex){a+c.a,b+c.b}; 
	}
	il Complex operator -(const Complex &c)const
	{
		return (Complex){a-c.a,b-c.b};
	}
	il Complex operator *(const Complex &c)const
	{
		return (Complex){a*c.a-b*c.b,a*c.b+b*c.a};
	}
};
Complex kx[N],bx[N],ky[N],by[N],w[N],ans2[N],ans1[N],ans0[N];
constexpr int mod=mod1,G=3;
int fac[N],inv[N],iv[N],val[N],xx[N],yy[N],g[N];
il int Poww(int x,int y)
{
	int mul=1;
	while(y)
	{
		(y&1)? mul=(lr)mul*x%mod:0;
		x=(lr)x*x%mod,y>>=1;
	}
	return mul;
}
il void Pre(int n)
{
	fac[0]=1;
	rep(i,1,n)
		fac[i]=(lr)fac[i-1]*i%mod;
	inv[n]=Poww(fac[n],mod-2);
	rep_(i,n,1)
		inv[i-1]=(lr)inv[i]*i%mod;
	iv[1]=1;
	rep(i,2,n)
		iv[i]=(lr)iv[mod%i]*(mod-mod/i)%mod;
}
il void FFT(Complex c[],int n)
{
	rep(i,0,n-1)
		(val[i]>i)? swap(c[i],c[val[i]]),0:0;
	for(int m=1,stp=(n>>1); m<=(n>>1); m<<=1,stp>>=1)
		for(int l=0; l<n; l+=(m<<1))
			rep(d,0,m-1)
			{
				Complex tmp=w[stp*d]*c[l+d+m];
				c[l+d+m]=c[l+d]-tmp,c[l+d]=c[l+d]+tmp;
			}
}
il void NTT(int c[],int n)
{
	rep(i,0,n-1)
		(val[i]>i)? swap(c[i],c[val[i]]),0:0;
	for(int m=1,stp=(n>>1); m<=(n>>1); m<<=1,stp>>=1)
		for(int l=0; l<n; l+=(m<<1))
			rep(d,0,m-1)
			{
				int tmp=(lr)g[stp*d]*c[l+d+m]%mod;
				(c[l+d+m]=c[l+d])-=tmp;
				(c[l+d+m]<0)? c[l+d+m]+=mod:0;
				c[l+d]+=tmp;
				(c[l+d]>=mod)? c[l+d]-=mod:0;
			}
}
struct Poly
{
	vi v;
	il void rd(int n)
	{
		v.resize(n);
		rep(i,0,n-1)
			cin>>v[i];
	}
	il void wt()
	{
		for(int i:v)
			cout<<i<<' ';
		cout<<'\n';
	}
};
il Poly Fix(Poly a,int n)
{
	a.v.resize(n);
	return a;
}
il Poly O(int n)
{
	Poly a;
	a.v.resize(n,0);
	return a;
}
il Poly I(int n)
{
	Poly a;
	a.v.resize(n,0),a.v[0]=1;
	return a;
}
il Poly operator +(Poly a,Poly b)
{
	int n=a.v.size(),m=b.v.size(),mx=Max(n,m);
	a.v.resize(mx);
	rep(i,0,m-1)
	{
		a.v[i]+=b.v[i];
		(a.v[i]>=mod)? a.v[i]-=mod:0;
	}
	return a;
}
il Poly operator -(Poly a,Poly b)
{
	int n=a.v.size(),m=b.v.size(),mx=Max(n,m);
	a.v.resize(mx);
	rep(i,0,m-1)
	{
		a.v[i]-=b.v[i];
		(a.v[i]<0)? a.v[i]+=mod:0;
	}
	return a;
}
il Poly operator *(Poly a,int b) 
{
	int n=a.v.size();
	rep(i,0,n-1)
		a.v[i]=(lr)a.v[i]*b%mod;
	return a;
}
il Poly operator *(Poly a,Poly b)
{
	int n=a.v.size(),m=b.v.size(),len=n+m-1,lg=0;
	while((1<<lg)<len)
		++lg;
	len=(1<<lg);
	rep(i,1,len-1)
		val[i]=val[i-(i&(-i))]+(len>>1)/(i&(-i));
#ifndef ntt
	rep(i,0,len-1)
		w[i].a=cos(2.0*pi*i/len),w[i].b=sin(2.0*pi*i/len);
	rep(i,0,len-1)
		kx[i].a=0,kx[i].b=0,bx[i].a=0,bx[i].b=0,ky[i].a=0,ky[i].b=0,by[i].a=0,by[i].b=0;
	rep(i,0,n-1)
		kx[i].a=a.v[i]>>15,bx[i].a=a.v[i]&32767;
	rep(i,0,m-1)
		ky[i].a=b.v[i]>>15,by[i].a=b.v[i]&32767;
	FFT(kx,len),FFT(bx,len),FFT(ky,len),FFT(by,len);
	rep(i,0,len-1)
		ans2[i]=kx[i]*ky[i],
		ans1[i]=kx[i]*by[i]+bx[i]*ky[i],
		ans0[i]=bx[i]*by[i],
		w[i].b=-w[i].b;
	FFT(ans2,len),FFT(ans1,len),FFT(ans0,len);
	a.v.resize(n+m-1);
	rep(i,0,n+m-2)
	{
		int a2=(lr)(ans2[i].a/len+0.5)%mod,
			a1=(lr)(ans1[i].a/len+0.5)%mod,
			a0=(lr)(ans0[i].a/len+0.5)%mod;
		a2=((lr)a2<<30)%mod,a1=((lr)a1<<15)%mod;
		(a.v[i]=a2)+=a1;
		(a.v[i]>=mod)? a.v[i]-=mod:0;
		a.v[i]+=a0;
		(a.v[i]>=mod)? a.v[i]-=mod:0;
	}
#else
	g[0]=1,g[1]=Poww(G,(mod-1)/len);
	rep(i,2,len-1)
		g[i]=(lr)g[i-1]*g[1]%mod;
	rep(i,0,len-1)
		xx[i]=0,yy[i]=0;
	rep(i,0,n-1)
		xx[i]=a.v[i];
	rep(i,0,m-1)
		yy[i]=b.v[i];
	NTT(xx,len),NTT(yy,len);
	g[1]=Poww(g[1],mod-2);
	rep(i,2,len-1)
		g[i]=(lr)g[i-1]*g[1]%mod;
	rep(i,0,len-1)
		xx[i]=(lr)xx[i]*yy[i]%mod;
	NTT(xx,len);
	a.v.resize(n+m-1);
	int Iv=Poww(len,mod-2);
	rep(i,0,n+m-2)
		a.v[i]=(lr)xx[i]*Iv%mod;
#endif
	return a;
}
il Poly polyinv(Poly a)
{
	int n=a.v.size();
	if(n==1)
	{
		a.v[0]=Poww(a.v[0],mod-2);
		return a;
	}
	Poly b=polyinv(Fix(a,(n+1)>>1));
	int m=(n+1)>>1,len=n+m-1,lg=0;
	while((1<<lg)<len)
		++lg;
	len=(1<<lg);
	rep(i,1,len-1)
		val[i]=val[i-(i&(-i))]+(len>>1)/(i&(-i));
	g[0]=1,g[1]=Poww(G,(mod-1)/len);
	rep(i,2,len-1)
		g[i]=(lr)g[i-1]*g[1]%mod;
	rep(i,0,len-1)
		xx[i]=0,yy[i]=0;
	rep(i,0,n-1)
		xx[i]=a.v[i];
	rep(i,0,m-1)
		yy[i]=b.v[i];
	NTT(xx,len),NTT(yy,len);
	g[1]=Poww(g[1],mod-2);
	rep(i,2,len-1)
		g[i]=(lr)g[i-1]*g[1]%mod;
	rep(i,0,len-1)
		xx[i]=(lr)yy[i]*yy[i]%mod*xx[i]%mod;
	NTT(xx,len);
	b.v.resize(n);
	int Iv=Poww(len,mod-2);
	rep(i,m,n-1)
	{
		int tmp=(lr)xx[i]*Iv%mod;
		b.v[i]-=tmp;
		(b.v[i]<0)? b.v[i]+=mod:0;
	}
	return b;
}
il Poly Der(Poly a)
{
	int n=a.v.size();
	rep(i,1,n-1)
		a.v[i-1]=(lr)a.v[i]*i%mod;
	a.v.pop_back();
	return a;
}
il Poly Int(Poly a)
{
	a.v.eb(0);
	int n=a.v.size();
	rep_(i,n-1,1)
		a.v[i]=(lr)a.v[i-1]*iv[i]%mod;
	a.v[0]=0;
	return a;
}
il Poly polyln(Poly a)
{
	int n=a.v.size();
	return Int(Fix(Der(a)*polyinv(a),n-1));
}
il Poly polyexp(Poly a)
{
	int n=a.v.size();
	if(n==1)
	{
		a.v[0]=1;
		return a;
	}
	Poly b=polyexp(Fix(a,(n+1)>>1));
	return Fix(b+b*(a-polyln(Fix(b,n))),n);
}
il Poly polypow(Poly a,int k)
{
	int n=a.v.size(),pos=0;
	while(pos<n&&!a.v[pos])
		++pos;
	if((lr)pos*k>=n)
	{
		rep(i,0,n-1)
			a.v[i]=0;
		return a;
	}
	rep(i,0,n-1-pos)
		a.v[i]=a.v[i+pos];
	a.v.resize(n-pos);
	int b=a.v[0];
	a=Fix(polyexp(polyln(a*Poww(b,mod-2))*k)*Poww(b,k),n);
	rep_(i,n-1,pos*k)
		a.v[i]=a.v[i-pos*k];
	rep(i,0,pos*k-1)
		a.v[i]=0;
	return a;
}
il Poly polypow(Poly a,int k1,int k2,int k3)
{
	int n=a.v.size(),pos=0;
	while(pos<n&&!a.v[pos])
		++pos;
	if((lr)pos*k3>=n)
	{
		rep(i,0,n-1)
			a.v[i]=0;
		return a;
	}
	rep(i,0,n-1-pos)
		a.v[i]=a.v[i+pos];
	a.v.resize(n-pos);
	int b=a.v[0];
	a=Fix(polyexp(polyln(a*Poww(b,mod-2))*k2)*Poww(b,k1),n);
	rep_(i,n-1,pos*k3)
		a.v[i]=a.v[i-pos*k3];
	rep(i,0,pos*k3-1)
		a.v[i]=0;
	return a;
}
il Poly operator /(Poly a,Poly b)
{
	int n=a.v.size(),m=b.v.size();
	if(n<m)
	{
		a.v[0]=0;
		return Fix(a,1);
	}
	reverse(a.v.begin(),a.v.end());
	reverse(b.v.begin(),b.v.end());
	a=Fix(Fix(a,n-m+1)*polyinv(Fix(b,n-m+1)),n-m+1);
	reverse(a.v.begin(),a.v.end());
	return a;
}
il Poly operator %(Poly a,Poly b)
{
	int m=b.v.size();
	return Fix(a-a/b*b,m-1);
}
struct Cipolla
{
	int a,b,i;
	Cipolla(int A,int B,int I)
	{
		a=A,b=B,i=I;
	}
	il Cipolla operator *(const Cipolla &c)const
	{
		return (Cipolla){(int)(((lr)a*c.a%mod+(lr)b*c.b%mod*i%mod)%mod),(int)(((lr)a*c.b%mod+(lr)b*c.a%mod)%mod),i};
	}
};
il int Poww(Cipolla x,int y)
{
	Cipolla mul(1,0,x.i);
	while(y)
	{
		if(y&1)
			mul=mul*x;
		x=x*x,y>>=1;
	}
	return mul.a;
}
il int Sqrt(int n)
{
	mt19937 eng(time(0));
	n%=mod;
	int a=eng()%mod,m=((lr)a*a%mod-n+mod)%mod;
	while(Poww(m,(mod-1)>>1)==1)
		a=eng()%mod,m=((lr)a*a%mod-n+mod)%mod;
	int x1=Poww((Cipolla){a,1,m},(mod+1)>>1),x2=(mod-x1)%mod;
	return Min(x1,x2);
}
il Poly polysqrt(Poly a)
{
	int n=a.v.size();
	if(n==1)
	{
		a.v[0]=Sqrt(a.v[0]);
		return a;
	}
	Poly b=Fix(polysqrt(Fix(a,(n+1)>>1)),n);
	return Fix((b+a*polyinv(b))*((mod+1)>>1),n);
}
Poly a; 
il void Solve()
{
	int n,k;
	cin>>n>>k,++n,a.rd(n),Pre(n);
	Poly b=a;
	b=polysqrt(b);
	b=polyinv(b);
	b=Int(b);
	b=polyexp(b);
	b=(I(1)*2)+a-(I(1)*a.v[0])-b;
	b=polyln(b);
	b=I(1)+b;
	b=polypow(b,k);
	b=Der(b);
	b=Fix(b,n-1);
	b.wt();
}
int main()
{
#ifdef FILEIO
    string pre="hack",isuf="in",osuf="out";
    freopen((pre+"."+isuf).c_str(),"r",stdin);
    freopen((pre+"."+osuf).c_str(),"w",stdout);
#endif
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int T=1;
    while(T--)
        Solve();
    return 0;
};