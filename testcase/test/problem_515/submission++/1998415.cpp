#include <iostream>
#include <cstdio>
using namespace std;
const int N=101;
const int W=64;
struct Bitset{
	unsigned long long a[N*N*N>>6];
	void shiftor(const Bitset& y,int p,int l,int r){
		int t=p-p/W*W;
		int tt=(t==0?0:W-t);
		int to=(r+p)/W;
		int qaq=(p+W-1)/W;
		for (register int i=(l+p)/W;i<=to;++i){
			if (i-qaq>=0) a[i]|=y.a[i-qaq]>>tt;
			a[i]|=((y.a[i-qaq+1]&((1ull<<tt)-1))<<t);
		}
	}
} f[N];
int main(){
	int n,a,b,l=0,r=0,ans=0;
	scanf("%d",&n);
	f[0].a[0]=1;
	for (register int i=1;i<=n;++i){
		scanf("%d%d",&a,&b);
		for (register int j=a;j<=b;++j) f[i].shiftor(f[i-1],j*j,l,r);
		l+=a*a;
		r+=b*b;
	}
	for (register int i=l/W;i<=r/W;++i) ans+=__builtin_popcount(f[n].a[i]&0xffffffffu)+__builtin_popcount(f[n].a[i]>>32);
	printf("%d",ans);
	return 0;
}