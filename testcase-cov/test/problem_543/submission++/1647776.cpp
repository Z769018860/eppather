#include <stdio.h>

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, k;
		scanf("%d %d", &n, &k);
		for (int j = 1; j <= k; j++){
			int x, y, z;
			scanf("%d %d %d", &x, &y, &z);
		}
		if ((n - k) % 2 == 1){
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}