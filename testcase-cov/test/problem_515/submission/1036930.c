#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool ok[2][1000025];


int main(){
	int t;
	int a, b;
	register int i, j;
	int first=0, second=1;
	int ans=0;
	memset(ok, 0, sizeof(ok));
	int max=0;
	ok[first][0]=1;
	scanf("%d", &t);
	while(t--){
		scanf("%d%d", &a, &b);
		max += b * b - a * a;
		for(j = max ;j >= 0 ; j--){
			ok[second][j] = 0;
			for(i = a ; i <= b && j >= i*i-a*a ; i++){
				ok[second][j] |= ok[first][j-i*i+a*a];
				if(ok[second][j])	break;
			}
		}
		int qq=first;
		first=second;
		second=qq;
		
	}
	for(i = 0 ; i <= max ; i++){
		if(ok[first][i]) ans++;
	}
	
	printf("%d\n",ans);
	
	
	return 0;
} 