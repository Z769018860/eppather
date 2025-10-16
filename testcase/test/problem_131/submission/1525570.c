#include <stdio.h>

int n;

int lowbits(int x) {
	return x & -x;
}

void ConstructDiff(long long *input,long long *Diff0) {
	int i;
	long long tmpvalue;
	Diff0[1] = input[0];
	Diff0[2] += Diff0[1];
	for(i = 2;i < n+1; i++) {
		tmpvalue = input[i-1] - input[i-2];
		Diff0[i] += tmpvalue;
		if(i + lowbits(i) <= n) {
			
			Diff0[i + lowbits(i)] += Diff0[i];
		}
	}
	return;
}

void add(int index,int value,long long *array) {
	int tmp = index;
	while(tmp <= n) {
		array[tmp] += value;
		tmp += lowbits(tmp);
	}
}

void SectionAdd(int l,int r,int value,long long *array) {
	add(l,value,array);
	add(r+1,-value,array);
}

long long Prefix(int index,long long *array) {
	int tmp = index;
	long long value = 0;
	while(tmp) {
		value += array[tmp];
		tmp -= lowbits(tmp);
	}
	return value;
}

int main() {
	int m,i,flag,tmpl,tmpr,tmpindex,tmpadd;
	long long value;
	scanf("%d %d",&n,&m);
	long long input[n],Diff0[n+1];
	
	Diff0[0] = 0;
	for(i = 0;i < n; i++) {
		scanf("%lld",input+i);
		Diff0[i+1] = 0;
	}
	
	

	ConstructDiff(input,Diff0);

	for(i = 0;i < m; i++) {
		scanf("%d",&flag);
		if(flag-1) {
			scanf("%d",&tmpindex);
			value = Prefix(tmpindex,Diff0);
			printf("%lld\n",value);
		}
		else {
			scanf("%d %d %d",&tmpl,&tmpr,&tmpadd);
			SectionAdd(tmpl,tmpr,tmpadd,Diff0);
		}
	}
	return 0;
}