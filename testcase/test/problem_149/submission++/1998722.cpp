#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const double eps=1e-6;
int n,k;
double a[N],b[N],c[N];
bool check(double L)
{
    for(int i=1;i<=n;i++) c[i]=a[i]-L*b[i];
    sort(c+1,c+1+n);
    double ans=0;
    for(int i=n;i>=n-k+1;i--) ans+=c[i];
    return ans>=0;
}
int main()
{
    scanf("%d%d", &n, &k); 
    for(int i=1;i<=n;i++) scanf("%lf",&a[i]);
    for(int i=1;i<=n;i++) scanf("%lf",&b[i]);
    double l=0, r=1,mid;
    while(fabs(r-l)>eps)
    {
        mid =(l+r)/2;
        if(check(mid)) l=mid;
        else           r=mid;
    }
    printf("%lf\n", l  ) ;
    return 0;
}