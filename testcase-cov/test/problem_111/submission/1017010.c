#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Chr(i) (cs == sizeof(int) ? ((int *)s)[i] : ((char *)s)[i])
#define isLMS(i) (i > 0 && 'S' == t[i] && 'L' == t[i-1])
#define InduceSort(s, n, K, cs, SA) \
	getBuckets(s, n, K, cs, 0);  \
	for (i = 0; i < n; i++) \
	if ((j = SA[i] - 1) >= 0 && 'L' == t[j]) SA[btk[Chr(j)]++] = j;  \
	getBuckets(s, n, K, cs, 1);  \
	for (i = n - 1; i >= 0; i--)  \
		if ((j = SA[i] - 1) >= 0 && 'S' == t[j]) SA[--btk[Chr(j)]] = j

int btk[1000020], SA[1000020];
char s[1000020];

void getBuckets(char *s, int n, int K, int cs, int end) {
	int i, sum = 0, minus = !end;
	for (i = 0; i <= K; i++) btk[i] = 0;
	for (i = 0; i < n; i++) btk[Chr(i)]++;
	for (i = 0; i <= K; i++) {
		sum += btk[i];
		btk[i] = sum - minus * btk[i];
	}
}

void SA_IS(void *s, int *SA, int n, int K, int cs) {
	char *t = (char *)malloc(sizeof(char) * n);
	int i, j;
	for (t[n-1] = 'S', i = n - 2; i >= 0; i--) {
		if (Chr(i) < Chr(i + 1)) t[i] = 'S';
		else if (Chr(i) > Chr(i + 1)) t[i] = 'L';
		else t[i] = t[i+1];
	}
	getBuckets(s, n, K, cs, 1);
	for (i = 0; i < n; i++) SA[i] = -1;
	for (i = 1; i < n; i++) if (isLMS(i)) SA[--btk[Chr(i)]] = i;
	InduceSort(s, n, K, cs, SA);
	int n1 = 0, name = 0, prev = -1, pos, diff;
	for (i = 0; i < n; i++) if (isLMS(SA[i])) SA[n1++] = SA[i];
	for (i = n1; i < n; i++) SA[i] = -1;
	for (i = 0; i < n1; i++) {
		for (j = 0, pos = SA[i], diff = 0; j < n; j++) {
			if (-1 == prev || Chr(pos + j) != Chr(prev + j) || t[pos+j] != t[prev+j]) {
				diff = 1; break;
			} else if (j > 0 && (isLMS(pos + j) || isLMS(prev + j))) break;
		}
		if (diff) { name++; prev = pos; }
		pos = (0 == pos % 2) ? (pos / 2) : (pos - 1) / 2;
		SA[n1+pos] = name - 1;
	}
	for (i = n - 1, j = n - 1; i >= n1; i--) if (SA[i] >= 0) SA[j--] = SA[i];
	int *SA1 = SA, *s1 = SA + n - n1;
	if (name < n1) SA_IS((void *)s1, SA1, n1, name - 1, sizeof(int));
	else
		for (i = 0; i < n1; i++) SA1[s1[i]] = i;
	getBuckets(s, n, K, cs, 1);
	for (i = 1, j = 0; i < n; i++) if (isLMS(i)) s1[j++] = i;
	for (i = 0; i < n1; i++) SA1[i] = s1[SA1[i]];
	for (i = n1; i < n; i++) SA[i] = -1;
	for (i = n1 - 1; i >= 0; i--) {
		j = SA[i]; SA[i] = -1;
		SA[--btk[Chr(j)]] = j;
	}
	InduceSort(s, n, K, cs, SA); free(t);
}

int main () {
	scanf("%s", s);
	int n = strlen(s);
	SA_IS((void *)s, SA, n + 1, 256, sizeof(s[0]));
	for (int i = 1; i <= n; i++) printf("%d ", SA[i] + 1);
	return 0;
}