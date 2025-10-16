#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 1000010
int sa[N], rank[N], sa2[N], cnt[N], cache[N];
char s[N];

int cmp(int *oldrk, int a, int b, int w) {  
	return oldrk[a] == oldrk[b] && oldrk[a+w] == oldrk[b+w];
}

void DA(char *s, int n, int m) {
    int i, p, w, *rk = rank, *pn = sa2, *t;
    
	for (i = 0; i < n; i++) cnt[rk[i] = s[i]]++;
	for (i = 1; i <= m; i++) cnt[i] += cnt[i-1];
	for (i = n - 1; i >= 0; i--) sa[--cnt[rk[i]]] = i;  
	
	for (p = w = 1; p < n; w *= 2, m = p) {
		for (i = 0; i <= m; i++) cnt[i] = 0;  
		
		for (p = 0, i = n - w; i < n; i++) pn[p++] = i;
		for (i = 0; i < n; i++) if (sa[i] >= w) pn[p++] = sa[i] - w;
		for (i = 0; i <= m; i++) cnt[i] = 0;  
		
		for (i = 0; i < n; i++) cnt[cache[i] = rk[pn[i]]]++;  
		for (i = 1; i <= m; i++) cnt[i] += cnt[i-1];  
		for (i = n - 1; i >= 0; i--) sa[--cnt[cache[i]]] = pn[i];
		
		for (t = pn, pn = rk, rk = t, rk[sa[0]] = 0, p = i = 1; i < n; i++) {
			rk[sa[i]] = (cmp(pn, sa[i-1], sa[i], w) ? p - 1 : p++);
		}
    }
    for (i = 0; i < n; i++) printf("%d ", sa[i] + 1);
}

int main () {
	scanf("%s", s);
	DA(s, strlen(s), 256);
	return 0;
}