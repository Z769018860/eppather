#include<bits/stdc++.h>
using namespace std;



#define int long long
#define y0 Y0
#define y1 Y1
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define min(a,b) (a<b?a:b) 
#define max(a,b) (a>b?a:b)
#define P pair<int,int>
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod) 
#define rd read()
#define lowbit(x) ((x)&(-x))
#define abs(x) ((x)<0?-(x):(x))
#define submod(x,y,mod) (((x-=y)<0)&&(x+=mod))
#define addmod(x,y,mod) (((x+=y)>=mod)&&(x-=mod))
mt19937 rnd(time(0));
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read(int u=0, char c=getchar(), bool f=false){
    for(;!isdigit(c);c=getchar()) f|=c=='-';
    for(;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+(c^'0');
    return f?-u:u;
}
inline void wt(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) wt(x/10);
    putchar((x%10)^'0');
}
inline void wt(int x,char k){wt(x),putchar(k);}
const int inf=~0U>>1,linf=~0ULL>>1;
const int mod=998244353,g=3,gi=332748118;
const int N=8e5+10;
namespace pam{
    int l,r,nxt[N][26],top,ans,llst,rlst,dep[N],fail[N],len[N];
    char s[N];
    void init(){
        fail[0]=1;len[1]=-1;top=1;l=4e5+1,r=4e5;
    }
    void push_back(int c){
        int p=rlst;s[++r]=c+'a';
        for(;s[r]!=s[r-len[p]-1];p=fail[p]);
        if(!nxt[p][c]){
            int u=++top,k=fail[p];len[u]=len[p]+2;
            for(;s[r]!=s[r-len[k]-1];k=fail[k]);
            fail[u]=nxt[k][c];nxt[p][c]=u;dep[u]=dep[fail[u]]+1;
        }
        rlst=nxt[p][c];
        if(len[rlst]==r-l+1) llst=rlst;
        ans+=dep[rlst];
    }
    void push_front(int c){
        int p=llst;s[--l]=c+'a';
        for(;s[l]!=s[l+len[p]+1];p=fail[p]);
        if(!nxt[p][c]){
            int u=++top,k=fail[p];len[u]=len[p]+2;
            for(;s[l]!=s[l+len[k]+1];k=fail[k]);
            fail[u]=nxt[k][c];nxt[p][c]=u;dep[u]=dep[fail[u]]+1;
        }
        llst=nxt[p][c];
        if(len[llst]==r-l+1) rlst=llst;
        ans+=dep[llst];
    }
}
using namespace pam;
string t;
int q;
main(){
    
    
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    init();cin>>t;
    for(char c:t) push_back(c-'a');
    cin>>q;
    while(q--){
        int op;cin>>op;
        if(op==1){
            cin>>t;
            for(char c:t) push_back(c-'a');
        }
        if(op==2){
            cin>>t;
            for(char c:t) push_front(c-'a');
        }
        if(op==3) cout<<ans<<endl;
    }
    return 0;
}