#include<bits/stdc++.h>
#define int ll
#define ll long long
#define db double
#define MP make_pair
#define vec vector<int>
#define pii pair<int,int>
#define pb emplace_back
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define CLK (double)clock()/CLOCKS_PER_SEC
using namespace std;
mt19937 rnd(time(0));
int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
void write(int x){
    if(x<0){putchar('-');write(-x);}
    else {
        if(x>9)write(x/10);
        putchar(x%10+'0');
    }
}
const int N=8e5+5;
int n,m,fa[N],tot,lst[2],len[N],ch[N][30],dep[N];
int L=4e5+1,R=4e5,ans;char s[N];
void init(){fa[0]=tot=1,len[1]=-1;}
int get(int t,int x,int op){
    while(s[t]!=s[t-(len[x]+1)*(op?1:-1)])x=fa[x];
    return x;
}
void extend(char c,int op){
    if(op)s[++R]=c,c-='a';
    else s[--L]=c,c-='a';
    int t=op==1?R:L,p=get(t,lst[op],op);
    if(!ch[p][c]){
        int x=++tot,q=get(t,fa[p],op);
        fa[x]=ch[q][c],ch[p][c]=x,len[x]=len[p]+2;
        dep[x]=dep[fa[x]]+1;
    }
    lst[op]=ch[p][c];ans+=dep[lst[op]];
    if(len[lst[op]]==R-L+1)lst[op^1]=lst[op];
}
void MAIN(){
    init();string t;
    cin>>t;for(auto i:t)extend(i,1);
    m=read();
    for(int i=1;i<=m;i++){
        int op=read();
        if(op==1){cin>>t;for(auto i:t)extend(i,1);}
        if(op==2){cin>>t;for(auto i:t)extend(i,0);}
        if(op==3){cout<<ans<<"\n";}
    }
}
signed main(){
    
    
    int T=1;while(T--)MAIN();
    
    return 0;
}
