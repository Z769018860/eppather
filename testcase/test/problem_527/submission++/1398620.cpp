#include<bits/stdc++.h>
#define pw(a) (1LL<<(a))
#define L ((p)<<1)
#define R ((p)<<1|1)
#define endl '\n'
using namespace std;
 
typedef long long LL;
typedef double DD;
typedef pair<int,int> PAIR;
 
const int INF=0x3f3f3f3f;
const int mod=998244353;
const int N=1e3+10;
 
int n,m,k,t,ans,cnt,sum;
int d[N][N],r[N][N],a[N][N][2];
 
signed main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    for(int j=1;j<m;j++) cin>>r[i][j];
    for(int i=1;i<n;i++)
    for(int j=1;j<=m;j++) cin>>d[i][j];

    for(int i=1,right;i<=n;i++)
    for(int j=m;j>=1;j--)
    {
        if(not r[i][j]) right=j;
        a[i][j][0]=right;
    }
    for(int j=1,down;j<=m;j++)
    for(int i=n;i>=1;i--)
    {
        if(not d[i][j]) down=i;
        a[i][j][1]=down;
    }

    for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
    {
        int s=j+1,t=i+1;
        while(s<=a[i][j][0] and t<=a[i][j][1])
        {
            if(a[i][s][1]>=t and a[t][j][0]>=s) ans++;
            
            s++,t++;
        }
    }
    cout<<ans<<endl;
    return 0;
}