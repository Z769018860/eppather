#include <stdio.h>
long long m1,m,sum;
int n1,n;
#define P 998244352
int main(){
	scanf("%lld%d",&m,&n);
	m1 = m;
	while(n){
		scanf("%d",&n1);
		sum =1;
	    m = m1;
	    m=m%P;
	    while(n1){
	     if(n1&1)sum =(sum *m)%P;
	     m = m*m%P;
	     n1>>=1;
}
		if(n==1) printf("%lld",sum);
		else printf("%lld ",sum);
		n--;
	}
	return 0;
}