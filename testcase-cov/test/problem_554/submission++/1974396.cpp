#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
typedef long long ll;
int n,q,a[N],st[N],pl[N],pr[N],nx[N],p[N],cnt,ans1[N];
vector<int>e[N];
vector<pair<int,int> >e3[N],e4[N];
bool du[N],ban[N];
ll ans2[N],c1[N],c2[N];
void add(int x,int y){
	e[x].push_back(y),e[y].push_back(x);
}
void calc(){
	if(n==1)return puts("1"),void();
	bool f1=true,f2=true;
	for(int i=1;i<n;++i)a[i]<a[i+1]?f1=false:f2=false;
	if(f1||f2)return puts("2"),void();
	for(int i=1;i<=n;++i)if(pl[i]&&pr[i]<=n&&e[i].size()&1)return puts("4"),void();
	puts("3");
}
void chg(int x,int l,int r){
	if(!ban[x])cnt-=du[x];
	ban[x]=pl[x]<l||pr[x]>r;
	du[x]^=1;
	if(!ban[x])cnt+=du[x];
}
void init(){
	int i,j,tp;
	for(i=1,tp=0;i<=n;++i){
		while(tp&&a[st[tp]]<a[i])--tp;
		if(tp)add(i,st[tp]),pl[i]=st[tp];
		else pl[i]=0;
		st[++tp]=i;
	}
	for(i=1,tp=0;i<=n;++i){
		while(tp&&a[st[tp]]>a[i])--tp;
		if(tp)add(i,st[tp]),pl[i]=min(pl[i],st[tp]);
		else pl[i]=0;
		st[++tp]=i;
	}
	for(i=n,tp=0;i;--i){
		while(tp&&a[st[tp]]<a[i])--tp;
		if(tp)add(i,st[tp]),pr[i]=st[tp];
		else pr[i]=n+1;
		st[++tp]=i;
	}
	for(i=n,tp=0;i;--i){
		while(tp&&a[st[tp]]>a[i])--tp;
		if(tp)add(i,st[tp]),pr[i]=max(pr[i],st[tp]);
		else pr[i]=n+1;
		st[++tp]=i;
	}
	for(i=1;i<=n;++i){
		sort(e[i].begin(),e[i].end());
		e[i].erase(unique(e[i].begin(),e[i].end()),e[i].end());
	}
	calc();
	nx[1]=nx[2]=1;
	for(i=3;i<=n;++i){
		if((a[i]<a[i-1])==(a[i-1]<a[i-2]))nx[i]=nx[i-1];
		else nx[i]=i-1;
	}
	for(i=j=1;i<=n;++i){
		ban[i]=true;
		for(auto v:e[i])if(j<=v&&v<=i)du[i]^=1,chg(v,j,i);
		while(cnt){
			++j;
			for(auto v:e[j-1])if(j<=v&&v<=i)chg(v,j,i);
		}
		p[i]=j;
	}
}
void upd(int x){
	for(int i=n-x+1;i<=n;i+=i&-i)++c1[i],c2[i]+=x;
}
ll sum(int x){
	ll res=0;
	for(int i=n-x+1;i;i-=i&-i)res+=c2[i]-c1[i]*x;
	return res;
}
void solve(int *p,vector<pair<int,int>>*g){
	for(int i=1;i<=n;++i){
		upd(p[i]);
		for(auto [x,y]:g[i])ans2[y]=sum(x);
	}
}
int main(){
	if(scanf("%d",&n)==EOF)return 0;
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	init();
	scanf("%d",&q);
	for(int i=1,l,r;i<=q;++i){
		scanf("%d%d",&l,&r);
		if(l==r){
			ans1[i]=ans2[i]=1;
			continue;
		}
		if(l>=p[r]){
			if(l>=nx[r])ans1[i]=2,ans2[i]=1ll*(r-l+1)*(r-l)/2;
			else ans1[i]=3,e3[r].push_back({l,i});
		}else ans1[i]=4,e4[r].push_back({l,i});
	}
	solve(p,e4);
	memset(c1,0,sizeof(c1));
	memset(c2,0,sizeof(c2));
	solve(nx,e3);
	for(int i=1;i<=q;++i)printf("%d %lld\n",ans1[i],ans2[i]);
	return 0;
}