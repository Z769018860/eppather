# include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using vu=vector<ull>;
namespace _NTT
{
	using Poly=vector<int>;
	constexpr int L=21,N=(1<<L)+1,g=3;
	int rev[N];
	struct _INIT
	{
		_INIT(){for(int i=1;i<(1<<L);i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(L-1));}
	}INIT;
	template<int mod>
	struct Mod
	{
		int l,maxn,invn[L+1],w[N];
		Mod()
		{
			invn[0]=1;invn[1]=power(2,mod-2);
			for(int i=2;i<=L;i++) invn[i]=(ll)invn[i-1]*invn[1]%mod;
			for(int i=1;i<(1<<L);i<<=1)
			{
				int wm=power(g,(mod-1)/(i<<1));w[i]=1;
				for(int j=1;j<i;j++) w[i+j]=(ll)w[i+j-1]*wm%mod;
			}
		}
		int power(int a,int b)
		{
			int ans=1;
			for(;b;b>>=1,a=(ll)a*a%mod)
				if(b&1) ans=(ll)ans*a%mod;
			return ans;
		}
		void init(int n){maxn=1<<(l=__lg(2*n-1));}
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
		void lift(Poly &F)
		{
			if(F.empty()) return;
			int n=F.size();
			init(2*n-1);
			NTT(F,1);
			for(int i=0;i<maxn;i++) F[i]=(ll)F[i]*F[i]%mod;
			NTT(F,0);F.resize(2*n-1);
		}
		void mul(Poly &F,Poly G)
		{
			if(F.empty() || G.empty()) return F.clear(),void();
			int n=F.size(),m=G.size();
			init(n+m-1);
			NTT(F,1);NTT(G,1);
			for(int i=0;i<maxn;i++) F[i]=(ll)F[i]*G[i]%mod;
			NTT(F,0);F.resize(n+m-1);
		}
	};
	Mod<998244353> M1;
	Mod<1004535809> M2;
	ull CRT(int a,int b)
	{
		using u128=unsigned __int128;
		static constexpr ull w1=334257240187163831,w2=668514958533372747,p=1002772198720536577;
		return ((u128)w1*a+(u128)w2*b)%p;
	}
}
bool less_vu(const vu &L,const vu &R)
{
	int n=L.size(),m=R.size();
	return n==m?L<R:n<m;
}
void add_vu(vu &L,const vu &R)
{
	L.resize(max(L.size(),R.size())+1);
	int n=R.size();
	for(int i=0;i<n;i++)
	{
		ull x=R[i];
		for(int j=i;x;j++)
		{
			ull y=(x>~L[j]);
			L[j]+=x;x=y;
		}
	}
}
void sub_vu(vu &L,const vu &R)
{
	int n=R.size();
	for(int i=0;i<n;i++)
	{
		ull x=R[i];
		for(int j=i;x;j++)
		{
			ull y=(x>L[j]);
			L[j]-=x;x=y;
		}
	}
}
void mul_vu(vu &L,const vu &R)
{
	if(L.empty() || R.empty()) return L.clear(),void();
	else if(min(L.size(),R.size())<=256)
	{
		using u128=unsigned __int128;
		int n=L.size(),m=R.size();
		vector<u128> F;
		F.assign(n+m,0);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
			{
				u128 t=(u128)L[i]*R[j];
				F[i+j]+=(ull)t;F[i+j+1]+=t>>64;
			}
		u128 x=0;L.resize(n+m);
		for(int i=0;i<n+m;i++) L[i]=(x+=F[i]),x>>=64;
	}
	else
	{
		using namespace _NTT;
		static constexpr int B=65536;
		static Poly F,F1,F2,G;
		int n=L.size()+R.size();
		for(ull i:L)
			for(int j=0;j<4;j++,i/=B)
				F1.push_back(i%B);
		for(ull i:R)
			for(int j=0;j<4;j++,i/=B)
				G.push_back(i%B);
		F2=F1;F.resize(4*n);
		M1.mul(F1,G);M2.mul(F2,G);
		ull x=0;
		for(int i=0;i<4*n-1;i++)
		{
			x+=CRT(F1[i],F2[i]);
			F[i]=x%B;x/=B;
		}
		F[4*n-1]=x;L.assign(n,0);
		for(int i=0;i<n;i++)
			for(int j=3;j>=0;j--)
				(L[i]*=B)|=F[4*i+j];
		F1.clear();F2.clear();
		F.clear();G.clear();
	}
}
struct Integer
{
	bool neg;vu a;
	Integer()=default;
	Integer(bool n,const vu &a):neg(n),a(a){}
	Integer(const Integer &R):neg(R.neg),a(R.a){}
	Integer(Integer &&R){swap(neg,R.neg);a.swap(R.a);}
	Integer &operator=(const Integer &R){neg=R.neg;a=R.a;return *this;}
	Integer &operator=(Integer &&R){swap(neg,R.neg);a.swap(R.a);return *this;}
	Integer(const int &x):neg(x<0),a(x<0?vu{(ull)(-x)}:(x>0?vu{(ull)x}:vu{})){}
	Integer(const unsigned int &x):neg(0),a(x>0?vu{(ull)x}:vu{}){}
	Integer(const long long &x):neg(x<0),a(x<0?vu{(ull)(-x)}:(x>0?vu{(ull)x}:vu{})){}
	Integer(const unsigned long long &x):neg(0),a(x>0?vu{x}:vu{}){}
	Integer(__int128 x):neg(x<0){for(;x;x>>=64) a.push_back((ull)x);}
	Integer(unsigned __int128 x):neg(0){for(;x;x>>=64) a.push_back((ull)x);}
	Integer(const string &str){from_string(str);}
	friend bool operator==(const Integer &L,const Integer &R){return L.neg==R.neg && L.a==R.a;}
	friend bool operator!=(const Integer &L,const Integer &R){return L.neg!=R.neg || L.a!=R.a;}
	friend bool operator<(const Integer &L,const Integer &R)
	{
		if(L.neg==R.neg) return L.neg^less_vu(L.a,R.a);
		else return L.neg>R.neg;
	}
	friend bool operator>(const Integer &L,const Integer &R){return R<L;}
	friend bool operator<=(const Integer &L,const Integer &R){return !(R<L);}
	friend bool operator>=(const Integer &L,const Integer &R){return !(L<R);}
	Integer &sanitize()
	{
		while(!a.empty() && !a.back()) a.pop_back();
		neg&=!a.empty();
		return *this;
	}
	Integer &operator&=(const Integer &R)
	{
		neg&=R.neg;
		size_t n=a.size(),m=R.a.size();
		if(n>m) a.resize(n=m);
		for(size_t i=0;i<n;i++) a[i]&=R.a[i];
		return sanitize();
	}
	Integer &operator|=(const Integer &R)
	{
		neg|=R.neg;
		size_t n=a.size(),m=R.a.size();
		if(n<m) a.resize(m);
		for(size_t i=0;i<m;i++) a[i]|=R.a[i];
		return sanitize();
	}
	Integer &operator^=(const Integer &R)
	{
		neg^=R.neg;
		size_t n=a.size(),m=R.a.size();
		if(n<m) a.resize(m);
		for(size_t i=0;i<m;i++) a[i]^=R.a[i];
		return sanitize();
	}
	Integer &operator<<=(size_t x)
	{
		if(!x) return *this;
		size_t n=a.size(),d=x/64;x%=64;
		if(x)
		{
			size_t y=64-x;
			a.resize(n+=d+1);
			for(size_t i=n-1;i>d;i--) a[i]=(a[i-d]<<x)|(a[i-d-1]>>y);
			a[d]=a[0]<<x;
		}
		else
		{
			a.resize(n+=d);
			for(size_t i=n-1;i>=d;i--) a[i]=a[i-d];
		}
		fill(a.begin(),a.begin()+d,0);
		return sanitize();
	}
	Integer &operator>>=(size_t x)
	{
		if(!x) return *this;
		size_t n=a.size(),d=x/64,m=n-d-1;x%=64;
		if(d>=n) return neg=0,a.clear(),*this;
		if(x)
		{
			size_t y=64-x;
			for(size_t i=0;i<m;i++) a[i]=(a[i+d]>>x)|(a[i+d+1]<<y);
			a[m]=a[n-1]>>x;
		}
		else for(size_t i=0;i<=m;i++) a[i]=a[i+d];
		a.resize(m+1);
		return sanitize();
	}
	friend Integer operator&(const Integer &L,const Integer &R){return Integer(L)&=R;}
	friend Integer operator|(const Integer &L,const Integer &R){return Integer(L)|=R;}
	friend Integer operator^(const Integer &L,const Integer &R){return Integer(L)^=R;}
	friend Integer operator<<(const Integer &L,const size_t &R){return Integer(L)<<=R;}
	friend Integer operator>>(const Integer &L,const size_t &R){return Integer(L)>>=R;}
	size_t count()const
	{
		size_t cnt=0;
		for(ull i:a) cnt+=__builtin_popcountll(i);
		return cnt;
	}
	Integer &operator+=(const Integer &R)
	{
		if(neg==R.neg) add_vu(a,R.a);
		else if(less_vu(a,R.a))
		{
			Integer tR=R;
			neg^=1;swap(a,tR.a);
			sub_vu(a,tR.a);
		}
		else sub_vu(a,R.a);
		return sanitize();
	}
	Integer &operator-=(const Integer &R)
	{
		if(neg!=R.neg) add_vu(a,R.a);
		else if(less_vu(a,R.a))
		{
			Integer tR=R;
			neg^=1;swap(a,tR.a);
			sub_vu(a,tR.a);
		}
		else sub_vu(a,R.a);
		return sanitize();
	}
	Integer &operator*=(const Integer &R)
	{
		neg^=R.neg;mul_vu(a,R.a);
		return sanitize();
	}
	friend Integer operator+(const Integer &L,const Integer &R){return Integer(L)+=R;}
	friend Integer operator-(const Integer &L,const Integer &R){return Integer(L)-=R;}
	friend Integer operator*(const Integer &L,const Integer &R){return Integer(L)*=R;}
	Integer &from_string(string str)
	{
		if(str=="0") return neg=0,a.clear(),*this;
		static const ull Base=1e19;
		static int o=1;
		static vu pw[30];
		static vector<vu> f;
		reverse(str.begin(),str.end());
		if(str.back()=='-') neg=1,str.pop_back();
		else neg=0;
		int n=str.size();
		for(int i=0;i<n;i+=19)
		{
			ull x=0;
			for(int j=min(n-i-1,18);j>=0;j--) x=x*10+(str[i+j]-'0');
			f.emplace_back(1,x);
		}
		n=f.size();pw[0]={Base};
		for(;(1<<o)<n;o++)
		{
			mul_vu(pw[o]=pw[o-1],pw[o-1]);
			while(!pw[o].empty() && !pw[o].back()) pw[o].pop_back();
		}
		for(int i=0;(1<<i)<n;i++)
		{
			int j=n-1,k=1<<(i+1);
			if((j&=~(k-1))+(1<<i)>=n) j-=k;
			for(;j>=0;j-=k)
			{
				mul_vu(f[j+(1<<i)],pw[i]);
				add_vu(f[j],f[j+(1<<i)]);
				while(!f[j].empty() && !f[j].back()) f[j].pop_back();
			}
		}
		swap(a,f[0]);f.clear();
		return *this;
	}
	template<typename T>
	Integer &from_string(string str,int B,T id)
	{
		if(str=="0") return neg=0,a.clear(),*this;
		static vu pw[30];
		static vector<vu> f;
		int K=1;
		ull Base=B;
		for(ull lim=((ull)-1)/B;Base<=lim;Base*=B) K++;
		reverse(str.begin(),str.end());
		if(str.back()=='-') neg=1,str.pop_back();
		else neg=0;
		int n=str.size();
		for(int i=0;i<n;i+=K)
		{
			ull x=0;
			for(int j=min(n-i-1,K-1);j>=0;j--) x=x*B+id(str[i+j]);
			f.emplace_back(1,x);
		}
		n=f.size();pw[0]={Base};
		for(int i=1;(1<<i)<n;i++)
		{
			mul_vu(pw[i]=pw[i-1],pw[i-1]);
			while(!pw[i].empty() && !pw[i].back()) pw[i].pop_back();
		}
		for(int i=0;(1<<i)<n;i++)
		{
			int j=n-1,k=1<<(i+1);
			if((j&=~(k-1))+(1<<i)>=n) j-=k;
			for(;j>=0;j-=k)
			{
				mul_vu(f[j+(1<<i)],pw[i]);
				add_vu(f[j],f[j+(1<<i)]);
				while(!f[j].empty() && !f[j].back()) f[j].pop_back();
			}
		}
		swap(a,f[0]);f.clear();
		return *this;
	}
	string to_string()const
	{
		if(a.empty()) return "0";
		using namespace _NTT;
		static constexpr int B=10,B1=1e5;
		static const Poly Base={51616,37095,74407,18446};
		static int o=1;
		static Poly pw[30];
		static vector<Poly> f;
		auto lift=[](Poly &F)
		{
			int n=2*F.size();
			Poly F2=F;
			M1.lift(F);M2.lift(F2);
			ull x=0;F.resize(n);
			for(int i=0;i<n-1;i++)
			{
				x+=CRT(F[i],F2[i]);
				F[i]=x%B1;x/=B1;
			}
			F[n-1]=x;
		};
		auto upd=[](Poly &F,Poly &G,const Poly &H)
		{
			int n=max(F.size(),G.size()+H.size())+1;
			Poly G2=G;
			M1.mul(G,H);M2.mul(G2,H);
			ull x=0;F.resize(n);
			for(int i=0,m=G.size();i<n-1;i++)
			{
				x+=F[i]+(i<m?CRT(G[i],G2[i]):0);
				F[i]=x%B1;x/=B1;
			}
			F[n-1]=x;
		};
		int n=a.size();
		pw[0]=Base;
		for(;(1<<o)<n;o++)
		{
			lift(pw[o]=pw[o-1]);
			while(!pw[o].empty() && !pw[o].back()) pw[o].pop_back();
		}
		f.resize(n);
		for(int i=0;i<n;i++)
			for(ull j=a[i];j;j/=B1)
				f[i].push_back(j%B1);
		for(int i=0;(1<<i)<n;i++)
		{
			int j=n-1,k=1<<(i+1);
			if((j&=~(k-1))+(1<<i)>=n) j-=k;
			for(;j>=0;j-=k)
			{
				upd(f[j],f[j+(1<<i)],pw[i]);
				while(!f[j].empty() && !f[j].back()) f[j].pop_back();
			}
		}
		string str;
		for(ull i:f[0])
			for(int j=0;j<5;j++,i/=B)
				str+=i%B+'0';
		f.clear();
		while(!str.empty() && str.back()=='0') str.pop_back();
		if(neg) str+='-';
		reverse(str.begin(),str.end());
		return str;
	}
	template<typename T>
	string to_string(int B,T id)const
	{
		if(a.empty()) return string(1,id(0));
		using namespace _NTT;
		static Poly pw[30];
		static vector<Poly> f;
		int K=1,B1=B;
		for(int lim=(int)1e5/B;B1<=lim;B1*=B) K++;
		
		cerr<<"K = "<<K<<" , B1 = "<<B1<<"\n";
		
		auto lift=[&B1](Poly &F)
		{
			int n=2*F.size();
			Poly F2=F;
			M1.lift(F);M2.lift(F2);
			ull x=0;F.resize(n);
			for(int i=0;i<n-1;i++)
			{
				x+=CRT(F[i],F2[i]);
				F[i]=x%B1;x/=B1;
			}
			F[n-1]=x;
		};
		auto upd=[&B1](Poly &F,Poly &G,const Poly &H)
		{
			int n=max(F.size(),G.size()+H.size())+1;
			Poly G2=G;
			M1.mul(G,H);M2.mul(G2,H);
			ull x=0;F.resize(n);
			for(int i=0,m=G.size();i<n-1;i++)
			{
				x+=F[i]+(i<m?CRT(G[i],G2[i]):0);
				F[i]=x%B1;x/=B1;
			}
			F[n-1]=x;
		};
		ull q=(ull)(-B1)/B1,r=(ull)(-B1)%B1;
		Poly Base={(int)r};
		for(q++;q;q/=B1) Base.push_back(q%B1);
		int n=a.size();
		pw[0]=Base;
		for(int i=1;(1<<i)<n;i++) lift(pw[i]=pw[i-1]);
		f.resize(n);
		for(int i=0;i<n;i++)
			for(ull j=a[i];j;j/=B1)
				f[i].push_back(j%B1);
		for(int i=0;(1<<i)<n;i++)
		{
			int j=n-1,k=1<<(i+1);
			if((j&=~(k-1))+(1<<i)>=n) j-=k;
			for(;j>=0;j-=k) upd(f[j],f[j+(1<<i)],pw[i]);
		}
		string str;
		for(int i:f[0])
			for(int j=0;j<K;j++,i/=B)
				str+=id(i%B);
		while(!str.empty() && str.back()==id(0)) str.pop_back();
		if(neg) str+='-';
		reverse(str.begin(),str.end());
		f.clear();
		return str;
	}
	friend istream &operator>>(istream &is,Integer &a)
	{
		string str;
		is>>str;a.from_string(str);
		return is;
	}
	friend ostream &operator<<(ostream &os,const Integer &a){return os<<a.to_string();}
};
int main()
{
	ios::sync_with_stdio(false);cin.tie(nullptr);
	int B1,B2;
	string str;
	cin>>B1>>B2>>str;
	cout<<Integer().from_string(str,B1,[](char c){return isdigit(c)?c-'0':(isupper(c)?c-'A'+10:c-'a'+36);}).to_string(B2,[](int c){return c<10?c+'0':((c-=10)<26?c+'A':c-26+'a');})<<"\n";
	return 0;
}