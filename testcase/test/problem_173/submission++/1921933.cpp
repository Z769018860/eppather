#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<int,int> PII;
const int N=1e6+5;const LL mod=998244335,base=29;
char st[N];int n;
struct Runs{int l,r,p;};vector<Runs> run;
bool cmp(Runs x,Runs y){return x.l!=y.l?x.l<y.l:x.r<y.r;}
bool operator==(Runs x,Runs y){return x.l==y.l && x.r==y.r;}
LL fc[N],ff[N];
void init(){
    fc[0]=1;
    for(int i=1;i<=n;i++)fc[i]=fc[i-1]*base%mod;
    for(int i=1;i<=n;i++)ff[i]=(ff[i-1]*base+st[i]-'A'+1)%mod;
}
LL gv(int l,int r){return ((ff[r]-ff[l-1]*fc[r-l+1])%mod+mod)%mod;}
LL gethash(int l,int r){return gv(l,r);}
int gl(int x,int y){
    int ans=0,l=1,r=min(x,y);
    while(l<=r){
        int mid=(l+r)>>1;
        if(gethash(x-mid+1,x)==gethash(y-mid+1,y))ans=mid,l=mid+1;
        else r=mid-1;
    }
    return ans;
}
int gr(int x,int y){
    int ans=0,l=1,r=min(n-x+1,n-y+1);
    while(l<=r){
        int mid=(l+r)>>1;
        if(gethash(x,x+mid-1)==gethash(y,y+mid-1))ans=mid,l=mid+1;
        else r=mid-1;
    }
    return ans;
}

bool getcmp(int x,int y){
    int len=gr(x,y);
    return st[x+len]<st[y+len];
}
int ly[N];
void lyndon(bool type){
    stack<PII> stk;stk.push({n,n});ly[n]=n;
    for(int i=n-1;i>=1;i--){
        int now=i;
        while(!stk.empty() && getcmp(i,stk.top().first)!=type)now=stk.top().second,stk.pop();
        ly[i]=now;
        stk.push({i,now});
    }
}
void getrun(){
    for(int l=1;l<=n;l++){
        int r=ly[l],ll=l,rr=r;
        if(l!=1)ll-=gl(l-1,r);
        if(r!=n)rr+=gr(l,r+1);
        if(rr-ll+1>=2*(r-l+1))run.push_back({ll,rr,r-l+1});
    }
}
int main(){
    scanf("%s",st+1);n=strlen(st+1);
    init();
    for(int op=0;op<=1;op++){
        lyndon(op);
        getrun();
    }
    sort(run.begin(),run.end(),cmp);
    run.erase(unique(run.begin(),run.end()),run.end());
    printf("%d\n",run.size());
    for(auto [l,r,p]:run)printf("%d %d %d\n",l,r,p);
    return 0;
}