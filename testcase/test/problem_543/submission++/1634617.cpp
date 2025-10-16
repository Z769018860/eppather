#include<stdio.h>
int T,n,k;
void solve(){
	scanf("%d%d",&n,&k);
	for(int i=1,x,y,z;i<=k;++i)scanf("%d%d%d",&x,&y,&z);
	if((n&1)==(k&1))puts("NO");
	else puts("YES");
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}