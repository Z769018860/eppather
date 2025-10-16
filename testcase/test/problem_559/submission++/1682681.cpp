#include<bits/stdc++.h>
#define ri register int
#define fo(i,x,y) for(ri i(x);i<=y;i=-~i)
using namespace std;
inline int reach_dest(){
	int x(0);printf("reach_dest\n");fflush(stdout);scanf("%d",&x);return x;
} 
inline int move_left(){
	int x(0);printf("move_left\n");fflush(stdout);scanf("%d",&x);return x;
} 
int n,m,l,d;
int main(){
	scanf("%d%d%d%d",&n,&m,&l,&d);
	while(!reach_dest())move_left();
	return 0;
}