#include<bits/stdc++.h>
using namespace std;
int n,k,a[105000],b[105000],c[105000],d[105000],ord[105000];
int ans[105000],cnt[105000],tmp[105000],tmplen;
namespace fen {
    int len,sum[205000];
    void init() {
        len=k;
    }
    void add(int x,int y) {
        for (;x<=len;x+=(x&(-x))) sum[x]+=y;
    }
    int query(int x) {
        int res=0;
        for (;x;x-=(x&(-x))) res+=sum[x];
        return res;
    }
}
void solve(int l,int r) {
    if (l==r) return;
    int mid=(l+r)/2;
    solve(l,mid);
    solve(mid+1,r);
    int pntu=l,pntv=mid+1;tmplen=l;
    while ((pntu<=mid)||(pntv<=r)) {
        if ((pntu<=mid)&&(b[pntu]<=b[pntv])||(pntv>r)) {
            tmp[tmplen++]=pntu;
            fen::add(c[pntu],1);
            pntu++;
        } else {
            tmp[tmplen++]=pntv;
            ans[d[pntv]]+=fen::query(c[pntv]);
            pntv++;
        }
    }
    for (int i=l;i<=mid;i++) fen::add(c[i],-1);
    for (int i=l;i<=r;i++) a[i]=b[tmp[i]];
    for (int i=l;i<=r;i++) b[i]=a[i],a[i]=c[tmp[i]];
    for (int i=l;i<=r;i++) c[i]=a[i],a[i]=d[tmp[i]];
    for (int i=l;i<=r;i++) d[i]=a[i];
}
int main() {
    scanf("%d%d",&n,&k);
    for (int i=1;i<=n;i++) scanf("%d%d%d",&a[i],&b[i],&c[i]);
    for (int i=1;i<=n;i++) ord[i]=i;
    sort(ord+1,ord+1+n,[](int u,int v){return (a[u]<a[v])||(a[u]==a[v])&&(b[u]<b[v])||(a[u]==a[v])&&(b[u]==b[v])&&(c[u]<c[v]);});
    for (int i=1;i<=n;i++) d[i]=a[ord[i]];
    for (int i=1;i<=n;i++) a[i]=d[i],d[i]=b[ord[i]];
    for (int i=1;i<=n;i++) b[i]=d[i],d[i]=c[ord[i]];
    for (int i=1;i<=n;i++) c[i]=d[i],d[i]=i;
    d[0]=0;
    for (int i=n-1;i>=1;i--) {
        if ((a[i]==a[i+1])&&(b[i]==b[i+1])&&(c[i]==c[i+1])) d[0]++;
        else d[0]=0;
        ans[i]=d[0];
    }
    fen::init();
    solve(1,n);
    for (int i=1;i<=n;i++) cnt[ans[i]]++;
    for (int i=0;i<n;i++) printf("%d\n",cnt[i]);
    return 0;
}
