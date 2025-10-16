#include<iostream>
#include<cstdio>
using namespace std;
#define reg register
int row[1005][1005],col[1005][1005],
	rb1[1005][1005],cb1[1005][1005],
	rb2[1005][1005],cb2[1005][1005];
int main() {
	int n,m,ans=0;
    scanf("%d%d",&n,&m);
    for (reg int i=1;i<=n;++i)
        for (reg int j=1;j<m;++j)
            scanf("%d",row[i]+j);
    for (reg int i=1;i<n;++i)
        for (reg int j=1;j<=m;++j)
            scanf("%d",col[i]+j);
    for (reg int i=1;i<=n;++i)
        for (reg int j=m-1,cnt=0;j;--j)
            if (row[i][j]) rb1[i][j]=++cnt;
            else rb1[i][j]=cnt=0;
    for (reg int i=1;i<=m;++i)
        for (reg int j=n-1,cnt=0;j;--j)
            if (col[j][i]) cb1[j][i]=++cnt;
            else cb1[j][i]=cnt=0;
    for (reg int i=1;i<=n;++i)
        for (reg int j=1,cnt=0;j<m;++j)
            if (row[i][j]) rb2[i][j+1]=++cnt;
            else rb2[i][j+1]=cnt=0;
    for (reg int i=1;i<=m;++i)
        for (reg int j=0,cnt=0;j<n;++j)
            if (col[j][i]) cb2[j+1][i]=++cnt;
            else cb2[j+1][i]=cnt=0;
	for (reg int i=1;i<n;++i)
		for (reg int j=1;j<m;++j)
			for (reg int k=min(min(cb1[i][j],rb1[i][j]),min(n-i,m-j));k;--k) {
				if (min(rb2[i+k][j+k],cb2[i+k][j+k])>=k) ++ans;
			}
	printf("%d",ans);
    return 0;
}