#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=3e5,Mod=19260817;

inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,y>>=1;
    }
    return res;
}

int n,m,s,ans,sz[Maxn+5],qr[Maxn+5][3],cnt[Maxn+5],all;
vector<int> v[Maxn+5],vec;
inline int Trans(int x) {return lower_bound(vec.begin(),vec.end(),x)-vec.begin()+1;}
inline int S(int x) {return (1ll*x*(x+1)/2)%Mod;}

struct Node
{
    int k,cnt;
    inline void Add(int x) {if(!x) cnt++; else k=1ll*k*x%Mod;}
    inline void Del(int x) {if(!x) cnt--; else k=1ll*k*Pow(x,Mod-2)%Mod;}
    inline int Get() {return cnt?0:k;}
};
struct Data
{
    map<int,set<int>> mp;
    map<int,int> val; Node t;
    inline void Add(int x,int y)
    {
        auto &st=mp[x]; if(st.empty()) val[x]=cnt[x],st.insert(0),st.insert(sz[x]+1);
        auto it=st.lower_bound(y); int pr=*prev(it),nx=*it;
        t.Del(val[x]);
        val[x]=(1ll*val[x]-S(nx-pr-1)+S(y-pr-1)+S(nx-y-1)+Mod)%Mod;
        st.insert(y),t.Add(val[x]);
    }
    inline void Del(int x,int y)
    {
        auto &st=mp[x]; t.Del(val[x]);
        auto it=st.lower_bound(y); it=st.erase(it);
        int pr=*prev(it),nx=*it;
        val[x]=(1ll*val[x]-S(y-pr-1)-S(nx-y-1)+S(nx-pr-1)+Mod+Mod)%Mod;
        t.Add(val[x]);
    }
    inline int Get() {return t.Get();}
} h[Maxn+5];

int main()
{
    

    cin>>n>>m;
    For(i,1,n) cin>>sz[i],v[i].resize(sz[i]+2);
    For(i,1,n) For(j,1,sz[i]) cin>>v[i][j],vec.push_back(v[i][j]);
    For(i,1,m)
    {
        int x,y,z; cin>>x>>y>>z; vec.push_back(z);
        qr[i][0]=x,qr[i][1]=y,qr[i][2]=z;
    } sort(vec.begin(),vec.end()),vec.erase(unique(vec.begin(),vec.end()),vec.end()),s=vec.size();
    For(i,1,n) For(j,1,sz[i]) v[i][j]=Trans(v[i][j]);
    For(i,1,m) qr[i][2]=Trans(qr[i][2]);
    For(i,1,n) cnt[i]=S(sz[i]);
    all=1; For(i,1,n) all=1ll*all*cnt[i]%Mod;
    For(i,1,s) h[i].t.k=all,h[i].t.cnt=0;
    For(i,1,n) For(j,1,sz[i]) h[v[i][j]].Add(i,j);
    For(i,1,s) ans=(1ll*ans+all-h[i].Get()+Mod)%Mod;
    printf("%d\n",ans); For(i,1,m)
    {
        int x=qr[i][0],y=qr[i][1],z=qr[i][2];
        if(v[x][y]!=z)
        {
            int k=v[x][y];
            int a=(all-h[k].Get()+Mod)%Mod;
            int b=(all-h[z].Get()+Mod)%Mod;
            ans=(1ll*ans-a-b+Mod+Mod)%Mod;
            h[k].Del(x,y),h[z].Add(x,y),v[x][y]=z;
            a=(all-h[k].Get()+Mod)%Mod;
            b=(all-h[z].Get()+Mod)%Mod;
            ans=(1ll*ans+a+b)%Mod;
        } printf("%d\n",ans);
        
    }
    return 0;
}