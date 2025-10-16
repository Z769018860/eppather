#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

const int MAXN = 500010;
const int MOD = 232792561;
const int G = 71;

inline int read() {
	register int ret, cc;
	while (!isdigit(cc = getchar())){}ret = cc-48;
	while ( isdigit(cc = getchar())) ret = cc-48+ret*10;
	return ret;
}
inline int add(int a, int b) { return (a += b) >= MOD ? a -= MOD : a; }
inline int mul(int a, int b) { return 1ll * a * b % MOD; }
inline int qpow(int a, int p) {
	int ret = 1;
	for ( ; p; a = mul(a, a), p >>= 1)
		if (p & 1) ret = mul(ret, a);
	return ret;
}

int N, M, U;
int A[30][30];
int W[30][30];
int C[30][30];
int iC[30][30];
int P[MAXN];
long long K;
int tmp[MAXN];
int ord[MAXN];
int cnt;

inline bool Judge(int n) {
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= n; ++j)
			if (A[i][j] <= n && mul(tmp[i], tmp[j]) != tmp[A[i][j]])
				return false;
	return true;
}

void Dfs(int n) {
	if (cnt == M) return;
	if (n == M) {
		
		
		
		for (int i = 0; i < M; ++i) C[cnt][i] = tmp[i];
		cnt++;
		return;
	}
	for (int i = 0; i <= ord[n]; ++i) {
		tmp[n] = W[ord[n]][i];
		if (Judge(n)) Dfs(n+1);
		tmp[n] = 0;
	}
}

void getinv() {
	int R[30][30];
	memcpy(R, C, sizeof C);
	for (int i = 0; i < M; ++i) iC[i][i] = 1;
	for (int i = 0; i < M; ++i) {
		if (!R[i][i]) for (int j = i + 1; j < M; ++j) if (R[j][i]) {
			for (int k = 0; k < M; ++k) 
				std::swap(R[i][k], R[j][k]), std::swap(iC[i][k], iC[j][k]);
			break;
		}
		for (int j = 0; j < M; ++j) if (i != j) {
			int rate = mul(R[j][i], qpow(R[i][i], MOD-2));
			for (int k = 0; k < M; ++k) {
				R[j][k] = add(R[j][k], MOD-mul(rate, R[i][k]));
				iC[j][k] = add(iC[j][k], MOD-mul(rate, iC[i][k]));
			}
		}
	}
	for (int i = 0; i < M; ++i) {
		int inv = qpow(R[i][i], MOD-2);
		for (int j = 0; j < M; ++j)
			iC[i][j] = mul(iC[i][j], inv);
	}
}

void dft(int* a, int n, int T[30][30]) {
	for (int i = 1; i < U; i *= M) {
		for (int j = 0, p = i * M; j < U; j += p) 
			for (int k = 0; k < i; ++k)
				for (int p = 0; p < M; ++p)
					for (int q = 0; q < M; ++q)
						tmp[j+k+p*i] = add(tmp[j+k+p*i], mul(T[p][q], a[j+k+q*i]));
		for (int j = 0; j < U; ++j) a[j] = tmp[j], tmp[j] = 0;
	}
}

int main() {
#ifdef ARK
	freopen("test.in", "r", stdin);
#endif
	N = read(), M = read(), scanf("%lld", &K), U = qpow(M, N);
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < M; ++j) A[i][j] = read();
	for (int i = 0; i < U; ++i) P[i] = read();
	for (int i = 0; i < M; ++i) {
		int cur = i;
		do {
			ord[i]++;
			cur = A[cur][i];
		} while (cur != i);
	}
	for (int i = 1; i <= 22; ++i) {
		W[i][0] = 1;
		int rt = qpow(G, (MOD-1)/i);
		for (int j = 1; j < i; ++j) W[i][j] = mul(W[i][j-1], rt);
	}
	Dfs(0);
	getinv();
	dft(P, U, C);
	for (int i = 0; i < U; ++i) P[i] = qpow(P[i], (K+1) % (MOD-1));
	dft(P, U, iC);
	for (int i = 0; i < U; ++i) printf("%d\n", P[i]);
}
