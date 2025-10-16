#include<bits/stdc++.h>
using namespace std;
#define int long long

vector<int>a;
int guess(int idx,int x)
{
    cout<<"guess "<<idx<<" "<<x<<endl;
    int ret;
    cin>>ret;
    return ret;
}

signed main(void)
{
    int n;
    cout<<"get_num"<<endl;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int l=0,r=1000000,mid;
        while(l<r)
        {
            mid=(l+r)>>1;
            int y=guess(i,mid);
            if(y==0)
                break;
            else if(y==-1)
                l=mid;
            else r=mid;
        }
        a.push_back(mid);
    }
    cout<<"submit";
    for(int i=0;i<n;i++)
        cout<<" "<<a[i];
    cout<<endl;
    return 0;
}