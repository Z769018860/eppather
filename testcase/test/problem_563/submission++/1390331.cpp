#include <bits/stdc++.h>
#define ll long long
#define mod 311021
using namespace std;
const int N = 1e7+5, limit = 1e7;
ll pw[N];
bool vis[N];
int tot, prime[N], phi[N], w[N];
ll f[N];
void init(){
	pw[0] = 1;
	for (int i = 1; i <= limit; i++)
		pw[i] = pw[i-1]*2%mod;
	phi[1] = 1;
	for (int i = 2; i <= limit; i++){
		if (!vis[i]){
			prime[++tot] = i;
			phi[i] = i-1;
			w[i] = 1;
		}
		for (int j = 1; j <= tot; j++){
			if (i*prime[j] > limit) break;
			vis[i*prime[j]] = 1;
			if (i%prime[j] == 0){
				phi[i*prime[j]] = phi[i]*prime[j];
				w[i*prime[j]] = w[i];
				break;
			}
			phi[i*prime[j]] = phi[i]*(prime[j]-1); 
			w[i*prime[j]] = w[i]+1;
		}
	}
	for (int i = 1; i <= limit; i++)
		f[i] = (f[i-1]+pw[(phi[i]-pw[w[i]-(i%2==0)+(i%4==0)+(i%8==0)])/2])%mod;
}
int T, l, r;
int main(){
	std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);


	init();
	cin >> T;
	while (T--){
		cin >> l >> r;
		cout << (f[r]-f[l-1]+mod)%mod << endl;
	}
	return 0;
}