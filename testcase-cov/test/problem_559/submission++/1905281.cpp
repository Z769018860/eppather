#include<cstdio>
int n,m,l,d,x;
inline int reach()
{
	printf("reach_dest\n");fflush(stdout);
	scanf("%d",&x);return x;
}
inline void mvl()
{
	printf("move_left\n");fflush(stdout);
	scanf("%d",&x);return ;
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&l,&d);
	fflush(stdout);
	while(!reach())mvl();
}