#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int N=2e5+5;
int n,K;
struct node{
	int a,b,c,v,ans;
	node(){a=b=c=v=ans=0;}
	node(int _a,int _b,int _c,int _v,int _ans){a=_a,b=_b,c=_c,v=_v,ans=_ans;}
	bool operator <(const node &_){return a!=_.a?a<_.a:(b!=_.b?b<_.b:c<_.c);}
};
node p[N],q[N],lq[N],rq[N];int tot;
int c[N],f[N];
void add(int x,int v){
	for(;x<=K;x+=x&-x)
		c[x]+=v;
}
int ask(int x){
	int ans=0;
	for(;x;x-=x&-x)
		ans+=c[x];
	return ans;
}
void solve(int l,int r,int ql,int qr){
	if(l==r){
		for(int i=ql;i<=qr;i++){
			q[i].ans+=ask(q[i].c);
			add(q[i].c,q[i].v);
		}
		for(int i=ql;i<=qr;i++)
			add(q[i].c,-q[i].v);
		return;
	}
	int mid=(l+r)>>1,lp=0,rp=0;
	for(int i=ql;i<=qr;i++)
		if(q[i].b<=mid){
			add(q[i].c,q[i].v);
			lq[++lp]=q[i];
		}
		else{
			q[i].ans+=ask(q[i].c);
			rq[++rp]=q[i];
		}
	for(int i=ql;i<=qr;i++)
		if(q[i].b<=mid)
			add(q[i].c,-q[i].v);
	for(int i=1;i<=lp;i++)q[ql+i-1]=lq[i];
	for(int i=1;i<=rp;i++)q[ql+lp+i-1]=rq[i];
	solve(l,mid,ql,ql+lp-1),solve(mid+1,r,ql+lp,qr);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>K;
	for(int i=1;i<=n;i++){
		int a,b,c;
		cin>>a>>b>>c;
		p[i]=node(a,b,c,1,0);
	}
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++)
		if(p[i-1]<p[i])q[++tot]=p[i];
		else ++q[tot].v,++q[tot].ans;
	solve(1,K,1,tot);
	for(int i=1;i<=tot;i++)f[q[i].ans]+=q[i].v;
	for(int i=0;i<n;i++)cout<<f[i]<<'\n';
	return 0;
}