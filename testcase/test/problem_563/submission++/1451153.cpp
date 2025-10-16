#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mod = 311021, mxn = 1e7+10, S = 1e7, MD = mod-1;

inline int mul(int x, int y) { return (LL)x*y%mod; }
inline int qpow(int x, int k) {
	int res = 1;
	for(; k; k >>= 1, x = mul(x, x)) if(k&1) res = mul(res, x);
	return res;
}

	
	
		
		
		
	
	
	

int phi[mxn], pr[mxn], flg[mxn], tot, low[mxn], cc[mxn], q, f[mxn], pw2[mod];
signed main() {
	pw2[0] = phi[1] = 1;
	for(int i = 2; i <= S; ++i) {
		if(!flg[i]) phi[i] = i-1, pr[++tot] = i, low[i] = i, cc[i] = 1;
		for(int j = 1; j <= tot && i*pr[j] <= S; ++j) {
			flg[pr[j]*i] = 1;
			if(i%pr[j] == 0) {
				low[i*pr[j]] = low[i]*pr[j];
				cc[i*pr[j]] = cc[i];
				phi[i*pr[j]] = phi[i/low[i]] * low[i] * (pr[j]-1);
				break;
			}
			low[i*pr[j]] = pr[j];
			phi[i*pr[j]] = phi[i] * (pr[j]-1);
			cc[i*pr[j]] = cc[i] + 1;
		}
	}
	for(int i = 1; i < mod; ++i) pw2[i] = (pw2[i-1]<<1)%mod;
	for(int i = 2; i <= S; ++i) {
		int s = 0;
		if(i&1) s = 1<<cc[i];
		else if(!(i&7)) s = 1<<(cc[i]+1);
		else if(!(i&3)) s = 1<<cc[i];
		else s = 1<<(cc[i]-1);
		
		
		
		f[i] = pw2[((phi[i] - s)>>1)%MD];
	}
	f[1] = 1;
	for(int i = 2; i <= S; ++i) (f[i] += f[i-1]) %= mod;
	scanf("%d", &q);
	while(q--) {
		int l, r; scanf("%d%d", &l, &r);
		printf("%d\n", (f[r]-f[l-1]+mod)%mod);
	}
	return 0;
}