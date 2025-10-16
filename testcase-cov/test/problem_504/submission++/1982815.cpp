#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pi pair<int,int>
#define fi first
#define se second
const int N=5e5+10,inf=1e9+7;
int n,a[N<<2],mx[N<<2],mn[N<<2],pos[N<<2];
void pushup(int p){
	if(mn[p*2]<mn[p*2+1]) pos[p]=pos[p*2];
	else pos[p]=pos[p*2+1];
	mn[p]=min(mn[p*2],mn[p*2+1]);
	mn[p]=max(mn[p],mx[p]);
}
void pushdown(int p){
	mx[p*2]=max(mx[p*2],mx[p]);
	mx[p*2+1]=max(mx[p*2+1],mx[p]);
	mn[p*2]=max(mx[p],mn[p*2]);
	mn[p*2+1]=max(mx[p],mn[p*2+1]);

}
void build(int p,int l,int r){
	if(l==r){
		mx[p]=0,mn[p]=a[l],pos[p]=l;
		return ;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	pushup(p);
}
void modifymax(int p,int l,int r,int x,int y,int k){
	if(l>y||r<x) return ;
	if(x<=l&&r<=y){
		mx[p]=max(mx[p],k);
		mn[p]=max(mn[p],mx[p]);
		return ;
	}
	pushdown(p);
	int mid=(l+r)/2;
	modifymax(p*2,l,mid,x,y,k);
	modifymax(p*2+1,mid+1,r,x,y,k);
	pushup(p);
}
void modify(int p,int l,int r,int x,int y){
	if(l>x||r<x) return ;
	if(l==r){
		mn[p]+=y;
		pos[p]=l;
		return ;
	}
	pushdown(p);
	int mid=(l+r)/2;
	modify(p*2,l,mid,x,y);
	modify(p*2+1,mid+1,r,x,y);
	pushup(p);
}
pi query(int p,int l,int r,int x,int y){
	if(l>y||r<x) return {0,inf*2};
	if(x<=l&&r<=y) return {pos[p],mn[p]};
	pushdown(p);
	int mid=(l+r)/2;
	pi q1=query(p*2,l,mid,x,y),q2=query(p*2+1,mid+1,r,x,y),q3;
	if(q1.se>q2.se) q3.fi=q2.fi;
	else q3.fi=q1.fi;
	q3.se=min(q1.se,q2.se);
	return q3;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build(1,1,n);
	int m;
	cin>>m;
	while(m--){
		int op,a,b,k,x;
		cin>>op>>a>>b>>k;
	
		if(op==1) modifymax(1,1,n,a,b,k);
		else{
			cin>>x;
			int cnt=0;
			queue<int> q,q2;
			while(cnt<x){
				pi q1=query(1,1,n,a,b);
				if(q1.se>=k) break;
				cnt++;
				modify(1,1,n,q1.fi,inf);
				q.push(q1.se),q2.push(q1.fi);
			}
			if(cnt<x){
				cout<<-1<<endl;
				while(!q.empty()){
					modify(1,1,n,q2.front(),-inf);
					q.pop(),q2.pop();
				}
			}else{
				while(!q.empty()){
					modify(1,1,n,q2.front(),-inf);
					cout<<q.front()<<" ";
					q.pop(),q2.pop();
				}
				cout<<endl;
			}
		}
	}
	return 0;
}