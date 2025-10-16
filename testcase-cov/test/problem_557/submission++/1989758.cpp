#include<bits/stdc++.h>
using namespace std;


using ll=long long;using ull=unsigned long long;using pii=pair<int,int>;using i128=__int128_t;
#define all(x) x.begin(),x.end()
#define mem0(x) memset(x,0,sizeof(x))
#define YES puts("YES")
#define NO puts("NO")
#define Yes puts("Yes")
#define No puts("No")
#define errorf(...) fprintf(stderr, __VA_ARGS__) 
#define endl '\n'
#define pb push_back
inline int read(){int f=1,x=0;char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}while(isdigit(c)){x=x*10+c-'0';c=getchar();}return x*f;}
template <class T> inline T read(){T f=1,x=0;char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}while(isdigit(c)){x=x*10+c-'0';c=getchar();}return x*f;}
template <class T> void write(T x){if(x<0)putchar('-'),x=-x;if(x>9)write(x/10);putchar(x%10+'0');}


const int N = 5e5+5;
struct Node{
    int l,r;
    int pri,sz;
    int x,y,cnt;
}t[N];
void pushup(int o){
    t[o].sz=t[t[o].l].sz+t[t[o].r].sz+1;
    t[o].cnt=t[t[o].l].cnt+t[t[o].r].cnt+(t[o].y-t[o].x+1);
}
void split(int o,int v,int& x,int& y){
    if(!o){x=0,y=0;return;}
    if(t[o].x<=v)x=o,split(t[x].r,v,t[x].r,y),pushup(x);
    else y=o,split(t[y].l,v,x,t[y].l),pushup(y);
}
int merge(int x,int y){
    if(!x||!y)return x+y;
    if(t[x].pri>t[y].pri){
        t[x].r=merge(t[x].r,y);
        pushup(x);
        return x;
    }
    else{
        t[y].l=merge(x,t[y].l);
        pushup(y);
        return y;
    }
}

stack<int> rubbish;
int tot;
int newnode(int l,int r){
    int o;
    if(rubbish.size()){
        o=rubbish.top();rubbish.pop();
    }
    else o=++tot;
    t[o]={0,0,rand(),1,l,r,r-l+1};
    return o;
}


struct ODT{
    int l,r,v;
};
bool operator<(const ODT& a,const ODT& b){
    return a.l<b.l;
}
set<ODT> odt;
unordered_map<int,int> rt;
int n,m;
auto insert(int l,int r,int v){
    int x,y;
    split(rt[v],l-1,x,y);
    rt[v]=merge(x,merge(newnode(l,r),y));
    return odt.insert({l,r,v}).first;
}
void erase(set<ODT>::iterator it){
    auto [l,r,v] = *it;
    int x,y,z;
    split(rt[v],l,x,z);
    split(x,l-1,x,y);
    rubbish.push(y);
    rt[v]=merge(x,z);
    odt.erase(it);
}
auto split(int x){
    if(x>n)return odt.end();
    auto it=--odt.upper_bound(ODT{x,0,0});
    if(it->l==x)return it;
    int l=it->l,r=it->r,v=it->v;
    erase(it);
    insert(l,x-1,v);
    return insert(x,r,v);
}
void assign(int l,int r,int v){
    auto itr = split(r+1);
    auto itl = split(l);
    for(auto it=next(itl);;++it){
        erase(prev(it));
        if(it==itr)break;
    }
    insert(l,r,v);
}
int query(int o,int k){
    if(!o)return 0;
    if(t[t[o].l].cnt>=k)return query(t[o].l,k);
    if(k<=t[t[o].l].cnt+(t[o].y-t[o].x+1))return t[o].x+(k-t[t[o].l].cnt-1);
    return query(t[o].r,k-t[t[o].l].cnt-(t[o].y-t[o].x+1));
}
int query(int l,int r,int k,int v){
    int x,y;
    split(l);
    split(rt[v],l-1,x,y);
    int ans = query(y,k);
    rt[v]=merge(x,y);
    if(ans>r)return 0;
    return ans;
}


int main(){
    n=read(); m=read();
    for(int i=1;i<=n;i++){
        int a=read();
        insert(i,i,a);
    }

    int last = 0;
   
    while(m--){
        char op[2];scanf("%s",op);
        if(op[0]=='Q'){
            int l=read()^last,r=read()^last,k=read()^last,v=read()^last;
            if(l==0)l=1;
            printf("%d\n",last=query(l,r,k,v));
            
        }
        else{
            int l=read()^last,r=read()^last,v=read()^last; 
            if(l==0)l=1;
            assign(l,r,v);
        }

        
    }

    return 0;
}