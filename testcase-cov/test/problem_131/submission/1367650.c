#include<stdio.h>
#define ll long long
#define LEN 1000005
ll array[LEN];

int lowbit(int x) {
	return x&(-x);
}
void add(ll array[],int length,int index,ll num) {
	for(int i=index;i<=length;i+=lowbit(i))
		array[i]+=num;
}
ll getSum(ll array[],int length,int index) {
	ll ret=0;
	for(int i=index;i>0;i-=lowbit(i))
		ret+=array[i];
		
	return ret;
}

int main(void) {
	int n,q;
	scanf("%d%d",&n,&q);
	ll pre=0,current=0;
	for(int i=1;i<=n;i++) {
		scanf("%lld",&current);
		add(array,n,i,current-pre);
		pre=current;
	}
	
	while(q--) {
		int option;
		scanf("%d",&option);
		
		if(option==1) {
			int l,r,x;
			scanf("%d%d%d",&l,&r,&x);
			
			add(array,n,l,x);
			add(array,n,r+1,-x);
		}
		else if(option==2) {
			int i;
			scanf("%d",&i);
			
			printf("%lld\n",getSum(array,n,i));
		}
	}
	
	return 0;
}