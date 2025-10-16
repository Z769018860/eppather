#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;
string s;
int n,k,p=0;
int a[1000006],ans[1000006];
int main(){
    cin>>n>>k>>s;
    s=' '+s;
    memset(a,0,sizeof(a));
    memset(ans,0,sizeof(ans));
    for(int i=n;i>0;i--)
        if(s[i]=='*')p++;
        else a[p]++;
    for(int i=0;i<=p||a[i];i++){
        int t=(a[i]-1)/2;
        a[i]-=t*2,a[i+1]+=t;
    }
    p=k-1;
    while(n--){
        while(n>=0&&!a[n])n--;
        if(n<0)break;
        if(n>=p)ans[p--]=1;
        else{
            for(int i=0;i<=p-1;i++){
                int t=a[i]/2;
                a[i]-=t*2,a[i+1]+=t;
            }
            for(int i=0;i<=p;i++)ans[i]=a[i];
            break;
        }
    }
    p=k-1;
    while(p>=0&&!ans[p])p--;
    if(p>=0)for(int i=p;i>=0;i--)cout<<ans[i];
    else cout<<0;
    return 0;
}