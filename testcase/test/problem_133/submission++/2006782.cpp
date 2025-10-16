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
            static int x,y,k;
            cin>>x>>y>>k,add(x,y,k);
        }
        else{
            static int l,r,u,d;
            cin>>l>>u>>r>>d;
            cout<<sum(r,d)-sum(l-1,d)-sum(r,u-1)+sum(l-1,u-1)<<'\n';
        }
    }
    return 0;
}