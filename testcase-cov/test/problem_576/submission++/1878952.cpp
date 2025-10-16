#include<bits/stdc++.h>
#define int long long 
#define ls p<<1
#define rs p<<1|1
using namespace std;
const int N=1e5+5;
int n,q,a[N];
struct SEG{
    int val[N<<2];
    void pushup(int p){
        val[p]=__gcd(val[ls],val[rs]);
    }
    void build(int p,int l,int r){
        if(l==r){
            val[p]=a[l];
            return;
        }
        int mid=l+r>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        pushup(p);
    }
    void add(int p,int l,int r,int x,int y){
        if(l==r){
            val[p]=y;
            return;
        }
        int mid=l+r>>1;
        if(x<=mid)add(ls,l,mid,x,y);
        else add(rs,mid+1,r,x,y);
        pushup(p);
    }
    int find(int p,int l,int r,int a,int b){
        if(l==r)return l;
        int mid=l+r>>1,pre=__gcd(a,val[ls]),suf=__gcd(b,val[rs]);
        if(pre<=suf)return find(ls,l,mid,a,suf);
        else return find(rs,mid+1,r,pre,b);
    }
    int query1(int p,int l,int r,int x,int y){
        if(l==r)return __gcd(val[p],y);
        int mid=l+r>>1,pre=__gcd(y,val[rs]);
        if(mid>=x)return query1(ls,l,mid,x,pre);
        else if(val[ls]%pre==0)return (mid-l+1)*pre+query1(rs,mid+1,r,x,y);
        else return query1(ls,l,mid,x,pre)+query1(rs,mid+1,r,x,y);
    }
    int query2(int p,int l,int r,int x,int y){
        if(l==r)return __gcd(val[p],y);
        int mid=l+r>>1,suf=__gcd(y,val[ls]);
        if(mid<x)return query2(rs,mid+1,r,x,suf);
        else if(val[rs]%suf==0)return (r-mid)*suf+query2(ls,l,mid,x,y);
        else return query2(ls,l,mid,x,y)+query2(rs,mid+1,r,x,suf);
    }
}tree;
signed main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i];
    tree.build(1,1,n);
    while(q--){
        int x,y;
        cin>>x>>y;
        tree.add(1,1,n,x,y);
        int p=tree.find(1,1,n,0,0);
        cout<<tree.query1(1,1,n,p,0)+tree.query2(1,1,n,p,0)-tree.val[1]<<endl;
    }
    return 0;
}
