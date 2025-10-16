#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

int n,m,q,top;
struct Node
{
    int x,k;
} st[Maxn+5];
inline Node operator+(Node a,Node b)
{
    Node c; c.x=a.x|b.x,c.k=a.k+b.k;
    Rof(i,30,0) if(a.x&(1<<i) && b.x&(1<<i))
        {c.x|=(1<<i)-1; break;} return c;
}
inline bool operator<(Node a,Node b)
{return a.k<b.k || (a.k==b.k && a.x>b.x);}

signed main()
{
    

    cin>>n>>m; st[top=1]=Node{0ll,0ll};
    For(i,1,n)
    {
        int x,k; cin>>k>>x; Node res=Node{x,k};
        For(j,1,top) st[top+j]=st[j]+res; top*=2;
        sort(st+1,st+top+1); int cnt=1;
        For(j,2,top) if(st[j].x>st[cnt].x)
            st[++cnt]=st[j]; top=cnt;
    } cin>>q;
    while(q--)
    {
        int x,ans=-1; cin>>x;
        For(i,1,top) if(st[i].x>=x) {ans=st[i].k; break;}
        printf("%lld\n",ans);
    }
    return 0;
}