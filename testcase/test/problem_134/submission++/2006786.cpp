#include<bits/stdc++.h>
using namespace std;
long long c[5005][5005];
int n,m,opt;
void add(int x,int y,int k){
    for(int i=x;i<=n;i+=i&-i)
        for(int j=y;j<=m;j+=j&-j) c[i][j]+=k;
}
long long sum(int x,int y){
    long long ret=0ll;
    for(int i=x;i;i-=i&-i)
        for(int j=y;j;j-=j&-j) ret+=c[i][j];
    return ret;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    while(cin>>opt){
        if(opt==1){
            static int l,r,u,d,k;
            cin>>l>>u>>r>>d>>k;
            add(l,u,k),add(l,d+1,-k),add(r+1,u,-k),add(r+1,d+1,k);
        }
        else{
            static int x,y;
            cin>>x>>y,cout<<sum(x,y)<<'\n';
        }
    }
    return 0;
}