#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
 
#define re register
#define ll long long
#define gc getchar()
inline int read()
{
    re int x(0),f(1);re char c(gc);
    while(c>'9'||c<'0')f=c=='-'?-1:1,c=gc;
    while(c>='0'&&c<='9')x=x*10+c-48,c=gc;
    return f*x;
}
 
const int N=505;
int f[N][N],a[N],b[N],c[N],n;
 
int main()
{
    n=read();
    int i,tot;
    for(tot=1;n;tot++)
    {
        for(i=1;i<tot&&i*(i-1)/2<=n;i++)
            f[i][tot]=1;
        n-=(i-1)*(i-2)/2;
    }
    cout<<tot<<endl;
    for(i=1;i<tot;i++)
    {
        for(int j=i+1;j<=tot;j++)
            cout<<(f[i][j]|f[j][i])<<" ";
        cout<<endl;
    }
    return 0;
}