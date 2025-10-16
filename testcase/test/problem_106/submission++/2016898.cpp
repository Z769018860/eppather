#include<bits/stdc++.h>
using namespace std;
const int m=200000050,k=100000010;
int n,q,a[105000],op,x,y,z;
namespace seg {
    int sgtcnt,sgt[30000000][3];
    void update(int p,int s,int t,int x,int y) {
        if (s==t) {
            sgt[p][2]+=y;
            return;
        }
        int mid=(s+t)/2;
        if (x<=mid) {
            if (!sgt[p][0]) sgt[p][0]=++sgtcnt;
            update(sgt[p][0],s,mid,x,y);
        } else {
            if (!sgt[p][1]) sgt[p][1]=++sgtcnt;
            update(sgt[p][1],mid+1,t,x,y);
        }
        sgt[p][2]+=y;
    }
    int query(int p,int s,int t,int l,int r) {
        if (!p) return 0;
        if ((l<=s)&&(t<=r)) return sgt[p][2];
        int mid=(s+t)/2;
        if (r<=mid) return query(sgt[p][0],s,mid,l,r);
        if (l>mid) return query(sgt[p][1],mid+1,t,l,r);
        return query(sgt[p][0],s,mid,l,r)+query(sgt[p][1],mid+1,t,l,r);
    }
}
void update(int p,int s,int t,int x,int y,int z) {
    seg::update(p,1,m,y,z);
    if (s==t) return;
    int mid=(s+t)/2;
    if (x<=mid) update(p*2,s,mid,x,y,z);
    else update(p*2+1,mid+1,t,x,y,z);
}
int query_leq(int p,int s,int t,int l,int r,int x) {
    if (x<=0) return 0;
    if (x>=m) return r-l+1;
    if ((l<=s)&&(t<=r)) return seg::query(p,1,m,1,x);
    int mid=(s+t)/2;
    if (r<=mid) return query_leq(p*2,s,mid,l,r,x);
    if (l>mid) return query_leq(p*2+1,mid+1,t,l,r,x);
    return query_leq(p*2,s,mid,l,r,x)+query_leq(p*2+1,mid+1,t,l,r,x);
}
vector<int> vect;
void getsub(int p,int s,int t,int l,int r) {
    if ((l<=s)&&(t<=r)) {
        vect.push_back(p);
        return;
    }
    int mid=(s+t)/2;
    if (l<=mid) getsub(p*2,s,mid,l,r);
    if (r>mid) getsub(p*2+1,mid+1,t,l,r);
}
int getkth(int s,int t,int k) {
    if (s==t) return s;
    int mid=(s+t)/2,cnt=0;
    for (auto cur:vect) cnt+=seg::sgt[seg::sgt[cur][0]][2];
    if (k<=cnt) {
        for (auto &cur:vect) cur=seg::sgt[cur][0];
        return getkth(s,mid,k);
    }
    for (auto &cur:vect) cur=seg::sgt[cur][1];
    return getkth(mid+1,t,k-cnt);
}
int main() {
    scanf("%d%d",&n,&q);
    seg::sgtcnt=(n<<2);
    for (int i=1;i<=n;i++) {
        scanf("%d",&a[i]);
        a[i]+=k;
    }
    for (int i=1;i<=n;i++) update(1,1,n,i,a[i],1);
    for (int i=1;i<=q;i++) {
        scanf("%d",&op);
        if (op==3) {
            scanf("%d%d",&x,&y);
            y+=k;
            update(1,1,n,x,a[x],-1);
            update(1,1,n,x,y,1);
            a[x]=y;
        }
        if (op==1) {
            scanf("%d%d%d",&x,&y,&z);
            z+=k;
            printf("%d\n",query_leq(1,1,n,x,y,z-1)+1);
        }
        if (op==2) {
            scanf("%d%d%d",&x,&y,&z);
            vect.clear();
            getsub(1,1,n,x,y);
            printf("%d\n",getkth(1,m,z)-k);
        }
        if (op==4) {
            scanf("%d%d%d",&x,&y,&z);
            z+=k;
            int tmp=query_leq(1,1,n,x,y,z-1);
            vect.clear();
            getsub(1,1,n,x,y);
            printf("%d\n",getkth(1,m,tmp)-k);
        }
        if (op==5) {
            scanf("%d%d%d",&x,&y,&z);
            z+=k;
            int tmp=query_leq(1,1,n,x,y,z)+1;
            vect.clear();
            getsub(1,1,n,x,y);
            printf("%d\n",getkth(1,m,tmp)-k);
        }
    }
    return 0;
}
