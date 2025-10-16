#include<stdio.h>
int n,m;
int a[1000001];
long long c[1000001];
int lowbit(int x){
	return x&(-x);
}

void add(int x,int s)
{
	while(x<=n){
		c[x]+=s;
		x+=lowbit(x);
	}
}
long long sum(int x)
{
	long long ans=0;
	while(x>0){
		ans+=c[x];
		x-=lowbit(x);
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	int i;
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		add(i,a[i]-a[i-1]);

	}
	for(i=0;i<m;i++){
		int sign;
		scanf("%d",&sign);
		if(sign==1){
			int x,y,k,j;
			scanf("%d%d%d",&x,&y,&k);
				add(x,k);
				add(y+1,-k);
		}
		else{
			int x;
			scanf("%d",&x);
			printf("%lld\n",sum(x));
		}
	}
	return 0;
}