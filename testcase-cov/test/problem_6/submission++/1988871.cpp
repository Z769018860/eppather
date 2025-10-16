#include"interaction.h"
#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> vt;

int main()
{
    n=get_num();
    for(int i=0;i<n;i++)
    {
        int l=0,r=10000000;
        while(l<r)
        {
            int mid=l+r>>1;
            int ans=guess(i,mid);
            if(ans==0){l=mid;break;}
            if(ans==1)r=mid-1;
            else l=mid+1;
        }
        vt.push_back(l);
    }
    submit(vt);
    return 0;
}