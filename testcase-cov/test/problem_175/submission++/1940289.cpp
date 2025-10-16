#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;
#define int long long
int i2,mod;
mt19937 rnd(time(NULL));
struct complex {
	int real,image;
	complex(int r = 0,int img = 0) {real = r,image = img;}
	complex operator+(complex b) {
		return complex((b.real+real)%mod,(b.image+image)%mod);	}
	complex operator*(complex b) {
		return complex((i2*b.image%mod*image+real*b.real)%mod,(image*b.real+real*b.image)%mod);
	}
	bool operator==(complex b) {
		return (real == b.real) && (image == b.image);
	}
};
complex power(complex a,int b) {
	complex ans(1,0);
	while(b) {
		if(b & 1) ans = ans*a;
		a = a*a;
		b >>= 1;
	}
	return ans;
}
int power(int a,int b) {
	int ans = 1;
	while(b) {
		if(b & 1) ans = (ans*a)%mod;
		a = (a*a)%mod;
		b >>= 1;
	}
	return ans;
}
bool issqrt(int q) {
	if(power(q,(mod-1)>>1) == 1) return true;
	else return false;
}
int ssqrt(int n) {
	if(mod == 2) {
		if(n == 1) return 1;
		else return 0;
	}
	if(n == 0) {return 1;}
	int a = rand()%mod;
	if(!issqrt(n)) {
		return -1;
	}
	while(!a || issqrt((a*a+mod-n)%mod)) {
		a = rand()%mod;
	}
	i2 = (a*a+mod-n)%mod;
	int x0 = power(complex(a,1),(mod+1)>>1).real;
	int x1 = mod-x0;
	if(x0 > x1) swap(x0,x1);
	return x0;
}
int i3;

struct ccomp {
	int a[3];
	ccomp operator+(ccomp x) {
		(x.a[0] += a[0]) %= mod;
		(x.a[1] += a[1]) %= mod;
		(x.a[2] += a[2]) %= mod;
		return x;
	}
	ccomp operator*(ccomp x) {
		ccomp ans;
		ans.a[0] = ans.a[1] = ans.a[2] = 0;
		for(int i = 0; i <= 2; i++) {
			for(int j = 0; j <= 2; j++) {
				if(i+j >= 3) (ans.a[i+j-3] += i3*a[i]%mod*x.a[j]%mod) %= mod;
				else (ans.a[i+j] += a[i]*x.a[j]%mod) %= mod;
			}
		}
		return ans;
	}
};
ccomp power(ccomp a,int b) {
	ccomp ans;
	ans.a[0] = 1,ans.a[1] = ans.a[2] = 0;
	while(b) {
		if(b & 1) ans = ans*a;
		a = a*a;
		b >>= 1;
	}
	return ans;
}
void solve() {
	int n;
	cin >> n >> mod;
	if(mod == 3) {
		cout << n << endl;
		return ;
	}
	if(mod % 3 == 2) {
		cout << power(n,(2*mod-1)/3) << endl;
		return ;
	}
	if(power(n,(mod-1)/3) != 1) {
		cout << 0 << endl;
		return ;
	}
	int inv2 = (mod+1)>>1;
	int w3 = (-1+ssqrt(-3)+mod)%mod*inv2%mod;
	
	i3 = n;
	while(true) {
		ccomp x;
		x.a[0] = rnd()%mod; x.a[1] = rnd()%mod; x.a[2] = rnd()%mod;
		x = power(x,(mod-1)/3);
		if(x.a[0] == 0 && x.a[1] != 0 && x.a[2] == 0) {
			x.a[1] = power(x.a[1],mod-2);
			x.a[0] = x.a[1]*w3%mod;
			x.a[2] = x.a[0]*w3%mod;
			sort(x.a,x.a+3);
			cout << x.a[0] << endl;
			return ;
		}
	}
}
signed main() {
	int T;
	cin >> T;
	while(T--) {
		solve();
	}
	return 0;
}