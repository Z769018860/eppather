
#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;
struct Node{
    int data,num;
    bool operator <(const Node tt) const {
        if(data!=tt.data)return data>tt.data;
        return num>tt.num;
    }
}a[100005];
priority_queue<Node>q[100005];
int n,m,prt[100005],del[100005];
int GetFa(int x){
    return x==prt[x]?x:prt[x]=GetFa(prt[x]);
}
void Merge(int x,int y){
    if(del[x]||del[y])return ;
    x=GetFa(x);
    y=GetFa(y);
    if(x==y)return ;
    if(q[x].size()>q[y].size())swap(x,y);
    prt[x]=y;
    while(q[x].size()){
        q[y].push(q[x].top());
        q[x].pop();
    }
}
int DeleteMin(int x){
    x=GetFa(x);
    Node t=q[x].top();
    q[x].pop();
    del[t.num]=1;
    return t.data;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i].data);
        prt[i]=i;
        a[i].num=i;
        q[i].push(a[i]);
    }
    for(int i=1;i<=m;i++){
        int opt,x,y;
        scanf("%d%d",&opt,&x);
        if(opt==1){
            scanf("%d",&y);
            Merge(x,y);
        }
        else {
            if(del[x])puts("-1");
            else printf("%d\n",DeleteMin(x));
        }
    }
    return 0;
}