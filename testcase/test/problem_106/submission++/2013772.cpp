#include<bits/stdc++.h>
using namespace std;
#define N 51000
int n,m,a[N],op,pos,l,r,k,rt[N*700],tot,root,x,y;
struct node{
	int l,r;
	int cnt;
}tr[N*700];
void modify(int &p,int nl,int nr,int l,int r,int k){
	if(nl>l||nr<l){
		return ;
	}
	if(k==1&&(!p)){
		tot++;
		p=tot;
	}
	if(p){
		tr[p].cnt+=k;
	}
	if(p==0||nl==nr){
		return ;
	}
	int mid=(nl+nr)/2;
	modify(tr[p].l,nl,mid,l,r,k);
	modify(tr[p].r,mid+1,nr,l,r,k);
	return ;
}
int query1(int p,int nl,int nr,int l,int r){
	if(nl>r||nr<l||p==0){
		return 0;
	}
	if(l<=nl&&nr<=r){
		return tr[p].cnt;
	}
	int mid=(nl+nr)/2;
	return query1(tr[p].l,nl,mid,l,r)+query1(tr[p].r,mid+1,nr,l,r);
}
int query2(int p,int nl,int nr,int l,int r,int k1,int k2){
	if(nl>r||nr<l||p==0){
		return 0;
	}
	if(l<=nl&&nr<=r){
		return query1(rt[p],1,n,k1,k2);
	}
	int mid=(nl+nr)/2;
	return query2(tr[p].l,nl,mid,l,r,k1,k2)+query2(tr[p].r,mid+1,nr,l,r,k1,k2);
}
int kth(int p,int nl,int nr,int k,int l,int r){
	if(nl==nr){
		return nl;
	}
	int mid=(nl+nr)/2;
	int now=query1(rt[tr[p].l],1,n,l,r);
	if(k<=now){
		return kth(tr[p].l,nl,mid,k,l,r);
	}
	return kth(tr[p].r,mid+1,nr,k-now,l,r);
}
void modify1(int &p,int nl,int nr,int l,int r,int k){
	if(nl>l||nr<l){
		return ;
	}
	if(k==1&&(!p)){
		tot++;
		p=tot;
	}
	if(p){
		modify(rt[p],1,n,r,r,k);
	}
	if(p==0||nl==nr){
		return ;
	}
	int mid=(nl+nr)/2;
	modify1(tr[p].l,nl,mid,l,r,k);
	modify1(tr[p].r,mid+1,nr,l,r,k);
	return ;
}
int pre(int l,int r,int k){
	if(query2(root,0,1e8,0,k-1,l,r)==query2(root,0,1e8,0,-1e9,l,r)){
		return -INT_MAX;
	}
	return kth(root,0,1e8,query2(root,0,1e8,0,k-1,l,r),l,r);
}
int next(int l,int r,int k){
	if(query2(root,0,1e8,0,k,l,r)==query2(root,0,1e8,0,1e9,l,r)){
		return INT_MAX;
	}
	return kth(root,0,1e8,query2(root,0,1e8,0,k,l,r)+1,l,r);
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		modify1(root,0,1e8,a[i],i,1);
	}
	while(m--){
		int op,l,r,k;
		cin>>op;
		if(op==3){
			cin>>x>>y;
		}
		else{
			cin>>l>>r>>k;
		}
		if(op==1){
			cout<<query2(root,0,1e8,0,k-1,l,r)+1<<endl;
		}
		else if(op==2){
			cout<<kth(root,0,1e8,k,l,r)<<endl;
		}
		else if(op==3){
			modify1(root,0,1e8,a[x],x,-1);
			modify1(root,0,1e8,y,x,1);
			a[x]=y;
		}
		else if(op==4){
			cout<<pre(l,r,k)<<endl;
		}
		else{
			cout<<next(l,r,k)<<endl;
		}
	}
	return 0;
}