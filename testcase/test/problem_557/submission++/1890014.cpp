#include<bits/stdc++.h>
using namespace std;
struct node{
	int l,r,col;
	node(){}
	node(int l_,int r_,int col_){
		l=l_,r=r_,col=col_;
	}
	bool operator<(const node&x)const{
		return l<x.l;
	}
};
set<node>s;
unordered_map<int,int>nid;
int curid;
int Getid(int x){
	if(!nid[x])nid[x]=++curid;
	return nid[x];
}
int rt[200005];
int ls[30000005],rs[30000005],sum[30000005],lazy[30000005],tot;
void pushdown(int p,int l,int r){
	if(!lazy[p])return;
	if(!ls[p])ls[p]=++tot;
	if(!rs[p])rs[p]=++tot;
	int mid=l+r>>1;
	sum[ls[p]]+=lazy[p]*(mid-l+1);
	sum[rs[p]]+=lazy[p]*(r-mid);
	lazy[ls[p]]+=lazy[p];
	lazy[rs[p]]+=lazy[p];
	lazy[p]=0;
}
void update(int &p,int l,int r,int x,int y,int v){
	if(!p)p=++tot;
	if(x<=l&&r<=y){
		sum[p]+=(r-l+1)*v;
		lazy[p]+=v;
		return;
	}
	pushdown(p,l,r);
	int mid=l+r>>1;
	if(x<=mid)update(ls[p],l,mid,x,y,v);
	if(y>mid)update(rs[p],mid+1,r,x,y,v);
	sum[p]=sum[ls[p]]+sum[rs[p]];
}
int Getp(int p,int l,int r,int k){
	if(l==r)return l;
	pushdown(p,l,r);
	int mid=l+r>>1;
	if(sum[ls[p]]>=k)return Getp(ls[p],l,mid,k);
	return Getp(rs[p],mid+1,r,k-sum[ls[p]]);
}
struct Seg{
	int p,l,r;
	Seg(){p=l=r=0;}
	Seg(int p_,int l_,int r_){
		p=p_,l=l_,r=r_; 
	}
}arr[100005];
int tt;
void Get(int p,int l,int r,int x,int y){
	if(x<=l&&r<=y){
		arr[++tt]=Seg(p,l,r);
		return;
	}
	pushdown(p,l,r);
	int mid=l+r>>1;
	if(x<=mid&&ls[p])Get(ls[p],l,mid,x,y);
	if(y>mid&&rs[p])Get(rs[p],mid+1,r,x,y);
}
int n,m,a[100005];
void split(int p){
	if(p==n+1)return;
	set<node>::iterator it=s.lower_bound(node(p,0,0));
	if(it!=s.end()&&(*it).l==p)return;
	it--;
	int l=(*it).l,r=(*it).r,col=(*it).col;
	s.erase(it);
	s.insert(node(l,p-1,col));
	s.insert(node(p,r,col));
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		a[i]=Getid(a[i]);
	}
	int lst=1;
	for(int i=2;i<=n;i++){
		if(a[i]!=a[i-1]){
			update(rt[a[i-1]],1,n,lst,i-1,1);
			s.insert(node(lst,i-1,a[i-1]));
			lst=i;
		}
	}
	update(rt[a[n]],1,n,lst,n,1);
	s.insert(node(lst,n,a[n]));
	int lans=0;
	while(m--){
		char op;
		scanf(" %c ",&op);
		if(op=='Q'){
			int l,r,k,v;
			scanf("%d%d%d%d",&l,&r,&k,&v);
			l^=lans,r^=lans,k^=lans,v^=lans;
			if(!nid[v]){
				lans=0;
				puts("0");
				continue;
			}
			v=nid[v];
			tt=0;
			Get(rt[v],1,n,l,r);
			int ans=0;
			for(int i=1;i<=tt;i++){
				if(k>sum[arr[i].p])k-=sum[arr[i].p];
				else{
					ans=Getp(arr[i].p,arr[i].l,arr[i].r,k);
					break;
				}
			}
			printf("%d\n",lans=ans);
		}
		else{
			int l,r,v;
			scanf("%d%d%d",&l,&r,&v);
			l^=lans,r^=lans,v^=lans;
			v=Getid(v);
			split(l),split(r+1);
			set<node>::iterator it1,it2;
			it1=s.lower_bound(node(l,0,0));
			it2=s.lower_bound(node(r+1,0,0));
			for(set<node>::iterator i=it1;i!=it2;i++){
				update(rt[(*i).col],1,n,(*i).l,(*i).r,-1);
			}
			s.erase(it1,it2);
			update(rt[v],1,n,l,r,1);
			s.insert(node(l,r,v));
		}
	}
	return 0;
}