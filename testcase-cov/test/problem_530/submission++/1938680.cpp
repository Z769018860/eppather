#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long LL;

LL Read() {
	LL x = 0; char c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
		x = x * 10 + (c ^ 48), c = getchar();
	return x;
}

const int MAXM = 100;
const int MAXP = 600;
const LL INF = 1e18;

bool Vis[MAXP + 5];
int P[MAXM + 5], cnt;

int M;
LL E[MAXM + 5];

int main() {


	for (int i = 2; i <= MAXP; i++) {
		if (!Vis[i])
			P[++cnt] = i;
		for (int j = 1; j <= cnt && i * P[j] <= MAXP; j++) {
			Vis[i * P[j]] = true;
			if (i % P[j] == 0)
				break;
		}
	}
	int T = Read();
	while (T--) {
		M = Read();
		LL lft = 0, rgt = 1;
		for (int i = 1; i <= M; i++) {
			E[i] = Read();
			rgt = std::max(rgt, E[i] * P[i]);
		}
		while (lft + 1 < rgt) {
			LL mid = (rgt + lft) >> 1;
			bool flag = true;
			for (int i = 1; i <= M; i++) {
				LL tmp = mid, res = 0;
				while (tmp && res < E[i]) {
					res += tmp / P[i];
					tmp /= P[i];
				}
				if (res < E[i]) {
					flag = false;
					break;
				}
			}
			if (flag)
				rgt = mid;
			else
				lft = mid;
		}
		printf("%lld\n", rgt);
	}
}
