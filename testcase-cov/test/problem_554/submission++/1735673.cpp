#include<bits/stdc++.h>
using namespace std;
#define MAXN 310001
int n,m,a[MAXN],gtl[MAXN],lsl[MAXN],maxl[MAXN];
int lgt[MAXN],lls[MAXN],rgt[MAXN],rls[MAXN],vis[MAXN];
int deg[MAXN],minr[MAXN];
long long sumr[MAXN],suml[MAXN];
vector<int>g[MAXN];
set<int>has[MAXN],cur;
deque<int>qmin,qmax;
inline void addEdge(int from,int to) {
	if(has[from].find(to)!=has[from].end()) return;
	if(from>to) swap(from,to);
	if(a[from]>a[to]) ++lgt[to],++rls[from];
	if(a[to]>a[from]) ++rgt[from],++lls[to];
	++deg[from],++deg[to];
	has[from].insert(to);has[to].insert(from);
	g[from].push_back(to);g[to].push_back(from);
}
inline bool check1() {
	for(int i=1;i<=n;i++) {
		if((deg[i]&1)&&lls[i]&&lgt[i]&&rls[i]&&rgt[i]) return true;
	}
	return false;
}
inline void cleartag() {
	memset(deg,0,sizeof(deg));
	memset(lls,0,sizeof(lls));
	memset(lgt,0,sizeof(lgt));
	memset(rls,0,sizeof(rls));
	memset(rgt,0,sizeof(rgt));
}
inline bool checkPoint(int u) {
	return (deg[u]&1)&&lls[u]&&lgt[u]&&rls[u]&&rgt[u];
}
inline void checkEdge(int from,int to) {
	if(from>to) swap(from,to);
	if(a[from]>a[to]) ++lgt[to],++rls[from];
	if(a[to]>a[from]) ++rgt[from],++lls[to];
	++deg[from],++deg[to];
	if(checkPoint(from)) cur.insert(from);
	else if(cur.find(from)!=cur.end()) cur.erase(from);
	if(checkPoint(to)) cur.insert(to);
	else if(cur.find(to)!=cur.end()) cur.erase(to);
}
inline void delEdge(int from,int to) {
	if(from>to) swap(from,to);
	if(a[from]>a[to]) --lgt[to],--rls[from];
	if(a[to]>a[from]) --rgt[from],--lls[to];
	--deg[from],--deg[to];
	if(checkPoint(from)) cur.insert(from);
	else if(cur.find(from)!=cur.end()) cur.erase(from);
	if(checkPoint(to)) cur.insert(to);
	else if(cur.find(to)!=cur.end()) cur.erase(to);
}
inline bool addR(int u) {
	vis[u]=true;
	for(auto v:g[u]) {
		if(!vis[v]) continue;
		checkEdge(u,v);
	}
	if(cur.size()) return true;
	return false;
}
inline bool delL(int u) {
	vis[u]=false;
	for(auto v:g[u]) {
		if(!vis[v]) continue;
		delEdge(u,v);
	}
	if(cur.size()) return true;
	return false;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) {
		while(!qmin.empty()&&a[qmin.back()]>a[i]) addEdge(qmin.back(),i),qmin.pop_back();
		while(!qmax.empty()&&a[qmax.back()]<a[i]) addEdge(i,qmax.back()),qmax.pop_back();
		if(!qmin.empty()) addEdge(qmin.back(),i);
		if(!qmax.empty()) addEdge(i,qmax.back());
		qmin.push_back(i),qmax.push_back(i);
	}
	for(int i=1;i<=n;i++) gtl[i]=lsl[i]=i,maxl[i]=1;
	for(int i=n-1;i>=1;i--) {
		if(a[i+1]>a[i]) gtl[i]=gtl[i+1];
		if(a[i+1]<a[i]) lsl[i]=lsl[i+1];
	} 
	for(int i=1;i<=n;i++) maxl[i]=max(gtl[i],lsl[i]);
	if(n==1) cout<<"1\n";
	else if(maxl[1]==n) cout<<"2\n";
	else if(!check1()) cout<<"3\n";
	else cout<<"4\n";
	cleartag();
	bool flag=false;
	for(int l=1,r=0;l<=n;l++) {
		while(r<=n&&!flag) {
			if(flag=addR(++r)) break;
		}
		minr[l]=r;
		flag=delL(l);
	}
	for(int i=1;i<=n;i++) {
		suml[i]=suml[i-1]+maxl[i];
		sumr[i]=sumr[i-1]+minr[i]-1;
	}
	minr[n+1]=maxl[n+1]=0x7fffffff;
	cin>>m;
	for(int i=1;i<=m;i++) {
		int l,r;cin>>l>>r;
		if(l==r) {
			cout<<"1 1\n";continue;
		} else if(maxl[l]>=r) {
			cout<<"2 "<<1ll*(r-l)*(r-l+1)/2<<"\n";
		} else if(minr[l]>r) {
			int len=upper_bound(maxl+1,maxl+n+2,r)-l-maxl-1;
			long long sum=suml[l+len]-suml[l-1];
			cout<<"3 "<<1ll*(r-l+1+r-l+1-len)*(len+1)/2-sum+1ll*(l+l+len-2)*(len+1)/2<<"\n";
		} else {
			int len=upper_bound(minr+1,minr+n+2,r)-l-minr-1;
			long long sum=sumr[l+len]-sumr[l-1];
			cout<<"4 "<<1ll*(r-l+1+r-l+1-len)*(len+1)/2-sum+1ll*(l+l+len-2)*(len+1)/2<<"\n"; 
		}
	}
	cout<<flush;
	return 0;
}
