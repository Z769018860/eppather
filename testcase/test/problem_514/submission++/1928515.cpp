#include <bits/stdc++.h>
using namespace std;
const int N = 1e4+10;
int a[N],ans[N];
int main() {
	int n,i,T,j;
	cin>>n>>T;
	for(i=1;i<=n;i++) cin>>a[i];
	for(i=1;i<=n;i++) ans[i]=-2e9;
	for(i=1;i<=n;i++) {
		int sum=0;
		for(j=i;j<=n;j++) {
			sum+=a[j];
			ans[j-i+1]=max(ans[j-i+1],sum);
		}
	}
	for(i=n-1;i>=1;i--) ans[i]=max(ans[i],ans[i+1]);
	while(T--) {
		cin>>j;
		cout<<ans[j]<<endl;
	}
	return 0;
}