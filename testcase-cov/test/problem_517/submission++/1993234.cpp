#include<cstdio>
typedef long long ll;
int n,TAG,REV,cur,rt=1,tot=1;
int a[200005];
struct BinaryNumber {
    int size,buc[35];
    inline void add(int x) {++size; for(register int i=29;i>=0;--i) buc[i]+=(x>>i&1);}
    inline ll ask() {
        ll res=0;
        for(register int i=29;i>=0;--i) {
            if(TAG>>i&1) res+=(1ll<<i)*(size-buc[i]);
            else res+=(1ll<<i)*buc[i];
        }
        return res;
    }
    inline ll countVal(int k) {
        ll res=0;
        for(register int i=29;i>=0;--i) {
            if(TAG>>i&1) res+=(1ll<<i)*(buc[i]==0)*k;
            else res+=(1ll<<i)*(buc[i]!=0)*k;
        }
        return res;
    }
}q[200005],f[6000005];
int tr[6000005][2];
inline int read() {
    register int x=0,f=1;register char s=getchar();
    while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
    while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
    return x*f;
}
inline void swap(int &x,int &y) {int tmp=x;x=y;y=tmp;}
inline void push(int x) {a[++n]=x^TAG; q[n]=q[n-1]; q[n].add(a[n]);}
inline void TRinsert(int x) {
    int p=rt;
    for(register int i=29;i>=0;--i) {
        int dir=x>>i&1; 
        if(!tr[p][dir]) tr[p][dir]=++tot;
        p=tr[p][dir]; f[p].add(x);
    }


}
inline ll query(int R) {
    if(R>cur) return q[R].ask();
    int p=rt; ll res=0;
    for(register int i=29;i>=0;--i) {
        int ls=tr[p][0],rs=tr[p][1];
        if(REV>>i&1) swap(ls,rs);
        if(R<=f[ls].size) {p=ls;}
        else {R-=f[ls].size; res+=f[ls].ask(); p=rs;}
    }

    return res+f[p].countVal(R);
} 
signed main() {
    int N=read(); cur=0;
    for(register int i=1;i<=N;++i) push(read());
    int Q=read();
    while(Q--) {
        int op=read();
        if(op==1) {push(read());}
        else if(op==2) {
            int l=read(),r=read();
            printf("%lld\n",query(r)-query(l-1));
        }
        else if(op==3) {TAG^=read();}
        else {
            for(REV=TAG;cur<n;) TRinsert(a[++cur]);
        } 
    }
    return 0;
}