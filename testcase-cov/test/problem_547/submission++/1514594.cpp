#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int lim = (1 << 21), p = 65537;
ll n, m;
int fac[p + 5], inv[p + 5];

int ksm(int a, ll b) {
	int s = 1;
	
	for (; b; b >>= 1, a = (ll)a * a % p)
		if ( b & 1 )
			s = (ll)s * a % p;
	
	return s;
}

void init() {
	fac[0] = 1;
	
	for (int i = 1; i <= p - 1; i ++)
		fac[i] = (ll)fac[i - 1] * i % p;
	inv[p - 1] = ksm(fac[p - 1], p - 2);
	
	for (int i = p - 1; i >= 1; i --)
		inv[i - 1] = (ll)inv[i] * i % p;
}

namespace Sub1 {
	#define re register
	#define cs const
	cs int mod=65537;
	inline int add(int a,int b){a+=b-mod;return a+(a>>31&mod);}
	inline int dec(int a,int b){a-=b;return a+(a>>31&mod);}
	inline int mul(int a,int b){ll r=(ll)a*b;return r>=mod?r%mod:r;}
	inline int power(int a,int b,int res=1){
		for(;b;b>>=1,a=mul(a,a))(b&1)&&(res=mul(res,a));
		return res;
	}
	inline void Inc(int &a,int b){a+=b-mod;a+=a>>31&mod;} 
	inline void Dec(int &a,int b){a-=b;a+=a>>31&mod;}
	inline void Mul(int &a,int b){a=mul(a,b);}

	cs int bit=16,SIZE=1<<bit|1;
	
	int r[SIZE],*w[bit+1];
	inline void init_NTT(){
		for(int re i=1;i<=bit;++i)w[i]=new int[1<<i-1];
		int wn=power(3,mod-1>>bit);w[bit][0]=1;
		for(int re i=1;i<(1<<bit-1);++i)w[bit][i]=mul(w[bit][i-1],wn);
		for(int re i=bit-1;i;--i)
		for(int re j=0;j<(1<<i-1);++j)w[i][j]=w[i+1][j<<1];
	}
	inline void NTT(int *A,int len,int typ){
		for(int re i=1;i<len;++i)if(i<r[i])std::swap(A[i],A[r[i]]);
		for(int re i=1,d=1;i<len;i<<=1,++d)
		for(int re j=0;j<len;j+=i<<1)
		for(int re k=0;k<i;++k){
			int &t1=A[j+k],&t2=A[j+k+i],t=mul(t2,w[d][k]);
			t2=dec(t1,t),Inc(t1,t);
		}
		if(typ==-1){
			std::reverse(A+1,A+len);
			for(int re i=0,inv=power(len,mod-2);i<len;++i)Mul(A[i],inv);
		}
	}
	inline void init_rev(int l){
		for(int re i=1;i<l;++i)r[i]=r[i>>1]>>1|((i&1)?l>>1:0);
	}
	int l;
	inline void mul(int *a,int *b,bool mul_self){
		static int A[SIZE],B[SIZE];
		memcpy(A,a,sizeof(int)*(m+1));
		memset(A+m+1,0,sizeof(int)*(l-m-1));
		if(!mul_self){
			memcpy(B,b,sizeof(int)*(m+1));
			memset(B+m+1,0,sizeof(int)*(l-m-1));
		}
		NTT(A,l,1);
		if(!mul_self){
			NTT(B,l,1);
			for(int re i=0;i<l;++i)Mul(A[i],B[i]);
		}else for(int re i=0;i<l;++i)Mul(A[i],A[i]);
		NTT(A,l,-1);
		int sum=0;
		for(int re i=(m<<1)-1;i>=m;--i)Inc(A[i],sum),Inc(sum,A[i]);
		for(int re i=m-1;~i;--i)b[i]=add(A[i],sum),Dec(sum,A[i+m]);
	}
	
	int A[SIZE],B[SIZE],F[SIZE];
	inline void Main(){
		init_NTT();l=1;while(l<=m+m)l<<=1;init_rev(l);
		A[1]=B[0]=F[0]=1;
		for(int re i=1;i<=m;++i)F[i]=add(F[i-1],F[i-1]);
		for(;n;(n>>=1)&&(mul(A,A,true),0))
		(n&1)&&(mul(A,B,false),0);
		int ans=0;
		for(int re i=0;i<m;++i)Inc(ans,mul(B[i],F[i]));
		cout<<ans<<"\n";
	}

} 

namespace Sub2 {
	
	
	int C(int a, int b) {
		
		if ( a < b )
			return 0;
		
		return (ll)fac[a] * inv[b] % p * inv[a - b] % p;
	}
	
	int lucas(ll a, ll b) {
		
		if ( b == 0 )
			return 1;
			
		return (ll)C(a % p, b % p) * lucas(a / p, b / p) % p;
	}
	
	int calc(ll n) {
		int s = 0;
		
		for (int i = n / (m + 1); ~i; i --) {
			
			if ( i & 1 )
				s += p - (ll)ksm(2, n - (m + 1) * i) * lucas(n - i * m, i) % p;
			else
				s += (ll)ksm(2, n - (m + 1) * i) * lucas(n - i * m, i) % p;
			
			s %= p;
		}
		
		return s;
	}
	
	int Main() {
		return cout << (calc(n + 1) - calc(n) + p) % p << '\n', 0;
	}
	
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m; init(); 
	
	if ( n / (m + 1) <= lim )
		Sub2::Main();
	else 
		Sub1::Main();
	
	return 0;
}