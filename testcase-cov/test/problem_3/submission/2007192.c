#include <stdio.h>
int t;
char a[1000000];
int main(){
	freopen("copycat.in", "r", stdin);
	freopen("copycat.out", "w", stdout);
	scanf("%d", &t), getchar();
	while(t = fread(a, 1, 1000000, stdin))
		fwrite(a, 1, t, stdout);
}