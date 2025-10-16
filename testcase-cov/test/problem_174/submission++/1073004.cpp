#include<bits/stdc++.h>

using namespace std;

#define rg register
#define In inline
#define ll long long
#define LL __int128
#define ld long double

const ll M1 = (5ll << 55) + 1;
const ll M2 = (7ll << 52) + 1;
const ll M3 = (119ll << 23) + 1;
const ll M4 = (479ll << 21) + 1;
const ll M5 = (7ll << 26) + 1;
const ll g1 = 6;
const ll g2 = 3;
const int W = 32000; 
const int N = 262144;

typedef vector<ll> poly;

namespace IO{
	In ll read(){
		ll s = 0,ww = 1;
		char ch = getchar();
		while(ch < '0' || ch > '9'){if(ch == '-')ww = -1;ch = getchar();}
		while('0' <= ch && ch <= '9'){s = 10 * s + ch - '0';ch = getchar();}
		return s * ww;
	}	
	In void write(ll x){
		if(x < 0)putchar('-'),x = -x;
		if(x > 9)write(x / 10);
		putchar('0' + x % 10);
	}
};
using namespace IO; 

namespace ModCalc{
	In void Adjust(ll &x,ll mod){
		x = (x % mod + mod) % mod;
	}
	In void Inc(ll &x,ll y,ll mod){
		x += y;if(x >= mod)x -= mod;
	}
	In void Dec(ll &x,ll y,ll mod){
		x -= y;if(x < 0)x += mod;
	}
	In void Tms(ll &x,ll y,ll mod){
		if(mod < M4)x = x * y % mod;
		else{
			x = x * y - (ll)((ld)x * y / mod) * mod;
			Adjust(x,mod);
		}
	}
	In void TMs(ll &x,ll y,ll mod){
		x = (LL)x * y % mod;
	}
	In ll Adj(ll x,ll mod){Adjust(x,mod);return x;}
	In ll Add(ll x,ll y,ll mod){Inc(x,y,mod);return x;}
	In ll Sub(ll x,ll y,ll mod){Dec(x,y,mod);return x;}
	In ll Mul(ll x,ll y,ll mod){Tms(x,y,mod);return x;}
};
using namespace ModCalc;

int n,m,mn,pn,pri[W+5];
bool isp[W+5];
ll Mod,M[12],P[12],V[12],jc1[N+5],iv1[N+5],jc2[N+5],iv2[N+5];
ll iv12,iv21,iv43,iv534;



In ll power(ll a,ll n,ll mod){ 
	ll s = 1,x = a;
	while(n){
		if(n & 1)Tms(s,x,mod);
		Tms(x,x,mod);
		n >>= 1;
	}
	return s;
}
void Euler(){
	for(rg int i = 2;i <= W;i++)isp[i] = 1;
	for(rg int i = 2;i <= W;i++){
		if(isp[i])pri[++pn] = i;
		for(rg int j = 1;pri[j] * i <= W;j++){
			isp[pri[j]*i] = 0;
			if(i % pri[j] == 0)break;
		}
	}
}
void divide(ll Mod){
	for(rg int i = 1;i <= pn;i++)if(Mod % pri[i] == 0){
		M[++mn] = 1;P[mn] = pri[i];V[mn] = 0;
		while(Mod % pri[i] == 0)Mod /= pri[i],M[mn] *= pri[i],V[mn]++;
	}
	if(Mod > 1)M[++mn] = Mod,P[mn] = Mod,V[mn] = 1;
}



namespace PolyCalc{
void print(poly a){
	for(rg int i = 0;i < a.size();i++)cout<<a[i]<<" ";cout<<endl;
}
	In poly Resize(poly a,int deg){a.resize(deg);return a;}
	int bit_rev[N+5];
	In poly poly1(ll a0){poly A = poly(1);A[0] = a0;return A;}
	In poly poly2(ll a0,ll a1){poly A = poly(2);A[0] = a0,A[1] = a1;return A;}
	void NTT(poly &a,int deg,int L,int opt,ll mod,ll g){
		for(rg int i = 1;i < deg;i++){
			bit_rev[i] = (bit_rev[i>>1]>>1) ^ ((i&1)<<(L-1));
			if(i < bit_rev[i])swap(a[i],a[bit_rev[i]]);
		}
		ll x = opt == 1 ? g : power(g,mod - 2,mod);
		for(rg int n = 2;n <= deg;n <<= 1){ 
			int m = n >> 1;
			ll wm = power(x,(mod-1) / n,mod);
			for(rg int i = 0;i < deg;i += n){

				LL w = 1;
				for(rg int j = 0;j < m;j++,w = w * wm % mod){

					ll v = Mul(a[i+j+m],w,mod);
					a[i+j+m] = Sub(a[i+j],v,mod);
					Inc(a[i+j],v,mod); 
				}
			}
		}
		if(opt == -1){
			ll iv = power(deg,mod - 2,mod);
			for(rg int i = 0;i < deg;i++)Tms(a[i],iv,mod);
		}
	}
	poly mul(poly a,poly b,int da,int db,ll mod,ll g){



		int deg = 1,L = 0;
		while(deg < da + db - 1)deg <<= 1,L++;
		a.resize(deg),b.resize(deg);
		NTT(a,deg,L,1,mod,g);
		NTT(b,deg,L,1,mod,g);
		for(rg int i = 0;i < deg;i++)Tms(a[i],b[i],mod);
		NTT(a,deg,L,-1,mod,g);
		a.resize(da + db - 1);
		return a;
	}
	poly mul_violent(poly A,poly B,ll M,int Dmax){
		poly C = poly(0);
		C.resize(min((int)(A.size()+B.size()-1),Dmax));
		for(rg int i = 0;i < A.size() && i < C.size();i++){
			for(rg int j = 0;j < B.size() && i + j < C.size();j++){
				Inc(C[i+j],A[i] * B[j] % M,M);
			}
		}
		return C;
	}
	poly iterate(poly A,ll d,ll M){ 
		poly B = poly2(d,1);
		poly C = poly1(A[A.size()-1]);
		for(rg int i = (int)A.size() - 2;i >= 0;i--){
			C = mul_violent(C,B,M,A.size());
			Inc(C[0],A[i],M);			
		}
		return C;
	}
};
using namespace PolyCalc;



poly Pl[20+5];
ll v[N+5],q[N+5],vq[N+5]; 

In ll id(ll mask,int p){return mask & (1ll << p);}
void Prepro(ll p,ll V,ll M){ 
	Pl[0] = poly1(1);
	for(rg int i = 1;i < p;i++)Pl[0] = mul_violent(Pl[0],poly2(i,1),M,V + 1);
	for(rg int i = 1;i <= 20;i++){
		poly Q = iterate(Pl[i-1],(p<<(i-1)) % M,M);
		Pl[i] = mul_violent(Pl[i-1],Q,M,V + 1);
	}
}



poly a,b;
ll ans[N+5],R[N+5][12];

void exgcd(ll a,ll &x,ll b,ll &y){
	if(!b){x = 1,y = 0;}
	else{
		exgcd(b,y,a % b,x);
		y -= a / b * x;
	}
}
In ll getInv(ll m,ll a){
	ll x,y;
	exgcd(a,x,m,y);
	Adjust(x,m);
	return x;
}
void Solve(int id,ll M,ll p,ll V){
	for(rg int i = 1;i <= n + m - 1;i++)v[i] = i / p + v[i/p];
	q[0] = vq[0] = 1;
	for(rg int i = 1;i <= n + m - 1;i++){
		ll cur = i;while(cur % p == 0)cur /= p;
		q[i] = q[i-1] * cur % M;
		vq[i] = getInv(M,q[i]);
	}	
	if(M > 1e8){
		ll ivp1 = power(p,M1 - 2,M1),ivp2 = power(p,M2 - 2,M2); 
		poly a1 = a,a2 = a,b1 = b,b2 = b;
		for(rg int i = 0;i < n;i++)a1[i] = a2[i] = a[i] % M * vq[i] % M;
		for(rg int i = 0;i < m;i++)b1[i] = b2[i] = b[i] % M * vq[i] % M;
		for(rg int i = 0;i < n;i++)Tms(a1[i],power(ivp1,v[i],M1),M1),Tms(a2[i],power(ivp2,v[i],M2),M2);
		for(rg int i = 0;i < m;i++)Tms(b1[i],power(ivp1,v[i],M1),M1),Tms(b2[i],power(ivp2,v[i],M2),M2);


		a1 = mul(a1,b1,n,m,M1,g1);
		a2 = mul(a2,b2,n,m,M2,g2);
		for(rg int i = 0;i < n + m - 1;i++)Tms(a1[i],power(p,v[i],M1),M1),Tms(a2[i],power(p,v[i],M2),M2);
		for(rg int i = 0;i < n + m - 1;i++){	
			ll k = Mul(Sub(a2[i],a1[i]%M2,M2),iv21,M2);
			ll x = Add(a1[i] % M,M1 % M * (k%M) % M,M); 
			R[i][id] = x * q[i] % M;
		}
	}
	else if(M > 1e4){
		ll ivp3 = power(p,M3 - 2,M3),ivp4 = power(p,M4 - 2,M4),ivp5 = power(p,M5 - 2,M5);
		poly a3 = a;for(rg int i = 0;i < n;i++)a3[i] = a3[i] % M * vq[i] % M;
		poly b3 = b;for(rg int i = 0;i < m;i++)b3[i] = b3[i] % M * vq[i] % M;
		poly a4 = a3,a5 = a3,b4 = b3,b5 = b3;
		for(rg int i = 0;i < n;i++)Tms(a3[i],power(ivp3,v[i],M3),M3),Tms(a4[i],power(ivp4,v[i],M4),M4),Tms(a5[i],power(ivp5,v[i],M5),M5);
		for(rg int i = 0;i < m;i++)Tms(b3[i],power(ivp3,v[i],M3),M3),Tms(b4[i],power(ivp4,v[i],M4),M4),Tms(b5[i],power(ivp5,v[i],M5),M5);
		a3 = mul(a3,b3,n,m,M3,g2);
		a4 = mul(a4,b4,n,m,M4,g2);
		a5 = mul(a5,b5,n,m,M5,g2);		
		for(rg int i = 0;i < n + m - 1;i++)Tms(a3[i],power(p,v[i],M3),M3),Tms(a4[i],power(p,v[i],M4),M4),Tms(a5[i],power(p,v[i],M5),M5);
		for(rg int i = 0;i < n + m - 1;i++){
			ll r3 = a3[i],r4 = a4[i],r5 = a5[i];
			ll k3 = Sub(r4,r3 % M4,M4) * iv43 % M4;
			ll r34 = r3 + k3 * M3;
			ll k34 = Sub(r5,r34 % M5,M5) * iv534 % M5;
			ll x = Add(k34 * M3 % M * M4 % M,r34 % M,M); 
			R[i][id] = x * q[i] % M;
		}
	}
	else if(M > 1e3){
		ll ivp3 = power(p,M3 - 2,M3),ivp4 = power(p,M4 - 2,M4);
		poly a3 = a;for(rg int i = 0;i < n;i++)a3[i] = a3[i] % M * vq[i] % M;
		poly b3 = b;for(rg int i = 0;i < m;i++)b3[i] = b3[i] % M * vq[i] % M;
		poly a4 = a3,b4 = b3;
		for(rg int i = 0;i < n;i++)Tms(a3[i],power(ivp3,v[i],M3),M3),Tms(a4[i],power(ivp4,v[i],M4),M4);
		for(rg int i = 0;i < m;i++)Tms(b3[i],power(ivp3,v[i],M3),M3),Tms(b4[i],power(ivp4,v[i],M4),M4);
		a3 = mul(a3,b3,n,m,M3,g2);
		a4 = mul(a4,b4,n,m,M4,g2);
		for(rg int i = 0;i < n + m - 1;i++)Tms(a3[i],power(p,v[i],M3),M3),Tms(a4[i],power(p,v[i],M4),M4);
		for(rg int i = 0;i < n + m - 1;i++){
			ll r3 = a3[i],r4 = a4[i];
			ll k3 = Sub(r4,r3 % M4,M4) * iv43 % M4;
			ll x = (r3 + k3 * M3) % M;
			R[i][id] = x * q[i] % M;
		}
	}
	else{

		ll ivp1 = power(p,M1 - 2,M1);
		poly a1 = a,b1 = b;
		for(rg int i = 0;i < n;i++)a1[i] = a[i] % M * vq[i] % M;
		for(rg int i = 0;i < m;i++)b1[i] = b[i] % M * vq[i] % M;
		for(rg int i = 0;i < n;i++)Tms(a1[i],power(ivp1,v[i],M1),M1);
		for(rg int i = 0;i < m;i++)Tms(b1[i],power(ivp1,v[i],M1),M1);

		a1 = mul(a1,b1,n,m,M1,g1);
		for(rg int i = 0;i < n + m - 1;i++){
			Tms(a1[i],power(p,v[i],M1),M1);
			R[i][id] = a1[i] % M * q[i] % M;
		}
	}
}



In void merge(ll &m1,ll &r1,ll m2,ll r2){
	ll k = Sub(r2,r1 % m2,m2) * getInv(m2,m1) % m2;
	r1 += k * m1;
	m1 *= m2;
}
void solve(){
	for(rg int i = 1;i <= mn;i++)Solve(i,M[i],P[i],V[i]);
	for(rg int i = 0;i < m + n - 1;i++){
		ll res = 0,mod = 1;
		for(rg int j = 1;j <= mn;j++)merge(mod,res,M[j],R[i][j]);
		ans[i] = res;
	}
	for(rg int i = 0;i < m + n - 1;i++){
		write(ans[i]),putchar(i == m + n - 2 ? '\n' : ' ');
	}
}

int main(){


	Euler();
	iv12 = power(M2 % M1,M1 - 2,M1);
	iv21 = power(M1 % M2,M2 - 2,M2);
	iv43 = power(M3 % M4,M4 - 2,M4);
	iv534 = power(M3 * M4 % M5,M5 - 2,M5);
	n = read() + 1,m = read() + 1,Mod = read();
	for(rg int i = 0;i < n;i++)a.push_back(read());
	for(rg int i = 0;i < m;i++)b.push_back(read());
	divide(Mod);
	solve();
	return 0;	
}