# include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using Poly=vector<int>;
constexpr int mod=998244353,g=3;
void add(int &x,const auto &y){x=(x+y)%mod;}
int power(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(ll)a*a%mod)
		if(b&1) ans=(ll)ans*a%mod;
	return ans;
}
namespace _NTT
{
	constexpr int L=18,N=(1<<L)+1;
	int l,maxn,invn[L+1],inv[N],rev[N],w[N];
	struct _INIT
	{
		_INIT()
		{
			invn[0]=1;invn[1]=(mod+1)/2;
			for(int i=2;i<=L;i++) invn[i]=(ll)invn[i-1]*invn[1]%mod;
			inv[1]=1;
			for(int i=2;i<(1<<L);i++) inv[i]=(ll)(mod-mod/i)*inv[mod%i]%mod;
			for(int i=1;i<(1<<L);i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));
			for(int i=1;i<(1<<L);i<<=1)
			{
				int wm=power(g,(mod-1)/(i<<1));w[i]=1;
				for(int j=1;j<i;j++) w[i+j]=(ll)w[i+j-1]*wm%mod;
			}
		}
	}INIT;
	void init(int n){maxn=1<<(l=31^__builtin_clz(2*n-1));}
	void NTT(Poly &p,bool flag)
	{
		static ull a[N];
		p.resize(maxn);
		for(int i=0;i<maxn;i++) a[i]=p[rev[i]>>(L-l)];
		for(int i=1;i<maxn;i<<=1)
		{
			for(int j=0;j<maxn;j+=i<<1)
				for(int k=j;k<j+i;k++)
				{
					ull x=a[k],y=a[k+i]*w[i+k-j]%mod;
					a[k]=x+y;a[k+i]=x+mod-y;
				}
			if(i==(1<<(L/2))) for(int j=0;j<maxn;j++) a[j]%=mod;
		}
		if(flag) for(int i=0;i<maxn;i++) p[i]=a[i]%mod;
		else
		{
			reverse(a+1,a+maxn);
			int inv=invn[l];
			for(int i=0;i<maxn;i++) p[i]=a[i]%mod*inv%mod;
		}
	}
}
using _NTT::maxn;
using _NTT::init;
using _NTT::NTT;
Poly &sanitize(Poly &F)
{
	while(!F.empty() && !F.back()) F.pop_back();
	return F;
}
Poly operator-(Poly F)
{
	for(int &i:F) i=(mod-i)%mod;
	return F;
}
Poly &operator+=(Poly &F,const Poly &G)
{
	int n=F.size(),m=G.size();
	if(n<m) F.resize(m);
	for(int i=0;i<m;i++) add(F[i],G[i]);
	return F;
}
Poly &operator-=(Poly &F,const Poly &G)
{
	int n=F.size(),m=G.size();
	if(n<m) F.resize(m);
	for(int i=0;i<m;i++) add(F[i],mod-G[i]);
	return F;
}
Poly operator+(Poly F,const Poly &G){return F+=G;}
Poly operator-(Poly F,const Poly &G){return F-=G;}
Poly &operator*=(Poly &F,int k)
{
	for(int &i:F) i=(ll)i*k%mod;
	return F;
}
Poly operator*(int k,Poly F){return F*=k;}
Poly operator*(Poly F,int k){return F*=k;}
Poly mul(Poly F,Poly G,int sz=-1)
{
	int n=F.size(),m=G.size();
	if(sz<0) sz=n+m-1;
	init(n+m-1);
	NTT(F,1);NTT(G,1);
	for(int i=0;i<maxn;i++) F[i]=(ll)F[i]*G[i]%mod;
	NTT(F,0);F.resize(sz);
	return F;
}
Poly operator*(const Poly &F,const Poly &G){return F.empty() || G.empty()?Poly{}:mul(F,G);}
Poly INV(const Poly &F,int sz=-1)
{
	int n=F.size();
	if(sz<0) sz=n;
	Poly G={power(F[0],mod-2)};
	for(int m=1;m<sz;m<<=1)
	{
		Poly F0(F.begin(),F.begin()+min(2*m,n)),G0=G;
		init(2*m);
		NTT(F0,1);NTT(G,1);
		for(int i=0;i<maxn;i++) F0[i]=(ll)F0[i]*G[i]%mod;
		NTT(F0,0);F0.resize(2*m);
		fill(F0.begin(),F0.begin()+m,0);
		NTT(F0,1);
		for(int i=0;i<maxn;i++) G[i]=(ll)G[i]*(mod-F0[i])%mod;
		NTT(G,0);G.resize(min(2*m,sz));
		move(G0.begin(),G0.end(),G.begin());
	}
	return G;
}
Poly mulInv(const Poly &F,const Poly &G,int sz=-1) 
{
	int n=F.size();
	if(sz<0) sz=n;
	int m=(sz+1)/2;
	Poly iG=INV(G,m),G0(G.begin(),G.begin()+min(sz,(int)G.size())),H(F.begin(),F.begin()+min(m,n));
	init(sz);
	NTT(iG,1);NTT(H,1);
	for(int i=0;i<maxn;i++) H[i]=(ll)iG[i]*H[i]%mod;
	NTT(H,0);H.resize(m);
	Poly H0=H;
	NTT(G0,1);NTT(H,1);
	for(int i=0;i<maxn;i++) H[i]=(ll)G0[i]*H[i]%mod;
	NTT(H,0);H.resize(sz);
	fill(H.begin(),H.begin()+m,0);
	for(int i=m,lim=min(sz,n);i<lim;i++) add(H[i],mod-F[i]);
	NTT(H,1);
	for(int i=0;i<maxn;i++) H[i]=(ll)iG[i]*(mod-H[i])%mod;
	NTT(H,0);H.resize(sz);
	move(H0.begin(),H0.end(),H.begin());
	return H;
}
pair<Poly,Poly> DIV(const Poly &F,const Poly &G)
{
	int n=F.size(),m=G.size();
	if(n<m) return {{},F};
	Poly rF(F.rbegin(),F.rend()),rG(G.rbegin(),G.rend());
	Poly Q=mulInv(rF,rG,n-m+1);
	reverse(Q.begin(),Q.end());
	Poly R=mul(G,Q,m-1);
	for(int i=0;i<m-1;i++) R[i]=(F[i]+mod-R[i])%mod;
	return {Q,R};
}
namespace GCD
{
	struct Matrix
	{
		Poly A,B,C,D;
		Matrix operator*(const Matrix &t)const
		{
			Poly tA=A*t.A+B*t.C,tB=A*t.B+B*t.D,tC=C*t.A+D*t.C,tD=C*t.B+D*t.D;
			return {sanitize(tA),sanitize(tB),sanitize(tC),sanitize(tD)};
		}
		Matrix adj()const{return {D,-B,-C,A};}
		pair<Poly,Poly> apply(const Poly &P,const Poly &Q)const
		{
			Poly tP=A*P+B*Q,tQ=C*P+D*Q;
			return {sanitize(tP),sanitize(tQ)};
		}
	};
	pair<int,Matrix> hgcd(Poly P,Poly Q)
	{
		int n=P.size(),m1=P.size()/2;
		if(Q.size()<=m1) return {0,{{1},{},{},{1}}};
		Poly P1(P.begin()+m1,P.end()),Q1(Q.begin()+m1,Q.end());
		auto [A,M1]=hgcd(P1,Q1);
		tie(P,Q)=M1.adj().apply(P,Q);
		if(Q.size()<=m1) return {A,M1};
		auto [a,R]=DIV(P,Q);
		A++;
		swap(P,R);
		swap(sanitize(P),Q);
		if(Q.size()<=m1) return {A,M1*Matrix{a,{1},{1},{}}};
		int m2=n-P.size();
		P1.assign(P.begin()+m2,P.end());
		Q1.assign(Q.begin()+m2,Q.end());
		auto [B,M2]=hgcd(P1,Q1);
		A+=B;
		return {A,M1*Matrix{a,{1},{1},{}}*M2};
	}
	pair<int,Matrix> gcd(Poly P,Poly Q)
	{
		int A=0;
		Matrix M={{1},{},{},{1}};
		while(!Q.empty())
			if(P.size()>=Q.size() && P.size()<2*Q.size()-1)
			{
				auto [tA,tM]=hgcd(P,Q);
				A+=tA;
				M=M*tM;
				tie(P,Q)=tM.adj().apply(P,Q);
			}
			else
			{
				auto [a,R]=DIV(P,Q);
				A++;
				M=M*Matrix{a,{1},{1},{}};
				swap(P,R);
				swap(sanitize(P),Q);
			}
		return {A,M};
	}
}
using GCD::hgcd;
using GCD::gcd;
int main()
{
	ios::sync_with_stdio(false);cin.tie(nullptr);
	int n;
	cin>>n;
	Poly F(n+1),G(n);
	for(int &i:F) cin>>i;
	for(int &i:G) cin>>i;
	auto [A,M]=gcd(sanitize(F),sanitize(G));
	if(~A&1) M.B=-M.B;
	for(int i=0,sz=G.size();i<sz;i++)
		if(G[i])
		{
			M.B*=(ll)M.C[i]*power(G[i],mod-2)%mod;
			break;
		}
	M.B.resize(n);
	for(int i=0;i<n;i++) cout<<M.B[i]<<" \n"[i==n-1];
	return 0;
}