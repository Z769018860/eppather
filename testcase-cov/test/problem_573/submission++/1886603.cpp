#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int mod=998244353;
const int maxn=1000005;
int n,T,m,type,p[maxn];
struct node{
	int t[2][2],l,r;
};
node Merge(const node& g1,const node& g2){
	node res;
	res.l=g1.l;res.r=g2.r;
	
	
	res.t[0][0]=((long long)g1.t[0][0]*g2.t[0][0]+(long long)g1.t[1][0]*g2.t[0][1])%mod;
	res.t[0][1]=((long long)g1.t[0][1]*g2.t[0][0]+(long long)g1.t[1][1]*g2.t[0][1])%mod;
	res.t[1][0]=((long long)g1.t[0][0]*g2.t[1][0]+(long long)g1.t[1][0]*g2.t[1][1])%mod;
	res.t[1][1]=((long long)g1.t[0][1]*g2.t[1][0]+(long long)g1.t[1][1]*g2.t[1][1])%mod;
	return res;
}
struct xds{
	node pool[maxn<<2];
	void pushup(int id){
		pool[id]=Merge(pool[id<<1],pool[id<<1|1]);
	}
	void build(int id,int l,int r){
		pool[id].l=l;pool[id].r=r;
		if(l==r){
			pool[id].t[0][0]=0;pool[id].t[0][1]=1;
			pool[id].t[1][0]=1;pool[id].t[1][1]=p[l];
			return;
		}
		int mid=l+r>>1;
		build(id<<1,l,mid);
		build(id<<1|1,mid+1,r);
		pushup(id);
	}
	void change(int id,int x,int y){
		if(pool[id].l==pool[id].r){
			pool[id].t[1][1]=y;
			return;
		}
		int mid=pool[id].l+pool[id].r>>1;
		if(x<=mid)change(id<<1,x,y);
		else change(id<<1|1,x,y);
		pushup(id);
	}
	node ask(int id,int l,int r){
		if(pool[id].l==l&&pool[id].r==r)return pool[id];
		int mid=pool[id].l+pool[id].r>>1;
		if(r<=mid)return ask(id<<1,l,r);
		else if(l>mid)return ask(id<<1|1,l,r);
		else return Merge(ask(id<<1,l,mid),ask(id<<1|1,mid+1,r));
	}
}t1;
int now,ansx,ansy;
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>T>>type;m=n+T;
	for(int i=1;i<=n;++i)cin>>p[m-i+1];
	t1.build(1,1,m);
	now=n;
	while(T--){
		int op,x,y;
		cin>>op>>x;
		if(type)x^=ansx;
		if(op==1){
			t1.change(1,m-(++now)+1,x);
		}
		else{
			cin>>y;
			if(type)y^=ansx;
			node tmp=t1.ask(1,m-y+1,m-x+1);
			ansx=tmp.t[1][1];
			ansy=tmp.t[0][1];
			cout<<ansx<<' '<<ansy<<'\n';
			ansx^=ansy;
		}
	}
	return 0;
}