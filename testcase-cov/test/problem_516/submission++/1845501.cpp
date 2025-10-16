#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct Kjr{
	int l,r;
}q[N];
int n,m,a[N],ans=2147483647;
unordered_map<int,set<int> > s; 
inline void merge(int x,int y){
	if(s[x].size()>s[y].size()) swap(s[x],s[y]);
	for(auto p:s[x]){
		auto it=s[y].insert(p).first,it1=it;
		if(it!=s[y].begin()) it--,ans=min(ans,p-(*it));
		it1++;
		if(it1!=s[y].end()) ans=min(ans,(*it1)-p);
	}
	s[x].clear();
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",a+i),s[a[i]].insert(i);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&q[i].l,&q[i].r);
		int x=q[i].l,y=q[i].r;
		if(!s[x].size()||x==y) printf("%d\n",ans);
		else if(!s[y].size()) printf("%d\n",ans),s[y]=s[x],s[x].clear();
		else merge(x,y),printf("%d\n",ans);
	}
	return 0;
}