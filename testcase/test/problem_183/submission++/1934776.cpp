# include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using vu=vector<ull>;
namespace _NTT
{
	using Poly=vector<int>;
	constexpr int L=20,N=(1<<L)+1,mod=998244353,g=3;
	int l,maxn,inv[N],rev[N],w[N];
	int power(int a,int b)
	{
		int ans=1;
		for(;b;b>>=1,a=(ll)a*a%mod)
			if(b&1) ans=(ll)ans*a%mod;
		return ans;
	}
	struct _INIT
	{
		_INIT()
		{
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
			int inv=power(maxn,mod-2);
			for(int i=0;i<maxn;i++) p[i]=a[i]%mod*inv%mod;
		}
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
	else if(L.size()<=32 || R.size()<=32)
	{
		int n=L.size(),m=R.size();
		L.resize(n+m);
		for(int i=n-1;i>=0;i--)
			for(int j=m-1;j>=0;j--)
			{
				auto t=(unsigned __int128)L[i]*R[j];
				ull x1=t,x2=t>>64;
				if(!j) L[i]=0;
				for(int k=i+j;x1;k++)
				{
					ull y=(x1>~L[k]);
					L[k]+=x1;x1=y;
				}
				for(int k=i+j+1;x2;k++)
				{
					ull y=(x2>~L[k]);
					L[k]+=x2;x2=y;
				}
			}
	}
	else
	{
		using namespace _NTT;
		static constexpr int B=16;
		static Poly F,G;
		for(ull i:L)
			for(int j=0;j<64;j+=4)
				F.push_back((i>>j)%B);
		for(ull i:R)
			for(int j=0;j<64;j+=4)
				G.push_back((i>>j)%B);
		int n=L.size()+R.size();
		init(16*n);
		NTT(F,1);NTT(G,1);
		for(int i=0;i<maxn;i++) F[i]=(ll)F[i]*G[i]%mod;
		NTT(F,0);
		for(int i=1;i<16*n;i++) F[i]+=F[i-1]/B,F[i-1]%=B;
		L.assign(n,0);
		for(int i=0;i<n;i++)
			for(int j=0;j<16;j++)
				L[i]|=(ull)F[16*i+j]<<4*j;
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
		return *this;
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
		return *this;
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
		static vu pw[20];
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
		static vu pw[20];
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
		static constexpr int B=10;
		static const Poly Base={6,1,6,1,5,5,9,0,7,3,7,0,4,4,7,6,4,4,8,1};
		static int o=1;
		static Poly pw[20];
		static vector<Poly> f;
		auto lift=[](Poly &F)
		{
			int n=F.size();
			init(2*n);NTT(F,1);
			for(int i=0;i<maxn;i++) F[i]=(ll)F[i]*F[i]%mod;
			NTT(F,0);F.resize(2*n);
			for(int i=1;i<2*n;i++) F[i]+=F[i-1]/B,F[i-1]%=B;
			while(!F.empty() && !F.back()) F.pop_back();
		};
		auto upd=[](Poly &F,Poly G,Poly H)
		{
			if(G.empty() || H.empty()) return;
			int n=G.size(),m=H.size();
			init(n+m);
			NTT(G,1);NTT(H,1);
			for(int i=0;i<maxn;i++) G[i]=(ll)G[i]*H[i]%mod;
			NTT(G,0);
			F.resize(max((int)F.size(),n+m)+1);
			for(int i=0;i<n+m;i++) F[i]+=G[i];
			n=F.size();
			for(int i=1;i<n;i++) F[i]+=F[i-1]/B,F[i-1]%=B;
			while(!F.empty() && !F.back()) F.pop_back();
		};
		int n=a.size();
		pw[0]=Base;
		for(;(1<<o)<n;o++) lift(pw[o]=pw[o-1]);
		f.resize(n);
		for(int i=0;i<n;i++)
			for(ull j=a[i];j;j/=B)
				f[i].push_back(j%B);
		for(int i=0;(1<<i)<n;i++)
		{
			int j=n-1,k=1<<(i+1);
			if((j&=~(k-1))+(1<<i)>=n) j-=k;
			for(;j>=0;j-=k) upd(f[j],f[j+(1<<i)],pw[i]);
		}
		string str;
		for(int i:f[0]) str+=i+'0';
		if(neg) str+='-';
		reverse(str.begin(),str.end());
		f.clear();
		return str;
	}
	template<typename T>
	string to_string(int B,T id)const
	{
		if(a.empty()) return "0";
		using namespace _NTT;
		static Poly pw[20];
		static vector<Poly> f;
		auto lift=[&B](Poly &F)
		{
			int n=F.size();
			init(2*n-1);NTT(F,1);
			for(int i=0;i<maxn;i++) F[i]=(ll)F[i]*F[i]%mod;
			NTT(F,0);F.resize(2*n);
			for(int i=1;i<2*n;i++) F[i]+=F[i-1]/B,F[i-1]%=B;
			while(!F.empty() && !F.back()) F.pop_back();
		};
		auto upd=[&B](Poly &F,Poly G,Poly H)
		{
			if(G.empty() || H.empty()) return;
			int n=G.size(),m=H.size();
			init(n+m-1);
			NTT(G,1);NTT(H,1);
			for(int i=0;i<maxn;i++) G[i]=(ll)G[i]*H[i]%mod;
			NTT(G,0);G.resize(n+m);
			F.resize(max((int)F.size(),n+m)+1);
			for(int i=0;i<n+m;i++) F[i]+=G[i];
			n=F.size();
			for(int i=1;i<n;i++) F[i]+=F[i-1]/B,F[i-1]%=B;
			while(!F.empty() && !F.back()) F.pop_back();
		};
		ull q=(ull)(-B)/B,r=(ull)(-B)%B;
		Poly Base={(int)r};
		for(q++;q;q/=B) Base.push_back(q%B);
		int n=a.size();
		pw[0]=Base;
		for(int i=1;(1<<i)<n;i++) lift(pw[i]=pw[i-1]);
		f.resize(n);
		for(int i=0;i<n;i++)
			for(ull j=a[i];j;j/=B)
				f[i].push_back(j%B);
		for(int i=0;(1<<i)<n;i++)
		{
			int j=n-1,k=1<<(i+1);
			if((j&=~(k-1))+(1<<i)>=n) j-=k;
			for(;j>=0;j-=k) upd(f[j],f[j+(1<<i)],pw[i]);
		}
		string str;
		for(int i:f[0]) str+=id(i);
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