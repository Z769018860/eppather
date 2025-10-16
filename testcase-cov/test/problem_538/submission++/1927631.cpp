

#include<bits/stdc++.h>
using namespace std;
#define il inline
#define mkp make_pair
#define pii pair<int,int>
#define pll pair<long long, long long>
#define fi first
#define se second
#define lll __int128
#define ll long long
#define uint unsigned int
#define ull unsigned ll
#define db double
#define ldb long double
#define sq(x) ((x)*(x))
#define pb push_back
#define eb emplace_back
#define all(x) x.begin(),x.end()
#define FileIO(filename) freopen(filename ".in" ,"r",stdin);freopen(filename ".out","w",stdout)
#define N 300010
#define int __int128
#define sz 2
#define inf 170141183460469231731687303715884105
int m,s[N],n,a0,a1,k;
map <int,int> mp;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}
signed main()
{
    m=read();
    for (int i=1;i<=m;i++)
    {
        s[i]=read();
        mp[s[i]]=1;
    }
    sort(s+1,s+m+1);
    n=read();
    for (int i=1;i<=n;i++)
    {
        a0=read();a1=read();k=read();
        if (a0==0 && a1==0)
        {
            write(s[1]);putchar(' ');
            write(s[1]);putchar('\n');
            continue;
        }
        pii mx={-inf,0},mi={inf,0};
        if (mp.find(0)!=mp.end()) mx=max((pii){a0,0},mx),mi=min((pii){a0,0},mi);
        if (mp.find(1)!=mp.end()) mx=max((pii){a1,-1},mx),mi=min((pii){a1,1},mi);
        int id=1;
        while (a0*a1<0)
        {
            int a2=k*a1+a0;
            a0=a1,a1=a2;
            id++;
            if (mp.find(id)!=mp.end()) mx=max((pii){a1,-id},mx),mi=min((pii){a1,id},mi);
        }
        if (a0<0 || a1<0)
        {
            while (a1>=mi.fi)
            {
                int a2=k*a1+a0;
                a0=a1,a1=a2;
                id++;
                if (mp.find(id)!=mp.end()) mx=max((pii){a1,-id},mx),mi=min((pii){a1,id},mi);
            }
            int p=lower_bound(s+1,s+m+1,id)-s;
            if (mx.fi==-inf) mx={0,-s[p]};
            if (p<=m) mi={0,s[m]};
        }
        else if (a0>0 || a1>0)
        {
            int p=lower_bound(s+1,s+m+1,id)-s;
            if (mi.fi==inf) mi.se=s[p];
            while (a1<=mx.fi)
            {
                int a2=k*a1+a0;
                a0=a1,a1=a2;
                id++;
                if (mp.find(id)!=mp.end()) mx=max((pii){a1,-id},mx),mi=min((pii){a1,id},mi);
            }
            p=lower_bound(s+1,s+m+1,id)-s;
            if (mi.fi==inf) mi={0,s[p]};
            if (p<=m) mx={0,-s[m]};
        }
        write(-mx.se);putchar(' ');write(mi.se);putchar('\n');
    }
    return 0;
}