#include<iostream>
#include<unordered_map>
#include<vector>
#define pb push_back
using namespace std;
unordered_map<long long,int> mp;
vector<int> g;
int ans[100010],cnt;
int main()
{
    long long k;
    cin>>k;
    for(int i=0;i<=60;i++)
    {
        mp[1LL<<i]=i;
        mp[(1LL<<i)-1]=i;
    }
    ans[++cnt]=1;
    int now=0;
    while(k%2==0)
    {
        k=k/2;
        ans[++cnt]=2;
    }
    ans[++cnt]=3;
    for(long long i=(1LL<<60)-1;i>1;i=i/2)
    {
        while(k%i==0&&i!=63)
        {
            int n=mp[i];
            while(n--)
                ans[++cnt]=now;
            now=now^1;
            k=k/i;
        }
    }
    if(k>1)
    {
        cout<<"qnq";
        return 0;
    }
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++)
        cout<<ans[i]<<" ";
}