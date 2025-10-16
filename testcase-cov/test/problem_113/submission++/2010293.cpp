bool _Start;
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
Tp il void read(T& x) {
	x=0;bool f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}Ts il void read(T& x,_T&... y) {read(x),read(y...);}
const int N=55;
using ll=long long;
int n;
ll p[N],ans;
il void ins(ll x) {
	for(int i=50;i>=0;i--) {
		if(x>>i&1) {
			if(!p[i]) {
				p[i]=x;
				break;
			}
			x^=p[i];
		}
	}
}
bool _End;
int main() {
	fprintf(stderr,"Memory: %.4lf Mib\n",abs(&_End-&_Start)/1048576.0);
	read(n);
	for(int i=1;i<=n;i++) {
		ll x;read(x);
		ins(x);
	}
	for(int i=50;i>=0;i--) {
		ans=max(ans,ans^p[i]);
	}
	printf("%lld",ans);
	return 0;
}
