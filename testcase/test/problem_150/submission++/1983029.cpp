#include<bits/stdc++.h>

#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
void file_IO() {
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
mt19937 rd(time(0));
int get(int l,int r) {
	return rd()%(r-l+1)+l;
}
template<int p>
struct mint {
	int x;
	mint() {
		x=0;
	}
	mint(int _x) {
		x=_x%p;
	}
	mint(ll _x) {
		x=_x%p;
	}
	friend mint operator + (mint a,mint b) {
		return a.x+b.x>=p? a.x+b.x-p:a.x+b.x;
	}
	friend mint operator - (mint a,mint b)  {
		return a.x<b.x? a.x-b.x+p:a.x-b.x;
	}
	friend mint operator * (mint a,mint b) {
		return 1ll*a.x*b.x%p;
	}
	friend mint operator ^ (mint a,ll b) {
		mint res=1,base=a;
		while(b) {
			if(b&1)
				res*=base;
			base*=base; b>>=1;
		}
		return res;
	}
	friend mint operator ~ (mint a) {
		return a^(p-2);
	}
	friend mint operator / (mint a,mint b) {
		return a*(~b);
	}
	friend mint & operator += (mint& a,mint b) {
		return a=a+b;
	}
	friend mint & operator -= (mint& a,mint b) {
		return a=a-b;
	}
	friend mint & operator *= (mint& a,mint b) {
		return a=a*b;
	}
	friend mint & operator /= (mint& a,mint b) {
		return a=a/b;
	}
	friend mint operator ++ (mint& a) {
		return a+=1;
	}
	friend mint operator -- (mint& a) {
		return a-=1;
	}
	friend bool operator < (mint a,mint b) {
		return a.x<b.x;
	}
	friend bool operator > (mint a,mint b) {
		return a.x>b.x;
	}
	friend bool operator == (mint a,mint b) {
		return a.x==b.x;
	}
	friend bool operator != (mint a,mint b) {
		return a.x!=b.x;
	}
};
template<int p>
struct Cipolla {
	#define mint mint<p>
	struct comp {
		mint x,y,w;
		comp() {
			x=y=0;
		}
		comp(mint _w) {
			w=_w;
		}
		comp(mint _x,mint _y,mint _w) {
			x=_x;
			y=_y;
			w=_w;
		}
		comp operator * (const comp &tmp) const {
			return comp(x*tmp.x+y*tmp.y*w,x*tmp.y+y*tmp.x,w);
		}
		comp pow(int k) {
			comp res=comp(1,0,w),base=*this;
			while(k) {
				if(k&1)
					res=res*base;
				base=base*base; k>>=1;
			}
			return res;
		}
	};
	bool check(mint n) {
		return (n^(p-1)/2).x==1;
	}
	mint cipolla(mint n) {
		if(n.x==0)
			return 0;
		if(!check(n))
			return -1;
		mint v=0,w=0;
		while(true) {
			v=get(0,p-1);
			w=v*v-n;
			if(!check(w))
				break;
		}
		comp val=comp(v,mint(1),w);
		return val.pow((p+1)/2).x;
	}
	#undef mint
}; 
template<int p,int g>
struct poly {
	#define mint mint<p>
	vector<mint> vec;
	vector<int> r;
	Cipolla<p> awa;
	poly() {
		vec.clear(); 
		r.clear();
	}
	poly(vector<mint> _vec) {
		vec=_vec;
	}
	int len() const {
		return (int)vec.size()-1;
	}
	void resize(int n) {
		vec.resize(n+1);
		r.resize(n+1);
	}
	poly(mint x) {
		resize(0);
		vec[0]=x;
	}
	void read(int l,int r) {
		resize(r);
		rep(i,l,r)
			scanf("%d",&vec[i].x);
	}
	void print() {
		rep(i,0,len())
			printf("%d ",vec[i].x);
		puts("");
	}
	mint calc(mint x) {
		mint res=0,base=1;
		rep(i,0,len()) {
			res+=base*vec[i];
			base*=x;
		}
		return res;
	}
	void NTT(int op) {
		rep(i,0,len()-1) {
			if(i<r[i])
				swap(vec[i],vec[r[i]]);
		}
		for(int i=1;i<len();i<<=1) {
			mint x=(op==1? mint(g):~mint(g))^((p-1)/(i<<1));
			for(int j=0;j<len();j+=(i<<1)) {
				mint y=1;
				rep(k,0,i-1) {
					mint v1=vec[j+k],v2=y*vec[j+k+i];
					vec[j+k]=v1+v2;
					vec[j+k+i]=v1-v2;
					y*=x;
				}
			}
		}
	}
	mint & operator [] (int x) {
		return vec[x];
	} 
	const mint & operator [] (int x) const {
		return vec[x];
	}
	poly get(int x) {
		poly res=*this;
		res.resize(x);
		return res;
	}
	poly rever() const {
		poly res=*this;
		reverse(res.vec.begin(),res.vec.end());
		return res;
	}
	poly rever() {
		poly res=*this;
		reverse(res.vec.begin(),res.vec.end());
		return res;
	}
	poly operator = (const vector<mint> &tmp) const {
		poly res;
		res.resize((int)tmp.size()-1);
		rep(i,0,res.len())
			res[i]=tmp[i];
		return res;
	}
	poly operator + (const poly &tmp) const {
		poly res=*this;
		res.resize(max(tmp.len(),len()));
		rep(i,0,tmp.len())
			res[i]+=tmp[i];
		return res;
	}
	poly operator + (const mint &tmp) const {
		poly res=*this;
		res[0]+=tmp;
		return res;
	}
	poly operator - (const poly &tmp) const {
		poly res=*this;
		res.resize(max(tmp.len(),len()));
		rep(i,0,tmp.len())
			res[i]-=tmp[i];
		return res;
	}
	poly operator - (const mint &tmp) const {
		poly res=*this;
		res[0]-=tmp;
		return res;
	}
	poly operator * (const mint &tmp) const {
		poly res=*this;
		rep(i,0,res.len())
			res[i]*=tmp;
		return res;
	}
	poly operator * (const poly &tmp) const {
		poly a=*this,b=tmp;
		int l=0,d=1;
		while(d<=a.len()+b.len())
			d<<=1,++l;
		a.resize(d);
		b.resize(d);
		rep(i,0,d-1)
			a.r[i]=b.r[i]=(a.r[i>>1]>>1)|((i&1)<<(l-1));
		a.NTT(1); b.NTT(1);
		rep(i,0,d)
			a[i]*=b[i];
		a.NTT(-1);
		mint val=~mint(d);
		rep(i,0,d)
			a[i]*=val;
		a.resize(len()+tmp.len());
		return a;
	}
	poly operator / (const mint &tmp) const {
		poly res=*this;
		rep(i,0,res.len())
			res[i]/=tmp;
		return res;
	}
	poly der(int x=-1) {
		if(x==-1)
			x=len()-1;
		poly res=*this;
		rep(i,1,res.len())
			res[i-1]=res[i]*i;
		res.resize(x);
		return res;
	}
	poly inte(int x=-1) {
		poly res=*this;
		per(i,res.len(),1)
			res[i]=res[i-1]/i;
		res[0]=0;
		if(x!=-1)
			res.resize(x);
		return res;
	}
	poly inv(int x=-1) {
		if(x==-1)
			x=len();
		if(len()==0)
			return poly(~vec[0]);
		poly val=get(len()/2).inv();
		return ((val*2)-((*this)*val*val)).get(x);
	}
	poly sqrt(int x=-1) {
		if(len()==0) {
			mint val=awa.cipolla(vec[0]);
			return poly(min(val,p-val));
		}
		if(x==-1)
			x=len();
		poly val=(get(len()/2)).sqrt(len());
		return ((val+((*this)*(val.inv()))).get(x))*((p+1)/2);
	}
	poly ln(int x=-1) {
		if(x==-1)
			x=len();
		return ((((*this).der())*((*this).inv())).get(x)).inte();
	}
	poly exp(int x=-1) {
		if(len()==0)
			return poly(1);
		if(x==-1)
			x=len();
		poly val=get(len()/2).exp(len());
		return (val+(val*((*this)-(val.ln())))).get(x);
	}
	poly pow(mint k,int x=-1) {
		poly res=(((*this).ln())*k).exp();
		if(x!=-1)
			res.resize(x);
		return res;
	}
	poly operator / (const poly &tmp) const {
		if(len()<tmp.len())
			return poly();
		int x=len()-tmp.len();
		poly a=(*this).rever().get(x);
		poly b=((tmp.rever()).get(x)).inv();
		return ((a*b).get(x)).rever();
	}
	poly operator % (const poly &tmp) const {
		if(len()<tmp.len())
			return *this;
		return ((*this)-((*this/tmp)*tmp)).get(tmp.len()-1);
	}
	#undef mint
};
const int MOD=998244353,g=3;
#define poly poly<MOD,g>
void solve() {
	int n,k;
	poly a;
	scanf("%d%d",&n,&k);
	a.read(0,n);
	poly b=(a.sqrt()).inv();
	poly c=(b.inte()).exp();
	poly d=(((a+2)-a[0])-c).ln();
	poly e=((d+1).pow(k)).der();
	e.print();
}
signed main() {
	
	int testcase=1;
	
	while(testcase--)
		solve();
	return 0;
}