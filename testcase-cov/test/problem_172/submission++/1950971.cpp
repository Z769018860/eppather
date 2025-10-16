#include<bits/stdc++.h>
using i64=long long;
using u64=unsigned long long;
using poly=std::vector<int>;
std::istream&operator>>(std::istream&is,poly&f){
	for(auto&x:f){
		is>>x;
	}
	return is;
}
std::ostream&operator<<(std::ostream&os,const poly&f){
	for(const auto&x:f){
		os<<x;
		if(&x!=&f.back()){
			os<<' ';
		}
	}
	return os;
}
using std::cin;
using std::cout;

constexpr int mod=998244353,_g=3;

constexpr int dil(int x){return x<0?x+mod:x;}
constexpr int mul(int x,int y){return u64(x)*y%mod;}
constexpr int qpw(int a,int b,int r=1){for(;b;b>>=1,a=mul(a,a)){b&1?r=mul(r,a):r;}return r;}
constexpr int bcl(int x){return x<2?1:1<<(std::__lg(x-1)+1);}

constexpr int maxN=1<<19;

int ntt_len = 0;

int w[maxN],wI[maxN],wx2[maxN<<1];
void init_ntt(int n=maxN){
    w[0]=wI[0]=1;
	for(int i=1;i<n;i<<=1){w[i]=qpw(_g,(mod>>2)/i),wI[i]=qpw(w[i],mod-2);}
	for(int i=1;i<n;++i){w[i]=mul(w[i&(i-1)],w[i&-i]),wI[i]=mul(wI[i&(i-1)],wI[i&-i]);}
	wx2[0]=1,wx2[1]=1;
	for(int i=2,i2=4;i<=n;i=i2,i2<<=1){
		int _G=qpw(_g,(mod-1)/i2);
		for(int j=i;j<i2;j+=2){
			wx2[j]=wx2[j>>1];
			wx2[j+1]=mul(wx2[j],_G);
		}
	}
}

void dif(int*f,int lim){
	ntt_len += lim;
    for(int l=lim>>1,r=lim;l;l>>=1,r>>=1){
		for(int*k=f,x,y;k!=f+l;++k){
			x=*k,y=mod-k[l],*k=dil(x-y),k[l]=x+y;
		}
        for(int*j=f+r,*o=w+1;j!=f+lim;j+=r,++o){
            for(int*k=j,x,y;k!=j+l;++k){
				x=dil(*k-mod),y=mul(k[l],*o),*k=x+y,k[l]=x-y+mod;
			}
		}
	}
	for(int i=0;i<lim;++i){
		f[i]=dil(f[i]-mod);
	}
}
void dit(int*f,int lim){
	ntt_len += lim;
    for(int l=1,r=2;l<lim;l<<=1,r<<=1){
		for(int*k=f,x,y;k!=f+l;++k){
			x=*k,y=k[l],*k=dil(x+y-mod),k[l]=dil(x-y);
		}
        for(int*j=f+r,*o=wI+1;j!=f+lim;j+=r,++o){
            for(int*k=j,x,y;k!=j+l;++k){
				x=*k,y=mod-k[l],*k=dil(x-y),k[l]=mul(x+y,*o);
			}
		}
	}
}

void dot(int*g,const int*f,int n){
	for(int i=0;i<n;++i){
		g[i]=mul(g[i],f[i]);
	}
}

void dif2(int*f,const int*g,int l,int n){
	std::copy_n(g,std::min(n,l),f+l);
	for(int i=l;i<n;++i){
		f[l+(i&(l-1))]=dil(f[l+(i&(l-1))]-g[i]);
	}
	dot(f+l,wx2+l,l),dif(f+l,l);
}

void dif(int*f,const int*g,int l,int n){
	std::copy_n(g,std::min(n,l),f);
	for(int i=l;i<n;++i){
		f[i&(l-1)]=dil(f[i&(l-1)]+g[i]-mod);
	}
	dif(f,l);
}

constexpr int iv4=qpw(4,mod-2);
void Inv(int*g,const int*f,int n){
	static int o[maxN],h[maxN];
	g[0]=qpw(f[0],mod-2);
	int lim=bcl(n);
	for(int t=2,m=1,fx=mod-iv4;t<=lim;m=t,t<<=1,fx=mul(fx,iv4)){
		int xl=std::min(t,n);
		std::fill(std::copy_n(f,xl,o),o+t,0),std::fill(std::copy_n(g,m,h),h+t,0);
		dif(o,t),dif(h,t),dot(o,h,t),dit(o,t),std::fill_n(o,m,0),dif(o,t),dot(o,h,t),dit(o,t);
        for(int i=m;i<xl;++i){g[i]=mul(o[i],fx);}
	}
}
void Quo(int*h,const int*f,const int*g,int n){
	static int o[maxN],a[maxN],b[maxN];
	if(n==1){*h=qpw(*g,mod-2,*f);return;}
	int lim=bcl(n),hl=lim>>1,iv=mod-(mod-1)/lim;
	Inv(a,g,hl),std::fill_n(a+hl,hl,0),dif(a,lim),std::fill(std::copy_n(f,hl,o),o+lim,0),dif(o,lim),dot(o,a,lim),dit(o,lim);
	for(int i=0;i<hl;++i){h[i]=o[i]=mul(o[i], iv);}
	std::fill_n(o+hl,hl,0),dif(o,lim),std::fill(std::copy_n(g,n,b),b+lim,0),dif(b,lim),dot(o,b,lim),dit(o,lim),std::fill_n(o,hl,0);
	for(int i=hl;i<n;++i){o[i]=(u64(o[i])*iv+(mod-f[i]))%mod;}
	dif(o,lim),dot(o,a,lim),dit(o,lim);
	for(int i=hl,_iv=mod-iv;i<n;++i){h[i]=mul(o[i],_iv);}
}
void Div(const int*f,int n,const int*g,int m,int*q,int*r=nullptr){
	static int o[maxN],h[maxN];
	int u=m-1,lm=n-u,R=std::min(m,lm);
	if(R<=16){
		std::copy(f,f+n,o);
		for(int i=n-m;~i;--i){
			q[i]=qpw(g[u],mod-2,o[i+u]);
			o[i+u]=0;
			for(int j=u-1;~j;--j){
				o[i+j]=dil(o[i+j]-mul(q[i],g[j]));		
			}
		}
		if(r){
			std::copy(o,o+u,r);
		}
		return;
	}
	std::reverse_copy(g+m-R,g+m,o);
	std::fill(o+R,o+lm,0);
	std::reverse_copy(f+u,f+n,h);
	Quo(q,h,o,lm);
	std::reverse(q,q+lm);
	if(r){
		int v=std::min(u,n-u),lm=bcl(std::min(n,m+m-3));
		std::fill(std::copy(g,g+u,o),o+lm,0);
		std::fill(std::copy(q,q+v,h),h+lm,0);
		dif(o,lm),dif(h,lm),dot(o,h,lm),dit(o,lm);
		for(int i=0,niv=(mod-1)/lm;i<u;++i){
			r[i]=(f[i]+o[i]*u64(niv))%mod;
		}
	}
}

struct silcep{
	const int*f;
	int l;
	silcep()=default;
	silcep(const int*g,int r):f(g),l(r){

	}
	silcep(const int*bg,const int*ed):f(bg),l(ed-bg){

	}
	silcep(const poly&f):f(f.data()),l(f.size()){
		
	}
	int operator[](int p){
		return f[p];
	}
	silcep silce(int L,int R=-1){
		if(R==-1||R>l){
			R=l;
		}
		L=std::max(L,0);
		if(L>=R){
			return {nullptr,0};
		}
		return {f+L,f+R};
	}
	poly cpy(){
		return {f,f+l};
	}
	int at(int p){
		return (p>=l||p<0)?0:f[p];
	}
	int deg(){
		return l-1;
	}
};

int deg(const poly&f){
	return f.size()-1;
}

struct matp{
	poly a00,a01,a10,a11;
	matp()=default;
	matp(poly b00,poly b01,poly b10,poly b11):a00(b00),a01(b01),a10(b10),a11(b11){
		
	}
	void reserve(int n){
		a00.reserve(n);
		a01.reserve(n);
		a10.reserve(n);
		a11.reserve(n);
	}
	void resize(int n){
		a00.resize(n);
		a01.resize(n);
		a10.resize(n);
		a11.resize(n);
	}
	void lmul_reg(const int*p,int n){
		a00.swap(a10);
		a01.swap(a11);
		a10.resize(deg(a00)+n);
		a11.resize(deg(a01)+n);
		for(int i=0;i<n;++i){
			for(int j=0;j<=deg(a00);++j){
				a10[i+j]=(a10[i+j]+u64(p[i])*a00[j])%mod;
			}
			for(int j=0;j<=deg(a01);++j){
				a11[i+j]=(a11[i+j]+u64(p[i])*a01[j])%mod;
			}
		}
	}
};

void shrk(poly&f){
	while(!f.empty()&&f.back()==0){
		f.pop_back();
	}
}

void idif(poly&f){
	int l=f.size(),iv=mod-(mod-1)/l;
	dit(f.data(),l);
	for(auto&x:f){
		x=mul(x,iv);
	}
}

poly divd(silcep F,silcep G){
	assert(G.l>0);
	if(F.l<G.l){
		return {};
	}
	poly Q(F.l-G.l+1);
	Div(F.f,F.l,G.f,G.l,Q.data());
	return Q;
}
std::pair<poly,poly> div_mod(silcep F,silcep G){
	assert(G.l>0);
	if(F.l<G.l){
		return {{},F.cpy()};
	}
	poly Q(F.l-G.l+1),R(G.l-1);
	Div(F.f,F.l,G.f,G.l,Q.data(),R.data());
	shrk(R);
	return {Q,R};
}
poly modp(silcep F,silcep G){
	return div_mod(F,G).second;
}

silcep silce(poly&f,int L,int R=-1){
	return silcep(f).silce(L,R);
}

int at(const poly&f,int p){
	return (p<0||p>=int(f.size()))?0:f[p];
}

matp __brute_force(int*P,int*Q,int n,int m,int k){
	int d=n-1,thr=d-k;
	matp res={{1},{},{},{1}};
	res.reserve(k+1);
	static int nq[maxN];
	while(m>thr){
		int u=m-1;
		for(int i=n-m;~i;--i){
			nq[i]=qpw(mod-Q[u],mod-2,P[i+u]);
			P[i+u]=0;
			for(int j=u-1;~j;--j){
				P[i+j]=(P[i+j]+u64(nq[i])*Q[j])%mod;		
			}
		}
		res.lmul_reg(nq,n-m+1);
		n=u;
		while(n>0&&P[n-1]==0){--n;}
		std::swap(n,m),std::swap(P,Q);
	}
	assert(deg(res.a11)<=k);
	return res;
}

poly dft(silcep f,int l){
	poly dftf(l);
	dif(dftf.data(),f.f,l,f.l);
	return dftf;
}

matp dft(const matp&M,int l){
	return matp(dft(M.a00,l),dft(M.a01,l),dft(M.a10,l),dft(M.a11,l));
}

std::pair<matp,matp> fdft(matp&&M,int l){
	return {M,dft(M,l)};
}

std::pair<matp,matp> brute_force(poly P,poly Q,int k,int l){
	return fdft(__brute_force(P.data(),Q.data(),P.size(),Q.size(),k),l);
}

void dif2(std::pair<matp,matp>&Mm){
	auto&[M,dftM]=Mm;
	int l=dftM.a00.size();
	dftM.resize(l<<1);
	dif2(dftM.a00.data(),M.a00.data(),l,M.a00.size());
	dif2(dftM.a01.data(),M.a01.data(),l,M.a01.size());
	dif2(dftM.a10.data(),M.a10.data(),l,M.a10.size());
	dif2(dftM.a11.data(),M.a11.data(),l,M.a11.size());
}

poly neg(poly f){
	for(auto&x:f){
		x=dil(-x);
	}
	return f;
}

poly mulx(poly f,int x){
	for(auto&y:f){
		y=mul(y,x);
	}
	return f;
}

std::pair<matp,matp> __calc(silcep P,silcep Q,int k,int l){
	
	int d=P.l-1;
	assert(Q.l<P.l);
	assert(k<=d&&k<=l);
	assert(__builtin_popcount(l)==1);
	if(Q.deg()<d-k){
		return {matp({1},{},{},{1}),matp(poly(l,1),poly(l),poly(l),poly(l,1))};
	}
	if(k==1){
		return fdft(matp({},{1},{1},neg(divd(P.silce(d-2),Q.silce(d-2)))),l);
	}
	
	
	
	int h=l/2;
	if(k<=h){
		auto pr=__calc(P,Q,k,h);
		dif2(pr);
		return pr;
	}
	int h_=k-h;
	auto [M,dftM]=__calc(P.silce(d-2*h),Q.silce(d-2*h),h,l);
	int ep=h-deg(M.a11);
	auto YZL=[&](silcep f,int ed){
		
		
		
		
		poly r(l);
		for(int i=ed-l;i<ed;++i){
			r[i-ed+l]=f.at(i);
		}
		dif(r.data(),l);
		return r;
	};
	auto P0=YZL(P,d-h+ep),P1=YZL(P,d-2*h);
	auto Q0=YZL(Q,d-h+ep),Q1=YZL(Q,d-2*h);
	auto LTY=[&](poly&p,poly&q){
		for(int i=0;i<l;++i){
			int x=(u64(p[i])*dftM.a00[i]+u64(q[i])*dftM.a01[i])%mod;
			int y=(u64(p[i])*dftM.a10[i]+u64(q[i])*dftM.a11[i])%mod;
			p[i]=x,q[i]=y;
		}
		idif(p),idif(q);
	};
	LTY(P0,Q0),LTY(P1,Q1);
	poly P_(P1.end()-h-ep,P1.end()),Q_(Q1.end()-h-ep,Q1.end());
	
	P_.insert(P_.end(),P0.end()-h-ep,P0.end());
	Q_.insert(Q_.end(),Q0.end()-h-ep,Q0.end());
	shrk(Q_);
	int x=0;
	for(int i=0,pos=d-h+ep;i<=pos;++i){
		x=(x+u64(P.at(i))*at(M.a00,pos-i)+u64(Q.at(i))*at(M.a01,pos-i))%mod;
	}
	P_.emplace_back(x);
	assert(deg(P_)==2*h+2*ep);
	assert(deg(Q_)<2*h+ep);
	
	
	
	
	
	if(deg(Q_)<h+ep){
		return {M,dftM};
	}
	int hh=k-deg(M.a11),z=M.a11.back(),zz=deg(M.a11);
	if(ep>0){
		
		
		
		
		
		
		auto [D,r]=div_mod(P_,Q_);
		int jok=deg(D),kil=jok-ep;
		hh=h_-kil;
		assert(jok<=h+ep);
		assert(kil>=0&&jok>0);
		z=mul(z,mod-D.back()),zz+=deg(D);
		auto dftD=dft(D,l);
		for(int i=0;i<l;++i){
			int a00=dftM.a10[i];
			int a01=dftM.a11[i];
			int a10=dil(dftM.a00[i]-mul(dftD[i],dftM.a10[i]));
			int a11=dil(dftM.a01[i]-mul(dftD[i],dftM.a11[i]));
			dftM.a00[i]=a00;
			dftM.a01[i]=a01;
			dftM.a10[i]=a10;
			dftM.a11[i]=a11;
		}
		P_.swap(Q_);
		Q_.swap(r);
		
	}
	assert(hh<=h_&&h_<=h);
	
	auto [M_,dftM_]=__calc(silce(P_,3*h+ep-k-hh),silce(Q_,3*h+ep-k-hh),hh,l);
	
	
	
	for(int i=0;i<l;++i){
		int a00=(u64(dftM_.a00[i])*dftM.a00[i]+u64(dftM_.a01[i])*dftM.a10[i])%mod;
		int a01=(u64(dftM_.a00[i])*dftM.a01[i]+u64(dftM_.a01[i])*dftM.a11[i])%mod;
		int a10=(u64(dftM_.a10[i])*dftM.a00[i]+u64(dftM_.a11[i])*dftM.a10[i])%mod;
		int a11=(u64(dftM_.a10[i])*dftM.a01[i]+u64(dftM_.a11[i])*dftM.a11[i])%mod;
		dftM.a00[i]=dftM_.a00[i]=a00;
		dftM.a01[i]=dftM_.a01[i]=a01;
		dftM.a10[i]=dftM_.a10[i]=a10;
		dftM.a11[i]=dftM_.a11[i]=a11;
	}
	auto&MM=dftM_;
	idif(MM.a00),MM.a00.resize(k),shrk(MM.a00);
	idif(MM.a01),MM.a01.resize(k),shrk(MM.a01);
	idif(MM.a10),MM.a10.resize(k),shrk(MM.a10);
	idif(MM.a11);
	zz+=deg(M_.a11);
	if(zz==l){
		MM.a11.resize(k+1);
		int x=mul(z,M_.a11.back());
		MM.a11[k]=x;
		MM.a11[0]=dil(MM.a11[0]-x);
	}
	shrk(MM.a11);
	
	
	return {MM,dftM};
}

void solve(){
	int n;
	cin>>n;
	poly M(n+1),P(n);
	cin>>M>>P;
	shrk(P);
	auto [mat,dft_mat]=__calc(M,P,n,bcl(n));
	auto F=mulx(mat.a01,qpw(mul(mat.a00[0],M[0])+mul(mat.a01[0],P[0]),mod-2));
	for(int i=0;i<n;++i){
		cout<<at(F,i)<<" \n"[i+1==n];
	}
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	
	init_ntt();
	solve();
	return 0;
}
