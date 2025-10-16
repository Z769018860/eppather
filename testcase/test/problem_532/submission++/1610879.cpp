#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
#define inf 1e9
#define pii pair <int, int>
const int mod = 1e9 + 7;
int read () {
	int x = 0, f = 1;
	char ch = getchar ();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar ();
	}
	while (ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar ();
	}
	return x * f;
}
void write (int x) {
	if (x < 0) x = -x, putchar ('-');
	if (x >= 10) write (x / 10);
	putchar (x % 10 + '0');
}
int quickmod (int x, int y) {
	int Ans = 1;
	while (y) {
		if (y & 1) Ans = (Ans * x) % mod;
		x = (x * x) % mod;
		y >>= 1;
	}
	return Ans;
}
inline void Add(int &x, int y) {
	x += y;
	if(x >= mod) x -= mod;
}
int a[2000005];
map <int, int> M;
int B1[2000005], B2[2000005];
int A, B, C, L1, R1, L2, R2;
int lenl, lenr, len, bas;
void init() {
	for(int i = L1; i <= min(lenl - 1, R1); i++) B1[a[i]]++;
	L1 = max(L1, lenl);
	int ti = 0;
	while(L1 <= R1 && L1 % len != lenl % len) {
		B1[a[L1%len+bas]]++;
		L1++;
	}
	while(L1 <= R1 && R1 % len != lenr % len) {
		B1[a[R1%len+bas]]++;
		R1--;
	}
	ti = ((R1 - L1 + 1) / len) % mod;
	for(int i = lenl; i <= lenr; i++) Add(B1[a[i]], ti);

	for(int i = L2; i <= min(lenl - 1, R2); i++) B2[a[i]]++;
	L2 = max(L2, lenl);
	while(L2 <= R2 && L2 % len != lenl % len) {
		B2[a[L2%len+bas]]++;
		L2++;
	}
	while(L2 <= R2 && R2 % len != lenr % len) {
		B2[a[R2%len+bas]]++;
		R2--;
	}
	if((R2 - L2 + 1) % len) printf("??\n");
	ti = ((R2 - L2 + 1) / len) % mod;
	for(int i = lenl; i <= lenr; i++) Add(B2[a[i]], ti);

	for(int i = 1; i <= 2000000; i++) Add(B1[i], B1[i-1]), Add(B2[i], B2[i-1]);
}

signed main () {


	A = read(), B = read(), C = read(), a[0] = read();
	L1 = read(), R1 = read(), L2 = read(), R2 = read();
	for(int i = 1; i <= 2000000; i++) {
		a[i] = ((A * a[i-1] + B) % C + 1);
		if(!len && M.find(a[i]) != M.end()) {
			lenl = M[a[i]], lenr = i - 1;
			len = lenr - lenl + 1;
		}
		if(!len) M[a[i]] = i;
	}
	bas = (lenl / len + 1) * len;
	
	init();
	int Ans = 0;
	
	
	
	
	
	
	
	for(int i = 1; i <= C; i++) {
		Ans = (Ans - 2 * (B1[i] - B1[i-1]) * (B2[i] - B2[i-1]) % mod + mod) % mod;
		int L = i;
		while(L <= C) {
			int l = L, r = C, ans = l;
			while(l <= r) {
				int mid = (l + r) / 2;
				if((int)ceil(1.0 * i / mid + 1.0 * mid / i) == (int)ceil(1.0 * i / L + 1.0 * L / i)) l = mid + 1, ans = mid;
				else r = mid - 1;
			}
			Add(Ans, (int)ceil(1.0 * i / L + 1.0 * L / i) * (B1[i] - B1[i-1] + mod) % mod * (B2[ans] - B2[L-1] + mod) % mod);
			Add(Ans, (int)ceil(1.0 * i / L + 1.0 * L / i) * (B2[i] - B2[i-1] + mod) % mod * (B1[ans] - B1[L-1] + mod) % mod);
			L = ans + 1;
		}
	}
	write((Ans % mod + mod) % mod), putchar('\n');
	return 0;
}
