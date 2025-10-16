#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=5e6+5,c=233,mod=19260817;
int n,k,ans;
ll cnt;
char s[N];
int vis[mod+5];
int main() {
	scanf("%s%d",s+1,&k);
	n=strlen(s+1);
	for (int i=1;i+k-1<=n;i++) {
		s[i]-='A';cnt=1;
		for (int j=i;j<=i+k-1;j++) {
			cnt=(cnt*c+s[j])%mod;
		}
		vis[cnt]++;
		ans=max(ans,vis[cnt]);
	}
	printf("%d\n",ans);
	return 0;
}
