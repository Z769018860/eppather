#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10, M=5e5+10;
struct edge{int x, y, c;} a[M];
bool cmp(edge a, edge b) {return a.c<b.c;}
int fa[N]; 
int find(int x) {return x==fa[x]?x:fa[x]=find(fa[x]);}
int main() {
	int n, m; scanf("%d%d", &n, &m);
	for(int i=1;i<=m;i++) 
		scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].c);
	sort(a+1, a+1+m, cmp);
	for(int i=1;i<=n;i++) fa[i]=i;
	long long ans=0; int res=0; 
	for(int i=1;i<=m;i++) {
		int tx=find(a[i].x), ty=find(a[i].y);
		if(tx!=ty) {
			fa[tx]=ty; ans+=a[i].c;
			res++; if(res==n-1) break;
		}
	} 
	printf("%lld", ans);
	return 0;
}			