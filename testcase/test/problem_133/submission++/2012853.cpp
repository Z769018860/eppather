#include <cstdio>
const int maxn=(1<<12)+10;
long long c[maxn][maxn];
int n,m;
void Modify(int x,int y,int val){
	while(x<=n){
		int ty=y;
		while(ty<=m){
			c[x][ty]+=val;
			ty+=ty&(-ty);
		}
		x+=x&(-x);
	}
}
long long s(int x,int y){
	long long ans=0;
	while(x){
		int ty=y;
		while(ty){
			ans+=c[x][ty];
			ty-=ty&(-ty);
		}
		x-=x&(-x);
	}
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);
	int opt;
	while(~scanf("%d",&opt)){
		if(opt==1){
			int x,y,k;
			scanf("%d%d%d",&x,&y,&k);
			Modify(x,y,k);
		}
		else{
			int a,b,c,d;
			scanf("%d%d%d%d",&a,&b,&c,&d);
			printf("%lld\n",s(c,d)-s(c,b-1)-s(a-1,d)+s(a-1,b-1));
		}
	}
	return 0;
}