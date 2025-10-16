#include<bits/stdc++.h>
using u64=uint64_t;
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

constexpr int maxN=1<<17;

int w[maxN],wI[maxN];
void init_ntt(int n=maxN){
    w[0]=wI[0]=1;
	for(int i=1;i<n;i<<=1){w[i]=qpw(_g,(mod>>2)/i),wI[i]=qpw(w[i],mod-2);}
	for(int i=1;i<n;++i){w[i]=mul(w[i&(i-1)],w[i&-i]),wI[i]=mul(wI[i&(i-1)],wI[i&-i]);}
}
void dif(int*f,int lim){
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
}
void dit(int*f,int lim){
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
void dot(int*f,int lim,const int *g){
	for(int i=0;i<lim;++i){f[i]=mul(f[i],g[i]);}
}
void dot(const int*f,const int *g,int lim,int*h){
	for(int i=0;i<lim;++i){h[i]=mul(f[i],g[i]);}
}
constexpr int iv4=qpw(4,mod-2);
void Inv(const int*f,int n,int*g){
	static int o[maxN],h[maxN];
	g[0]=qpw(f[0],mod-2);
	int lim=bcl(n);
	for(int t=2,m=1,fx=mod-iv4;t<=lim;m=t,t<<=1,fx=mul(fx,iv4)){
		int xl=std::min(t,n);
		std::fill(std::copy_n(f,xl,o),o+t,0),std::fill(std::copy_n(g,m,h),h+t,0);
		dif(o,t),dif(h,t),dot(o,t,h),dit(o,t),std::fill_n(o,m,0),dif(o,t),dot(o,t,h),dit(o,t);
        for(int i=m;i<xl;++i){g[i]=mul(o[i],fx);}
	}
}
void Quo(const int*f,int n,const int*g,int*h){
	static int o[maxN],a[maxN],b[maxN];
	if(n==1){*h=qpw(*g,mod-2,*f);return;}
	int lim=bcl(n),hl=lim>>1,iv=mod-(mod-1)/lim;
	Inv(g,hl,a),std::fill_n(a+hl,hl,0),dif(a,lim),std::fill(std::copy_n(f,hl,o),o+lim,0),dif(o,lim),dot(o,lim,a),dit(o,lim);
	for(int i=0;i<hl;++i){h[i]=o[i]=mul(o[i], iv);}
	std::fill_n(o+hl,hl,0),dif(o,lim),std::fill(std::copy_n(g,n,b),b+lim,0),dif(b,lim),dot(o,lim,b),dit(o,lim),std::fill_n(o,hl,0);
	for(int i=hl;i<n;++i){o[i]=(u64(o[i])*iv+(mod-f[i]))%mod;}
	dif(o,lim),dot(o,lim,a),dit(o,lim);
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
	Quo(h,lm,o,q);
	std::reverse(q,q+lm);
	if(r){
		int v=std::min(u,n-u),lm=bcl(std::min(n,m+m-3));
		std::fill(std::copy(g,g+u,o),o+lm,0);
		std::fill(std::copy(q,q+v,h),h+lm,0);
		dif(o,lm),dif(h,lm),dot(o,lm,h),dit(o,lm);
		for(int i=0,niv=(mod-1)/lm;i<u;++i){
			r[i]=(f[i]+o[i]*u64(niv))%mod;
		}
	}
}
void shrk(poly&f){
	while(!f.empty()&&f.back()==0){
		f.pop_back();
	}
}
std::pair<poly,poly> div_mod(const poly&F,const poly&G){
	assert(G.size()>0);
	if(F.size()<G.size()){
		return {{},F};
	}
	poly Q(F.size()-G.size()+1),R(G.size()-1);
	Div(F.data(),F.size(),G.data(),G.size(),Q.data(),R.data());
	shrk(R);
	return {Q,R};
}
poly divd(const poly&F,const poly&G){
	assert(G.size()>0);
	if(F.size()<G.size()){
		return {};
	}
	poly Q(F.size()-G.size()+1);
	Div(F.data(),F.size(),G.data(),G.size(),Q.data());
	return Q;
}
poly modp(const poly&F,const poly&G){
	return div_mod(F,G).second;
}
poly mul_naive(const poly&f,const poly&g){
	int n=f.size(),m=g.size();
	poly r(n+m-1);
	for(int i=0;i<n;++i){
		for(int j=0;j<m;++j){
			r[i+j]=(r[i+j]+u64(f[i])*g[j])%mod;
		}
	}
	return r;
}
poly mul_fft(const poly&f,const poly&g){
	int n=f.size(),m=g.size(),u=n+m-1,lm=bcl(u);
	static int h[maxN];
	poly r;
	r.reserve(lm),r=f,r.resize(lm);
	std::fill(std::copy(g.begin(),g.end(),h),h+lm,0);
	dif(r.data(),lm),dif(h,lm),dot(r.data(),lm,h),dit(r.data(),lm);
	for(int i=0,iv=mod-(mod-1)/lm;i<u;++i){
		r[i]=mul(r[i],iv);
	}
	r.resize(u);
	return r;
}
poly mul(const poly&f,const poly&g){
	if(f.empty()||g.empty()){
		return {};
	}
	if(std::min(f.size(),g.size())<=16){
		return mul_naive(f,g);
	}
	return mul_fft(f,g);
}
int deg(const poly&f){
	return f.size()-1;
}
int at(const poly&f,int n){
	return n>deg(f)?0:f[n];
}
poly add(const poly&f,const poly&g){
	int u=std::max(f.size(),g.size());
	poly r(u);
	for(int i=0;i<u;++i){
		r[i]=dil(at(f,i)+at(g,i)-mod);
	}
	shrk(r);
	return r;
}

struct matp{
	poly a00,a01,a10,a11;
	matp(poly&&b00,poly&&b01,poly&&b10,poly&&b11):a00(b00),a01(b01),a10(b10),a11(b11){
		
	}
	std::pair<poly,poly> mul_vec(const poly&a0,const poly&a1)const{
		return {add(mul(a00,a0),mul(a01,a1)),add(mul(a10,a0),mul(a11,a1))};
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
	void reserve(int n){
		a00.reserve(n);
		a01.reserve(n);
		a10.reserve(n);
		a11.reserve(n);
	}
};
matp operator*(const matp&a,const matp&b){
	return {
		add(mul(a.a00,b.a00),mul(a.a01,b.a10)),
		add(mul(a.a00,b.a01),mul(a.a01,b.a11)),
		add(mul(a.a10,b.a00),mul(a.a11,b.a10)),
		add(mul(a.a10,b.a01),mul(a.a11,b.a11))
	};
}

poly mulx(poly f,int x){
	for(auto&y:f){
		y=mul(y,x);
	}
	return f;
}
poly neg(poly f){
	for(auto&x:f){
		x=dil(-x);
	}
	return f;
}
poly silce(const poly&f,int l,int r=-1){
	if(r==-1||r>int(f.size())){
		r=f.size();
	}
	l=std::max(l,0);
	if(l>=r){
		return {};
	}
	return poly(f.begin()+l,f.begin()+r);
}
matp __brute_force(int*P,int n,int*Q,int m,int k){
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

matp brute_force(poly P,poly Q,int k){
	return __brute_force(P.data(),P.size(),Q.data(),Q.size(),k);
}

matp calc4(poly P,poly Q,int k){
	int d=deg(P);
	assert(deg(Q)<d&&k<=d);
	if(deg(Q)<d-k){
		return {{1},{},{},{1}};
	}
	if(std::min(P.size(),Q.size())<=64){
		return __brute_force(P.data(),P.size(),Q.data(),Q.size(),k);
	}
	if(k==1){
		return {{},{1},{1},neg(divd(silce(P,d-2),silce(Q,d-2)))};
	}
	int h=(k+1)/2,h_=k-h;
	auto M=calc4(silce(P,d-2*h),silce(Q,d-2*h),h);
	int ep=h-deg(M.a11);
	auto [P_,Q_]=M.mul_vec(P,Q);
	assert(deg(P_)==d-h+ep);
	assert(deg(Q_)<d-h);
	if(deg(Q_)<d-k){
		return M;
	}
	if(ep>0){
		
		
		auto D=divd(silce(P_,d-h-2*h_-ep),silce(Q_,d-h-2*h_-ep));
		M=matp({},{1},{1},neg(D))*M;
		
		poly t;
		t.swap(P_);
		P_.swap(Q_);
		Q_=add(t,neg(mul(P_,D)));
	}
	int hh=k-deg(M.a11);
	assert(hh<=h_);
	return calc4(silce(P_,d-k-hh),silce(Q_,d-k-hh),hh)*M;
}
void solve(){
	int n;
	cin>>n;
	poly M(n+1),P(n);
	cin>>M>>P;
	shrk(P);
	auto mat=calc4(M,P,n);
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



