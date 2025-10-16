#include<bits/stdc++.h>
using namespace std;
#define debug cout<<endl<<"***************************"<<endl
int n,m,sum[10010],a[10010];
int main()
{
	memset(a,0xcf,sizeof a);
	cin>>n>>m;
	for(int i=1;i<=n;i++) { cin>>sum[i]; sum[i]+=sum[i-1]; }
	for(int i=1;i<=n;i++) for(int j=0;j<=n-i;j++) a[i]=max(a[i],sum[i+j]-sum[j]);
	for(int i=n-1;i>=1;i--) a[i]=max(a[i],a[i+1]);
	while(m--) {int x; cin>>x; cout<<a[x]<<endl;}
	return 0;
}
