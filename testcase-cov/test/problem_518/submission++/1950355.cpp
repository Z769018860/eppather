#include<bits/stdc++.h>
#define N 200005
#define mod 19260817
using namespace std;
int n,m,pre[N],tot,a[N];
map<int ,int > mp;
int getc(int x){
	if(mp[x]==0) mp[x]=++tot;
	return mp[x];
}
struct node{
	int x,y,t,w;
};
vector<node> clr[N];
set<int > st[N];
set<int > ::iterator it;
long long tre[N*4],sum[N];
void build(int q,int l,int r){
	tre[q]=1;
	if(l==r) return;
	int mid=(l+r)/2;
	build(q*2,l,mid);
	build(q*2+1,mid+1,r);
}
void modify(int q,int l,int r,int x,long long y){
	if(l==r){
		sum[l]+=y;
		tre[q]=sum[l]%mod;
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid) modify(q*2,l,mid,x,y);
	else modify(q*2+1,mid+1,r,x,y);
	tre[q]=tre[q*2]*tre[q*2+1]%mod;
}
long long gets(int p,int x){
	it=st[p].lower_bound(x);
	it++;int r=*it;
	it--;it--;int l=*it;
	return 1ll*(r-x-1)*(r-x)/2+1ll*(x-l-1)*(x-l)/2-1ll*(r-l-1)*(r-l)/2;
}
void add(int x,int y){
	st[x].insert(y);
	modify(1,1,n,x,gets(x,y));
}
void del(int x,int y){
	modify(1,1,n,x,-gets(x,y));
	st[x].erase(y);
}
long long cf[N];
int main(){
	scanf("%d%d",&n,&m);
	pre[0]=1;
	for(int i=1;i<=n;i++){
		scanf("%d",&pre[i]);
		pre[i]=pre[i]+pre[i-1]+1;
	}
	for(int i=1;i<=n;i++){
		for(int j=pre[i-1]+1;j<pre[i];j++){
			scanf("%d",&a[j]);
			a[j]=getc(a[j]);
			clr[a[j]].push_back(node{i,j,0,1});
		}
	}
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		z=getc(z);
		y=pre[x-1]+y;
		if(a[y]==z) continue;
		clr[a[y]].push_back(node{x,y,i,-1});
		clr[a[y]=z].push_back(node{x,y,i,1});
	}
	for(int i=1;i<=n;i++)
		for(int j=pre[i-1]+1;j<pre[i];j++)
			clr[a[j]].push_back(node{i,j,m+1,-1});
	build(1,1,n);
	for(int i=1;i<=n;i++){
		st[i].insert(pre[i-1]);
		st[i].insert(pre[i]);
		modify(1,1,n,i,1ll*(pre[i]-pre[i-1]-1)*(pre[i]-pre[i-1])/2);
	}
	long long ans=0;
	for(int i=1;i<=tot;i++){
		cf[0]=(cf[0]+tre[1])%mod;ans=(ans+tre[1])%mod;
		for(node v:clr[i]){
			long long bef=tre[1];
			if(v.w==-1) del(v.x,v.y);
			else add(v.x,v.y);
			cf[v.t]=(cf[v.t]+tre[1]-bef+mod)%mod;
		}
	}
	for(int i=1;i<=m+1;i++) cf[i]=(cf[i]+cf[i-1])%mod;
	for(int i=0;i<=m;i++) printf("%lld\n",(ans-cf[i]+mod)%mod);
}