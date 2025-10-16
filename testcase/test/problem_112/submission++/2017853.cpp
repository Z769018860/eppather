#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 2e5 + 10;
const int M = 500;

struct node {
	int a, b, c;
	int cnt;
	int idx;
} t[N], temp[N];
int n, k;
int cnt;

int m;

bool cmp(node &a, node &b) {
	if (a.a != b.a) {
		return a.a < b.a;
	}
	if (a.b != b.b) {
		return a.b < b.b;
	}
	return a.c < b.c;
}

int pre[510][510][510];
int block[N], L[N], R[N];
int ans[N], res[N];
int x[510][510], xl[510], y[510][510], yl[510];

void calc() {
	m = (cnt - 1) / M + 1;

	for (int i = 1; i <= cnt; i++) {
		block[i] = (i - 1) / M + 1;
		if (!L[block[i]]) {
			L[block[i]] = i;
		}
		R[block[i]] = i;
	}
	for (int i = 1; i <= m; i++) {

		for (int j = L[i]; j <= R[i]; j++) {
			x[i][++xl[i]] = temp[j].b;
			y[i][++yl[i]] = temp[j].c;
		}
		sort(x[i] + 1, x[i] + xl[i] + 1);
		sort(y[i] + 1, y[i] + yl[i] + 1);
		xl[i] = unique(x[i] + 1, x[i] + 1 + xl[i]) - x[i] - 1;
		yl[i] = unique(y[i] + 1, y[i] + 1 + yl[i]) - y[i] - 1;
		for (int j = L[i]; j <= R[i]; j++) {
			int px = lower_bound(x[i] + 1, x[i] + 1 + xl[i], temp[j].b) - x[i];
			int py = lower_bound(y[i] + 1, y[i] + 1 + yl[i], temp[j].c) - y[i];
			pre[i][px][py] += temp[j].cnt;
		}
		for (int i1 = 1; i1 <= xl[i]; i1++) {
			for (int j1 = 1; j1 <= yl[i]; j1++) {
				pre[i][i1][j1] += pre[i][i1 - 1][j1] + pre[i][i1][j1 - 1] - pre[i][i1 - 1][j1 - 1];
			}
		}
	}

	for (int i = 1; i <= m; i++) {
		for (int j = L[i]; j <= R[i]; j++) {
			for (int k = 1; k < i; k++) {
				int px = lower_bound(x[k] + 1, x[k] + 1 + xl[k], temp[j].b) - x[k];
				int py = lower_bound(y[k] + 1, y[k] + 1 + yl[k], temp[j].c) - y[k];
				if (px > xl[k] || x[k][px] != temp[j].b) {
					px--;
				}
				if (py > yl[k] || y[k][py] != temp[j].c) {
					py--;
				}
				ans[j] += pre[k][px][py];
			}
			for (int k = L[i]; k <= j; k++) {
				if (temp[k].b <= temp[j].b && temp[k].c <= temp[j].c) {
					ans[j] += temp[k].cnt;
					if (k == j) {
						ans[j]--;
					}
				}
			}
		}
	}

}

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &t[i].a, &t[i].b, &t[i].c);
		t[i].idx = i;
		t[i].cnt = 1;
	}
	sort(t + 1, t + 1 + n, cmp);
	for (int i = 1; i <= n; i++) {
		int j = i;
		while (j <= n && t[i].a == t[j].a && t[i].b == t[j].b && t[i].c == t[j].c) {
			j++;
		}
		temp[++cnt] = t[i];
		temp[cnt].idx = cnt;
		temp[cnt].cnt = j - i;
		i = j - 1;
	}





	calc();

	for (int i = 1; i <= cnt; i++) {
		res[ans[i]] += temp[i].cnt;
	}

	for (int i = 0; i < n; i++) {
		printf("%d\n", res[i]);
	}
}