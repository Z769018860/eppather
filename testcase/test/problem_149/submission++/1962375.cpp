
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000010;
const int inf=1e-6;
int a[N],b[N];
int n,k;
double d[N];
signed main(){
	scanf("%lld %lld",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}	
	for(int i=1;i<=n;i++){
		scanf("%lld",&b[i]);
	}
	double r=1e10,l=0;
	for(int i=1;i<=100;i++){
		double mid=l+(r-l)/2.0;
		for(int j=1;j<=n;j++){
			d[j]=(double)a[j]-b[j]*mid;
		} 
		sort(d+1,d+n+1);
		double ans=0;
		for(int j=n;j>n-k;j--) ans+=d[j];
		if(ans>-inf) l=mid+inf;
		else r=mid-inf; 
	}
	printf("%.10lf\n",l);
	return 0;
}