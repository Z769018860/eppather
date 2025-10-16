#include<bits/stdc++.h>
using namespace std;
constexpr int lim=1000000;
int guess(int x,int i){
    static int ret;
    cout<<"guess"<<' '<<i<<' '<<x<<endl;
    cin>>ret;
    return ret;
}
void solution(int &ans){
    static int l,r,cnt=-1;
    l=0,r=lim,++cnt;
    while(l<=r){
        int mid=(l+r)/2,res=guess(mid,cnt);
        if(res<0) l=mid+1;
        else r=mid-1,ans=mid;
    }
}
int n;
int main(){
    ios::sync_with_stdio(0);
    cout<<"get_num"<<endl;
    cin>>n;
    vector<int> ans(n);
    for(auto &i:ans) solution(i);
    cout<<"submit"<<' ';
    for(auto i:ans) cout<<i<<' ';
    cout<<endl;
    return 0;
}