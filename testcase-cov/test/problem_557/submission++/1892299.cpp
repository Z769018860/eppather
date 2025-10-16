#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
const int N=1e5+5,S=300,M=405;
unordered_map<int,int> mp;
int n,m,a[N],id[N],tot;
int cnt[M][N*2],la;
int L[M],R[M],lz[M]; 
int d(int x) {return mp[x]?mp[x]:(mp[x]=++tot);}
void cg(int l,int r,int x) {
	int k=id[l];
	if(lz[k]==-1) {
		for(int i=l;i<=r;i++) {
			cnt[k][a[i]]--;
			cnt[k][x]++;a[i]=x;
		}
	} else {
		for(int i=L[k];i<l;i++) a[i]=lz[k];
		for(int i=l;i<=r;i++) a[i]=x;
		for(int i=r+1;i<=R[k];i++) a[i]=lz[k];
		cnt[k][x]+=r-l+1;cnt[k][lz[k]]-=r-l+1;lz[k]=-1;
	}
}
void cg1(int k,int x) {
	if(lz[k]!=-1) cnt[k][lz[k]]=0; 
	else for(int i=L[k];i<=R[k];i++) cnt[k][a[i]]--;
	cnt[k][x]=R[k]-L[k]+1;
	lz[k]=x;
}
int sz(int l,int r,int x) {
	int k=id[l],cnt=0;
	if(lz[k]!=-1) {
		if(x==lz[k]) return r-l+1;
		return 0;
	}
	for(int i=l;i<=r;i++)
		if(a[i]==x) cnt++;
	return cnt;
}
int query(int l,int r,int x,int y) {
	int k=id[l],cnt=0;
	if(lz[k]!=-1) {
		if(x==lz[k]&&(r-l+1)>=y) return l+y-1;
		return 0;
	}
	for(int i=l;i<=r;i++)
		if(a[i]==x) {
			cnt++;
			if(cnt==y) return i;
		}
	return 0;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) {
		id[i]=(i-1)/S+1;
		a[i]=d(a[i]);
		cnt[id[i]][a[i]]++;
	}
	for(int l=1,r=S,i=1;l<=n;l+=S,r+=S,i++) L[i]=l,R[i]=min(r,n),lz[i]=-1;
	while(m--) {
		char s[10];
		int l,r,x,y;
		scanf("%s%d%d%d",s,&l,&r,&x);l^=la,r^=la,x^=la;
		if(s[0]=='M') {
			x=d(x);
			if(id[l]==id[r]) cg(l,r,x);
			else {
				int u=id[l]+1,v=id[r]-1;
				cg(l,R[id[l]],x);
				for(int i=u;i<=v;i++) cg1(i,x);
				cg(L[id[r]],r,x);
			}
		} 
		else {
			scanf("%d",&y);y^=la;y=d(y);
			if(id[l]==id[r]) printf("%d\n",la=query(l,r,y,x));
			else {
				int u=id[l]+1,v=id[r]-1,e;
				if(x<=(e=sz(l,R[id[l]],y))) {
					printf("%d\n",la=query(l,R[id[l]],y,x));
					continue;
				}
				x-=e;
				for(int i=u;i<=v;i++) {
					if(x<=cnt[i][y]) {
						printf("%d\n",la=query(L[i],R[i],y,x));
						x-=cnt[i][y];
						break;
					}
					x-=cnt[i][y];
				}
				if(x>0) printf("%d\n",la=query(L[id[r]],r,y,x));
			}
		}
	}
}