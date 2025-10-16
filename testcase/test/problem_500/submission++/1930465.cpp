
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long LL;
int n,m;
int a[101],b[101];
LL f[101][101];
bool check(const int x){
	memset(f,0xcf,sizeof f);
	f[0][0]=0;
	for(int i=1;i<=n;i++)for(int j=0;j<=m;j++)for(int k=std::max(0,j-x/a[i]);k<=j;k++)
		f[i][j]=std::max(f[i][j],f[i-1][k]+(x+(LL)a[i]*(k-j))/b[i]);
	return f[n][m]>=m;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	int l=0,r=100000000;
	for(int mid;l<r;){

		if(check(mid=(l+r)>>1)) r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}
