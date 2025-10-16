#include<bits/stdc++.h>
#define LL long long
#define LLL __int128
#define uint unsigned
#define ldb long double
#define uLL unsigned long long
using namespace std;
typedef pair<int,int> PII;
int plen,ptop,pstk[40];
char rdc[1<<20],out[1<<20],*rS,*rT;
#define gc() (rS==rT?rT=(rS=rdc)+fread(rdc,1,1<<20,stdin),(rS==rT?EOF:*rS++):*rS++)
#define pc(x) out[plen++]=(x)
#define flush() fwrite(out,1,plen,stdout),plen=0
template<class T=int>inline T read(){
    T x=0;char ch;bool f=1;
    while(!isdigit(ch=gc()))if(ch=='-')f^=1;
    do x=(x<<1)+(x<<3)+(ch^48);while(isdigit(ch=gc()));
    return f?x:-x;
}
inline int read(char*const s){
	char *t=s,ch;
    while(!isgraph(ch=gc()));
	do (*(t++))=ch;while(isgraph(ch=gc()));
	return (*t)='\000',t-s;
}
template<class T=int>inline void write(T x){
	if(plen>=1000000)flush();
	if(!x)return pc('0'),void();
	if(x<0)pc('-'),x=-x;
	for(;x;x/=10)pstk[++ptop]=x%10;
	while(ptop)pc(pstk[ptop--]+'0');
}
inline void write(const char*s){
	if(plen>=1000000)flush();
	for(int i=0;(*(s+i))!='\000';pc(*(s+(i++))));
}
inline void write(char*const s){
	if(plen>=1000000)flush();
	for(int i=0;(*(s+i))!='\000';pc(*(s+(i++))));
}
typedef pair<int,int> PII;
typedef vector<int> poly;
const int Mod=998244353,G=3,img=86583718;
const int winv=932051910,rinv=998244351;

const int Lim=64,inv2=(Mod+1)/2,inv3=(Mod+1)/3;
const LL Mod2=(LL)Mod*Mod;
poly w0={1},W0;
vector<poly>Tr,Ts;
inline int fadd(int x,int y){
	x+=y-2*Mod;
	return x>=0?x:x+2*Mod;
}
inline int fsub(int x,int y){
	x-=y;
	return x>=0?x:x+2*Mod;
}
inline int reduce(LL x){
	uint t=(uint)x*rinv;
	return (x+(LL)t*Mod)>>32;
}
inline int qpow(int x,int y){
	int res=1;
	for(;y;y>>=1,x=(LL)x*x%Mod)
		if(y&1)res=(LL)res*x%Mod;
	return res;
}
inline int BSGS(int x){
	map<int,int>mp;
	int S=sqrtl(Mod)+1,j=1,q=1;
	for(int i=0;i<S;++i,j=(LL)j*G%Mod)
		mp[(LL)j*x%Mod]=i;
	for(int i=0;i<=S;++i,q=(LL)q*j%Mod)
		if(mp.find(q)!=mp.end()&&i*S>=mp[q])
			return i*S-mp[q];
	return -1;
}
template<int tn>
inline void dft(poly &P){
	int m=P.size(),n=m/tn,L=w0.size();
	if(L*2<n)for(w0.resize(n/2);L*2<n;L<<=1){
		int cr=qpow(G,Mod/(L<<2));
		for(int i=0;i<L;++i)w0[i+L]=(LL)cr*w0[i]%Mod;
	}
	if(W0.size()<w0.size()){
		int pr=W0.size(),ed=w0.size();
		W0.resize(ed);
		for(int i=pr;i<ed;++i)W0[i]=reduce((LL)winv*w0[i]);
	}
	for(int k=n,st1,st2;st1=k*tn,st2=st1>>1,k>1;k>>=1)
		for(int i=0,ie=n/k;i<ie;++i)
			for(int p=i*st1,pe=p+st2;p<pe;++p){
				int q=p+st2,z=reduce((LL)P[q]*W0[i]);
				P[q]=fsub(P[p],z),P[p]=fadd(P[p],z);
			}
    for(int &i:P)(i>=Mod)?(i-=Mod):0;
}
template<int tn>
inline void idft(poly &P){
	int m=P.size(),n=m/tn,ni=qpow(n,Mod-2);
	poly rev(n);
	for(int i=1;i<n;++i)rev[i]=rev[i/2]/2+(i&1)*(n/2);
	for(int &i:P)i=1LL*i*ni%Mod;
	for(int i=1;i<n;++i)if(i<rev[i])
		swap_ranges(P.begin()+tn*i,P.begin()+tn*(i+1),P.begin()+tn*rev[i]);
	for(int i=1;i<n/2;++i)
		swap_ranges(P.begin()+tn*i,P.begin()+tn*(i+1),P.begin()+tn*(n-i));
	dft<tn>(P);
	for(int i=1;i<n;++i)if(i<rev[i])
		swap_ranges(P.begin()+tn*i,P.begin()+tn*(i+1),P.begin()+tn*rev[i]);
}
template<int tn>
inline void mul_mod(poly &P,poly &Q){
	int m=P.size(),n=m/tn;
	dft<tn>(P),dft<tn>(Q);
	for(int i=0;i<n;++i){
		vector<uLL>ans(tn<<1);
		for(int j=0;j<tn;++j){
			for(int k=0;k<tn;++k)
				ans[j+k]+=(LL)P[i*tn+j]*Q[i*tn+k];
			if(!((~j)&7))for(int k=j;k<j+tn;++k)
				if(ans[k]>=(Mod2<<3))ans[k]-=Mod2<<3;
		}
		int c=((i&1)?Mod-w0[i>>1]:w0[i>>1]);
		for(int j=0;j<tn;++j)
			P[i*tn+j]=(ans[j]+ans[j+tn]%Mod*c)%Mod;
	}
	idft<tn>(P);
}
template<size_t... m>
inline void solve(index_sequence<m...>,int n,poly &P,poly &Q){
	static void (*ptrs[])(poly&,poly&)={&mul_mod<m+1>...};
	ptrs[n-1](P,Q);
}
inline poly Mul(poly P,poly Q){
	int pn=P.size(),qn=Q.size(),rn=pn+qn-1,b=1;
	while((Lim<<b)<rn)++b;
	int tn=((rn-1)>>b)+1,m=tn<<b;
	P.resize(m),Q.resize(m);
	solve(make_index_sequence<Lim>{},tn,P,Q);
	return P.resize(rn),P;
}
inline poly Inv(poly P){
	if(P.size()==1)return {qpow(P[0],Mod-2)};
	int n=P.size(),m=(n+1)/2;
	poly tP=P;
	tP.resize(m);
	poly Q=Inv(tP),R=Mul(Mul(P,Q),Q);
    R.resize(n),Q.resize(n);
	for(int i=0;i<n;++i)R[i]=(2LL*Q[i]+Mod-R[i])%Mod;
	return R;
}
inline poly Direv(poly P){
    int n=P.size();
	for(int i=1;i<n;++i)P[i-1]=(LL)P[i]*i%Mod;
	return P[n-1]=0,P;
}
inline poly Inter(poly P){
	int n=P.size();
	for(int i=n-1;i>=1;--i)P[i]=(LL)P[i-1]*qpow(i,Mod-2)%Mod;
	return P[0]=0,P;
}
inline poly Ln(poly P){
	int n=P.size();
	P=Mul(Direv(P),Inv(P));
	return P.resize(n),Inter(P);
}
inline poly Exp(poly P){
	if(P.size()==1)return {1};
	int n=P.size(),m=(n+1)/2;
	poly tP=P;
	tP.resize(m);
	poly Q=Exp(tP);
    Q.resize(n);
    poly R=Ln(Q);
	for(int i=0;i<n;++i)R[i]=(P[i]-R[i]+Mod)%Mod;
	++R[0],R=Mul(R,Q);
	return R.resize(n),R;
}
inline poly Div(poly P,poly Q){
    int n=P.size(),m=Q.size();
	reverse(P.begin(),P.end());
	reverse(Q.begin(),Q.end()),Q.resize(n);
    P=Mul(P,Inv(Q)),P.resize(n-m+1);
	reverse(P.begin(),P.end());
	return P;
}
inline poly MOD(poly P,poly Q){
	int m=Q.size();
	Q=Mul(Q,Div(P,Q)),P.resize(m-1),Q.resize(m-1);
	for(int i=0;i<m-1;++i)P[i]=(P[i]-Q[i]+Mod)%Mod;
	return P;
}
inline poly Qpow(poly P,int k){
	P=Ln(P);
	for(int &i:P)i=(LL)i*k%Mod;
	return Exp(P);
}
inline poly Fpow(poly P,int k,int ki){
	int n=P.size(),tn=0;
	for(tn=0;tn<=n&&!P[tn];++tn);
	if((LL)tn*k>=n){
		for(int &i:P)i=0;
		return P;
	}
	int x=qpow(P[tn],Mod-2),y=qpow(P[tn],ki);
	poly Q(n-tn*k);
	for(int i=0;i<n-tn*k;++i)Q[i]=(LL)P[i+tn]*x%Mod;
	Q=Ln(Q);
	for(int &i:Q)i=(LL)i*k%Mod;
	Q=Exp(Q);
	for(int i=0;i<tn*k;++i)P[i]=0;
	for(int i=tn*k;i<n;++i)P[i]=(LL)Q[i-tn*k]*y%Mod;
	return P;
}
inline poly Sqrt(poly P){
	LL p0=BSGS(P[0]);
	while(p0%2)p0+=Mod-1;
	p0=(LL)qpow(G,p0/2);
	int p_=qpow(P[0],Mod-2);
	for(int &i:P)i=(LL)i*p_%Mod;
	P=Qpow(P,inv2);
	for(int &i:P)i=(LL)i*p0%Mod;
	return P;
}
inline poly Cbrt(poly P){
	LL p0=BSGS(P[0]);
	while(p0%3)p0+=Mod-1;
	p0=(LL)qpow(G,p0/3);
	int p_=qpow(P[0],Mod-2);
	for(int &i:P)i=(LL)i*p_%Mod;
	P=Qpow(P,inv3);
	for(int &i:P)i=(LL)i*p0%Mod;
	return P;
}
inline poly Comp(poly P,poly Q){
    int n=P.size(),L=sqrtl(n)+1;
	vector<poly>F(L),G(L);
	F[0].resize(n),G[0].resize(n);
	F[0][0]=1,G[0][0]=1;
	for(int i=1;i<L;++i)F[i]=Mul(F[i-1],Q),F[i].resize(n);
	Q=Mul(F[L-1],Q),Q.resize(n);
	for(int i=1;i<L;++i)G[i]=Mul(G[i-1],Q),G[i].resize(n);
	for(int &i:Q)i=0;
	for(int i=0;i<L;++i){
		poly H(n);
		for(int j=0;j<L&&i*L+j<n;++j)
			for(int k=0;k<n;++k)
				H[k]=(H[k]+(LL)F[j][k]*P[i*L+j])%Mod;
		H=Mul(H,G[i]);
		for(int j=0;j<n;++j)Q[j]=(Q[j]+H[j])%Mod;
	}
	return Q;
}
inline poly Sin(poly P){
	for(int &i:P)i=(LL)i*img%Mod;
	poly Q=Exp(P);
	for(int &i:P)i=(Mod-i)%Mod;
	P=Exp(P);
	int n=P.size();
	for(int i=0;i<n;++i)
		P[i]=(LL)(P[i]-Q[i]+Mod)*inv2%Mod*img%Mod;
	return P;
}
inline poly Cos(poly P){
	for(int &i:P)i=(LL)i*img%Mod;
	poly Q=Exp(P);
	for(int &i:P)i=(Mod-i)%Mod;
	P=Exp(P);
	int n=P.size();
	for(int i=0;i<n;++i)
		P[i]=(LL)(P[i]+Q[i])*inv2%Mod;
	return P;
}
inline poly Tan(poly P){
	return Mul(Sin(P),Inv(Cos(P)));
}
inline poly Asin(poly P){
	int n=P.size();
	poly Q=Mul(P,P);
	for(int &i:Q)i=(Mod-i)%Mod;
	Q[0]=1,Q=Sqrt(Q),Q.resize(n);
	for(int i=0;i<n;++i)P[i]=((LL)img*P[i]+Q[i])%Mod;
	P=Ln(P);
	for(int i=0;i<n;++i)P[i]=(LL)(Mod-img)*P[i]%Mod;
	return P;
}
inline poly Atan(poly P){
	int n=P.size();
	for(int &i:P)i=(LL)img*i%Mod;
	P[0]=1;
	poly Q=Ln(P);
	for(int &i:P)i=(Mod-i)%Mod;
	P[0]=1,P=Ln(P);
	for(int i=0;i<n;++i)P[i]=(LL)img*inv2%Mod*(P[i]-Q[i]+Mod)%Mod;
	return P;
}
inline poly Acos(poly P){
	int n=P.size();
	poly Q(n);
	Q=Asin(Q),P=Asin(P);
	for(int i=0;i<n;++i)P[i]=(Q[i]-P[i]+Mod)%Mod;
	return P;
}
inline poly MulT(poly P,poly Q){
	int n=P.size(),m=Q.size();
	reverse(Q.begin(),Q.end()),Q=Mul(P,Q);
	for(int i=0;i<n;++i)P[i]=Q[i+m-1];
	return P;
}
inline void build_qry(int p,int l,int r,poly&Q){
	if(l==r)return Tr[p]={1,(Mod-Q[l])%Mod},void();
	int mid=(l+r)>>1;
	build_qry(p<<1,l,mid,Q),build_qry(p<<1|1,mid+1,r,Q);
	Tr[p]=Mul(Tr[p<<1],Tr[p<<1|1]);
}
inline void solve_qry(int p,int l,int r,poly P,poly&Q){
	P.resize(r-l+1);
	if(l==r)return Q[l]=P[0],void();
	int mid=(l+r)>>1;
	solve_qry(p<<1,l,mid,MulT(P,Tr[p<<1|1]),Q);
	solve_qry(p<<1|1,mid+1,r,MulT(P,Tr[p<<1]),Q);
}
inline poly Qry(poly P,poly Q){
	int m=Q.size(),n=max((int)P.size(),m);
	P.resize(n+1),Q.resize(n),Tr.resize(n<<2|3);
	build_qry(1,0,n-1,Q);
	solve_qry(1,0,n-1,MulT(P,Inv(Tr[1])),Q);
	return Q.resize(m),Q;
}
inline poly dervt(poly P){
	int n=P.size();
	for(int i=1;i<n;++i)P[i-1]=(LL)i*P[i]%Mod;
	return P.pop_back(),P;
}
inline void build_ins(int p,int l,int r,poly&P){
	if(l==r)return Ts[p]={(Mod-P[l])%Mod,1},void();
	int mid=(l+r)>>1;
	build_ins(p<<1,l,mid,P),build_ins(p<<1|1,mid+1,r,P);
	Ts[p]=Mul(Ts[p<<1],Ts[p<<1|1]);
}
inline poly solve_ins(int p,int l,int r,poly&P){
	if(l==r)return {P[l]};
	int mid=(l+r)>>1;
	poly L=Mul(solve_ins(p<<1,l,mid,P),Ts[p<<1|1]);
	poly R=Mul(solve_ins(p<<1|1,mid+1,r,P),Ts[p<<1]);
	int nR=R.size();
	for(int i=0;i<nR;++i)L[i]=(L[i]+R[i])%Mod;
	return L;
}
inline poly Ins(poly P,poly Q){
	int n=P.size();
	Ts.resize(n<<2|3);
	build_ins(1,0,n-1,P),P=Qry(dervt(Ts[1]),P);
	for(int i=0;i<n;++i)P[i]=(LL)Q[i]*qpow(P[i],Mod-2)%Mod;
	Q=solve_ins(1,0,n-1,P);
	return Q;
}
signed main(){
	int n=read()+1;
	poly P(n);
	for(int &i:P)i=read();
	P=Cbrt(P);
	for(int &i:P)write(i),pc(' ');
	cerr<<clock()*1.0/CLOCKS_PER_SEC<<endl;
	return flush(),0;
}
