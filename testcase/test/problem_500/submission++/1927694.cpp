#include<bits/stdc++.h>
using namespace std;
const int maxn=105;
int n,m;
int a[maxn],b[maxn];
int f[maxn][maxn];
inline bool check(int mid){
	memset(f,0xcf,sizeof(f)); f[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=min(mid/b[i],m);j++){
			int x=floor(1.0*b[i]/a[i]*(1.0*mid/b[i]-1.0*j));
			for(int k=j;k<=m;k++) f[i][k]=max(f[i][k],f[i-1][k-j]+x);
		}
	}
	return f[n][m]>=m;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	int l=1,r=1e8;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}

