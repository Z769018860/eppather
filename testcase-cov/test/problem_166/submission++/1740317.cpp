#include<cstdio>
#include<vector>
#define fo(i,x,y) for(int i = x;i <= y;++i)
#define fd(i,x,y) for(int i = x;i >= y;--i)
#define _is 1048576 * 2
#define _os 1048576 * 2
#define gc() ib[++bi]
#define pc(ch) ob[++bo] = ch
using namespace std;
char ib[_is],ob[_os];int bi = -1,bo = -1;
int rd()
{
	int x = 0;char ch = gc();
	while(ch < 48 || ch > 57) ch = gc();
	while(ch >= 48 && ch <= 57) x = x * 10 + ch - 48,ch = gc();
	return x;
}
void pr(int x)
{
	char ch[20];int w = -1;
	if(x == 0) ch[++w] = 48;
	while(x) ch[++w] = x % 10 + 48,x /= 10;
	fd(i,w,0) pc(ch[i]);pc(' ');
}

namespace Polyint{
	#define sz(x) int(x.size())
	#define add(x,y) (x >= p - y ? x + y - p : x + y)
	#define sub(x,y) (x < y ? x - y + p : x - y)
	#define p 998244353
	
	inline int ksm(int x,int y) {int res = 1;for(;y;y >>= 1,x = 1ll * x * x % p) if(y & 1) res = 1ll * res * x % p;return res;}
	vector<int> w;
	int pN = 0;
	void pre(int N,int lg)
	{
		w.resize((N >> 1) + 1);
		w[0] = 1,w[1ll << (lg - 1)] = ksm(3,(p - 1) >> (lg + 1));
		fd(i,lg - 1,1) w[1ll << (i - 1)] = 1ll * w[1ll << i] * w[1ll << i] % p;
		fo(i,1,1 << (lg - 1)) w[i] = 1ll * w[i & i - 1] * w[i & -i] % p;
	}
	struct poly
	{
		vector<int> a;

		poly() {}
		poly(int sz) {a.resize(sz);}

		int &operator [](int x) {return a[x];}
		void resize(int x) {a.resize(x);}
		void clear() {a.clear(),a.shrink_to_fit();}
		int size() {return a.size();}
		void DIF()
		{
			int N = sz(a);
			for(int l = N >> 1;l;l >>= 1) for(int i = 0,k = 0;i < N;i += l << 1,++k) fo(j,0,l - 1)
			{
				int x = a[i + j],y = 1ll * a[i + j + l] * w[k] % p;
				a[i + j] = add(x,y),a[i + j + l] = sub(x,y);
			}
		}
		void DIT()
		{
			int N = sz(a);
			for(int l = 1;l < N;l <<= 1) for(int i = 0,k = 0;i < N;i += l << 1,++k) fo(j,0,l - 1)
			{
				int x = a[i + j],y = a[i + j + l];
				a[i + j] = add(x,y),a[i + j + l] = 1ll * sub(x,y) * w[k] % p;
			}
			fo(i,1,(N - 1) >> 1) a[i] ^= a[N - i] ^= a[i] ^= a[N - i];
			int ny = ksm(N,p - 2);
			fo(i,0,N - 1) a[i] = 1ll * a[i] * ny % p;
		}
		void mul(poly &b)
		{
			poly c(b);
			int N = 1,lg = 0,n = sz(a) + sz(b);
			if(sz(a) <= 50 || sz(c) <= 50)
			{
				poly d(*this);clear(),resize(n - 1);
				fo(i,0,sz(d) - 1)
				{
					if(d.a[i] == 0) continue;
					fo(j,0,sz(c) - 1) a[i + j] = (a[i + j] + 1ll * d[i] * c[j]) % p;
				}
			}
			else
			{
				while(N < n) N <<= 1,++lg;
				if(N > pN) pre(N,lg),pN = N;
				resize(N),c.resize(N),DIF(),c.DIF();
				fo(i,0,N - 1) a[i] = 1ll * a[i] * c[i] % p;
				DIT();
			}
			a.resize(n - 1);
		}
	};
}
using namespace Polyint;
int n,m,fac[100010],ifac[100010];
int main()
{
	fread(ib,1,_is,stdin);
	n = rd(),m = rd() - n,fac[0] = 1;
	fo(i,1,n) fac[i] = 1ll * fac[i - 1] * i % p;
	ifac[n] = ksm(fac[n],p - 2);
	fd(i,n - 1,0) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % p;
	poly a(n + 1),b(n + n + 1);
	fo(i,0,n)
	{
		a[i] = 1ll * ifac[i] * rd() % p * ifac[n - i] % p;
		if(n - i & 1) a[i] = sub(0,a[i]);
	}
	fo(i,0,n + n) b[i] = ksm(i + m,p - 2);
	a.mul(b);int v = 1;
	fo(i,m,m + n) v = 1ll * v * i % p;
	fo(i,0,n) pr(1ll * a[i + n] * v % p),v = 1ll * v * (m + n + i + 1) % p * ksm(m + i,p - 2) % p;
	fwrite(ob,1,bo + 1,stdout);
}
