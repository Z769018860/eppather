#include <stdio.h>

long long n;

long long lowbits(long long k) {
	return k&-k;
}

void Construct(long long *input,long long *array) {
	long long i;
	for(i = 1;i < n+1; i++) {
		array[i] += input[i-1];
		if(i + lowbits(i) <= n)
			array[i+lowbits(i)] += array[i];
		
	}
}

void add(long long index,long long value,long long *array) {
	long long tmp = index;
	while(tmp <= n) {
		array[tmp] += value;
		tmp += lowbits(tmp);
	}
}

long long Prefix(long long index,long long *array) {
	long long value = 0;
	while(index) {
		value += array[index];
		index -= lowbits(index);
	}
	return value;
}

long long GetSum(long long l,long long r,long long *array) {
	return Prefix(r,array) - Prefix(l-1,array);
}

int main() {
	long long m,i,flag,tmpindex,tmpl,tmpr,tmpvalue;
	long long sumvalue;
	scanf("%lld %lld",&n,&m);
	long long input[n],tarray[n+1];
	tarray[0] = -1;
	for(i = 0;i < n; i++) {
		scanf("%lld",input+i);
		tarray[i+1] = 0;
	}
	Construct(input,tarray);
	
	for(i = 0;i < m; i++) {
		scanf("%lld",&flag);
		if(flag-1) {
			
			scanf("%lld %lld",&tmpl,&tmpr);
			sumvalue = GetSum(tmpl,tmpr,tarray);
			printf("%lld\n",sumvalue);
		}
		else {
			
			scanf("%lld %lld\n",&tmpindex,&tmpvalue);
			add(tmpindex,tmpvalue,tarray);
		}
	}
	return 0;
}