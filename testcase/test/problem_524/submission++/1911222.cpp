#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
string s[200100];
int a[200100],sum,sol[200100];
struct BIT_Tree
{
    int tr[200100];
    int lowbit(int x) {return x&(-x);}
    void add(int x,int val)
    {
        for(int i=x;i<=n;i+=lowbit(i))
            tr[i]+=val;
        return ;
    }
    int ask(int x)
    {
        int res=0;
        for(int i=x;i;i-=lowbit(i))
            res+=tr[i];
        return res;	
    }
}c;

signed main()
{
    
    
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>s[i];
        if(s[i][0]=='X') sum++;
    }
    if(n==1) cout<<"L"<<endl;
    else if(sum==0)
    {
        for(int i=1;i<=n;i++)
        {
            int x=0,w=1;
            for(int j=0;j<s[i].size();j++)
            {
                if(s[i][j]=='-') {w=-1;continue;}
                x=x*10+s[i][j]-'0';
            }
            a[i]=x*w;
            
        }
        for(int i=1;i<=n;i++)
        {
            sol[i]=a[i];
        }
        sort(sol+1,sol+1+n);
        int cnt=unique(sol+1,sol+1+n)-sol-1;
        for(int i=1;i<=n;i++)
        {
            a[i]=lower_bound(sol+1,sol+1+cnt,a[i])-sol;
        }
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            ans+=(i-1-c.ask(a[i]));
            c.add(a[i],1);
        }
        if(ans%2==0) cout<<"L"<<endl;
        else cout<<"W"<<endl;
    }
    else if(sum%2==0) cout<<"L"<<endl;
    else cout<<"W"<<endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}