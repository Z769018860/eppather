#include <cstdio>

#define LL long long
#define uLL unsigned LL

LL rint() {
	LL x = 0, Fx = 1; char c = getchar();
	while (c < '0' || c > '9') { Fx ^= (c == '-'); c = getchar(); }
	while ('0' <= c && c <= '9') { x = (x << 3) + (x << 1) + (c ^ 48); c = getchar(); }
	return Fx ? x : -x;
}

template <typename T>
void read(T &x) {
	x = rint();
}

template <typename T, typename... Ts>
void read(T &x, Ts &...rest) {
	read(x);
	read(rest...);
}

LL Max(LL u, LL v) {
	return (u > v) ? u : v;
}

LL Min(LL u, LL v) {
	return (u < v) ? u : v;
}

const int mod = 1e9 + 7;

const int mx = 1e6;

LL A, B, C, L1, R1, L2, R2;
LL X[mx + 5];

int vis[mx + 5];

int L, R;

LL cnt1[mx + 5];
LL cnt2[mx + 5];

LL sumcnt1[mx + 5];
LL sumcnt2[mx + 5];

void add(LL &x, LL y) {
	if ((x += y) >= mod)
		x -= mod;
}

LL get1(int L, int R) {
	L = Min(L, C + 1);
	R = Min(R, C);
	if (L > R) return 0;
	return (sumcnt1[R] - sumcnt1[L - 1] + mod) % mod;
}

LL get2(int L, int R) {
	L = Min(L, C + 1);
	R = Min(R, C);
	if (L > R) return 0;
	return (sumcnt2[R] - sumcnt2[L - 1] + mod) % mod;
}

bool in[mx + 5];

bool chk(LL x, LL y) {
	return (x * x + y * y + x * y - 1) / (x * y) == y / x + 2;
}

int main() {
	read(A, B, C, X[0], L1, R1, L2, R2);
	for (int i = 1; i <= C; i++)
		vis[i] = -1;
	vis[X[0]] = 0;
	for (int i = 1; i <= C; i++) {
		X[i] = (A * X[i - 1] + B) % C + 1;
		if (vis[X[i]] != -1) { L = vis[X[i]]; R = i - 1; break; }
		vis[X[i]] = i;
	}
	for (LL i = L1; i <= R1 && i < L; i++) add(cnt1[X[i]], 1);
	for (LL i = L2; i <= R2 && i < L; i++) add(cnt2[X[i]], 1);
	int tot = 0;
	for (int i = L; i <= R; i++)
		in[X[tot++] = X[i]] = true;
	if (R1 >= L) {
		L1 = Max(L1 - L, 0); R1 -= L;
		LL cnt = R1 / tot % mod;
		for (int i = 1; i <= C; i++)
			if (in[i]) add(cnt1[i], cnt);
		R1 %= tot;
		for (int i = 0; i <= R1; i++)
			add(cnt1[X[i]], 1);
		if (L1 > 0) {
			--L1; cnt = L1 / tot % mod;
			for (int i = 1; i <= C; i++)
				if (in[i]) add(cnt1[i], (mod - cnt) % mod);
			L1 %= tot;
			for (int i = 0; i <= L1; i++)
				add(cnt1[X[i]], (mod - 1) % mod);
		}
	}
	if (R2 >= L) {
		L2 = Max(L2 - L, 0); R2 -= L;
		LL cnt = R2 / tot % mod;
		for (int i = 1; i <= C; i++)
			if (in[i]) add(cnt2[i], cnt);
		R2 %= tot;
		for (int i = 0; i <= R2; i++)
			add(cnt2[X[i]], 1);
		if (L2 > 0) {
			--L2; cnt = L2 / tot % mod;
			for (int i = 1; i <= C; i++)
				if (in[i]) add(cnt2[i], (mod - cnt) % mod);
			L2 %= tot;
			for (int i = 0; i <= L2; i++)
				add(cnt2[X[i]], (mod - 1) % mod);
		}
	}
	for (int i = 1; i <= C; i++) {
		sumcnt1[i] = (sumcnt1[i - 1] + cnt1[i]) % mod;
		sumcnt2[i] = (sumcnt2[i - 1] + cnt2[i]) % mod;
	}
	LL ans = sumcnt1[C] * sumcnt2[C] * 2 % mod;
	for (int i = 1; i <= C; i++) {
		for (int j = 1; i * j <= C; j++) {
			add(ans, j * cnt1[i] % mod * get2(Max(i * j, i + 1), i * (j + 1) - 1) % mod);
			add(ans, j * cnt2[i] % mod * get1(Max(i * j, i + 1), i * (j + 1) - 1) % mod);
		}
	}
	for (int i = 1; i <= C; i++) {
		if (cnt1[i] || cnt2[i]) {
			add(ans, cnt1[i] * (mod - get2(i * 2, C)) % mod);
			add(ans, cnt2[i] * (mod - get1(i * 2, C)) % mod);
			for (int j = i * 3 - 1, k = 3, last = i - 1; j - i + 1 <= C && k <= i; j += i, k++) {
				int l = j - last, r = j;
				while (l < r) {
					int mid = (l + r) >> 1;
					LL now = ((LL)i * i + (LL)mid * mid + (LL)i * mid - 1) / ((LL)i * mid);
					if (now == mid / i + 2) r = mid;
					else l = mid + 1;
				}
				add(ans, cnt1[i] * get2(r, j) % mod);
				add(ans, cnt2[i] * get1(r, j) % mod);
				last = j - r;
			}
		}
	}
	printf("%lld\n", ans);
	return 0;
}
