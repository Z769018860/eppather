#include <cstdio>
#include <iostream>
#include <unordered_map>
using namespace std;
const int N = 1e5 + 5, S = 400, M = 255;

int n, m, lstans, tot, a[N], id[N], buc[M][N << 1], lazy[M];
unordered_map<int, int> lsh;
int L(int x) {return (x - 1) * S + 1;}
int R(int x) {return min(n, x * S);}

void build(int x) {
	for (int i = L(x); i <= R(x); i++) buc[x][a[i]]++;
}
void pushdown(int x) {
	for (int i = L(x); i <= R(x); i++) buc[x][a[i]]--;
	if (!lazy[x]) return;
	for (int i = L(x); i <= R(x); i++) a[i] = lazy[x];
	lazy[x] = 0;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		id[i] = (i - 1) / S + 1;
		if (!lsh.count(a[i])) lsh[a[i]] = ++tot;
		a[i] = lsh[a[i]];
		buc[id[i]][a[i]]++;
	}
	while (m--) {
		char op;
		int l, r, k, v;
		scanf("\n%c %d %d", &op, &l, &r), l ^= lstans, r ^= lstans;
		if (op == 'M') {
			scanf("%d", &v), v ^= lstans;
			if (!lsh.count(v)) lsh[v] = ++tot;
			v = lsh[v];
			if (id[l] == id[r]) {
				pushdown(id[l]);
				for (int i = l; i <= r; i++) a[i] = v;
				build(id[l]);
				continue;
			}
			pushdown(id[l]);
			for (int i = l; i <= R(id[l]); i++) a[i] = v;
			build(id[l]);
			pushdown(id[r]);
			for (int i = L(id[r]); i <= r; i++) a[i] = v;
			build(id[r]);
			for (int i = id[l] + 1; i < id[r]; i++) lazy[i] = v;
		}
		else {
			scanf("%d %d", &k, &v), k ^= lstans, v ^= lstans;
			if (!lsh.count(v)) lsh[v] = ++tot;
			v = lsh[v];
			if (id[l] == id[r]) {
				pushdown(id[l]), build(id[l]);
				int pos = 0;
				for (int i = l; i <= r; i++)
					if (a[i] == v) {
						k--;
						if (!k) {pos = i; break;}
					}
				printf("%d\n", lstans = pos);
				continue;
			}
			pushdown(id[l]), build(id[l]);
			pushdown(id[r]), build(id[r]);
			int pos = 0;
			for (int i = l; i <= R(id[l]); i++)
				if (a[i] == v) {
					k--;
					if (!k) {pos = i; break;}
				}
			if (pos) {printf("%d\n", lstans = pos); continue;}
			for (int i = id[l] + 1; i < id[r]; i++) {
				if (lazy[i]) {
					if (lazy[i] != v) continue;
					if (k > R(i) - L(i) + 1) {k -= R(i) - L(i) + 1; continue;}
					pos = L(i) + k - 1;
					break;
				}
				if (k > buc[i][v]) {k -= buc[i][v]; continue;}
				for (int j = L(i); j <= R(i); j++)
					if (a[j] == v) {
						k--;
						if (!k) {pos = j; break;}
					}
				break;
			}
			if (pos) {printf("%d\n", lstans = pos); continue;}
			for (int i = L(id[r]); i <= r; i++)
				if (a[i] == v) {
					k--;
					if (!k) {pos = i; break;}
				}
			printf("%d\n", lstans = pos);
		}
	}
	return 0;
}