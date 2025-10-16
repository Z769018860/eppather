#include<bits/stdc++.h>
using namespace std;
constexpr int lim=1000000;
int guess(int x,int i){
    static int ret;
    printf("guess %d %d\n",i,x);
    fflush(stdout);
    scanf("%d",&ret);
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
int main(){
    static int n;
    puts("get_num");
    fflush(stdout);
    scanf("%d",&n);
    vector<int> ans(n);
    for(auto &i:ans) solution(i);
    printf("submit");
    for(auto i:ans) printf(" %d",i);
    putchar('\n');
    fflush(stdout);
    return 0;
}