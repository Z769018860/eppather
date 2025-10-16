#include<stdio.h>
#define ll long long
#define LEN 1000005
ll array1[LEN];
ll array2[LEN];

ll lowbit(ll x) {
	return x&(-x);
}
void add(ll array[],ll length,ll index,ll num) {
	for(ll i=index;i<=length;i+=lowbit(i))
		array[i]+=num;
}
ll getSum(ll index) {
	ll ret=0;
	for(ll i=index;i>0;i-=lowbit(i))
		ret+=(index+1)*array1[i]-array2[i];
		
	return ret;
}

int main(void) {
	int n,q;
	scanf("%d%d",&n,&q);
	ll pre=0,current=0;
	for(ll i=1;i<=n;i++) {
		scanf("%lld",&current);
		add(array1,n,i,current-pre);
		add(array2,n,i,(current-pre)*i);
		pre=current;
	}
	
	while(q--) {
		int option;
		scanf("%d",&option);
		
		if(option==1) {
			ll l,r,x;
			scanf("%lld%lld%lld",&l,&r,&x);
			
			add(array1,n,l,x);
			add(array1,n,r+1,-x);
			
			add(array2,n,l,l*x);
			add(array2,n,r+1,(r+1)*(-x));
		}
		else if(option==2) {
			ll l,r;
			scanf("%lld%lld",&l,&r);
			
			printf("%lld\n",getSum(r)-getSum(l-1));
		}
	}
	
	return 0;
}