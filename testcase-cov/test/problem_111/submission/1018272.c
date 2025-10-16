#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define tget(i) ((t[(i)/8] & mask[(i)%8]) ? 1 : 0)
#define tset(i, b) t[(i)/8] = (b) ? (t[(i)/8] | mask[(i)%8]) : (t[(i)/8] & (~mask[(i)%8]))
#define Chr(i) (cs == sizeof(int) ? ((int *)s)[i] : ((char *)s)[i])
#define isLMS(i) (i > 0 && tget(i) && !tget(i-1))


#define N 1000010
unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

int btk[N], SA[N];
char s[N];

void getBuckets(void *s, int *btk, int n, int K, int cs, int end) {
    int i, sum = 0, minus = !end;
    for (i = 0; i <= K; i++) btk[i] = 0;
    for (i = 0; i < n; i++) btk[Chr(i)]++;
    for (i = 0; i <= K; i++) {
        sum += btk[i];
        btk[i] = sum - minus * btk[i];
    }
}

void InduceSort(void *s, int *btk, unsigned char *t, int n, int K, int cs, int *SA) {
	
    getBuckets(s, btk, n, K, cs, 0);  
	for (int i = 0, j; i < n; i++) {
		j = SA[i] - 1;
		if (j >= 0 && !tget(j)) SA[btk[Chr(j)]++] = j;
	}
	
	getBuckets(s, btk, n, K, cs, 1);  
	for (int i = n - 1, j; i >= 0; i--) {
		j = SA[i] - 1;
		if (j >= 0 && tget(j)) SA[--btk[Chr(j)]] = j;
	}
}

void SA_IS(void *s, int *SA, int n, int K, int cs) {
	
    unsigned char *t = (unsigned char *)malloc(n / 8 + 1);
    int i, j;
    for (tset(n - 1, 1), i = n - 2; i >= 0; i--) {
        if (Chr(i) < Chr(i + 1)) tset(i, 1);
        else if (Chr(i) > Chr(i + 1)) tset(i, 0);
        else tset(i, tget(i + 1));
    }
    
    getBuckets(s, btk, n, K, cs, 1);
    for (i = 0; i < n; i++) SA[i] = -1;
    for (i = 1; i < n; i++) if (isLMS(i)) SA[--btk[Chr(i)]] = i;
    
    InduceSort(s, btk, t, n, K, cs, SA);
    int n1 = 0, name = 0, prev = -1, pos, diff;
    
    for (i = 0; i < n; i++) if (isLMS(SA[i])) SA[n1++] = SA[i];  
    for (i = n1; i < n; i++) SA[i] = -1;
    for (i = 0; i < n1; i++) {  
        for (j = 0, pos = SA[i], diff = 0; j < n; j++) {
            if (-1 == prev || Chr(pos + j) != Chr(prev + j) || tget(pos+j) != tget(prev+j)) {
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
    else for (i = 0; i < n1; i++) SA1[s1[i]] = i;  
    
    for (i = 1, j = 0; i < n; i++) if (isLMS(i)) s1[j++] = i;  
    for (i = 0; i < n1; i++) SA1[i] = s1[SA1[i]];
    for (i = n1; i < n; i++) SA[i] = -1;
    
    getBuckets(s, btk, n, K, cs, 1);
    for (i = n1 - 1; i >= 0; i--) {  
        j = SA[i]; SA[i] = -1;
        SA[--btk[Chr(j)]] = j;
    }
    InduceSort(s, btk, t, n, K, cs, SA); free(t);
}


int main () {
    scanf("%s", s);
    int n = strlen(s);
    SA_IS((void *)s, SA, n + 1, 256, sizeof(s[0]));
    for (int i = 1; i <= n; i++) printf("%d ", SA[i] + 1);
    return 0;
}