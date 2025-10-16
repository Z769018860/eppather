#include <bits/stdc++.h>

using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

const int N=5e5+5;

typedef long long ll;
typedef double db;

# define chkmax(a,b) a=max(a,b)
# define chkmin(a,b) a=min(a,b)
# define PII pair<int,int>  
# define mkp make_pair

template<typename T> void read(T &x){
    x=0;int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int n,m,q;
int faz[N],son[N][2],siz[N],isiz[N],val[N],col[N];
ll sum[N],lans[N],rans[N],ians[N];
int stk[N];
bool rev[N];
map<PII,int> var;

bool locate(int x){return son[faz[x]][1]==x;}
bool isroot(int x){return son[faz[x]][0]!=x&&son[faz[x]][1]!=x;}

void update(int x){
    siz[x]=siz[son[x][0]]+siz[son[x][1]]+isiz[x]+col[x];
    sum[x]=sum[son[x][0]]+sum[son[x][1]]+val[x];
    lans[x]=lans[son[x][0]]+lans[son[x][1]]+ians[x]+(sum[son[x][0]]+val[x])*(siz[son[x][1]]+isiz[x]+col[x]);
    rans[x]=rans[son[x][0]]+rans[son[x][1]]+ians[x]+(sum[son[x][1]]+val[x])*(siz[son[x][0]]+isiz[x]+col[x]);
}

void pushr(int x){
    swap(son[x][0],son[x][1]);
    swap(lans[x],rans[x]);
    rev[x]^=1;
}

void pushdown(int x){
    if(rev[x]){
        if(son[x][0])pushr(son[x][0]);
        if(son[x][1])pushr(son[x][1]);
        rev[x]=0;
    }
}

void rotate(int x){
    int y=faz[x],z=faz[y],side=locate(x);
    if(!isroot(y))son[z][son[z][1]==y]=x;
    son[y][side]=son[x][side^1],faz[son[y][side]]=y;
    son[x][side^1]=y,faz[y]=x,faz[x]=z;
    update(y),update(x);
}   

void splay(int x){
    int y=x,top=0;
    while(!isroot(y))stk[++top]=y,y=faz[y];
    stk[++top]=y;
    while(top)pushdown(stk[top--]);
    while(!isroot(x)){
        y=faz[x];
        if(!isroot(y))rotate(locate(x)==locate(y)?y:x);
        rotate(x);
    }
    update(x);
}

void access(int x){
    for(int y=0;x;y=x,x=faz[x]){
        splay(x);
        isiz[x]+=siz[son[x][1]];
        ians[x]+=lans[son[x][1]];
        son[x][1]=y;
        isiz[x]-=siz[son[x][1]];
        ians[x]-=lans[son[x][1]];
        update(x);
    }   
}

void makeroot(int x){
    access(x),splay(x),pushr(x);
}   

void split(int x,int y){
    makeroot(x),access(y),splay(y);
}

void link(int x,int y){
    split(x,y);
    faz[x]=y,isiz[y]+=siz[x],ians[y]+=lans[x];
    update(y);
}

void cut(int x,int y){
    makeroot(x),access(y);
    faz[x]=son[y][0]=0;
    update(y);
}

void connect(int x,int y,int c){
    if(x>y)swap(x,y);
    val[++n]=c;
    update(n);
    var[mkp(x,y)]=n;
    link(x,n),link(n,y);
}

void disconn(int x,int y){
    if(x>y)swap(x,y);
    int p=var[mkp(x,y)];
    cut(x,p),cut(y,p);
}

int main()
{
    # ifndef ONLINE_JUDGE   
    freopen("testdata.in","r",stdin);
    freopen("test1.out","w",stdout);
    # endif
    read(n),read(m),read(q);
    Rep(i,1,m){
        int x,y,c;
        read(x),read(y),read(c);
        connect(x,y,c);
    }
    while(q--){
        char opt[10];
        int x,y,c;
        scanf("%s",opt);
        read(x);
        if(opt[0]=='L')read(y),read(c),connect(x,y,c);
        if(opt[0]=='C')read(y),disconn(x,y);
        if(opt[0]=='F')makeroot(x),col[x]^=1,update(x);
        if(opt[0]=='Q')makeroot(x),printf("%lld\n",lans[x]);
    }
    return 0;
}