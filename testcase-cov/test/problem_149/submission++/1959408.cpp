
#include<algorithm>
#include<cstdio>
#include<iostream>
using namespace std;

const int N = 1e5 + 10;
const double e = 1e-15;
double a[N] , b[N] , y[N];
int n , k;

bool cmp(double a , double b){
	return a > b;
}
bool check(double x){
	for(int i = 1;i <= n;++ i){
		y[i] = a[i] - x * b[i];
	}
	double f = 0;
	sort(y + 1 , y + n + 1 , cmp);
	for(int i = 1;i <= k;++ i){
		f += y[i];
	}
	return f >= 0;
}

int main(){
	scanf("%d%d" , &n , &k);
		for(int i = 1;i <= n;++ i){
			scanf("%lf" , &a[i]);
		}
		for(int i = 1;i <= n;++ i){
			scanf("%lf" , &b[i]);
		}
		double L = 0;
		double R = 0x3f3f3f3f;
		double mid;
		while(R - L > e){
			mid = L + (R - L) / 2;
			if(check(mid)){
				L = mid;
			}
			else R = mid;
		}
		printf("%.10lf\n" , mid);
	
	return 0;
}