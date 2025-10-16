#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define mx3(a,b,c) ((a>b?a:b)>c?(a>b?a:b):c)
#define mn3(a,b,c) ((a<b?a:b)<c?(a<b?a:b):c)
#define infll 1e16
#define inf 1e9
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
const int maxn=500005;
int a[maxn],n,m;
int t[maxn<<2],lz[maxn<<2],pos[maxn<<2];
#define ls (o<<1)
#define rs (o<<1|1)
void build(int o,int l,int r){
	if(l==r) return t[o]=a[l],pos[o]=l,void();
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	t[o]=min(t[ls],t[rs]);
	if(t[o]==t[ls]) pos[o]=pos[ls];
	else pos[o]=pos[rs];
}
void pushdown(int o){
	if(!lz[o]) return;
	t[ls]=max(t[ls],lz[o]);
	lz[ls]=max(lz[ls],lz[o]);
	t[rs]=max(t[rs],lz[o]);
	lz[rs]=max(lz[rs],lz[o]);
	lz[o]=0;
}
void update(int o,int l,int r,int ql,int qr,int x){
	if(ql<=l&&qr>=r){
		lz[o]=max(lz[o],x);
		t[o]=max(t[o],x);
		return;
	}
	int mid=(l+r)>>1;
	pushdown(o);
	if(ql<=mid) update(ls,l,mid,ql,qr,x);
	if(qr>mid) update(rs,mid+1,r,ql,qr,x);
	t[o]=min(t[ls],t[rs]);
	if(t[o]==t[ls]) pos[o]=pos[ls];
	else pos[o]=pos[rs];
}
pii query(int o,int l,int r,int ql,int qr){
	if(ql<=l&&qr>=r) return make_pair(t[o],pos[o]);
	int mid=(l+r)>>1;
	pushdown(o);
	pii rt=make_pair(inf,0);
	if(ql<=mid){
		pii sb=query(ls,l,mid,ql,qr);
		if(sb.fi<rt.fi) rt=sb;
	}
	if(qr>mid){
		pii sb=query(rs,mid+1,r,ql,qr);
		if(sb.fi<rt.fi) rt=sb;
	}
	return rt;
}
vector<int>ans;
struct lzmwh{
	int l,r,k,pos;
	lzmwh(int l,int r,int k,int pos):l(l),r(r),k(k),pos(pos){}
	bool operator<(const lzmwh &b)const{
		return k>b.k;
	}
};
priority_queue<lzmwh>q;
void solve(int L,int R,int k,int x){
	pii sb=query(1,1,n,L,R);
	while(!q.empty()) q.pop();
	q.push(lzmwh(L,R,sb.fi,sb.se));
	while(!q.empty()){
		lzmwh tt=q.top();
		q.pop();
		int l=tt.l,r=tt.r,kk=tt.k,pp=tt.pos;
		if(kk<k){
			ans.pb(kk);
			if(l<=pp-1){
				pii sb=query(1,1,n,l,pp-1);
				q.push(lzmwh(l,pp-1,sb.fi,sb.se));
			}
			if(pp+1<=r){
				sb=query(1,1,n,pp+1,r);
				q.push(lzmwh(pp+1,r,sb.fi,sb.se));
			}
			if((int)ans.size()==x) break;
		}
	}
}
signed main(){
	memset(t,0x3f,sizeof t);
	n=read();
	F(i,1,n) a[i]=read();
	m=read();
	build(1,1,n);
	F(i,1,m){
		int op=read(),l=read(),r=read(),k=read();
		if(op&1) update(1,1,n,l,r,k);
		else{
			int x=read();
			if(r-l+1<x){ puts("-1"); continue;}
			ans.clear();
			solve(l,r,k,x);
			sort(ans.begin(),ans.end());
			if((int)ans.size()!=x||ans.back()>=k) printf("-1");
			else for(int i:ans) printf("%d ",i);
			HH;
		}
	}
}