#include<bits/stdc++.h>
using namespace std;
int m,n,ttt,x[1000003],nn,y[1000003],d[500003],c[1000003],a[500003],b[500003],mm;
vector<int>g[500003];
int ans;
void dfs(int x,int col,int p,int lst){
	if(lst==x)
		return;
	if(lst==-1)lst=x;
	for(auto i:g[x])
		if(d[y[i]]&&(i^p)!=1){
			c[i]=col<<1;
			c[i^1]=col<<1|1;
			dfs(y[i],col,i,lst);
			break;
		}
	d[x]-=2;
}
int ord,l[500003],r[500003],tp[500003],pa[500003],L[500003],R[500003],tt;
int w[1000003];
void DFS(int x,int p,int nw){
	l[x]=ord++;
	tp[x]=nw;
	for(auto i:g[x])
		if((i^p)!=1)
			c[i]=-2,c[i^1]=-2,
			DFS(y[i],i,nw);
	r[x]=ord-1;
}
int mp[1000003],nnn;
int sum[500003];
void add(int col,int w){
	ans-=max(sum[col],sum[col^1]);
	sum[col]+=w;
	ans+=max(sum[col],sum[col^1]);
}
int maxn[1048576],lzy[1048576];
void pushdown(int k){
	lzy[k<<1]+=lzy[k];
	maxn[k<<1]+=lzy[k];
	lzy[k<<1|1]+=lzy[k];
	maxn[k<<1|1]+=lzy[k];
	lzy[k]=0;
}
void pushup(int k){
	maxn[k]=max(maxn[k<<1],maxn[k<<1|1]);
}
void add(int _l,int _r,int l,int r,int k,int w){
	if(l>_r||r<_l)return;
	if(l<=_l&&_r<=r){
		lzy[k]+=w;
		maxn[k]+=w;
		return;
	}
	pushdown(k);
	add(_l,_l+_r>>1,l,r,k<<1,w);
	add(_l+_r+2>>1,_r,l,r,k<<1|1,w);
	pushup(k);
}
int query(int _l,int _r,int l,int r,int k){
	if(l>_r||r<_l)return -1e18;
	if(l<=_l&&_r<=r)return maxn[k];
	pushdown(k);
	return max(query(_l,_l+_r>>1,l,r,k<<1),query(_l+_r+2>>1,_r,l,r,k<<1|1));
}
void add(int x,int y,int w){
	if(pa[y]==x)
		ans+=w,add(y,x,-w);
	else{
		ans-=query(0,524287,L[tp[x]],R[tp[x]],1);
		add(0,524287,l[x],r[x],1,w);
		ans+=query(0,524287,L[tp[x]],R[tp[x]],1);
	}
}
bool used[1000003];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	memset(pa,-1,sizeof(pa));
	cin>>m>>n>>ttt;
	for(int i=0;i<m;i++)
		cin>>a[i];
	for(int i=0;i<m;i++){
		cin>>b[i];
		int X=(a[i]-b[i]+n)%n,Y=(a[i]+b[i])%n;
		x[nn]=max(X,Y);
		d[x[nn]]++;
		g[x[nn]].push_back(nn);
		y[nn++]=min(X,Y);
		x[nn]=min(X,Y);
		d[x[nn]]++;
		g[x[nn]].push_back(nn);
		y[nn++]=max(X,Y);
	}
	vector<int>V,rt;
	for(int i=0;i<n;i++)
		if(d[i]==1)
			V.push_back(i);
	while(V.size()){
		int x=V.back();
		V.pop_back();
		bool fnd=0;
		for(auto i:g[x])
			if(!used[i>>1]){
				pa[x]=y[i];
				used[i>>1]=1;
				d[y[i]]--;
				if(d[y[i]]==1)
					V.push_back(y[i]);
				fnd=1;
			}
		d[x]=0;
		if(!fnd)
			rt.push_back(x);
	}
	memset(c,-1,sizeof(c));
	for(int i=0;i<n;i++)
		if(d[i]==2)
			dfs(i,mm++,-1,-1);
	int tt=0;
	for(auto i:rt){
		DFS(i,-1,tt);
		L[tt]=l[i];R[tt]=r[i];
		tt++;
	}
	for(int i=0;i<nn;i++){
		mp[nnn++]=i;
		if(x[i]==y[i]||c[i]==-1){
			cin>>w[i];
			if(x[i]==y[i]||pa[y[i]]==x[i])
				ans+=w[i];
			i+=(x[i]==y[i]);
		}else{
			cin>>w[i];
			if(c[i]==-2)
				add(x[i],y[i],w[i]);
			else
				add(c[i],w[i]);
		}
	}
	cout<<ans<<'\n';
	int T;
	cin>>T;
	while(T--){
		int i,t;
		cin>>i>>t;
		i-=ttt*ans;t-=ttt*ans;
		i=mp[i-1];
		t-=w[i];
		w[i]+=t;
		if(x[i]==y[i]||c[i]==-1){
			if(x[i]==y[i]||pa[y[i]]==x[i])
				ans+=t;
		}else{
			if(c[i]==-2)
				add(x[i],y[i],t);
			else
				add(c[i],t);
		}cout<<ans<<'\n';
	}
}