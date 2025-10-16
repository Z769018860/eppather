#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#define int long long
#define endl '\n'
#define ls (now<<1)
#define rs (now<<1|1)
#define mid ((l+r)>>1)
#define midd ((t[now].l+t[now].r)>>1)
using namespace std;
const int N=5e5+10;
struct tree{
	int l,r;
	int mi,miw;
	int tag;
}t[N<<2];
vector<int>ansl;
struct Data{
	int l,r,v,where;
	Data(int x,int y,int z,int k){
		l=x,r=y,v=z,where=k;
	}
	bool operator < (const Data &a)const 
	{
		return v>a.v;
	}
};


int a[N];
priority_queue<Data> q;
void pushup(int now){
	if(t[rs].mi>t[ls].mi){
		t[now].mi=t[ls].mi;
		t[now].miw=t[ls].miw;
	}
	else{
		t[now].mi=t[rs].mi;
		t[now].miw=t[rs].miw;
	}
	return ;
}
void modif(int o,int v){
	t[o].mi=max(t[o].mi,v);
	t[o].tag=v;
}
void pushdown(int now){
	if(t[now].tag){
		modif(ls,t[now].tag);
		modif(rs,t[now].tag);
		t[now].tag=0;
	}
	return;
}
void build(int now,int l,int r){
	t[now].l=l,t[now].r=r;
	if(l==r){
		t[now].mi=a[l],t[now].miw=l;
		return ;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	pushup(now);
	return ;
}
void update(int now,int l,int r,int k){
	if(t[now].l>=l and t[now].r<=r){	
		modif(now,k);
		return;	
	}
	pushdown(now);
	if(l<=midd)update(ls,l,r,k);
	if(r>midd)update(rs,l,r,k);
	pushup(now);
	return;
}
pair<int,int> query(int now,int l,int r){
	if(t[now].l>=l and t[now].r<=r){
		return {t[now].mi,t[now].miw};
	}
	pushdown(now);
	pair<int,int> ans={1e9,-1};
	if(l<=midd) ans=min(ans,query(ls,l,r));
	if(r>midd) ans=min(ans,query(rs,l,r));
	pushup(now);
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,m;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	cin>>m;
	for(int _=1;_<=m;_++){
	
		int opt,a,b,k,x;
		cin>>opt>>a>>b>>k;

		if(opt==1){
			update(1,a,b,k);


		}else{

			cin>>x;



			if(b-a+1<x){
				cout<<"-1"<<endl;
				continue;
			}
			pair<int,int> ans=query(1,a,b);
			while(!q.empty())q.pop();
			ansl.clear();
			q.push(Data(a,b,ans.first,ans.second));
			for(int i=1;i<=x;i++){
				Data pos=q.top();
			
				q.pop();
				if(pos.v<k){
					ansl.push_back(pos.v);
				} 
				else break;	
				if(pos.l<pos.where){
					pair<int,int> now=query(1,pos.l,pos.where-1);
					q.push(Data(pos.l,pos.where-1,now.first,now.second));
				}
				if(pos.r>pos.where){
					pair<int,int> now=query(1,pos.where+1,pos.r);
					q.push(Data(pos.where+1,pos.r,now.first,now.second));
				}
			}int siz=ansl.size();
		
			if(siz<x){
		
		
		
				cout<<-1<<endl;
				continue;
			}
			for(auto it:ansl)cout<<it<<" ";
			cout<<endl;
			
		}
	}
	return 0;
}