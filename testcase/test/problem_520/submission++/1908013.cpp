#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100005;
typedef long long LL;
int n,a[maxn];
LL ans;
LL sqr(LL x){ return x*x; }
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    ans+=sqr(a[1]-a[2])+sqr(a[n-1]-a[n]);
    for(int i=1;i<=n-2;i++) ans+=sqr(a[i]-a[i+2]);
    printf("%lld\n",ans);
    return 0;
} 