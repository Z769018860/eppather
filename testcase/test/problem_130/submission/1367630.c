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
	for(int i=1;i<=n;i++) {
		ll input;
		scanf("%lld",&input);
		add(array,n,i,input);
	}
	
	while(q--) {
		int option,input1,input2;
		scanf("%d%d%d",&option,&input1,&input2);
		
		if(option==1)
			add(array,n,input1,input2);
		else if(option==2)
			printf("%lld\n",getSum(array,n,input2)-getSum(array,n,input1-1));
	}
	
	return 0;
}