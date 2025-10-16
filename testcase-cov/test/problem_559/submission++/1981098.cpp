#include<cstdio>
#define flush fflush(stdout)
using namespace std;
int n,m,l,d,x;
bool reach() {
	printf("reach_dest\n");
	flush;
	scanf("%d",&x);
	return x;
}
int main() {
	scanf("%d%d%d%d",&n,&m,&l,&d);
	while(!reach()) {
		printf("move_left\n");
		flush;
		scanf("%d",&x);
	}
	return 0;
}