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
const int N=4e5,M=8e5+10;
namespace pam{
    char s[M];
    int ans,len[N],fail[N],nxt[N][26],dep[N],llst,rlst,top,l,r;
    void init(){
        fail[0]=1,len[1]=-1,top=1;
    }
    void push_back(int c){
        int p=rlst;s[++r]=c+'a';
        for(;s[r]!=s[r-len[p]-1];p=fail[p]);
        if(!nxt[p][c]){ 
            int u=++top,k=fail[p];len[u]=len[p]+2;
            for(;s[r]!=s[r-len[k]-1];k=fail[k]);
            fail[u]=nxt[k][c],dep[u]=dep[fail[u]]+1;
            nxt[p][c]=u;
        }
        rlst=nxt[p][c];
        if(r-l+1==len[rlst]) llst=rlst;
        ans+=dep[rlst];
    }
    void push_front(int c){
        int p=llst;s[--l]=c+'a';
        for(;s[l]!=s[l+len[p]+1];p=fail[p]);
        if(!nxt[p][c]){ 
            int u=++top,k=fail[p];len[u]=len[p]+2;
            for(;s[l]!=s[l+len[k]+1];k=fail[k]);
            fail[u]=nxt[k][c],dep[u]=dep[fail[u]]+1;
            nxt[p][c]=u;
        }
        llst=nxt[p][c];
        if(r-l+1==len[llst]) rlst=llst;
        ans+=dep[llst];
    }    
};
using namespace pam;
int q;
char t[N];
main(){
    
    
    l=N+1,r=N;init();
    scanf("%s",t+1);
    for(char *c=t+1;*c;c++) push_back(*c-'a');
    scanf("%lld",&q);
    while(q--){
        int op;
        scanf("%lld",&op);
        if(op==1){
            scanf("%s",t+1);
            for(char *c=t+1;*c;c++) push_back(*c-'a');            
        }
        if(op==2){
            scanf("%s",t+1);
            for(char *c=t+1;*c;c++) push_front(*c-'a');
        }
        if(op==3) wt(ans,'\n');
    }
    return 0;
}