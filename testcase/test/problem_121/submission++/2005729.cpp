








#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define EPS 1e-8
#define ll long long
#define ld long double
#define PII pair<int,int>
#define PDD pair<int,int>
#define max3(a,b,c) max(max(a,b),c)
#define max4(a,b,c,d) max(max3(a,b,c),d)
#define lowbit(x) ((x)&-(x))
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define Yes printf("Yes")
#define No printf("No")
using namespace std;

int read(){
	int res=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9')f=ch=='-'?-1:f,ch=getchar();
    while(ch>='0' && ch<='9')res=res*10+ch-'0',ch=getchar();
    return res*f;
}
void write(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
constexpr int N=5010,M=500010;
int n,m;
int mnum,qnum;
struct Modify{
	int u,v,t;
	int op;
	Modify(){}
	Modify(int u,int v,int op,int t):
		u(u),v(v),op(op),t(t){}
	bool operator == (const Modify B)const{
		return u==B.u&&v==B.v&&t==B.t;
	}
	bool operator < (const Modify B)const{
		if(u!=B.u)return u<B.u;
		if(v!=B.v)return v<B.v;
		return t<B.t;
	}
}a[M];
struct Query{
	int u,v;
	Query(){}
	Query(int u,int v):
		u(u),v(v){}
}b[M];
int rt,tot;
struct SEG{
	int ls,rs;
	vector<PII> e;
	#define lc (t[p].ls)
	#define rc (t[p].rs)
	#define mid (L+R>>1)
}t[M<<1];
void build(int &p,int L,int R){
	if(L>R)return;
	if(!p)p=++tot;
	if(L==R)return;
	build(lc,L,mid);
	build(rc,mid+1,R);
}
void modify(int p,int L,int R,int l,int r,PII x){
	if(l>r)return;
	if(l<=L&&R<=r){
		t[p].e.emplace_back(x);
		return;
	}
	if(l<=mid)modify(lc,L,mid,l,r,x);
	if(r>mid)modify(rc,mid+1,R,l,r,x);
}
stack<PII> tmp;
struct UF{
	int fa[N],siz[N];
	void init(){
		rep(i,1,n)fa[i]=i,siz[i]=1;
	}
	int find(int x){return fa[x]==x?x:find(fa[x]);}
	void merge(int x,int y){
		int f1=find(x),f2=find(y);
		if(siz[f1]>siz[f2])swap(f1,f2);
		tmp.emplace(f1,f2);
		fa[f1]=f2;
		siz[f2]+=siz[f1];
	}
	void erase(int x,int y){
		fa[x]=x;
		siz[y]-=siz[x];
	}
}uf;
void solve(int p,int L,int R){
	if(L>R)return;
	int sz=tmp.size();
	for(auto i:t[p].e){
		int u=i.first,v=i.second;
		if(uf.find(u)==uf.find(v))continue;
		uf.merge(u,v);
	}
	if(L==R){
		int u=b[L].u,v=b[L].v;
		if(uf.find(u)==uf.find(v))puts("Y");
		else puts("N");
	}
	else{
		solve(lc,L,mid);
		solve(rc,mid+1,R);
	}
	while((L!=1||R!=qnum)&&tmp.size()>sz){
		uf.erase(tmp.top().first,tmp.top().second);
		tmp.pop();
	}
}
int main(){


	ios::sync_with_stdio(0);
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		int op=read(),x=read(),y=read();
		if(x>y)swap(x,y);
		if(op==0)
			a[++mnum]=Modify(x,y,1,qnum);
		else if(op==1)
			a[++mnum]=Modify(x,y,0,qnum);
		else
			b[++qnum]=Query(x,y);
	}
	uf.init();
	build(rt,1,qnum);
	sort(a+1,a+mnum+1);
	for(int i=1;i<=mnum;){
		int I=i;
		int lst=-1;
		while(i<=mnum&&a[i].u==a[I].u&&a[i].v==a[I].v){
			int num=0,j;
			for(j=i;j<=mnum&&a[j]==a[i];j++){
				if(a[j].op==1)num++;
				else num--;
			}
			j--;
			if(num==0){
				i=j+1;
				continue;
			}
			else if(num==1){
				lst=a[i].t;
				i=j+1;
			}
			else{
				modify(rt,1,qnum,lst+1,a[i].t,{a[I].u,a[I].v});
				lst=-1;
				i=j+1;
			}
		}
		if(lst!=-1)
			modify(rt,1,qnum,lst+1,qnum,{a[I].u,a[I].v});
	}
	solve(rt,1,qnum);
	return 0;
}