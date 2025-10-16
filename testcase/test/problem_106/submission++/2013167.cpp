#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int N=50010;
const ll V=1e8;
int n,m;

#define INF 0x3f3f3f3f
int tot;
struct SEG_Node{
	int ls,rs,sum;
	#define lc t[p].ls
	#define rc t[p].rs
	#define mid (L+R>>1)
}t[N*17*27];
int mknode(){
	++tot;
	return tot;
}
int a[N];
struct SEG{
	int rt;
	void pushup(int p){
		t[p].sum = t[lc].sum+t[rc].sum;
	}
	void modify(int &p,ll L,ll R,ll x,int v){
		if(!p)p=mknode();

		if(L==R){
			t[p].sum += v;
			return;
		}
		if(x<=mid)modify(lc,L,mid,x,v);
		else modify(rc,mid+1,R,x,v);
		pushup(p);
	}
	
		
		
		
	
};

struct BIT{
	SEG c[N];
	#define lowbit(x) ((x)&-(x))
	void change(int x,ll v,int k){
		if(x==0)return;
		for(int i=x;i<=n;i+=lowbit(i)){
			c[i].modify(c[i].rt,0,V,v,k);
			
		}
	}
	void find(int x,vector<int> &a){
		for(;x;x-=lowbit(x)){
			a.emplace_back(c[x].rt);
		}
	}
}bit;
int lsum(vector<int> a,vector<int> b){
	int res=0;
	for(auto x:a)
		if(x&&t[x].ls)res -= t[t[x].ls].sum;
	for(auto x:b)
		if(x&&t[x].ls)res += t[t[x].ls].sum;
	return res;
}
int rsum(vector<int> a,vector<int> b){
	int res=0;
	for(auto x:a)
		if(x&&t[x].rs)res -= t[t[x].rs].sum;
	for(auto x:b)
		if(x&&t[x].rs)res += t[t[x].rs].sum;
	return res;
}
void goL(vector<int> &a,vector<int> &b){
	for(int i=0;i<a.size();++i)
		a[i]=t[a[i]].ls;
	for(int i=0;i<b.size();++i)
		b[i]=t[b[i]].ls;
}
void goR(vector<int> &a,vector<int> &b){
	for(int i=0;i<a.size();++i)
		a[i]=t[a[i]].rs;
	for(int i=0;i<b.size();++i)
		b[i]=t[b[i]].rs;
}
int krank(ll l,ll r,ll k){
	vector<int> a,b;
	bit.find(l-1,a);
	bit.find(r,b);
	ll L=0,R=V;
	int res=1;
	while(L<=R){
		if(L==R)return res;
		if(k>mid)res += lsum(a,b);

		if(k<=mid)goL(a,b),R=mid;
		else goR(a,b),L=mid+1;
	}
}
int kth(int l,int r,int k){
	vector<int> a,b;
	bit.find(l-1,a);
	bit.find(r,b);
	ll L=0,R=V;
	int res=0;
	while(L<=R){
		if(L==R)return L;
		int tmp=lsum(a,b);
		if(k<=tmp)R=mid,goL(a,b);
		else L=mid+1,k-=tmp,goR(a,b);
	}
}
int pre(int l,int r,int k){
	vector<int> a,b;
	bit.find(l-1,a);
	bit.find(r,b);
	stack<vector<int>> stka;
	stack<vector<int>> stkb;
	stack<int> state;
	stack<pair<int,int>> LR;
	stka.emplace(a);
	stkb.emplace(b);
	LR.emplace(0,V);
	state.emplace(2);
	while(!stka.empty()){
		int L=LR.top().first,R=LR.top().second;
		int s=state.top();state.pop();
		a=stka.top();
		b=stkb.top();
		if(L==R)return L;
		if(s==2){
			state.emplace(--s);
			if(k-1>mid&&rsum(a,b)){
				goR(a,b);
				stka.emplace(a);
				stkb.emplace(b);
				LR.emplace(mid+1,R);
				state.emplace(2);
			}
			continue;
		}
		if(s==1){
			state.emplace(--s);
			if(k-1>=L&&lsum(a,b)){
				goL(a,b);
				stka.emplace(a);
				stkb.emplace(b);
				LR.emplace(L,mid);
				state.emplace(2);
			}
			continue;
		}
		stka.pop();
		stkb.pop();
		LR.pop();
	}
	return -2147483647;
}
int suf(int l,int r,int k){
	vector<int> a,b;
	bit.find(l-1,a);
	bit.find(r,b);
	stack<vector<int>> stka;
	stack<vector<int>> stkb;
	stack<int> state;
	stack<pair<int,int>> LR;
	stka.emplace(a);
	stkb.emplace(b);
	LR.emplace(0,V);
	state.emplace(2);
	while(!stka.empty()){
		int L=LR.top().first,R=LR.top().second;
		int s=state.top();state.pop();
		a=stka.top();
		b=stkb.top();
		if(L==R)return L;
		if(s==2){
			state.emplace(--s);
			if(k+1<=mid&&lsum(a,b)){
				goL(a,b);
				stka.emplace(a);
				stkb.emplace(b);
				LR.emplace(L,mid);
				state.emplace(2);
			}
			continue;
		}
		if(s==1){
			state.emplace(--s);
			if(k+1<=R&&rsum(a,b)){
				goR(a,b);
				stka.emplace(a);
				stkb.emplace(b);
				LR.emplace(mid+1,R);
				state.emplace(2);
			}
			continue;
		}
		stka.pop();
		stkb.pop();
		LR.pop();
	}
	return 2147483647;
}
int main(){



	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>a[i];

		bit.change(i,a[i],1);
	}
	for(int i=1;i<=m;++i){
		int opt;cin>>opt;

		if(opt==1){
			ll l,r,k;
			cin>>l>>r>>k;
			printf("%d\n",krank(l,r,k));
		}else if(opt==2){
 			int l,r,k;
 			cin>>l>>r>>k;
 			printf("%d\n",kth(l,r,k));
		}else if(opt==3){
			int pos,k;cin>>pos>>k;
			bit.change(pos,a[pos],-1);
			a[pos]=k;
			bit.change(pos,a[pos],1);
		}else if(opt==4){
			int l,r,k;
			cin>>l>>r>>k;
			printf("%d\n",pre(l,r,k));
		}else{
			int l,r,k;
			cin>>l>>r>>k;
			printf("%d\n",suf(l,r,k));
		}
	}
	cerr<<(double)clock()/CLOCKS_PER_SEC<<"s"<<endl;
	return 0;
}