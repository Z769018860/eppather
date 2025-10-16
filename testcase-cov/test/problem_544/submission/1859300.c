#include <stdio.h>

int main(){
	int k, ki;
	scanf("%d", &k);
	ki = k + 1;
	printf("%d\n", ki);
	if (ki % 2 == 0){
		for (int i = ki / 2, j = i + 1; i >= 1 && j <= ki; i--, j++){
			printf("%d %d ", i, j);
		}
	} else {
		int x = (ki + 1) / 2;
		printf("%d ", x);
		for (int i = x - 1, j = x + 1; i >= 1 && j <= ki; i--, j++){
			printf("%d %d ", i, j);
		}
	}
	return 0;
}