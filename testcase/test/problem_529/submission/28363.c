#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXN 1000100
int main(void) {
	int T, n, a, b, i;
	static char s[MAXN];
	scanf("%d\n", &T);
	while(T--) {
		a = 0, b = 0;
		n = strlen(fgets(s, MAXN, stdin));
		if(s[n - 1] == '\n') s[--n] = '\0';
		for(i = 0; i < n; i++)
			if(s[i] == 'N') a = b = 1;
		for(i = 0; i < n - 1; i++)
			if(s[i] == 'N' && s[i + 1] == 'N') a = b = 0;
		if(s[0] == 'V') b = 0;
		printf("%d %d\n", a, b);
	}
	return 0;
}