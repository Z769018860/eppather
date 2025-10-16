#include<stdio.h>

typedef long long ll;
ll tree[1000010];
int s[1000010],n,q;

int move(int i){
	return i&(-i);
}
void adds(int i,int x){
	while(i<=n){
		tree[i]+=x;
		i+=move(i);
	}
}
ll sum(int x){
	ll sums=0;
	while(x>0){
		sums+=tree[x];
		x-=move(x);
	}
	return sums;
}
int main(){
	int i,j,a,b,c;
	scanf("%d%d",&n,&q);
	for(i=1;i<=n;i++)
		scanf("%d",&s[i]);
	for(i=1;i<=n;i++){
		adds(i,s[i]);
	}
	for(j=0;j<q;j++){
		scanf("%d%d%d",&a,&b,&c);
		if(a==1)adds(b,c);
		else printf("%lld\n",sum(c)-sum(b-1));
	}
	return 0;
}

