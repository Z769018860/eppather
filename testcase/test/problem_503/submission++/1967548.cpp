







#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define mx3(a,b,c) ((a>b?a:b)>c?(a>b?a:b):c)
#define mn3(a,b,c) ((a<b?a:b)<c?(a<b?a:b):c)
#define infll 1e16
#define inf 50000005
#define pii pair<int,int>
#define F(i,a,b) for(int i=a;i<=(b);i++)
#define dF(i,a,b) for(int i=a;i>=(b);i--)
#define wh(lzm) while(lzm--)
#define lowbit(x) (x&(-x))
#define HH printf("\n")
#define eb emplace_back
#define vi vector<int>
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
const int maxn=309309;
int t[maxn<<1],tot,pre[maxn],Ans[maxn],ls[maxn],rs[maxn],n,m;
void update(int &o,int l,int r,int ql,int qr,int x){
	if(!o) o=++tot;
	if(ql<=l&&qr>=r) return t[o]+=x,void();
	int mid=(l+r)>>1;
	if(ql<=mid) update(ls[o],l,mid,ql,qr,x);
	if(qr>mid) update(rs[o],mid+1,r,ql,qr,x);
}
int query(int o,int l,int r,int pos){
	if(!o) return 0;
	if(l==r) return t[o];
	int mid=(l+r)>>1;
	if(pos<=mid) return query(ls[o],l,mid,pos)+t[o];
	else return query(rs[o],mid+1,r,pos)+t[o];
}
int rt;
void add(int l,int r,int x){
	update(rt,0,inf<<1,l+inf,r+inf,x);
}
int query(int pos){
	return query(rt,0,inf<<1,pos+inf);
}
int nx[maxn],ny[maxn],op[maxn],qx[maxn],qy[maxn];
void solve(int a[],int cg[]){
	pre[0]=1;
	F(i,1,n) pre[i]=pre[i-1]+a[i]; 
	int dt=0,cur=0,top=1;
	rt=0;
	F(i,1,n-1) add(min(pre[i],pre[i+1]),max(pre[i],pre[i+1]),1);
	cur=query(0)+(pre[1]<0);
	F(i,1,m)
		if(op[i]==1){if(top!=1){
			--top;
			pre[top]-=dt;
			add(min(pre[top],pre[top+1]),max(pre[top],pre[top+1]),1);
		}}
		else if(op[i]==2){if(top!=n){
			add(min(pre[top],pre[top+1]),max(pre[top],pre[top+1]),-1);
			pre[top]+=dt;
			++top;
		}}
		else if(op[i]==3){
			cur-=query(-dt);
			if(1ll*pre[top-1]*(pre[top]+dt)<0ll) cur--;
			dt+=cg[i]-a[top];
			a[top]=cg[i];
			cur+=query(-dt);
			if(1ll*pre[top-1]*(pre[top]+dt)<0ll) cur++;
		}
		else Ans[i]+=cur;
}
signed main(){
	n=read();
	F(i,1,n) nx[i]=read(),ny[i]=read();
	m=read();
	F(i,1,m){
		char tmp; cin>>tmp;
		if(tmp=='B') op[i]=1;
		if(tmp=='F') op[i]=2;
		if(tmp=='C') op[i]=3,qx[i]=read(),qy[i]=read();
		if(tmp=='Q') op[i]=4; 
	}
	solve(nx,qx);
	solve(ny,qy);
	F(i,1,m) if(op[i]==4) printf("%d\n",Ans[i]);
}