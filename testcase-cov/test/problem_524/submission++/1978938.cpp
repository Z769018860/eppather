#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;
const int N=100005;
int w[N];
int la(int l,int r)
{
    if(r-l==1)
        return 0;
    int m=l+r>>1,s=la(l,m)+la(m,r);
    for(int i=l; i<m; ++i)
        s+=lower_bound(w+m,w+r,w[i])-w-m;
    sort(w+l,w+r);
    return s&1;
}
int main()
{
    int n;
    scanf("%d",&n);
    int t=0;
    for(int i=0; i<n; i++)
    {
        getchar();
        char c[15];
        scanf("%s",c);
        if(c[0]=='X')t++;
        else
        {
            sscanf(c,"%d",&w[i]);
        }
    }
    if(t)
    {
        if(n==1&&t==1||t%2==0)
            cout<<"L"<<endl;
        else cout<<"W"<<endl;
    }
    else
    {
        if(la(0,n))
            cout<<"W"<<endl;
        else cout<<"L"<<endl;
    }
    return 0;
}
