
#include<iostream>
#include<algorithm>
using namespace std;
const int M = 1e5 + 10 ;
const double eps=1e-15;
double a[M],b[M],y[M];
int n,k;
const int N=0x3f3f3f;
bool check(double x){
	for(int i=1;i<=n;i++){
		y[i]=a[i]-x*b[i];
	}
	double sum=0;
	sort(y+1,y+n+1,greater<double>());
	for(int i=1;i<=k;i++){
		sum+=y[i];
	}
	return sum>=0;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	double l=0,r=N,mid;
	while(r-l>eps){
		mid=l+(r-l)/2;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%.10f\n",mid);	
	return 0;
}