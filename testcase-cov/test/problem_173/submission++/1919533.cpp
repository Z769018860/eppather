#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> PII;
const int N=1e6+5;
int n;
struct Runs{
    int l,r,p;
};vector<Runs> run;
bool cmp(Runs x,Runs y){return x.l!=y.l?x.l<y.l:x.r<y.r;}
bool operator==(Runs x,Runs y){return x.l==y.l && x.r==y.r;}
struct SA{
    char ss[N];
    int cc[N],sa[N],xx[N],yy[N],top,V;
    int rk[N],height[N],h[N],rmq[20][N];
    int getlcp(int x,int y){
        x=rk[x];y=rk[y];
        if(x>y)swap(x,y);
        x++;int k=__lg(y-x+1);
        return min(rmq[k][x],rmq[k][y-(1<<k)+1]);
    }
    int getcmp(int x,int y){
        int t=getlcp(x,y);
        return ss[x+t]<ss[y+t];
    }
    void getsa(){
        V=256;memset(cc+1,0,V<<2);
        for(int i=1;i<=n;i++)cc[xx[i]=ss[i]]++;
        for(int i=1;i<=V;i++)cc[i]+=cc[i-1];
        for(int i=n;i>=1;i--)sa[cc[xx[i]]--]=i;
        for(int k=1;k<n;k<<=1){
            top=0;for(int i=n;i>n-k;i--)yy[++top]=i;
            for(int i=1;i<=n;i++){
                if(sa[i]>k)yy[++top]=sa[i]-k;
            }
            memset(cc+1,0,V<<2);
            for(int i=1;i<=n;i++)cc[xx[i]]++;
            for(int i=1;i<=V;i++)cc[i]+=cc[i-1];
            for(int i=n;i>=1;i--)sa[cc[xx[yy[i]]]--]=yy[i];
            swap(xx,yy);
            V=xx[sa[1]]=1;for(int i=2;i<=n;i++)xx[sa[i]]=V+=!(sa[i]+k<=n && sa[i-1]+k<=n && yy[sa[i]]==yy[sa[i-1]] && yy[sa[i]+k]==yy[sa[i-1]+k]);
            if(V==n)break;
        }
        for(int i=1;i<=n;i++)rk[sa[i]]=i;
        int now=0;
        for(int i=1;i<=n;i++){
            if(now)now--;
            if(rk[i]==1)continue;
            while(ss[i+now]==ss[sa[rk[i]-1]+now])now++;
            h[i]=now;height[rk[i]]=now;
        }
        for(int i=1;i<=n;i++)rmq[0][i]=height[i];
        for(int i=1;i<=__lg(n);i++){
            for(int j=n-(1<<i)+1;j>=1;j--)rmq[i][j]=min(rmq[i-1][j],rmq[i-1][j+(1<<(i-1))]);
        }
    }
}s0,s1;
char st[N];
int ly[N];
void lyndon(bool op){
    stack<PII> stk;stk.push({n,n});ly[n]=n;
    for(int i=n-1;i>=1;i--){
        int now=i;
        while(!stk.empty() && s0.getcmp(i,stk.top().first)!=op)now=stk.top().second,stk.pop();
        ly[i]=now;
        stk.push({i,now});
    }
}
void getrun(){
    for(int l=1;l<=n;l++){
        int r=ly[l],ll=l,rr=r;
        if(l!=1)ll-=s1.getlcp(n-r+1,n-(l-1)+1);
        if(r!=n)rr+=s0.getlcp(l,r+1);
        if(rr-ll+1>=2*(r-l+1))run.push_back({ll,rr,r-l+1});
    }
}
int main(){
    scanf("%s",st+1);n=strlen(st+1);
    
    for(int i=1;i<=n;i++)s0.ss[i]=s1.ss[n-i+1]=st[i];
    st[n+1]=s0.ss[n+1]=s1.ss[n+1]='\0';
    s0.getsa();s1.getsa();
    for(int op=0;op<=1;op++){
        lyndon(op);
        getrun();
    }
    sort(run.begin(),run.end(),cmp);
    run.erase(unique(run.begin(),run.end()),run.end());
    printf("%d\n",run.size());
    for(auto [l,r,p]:run){
        printf("%d %d %d\n",l,r,p);
    }
    return 0;
}