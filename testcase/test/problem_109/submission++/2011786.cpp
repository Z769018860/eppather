
#include <iostream>
#include <cstdio>
using namespace std;
const int N=1e7;
int n,m,fa[N],x,y,s;
long long num=0ll;
int find(int x){
    if(fa[x]==x)return x;
    else return fa[x]=find(fa[x]);
}
void unionset(int x,int y){
    fa[find(x)]=find(y);
}
signed main(void){
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)fa[i]=i;
    for(int i=1;i<=m;i++){
        if(scanf("%d%d%d",&s,&x,&y)&&s){
            num=num*2;
            num+=find(x)==find(y);num%=998244353;
        }
        else{
        unionset(x,y);
        }
        }
        printf("%lld",num);
}