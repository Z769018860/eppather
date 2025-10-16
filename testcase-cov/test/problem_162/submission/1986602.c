#include<stdio.h>
long long int x,n,p=998244352,i;
long long int q(long long int b){
	long long int m=0,t=1;
	m=x;
	while(b){
		if(b%2==1){
			t=(t*m)%p;
		}
		m=(m*m)%p;
		b=b/2;
	} 
	return t;
}
int main(){
	scanf("%lld %lld",&x,&n);
	for(i=0;i<n;i++){
		long long int a;
		scanf("%lld",&a);
		printf("%lld ",q(a));
	}
	return 0;
}