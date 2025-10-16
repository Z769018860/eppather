#include <bits/stdc++.h>
using namespace std;
int p,q,n,ans;
int gcd (int a,int b) {return (b==0?a:gcd(b,a%b));}
int main () {
	scanf("%d%d%d",&p,&q,&n);
	ans=1;
	for (int i=2;i*i<=n;i++) {
		if (n%i==0) {
			int cnt=0,prod=1,tmp=0;
			while (n%i==0) {cnt++,prod*=i,n/=i;}
			for (int j=0;j<=cnt&&prod>1;j++) {
				if (i!=2) {tmp+=(prod-prod/i)/gcd(prod-prod/i,p);}
				else {
					if (p&1) {tmp+=prod/2;}
					else {tmp+=(prod==2?1:(prod/4)/gcd(prod/4,p));}
				}
				for (int k=1;k<=p&&prod;k++) {prod/=i;}
			}
			tmp++;
			ans*=tmp;
		}
	}
	if (n>1) {
		int cnt=1,prod=n,tmp=0;
		for (int j=0;j<=cnt&&prod>1;j++) {
			tmp+=(prod-prod/n)/gcd(prod-prod/n,p);
			for (int k=1;k<=p&&prod;k++) {prod/=n;}
		}
		tmp++;
		ans*=tmp;
	}
	printf("%d\n",ans);
	return 0;
}