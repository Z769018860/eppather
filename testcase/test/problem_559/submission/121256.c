#include <stdio.h>
int n,m,l,d,v;
int reach_dest()
{
	printf("reach_dest\n");
	fflush(stdout);
	scanf("%d",&v);
	return v;
}
void move_left()
{
	printf("move_left\n");
	fflush(stdout);
	scanf("%d",&v);
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&l,&d);
	while (!reach_dest())
		move_left();
	return 0;
}