






#include<bits/stdc++.h>
using namespace std;
typedef int ll;
template <typename T>
inline void read(T &x){
	x=0; bool f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=0; ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48); ch=getchar();
	}
	x=f?x:-x;
}
template <typename T>
inline void write(T x){
	if(x<0) x=-x,putchar('-');
	if(x>9) write(x/10);
	putchar('0'+x%10);
}
const ll N=500009;
const ll M=10000009;
const ll INF=2147483647;
ll n,m,a[N];
mt19937 rnd(time(0));
namespace FHQ_Treap{
	ll tot;
	#define ls(u) tr[u].ls
	#define rs(u) tr[u].rs
	#define sz(u) tr[u].sz
	#define val(u) tr[u].val
	#define pri(u) tr[u].pri
	struct Node{
		ll val,sz,ls,rs,pri;
	} tr[M];
	struct fhq{
		ll rt;
		inline void pushup(ll u){
			sz(u)=sz(ls(u))+sz(rs(u))+1;
			return;
		}
		inline ll merge(ll u,ll v){
			if(!u||!v) return u+v;
			if(pri(u)<pri(v)){
				rs(u)=merge(rs(u),v);
				pushup(u);
				return u;
			}
			else{
				ls(v)=merge(u,ls(v));
				pushup(v);
				return v;
			}
		}
		inline void split(ll u,ll z,ll &x,ll &y){
			if(!u){
				x=y=0;
				return;
			}
			if(val(u)<=z){
				x=u;
				split(rs(u),z,rs(x),y);
			}
			else{
				y=u;
				split(ls(u),z,x,ls(y));
			}
			pushup(u);
			return;
		}
		inline ll expand(ll z){
			val(++tot)=z;
			pri(tot)=rnd();
			sz(tot)=1;
			return tot;
		}
		ll x,y,z;
		inline void insert(ll val){
			split(rt,val,x,y);
			rt=merge(x,merge(expand(val),y));
		}
		inline void del(ll val){
			split(rt,val,x,z);
			split(x,val-1,x,y);
			y=merge(ls(y),rs(y));
			rt=merge(x,merge(y,z));
		}
		inline ll findrk(ll key){
			split(rt,key-1,x,y);
			ll ans=sz(x)+1;
			rt=merge(x,y);
			return ans;
		}
		inline void build(ll l,ll r){
			for(ll i=l;i<=r;i++){
				insert(a[i]);
			}
		}
		inline ll findkey(ll u,ll rk){
			if(rk<=sz(ls(u))) return findkey(ls(u),rk);
			if(rk==sz(ls(u))+1) return val(u);
			return findkey(rs(u),rk-sz(ls(u))-1);
		}
		inline ll pre(ll key){
			split(rt,key-1,x,y);
			ll res;
			if(sz(x)) res=findkey(x,sz(x));
			else res=-INF;
			rt=merge(x,y);
			return res;
		}
		inline ll nxt(ll key){
			split(rt,key,x,y);
			ll res;
			if(sz(y)) res=findkey(y,1);
			else res=INF;
			rt=merge(x,y);
			return res;
		}
	} ft[N*4];
}
using namespace FHQ_Treap;
namespace segment{
	ll rt[N*4];
	inline void build(ll u,ll l,ll r){
		ft[u].build(l,r);
		if(l==r) return;
		ll mid=(l+r)/2;
		build(u*2,l,mid);
		build(u*2+1,mid+1,r);
	}
	inline ll queryrk(ll u,ll l,ll r,ll ql,ll qr,ll x){
		if(r<ql||qr<l) return 0;
		if(ql<=l&&r<=qr) return ft[u].findrk(x)-1;
		ll mid=(l+r)/2;
		return queryrk(u*2,l,mid,ql,qr,x)+queryrk(u*2+1,mid+1,r,ql,qr,x);
	}
	inline ll querykey(ll l,ll r,ll rk){
		ll L=0,R=1e9,ans=-1;
		while(L<=R){
			ll mid=(L+R)/2;
			if(queryrk(1,1,n,l,r,mid)+1<=rk){
				ans=mid;
				L=mid+1;
			}
			else{
				R=mid-1;
			}
		}
		return ans;
	}
	inline void upd(ll u,ll l,ll r,ll p,ll k){
		ft[u].del(a[p]);
		ft[u].insert(k);
		if(l==r) return;
		ll mid=(l+r)/2;
		if(p<=mid) upd(u*2,l,mid,p,k);
		else upd(u*2+1,mid+1,r,p,k);
	}
	inline ll pre(ll u,ll l,ll r,ll ql,ll qr,ll x){
		if(r<ql||qr<l) return -INF;
		if(ql<=l&&r<=qr) return ft[u].pre(x);
		ll mid=(l+r)/2;
		return max(pre(u*2,l,mid,ql,qr,x),pre(u*2+1,mid+1,r,ql,qr,x));
	}
	inline ll nxt(ll u,ll l,ll r,ll ql,ll qr,ll x){
		if(r<ql||qr<l) return INF;
		if(ql<=l&&r<=qr) return ft[u].nxt(x);
		ll mid=(l+r)/2;
		return min(nxt(u*2,l,mid,ql,qr,x),nxt(u*2+1,mid+1,r,ql,qr,x));
	}
}
int main(){
	read(n),read(m);
	for(ll i=1;i<=n;i++){
		read(a[i]);
	}
	segment::build(1,1,n);
	while(m--){
		ll opt; read(opt);
		if(opt==1){
			ll l,r,k;
			read(l),read(r),read(k);
			printf("%d\n",segment::queryrk(1,1,n,l,r,k)+1);
		}
		else if(opt==2){
			ll l,r,k;
			read(l),read(r),read(k);
			printf("%d\n",segment::querykey(l,r,k));
		}
		else if(opt==3){
			ll p,k;
			read(p),read(k);
			segment::upd(1,1,n,p,k);
			a[p]=k;
		}
		else if(opt==4){
			ll l,r,k;
			read(l),read(r),read(k);
			printf("%d\n",segment::pre(1,1,n,l,r,k));
		}
		else{
			ll l,r,k;
			read(l),read(r),read(k);
			printf("%d\n",segment::nxt(1,1,n,l,r,k));
		}
	}
	return 0;
}

