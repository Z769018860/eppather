#include<cstdio>
#define N 1001
using namespace std;
int n,m;
int trans[N][N],erect[N][N];
int left[N][N],up[N][N];
void init()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<m;j++)
            scanf("%d",&up[i][j]);
    for(int i=1;i<n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&left[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=m-2;j;j--)
            if(up[i][j]) up[i][j]+=up[i][j+1];
    for(int j=1;j<=m;j++)
        for(int i=n-2;i;i--)
            if(left[i][j]) left[i][j]+=left[i+1][j];
}
void solve()
{
    int k,ans=0;
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++)
            if(up[i][j] && left[i][j])
            {
                k=1;
                while(up[i][j]>=k && left[i][j]>=k )
                {
                    if(up[i+k][j]>=k && left[i][j+k]>=k) ans++;
                    k++;
                }
            }
    printf("%d",ans);
}
int main()
{
    init();
    solve();
}