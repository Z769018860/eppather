#include <stdio.h>
#include <stdlib.h>
int main() {
	FILE* in, * out;
	if ((in = fopen("copycat.in", "r")) == NULL) {
		printf("文件打开失败");
		exit(1);
	}
	if ((out = fopen("copycat.out", "w")) == NULL) {
		printf("文件打开失败");
		exit(1);
	}
	int t;
	char a[1000000];
	fscanf(in, "%d\n", &t),getchar();
		while (t = fread(a, 1, 1000000,in))
			
			
			fwrite(a, 1, t, out);
		
		fclose(in);
		fclose(out);
	return 0;
}