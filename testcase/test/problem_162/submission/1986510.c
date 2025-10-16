#include<stdio.h>
long long x,n,p=998244352,i;
long long int q(long long b){
	long long m,ans=1;
	m = x;
	while(b > 0){
		if(b%2){
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