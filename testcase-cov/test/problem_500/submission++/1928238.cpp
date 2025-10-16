#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)){ if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)){ x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); }
	return x*f;
}
int n,m,f[105][105],a[105],b[105];
inline bool cheak(int x){
	memset(f,128,sizeof(f));
	f[0][0]=0;
	for (int i=1;i<=n;i++)
	for (int j=0;j<=m;j++)
	for (int k=0;k<=j;k++)
		if (j-k<=x/a[i])
			f[i][j]=max(f[i][j],f[i-1][k]+(x-a[i]*j+a[i]*k)/b[i]);
	return f[n][m]>=m;
}
signed main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++) a[i]=read(),b[i]=read();
	int l=1,r=1e8,res;
	while (l<=r){
		int mid=(l+r)>>1;
		if (cheak(mid)) r=mid-1,res=mid;
		else l=mid+1;
	} printf("%lld",res);
	return 0;
}
