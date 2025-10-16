#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=5e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,cnt[Maxn+5],vis[Maxn+5],chk[Maxn+5];
vector<int> v[Maxn+5];
priority_queue<int,vector<int>,greater<int>> q;
vector<int> ans;

inline void Add(int x)
{
    chk[x]=1;
    for(auto y:v[x]) if(!vis[y] && --cnt[y]<=1) q.push(y);
}

int main()
{
    

    n=read();
    if(n==1) {puts("-1"); return 0;}
    For(i,1,n-1)
    {
        int a=read(),b=read();
        v[a].push_back(b),v[b].push_back(a);
    }
    For(i,1,n) cnt[i]=v[i].size();
    For(i,1,n) if(cnt[i]<=1) q.push(i);
    while(!q.empty())
    {
        int x=q.top(); q.pop();
        if(vis[x]) continue; vis[x]=1;
        ans.push_back(x);
        for(auto y:v[x]) if(!chk[y]) Add(y);
    }
    if(ans.size()<n) puts("-1");
    else {for(auto i:ans) printf("%d ",i); printf("\n");}
    return 0;
}