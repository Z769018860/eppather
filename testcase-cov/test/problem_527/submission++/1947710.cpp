#include<bits/stdc++.h>
using namespace std;
int const N=1e3+10;
int a[N][N],b[N][N],dwn[N][N],rig[N][N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    for (int i=1;i<=n;++i)
        for (int j=1;j<m;++j) cin>>a[i][j];
    for (int i=1;i<n;++i)
        for (int j=1;j<=m;++j) cin>>b[i][j];
    for (int i=1;i<=n;++i)
        for (int j=m-1;j>=1;--j)
            if (a[i][j]) rig[i][j]=rig[i][j+1]+1;
    for (int j=1;j<=m;++j)
        for (int i=n-1;i>=1;--i)
            if (b[i][j]) dwn[i][j]=dwn[i+1][j]+1;
    int ans=0;
    for (int i=1;i<=n;++i)
        for (int j=1;j<=m;++j)
            for (int k=1;k<=min(rig[i][j],dwn[i][j]);++k)
                if (rig[i+k][j]>=k && dwn[i][j+k]>=k) ++ans;
    return cout<<ans<<'\n',0;
}