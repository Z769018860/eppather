#include <bits/stdc++.h>
using namespace std;
const int maxn=2000010,mod=998244353;
int T,m,a,b,c,d,anss;
int it,dc,as,q[maxn],del[maxn];
bitset<maxn>v,cur;
unsigned seed;
inline unsigned Rand() {
    return seed^=seed<<13,seed^=seed>>17,seed^=seed<<5,seed;
}
void solve() {
    int ans=0,head,tail;
    cin>>m>>seed>>a>>b>>c>>d;
    head=tail=dc=as=anss=0,it=a+1;
    for(int i=0; i<=b; i++) v[i]=cur[i]=i<=a;
    for(int i=1,x; i<=m; ++i) {
        if(Rand()%c==0) x=-1;
        else x=Rand()%b;
        if(x==-1) {
            if(d||as>=dc) continue;
            if(head<tail&&q[head]==del[as]) ++head;
            cur[del[as++]]=1;
        }
        else if(!v[x])
            for(v[x]=cur[x]=1; v[it]; ++it);
        else if(cur[x]) {
            if(d) continue;
            for(cur[x]=0; head<tail&&q[tail-1]>x; tail--);
            q[tail++]=del[dc++]=x;
        }
        else if(as<dc) {
            if(d) continue;
            if(head<tail&&q[head]==del[as]) ++head;
            cur[del[as++]]=1;
        }
        else continue;
        anss^=1ll*i*(i+7)%mod*min(it,(int)(head<tail?q[head]:1e9))%mod;
    }
    cout<<anss<<'\n';
}
int main() {
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--) solve();
    return 0;
}