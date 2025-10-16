#include<bits/stdc++.h>
#define ll long long
#define lc (p<<1)
#define rc (p<<1|1)
using namespace std;
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
char buf[1<<20],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
Tp inline void read(T& x){
    x=0;char c=getchar();bool f=0;
    for(;c<48||c>57;c=getchar())c=='-'&&(f=1);
    for(;c>47&&c<58;c=getchar())x=(x<<1)+(x<<3)+(c^48);
    f&&(x=-x);
}
Ts inline void read(T& x,_T&... y){read(x),read(y...);}
const int N=1e5+5;
const double eps=1e-8;
int n,k,a[N],b[N];
double w[N];
bool check(double mid){
	for(int i=1;i<=n;i++){
		w[i]=(double)a[i]-mid*(double)b[i];
	}
	sort(w+1,w+1+n);
	double ans=0;
	for(int i=n;i>=n-k+1;i--)ans+=w[i];
	return ans>=0;
}
int main(){
	read(n,k);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++)read(b[i]);
	double l=0,r=1;
	while(r-l>eps){
		double mid=(l+r)/2;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%.7f",l);
	return 0;
}