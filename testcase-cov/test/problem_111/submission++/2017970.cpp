#include<bits/stdc++.h>
using namespace std;
char s[1000005];
int rk[1000005],sa[1000005];
int RK[1000005],SA[1000005];
int cnt[1000005];
int main(){
	scanf("%s",s+1);
	int n=strlen(s+1);
	for(int i=1;i<=n;++i)++cnt[(int)s[i]];
	for(int i=1;i<=150;++i)cnt[i]+=cnt[i-1];
	for(int i=1;i<=n;++i)sa[cnt[(int)s[i]]--]=i;
	for(int i=1;i<=n;++i)rk[sa[i]]=rk[sa[i-1]]+(s[sa[i-1]]!=s[sa[i]]);
	for(int z=1;;z<<=1){
		for(int i=1;i<=n;++i)cnt[i]=0;
		for(int i=1;i<=n;++i)++cnt[rk[i]];
		for(int i=1;i<=n;++i)cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;--i)if(sa[i]>z)SA[cnt[rk[sa[i]-z]]--]=sa[i]-z;
		for(int i=n-z+1;i<=n;++i)SA[cnt[rk[i]]--]=i;
		for(int i=1;i<=n;++i){
			int t=SA[i],tb=SA[i-1];
			RK[SA[i]]=RK[SA[i-1]]+(rk[t]!=rk[tb]||rk[t+z]!=rk[tb+z]);
		}
		for(int i=1;i<=n;++i)sa[i]=SA[i],rk[i]=RK[i];
		if(rk[sa[n]]==n)break;
	}
	for(int i=1;i<=n;++i)printf("%d ",sa[i]);
	return 0;
}