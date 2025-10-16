#include<stdio.h>
long long x,n,p=998244352,i;
long long int q(long long b){
	long long m=0,ans=1;
	m=x;
	while(b){
		if(b%2==1){
			ans=(ans*m)%p;
		}
		m=(m*m)%p;
		b=b/2;
	} 
	return ans;
}
int main(){
	scanf("%lld %lld",&x,&n);
	for(i=0;i<n;i++){
		long long a;
		scanf("%lld",&a);
		printf("%lld ",q(a));
	}
	return 0;
}